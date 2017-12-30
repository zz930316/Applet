#include "FileMaster.h"
extern map<SOCKET, ClientInfo> fmap_Clien;
extern ClientInfo clientInfo;
extern FileSize filesize, rfilesize;
extern HANDLE Thread[7];			//线程数
extern TCPTransfer fTCPTransfer;
extern UDPTransfer fUDPTransfer;
extern SYSTEMTIME ftime;//存放时间
extern queue<FileSize*> send_information_que, recv_information_que;//存放发送的和接收的文件信息队列
extern float process;		//显示当前传输进度
extern queue<UDPcontent> information_UDP;//存放UDP接收的消息队列




bool thread_three_open = false;
bool thread_six_open = false;

FileMaster::FileMaster()
{
	
	Reset();
	Semagphore();
/*	memset(&cliipaddr, 0, sizeof(cliipaddr));*/
// 	WSADATA wsaData;
// 	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
// 		printf("[error] WSAStartup error!\n");
}


FileMaster::~FileMaster()
{
	CloseThread();
}



int FileMaster::EstablishTCP()
{
	fTCPTransfer.Open();
	fTCPTransfer.SetIOType(1);// 1 是非阻塞
	fTCPTransfer.Listen(TCP_PORT);
	return 0;
}

int FileMaster::EstablishUDP()
{
	fUDPTransfer.Open();
	fUDPTransfer.Bind(UDP_PORT);
	return 0;
}

void FileMaster::Display()
{
	Create_Thread();
	bool judeg = true;
	while (judeg)
	{
		system("cls");//清屏
		/*gotoy(22, 7);*///指定位置显示
		cout << "1、文件处理" << endl;
		cout << "2、消息处理" << endl;
		cout << "3、退出程序" << endl;
		cout << "请选择操作：";
		char choice = getch();

		switch (choice)
		{
		case '1':TransferFiles(); break;
		case '2':TransmitMessage(); break;
		case '3': judeg = false; break;
		default:
			break;
		}
	}
}

void FileMaster::Create_Thread()
{
	Thread[0] = CreateThread(NULL, 0, ReceivesConnection, NULL, 0, NULL);		//接收连接线程
	Thread[2] = CreateThread(NULL, 0, Recvmessage, NULL, 0, NULL);				//接收消息线程
	Thread[4] = CreateThread(NULL, 0, RecvFile, this, 0, NULL);					 //接收文件线程
	Thread[3] = CreateThread(NULL, 0, SendFile, NULL, 0, NULL);			//发送文件线程
	Thread[6] = CreateThread(NULL, 0, FileUnpack, this, 0, NULL);				//文件解包线程
}

void FileMaster::CloseThread()
{

// 	WaitForSingleObject(Thread[1], INFINITE);
// 	WaitForSingleObject(Thread[2], INFINITE);
// 	WaitForSingleObject(Thread[3], INFINITE);
// 	WaitForSingleObject(Thread[4], INFINITE);
// 	WaitForSingleObject(Thread[5], INFINITE);
// 	WaitForSingleObject(Thread[6], INFINITE);
	CloseHandle(fileLock);
	CloseHandle(queueLock);
	for (int i = 0; i < 7; i++)
		CloseHandle(Thread[i]); //关闭一个内核对象。其中包括文件、文件映射、进程、线程、安全和同步对象等
//	WSACleanup();/*WSACleanup是来解除与Socket库的绑定并且释放Socket库所占用的系统资源。*/
}

void FileMaster::TransferFiles()
{
	/*  1、新建传输
		2、正在传输*/
	bool judeg = true;
	while (judeg)
	{
		system("cls");//清屏
		//gotoy(22, 7);//指定位置显示
		cout << "1、新建传输" << endl;
		cout << "2、正在传输" << endl; 
		cout << "3、查看已连接的客户端信息" << endl;
		cout << "4、返回上一级" << endl;
		cout << "请选择操作：";
		char choice = getch();
		switch (choice)
		{
		case '1': ConnectionObject(SOCK_STREAM); judeg = false; break;
		case '2': FileTransfer_Underway(); break;
		case '3': ConnectTheClient(); break;
		case '4': judeg = false; break;/*Display(); break;*/
		default:
			break;
		}
	}
}

