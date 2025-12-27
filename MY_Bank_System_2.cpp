#include<iostream>///////////////////test date//
#include<string>
#include<limits>
#include<iomanip>
#include<vector>
#include<fstream>
using namespace std;
const string Bank = "C:/Bank_System/Client.txt";
const string Users_d = "C:/Bank_System/Users.txt";
struct St_Cilent
{
    string Account_number;
    string pin_code;
    string Full_name;
    string phone;
    double Account_balance;
    bool Mark = false;
};

struct St_User
{
    string User_name;
    string Password;
    int Permisson;
    bool Marking = false;
};
enum EN_Record { Show = 1, Add = 2, Delete = 3, Update = 4, Find = 5, Tranacthions = 6, Manage_users = 7, Exit = 8 };
enum En_Record_manage { Users_List = 1, NewUser = 2, E_Delete = 3, E_Update = 4, E_find = 5, main_Menu = 6 };

enum EN_Record_Tranacthions { Deposit_1 = 1, Winthdraw_1 = 2, toala_balances = 3, Main_menu = 4 };

enum EN_Permissions { E_full = -1, PE_list_Client = 1, P_E_Add_New_Client = 2, E_P_DElete_Client = 4, P_E_Update_Clent = 8, P_E_Find_clent = 16, P_E_Tranactions = 32, Manage_Users = 64 };

St_User Global;
vector<string>Split_Line(string Word, string Dlimter)
{
    string Add_Word_data;
    int Index_pos = 0;
    vector<string>Data;
    while ((Index_pos = Word.find(Dlimter)) != std::string::npos)
    {
        Add_Word_data = Word.substr(0, Index_pos);
        if (!Add_Word_data.empty())
        {
            Data.push_back(Add_Word_data);
        }
        Word.erase(0, Index_pos + Dlimter.length());
    }
    if (!Word.empty())
    {
        Data.push_back(Word);
    }
    return Data;
}

St_Cilent Add_data_To_struct(string Line, string Delimter = "/")
{
    vector<string>S_v;

    St_Cilent Data_bank;

    S_v = Split_Line(Line, Delimter);
    if (S_v.size() >= 5)
    {
        Data_bank.Account_number = S_v[0];

        Data_bank.pin_code = S_v[1];

        Data_bank.Full_name = S_v[2];

        Data_bank.phone = S_v[3];

        Data_bank.Account_balance = stod(S_v[4]);
    }

    return Data_bank;
}

St_User Add_Users_To_Struct(string Line, string Delimter = "/$/")
{
    St_User u;
    vector<string>Users;
    Users = Split_Line(Line, Delimter);

    if (Users.size() >= 3)
    {
        u.User_name = Users[0];

        u.Password = Users[1];

        u.Permisson = stoi(Users[2]);

    }

    return u;
}

vector<St_Cilent>Read_file_And_Add_data_in_file_to_Vectoe(const string& Loc_file)
{
    fstream Read_F;
    vector<St_Cilent>Ref;
    Read_F.open(Loc_file, ios::in);
    if (Read_F.is_open())
    {
        string line_add;
        St_Cilent Data;
        while (getline(Read_F, line_add))
        {
            Data = Add_data_To_struct(line_add);
            Ref.push_back(Data);
        }
        Read_F.close();
    }
    return Ref;
}

vector<St_User>Read_File_And_Add_Users_To_Vector(const string& Loc_file)
{
    fstream Read_F;
    vector<St_User>Ref;
    Read_F.open(Loc_file, ios::in);
    if (Read_F.is_open())
    {
        string line_add;
        St_User User;
        while (getline(Read_F, line_add))
        {
            User = Add_Users_To_Struct(line_add);
            Ref.push_back(User);
        }
        Read_F.close();
    }
    return Ref;
}

bool Check_if_the_account_number_exists_or_noteck(string Account_number_User, vector<St_Cilent>& Data)
{
    if (Data.empty())return false;
    for (St_Cilent& Client : Data)
    {
        if (Client.Account_number == Account_number_User)
        {
            return true;
        }
    }
    return false;
}

bool Check_if_the_Username_exists_or_noteck(string Username, vector<St_User>& User)
{
    if (User.empty())return false;
    for (St_User& Users : User)
    {
        if (Users.User_name == Username)
        {
            return true;
        }
    }
    return false;
}

