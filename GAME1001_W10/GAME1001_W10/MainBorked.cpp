#include <iostream>
#include <string>
using namespace std;

class Employee
{
private:
	int m_empNumber;
	string m_name;
	double m_payRate;
	double m_hours;

public:
	string GetName(string name);
	double GetPayRate(double payRate);
	double GetHours(double hours);
	double GetWage();
	string PrintName();
};

string Employee::GetName(string name)
{
	m_name = name;
	return 0;
}
double Employee::GetPayRate(double payRate)
{
	m_payRate = payRate;
	return 0;
}
double Employee::GetHours(double hours)
{
	m_hours = hours;
	return 0;
}
double Employee::GetWage()
{
	return m_payRate * m_hours;
}
string Employee::PrintName()
{
	return m_name;
}

int main()
{
	Employee employee1;
	Employee employee2;
	string name;
	double pay;
	double hours;

	cout << "Employee 1" << endl;
	cout << "Please enter your name: ";
	cin >> name;
	employee1.GetName(name);
	cout << "Please enter your pay rate: ";
	cin >> pay;
	employee1.GetPayRate(pay);
	cout << "Please enter your hours worked: ";
	cin >> hours;
	employee1.GetHours(hours);

	cout << "\n\nEmployee 2" << endl;
	cout << "Please enter your name: ";
	cin >> name;
	employee2.GetName(name);
	cout << "Please enter your pay rate: ";
	cin >> pay;
	employee2.GetPayRate(pay);
	cout << "Please enter your hours worked: ";
	cin >> hours;
	employee2.GetHours(hours);

	if (employee1.GetWage() > employee2.GetWage())
	{
		cout << employee1.PrintName() << " has a higher wage than " << employee2.PrintName() << ": " << employee1.GetWage() << ' vs ' << employee2.GetWage() << endl;
	}
	else if (employee2.GetWage() > employee1.GetWage())
	{
		cout << employee2.PrintName() << " has a higher wage than " << employee1.PrintName() << ": " << employee2.GetWage() << ' vs ' << employee1.GetWage() << endl;
	}
	else
	{
		cout << employee2.PrintName() << " has the same wage as " << employee1.PrintName() << ": " << employee2.GetWage() << ' vs ' << employee1.GetWage() << endl;
	}


	system("pause");
	return 0;
}