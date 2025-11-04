#include <iostream>
using namespace std;

char* my_strcat(char* dest, const char* src)
{
    /****************** TODO ******************/
    // 思考：<string.h>头文件中的strcat为什么返回类型为char*？
    // 原因是strcat函数将src拼接到dest后，返回dest的首地址，即返回dest的地址

    char* p = dest;
    const char* q = src;
    //找到'\0'
    while (*p != '\0')
    {
	    p++;
    }
    //拼接
    while (*q != '\0')
    {
		*p = *q;
		p++;
		q++;
    }
	*p = '\0';
    return dest;
    /**************** TODO-END ****************/
}

int main()
{
    const int str_length = 100;

    char arr1[str_length] = {};
    char arr2[str_length] = {};

    cin.getline(arr1, str_length);
    cin.getline(arr2, str_length);

    my_strcat(arr1, arr2);

    cout << arr1 << endl;

    return 0;
}