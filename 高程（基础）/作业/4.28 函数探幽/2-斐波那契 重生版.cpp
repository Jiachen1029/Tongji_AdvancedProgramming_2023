#include <iostream>
using namespace std;

/****************** TODO ******************/
long long fibonacci(int n)
{
	long long a = 0, b = 0, c = 1;
	for (int i = 1; i < n; i++)
	{
		//原来a b c
		//现在  a b c
		//所以现在的a是原来的b，现在的b是原来的c，现在的c是原来b和c的和，也就是现在a和b的和
		a = b;
		b = c;
		c = a + b;
	}
	return c;
}
/**************** TODO-END ****************/

int main()
{
    int num = 0; // 斐波那契数列的项数

    cin >> num;
    cout << "斐波那契数列中第" << num
        << "项的值为" << fibonacci(num) << "。" << endl;

    return 0;
}