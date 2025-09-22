#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <string>
using namespace std;

const string INPUT_FILE = "file_in.dat";
const string OUTPUT_FILE = "file_out.dat";
const string ERROR_FILE = "file_err.dat";
const string LOG_FILE = "log_out.dat";

const int LIST_SIZE = 15;

class BankAccount {
public:

    BankAccount();
    BankAccount(const BankAccount& NewAccount);
    BankAccount(string SSN, string firstname, string lastname, string email);
    ~BankAccount();

    void setAccount(string newSSN, string newFirstName, string newLastName, string newEmail, int newID, double newAvailableBalance, double newPresentBalance);
    void setAccount(string newSSN, string newFirstName, string newLastName, string newEmail);
   
    double setPresentBalance(double newPresentBalance);
    double setAvailableBalance(double newAvailableBalance);
    void createCheckingAcc(string domain, int index);
    
    void setEmail(string newEmail);
    void setID(int newID);
    void setName(string newFirstName, string newLastName);

    string toString();

private:

    int accountID = 0;
    double availableBalance = 0.00, presentBalance = 100.00;
    string firstName = "", lastName = "", emailAdress = "", SSN = "";

};

void validateInput(BankAccount validList[], BankAccount invalidList[], int &validSize, int &invalidSize);
void printListToScreen(BankAccount list[], int size);
void printListToFile(BankAccount list[], int size, const string filename);
void printListToFile(BankAccount list[], int size, const string filename);


int main()
{

    BankAccount validAccounts[LIST_SIZE], invalidAccounts[LIST_SIZE];
    int validAccountSize = -1, invalidAccountSize = -1;

    int input = 0;
    while (input != 5) {

        cout << "\nMenu:\n1.process all new checking account requests\n2.print all successfully created accounts to the screen\n3.print all invalid records to the screen\n4.print the log file\n5.quit and write all  newly created checking accounts to an output file\n\nInput: ";
        cin >> input;
        
        switch (input) {
        case 1:
            validateInput(validAccounts, invalidAccounts, validAccountSize, invalidAccountSize);
            break;
        case 2:
            printListToScreen(validAccounts, validAccountSize);
            break;
        case 3:       
            printListToScreen(invalidAccounts, invalidAccountSize);          
            break;
        case 4:
            printListToFile(validAccounts, validAccountSize, OUTPUT_FILE);
            break;
        case 5:
            printListToFile(validAccounts, validAccountSize, OUTPUT_FILE);
            break;
        default:

            cout << "Invalid choice, try again\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        
        }

    }
    

    return 0;
}

BankAccount::BankAccount() {
    //these will be the default paramiters, I wasnt able to find anything that mentioned what the specifics were for the default
    setAccount("0000000000", "FirstName", "LastName", "user_name@mailserver.domain", 0, 0, 0);

}
BankAccount::BankAccount(const BankAccount& copyFromAccount) {
    //I called it "copyFromAccount to remind myself that the 'BankAccount' you are copying from is the one being passed through the function.

    setAccount(copyFromAccount.SSN, copyFromAccount.firstName, copyFromAccount.lastName, copyFromAccount.emailAdress, copyFromAccount.accountID, copyFromAccount.availableBalance, copyFromAccount.presentBalance);

}
BankAccount::BankAccount(string SSN, string firstname, string lastname, string email) {

    setAccount(SSN, firstname, lastname, email, accountID, availableBalance, presentBalance);

}
BankAccount::~BankAccount() {

    setAccount("0000000000", "FirstName", "LastName", "user_name@mailserver.domain", 0, 0, 0);

}

void BankAccount::setAccount(string newSSN, string newFirstName, string newLastName, string newEmail, int newID, double newAvailableBalance, double newPresentBalance) {

    firstName = newFirstName;
    lastName = newLastName;
   
    emailAdress = newEmail;
    accountID = newID;
    
    availableBalance = setAvailableBalance(newAvailableBalance);
    presentBalance = setPresentBalance(newPresentBalance);

    SSN = newSSN;
}
void BankAccount::setAccount(string newSSN, string newFirstName, string newLastName, string newEmail) {

    setAccount(newSSN, newFirstName, newLastName, newEmail, accountID, availableBalance, presentBalance);

}
void BankAccount::setName(string newFirstName, string newLastName) {

    setAccount(SSN, newFirstName, newLastName, emailAdress, accountID, availableBalance, presentBalance);

}

