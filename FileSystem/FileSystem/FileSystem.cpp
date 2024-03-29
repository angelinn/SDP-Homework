#include "FileSystem.h"
#include "FileSystemException.h"
#include <sys/stat.h>
#include <direct.h>
#include "dirent/dirent.h"
#include "ReadState.h"

typedef unsigned char byte;

///
/// Sets default values for core variables
///
FileSystem::FileSystem() : treeAt(-1), lastFragmentID(-1), totalSize(0)
{  }

///
/// Upon destroying the object, all the information is serialized
/// If the destructor is not called, the data will be lost
///
FileSystem::~FileSystem()
{
	writeCoreData();
	file.close();
}

///
/// Serializes the needed data to boot up the system
///
void FileSystem::writeCoreData()
{
	file.seekp(0, std::ios::end);
	treeAt = file.tellp();

	files.serialize(file);
	deletedSectors.serializeBuiltInType(file);
	file.write(reinterpret_cast<const char*>(&treeAt), sizeof(size_t));
	file.write(reinterpret_cast<const char*>(&lastFragmentID), sizeof(int));
	file.write(reinterpret_cast<const char*>(&totalSize), sizeof(size_t));
}

///
/// Deserializes the needed data to boot up the system
///

void FileSystem::readCoreData()
{
	int variables = 3;

	file.seekg(-static_cast<int>(variables * sizeof(int)), std::ios::end);

	file.read(reinterpret_cast<char*>(&treeAt), sizeof(size_t));
	file.read(reinterpret_cast<char*>(&lastFragmentID), sizeof(int));
	file.read(reinterpret_cast<char*>(&totalSize), sizeof(size_t));

	files.deserialize(file, treeAt);
	deletedSectors.deserializeBuiltInType(file);
}

///
/// Creates or boots already existing file system
///
void FileSystem::create(const std::string& path, bool newFS)
{
	if (newFS)
	{
		file.open(path, std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc);
		if (!file)
			throw FileOpenError("Can't open file in create() method.");

		files.setRoot();
	}
	else
	{
		file.open(path, std::ios::in | std::ios::out | std::ios::binary);
		if (!file)
			throw FileOpenError("Can't open file in create() method.");

		readCoreData();
	}
}

///
/// Writes a byte array to the file system
///
WriteState FileSystem::writeToFS(const byte* content, size_t size)
{
	WriteState state;
	state.lastSectorID = getNextSectorID();

	do
	{
		file.seekp(getNextSectorID() * SectorInfo::SECTOR_SIZE, std::ios::beg);
		moveTonextSectorID();
	}
	while (!writeCore(content, size, state));

	return state;
}

///
/// Appends a byte array to the sector that the file points at
/// (you must seekp() before using this method)
/// 
void FileSystem::append(const byte* content, size_t size, SectorInfo& info)
{
	file.seekp(-static_cast<int>(SectorInfo::AVAILABLE_SIZE() - info.size), std::ios::cur);
	file.write(reinterpret_cast<const char*>(content), size * sizeof(byte));

	info.size += size;

	if (info.size != SectorInfo::AVAILABLE_SIZE())
	{
		file.seekp(info.freeSpace() - 1, std::ios::cur);
		file.write(reinterpret_cast<const char*>(&NULL_BYTE), sizeof(byte));
	}
	file.seekp(-static_cast<int>(SectorInfo::SECTOR_SIZE), std::ios::cur);

	info.serialize(file);
	file.seekp(SectorInfo::SECTOR_SIZE - SectorInfo::informationSize(), std::ios::cur);
}

///
/// Writes a byte array into a single sector of the file system
/// 
bool FileSystem::writeCore(const byte*& content, size_t& size, WriteState& state)
{

	state.info.nextSector = getNextSectorID();
	//std::cout << "Next: " << state.info.nextSector << std::endl;

	if (size > SectorInfo::AVAILABLE_SIZE())
	{
		state.info.size = SectorInfo::AVAILABLE_SIZE();
		state.info.serialize(file);

		file.write(reinterpret_cast<const char*>(content), state.info.size * sizeof(byte));
		size -= state.info.size;
		content += state.info.size;

		return false;
	}

	else
	{
		state.info.size = size;
		state.info.nextSector = SectorInfo::noNext;
		state.info.serialize(file);

		if (content)
			file.write(reinterpret_cast<const char*>(content), state.info.size * sizeof(byte));

		if (state.info.freeSpace())
		{
			file.seekp(state.info.freeSpace() - 1, std::ios::cur);
			file.write(reinterpret_cast<const char*>(&NULL_BYTE), sizeof(byte));
		}

		return true;
	}
}