void FileMaster::TransmitMessage()
{
	bool judeg = true;
	while (judeg)
	{
		system("cls");//清屏
		cout << "1、发送消息" << endl;
		cout << "2、查看消息" << endl;
		cout << "3、返回上一级" << endl;
		cout << "请选择操作：";
		char choice = getch();
		switch (choice)
		{
		case '1': ConnectionObject(SOCK_DGRAM); break;
		case '2': View_New_Message(); break;
		case '3': Display(); break;
		default:
			break;
		}
	}
}

void FileMaster::Establish_IP_Address()
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		printf("[error] WSAStartup error!\n");
}



//设置文件存放路径
char * FileMaster::File_Storage_Path()
{
	bool judeg = true;
	while (judeg)
	{
		cout << "是否修改文件存放路径  Y/N" << endl;
		char a = getch();
		if (a == 'Y' || a == 'y')
		{
			char path[400] = { "0" };
			memset(&path, 0, sizeof(path));
			cout << "输入文件存放路径(按双\\) : ";
			cin >> path;
			strcat(path, "\\");
			return path;
		}
		else
			break;
	}
	return NULL;
}



void FileMaster::ConnectionObject(int type)
{
	//char addr_C_addr[15] = { "127.0.0.1" };

	char addr_C_addr[15];
	memset(&addr_C_addr, 0, sizeof(addr_C_addr));
	unsigned short Port = 0;   // 用于消息传输
	SOCKET sock = 0;
	TransferMode(addr_C_addr, &Port, &sock);
	
	if (type == SOCK_STREAM)
	{
		/*下面写传输文件部分*/
		if (strcmp(addr_C_addr, "0") > 0)
			filesize.sock = fTCPTransfer.Connect(addr_C_addr, Port);
		else
			filesize.sock = fTCPTransfer.Connect(sock);
		Thread[5] = CreateThread(NULL, 0, FilePackage, NULL, 0, NULL);				 //文件打包线程
 	//	WaitForSingleObject(Thread[5], INFINITE);
		CloseHandle(Thread[5]); //关闭一个内核对象。其中包括文件、文件映射、进程、线程、安全和同步对象等
	}
	else if (type == SOCK_DGRAM)
	{
		fUDPTransfer.Connect_U(addr_C_addr, Port);
		
/*这里写udp传消息*/
		Thread[1] = CreateThread(NULL, 0, Sendmessage, NULL, 0, NULL);				//发送消息线程
		WaitForSingleObject(Thread[1], INFINITE);
		CloseHandle(Thread[1]); //关闭一个内核对象。其中包括文件、文件映射、进程、线程、安全和同步对象等
	}

}

void FileMaster::FileTransfer_Underway()//文件传输进程
{

	cout << "已传输了：";
	cout.precision(2);
	cout << process << "%！" << endl;
	system("pause");
}

void FileMaster::ConnectTheClient()
{
	/*查看已经连接上的客户端信息*/
	system("cls");//清屏
	int i = 1;//个数显示
	char addr[20];//地址
	unsigned short port = 0;
	char time[30];
	int num = fmap_Clien.size();
	cout << "有 " << num << " 个客户端连接" << endl;

	cout << "个数" << "   socket" << "   IP地址" << "        端口号" << "   连接时间" << endl;
	map<SOCKET, ClientInfo>::iterator map_it = fmap_Clien.begin();
	while (map_it != fmap_Clien.end())
	{
		memset((void*)&addr, 0, sizeof(addr));
		memset((void*)&time, 0, sizeof(time));
		strcpy(addr, inet_ntoa(map_it->second.fAddress.sin_addr));
		port = ntohs(map_it->second.fAddress.sin_port);
		strcpy(time, map_it->second.fArriveTime.c_str());
		cout.setf(ios::left);
		cout.width(7);	cout << i; 
		cout.width(9);	cout << map_it->first; 
		cout.width(14);	cout << addr;
		cout.width(9);	cout << port; 
		cout.width(6);	cout << time << endl;
		i++; map_it++;
	}
	system("pause");
}


void FileMaster::TransferMode(char *addr_C_addr, unsigned short *Port, SOCKET *sock)//选择传输方式)
{
	/*选择传输方式
	1、知道对方ip，端口
	2、输入已连接的客户端的socket*/
	bool judeg = true;
	while (judeg)
	{
		system("cls");//清屏
		cout << "1、新建传输连接（未连接对方，知道对方ip和端口，端口不输入则默认）" << endl;
		cout << "2、使用已连接传输（输入已连接的客户端的socke！    ps：TCP使用）" << endl;
		cout << "3、查看已连接的客户端信息" << endl;
		cout << "4、返回上一级" << endl;
		cout << "请选择操作：";
		char choice = getch();
		switch (choice)
		{
		case '1': GetIP(addr_C_addr, Port); judeg = false; break;
		case '2': GetIP(sock);  judeg = false; break;
		case '3': ConnectTheClient();   break;
		case '4': Display(); judeg = false; break;
		default:
			break;
		}
	}
}


