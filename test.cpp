#include <iostream>
#include <vector>
#include <string>
using namespace std;

class entryTypeException {
private:
    string message;
public:
    entryTypeException() {
        message = " ";
    }
    entryTypeException(string msg) {
        this->message = msg;
    }
    void printStackTrace() {
        cout << "You have encountered an exception..." << endl;
        cout << "Message: " << message << endl;
    }
};

class employee {
private:
    string companyName;
    string employeeName;
    double salary;
    int noOfLeave;
    double salaryPerDay;

public:
    employee() {
        companyName = " ";
        employeeName = " ";
        salary = 0.0;
        noOfLeave = 0;
    }
    employee(string coName, string eName, double salary, int leave) : companyName(coName), employeeName(eName), salary(salary), noOfLeave(leave) {}

   virtual void acceptEmployee() {
        cout << "Enter company name: " << endl;
        cin >> companyName;
        cout << "Enter name of employee: " << endl;
        cin >> employeeName;
        cout << "Enter your salary: " << endl;
        cin >> salary;
        cout << "Enter number of leave taken: " << endl;
        cin >> noOfLeave;
    }

    virtual void displayEmployee() {
        cout << "Company Name: " << companyName << endl;
        cout << "Employee Name: " << employeeName << endl;
        cout << "Salary: " << salary << endl;
        cout << "Leaves Taken: " << noOfLeave << endl;
    }

    virtual void calculateSalary() = 0;

    void setSalary(double salaries) {
        this->salary = salaries;
    }

    int getSalary() {
        return salary;
    }

    void setLeavesCount(int numOfLeave) {
        this->noOfLeave = numOfLeave;
    }

    int getLeavesCount() {
        return noOfLeave;
    }
};

class HR : public employee {
private:
    int noOfEmployeesHired;
public:
    HR() : noOfEmployeesHired(0) {}

    HR(string coName, string eName, double salary, int leave) : employee(coName, eName, salary, leave), noOfEmployeesHired(0) {}
    void acceptEmployee(){
        employee::acceptEmployee();
        cout<<"enter no of emplyees hired:"<<endl;
        cin>>noOfEmployeesHired;
    }
     void displayEmployee(){
        employee::displayEmployee();
        cout<<"employees hired:"<<noOfEmployeesHired<<endl;
     }
    void calculateSalary() {
        double sal;

        if (noOfEmployeesHired < 0 || getLeavesCount() < 0) {
            throw entryTypeException("Incentives or leaves can't be negative");
        }

        if (getLeavesCount() > 3) {
            sal = (34 - getLeavesCount()) * 1250 + noOfEmployeesHired;
        } else {
            sal = (31) * 1250 + noOfEmployeesHired;
        }

        setSalary(sal);
        cout << "Your salary is: " << getSalary() << endl;
    }
};

class trainingEmployee : public employee {
private:
    int noOfLectureSession;
    int noOfLabSession;
public:
    trainingEmployee() : noOfLectureSession(0), noOfLabSession(0) {}

    trainingEmployee(int lec, int lab, string coName, string eName, double salary, int leave)
        : employee(coName, eName, salary, leave), noOfLectureSession(lec), noOfLabSession(lab) {}

    void acceptEmployee(){
        employee::acceptEmployee();
        cout<<"enter the no of lecture taken"<<endl;
        cin>>noOfLectureSession;
        cout<<"enter no of lab session taken:"<<endl;
        cin>>noOfLabSession; 
    }
    void displayEmployee(){
        employee::displayEmployee();
        cout<<"lecture session:"<<noOfLectureSession<<endl;
        cout<<"lab session:"<<noOfLabSession<<endl;
    }

    void calculateSalary() override {
        double sal;

        if (getLeavesCount() < 0 || noOfLabSession < 0 || noOfLectureSession < 0) {
            throw entryTypeException("Leaves, lecture sessions, and lab sessions can't be negative");
        }

        if (getLeavesCount() > 3) {
            sal = (34 - getLeavesCount()) * 900 + noOfLabSession + noOfLectureSession;
        } else {
            sal = (31) * 1250 + noOfLabSession + noOfLectureSession;
        }

        setSalary(sal);
        cout << "Your salary is: " << getSalary() << endl;
    }
};

int main() {
    vector<employee*> arr;
    employee* p = NULL;

    while (true) {
        cout << "0. EXIT" << endl;
        cout << "1. TO ADD HR EMPLOYEE" << endl;
        cout << "2. TO ADD TRAINING EMPLOYEE" << endl;
        int choice;
        cout << "ENTER YOUR CHOICE:" << endl;

        cin >> choice;
        switch (choice) {
        case 0:
            cout << "Exiting the program..." << endl;
            return 0;
        case 1:
            p = new HR();
            p->acceptEmployee();
            p->displayEmployee();
            try {
                p->calculateSalary();
            } catch (entryTypeException& e) {
                e.printStackTrace();
            }
            arr.push_back(p);
            break;
        case 2:
            p = new trainingEmployee(5, 3, "Company A", "John Doe", 3000, 2); // example args
            p->acceptEmployee();
            p->displayEmployee();
            try {
                p->calculateSalary();
            } catch (entryTypeException& e) {
                e.printStackTrace();
            }
            arr.push_back(p);
            break;
        default:
            cout << "You have entered a wrong choice!" << endl;
            break;
        }
    }
    return 0;
}
