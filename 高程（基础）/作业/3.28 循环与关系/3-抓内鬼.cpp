#include<iostream>
using namespace std;

int main()
{
	int a;
	int i = 0;
	while (cin >> a) {
		if (cin.fail())
		{
			break;
		}
		else
			i += 1;
	}
	cout << i << endl;
	return 0;
}