double BankAccount::setPresentBalance(double newPresentBalance) {
    //rather than call "SetAccount", these functions are called within "setAccount" to ensure that they are valid anytime they are changed, 
    // and the function can still be called to change only "presetBalance"
    
    if (newPresentBalance < -50.00) {

        cout << "Present balance cannot be less than $50.00, cancelling request...\n";
        newPresentBalance = presentBalance;

    }

    return newPresentBalance;

}
double BankAccount::setAvailableBalance(double newAvailableBalance) {
    //rather than call "SetAccount", these functions are called within "setAccount" to ensure that they are valid anytime they are changed, 
    // and the function can still be called to change only "availableBalance, just like in "setPresentBalance"
    
    if (newAvailableBalance > presentBalance) {

        cout << "Available balance cannot be greater, cancelling request...\n";
        newAvailableBalance = availableBalance;

    }
    else if (newAvailableBalance < -50.00) {

        cout << "Available balance cannot be less than $50.00, cancelling request...\n";
        newAvailableBalance = availableBalance;

    }
    return newAvailableBalance;

}
void BankAccount::createCheckingAcc(string domain, int index) {

    accountID = (((rand() % 1000) + 1) * 100) + (index + 1);

    if (domain == "edu") {

        setPresentBalance(150.00);

    }
    else {

        setPresentBalance(100.00);

    }

    
}

void BankAccount::setEmail(string newEmail) {

    setAccount(SSN, firstName, lastName, newEmail, accountID, availableBalance, presentBalance);

}
void BankAccount::setID(int newID) {

    setAccount(SSN, firstName, lastName, emailAdress, newID, availableBalance, presentBalance);

}

string BankAccount::toString() {

    return SSN + " " + firstName + " " + lastName + " " + emailAdress + "\n";

}

void validateInput(BankAccount validList[], BankAccount invalidList[], int &validSize, int &invalidSize) {

    ifstream infile;

    infile.open(INPUT_FILE);
    
    if (!infile) {
        cout << "Cannot open file" << endl;
        exit(EXIT_FAILURE);
    }
    
    string tempFirstName = "", tempLastName = "", tempEmailAdress = "", tempSSN = "";
    BankAccount tempAccount;
    int usernameSize = 0, mailserverSize = 0, firstNameSize = 0, lastNameSize = 0, ssnSize = 0, index = 0, requestCount = 0;
    string domain = "";


    infile >> tempSSN >> tempFirstName >> tempLastName >> tempEmailAdress;

    while (infile) {
       
        
        index = 0, usernameSize = 0, mailserverSize = 0, firstNameSize = 0, lastNameSize = 0, ssnSize = 0, index = 0;
        domain = "";
        tempAccount.setAccount(tempSSN, tempFirstName, tempLastName, tempEmailAdress);

        while (tempEmailAdress[index] != '@') {

            if ((tempEmailAdress[index] >= '0' && tempEmailAdress[index] <= '9') || (tempEmailAdress[index] >= 'A' && tempEmailAdress[index] <= 'Z') || (tempEmailAdress[index] >= 'a' && tempEmailAdress[index] <= 'z')) {

                usernameSize++;

            }
            index++;
        }
        while (tempEmailAdress[index] != '.') {

            if ((tempEmailAdress[index] >= 'A' && tempEmailAdress[index] <= 'Z') || (tempEmailAdress[index] >= 'a' && tempEmailAdress[index] <= 'z')) {

                mailserverSize++;

            }
            index++;
        }

        for (int i = tempEmailAdress.length() - 3; i < tempEmailAdress.length(); i++) {

            if (tempEmailAdress[i] >= 'a' && tempEmailAdress[i] <= 'z') {

                domain = domain + tempEmailAdress[i];

            }

        }

        for (int i = 0; i < tempFirstName.length(); i++) {

            if ((tempFirstName[i] >= 'A' && tempFirstName[i] <= 'Z') || (tempFirstName[i] >= 'a' && tempFirstName[i] <= 'z')) {

                firstNameSize++;

            }

        }
        for (int i = 0; i < tempLastName.length(); i++) {

            if ((tempLastName[i] >= 'A' && tempLastName[i] <= 'Z') || (tempLastName[i] >= 'a' && tempLastName[i] <= 'z')) {

                lastNameSize++;

            }

        }

        for (int i = 0; i < tempSSN.length(); i++) {

            if (tempSSN[i] >= '0' && tempSSN[i] <= '9') {

                ssnSize++;

            }

        }
        
        if ((ssnSize > 9) && (usernameSize > 3) && (firstNameSize > 1) && (lastNameSize > 1) && (mailserverSize > 3) && ((domain == "edu") || (domain == "com"))) {

            if (validSize < 14) {

                validSize++;
                validList[validSize] = tempAccount;
                validList[validSize].createCheckingAcc(domain, validSize);
          
            }

        }
        else if ((ssnSize < 9) || (usernameSize < 3) || (firstNameSize < 1) || (lastNameSize < 1) || (mailserverSize < 3) || ((domain != "edu") || (domain != "com"))) {
          
            if (invalidSize < 14) {

                invalidSize++;
                invalidList[invalidSize] = tempAccount;
                
            }   

        }
       
        requestCount++;
        
        infile >> tempSSN >> tempFirstName >> tempLastName >> tempEmailAdress;
           
    }
     
    if (validSize >= 15) {

        cout << "Warning: Max file sized reached, some valid accounts may not be recorded\n";
        validSize = 14;
    
    }     

    if (invalidSize >= 15) {

        cout << "Warning: Max file sized reached, some invalid accounts may not be recorded\n";
        invalidSize = 14;

    }
        validSize++;
        invalidSize++;

        cout << "\nRequests Processed: " << requestCount << "\nSuccsesfull Accounts: " << validSize << "\nUnsuccesfull Accounts: " << invalidSize << "\nAccounts not stored: " << requestCount - (validSize + invalidSize) << endl;

    infile.close();

}
void printListToScreen(BankAccount list[], int size) {

    if (size <= 0) {
        cout << "There are none available at the moment, make you you've processed all checking account requests\n";
    }
    else {

        for (int i = 0; i < size; i++) {

            cout << list[i].toString();

        }

    }

}