//输入要连接的ip和端口
void FileMaster::GetIP(char *addr_C_addr, unsigned short *Port)
{
	/*输入要连接的ip和端口*/

	cout << "\n请输入对方ip : ";
	cin >> addr_C_addr;

	cout << "\n请输入对方端口（不知道就输入 0 ,默认9998） : ";
	cin >> *Port;
	if (*Port==0)
	{
		*Port = TCP_SEND;
	}
}

void FileMaster::GetIP(SOCKET * sock)
{
	cout << "\n请输入对方socket值 : ";
	cin >> *sock;
}

void FileMaster::View_New_Message()
{
	/*查看最新接收到的信息*/
	system("cls");//清屏
	int i = 1;//个数显示
	unsigned short num = information_UDP.size();
	cout << "有 " << num << " 条新信息" << endl;
	cout << "个数" << "   接收时间" << "              地址" << "           消息内容" << endl;
	while (information_UDP.empty()==false)
	{
		cout.setf(ios::left);
		cout.width(7);	cout << i;
		cout.width(22);	cout << information_UDP.front().sDateTime;
		cout.width(15);	cout << information_UDP.front().addr;
		cout.width(9);	cout << information_UDP.front().buffer << endl;
		i++; 
		information_UDP.pop();
	}
	system("pause");
}

//extern queue<int*> g_intQueue;
DWORD WINAPI ReceivesConnection(LPVOID pM)//接收连接线程
{
// 	while (true)
// 	{
// 		for (int i = 0; i < g_intQueue.size(); i++)
// 		{
// 			int *p = g_intQueue.front();
// 			cout << *p << " ";
// 		}
// 	}
	while (true)
	{
		fTCPTransfer.Accept(clientInfo);
		Sleep(10);
	}
	return 0;
}

DWORD WINAPI Sendmessage(LPVOID pM)//发送消息
{
	fUDPTransfer.SendTo();
	return 0;
}


DWORD WINAPI Recvmessage(LPVOID pM)//接收消息
{
// 	int i = 0;
// 	while (true)
// 	{
// 		int *p = new int;
// 		*p = ++i;
// 		g_intQueue.push(p);
// 	}
	while (1)
	{
		Sleep(100);
		fUDPTransfer.RecvFrom();
	}
	return 0;
}
		///*发送文件*/
DWORD WINAPI SendFile(LPVOID pM)//发送文件
{
	////TCP传输消息
// 	int i = 1, result = 0;
// 	while (true)
// 	{
// 		if (thread_three_open)
// 		{
// 			if (send_information_que.empty() == false)
// 			{
// 				result = fTCPTransfer.Send(&filesize);
// 				if (result <= 0)
// 					cout << "\n传输出错" << endl;
// 				else if (i == filesize.num)
// 				{
// 					cout << "\n文件传输完成" << endl;
// 					system("pause");
// 					i = 0;
// 				}
// 				i++;
// 			}
// 		}
// 		Sleep(100);
// 	}
// 	return 1;

	LONG i = 1, result = 0, num = 0;
	USHORT q = 0;
	while (TRUE)
	{
		WaitForSingleObject(hSemp2, INFINITE);//等待信号量 ；INFINITE  无限等待（时间）	P(S)减一
		if (send_information_que.size() <= 0)
		{
			Sleep(10);
		}
		WaitForSingleObject(queueLock, INFINITE);
		FileSize*filesize_TCP = send_information_que.front();
		ReleaseMutex(queueLock);//解锁
		num = filesize_TCP->num;
		result = fTCPTransfer.Send(&filesize);
	//	cout << ++q << endl;
		if (result ==-1)
		{
			--i;
 	//		cout << "\n传输出错" << endl;
// 			system("pause");
		}
		else if (i == num)
		{
			cout << "\n文件传输完成" << endl;
			system("pause");
			i = 0; result = 0, num = 0;
// 			hSemp1 = CreateSemaphore(NULL, 100, 100, NULL);//打包文件
// 			hSemp2 = CreateSemaphore(NULL, 0, 100, NULL);//发送文件
		}
		i++;
		ReleaseSemaphore(hSemp1, 1, NULL);//释放信号量的占有权	V(S)  加一
	}
	return 1;
}

