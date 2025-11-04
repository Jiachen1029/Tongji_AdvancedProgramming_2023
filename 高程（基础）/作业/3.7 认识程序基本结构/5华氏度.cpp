#include <iostream>
using namespace std;
double a, b;
void hua()
{
	b=1.8*a+32;
}
int main()
{
	cin >> a;
	hua();
	cout << "摄氏温度" << a << "度对应华氏温度" << b << "度。" << endl;
	return 0;
}