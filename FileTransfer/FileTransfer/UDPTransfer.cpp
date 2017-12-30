#include "UDPTransfer.h"
extern SYSTEMTIME ftime;
extern queue<UDPcontent> information_UDP;//���UDP���յ���Ϣ����



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
	if (INVALID_SOCKET == fUDPSeversocket)//INVALID_SOCKET  0  ����Ч�׽���
	{
		cout << "socket failed!" << endl;
		WSACleanup();/*WSACleanup���������Socket��İ󶨲����ͷ�Socket����ռ�õ�ϵͳ��Դ��*/
	}
}

void UDPTransfer::Bind(const USHORT& inPort)
{
	USHORT flag = inPort;
	addrUDPServ.sin_family = AF_INET;//AF_INET�ǻ�������:UDP TCP�ȡ�
	addrUDPServ.sin_port = htons(flag);//htons�����������ֽ�˳��ת��Ϊ�����ֽ�˳��(to network short) 
	addrUDPServ.sin_addr.S_un.S_addr = htonl(INADDR_LOOPBACK);// inet_addr��IP��ַ�ӵ�����ʽת���������ֽڸ�ʽ���͡�
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
			cout << "UDP�˿�:" << flag << endl;
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
	addrSrv.sin_port = htons(port);//htons�����������ֽ�˳��ת��Ϊ�����ֽ�˳��(to network short) 
	addrSrv.sin_addr.S_un.S_addr = inet_addr(addr);// inet_addr��IP��ַ�ӵ�����ʽת���������ֽڸ�ʽ���͡�

	//       ���ù㲥��ʽ�뽫��������������ΪSO_BROADCAST
//setsockopt(sockListener, SOL_SOCKET, SO_BROADCAST, (CHAR *)&fBroadcast, sizeof(BOOL));
	//  �������ã�ע��Ҫ��IP��ַ��ΪINADDR_BROADCAST����ʾ���͹㲥UDP���ݱ�
	/*saUdpServ.sin_addr.s_addr = htonl(addr);*/
	return 	sockClient;
}

int UDPTransfer::SendTo()
{
	char buffer[kMaxUDPPacket];
	memset(&buffer, 0, sizeof(buffer));
	cout << "������Ϣ��";
	cin >> buffer;
	getchar();
	int sentBytes = ::sendto(sockClient, buffer, strlen(buffer), 0, (const sockaddr*)&addrSrv, sizeof(struct sockaddr));
	if (sentBytes<0)
	{
		cout << "����ʧ�ܣ�" << endl;
		system("pause");
		return sentBytes;
	}
	cout << "���ͳɹ���" << endl;
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
	/*����˵��:recvfrom()��������Զ��������ָ����socket����������,�������ݴ����ɲ���bufָ����ڴ�ռ�,����lenΪ�ɽ������ݵ���󳤶�.
	����flagsһ����0,������ֵ����ο�recv().����from����ָ�������͵������ַ,�ṹsockaddr��ο�bind()����.����fromlenΪsockaddr�Ľṹ����.
	����ֵ:�ɹ��򷵻ؽ��յ����ַ���, ʧ�ܷ��� - 1.*/
	if (receivedBytes>0)
	{
		UDPcontent *udpcontent = new UDPcontent;
		memset(udpcontent, 0, sizeof(udpcontent));
		GetLocalTime(&ftime);		//��ȡ���صĵ�ǰϵͳ���ں�ʱ��,�����ftime�ṹ����;
		sprintf_s(udpcontent->sDateTime, "%4d-%2d-%2d %2d:%2d:%2d", ftime.wYear, ftime.wMonth, ftime.wDay, ftime.wHour, ftime.wMinute, ftime.wSecond);
		strcpy(udpcontent->buffer, buffer);
		strcpy(udpcontent->addr, inet_ntoa(addrUDPServ.sin_addr));
		information_UDP.push(*udpcontent);
	}
	return 0;
}