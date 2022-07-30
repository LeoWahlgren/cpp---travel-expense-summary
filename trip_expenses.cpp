/*
Calculates and summarize all expenses form trip for a group of friends. Reads a file of transactions, it's also possible to
add and delete transactions. Using vectors to store things in lists

*/
#include <iostream>
#include <cctype>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
//#include <format>
using namespace std;

//========Function decleration===========
void menu1();
void menu2();
// ======Class decleration===============
class Person{
private:
    string name;
    double payed_others;
    double debt;
public:
    Person(); //Constructor
    Person(string n, double p, double d); //Constructor with parameters
    string get_name(); //get name of person
    double get_payed(); //get the amount of how much the person has payed
    double get_debt(); //get the debt
    void writeout(ostream &os); //writes out a summary of all debts/payments for all persons in the list
};

class Transaction{
private:
    string date;
    string type;
    string name;
    double amount;
    int num_friends;
    vector<string> friends;
public:
    Transaction(); //constructor
    void clear_friends();
    string get_name(); //Getter of name who payed for the transaction
    double get_amount(); //Getter of transaction amount
    int get_num_friends(); //Getter of number of friends belonging to the transaction
    bool check_friend( string name ); //check if friend name exists in the transaction
    bool readTrans( istream &is ); //Reads a transaction, either from file or user input
    void writeTrans( ostream &os ); //Writes a file

};

class Person_list{
private:
    int num_pers;

public:
    vector <Person> persons; //vector of class Persons
    Person_list(); //constructor
    int get_num_persons();
    void add_person(Person pnew); //function to add person to person_list
    void write_out_all(ostream &os); //Anropar skrivUt och skriver ut information för alla delaktiga på resan
    bool check_person( const string& name); //check if person exists
    double sumDebt(); //Calculates the sum of all debts for a person
    double summaPayment(); //Calculates the sum of all payments for a person
    void print_names();

};


class Transaction_list{
private:
    int num_transactions;

public:
    vector <Transaction> transactions; //vector of class transactions
    Transaction_list(); //constructor
    int get_num_transactions(); //get number of transactions
    void add_trans(Transaction &t); //adds transaction
    void write_out(ostream & os); //writes out the transaction list on a file
    void reads(istream & is, bool type); //reads transation, either from file or keyboard input
    double total_cost(); //Total cost of trip
    double payment( string name ); //Total sum of payment for a person
    double debt( string name ); //Total sum of debt for a person
    Person_list arrange_persons(); //Arrange a peson list from all the transactions;
};

int main(){
Transaction_list trip;
menu1();
int choice1;
cin >> choice1;
if (choice1 == 0)
    {
        cout << "yes" << endl;
        ifstream is;
        is.open("resa5.txt");
        trip.reads(is, true);
    }
else if (choice1 == 1)
    {
        cout <<"Insert one transaction, press" << endl;
        cout << "000000(date) string(type) name(payed) 00(amount) 0(num_friends) Lars Bengt(list of names)" << endl;
        trip.reads(cin, false);
    }
else
{
    cout << "Wrong input" << endl;
    main();
}
int choice;
menu2();
cin >> choice;
while (choice!=0){

    switch(choice){
    case 0:
        {
        break;
        }

    case 1:
        {
        cout <<"Insert one transaction" << endl;
        cout << "000000(date) string(type) name(payed) 00(amount) 0(num_friends) Lars Bengt(list of names)" << endl;
        trip.reads(cin, false);
        break;
        }
    case 2:
        {
            trip.write_out(cout);
            break;
        }
    case 3:
        {
            cout << "Total cost: $" << trip.total_cost() << endl;
            break;
        }
    case 4:
        {
            cout << "Please state name" << endl;
            string curr_name;
            cin >> curr_name;
            cout << curr_name << " has in debt " << trip.debt(curr_name) << endl;
            break;
        }
    case 5:
        {
            cout << "Please state name" << endl;
            string curr_name;
            cin >> curr_name;
            cout << curr_name << " has payed " << trip.payment(curr_name) << endl;
            break;
        }
    case 6:
        {
            Person_list participants = trip.arrange_persons();
            participants.print_names();
            cout << "Please give name of file to save summary on " << endl;
            string fname;
            cin >> fname;
            fname += ".txt";
            ofstream os (fname);
            participants.write_out_all(os);
        }

    }
    menu2();
    cin >> choice;
}
        cout << "Please give name of file" << endl;
        string fname;
        cin >> fname;
        fname += ".txt";
        ofstream os (fname);
        trip.write_out(os);
        cout << "All transactions has been saved to " + fname << endl;

return 0;
}

void menu1()
{
    cout << "Choose an option in the menu below: " << endl;
    cout << "0. Read a trip from file." << endl;
    cout << "1. Start with an empty trip." << endl;
}

void menu2()
{
    cout << "Choose an option in the menu below: " << endl;
    cout << "0. Finish. All transactions are saved." << endl;
    cout << "1. Read one transaction from keyboard_input." << endl;
    cout << "2. Write out information about all transactions." << endl;
    cout << "3. Calculate total cost." << endl;
    cout << "4. Show how much a person has in debt" << endl;
    cout << "5. Show how much a person has payed" << endl;
    cout << "6. List all persons and their information " << endl;
}
//--------------Person functions----------------------------------
Person::Person()
:name("None"), payed_others(0.00), debt(0.00){}

