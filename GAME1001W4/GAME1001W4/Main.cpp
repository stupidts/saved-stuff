#include <iostream>
#include <string>
using namespace std;

double TicketPrice(int choice, double basePrice);

int main(void)
{
	double ticketPrice = 20;
	cout << "1. Child  | <15 | \n2. Adult  |15-64| \n3. Senior | 65+ | \n4. Exit\n" << endl;
	int choice;
	cin >> choice;
	
	if (choice >= 1 && choice <= 3)
	{
		cout << "\nYour ticket price is $" << TicketPrice(choice, ticketPrice) << endl;
	}
	else
	{
		cout << "\nMaybe next time" << endl;
	}

	cout << "Have a nice day" << endl;
	system("pause");
	return 0;
}

double TicketPrice(int choice, double basePrice)
{
	if (choice == 1)
		return basePrice / 2;
	if (choice == 2)
		return basePrice;
	if (choice == 3)
		return basePrice * 0.8;
	else
		return -1;
}