int Read_Permissions()
{
    int Per = 0;
    char User_input = 'N';

    cout << "Do You Want Full Access : [Y / N ] : ";
    cin >> User_input;
    if (toupper(User_input) == 'Y') Per += E_full;

    cout << "Do You Want Show List client Access : [Y / N ] : ";
    cin >> User_input;
    if (toupper(User_input) == 'Y') Per += PE_list_Client;

    cout << "Do You Want Add New client Access : [Y / N ] : ";
    cin >> User_input;
    if (toupper(User_input) == 'Y') Per += P_E_Add_New_Client;


    cout << "Do You Want delete Client Access : [Y / N ] : ";
    cin >> User_input;
    if (toupper(User_input) == 'Y') Per += E_P_DElete_Client;


    cout << "Do You Want updat Client Access : [Y / N ] : ";
    cin >> User_input;
    if (toupper(User_input) == 'Y') Per += P_E_Update_Clent;


    cout << "Do You Want Find Client Access : [Y / N ] : ";
    cin >> User_input;
    if (toupper(User_input) == 'Y') Per += P_E_Find_clent;


    cout << "Do You Want Tranactions Access : [Y / N ] : ";
    cin >> User_input;
    if (toupper(User_input) == 'Y') Per += P_E_Tranactions;

    cout << "Do You Want Manage Users Access : [Y / N ] : ";
    cin >> User_input;
    if (toupper(User_input) == 'Y') Per += Manage_Users;

    return Per;
}

St_Cilent Read_Data(vector<St_Cilent>& Data_cli, bool Read_Account_number = false)
{
    St_Cilent data;

    //-------------check_Account_number------------//
    if (!Read_Account_number)
    {
        cout << " Enter A Account Number : ";
        getline(cin >> ws, data.Account_number);

        while (Check_if_the_account_number_exists_or_noteck(data.Account_number, Data_cli))
        {
            cout << "Sory ): Invaled Account Number [" << data.Account_number << "] :: Enter Account Number : ";
            getline(cin >> ws, data.Account_number);
        }
    }

    cout << "Enter A  Pin Code  : ";
    getline(cin >> ws, data.pin_code);

    cout << "Enter A Full Name : ";
    getline(cin >> ws, data.Full_name);

    cout << "Enter A Phone : ";
    getline(cin >> ws, data.phone);

    cout << "Enter A Account Balance : ";
    cin >> data.Account_balance;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return data;
}

St_User Read_USer(vector<St_User>& Users, bool Read_Usernaem = false)
{
    St_User USer;

    if (!Read_Usernaem)
    {
        cout << " Enter A Username : ";
        getline(cin >> ws, USer.User_name);

        while (Check_if_the_Username_exists_or_noteck(USer.User_name, Users))
        {
            cout << "Sory ): Invaled Username  [" << USer.User_name << "] :: Enter Username: ";
            getline(cin >> ws, USer.User_name);
        }
    }

    cout << "Enter Password : ";
    getline(cin >> ws, USer.Password);
    ///Raed_Perm 
    USer.Permisson = Read_Permissions();

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return USer;
}

void show_data1(St_Cilent data)
{

    cout << "======================" << endl;
    cout << " Account Number: " << data.Account_number << endl;

    cout << " Pin code      : " << data.pin_code << endl;

    cout << " Full Name     : " << data.Full_name << endl;

    cout << " Phone         : " << data.phone << endl;

    cout << "Account Balance: " << data.Account_balance << endl;
    cout << "======================" << endl;
}



void show_data2(St_User data)
{

    cout << "======================" << endl;
    cout << " User name : " << data.User_name << endl;

    cout << " Password      : " << data.Password << endl;

    cout << " Permisson   : " << data.Permisson << endl;

    cout << "======================" << endl;
}

string Add_date_To_one_line_and_Delmter(St_Cilent Data, string Delimter = "/")
{

    return   Data.Account_number + Delimter + Data.pin_code + Delimter + Data.Full_name + Delimter + Data.phone + Delimter + to_string(Data.Account_balance);
}


string Add_Users_To_one_line_and_Delmter(St_User User, string Delimter = "/$/")
{

    return  User.User_name + Delimter + User.Password + Delimter + to_string(User.Permisson);
}


void Add_data_To_File(const string& loc, string line)
{
    fstream Add_mod;
    Add_mod.open(loc, ios::out | ios::app);//
    if (Add_mod.is_open())
    {
        Add_mod << line << '\n';
        Add_mod.flush();
        Add_mod.close();
    }
}