///
/// Returns the next free fragment ID
/// 
inline int FileSystem::getNextSectorID() const
{
	return deletedSectors.isEmpty() ? lastFragmentID + 1 : deletedSectors.peek();
}

///
/// Sets the next fragment ID
///
void FileSystem::moveTonextSectorID()
{
	if (deletedSectors.isEmpty())
		++lastFragmentID;
	else
		deletedSectors.dequeue();
}

///
/// Adds a file with size of zero to the file system
///
void FileSystem::addEmptyFile(const std::string& file)
{
	stringPair pair = splitPathAndName(file);
	File* empty = new File(pair.second, getNextSectorID());
	empty->setSize(0);

	writeToFS(NULL, 0);

	files.insert(pair.first, empty);
	this->file.flush();
}

///
/// Adds a dir to the file system
/// 
void FileSystem::addDirectory(const std::string& dir)
{
	stringPair pair = splitPathAndName(dir);
	files.insert(pair.first, new Directory(pair.second));
}

///
/// Moves a file or a directory from one node to another
/// 
void FileSystem::moveFile(const std::string& path, const std::string& dest)
{
	TNode* toMove = files.remove(path);

	stringPair pair = splitPathAndName(dest);
	toMove->data->setName(pair.second);

	files.moveTree(files.getNode(pair.first), toMove);
}

///
/// Exports a file from the system to the OS' file system
///
// rebuild
void FileSystem::exportFile(const std::string& path, const std::string& dest)
{
	TNode* fileNode = files.getNode(path);

	if (!fileNode)
		throw InvalidFilePath("No file found.");

	std::ofstream output(dest, std::ios::out | std::ios::binary);
	if (!output)
		throw FileOpenError("Couldn't open file for writing!");

	file.seekg(fileNode->data->getFirstSectorID() * SectorInfo::SECTOR_SIZE, std::ios::beg);

	byte* placeholder = NULL;
	allocate<byte>(placeholder, BUFFER_SIZE);
	size_t thingy = file.tellg();
	ReadState state;

	do
	{
		state = readFromFS(placeholder, BUFFER_SIZE);
		//std::cout << "read " << state.info.nextSector << std::endl;
		output.write(reinterpret_cast<const char*>(placeholder), state.filled * sizeof(byte));
	} while ((state.info.nextSector != SectorInfo::noNext) || state.wouldOverwrite);

	output.close();
	delete[] placeholder;
}

///
/// Exports a dir to the OS' file system
/// 
void FileSystem::exportDirectory(const std::string& path, const std::string& dest)
{
	TNode* dirNode = files.getNode(path);
	if (!dirNode)
		throw InvalidFilePath("Dir not found.");

	if (!dirNode->data->isDirectory())
		throw InvalidFileType("File is not a directory.");

	_mkdir(dest.c_str());

	for (ListIterator iter = dirNode->children.begin(); iter; ++iter)
	{
		if ((*iter)->data->isDirectory())
			exportDirectory(buildPath(path, (*iter)->data->getName()), buildPath(dest, (*iter)->data->getName()));
		else
			exportFile(buildPath(path, (*iter)->data->getName()), buildPath(dest, (*iter)->data->getName()));
	}

}

///
/// Reads maxSize bytes from the fileSystem.
/// seekg() must already have been set to the correct position.
/// Returns a ReadState object.
///
ReadState FileSystem::readFromFS(byte* content, size_t maxSize)
{
	ReadState state;
	state.filled = 0;

	do
	{
		if (state.filled >= BUFFER_SIZE)
			if (state.filled == BUFFER_SIZE)
				break;
			else
				throw InvalidFileOperation("filled > BUFFER_SIZE instead of equal!");

		size_t pos = file.tellg();
		state.info.deserialize(file);
		if ((state.filled + state.info.size) > BUFFER_SIZE)
		{
			file.seekg(-8, std::ios::cur);
			state.wouldOverwrite = true;
			return state;
		}

		file.read(reinterpret_cast<char*>(content), sizeof(byte) * state.info.size);
		state.filled += state.info.size;
		content += state.info.size;
		file.seekg(state.info.nextSector * SectorInfo::SECTOR_SIZE, std::ios::beg);
	} while (state.info.nextSector != SectorInfo::noNext);

	content -= state.info.size;
	state.wouldOverwrite = false;
	return state;
}

///
/// Deletes a file from the tree.
/// Puts all its sectors to the deletedSectors queue.
///
void FileSystem::deleteFile(const std::string& path)
{
	TNode* toDelete = files.getNode(path);
	if (!toDelete)
		throw InvalidFilePath("File not found!");

	if (toDelete->data->isDirectory())
		throw InvalidFileOperation("File is a directory. (file expected)");
	deleteAllSectors(toDelete->data->getFirstSectorID());
	totalSize -= toDelete->data->getSize();

	delete files.remove(path);
}

