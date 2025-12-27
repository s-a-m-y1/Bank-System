#include<iostream>
#include<string>
#include<vector>
#include<fstream>
using namespace std;
const string ClientS = "Client.txt";
//_________//
//calls _This is
enum En_record{Quick_Withdrow =1 , Normal_Withdrow =2 ,Deposit =3 , Check_BAlance = 4 , Logout =5 };
void Print_Atm_system_Screan( );
void Show_Perforem_Quick_Withdrow();
void Show_Perform_depodit();
void Show_Perforem_Nurmal_WhithDrow();
void Login();
void Print_Quick_( );
//_________//

struct St_Cilent
{
    string Account_number;
    string pin_code;
    string Full_name;
    string phone;
    double Account_balance;
    bool Mark = false;
};
St_Cilent Iam_Global;
vector<string> Split_string(string word , string Spretor)
{
    string Line = "";
    vector<string> V_client ;
    short Index_Pos = 0;
    while ((Index_Pos = word.find(Spretor)) != std::string::npos )
    {
    Line = word.substr(0,Index_Pos);
    if (!Line.empty())
    {
    V_client.push_back(Line);
    }
     word.erase(0,Index_Pos+Spretor.length());
    }
    if (!word.empty())
    {
    V_client.push_back(word);
    }
    
   return V_client;
}

St_Cilent client_to_struct(string Word , string spretor ="/")
{
St_Cilent Adding;
vector<string>V_Struct = Split_string(Word , spretor);
//_________________________________________________//

Adding.Account_number = V_Struct[0];
Adding.pin_code = V_Struct[1];
Adding.Full_name = V_Struct[2];
Adding.phone = V_Struct [3];
Adding.Account_balance  = stold(V_Struct[4]);
return Adding;
}


string Add_Data_To_String(St_Cilent Client , string spretor = "/")
{
string Line = 
Client.Account_number + spretor +
Client.pin_code + spretor +
Client.Full_name + spretor +
Client.phone + spretor +
to_string(Client.Account_balance); 
  return Line;
}

vector<St_Cilent>Read_data_From_file_To_Vector(const string & Locthoin_file)
{
vector<St_Cilent>Load_;
fstream Read ;
Read.open(Locthoin_file, ios::in);//read_mood
if (Read.is_open())
   {
    St_Cilent Clients;
    string line;
    while (getline(Read , line))
    {
    Clients = client_to_struct(line);
    
    Load_.push_back(Clients);
    }
    Read.close();
   }
    return Load_;
}


bool Find_clien_By_Accountnumber_And_pincode(string Accounumber , string Pincode , St_Cilent& Client )
{
   vector<St_Cilent>clients =  Read_data_From_file_To_Vector(ClientS);
for(St_Cilent Cli : clients)

  {
    if (Accounumber==Cli.Account_number&&Pincode==Cli.pin_code)

    {
    Client = Cli;
    return true;
    }


 }

return false;

}

vector<St_Cilent>Save_Date_From_file(string loc , vector<St_Cilent> Client)
{
    fstream saveing ;
    saveing.open(loc , ios::out);//write//
    if (saveing.is_open())
    {
         string Line = "";

        for(St_Cilent cl_loop:Client)

    {
        if (cl_loop.Mark==false)
        {
         Line = Add_Data_To_String(cl_loop);
         saveing << Line <<endl;

        }
      
    }
   saveing.close();

    }
    
   return Client;
}

bool Deposit_Balace_In_Account_number(string Account_number , double Amount , vector<St_Cilent>&Client_P)//ايداع
{
    char What_User ='N';
    cout<<"\n Are You Sure Add Deposit Balance [Y/N] ?";
    cin>>ws>>What_User;
    if (What_User=='Y'||What_User=='y')
    {
      for(St_Cilent&Clent_loop:Client_P)
      {

        if (Account_number==Clent_loop.Account_number)
        {
             Clent_loop.Account_balance += Amount;
            Save_Date_From_file(ClientS , Client_P);
            return true;
        }
        
      }

    }
    return false;

}

short Read_Quick_Withdrow()
{
    short Read = 0;
    while (Read<1||Read>9)
    {
        cout<<"Choese Enter from [1] TO [9] ? ";
        cin>>Read;   
    }
    return Read;
}

short Quick_Withdwor_chose(short Read_Quick_Withdrow)
{
switch (Read_Quick_Withdrow)
{
case  1:
return 20;
break;
case  2:
return 50;
break;
case  3:
return 100;
break;
case  4:
return 200;
break;
case  5:
return 400;
break;
case  6:
return 600;
break;
case  7:
return 800;
break;
case  8:
return 1000;
break;
default:
return 0;
}
return Read_Quick_Withdrow;
}

void Perforem_Quick_Withdrow(short Chose  )
{
if (Chose==9)return;//note!
short User_reference = Quick_Withdwor_chose(Chose);
if (User_reference>Iam_Global.Account_balance)
{
   cout << "\nThe amount exceeds your balance, make another choice.\n";
        cout << "Press Anykey to continue...";
        system("pause>0");
        Print_Atm_system_Screan( );
        return ;
}
//_Load_Data//
 vector<St_Cilent>Client_P= Save_Date_From_file(ClientS ,Client_P );
Deposit_Balace_In_Account_number(Iam_Global.Account_number , User_reference *-1 , Client_P  );
Iam_Global.Account_balance -= User_reference;
}

double Read_debosit ()
{
    double Read = 0 ;
    cout<<"Enter A postiver Nmuber : ";
    cin>>Read;
    while (Read<=0)
    {
    cout<<"Enter A postiver Nmuber : ";
    cin>>Read;
    }
    return Read;
}

