#include<iostream>
using namespace std;

int main()
{
	int n;
	cout << "请输入项数" << endl;
	cin >> n;
	long long a=0, b=0, c=1;//分别是a(n-2) a(n-1) an
	for (int i = 2; i <= n; i++)
	{
	//原来a b c
	//现在  a b c
	//所以现在的a是原来的b，现在的b是原来的c，现在的c是原来b和c的和，也就是现在a和b的和
		a = b;
		b = c;
		c = a + b;
	}
	cout <<"斐波那契数列中第"<<n<<"项的值是" << c << "。" << endl;
	return 0;
}