#include <iostream>
using namespace std;

/****************** TODO ******************/
    // 返回num的整数部分
int integer(double num) 
{
    return int(num);
}
    // 返回num的小数部分
double decimal(double num)
{
	return (num - integer(num));
}
/**************** TODO-END ****************/

int main()
{
    double num = 0;

    cin >> num;
    cout << "整数部分是" << integer(num)
        << "，小数部分是" << decimal(num) << "。" << endl;

    return 0;
}