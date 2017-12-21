#include "Common.h"
#include "TCPTransfer.h"
#include "UDPTransfer.h"
#include <queue>
#include <map>

map<SOCKET, ClientInfo> fmap_Clien;		//存放客户端连接信息
SYSTEMTIME ftime;				//这个结构体存放年，月，日，星期，时，分，秒，毫秒等;

HANDLE Thread[7] = { 0 };			//线程数

TCPTransfer fTCPTransfer;
UDPTransfer fUDPTransfer;
/*char * addr_C_addr = {0};*/
ULONG retVal_r = 0;
float process;		//显示当前传输进度
ClientInfo clientInfo;
FileSize filesize, rfilesize;
queue<FileSize*> send_information_que, recv_information_que;//存放发送的和接收的文件信息队列
queue<UDPcontent> information_UDP;//存放UDP接收的消息队列

	  // HANDLE   句柄，保存地址的意思

HANDLE fileLock,queueLock;//互斥锁句柄

HANDLE hSemp1, hSemp2, hSemp3, hSemp4;	// 信号量句柄

void Semagphore()
{

	//创建一个锁
	fileLock = CreateMutex(NULL, FALSE, NULL);
	queueLock = CreateMutex(NULL, FALSE, NULL);
	hSemp1 = CreateSemaphore(NULL, semaphore, semaphore, NULL);//打包文件
	hSemp2 = CreateSemaphore(NULL, 0, semaphore, NULL);//发送文件

	hSemp3 = CreateSemaphore(NULL, semaphore, semaphore, NULL);////接收文件
	hSemp4 = CreateSemaphore(NULL, 0, semaphore, NULL);//解包文件

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
	process = 0.0;	//显示当前传输进度
	memset(&Thread, 0, sizeof(Thread));
	memset(&clientInfo, 0, sizeof(clientInfo));
	memset(&filesize, 0, sizeof(filesize));
	memset(&rfilesize, 0, sizeof(rfilesize));
	memset(&ftime, 0, sizeof(ftime));
	memset(&clientInfo, 0, sizeof(clientInfo));
}

