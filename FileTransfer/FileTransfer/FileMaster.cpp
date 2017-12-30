#include "FileMaster.h"
extern map<SOCKET, ClientInfo> fmap_Clien;
extern ClientInfo clientInfo;
extern FileSize filesize, rfilesize;
extern HANDLE Thread[7];			//�߳���
extern TCPTransfer fTCPTransfer;
extern UDPTransfer fUDPTransfer;
extern SYSTEMTIME ftime;//���ʱ��
extern queue<FileSize*> send_information_que, recv_information_que;//��ŷ��͵ĺͽ��յ��ļ���Ϣ����
extern float process;		//��ʾ��ǰ�������
extern queue<UDPcontent> information_UDP;//���UDP���յ���Ϣ����




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
	fTCPTransfer.SetIOType(1);// 1 �Ƿ�����
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
		system("cls");//����
		/*gotoy(22, 7);*///ָ��λ����ʾ
		cout << "1���ļ�����" << endl;
		cout << "2����Ϣ����" << endl;
		cout << "3���˳�����" << endl;
		cout << "��ѡ�������";
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
	Thread[0] = CreateThread(NULL, 0, ReceivesConnection, NULL, 0, NULL);		//���������߳�
	Thread[2] = CreateThread(NULL, 0, Recvmessage, NULL, 0, NULL);				//������Ϣ�߳�
	Thread[4] = CreateThread(NULL, 0, RecvFile, this, 0, NULL);					 //�����ļ��߳�
	Thread[3] = CreateThread(NULL, 0, SendFile, NULL, 0, NULL);			//�����ļ��߳�
	Thread[6] = CreateThread(NULL, 0, FileUnpack, this, 0, NULL);				//�ļ�����߳�
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
		CloseHandle(Thread[i]); //�ر�һ���ں˶������а����ļ����ļ�ӳ�䡢���̡��̡߳���ȫ��ͬ�������
//	WSACleanup();/*WSACleanup���������Socket��İ󶨲����ͷ�Socket����ռ�õ�ϵͳ��Դ��*/
}

