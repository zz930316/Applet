#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include<string.h>
FILE*map;
#define N 257
#define M 258
char map1[15][20],map0[15][20];//��ͼ
char choose;//choose�ǿ�ʼ����ѡ��;
void ksjm();//��ʼ����-----����
void dqdt(int n);//�ļ��ڻ�õ�ͼ-----����
void czsm();//����˵��-----����
void gbyx();//�˳���Ϸ-----����

int main()
{
	//�򿪵�ͼ�ļ�
	char i;
	if ((map = fopen("map.txt", "r")) == NULL)
	{
		printf("û�е�ͼ�ļ�");
		exit(0);
	}
	//��ʾ��Ϸ����-----����
	ksjm();
	//��Ϸ��ʾ����ѡ�񷵻�
	if (choose == '3')
	{
		fclose(map);
		system("pause");
		return 0;
	}
	return 0;
}

//��ʾ��Ϸ����-----����
void ksjm()
{
	system("cls");
 	printf("\n\n\n\n\t\t\t������С��Ϸ42�ذ汾\n\n\n\t\t\t1.��ʼ��Ϸ\n\t\t\t2.����˵��\n\t\t\t3.�˳���Ϸ\n");
	//��Ϸ����ѡ��1����ʼ��Ϸ  2������˵��   3���˳���Ϸ	
	choose = getch();
	while (choose != '3')
	{
		if (choose == '1')
			dqdt(0);
		else if (choose == '2')
			czsm();//����˵��-----����
		else
			choose = getch();
	}
}

//�ļ��ڻ�õ�ͼ-----����
void dqdt(int n)
{
	void estimate(int w);
	void MapDisplay(int n);//��ͼ��ʾ
	char cz;
	int i, j, i1, j1, k = 0, k1 = 0;
	int guanka();//�ؿ�ѡ����ʾ-----����
	system("cls");
	printf("\n\n\n\n\t\t\t�� %d ��\n\n\n\n\n\n\n\n\n\n\n\n\n�������������Ϸ", n+1);
	getch();
	system("cls");
	if (n >= 42)
	{
		printf("���ֻ��42�أ���Ϸ����");
		fclose(map);
		system("pause");
		return ;
	}
	else if (n < 10)
	{
		fseek(map, n* N, 0);
		//fgets��ȡ���������з��Զ���ȡ����
		for (i = 0;i < 15;i++)
		{
			fgets(map1[i], N, map);
			strcpy(map0[i], map1[i]);
		}
	}
	else 	if (n > 10)
	{
		fseek(map, 9 * N, 0);
		fseek(map, (n - 9)* M, 1);
		//fgets��ȡ���������з��Զ���ȡ����
		for (i = 0;i < 15;i++)
		{
			fgets(map1[i], M, map);
			strcpy(map0[i], map1[i]);
		}
	}
	MapDisplay(n);//��ͼ��ʾ
	//����ͼ���ж��ٸ�����
	for (i1 = 1;i1 < 15;i1++)
	{
		for (j1 = 0;j1 < 18;j1++)
		{
			if (map0[i1][j1] == '4')
				k++;
		}
	}
	for (i = 0;k != k1;i++)
	{
		cz = getch();
		if (cz == '1')
			dqdt(n);//�ļ��ڻ�õ�ͼ-----����
		else if (cz == '2')
			ksjm();//��ʾ��Ϸ����
		else if (cz == '3')
		{
			n = guanka();//�ؿ�ѡ����ʾ-----����;//ѡ��
			dqdt(n);//�ļ��ڻ�õ�ͼ-----����
		}
		else if (cz == 'a' || cz == 'A')
			estimate(1);
		else if (cz == 's' || cz == 'S')
			estimate(2);
		else if (cz == 'd' || cz == 'D')
			estimate(3);
		else if (cz == 'w' || cz == 'W')
			estimate(4);
		MapDisplay(n);
		for (i1 = 1,k1=0;i1 < 15;i1++)
		{
			for (j1 = 0;j1 < 18;j1++)
			{
				if (map1[i1][j1] == '5')
					++k1;
			}
		}
	}
	dqdt(++n);
	
}

//����˵��-----����
void czsm()
{
	system("cls");
	char i;
	printf("\n\n\n\n\t\t����˵��:ÿ�ض������ӣ���Ҳ����������ƶ�\n\t\t���ӣ�ֱ�������е������Ƶ�Ŀ�ĵز������.\n\t\t����ͼ��:��\n\t\tĿ�ص�ͼ�� : ��\n\t\tǽͼ�� : ��\n\t\t����ͼ�� : ��\n\t\t����ͼ��(��Ŀ�ĵ���) : ��\n\t\tW : ��������.\n\t\tS : ��������.\n\t\tA : ��������.\n\t\tD : ��������.\n\n\n\n��E�����ز˵�");
	while (i = getch())
	{
		if (i == 'E' || i == 'e')
			break;
	}
	ksjm();//��ʾ��Ϸ����
}

//�ؿ�ѡ����ʾ-----����;
int guanka()//�ؿ�ѡ����ʾ-----����
{
	system("cls");
	int i;
	printf("������ѡ��Ĺؿ���");
	scanf("%d", &i);
	getchar();
	return i-1;
}

