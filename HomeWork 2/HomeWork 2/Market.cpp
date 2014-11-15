#include "Market.h"

typedef DLList<Queue<Client>>::Iterator ListIterator;

Market::Market(int numberOfAllCashDecks) : maxCashDecks(numberOfAllCashDecks)
{
	addDeck();
}

void Market::AddClient(Client* clients, int number)
{
	for (int i = 0; i < number; ++i)
		addSingleClient(clients[i]);
}

void Market::addSingleClient(Client client)
{
	int minQueue = getLeastFilledDeck();

	for (ListIterator iter = decks.begin(), end = decks.end(); iter != end; ++iter)
		if (minQueue == (*iter).getSize())
			(*iter).enqueue(client);
}

void Market::addDeck()
{
	if (decks.getSize() >= maxCashDecks)
		throw std::exception("Maximum Cash Decks limit reached!");

	decks.pushBack(*new Queue<Client>);
}

int Market::getLeastFilledDeck()
{
	ListIterator iter = decks.begin();
	int min = (*iter).getSize();
	++iter;

	for (; true; ++iter)
	{
		if ((*iter).getSize() < min)
			min = (*iter).getSize();
	}

	return min;
}

MarketState Market::getMarketState()
{
	MarketState b;
	return b;
}

ClientState Market::getClientState(int id)
{
	ClientState a;
	return a;
}