void Add_more_data(vector<St_Cilent>& data1)
{
    St_Cilent Add;
    char What = 'N';
    do
    {
        Add = Read_Data(data1);

        Add_data_To_File(Bank, Add_date_To_one_line_and_Delmter(Add));
        data1.push_back(Add);
        cout << "Do you Add More Client [Y / N ] : ";

        cin >> What;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\t\tAdd New Data :-) \n";


    } while (toupper(What) == 'Y');

}

void Add_More_Users(vector<St_User>& User)
{
    St_User Add;
    char What = 'N';
    do
    {
        Add = Read_USer(User);

        Add_data_To_File(Users_d, Add_Users_To_one_line_and_Delmter(Add));
        User.push_back(Add);
        cout << "Do You Add More User [Y / N ] : ";

        cin >> What;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\t\tAdd New User :-) \n";


    } while (toupper(What) == 'Y');

}

bool Find_Client(string Account_number, vector<St_Cilent>& data, St_Cilent& New_data)
{
    for (St_Cilent& client : data)
    {
        if (client.Account_number == Account_number)
        {
            New_data = client;

            return true;
        }
    }
    return false;
}

bool Find_User(string Username, vector<St_User>& data, St_User& New_User)
{
    for (St_User& Users : data)
    {
        if (Users.User_name == Username)
        {
            New_User = Users;

            return true;
        }
    }
    return false;
}

bool Find_User_name_A_Password(string Username, string Password, vector<St_User>& data, St_User& New_User)
{
    for (St_User& Users : data)
    {
        if (Users.User_name == Username && Users.Password == Password)
        {
            New_User = Users;

            return true;
        }
    }
    return false;
}


bool Check_account_number_and_marking(vector<St_Cilent>& data, string Account_number)
{
    for (St_Cilent& A : data)
    {
        if (A.Account_number == Account_number)
        {
            A.Mark = true;
            return true;
        }

    }
    return false;
}

bool Check_Username_and_marking(vector<St_User>& User, string Username)
{
    for (St_User& A : User)
    {
        if (A.User_name == Username)
        {
            A.Marking = true;
            return true;
        }

    }
    return false;
}

vector<St_Cilent> Delete_data_In_file(const string& loc, vector<St_Cilent>& REf)
{
    fstream IS_delete;
    IS_delete.open(loc, ios::out);//Delete Mod / 
    if (IS_delete.is_open())
    {
        for (St_Cilent& LOOP : REf)
        {
            if (!LOOP.Mark)
            {
                IS_delete << Add_date_To_one_line_and_Delmter(LOOP) << endl;
            }

        }
        IS_delete.close();
    }
    return REf;
}

vector<St_User> Delete_User_In_file(const string& loc, vector<St_User>& REf)
{
    fstream IS_delete;
    IS_delete.open(loc, ios::out);//Delete Mod / 
    if (IS_delete.is_open())
    {
        for (St_User& LOOP : REf)
        {
            if (!LOOP.Marking)
            {
                IS_delete << Add_Users_To_one_line_and_Delmter(LOOP) << endl;
            }

        }
        IS_delete.close();
    }
    return REf;
}


bool More_Delete_Client(string Account_number, vector<St_Cilent>& data)
{
    St_Cilent data1;
    char USer = 'N';
    if (Find_Client(Account_number, data, data1))
    {
        show_data1(data1);
        cout << "Are You Sure Delete : ";
        cin >> USer;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (toupper(USer) == 'Y')
        {
            Check_account_number_and_marking(data, Account_number);
            Delete_data_In_file(Bank, data);
            return true;
        }
        else
        {
            cout << "\nDeletion cancelled by user." << endl;
            return false;
        }
    }
    else
        while (!Find_Client(Account_number, data, data1))
        {
            cout << "\n Client with Account Number " << Account_number << "Is Not Found ! ";
            cout << "Enter A Account Number ";
            cin >> Account_number;
        }

    return false;
}

bool Update_Client(string Account_number, vector<St_Cilent>& Data_New)
{
    St_Cilent Showing;
    char User = 'N';
    if (Find_Client(Account_number, Data_New, Showing))
    {
        show_data1(Showing);
        cout << "Are You Sure IS Updata Data  [ Y / N ] :";
        cin >> User;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (toupper(User) == 'Y')
        {
            for (St_Cilent& Itr : Data_New)//
            {
                if (Itr.Account_number == Account_number)
                {
                    Itr = Read_Data(Data_New, true);
                    break;
                }
            }

            Delete_data_In_file(Bank, Data_New);
            return true;
        }
    }
    else
    {
        while (!Find_Client(Account_number, Data_New, Showing))
        {
            cout << "\n Client with Account Number " << Account_number << "Is Not Found ! ";
            cout << "Enter A Account Number ";
            cin >> Account_number;

        }
    }

    return false;
}

