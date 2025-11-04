#include <iostream>
using namespace std;
int main()
{
	int m[5][5];
	cout << "输入3x3的矩阵，将输出其进行插值操作后的结果" << endl;
	for (int i = 0; i <= 4; i += 2)
	{
		for (int j = 0; j <= 4; j += 2)
		{
			cin >> m[i][j];//黑数
		}
	}
	for (int i = 1; i <= 3; i += 2)//对于第一行与第三行,输出0,2,4列（白数）
	{
		for (int j = 0; j <= 4; j += 2)
		{
			m[i][j] = (m[i - 1][j] + m[i + 1][j]) / 2;
		}
	}
	for (int i = 1; i <= 3; i += 2)//对于第一列与第三列,输出0,2,4行（白数）
	{
		for (int j = 0; j <= 4; j += 2)
		{
			m[j][i] = (m[j ][i-1] + m[j ][i+1]) / 2;
		}
	}
	for (int i = 1; i <= 3; i += 2)//灰数
	{
		for (int j = 1; j <= 3; j += 2)
		{
			m[i][j] = (m[i - 1][j-1] + m[i + 1][j+1] + m[i+1][j - 1] + m[i-1][j + 1]) / 4;
		}
	}
	cout << "进行简单插值后的结果为：" << endl;
	for (int i = 0; i <= 4; i++)
	{
		for (int j = 0; j <= 4; j++)
		{
			cout << m[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}
