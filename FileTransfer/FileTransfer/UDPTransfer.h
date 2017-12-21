#pragma once


#include <iostream>
#include <string>
#include <winsock2.h>  
#include "Common.h"
#include <queue>
#pragma comment(lib,"ws2_32.lib")  
using namespace std;

class UDPTransfer
{
public:
	enum   { kMaxUDPPacket = 1500 };
	UDPTransfer(/* int inSocketID= kInvalidSocketID*/);
	~UDPTransfer();
	
	void Open();
	void Bind(const USHORT& inPort);//绑定
	UINT_PTR Connect_U(char *addr, USHORT port);//
	int SendTo();
	int RecvFrom();
private:
	SOCKET fUDPSeversocket;			//服务器的套接字
	sockaddr_in addrUDPServ;//创建存储地址和端口的结构体
	SOCKET sockClient;
	SOCKADDR_IN addrSrv;
};

