#include "Market.h"
#include <iostream>

int Market::currentID = 1;

Market::Market(int numberOfAllCashDecks) : maxCashDecks(numberOfAllCashDecks)
{
	openDeck();
}

void Market::AddClient(Client* clients, int number)
{
	tick(clients, number);
}

void Market::arrangeClient(Client& client)
{

	int minQueue = getLeastFilledDeck();

		int deskCounter = 1;

		for (ListIterator iter = decks.begin(); iter; ++iter, ++deskCounter)
		{
			if (minQueue == (*iter).getSize())
			{
				(*iter).enqueue(client);
				setClientState(client, deskCounter, (*iter).getSize());

				return;
			}
		}
		throw std::exception("Something went terribly wrong .. ");
}

bool Market::areThereFullDecks()
{
	for (ListIterator iter = decks.begin(); iter; ++iter)
	{
		if ((*iter).getSize() > maxCashDecks)
			return true;
	}
	
	return false;
}

bool Market::moveClientsIfNeeded()
{
	for (ListIterator iter = decks.begin(); iter; ++iter)
	{
		for (ListIterator iter2 = decks.begin(); iter2; ++iter2)
		{
			if ((*iter).getSize() - (*iter2).getSize() > maxCashDecks / 8)
			{
				Queue<Client> placeholder;
				Queue<Client> clientsToBeMoved;

				int size = (*iter).getSize();
				int middle = size / 2;

				for (int i = 0; i < middle; ++i)
					placeholder.enqueue((*iter).dequeue());

				
				clientsToBeMoved = (*iter);
				(*iter) = placeholder;

				while (!clientsToBeMoved.isEmpty())
					arrangeClient(clientsToBeMoved.dequeue());
						
				return true;
			}
		}	
	}
	return false;
}

void Market::setClientState(Client client, int deskCounter, int position)
{
	bool set = false;

	for (DLList<ClientState>::Iterator clIter = states.begin(); clIter; ++clIter)
	{
		if ((*clIter).client->ID == client.ID)
		{
			states.popAt(clIter);
			states.pushBack(ClientState{ deskCounter, position, &client });
			set = true;
			break;
		}
	}

	if (!set)
		states.pushBack(ClientState{ deskCounter, position, &client });
}

bool Market::closeDeckIfNeeded()
{
	for (ListIterator iter = decks.begin(); iter; ++iter)
	{
		if ((*iter).getSize() < static_cast<double>(maxCashDecks) / 10.0)
		{
			for (int i = 0; i < (*iter).getSize(); ++i)
				arrangeClient((*iter).dequeue());

			decks.popAt(iter);
			return true;
		}
	}
	return false;
}

void Market::addAllClients(Client* clients, int number)
{
	for (int i = 0; i < number; ++i)
	{
		if (!clients || number < 1)
			return;

		clients[i].ID = Market::currentID;
		++Market::currentID;

		if (!clients[i].numberOfGoods)
			continue;

		if (clients[i].numberOfGoods <= 3 && expressDeck.getSize() < 2 * maxCashDecks)
		{
			expressDeck.enqueue(clients[i]);
			setClientState(clients[i], 0, expressDeck.getSize());
		}

		else
			arrangeClient(clients[i]);
	}
}

void Market::tick(Client* clients, int number)
{
	processClients();

	addAllClients(clients, number);

	if (decks.getSize() > 1 && closeDeckIfNeeded())
	{  }

	else if (moveClientsIfNeeded())
	{  }

	else if (decks.getSize() < maxCashDecks && areThereFullDecks())
	{
		try
		{
			openDeck();
			moveClientsIfNeeded();
		}
		catch (std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}

	}
}

void Market::processClients()
{
	for (ListIterator iter = decks.begin(); iter; ++iter)
	{
		if (!(*iter).isEmpty())
		{
			--(*iter).peek().numberOfGoods;

			if (isClientReadyToGo((*iter).peek())) 
				setClientState((*iter).dequeue(), -1, -1);
		}
	}

	if (!expressDeck.isEmpty())
	{
		--expressDeck.peek().numberOfGoods;

		if (isClientReadyToGo(expressDeck.peek()))
			setClientState(expressDeck.dequeue(), -1, -1);
	}

}

bool Market::isClientReadyToGo(const Client& client)
{
	if (client.creditCard && client.numberOfGoods == -1)
		return true;
	if (!client.creditCard && client.numberOfGoods == -2)
		return true;

	return false;
}

void Market::openDeck()
{
	if (decks.getSize() >= maxCashDecks)
		throw std::exception("Maximum Cash Decks limit reached!");

	decks.pushBack(*(new Queue<Client>));
}

int Market::getLeastFilledDeck()
{
	int min = INT_MAX;


	for (ListIterator iter = decks.begin(); iter; ++iter)
	{
		if ((*iter).getSize() < min)
			min = (*iter).getSize();
	}

	if (min == INT_MAX)
		throw std::exception("Something went really wrong /min/");

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
	for (DLList<ClientState>::Iterator iter = states.begin(); iter; ++iter)
	{
		if (id == (*iter).client->ID)
			return (*iter);
	}

	throw std::exception("Client not found!");
}