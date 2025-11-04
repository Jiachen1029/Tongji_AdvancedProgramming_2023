#include <iostream>
#include <string>
#include <cstring>
using namespace std;
int main()
{
	cout << "1长度获取，2字符串输出，3大小写翻转，4定点插入，5子串替换，q结束" << endl;
	string s;
	char m;
	while (cin >> m)
	{
		if (m == 'q')
		{
			cout <<s << endl;
			break;
		}
		if (m == '1')
		{
			cout << s.size() << endl;
		}
		if (m == '2')
		{
			cout <<  s << endl;
		}
		if (m == '3')
		{
			char a;	
			cin >> a;
			if (a == 'L')
			{	//大写字母转小写字母
				for (int i = 0; i < s.size(); i++)
				{
					if (s[i] >= 'A' && s[i] <= 'Z')
					{
						s[i] += 32;
					}
				}
			}
			if (a == 'U')
			{	//小写字母转大写字母
				for (int i = 0; i < s.size(); i++)
				{
					if (s[i] >= 'a' && s[i] <= 'z')
					{
						s[i] -= 32;
					}
				}
			}
		}
		if (m == '4')
		{
			//cout << "将字符串s插入到s[op]处" << endl;
			//cout<<"输入字符串s和插入位置op"<<endl;
			int op;
			string str;
			cin >> str;
			cin >> op;
			s=s.insert(op, str);
		}
		if (m == '5')
		{
			//cout << "找到s1在s中第一次出现的位置，并用s2替换" << endl;
			//cout<<"输入s1和s2"<<endl;
			string s1, s2;
			cin >> s1;
			cin >> s2;
			int pos = int(s.find(s1));
			if (pos == -1)
			{
			}//没找到，不执行
			else
			{
				s=s.replace(pos, s1.size(), s2);
			}
		}
	}
	return 0;
}