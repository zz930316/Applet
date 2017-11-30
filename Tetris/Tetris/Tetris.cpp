#include "Tetris.h"



Tetris::Tetris()
{
	Initialization();
}


Tetris::~Tetris()
{
	delete[]Map;
	delete[]Map2;
	delete[]Diamonds;
}

void Tetris::MainMenu()
{
	system("cls");
	bool a = false;
	gotoy(34, 7);
	cout << "1����ʼ��Ϸ" << endl;
	gotoy(34, 9);
	cout << "2���˳���Ϸ" << endl;
	while (!a)
	{
		geta = getch();
		switch (geta)
		{
		case '1':GameInterface(); break;
		case '2':exit(1); break;
		default:break;
		}
	}
}

//��Ϸ����
void Tetris::GameInterface()
{
	Initialization();
	while (true)
	{
		if (S_Diamonds)
			Stochastic();
		if (Diamonds_Num <= 4)
			Insertion_Map(); 
		ShowMap();
		GameOver();
		if (kbhit())
			Key();
		DropDown();
		Sleep(Time);
	}
}

//��ʾ��ͼ
void Tetris::ShowMap()
{
	system("cls");
	for (int i = 0; i < Map_Height; i++)
	{
		for (int j = 0; j < Map_Width; j++)
		{
			switch (Map[i][j])
			{
			case '0':cout << "  "; break;
			case '1':
			case '2':cout << "��"; break;
			case '8':
			case '9':cout << "��"; break;
			default:
				break;
			}
		}
		cout << endl;
	}
	ShowGrade();
}

//����
void Tetris::Key()
{
	bool a = false;
	while (!a)
	{
		getb = getch();
		if (getb == 'w' || getb == 'W')
		{
			if(Diamonds_Num > 4)
				Deformation_Bool = true;
			Deformation_Diamonds();
		}
		else if (getb == 's' || getb == 'S')
		{
			DropDown();
			if (S_Diamonds)
				break;
			else if (!S_Diamonds&& Diamonds_Num <= 4)
				Insertion_Map();
			ShowMap();
		}
		else if (getb == 'a' || getb == 'A' || getb == 'd' || getb == 'D')
		{
			if (getb == 'a' || getb == 'A')
				LeftShift();
			else if (getb == 'd' || getb == 'D')
				RightShift();
			if (!S_Diamonds && Diamonds_Num <= 4)
				Insertion_Map();
			ShowMap();
		}
		if (!kbhit())
			a = true;
	}
}

//Ƕ�뷽��
void Tetris::Insertion_Map()
{
	int i = 0, j = Gameobject, k = 0;
	for (j; k < 4; j++,k++)
		Map2[i][j] = Diamonds[4- Diamonds_Num][k];
	Copy_Map(Map2, Map);
	Diamonds_Num++;
	if (Diamonds_Num>4)
		Deformation_Bool = true;
}

//��ʼ��
void Tetris::Initialization()
{
	for (int i = 0; i < Map_Height - 1; i++)
		strcpy(Map[i], "900000000009");
	strcpy(Map[Map_Height - 1], "999999999999");
	Copy_Map(Map, Map2);
	Diamonds[4][4] = { 0 };//��������
	CustomsPass = 1;//�ؿ�
	score = 0;//����
	S_Diamonds = true;//�ж��Ƿ�����������
	Time = 200;//ʱ��
	Diamonds_Type = 0;//���������
	Diamonds_Type_Deformation = 0;//������������
	Diamonds_Num = 1;//���鸴�ƽ���ͼ�Ĵ���
	Gameobject = 4;//ˢ�µ�
	Deformation_Bool = false;//�ж��Ƿ񰴼�����
}

