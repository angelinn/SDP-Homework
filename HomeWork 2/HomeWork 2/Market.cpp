#include "Market.h"

typedef DLList<Queue<Client>>::Iterator ListIterator;
int Market::currentID = 0;

Market::Market(int numberOfAllCashDecks) : maxCashDecks(numberOfAllCashDecks)
{
	openDeck();
}

void Market::AddClient(Client* clients, int number)
{
	for (int i = 0; i < number; ++i)
		addSingleClient(clients[i]);
}

void Market::addSingleClient(Client client)
{
	int minQueue = getLeastFilledDeck();

	client.ID = Market::currentID;
	++Market::currentID;

	if (client.numberOfGoods <= 3 && expressDeck.getSize() < 2 * decks.getSize())
		expressDeck.enqueue(client);
	else
		for (ListIterator iter = decks.begin(); iter; ++iter)
			if (minQueue == (*iter).getSize())
				(*iter).enqueue(client);
}

bool Market::areThereFullDecks()
{
	for (ListIterator iter = decks.begin(); iter; ++iter)
	{
		if ((*iter).getSize() > decks.getSize())
			return true;
	}
	
	return false;
}

bool Market::moveClientsIfNeeded()
{
	bool moved = false;

	for (ListIterator iter = decks.begin(); iter; ++iter)
	{
		if ((*iter).getSize() > decks.getSize())
			return true;
	}
}

void Market::tick()
{
	if (areThereFullDecks())
		openDeck();
	else if 
}

void Market::openDeck()
{
	if (decks.getSize() >= maxCashDecks)
		throw std::exception("Maximum Cash Decks limit reached!");

	decks.pushBack(*(new Queue<Client>));
}

void Market::closeDeck()
{

}

int Market::getLeastFilledDeck()
{
	ListIterator iter = decks.begin();
	int min = (*iter).getSize();


	for (; iter; ++iter)
	{
		if ((*iter).getSize() < min)
			min = (*iter).getSize();
	}

	return min;
}

MarketState Market::getMarketState()
{
	MarketState state;
	state.numberOfCashDesk = decks.getSize();
	state.numberOfClientsAtExpressCashDeck = expressDeck.getSize();

	state.numberOfClientsAtCashDecsk = new int[decks.getSize()];

	ListIterator iter = decks.begin();
	for (int i = 0; i < decks.getSize(); ++i, ++iter)
		state.numberOfClientsAtCashDecsk[i] = (*iter).getSize();

	return state;
}

ClientState Market::getClientState(int id)
{
	ClientState state;

	for (ListIterator iter = decks.begin(), end = decks.end(); iter != end; ++iter)
	{

	}

	return state;
}