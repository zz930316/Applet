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
	//�������folat�ͺ�double�������ʽΪС���������С��λΪ1
	cout.precision(1); 
	cout.setf(ios::fixed);
	ms.MainMenu();
	return 0;
}