////文件打包
DWORD WINAPI FilePackage(LPVOID pM)//文件打包
{
	////TCP传输消息

	//	fstream fFile;
	//	char path[50] = {"F:\\xfmovie\\file.txt"};
	////	char path[50];
	//// 	memset(&path, 0, sizeof(path));
	//// 	cout << "输入要传输文件的路径(按双\\) : ";
	//// 	cin >> path;
	//	strcpy(filesize.filename, Get_File_Name(path));
	//	//一个测量文件大小的函数，（为了算出传输次数）
	//	struct _stat info;
	//	_stat(path, &info);//参数一放文件路径
	//	int num = info.st_size;//文件大小
	//	int totalDegree = num / 10;//传输次数
	//	if (num % 10)
	//		totalDegree++;
	//	filesize.num = totalDegree;
	//	fFile.open(path, ios::out | ios::binary | ios::_Nocreate);//打开文件
	//	if (!fFile)
	//	{
	//		cout << "文件打开失败,请检查文件路径是否正确" << endl;
	//		return 0;
	//		system("pause");
	//	}

	// 	const unsigned short Con = Content + 1;   // 读取文件数据大小
	// 	while (TRUE)
	// 	{
	// 		char *fileContent = new char[Con];	//内容
	// 		memset(fileContent, 0, Con);
	// 		fFile.read(fileContent, Content);
	// 		cout << fileContent;
	// 		send_information_que.push(fileContent);
	// 		if (fFile.eof())
	// 			break;
	// 		thread_three_open = TRUE;
	// 	}

	fstream fFile;
	// F:\\xfmovie\\MS.rar
	char path[2000] = { "F:\\迅雷下载\\电影\\Dead.Island.Riptide.Definitive.Edition.CHS.1.1-ALI213\\Dead.Island.Riptide.Definitive.Edition.CHS.1.1-ALI213.part01.rar" };

	//	char path[50];
	// 	memset(&path, 0, sizeof(path));
	// 	cout << "输入要传输文件的路径(按双\\) : ";
	// 	cin >> path;
	char filename[MAX_PATH] = "0";
	strcpy(filename, Get_File_Name(path));
	//一个测量文件大小的函数，（为了算出传输次数）
	struct _stat info;
	_stat(path, &info);//参数一放文件路径
	ULONG num = info.st_size;//文件大小
	ULONG totalDegree = num / Content;//传输次数
	if (num % Content)
		totalDegree++;
	fFile.open(path, ios::in | ios::binary | ios::_Nocreate);//打开文件
	if (!fFile)
	{
		cout << "文件打开失败,请检查文件路径是否正确" << endl;
		return 0;
		system("pause");
	}

	while (num > 0)
	{
		WaitForSingleObject(hSemp1, INFINITE);//等待信号量 ；INFINITE  无限等待（时间）	P(S)减一
		FileSize*filesize_TCP = new FileSize;
		memset((void*)filesize_TCP, 0, sizeof(FileSize));
		strcpy(filesize_TCP->filename, filename);	//复制文件名
		filesize_TCP->num = totalDegree;			//传输次数
		filesize_TCP->sock = filesize.sock;			//传送对象

		filesize_TCP->fileContentSize = (num > Content ? Content : num);//每次发送的Content字节，不足时发送num;

		if (num > Content)//如果文件大小大于filesize_TCP->fileContent，
		{
			num -= Content;
			WaitForSingleObject(fileLock, INFINITE);
			if (!fFile.read(filesize_TCP->fileContent, filesize_TCP->fileContentSize))
				cout << "read error!" << endl;//读取内容（10个字节）
			send_information_que.push(filesize_TCP);
			ReleaseMutex(fileLock);//解锁
			if (send_information_que.size()>40)
			{
				Sleep(10);
			}
			ReleaseSemaphore(hSemp2, 1, NULL);//释放信号量的占有权	V(S)  加一
		}
		else//如果文件大小刚好等于或者小于filesize_TCP->fileContent，读完就直接跳出
		{
			num -= filesize_TCP->fileContentSize;
			fFile.read(filesize_TCP->fileContent, filesize_TCP->fileContentSize);
			send_information_que.push(filesize_TCP);
			ReleaseSemaphore(hSemp2, 1, NULL);//释放信号量的占有权	V(S)  加一
			break;
		}
		Sleep(10);
	}
	fFile.close();
	return 0;
}

			// /*接收文件*/