///
/// Deletes a directory from the file system
///
void FileSystem::deleteDirectory(const std::string& path)
{
	TNode* toDelete = files.getNode(path);
	if (!toDelete)
		throw InvalidFilePath("Dir not found!");

	if (!toDelete->data->isDirectory())
		throw InvalidFileType("File is not a directory.");

	for (ListIterator iter = toDelete->children.begin(); iter;)
	{
		if ((*iter)->data->isDirectory())
		{
			ListIterator deleter = iter;
			++iter;
			deleteDirectory(buildPath(path, (*deleter)->data->getName()));
			continue;
		}
		else
		{
			ListIterator deleter = iter;
			++iter;
			deleteFile(buildPath(path, (*deleter)->data->getName()));
			continue;
		}
		++iter;
	}

	delete files.remove(path);
}

///
/// Imports a file from the real FS to this one
///
void FileSystem::importFile(const std::string& path, const std::string& dest)
{
	std::ifstream input(path, std::ios::in | std::ios::binary);
	if (!input)
		throw FileOpenError("Can't open file for import!");

	size_t fileSize = File::getFileSize(input);
	input.seekg(0, std::ios::beg);
	if (!fileSize)
	{
		addEmptyFile(dest);
		return;
	}

	stringPair pair = splitPathAndName(dest);
	File* toImport = new File(pair.second, getNextSectorID());

	byte* part = NULL;
	allocate<byte>(part, BUFFER_SIZE);

	WriteState state;
	size_t readSize = BUFFER_SIZE;
	size_t sizeOnFS = 0;
	while (fileSize)
	{
		if (readSize > fileSize)
			readSize = fileSize;

		input.read(reinterpret_cast<char*>(part), readSize * sizeof(byte));
		state = writeToFS(part, readSize);

		fileSize -= readSize;
		sizeOnFS += readSize;

		if (state.info.size < SectorInfo::AVAILABLE_SIZE())
		{
			size_t bytesToWrite = fileSize > state.info.freeSpace() ? state.info.freeSpace() : fileSize;
			input.read(reinterpret_cast<char*>(part), bytesToWrite * sizeof(byte));
			append(part, bytesToWrite, state.info);
			fileSize -= bytesToWrite;
			sizeOnFS += bytesToWrite;
		}

		if (fileSize && state.info.nextSector == SectorInfo::noNext)
			setnextSector(state.info);
	}

	delete[] part;
	toImport->setLastSectorID(state.lastSectorID);
	toImport->setSize(sizeOnFS);
	files.insert(pair.first, toImport);
	totalSize += sizeOnFS;
	input.close();
}

///
/// Deletes all the sectors of the file that
/// starts at the 'at' position
///
void FileSystem::deleteAllSectors(size_t at)
{
	deletedSectors.enqueue(at);
	file.seekg(at * SectorInfo::SECTOR_SIZE, std::ios::beg);

	SectorInfo info;
	info.nextSector = INT_MAX;

	while (info.nextSector != SectorInfo::noNext)
	{
		info.deserialize(file);
		if (info.nextSector != SectorInfo::noNext)
		{
			deletedSectors.enqueue(info.nextSector);
			file.seekg(info.nextSector * SectorInfo::SECTOR_SIZE, std::ios::beg);
		}
	}
}

///
/// Copies a file from this FS back to it
/// 
void FileSystem::copyFile(const std::string& path, const std::string& dest)
{
	TNode* toCopy = files.getNode(path);
	if (!toCopy)
		throw InvalidFilePath("File not found.");

	if (toCopy->data->isDirectory())
		throw InvalidFileType("Expected a file, got a dir.");

	stringPair pair = splitPathAndName(dest);
	byte* courier = NULL;
	allocate<byte>(courier, BUFFER_SIZE);
	File* theCopy = new File(pair.second, getNextSectorID());
	theCopy->setSize(toCopy->data->getSize());

	size_t tellgPos = toCopy->data->getFirstSectorID() * SectorInfo::SECTOR_SIZE;
	ReadState state;
	WriteState writer;

	do
	{
		file.seekg(tellgPos, std::ios::beg);
		state = readFromFS(courier, BUFFER_SIZE);
		tellgPos = file.tellg();

		writer = writeToFS(courier, state.filled);

		if ((state.info.nextSector != SectorInfo::noNext) || state.wouldOverwrite)
			setnextSector(writer.info);

	} while ((state.info.nextSector != SectorInfo::noNext) || state.wouldOverwrite);

	delete[] courier;
	theCopy->setLastSectorID(writer.lastSectorID);
	files.insert(pair.first, theCopy);
}

