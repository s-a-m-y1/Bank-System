#include<iostream>
#include<string>
#include<limits>
#include<iomanip>
#include<vector>
#include<fstream>
using namespace std;

const string ClientS = "Client.txt";
const string Users = "Users.txt";

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

enum EN_Record { E_Show_cl = 1, E_Add_cl = 2, E_Delete_cl = 3, E_Update_Cl = 4, E_Find_cl = 5, Tranacthions = 6, Manage_users = 7, Exit = 8 };

enum En_Record_manage { Users_List = 1, NewUser = 2, E_Delete = 3, E_Update = 4, E_find = 5, main_Menu = 6 };

enum EN_Record_Tranacthions { Deposit_1 = 1, Winthdraw_1 = 2, toala_balances = 3, Main_menu = 4 };

enum EN_Permissions { E_full = -1, PE_list_Client = 1, P_E_Add_New_Client = 2, E_P_DElete_Client = 4, P_E_Update_Clent = 8, P_E_Find_clent = 16, P_E_Tranactions = 32, Manage_Users = 64 };

St_User Current_Users;//this_Is_Global_Varibal
void ShowMainMenue();
void ShowManageUsersMenue();
void ShowTransactionsMenue();
void Login();
///___________________________________________________________________________________________________________________________________________________________________///

vector<string>Split_string ( string Word,  string Dlimter)
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

    S_v = Split_string(Line, Delimter);
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

St_User Add_Users_To_Struct(string Line, string Delimter = "//#//")
{
    St_User u;
    vector<string>Users;
    Users = Split_string (Line, Delimter);

    if (Users.size() >= 3)
    {
        u.User_name = Users[0];

        u.Password = Users[1];

        u.Permisson = stoi(Users[2]);
    }
    return u;
}


string Add_date_To_one_line_and_Delmter( St_Cilent Data , string Delimter = "/")
{

    return   Data.Account_number + Delimter + Data.pin_code + Delimter + Data.Full_name + Delimter + Data.phone + Delimter + to_string(Data.Account_balance);
}


string Add_Users_To_one_line_and_Delmter(St_User User , string Delimter = "//#//")
{


    return  User.User_name + Delimter + User.Password + Delimter + to_string(User.Permisson);
}


bool User_Exsists_By_Username(string Username , string User_file)
{
    fstream read ;
    vector<St_User>user1;
      read.open(User_file , ios::in );
      if (read.is_open())
      {
        string Line ;
        St_User user;
       while (getline(read , Line))
       {
        user = Add_Users_To_Struct(Line);
        if (Username==user.User_name)
        {
            read.close();
            return true;
        }
        
       user1.push_back(user);
       }
       read.close();
      }
      
      return false;
}

bool Client_Exsists_By_Account_number(string Accountnumber , string User_file)
{
    fstream read ;
    vector<St_Cilent>user1;
      read.open(User_file , ios::in );
      if (read.is_open())
      {
        string Line ;
        St_Cilent user;
       while (getline(read , Line))
       {
        user = Add_data_To_struct(Line);
        if (Accountnumber==user.Account_number)
        {
            read.close();
            return true;
        }
        
       user1.push_back(user);
       }
       read.close();
      }
      
      return false;
}

