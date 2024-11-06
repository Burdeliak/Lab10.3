#include "pch.h"
#include "CppUnitTest.h"
#include <vector>
#include <string>
#include <algorithm>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// Визначаємо структуру Employee
struct Employee {
	std::string lastName;
	std::string initials;
	std::string position;
	int yearOfHire;
	int salary;
};

// Функція для додавання службовця
void AddEmployee(std::vector<Employee>& employees, const Employee& emp) {
	employees.push_back(emp);
}

// Функція для пошуку службовця за прізвищем
int FindEmployee(const std::vector<Employee>& employees, const std::string& lastName) {
	for (size_t i = 0; i < employees.size(); ++i) {
		if (employees[i].lastName == lastName) {
			return static_cast<int>(i);
		}
	}
	return -1; // Якщо не знайдено
}

// Функція для редагування службовця
void EditEmployee(std::vector<Employee>& employees, int index, const Employee& updatedEmp) {
	if (index >= 0 && index < employees.size()) {
		employees[index] = updatedEmp;
	}
}

// Функція для видалення службовця
void DeleteEmployee(std::vector<Employee>& employees, int index) {
	if (index >= 0 && index < employees.size()) {
		employees.erase(employees.begin() + index);
	}
}

// Функція для сортування службовців за зарплатою
void SortEmployeesBySalary(std::vector<Employee>& employees) {
	std::sort(employees.begin(), employees.end(), [](const Employee& a, const Employee& b) {
		return a.salary < b.salary;
		});
}

namespace TestLab103
{
	TEST_CLASS(TestLab103)
	{
	public:
		// Тест для додавання службовця
		TEST_METHOD(TestAddEmployee)
		{
			std::vector<Employee> employees;
			Employee emp1 = { "Ivanov", "I.I.", "Manager", 2018, 45000 };

			AddEmployee(employees, emp1);

			Assert::AreEqual(size_t(1), employees.size());
			Assert::AreEqual(std::string("Ivanov"), employees[0].lastName);
			Assert::AreEqual(45000, employees[0].salary);
		}

		// Тест для пошуку службовця за прізвищем
		TEST_METHOD(TestFindEmployee)
		{
			std::vector<Employee> employees = {
				{"Ivanov", "I.I.", "Manager", 2018, 45000},
				{"Petrenko", "P.P.", "Engineer", 2020, 38000}
			};

			int index = FindEmployee(employees, "Petrenko");

			Assert::AreEqual(1, index); // Перевірка, що знайдено службовця з індексом 1
			Assert::AreEqual(std::string("Petrenko"), employees[index].lastName);
		}

		// Тест для редагування службовця
		TEST_METHOD(TestEditEmployee)
		{
			std::vector<Employee> employees = {
				{"Ivanov", "I.I.", "Manager", 2018, 45000}
			};

			Employee updatedEmp = { "Ivanov", "I.M.", "Senior Manager", 2019, 50000 };
			EditEmployee(employees, 0, updatedEmp);

			Assert::AreEqual(std::string("I.M."), employees[0].initials);
			Assert::AreEqual(std::string("Senior Manager"), employees[0].position);
			Assert::AreEqual(50000, employees[0].salary);
		}

		// Тест для видалення службовця
		TEST_METHOD(TestDeleteEmployee)
		{
			std::vector<Employee> employees = {
				{"Ivanov", "I.I.", "Manager", 2018, 45000},
				{"Petrenko", "P.P.", "Engineer", 2020, 38000}
			};

			DeleteEmployee(employees, 0);

			Assert::AreEqual(size_t(1), employees.size());
			Assert::AreEqual(std::string("Petrenko"), employees[0].lastName);
		}

		// Тест для сортування за зарплатою
		TEST_METHOD(TestSortBySalary)
		{
			std::vector<Employee> employees = {
				{"Ivanov", "I.I.", "Manager", 2018, 45000},
				{"Petrenko", "P.P.", "Engineer", 2020, 38000}
			};

			SortEmployeesBySalary(employees);

			Assert::AreEqual(std::string("Petrenko"), employees[0].lastName);
			Assert::AreEqual(std::string("Ivanov"), employees[1].lastName);
		}
	};
}
