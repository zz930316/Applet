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
//主菜单
void StudentManagementSystem::MainMenu()
{
	Read();
	bool a = true;
	while (a)
	{
		system("cls");
		cout << "1、学生基本信息的录入和保存" << endl;
		cout << "2、读取学生信息" << endl;
		cout << "3、删除学生信息" << endl;
		cout << "4、追加学生信息" << endl;
		cout << "5、修改学生信息" << endl;
		cout << "6、统计各分数段人数并输出学生信息清单" << endl;
		cout << "7、按学号查找学生信息" << endl;
		cout << "8、按照平均分输出学生信息清单" << endl;
		cout << "9、退出系统，结束任务" << endl;
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
			cout << "输入错误，请重新输入！" << endl;
			break;
 		}
		//按任意键继续的函数
		system("pause");
	}
}
//1、录入保存
void StudentManagementSystem::Entering()
{
	system("cls");
	bool a = true;
	cout << "此功能会导致覆盖以保存的学生信息！Y/N" << endl;
	char b = getch();
	if (b == 'Y' || b == 'y')
		a = false;
	if (!a)
	{
		cout << "输入要录入的学生人数 : ";
		cin >> Studentnum;
		if (stud)
			delete[]stud;
		stud = new Student[Studentnum];
		cout << "\n请输入学生的学号、姓名、年龄、性别、语文成绩、数学成绩、英语成绩。" << endl;
		for (int i = 0; i < Studentnum; i++)
		{
			cout << i + 1 << "、\t";
			cin >> stud[i];
			bool b = false, c = false;
			for (int j = 1; j <= 6; j++)
				b = Validity(stud[i], j);
			c = Validity_Num(stud[i].num);
			if (!b||!c)
				--i;
		}
		cout << "已添加" << Studentnum << "名学生信息!" << endl;
		a = false;
	}
	if (!a)
		Save();
	else
		cout << "未保存学生信息!" << endl;
}
//2、读取
void StudentManagementSystem::ShowStuent()
{
	Estimate = Judge();
	while (Estimate)
	{
		cout << "\t学号\t姓名\t年龄\t性别\t语文\t数学\t英语\t总分\t平均分" << endl;
		for (int i = 0; i < Studentnum; i++)
			cout << i + 1 << "、\t" << stud[i] << "\t" << stud[i].Total() << "\t" << stud[i].average() << endl;
		cout << "\t\t\t\t学生总人数有 " << Studentnum << " 个" << endl;
		Estimate = false;
	}
}
//3、删除	
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
				cout << "是否删除该名学生信息。Y/N" << endl;
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
			cout << "                      未删除学生信息!" << endl;
		Estimate = false;
	}
}
//4、追加
void StudentManagementSystem::AppaddStuent()
{
	int num;
	bool a = false;
	cout << "输入要追加的学生人数：";
	cin >> num;
	if (num > 0)
	{
		num += Studentnum;
		Student *stud2 = new Student[num];
		for (int i=0;i<Studentnum;i++)
			stud2[i] = stud[i];
		cout << "\n请输入学生的学号、姓名、年龄、性别、语文成绩、数学成绩、英语成绩。" << endl;
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
		cout << "已添加" << num - Studentnum << "名学生信息，是否保存Y/N" << endl;
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
		cout << "未成功追加学生信息！";
	if (a)
		Save();
}
//5、修改
void StudentManagementSystem::AmendStuent()
{
	Estimate = Judge();
	while (Estimate)
	{
		int i = Seek();
		bool a = false, b = false;
		cout << "\n\t<<<<<<<<<<<<<<<<<<<<<<<<请输入修改之后的信息>>>>>>>>>>>>>>>>>>>>>>>>>\n" << endl;
		cout << "\t学号\t姓名\t年龄\t性别\t语文\t数学\t英语\n\t";
		//Seek(）返回的是要查找的学生下标
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
			cout << "                      未修改学生信息!" << endl;
		Estimate = false;
	}
}
//6、统计各分数段人数并输出学生信息清单
void StudentManagementSystem::Statistics()
{
	Estimate = Judge();
	while (Estimate)
	{
		system("cls");
		cout << "1、查看语文成绩" << endl;
		cout << "2、查看数学成绩" << endl;
		cout << "3、查看英语成绩" << endl;
		char b = getch();
		switch (b)
		{
		case '1':
		case '2':
		case '3':
		{
			system("cls");
			cout << "1、查看0-59分成员" << endl;
			cout << "2、查看60-79分成员" << endl;
			cout << "3、查看80-100分成员" << endl;
			char c = getch();
			switch (c)
			{
			case '1':Estimate = GardeSection(b, 0, 59); break;
			case '2':Estimate = GardeSection(b, 60, 79); break;
			case '3':Estimate = GardeSection(b, 80, 100); break;
			default:cout << "输入有误，请重新输入！" << endl;
				break;
			}
			break;
		}
		default:cout << "输入有误，请重新输入！" << endl;
			break;
		}
		system("pause");
		Estimate = false;
	}
}
//7、按学号查找学生信息//返回值为学生下标
int StudentManagementSystem::Seek()
{
	Estimate = Judge();
	while (Estimate)
	{
		int num;
		cout << "输入要查找的学生学号:";
		cin >> num;
		cout << "\t<<<<<<<<<<<<<<<<<<<<<<<<<<<<<该生原信息>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n" << endl;
		cout << "\t学号\t姓名\t年龄\t性别\t语文\t数学\t英语\t总分\t平均分" << endl;
		for (int i = 0, j = 1; i < Studentnum; i++)
		{
			if (stud[i].num == num)
			{
				cout << "  \t" << stud[i] << "\t" << stud[i].Total() << "\t" << stud[i].average() << endl;
				return i;
			}
		}
		cout << "未找到该学生信息！" << endl;
		Estimate = false;
	}
	return -1;
}
//8、按照平均分输出学生信息清单
void StudentManagementSystem::AverageScore()
{
	Estimate = Judge();
	while (Estimate)
	{
		cout << "<<<<<<<<<<<<<<<<<<<<<<<<<按成绩平均分排序>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl << endl;
		cout << "\t学号\t姓名\t年龄\t性别\t语文\t数学\t英语\t总分\t平均分" << endl;
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
			cout << i + 1 << "、\t" << stud[i] << "\t" << stud[i].Total() << "\t" << stud[i].average() << endl;
		cout << "\n\t\t\t学生总人数有 " << Studentnum << " 个" << endl;
		Estimate = false;
	}
}
//检查输入合法
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
	default: cout << "程序出错请重启！";
		break;
	}
	if (!a)
		cout << "输入有误，请重新输入该生信息！（学号范围为100~200、姓名不限、年龄为15~50岁、性别可输入m或f、各科成绩均限定在0~100之间）" << endl;
	return a;
}
//检查学号是否重复
bool StudentManagementSystem::Validity_Num(int num)
{
	for (int i=0;i<Studentnum;i++)
		if (stud[i].num == num)
		{
			cout << "已有学号为 " << num << " 的学生，请确认是否输入错误或覆盖原学号为 " << num << " 的学生信息后!  Y/N" << endl;
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
//按学号排序
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
//读
bool StudentManagementSystem::Read()
{
	FStrent.open("StudentInformation.txt", ios::in);
	if (!FStrent)
	{
		cout << "读取信息失败,没有学生信息！" << endl;
		FStrent.close();
		return false;
	}
	if (FStrent.eof())
	{
		cout << "没有学生信息，请先输入！" << endl;
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
	cout << "读取学生信息成功！" << endl;
	return true;
}
//检查是否有学生信息
bool StudentManagementSystem::Judge()
{
	if (Studentnum)
		return true;
	else
	{
		system("cls");
		cout << "没有学生信息，请先录入学生信息！" << endl;
	}
	return false;
}
//写
void StudentManagementSystem::Save()
{
	FStrent.open("StudentInformation.txt", ios::out);
	if (!FStrent)
	{
		cout << "无法创建StudentInformation.txt" << endl;
	}
	FStrent << Studentnum << endl;
	Sort();
	for (int i = 0; i < Studentnum; i++)
	{
		FStrent << stud[i] << endl;
	}
	FStrent.close();
	cout << "已按学号顺序保存成功!" << endl;
}
//按科目输出分数段成绩
bool StudentManagementSystem::GardeSection(char Cou, int min, int max)
{
	int a = 0;
	cout << "\t学号\t姓名\t年龄\t性别\t语文\t数学\t英语\t总分\t平均分" << endl << endl;
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
	cout << "\n\t\t\t该科目成绩为" << min << "~" << max << "的有" << a << "个人" << endl;
	return false;
}