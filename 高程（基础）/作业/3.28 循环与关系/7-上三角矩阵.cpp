#include<iostream>
using namespace std;
//输出ALPD矩阵
int main()
{
	int a = 1;
	int n;
	cout << "请输入矩阵的长宽" << endl;
	cin >> n;
	for (int i = 1; i <= n; ++i)//行
	{
		for (int j = 1; j <= n; ++j)//列
			if (j >= i)
			{
				cout << a <<" ";
				a += 1;
			}
			else
				cout << 0 << " ";
		cout << endl;
	}
	return 0;
}