#pragma once

#include <string>

namespace Records {

	const int kDefaultStartingSalary = 30000;

	class Employee
	{
	public:
		static const size_t CSV_INDEX_EMPLOYEE_NUMBER = 0;
        static const size_t CSV_INDEX_FIRST_NAME = 1;
        static const size_t CSV_INDEX_MIDDLE_NAME = 2;
        static const size_t CSV_INDEX_LAST_NAME = 3;
		static const size_t CSV_INDEX_ADDRESS = 4;
        static const size_t CSV_INDEX_SALARY = 5;
        static const size_t CSV_INDEX_HIRE_STATUS = 6;

		Employee() = default;
		Employee(
			const std::string& firstName,
			const std::string& middleName, 
			const std::string& lastName);

		void promote(int raiseAmount = 1000);
		void demote(int demeritAmount = 1000);
		void hire(); // Hires or rehires the employee
		void fire(); // Dismisses the employee
		void display() const;// Outputs employee info to console

		// Getters and setters
		void setFirstName(const std::string& firstName);
		const std::string& getFirstName() const;

		void setMiddleName(const std::string& middleName);
		const std::string& getMiddleName() const;

		void setLastName(const std::string& lastName);
		const std::string& getLastName() const;

		void setAddress(const std::string& address){
			mAddress = address;
		}
		const std::string& getAddress() const{
			return mAddress;
		}

		void setEmployeeNumber(int employeeNumber);
		void setEmployeeNumber(const std::string& text);
		int getEmployeeNumber() const;

		void setSalary(int newSalary);
		int getSalary() const;
		void setHireStatus(bool hired);
		bool isHired() const;

	private:
		std::string mFirstName;
		std::string mMiddleName;
		std::string mLastName;
		std::string mAddress;
		int mEmployeeNumber = -1;
		int mSalary = kDefaultStartingSalary;
		bool mHired = false;
	};
}

