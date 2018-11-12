#include <iostream>
using namespace std;

//add inputs for multiple class members
//total the class average and grade

int calcFinal(double FinalMark, double marksAdded)
{
	FinalMark = FinalMark / marksAdded;
	if (FinalMark >= 90)
	{
		cout << "Your Average is " << FinalMark << "% which is an A+! Good Job!\n" << endl;
	}
	else if (FinalMark >= 80 && FinalMark < 90)
	{
		cout << "Your Average is " << FinalMark << "% which is an A!\n" << endl;
	}
	else if (FinalMark >= 70 && FinalMark < 80)
	{
		cout << "Your Average is " << FinalMark << "% which is a B!\n" << endl;
	}
	else if (FinalMark >= 60 && FinalMark < 70)
	{
		cout << "Your Average is " << FinalMark << "% which is a C!\n" << endl;
	}
	else if (FinalMark >= 50 && FinalMark < 60)
	{
		cout << "Your Average is " << FinalMark << "% which is a D!\n" << endl;
	}
	else
	{
		cout << "Your Average is " << FinalMark << "% which is an F! You Failed!\n" << endl;
	}
	return 0;
}

int main(void)
{
	double MarkFinalExam;
	double MarkMidTerm;
	double MarkLabs;
	double MarkAssign1;
	double MarkAssign2;

	double FinalMark = 0;
	bool keepGrading = true;
	int marksAdded = 0;      // this is how many student marks were added

	while (keepGrading)
	{
		cout << "Please enter marks for student " << marksAdded + 1 << endl;
		//resets the grades
		MarkAssign1 = 0;
		MarkAssign2 = 0;
		MarkMidTerm = 0;
		MarkLabs = 0;
		MarkFinalExam = 0;

		cout << "What mark did you get on Assignment 1? ";
		cin >> MarkAssign1;
		cout << "What mark did you get on Assignment 2? ";
		cin >> MarkAssign2;
		cout << "What mark did you get on Labs? ";
		cin >> MarkLabs;
		cout << "What mark did you get on Mid Term? ";
		cin >> MarkMidTerm;
		cout << "What mark did you get on Final Exam? ";
		cin >> MarkFinalExam;

		//Makes sure you can't get over 100% on something
		if (MarkAssign1 > 100) MarkAssign1 = 100;
		if (MarkAssign2 > 100) MarkAssign2 = 100;
		if (MarkLabs > 100) MarkLabs = 100;
		if (MarkMidTerm > 100) MarkMidTerm = 100;
		if (MarkFinalExam > 100) MarkFinalExam = 100;


		++marksAdded;
		FinalMark += (MarkAssign1 * 0.1 + MarkAssign2 * 0.2 + MarkLabs * 0.2 + MarkMidTerm * 0.2 + MarkFinalExam * 0.3);
		calcFinal(FinalMark, marksAdded);

		cout << "Would you like to add another students marks?\n1 Yes\n2 No" << endl;
		int choice;
		cin >> choice;
		switch (choice)
		{
		case (1):
			keepGrading = true;
			break;
		case (2):
			keepGrading = false;
			break;
		default:
			break;
		}
	}


	calcFinal(FinalMark, marksAdded);

	system("pause");
	return 0;
}