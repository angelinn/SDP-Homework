#include "DLList.h"
#include "Queue.h"

struct Client;
struct MarketState;
struct ClientState;


class Market
{
public:
	Market(int NumberOfAllCashDecks); // максимални брой каси които може да бъдат отворени в магазина (без експресната)
	void AddClient(Client * clients, int number); // добавяме number клиенти в магазина
	MarketState getMarketState(); // връща състоянието на магазина
	ClientState getClientState(int ID); // връща състоянието на клиента

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
	int CashDeskPosition; // номер на каса
	int QueuePosition; // позиция в опашката на касата
	Client * client;
};

struct MarketState
{
	int numberOfCashDesk; // броя на касите които са отворили в момента
	int * numberOfClientsAtCashDecsk; // броя на клиентите на всяка каса в този момент
	int numberOfClientsAtExpressCashDeck;
};

struct Client
{
	int ID; // уникален номер на клиента в магазина
	int numberOfGoods; // брой на покупките на клиента
	bool creditCard; // истина ако плаща с крединта карта
};