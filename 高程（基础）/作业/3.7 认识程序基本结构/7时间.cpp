#include <iostream>
using namespace std;
 
double year()
{
	double d;
	cin >> d;
	return d;
}
double time(double d)
{
	double v = 0.01;
	double t;
	t = d / v;
	return t;
}
void jie(double t)
{
	cout << "三体人需要" << t << "年到达地球。" << endl;
}
int main()
{
	double d =year();
	double t= time(d);
	jie(t);
	return 0;
}