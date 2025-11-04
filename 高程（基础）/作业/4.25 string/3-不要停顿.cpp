#include<iostream>
#include<string>
using namespace std;

int main()
{
	string input;
	string result;
	int num = 0;
	while (getline(cin, input))//把cin放到input里
	{
		if (input == " ")
			break;
		else
		{
			num += int(input.size());
			result += input;//结果合并
		}
	}
	cout << num << endl;
	cout << result<<endl;
	return 0;
}