//��ͼ��ʾ,,���map1�����е����ݣ�ÿ����18���ַ�����ͼ�ַ�����\0�ͻ��з�
void MapDisplay(int n)
{
	system("cls");
	int i, j;
	printf("\t\t\t\t�� %d ��\n\t\t\t",n+1);
	for (i = 1;i < 15;i++)
	{
		for (j = 0;j <= 18;j++)
		{
			switch (map1[i][j])
			{
			case '0':printf("  ");break;
			case '1':printf("��");break;
			case '2':printf("  ");break;
			case '3':printf("��");break;
			case '4':printf("��");break;
			case '5':printf("��");break;
			case '6':printf("��");break;
			default:break;
			}
		}
		printf("\n\t\t\t");
	}
	printf("\t1.���¿�ʼ\n\t\t\t\t2.���ز˵�\n\t\t\t\t3.ѡ��\n\n\n\n\n2017-7-28\n12:11�������\n�����ˣ�Zz");
}

//��Ϸ����---����;
void estimate(int w)
{
	int i, j, tmp,x1, x2, y1, y2;
	for (i = 1;i < 15;i++)
	{
		for (j = 0;j < 18;j++)
		{
			if (map1[i][j] == '6')
			{
				if (w == 1)
				{
					x1 = x2 = i;
					y1 = j - 1;
					y2 = j - 2;
					break;
				}
				else if (w == 2)
				{
					x1 = i + 1;
					x2 = i + 2;
					y1 = y2 = j;
					break;
				}
				else if (w == 3)
				{
					x1 = x2 = i;
					y1 = j + 1;
					y2 = j + 2;
					break;
				}
				else if (w == 4)
				{
					x1 = i - 1;
					x2 = i - 2;
					y1 = y2 = j;
					break;
				}
			}
		}
		if (map1[i][j] == '6')
			break;
	}
	for (i = 1;i < 15;i++)
	{
		for (j = 0;j < 18;j++)
		{
			if (map1[i][j] == '6')
			{//�ж���ǰ���ǲ���ǽ
				if (map1[i][j] == '6'&&map1[x1][y1] != '1')
				{
					//�ж� ��ǰ���ǿյ�
					if (map1[i][j] == '6'&&map1[x1][y1] == '2')
					{
						if (map0[i][j] == '3')//����˵�ԭ��λ�����յ�
						{
							map1[x1][y1] = map1[i][j];
							map1[i][j] = '3';
							return;
						}
						else//����˵�ԭ��λ�ò����յ�
						{
							tmp = map1[x1][y1];
							map1[x1][y1] = map1[i][j];
							map1[i][j] = tmp;
							return;
						}
					}
					//�ж� ��ǰ��������
					else if (map1[i][j] == '6' && (map1[x1][y1] == '4' || map1[x1][y1] == '5'))
					{
						//�ж�����ǰ���ǿյ�
						if (map1[x2][y2] == '2')
						{
							if (map0[i][j] == '3')//����˵�λ�����յ�
							{
								if (map0[x1][y1] == '3')//������ӵ�λ�����յ�
								{
									map1[x2][y2] = '4';
									map1[x1][y1] = map1[i][j];
									map1[i][j] = '3';
								}
								else//������ӵ�λ�ò������յ�
								{
									map1[x2][y2] = map1[x1][y1];
									map1[x1][y1] = map1[i][j];
									map1[i][j] = '3';
								}
							}
							else//����˲����յ�
							{
								if (map0[x1][y1] == '3')//������ӵ�λ�����յ�
								{
									map1[x2][y2] = '4';
									map1[x1][y1] = map1[i][j];
									map1[i][j] = '2';
								}
								else//������ӵ�λ�ò����յ�
								{
									tmp = map1[x2][y2];
									map1[x2][y2] = map1[x1][y1];
									map1[x1][y1] = map1[i][j];
									map1[i][j] = tmp;
									return;
								}
							}
						}
						//�ж�����ǰ�����յ�
						else if (map1[x2][y2] == '3')
						{
							if (map0[i][j] == '3')//����˵�λ�����յ�
							{
								tmp = map1[x2][y2];
								map1[x2][y2] = '5';
								map1[x1][y1] = map1[i][j];
								map1[i][j] = tmp;
								return;
							}
							else//����˵�λ�ò����յ�
							{
								map1[x2][y2] = '5';
								map1[x1][y1] = map1[i][j];
								map1[i][j] = '2';
							}
						}
						//����ǰ�������ӻ���ǽ
						else
							return;
					}
					//�ж� ��ǰ�����յ�
					else if (map1[i][j] == '6'&&map1[x1][y1] == '3')
					{
						if (map0[i][j] == '3')//����˵�ԭ��λ�����յ�
						{
							tmp = map1[x1][y1];
							map1[x1][y1] = map1[i][j];
							map1[i][j] = tmp;
							return;
						}
						else//����˵�ԭ��λ�ò����յ�
						{
							map1[x1][y1] = map1[i][j];
							map1[i][j] = '2';
							return;
						}
					}
				}
				else
					return;
			}
		}
	}
}