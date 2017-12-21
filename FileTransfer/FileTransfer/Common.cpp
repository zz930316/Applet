#include "Common.h"
#include "TCPTransfer.h"
#include "UDPTransfer.h"
#include <queue>
#include <map>

map<SOCKET, ClientInfo> fmap_Clien;		//��ſͻ���������Ϣ
SYSTEMTIME ftime;				//����ṹ�����꣬�£��գ����ڣ�ʱ���֣��룬�����;

HANDLE Thread[7] = { 0 };			//�߳���

TCPTransfer fTCPTransfer;
UDPTransfer fUDPTransfer;
/*char * addr_C_addr = {0};*/
ULONG retVal_r = 0;
float process;		//��ʾ��ǰ�������
ClientInfo clientInfo;
FileSize filesize, rfilesize;
queue<FileSize*> send_information_que, recv_information_que;//��ŷ��͵ĺͽ��յ��ļ���Ϣ����
queue<UDPcontent> information_UDP;//���UDP���յ���Ϣ����

	  // HANDLE   ����������ַ����˼

HANDLE fileLock,queueLock;//���������

HANDLE hSemp1, hSemp2, hSemp3, hSemp4;	// �ź������

void Semagphore()
{

	//����һ����
	fileLock = CreateMutex(NULL, FALSE, NULL);
	queueLock = CreateMutex(NULL, FALSE, NULL);
	hSemp1 = CreateSemaphore(NULL, semaphore, semaphore, NULL);//����ļ�
	hSemp2 = CreateSemaphore(NULL, 0, semaphore, NULL);//�����ļ�

	hSemp3 = CreateSemaphore(NULL, semaphore, semaphore, NULL);////�����ļ�
	hSemp4 = CreateSemaphore(NULL, 0, semaphore, NULL);//����ļ�

}

const char * Get_File_Name(char *name)
{
	char fname[MAX_PATH];
	memset(&fname, 0, sizeof(fname));
	string path = name;
	int pos = path.find_last_of('\\');
	string sz_path;
	if (pos != -1)
	{
		sz_path = std::string(path.substr(pos + 1));
		strcpy(fname, sz_path.c_str());
		return fname;
	}
	else
	{
		pos = path.find_last_of('/');
		sz_path = std::string(path.substr(pos + 1));
	}
	return sz_path.c_str();
}

void gotoy(int x, int y)
{
	COORD coo;
	coo.X = x;
	coo.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coo);
}

void Reset()
{
	retVal_r = 0;
	process = 0.0;	//��ʾ��ǰ�������
	memset(&Thread, 0, sizeof(Thread));
	memset(&clientInfo, 0, sizeof(clientInfo));
	memset(&filesize, 0, sizeof(filesize));
	memset(&rfilesize, 0, sizeof(rfilesize));
	memset(&ftime, 0, sizeof(ftime));
	memset(&clientInfo, 0, sizeof(clientInfo));
}

