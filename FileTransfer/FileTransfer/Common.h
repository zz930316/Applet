#pragma once
/********************************************************************
����:	2017/12/5
�ļ���:	Common.h

��;:	���ļ�Ϊ������Ŀ��Ҫ�õ��Ĺ����ļ�
*********************************************************************/


#include <iostream>
using namespace std;
#include <winsock2.h>
#include <time.h>
#include <mutex>


#pragma comment(lib, "ws2_32.lib")
const USHORT semaphore = 1;


/* ����˶˿ں� */
const unsigned short TCP_PORT = 5555;   // �����ļ�����
const unsigned short TCP_SEND = 9998;   // �����ļ�����

const unsigned short UDP_PORT = 7777;   // ������Ϣ����
const unsigned short UDP_SEND = 9999;   // ������Ϣ����

extern HANDLE hSemp1, hSemp2, hSemp3, hSemp4;	// HANDLE   ����������ַ����˼
extern HANDLE fileLock, queueLock;//���������

/*�����ļ����ݴ�С*/
const ULONG SND_BUF_SIZE = 96 * 1024 * 1024;
const ULONG RCV_BUF_SIZE = 96 * 1024 * 1024;
const ULONG Content = 100 * 1024;   // 

			/* ��ſͻ�����Ϣ */							
struct ClientInfo
{
	SOCKET fSocket;			//socket
	SOCKADDR_IN fAddress;	//�ͻ���ip��˿�
	string fArriveTime;		//�ͻ�������ʱ��
};

		/*���TCP�����ļ�����Ϣ*/
struct FileSize
{
	SOCKET sock;//Ҫ���͵ĶԷ�
	/*const */char filename[MAX_PATH];//�ļ���
	SOCKADDR_IN Sentaddr;//����ip�˿�
	ULONG num;//�ܴ���
	ULONG fileContentSize;
	char fileContent[Content];	//����
};


/*UDP���յ�����*/
struct UDPcontent
{
	char addr[20];//�����˵�ip���˿�
	char sDateTime[30];//����ʱ��
	char buffer[1500];//������Ϣ
};


void Semagphore();//�����ź���

// ReceivesConnection  ���������߳�, Sendmessage  ������Ϣ, Recvmessage  ������Ϣ, SendFile  �����ļ�,
// RecvFile  �����ļ�, FilePackage  �ļ����, FileUnpack  �ļ����;
DWORD WINAPI ReceivesConnection(LPVOID pM);//���������߳�

DWORD WINAPI Sendmessage(LPVOID pM);//������Ϣ

DWORD WINAPI Recvmessage(LPVOID pM);//������Ϣ

DWORD WINAPI SendFile(LPVOID pM);//�����ļ�

DWORD WINAPI RecvFile(LPVOID pM);//�����ļ�

DWORD WINAPI FilePackage(LPVOID pM);//�ļ����

DWORD WINAPI FileUnpack(LPVOID pM);//�ļ����

const char * Get_File_Name(char *name);//��ȡ�ļ���

void gotoy(int x, int y);

void Reset();