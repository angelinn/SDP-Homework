#ifndef MARKET_H
#define MARKET_H

#include "DLList.h"
#include "Queue.h"

struct Client;
struct MarketState;
struct ClientState;

typedef DLList<Queue<Client>>::Iterator ListIterator;

class Market
{
public:
	Market(int NumberOfAllCashDecks); // ���������� ���� ���� ����� ���� �� ����� �������� � �������� (��� �����������)
	void AddClient(Client * clients, int number); // �������� number ������� � ��������
	MarketState getMarketState(); // ����� ����������� �� ��������
	ClientState getClientState(int ID); // ����� ����������� �� �������

public:
	static int currentID; // Holds the ID for the Clients

private:
	void addAllClients(Client *, int); // Adds an array of clients to the store
	void arrangeClient(Client &); // Puts the client in the least queue
	int getLeastFilledDeck(); // Gets the least queue

private:
	void tick(Client *, int); // The main function that does the ticking
	void openDeck(); // Opens a new deck
	bool areThereFullDecks(); // Checks if there are full decks
	bool moveClientsIfNeeded(); // Moves clients if needed
	bool closeDeckIfNeeded(); // Closes deck if needed (lol)

private:
	void processClients(); // Processes one grocery
	bool isClientReadyToGo(const Client &); // Returns true or false depend if the client is ready to leave
	void setClientState(Client, int, int); // Sets the client state into the array

private:
	int maxCashDecks; // Holds the maximum for available cash decks
	Queue<Client> expressDeck; // Variable for the express cash deck
	DLList<Queue<Client>> decks; // The cash decks
	DLList<ClientState> states; // A list for the Clients' states
};

struct ClientState
{
	int CashDeskPosition; // ����� �� ����
	int QueuePosition; // ������� � �������� �� ������
	Client * client;
};

struct MarketState
{
	int numberOfCashDesk; // ���� �� ������ ����� �� �������� � �������
	int * numberOfClientsAtCashDecsk; // ���� �� ��������� �� ����� ���� � ���� ������
	int numberOfClientsAtExpressCashDeck;
};

struct Client
{
	int ID; // �������� ����� �� ������� � ��������
	int numberOfGoods; // ���� �� ��������� �� �������
	bool creditCard; // ������ ��� ����� � �������� �����
};

#endif // MARKET_H
