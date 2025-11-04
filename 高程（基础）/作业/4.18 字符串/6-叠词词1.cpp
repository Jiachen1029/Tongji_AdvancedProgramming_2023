#include<iostream>
#include<cstring>
using namespace std;

char sentence[210]{};
char word[210][20]{};
//提取单词
void tiqu()
{
	int n = 0;//用于提取之前的字符串句子
	int	i = 0, j = 0;//用于提取之后的单词字符串组，i是指第几个单词，j是指这个单词的第几个字母或者字符
	while (n < 210)
	{
		if ((sentence[n]>= 48  && sentence[n] <= 57) || (sentence[n] >= 'A' && sentence[n] <= 'Z') || (sentence[n] >= 'a' && sentence[n] <= 'z') || sentence[n] == 39 || sentence[n] == '-')
		//如果输入的是数字，字母，'或者-，那么需要判断
		{
			if ((n >= 1)&&((sentence[n - 1] <= 57 && sentence[n - 1] >= 48) || (sentence[n - 1] >= 'A' && sentence[n - 1] <= 'Z') || (sentence[n - 1] >= 'a' && sentence[n - 1] <= 'z') || sentence[n - 1] == 39 || sentence[n - 1] == '-')) {}
				//如果下一个还是数字，字母，'或者-,那么还是这个单词
			else
			{
				j = 0;
				i++;//否则单词数+1
			}
			word[i][j] = sentence[n];
			j++;
		}
		else
		{
			i++;
			word[i][0] = sentence[n];//直接去判断下一个
		}
		n++;
	}
}
int main()
{
	cin.getline(sentence, 210);
	tiqu();
	//筛选单词
	int i = 0;
	while (i < 210)
	{
		if (strcmp(word[i], word[i + 2]) == 0 && word[i + 1][0] == ' ')//重复而且中间有一个空格
		{
			word[i+1][0]=word[i][0] = '\0';//不输出空格与这个单词
		}
		cout << word[i];
		i++;
	}
	return 0;
}