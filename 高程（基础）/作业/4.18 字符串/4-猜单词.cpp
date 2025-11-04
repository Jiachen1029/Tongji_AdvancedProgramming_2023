#include <iostream>
using namespace std;

//判断两字符串是否相等
int strcmp(char* str1, char* str2)
{
	int i = 0;
	while (str1[i] != '\0' && str2[i] != '\0')
	{
		if (str1[i] != str2[i])
			return 0;//不相等
		i++;
	}
	if (str1[i] == '\0' && str2[i] == '\0')
		return 1;//相等
	else
		return 0;
}

int main() 
{
	char word[31];
	char star[31]{};//*与猜中的字母
	char guess[31]{};
	cout << "请输入单词，下面开始猜单词：" << endl;
	cin.getline(word,30);
	for (int i = 0; i < 31; i++)
	{
		if (word[i] != '\0')
			star[i] = '*';
		else
			star[i] = '\0';
	}
	int length = int(strlen(word));//strlen输出长度
	cout << star << endl;
	while (cin.getline(guess, 30))
	{
		if (guess[0] == 'e' && guess[1] == 'n' && guess[2] == 'd' && guess[3] == '\0')
			//如果输入end直接停止
			break;
		else if (strcmp(guess, star))//全部猜中，直接停止
		{
			cout << guess << endl;
			break;
		}
		else
		{
			for (int j = 0; j < length; j++)
			{
				if (guess[j] != '\0' && guess[j] == word[j])//猜中某个字母，进行替换（前提：不是空字符）
				{
					star[j] = guess[j];
				}
			}
			
		}
		cout<< star << endl;
	}
	return 0;
}
