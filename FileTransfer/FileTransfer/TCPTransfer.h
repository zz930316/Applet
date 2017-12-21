
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

/* TCPServer服务端 */
class TCPTransfer
{
public:
	enum  Establish { kBlocking, kNonBlocking }; //设置阻塞
// 	enum { kMaxSendBufSize = 96u * 1024u, kMaxRecvBufSize = 96u * 1024u };
// 	enum { kMaxTCPPacketSize = 5 };//存放信息内存大小

	TCPTransfer();
	~TCPTransfer();

	bool SetIOType(int inIOType);	//设置阻塞
	UINT_PTR Open();	//打开
	bool Close();	//关闭
	SOCKET Connect(char * ,USHORT);//连接服务器
	SOCKET Connect(SOCKET);//通过socket连接
	int Listen(const unsigned short& inPort);	//监听	
	int Send(FileSize*);//发送信息
//	char * Recv(const SOCKET*,int *);		//接受信息
	FileSize * Recv(const SOCKET*, int *);		//接收文件

	int Accept(ClientInfo);//接收客户端连接	

private:
	//SOCKET fclient;
	SOCKET fSeversocket;			//服务器的套接字
	sockaddr_in addrServ;//创建存储地址和端口的结构体
	SOCKET sockClient;//客户端套接字
};