#include<iostream>
#include<iomanip>
//第二题保留十位小数的做法
using namespace std;

int main()
{
	int i;
	double factorial=1.0;
	double sum = 1.0;
	cout << "请输入级数的项数" << endl;
	cin >> i;
	for (int r = 1; r <= i; r++)
	{
		factorial *= r;//先求阶乘
		sum += (1 / factorial);//再求相加得到的e值
	}
	cout << "估算值为" << setiosflags(ios::fixed) << setprecision(10) << sum << "。" << endl;
	//第二题保留十位小数的做法
	return 0;
}