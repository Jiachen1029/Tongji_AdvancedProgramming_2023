#include<iostream>
using namespace std;
int main()
{
	cout << "请输入一行字符串，将进行小写转大写" << endl;
	char s[200];//0-200，最后一个必须\0
	cin.getline(s, 200);
	int count = 0;
	for (int i = 0; i < 199; i++)
	{
		if (s[i] >= 'a' && s[i] <= 'z')
		{
			s[i] -= 32;
			count++;
		}
		else if (s[i] == '\0')
			break;
	}
	cout << "共转换"<<count<<"个字母。" << endl;
	cout << s << endl;
	return 0;
}