void printListToFile(BankAccount list[], int size, const string filename) {

    ofstream outfile;
    outfile.open(filename);

    if (size <= 0) {
        cout << "There are none available at the moment, make you you've processed all checking account requests\n";
    }
    else {

        for (int i = 0; i < size; i++) {

            outfile << list[i].toString();

        }

    }

    outfile.close();

}

/*

Menu:
1.process all new checking account requests
2.print all successfully created accounts to the screen
3.print all invalid records to the screen
4.print the log file
5.quit and write all  newly created checking accounts to an output file

Input: 1

Requests Processed: 19
Succsesfull Accounts: 15
Unsuccesfull Accounts: 1
Accounts not stored: 3

Menu:
1.process all new checking account requests
2.print all successfully created accounts to the screen
3.print all invalid records to the screen
4.print the log file
5.quit and write all  newly created checking accounts to an output file

Input: 2
1274927503 Mary Lee lee35@lapc.edu
1274927503 Jane Lee lee35@lapc.edu
1274927503 poo Lee lee35@lapc.edu
1274927503 geeq2w Lee lee35@lapc.edu
1274927503 Mary Lee lee35@lapc.edu
1274927503 Mary Lee lee35@lapc.edu
1274927503 Mary Lee lee35@lapc.edu
1274927503 Mary Lee lee35@lapc.edu
1274927503 Mary Lee lee35@lapc.edu
1274927503 Mary Lee lee35@lapc.edu
1274927503 Mary Lee lee35@lapc.edu
1274927503 Mary Lee lee35@lapc.edu
1274927503 Mary Lee lee35@lapc.edu
1274927503 Mary Lee lee35@lapc.edu
1274927503 Mary Lee lee35@lapc.edu

Menu:
1.process all new checking account requests
2.print all successfully created accounts to the screen
3.print all invalid records to the screen
4.print the log file
5.quit and write all  newly created checking accounts to an output file

Input: 3
1274927503 a Lee lee35@lapc.edu

Menu:
1.process all new checking account requests
2.print all successfully created accounts to the screen
3.print all invalid records to the screen
4.print the log file
5.quit and write all  newly created checking accounts to an output file

Input: 4

Menu:
1.process all new checking account requests
2.print all successfully created accounts to the screen
3.print all invalid records to the screen
4.print the log file
5.quit and write all  newly created checking accounts to an output file

Input: 5

C:\Users\Matteo\source\repos\Bank application thing\x64\Debug\Bank application thing.exe (process 26040) exited with code 0.
Press any key to close this window . . .
*/