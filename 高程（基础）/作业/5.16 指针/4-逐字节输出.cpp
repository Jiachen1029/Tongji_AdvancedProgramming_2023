#include<iostream>
using namespace std;

void print(int* p)
{
	for (int i = 0; i < 5; i++)
	{
		char *q = (char *)(p + i);
		for (int j = 0; j < sizeof(int); j++)
		{
			cout << (int)*(q + j) << " ";
		}
	}
}
int main()
{
	int a[5];
	cout << "请输入5个整型数，下面将转化为转化为十进制后的每个字节的内容" << endl;
	for (int i = 0; i < 5; i++)
	{
		cin >> a[i];
	}
	print(a);
	return 0;
}