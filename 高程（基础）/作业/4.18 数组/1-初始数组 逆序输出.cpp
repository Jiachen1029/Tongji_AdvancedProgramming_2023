#include<iostream>
using namespace std;
int main()
{
	cout << "请输出十个整数，系统将为你倒序输出" << endl;
	int s[10];
	for (int i = 0; i <= 9; i++)
		cin >> s[i];
	int p[10];//反过来
	for (int j = 0; j <= 9; j++)
	{
		p[j] = s[9 - j];
		cout << p[j] << " ";
	}
	return 0;
}