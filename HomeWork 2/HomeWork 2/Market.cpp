#include "Market.h"

typedef DLList<Queue<Client>>::Iterator ListIterator;

Market::Market(int numberOfAllCashDecks) : maxCashDecks(numberOfAllCashDecks)
{  }

void Market::AddClient(Client* clients, int number)
{
	for (ListIterator iter = decks.begin(), int i = 0; i < number; ++iter, ++i)
		(*iter).enqueue(clients[i]);
}

int Market::getLeastFilledDeck()
{
	ListIterator iter = decks.begin();
	ListIterator min = iter;
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