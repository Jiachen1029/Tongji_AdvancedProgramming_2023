#include <iostream>
using namespace std;

/****************** TODO ******************/
void print_variable(int* a)//&a表示a的地址
{
    cout << a << " ";//输出a的地址
    cout << *a << endl;//输出a的值
}
/**************** TODO-END ****************/

int main()
{
    int a = 0;

    cin >> a;

    print_variable(&a);

    return 0;
}