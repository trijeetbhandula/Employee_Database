#include <iostream>
#include <stdexcept>
#include "Database.h"
#include <fstream>
#include <algorithm>
#include <sstream>

using namespace std;

namespace Records {

	Employee& Database::addEmployee(
		const string& firstName,
		const string& middleName,
		const string& lastName)
	{
		Employee theEmployee(firstName, middleName, lastName);
		theEmployee.setEmployeeNumber(mNextEmployeeNumber++);
		theEmployee.hire();
		mEmployees.push_back(theEmployee);

		return mEmployees[mEmployees.size() - 1];
	}

	Employee& Database::addEmployee(Employee empl)
	{
		mEmployees.push_back(empl);
		return mEmployees[mEmployees.size() - 1];
	}


	Employee& Database::getEmployee(int employeeNumber)
	{
		for (auto& employee : mEmployees) {
			if (employee.getEmployeeNumber() == employeeNumber) {
				return employee;
			}
		}
		throw logic_error("No employee found.");
	}

	Employee& Database::getEmployee(
		const string& firstName, 
		const string& middleName,
		const string& lastName)
	{
		for (auto& employee : mEmployees) {
			if (employee.getFirstName() == firstName &&
				employee.getMiddleName() == middleName &&
				employee.getLastName() == lastName) {
					return employee;
			}
		}
		throw logic_error("No employee found.");
	}

	void Database::displayAll() const
	{
		for (const auto& employee : mEmployees) {
			employee.display();
		}
	}
string getSearchStringMenu()
{
    string searchTag;
    cout << "Enter search string here --> ";
    cin >> searchTag;
    return searchTag;
}


int displaySearchMenu()
{
    int selection;

    cout << endl;
    cout << "Search Employee Database" << endl;
    cout << "-----------------" << endl;
    cout << "1) Search by first name" << endl;
    cout << "2) Search by middle name" << endl;
    cout << "3) Search by last name" << endl;
	cout << "4) Search by address" << endl;
	cout << "0) Quit" << endl;	
    cout << endl;
    cout << "---> ";
	cin >> selection;
	return selection;
}


void Database::searchMenu() const{
	bool done = false;
	Database searchResults;
	while (!done) {
		int selection = displaySearchMenu();
		switch (selection) {
		case 0:
			done = true;
			break;
		case 1:
			searchResults = searchBy(SearchOption::BY_FIRST_NAME);
			break;
        case 2:
            searchResults = searchBy(SearchOption::BY_MIDDLE_NAME);
            break;
        case 3:
            searchResults = searchBy(SearchOption::BY_LAST_NAME);
            break;
        case 4:
            searchResults = searchBy(SearchOption::BY_ADDRESS);
            break;
		default:
			cerr << "Unknown command." << endl;
			break;
		}
	}
}


Database Database::searchBy(SearchOption option) const
{
    string searchTag = getSearchStringMenu();
	Database result;
    for (const auto& e : mEmployees) {
        string targetString;
        switch (option) {
        case SearchOption::BY_FIRST_NAME:
            targetString = e.getFirstName();
            break;
        case SearchOption::BY_MIDDLE_NAME:
            targetString = e.getMiddleName();
            break;
        case SearchOption::BY_LAST_NAME:
            targetString = e.getLastName();
            break;
        case SearchOption::BY_ADDRESS:
            targetString = e.getAddress();
            break;
        }
        size_t pos = targetString.find(searchTag, 0);
        if (pos == string::npos) {
            continue;
        }
        e.display();
        result.addEmployee(e);
    }
    if (result.size() == 0) {
        cout << "No results found." << endl;
    }
    return result;
}


void Database::saveToFile(const string& fileName) const
{
    if (fileName.size() == 0) {
        cout << "Ignore saving to empty file name\n";
        return;
    }
    ofstream dbFile(fileName, ios_base::trunc);
    if (dbFile.fail()) {
        cerr << "Unable to open debug file!" << endl;
        return;
    }

    dbFile << "EmployeeNumber,FirstName,MiddleName,LastName,Address,Salary,HireStatus\n";
    for (const auto& employee : mEmployees) {
        dbFile << employee.getEmployeeNumber() << ", ";
        dbFile << employee.getFirstName() << ", ";
        dbFile << employee.getMiddleName() << ", ";
        dbFile << employee.getLastName() << ", ";
        dbFile << employee.getAddress() << ", ";
        dbFile << employee.getSalary() << ", ";
        dbFile << (employee.isHired() ? "Hired" : "Not Hired") << "\n";
    }
}

