#include <iostream>
#define ARRAY_LENGTH 50
using namespace std;

void decode(char* p)
{
    /****************** TODO ******************/
    int len = int(strlen(p));
    int left = 0;
    int right = len - 1;
    while (left <= right)
    {
		cout << p[left++];
        if (left <= right)
        {
			cout << p[right--];
		}
    }
    /**************** TODO-END ****************/
}
int main()
{
    char str[ARRAY_LENGTH] = {};
    cin.getline(str, ARRAY_LENGTH);

    decode(str);

    return 0;
}