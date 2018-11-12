#pragma once
#include <iostream>
#include <string>
using namespace std;

class Weapon {

private:
	bool m_owned;
	int m_cost;
	string m_name;
	string m_sound;

public:
	void SetSound(string s)
	{
		m_sound = s;
	}
	void Use()
	{
		cout << m_sound << endl;
	}

};