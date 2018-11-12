#include <iostream>
#include <string>
#include <ctime>
using namespace std;


//Object type
//assigned to 1-9 minimum 5
//Objects properties will be stored in arrays
//--string name
//--double cost
//--int number of uses
//--string description
//--Other possibilities
//----quality modifier, increasing some property
//----durability
//----level requirement
//----cooldown


int shop()
{
	int spellCost = 50;
	int spellCosts[5] = { 50, 100, 120, 150, 180 };
	spellCosts[5] = 200;//this is how to set an array value
	cout << spellCosts[2] << endl;//This is accessing the 2nd index which is the third element
	return 0;
}

int main(void)
{
	shop();
	srand((unsigned)time(0));
	// Random number from 152 to 667 inclusive
	// min + rand() % ((max-min) + 1)

	cout << 152 + rand() % ((667 - 152) + 1) << endl;
	cout << 7 + rand() % ((24 - 7) + 1) << endl;
	cout << 1 + rand() % (100) << endl;

	system("pause");
	return 0;
}