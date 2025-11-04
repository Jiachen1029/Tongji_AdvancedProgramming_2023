#include<iostream>
using namespace std;
int main()
{
	char m[200];
	int n;//偏移量
	cout << "请输入一行字符串，每个词以空格分隔，并输入解密的偏移量，负数代表向前偏移，正数代表向后偏移。";
	cout << endl;
	cin.getline(m, 200);
	cin >> n;
	for (int i = 0; i <= 199; i++)
	{
		if (m[i] == '\0')
			break;
		else if (m[i] >= 'a' && m[i] <= 'z')
		{
			if (m[i] + n < 'a' && n < 0)//从小写超出下限
				m[i] = m[i] + n + 26;
			else if (m[i] + n > 'z')//小写上限
				m[i] = m[i] + n - 26;
			else//正常
				m[i] += n;
		}
		else if(m[i] >= 'A' && m[i] <= 'Z')
		{
			if (m[i] + n > 'Z' && n > 0)//从大写超出上限
				m[i] = m[i] + n - 26;
			else if (m[i] + n < 'A')//大写下限
				m[i] = m[i] + n + 26;
			else//正常
				m[i] += n;
		}
	}
	cout << m << endl;
	return 0;
}