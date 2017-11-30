#include "GluttonousSnake.h"



GluttonousSnake::GluttonousSnake()
{
	Mapin();
}

GluttonousSnake::~GluttonousSnake()
{
	if (Map)
		delete[]Map;
	if (snake)
	{
		DeleteSnake();
		snake = NULL;
	}
}

void GluttonousSnake::MainMenu()
{
	bool q = true;
	while (q)
	{
		system("cls");
		gotoy(22, 7);
		cout << "1����ʼ��Ϸ" << endl;
		gotoy(22, 9);
		cout << "2���˳���Ϸ" << endl;
		char a = getch();
		if (a=='1')
			GameInterface();
		system("pause");
	}
}
//��ʼ��Ϸ
void GluttonousSnake::GameInterface()
{
	system("cls");
	if (snake)
		DeleteSnake();
	char a ,b;
	bool p = false;
	Mapin();
	NewSnake();
	ShowMap();
	a = 's';
	while (true)
	{
		NEXT();
		SnakeFood();
		Sleep(Speed);
		if (kbhit())
		{
			b = getch();
			p = Direction(a, b);
			if (b == ' ')
				Pause();
		}
		if (p)
		{
			a = b;
			p = false;
		}
		control(a);
	}
}
//��ʾ��ͼ
void GluttonousSnake::ShowMap()
{
	system("cls");
	Food();
	gotoy(0,0);
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			switch (Map[i][j])
			{
			case '0':cout << "  "; break;
			case '1':cout << "��"; break;
			case '2':cout << "��"; break;
			case '3':cout << "��"; break;
			case '5':cout << "��"; break;
			case '9':cout << "��"; break;
			default:
				break;
			}
		}
		switch (i)
		{
		case 3:cout << "�ٶȣ� "; break;
		case 4:cout << "                 " << CustomsPass; break;
		case 7:cout << "�÷֣�"; break;
		case 12:cout << "    w,a,s,d,���Ʒ���"; break;
		case 13:break;
		case 14:cout << "    �ո����ͣ"; break;
		default:
			break;
		}
		cout << endl;
	}
}
//�ٿ�
void GluttonousSnake::control(char z)
 {
	char tem;
	bool a = true;
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			int n, m;
			//�жϷ���
			switch (z)
			{
			case 'a':n = i; m = j - 1; break;
			case 's':n = i + 1; m = j; break;
			case 'd':n = i; m = j + 1; break;
			case 'w':n = i - 1; m = j; break;
			default:
				break;
			}
			//�ҵ�ͷ��λ��
			if (Map[i][j] == '1')
			{
				//���ǰ���λ����ǽ����������
				if (Map[n][m] == '9' || Map[n][m] == '2')
				{
					//��Ϸ����
					GameOver();
					MainMenu();
				}
				//���ǰ���λ���ǿյ�
				else if (Map[n][m] == '0')
					Move(&Map[n][m], 0);
				//���ǰ���λ����ʳ��
				else if (Map[n][m] == '5')
				{
					Map[n][m] = Map[i][j];
					Map[i][j] = '2';
					Move(&Map[n][m], 5);
				}
				a = false;
				break;
			}
		}
		if (!a)
			break;
	}
 }
//��ʼ��ͼ
void GluttonousSnake::Mapin()
{
	snake = NULL;
	len = 3;
	score = 0;
	CustomsPass = 1;
	Speed = 201;
	bool Food1 = true;
	strcpy(Map[0], "9999999999999999999999");
	for (int i = 1; i < 10; i++)
		strcpy(Map[i], "9000000000000000000009");
	strcpy(Map[10], "9000000000020000000009");
	strcpy(Map[11], "9000000000020000000009");
	strcpy(Map[12], "9000000000010000000009");
	for (int i = 13; i < 21; i++)
		strcpy(Map[i], "9000000000000000000009");
	strcpy(Map[21], "9999999999999999999999");
}
//ʳ��
void GluttonousSnake::Food()
{
	srand(time(0));
	while (Food1)
	{
		int i = rand() % MAP_HEIGHT; 
		int j = rand() % MAP_WIDTH;
		if (Map[i][j] == '0')
		{
			Map[i][j] = '5';
			gotoy(61, 8); 
			cout << "   ";
			gotoy(61, 8); 
			cout << score;;
			Food1 = false;
			break;
		}
	}
}

