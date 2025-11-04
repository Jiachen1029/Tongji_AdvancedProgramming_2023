#include<iostream>  
#include<string>  
#include<algorithm> //reverse函数所在头文件
using namespace std;

int main()
{
	string a;
	string b;
	string fan;//反过来的sum
	int c = 0;//每一位相加，用于存储当前位的和
	int jinwei = 0;
	cout << "请输入两个大数，将进行求和运算：" << endl;
	cin >> a >> b;
	int lengtha =int(a.size()) - 1;
	int lengthb = int(b.size()) - 1;
	

	//从结尾开始每位相加
	while (lengtha >= 0 && lengthb >= 0)
	{
		c = a[lengtha]-'0' + b[lengthb]-'0' + jinwei;
		fan += c % 10 + '0';//反过来的sum，位数左到右从个位到更大位，不断添加
		if (c >= 10)
			jinwei = 1;
		else
			jinwei = 0;
		lengtha--;
		lengthb--;
	}
	//直到有一个减到0，只有剩下的
	while (lengtha >= 0)
	{
		c = a[lengtha] - '0' + jinwei;
		fan += c % 10 + '0';//反过来的sum，位数左到右从个位到更大位，不断添加
		if (c >= 10)
			jinwei = 1;
		else
			jinwei = 0;
		lengtha--;
	}
	while (lengthb >= 0)
	{
		c = b[lengthb] - '0' + jinwei;
		fan += c % 10 + '0';//反过来的sum，位数左到右从个位到更大位，不断添加
		if (c >= 10)
			jinwei = 1;
		else
			jinwei = 0;
		lengthb--;
	}
	//最高位进位问题
	if (jinwei == 1)//在最后
		fan += jinwei + '0';
	//最后输出倒序（直接参考代码了）
	reverse(fan.begin(), fan.end());
	cout << fan << endl;	
	return 0;
}