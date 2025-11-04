#include <iostream>
#define MAX_STR_LENGTH 100
using namespace std;

void print_merged(const char(*str)[MAX_STR_LENGTH])
{
    /****************** TODO ******************/
    const char *p1 = str[0];
    const char *p2 = str[1];
    while (*p1 != '\0' && *p2 != '\0')
    {
        while (*p1 != ' ' && *p1 != '\0')
        {
			cout << *p1;
			p1++;
		}
		cout << ' ';
        while (*p2 != ' ' && *p2 != '\0')
        {
			cout << *p2;
			p2++;
		}
		cout << ' ';
        if (*p1 == ' ')
        {
			p1++;
		}
        if (*p2 == ' ')
        {
			p2++;
		}
	}
    //如果有一个字符串已经结束，那么直接输出另一个字符串
    while (*p1 != '\0'&&*p2=='\0')
    {
        cout<<*p1;
        p1++;
    }
    while (*p2 != '\0' && *p1 == '\0')
    {
        cout<<*p2;
        p2++;
	}
    /**************** TODO-END ****************/
}

int main()
{
    char str[2][MAX_STR_LENGTH] = {};

    cin.getline(str[0], MAX_STR_LENGTH);
    cin.getline(str[1], MAX_STR_LENGTH);

    print_merged(str);
  
    return 0;
}