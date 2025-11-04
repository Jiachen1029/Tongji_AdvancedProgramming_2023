#include<iostream>
using namespace std;
int main()
{
	int m[5][5]={};//五行五列，只取中间三行三列，防止越界
	int a, b;//输入的a行，b列（0，1，2），实际在五行五列中应该加1
	cout << "请输入a行b列（可以选择0，1，2），将进行翻转游戏，0为正面，1为反面，输入-1游戏停止。" << endl;
	cin >> a;
	while (a != -1)
	{
		cin >> b;
		m[a][b+1]++;//左边+1
		m[a+1][b+1]++;//本身+1
		m[a+2][b + 1]++;//右边+1
		m[a + 1][b]++;//上边+1
		m[a + 1][b + 2]++;//下边+1
		cin >> a;
	}
	cout << "最终的翻转结果是：" << endl;
	for (int i = 1; i <= 3; i++)//行
	{
		for(int j=1;j<=3;j++)//列
		{
			cout << m[i][j] % 2 << " ";
		}
		cout << endl;
	}
	return 0;
}