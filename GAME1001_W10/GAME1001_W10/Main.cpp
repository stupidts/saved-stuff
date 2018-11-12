#include <iostream>
#include <string>
using namespace std;

class Employee
{
private:
	int m_empNum;
	string m_name;
	double m_pay;
	double m_hours;
public:
	Employee()
	{
		m_empNum = 0;
		m_name = "No Name";
		m_pay = 0;
		m_hours = 0;
	}
	Employee(int en, string n, double p, double h)
	{
		m_empNum = en;
		m_name = n;
		m_pay = p;
		m_hours = h;
	}

	void setPay(double pay);
	void setHours(double hours);
	void setName(string name);
	void setEmpNum(int empNum);
	double getWage();
	string getEmpData();
};

void Employee::setPay(double pay)
{
	m_pay = pay;
}
void Employee::setHours(double hours)
{
	m_hours = hours;
}
void Employee::setName(string name)
{
	m_name = name;
}
void Employee::setEmpNum(int empNum)
{
	m_empNum = empNum;
}
double Employee::getWage()
{
	return m_pay * m_hours;
}
string Employee::getEmpData()
{
	string data =  "\nID Number ====> " + to_string(m_empNum);
		   data += "\nName =========> " + m_name;
		   data += "\nPay Rate =====> " + to_string(m_pay);
		   data += "\nHours Worked => " + to_string(m_hours);
		   data += "\nTotal Wage ===> " + to_string(getWage());
	return data;
}


int main()
{
	Employee emp1;
	Employee emp2(1,"John",30,20);
	int empNum;
	string name;
	double pay;
	double hours;

	cout << "Please enter your ID: ";
	cin >> empNum;
	emp1.setEmpNum(empNum);
	cout << "Please enter your name: ";
	cin >> name;
	emp1.setName(name);
	cout << "Please enter your pay rate: ";
	cin >> pay;
	emp1.setPay(pay);
	cout << "Please enter your hours worked: ";
	cin >> hours;
	emp1.setHours(hours);

	cout << emp2.getEmpData() << endl;
	cout << emp1.getEmpData() << endl;

	if (emp2.getWage() > emp1.getWage())
	{
		cout << "\n\nv This employee has a higher wage v" << endl;
		cout << emp2.getEmpData() << endl;
	}
	else if (emp1.getWage() > emp2.getWage())
	{
		cout << "\n\nv This employee has a higher wage v" << endl;
		cout << emp1.getEmpData() << endl;
	}
	else
	{
		cout << "Both employees made the same money" << endl;
	}

	system("pause");
	return 0;
}