#include<iostream>
using namespace std;
int main()
{
	int a, b;
	int n;//从2到i-1的除数
	cout << "请输入区间的两端值" << endl;
	cin >> a >> b;
	for (int i = a; i <= b; ++i)//i是a到b每个数都筛一遍的数
	{
		if ((i % 2 != 0 || i == 2)&&i!=1)
		{
			bool shi = true;
			for (n = 2; n * n <= i; ++n)
			{
				if (i % n == 0)
				{
					shi = false;
				}

			}
			if (shi)
				cout << i << " ";
		}
	}
	return 0;
}