void Performe_depodit()
{
    double Read_Amount =  Read_debosit ();
    vector<St_Cilent>Load= Read_data_From_file_To_Vector(ClientS);
    Deposit_Balace_In_Account_number(Iam_Global.Account_number , Read_Amount , Load);
    Iam_Global.Account_balance += Read_Amount;
}

void Show_Perforem_Quick_Withdrow()
{
    cout<<"==============================\n";
    cout<<"\tQuick Withdrow Screan \n";
    cout<<"==============================\n";
Perforem_Quick_Withdrow(Read_Quick_Withdrow());
}

void Show_Perform_depodit()
{

    cout<<"==============================\n";
    cout<<"\tDeposit Screan \n";
    cout<<"==============================\n";
Performe_depodit();
}

int  Read_Nourmal_With_drow()
{
    int Read =0 ; 
    cout<<"Enter An  Amount of multiple 5's ? ";
    cin>>Read;
    while (Read%5!=0)
    { 
        system("cls");
     cout<<"Enter An  Amount of multiple 5's ? ";
    cin>>Read;
 
    }
    return Read;
}

void Perforem_Nurmal_WhithDrow()
{
    int Read = Read_Nourmal_With_drow();
    if (Read>Iam_Global.Account_balance)
    {
      cout<<"\n The Amount Excods Your Balance , Make Anthor choice ?\n";
      cout<<"Press AnyKey To Counthune ....\n ";
      system("pause>0");
     Print_Atm_system_Screan( );
      return ;
    }
    vector<St_Cilent>clent = Read_data_From_file_To_Vector(ClientS );
    Deposit_Balace_In_Account_number(Iam_Global.Account_number , Read *- 1 , clent);
    Iam_Global.Account_balance-=Read;
}

void Print_Quick_( )
 { system("cls");
    cout << "===============================================" << endl;
    cout << "\t\t Quick Withdrow " << endl;
    cout << "===============================================" << endl;
    cout << "\t[1] 20  \t [2] 50 " <<endl;
    cout << "\t[3] 100 \t [4] 200 " << endl;
    cout << "\t[5] 400 \t [6] 600 " << endl; 
    cout << "\t[7] 800 \t [8] 1000 " << endl;
    cout << "\t[9] Exit\t " << endl;
    cout<<"The Balance IS ("<<Iam_Global.Account_balance<<") "<<endl;
    cout << "===============================================" << endl;
     Perforem_Quick_Withdrow(Read_Quick_Withdrow());
 }
void GO_Back_Main_Menu()
{

cout<<"\n\n Press Any to go back to Main Menu .....  ";
    system("pause>0");
    Print_Atm_system_Screan( );
}

void Show_Perforem_Nurmal_WhithDrow()
{
  cout<<"==============================\n";
 cout<<"\t Nurmal WhithDrow Screan \n";
 cout<<"==============================\n";
Perforem_Nurmal_WhithDrow();
}

void Show_balances()
{
cout<<"==============================\n";
 cout<<"\t show Balances Screan \n";
 cout<<"==============================\n";
cout<<"THe BAlanace is : ("<< Iam_Global.Account_balance<<")"<<endl;

}

short Read_M_Menu()
{
short Me;
cout<<"Enter A Number From [1] To [5] ?";
cin>>Me;
while (Me<1||Me>5)
{
    system("cls");
  cout<<"Please Enter A Number From [1] To [5] ? ";
  cin>>Me;

}
return Me;
}

void Calls(En_record Call1)
{
    switch (Call1)
    {
    case  En_record::Quick_Withdrow:
      system("cls");
      Print_Quick_();
       GO_Back_Main_Menu();
        break;
        case  En_record::Normal_Withdrow :
      system("cls");
      Show_Perforem_Nurmal_WhithDrow();
       GO_Back_Main_Menu();
        break;
    
        case  En_record::Deposit :
      system("cls");
      Show_Perform_depodit();
       GO_Back_Main_Menu();
        break;
    
        case  En_record::Check_BAlance :
      system("cls");
      Show_balances();
       GO_Back_Main_Menu();
        break;
    
    case  En_record::Logout :
      system("cls");
      Login();
        break;
    
    }

}



void Print_Atm_system_Screan( )
 { system("cls");
     cout << "===============================================" << endl; 
     cout << "\t\t ATM Menu Screen " << endl; 
     cout << "===============================================" << endl;
    cout << "\t Quick Withdrow  [1] : " << endl;
    cout << "\t Normal Withdrow [2] : " << endl;
    cout << "\t Deposit         [3] : " << endl;
    cout << "\t Check Balance   [4] :" << endl;
    cout << "\t Logout          [5] : " << endl;
    cout << "===============================================" << endl;
  Calls((En_record) Read_M_Menu()); 
}
bool Check_Login_fald(string Account , string pin )
{
    if (Find_clien_By_Accountnumber_And_pincode(Account, pin , Iam_Global))
    {
      return true;
    }
    
return false;
}

void Login()
{
    string Account_number = "", Pin_code = "";
    bool Login_Fald = false; 
    do
    {
         system("cls");
        cout << "\n---------------------------------\n";
        cout << "\tLogin Screen";
        cout << "\n---------------------------------\n";
        if (Login_Fald)
        {
           cout<<"The Account|OR|PinCode Error ! :Please reload Enter a Account And Pin :  ";
        }
        cout<<"PLease Enter A Account Number : ";
        cin>>Account_number;

        cout<<"Please Enter A Pincode : ";
        cin>>Pin_code;
       Login_Fald =!  Check_Login_fald(Account_number , Pin_code );

    } while (Login_Fald);
    Print_Atm_system_Screan( );


}

int main()
{
Login();
return 0;
}