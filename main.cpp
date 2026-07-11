#include "Bank.h"

using namespace bnk;

int main()
{
    vector <sClient> vClients;
    vClients=LoadClientsDataFromFile(ClientFile);

    BankSystem(vClients);
}