#include "FileMaster.h"
#include <iostream>
#include <windows.h>
#include <time.h>
using namespace std;

//queue<int*> g_intQueue;

int main()
{
// 	WSADATA wsaData;
// 	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
// 		printf("[error] WSAStartup error!\n");
	WSADATA wsd;
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)//WSAStartup的功能是初始化Winsock DLL，
	{
		cout << "WSAStartup failed!" << endl;
	}
	FileMaster fileMaster;
	fileMaster.EstablishTCP();
	fileMaster.EstablishUDP();
	fileMaster.Display();
	system("pause");
	return 0;
}