St_Cilent Read_Data( )
{
    St_Cilent data;
      cout << " Enter A Account Number : ";
        getline(cin >> ws, data.Account_number);

        while (Client_Exsists_By_Account_number(data.Account_number , ClientS))
        {
            cout << "Sory ): Invaled Account Number [" << data.Account_number << "] :: Enter Account Number : ";
            getline(cin >> ws, data.Account_number);
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
bool ChecK_Access(EN_Permissions Per)
{
    if (Current_Users.Permisson==EN_Permissions::E_full)
    {
     return true;
    }
    if ((Per & Current_Users.Permisson )==Per)
    return true;
    else
    return false;  

}

St_User Read_New_User()
{
    St_User USer;

    
        cout << " Enter A Username : ";
        getline(cin >> ws, USer.User_name);

        while (User_Exsists_By_Username(USer.User_name,Users ))
        {
            cout << "Sory ): Invaled Username  [" << USer.User_name << "] :: Enter Username: ";
            getline(cin >> ws, USer.User_name);
        }
    

    cout << "Enter Password : ";
    getline(cin >> ws, USer.Password);
    ///Raed_Perm 
    USer.Permisson = Read_Permissions();

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return USer;
}


vector<St_Cilent>Load_Data_From_File(string namef )
{
    vector<St_Cilent>Client;
    fstream Read;
    Read.open(namef , ios::in);
    if (Read.is_open())
    {
        string line;
        St_Cilent Cl;
        while (getline(Read , line))
        {
           Cl = Add_data_To_struct(line);
           Client.push_back(Cl);
        }
        
        Read.close();
    }
return Client;
}

vector<St_User>Load_Users_From_File(string namef )
{
    vector<St_User>Client;
    fstream Read;
    Read.open(namef , ios::in);
    if (Read.is_open())
    {
        string line;
        St_User Cl;
        while (getline(Read , line))
        {
           Cl = Add_Users_To_Struct(line);
           Client.push_back(Cl);
        }
        
        Read.close();
    }
return Client;
}

void Print_client_record(St_Cilent client)
{
    cout << "| " << setw(15) << left << client.Account_number;
    cout << "| " << setw(10) << left << client.pin_code;
    cout << "| " << setw(40) << left << client.Full_name;
    cout << "| " << setw(12) << left << client.phone;
    cout << "| " << setw(12) << left << client.Account_balance;
}

void Print_User_record(St_User User)
{
    cout << "| " << setw(15) << left << User.User_name;
    cout << "| " << setw(10) << left << User.Password;
    cout << "| " << setw(40) << left << User.Permisson;
}

void Print_client_Balances(St_Cilent client)
{
    cout << "| " << setw(15) << left << client.Account_number;
    cout << "| " << setw(40) << left << client.Full_name;
    cout << "| " << setw(12) << left << client.Account_balance;
}

void ShowAccessDeniedMessage()
{
cout << "\n------------------------------------\n";
cout << "Access Denied, \nYou dont Have Permission To Do this,\nPlease Conact Your Admin.";
cout << "\n------------------------------------\n";
}

void Show_Client_screan()
{
    if (!ChecK_Access(EN_Permissions::PE_list_Client))
    {
        ShowAccessDeniedMessage();
        return;
    }
    
vector<St_Cilent> client1 = Load_Data_From_File(ClientS);

    cout << "\n\t\t\t\t\t client List(" << client1.size() << ")Client(s)" << endl;

    cout << "\n=================================================================================================*\n" << endl;
    cout << "| " << left << setw(15) << " Accout Number ";
    cout << "| " << left << setw(10) << " Pin Code ";
    cout << "| " << left << setw(40) << " Client Name ";
    cout << "| " << left << setw(12) << " Phone ";
    cout << "| " << left << setw(12) << " Balance ";
    cout << "\n=================================================================================================*\n" << endl;
    for (St_Cilent One_client : client1)
    {
        Print_client_record(One_client);
        cout << endl;
    }
    cout << "\n=================================================================================================*\n" << endl;

}

void Show_User_screan()
{
vector<St_User> User1 = Load_Users_From_File(Users);

    cout << "\n\t\t\t\t\t Users List(" << User1.size() << ")Users(s)" << endl;

    cout << "\n=================================================================================================*\n" << endl;
    cout << "| " << left << setw(15) << " Username  ";
    cout << "| " << left << setw(10) << " Password  ";
    cout << "| " << left << setw(40) << " Permissions ";

    cout << "\n=================================================================================================*\n" << endl;
    for (St_User& One_User : User1)
    {
        Print_User_record(One_User);
        cout << endl;
    }
    cout << "\n=================================================================================================*\n" << endl;

}

void Show_Balanses_Screan()
{
    double total_balance = 0;

     vector<St_Cilent> client1= Load_Data_From_File(ClientS);
    cout << "\n\t\t\t\t\t client List(" << client1.size() << ")Client(s)" << endl;

    cout << "\n=================================================================================================*\n" << endl;
    cout << "| " << left << setw(15) << " Accout Number ";
    cout << "| " << left << setw(40) << " Client Name ";
    cout << "| " << left << setw(12) << " Balance ";
    cout << "\n=================================================================================================*\n" << endl;
    for (St_Cilent One_client : client1)
    {
        Print_client_Balances(One_client);
        cout << endl;
        total_balance += One_client.Account_balance;
    }
    cout << "\n\t\t\t\t\t TOtal Balances : " << total_balance << endl;
    cout << "\n=================================================================================================*\n" << endl;

}

void Show_User_Card(St_User data)
{

   cout << "======================" << endl;
   cout << " User name : " << data.User_name << endl;

   cout << " Password      : " << data.Password << endl;

   cout << " Permisson   : " << data.Permisson << endl;

   cout << "======================" << endl;
}
void Show_client_Card(St_Cilent data)
{

   cout << "======================" << endl;
   cout << " Account Number: " << data.Account_number << endl;

   cout << " Pin code      : " << data.pin_code << endl;

   cout << " Full Name     : " << data.Full_name << endl;

   cout << " Phone         : " << data.phone << endl;

   cout << "Account Balance: " << data.Account_balance << endl;
   cout << "======================" << endl;
}

bool find_client_By_Account_number(string Accountnumber ,vector<St_Cilent> clinet , St_Cilent&client_1)
{
    for(St_Cilent&l:clinet)
    {
        if (Accountnumber==l.Account_number)
        {
         client_1 = l;
         return true;
        }
        
    }
return false;
}

bool find_User_By_Usernaem(string Username ,vector<St_User> Users , St_User&user_1)
{
    for(St_User&l:Users)
    {
        if (Username==l.User_name)
        {
         user_1 = l;
         return true;
        }
        
    }
return false;
}

bool find_bY_Username_And_Password(string Username ,string password, St_User&local_var)
{
    vector<St_User> Users1 = Load_Users_From_File(Users);
    for(St_User& L : Users1)
    {
        if (Username == L.User_name && password == L.Password)
        {
          local_var = L;
          return true;
        }
    }
return false;
}


St_Cilent Raed_change_clirnt_record(string Account_number)
{
    St_Cilent Client;
    Client.Account_number = Account_number;

    cout<<"Enter A Pin Code  ";
    getline(cin>>ws,Client.pin_code);
    
    cout<<"Enter Phone : ";
    getline(cin , Client.phone);

    cout<<"Enter Account BAlance ? : " ;
    cin>>Client.Account_balance;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return Client;

}

St_User chanage_User_Record(string Username )
{
    St_User user1 ;

    user1.User_name = Username;

    cout<<"Enter Password : ";
    getline(cin>>ws,user1.Password);

   user1.Permisson  =Read_Permissions();

   return user1;
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

vector<St_Cilent>Saver_New_Data(vector<St_Cilent>client , string File_Loc)
{

    fstream Delete ;
    Delete.open(File_Loc  , ios::out);
    if (Delete.is_open())
    {
        string oneLine="";
      for(St_Cilent&Cliets:client)
        {
        if (Cliets.Mark==false)
        {
            //  Delete<< Add_date_To_one_line_and_Delmter(Cliets)<<endl;
            oneLine= Add_date_To_one_line_and_Delmter(Cliets);
             Delete<<oneLine<<endl;
        }
        
        }
        Delete.close();
    }
    
return client;
}


vector<St_User>Saver_New_User(vector<St_User>User , string File_Loc)
{

    fstream Delete ;
    Delete.open(File_Loc  , ios::out);
    if (Delete.is_open())
    {
        string oneLine="";
      for(St_User&USers:User)
        {
        if (USers.Marking==false)
        {
            //  Delete<< Add_date_To_one_line_and_Delmter(Cliets)<<endl;
            oneLine= Add_Users_To_one_line_and_Delmter(USers);
             Delete<<oneLine<<endl;
        }
        
        }
        Delete.close();
    }
    
return User;
}


void Add_Data_TO_Line(string Loc_File , string LIne_Push )
{
    fstream Add;
    Add.open(Loc_File,ios::app|ios::out);
    if (Add.is_open())
    {
      
        
            Add<<LIne_Push<<endl;
        Add.close();
        
    }

}

void Add_New_client(  )
{

St_Cilent Client = Read_Data();
Add_Data_TO_Line(ClientS , Add_date_To_one_line_and_Delmter(Client));

}


void Add_User_To_File( )
{

St_User User = Read_New_User();
Add_Data_TO_Line(Users , Add_Users_To_one_line_and_Delmter(User));

}


void Add_New_Client_1()
{
    char User = 'Y';
    do
    {
        cout<<"Adding New Client  : ";

      Add_New_client(  );

        cout<<"\nClient Added Successfully  | do You Want Add Client : [ Y / N ] : ";

        cin>>User;

       
    } while (User=='y'||User=='Y');
    
}


void Add_New_User_1()
{
    char choice = 'Y';
    do
    {
        cout<<"Adding New User  : ";

      Add_User_To_File(  );

        cout<<"\nUser Added Successfully  | do You Want Add User : [ Y / N ] : ";

        cin>>choice;

       
    } while (choice=='y'||choice=='Y');
    
}

bool Delete_client_By_Accoutn_number(string Accountnumber , vector<St_Cilent>&LCient)
{
    char User='n';

    St_Cilent cl;//this is target 
    if (find_client_By_Account_number(Accountnumber , LCient , cl))
    {
        Show_client_Card(cl);

        cout<<"Are You sure You Want Delete This Client [ Y / N ] : ";
        cin>>User;
        if (toupper(User)=='Y')
        {
           Check_account_number_and_marking(LCient, Accountnumber );
           Saver_New_Data(LCient , ClientS);
           LCient = Load_Data_From_File(ClientS);
           cout<<"Delete Client Successfully : ";
            return true;
        }
        
    }
    else
    {cout<<"Clienyt Whith Account Number ["<<Accountnumber<<"]Is Not found:"<<endl;}

    return false;
}


bool Delete_User_By_Username(string Username , vector<St_User>&User)
{
    char User_w='n';

    St_User cl;//this is target 
    if (find_User_By_Usernaem(Username , User , cl))
    {
        Show_User_Card(cl);

        cout<<"Are You sure You Want Delete This User [ Y / N ] : ";
        if (User_w=='Y'||User_w=='y')
        {
           Check_Username_and_marking(User, Username );
           Saver_New_User(User , Users);
           User = Load_Users_From_File(Users);
           cout<<"Delete User Successfully : ";
            return true;
        }
        
    }
    else
    {cout<<"Clienyt Whith username ["<<Username<<"]Is Not found:"<<endl;}

    return false;
}

bool Update_client(string Accountnumber , vector<St_Cilent>&Client )
{
    char User_W ='N';
    St_Cilent cl ;
    if (find_client_By_Account_number(Accountnumber,Client , cl))
    {
        Show_client_Card(cl);
        cout<<"Are You Sure Want Update This Client [Y / N ] :";
        cin>>User_W;
        if (User_W=='Y'||User_W=='y')
        {
            for(St_Cilent&c:Client)
            {
            c = Raed_change_clirnt_record(Accountnumber);////////////////////////////////////////////////
            break;
            }

        }
        Saver_New_Data(Client , ClientS);
          cout<<"Update client Successfully : ";
        return true;
    }
    else
    {cout<<"Clienyt Whith Account Number ["<<Accountnumber<<"]Is Not found:"<<endl;}
return false;
}

bool Update_User(string Username , vector<St_User>&user )
{
    char User_W ='N';
    St_User cl ;
    if (find_User_By_Usernaem(Username,user , cl))
    {
        Show_User_Card(cl);
        cout<<"Are You Sure Want Update This user [Y / N ] :";
        cin>>User_W;
        if (User_W=='Y'||User_W=='y')
        {
            for(St_User&u:user)
            {
            cl = chanage_User_Record (Username);
            break;
            }

        }
        Saver_New_User( user ,Users);
          cout<<"Update client Successfully : ";
        return true;
    }
    else
    {cout<<"User Whith Username  ["<<Username<<"]Is Not found:"<<endl;}
return false;
}



bool Add_Balances(string Account_number, vector<St_Cilent>& Data)
{
    St_Cilent data1;
    double Add_Balances = 0;
    char User = 'N';
    if (find_client_By_Account_number(Account_number, Data, data1))
    {
        Show_client_Card(data1);
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
            Saver_New_Data(Data , ClientS );
            return true;
        }
    }
    else
    {
        while (!find_client_By_Account_number(Account_number, Data, data1))
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
    if (find_client_By_Account_number(Account_number, Data, data1))
    {
        Show_client_Card(data1);
        do
        {
            cout << "Please Enter Withdraw Amount : ";
            cin >> Withdraw;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (Withdraw > data1.Account_balance)
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
            Saver_New_Data( Data , ClientS);
            return true;
        }
    }
    else
    {
        while (!find_client_By_Account_number(Account_number, Data, data1))
        {
            cout << "\n Client with Account Number " << Account_number << "Is Not Found ! ";
            cout << "Enter A Account Number ";
            cin >> Account_number;

        }
    }
    return false;
}


string Read_account_number()
{
    string User ;

     cout<<"Enter A Account number : ";

     cin>>User;

     return User;
}

string Read_Username()
{
string User ;

cout<<"Enter A Username : ";

cin>>User;

return User ;

}

void Show_User_screan_Menu()
{
 Show_User_screan();

}

void Show_Client_screan_menu()
{
 Show_Client_screan();

}

void Show_Add_New_User()
{
    cout<<"===================================="<<endl;
    cout<<"\t Add User"<<endl;
    cout<<"===================================="<<endl;
    Add_New_User_1();
}

void Show_delete_Screan()
{
cout<<"===================================="<<endl;
cout << "\tDelete Users Screen\n";
cout<<"===================================="<<endl;
vector<St_User>User = Load_Users_From_File(Users);
string Username = Read_Username();
Delete_User_By_Username(Username ,User );
}



void Show_Update_Screan()
{
cout<<"===================================="<<endl;
cout << "\tUpdate Users Screen\n";
cout<<"===================================="<<endl;
vector<St_User>User = Load_Users_From_File(Users);
string Username = Read_Username();
Update_User(Username ,User );
}

void show_Find_screan()
{
 cout<<"===================================="<<endl;
cout << "\nFind Users Screen\n";
cout<<"===================================="<<endl;
vector<St_User>Users1 = Load_Users_From_File(Users)  ;
St_User u;
string Username= Read_Username();
if (find_User_By_Usernaem(Username ,Users1 ,u ))
{
    Show_User_screan();
}
else
 cout << "\n Client with  username " << Username << "Is Not Found ! ";

}


void    Show_delete_Client()
{
 if (!ChecK_Access(EN_Permissions::E_P_DElete_Client))
    {
        ShowAccessDeniedMessage();
        return;
    }
cout<<"===================================="<<endl;
cout << "\tDelete client Screen\n";
cout<<"===================================="<<endl;
vector<St_Cilent>client = Load_Data_From_File(ClientS);
string Accountnumber = Read_account_number();
Delete_client_By_Accoutn_number(Accountnumber ,client );
}

void Show_Update_client_Screan()
{
    if (!ChecK_Access(EN_Permissions::P_E_Update_Clent))
    {
        ShowAccessDeniedMessage();
        return;
    }
cout<<"===================================="<<endl;
cout << "\tUpdate Client Screen\n";
cout<<"===================================="<<endl;
vector<St_Cilent>Client = Load_Data_From_File(ClientS);
string Accountnumber = Read_account_number();
Update_client(Accountnumber ,Client );
}

void Show_Add_New_Client()
{
    if (!ChecK_Access(EN_Permissions::P_E_Add_New_Client))
    {
         ShowAccessDeniedMessage();
        return;
    }
    
    cout<<"===================================="<<endl;
    cout<<"\t Add Client Screen "<<endl;
    cout<<"===================================="<<endl;
     Add_New_Client_1();

}

void show_Find_screan_client()
{
    if (!ChecK_Access(EN_Permissions::P_E_Find_clent))
    {
        ShowAccessDeniedMessage();
        return;
    }
    
 cout<<"===================================="<<endl;
cout << "\nFind Users Screen\n";
cout<<"===================================="<<endl;

vector<St_Cilent>client = Load_Data_From_File(ClientS)  ;
St_Cilent u;
string Accountnumber= Read_account_number();

if (find_client_By_Account_number(Accountnumber ,client ,u ))
{
    Show_Client_screan();
}
else
 cout << "\n Client with  Accountnumber " << Accountnumber << "Is Not Found ! ";

}

void ShowEndScreen()
{
 cout<<"===================================="<<endl;
cout << "\tProgram Ends :-)\n";
 cout<<"===================================="<<endl;

}


void show_Deposet_Screan()
{
 cout<<"===================================="<<endl;
cout << "\t Deposit Screann\n";
 cout<<"===================================="<<endl;
vector<St_Cilent>client = Load_Data_From_File(ClientS);
string Accountnumber = Read_account_number();

    if  (Add_Balances(Accountnumber , client))
     {
       cout << "Verified......Scanned[?]" << endl;
     Show_Client_screan();
     }
     
 else

     cout << "Verification failed![??] Account Number Is Not True [" << Accountnumber << ']' << endl;
}


void Show_Withdraw( )
{
    string Accountnumber = Read_account_number();
     vector<St_Cilent>client = Load_Data_From_File(ClientS);
    system("cls");
    cout << "=============================" << endl;
    cout << "\t    Withdraw   \t" << endl;
    cout << "=============================" << endl;
    if (Withdraw(Accountnumber, client))
    {
        cout << "Verified......Scanned[?]" << endl;
       Show_Client_screan();
    }
    else

        cout << "Verification failed![??] Account Number Is Not True [" << Accountnumber << ']' << endl;
}


void show_Total_balances_screan()
{
Show_Balanses_Screan();
}

void Go_To_back_Main_Menu()
{
    cout<<"\n\n Press Any to go back to Main Menu .....  ";
    system("pause>0");
    ShowMainMenue();
}

void Go_To_back_ManageUsers_Menu()
{
    cout<<"\n\n Press Any to go back to Manage Users Menu .....  ";
    system("pause>0");
    ShowManageUsersMenue();
}

void Go_To_Transactions_Menu()
{
    cout<<"\n\n Press Any to go back to Transactions Menu .....  ";
    system("pause>0");
    ShowTransactionsMenue();
}

short Read_Transactions_Menu()
{
    short user = 0 ;
    cout<<"Choose What Do you Want To so ? [ 1 To 4 ] ? ";
    cin>>user;
return user;
}

void Order_Transactions_Menu(EN_Record_Tranacthions Call2)
{

    switch (Call2)
    {
    case  EN_Record_Tranacthions::Deposit_1:
        system("cls");
        show_Deposet_Screan();
        Go_To_back_Main_Menu();
        break;
    case EN_Record_Tranacthions::Winthdraw_1:
        system("cls");
        Show_Withdraw();
        Go_To_back_Main_Menu();
        break;
    case EN_Record_Tranacthions::toala_balances:
        system("cls");
        show_Total_balances_screan();
      Go_To_back_Main_Menu();
        break;
    case EN_Record_Tranacthions::Main_menu:
      ShowMainMenue();
    default:
        return;
    }
}

void ShowTransactionsMenue()
{
    if (!ChecK_Access(EN_Permissions::P_E_Tranactions))
    {
      ShowAccessDeniedMessage();
      return;
    }
    
    system("cls");
    cout << "===============================================" << endl;
    cout << "\t\t Tranacthions Menu Screen " << endl;
    cout << "===============================================" << endl;
    cout << "\t Deposit         [1] . " << endl;
    cout << "\t withdraw        [2] . " << endl;
    cout << "\t Total Balances  [3] . " << endl;
    cout << "\t Main Menue      [4] . " << endl;
    cout << "===============================================" << endl;
    Order_Transactions_Menu((EN_Record_Tranacthions)Read_Transactions_Menu());
}

short raed_Main_menu()
{
    short r = 0 ;
    cout<<"Choose What Do you Want To so ? [ 1 To 8 ] ? ";
    cin >> r;
    return r;
}


void  Order_Manage_Users(En_Record_manage Users)
{
    switch (Users)
    {
    case En_Record_manage::Users_List  :
     system("cls");
    Show_User_screan_Menu();
     Go_To_back_ManageUsers_Menu();
        break;
    case En_Record_manage::NewUser  :
     system("cls");
    Show_Add_New_User();
     Go_To_back_ManageUsers_Menu();
        break;

     case En_Record_manage::E_Delete  :
     system("cls");
    Show_delete_Screan();
     Go_To_back_ManageUsers_Menu();
        break;
        
     case En_Record_manage::E_Update  :
     system("cls");
    Show_Update_client_Screan();
     Go_To_back_ManageUsers_Menu();
        break;   
    
     case En_Record_manage::E_find  :
     system("cls");
    show_Find_screan();
     Go_To_back_ManageUsers_Menu();
        break;

    case En_Record_manage::main_Menu  :
     system("cls");
    
     ShowMainMenue();
        break;

    default:
        break;
    }

}

short raed_ManageUsersMenuescreans()
{
    short r = 0 ;
    cout<<"Choose What Do you Want To so ? [ 1 To 6 ] ? ";
    cin >> r;
    return r;
}

void ShowManageUsersMenue()

{
    if (!ChecK_Access(EN_Permissions::Manage_Users))
    {
        ShowAccessDeniedMessage();
        return;
    }
    system("cls");
    cout << "===============================================" << endl;
    cout << "\t\t Manage Menu Screen " << endl;
    cout << "===============================================" << endl;
    cout << "\tShow Users List [1] : " << endl;
    cout << "\t Add  New User  [2] : " << endl;
    cout << "\t Delete User    [3] : " << endl;
    cout << "\t Update User    [4] : " << endl;
    cout << "\t Find User      [5] : " << endl;
    cout << "\t Main Menu      [6] : " << endl;
    cout << "===============================================" << endl;
  Order_Manage_Users((En_Record_manage) raed_ManageUsersMenuescreans());   
}

void Order_Main_Menu(EN_Record Clients)
{
    
  switch (Clients)
  {
  case EN_Record::E_Show_cl :
    system("cls");
   Show_Client_screan_menu();
   Go_To_back_Main_Menu();
    break;
   case EN_Record::E_Add_cl :
    system("cls");
   Show_Add_New_Client();
   Go_To_back_Main_Menu();
    break;
  
   case EN_Record::E_Delete_cl :
    system("cls");
   Show_delete_Client();
   Go_To_back_Main_Menu();
    break;
  
   case EN_Record::E_Update_Cl :
    system("cls");
   Show_Update_Screan();
   Go_To_back_Main_Menu();
    break;
  
   case EN_Record::E_Find_cl :
    system("cls");
   show_Find_screan_client();
   Go_To_back_Main_Menu();
    break;
  
   case EN_Record::Tranacthions :
    system("cls");
   ShowTransactionsMenue();
      Go_To_back_Main_Menu();
    break;
  
    case EN_Record::Manage_users :
    system("cls");
    ShowManageUsersMenue();
    Go_To_back_Main_Menu();
    break;
  
   case EN_Record::Exit :
    system("cls");
   Login();
    break;

  default:
    break;
  }
   
}

short read_screan()
{
    short r = 0 ;
    cout<<"Choose What Do you Want To so ? [ 1 To 8 ] ? ";
    cin >> r;
    return r;
}


void ShowMainMenue()
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
    Order_Main_Menu((EN_Record) read_screan());
   
}



bool Load_User_info(string Username , string password )
{
    if (find_bY_Username_And_Password(Username , password ,Current_Users ))
    {
     return true;
    }
    else
    return false;
}

void Login()
{
    string Username = "" ,Password  = "";
    bool Login_check=false;
    do
    {
        system("cls");
cout<<"===================================="<<endl;
cout << " Login Screan  \t";cout<<"Hello (:"<<endl;
cout<<"===================================="<<endl;
  
if (Login_check)
{
   cout<<"Invlaid Username/Password!\n"<<endl;
}
 cout<<"Enter Username  : ";
 cin>>Username ;

 cout<<"Enter Password : ";
 cin>>Password;
 Login_check = ! Load_User_info(Username , Password);
    } while (Login_check);
    
    ShowMainMenue();
}

int main()
{
   Login() ; 
   system("pause>0");
   return 0; 
}

