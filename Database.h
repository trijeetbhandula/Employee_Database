#pragma once

#include <iostream>
#include <vector>
#include "Employee.h"

namespace Records {
	const int kFirstEmployeeNumber = 1000;

	class Database
	{
	public:
		Employee& addEmployee(const std::string& firstName,
							  const std::string& middleName,
							  const std::string& lastName);
		Employee& addEmployee(Employee empl);
		Employee& getEmployee(int employeeNumber);
		Employee& getEmployee(const std::string& firstName,
							  const std::string& middleName,
							  const std::string& lastName);

		void displayAll() const;
		void saveToFile(const std::string& fileName) const;
		void displayCurrent() const;
		void displayFormer() const;
		void searchMenu() const;
		std::size_t size() const {return mEmployees.size();};

	private:
		std::vector<Employee> mEmployees;
		int mNextEmployeeNumber = kFirstEmployeeNumber;
		enum class SearchOption {BY_FIRST_NAME, BY_MIDDLE_NAME, BY_LAST_NAME, BY_ADDRESS};
		Database searchBy(SearchOption op) const;
	};

	Database makeNewDatabase();
	Database loadFromFile(const std::string& fileName);

}
