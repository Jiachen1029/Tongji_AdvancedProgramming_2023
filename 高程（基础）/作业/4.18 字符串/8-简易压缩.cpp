#include<iostream>
#include<cstring>
using namespace std;
int main()
{
	char s[250]{};
	char zip[200]{};//位数与zip相同
	cout << "请输入字符串，将进行简易压缩。" << endl;
	cin.getline(s, 250);
	int count = 1;
	int len = int(strlen(s));
	int ziplen = 0;
	char current=s[0];
	for (int i = 1; i <= len; i++)
	{
		if (s[i] == current)
		{
			count++;
		}
		else
		{
			while (1)
			{
				if (count > 9)
				{
					ziplen++;
					zip[ziplen] = current;
					zip[++ziplen] = '0' + 9;
					count = count - 9;
				}
				else
				{
					ziplen++;
					zip[ziplen] = current;
					zip[++ziplen] = '0' + count;
					break;
				}
			}
			current = s[i];
			count = 1;
		}
	}
	//输出
	if (ziplen >= len)
	{
		cout << "压缩失败！" << endl;
	}
	else
	{
		for (int i = 0; i <= ziplen; i++)
		{
			cout << zip[i];
		}
	}
	return 0;
}