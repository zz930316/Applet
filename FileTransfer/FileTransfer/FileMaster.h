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
	int EstablishTCP();//����tcp
	int EstablishUDP();//����udp
	void Display();		//��ʾ
	void Create_Thread();//�����߳�
	void CloseThread();//�ر��߳�
	void TransferFiles();		//�ļ�����tcp��
	void TransmitMessage();			//��Ϣ����udp��
	void Establish_IP_Address();	//�����Լ���ip�Ͷ˿�
	char* File_Storage_Path();//�����ļ����·��
protected:
	//char* Open_File( );//���ļ�
	void ConnectionObject(int type);//���ӶԷ�ip
	void FileTransfer_Underway();		//�ļ��������
	void ConnectTheClient();	//�Ѿ������Ͽͻ���
	void TransferMode(char *addr_C_addr, unsigned short *Port, SOCKET*sock);//ѡ���䷽ʽ
	void GetIP(char *addr_C_addr, unsigned short *Port);//����Ҫ���ӵ�ip�Ͷ˿�
	void GetIP(SOCKET*sock);//���������ӿͻ��˵�socket
	void View_New_Message();//�鿴������Ϣ
private:
	SOCKET fSeversocket;			//���������׽���

	vector<string> filequeue;
};
