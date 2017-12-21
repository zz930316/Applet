#include "TCPTransfer.h"
extern ULONG retVal_r;
extern ClientInfo clientInfo;
extern FileSize filesize, rfilesize;
extern map<SOCKET, ClientInfo> fmap_Clien;
extern SYSTEMTIME ftime;
extern queue<FileSize*> send_information_que, recv_information_que;//��ŷ��͵ĺͽ��յ��ļ���Ϣ����




int fileNum = 0;	//	�ļ����մ���
TCPTransfer::TCPTransfer()
{
	fSeversocket = 0;			//���������׽���
	::memset((void*)&addrServ, 0, sizeof(addrServ));//�Խϴ�Ľṹ�������������������һ����췽��
	sockClient = 0;

}


TCPTransfer::~TCPTransfer()
{
	Close();
	WSACleanup();/*WSACleanup���������Socket��İ󶨲����ͷ�Socket����ռ�õ�ϵͳ��Դ��*/
}

bool TCPTransfer::SetIOType(int inIOType)
{
	Establish establish = kNonBlocking;
	retVal_r = ioctlsocket(fSeversocket, FIONBIO, (u_long FAR*)&establish);
	if (retVal_r == SOCKET_ERROR)//SOCKET_ERROR -1
	{
		cout << "ioctlsocket failed!" << endl;
		WSACleanup();/*WSACleanup���������Socket��İ󶨲����ͷ�Socket����ռ�õ�ϵͳ��Դ��*/
		return false;
	}
	return true;
}

UINT_PTR TCPTransfer::Open()
{
	fSeversocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == fSeversocket)//INVALID_SOCKET  0  ����Ч�׽���
	{
		cout << "socket failed!" << endl;
		WSACleanup();/*WSACleanup���������Socket��İ󶨲����ͷ�Socket����ռ�õ�ϵͳ��Դ��*/
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
	/*closesocket(fSeversocket);	//�ر�sServer����������IP���˿�����*/
	map<SOCKET, ClientInfo > ::iterator map_it = fmap_Clien.begin();
	while (true)
	{
		if (map_it != fmap_Clien.end())
			break;
		closesocket(map_it->first);	//�ر�sClient���ͻ��ˣ�IP���˿�����
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
	addr_C.sin_addr.S_un.S_addr = inet_addr(addr);// inet_addr��IP��ַ�ӵ�����ʽת���������ֽڸ�ʽ���͡�
	addr_C.sin_family = AF_INET;//AF_INET�ǻ�������:UDP TCP�ȡ�
	addr_C.sin_port = htons(port);//htons�����������ֽ�˳��ת��Ϊ�����ֽ�˳��(to network short) 
	connect(sockClient, (SOCKADDR*)&addr_C, sizeof(SOCKADDR));
	return sockClient;
}

SOCKET TCPTransfer::Connect(SOCKET sock)
{
	/*ͨ��socket����*/
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
			cout << "TCP�˿�:" << flag << endl;
			
		}
		if (retVal_r == SOCKET_ERROR)//SOCKET_ERROR -1
		{
			flag++;
			addrServ.sin_port = htons(flag);
			continue;
// 			cout << "bind failed!" << endl;
// 			closesocket(fSeversocket);//�ر�sServer����������IP���˿�����
// 			WSACleanup();/*WSACleanup���������Socket��İ󶨲����ͷ�Socket����ռ�õ�ϵͳ��Դ��*/
// 			system("pause");
// 			exit(1);
// 			return -1;
		}
	}
	retVal_r = listen(fSeversocket, 1);
	if (retVal_r == SOCKET_ERROR)//SOCKET_ERROR -1
	{
		cout << "listen failed!" << endl;
		closesocket(inPort);//�ر�sServer����
		WSACleanup();/*WSACleanup���������Socket��İ󶨲����ͷ�Socket����ռ�õ�ϵͳ��Դ��*/
		system("pause");
		exit(1);
		return -1;
	}
	return 0;
}

int TCPTransfer::Send(FileSize* filesize)
{
		//�ļ�����
	Sleep(10);
	FileSize*filesize_TCP = send_information_que.front();
	USHORT sock = filesize_TCP->sock;
	LONG num = 0;
	ULONG size = sizeof(FileSize);
	ULONG establish = kNonBlocking;
// 	if (ioctlsocket(sock, FIONBIO, (u_long FAR*)&establish) == SOCKET_ERROR)//SOCKET_ERROR -1
// 	{
// 		cout << "ioctlsocket failed!" << endl;
// 		WSACleanup();/*WSACleanup���������Socket��İ󶨲����ͷ�Socket����ռ�õ�ϵͳ��Դ��*/
// 		return false;
// 	}
	num = send(sock, (char*)filesize_TCP, size, 0);
	if (num != size)
		return -1;
	send_information_que.pop();
	delete[]filesize_TCP;
	return num;
	// 		//��Ϣ����
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


			//TCP�����ļ�
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
// 		WSACleanup();/*WSACleanup���������Socket��İ󶨲����ͷ�Socket����ռ�õ�ϵͳ��Դ��*/
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


//			//TCP������Ϣ
// char * TCPTransfer::Recv(const SOCKET*sock, int *timeRemind)
// {
// 	const unsigned short Con = Content + 1;   // ��ȡ�ļ����ݴ�С
// 	char *fileContent = new char[Con];	//����
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
		if (INVALID_SOCKET == fClient.fSocket)//INVALID_SOCKET ����Ч�׽���
		{
			int err = WSAGetLastError();
			if (err == WSAEWOULDBLOCK)//WSAEWOULDBLOCK : 10035 ��Դ��ʱ������
			{
				Sleep(100);
				continue;
			}
// 			else
// 			{
// 				cout << "accept failed!" << endl;
// 				closesocket(fSeversocket);//�رգ���������IP���˿�����
// 				WSACleanup();/*WSACleanup���������Socket��İ󶨲����ͷ�Socket����ռ�õ�ϵͳ��Դ��*/
// 				return -1;
// 			}
		}
		else
		{	
			break;
		}
	}
	Sleep(100);
	GetLocalTime(&ftime);		//��ȡ���صĵ�ǰϵͳ���ں�ʱ��,�����ftime�ṹ����;
	char sDateTime[30];
	sprintf_s(sDateTime, "%4d-%2d-%2d %2d:%2d:%2d", ftime.wYear, ftime.wMonth, ftime.wDay, ftime.wHour, ftime.wMinute, ftime.wSecond);

	fClient.fArriveTime = sDateTime;
	// 		cout << fClient.fArriveTime << "�пͻ���IP:" << inet_ntoa(fClient.fAddress.sin_addr) <<
	// 			"  �˿ڣ�" << ntohs(fClient.fAddress.sin_port) << " ���ӷ������� " << endl;

	fmap_Clien.insert(map<SOCKET, ClientInfo>::value_type(fClient.fSocket, fClient));
	return 1;
}