//�������
void Tetris::Stochastic()
{
 	srand(time(0));
 	Diamonds_Type = rand() % 7;
	/*Diamonds_Type = 5;*/
	Diamonds_Type_Deformation = 1;
	S_Diamonds = false;
	Deformation_Bool = false;
	switch (Diamonds_Type)
	{
	case 0:
		strcpy(Diamonds[0], "0110");
		strcpy(Diamonds[1], "0110");
		strcpy(Diamonds[2], "0000");
		strcpy(Diamonds[3], "0000");
		break;
	case 1:
		strcpy(Diamonds[0], "0010");
		strcpy(Diamonds[1], "0020");
		strcpy(Diamonds[2], "0010");
		strcpy(Diamonds[3], "0010");
		break;
	case 2:
		strcpy(Diamonds[0], "0010");
		strcpy(Diamonds[1], "0120");
		strcpy(Diamonds[2], "0100");
		strcpy(Diamonds[3], "0000");
		break;
	case 3:
		strcpy(Diamonds[0], "0100");
		strcpy(Diamonds[1], "0210");
		strcpy(Diamonds[2], "0010");
		strcpy(Diamonds[3], "0000");
		break;
	case 4:
		strcpy(Diamonds[0], "1210");
		strcpy(Diamonds[1], "0100");
		strcpy(Diamonds[2], "0000");
		strcpy(Diamonds[3], "0000");
		break;
	case 5:
		strcpy(Diamonds[0], "1000");
		strcpy(Diamonds[1], "2110");
		strcpy(Diamonds[2], "0000");
		strcpy(Diamonds[3], "0000");
		break;
	case 6:
		strcpy(Diamonds[0], "0010");
		strcpy(Diamonds[1], "1120");
		strcpy(Diamonds[2], "0000");
		strcpy(Diamonds[3], "0000");
		break;
	default:
		break;
	}
}

//����
void Tetris::Deformation_Diamonds()
{
	if (Diamonds_Type ==1)
	{
		if (++Diamonds_Type_Deformation > 2)
			Diamonds_Type_Deformation = 1;
		switch (Diamonds_Type_Deformation)
		{
		case 1:	
			strcpy(Diamonds[0], "0010");
			strcpy(Diamonds[1], "0020");
			strcpy(Diamonds[2], "0010");
			strcpy(Diamonds[3], "0010");
			break;
		case 2:
			strcpy(Diamonds[0], "0000");
			strcpy(Diamonds[1], "1121");
			strcpy(Diamonds[2], "0000");
			strcpy(Diamonds[3], "0000");
			break;
		default:
			break;
		}
		Deformation_Diamonds_Insertion_Map();
	}
	else if (Diamonds_Type == 2)
	{
		if (++Diamonds_Type_Deformation > 2)
			Diamonds_Type_Deformation = 1;
		switch (Diamonds_Type_Deformation)
		{
		case 1:
			strcpy(Diamonds[0], "0010");
			strcpy(Diamonds[1], "0120");
			strcpy(Diamonds[2], "0100");
			strcpy(Diamonds[3], "0000");
			break;
		case 2:
			strcpy(Diamonds[0], "0110");
			strcpy(Diamonds[1], "0021");
			strcpy(Diamonds[2], "0000");
			strcpy(Diamonds[3], "0000");
			break;
		default:
			break;
		}
		Deformation_Diamonds_Insertion_Map();
	}
	else if (Diamonds_Type == 3)
	{
		if (++Diamonds_Type_Deformation > 2)
			Diamonds_Type_Deformation = 1;
		switch (Diamonds_Type_Deformation)
		{
		case 1:
			strcpy(Diamonds[0], "0100");
			strcpy(Diamonds[1], "0120");
			strcpy(Diamonds[2], "0010");
			strcpy(Diamonds[3], "0000");
			break;
		case 2:
			strcpy(Diamonds[0], "0011");
			strcpy(Diamonds[1], "0120");
			strcpy(Diamonds[2], "0000");
			strcpy(Diamonds[3], "0000");
			break;
		default:
			break;
		}
		Deformation_Diamonds_Insertion_Map();
	}
	else if (Diamonds_Type == 4)
	{
		if (++Diamonds_Type_Deformation > 4)
			Diamonds_Type_Deformation = 1;
		switch (Diamonds_Type_Deformation)
		{
		case 1:
			strcpy(Diamonds[0], "0000");
			strcpy(Diamonds[1], "1210");
			strcpy(Diamonds[2], "0100");
			strcpy(Diamonds[3], "0000");
			break;
		case 2:
			strcpy(Diamonds[0], "0100");
			strcpy(Diamonds[1], "1200");
			strcpy(Diamonds[2], "0100");
			strcpy(Diamonds[3], "0000");
			break;
		case 3:
			strcpy(Diamonds[0], "0100");
			strcpy(Diamonds[1], "1210");
			strcpy(Diamonds[2], "0000");
			strcpy(Diamonds[3], "0000");
			break;
		case 4:
			strcpy(Diamonds[0], "0100");
			strcpy(Diamonds[1], "0210");
			strcpy(Diamonds[2], "0100");
			strcpy(Diamonds[3], "0000");
			break;
		default:
			break;
		}
		Deformation_Diamonds_Insertion_Map();
	}
	else if (Diamonds_Type == 5)
	{
		if (++Diamonds_Type_Deformation > 4)
			Diamonds_Type_Deformation = 1;
		switch (Diamonds_Type_Deformation)
		{
		case 1:
			strcpy(Diamonds[0], "1000");
			strcpy(Diamonds[1], "2110");
			strcpy(Diamonds[2], "0000");
			strcpy(Diamonds[3], "0000");
			break;
		case 2:
			strcpy(Diamonds[0], "1100");
			strcpy(Diamonds[1], "2000");
			strcpy(Diamonds[2], "1000");
			strcpy(Diamonds[3], "0000");
			break;
		case 3:
			strcpy(Diamonds[0], "1110");
			strcpy(Diamonds[1], "0020");
			strcpy(Diamonds[2], "0000");
			strcpy(Diamonds[3], "0000");
			break;
		case 4:
			strcpy(Diamonds[0], "0010");
			strcpy(Diamonds[1], "0020");
			strcpy(Diamonds[2], "0110");
			strcpy(Diamonds[3], "0000");
			break;
		default:
			break;
		}
		Deformation_Diamonds_Insertion_Map();
	}
	else if (Diamonds_Type == 6)
	{
		if (++Diamonds_Type_Deformation > 4)
			Diamonds_Type_Deformation = 1;
		switch (Diamonds_Type_Deformation)
		{
		case 1:
			strcpy(Diamonds[0], "0010");
			strcpy(Diamonds[1], "2110");
			strcpy(Diamonds[2], "0000");
			strcpy(Diamonds[3], "0000");
			break;
		case 2:
			strcpy(Diamonds[0], "1000");
			strcpy(Diamonds[1], "2000");
			strcpy(Diamonds[2], "1100");
			strcpy(Diamonds[3], "0000");
			break;
		case 3:
			strcpy(Diamonds[0], "1110");
			strcpy(Diamonds[1], "2000");
			strcpy(Diamonds[2], "0000");
			strcpy(Diamonds[3], "0000");
			break;
		case 4:
			strcpy(Diamonds[0], "1100");
			strcpy(Diamonds[1], "0200");
			strcpy(Diamonds[2], "0100");
			strcpy(Diamonds[3], "0000");
			break;
		default:
			break;
		}
		Deformation_Diamonds_Insertion_Map();
	}
}

