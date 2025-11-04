#include<iostream>
using namespace std;

int main()
{
	char game[5][5]{};
	cout << "请输入5x5的网格盘面，并输入位移方向（ASDW分别代表左下右上）：" << endl;
	for(int i = 0; i <= 4; i++)
	{
		for (int j = 0; j <= 4; j++)
		{
			cin >> game[i][j];
		}
	}
	char direction;
	cin >> direction;
	if (direction == 'A')
	{
		for (int i = 0; i <5; i++)//行
		{
			for (int j = 0; j <4; j++)//从左边开始，最右边不用考虑再右边
			{
				for (int k = 0; k <4-j ; k++)
				{
					if (game[i][k] == '*')
					{
						game[i][k] = game[i][k + 1];
						game[i][k + 1] = '*';//从左侧开始一个一个替换
					}
				}
			}
		}
	}
	else if (direction == 'D')
	{
		for (int i = 0; i <5; i++)
		{
			for(int j=4;j>0;j--)//从右边开始，最左边不用考虑再左边
			{
				for (int k = 4; k >4-j; k--)
				{
					if (game[i][k] == '*')
					{
						game[i][k] = game[i][k - 1];
						game[i][k- 1] = '*';//从右侧开始一个一个替换
					}
				}
			}
		}
	}
	else if (direction == 'W')
	{
		for (int j = 0; j <5; j++)
		{
			for(int i=0;i<4;i++)
			{
				for (int k = 0; k <4-i; k++)
				{
					if (game[k][j] == '*')
					{
						game[k][j] = game[k + 1][j];
						game[k + 1][j] = '*';
					}
				}
			}
		}
	}
	else if (direction == 'S')
	{
		for (int j = 0; j <5;j++ )
		{
			for (int i = 4; i >0; i--)
			{
				for (int k = 4; k >4-i; k--)
				{
					if (game[k][j] == '*')
					{
						game[k][j] = game[k - 1][j];
						game[k - 1][j] = '*';
					}
				}
			}
		}
	}
	//最后输出
	for (int i = 0; i <5; i++)
	{
		for (int j = 0; j <5; j++)
		{
			cout << game[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}