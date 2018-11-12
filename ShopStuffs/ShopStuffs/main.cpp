#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//5 items to put into shop stored at C://Temp/Items.txt

int main(void)
{
	string item;
	string price;
	bool loop = true;

	while (loop)
	{
		cout << "Would you like to make a shop or view a shop?\n1 Make\n2 View\n3 Quit" << endl;
		int choice;
		cin >> choice;
		if (choice == 1)
		{
			ofstream itemOut;
			ofstream priceOut;
			cout << "Please enter your 5 items to put in your shop. [No Spaces]" << endl;
			itemOut.open("C:\\Temp\\Items.txt");
			priceOut.open("C:\\Temp\\Price.txt");
			for (int i = 1; i < 6; i++)
			{
				cout << "Item " << i << ": ";
				cin >> item;
				itemOut << item << endl;
				cout << "Price " << i << ": ";
				cin >> price;
				priceOut << price << endl;
			}
			itemOut.close();
			priceOut.close();
		}
		else if (choice == 2)
		{
			ifstream itemIn;
			ifstream priceIn;
			fstream  receipt;
			cout << "Here are the shop items:" << endl;
			itemIn.open("C:\\Temp\\Items.txt");
			priceIn.open("C:\\Temp\\Price.txt");
			receipt.open("C:\\Temp\\Receipt.txt");
			for (int i = 1; i < 6; i++)
			{
				itemIn >> item;
				priceIn >> price;
				cout << item << ": " << price << endl;
			}
			cout << "\nWould you like to buy anything?\n1 Yes\n2 No" << endl;
			for (int i = 1; i < 6; i++)
			{
				cout << item << ": " << price << ". How many would you like? " << endl;
				
			}
		}
		else
		{
			loop = false;
		}
	}
	system("pause");
	return 0;
}