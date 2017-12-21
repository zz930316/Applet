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
	void Bind(const USHORT& inPort);//��
	UINT_PTR Connect_U(char *addr, USHORT port);//
	int SendTo();
	int RecvFrom();
private:
	SOCKET fUDPSeversocket;			//���������׽���
	sockaddr_in addrUDPServ;//�����洢��ַ�Ͷ˿ڵĽṹ��
	SOCKET sockClient;
	SOCKADDR_IN addrSrv;
};