///
/// Copies a directory from this FS back to it
///
void FileSystem::copyDirectory(const std::string& path, const std::string& dest)
{
	TNode* toCopy = files.getNode(path);
	if (!toCopy)
		throw InvalidFilePath("Directory not found.");

	if (!toCopy->data->isDirectory())
		throw InvalidFileType("File is not a directory.");

	stringPair pair = splitPathAndName(dest);
	files.insert(pair.first, new Directory(pair.second));

	for (ListIterator iter = toCopy->children.begin(); iter; ++iter)
	{
		if ((*iter)->data->isDirectory())
			copyDirectory(buildPath(path, (*iter)->data->getName()), 
						  buildPath(dest, (*iter)->data->getName()));
		else
			copyFile(buildPath(path, (*iter)->data->getName()),
					 buildPath(dest, (*iter)->data->getName()));
	}
}

///
/// Checks if the path is a directory, using the stat structure
///
bool FileSystem::isDirectory(const std::string& path) const
{
	struct stat buffer;
	stat(path.c_str(), &buffer);

	/// S_IFMT is a mask, that combined with st_mode can be compared with other masks
	return (buffer.st_mode & S_IFMT) == S_IFDIR;
}

///
/// Imports directory from the real FS to this one
///
void FileSystem::importDirectory(const std::string& path, const std::string& dest)
{
	if (!isDirectory(path))
		throw InvalidFilePath("File is not a directory!");

	stringPair pair = splitPathAndName(dest);
	files.insert(pair.first, new Directory(pair.second));

	DLList<std::string> fileNames = getFilesFromADirectory(path);
	for (DLList<std::string>::Iterator iter = fileNames.begin(); iter; ++iter)
	{
		if (isDirectory(path + "\\" + (*iter)))
			importDirectory(path + "\\" + (*iter), buildPath(dest, *iter));
		else
			importFile(path + "\\" + (*iter), buildPath(dest, *iter));
	}
}

///
/// Renames a File in the current FS
///
void FileSystem::rename(const std::string& path, const std::string& newName)
{
	TNode* toRename = files.getNode(path);
	if (!toRename)
		throw InvalidFilePath("File not found.");

	toRename->data->setName(newName);
}

///
/// Appends text to the end of a file
///
void FileSystem::appendText(const std::string& text, const std::string& dest)
{
	TNode* toBeAppended = files.getNode(dest);
	if (!toBeAppended)
		throw InvalidFilePath("File not found.");

	if (toBeAppended->data->isDirectory())
		throw InvalidFileType("Expected a file, got a folder.");

	file.seekg(toBeAppended->data->getLastSectorID() * SectorInfo::SECTOR_SIZE, std::ios::beg);
	SectorInfo info;
	info.deserialize(file);
	file.seekp((toBeAppended->data->getLastSectorID() + 1)* SectorInfo::SECTOR_SIZE, std::ios::beg);
	append(reinterpret_cast<const byte *>(text.c_str()), text.size(), info);
}

///
/// This method is used to go back to the service information
/// of the fragment, when the info.nextSector is SectorInfo::noNext,
/// so it can set it to show to real number, in order to continue read/write
///
bool FileSystem::setnextSector(SectorInfo& info)
{
	info.nextSector = getNextSectorID();

	file.seekp(-static_cast<int>(SectorInfo::SECTOR_SIZE), std::ios::cur);
	info.serialize(file);

	return true;
}

///
/// Gets the information for a file
///
std::string FileSystem::getFileInfo(const std::string& path)
{
	TNode* file = files.getNode(path);
	if (!file)
		throw InvalidFilePath("wrong path - getFileInfo()");

	return file->toString();
}

///
/// Gets the names of all the files in the first level 
/// in a directory. Returns a DLList of std::string
///
DLList<std::string> FileSystem::getFilesFromADirectory(const std::string& path) const
{
	DLList<std::string> fileNames;
	struct dirent* buffer;
	DIR* dir = opendir(path.c_str());

	if (!dir)
		throw InvalidFilePath("Directory not found.");

	while (buffer = readdir(dir))
		if (strcmp(buffer->d_name, ".") && strcmp(buffer->d_name, ".."))
			fileNames.pushBack(buffer->d_name);

	return fileNames;
}

///
/// Splits a path into the path a file to be inserted into
/// and the name of the file. Returns a pair of std::string
///
stringPair FileSystem::splitPathAndName(const std::string& path) const
{
	size_t backslash = path.rfind(BACKSLASH_CHAR);

	if (backslash == std::string::npos)
		throw InvalidFilePath("Backslash not found!");

	std::string pathOnly(path, 0, backslash);

	if (!backslash)
		pathOnly = "/";

	std::string name(path, backslash + 1);

	return stringPair(pathOnly, name);
}
