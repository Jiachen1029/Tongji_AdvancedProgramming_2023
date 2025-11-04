#include<iostream>
using namespace std;
int main()
{
	int s[10];
	for (int i = 0; i <= 9; i++)
		cin >> s[i];//先输入数组
	int a;
	while (cin >> a)
	{
		if (a == -1)
			break;//结束
		else
		{
			for (int j = 0; j <= 9; j++)
			{
				if (a == s[j])
				{
					cout << a << "在数组中。" << endl;
					break;//从新开始
				}
				else if (j == 9)
				{
					cout << a << "不在数组中。" << endl;
					continue;//从新开始
				}
			}
		}
	}
	return 0;
}