bool Update_User(string Username, vector<St_User>& Data_New)
{
    St_User Showing;
    char User = 'N';
    if (Find_User(Username, Data_New, Showing))
    {
        show_data2(Showing);
        cout << "Are You Sure IS Updata Data  [ Y / N ] :";
        cin >> User;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (toupper(User) == 'Y')
        {
            for (St_User& Itr : Data_New)//
            {
                if (Itr.User_name == Username)
                {
                    Itr = Read_USer(Data_New, true);
                    break;
                }
            }

            Delete_User_In_file(Users_d, Data_New);
            return true;
        }
    }
    else
    {
        while (!Find_User(Username, Data_New, Showing))
        {
            cout << "\n Client with Account Number " << Username << "Is Not Found ! ";
            cout << "Enter A Account Number ";
            cin >> Username;

        }
    }

    return false;
}






bool More_Delete_User(string User_name, vector<St_User>& Users)
{
    St_User User;
    char USer = 'N';
    if (Find_User(User_name, Users, User))
    {
        show_data2(User);
        cout << "Are You Sure Delete : ";
        cin >> USer;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (toupper(USer) == 'Y')
        {
            Check_Username_and_marking(Users, User_name);
            Delete_User_In_file(Users_d, Users);
            return true;
        }
        else
        {
            cout << "\nDeletion cancelled by user." << endl;
            return false;
        }
    }
    else
        if (!Find_User(User_name, Users, User))
        {
            cout << "\n Client with Username " << User_name << "Is Not Found ! ";
            cout << "Enter A Account Number ";
            cin >> User_name;
        }

    return false;
}

bool Add_Balances(string Account_number, vector<St_Cilent>& Data)
{
    St_Cilent data1;
    double Add_Balances = 0;
    char User = 'N';
    if (Find_Client(Account_number, Data, data1))
    {
        show_data1(data1);
        do
        {
            cout << "Pleade Enter Deposit Amount : ";
            cin >> Add_Balances;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (Add_Balances <= 0)
            {
                cout << "Invalid amount! Please enter a positive number:??";
            }

        } while (Add_Balances <= 0);
        cout << "Are You Sure  You want Perfrom this transacthion [ Y / N ] :";
        cin >> User;
        if (toupper(User) == 'Y')
        {
            for (St_Cilent& Balance : Data)
            {
                if (Balance.Account_number == Account_number)
                {
                    Balance.Account_balance += Add_Balances;
                    cout << "New Deposit : " << Balance.Account_balance << endl;
                    break;
                }
            }
            Delete_data_In_file(Bank, Data);
            return true;
        }
    }
    else
    {
        while (!Find_Client(Account_number, Data, data1))
        {
            cout << "\n Client with Account Number " << Account_number << "Is Not Found ! ";
            cout << "Enter A Account Number ";
            cin >> Account_number;

        }
    }
    return false;
}

bool Withdraw(string Account_number, vector<St_Cilent>& Data)
{
    St_Cilent data1;
    double Withdraw = 0;
    char User = 'N';
    if (Find_Client(Account_number, Data, data1))
    {
        show_data1(data1);
        do
        {
            cout << "Please Enter Withdraw Amount : ";
            cin >> Withdraw;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (Withdraw >= data1.Account_balance)
            {
                cout << "Amount exceeds balance! You can withdraw up to: " << data1.Account_balance << endl;
            }

        } while (Withdraw >= data1.Account_balance);
        cout << "Are You Sure  You want Perfrom this withdraw [ Y / N ] :";
        cin >> User;
        if (toupper(User) == 'Y')
        {
            for (St_Cilent& Withdraw1 : Data)
            {
                if (Withdraw1.Account_number == Account_number)
                {
                    Withdraw1.Account_balance -= Withdraw;
                    cout << "New Deposit : " << Withdraw1.Account_balance << endl;
                    break;
                }
            }
            Delete_data_In_file(Bank, Data);
            return true;
        }
    }
    else
    {
        while (!Find_Client(Account_number, Data, data1))
        {
            cout << "\n Client with Account Number " << Account_number << "Is Not Found ! ";
            cout << "Enter A Account Number ";
            cin >> Account_number;

        }
    }
    return false;
}

