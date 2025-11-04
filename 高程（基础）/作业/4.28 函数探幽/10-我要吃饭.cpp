#include<iostream>
using namespace std;

int beginx, beginy, finalx, finaly;
int building[9][9]{};
bool matrix[9][9]{};//新开一个矩阵记录是否走过
int changex[4] = { 0, 1, 0, -1 };
int changey[4] = { 1, 0, -1, 0 };
void find(int building[9][9])
{
	//寻找教学楼最外围为1的点的坐标,即出口(finalx,finaly)
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (building[0][i] == 1)
			{
				finalx = 0;
				finaly = i;
				break;
			}
			if (building[8][i] == 1)
			{
				finalx = 8;
				finaly = i;
				break;
			}
			if (building[i][0] == 1)
			{
				finalx = i;
				finaly = 0;
				break;
			}
			if (building[i][8] == 1)
			{
				finalx = i;
				finaly = 8;
				break;
			}
		}
	}
}
bool way(int beginx, int beginy, int finalx, int finaly)
{
	matrix[finalx][finaly] = true;
	if (beginx == finalx && beginy == finaly)
	{
		cout << finalx << "," << finaly << endl;
		return true;
	}
	for (int i = 0; i < 4; i++)
	{
		int newx = finalx + changex[i];
		int newy = finaly + changey[i];//分别是y+1, x+1, y-1, x-1
		//从终点往起点走，没走一个再用一下way函数迭代，直到到起点输出坐标
		if (newx >= 0 && newx <= 8 && newy >= 0 && newy <= 8 && building[newx][newy] == 1 && !matrix[newx][newy])
			//判断是否越界，是否为墙，是否走过
		{
			if (way(beginx, beginy, newx, newy))
			{
				cout << finalx << "," << finaly << endl;
				return true;
			}
		}
	}
	return false;
}
int main()
{
	//输入教学楼地形图
	for (int i = 0; i <= 8; i++)
	{
		for (int j = 0; j <= 8; j++)
		{
			cin >> building[i][j];
		}
	}
	cin >> beginx >> beginy;
	find(building);//找出口
	way(beginx, beginy, finalx, finaly);
	return 0;
}