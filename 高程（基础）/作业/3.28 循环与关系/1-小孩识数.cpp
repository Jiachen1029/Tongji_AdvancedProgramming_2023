#include<iostream>
using namespace std;

int main()
{
	int N,m;//个数，计数器
	long a;//每个数据
	long long sum=0;//总和
	cin >> N;//输入个数
	for (m = 0; m < N; m++)
	{
		cin >> a;//输入每个数据，由于循环N次，故可以输入N个数值
		sum = sum + a;//累加
	}
	cout << "这" << N << "个数的求和结果为" << sum << "。" << endl;
	return 0;
}