DWORD WINAPI RecvFile(LPVOID pM)	//接收文件
{
	TCPTransfer * multiSer = (TCPTransfer*)pM;
	while (TRUE)
	{
		int practicalETX = 0; ULONG byte = 0;
		map<SOCKET, ClientInfo>::iterator mclien_socket = fmap_Clien.begin();
		while (mclien_socket != fmap_Clien.end())//如果有客户端连接了，就进去
		{
			FileSize* fileContent = multiSer->Recv(&mclien_socket->first, &practicalETX);
			if (practicalETX == 1)//如果practicalETX大于0，说明已经接收到数据了
			{
				ULONG ETX = fileContent->num;
				while (TRUE)
				{	//接收文件
					WaitForSingleObject(hSemp3, INFINITE);//等待信号量 ；INFINITE  无限等待（时间）	P(S)减一
			//		cout << "RecvFile: 等待进入临界区" << endl;
			//		WaitForSingleObject(Lock, INFINITE); //加锁,没上锁的话就自己锁上，否则等着
			//		cout << "RecvFile: 进临界区" << endl;					
					WaitForSingleObject(queueLock, INFINITE);
					recv_information_que.push(fileContent);//存放发送的和接收的文件信息队列
					byte += fileContent->fileContentSize;
					fileContent = NULL;	
					ReleaseMutex(queueLock);//解锁
			//		cout.setf(ios::hex);
			//		cout << "添加" << fileContent << endl;
			//		cout.unsetf(ios::hex);
					if (recv_information_que.size()>10)
					{
						Sleep(10);
					}
					fileContent = multiSer->Recv(&mclien_socket->first, &practicalETX);
			//		cout << "RecvFile: 出临界区" << endl;
				//	ReleaseMutex(Lock);//解锁
					if (fileContent == NULL&&practicalETX == ETX)
					{
						cout << "\n一共接收到 " << byte << " 个字节" << endl;
						practicalETX = 0;
						byte = 0;
						mclien_socket++;
						ReleaseSemaphore(hSemp4, 1, NULL);//释放信号量的占有权	V(S)  加一
						break;
					}
					else if (fileContent == NULL)
					{
						while (TRUE)
						{
							if (fileContent != NULL)
								break;
							fileContent = multiSer->Recv(&mclien_socket->first, &practicalETX);
						}
					}
					ReleaseSemaphore(hSemp4, 1, NULL);//释放信号量的占有权	V(S)  加一
				}
			}
			else if (practicalETX == 0)
			{
				byte = 0;
				mclien_socket++;
			}
		}
		Sleep(10);
	}
	return 0;
	//		//TCP接收消息
// 	USHORT byte = 0;
// 	TCPTransfer * multiSer = (TCPTransfer*)pM;
// 	while (TRUE)
// 	{
// 		Sleep(10);
// 		int practicalETX = 0;
// 		map<SOCKET, ClientInfo>::iterator mclien_socket = fmap_Clien.begin();
// 		while (mclien_socket != fmap_Clien.end())//如果有客户端连接了，就进去
// 		{
// 			Sleep(10);
// 			char *fileContent = multiSer->Recv(&mclien_socket->first, &practicalETX);
// 			if (practicalETX == 1)//如果practicalETX大于0，说明已经接收到数据了
// 			{
// 				USHORT num = strlen(fileContent);
// 				byte += num;
// 				//thread_six_open = TRUE;
// 				GetLocalTime(&ftime);		//获取当地的当前系统日期和时间,存放在ftime结构体中;
// 				char sDateTime[30] = { "0" };
// 				sprintf_s(sDateTime, "%4d-%2d-%2d %2d:%2d:%2d", ftime.wYear, ftime.wMonth, ftime.wDay, ftime.wHour, ftime.wMinute, ftime.wSecond);
// 				cout << sDateTime << "\n接收到 " << inet_ntoa(rfilesize.Sentaddr.sin_addr) << " 传来的 " << filesize.filename << " 文件" << endl;
// 				recv_information_que.push(fileContent);//存放发送的和接收的文件信息队列
// 				while (TRUE)
// 				{
// 					Sleep(10);
// 					fileContent = multiSer->Recv(&mclien_socket->first, &practicalETX);
// 					if (fileContent==NULL)
// 					{
// 						cout << "\n一共接收到 " << byte << " 个字节" << endl;
// 						break;
// 					}
// 					num = strlen(fileContent);
// 					byte += num;
// 					recv_information_que.push(fileContent);//存放发送的和接收的文件信息队列
// 				}
// 			}
// 			else if (practicalETX == 0)
// 			{
// 				byte = 0;
// 				mclien_socket++;
// 			}
// 		}
// 	}
// 	return 0;
}



