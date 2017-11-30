#include "Calculator.h"



Calculator::Calculator()
{
	ftop1 = -1;
	ftop2 = -1;
	fopnd[CSize] = 0; foptr[CSize] = 0;
	num = 0;
}


Calculator::~Calculator()
{
	if (ftop1 != -1)
		delete[]fopnd;
	if (ftop2)
		delete[]foptr;
}

//输入算式
void Calculator::Import()
{
	Initialize();
	string fformula;
	cout << "输入运算式:" << endl;
	cin >> fformula;
	num = size(fformula);
	Disassemble(fformula);
}

void Calculator::Initialize()
{
	ftop1 = -1;
	ftop2 = -1;
	fopnd[CSize] = 0; foptr[CSize] = 0;
	num = 0;
	judge = false;
}

//分解
void Calculator::Disassemble(string fformula)
{
	bool a = false;
	char fsym;
	int ftime = 0;
	for (int i = 0; i < num; i++)
	{
		if (fformula[i] >= 48 && fformula[i] <= 57)
		{
			if (!a)
				fopnd[++ftop1] = fformula[i] - 48;
			else
				fopnd[ftop1] = fopnd[ftop1] * 10 + (fformula[i] - 48);
			a = true;
		}
		else if (fformula[i] == '(' || fformula[i] == ')' ||
			fformula[i] == '+' || fformula[i] == '-' || fformula[i] == '*' || fformula[i] == '/')
		{
			a = false;
			ftime = 0;
			if (fformula[i] == '(')
				foptr[++ftop2] = '(';
			else if (fformula[i] == ')')
			{
				while (1)
				{
					fsym = foptr[ftop2];
					if (fsym == '(')
					{
						ftop2--;
						break;
					}
					Operation(fsym);
				}
			}
			else if (fformula[i] == '*' || fformula[i] == '/')
			{
				fsym = foptr[ftop2];
				if (fsym == '(' || ftop2 == -1 || fsym == '+' || fsym == '-')
					foptr[++ftop2] = fformula[i];
				else
				{
					Operation(fsym);
					foptr[++ftop2] = fformula[i];
				}
			}
			else if (fformula[i] == '+' || fformula[i] == '-')
			{
				fsym = foptr[ftop2];
				if (fsym == '(' || ftop2 == -1)
					foptr[++ftop2] = fformula[i];
				else
				{
					while (1)
					{
						fsym = foptr[ftop2];
						if (fsym == '(' || ftop2 == -1)
							break;
						Operation(fsym);
					}
					foptr[++ftop2] = fformula[i];
				}
			}
		}
		else
			cout << "参数错误" << endl;
	}
}

void Calculator::Operation(char fsym)
{
	float a = fopnd[ftop1--], b = fopnd[ftop1--], c = 0.0;
	if (fsym == '+')
		c = b + a;
	else if (fsym == '-')
		c = b - a;
	else if (fsym == '*')
		c = b*a;
	else if (fsym == '/')
	{
		if (a == 0)
			judge = true;
		c = b / a;
	}
	--ftop2;
	fopnd[++ftop1] = c;
}

void Calculator::Result()
{
	while (ftop2!=-1)
		Operation(foptr[ftop2]);
	float i = fopnd[ftop1];
	if (judge)
		cout << "错误" << endl;
	else if (ftop2 == -1 && ftop1 == 0)
		cout << i << endl;
}
