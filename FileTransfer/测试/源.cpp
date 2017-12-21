#include <iostream>
using namespace std;
#include <queue>
#include <string>
void main()
{
	char a[5];
	queue<char [5]> que;
	for (int i = 0; i < 5; i++)
	{
		cin >> a[i];
		que.push(a);
	}
	for (int i = 0; i < 5; i++)
	{
		char m[5];
		for(int j=0;j<5;j++)
			 m[j]= que.front()[i];
		cout << m << endl;
		que.pop();
	}
}