#pragma once

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <conio.h>
using namespace std;

struct Dict
{
	static int count;
	char Word1[20];
	string Word2;
	Dict * p;
	friend ostream & operator << (ostream & o, Dict & d)
	{
		o << d.Word1 << endl << d.Word2;
		return o;
	}
	friend istream & operator >> (istream & in, Dict & d)
	{
		in >> d.Word1 >> d.Word2;
		return in;
	}
	Dict() 
	{
		count++;
		//cout << count << endl;
	}
	~Dict() 
	{
		count--;
		//cout << count << endl;
	}
};

class YoudaoDict
{
public:
 	YoudaoDict();
 	~YoudaoDict();
	//���˵�
	void MainMenu();
	//��ѯ
	void ShowWord();
 	//׷��
 	void AppWord();
 	//ɾ��
 	void DeleteWord();
protected:
	//��ȡ�ļ���
	bool Fread(char);
	//��ȡ����
	void ReadWord();
	//�ж���û�е���
	Dict* Judge();
	//д���ļ�
	void Save();
	//ɾ������
	void DeleteSite();
private:
	Dict *dict;
	//������ĵ���
	char Word3[20];
	char Tem;
	fstream fdict;
	string fname;

};

