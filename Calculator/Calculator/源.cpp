#include <iostream>
#include "Calculator.h"
using namespace std;


int main()
{
	Calculator calculator;
	while (1)
	{
		calculator.Import();
		calculator.Result();
	}
	return 0;
}