#include <iostream>
using namespace std;

int main()
{
	double a, c;//原数字 小数部分
	int b;//整数部分
	cin>>a;
	b = int(a);
	c = a - b;
	cout << "整数部分是"<< b<<"，小数部分是"<<c <<"。" << endl;
	return 0;
}