#include <iostream>
#include <iomanip>
using namespace std;

//Ashley Vierling
//EC Lab #3
///Due Nov 26, 2023 
//A simple bank account designed to use the deposit, withdraw, and transfer features.
//This program also uses inheritance as well as overloading  

class Account {
    public:
        string accountNumber;
        string accountHolder;
        double balance;
        

        Account(const string& number, const string& holder, double initialBalance)
            : accountNumber(number), accountHolder(holder),balance(initialBalance){}

        
        void displayDetails() const{
            cout<<"Account Details for Account (ID: "<< accountNumber<< "):\n"
                <<"  Holder: "<<accountHolder<< "\n"
                <<"  Balance: $"<<fixed << setprecision(2) << balance << "\n";
        }

        void deposit(double amount){
            balance+=amount;
        }

        void withdraw(double amount){
            if(balance>=amount){
                balance-=amount;
            } else{
                cout<< "Invalid withdrawal amount or insufficient balance. \n";
            }
        }

        friend ostream& operator<< (ostream& os, const Account& account);
};

ostream& operator<<(ostream& os, const Account& account){
    account.displayDetails();
    return os;
}           

class SavingsAccount: public Account{
    public:
        double interestRate;
        SavingsAccount(const string& number, const string& holder, double initialBalance, double rate)
            : Account(number,holder,initialBalance), interestRate(rate){}

        void displayDetails() const {
            cout<<"Account Details for Account (ID: "<< accountNumber<< "):\n"
                <<"  Holder: "<<accountHolder<< "\n"
                <<"  Balance: $"<<fixed << setprecision(2) << balance << "\n"
                <<"  Interest Rate: " <<fixed<<setprecision(2)<<interestRate *100 << "%\n";
        }

        void withdraw(double amount) {
            const double minBalance = 100.0;
            if(amount > 0 && (balance - amount) >= minBalance){
                balance-=amount;
            } else{
                cout<< "Invalid withdrawal amount or insufficient balance. \n";
            }
        }

};

class CurrentAccount : public Account{
    public:
        double overdraftLimit;

        CurrentAccount(const string& number, const string& holder, double initialBalance, double overdraft)
            : Account(number,holder,initialBalance), overdraftLimit(overdraft){}

        void displayDetails() const {
            cout<<"Account Details for Account (ID: "<< accountNumber<< "):\n"
                <<"  Holder: "<<accountHolder<< "\n"
                <<"  Balance: $"<<fixed << setprecision(2) << balance << "\n"
                <<"  Overdraft Limit: $" <<fixed<<setprecision(2)<< overdraftLimit << "\n";
        }

        void withdraw(double amount) {
            if (amount > 0 && (balance - amount) >= overdraftLimit){
                balance -= amount;
            } else{
                cout<< "Invalid withdrawal amount or insufficient balance. \n";
            }
        }
};

CurrentAccount operator+(CurrentAccount& current, SavingsAccount& savings){
    double transferAmount = 300.0;
    if(transferAmount <= savings.balance){
        savings.balance -= transferAmount;
        current.balance += transferAmount;
    }else{
        cout<< "Insufficient funds in Savings Account for transfer\n";
    }
    return current;
}



int main() {
    SavingsAccount savings("S123", "John Doe", 1000, 0.02);
    CurrentAccount current("C456", "Jane Doe", 2000, 500);

    savings.displayDetails();
    current.displayDetails();

    savings.deposit(500);
    current.withdraw(1000);
    
    savings.displayDetails();
    current.displayDetails();

    
    current = current + savings;

    savings.displayDetails();
    current.displayDetails();

    return 0;
}