///_____________________________________________________________________________________________//
void Pritn_data_Record1(St_Cilent& client)//data client is  a vector data struct //
{


    cout << "| " << setw(15) << client.Account_number;
    cout << "| " << setw(10) << client.pin_code;
    cout << "| " << setw(40) << client.Full_name;
    cout << "| " << setw(12) << client.phone;
    cout << "| " << setw(12) << client.Account_balance;
}
void Pritn_data_For_vectorst1(vector<St_Cilent>& client)
{


    cout << "\n\t\t\t\t\t client List(" << client.size() << ")Client(s)" << endl;

    cout << "\n=================================================================================================*\n" << endl;
    cout << "| " << left << setw(15) << " Accout Number ";
    cout << "| " << left << setw(10) << " Pin Code ";
    cout << "| " << left << setw(40) << " Client Name ";
    cout << "| " << left << setw(12) << " Phone ";
    cout << "| " << left << setw(12) << " Balance ";
    cout << "\n=================================================================================================*\n" << endl;
    for (St_Cilent One_client : client)
    {
        Pritn_data_Record1(One_client);
        cout << endl;
    }
    cout << "\n=================================================================================================*\n" << endl;

}


void Pritn_Users_Record(St_User& User)//data client is  a vector data struct //
{


    cout << "| " << setw(15) << User.User_name;
    cout << "| " << setw(10) << User.Password;
    cout << "| " << setw(40) << User.Permisson;

}
void Pritn_Users_For_vectorst(vector<St_User>& User)
{


    cout << "\n\t\t\t\t\t Users List(" << User.size() << ")Users(s)" << endl;

    cout << "\n=================================================================================================*\n" << endl;
    cout << "| " << left << setw(15) << " Username  ";
    cout << "| " << left << setw(10) << " Password  ";
    cout << "| " << left << setw(40) << " Permissions ";

    cout << "\n=================================================================================================*\n" << endl;
    for (St_User One_User : User)
    {
        Pritn_Users_Record(One_User);
        cout << endl;
    }
    cout << "\n=================================================================================================*\n" << endl;

}





void print_data_B(St_Cilent& client)
{


    cout << "| " << setw(15) << client.Account_number;
    cout << "| " << setw(40) << client.Full_name;
    cout << "| " << setw(12) << client.Account_balance;
}
void print_data_B1(vector<St_Cilent>& client)
{
    double total_balance = 0;


    cout << "\n\t\t\t\t\t client List(" << client.size() << ")Client(s)" << endl;

    cout << "\n=================================================================================================*\n" << endl;
    cout << "| " << left << setw(15) << " Accout Number ";
    cout << "| " << left << setw(40) << " Client Name ";
    cout << "| " << left << setw(12) << " Balance ";
    cout << "\n=================================================================================================*\n" << endl;
    for (St_Cilent One_client : client)
    {
        print_data_B(One_client);
        cout << endl;
        total_balance += One_client.Account_balance;
    }
    cout << "\n\t\t\t\t\t TOtal Balances : " << total_balance << endl;
    cout << "\n=================================================================================================*\n" << endl;

}

void Pritn_data_Record(St_Cilent& client)//data client is  a vector data struct //
{


    cout << "| " << setw(15) << client.Account_number;
    cout << "| " << setw(10) << client.pin_code;
    cout << "| " << setw(40) << client.Full_name;
    cout << "| " << setw(12) << client.phone;
    cout << "| " << setw(12) << client.Account_balance;
}
void Pritn_data_For_vectorst(vector<St_Cilent>& client)
{


    cout << "\n\t\t\t\t\t client List(" << client.size() << ")Client(s)" << endl;

    cout << "\n=================================================================================================*\n" << endl;
    cout << "| " << left << setw(15) << " Accout Number ";
    cout << "| " << left << setw(10) << " Pin Code ";
    cout << "| " << left << setw(40) << " Client Name ";
    cout << "| " << left << setw(12) << " Phone ";
    cout << "| " << left << setw(12) << " Balance ";
    cout << "\n=================================================================================================*\n" << endl;
    for (St_Cilent One_client : client)
    {
        Pritn_data_Record(One_client);
        cout << endl;
    }
    cout << "\n=================================================================================================*\n" << endl;

}



void msg()
{
    cout << "-------------------------------------------\n";
    cout << "  ACCESS DENIED!\n";
    cout << "  You don't have permission to perform this action.\n";
    cout << "  Please contact your Admin.\n";
    cout << "-------------------------------------------\n";
}


