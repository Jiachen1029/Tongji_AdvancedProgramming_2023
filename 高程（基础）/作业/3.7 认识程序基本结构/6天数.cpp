#include <iostream>
using namespace std;
int a,b,c;
int nian()
{
	c = (b - a) * 365;
	return c;
}
int main()
{
	cin >> a >> b;
	nian();
	cout << "Ò»¹²"<<c<<"Ìì¡£" << endl;
	return 0;
}