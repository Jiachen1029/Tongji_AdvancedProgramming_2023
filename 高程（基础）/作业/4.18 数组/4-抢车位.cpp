#include<iostream>
using namespace std;
int main()
{
	int car[15][2];
	//15辆车，前面的数代表i号车停在几号车位，后面的数1是没停，2是停了
	int park[10][2];
	//10个车位，前面的数代表j车位几号车停了，后面的数1是空车位，2是有车停
	// 初始化车辆和车位信息
	for (int k = 0; k < 15; k++) {
		car[k][1] = 1; // 表示车未停
	}
	for (int k = 0; k < 10; k++) {
		park[k][1] = 1; // 表示车位空闲
	}
	int i=0, j;//车号与车位号
	cout << "请输入车号与车位号，将判断是否能成功停车，输入-1结束" << endl;
	cin >> i;
	while (i != -1)
	{
		cin >> j;
		if (car[i][1] == 2)//i号车停车了
			cout << "该车已经停在" << car[i][0] << "号车位了！" << endl;
		else//如果没停车
		{
			if (park[j][1] == 2)//车位有别的车
			{
				cout << park[j][0] << "号车已经占据该车位了！" << endl;
			}
			else
			{
				cout << i << "号车成功停靠在" << j << "号车位！" << endl;
				park[j][0] = i;
				car[i][0] = j;
				park[j][1] = 2;//车位被占用
				car[i][1] = 2;//车停好了
			}
		}
		cin >> i;
	}
		return 0;
}