void Show_Adding_New_Data(vector<St_Cilent>& add)
{
    system("cls");

    cout << "=============================" << endl;
    cout << "\t Add Data \t" << endl;
    cout << "=============================" << endl;

    Add_more_data(add);
}

void Show_Adding_New_User(vector<St_User>& add)
{
    system("cls");

    cout << "=============================" << endl;
    cout << "\t Add User \t" << endl;
    cout << "=============================" << endl;

    Add_More_Users(add);
}

void show_List_Screan_Users(vector<St_User>& users)
{
      system("cls");
    Pritn_Users_For_vectorst(users);
}

void show_list_client_screan(vector<St_Cilent>& clent)
{
     system("cls");
    Pritn_data_For_vectorst1(clent);
}
string ReadUserName()
{
    string Username = "";
    cout << "\nPlease enter Username? ";
    cin >> Username;
    return Username;
}
string ReadClientAccountNumber()
{
    string AccountNumber = "";
    cout << "\nPlease enter AccountNumber? ";
    cin >> AccountNumber;
    return AccountNumber;
}


void Show_delete_Client(vector<St_Cilent>& New_data)
{
    system("cls");

    cout << "=============================" << endl;
    cout << "\t  Delete Client \t" << endl;
    cout << "=============================" << endl;

    if (More_Delete_Client(ReadClientAccountNumber(), New_data)) cout << "Verified......Scanned[Done]" << endl;//Here we check whether the scan was successful or not//
    else
        cout << "Verification failed![Not]" << endl;
}

void Show_delete_User(vector<St_User>& New_data)
{
    system("cls");

    cout << "=============================" << endl;
    cout << "\t  Delete User \t" << endl;
    cout << "=============================" << endl;

    if (More_Delete_User(ReadUserName(), New_data)) cout << "Verified......Scanned[Done]" << endl;//Here we check whether the scan was successful or not//
    else
        cout << "Verification failed![Not]" << endl;
}


void Show_Update_User(vector<St_User>& New_data)
{
    system("cls");

    cout << "=============================" << endl;
    cout << "\t  Update User \t" << endl;
    cout << "=============================" << endl;

    if (Update_User(ReadUserName(), New_data)) cout << "Verified......Scanned[Done]" << endl;//Here we check whether the scan was successful or not//
    else
        cout << "Verification failed![Not]" << endl;
}

void Show_Update_Client(vector<St_Cilent>& New_data)
{
    system("cls");

    cout << "=============================" << endl;
    cout << "\t  Update Client \t" << endl;
    cout << "=============================" << endl;

    if (Update_Client(ReadClientAccountNumber(), New_data)) cout << "Verified......Scanned[Done]" << endl;//Here we check whether the scan was successful or not//
    else
        cout << "Verification failed![Not]" << endl;
}

void Show_Client_find(vector<St_Cilent>& Data)
{

    St_Cilent data1;
    cout << "=============================" << endl;
    cout << "\t  Find Client \t" << endl;
    cout << "=============================" << endl;
    string Cl = ReadClientAccountNumber();
    if (Find_Client(Cl, Data, data1))
    {
        cout << "Verified......Scanned[Done]" << endl;
        show_data1(data1);
    }
    else

        cout << "Verification failed![Not] Account Number Is Not True [" << Cl << ']' << endl;

}

void Show_User_find(vector<St_User>& Data)
{

    St_User data1;
    cout << "============================" << endl;
    cout << "\t  Find User \t" << endl;
    cout << "=============================" << endl;
    string Cl = ReadUserName();
    if (Find_User(Cl, Data, data1))
    {
        cout << "Verified......Scanned[Done]" << endl;
        show_data2(data1);
    }
    else

        cout << "Verification failed![Not] Account Number Is Not True [" << Cl << ']' << endl;

}

void Show_Deposit(vector<St_Cilent>& data_TO_vector)
{
    string Accout_number = ReadClientAccountNumber();
    system("cls");
    cout << "=============================" << endl;
    cout << "\t    Deposit   \t" << endl;
    cout << "=============================" << endl;
    if (Add_Balances(Accout_number, data_TO_vector))
    {
        cout << "Verified......Scanned[?]" << endl;
        Pritn_data_For_vectorst(data_TO_vector);
    }
    else

        cout << "Verification failed![??] Account Number Is Not True [" << Accout_number << ']' << endl;
}

