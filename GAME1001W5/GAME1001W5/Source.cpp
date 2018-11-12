#include <iostream>
using namespace std;



int main(void)
{
	int number1, number2, sum = 0;
	cout << "Please enter a number: ";
	cin >> number1;
	cout << "Please enter another number: ";
	cin >> number2;
	int tempNum;
	tempNum = number1;

	if (number1 < 0)
	{
		number1 = -number1;
		tempNum = -tempNum;
	}
	if (number2 < 0)
	{
		number2 = -number2;
	}
	if (number2 < number1)
	{
		number1 = number2;
		number2 = tempNum;
	}
	for (int i = number1; i <= number2; i++)
	{
		sum += i;
	}

	cout << "The sum of the numbers between " << number1 << " and " << number2 << " is " << sum << endl;

	system("pause");
	return 0;
}