void FileMaster::TransferFiles()
{
	/*  1���½�����
		2�����ڴ���*/
	bool judeg = true;
	while (judeg)
	{
		system("cls");//����
		//gotoy(22, 7);//ָ��λ����ʾ
		cout << "1���½�����" << endl;
		cout << "2�����ڴ���" << endl; 
		cout << "3���鿴�����ӵĿͻ�����Ϣ" << endl;
		cout << "4��������һ��" << endl;
		cout << "��ѡ�������";
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
		system("cls");//����
		cout << "1��������Ϣ" << endl;
		cout << "2���鿴��Ϣ" << endl;
		cout << "3��������һ��" << endl;
		cout << "��ѡ�������";
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



//�����ļ����·��
char * FileMaster::File_Storage_Path()
{
	bool judeg = true;
	while (judeg)
	{
		cout << "�Ƿ��޸��ļ����·��  Y/N" << endl;
		char a = getch();
		if (a == 'Y' || a == 'y')
		{
			char path[400] = { "0" };
			memset(&path, 0, sizeof(path));
			cout << "�����ļ����·��(��˫\\) : ";
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
	unsigned short Port = 0;   // ������Ϣ����
	SOCKET sock = 0;
	TransferMode(addr_C_addr, &Port, &sock);
	
	if (type == SOCK_STREAM)
	{
		/*����д�����ļ�����*/
		if (strcmp(addr_C_addr, "0") > 0)
			filesize.sock = fTCPTransfer.Connect(addr_C_addr, Port);
		else
			filesize.sock = fTCPTransfer.Connect(sock);
		Thread[5] = CreateThread(NULL, 0, FilePackage, NULL, 0, NULL);				 //�ļ�����߳�
 	//	WaitForSingleObject(Thread[5], INFINITE);
		CloseHandle(Thread[5]); //�ر�һ���ں˶������а����ļ����ļ�ӳ�䡢���̡��̡߳���ȫ��ͬ�������
	}
	else if (type == SOCK_DGRAM)
	{
		fUDPTransfer.Connect_U(addr_C_addr, Port);
		
/*����дudp����Ϣ*/
		Thread[1] = CreateThread(NULL, 0, Sendmessage, NULL, 0, NULL);				//������Ϣ�߳�
		WaitForSingleObject(Thread[1], INFINITE);
		CloseHandle(Thread[1]); //�ر�һ���ں˶������а����ļ����ļ�ӳ�䡢���̡��̡߳���ȫ��ͬ�������
	}

}

void FileMaster::FileTransfer_Underway()//�ļ��������
{

	cout << "�Ѵ����ˣ�";
	cout.precision(2);
	cout << process << "%��" << endl;
	system("pause");
}

void FileMaster::ConnectTheClient()
{
	/*�鿴�Ѿ������ϵĿͻ�����Ϣ*/
	system("cls");//����
	int i = 1;//������ʾ
	char addr[20];//��ַ
	unsigned short port = 0;
	char time[30];
	int num = fmap_Clien.size();
	cout << "�� " << num << " ���ͻ�������" << endl;

	cout << "����" << "   socket" << "   IP��ַ" << "        �˿ں�" << "   ����ʱ��" << endl;
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


void FileMaster::TransferMode(char *addr_C_addr, unsigned short *Port, SOCKET *sock)//ѡ���䷽ʽ)
{
	/*ѡ���䷽ʽ
	1��֪���Է�ip���˿�
	2�����������ӵĿͻ��˵�socket*/
	bool judeg = true;
	while (judeg)
	{
		system("cls");//����
		cout << "1���½��������ӣ�δ���ӶԷ���֪���Է�ip�Ͷ˿ڣ��˿ڲ�������Ĭ�ϣ�" << endl;
		cout << "2��ʹ�������Ӵ��䣨���������ӵĿͻ��˵�socke��    ps��TCPʹ�ã�" << endl;
		cout << "3���鿴�����ӵĿͻ�����Ϣ" << endl;
		cout << "4��������һ��" << endl;
		cout << "��ѡ�������";
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


//����Ҫ���ӵ�ip�Ͷ˿�
void FileMaster::GetIP(char *addr_C_addr, unsigned short *Port)
{
	/*����Ҫ���ӵ�ip�Ͷ˿�*/

	cout << "\n������Է�ip : ";
	cin >> addr_C_addr;

	cout << "\n������Է��˿ڣ���֪�������� 0 ,Ĭ��9998�� : ";
	cin >> *Port;
	if (*Port==0)
	{
		*Port = TCP_SEND;
	}
}

void FileMaster::GetIP(SOCKET * sock)
{
	cout << "\n������Է�socketֵ : ";
	cin >> *sock;
}

void FileMaster::View_New_Message()
{
	/*�鿴���½��յ�����Ϣ*/
	system("cls");//����
	int i = 1;//������ʾ
	unsigned short num = information_UDP.size();
	cout << "�� " << num << " ������Ϣ" << endl;
	cout << "����" << "   ����ʱ��" << "              ��ַ" << "           ��Ϣ����" << endl;
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
DWORD WINAPI ReceivesConnection(LPVOID pM)//���������߳�
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

DWORD WINAPI Sendmessage(LPVOID pM)//������Ϣ
{
	fUDPTransfer.SendTo();
	return 0;
}


DWORD WINAPI Recvmessage(LPVOID pM)//������Ϣ
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
		///*�����ļ�*/
DWORD WINAPI SendFile(LPVOID pM)//�����ļ�
{
	////TCP������Ϣ
// 	int i = 1, result = 0;
// 	while (true)
// 	{
// 		if (thread_three_open)
// 		{
// 			if (send_information_que.empty() == false)
// 			{
// 				result = fTCPTransfer.Send(&filesize);
// 				if (result <= 0)
// 					cout << "\n�������" << endl;
// 				else if (i == filesize.num)
// 				{
// 					cout << "\n�ļ��������" << endl;
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
		WaitForSingleObject(hSemp2, INFINITE);//�ȴ��ź��� ��INFINITE  ���޵ȴ���ʱ�䣩	P(S)��һ
		if (send_information_que.size() <= 0)
		{
			Sleep(10);
		}
		WaitForSingleObject(queueLock, INFINITE);
		FileSize*filesize_TCP = send_information_que.front();
		ReleaseMutex(queueLock);//����
		num = filesize_TCP->num;
		result = fTCPTransfer.Send(&filesize);
	//	cout << ++q << endl;
		if (result ==-1)
		{
			--i;
 	//		cout << "\n�������" << endl;
// 			system("pause");
		}
		else if (i == num)
		{
			cout << "\n�ļ��������" << endl;
			system("pause");
			i = 0; result = 0, num = 0;
// 			hSemp1 = CreateSemaphore(NULL, 100, 100, NULL);//����ļ�
// 			hSemp2 = CreateSemaphore(NULL, 0, 100, NULL);//�����ļ�
		}
		i++;
		ReleaseSemaphore(hSemp1, 1, NULL);//�ͷ��ź�����ռ��Ȩ	V(S)  ��һ
	}
	return 1;
}

////�ļ����
DWORD WINAPI FilePackage(LPVOID pM)//�ļ����
{
	////TCP������Ϣ

	//	fstream fFile;
	//	char path[50] = {"F:\\xfmovie\\file.txt"};
	////	char path[50];
	//// 	memset(&path, 0, sizeof(path));
	//// 	cout << "����Ҫ�����ļ���·��(��˫\\) : ";
	//// 	cin >> path;
	//	strcpy(filesize.filename, Get_File_Name(path));
	//	//һ�������ļ���С�ĺ�������Ϊ��������������
	//	struct _stat info;
	//	_stat(path, &info);//����һ���ļ�·��
	//	int num = info.st_size;//�ļ���С
	//	int totalDegree = num / 10;//�������
	//	if (num % 10)
	//		totalDegree++;
	//	filesize.num = totalDegree;
	//	fFile.open(path, ios::out | ios::binary | ios::_Nocreate);//���ļ�
	//	if (!fFile)
	//	{
	//		cout << "�ļ���ʧ��,�����ļ�·���Ƿ���ȷ" << endl;
	//		return 0;
	//		system("pause");
	//	}

	// 	const unsigned short Con = Content + 1;   // ��ȡ�ļ����ݴ�С
	// 	while (TRUE)
	// 	{
	// 		char *fileContent = new char[Con];	//����
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
	char path[2000] = { "F:\\Ѹ������\\��Ӱ\\Dead.Island.Riptide.Definitive.Edition.CHS.1.1-ALI213\\Dead.Island.Riptide.Definitive.Edition.CHS.1.1-ALI213.part01.rar" };

	//	char path[50];
	// 	memset(&path, 0, sizeof(path));
	// 	cout << "����Ҫ�����ļ���·��(��˫\\) : ";
	// 	cin >> path;
	char filename[MAX_PATH] = "0";
	strcpy(filename, Get_File_Name(path));
	//һ�������ļ���С�ĺ�������Ϊ��������������
	struct _stat info;
	_stat(path, &info);//����һ���ļ�·��
	ULONG num = info.st_size;//�ļ���С
	ULONG totalDegree = num / Content;//�������
	if (num % Content)
		totalDegree++;
	fFile.open(path, ios::in | ios::binary | ios::_Nocreate);//���ļ�
	if (!fFile)
	{
		cout << "�ļ���ʧ��,�����ļ�·���Ƿ���ȷ" << endl;
		return 0;
		system("pause");
	}

	while (num > 0)
	{
		WaitForSingleObject(hSemp1, INFINITE);//�ȴ��ź��� ��INFINITE  ���޵ȴ���ʱ�䣩	P(S)��һ
		FileSize*filesize_TCP = new FileSize;
		memset((void*)filesize_TCP, 0, sizeof(FileSize));
		strcpy(filesize_TCP->filename, filename);	//�����ļ���
		filesize_TCP->num = totalDegree;			//�������
		filesize_TCP->sock = filesize.sock;			//���Ͷ���

		filesize_TCP->fileContentSize = (num > Content ? Content : num);//ÿ�η��͵�Content�ֽڣ�����ʱ����num;

		if (num > Content)//����ļ���С����filesize_TCP->fileContent��
		{
			num -= Content;
			WaitForSingleObject(fileLock, INFINITE);
			if (!fFile.read(filesize_TCP->fileContent, filesize_TCP->fileContentSize))
				cout << "read error!" << endl;//��ȡ���ݣ�10���ֽڣ�
			send_information_que.push(filesize_TCP);
			ReleaseMutex(fileLock);//����
			if (send_information_que.size()>40)
			{
				Sleep(10);
			}
			ReleaseSemaphore(hSemp2, 1, NULL);//�ͷ��ź�����ռ��Ȩ	V(S)  ��һ
		}
		else//����ļ���С�պõ��ڻ���С��filesize_TCP->fileContent�������ֱ������
		{
			num -= filesize_TCP->fileContentSize;
			fFile.read(filesize_TCP->fileContent, filesize_TCP->fileContentSize);
			send_information_que.push(filesize_TCP);
			ReleaseSemaphore(hSemp2, 1, NULL);//�ͷ��ź�����ռ��Ȩ	V(S)  ��һ
			break;
		}
		Sleep(10);
	}
	fFile.close();
	return 0;
}

			// /*�����ļ�*/
DWORD WINAPI RecvFile(LPVOID pM)	//�����ļ�
{
	TCPTransfer * multiSer = (TCPTransfer*)pM;
	while (TRUE)
	{
		int practicalETX = 0; ULONG byte = 0;
		map<SOCKET, ClientInfo>::iterator mclien_socket = fmap_Clien.begin();
		while (mclien_socket != fmap_Clien.end())//����пͻ��������ˣ��ͽ�ȥ
		{
			FileSize* fileContent = multiSer->Recv(&mclien_socket->first, &practicalETX);
			if (practicalETX == 1)//���practicalETX����0��˵���Ѿ����յ�������
			{
				ULONG ETX = fileContent->num;
				while (TRUE)
				{	//�����ļ�
					WaitForSingleObject(hSemp3, INFINITE);//�ȴ��ź��� ��INFINITE  ���޵ȴ���ʱ�䣩	P(S)��һ
			//		cout << "RecvFile: �ȴ������ٽ���" << endl;
			//		WaitForSingleObject(Lock, INFINITE); //����,û�����Ļ����Լ����ϣ��������
			//		cout << "RecvFile: ���ٽ���" << endl;					
					WaitForSingleObject(queueLock, INFINITE);
					recv_information_que.push(fileContent);//��ŷ��͵ĺͽ��յ��ļ���Ϣ����
					byte += fileContent->fileContentSize;
					fileContent = NULL;	
					ReleaseMutex(queueLock);//����
			//		cout.setf(ios::hex);
			//		cout << "���" << fileContent << endl;
			//		cout.unsetf(ios::hex);
					if (recv_information_que.size()>10)
					{
						Sleep(10);
					}
					fileContent = multiSer->Recv(&mclien_socket->first, &practicalETX);
			//		cout << "RecvFile: ���ٽ���" << endl;
				//	ReleaseMutex(Lock);//����
					if (fileContent == NULL&&practicalETX == ETX)
					{
						cout << "\nһ�����յ� " << byte << " ���ֽ�" << endl;
						practicalETX = 0;
						byte = 0;
						mclien_socket++;
						ReleaseSemaphore(hSemp4, 1, NULL);//�ͷ��ź�����ռ��Ȩ	V(S)  ��һ
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
					ReleaseSemaphore(hSemp4, 1, NULL);//�ͷ��ź�����ռ��Ȩ	V(S)  ��һ
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
	//		//TCP������Ϣ
// 	USHORT byte = 0;
// 	TCPTransfer * multiSer = (TCPTransfer*)pM;
// 	while (TRUE)
// 	{
// 		Sleep(10);
// 		int practicalETX = 0;
// 		map<SOCKET, ClientInfo>::iterator mclien_socket = fmap_Clien.begin();
// 		while (mclien_socket != fmap_Clien.end())//����пͻ��������ˣ��ͽ�ȥ
// 		{
// 			Sleep(10);
// 			char *fileContent = multiSer->Recv(&mclien_socket->first, &practicalETX);
// 			if (practicalETX == 1)//���practicalETX����0��˵���Ѿ����յ�������
// 			{
// 				USHORT num = strlen(fileContent);
// 				byte += num;
// 				//thread_six_open = TRUE;
// 				GetLocalTime(&ftime);		//��ȡ���صĵ�ǰϵͳ���ں�ʱ��,�����ftime�ṹ����;
// 				char sDateTime[30] = { "0" };
// 				sprintf_s(sDateTime, "%4d-%2d-%2d %2d:%2d:%2d", ftime.wYear, ftime.wMonth, ftime.wDay, ftime.wHour, ftime.wMinute, ftime.wSecond);
// 				cout << sDateTime << "\n���յ� " << inet_ntoa(rfilesize.Sentaddr.sin_addr) << " ������ " << filesize.filename << " �ļ�" << endl;
// 				recv_information_que.push(fileContent);//��ŷ��͵ĺͽ��յ��ļ���Ϣ����
// 				while (TRUE)
// 				{
// 					Sleep(10);
// 					fileContent = multiSer->Recv(&mclien_socket->first, &practicalETX);
// 					if (fileContent==NULL)
// 					{
// 						cout << "\nһ�����յ� " << byte << " ���ֽ�" << endl;
// 						break;
// 					}
// 					num = strlen(fileContent);
// 					byte += num;
// 					recv_information_que.push(fileContent);//��ŷ��͵ĺͽ��յ��ļ���Ϣ����
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



DWORD WINAPI FileUnpack(LPVOID pM)	//�ļ����
{
	//			//TCP������Ϣ
	// 	int practicalETX = 0, ETX = 0;// ETX ϣ���������, practicalETX ʵ�ʴ������;
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
	ULONG practicalETX = 0, ETX = 0;// ETX ϣ���������, practicalETX ʵ�ʴ������;
	fstream fFile;
	char path[1000];//�ļ����·��
	int num = 0;
	while (TRUE)
	{
		Sleep(10);
		if (recv_information_que.empty() == false)
		{
			WaitForSingleObject(queueLock, INFINITE);
			FileSize* fileContent = recv_information_que.front();
			ReleaseMutex(queueLock);//����
//			cout.setf(ios::hex);
//			cout << "*******��ȡ*****" << fileContent << endl;
//			cout.unsetf(ios::hex);
			
// 			GetLocalTime(&ftime);		//��ȡ���صĵ�ǰϵͳ���ں�ʱ��,�����ftime�ṹ����;
// 			char sDateTime[30] = { "0" };
// 			sprintf_s(sDateTime, "%4d-%2d-%2d %2d:%2d:%2d", ftime.wYear, ftime.wMonth, ftime.wDay, ftime.wHour, ftime.wMinute, ftime.wSecond);
// 			cout << sDateTime << "\n���յ� " << inet_ntoa(fileContent->Sentaddr.sin_addr) << " ������ " << fileContent->filename << " �ļ�" << endl;
			num++;
			if (num == 1)
			{
// 				memset((void*)path, 0, sizeof(path));
// 				char * name = multiSer->File_Storage_Path();//�����ļ����·��
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
			fFile.open(path, ios::out | ios::binary /*| ios::app*/);//���ļ�
			if (!fFile)
			{
				cout << "�ļ��½�ʧ�ܣ���" << endl;
				system("pause");
			}
			while (true)//���
			{
				WaitForSingleObject(hSemp4, INFINITE);//�ȴ��ź��� ��INFINITE  ���޵ȴ���ʱ�䣩P(S)��һ
				 //����,û�����Ļ����Լ����ϣ��������
//				cout << "FileUnpack: �ȴ������ٽ���" << endl;
				
//				cout << "FileUnpack: ���ٽ���" << endl;
				if (recv_information_que.empty() == false && fileContent == NULL)
				{		
					WaitForSingleObject(queueLock, INFINITE);
					fileContent = recv_information_que.front();
					ReleaseMutex(queueLock);//����
//					cout.setf(ios::hex);
//					cout << "*******��ȡ*****" << fileContent << endl;
//					cout.unsetf(ios::hex);
				}
				if (fileContent != NULL)
				{
					recv_information_que.pop();
					WaitForSingleObject(fileLock, INFINITE);
					cout << fileContent->filename << endl;
					fFile.write(fileContent->fileContent, fileContent->fileContentSize);
					ReleaseMutex(fileLock);//����
					++practicalETX;
					process = (float)ETX / (float)practicalETX;
					delete[]fileContent;
					fileContent = NULL;
					
				}
//				cout << practicalETX << "---" << ETX << endl;
//				cout << "FileUnpack: ���ٽ���" << endl;	
				ReleaseSemaphore(hSemp3, 1, NULL);//�ͷ��ź�����ռ��Ȩ	V(S)  ��һ
				if (practicalETX >= ETX)
				{
					cout << "д����ɣ�" << endl;
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