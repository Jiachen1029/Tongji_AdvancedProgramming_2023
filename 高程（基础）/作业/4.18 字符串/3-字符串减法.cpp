#include<iostream>
using namespace std;
int main()
{
	char str1[200];
	char str2[200];
	cout << "输入两个字符串，将输出它们相减的结果。" << endl;
	cin.getline(str1,200);
	cin.getline(str2,200);
	for (int i = 0; i <= 199&& str2[i] != '\0'; i++)//str2中每一个字符
	{
		for (int j = 0; j <= 199&& str1[j] != '\0'; )//str1中每一个字符
		{
			if (str1[j] == str2[i])//如果发现相同的项
			{
				for (int x = j; x <= 198; x++)//从这项以后的全部往前调一位，最后一位肯定是空
				{
					str1[x] = str1[x + 1];
				}
			}
			else
				j += 1;
		}
	}
	int count = 0;
	for (int i = 0; i <= 200; i++)
	{
		if (str1[i] != '\0')
		{
			count++;
			cout << str1[i];
		}
		else if (count == 0)
		{
			cout << "空串" << endl;
			break;
		}

		else
			break;
	}
	return 0;
}