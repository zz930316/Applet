#pragma once
/********************************************************************
日期:	2017/12/5
文件名:	Common.h

用途:	此文件为整个项目需要用到的公共文件
*********************************************************************/


#include <iostream>
using namespace std;
#include <winsock2.h>
#include <time.h>
#include <mutex>


#pragma comment(lib, "ws2_32.lib")
const USHORT semaphore = 1;


/* 服务端端口号 */
const unsigned short TCP_PORT = 5555;   // 用于文件传输
const unsigned short TCP_SEND = 9998;   // 用于文件传输

const unsigned short UDP_PORT = 7777;   // 用于消息传输
const unsigned short UDP_SEND = 9999;   // 用于消息传输

extern HANDLE hSemp1, hSemp2, hSemp3, hSemp4;	// HANDLE   句柄，保存地址的意思
extern HANDLE fileLock, queueLock;//互斥锁句柄

/*传输文件数据大小*/
const ULONG SND_BUF_SIZE = 96 * 1024 * 1024;
const ULONG RCV_BUF_SIZE = 96 * 1024 * 1024;
const ULONG Content = 100 * 1024;   // 

			/* 存放客户端信息 */							
struct ClientInfo
{
	SOCKET fSocket;			//socket
	SOCKADDR_IN fAddress;	//客户端ip与端口
	string fArriveTime;		//客户端连接时间
};

		/*存放TCP发送文件的信息*/
struct FileSize
{
	SOCKET sock;//要传送的对方
	/*const */char filename[MAX_PATH];//文件名
	SOCKADDR_IN Sentaddr;//本地ip端口
	ULONG num;//总次数
	ULONG fileContentSize;
	char fileContent[Content];	//内容
};


/*UDP接收的内容*/
struct UDPcontent
{
	char addr[20];//发送人的ip，端口
	char sDateTime[30];//接收时间
	char buffer[1500];//接收信息
};


void Semagphore();//创建信号量

// ReceivesConnection  接收连接线程, Sendmessage  发送消息, Recvmessage  接收消息, SendFile  发送文件,
// RecvFile  接收文件, FilePackage  文件打包, FileUnpack  文件解包;
DWORD WINAPI ReceivesConnection(LPVOID pM);//接收连接线程

DWORD WINAPI Sendmessage(LPVOID pM);//发送消息

DWORD WINAPI Recvmessage(LPVOID pM);//接收消息

DWORD WINAPI SendFile(LPVOID pM);//发送文件

DWORD WINAPI RecvFile(LPVOID pM);//接收文件

DWORD WINAPI FilePackage(LPVOID pM);//文件打包

DWORD WINAPI FileUnpack(LPVOID pM);//文件解包

const char * Get_File_Name(char *name);//获取文件名

void gotoy(int x, int y);

void Reset();