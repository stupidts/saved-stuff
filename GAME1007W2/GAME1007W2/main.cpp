#include <iostream>
using namespace std;

double Sum (double num1, double num2, double num3);
double Prod(double num1, double num2, double num3);
double Avg (double num1, double num2, double num3);
double Pwr (double base, int    power);

int main()
{
	double num1, num2, num3;

	cout << "Enter number 1: ";
	cin >> num1;

	cout << "Enter number 2: ";
	cin >> num2;

	cout << "Enter number 3: ";
	cin >> num3;

	cout << "The sum of "     << num1 << " + " << num2 << " + " << num3 << " is " << Sum (num1, num2, num3) << endl;
	cout << "The product of " << num1 << " * " << num2 << " * " << num3 << " is " << Prod(num1, num2, num3) << endl;
	cout << "The average of " << num1 << " + " << num2 << " + " << num3 << " is " << Avg (num1, num2, num3) << endl;
	

	double base;
	int power;
	cout << "\n\nPlease enter a base number: ";
	cin >> base;
	cout << "Please enter a power number: ";
	cin >> power;
	cout << base << " to the power of " << power << " is " << Pwr(base, power) << endl;

	system("pause");
	return 0;
}

double Sum(double num1, double num2, double num3)
{
	return num1 + num2 + num3;
}

double Prod(double num1, double num2, double num3)
{
	return num1 * num2 * num3;
}

double Avg(double num1, double num2, double num3)
{
	return (num1 + num2 + num3) / 3;
}

double Pwr(double base, int power)
{
	double sum = 1;
	for (int i = 1; i <= power; i++)
	{
		sum *= base;
	}
	return sum;
}