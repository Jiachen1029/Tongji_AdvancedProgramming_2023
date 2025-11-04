#include<iostream>
using namespace std;

int main()
{
	int m=0,one=0,two=0,three=0,four=0,five=0,six=0,seven=0,eight=0;

	cin>>m;
	eight=m/128;
	seven=m%128/64;
	six=m%64/32;
	five=m%32/16;
	four=m%16/8;
	three=m%8/4;
	two=m%4/2;
	one=m%2;
	
	cout << eight << seven << six << five << four << three << two << one << endl;
	return 0;
}