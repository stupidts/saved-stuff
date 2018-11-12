#pragma once
#include <string>
#include <iostream>
#define ABIL_PLR 4
using namespace std;

/* Structs and classes are nearly identical ways to group variables and functions
together to create a template for what becomes an object. The class/struct's name,
e.g. 'Ability', becomes like a data type and we can declare variables of this new
type, e.g. Ability myAbility; and 'myAbility' is what's called an object. We then use
the member access, a.k.a. dot operator (.) to access the members of the object, thus:
myAbilty.name = "Kamehameha"; and member functions are called similarly, thus:
myAbility.AdvCooldown(); */

struct Ability /* In a struct, all members are public by default. Public means we can
			   access the member through the dot operator. Otherwise we can't. */
{
	/* Member attributes initialized from file. */
	string name;
	short damage;
	short critChance; /* I should have just made the critChance the d20 number to meet or beat. Oh well.*/
	bool autohit;
	short cooldown;
	short currEff[4]; /* Current round effects. */
	short nextEff[4]; /* Effects applied until the end of a players' next turn. */

	short cdTimer = 0; /* Use of in-class initializers (C++11). Many code standards
					   say this is a no-no. But I'm showing it to you for now. */
	bool onCooldown = false;
	bool selected = false;

	void AdvCooldown()
	{
		if (onCooldown)
		{
			cdTimer--;
			if (cdTimer == 0)
			{
				onCooldown = false;
				selected = true; /* Once the game starts, I used selected to show
								 if the ability is available to use */
			}
		}
	}
	void SetCooldown()
	{
		if (cooldown > 0)
		{
			onCooldown = true;
			selected = false;
			cdTimer = cooldown;
		}
	}
};

class Player /* In a class, all members are private by default meaning we can't use the dot
			 operator to access a member. This allows us to keep our private members 'safe'
			 and provide a public member function only if access to them is required. */
{
	string name;
	short health = 100; /* More in-class initializers here. */
	short bonuses[4] = { 0 }; /* Attack bonus, defense bonus, damage bonus, health bonus. */
	Ability abilities[ABIL_PLR]; /* Array holding the four abilities the player can use. */

public: /* We can add a heading, thus, to specify an access type other than the default. */
		/* All these that follow are member functions, often called methods. */
	string GetName() { return name; }
	short GetHealth() { return health; }
	Ability* GetAbilities() { return abilities; }
	short GetDefense() { return 10 + bonuses[1]; }
	void SetName(const string n) { name = n; }
	void SetAbility(Ability a, short i) { abilities[i] = a; }
	void SetBonuses(short* e)
	{
		for (int i = 0; i < 4; i++)
			bonuses[i] = e[i];
	}
	void SetHealth(short m)
	{
		health += m;
		health = (health > 100 ? 100 : (health < 0 ? 0 : health));
	}
	void ResetBonuses()
	{
		for (int i = 0; i < 4; i++)
			bonuses[i] = 0;
	}
	void PrintStats()
	{
		cout << name << "'s Stats\nHealth: " << health << "  Atk Bonus: " << bonuses[0]
			<< "  Def Bonus: " << bonuses[1] << "  Dmg Bonus: " << bonuses[2] << endl;
	}
	/* The jacked boi attack function. And the second part of this test. */
	bool DoAttack(Player& target) /* We are passing in a reference to the other player we are attacking. */
	{
		char opt;
		int atkRoll = 0, defRoll = 0, dmgRoll = 0, aIndex;

		Player player;
		player.PrintStats();
		while (true)
		{
			cout << "Use ability\nPunch\nHaymaker\nUppercut\nJab" << endl;
			cin.get(opt);
			cin.ignore(INT_MAX, '\n');
			aIndex = opt - 48;
			if (!(aIndex >= 0 && aIndex < ABIL_PLR))
			{
				cout << "That number is invalid!" << endl;
				continue;
			}
			else if (abilities[aIndex].onCooldown == true) /* abilities[aIndex] represents the current ability used. */
			{
				cout << "That ability is on cooldown! Try again later" << endl;
				continue;
			}
			else
				break;
		}
		SetBonuses(abilities[aIndex].currEff);
		cout << name << " uses " << abilities[aIndex].name; /* This outputs that the current player uses the current ability. */
		if (abilities[aIndex].autohit == false)
		{
			atkRoll = (1 + rand() % 20) + bonuses[0];
			defRoll = target.GetDefense();
			if (atkRoll >= defRoll)
				cout << " and hits ";
			else
				cout << " and misses ";
			cout << '(' << atkRoll << " vs " << defRoll << ")";
		}
		if (abilities[aIndex].damage > 0 && atkRoll >= defRoll)
		{
			for (int i = 0; i < abilities[aIndex].damage; i++)
			{
				dmgRoll += 1 + rand() % 6;
				dmgRoll += bonuses[2];
			}
			int critRoll = 20 - (20.0 * abilities[aIndex].critChance / 100.0); /* Which set of parenthesis do I not need? */
			if (atkRoll >= critRoll)
			{
				dmgRoll *= 2;
			}
			cout << " for " << dmgRoll << (atkRoll >= critRoll ? " critical " : " ") << "damage";
		}
		cout << '!' << endl; /* The enemy has been alerted to your presence, Snake. */
		SetHealth(bonuses[3]);
		target.SetHealth(-dmgRoll); /* Here we are essentially decrementing the target's health by dmgRoll. */
		cout << name << "'s health: " << health << ". " << target.GetName() << "'s health: " << target.GetHealth() << '.' << endl;
		if (target.GetHealth() == 0)
		{
			return 1;
		}
		ResetBonuses();
		SetBonuses(abilities[aIndex].nextEff);
		for (int i = 0; i < ABIL_PLR; i++)
		{
			if (i == aIndex)
				abilities[i].SetCooldown();
			else
				abilities[i].AdvCooldown();
		}
		return 0;
	}
};