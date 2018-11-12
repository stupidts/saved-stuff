#include <iostream>
#include <string>
#include <ctime>
using namespace std;

// 0 = water, 1 = ship piece, 2 = miss, 3 = hit
// have to hard code ships in just to get the basics down first

//Player Board
int Row0[10]  = { 0,0,0,0,0,0,0,0,0,0 };
int Row1[10]  = { 0,0,0,0,0,1,1,1,0,0 };
int Row2[10]  = { 0,0,1,0,0,0,0,0,0,0 };
int Row3[10]  = { 0,0,1,0,0,0,0,1,0,0 };
int Row4[10]  = { 0,0,1,0,0,0,0,1,0,0 };
int Row5[10]  = { 0,0,0,1,1,1,1,1,0,0 };
int Row6[10]  = { 0,0,0,0,0,0,0,1,0,0 };
int Row7[10]  = { 0,0,0,0,0,0,0,1,0,0 };
int Row8[10]  = { 0,0,0,0,0,0,0,0,0,0 };
int Row9[10]  = { 0,0,1,1,0,0,0,0,0,0 };
//CPU Board
int CRow0[10] = { 0,0,0,0,0,0,1,1,1,0 };
int CRow1[10] = { 0,0,0,0,0,0,0,0,0,0 };
int CRow2[10] = { 0,0,1,1,1,1,1,0,0,0 };
int CRow3[10] = { 0,0,0,0,0,0,0,0,0,0 };
int CRow4[10] = { 0,0,0,0,0,0,1,1,0,0 };
int CRow5[10] = { 0,0,1,0,0,0,1,0,0,0 };
int CRow6[10] = { 0,0,1,0,0,0,1,0,0,0 };
int CRow7[10] = { 0,0,1,0,0,0,1,0,0,0 };
int CRow8[10] = { 0,0,0,0,0,0,1,0,0,0 };
int CRow9[10] = { 0,0,0,0,0,0,0,0,0,0 };


void PlayerBoard()
{
	cout << Row0[1] << Row0[2] << Row0[3] << Row0[4] << Row0[5] << Row0[6] << Row0[7] << Row0[8] << Row0[9] << Row0[10];
}

int main(void)
{
	



	system("pause");
	return 0;
}