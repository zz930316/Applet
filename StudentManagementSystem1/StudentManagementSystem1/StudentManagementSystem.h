#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <conio.h>
using namespace std;

struct Student
{
	int num;
	char name[10];
	int age;
	char sex;
	float yu;
	float shu;
	float ying;
	//总分
	float Total() { return shu + shu + ying; }
	//平均分
	float average() { return Total() / 3.0f; }

	Student & operator= (Student&s2)
	{
	
		num= s2.num;
		strcpy(name, s2.name);
		age = s2.age;
		sex = s2.sex;
		shu = s2.shu;
		ying = s2.ying;
		yu = s2.yu;
		return *this;
	}

	friend ostream & operator << (ostream & output, Student &s)
	{
		output << s.num << "\t" << s.name << "\t" << s.age << "\t" <<
			s.sex << "\t" << s.yu << "\t" << s.shu << "\t" << s.ying;
		return output;
	}

	friend istream &operator>>(istream & ion, Student &s)
	{
		ion >> s.num >> s.name >> s.age >> s.sex >> s.yu >> s.shu >> s.ying;
		return ion;
	}
};



class StudentManagementSystem
{
public:
	StudentManagementSystem();
	~StudentManagementSystem();
	//主菜单
	void MainMenu();
	//1、录入保存
	void Entering();
	//2、读取
	void ShowStuent();
	//3、删除
	void DeletStuent();
	//4、追加
	void AppaddStuent();
	//5、修改
	void AmendStuent();
	//6、统计各分数段人数并输出学生信息清单
	void Statistics();
	//7、按学号查找学生信息
	int Seek();
	//8、按照平均分输出学生信息清单
	void AverageScore();
protected:
	//读取
	bool Read();
	//检查是否有学生信息
	bool Judge();
	//写出文件
	void Save();
	//按科目输出分数段成绩
	bool GardeSection(char, int, int);
	//检查输入合法
	bool Validity(Student &,int );
	//检查学号是否重复
	bool Validity_Num(int);
	//按学号排序
	void Sort();
private:
	Student *stud;
	int Studentnum;
	bool Estimate;
	fstream FStrent;
};


