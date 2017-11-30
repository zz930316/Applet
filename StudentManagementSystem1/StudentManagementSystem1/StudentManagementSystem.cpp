#include "StudentManagementSystem.h"

StudentManagementSystem::StudentManagementSystem()
{
	stud = NULL;
	Studentnum = 0;
	Estimate = false;
}

StudentManagementSystem::~StudentManagementSystem()
{
	if (stud)
	{
		delete[]stud;
		stud = NULL;
	}
}
//���˵�
void StudentManagementSystem::MainMenu()
{
	Read();
	bool a = true;
	while (a)
	{
		system("cls");
		cout << "1��ѧ��������Ϣ��¼��ͱ���" << endl;
		cout << "2����ȡѧ����Ϣ" << endl;
		cout << "3��ɾ��ѧ����Ϣ" << endl;
		cout << "4��׷��ѧ����Ϣ" << endl;
		cout << "5���޸�ѧ����Ϣ" << endl;
		cout << "6��ͳ�Ƹ����������������ѧ����Ϣ�嵥" << endl;
		cout << "7����ѧ�Ų���ѧ����Ϣ" << endl;
		cout << "8������ƽ�������ѧ����Ϣ�嵥" << endl;
		cout << "9���˳�ϵͳ����������" << endl;
		char b = getch();
 		switch (b)
 		{
 		case '1':system("cls"); Entering(); break;
 		case '2':system("cls"); ShowStuent(); break;
 		case '3':system("cls"); DeletStuent(); break;
 		case '4':system("cls"); AppaddStuent(); break;
 		case '5':system("cls"); AmendStuent(); break;
 		case '6':system("cls"); Statistics(); break;
 		case '7':system("cls"); Seek(); break;
 		case '8':system("cls"); AverageScore(); break;
 		case '9':a = false; break;
		default:
			cout << "����������������룡" << endl;
			break;
 		}
		//������������ĺ���
		system("pause");
	}
}
//1��¼�뱣��
void StudentManagementSystem::Entering()
{
	system("cls");
	bool a = true;
	cout << "�˹��ܻᵼ�¸����Ա����ѧ����Ϣ��Y/N" << endl;
	char b = getch();
	if (b == 'Y' || b == 'y')
		a = false;
	if (!a)
	{
		cout << "����Ҫ¼���ѧ������ : ";
		cin >> Studentnum;
		if (stud)
			delete[]stud;
		stud = new Student[Studentnum];
		cout << "\n������ѧ����ѧ�š����������䡢�Ա����ĳɼ�����ѧ�ɼ���Ӣ��ɼ���" << endl;
		for (int i = 0; i < Studentnum; i++)
		{
			cout << i + 1 << "��\t";
			cin >> stud[i];
			bool b = false, c = false;
			for (int j = 1; j <= 6; j++)
				b = Validity(stud[i], j);
			c = Validity_Num(stud[i].num);
			if (!b||!c)
				--i;
		}
		cout << "�����" << Studentnum << "��ѧ����Ϣ!" << endl;
		a = false;
	}
	if (!a)
		Save();
	else
		cout << "δ����ѧ����Ϣ!" << endl;
}
//2����ȡ
void StudentManagementSystem::ShowStuent()
{
	Estimate = Judge();
	while (Estimate)
	{
		cout << "\tѧ��\t����\t����\t�Ա�\t����\t��ѧ\tӢ��\t�ܷ�\tƽ����" << endl;
		for (int i = 0; i < Studentnum; i++)
			cout << i + 1 << "��\t" << stud[i] << "\t" << stud[i].Total() << "\t" << stud[i].average() << endl;
		cout << "\t\t\t\tѧ���������� " << Studentnum << " ��" << endl;
		Estimate = false;
	}
}
//3��ɾ��	
void StudentManagementSystem::DeletStuent()
{
	Estimate = Judge();
	while (Estimate)
	{
		bool a = false;
		if (!a)
		{
			int i = Seek();
			if (i>=0)
			{
				cout << "�Ƿ�ɾ������ѧ����Ϣ��Y/N" << endl;
				char b = getch();
				if (b == 'Y' || b == 'y')
				{
					for (; i < Studentnum; i++)
						stud[i] = stud[i + 1];
					--Studentnum;
					a = true;
				}
			}
		}
		if (a)
			Save();
		else
			cout << "                      δɾ��ѧ����Ϣ!" << endl;
		Estimate = false;
	}
}
//4��׷��
void StudentManagementSystem::AppaddStuent()
{
	int num;
	bool a = false;
	cout << "����Ҫ׷�ӵ�ѧ��������";
	cin >> num;
	if (num > 0)
	{
		num += Studentnum;
		Student *stud2 = new Student[num];
		for (int i=0;i<Studentnum;i++)
			stud2[i] = stud[i];
		cout << "\n������ѧ����ѧ�š����������䡢�Ա����ĳɼ�����ѧ�ɼ���Ӣ��ɼ���" << endl;
		for (int i = Studentnum; i < num; i++)
		{
			cin >> stud2[i];
			bool b = false, c = false;
			for (int j = 1; j <= 6; j++)
				b = Validity(stud2[i], j);
			c = Validity_Num(stud2[i].num);
			if (!b || !c)
				--i;
		}
		cout << "�����" << num - Studentnum << "��ѧ����Ϣ���Ƿ񱣴�Y/N" << endl;
		char b = getch();
		if (b == 'Y' || b == 'y')
		{
			delete[]stud;
			a = true;
			Studentnum = num;
			stud = new Student[Studentnum];
			for (int i = 0; i < Studentnum; i++)
				stud[i] = stud2[i];
		}
		delete[]stud2;
		stud2 = NULL;
	}
	else
		cout << "δ�ɹ�׷��ѧ����Ϣ��";
	if (a)
		Save();
}
//5���޸�
void StudentManagementSystem::AmendStuent()
{
	Estimate = Judge();
	while (Estimate)
	{
		int i = Seek();
		bool a = false, b = false;
		cout << "\n\t<<<<<<<<<<<<<<<<<<<<<<<<�������޸�֮�����Ϣ>>>>>>>>>>>>>>>>>>>>>>>>>\n" << endl;
		cout << "\tѧ��\t����\t����\t�Ա�\t����\t��ѧ\tӢ��\n\t";
		//Seek(�����ص���Ҫ���ҵ�ѧ���±�
		while (i >= 0)
		{
			cin >> stud[i];
			bool b = false, c = false;
			for (int j = 1; j <= 6; j++)
				b = Validity(stud[i], j);
			c = Validity_Num(stud[i].num);
			if (!b || !c)
				break;
			a = true;
		}
		if (a)
			Save();
		else
			cout << "                      δ�޸�ѧ����Ϣ!" << endl;
		Estimate = false;
	}
}
//6��ͳ�Ƹ����������������ѧ����Ϣ�嵥
void StudentManagementSystem::Statistics()
{
	Estimate = Judge();
	while (Estimate)
	{
		system("cls");
		cout << "1���鿴���ĳɼ�" << endl;
		cout << "2���鿴��ѧ�ɼ�" << endl;
		cout << "3���鿴Ӣ��ɼ�" << endl;
		char b = getch();
		switch (b)
		{
		case '1':
		case '2':
		case '3':
		{
			system("cls");
			cout << "1���鿴0-59�ֳ�Ա" << endl;
			cout << "2���鿴60-79�ֳ�Ա" << endl;
			cout << "3���鿴80-100�ֳ�Ա" << endl;
			char c = getch();
			switch (c)
			{
			case '1':Estimate = GardeSection(b, 0, 59); break;
			case '2':Estimate = GardeSection(b, 60, 79); break;
			case '3':Estimate = GardeSection(b, 80, 100); break;
			default:cout << "�����������������룡" << endl;
				break;
			}
			break;
		}
		default:cout << "�����������������룡" << endl;
			break;
		}
		system("pause");
		Estimate = false;
	}
}
//7����ѧ�Ų���ѧ����Ϣ//����ֵΪѧ���±�
int StudentManagementSystem::Seek()
{
	Estimate = Judge();
	while (Estimate)
	{
		int num;
		cout << "����Ҫ���ҵ�ѧ��ѧ��:";
		cin >> num;
		cout << "\t<<<<<<<<<<<<<<<<<<<<<<<<<<<<<����ԭ��Ϣ>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n" << endl;
		cout << "\tѧ��\t����\t����\t�Ա�\t����\t��ѧ\tӢ��\t�ܷ�\tƽ����" << endl;
		for (int i = 0, j = 1; i < Studentnum; i++)
		{
			if (stud[i].num == num)
			{
				cout << "  \t" << stud[i] << "\t" << stud[i].Total() << "\t" << stud[i].average() << endl;
				return i;
			}
		}
		cout << "δ�ҵ���ѧ����Ϣ��" << endl;
		Estimate = false;
	}
	return -1;
}
//8������ƽ�������ѧ����Ϣ�嵥
void StudentManagementSystem::AverageScore()
{
	Estimate = Judge();
	while (Estimate)
	{
		cout << "<<<<<<<<<<<<<<<<<<<<<<<<<���ɼ�ƽ��������>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl << endl;
		cout << "\tѧ��\t����\t����\t�Ա�\t����\t��ѧ\tӢ��\t�ܷ�\tƽ����" << endl;
		for (int i = 0; i < Studentnum - 1; i++)
		{
			for (int j = i + 1; j < Studentnum; j++)
			{
				if (stud[i].average() < stud[j].average())
				{
					swap(stud[i], stud[j]);
// 					Student tem = stud[i];
// 					stud[i] = stud[j];
// 					stud[j] = tem;
				}
			}
		}
		for (int i = 0; i < Studentnum; i++)
			cout << i + 1 << "��\t" << stud[i] << "\t" << stud[i].Total() << "\t" << stud[i].average() << endl;
		cout << "\n\t\t\tѧ���������� " << Studentnum << " ��" << endl;
		Estimate = false;
	}
}
//�������Ϸ�
bool StudentManagementSystem::Validity(Student & s, int i)
{
	bool a = false;
	switch (i)
	{
	case 1:
		if (s.num >= 100 && s.num <= 200)
			a = true; break;
	case 2:
		if (s.age >= 15 && s.age <= 50)
			a = true; break;
	case 3:
		if (s.sex == 'f' || s.sex == 'm')
			a = true; break;
	case 4:
		if (s.yu >= 0 && s.yu <= 100)
			a = true; break;
	case 5:
		if (s.shu >= 0 && s.shu <= 100)
			a = true; break;
	case 6:
		if (s.ying >= 0 && s.ying <= 100)
			a = true; break;
	default: cout << "���������������";
		break;
	}
	if (!a)
		cout << "�����������������������Ϣ����ѧ�ŷ�ΧΪ100~200���������ޡ�����Ϊ15~50�ꡢ�Ա������m��f�����Ƴɼ����޶���0~100֮�䣩" << endl;
	return a;
}
//���ѧ���Ƿ��ظ�
bool StudentManagementSystem::Validity_Num(int num)
{
	for (int i=0;i<Studentnum;i++)
		if (stud[i].num == num)
		{
			cout << "����ѧ��Ϊ " << num << " ��ѧ������ȷ���Ƿ��������򸲸�ԭѧ��Ϊ " << num << " ��ѧ����Ϣ��!  Y/N" << endl;
			while (true)
			{
				char a = getch();
				if (a == 'Y' || a == 'y')
					return false;
				else if (a == 'N' || a == 'n')
					return true;
			}
		}
	return true;
}
//��ѧ������
void StudentManagementSystem::Sort()
{
	for (int i = 0; i < Studentnum - 1; i++)
	{
		for (int j = i + 1; j < Studentnum; j++)
		{
			if (stud[i].num > stud[j].num)
			{
				Student tem = stud[i];
				stud[i] = stud[j];
				stud[j] = tem;
			}
		}
	}
}
//��
bool StudentManagementSystem::Read()
{
	FStrent.open("StudentInformation.txt", ios::in);
	if (!FStrent)
	{
		cout << "��ȡ��Ϣʧ��,û��ѧ����Ϣ��" << endl;
		FStrent.close();
		return false;
	}
	if (FStrent.eof())
	{
		cout << "û��ѧ����Ϣ���������룡" << endl;
		FStrent.close();
		return false;
	}
	FStrent >> Studentnum;
	if (stud)
		delete[]stud;
	stud = new Student[Studentnum];
	for (int i = 0; i < Studentnum; i++)
	{
		FStrent >> stud[i];
	}
	FStrent.close();
	cout << "��ȡѧ����Ϣ�ɹ���" << endl;
	return true;
}
//����Ƿ���ѧ����Ϣ
bool StudentManagementSystem::Judge()
{
	if (Studentnum)
		return true;
	else
	{
		system("cls");
		cout << "û��ѧ����Ϣ������¼��ѧ����Ϣ��" << endl;
	}
	return false;
}
//д
void StudentManagementSystem::Save()
{
	FStrent.open("StudentInformation.txt", ios::out);
	if (!FStrent)
	{
		cout << "�޷�����StudentInformation.txt" << endl;
	}
	FStrent << Studentnum << endl;
	Sort();
	for (int i = 0; i < Studentnum; i++)
	{
		FStrent << stud[i] << endl;
	}
	FStrent.close();
	cout << "�Ѱ�ѧ��˳�򱣴�ɹ�!" << endl;
}
//����Ŀ��������γɼ�
bool StudentManagementSystem::GardeSection(char Cou, int min, int max)
{
	int a = 0;
	cout << "\tѧ��\t����\t����\t�Ա�\t����\t��ѧ\tӢ��\t�ܷ�\tƽ����" << endl << endl;
	for (int i = 0; i < Studentnum; i++)
	{
		float Course = 0;
		switch (Cou)
		{
		case '1':Course = stud[i].yu; break;
		case '2':Course = stud[i].shu; break;
		case '3':Course = stud[i].ying; break;
		default:
			break;
		}
		if (Course>=min&&Course<=max)
		{
			++a;
			cout <<"\t"<< stud[i] << "\t" << stud[i].Total() << "\t" << stud[i].average() << endl;
		}
	}
	cout << "\n\t\t\t�ÿ�Ŀ�ɼ�Ϊ" << min << "~" << max << "����" << a << "����" << endl;
	return false;
}