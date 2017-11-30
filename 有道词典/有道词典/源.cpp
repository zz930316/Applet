#include <iostream>
#include "YoudaoDict.h"
#include <windows.h>
#include <time.h>
using namespace std;

void main()
{
	srand(time(0));
	while (1)
	{
		Sleep(1000);
		//cout << "[" << rand()%10 << "," << rand() % 10 << "]" << endl;
		cout << time(0) << endl;
	}
	YoudaoDict you;
	you.MainMenu();
}