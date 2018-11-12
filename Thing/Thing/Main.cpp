#include <iostream>
#include "Class.h"
using namespace std;

int main()
{
	Lamp lamp1(true, 2.3, 3, 100);
	Lamp* lamp2;
	lamp1.PrintLamp();
	lamp2 = new Lamp(false, 5, 12, 100);
	lamp2->PrintLamp();

	int numLamps;
	cout << "How many lamps do you want to make? ";
	cin >> numLamps;
	Lamp* lArray;
	lArray = new Lamp[numLamps];
	system("pause");
	return 0;
}