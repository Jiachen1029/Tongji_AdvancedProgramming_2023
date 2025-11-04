#include <iostream>
using namespace std;

int i = 1;
void move(char x, char y, int n)
{
	cout << i++ <<". " << x << " -> " << y << endl;
}
void hannuo(char x, char y, char z, int n)
{
	if (n == 1)
		move(x, y, 1);
	else
	{
		hannuo(x, z, y, n - 1);
		move(x, y, n);
		hannuo(z, y, x, n - 1);
	}
}
int main()
{
	char x, y, z;
	int n;
	cin >> x >> y >> n;
	z = 'A' + 'B' + 'C' - x - y;
	hannuo (x, y, z, n);
	return 0;
}