DWORD WINAPI FileUnpack(LPVOID pM)	//文件解包
{
	//			//TCP接收消息
	// 	int practicalETX = 0, ETX = 0;// ETX 希望传输次数, practicalETX 实际传输次数;
	// 	while (TRUE)
	// 	{
	// 		Sleep(100);
	// 		if (recv_information_que.empty() == false)
	// 		{
	// 			char *a = recv_information_que.front();
	// 			cout << a;
	// 			recv_information_que.pop();
	// 			delete[]a;

	FileMaster * multiSer = (FileMaster*)pM;
	ULONG practicalETX = 0, ETX = 0;// ETX 希望传输次数, practicalETX 实际传输次数;
	fstream fFile;
	char path[1000];//文件存放路径
	int num = 0;
	while (TRUE)
	{
		Sleep(10);
		if (recv_information_que.empty() == false)
		{
			WaitForSingleObject(queueLock, INFINITE);
			FileSize* fileContent = recv_information_que.front();
			ReleaseMutex(queueLock);//解锁
//			cout.setf(ios::hex);
//			cout << "*******提取*****" << fileContent << endl;
//			cout.unsetf(ios::hex);
			
// 			GetLocalTime(&ftime);		//获取当地的当前系统日期和时间,存放在ftime结构体中;
// 			char sDateTime[30] = { "0" };
// 			sprintf_s(sDateTime, "%4d-%2d-%2d %2d:%2d:%2d", ftime.wYear, ftime.wMonth, ftime.wDay, ftime.wHour, ftime.wMinute, ftime.wSecond);
// 			cout << sDateTime << "\n接收到 " << inet_ntoa(fileContent->Sentaddr.sin_addr) << " 传来的 " << fileContent->filename << " 文件" << endl;
			num++;
			if (num == 1)
			{
// 				memset((void*)path, 0, sizeof(path));
// 				char * name = multiSer->File_Storage_Path();//设置文件存放路径
// 				if (name != NULL)
// 				{
// 					strcat(name, fileContent->filename);
// 					strcpy(path, name);
// 				}
// 				else
// 				{
// 					strcpy(path, fileContent->filename);
// 				}
				cout << fileContent->filename << endl;
				strcpy(path, fileContent->filename);
			}
			ETX = fileContent->num;
			fFile.open(path, ios::out | ios::binary /*| ios::app*/);//打开文件
			if (!fFile)
			{
				cout << "文件新建失败！！" << endl;
				system("pause");
			}
			while (true)//解包
			{
				WaitForSingleObject(hSemp4, INFINITE);//等待信号量 ；INFINITE  无限等待（时间）P(S)减一
				 //加锁,没上锁的话就自己锁上，否则等着
//				cout << "FileUnpack: 等待进入临界区" << endl;
				
//				cout << "FileUnpack: 进临界区" << endl;
				if (recv_information_que.empty() == false && fileContent == NULL)
				{		
					WaitForSingleObject(queueLock, INFINITE);
					fileContent = recv_information_que.front();
					ReleaseMutex(queueLock);//解锁
//					cout.setf(ios::hex);
//					cout << "*******提取*****" << fileContent << endl;
//					cout.unsetf(ios::hex);
				}
				if (fileContent != NULL)
				{
					recv_information_que.pop();
					WaitForSingleObject(fileLock, INFINITE);
					cout << fileContent->filename << endl;
					fFile.write(fileContent->fileContent, fileContent->fileContentSize);
					ReleaseMutex(fileLock);//解锁
					++practicalETX;
					process = (float)ETX / (float)practicalETX;
					delete[]fileContent;
					fileContent = NULL;
					
				}
//				cout << practicalETX << "---" << ETX << endl;
//				cout << "FileUnpack: 出临界区" << endl;	
				ReleaseSemaphore(hSemp3, 1, NULL);//释放信号量的占有权	V(S)  加一
				if (practicalETX >= ETX)
				{
					cout << "写入完成！" << endl;
					process = 0;
					break;
				}
				
				Sleep(10);
			}
			fFile.close();
		}
	}
	return 0;
}