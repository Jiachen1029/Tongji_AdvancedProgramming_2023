#include<iostream>
#include<string>
using namespace std;
int main()
{
	string m;
	int input;
	cout << "请输入数字！" << endl;
	while (!(cin>>input))//如果没有输入成功
	{
		cout << "输入错误！" << endl;
		//input缓冲区清空
		cin.clear();
		getline(cin, m);
	}
	cout << input;
	return 0;
}