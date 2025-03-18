#include <iostream>
#include <vector>
#include <iomanip>
#include <unordered_set>
#include <algorithm>
#include <cctype>
#include <limits>
using namespace std;

class Employee {
protected:
    string id;
    string name;
public:
    Employee(string id, string name) : id(id), name(name) {}
    virtual double calculateSalary() const = 0;
    virtual void display() const = 0;
    string getId() const { return id; }
    string getName() const { return name; }
};

class FullTimeEmployee : public Employee {
    double salary;
public:
    FullTimeEmployee(string id, string name, double salary) : Employee(id, name), salary(salary) {}
    double calculateSalary() const override { return salary; }
    void display() const override {
        cout << "Employee: " << name << " (ID: " << id << ")\n";
        cout << "Fixed Monthly Salary: $" << salary << "\n";
    }
};

class PartTimeEmployee : public Employee {
    double hourlyWage;
    int hoursWorked;
public:
    PartTimeEmployee(string id, string name, double hourlyWage, int hoursWorked) 
        : Employee(id, name), hourlyWage(hourlyWage), hoursWorked(hoursWorked) {}
    double calculateSalary() const override { return hourlyWage * hoursWorked; }
    void display() const override {
        cout << "Employee: " << name << " (ID: " << id << ")\n";
        cout << "Hourly Wage: $" << hourlyWage << "\n";
        cout << "Hours Worked: " << hoursWorked << "\n";
        cout << "Total Salary: $" << calculateSalary() << "\n";
    }
};

class ContractualEmployee : public Employee {
    double paymentPerProject;
    int projectsCompleted;
public:
    ContractualEmployee(string id, string name, double paymentPerProject, int projectsCompleted) 
        : Employee(id, name), paymentPerProject(paymentPerProject), projectsCompleted(projectsCompleted) {}
    double calculateSalary() const override { return paymentPerProject * projectsCompleted; }
    void display() const override {
        cout << "Employee: " << name << " (ID: " << id << ")\n";
        cout << "Contract Payment Per Project: $" << paymentPerProject << "\n";
        cout << "Projects Completed: " << projectsCompleted << "\n";
        cout << "Total Salary: $" << calculateSalary() << "\n";
    }
};

vector<Employee*> employees;
unordered_set<string> idSet;
unordered_set<string> nameSet;

bool isUniqueID(const string& id) {
    return idSet.find(id) == idSet.end();
}

bool isUniqueName(const string& name) {
    return nameSet.find(name) == nameSet.end();
}

bool isValidName(const string& name) {
    for (char c : name) {
        if (!isalpha(c) && !isspace(c)) {
            return false;
        }
    }
    return true;
}

int getValidIntInput(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail() || value < 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid positive number.\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

void addEmployee(int type) {
    string id, name;
    double salary, hourlyWage, paymentPerProject;
    int hoursWorked, projectsCompleted;
    
    cout << "Enter ID: ";
    cin >> id;
    while (!isUniqueID(id)) {
        cout << "Duplicate ID. Enter another ID: ";
        cin >> id;
    }
    cin.ignore();
    
    cout << "Enter Name: ";
    getline(cin, name);
    while (!isValidName(name) || !isUniqueName(name)) {
        cout << "Invalid or duplicate name. Enter again: ";
        getline(cin, name);
    }
    
    if (type == 1) {
        cout << "Enter Salary: ";
        cin >> salary;
        employees.push_back(new FullTimeEmployee(id, name, salary));
    } else if (type == 2) {
        cout << "Enter Hourly Wage: ";
        cin >> hourlyWage;
        hoursWorked = getValidIntInput("Enter Hours Worked: ");
        employees.push_back(new PartTimeEmployee(id, name, hourlyWage, hoursWorked));
    } else if (type == 3) {
        cout << "Enter Payment Per Project: ";
        cin >> paymentPerProject;
        projectsCompleted = getValidIntInput("Enter Projects Completed: ");
        employees.push_back(new ContractualEmployee(id, name, paymentPerProject, projectsCompleted));
    }
    idSet.insert(id);
    nameSet.insert(name);
}

void displayPayrollReport() {
    cout << "\n------ Employee Payroll Report ------\n";
    for (const auto& emp : employees) {
        emp->display();
        cout << "\n";
    }
}

int main() {
    int choice;
    do {
        cout << "\nMenu";
        cout << "\n1 - Full-time Employee";
        cout << "\n2 - Part-time Employee";
        cout << "\n3 - Contractual Employee";
        cout << "\n4 - Display Payroll Report";
        cout << "\n5 - Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1: case 2: case 3:
                addEmployee(choice);
                break;
            case 4:
                displayPayrollReport();
                break;
            case 5:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 5);
    
    for (auto emp : employees) {
        delete emp;
    }
    return 0;
}