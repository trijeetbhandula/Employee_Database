#include <iostream>
#include <fstream>
#include <stdexcept>
#include <exception>
#include "my_debugger.h"
#include "Database.h"

using namespace std;
using namespace Records;

int displayMenu();
void doHire(Database& db);
void doFire(Database& db);
void doEdit(Database& db);
void doPromote(Database& db);
void doDemote(Database& db);

string selectInputFileName(const string& oldName);
string selectOutputFileName(const string& oldName);


int main()
{
    mylog("started");
	Database employeeDB;
    string dbFileName = "saved_db.csv";

	bool done = false;
	while (!done) {
		int selection = displayMenu();
		switch (selection) {
		case 0:
            mylog("case 0");
			done = true;
			break;
		case 1:
			doHire(employeeDB);
			break;
		case 2:
			doFire(employeeDB);
			break;
		case 3:
			doPromote(employeeDB);
			break;
		case 4:
			employeeDB.displayAll();
			break;
		case 5:
			employeeDB.displayCurrent();
			break;
		case 6:
			employeeDB.displayFormer();
			break;
        case 7:
            employeeDB = makeNewDatabase();
            break;
        case 8:
            dbFileName = selectOutputFileName(dbFileName);
            employeeDB.saveToFile(dbFileName);
            break;
        case 9:
            dbFileName = selectInputFileName(dbFileName);
            employeeDB = loadFromFile(dbFileName);
            break;
        case 10:
            doEdit(employeeDB);
            break;
        case 11:
            employeeDB.searchMenu();
            break;
		default:
			cerr << "Unknown command." << endl;
			break;
		}
	}

	return 0;
}

string selectInputFileName(const string& oldName)
{
    string fileName;
    bool done = false;
    while (!done) {
        cout << "Old file name --> " << oldName << endl;
        cout << "Enter 0 to exit --> \n";
        cout << "Enter file name --> ";
        cin >> fileName;
        cout << "Entered file name --> " << fileName << endl;
        if (fileName == "0") {
            cout << "Nothing was selected. Returning empty name." << endl;
            return "";
        }
        // Check if exists
        ifstream inFile;
        inFile.open(fileName);
        if(inFile) {
            cout << "File exists." << endl;
            return fileName;
        } else {
            cout << "File does not exist. Try again" << endl;
        }
    }
    return "";
}

string selectOutputFileName(const string& oldName)
{
    string fileName;
    bool done = false;
    while (!done) {
        cout << "Old file name --> " << oldName << endl;
        cout << "Enter 0 to exit --> \n";
        cout << "Enter file name --> ";
        cin >> fileName;
        cout << "Entered file name --> " << fileName << endl;
        if (fileName == "0") {
            cout << "Nothing was selected. Returning empty name." << endl;
            return "";
        }
        // Check if exists
        ifstream inFile;
        inFile.open(fileName);
        if(inFile) {
            cout << "File exists. Overwrite? Y/N -->" << endl;
            string ok;
            cin >> ok;
            if (ok == "Y" || ok == "y"){
                return fileName;
            }
            else {
                cout << "File will not be overwritten. Try again." << endl;
            }
        } else {
            cout << "File does not exist. New file will be created." << endl;
            return fileName;
        }
    }
    return "";
}



int displayMenu()
{
	// Note:
	//		One important note is that this code assumes that the user will
	//		"play nice" and type a number when a number is requested.
	//		When you read about I/O in Chapter 13, you will learn how to
	//		protect against bad input.

    int selection;

    cout << endl;
    cout << "Employee Database" << endl;
    cout << "-----------------" << endl;
    cout << "1) Hire a new employee" << endl;
    cout << "2) Fire an employee" << endl;
    cout << "3) Promote an employee" << endl;
    cout << "4) List all employees" << endl;
    cout << "5) List all current employees" << endl;
    cout << "6) List all former employees" << endl;
    cout << "7) Generate new database" << endl;
    cout << "8) Save database to file" << endl;
    cout << "9) Load database from file" << endl;
    cout << "10) Edit employee" << endl;
    cout << "11) Search empoyee" << endl;
    cout << "0) Quit" << endl;
    cout << endl;
    cout << "---> ";
    
	cin >> selection;
    
	return selection;
}

void doHire(Database& db)
{
    mylog("start"); 
    string firstName;
    string middleName;
    string lastName;

    cout << "First name? ";
    cin >> firstName;
    cout << "Middle name? ";
    cin >> middleName;
    cout << "Last name? ";
    cin >> lastName;
    
    db.addEmployee(firstName, middleName, lastName);
    mylog("end"); 
}

void doFire(Database& db)
{
    int employeeNumber;

    cout << "Employee number? ";
    cin >> employeeNumber;

    try {
        Employee& emp = db.getEmployee(employeeNumber);
        emp.fire();
        cout << "Employee " << employeeNumber << " terminated." << endl;
    } catch (const std::logic_error& exception) {
        cerr << "Unable to terminate employee: " << exception.what() << endl;
    }
}

void doEdit(Database& db)
{
    int employeeNumber;

    cout << "Employee number? ";
    cin >> employeeNumber;

    try {
        Employee& emp = db.getEmployee(employeeNumber);
        bool done {false};
        while (!done) {
            emp.display();
            int intOption;
            cout << "1) Edit first name" << endl;
            cout << "2) Edit middle name" << endl;
            cout << "3) Edit last name" << endl;
            cout << "4) Edit address" << endl;
            cout << "5) Edit salary" << endl;
            cout << "0) Exit" << endl;
            cin >> intOption;
            switch (intOption) {
                case 1:
                    {
                        string firstName;
                        cout << "Enter new first name --> ";
                        cin >> firstName;
                        emp.setFirstName(firstName);
                        break;
                    }
                case 2:
                    {
                        string middleName;
                        cout << "Enter new middle name --> ";
                        cin >> middleName;
                        emp.setMiddleName(middleName);
                        break;
                    }
                case 3:
                    {
                        string lastName;
                        cout << "Enter new last name --> ";
                        cin >> lastName;
                        emp.setLastName(lastName);
                        break;
                    }
                case 4:
                    {
                        string address;
                        cout << "Enter new address --> ";
                        std::getline(std::cin >> std::ws, address);
                        emp.setAddress(address);
                        break;
                    }
                case 5:
                    {
                        int salary;
                        cout << "Enter new salary --> ";
                        cin >> salary;
                        emp.setSalary(salary);
                        break;
                    }
                case 0:
                    cout << "Finished editing employee." << endl;
                    done = true;
                break;
                default:
                    cout << "Unknown option. Nothing will be changed." << endl;
                    break;
            }
        }
    } catch (const std::logic_error& exception) {
        cerr << "Unable to terminate employee: " << exception.what() << endl;
    }
}

void doPromote(Database& db)
{
    int employeeNumber;
    int raiseAmount;

    cout << "Employee number? ";
    cin >> employeeNumber;
    cout << "How much of a raise? ";
    cin >> raiseAmount;

    try {
        Employee& emp = db.getEmployee(employeeNumber);
        emp.promote(raiseAmount);
    } catch (const std::logic_error& exception) {
        cerr << "Unable to promote employee: " << exception.what() << endl;
    }
}
