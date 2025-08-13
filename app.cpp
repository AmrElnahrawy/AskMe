#include <bits/stdc++.h>
using namespace std;

int is_digit(string num) {
    if (num == "-1")
        return 1;
    for (char i : num) {
        if (!('0' <= i && i <= '9'))
            return 0;
    }
    return 1;
}

struct system_users
{
    int id;
    string name;
    string password;
    int questions_status{1};
};

struct users_questions
{
    int id;
    int parent_id{-1};
    int questions_status{1};
    int from;
    int to;
    int deleted{0};
    string question;
    string answer;
};

struct main_system
{
    map<int, system_users> users_data;
    int users_ids{10};
    map<int, users_questions> questions;
    int questions_ids{100};

    int load_users_data()
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
            iss >> users_data[id].questions_status;
            if (id >= users_ids)
                users_ids++;
        }
        ud.close();
        return 1;
    }

    int load_questions_data()
    {
        ifstream qd("questions_data.txt");
        if (qd.fail())
        {
            cout << "Sorry, can't connect to the server" << endl;
            return 0;
        }
        string question;
        int id;
        while (getline(qd, question))
        {
            istringstream iss(question);
            iss >> id;
            questions[id].id = id;
            iss >> questions[id].parent_id;
            iss >> questions[id].questions_status;
            iss >> questions[id].from;
            iss >> questions[id].to;
            iss >> questions[id].deleted;
            string str, qstr = "", astr = "";
            while (qstr != "#")
            {
                iss >> str;
                qstr += str + " ";
            }
            questions[id].question = qstr;
            iss.ignore();
            while (iss)
            {
                iss >> str;
                astr += str + " ";
            }

            questions[id].answer = astr;
            if (id >= questions_ids)
                questions_ids++;
        }
        qd.close();
        return 1;
    }

    void run()
    {
        int choice{0};
        int account;
        load_users_data();
        load_questions_data();
        while (true)
        {
            account = first_menu();
            if (account == 0)
                return;
            while (true)
            {
                choice = second_menu();
                if (choice == 1)
                    user_settings(account);
                else if (choice == 2)
                    questions_to_me();
                else if (choice == 3)
                    questions_from_me();
                else if (choice == 4)
                    answer_question();
                else if (choice == 5)
                    delete_question();
                else if (choice == 6)
                    ask_question(account);
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
        ud << users_data[users_ids].questions_status << endl;
        ud.close();
        cout << "***********************************" << endl;
        cout << "Hello " << users_data[users_ids].name << ", your id is [" << users_data[users_ids].id << "]" << endl;
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
            cout << "Enter number in range (1 - 9): ";
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

    void user_settings(int id)
    {
        fstream ud("users_data.txt", ios::app);
        if (ud.fail())
        {
            cout << "Sorry, the system can't change sittings right now" << endl;
            return;
        }
        string schoice;
        while (true)
        {
            cout << "Anonymous questions are" << (users_data[id].questions_status == 1 ? " allowed" : " not allowed") << endl;
            cout << "\t1) Allow questions (anonymous - public only)" << endl;
            cout << "\t2) Return" << endl
                 << endl;
            cout << "Enter number in range (1 - 2): ";
            getline(cin, schoice);
            if (schoice.size() != 1 || !(int('1') <= (int)schoice[0] && (int)schoice[0] <= int('2')))
            {
                cout << "ERROR: Invalid input...Try again" << endl;
                cout << "***********************************" << endl;
                continue;
            }
            if (schoice[0] == '1')
                users_data[id].questions_status == 1 ? users_data[id].questions_status = 2 : users_data[id].questions_status = 1;
            if (schoice[0] == '2')
                return;
            break;
        }
        ud << users_data[id].id << " ";
        ud << users_data[id].name << " ";
        ud << users_data[id].password << " ";
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

    void ask_question(int account)
    {
        fstream qd("questions_data.txt", ios::app);
        if (qd.fail())
        {
            cout << "Sorry, can't add questions right now" << endl;
            return;
        }
        string suid, sanon, sqid, question;
        int flag{1}, uid, anon, qid;
        while (true)
        {
            cout << "Enter user ID or -1 to cancel: ";
            getline(cin, suid);
            if (suid.find(' ') != string::npos && is_digit(suid))
            {
                cout << "ERROR: Invalid input...Try again" << endl;
                cout << "***********************************" << endl;
                continue;
            }
            uid = stoi(suid);
            for (auto &pair : users_data)
            {
                if (uid == -1 || uid == pair.first)
                {
                    flag = 0;
                    break;
                }
            }
            if (flag)
            {
                cout << "ERROR: User doesn't exist...Try again" << endl;
                cout << "***********************************" << endl;
                continue;
            }
            break;
        }
        if (uid == -1)
        {
            cout << "***********************************" << endl;
            return;
        }
        if (users_data[uid].questions_status == 2)
        {
            cout << "Note: Anonymous questions are not allowed for this user" << endl;
            anon = 2;
        }
        else
        {
            while (true)
            {
                cout << "Enter 2 for anonymous question else 1: ";
                 getline(cin, sanon);
                if (sanon.find(' ') != string::npos && !(sanon[0] == '1' || sanon[0] == '2'))
                {
                    cout << "ERROR: Invalid input...Try again" << endl;
                    cout << "***********************************" << endl;
                    continue;
                }
                anon = stoi(sanon);
                break;
            }
        }
        while (true)
        {
            cout << "For thread question enter Question ID or -1 for new question: " << endl;
             getline(cin, sqid);
            if (sqid.find(' ') != string::npos && is_digit(sqid))
            {
                cout << "ERROR: Invalid input...Try again" << endl;
                cout << "***********************************" << endl;
                continue;
            }
            qid = stoi(sqid);
            for (auto &pair : questions)
            {
                if (qid == -1 || qid == pair.second.parent_id)
                {
                    flag = 0;
                    break;
                }
            }
            if (flag)
            {
                cout << "ERROR: the main question is deleted or doesn't exist" << endl;
                cout << "***********************************" << endl;
                continue;
            }
            break;
        }
        while (true)
        {
            cout << "Enter question (# is not allowed): ";
            getline(cin, question);
            if (question.find('#') != string::npos)
            {
                cout << "ERROR: Invalid input...Try again" << endl;
                cout << "***********************************" << endl;
                continue;
            }
            cout << "***********************************" << endl;
            break;
        }
        questions.insert({questions_ids, {questions_ids, qid, anon, account, uid, 0, question, ""}});
        qd << questions[questions_ids].id << " ";
        qd << questions[questions_ids].parent_id << " ";
        qd << questions[questions_ids].questions_status << " ";
        qd << questions[questions_ids].from << " ";
        qd << questions[questions_ids].to << " ";
        qd << questions[questions_ids].deleted << " ";
        qd << questions[questions_ids].question << " ";
        qd << "#" << endl;
        questions_ids++;
        qd.close();
    }

    void
    list_system_users()
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