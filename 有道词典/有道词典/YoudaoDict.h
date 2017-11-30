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
	//主菜单
	void MainMenu();
	//查询
	void ShowWord();
 	//追加
 	void AppWord();
 	//删除
 	void DeleteWord();
protected:
	//读取文件名
	bool Fread(char);
	//读取单词
	void ReadWord();
	//判断有没有单词
	Dict* Judge();
	//写出文件
	void Save();
	//删除链表
	void DeleteSite();
private:
	Dict *dict;
	//存输入的单词
	char Word3[20];
	char Tem;
	fstream fdict;
	string fname;

};

