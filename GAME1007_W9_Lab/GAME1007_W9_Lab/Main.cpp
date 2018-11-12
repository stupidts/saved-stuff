#include <iostream>
using namespace std;

class Rectangle
{
private:
	double length;
	double width;
public:
	Rectangle()
	{
		width = 1;
		length = 1;
	}
	Rectangle(double l, double w)
	{
		width = w;
		length = l;
	}

	bool setLength(double length);
	bool setWidth(double width);
	double getLength();
	double getWidth();
	double getArea();
	double getPerimeter();
};

bool Rectangle::setLength(double len)
{
	bool validData = true;

	if (len >= 0)               // If the len is valid
		length = len;            // copy it to length
	else
		validData = false;       // else leave length unchanged

	return validData;
}
bool Rectangle::setWidth(double w)
{
	bool validData = true;

	if (w >= 0)                 // If w is valid
		width = w;               // copy it to width
	else
		validData = false;       // else leave width unchanged

	return validData;
}
double Rectangle::getLength()
{
	return length;
}
double Rectangle::getWidth()
{
	return width;
}
double Rectangle::getArea()
{
	return length * width;
}
double Rectangle::getPerimeter()
{
	return 2 * (length + width);
}


int main()
{
	Rectangle rect1;
	Rectangle rect2(5,8);
	double length;
	double width;


	cout << "The area of rectangle 1 is " << rect1.getArea() << " units squared" << endl;
	cout << "The perimeter of rectangle 1 is " << rect1.getPerimeter() << " units" << endl;

	cout << "The area of rectangle 2 is " << rect2.getArea() << " units squared" << endl;
	cout << "The perimeter of rectangle 2 is " << rect2.getPerimeter() << " units" << endl;

	system("pause");
	return 0;
}