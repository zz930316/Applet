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
	void Import();//输入算式
	void Result();//结果
protected:
	void Initialize();//初始化
	void Disassemble(string);//分解
	void Operation(char);//运算
private:
	int ftop1, ftop2;
	char fopnd[CSize], foptr[CSize];
	int num;
	bool judge;
};

