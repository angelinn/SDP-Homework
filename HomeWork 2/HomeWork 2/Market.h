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

private:
	int getLeastFilledDeck();
	void addSingleClient(Client);
	void addDeck();

private:
	int maxCashDecks;
	Queue<Client> expressDeck;
	DLList<Queue<Client>> decks;
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