//���η���Ƕ���ͼ
void Tetris::Deformation_Diamonds_Insertion_Map()
{
	//��Deformation_BoolΪ��ʱ����ʾ����û��ȫ��ˢ���ڵ�ͼ��
	if (!Deformation_Bool)
	{
		//	Diamonds_Num�ĳ�ֵΪ1��
		//	���統Diamonds_NumΪ4ʱ����ʾ����ȫ�������ڵ�ͼ����ʱ����������һ���ڵ�ͼ�ϵ�������i=��2,Gameobject��
		//	i�Ǵ����ͼ�������꣬jΪ�����ꣻl�Ƿ��������kΪ��
		Deformation_Seek();
		for (int l = 1, i = Diamonds_Num - 2; l < Diamonds_Num; l++, i--)
		{
			for (int k = 0, j = Gameobject; k < 4; j++, k++)
			{
				Map2[i][j] = Diamonds[4 - l][k];
			}
		}
		Copy_Map(Map2, Map);
	}
	//��Deformation_BoolΪ��ʱ����ʾ�����Ѿ�ȫ��ˢ���ڵ�ͼ�ϲ��ң��Ѿ��½�����Ҫ�ҵ������λ�ã����ж��Ƿ���ϱ��ε�����
	else
	{
		int i = Deformation_Seek();
		for (int l = 1; l < Diamonds_Num; l++, i--)
		{
			for (int k = 0, j = Gameobject; k < 4; j++, k++)
			{
				Map2[i][j] = Diamonds[4 - l][k];
			}
		}
		Copy_Map(Map2, Map);
	}
	ShowMap();
}

//Ѱ�ҷ���λ��
int Tetris::Deformation_Seek()
{
	int k = 1, Position = 0;
	for (int i = Map_Height - 2; i >= 0; i--)
	{
		for (int j = Gameobject; j < Map_Width - 2; j++)
		{
			if (Map2[i][j] == '1' || Map2[i][j] == '2')
			{
				if (k == 1)
					Position = i;
				Map2[i][j] = '0';
				k++;
			}
		}
	}
	return Position;
}

//��ʾ����
void Tetris::ShowGrade()
{
	gotoy(25, 1);
	cout << "�ؿ�:";
	gotoy(35, 2);
	cout << CustomsPass;
	gotoy(25, 4);
	cout << "������";
	gotoy(35, 5);
	cout << score;
	gotoy(30, 7);
	cout << "�ո���ͣ";
	gotoy(30, 8);
	cout << "a,w,s,d,����";
}

