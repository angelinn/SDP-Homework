template <typename T>

class Stack
{
public:
	Stack();

public:
	bool isEmpty() const;
	void push(T);
	T pop();
	T peek() const;

public:
	static const int DATA_SIZE = 1024;

private:
	T data[DATA_SIZE];
	int used;
};

template <typename T>
Stack<T>::Stack() : used(0)
{ }

template <typename T>
bool Stack<T>::isEmpty() const
{
	return !used;
}

template <typename T>
void Stack<T>::push(T element)
{
	if (used >= DATA_SIZE)
		throw "Stack overflow";

	data[used++] = element;
}

template <typename T>
T Stack<T>::peek() const
{
	if (isEmpty())
		throw "Stack is empty";

	return data[used - 1];
}

template <typename T>
T Stack<T>::pop()
{
	if (isEmpty())
		throw "Stack is empty";

	return data[--used];	
}