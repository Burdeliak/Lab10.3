#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>

using namespace std;

struct Employee {
    string lastName;
    string initials;
    string position;
    int yearOfHire;
    double salary;
};

// Додавання службовця
void addEmployee(vector<Employee>& employees) {
    Employee emp;
    cout << "Enter last name: ";
    cin >> emp.lastName;
    cout << "Enter initials: ";
    cin >> emp.initials;
    cout << "Enter position: ";
    cin.ignore();
    getline(cin, emp.position);
    cout << "Enter year of hire: ";
    while (!(cin >> emp.yearOfHire) || emp.yearOfHire < 1900 || emp.yearOfHire > 2023) {
        cout << "Invalid year. Please enter a valid year: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    cout << "Enter salary: ";
    while (!(cin >> emp.salary) || emp.salary < 0) {
        cout << "Invalid salary. Please enter a non-negative number: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    employees.push_back(emp);
    cout << "Employee added successfully.\n";
}

// Редагування службовця
void editEmployee(vector<Employee>& employees) {
    string lastName;
    cout << "Enter last name of the employee to edit: ";
    cin >> lastName;

    auto it = find_if(employees.begin(), employees.end(), [&lastName](const Employee& emp) {
        return emp.lastName == lastName;
        });

    if (it != employees.end()) {
        cout << "Editing employee: " << it->lastName << endl;
        cout << "Enter new initials: ";
        cin >> it->initials;
        cout << "Enter new position: ";
        cin.ignore();
        getline(cin, it->position);
        cout << "Enter new year of hire: ";
        while (!(cin >> it->yearOfHire) || it->yearOfHire < 1900 || it->yearOfHire > 2023) {
            cout << "Invalid year. Please enter a valid year: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        cout << "Enter new salary: ";
        while (!(cin >> it->salary) || it->salary < 0) {
            cout << "Invalid salary. Please enter a non-negative number: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        cout << "Employee information updated.\n";
    }
    else {
        cout << "Employee not found.\n";
    }
}

// Видалення службовця
void deleteEmployee(vector<Employee>& employees) {
    string lastName;
    cout << "Enter last name of the employee to delete: ";
    cin >> lastName;

    auto it = remove_if(employees.begin(), employees.end(), [&lastName](const Employee& emp) {
        return emp.lastName == lastName;
        });

    if (it != employees.end()) {
        employees.erase(it, employees.end());
        cout << "Employee deleted.\n";
    }
    else {
        cout << "Employee not found.\n";
    }
}

// Сортування службовців
void sortEmployees(vector<Employee>& employees) {
    int choice;
    cout << "Sort by: 1 - Last Name, 2 - Salary, 3 - Year of Hire: ";
    cin >> choice;

    if (choice == 1) {
        sort(employees.begin(), employees.end(), [](const Employee& a, const Employee& b) {
            return a.lastName < b.lastName;
            });
    }
    else if (choice == 2) {
        sort(employees.begin(), employees.end(), [](const Employee& a, const Employee& b) {
            return a.salary < b.salary;
            });
    }
    else if (choice == 3) {
        sort(employees.begin(), employees.end(), [](const Employee& a, const Employee& b) {
            return a.yearOfHire < b.yearOfHire;
            });
    }
    else {
        cout << "Invalid choice.\n";
    }
}

// Пошук службовця за прізвищем
void searchEmployee(const vector<Employee>& employees) {
    string lastName;
    cout << "Enter last name to search: ";
    cin >> lastName;

    auto it = find_if(employees.begin(), employees.end(), [&lastName](const Employee& emp) {
        return emp.lastName == lastName;
        });

    if (it != employees.end()) {
        cout << "Employee found: " << it->lastName << " " << it->initials << ", Position: " << it->position
            << ", Year of Hire: " << it->yearOfHire << ", Salary: " << it->salary << endl;
    }
    else {
        cout << "Employee not found.\n";
    }
}

// Збереження інформації у файл
void saveToFile(const vector<Employee>& employees) {
    string filename;
    cout << "Enter file name to save data: ";
    cin >> filename;
    ofstream file(filename);

    if (file.is_open()) {
        for (const auto& emp : employees) {
            file << emp.lastName << " " << emp.initials << " " << emp.position << " "
                << emp.yearOfHire << " " << emp.salary << endl;
        }
        file.close();
        cout << "Data saved successfully.\n";
    }
    else {
        cout << "Error opening file.\n";
    }
}

// Зчитування інформації з файлу
void loadFromFile(vector<Employee>& employees) {
    string filename;
    cout << "Enter file name to load data: ";
    cin >> filename;
    ifstream file(filename);

    if (file.is_open()) {
        Employee emp;
        while (file >> emp.lastName >> emp.initials) {
            file.ignore();
            getline(file, emp.position);
            file >> emp.yearOfHire >> emp.salary;
            employees.push_back(emp);
        }
        file.close();
        cout << "Data loaded successfully.\n";
    }
    else {
        cout << "Error opening file.\n";
    }
}

// Головне меню
void menu() {
    vector<Employee> employees;
    int choice;

    do {
        cout << "\nMenu:\n";
        cout << "1. Add Employee\n";
        cout << "2. Edit Employee\n";
        cout << "3. Delete Employee\n";
        cout << "4. Sort Employees\n";
        cout << "5. Search Employee\n";
        cout << "6. Save to File\n";
        cout << "7. Load from File\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: addEmployee(employees); break;
        case 2: editEmployee(employees); break;
        case 3: deleteEmployee(employees); break;
        case 4: sortEmployees(employees); break;
        case 5: searchEmployee(employees); break;
        case 6: saveToFile(employees); break;
        case 7: loadFromFile(employees); break;
        case 0: cout << "Exiting...\n"; break;
        default: cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
}

int main() {
    menu();
    return 0;
}
