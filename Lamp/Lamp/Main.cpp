#include <iostream>
#include "Lamp.h"
using namespace std;

int main()
{
	Lamp lamp1;
	Lamp lamp2(90, 7.8, 200);

	cout << "Your lamp of selection has these stats:\n\n" << endl;
	lamp2.TurnOn();
	lamp2.GetLamp();

	system("pause");
	return 0;
}