#include "DLList.h"
#include "Queue.h"

struct Client;
struct MarketState;
struct ClientState;


class Market
{
public:
	Market(int NumberOfAllCashDecks); // ���������� ���� ���� ����� ���� �� ����� �������� � �������� (��� �����������)
	void AddClient(Client * clients, int number); // �������� number ������� � ��������
	MarketState getMarketState(); // ����� ����������� �� ��������
	ClientState getClientState(int ID); // ����� ����������� �� �������

public:
	static int currentID;

private:
	int getLeastFilledDeck();
	void addSingleClient(Client);
	void openDeck();
	void tick();
	void closeDeck();
	bool areThereFullDecks();
	bool moveClientsIfNeeded();

private:
	int maxCashDecks;
	Queue<Client> expressDeck;
	DLList<Queue<Client>> decks;
	DLList<ClientState> states;
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

	~MarketState() { delete numberOfClientsAtCashDecsk; }
};

struct Client
{
	int ID; // �������� ����� �� ������� � ��������
	int numberOfGoods; // ���� �� ��������� �� �������
	bool creditCard; // ������ ��� ����� � �������� �����
};