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
    void first_menu()
    {
        int choice{0};
        while (choice == 0)
        {
            cout << "Menu:" << endl;
            cout << "\t1) Login" << endl;
            cout << "\t2) Sign Up" << endl;
            cout << "\t3) Exit" << endl
                 << endl;
            cout << "Enter choice: ";
            cin >> choice;
            if (isdigit(choice) && !(1 <= choice && choice <= 2))
            {
                cout << "Invalid choice, Please try again" << endl;
                continue;
            }
            if (choice == 1)
            {
                login();
            }
            else if (choice == 2)
            {
                signup();
            }
            else if (choice == 3)
            {
                return;
            }
        }
    }
    void
    login()
    {
        string name, password;
        while (true)
        {
            cout << "Enter user name: ";
            cin.ignore();
            getline(cin, name);
            if (name.find(' ') != string::npos)
            {
                cout << "Invalid input. Try again" << endl;
                cout << "***********************************" << endl;
                continue;
            }
            cout << "Enter password: ";
            getline(cin, password);
            if (password.find(' ') != string::npos)
            {
                cout << "Invalid input. Try again" << endl;
                cout << "***********************************" << endl;
                continue;
            }
        }
    }

    void signup()
    {
        string name, password;
        while (true)
        {
            cout << "Enter user name: ";
            cin.ignore();
            getline(cin, name);
            if (name.find(' ') != string::npos)
            {
                cout << "Invalid input. Try again" << endl;
                cout << "***********************************" << endl;
                continue;
            }
            cout << "Enter password: ";
            getline(cin, password);
            if (password.find(' ') != string::npos)
            {
                cout << "Invalid input. Try again" << endl;
                cout << "***********************************" << endl;
                continue;
            }

        }
    }

    void run()
    {
        first_menu();
    }
};

int main()
{
    main_system AskMe;
    AskMe.run();
}