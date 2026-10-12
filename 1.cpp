 
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

class BankAccount {
private:
    int accountNumber;
    string name;
    double balance;

public:
    BankAccount() {
        accountNumber = 0;
        name = "";
        balance = 0;
    }

    void createAccount() {
        ifstream checkFile("account.txt");

        if (checkFile.good()) {
            cout << "\nAccount already exists!\n";
            checkFile.close();
            return;
        }
        checkFile.close();

        cout << "\nEnter Account Number: ";
        cin >> accountNumber;

        if (accountNumber <= 0) {
            cout << "Invalid account number!\n";
            accountNumber = 0;
            return;
        }

        cout << "Enter Customer Name: ";
        getline(cin >> ws, name);

        cout << "Enter Initial Balance: Rs. ";
        cin >> balance;

        if (balance < 0) {
            cout << "Invalid balance!\n";
            accountNumber = 0;
            name = "";
            balance = 0;
            return;
        }

        saveToFile();
        cout << "\nAccount Created Successfully!\n";
    }

    bool loadFromFile() {
        ifstream file("account.txt");

        if (!file.is_open()) {
            return false;
        }

        file >> accountNumber;
        file.ignore();
        getline(file, name);
        file >> balance;

        file.close();
        return !file.fail();
    }

    void saveToFile() {
        ofstream file("account.txt");

        if (file.is_open()) {
            file << accountNumber << "\n";
            file << name << "\n";
            file << fixed << setprecision(2) << balance << "\n";
            file.close();
        } else {
            cout << "Error saving account data!\n";
        }
    }

    void depositMoney() {
        if (!loadFromFile()) {
            cout << "\nPlease create an account first!\n";
            return;
        }

        double amount;
        cout << "\nEnter Deposit Amount: Rs. ";
        cin >> amount;

        if (amount > 0) {
            balance += amount;
            saveToFile();
            cout << "Deposit Successful!\n";
            cout << "New Balance: Rs. "
                 << fixed << setprecision(2) << balance << "\n";
        } else {
            cout << "Invalid Amount!\n";
        }
    }

    void withdrawMoney() {
        if (!loadFromFile()) {
            cout << "\nPlease create an account first!\n";
            return;
        }

        double amount;
        cout << "\nEnter Withdrawal Amount: Rs. ";
        cin >> amount;

        if (amount <= 0) {
            cout << "Invalid Amount!\n";
        } else if (amount > balance) {
            cout << "Insufficient Balance!\n";
        } else {
            balance -= amount;
            saveToFile();
            cout << "Withdrawal Successful!\n";
            cout << "Remaining Balance: Rs. "
                 << fixed << setprecision(2) << balance << "\n";
        }
    }

    void checkBalance() {
        if (!loadFromFile()) {
            cout << "\nPlease create an account first!\n";
            return;
        }

        cout << "\n===== ACCOUNT DETAILS =====\n";
        cout << "Account Number: " << accountNumber << "\n";
        cout << "Customer Name: " << name << "\n";
        cout << "Available Balance: Rs. "
             << fixed << setprecision(2) << balance << "\n";
    }
};

int main() {
    BankAccount account;
    int choice;

    do {
        cout << "\n================================\n";
        cout << "     BANK MANAGEMENT SYSTEM\n";
        cout << "================================\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Check Balance\n";
        cout << "5. Exit\n";
        cout << "================================\n";
        cout << "Enter Your Choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input! Please enter a number.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
            case 1:
                account.createAccount();
                break;

            case 2:
                account.depositMoney();
                break;

            case 3:
                account.withdrawMoney();
                break;

            case 4:
                account.checkBalance();
                break;

            case 5:
                cout << "\nThank you for using our Bank System!\n";
                break;

            default:
                cout << "\nInvalid Choice! Try Again.\n";
        }

    } while (choice != 5);

    return 0;
}
