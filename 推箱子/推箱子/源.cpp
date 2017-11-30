#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include<string.h>
FILE*map;
#define N 257
#define M 258
char map1[15][20],map0[15][20];//地图
char choose;//choose是开始界面选择;
void ksjm();//开始界面-----函数
void dqdt(int n);//文件内获得地图-----函数
void czsm();//操作说明-----函数
void gbyx();//退出游戏-----函数

int main()
{
	//打开地图文件
	char i;
	if ((map = fopen("map.txt", "r")) == NULL)
	{
		printf("没有地图文件");
		exit(0);
	}
	//显示游戏界面-----函数
	ksjm();
	//游戏显示界面选择返回
	if (choose == '3')
	{
		fclose(map);
		system("pause");
		return 0;
	}
	return 0;
}

//显示游戏界面-----函数
void ksjm()
{
	system("cls");
 	printf("\n\n\n\n\t\t\t推箱子小游戏42关版本\n\n\n\t\t\t1.开始游戏\n\t\t\t2.操作说明\n\t\t\t3.退出游戏\n");
	//游戏界面选择，1，开始游戏  2，操作说明   3，退出游戏	
	choose = getch();
	while (choose != '3')
	{
		if (choose == '1')
			dqdt(0);
		else if (choose == '2')
			czsm();//操作说明-----函数
		else
			choose = getch();
	}
}

//文件内获得地图-----函数
void dqdt(int n)
{
	void estimate(int w);
	void MapDisplay(int n);//地图显示
	char cz;
	int i, j, i1, j1, k = 0, k1 = 0;
	int guanka();//关卡选择，显示-----函数
	system("cls");
	printf("\n\n\n\n\t\t\t第 %d 关\n\n\n\n\n\n\n\n\n\n\n\n\n按任意键进入游戏", n+1);
	getch();
	system("cls");
	if (n >= 42)
	{
		printf("最多只有42关，游戏结束");
		fclose(map);
		system("pause");
		return ;
	}
	else if (n < 10)
	{
		fseek(map, n* N, 0);
		//fgets读取中遇到换行符自动读取结束
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
		//fgets读取中遇到换行符自动读取结束
		for (i = 0;i < 15;i++)
		{
			fgets(map1[i], M, map);
			strcpy(map0[i], map1[i]);
		}
	}
	MapDisplay(n);//地图显示
	//检查地图中有多少个箱子
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
			dqdt(n);//文件内获得地图-----函数
		else if (cz == '2')
			ksjm();//显示游戏界面
		else if (cz == '3')
		{
			n = guanka();//关卡选择，显示-----函数;//选关
			dqdt(n);//文件内获得地图-----函数
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

//操作说明-----函数
void czsm()
{
	system("cls");
	char i;
	printf("\n\n\n\n\t\t操作说明:每关都有箱子，玩家操作人物来推动\n\t\t箱子，直到将所有的箱子推到目的地才算过关.\n\t\t人物图标:♀\n\t\t目地地图标 : ×\n\t\t墙图标 : ■\n\t\t箱子图标 : □\n\t\t箱子图标(在目的地上) : ☆\n\t\tW : 人物向上.\n\t\tS : 人物向下.\n\t\tA : 人物向左.\n\t\tD : 人物向右.\n\n\n\n按E键返回菜单");
	while (i = getch())
	{
		if (i == 'E' || i == 'e')
			break;
	}
	ksjm();//显示游戏界面
}

//关卡选择，显示-----函数;
int guanka()//关卡选择，显示-----函数
{
	system("cls");
	int i;
	printf("请输入选择的关卡：");
	scanf("%d", &i);
	getchar();
	return i-1;
}

//地图显示,,输出map1数组中的内容；每行有18个字符，地图字符加上\0和换行符
void MapDisplay(int n)
{
	system("cls");
	int i, j;
	printf("\t\t\t\t第 %d 关\n\t\t\t",n+1);
	for (i = 1;i < 15;i++)
	{
		for (j = 0;j <= 18;j++)
		{
			switch (map1[i][j])
			{
			case '0':printf("  ");break;
			case '1':printf("■");break;
			case '2':printf("  ");break;
			case '3':printf("×");break;
			case '4':printf("□");break;
			case '5':printf("★");break;
			case '6':printf("♀");break;
			default:break;
			}
		}
		printf("\n\t\t\t");
	}
	printf("\t1.重新开始\n\t\t\t\t2.返回菜单\n\t\t\t\t3.选关\n\n\n\n\n2017-7-28\n12:11制作完成\n制作人：Zz");
}

//游戏操作---函数;
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
			{//判断人前面是不是墙
				if (map1[i][j] == '6'&&map1[x1][y1] != '1')
				{
					//判断 人前面是空地
					if (map1[i][j] == '6'&&map1[x1][y1] == '2')
					{
						if (map0[i][j] == '3')//如果人的原来位置是终点
						{
							map1[x1][y1] = map1[i][j];
							map1[i][j] = '3';
							return;
						}
						else//如果人的原来位置不是终点
						{
							tmp = map1[x1][y1];
							map1[x1][y1] = map1[i][j];
							map1[i][j] = tmp;
							return;
						}
					}
					//判断 人前面是箱子
					else if (map1[i][j] == '6' && (map1[x1][y1] == '4' || map1[x1][y1] == '5'))
					{
						//判断箱子前面是空地
						if (map1[x2][y2] == '2')
						{
							if (map0[i][j] == '3')//如果人的位置是终点
							{
								if (map0[x1][y1] == '3')//如果箱子的位置是终点
								{
									map1[x2][y2] = '4';
									map1[x1][y1] = map1[i][j];
									map1[i][j] = '3';
								}
								else//如果箱子的位置不是是终点
								{
									map1[x2][y2] = map1[x1][y1];
									map1[x1][y1] = map1[i][j];
									map1[i][j] = '3';
								}
							}
							else//如果人不是终点
							{
								if (map0[x1][y1] == '3')//如果箱子的位置是终点
								{
									map1[x2][y2] = '4';
									map1[x1][y1] = map1[i][j];
									map1[i][j] = '2';
								}
								else//如果箱子的位置不是终点
								{
									tmp = map1[x2][y2];
									map1[x2][y2] = map1[x1][y1];
									map1[x1][y1] = map1[i][j];
									map1[i][j] = tmp;
									return;
								}
							}
						}
						//判断箱子前面是终点
						else if (map1[x2][y2] == '3')
						{
							if (map0[i][j] == '3')//如果人的位置是终点
							{
								tmp = map1[x2][y2];
								map1[x2][y2] = '5';
								map1[x1][y1] = map1[i][j];
								map1[i][j] = tmp;
								return;
							}
							else//如果人的位置不是终点
							{
								map1[x2][y2] = '5';
								map1[x1][y1] = map1[i][j];
								map1[i][j] = '2';
							}
						}
						//箱子前面是箱子或者墙
						else
							return;
					}
					//判断 人前面是终点
					else if (map1[i][j] == '6'&&map1[x1][y1] == '3')
					{
						if (map0[i][j] == '3')//如果人的原来位置是终点
						{
							tmp = map1[x1][y1];
							map1[x1][y1] = map1[i][j];
							map1[i][j] = tmp;
							return;
						}
						else//如果人的原来位置不是终点
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