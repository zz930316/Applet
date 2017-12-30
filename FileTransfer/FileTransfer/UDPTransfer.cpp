#include "UDPTransfer.h"
extern SYSTEMTIME ftime;
extern queue<UDPcontent> information_UDP;//存放UDP接收的消息队列



UDPTransfer::UDPTransfer()
{
	fUDPSeversocket = 0;
	sockClient = 0;
	memset(&addrUDPServ, 0, sizeof(addrUDPServ));
	memset(&addrSrv, 0, sizeof(addrSrv));
}


UDPTransfer::~UDPTransfer()
{
	/*closesocket(fUDPSeversocket);*/
}

void UDPTransfer::Open()
{
	fUDPSeversocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (INVALID_SOCKET == fUDPSeversocket)//INVALID_SOCKET  0  是无效套接字
	{
		cout << "socket failed!" << endl;
		WSACleanup();/*WSACleanup是来解除与Socket库的绑定并且释放Socket库所占用的系统资源。*/
	}
}

void UDPTransfer::Bind(const USHORT& inPort)
{
	USHORT flag = inPort;
	addrUDPServ.sin_family = AF_INET;//AF_INET是互联网络:UDP TCP等。
	addrUDPServ.sin_port = htons(flag);//htons用来将主机字节顺序转换为网络字节顺序(to network short) 
	addrUDPServ.sin_addr.S_un.S_addr = htonl(INADDR_LOOPBACK);// inet_addr将IP地址从点数格式转换成网络字节格式整型。
// 	if (setsockopt(fUDPSeversocket, SOL_SOCKET, SO_REUSEADDR, (char*)&flag, len) == -1)
// 	{
// 		perror("setsockopt");
// 		exit(1);
// 	}
	bool re = false;
	while (!re)
	{
		int a = ::bind(fUDPSeversocket, (const struct sockaddr*)&addrUDPServ, sizeof(addrUDPServ));
		if (a != SOCKET_ERROR)
		{
			re = true;
			cout << "UDP端口:" << flag << endl;
			system("pause");
		}
		else if (a == SOCKET_ERROR)
		{
			flag++;
			addrUDPServ.sin_port = htons(flag);
			continue;
// 			cout << "[error]Socket::_Bind Binded socket error!" << endl;
// 			system("pause");
// 			exit(1);
		}
	}
}

UINT_PTR UDPTransfer::Connect_U(char *addr, USHORT port)
{
	sockClient = socket(AF_INET, SOCK_DGRAM, 0);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(port);//htons用来将主机字节顺序转换为网络字节顺序(to network short) 
	addrSrv.sin_addr.S_un.S_addr = inet_addr(addr);// inet_addr将IP地址从点数格式转换成网络字节格式整型。

	//       采用广播形式须将第三个参数设置为SO_BROADCAST
//setsockopt(sockListener, SOL_SOCKET, SO_BROADCAST, (CHAR *)&fBroadcast, sizeof(BOOL));
	//  参数设置，注意要将IP地址设为INADDR_BROADCAST，表示发送广播UDP数据报
	/*saUdpServ.sin_addr.s_addr = htonl(addr);*/
	return 	sockClient;
}

int UDPTransfer::SendTo()
{
	char buffer[kMaxUDPPacket];
	memset(&buffer, 0, sizeof(buffer));
	cout << "输入消息：";
	cin >> buffer;
	getchar();
	int sentBytes = ::sendto(sockClient, buffer, strlen(buffer), 0, (const sockaddr*)&addrSrv, sizeof(struct sockaddr));
	if (sentBytes<0)
	{
		cout << "发送失败！" << endl;
		system("pause");
		return sentBytes;
	}
	cout << "发送成功！" << endl;
	system("pause");
	closesocket(sockClient);
	return sentBytes;
}


int UDPTransfer::RecvFrom()
{
	int receivedBytes = 0;
	char buffer[kMaxUDPPacket];
	memset(&buffer, 0, sizeof(buffer));
	int size = sizeof(sockaddr);
	receivedBytes = ::recvfrom(fUDPSeversocket, (char *)buffer, sizeof(buffer), 0, (struct sockaddr*)&addrUDPServ, &size);
	/*函数说明:recvfrom()用来接收远程主机经指定的socket传来的数据,并把数据传到由参数buf指向的内存空间,参数len为可接收数据的最大长度.
	参数flags一般设0,其他数值定义参考recv().参数from用来指定欲传送的网络地址,结构sockaddr请参考bind()函数.参数fromlen为sockaddr的结构长度.
	返回值:成功则返回接收到的字符数, 失败返回 - 1.*/
	if (receivedBytes>0)
	{
		UDPcontent *udpcontent = new UDPcontent;
		memset(udpcontent, 0, sizeof(udpcontent));
		GetLocalTime(&ftime);		//获取当地的当前系统日期和时间,存放在ftime结构体中;
		sprintf_s(udpcontent->sDateTime, "%4d-%2d-%2d %2d:%2d:%2d", ftime.wYear, ftime.wMonth, ftime.wDay, ftime.wHour, ftime.wMinute, ftime.wSecond);
		strcpy(udpcontent->buffer, buffer);
		strcpy(udpcontent->addr, inet_ntoa(addrUDPServ.sin_addr));
		information_UDP.push(*udpcontent);
	}
	return 0;
}