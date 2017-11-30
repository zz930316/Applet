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
	//�ܷ�
	float Total() { return shu + shu + ying; }
	//ƽ����
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
	//���˵�
	void MainMenu();
	//1��¼�뱣��
	void Entering();
	//2����ȡ
	void ShowStuent();
	//3��ɾ��
	void DeletStuent();
	//4��׷��
	void AppaddStuent();
	//5���޸�
	void AmendStuent();
	//6��ͳ�Ƹ����������������ѧ����Ϣ�嵥
	void Statistics();
	//7����ѧ�Ų���ѧ����Ϣ
	int Seek();
	//8������ƽ�������ѧ����Ϣ�嵥
	void AverageScore();
protected:
	//��ȡ
	bool Read();
	//����Ƿ���ѧ����Ϣ
	bool Judge();
	//д���ļ�
	void Save();
	//����Ŀ��������γɼ�
	bool GardeSection(char, int, int);
	//�������Ϸ�
	bool Validity(Student &,int );
	//���ѧ���Ƿ��ظ�
	bool Validity_Num(int);
	//��ѧ������
	void Sort();
private:
	Student *stud;
	int Studentnum;
	bool Estimate;
	fstream FStrent;
};


