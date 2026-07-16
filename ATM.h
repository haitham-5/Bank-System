#pragma once

#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <cctype>

using namespace std;

namespace atm
{

    struct sClient
    {
        string AccountNumber;
        string PinCode;
        string Name;
        string Phone;
        double Balance;
        bool MarkedForDelete = false;
    };

    inline sClient CurrentClient;
    const string ClientsFile = "client.txt";

    int ReadNumber(int Min = -1, int Max = 100000000)
    {
        int Number;
        while (true)
        {
            cout << " -> Choose option [" << Min << "-" << Max << "]: ";
            if (cin >> Number)
            {
                if (Number >= Min && Number <= Max)
                {
                    return Number;
                }
            }

            cout << " [!] Invalid input. Please choice out of the range.\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    vector<string> SplitString(string S1, string Delim)
    {
        vector<string> vString;
        size_t pos = 0;
        string sWord;
        while ((pos = S1.find(Delim)) != std::string::npos)
        {
            sWord = S1.substr(0, pos);
            if (sWord != "")
                vString.push_back(sWord);
            S1.erase(0, pos + Delim.length());
        }
        if (S1 != "")
            vString.push_back(S1);
        return vString;
    }
    void PrintHeader(string Title)
    {
        cout << "\n==================================================\n";
        cout << "\t\t" << Title << "\n";
        cout << "==================================================\n";
    }

    sClient LineToRecord(string S, string Delim)
    {
        vector<string> vec = SplitString(S, Delim);
        sClient C;
        if (vec.size() >= 5)
        {
            C.AccountNumber = vec[0];
            C.PinCode = vec[1];
            C.Name = vec[2];
            C.Phone = vec[3];
            try
            {
                C.Balance = stod(vec[4]);
            }
            catch (...)
            {
                C.Balance = 0.0;
            }
        }
        return C;
    }

    string RecordToLine(sClient Client, string Delim)
    {
        string S = "";
        S += (Client.AccountNumber) + Delim;
        S += (Client.PinCode) + Delim;
        S += (Client.Name) + Delim;
        S += (Client.Phone) + Delim;
        S += (to_string(Client.Balance));
        return S;
    }

    bool FindClientByAccountNumber(string AccNum, vector<sClient> &vClients, sClient &Client)
    {
        for (sClient &C : vClients)
        {
            if (C.AccountNumber == AccNum)
            {
                Client = C;
                return true;
            }
        }
        return false;
    }

    vector<sClient> LoadClientsDataFromFile(string FileName)
    {
        vector<sClient> vClients;
        fstream MyFile;
        MyFile.open(FileName, ios::in);
        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                if (!Line.empty())
                {
                    sClient Client = LineToRecord(Line, "#//#");
                    vClients.push_back(Client);
                }
            }
            MyFile.close();
        }
        return vClients;
    }

    void SaveClientsDataToFile(string FileName, const vector<sClient> &vClients)
    {
        fstream MyFile;
        MyFile.open(FileName, ios::out);
        if (MyFile.is_open())
        {
            for (const sClient &Client : vClients)
            {
                if (!Client.MarkedForDelete)
                {
                    string Line = RecordToLine(Client, "#//#");
                    MyFile << Line << endl;
                }
            }
            MyFile.close();
        }
    }

    void ATMMenu()
    {
        cout << "\n==================================================\n";
        cout << "               ATM SYSTEM MENU                               \n";
        cout << "==================================================\n";
        cout << "  [1] Quick Withdraw\n";
        cout << "  [2] Withdraw\n";
        cout << "  [3] Deposit\n";
        cout << "  [4] Check Balance\n";
        cout << "  [5] Log Out\n";
        cout << "==================================================\n";
    }

