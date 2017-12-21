#pragma once

#include "Common.h"
#include "TCPTransfer.h"
#include "UDPTransfer.h"
#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <fstream>
#include <vector>
#include <queue>
#include<stdio.h>
#include <corecrt_wstdio.h>
using namespace std;

class FileMaster
{

public:

	FileMaster();
	~FileMaster();
	int EstablishTCP();//建立tcp
	int EstablishUDP();//建立udp
	void Display();		//显示
	void Create_Thread();//创建线程
	void CloseThread();//关闭线程
	void TransferFiles();		//文件传输tcp传
	void TransmitMessage();			//消息传输udp传
	void Establish_IP_Address();	//创建自己的ip和端口
	char* File_Storage_Path();//设置文件存放路径
protected:
	//char* Open_File( );//打开文件
	void ConnectionObject(int type);//连接对方ip
	void FileTransfer_Underway();		//文件传输进程
	void ConnectTheClient();	//已经连接上客户端
	void TransferMode(char *addr_C_addr, unsigned short *Port, SOCKET*sock);//选择传输方式
	void GetIP(char *addr_C_addr, unsigned short *Port);//输入要连接的ip和端口
	void GetIP(SOCKET*sock);//输入已连接客户端的socket
	void View_New_Message();//查看最新消息
private:
	SOCKET fSeversocket;			//服务器的套接字

	vector<string> filequeue;
};
