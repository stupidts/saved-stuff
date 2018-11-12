#pragma once

#ifndef CLASS_H
#define CLASS_H

/* 
// used to 
struct structure name
{
	type1 field1;
	type2 field2;
	typen fieldn;
};
*/

/*
example
// Does not allocate memory or create variables
// Use the . operator to refer to the data members of structs
// Student s1;
// cout << s1.studentName << endl;
// You cannot initialize any data in a struct or it will give an error (doesn't allocate memory)

// Student stu = {"bert", 12};
// structs can use other structs inside as a member
struct Student // usually starts with Capital
{
	string studentName;
	int studentID;
	etc.
};
*/

class Class
{
private:

public:
	Class() {} // Constructor
	~Class() {}// Destructor

	void functionOne() {}// This is an inline function
};

class Thing
{
public:
	Thing() {}
	~Thing() {} // Destructor



	/*const GetStuff()
	{

	}*/
};

#endif