//ɾ��������
void GluttonousSnake::DeleteSnake()
{
	Snake *p1, *p2;
	for (p1 = snake; p1; p1 = p2)
	{
		p2 = p1->w;
		delete p1;
	}
}
//����������
void GluttonousSnake::NewSnake()
{
	Snake *p1, *p2;
	p1 = snake = new Snake;
	for (int i = 12; i > 9; i--)
	{
		p2 = new Snake;
		if (i==10)
		{
			delete p2;
			p2 = NULL;
		}
		p1->s = &Map[i][11];
		p1->w = p2;
		p1 = p2;
	}
}
//�жϷ�����ȷ��
bool GluttonousSnake::Direction(char a, char b)
{
	if ((a == 'w'||a == 'W')&&(b == 'a' || b == 'A' || b == 'd' || b == 'D'))
		return true;
	else if ((a == 's'||a == 'S') && (b == 'a' || b == 'A' || b == 'd' || b == 'D'))
		return true;
	else if ((a == 'a'||a == 'A') && (b == 'w' || b == 'W' || b == 's' || b == 'S'))
		return true;
	else if ((a == 'd'||a == 'D') && (b == 'w' || b == 'W' || b == 's' || b == 'S'))
		return true;
	return false;
}
//��һ���жϼ�����
void GluttonousSnake::NEXT()
{
	int i = score % 100;
	if (score)
	{
		if (!i)
		{
			gotoy(61, 4); 
			cout << ++CustomsPass;
			Speed = Speed - 20;
			score = 0;
			gotoy(61, 8);
			cout << score;
		}
	}
}
//��ͣ
void GluttonousSnake::Pause()
{
	bool b = false;
	gotoy(50, 17); cout << "1��������Ϸ";
	gotoy(50, 18); cout << "2�����¿�ʼ";
	gotoy(50, 19); cout << "3���˳���Ϸ";
	while (!b)
	{
		switch (getch())
		{
		case '1': gotoy(50, 17); cout << "          ";
			gotoy(50, 18); cout << "          ";
			gotoy(50, 19); cout << "          ";
			b = true;break;
		case '2':b = true; GameInterface(); break;
		case '3':exit(1); break;
		default:break;
		}
	}
}
//�ƶ�����
void GluttonousSnake::Move(char *m,int i)
{
	char *p1, *p2;
	char tem;
	Snake *s1, *s2;
	p2 = m;
	if (i == 0)
	{
		for (s1 = snake; s1; s1 = s2)
		{
			tem = *p2;
			s2 = s1->w;
			p1 = s1->s;
			s1->s = p2;
			*s1->s = *p1;
			p2 = p1;
			*p2 = tem;
		}
	}
	else if (i==5)
	{
		Food1 = true;
		score += 10;
		len++;
		s1 = new Snake;
		s2 = snake->w;
		snake->w = s1;
		s1->w = s2;
		p1 = snake->s;
		snake->s = p2;
		s1->s = p1;
	}
}
//��ȡ�䶯���ߺ�ʳ��
void GluttonousSnake::SnakeFood()
{
	Food();
	int m;
	for (int i = 1; i < 21; i++)
	{
		for (int j = 1, m = 2; j < 21; j++, m += 2)
		{
			gotoy(m, i);
			switch (Map[i][j])
			{
			case '0':cout << "  "; break;
			case '1':cout << "��"; break;
			case '2':cout << "��"; break;
			case '3':cout << "��"; break;
			case '5':cout << "��"; break;
			case '9':cout << "��"; break;
			default:
				break;
			}
			cout << endl;
		}
	}
}

void GluttonousSnake::gotoy(int x, int y)
{
	COORD coo;
	coo.X = x;
	coo.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coo);
}

void GluttonousSnake::GameOver()
{
	gotoy(18, 11);
	cout << "��Ϸ������";
	gotoy(16, 12);
	system("pause");
}
