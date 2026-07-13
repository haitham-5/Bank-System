#pragma once

#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <cctype>

using namespace std;

namespace bnk
{

    void LogIn();
    struct sClient
    {
        string AccountNumber;
        string PinCode;
        string Name;
        string Phone;
        double Balance;
        bool MarkedForDelete = false;
    };

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

    void PrintHeader(string Title)
    {
        cout << "\n==================================================\n";
        cout << "\t\t" << Title << "\n";
        cout << "==================================================\n";
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

    struct sUser
    {
        string Name;
        string Password;
        int Permissions = 0;
        bool MarkedForDelete = false;
    };

    sUser Current;

    bool CheckIfUserExists(const vector<sUser> &vUsers, string Name)
    {
        for (const sUser &User : vUsers)
        {
            if (User.Name == Name)
            {
                return true;
            }
        }
        return false;
    }

    string HashPassword(const string &password)
    {
        size_t hashValue = hash<string>{}(password);
        return to_string(hashValue);
    }

    sUser ReadUserRecord(vector<sUser> &vUsers)
    {
        sUser User;
        cout << " -> Please enter UserName: ";
        getline(cin >> ws, User.Name);
        while (CheckIfUserExists(vUsers, User.Name))
        {
            cout << " [!] UserName already exists!\n";
            cout << " -> Please enter UserName: ";
            getline(cin >> ws, User.Name);
        }

        cout << " -> Please Enter User Password : ";
        getline(cin >> ws, User.Password);
        User.Password = HashPassword(User.Password);
        cout << " -> do you want to give access to the whole System Y/N: ";
        char answer = 'n';
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
        {
            User.Permissions = -1;
            return User;
        }
        cout << " -> do you want to give access to See Client List : ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
            User.Permissions += 1;
        cout << " -> do you want to give access to Add New Clients : ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
            User.Permissions += 2;
        cout << " -> do you want to give access to Update Clients : ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
            User.Permissions += 4;
        cout << " -> do you want to give access to Delete Clients : ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
            User.Permissions += 8;
        cout << " -> do you want to give access to Find Clients: ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
            User.Permissions += 16;
        cout << " -> do you want to give access to The Transaction Screen: ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
            User.Permissions += 32;
        cout << " -> do you want to give access to Manage Users : ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
            User.Permissions += 64;
        cin.ignore();
        return User;
    }

    sUser UpdateUserRecord(string Name)
    {
        sUser User;
        User.Permissions = 0;
        User.Name = Name;
        cout << " -> Please Enter User Password : ";
        getline(cin >> ws, User.Password);
        User.Password = HashPassword(User.Password);
        cout << " -> do you want to give access to the whole System Y/N: ";
        char answer = 'n';
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
        {
            User.Permissions = -1;
            return User;
        }
        cout << " -> do you want to give access to See Client List : ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
            User.Permissions += 1;
        cout << " -> do you want to give access to Add New Clients : ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
            User.Permissions += 2;
        cout << " -> do you want to give access to Update Clients : ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
            User.Permissions += 4;
        cout << " -> do you want to give access to Delete Clients : ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
            User.Permissions += 8;
        cout << " -> do you want to give access to Find Clients: ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
            User.Permissions += 16;
        cout << " -> do you want to give access to The Transaction Screen: ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
            User.Permissions += 32;
        cout << " -> do you want to give access to Manage Users : ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
            User.Permissions += 64;
        cin.ignore();
        return User;
    }

    sUser UserLineToRecord(string S, string Delim)
    {
        vector<string> vec = SplitString(S, Delim);
        sUser U;
        if (vec.size() >= 3)
        {
            U.Name = vec[0];
            U.Password = (vec[1]);
            U.Permissions = stoi(vec[2]);
        }
        return U;
    }

    string UserRecordToLine(sUser User, string Delim)
    {
        string S = "";
        S += (User.Name) + Delim;
        S += (User.Password) + Delim;
        S += (to_string(User.Permissions));
        return S;
    }

    const string UsersFile = "Users.txt";

    void AddLineToFile(string FileName, string Line)
    {
        fstream File;
        File.open(FileName, ios::out | ios::app);
        if (File.is_open())
        {
            File << Line << endl;
        }
        File.close();
    }

    void AddUserToFile(vector<sUser> &vUsers)
    {
        sUser User = ReadUserRecord(vUsers);
        vUsers.push_back(User);
        AddLineToFile(UsersFile, UserRecordToLine(User, "#//#"));
    }

    void AddUsersToFile(vector<sUser> &vUsers)
    {
        char AddMore = 'Y';
        do
        {
            system("cls");
            PrintHeader("ADD NEW USER");
            AddUserToFile(vUsers);
            cout << "\n -> Do you want to add more Users? [Y/N]: ";
            cin >> AddMore;
        } while (toupper(AddMore) == 'Y');
    }

    vector<sUser> LoadUsersDataFromFile(string FileName)
    {
        vector<sUser> vUsers;
        fstream MyFile;
        MyFile.open(FileName, ios::in);
        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                if (!Line.empty())
                {
                    sUser User = UserLineToRecord(Line, "#//#");

                    vUsers.push_back(User);
                }
            }
            MyFile.close();
        }
        return vUsers;
    }

    void SaveUsersDataToFile(string FileName, const vector<sUser> &vUsers)
    {
        fstream MyFile;
        MyFile.open(FileName, ios::out);
        if (MyFile.is_open())
        {
            for (const sUser &User : vUsers)
            {
                if (!User.MarkedForDelete)
                {
                    string Line = UserRecordToLine(User, "#//#");
                    MyFile << Line << endl;
                }
            }
            MyFile.close();
        }
    }

    void PrintUserCard(sUser User)
    {
        cout << "\n----------------------------------------\n";
        cout << " UserName            :  " << User.Name << "\n";
        cout << " UserPassword    :  " << User.Password << "\n";
        cout << " Permissions         :  " << User.Permissions << "\n";
        cout << "----------------------------------------\n";
    }

    void PrintUserRecord(sUser User)
    {
        cout << "| " << setw(36) << left << User.Name;
        cout << "| " << setw(28) << left << "********";
        cout << "| " << setw(22) << left << User.Permissions;
    }

    void ShowAllUsersData(vector<sUser> &vUsers)
    {

        cout << "\n\t\t\tUSER DATABASE LIST (" << vUsers.size() << ") USER(s).";
        cout << "\n=========================================================================================\n"
             << endl;
        cout << "| " << setw(36) << left << "Name";
        cout << "| " << setw(28) << left << "Password";
        cout << "| " << setw(22) << left << "Permissions";
        cout << "\n-----------------------------------------------------------------------------------------\n"
             << endl;

        for (const sUser &User : vUsers)
        {
            PrintUserRecord(User);
            cout << endl;
        }
        cout << "\n=========================================================================================\n"
             << endl;
    }

    bool FindUserByUserName(string Name, vector<sUser> &vUsers, sUser &User)
    {
        for (sUser &U : vUsers)
        {
            if (U.Name == Name)
            {
                User = U;
                return true;
            }
        }
        return false;
    }

    void FindUser(vector<sUser> &vUsers)
    {
        PrintHeader("FIND USER");
        cout << " -> Enter the UserName you want to find: ";
        string Name;
        cin >> Name;
        sUser User;
        if (FindUserByUserName(Name, vUsers, User))
        {
            cout << "\n[-] Target User record found:\n";
            PrintUserCard(User);
        }
        else
        {
            cout << "\n[!] User with UserName (" << Name << ") was not found.\n";
        }
    }

    void MarkUserForDelete(string Name, vector<sUser> &vUsers)
    {
        for (sUser &U : vUsers)
        {
            if (U.Name == Name)
            {
                U.MarkedForDelete = true;
                return;
            }
        }
    }

    void DeleteUser(vector<sUser> &vUsers)
    {
        PrintHeader("DELETE USER ACCOUNT");
        cout << " -> Enter the UserName you want to delete: ";
        string Name;
        cin >> Name;
        if (Name == "Admin")
        {
            cout << " [!] You Can't Delete The Admin !";
            return;
        }
        sUser User;

        char Answer = 'n';
        if (!FindUserByUserName(Name, vUsers, User))
        {
            cout << "\n [!] User with UserName (" << Name << ") is not found!\n";
            return;
        }

        cout << "\n[✓] Target User record found:\n";
        PrintUserCard(User);
        cout << "\n -> Are you sure you want to delete this User? (Y/N): ";
        cin >> Answer;
        if (Answer != 'y' && Answer != 'Y')
        {
            cout << "\n[-] Delete operation canceled.\n";
            return;
        }
        MarkUserForDelete(Name, vUsers);
        SaveUsersDataToFile(UsersFile, vUsers);
        vUsers = LoadUsersDataFromFile(UsersFile);
        cout << "\n[-] User with UserName (" << Name << ") has been successfully deleted.\n";
        if (Name == Current.Name)
        {
            Current.Permissions = 0;
        }
    }

    void UpdateUser(vector<sUser> &vUsers)
    {
        PrintHeader("UPDATE USER INFO");
        string Name;
        cout << " -> Enter the UserName you want to update: ";
        cin >> Name;
        sUser User;
        char Answer = 'n';
        if (!FindUserByUserName(Name, vUsers, User))
        {
            cout << "\n [!] User with Account Number (" << Name << ") is not found!\n";
            return;
        }
        cout << "\n[-] Current User record:\n";
        PrintUserCard(User);
        cout << "\n -> Are you sure you want update this User? (Y/N): ";
        cin >> Answer;
        if (Answer != 'y' && Answer != 'Y')
        {
            cout << "\n[-] Update operation canceled.\n";
            return;
        }
        for (sUser &U : vUsers)
        {
            if (U.Name == Name)
            {
                U = UpdateUserRecord(Name);
                break;
            }
        }
        SaveUsersDataToFile(UsersFile, vUsers);
        cout << "\n[✓] User Updated Successfully.\n";
    }

    void PrintRecord(const sClient &Client)
    {
        cout << " Account number :  " << Client.AccountNumber << "\n";
        cout << " PinCode        :  " << Client.PinCode << "\n";
        cout << " Name           :  " << Client.Name << "\n";
        cout << " Phone          :  " << Client.Phone << "\n";
        cout << " Balance        :  $" << fixed << setprecision(2) << Client.Balance << "\n";
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
        Client.Balance = ReadNumber();
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
        Client.Balance = ReadNumber();
        return Client;
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

    const string ClientsFile = "client.txt";

    void AddClientToFile(vector<sClient> &vClients)
    {
        sClient MyClient = ReadRecord(vClients);
        vClients.push_back(MyClient);
        AddLineToFile(ClientsFile, RecordToLine(MyClient, "#//#"));
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

    void ShowAllClientsData(vector<sClient> &vClients)
    {
        cout << "\n\t\t\tCLIENT DATABASE LIST (" << vClients.size() << ") Client(s).";
        cout << "\n=========================================================================================\n"
             << endl;
        cout << "| " << left << setw(16) << "Account Number";
        cout << "| " << left << setw(12) << "Pin Code";
        cout << "| " << left << setw(26) << "Client Name";
        cout << "| " << left << setw(16) << "Phone";
        cout << "| " << left << setw(13) << "Balance";
        cout << "\n-----------------------------------------------------------------------------------------\n"
             << endl;

        for (const sClient &Client : vClients)
        {
            PrintClientRecord(Client);
            cout << endl;
        }
        cout << "\n=========================================================================================\n"
             << endl;
    }

    void PrintClientBalance(sClient Client)
    {
        cout << "| " << setw(20) << left << Client.AccountNumber;
        cout << "| " << setw(46) << left << Client.Name;
        cout << "| $" << setw(16) << left << fixed << setprecision(2) << Client.Balance;
    }

    void ShowAllClientsBalance(vector<sClient> vClients)
    {
        cout << "\n\t\t\tCLIENT BALANCE LIST (" << vClients.size() << ") Client(s).";
        cout << "\n=========================================================================================\n"
             << endl;
        cout << "| " << left << setw(20) << "Account Number";
        cout << "| " << left << setw(46) << "Client Name";
        cout << "| " << left << setw(17) << "Balance";
        cout << "\n-----------------------------------------------------------------------------------------\n"
             << endl;

        for (const sClient &Client : vClients)
        {
            PrintClientBalance(Client);
            cout << endl;
        }
        cout << "\n=========================================================================================\n"
             << endl;
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

    void FindAccount(vector<sClient> &vClients)
    {
        PrintHeader("FIND CLIENT");
        cout << " -> Enter the account number you want to find: ";
        string AccNum;
        cin >> AccNum;
        sClient Client;
        if (FindClientByAccountNumber(AccNum, vClients, Client))
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

    void DeleteClient(vector<sClient> &vClients)
    {
        PrintHeader("DELETE CLIENT ACCOUNT");
        cout << " -> Enter the account number you want to delete: ";
        string AccountNumber;
        cin >> AccountNumber;
        sClient Client;

        char Answer = 'n';
        if (!FindClientByAccountNumber(AccountNumber, vClients, Client))
        {
            cout << "\n [!] Client with Account Number (" << AccountNumber << ") is not found!\n";
            return;
        }

        cout << "\n[✓] Target client record found:\n";
        PrintClientCard(Client);
        cout << "\n -> Are you sure you want to delete this client? (Y/N): ";
        cin >> Answer;
        if (Answer != 'y' && Answer != 'Y')
        {
            cout << "\n[-] Delete operation canceled.\n";
            return;
        }
        MarkClientForDelete(AccountNumber, vClients);
        SaveClientsDataToFile(ClientsFile, vClients);
        vClients = LoadClientsDataFromFile(ClientsFile);
        cout << "\n[-] Client with Account Number (" << AccountNumber << ") has been successfully deleted.\n";
    }

    void UpdateClient(vector<sClient> &vClients)
    {
        PrintHeader("UPDATE CLIENT INFO");
        string AccountNumber;
        cout << " -> Enter the account number you want to update: ";
        cin >> AccountNumber;
        sClient Client;
        char Answer = 'n';
        if (!FindClientByAccountNumber(AccountNumber, vClients, Client))
        {
            cout << "\n [!] Client with Account Number (" << AccountNumber << ") is not found!\n";
            return;
        }
        cout << "\n[-] Current client record:\n";
        PrintClientCard(Client);
        cout << "\n -> Are you sure you want update this client? (Y/N): ";
        cin >> Answer;
        if (Answer != 'y' && Answer != 'Y')
        {
            cout << "\n[-] Update operation canceled.\n";
            return;
        }
        for (sClient &C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C = UpdateRecord(AccountNumber);
                break;
            }
        }
        SaveClientsDataToFile(ClientsFile, vClients);
        cout << "\n[✓] Client Updated Successfully.\n";
    }

    void Deposit(vector<sClient> &vClients)
    {

        PrintHeader("DEPOSIT");
        string AccountNumber;
        cout << " -> pls enter account number : ";
        cin >> AccountNumber;
        sClient Client;
        if (!FindClientByAccountNumber(AccountNumber, vClients, Client))
        {
            cout << "\n [!] Client with Account Number (" << AccountNumber << ") is not found!\n";
            return;
        }

        cout << "\n[-] Current client record:\n";
        PrintClientCard(Client);
        char Answer = 'n';
        cout << "\n -> Are you sure you want update this client? (Y/N): ";
        cin >> Answer;
        if (Answer != 'y' && Answer != 'Y')
        {
            cout << "\n[-] Operation canceled.\n";
            return;
        }
        double Amount;
        cout << " -> pls enter amount to deposite : ";
        cin >> Amount;
        for (sClient &c : vClients)
        {
            if (c.AccountNumber == AccountNumber)
            {
                c.Balance += Amount;
                SaveClientsDataToFile(ClientsFile, vClients);
                cout << "\n\n [+] Deposit Successful. New Balance: " << c.Balance << endl;
                break;
            }
        }
    }

    void Withdraw(vector<sClient> &vClients)
    {
        PrintHeader("WITHDRAW");
        string AccountNumber;
        cout << " -> pls enter account number : ";
        cin >> AccountNumber;
        sClient Client;
        if (!FindClientByAccountNumber(AccountNumber, vClients, Client))
        {
            cout << "\n [!] Client with Account Number (" << AccountNumber << ") is not found!\n";
            return;
        }
        cout << "\n[-] Current client record:\n";
        PrintClientCard(Client);
        char Answer = 'n';
        cout << "\n -> Are you sure you want update this client? (Y/N): ";
        cin >> Answer;
        if (Answer != 'y' && Answer != 'Y')
        {
            cout << "\n[-] Operation canceled.\n";
            return;
        }
        double Amount;
        cout << " -> pls enter amount to withdraw : ";
        cin >> Amount;

        for (sClient &c : vClients)
        {
            if (c.AccountNumber == AccountNumber)
            {
                if (Amount > c.Balance)
                {
                    cout << "\n [!] Insufficient balance. Current Balance: " << c.Balance << endl;
                    return;
                }
                c.Balance -= Amount;

                SaveClientsDataToFile(ClientsFile, vClients);
                cout << "\n\n [-] Withdrawal Successful. New Balance: " << c.Balance << endl;
                break;
            }
        }
    }

    void TotalBalance(vector<sClient> &vClients)
    {
        cout << "\n=========================================================================================\n";
        cout << "\n\t\t\t         TOTAL BALANCES  " << endl;
        cout << "\n=========================================================================================\n";
        ShowAllClientsBalance(vClients);
        double Total = 0.0;
        for (const sClient &c : vClients)
        {
            Total += c.Balance;
        }
        cout << "| " << left << setw(68) << "Total Balance of All Clients :";
        cout << "| " << Total << endl;
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
        cout << "  [6] Transaction Menu\n";
        cout << "  [7] Manage Users\n";
        cout << "  [8] Log Out\n";
        cout << "==================================================\n";
    }
    void UserMenu()
    {
        cout << "\n==================================================\n";
        cout << "                         MANAGE USERS MENU                        \n";
        cout << "==================================================\n";
        cout << "  [1] Show All Users\n";
        cout << "  [2] Add New User/s\n";
        cout << "  [3] Update User Info\n";
        cout << "  [4] Delete User Account\n";
        cout << "  [5] Find User Profile\n";
        cout << "  [6] Back To Main Menu\n";
        cout << "==================================================\n";
    }

    void TransactionMenu()
    {
        cout << "\n==================================================\n";
        cout << "                           TRANSATION MENU                          \n";
        cout << "==================================================\n";
        cout << "  [1] Deposit\n";
        cout << "  [2] Withdraw\n";
        cout << "  [3] Total Balance\n";
        cout << "  [4] Back To Main Menu\n";
        cout << "==================================================\n";
    }

    void TransactionScreen(vector<sClient> &vClients)
    {
        short Choice;
        do
        {
            system("cls");
            TransactionMenu();
            Choice = ReadNumber(1, 4);
            system("cls");
            switch (Choice)
            {
            case 1:
                Deposit(vClients);
                break;
            case 2:
                Withdraw(vClients);
                break;
            case 3:
                TotalBalance(vClients);
                break;
            case 4:
                break;
            }
            if (Choice != 4)
            {
                cout << "\n\nPress any key to go back to the Transaction Menu...";
                system("pause>0");
            }
        } while (Choice != 4);
    }
    void ManageUsersScreen(vector<sUser> &vUsers)
    {
        short Choice;
        do
        {
            system("cls");
            UserMenu();
            Choice = ReadNumber(1, 6);
            system("cls");
            switch (Choice)
            {
            case 1:
                ShowAllUsersData(vUsers);
                break;
            case 2:
                AddUsersToFile(vUsers);
                break;
            case 3:
                UpdateUser(vUsers);
                break;
            case 4:
                DeleteUser(vUsers);
                break;
            case 5:
                FindUser(vUsers);
                break;
            case 6:
                break;
            }
            if (Choice != 6)
            {
                cout << "\n\n Press any key to go back to the Users Menu...";
                system("pause>0");
            }
        } while (Choice != 6);
    }

    enum ePermissions
    {
        eAll = -1,
        eShowAllClient = 1,
        eAddNewClient = 2,
        eUpdateClient = 4,
        eDeleteClient = 8,
        eFindClient = 16,
        eTransaction = 32,
        eManageUsers = 64
    };
    bool CheckUserPermission(ePermissions Permission)
    {
        if (Current.Permissions == ePermissions ::eAll)
            return true;

        if ((Current.Permissions & Permission) == Permission)
            return true;

        return false;
    }

    void BankSystem()
    {
        vector<sClient> vClients;
        vector<sUser> vUsers;
        vClients = LoadClientsDataFromFile(ClientsFile);
        vUsers = LoadUsersDataFromFile(UsersFile);
        short Choice;
        do
        {
            system("cls");
            MainMenu();
            Choice = ReadNumber(1, 8);
            system("cls");
            switch (Choice)
            {
            case 1:
                if (CheckUserPermission(eShowAllClient))
                    ShowAllClientsData(vClients);
                else
                    PrintHeader("ACCESS DENIED !");
                break;
            case 2:
                if (CheckUserPermission(eAddNewClient))
                    AddClientsToFile(vClients);
                else
                    PrintHeader("ACCESS DENIED !");
                break;
            case 3:
                if (CheckUserPermission(eUpdateClient))
                    UpdateClient(vClients);
                else
                    PrintHeader("ACCESS DENIED !");
                break;
            case 4:
                if (CheckUserPermission(eDeleteClient))
                    DeleteClient(vClients);
                else
                    PrintHeader("ACCESS DENIED !");
                break;
            case 5:
                if (CheckUserPermission(eFindClient))
                    FindAccount(vClients);
                else
                    PrintHeader("ACCESS DENIED !");
                break;
            case 6:
                if (CheckUserPermission(eTransaction))
                    TransactionScreen(vClients);
                else
                {
                    PrintHeader("ACCESS DENIED !");
                    cout << "\n\n Press any key to go back to the Main Menu...";
                    system("pause>0");
                }
                break;
            case 7:
                if (CheckUserPermission(eManageUsers))
                    ManageUsersScreen(vUsers);
                else
                {
                    PrintHeader("ACCESS DENIED !");
                    cout << "\n\n Press any key to go back to the Main Menu...";
                    system("pause>0");
                }
                break;
            case 8:
                return;
            }
            if (Choice < 6)
            {
                cout << "\n\n Press any key to go back to the Main Menu...";
                system("pause>0");
            }
        } while (Choice != 8);
    }
    void LogIn()
    {
        do
        {
            vector<sUser> vUsers;
            vUsers = LoadUsersDataFromFile(UsersFile);
            sUser User;
            string Name = "";
            string Password = "";

            system("cls");
            PrintHeader("LOGIN SCREEN");

            cout << " Enter UserName : ";
            getline(cin >> ws, Name);

            if (FindUserByUserName(Name, vUsers, User))
            {
                cout << " Enter Password : ";
                getline(cin, Password);

                if (HashPassword(Password) == User.Password)
                {
                    Current = User;
                    BankSystem();
                }
                else
                {
                    cout << "\n[!] Invalid Password! Press any key to try again...";
                    system("pause>0");
                }
            }
            else
            {
                cout << "\n[!] User not found! Press any key to try again...";
                system("pause>0");
            }
        } while (true);
    }
}