void Show_Withdraw(vector<St_Cilent>& data_TO_vector)
{
    string user_input = ReadClientAccountNumber();
    //  data_TO_vector = Read_file_And_Add_data_in_file_to_Vectoe(Bank);
    system("cls");
    cout << "=============================" << endl;
    cout << "\t    Withdraw   \t" << endl;
    cout << "=============================" << endl;
    if (Withdraw(user_input, data_TO_vector))
    {
        cout << "Verified......Scanned[?]" << endl;
        Pritn_data_For_vectorst(data_TO_vector);
    }
    else

        cout << "Verification failed![??] Account Number Is Not True [" << user_input << ']' << endl;
}

void Show_balance(vector<St_Cilent>& New_data)
{
    //  New_data = Read_file_And_Add_data_in_file_to_Vectoe(Bank);
    system("cls");
    print_data_B1(New_data);
}

void Exit_Program()
{
    system("cls");
    cout << "=============================" << endl;
    cout << "\t   Thank  :)   \t" << endl;
    cout << "=============================" << endl;
}


void Print_menu(vector<St_Cilent>& data, vector<St_User>& User);
void GO_back_end(vector<St_Cilent>& data, vector<St_User>& User)
{
    cout << "\n\nPress any key to go back to Main Menue..." << endl;
    system("pause>0");
    Print_menu(data, User);
}
void Print_Menu_Tranacthions(vector<St_Cilent>& data, vector<St_User>& user);
void main_menu_back(vector<St_Cilent>& data, vector<St_User>& user)
{
    cout << "\n\nPress any key to go back to Main Menue..." << endl;
    system("pause>0");
    Print_menu(data, user);

}
void Print_Mnage(vector<St_User>& Users, vector<St_Cilent>& c);
void Go_back_manage_Users_Screan(vector<St_User>& Users, vector<St_Cilent>& c)
{
    cout << "\n\nPress any key to go back to Main Menue..." << endl;
    system("pause>0");
    Print_Mnage(Users, c);

}


bool check_Access_permission(EN_Permissions perm)
{
    if (Global.Permisson == E_full) return true;

    if ((Global.Permisson & perm) == perm) return true;

    else
        return false;

}
void Print_Mnage(vector<St_User>& Users, vector<St_Cilent>& c);
void Calls_1(EN_Record calls_Records, vector<St_Cilent>& data, vector<St_User>& Users)
{
    switch (calls_Records)
    {
    case EN_Record::Show:
        system("cls");
        show_list_client_screan(data);
        GO_back_end(data, Users);
        break;

    case EN_Record::Add:
        system("cls");
        Show_Adding_New_Data(data);
        GO_back_end(data, Users);
        break;

    case EN_Record::Delete:
        Show_delete_Client(data);
        GO_back_end(data, Users);
        break;

    case EN_Record::Update:
        system("cls");
        Show_Update_Client(data);
        GO_back_end(data, Users);
        break;

    case EN_Record::Find:
        system("cls");
        Show_Client_find(data);
        GO_back_end(data, Users);
        break;

    case EN_Record::Tranacthions:
        system("cls");
        Print_Menu_Tranacthions(data, Users);
        break;

    case EN_Record::Manage_users:
        system("cls");
        Print_Mnage(Users, data);
        Print_Menu_Tranacthions(data, Users);
        break;


    case EN_Record::Exit:
        system("cls");
        Exit_Program();
        break;
    default:
        return;
    }

}


void Calls_2(EN_Record_Tranacthions Call2, vector<St_Cilent>& Data, vector<St_User>& user)
{

    switch (Call2)
    {
    case  EN_Record_Tranacthions::Deposit_1:
        system("cls");
        Show_Deposit(Data);
        main_menu_back(Data, user);
        break;
    case EN_Record_Tranacthions::Winthdraw_1:
        system("cls");
        Show_Withdraw(Data);
        main_menu_back(Data, user);
        break;
    case EN_Record_Tranacthions::toala_balances:
        system("cls");
        Show_balance(Data);
        main_menu_back(Data, user);
        break;
    case EN_Record_Tranacthions::Main_menu:
        Print_menu(Data, user);
    default:
        return;
    }
}

short read____()
{
    short data;
    cout << "Choose what Do you  Want To Do :[ 1 To 4 ] : ";
    cin >> data;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return data;
}

