#pragma once
#include <iostream>
using namespace std;

class Lamp
{
private:
	bool m_on;
	int m_brightness;
	double m_height;
	int m_attraction; // how much insects are attracted to this lamp
public:
	Lamp()
	{
		cout << "Creating lamp!" << endl;
	}
	Lamp(double brightness, double height, int attraction)
	{
		m_brightness = brightness;
		m_height = height;
		m_attraction = attraction;
		cout << "Creating lamp!" << endl;
	}

	void GetLamp()
	{
		cout << "The lamp is : " << (m_on == false ? "off" : "on") << ", the brightness is: " << m_brightness << "%, the lamps height is: " << m_height << "ft tall, the attraction level of the lamp is: " << m_attraction << "%." << endl;
	}

	void TurnOn()
	{
		m_on = true;
	}
};