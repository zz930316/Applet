
#pragma once
#include <iostream>
#include <string>
#include <map>
#include <winsock2.h>  
#include "Common.h"
#include <queue>
#include <fstream>
#pragma comment(lib,"ws2_32.lib")  
using namespace std;

/* TCPServer����� */
class TCPTransfer
{
public:
	enum  Establish { kBlocking, kNonBlocking }; //��������
// 	enum { kMaxSendBufSize = 96u * 1024u, kMaxRecvBufSize = 96u * 1024u };
// 	enum { kMaxTCPPacketSize = 5 };//�����Ϣ�ڴ��С

	TCPTransfer();
	~TCPTransfer();

	bool SetIOType(int inIOType);	//��������
	UINT_PTR Open();	//��
	bool Close();	//�ر�
	SOCKET Connect(char * ,USHORT);//���ӷ�����
	SOCKET Connect(SOCKET);//ͨ��socket����
	int Listen(const unsigned short& inPort);	//����	
	int Send(FileSize*);//������Ϣ
//	char * Recv(const SOCKET*,int *);		//������Ϣ
	FileSize * Recv(const SOCKET*, int *);		//�����ļ�

	int Accept(ClientInfo);//���տͻ�������	

private:
	//SOCKET fclient;
	SOCKET fSeversocket;			//���������׽���
	sockaddr_in addrServ;//�����洢��ַ�Ͷ˿ڵĽṹ��
	SOCKET sockClient;//�ͻ����׽���
};