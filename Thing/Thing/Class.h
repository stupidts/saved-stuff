#pragma once
#include <iostream>
using namespace std;

class Lamp
{
private:
	bool m_on;
	double m_brightness;
	double m_height;
	double m_durability;
public:
	Lamp(bool on, double bright = 1, double height = 1, double durability = 100) : m_on(on), m_brightness(bright),
		m_height(height), m_durability(durability)
	{
		cout << "Making a lamp!" << endl;
	}

	void PrintLamp()
	{
		cout << m_on << ", " << m_brightness << ", " << m_height << ", " << m_durability << endl;
	}
};