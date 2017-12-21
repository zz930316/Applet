#include "TCPTransfer.h"
extern ULONG retVal_r;
extern ClientInfo clientInfo;
extern FileSize filesize, rfilesize;
extern map<SOCKET, ClientInfo> fmap_Clien;
extern SYSTEMTIME ftime;
extern queue<FileSize*> send_information_que, recv_information_que;//存放发送的和接收的文件信息队列




int fileNum = 0;	//	文件接收次数
TCPTransfer::TCPTransfer()
{
	fSeversocket = 0;			//服务器的套接字
	::memset((void*)&addrServ, 0, sizeof(addrServ));//对较大的结构体或数组进行清零操作的一种最快方法
	sockClient = 0;

}


TCPTransfer::~TCPTransfer()
{
	Close();
	WSACleanup();/*WSACleanup是来解除与Socket库的绑定并且释放Socket库所占用的系统资源。*/
}

bool TCPTransfer::SetIOType(int inIOType)
{
	Establish establish = kNonBlocking;
	retVal_r = ioctlsocket(fSeversocket, FIONBIO, (u_long FAR*)&establish);
	if (retVal_r == SOCKET_ERROR)//SOCKET_ERROR -1
	{
		cout << "ioctlsocket failed!" << endl;
		WSACleanup();/*WSACleanup是来解除与Socket库的绑定并且释放Socket库所占用的系统资源。*/
		return false;
	}
	return true;
}

UINT_PTR TCPTransfer::Open()
{
	fSeversocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == fSeversocket)//INVALID_SOCKET  0  是无效套接字
	{
		cout << "socket failed!" << endl;
		WSACleanup();/*WSACleanup是来解除与Socket库的绑定并且释放Socket库所占用的系统资源。*/
		return INVALID_SOCKET;
	}
	if (SOCKET_ERROR == setsockopt(fSeversocket, SOL_SOCKET, SO_RCVBUF, (char*)&RCV_BUF_SIZE, sizeof(RCV_BUF_SIZE)))
	{
		cout << "setsockopt error!" << endl;
		return -1;
	}
	return fSeversocket;
}

bool TCPTransfer::Close()
{
	/*closesocket(fSeversocket);	//关闭sServer（服务器）IP，端口连接*/
	map<SOCKET, ClientInfo > ::iterator map_it = fmap_Clien.begin();
	while (true)
	{
		if (map_it != fmap_Clien.end())
			break;
		closesocket(map_it->first);	//关闭sClient（客户端）IP，端口连接
		map_it++;
	}
	return true;
}


SOCKET TCPTransfer::Connect(char *addr, USHORT port)
{
	sockaddr_in addr_C;
	sockClient = socket(AF_INET, SOCK_STREAM, 0);
	if (SOCKET_ERROR == setsockopt(sockClient, SOL_SOCKET, SO_SNDBUF, (char*)&SND_BUF_SIZE, sizeof(SND_BUF_SIZE)))
	{
		cout << "setsockopt error!" << endl;
		return -1;
	}
	addr_C.sin_addr.S_un.S_addr = inet_addr(addr);// inet_addr将IP地址从点数格式转换成网络字节格式整型。
	addr_C.sin_family = AF_INET;//AF_INET是互联网络:UDP TCP等。
	addr_C.sin_port = htons(port);//htons用来将主机字节顺序转换为网络字节顺序(to network short) 
	connect(sockClient, (SOCKADDR*)&addr_C, sizeof(SOCKADDR));
	return sockClient;
}

SOCKET TCPTransfer::Connect(SOCKET sock)
{
	/*通过socket连接*/
	return sock;
}

int TCPTransfer::Listen(const unsigned short& inPort)
{
	USHORT flag = inPort;
	addrServ.sin_family = AF_INET;
	addrServ.sin_port = htons(flag);
	addrServ.sin_addr.S_un.S_addr = htonl(INADDR_LOOPBACK);

	bool re = false;
	while (!re)
	{
		retVal_r = ::bind(fSeversocket, (const struct sockaddr*)&addrServ, sizeof(addrServ));
		if (retVal_r != SOCKET_ERROR)
		{
			re = true;
			cout << "TCP端口:" << flag << endl;
			
		}
		if (retVal_r == SOCKET_ERROR)//SOCKET_ERROR -1
		{
			flag++;
			addrServ.sin_port = htons(flag);
			continue;
// 			cout << "bind failed!" << endl;
// 			closesocket(fSeversocket);//关闭sServer（服务器）IP，端口连接
// 			WSACleanup();/*WSACleanup是来解除与Socket库的绑定并且释放Socket库所占用的系统资源。*/
// 			system("pause");
// 			exit(1);
// 			return -1;
		}
	}
	retVal_r = listen(fSeversocket, 1);
	if (retVal_r == SOCKET_ERROR)//SOCKET_ERROR -1
	{
		cout << "listen failed!" << endl;
		closesocket(inPort);//关闭sServer连接
		WSACleanup();/*WSACleanup是来解除与Socket库的绑定并且释放Socket库所占用的系统资源。*/
		system("pause");
		exit(1);
		return -1;
	}
	return 0;
}

