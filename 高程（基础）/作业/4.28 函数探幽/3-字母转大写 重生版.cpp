#include <iostream>
#define STRING_MAX_LENGTH 200
using namespace std;

/****************** TODO ******************/
int to_upper(char* str)
{
	int count = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] >= 'a' && str[i] <= 'z')
        {
			str[i] -= 32;
			count++;
		}
	}
	return count;
}
//问题：字符串内容改变了吗？为什么？
//回答：改变了，因为在函数中传递的是指针，指针指向的是字符串的首地址，修改会影响到原字符串。
/**************** TODO-END ****************/

int main()
{
    char str[STRING_MAX_LENGTH];
    cin.getline(str, STRING_MAX_LENGTH);

    int num = to_upper(str);
    // 想一想，字符串内容改变了吗？为什么？

    cout << "共转换" << num << "个字母。" << endl;
    cout << str << endl;

    return 0;
}