void Print_Menu_Tranacthions(vector<St_Cilent>& data, vector<St_User>& User)
{
    system("cls");
    cout << "===============================================" << endl;
    cout << "\t\t Tranacthions Menu Screen " << endl;
    cout << "===============================================" << endl;
    cout << "\t Deposit         [1] . " << endl;
    cout << "\t withdraw        [2] . " << endl;
    cout << "\t Total Balances  [3] . " << endl;
    cout << "\t Main Menue      [4] . " << endl;
    cout << "===============================================" << endl;
    Calls_2((EN_Record_Tranacthions)read____(), data, User);
}
short raed()
{
    short r;
    cout << "Enter a Number [  1 To 7 ] :";
    cin >> r;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return r;
}

void Print_menu(vector<St_Cilent>& data, vector<St_User>& User)
{
    system("cls");
    cout << "===============================================" << endl;
    cout << "\t\t Main Menu Screen " << endl;
    cout << "===============================================" << endl;
    cout << "\t Show Client List [1] : " << endl;
    cout << "\t Add  New Client  [2] : " << endl;
    cout << "\t Delete Client    [3] : " << endl;
    cout << "\t Update Client    [4] : " << endl;
    cout << "\t Find Client      [5] : " << endl;
    cout << "\t Tranacthions     [6] : " << endl;   /// Add Mange Users ///
    cout << "\t Manage Users     [7] : " << endl;
    cout << "\t Loguot           [8] : " << endl;
    cout << "===============================================" << endl;
    Calls_1((EN_Record)raed(), data, User);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void CAll3(vector<St_User>& Users, En_Record_manage Record, vector<St_Cilent>& c)
{
    switch (Record)
    {
    case En_Record_manage::Users_List:
        show_List_Screan_Users(Users);
        Go_back_manage_Users_Screan(Users, c);
        break;

    case En_Record_manage::NewUser:
        Show_Adding_New_User(Users);
        Go_back_manage_Users_Screan(Users, c);
        break;

    case En_Record_manage::E_Delete:
        Show_delete_User(Users);
        Go_back_manage_Users_Screan(Users, c);
        break;

    case En_Record_manage::E_Update:
        Show_Update_User(Users);
        Go_back_manage_Users_Screan(Users, c);
        break;

    case En_Record_manage::E_find:
        Show_User_find(Users);
        Go_back_manage_Users_Screan(Users, c);
        break;
    case En_Record_manage::main_Menu:
        main_menu_back(c, Users);
        break;
    default:
        return;
    }
}

short ReadManageUsersMenueOption()
{
    cout << "Choose what do you want to do? [1 to 6]? ";
    short Choice = 0;
    cin >> Choice;
    return Choice;
}

void Print_Mnage(vector<St_User>& Users, vector<St_Cilent>& c)

{
    if (!check_Access_permission(EN_Permissions::Manage_Users))
    {
        msg();
        GO_back_end(c, Users);
        return;
    }
    system("cls");
    cout << "===============================================" << endl;
    cout << "\t\t Manage Menu Screen " << endl;
    cout << "===============================================" << endl;
    cout << "\t Show Users List[1] : " << endl;
    cout << "\t Add  New User  [2] : " << endl;
    cout << "\t Delete User    [3] : " << endl;
    cout << "\t Update User    [4] : " << endl;
    cout << "\t Find User      [5] : " << endl;
    cout << "\t Main Menu      [6] : " << endl;
    cout << "===============================================" << endl;

    CAll3(Users, (En_Record_manage)ReadManageUsersMenueOption(), c);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool Load_User_info(string Username, string pasword, vector<St_User >& U)
{

    if (Find_User_name_A_Password(Username, pasword, U, Global))
        return true;
    else
        return false;


}

void Login(vector<St_User >& U, vector<St_Cilent>& d)
{
    bool IS_loading = false;
    string Username, Passsword;
    do
    {
        system("cls");
        cout << "\n---------------------------------\n";
        cout << "\tLogin Screen";
        cout << "\n---------------------------------\n";
        if (IS_loading)
        {
            cout << "Invlaid Username / Password!\n";
        }
        cout << "Enter Username : ";
        cin >> Username;

        cout << "Enter PAssword : ";
        cin >> Passsword;

        IS_loading = !Load_User_info(Username, Passsword, U);


    } while (IS_loading);

    Print_menu(d, U);
}

int main()
{
    vector<St_Cilent>Call1 = Read_file_And_Add_data_in_file_to_Vectoe(Bank);
    vector<St_User>Call2 = Read_File_And_Add_Users_To_Vector(Users_d);
    Login(Call2, Call1);
}