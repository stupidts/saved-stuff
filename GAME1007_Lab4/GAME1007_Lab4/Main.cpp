#include <iostream>
#include "Weapon.h"
using namespace std;

int main()
{
	Weapon pistol; // Creating object with default constructor.
	Weapon shotgun("Remington 870 Marine Magnum", 899.99, "Boom-chk-chk!"); // Creating with non-default constructor.
	shotgun.SetOwned(true); // Calling the setter of the object.
	cout << "You're using a " << shotgun.GetName() << ", that goes: ";
	shotgun.Use();
	system("pause");
	return 0;
}