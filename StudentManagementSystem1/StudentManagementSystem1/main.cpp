 #include <iostream>
#include "StudentManagementSystem.h"
using namespace std;

struct Stu
{
	Stu() 
	{
		ptr = new char[10];
	}
	~Stu()
	{
		delete[]ptr;
	}
	char *ptr;
};

int main()
{
	StudentManagementSystem ms;
	//设置输出folat型和double型输出格式为小数点输出，小数位为1
	cout.precision(1); 
	cout.setf(ios::fixed);
	ms.MainMenu();
	return 0;
}