#include <iostream>
using namespace std;
int main()
{
	cout << "请输入20个整数，将自动升序排列" << endl;
	int a[20];
	for (int i = 0;i<=19;i++)
	{
		cin >> a[i];
	}
	int i, j, other;
	for (i = 0; i < 19; i++)
	{
		for (j = 0; j < 19 - i; j++)
		{
			if (a[j] > a[j + 1])
			{
				other = a[j];
				a[j] = a[j + 1];
				a[j + 1] = other;
			}
		}
	}
	cout << "升序排序后的结果：" << endl  ;
	for (i = 0; i <= 19; i++)
	{
		cout <<  a[i] << " ";
	}
	return 0;
}