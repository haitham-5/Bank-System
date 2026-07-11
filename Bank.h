#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <cctype>

using namespace std;

namespace bnk
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

    void PrintHeader(string Title)
    {
        cout << "\n==================================================\n";
        cout << "\t\t" << Title << "\n";
        cout << "==================================================\n";
    }

    void PrintRecord(const sClient &Client)
    {
        cout << " Account number :  " << Client.AccountNumber << "\n";
        cout << " PinCode        :  " << Client.PinCode << "\n";
        cout << " Name           :  " << Client.Name << "\n";
        cout << " Phone          :  " << Client.Phone << "\n";
        cout << " Balance        : $" << fixed << setprecision(2) << Client.Balance << "\n";
    }

    bool CheckIfClientExists(const vector<sClient> &vClients, string AccountNumber)
    {
        for (const sClient &Client : vClients)
        {
            if (Client.AccountNumber == AccountNumber)
            {
                return true;
            }
        }
        return false;
    }

    sClient ReadRecord(vector<sClient> &vClients)
    {
        sClient Client;
        cout << " -> Please enter account number: ";
        getline(cin >> ws, Client.AccountNumber);
        while (CheckIfClientExists(vClients, Client.AccountNumber))
        {
            cout << " [!] Account Number already exists!\n";
            cout << " -> Please enter account number: ";
            getline(cin >> ws, Client.AccountNumber);
        }
        cout << " -> Please enter pincode: ";
        getline(cin, Client.PinCode);
        cout << " -> Please enter name: ";
        getline(cin, Client.Name);
        cout << " -> Please enter phone: ";
        getline(cin, Client.Phone);
        cout << " -> Please enter balance: ";
        cin >> Client.Balance;
        return Client;
    }

    sClient UpdateRecord(string AccountNumber)
    {
        sClient Client;
        Client.AccountNumber = AccountNumber;
        cout << " -> Please enter new pincode: ";
        getline(cin >> ws, Client.PinCode);
        cout << " -> Please enter new name: ";
        getline(cin, Client.Name);
        cout << " -> Please enter new phone: ";
        getline(cin, Client.Phone);
        cout << " -> Please enter new balance: ";
        cin >> Client.Balance;
        return Client;
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
            C.Balance = stod(vec[4]);
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

    vector<string> AddRecord(sClient Client)
    {
        vector<string> vec;
        vec.push_back(Client.AccountNumber);
        vec.push_back(Client.PinCode);
        vec.push_back(Client.Name);
        vec.push_back(Client.Phone);
        vec.push_back(to_string(Client.Balance));
        return vec;
    }

    const string ClientFile = "client.txt";
    const string UsersFile = "users.txt";

    void AddLineToFile(string ClientFile, string Line)
    {
        fstream File;
        File.open(ClientFile, ios::out | ios::app);
        if (File.is_open())
        {
            File << Line << endl;
        }
        File.close();
    }

    void AddClientToFile(vector<sClient> &vClients)
    {
        sClient MyClient = ReadRecord(vClients);
        vClients.push_back(MyClient);
        AddLineToFile(ClientFile, RecordToLine(MyClient, "#//#"));
    }

    void AddClientsToFile(vector<sClient> &vClients)
    {
        char AddMore = 'Y';
        do
        {
            system("cls");
            PrintHeader("ADD NEW CLIENTS");
            AddClientToFile(vClients);
            cout << "\n -> Do you want to add more clients? [Y/N]: ";
            cin >> AddMore;
        } while (toupper(AddMore) == 'Y');
    }

    vector<sClient> LoadCleintsDataFromFile(string FileName)
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

    void SaveCleintsDataToFile(string FileName, vector<sClient> vClients)
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

    void PrintClientCard(sClient Client)
    {
        cout << "\n----------------------------------------\n";
        PrintRecord(Client);
        cout << "----------------------------------------\n";
    }

    void PrintClientRecord(sClient Client)
    {
        cout << "| " << setw(16) << left << Client.AccountNumber;
        cout << "| " << setw(12) << left << Client.PinCode;
        cout << "| " << setw(26) << left << Client.Name;
        cout << "| " << setw(16) << left << Client.Phone;
        cout << "| $" << setw(12) << left << fixed << setprecision(2) << Client.Balance;
    }

    void PrintAllClientsData()
    {
        vector<sClient> vClients = LoadCleintsDataFromFile(ClientFile);

        cout << "\n\t\t\t\t\tCLIENT DATABASE LIST (" << vClients.size() << ") Client(s).";
        cout << "\n=========================================================================================\n" << endl;
        cout << "| " << left << setw(16) << "Account Number";
        cout << "| " << left << setw(12) << "Pin Code";
        cout << "| " << left << setw(26) << "Client Name";
        cout << "| " << left << setw(16) << "Phone";
        cout << "| " << left << setw(13) << "Balance";
        cout << "\n-----------------------------------------------------------------------------------------\n" << endl;

        for (const sClient &Client : vClients)
        {
            PrintClientRecord(Client);
            cout << endl;
        }
        cout << "\n=========================================================================================\n" << endl;
    }

    bool FindClientByAccNum(string AccNum, vector<sClient> vClients, sClient &Client)
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

    void FindAccount(vector<sClient> vClients)
    {
        PrintHeader("FIND CLIENT");
        cout << " -> Enter the account number you want to find: ";
        string AccNum;
        cin >> AccNum;
        sClient Client;
        if (FindClientByAccNum(AccNum, vClients, Client))
        {
            cout << "\n[-] Target client record found:\n";
            PrintClientCard(Client);
        }
        else
        {
            cout << "\n[!] Client with Account Number (" << AccNum << ") was not found.\n";
        }
    }

    void MarkClientForDelete(string AccNum, vector<sClient> &vClients)
    {
        for (sClient &C : vClients)
        {
            if (C.AccountNumber == AccNum)
            {
                C.MarkedForDelete = true;
                return;
            }
        }
    }

    void DeleteAccount(vector<sClient> &vClients)
    {
        PrintHeader("DELETE CLIENT ACCOUNT");
        cout << " -> Enter the account number you want to delete: ";
        string AccNum;
        cin >> AccNum;
        sClient Client;

        char DeleteChoice;
        if (FindClientByAccNum(AccNum, vClients, Client))
        {
            cout << "\n[✓] Target client record found:\n";
            PrintClientCard(Client);
            cout << "\n -> Are you sure you want to delete this client? (Y/N): ";
            cin >> DeleteChoice;
            if (toupper(DeleteChoice) == 'Y')
            {
                MarkClientForDelete(AccNum, vClients);
                SaveCleintsDataToFile(ClientFile, vClients);
                vClients = LoadCleintsDataFromFile(ClientFile);
                cout << "\n[-] Client with Account Number (" << AccNum << ") has been successfully deleted.\n";
            }
            else
            {
                cout << "\n[-] Delete operation canceled.\n";
            }
        }
        else
        {
            cout << "\n[!] Client with Account Number (" << AccNum << ") was not found.\n";
        }
    }

    void UpdateAccount(vector<sClient> &vClients)
    {
        PrintHeader("UPDATE CLIENT INFO");
        string AccountNumber;
        cout << " -> Enter the account number you want to update: ";
        cin >> AccountNumber;
        sClient Client;
        char Answer = 'n';
        if (FindClientByAccNum(AccountNumber, vClients, Client))
        {
            cout << "\n[-] Current client record:\n";
            PrintClientCard(Client);
            cout << "\n -> Are you sure you want update this client? (Y/N): ";
            cin >> Answer;
            if (Answer == 'y' || Answer == 'Y')
            {
                for (sClient &C : vClients)
                {
                    if (C.AccountNumber == AccountNumber)
                    {
                        C = UpdateRecord(AccountNumber);
                        break;
                    }
                }
                SaveCleintsDataToFile(ClientFile, vClients);
                cout << "\n[✓] Client Updated Successfully.\n";
            }
            else
            {
                cout << "\n[-] Update operation canceled.\n";
            }
        }
        else
        {
            cout << "\n[!] Client with Account Number (" << AccountNumber << ") was not found.\n";
        }
    }

    void MainMenu()
    {
        cout << "\n==================================================\n";
        cout << "             MAIN BANKING SYSTEM MENU             \n";
        cout << "==================================================\n";
        cout << "  [1] Show All Clients\n";
        cout << "  [2] Add New Client\n";
        cout << "  [3] Update Client Info\n";
        cout << "  [4] Delete Client Account\n";
        cout << "  [5] Find Client Profile\n";
        cout << "  [6] Exit System\n";
        cout << "==================================================\n";
    }

    int ReadNumber(int Min, int Max)
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

    void BankSystem(vector<sClient> &vClients)
    {
        short Choice;
        do
        {
            system("cls");
            MainMenu();
            Choice = ReadNumber(1, 6);
            system("cls");
            switch (Choice)
            {
            case 1:
                PrintAllClientsData();
                break;
            case 2:
                AddClientsToFile(vClients);
                break;
            case 3:
                UpdateAccount(vClients);
                break;
            case 4:
                DeleteAccount(vClients);
                break;
            case 5:
                FindAccount(vClients);
                break;
            case 6:
                PrintHeader("SYSTEM TERMINATED");
                cout << " Thank you for using our banking service. Goodbye!\n\n";
                break;
            }
            if (Choice != 6)
            {
                cout << "\n\n Press any key to go back to the main menu...";
                system("pause>0");
            }
        } while (Choice != 6);
    }
}