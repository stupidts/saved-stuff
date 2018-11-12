#pragma once
#include <iostream>
#include <string>
using namespace std;

class Weapon
{
private: // This 'private:' heading is optional as members are private by default.
	bool m_owned;
	float m_cost;
	string m_name;
	string m_sound;
public:
	Weapon() // Default constructor.
	{
		cout << "Calling default constructor..." << endl;
	}
	Weapon(string name, float cost, string sound) // Non-default or parameterized constructor.
	{
		cout << "Calling non-default constructor..." << endl;
		m_name = name; // We can re-write these three following lines in the header with 
		m_cost = cost; // an initializer list but I'll show you this method another time.
		m_sound = sound;
	}
	~Weapon() {} // Destructor. Don't need unless there's dynamic memory used.
	string& GetName() // Example of a getter.
	{
		return m_name;
	}
	void SetOwned(bool o) // Example of a setter.
	{
		m_owned = o;
	}
	void Use() // A custom method.
	{
		cout << m_sound << endl;
	}
};