    int ReadPositiveNumber()
    {
        int Number;
        do
        {
            cin >> Number;
            if (Number < 0)
                cout << " Please Enter a Positive Number ! \n";
        } while (Number < 0);
        return Number;
    }
    void QuickWithdrawMenu()
    {
        cout << " [1] 20          [2] 50\n";
        cout << " [3] 100         [4] 200\n";
        cout << " [5] 400         [6] 600\n";
        cout << " [7] 800         [8] 1000\n";
        cout << " [9]  Exit         \n";
    }
    void QuickWithdraw(vector<sClient> &vClients)
    {
        QuickWithdrawMenu();
        int arr[8]{20, 50, 100, 200, 400, 600, 800, 1000};
        short choice = ReadNumber(1, 9);
        if (choice == 9)
            return;
        if (arr[choice - 1] > CurrentClient.Balance)
        {
            cout << " [!] You Don't Have Enough Balance In Your Account.\n";
            cout << " Your Balance Is : " << CurrentClient.Balance;
        }
        else
        {
            for (sClient &C : vClients)
            {
                if (C.AccountNumber == CurrentClient.AccountNumber)
                {
                    CurrentClient.Balance -= arr[choice - 1];
                    C.Balance -= arr[choice - 1];
                    cout << " Your Balance After Withdrawing " << arr[choice - 1] << " Is : " << C.Balance;
                    SaveClientsDataToFile(ClientsFile, vClients);
                    break;
                }
            }
        }
    }

    void Withdraw(vector<sClient> &vClients)
    {
        int Amount;
        while (true)
        {
            cout << " [-] Note : Enter An Amount That's Divisible By 10 . \n";
            cout << " [-] How Much Do You Want To WithDraw : \n";
            Amount = ReadPositiveNumber();
            if (Amount % 10 == 0)
                break;
            cout << " [!] Sorry We Have Just Tens (10)... : \n";
        }
        if (Amount > CurrentClient.Balance)
        {
            cout << " [!] You Don't Have Enough Balance In Your Account.\n";
            cout << " Your Balance Is : " << CurrentClient.Balance;
        }
        else
        {
            for (sClient &C : vClients)
            {
                if (C.AccountNumber == CurrentClient.AccountNumber)
                {
                    CurrentClient.Balance -= Amount;
                    C.Balance -= Amount;
                    cout << " Your Balance After Withdrawing " << Amount << " Is : " << C.Balance;
                    SaveClientsDataToFile(ClientsFile, vClients);
                    break;
                }
            }
        }
    }
    void Deposit(vector<sClient> &vClients)
    {
        int Amount;
        cout << " [-] How Much Do You Want To Deposit.\n";
        Amount = ReadPositiveNumber();
        for (sClient &C : vClients)
        {
            if (C.AccountNumber == CurrentClient.AccountNumber)
            {
                CurrentClient.Balance += Amount;
                C.Balance += Amount;
                cout << " Your Balance After The Deposit Of " << Amount << " Is : " << C.Balance;
                SaveClientsDataToFile(ClientsFile, vClients);
                break;
            }
        }
    }

    void CheckBalance(vector<sClient> &vClients)
    {
        for (sClient &C : vClients)
        {
            if (C.AccountNumber == CurrentClient.AccountNumber)
            {
                cout << "The Account Number Of " << C.AccountNumber << " Balance Is : " << C.Balance << endl;
                break;
            }
        }
    }
    void ATMSystem()
    {

        vector<sClient> vClients;
        vClients = LoadClientsDataFromFile(ClientsFile);
        short Choice;
        do
        {
            system("cls");
            ATMMenu();
            Choice = ReadNumber(1, 5);
            system("cls");
            switch (Choice)
            {
            case 1:
                QuickWithdraw(vClients);
                break;
            case 2:
                Withdraw(vClients);
                break;
            case 3:
                Deposit(vClients);
                break;
            case 4:
                CheckBalance(vClients);
                break;
            case 5:
                return;
            }
            if (Choice < 5)
            {
                cout << "\n\n Press any key to go back to the Main Menu...";
                system("pause>0");
            }
        } while (Choice != 5);
    }

    void ATMLogIn()
    {
        do
        {
            vector<sClient> vClients;
            vClients = LoadClientsDataFromFile(ClientsFile);
            sClient Client;
            string AccountNumber = "";
            string Pincode = "";

            system("cls");
            PrintHeader("ATM LOGIN SCREEN");

            cout << " Enter Account Number : ";
            getline(cin >> ws, AccountNumber);

            if (FindClientByAccountNumber(AccountNumber, vClients, Client))
            {
                cout << " Enter PinCode : ";
                getline(cin, Pincode);

                if (Pincode == Client.PinCode)
                {
                    CurrentClient = Client;
                    ATMSystem();
                }
                else
                {
                    cout << "\n[!] Invalid PinCode! Press any key to try again...";
                    system("pause>0");
                }
            }
            else
            {
                cout << "\n[!] Account not found! Press any key to try again...";
                system("pause>0");
            }
        } while (true);
    }

}