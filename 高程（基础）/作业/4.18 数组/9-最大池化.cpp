#include<iostream>
using namespace std;
int main()
{
	int m[8][8]{};
	int change1[4][8];
	int change2[4][4];
	cout << "64个整数输入，代表8*8的矩阵，将进行2*2最大池化" << endl;
	for (int i = 0; i <= 7; i++)//行
	{
		for (int j = 0; j <= 7; j++)//列
		{
			cin >> m[i][j];
		}
	}
	for (int i = 0; i <= 3; i++)
	{
		for (int j = 0; j <= 7; j++)
		{
			if (m[2 * i][j] < m[2 * i + 1][j])
				change1[i][j] = m[2 * i + 1][j];
			else
				change1[i][j] = m[2 * i][j];//同一列奇数行偶数行比较，行数减少到4
		}
	}
	for (int j = 0; j <= 3; j++)
	{
		for (int i = 0; i <= 3; i++)
		{
			if (change1[i][2 * j] < change1[i][2 * j + 1])
				change2[i][j]=change1[i][2 * j + 1];
			else
				change2[i][j] = change1[i][2 * j];//列数减少到4
		}
	}
	cout << "进行2*2最大池化后的结果为：" << endl;
	for (int i = 0; i <= 3; i++)
	{
		for (int j = 0; j <= 3; j++)
		{
			cout << change2[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}