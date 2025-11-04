#include<iostream>
using namespace std;
int main()
{
	cout << "请输入16个整数，代表一个四阶方阵。" << endl;
	int s[4][4];
	int sumi[4], sumj[4];
	for (int i = 0; i <= 3; i++)//行
	{
		for (int j = 0; j <= 3; j++)//列
			cin >> s[i][j];
	}
	for (int i = 0; i <= 3; i++)//行
	{
		sumi[i] = s[i][0] + s[i][1] + s[i][2] + s[i][3];
	}
	for (int j = 0; j <= 3; j++)//列
	{
		sumj[j] = s[0][j] + s[1][j] + s[2][j] + s[3][j];
	}
	cout << "每一行元素的和：" << sumi[0] << ' ' << sumi[1] << ' ' << sumi[2] << ' ' << sumi[3];
	cout << endl;
	cout << "每一列元素的和：" << sumj[0] << ' ' << sumj[1] << ' ' << sumj[2] << ' ' << sumj[3];
	return 0;
}