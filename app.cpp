#include <bits/stdc++.h>
using namespace std;

struct system_users
{
    int id;
    string name;
    string password;
};

struct main_system
{
    map<int, system_users> users_data;
    int ids{1};

    int load_data()
    {
        ifstream ud("users_data.txt");
        if (ud.fail())
        {
            cout << "Sorry, can't connect to the server" << endl;
            return 0;
        }
        string user;
        while (getline(ud, user))
        {
            istringstream iss(user);
            iss >> users_data[ids].id;
            iss >> users_data[ids].name;
            iss >> users_data[ids].password;
            ids++;
        }
        ud.close();
        return 1;
    }

    void run()
    {
        int choice{0};
        int account;
        load_data();
        while (true)
        {
            account = first_menu();
            if (account == 0)
                return;
            while (true)
            {
                choice = second_menu();
                // if (choice == 1)
                //     questions_to_me();
                // else if (choice == 2)
                //     questions_from_me();
                // else if (choice == 3)
                //     answer_question();
                // else if (choice == 4)
                //     delete_question();
                // else if (choice == 5)
                //     ask_question();
                // else if (choice == 6)
                //     list_system_users();
                // else if (choice == 7)
                //     feed();
                /* else */if (choice == 8) {
                    cout << "***********************************" << endl;
                    break;
                }
                   
            }
        }
    }

    int first_menu()
    {
        string schoice;
        while (true)
        {
            cout << "Menu:" << endl;
            cout << "\t1) Login" << endl;
            cout << "\t2) Sign Up" << endl;
            cout << "\t3) Exit" << endl
                 << endl;
            cout << "Enter number in range (1 - 3): ";
            getline(cin, schoice);
            if (schoice.size() != 1 || !(schoice[0] == '1' || schoice[0] == '2' || schoice[0] == '3'))
            {
                cout << "ERROR: Invalid input...Try again" << endl;
                cout << "***********************************" << endl;
                continue;
            }
            int choice = (int)schoice[0] - '0';
            if (choice == 1)
                return login();
            else if (choice == 2)
                return signup();
            else if (choice == 3)
                return 0;
        }
        return 0;
    }

    int login()
    {
        string name, password;
        while (true)
        {
            cout << "Enter user name: ";
            getline(cin, name);
            int crnt_id{0};
            if (name.find(' ') != string::npos)
            {
                cout << "ERROR: No space allowed...Try again" << endl;
                cout << "***********************************" << endl;
                continue;
            }
            for (auto &pair : users_data)
            {
                if (name == pair.second.name)
                {
                    crnt_id = pair.first;
                    break;
                }
            }
            if (crnt_id == 0)
            {
                cout << "This name don't exist. Please try again" << endl;
                cout << "***********************************" << endl;
                continue;
            }
            cout << "Enter password: ";
            getline(cin, password);
            if (password.find(' ') != string::npos)
            {
                cout << "ERROR: Invalid input...Try again" << endl;
                cout << "***********************************" << endl;
                continue;
            }
            if (password == users_data[crnt_id].password)
            {
                cout << "***********************************" << endl;
                return crnt_id;
            }
            cout << "Wrong password. Try again" << endl;
            cout << "***********************************" << endl;
        }
    }

    int signup()
    {
        string name, password;
        fstream ud("users_data.txt", ios::app);
        if (ud.fail())
        {
            cout << "Sorry, the system can't add users right now" << endl;
            return 0;
        }
        while (true)
        {
            int flag{0};
            cout << "Enter user name: ";
            getline(cin, name);
            if (name.find(' ') != string::npos)
            {
                cout << "ERROR: No space allowed...Try again" << endl;
                cout << "***********************************" << endl;
                continue;
            }
            for (auto &pair : users_data)
            {
                if (pair.second.name == name)
                {
                    cout << "This name already exist. Please try another name" << endl;
                    cout << "***********************************" << endl;
                    flag = 1;
                    break;
                }
            }
            if (flag)
                continue;
            cout << "Enter password: ";
            getline(cin, password);
            if (password.find(' ') != string::npos)
            {
                cout << "ERROR: No space allowed...Try again" << endl;
                cout << "***********************************" << endl;
                continue;
            }
            break;
        }
        users_data.insert({ids, {ids, name, password}});
        ud << users_data[ids].id << " ";
        ud << users_data[ids].name << " ";
        ud << users_data[ids].password << endl;
        ids++;
        ud.close();
        cout << "***********************************" << endl;
        return ids - 1;
    }

    int second_menu()
    {
        string schoice;
        while (true)
        {
            cout << "Menu:" << endl;
            cout << "\t1) Print Questions To Me" << endl;
            cout << "\t2) Print Questions From Me" << endl;
            cout << "\t3) Answer Question" << endl;
            cout << "\t4) Delete Question" << endl;
            cout << "\t5) Ask Question" << endl;
            cout << "\t6) List System Users" << endl;
            cout << "\t7) Feed" << endl;
            cout << "\t8) Logout" << endl << endl;
            cout << "Enter number in range (1 - 8): ";
            getline(cin, schoice);
            if (schoice.size() != 1 || !(int('1') <= (int)schoice[0] && (int)schoice[0] <= int('8')))
            {
                cout << "ERROR: Invalid input...Try again" << endl;
                cout << "***********************************" << endl;
                continue;
            }
            int choice = (int)schoice[0] - '0';
            return choice;
        }
    }
};

int main()
{
    main_system AskMe;
    AskMe.run();
    return 0;
}