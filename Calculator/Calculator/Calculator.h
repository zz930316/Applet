#pragma once
#include <iostream>
#include <string>
#include <math.h>
using namespace std;

const int CSize = 10;

class Calculator
{
public:
	Calculator();
	~Calculator();
	void Import();//������ʽ
	void Result();//���
protected:
	void Initialize();//��ʼ��
	void Disassemble(string);//�ֽ�
	void Operation(char);//����
private:
	int ftop1, ftop2;
	char fopnd[CSize], foptr[CSize];
	int num;
	bool judge;
};