//����
void Tetris::LeftShift()
{
	if (Gameobject > 1)
		Gameobject -= 1;
	bool a = false;
	int M = 0;//�ƶ�����
	for (int j = 1; j < Map_Width; j++)
	{
		int x = j - 1;//����
		for (int i = 0; i < Map_Height; i++)
		{
			if ((Map2[i][j] == '1' || Map2[i][j] == '2') && (Map2[i][x] == '9' || Map2[i][x] == '8'))
				a = true;
			else if ((Map2[i][j] == '1' || Map2[i][j] == '2') && (Map2[i][x] == '0'))
			{
				char tem = Map2[i][j];
				Map2[i][j] = Map2[i][x];
				Map2[i][x] = tem;
				M++;
			}
			if (a == true || M >= 4)
				break;
		}
		if (a == true || M >= 4)
			break;
	}
	if (a)
		Copy_Map(Map, Map2);
	else
		Copy_Map(Map2, Map);
}

//����
void Tetris::RightShift()
{
	if (Gameobject < 7)
		Gameobject += 1;
	bool a = false;
	int M = 0;//�ƶ�����
	for (int j = Map_Width - 2; j > 0; j--)
	{
		int x = j + 1;//����
		for (int i = 0; i < Map_Height; i++)
		{
			if ((Map2[i][j] == '1' || Map2[i][j] == '2') && (Map2[i][x] == '9' || Map2[i][x] == '8'))
				a = true;
			else if ((Map2[i][j] == '1' || Map2[i][j] == '2') && (Map2[i][x] == '0'))
			{
				char tem = Map2[i][j];
				Map2[i][j] = Map2[i][x];
				Map2[i][x] = tem;
				M++;
			}
			if (a == true || M >= 4)
				break;
		}
		if (a == true || M >= 4)
			break;
	}
	if (a)
		Copy_Map(Map, Map2);
	else
		Copy_Map(Map2, Map);
}

//�½�
void Tetris::DropDown()
{
	bool a = false;
	for (int i = Map_Height - 2; i >= 0; i--)
	{
		int y = i + 1;
		for (int j = Map_Width - 2; j >= 1; j--)
		{
			if ((Map2[i][j] == '1' || Map2[i][j] == '2') && (Map2[y][j] == '9' || Map2[y][j] == '8'))
			{
				a = true;
				break;
			}
			else if ((Map2[i][j] == '1' || Map2[i][j] == '2') && Map2[y][j] == '0')
			{
				char tem = Map2[i][j];
				Map2[i][j] = Map2[y][j];
				Map2[y][j] = tem;
			}
		}
		if (a)
			break; 
	}
	if (a)
	{
		Copy_Map(Map, Map2);
		Contact();
		Copy_Map(Map2, Map);
	}
	else
		Copy_Map(Map2, Map);
}
//������ر�ֵ
void Tetris::Contact()
{
	for (int i = 0; i < Map_Height; i++)
	{
		for (int j = 0; j < Map_Width; j++)
		{
			if (Map2[i][j] == '1' || Map2[i][j] == '2')
				Map2[i][j] = '8';
		}
	}
	Eliminate();
	Diamonds_Num = 1;
	Gameobject = 4;
	S_Diamonds = true;
}

void Tetris::gotoy(int x, int y)
{
	COORD coo;
	coo.X = x;
	coo.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coo);
}

//��Ϸ����
void Tetris::GameOver()
{
	bool z = true;
	for (int i = 1, j = 1; j < Map_Width - 1; j++)
	{
		if (Map2[i][j] == '8')
		{
			z = false;
			break;
		}
	}
	if (!z)
	{
		gotoy(14, 10);
		cout << "��Ϸ������";
		gotoy(10, 11);
		system("pause");
		GameInterface();
	}
}

//���Ƶ�ͼ
void Tetris::Copy_Map(char M1[][Map_Width], char M2[][Map_Width])
{
	for (int i = 0; i < Map_Height; i++)
		strcpy(M2[i], M1[i]);
}

//���һ��
void Tetris::Eliminate()
{
	bool a = false;
	for (int i = Map_Height - 2; i >= 1; i--)
	{
		if (strcmp(Map2[i], "988888888889") == 0)
		{
			score += 1;
			if (score >= 10)
			{
				score = 0;
				Time -= 20;
				CustomsPass += 1;
			}
			a = true;
			strcpy(Map2[i], "900000000009");
		}
		if (a)
		{
			strcpy(Map2[i], Map2[i - 1]);
			strcpy(Map2[i - 1], "900000000009");
		}
	}
}
