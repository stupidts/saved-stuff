#include <iostream>
using namespace std;

int main()
{
	int *pointer;
	int x = 100, y = 20;

	pointer = &x;

	cout << *pointer << " " << x << " " << y << endl;

	*pointer = 20;

	cout << *pointer << " " << x << " " << y << endl;

	*pointer *= 20;

	cout << *pointer << " " << x << " " << y << endl;

	system("pause");
	return 0;
}