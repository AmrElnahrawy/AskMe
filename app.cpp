#include <bits/stdc++.h>
using namespace std;

struct system_users
{
    int id;
    string name;
    string password;
    int user_status{1};
    int questions_status{1};
};

struct user_questions
{
    int id;
    string question;
    string answer;
};

struct main_system
{
    map<int, system_users> users_data;
    int users_ids{10};
    map<int, vector<user_questions>> questions;

    int load_data()
    {
        ifstream ud("users_data.txt");
        if (ud.fail())
        {
            cout << "Sorry, can't connect to the server" << endl;
            return 0;
        }
        string user;
        int id;
        while (getline(ud, user))
        {
            istringstream iss(user);
            iss >> id;
            users_data[id].id = id;
            iss >> users_data[id].name;
            iss >> users_data[id].password;
            iss >> users_data[id].user_status;
            if (id >= users_ids)
                users_ids++;
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
                if (choice == 1)
                    user_sittings(account);
                else if (choice == 2)
                    questions_to_me();
                else if (choice == 3)
                    questions_from_me();
                else if (choice == 4)
                    answer_question();
                else if (choice == 5)
                    delete_question();
                else if (choice == 6)
                    ask_question();
                else if (choice == 7)
                    list_system_users();
                else if (choice == 8)
                    feed();
                else if (choice == 9)
                {
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
        users_data.insert({users_ids, {users_ids, name, password}});
        ud << users_data[users_ids].id << " ";
        ud << users_data[users_ids].name << " ";
        ud << users_data[users_ids].password << " ";
        ud << users_data[users_ids].user_status << " ";
        ud << users_data[users_ids].questions_status << endl;
        ud.close();
        cout << "***********************************" << endl;
        cout << "Welcome " << users_data[users_ids].name << ", your id is [" << users_data[users_ids].id << "]" << endl;
        cout << "***********************************" << endl;
        users_ids++;
        return users_ids - 1;
    }

    int second_menu()
    {
        string schoice;
        while (true)
        {
            cout << "Menu:" << endl;
            cout << "\t1) User Sittings" << endl;
            cout << "\t2) Print Questions To Me" << endl;
            cout << "\t3) Print Questions From Me" << endl;
            cout << "\t4) Answer Question" << endl;
            cout << "\t5) Delete Question" << endl;
            cout << "\t6) Ask Question" << endl;
            cout << "\t7) List System Users" << endl;
            cout << "\t8) Feed" << endl;
            cout << "\t9) Logout" << endl
                 << endl;
            cout << "Enter number in range (1 - 8): ";
            getline(cin, schoice);
            if (schoice.size() != 1 || !(int('1') <= (int)schoice[0] && (int)schoice[0] <= int('9')))
            {
                cout << "ERROR: Invalid input...Try again" << endl;
                cout << "***********************************" << endl;
                continue;
            }
            int choice = (int)schoice[0] - '0';
            return choice;
        }
    }

    void user_sittings(int id)
    {
        fstream ud("users_data.txt", ios::app);
        if (ud.fail())
        {
            cout << "Sorry, the system can't change sittings right now" << endl;
            return;
        }
        int status = users_data[id].user_status;
        string schoice;
        while (true)
        {
            cout << "Your name is " << (users_data[id].user_status == 1 ? "public" : "anonymous") << ", anonymous questions are"  <<  (users_data[id].questions_status == 1 ? " allowed" : " not allowed" ) << endl;
            cout << "\t1) Change name (public - anonymous)" << endl;
            cout << "\t2) Allow questions (anonymous - public only)" << endl;
            cout << "\t3) Return" << endl
                 << endl;
            cout << "Enter number in range (1 - 3): ";
            getline(cin, schoice);
            if (schoice.size() != 1 || !(int('1') <= (int)schoice[0] && (int)schoice[0] <= int('3')))
            {
                cout << "ERROR: Invalid input...Try again" << endl;
                cout << "***********************************" << endl;
                continue;
            }
            if (schoice[0] == '1')
                users_data[id].user_status == 1 ? users_data[id].user_status = 2 : users_data[id].user_status = 1;
            if (schoice[0] == '2')
                users_data[id].questions_status == 1 ? users_data[id].questions_status = 2 : users_data[id].questions_status = 1;
            if (schoice[0] == '3')
                return;
            break;
        }
        ud << users_data[id].id << " ";
        ud << users_data[id].name << " ";
        ud << users_data[id].password << " ";
        ud << users_data[id].user_status << " ";
        ud << users_data[id].questions_status << endl;
        cout << "***********************************" << endl;
        ud.close();
    }

    void questions_to_me()
    {
    }

    void questions_from_me()
    {
    }

    void answer_question()
    {
    }

    void delete_question()
    {
    }

    void ask_question()
    {
    }

    void list_system_users()
    {
        if (users_data.empty())
        {
            cout << "No users in the database" << endl;
            cout << "***********************************" << endl;
            return;
        }
        cout << "***********************************" << endl;
        for (const auto &pair : users_data)
        {
            cout << "ID: " << pair.first << "\tName: " << pair.second.name << endl;
        }
        cout << "***********************************" << endl;
    }

    void feed()
    {
    }
};

int main()
{
    main_system AskMe;
    AskMe.run();
    return 0;
}