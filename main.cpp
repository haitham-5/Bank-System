#include "Bank.h"

using namespace bnk;

int main()
{
    vector <sClient> vClients;
    vClients=LoadCleintsDataFromFile(ClientFile);

    BankSystem(vClients);
}