int TCPTransfer::Send(FileSize* filesize)
{
		//文件部分
	Sleep(10);
	FileSize*filesize_TCP = send_information_que.front();
	USHORT sock = filesize_TCP->sock;
	LONG num = 0;
	ULONG size = sizeof(FileSize);
	ULONG establish = kNonBlocking;
// 	if (ioctlsocket(sock, FIONBIO, (u_long FAR*)&establish) == SOCKET_ERROR)//SOCKET_ERROR -1
// 	{
// 		cout << "ioctlsocket failed!" << endl;
// 		WSACleanup();/*WSACleanup是来解除与Socket库的绑定并且释放Socket库所占用的系统资源。*/
// 		return false;
// 	}
	num = send(sock, (char*)filesize_TCP, size, 0);
	if (num != size)
		return -1;
	send_information_que.pop();
	delete[]filesize_TCP;
	return num;
	// 		//消息部分
	// 	int num = -1;
	// 	char *a = send_information_que.front();
	// 	num = send(filesize->sock, a, strlen(a), 0);
	// 	if (num <= 0)
	// 		return -1;
	// 	else
	// 	{
	// 		delete[]a;
	// 		send_information_que.pop();
	// 	}
	// 	return num;
}


			//TCP接收文件
FileSize * TCPTransfer::Recv(const SOCKET*sock, int *timeRemind)
{
	Sleep(10);
	ULONG size = sizeof(FileSize);
	LONG retVal_r = 0;
	char *file = new char[size];
	::memset(file, 0, sizeof(FileSize));
	ULONG establish = kNonBlocking;
// 	if (ioctlsocket(*sock, FIONBIO, (u_long FAR*)&establish) == SOCKET_ERROR)//SOCKET_ERROR -1
// 	{
// 		cout << "ioctlsocket failed!" << endl;
// 		WSACleanup();/*WSACleanup是来解除与Socket库的绑定并且释放Socket库所占用的系统资源。*/
// 		return false;
// 	}
	retVal_r = recv(*sock,file, size, 0);
//	FileSize*fil = (FileSize*)file;
// 	fil->sock = ntohs(fil->sock);
// 	fil->fileContentSize = ntohl(fil->fileContentSize);
	if (retVal_r > 0 && retVal_r <= size)
	{
		*(timeRemind) += 1;
		return (FileSize*)file;
	}
	delete[]file;
	return NULL;
}


//			//TCP接收消息
// char * TCPTransfer::Recv(const SOCKET*sock, int *timeRemind)
// {
// 	const unsigned short Con = Content + 1;   // 读取文件数据大小
// 	char *fileContent = new char[Con];	//内容
// 	memset(fileContent, 0, Con);
// 	retVal_r = recv(*sock, fileContent, Content, 0);
// 	if (retVal_r > 0)
// 	{
// 		*(timeRemind) += 1;
// 		return fileContent;
// 	}
// 	delete[]fileContent;
// 	return NULL;
// }

int TCPTransfer::Accept(ClientInfo fClient)
{
	int fclifAddr = sizeof(SOCKADDR_IN);
	while (true)
	{
		fClient.fSocket = accept(fSeversocket, (sockaddr FAR*)&fClient.fAddress, &fclifAddr);
		if (INVALID_SOCKET == fClient.fSocket)//INVALID_SOCKET 是无效套接字
		{
			int err = WSAGetLastError();
			if (err == WSAEWOULDBLOCK)//WSAEWOULDBLOCK : 10035 资源暂时不可用
			{
				Sleep(100);
				continue;
			}
// 			else
// 			{
// 				cout << "accept failed!" << endl;
// 				closesocket(fSeversocket);//关闭（服务器）IP，端口连接
// 				WSACleanup();/*WSACleanup是来解除与Socket库的绑定并且释放Socket库所占用的系统资源。*/
// 				return -1;
// 			}
		}
		else
		{	
			break;
		}
	}
	Sleep(100);
	GetLocalTime(&ftime);		//获取当地的当前系统日期和时间,存放在ftime结构体中;
	char sDateTime[30];
	sprintf_s(sDateTime, "%4d-%2d-%2d %2d:%2d:%2d", ftime.wYear, ftime.wMonth, ftime.wDay, ftime.wHour, ftime.wMinute, ftime.wSecond);

	fClient.fArriveTime = sDateTime;
	// 		cout << fClient.fArriveTime << "有客户端IP:" << inet_ntoa(fClient.fAddress.sin_addr) <<
	// 			"  端口：" << ntohs(fClient.fAddress.sin_port) << " 连接服务器！ " << endl;

	fmap_Clien.insert(map<SOCKET, ClientInfo>::value_type(fClient.fSocket, fClient));
	return 1;
}