	void Database::displayCurrent() const
	{
		for (const auto& employee : mEmployees) {
			if (employee.isHired())
				employee.display();
		}
	}

	void Database::displayFormer() const
	{
		for (const auto& employee : mEmployees) {
			if (!employee.isHired())
				employee.display();
		}
	}

Database makeNewDatabase()
{
    vector<string> arrStreetNames = {"Maple", "Oak", "Cedar", "Pine", "Elm", "Willow"};

    vector<string> arrFirst {
        "Emma", "Liam", "Olivia", "Noah", "Ava",
        "Sophia", "Isabella", "Mia", "Jackson", "Lucas",
        "Oliver", "Evelyn", "Aiden", "Aria", "Caden",
        "Charlotte", "Amelia", "Harper", "Mila", "Ella"
    };

    vector<string> arrMiddle {
        "James", "Grace", "Benjamin", "Hazel", "Henry",
        "Lily", "William", "Luna", "Alexander", "Chloe",
        "Ethan", "Eleanor", "Madison", "Aurora", "Mason",
        "Scarlett", "Abigail", "Ella", "Liam", "Aiden"
    };

    vector<string> arrLast {
        "Johnson", "Smith", "Williams", "Jones", "Brown",
        "Davis", "Miller", "Wilson", "Moore", "Taylor",
        "Anderson", "Thomas", "Jackson", "White", "Harris",
        "Martin", "Thompson", "Garcia", "Martinez", "Robinson"
    };
    
    Database db;
    int count = 0;
    for (const string& firstName: arrFirst) {
        for (const string& middleName: arrMiddle) {
            for (const string& lastName: arrLast) {
                count++;
                    string countStr = to_string(count);
                    Employee& emp1 = db.addEmployee(
                        firstName, middleName, lastName);
                        const string& streetname = arrStreetNames[count % arrStreetNames.size()];
                        string address = countStr + " " + streetname + " street";
                        emp1.setAddress(address);
                            
            }
        }
    }    
    return db;
}

Database loadFromFile(const string& fileName) {
    Database db;
    if (fileName.size() == 0) {
        cout << "Ignore loading from empty file name\n";
        return db;
    }
    ifstream dbFile(fileName, ios_base::in);
    if (dbFile.fail()) {
        cerr << "Unable to open file: " << fileName << endl;
        return db;
    }

    string header;
    getline(dbFile, header);
    cout << header << endl;

    string line;
    while (getline(dbFile, line)) {
        if (line.empty()) {
            continue;
        }

        vector<string> tokens;
        stringstream streamFromLine(line);
        string token;
        while (getline(streamFromLine, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() < Employee::CSV_INDEX_HIRE_STATUS + 1) {
            cerr << "Incomplete data in line: " << line << endl;
            continue;
        }

        Employee empl(
            tokens[Employee::CSV_INDEX_FIRST_NAME],
            tokens[Employee::CSV_INDEX_MIDDLE_NAME],
            tokens[Employee::CSV_INDEX_LAST_NAME]
        );

        empl.setEmployeeNumber(stoi(tokens[Employee::CSV_INDEX_EMPLOYEE_NUMBER]));
        empl.setAddress(tokens[Employee::CSV_INDEX_ADDRESS]);
        empl.setSalary(stoi(tokens[Employee::CSV_INDEX_SALARY]));
        empl.setHireStatus(tokens[Employee::CSV_INDEX_HIRE_STATUS] == "Hired");

        db.addEmployee(empl);
    }
    return db;
}



}