Person::Person(string n, double p, double d)
{
    name=n;
    payed_others = p;
    debt = d;
}
string Person::get_name()
{
    return name;
}
double Person::get_payed()
{
    return payed_others;
}

double Person::get_debt()
{
    return debt;
}

void Person::writeout(ostream &outfile)
{
    cout << name << " has payed $" << payed_others << endl;
    cout << name << " has $" << debt << " in debt" << endl;

    double rest = payed_others - debt;
    if (rest >= 0)
        {
            cout << name << " will get back $" << rest << endl;
            outfile << name << " will get back $" << rest << endl;
        }
    else
    {
            cout << name << " will pay other $" << abs(rest) << endl;
            outfile << name << " will pay other $" << abs(rest) << endl;

    }
    outfile << endl;


}
// ----------------- Person list functions--------------------

Person_list::Person_list()
:num_pers(0)
{
    vector<Person> persons;
}
int Person_list::get_num_persons()
{
    return num_pers;
}

void Person_list::add_person(Person pnew)
{
    persons.push_back(pnew);
    num_pers++;

}
void Person_list::print_names()
{
    for (int i=0; i < num_pers; i++)
    {
        string namep = persons[i].get_name();
        cout << namep << ", ";
    }
    cout << endl;
}

void Person_list::write_out_all(ostream &outfile)
{
    for (int i = 0;i < num_pers; i++)
    {
        persons[i].writeout(outfile);
    }
}

bool Person_list::check_person(const string &name)
{
    for (int i=0; i < num_pers; i++)
    {
        if (name == persons[i].get_name())
            {
                return true;
            }
    }
    return false;
}

//--------------Transaction functions--------------------------
Transaction::Transaction()
:date("000000"), type("None"), name("None"), amount(0.00), num_friends(0)
{
    vector <string> friends;
}

void Transaction::clear_friends()
{
    friends.clear();
}

string Transaction::get_name()
{
    return name;
}

double Transaction::get_amount()
{
    return amount;
}

int Transaction::get_num_friends()
{
    return num_friends;
}

bool Transaction::check_friend(string name)
{
    for (int i = 0; i < num_friends; i++)
    {
        if (friends[i] == name)
        {
            return true;
        }

    }
    return false;
}

bool Transaction::readTrans(istream &is)
{
    is >> date >> type >> name >>
    amount >> num_friends;

    for (int i = 0; i < num_friends; i++)
    {
        string temp="";
        is >> temp;
        friends.push_back(temp);
    }
    return !is.eof();
}

void Transaction::writeTrans(ostream &outfile)
{
    outfile << date << " " << type << " " << name << " " << amount << " " << num_friends << " ";
    for (int i = 0; i < num_friends; i++)
    {
        outfile << friends[i] << " ";
    }

    outfile << endl;

}


//------------------------Transaction List methods-------------------------------
Transaction_list::Transaction_list():num_transactions(0)
{
    vector<Transaction> transactions;
}

int Transaction_list::get_num_transactions()
{
    return num_transactions;
}

void Transaction_list::add_trans(Transaction &t)
{
    transactions.push_back(t);
}

void Transaction_list::write_out(ostream &outfile)
{
   for (int i = 0; i < num_transactions; i++)
    {
    transactions[i].writeTrans(outfile);
   }

}

void Transaction_list::reads(istream& is, bool type)
{
    if (!type)
    {
        Transaction t;
        t.readTrans(is);
        add_trans(t);
        num_transactions++;
    }
    else
    {
            Transaction t;
         while(t.readTrans(is))
         {
             add_trans(t);
            num_transactions++;
            t.clear_friends();
         }
    }
}

double Transaction_list::total_cost(){
double total = 0;
for (int i =0; i < num_transactions; i++)
{
  total += transactions[i].get_amount();
}
    return total;
}

double Transaction_list::payment(string name)
{
    double payment_person = 0;
    for (int i =0; i < num_transactions; i++)
    {
        string curr_name = transactions[i].get_name();
        if (name == curr_name)
        {
            int n_friends = transactions[i].get_num_friends();
            payment_person += (transactions[i].get_amount() * n_friends/(n_friends + 1));
        }
    }
    return payment_person;
}

double Transaction_list::debt(string name)
{
    double debt_person = 0;
    for (int i =0; i < num_transactions; i++)
    {
        if (transactions[i].check_friend(name))
        {
            debt_person += (transactions[i].get_amount() / (transactions[i].get_num_friends() + 1));
        }
    }
    return debt_person;
}

Person_list Transaction_list::arrange_persons()
{
    Person_list participants;
    for (int i=0; i < num_transactions; i++)
    {
        string name = transactions[i].get_name();

        if (!(participants.check_person(name)))
        {
            Person participant(name, payment(name), debt(name));
            participants.add_person(participant);
        }

    }
    return participants;
}



