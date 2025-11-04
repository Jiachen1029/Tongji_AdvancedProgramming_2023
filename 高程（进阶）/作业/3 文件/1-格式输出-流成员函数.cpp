#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main() {
    double numbers[1000];
    int count = 0;
    double num;
    char endChar;
    cout << "请输入一些浮点数，以q结束:" << endl;
    //读取输入
    while (cin >> num)
    {
        if (count < 1000)
        {
            numbers[count] = num;
            count++;
        }
    }
    cin.clear();
    cin >> endChar;
    //找到小数点左侧位数最多的数
    int maxIntPartLength = 0;
    for (int i = 0; i < count; ++i)
    {
        int intPartLength = (numbers[i] < 0) ? static_cast<int>(log10(-numbers[i])) + 2 : static_cast<int>(log10(numbers[i])) + 1;
        if (intPartLength > maxIntPartLength)
        {
            maxIntPartLength = intPartLength;
        }
    }
    //输出对齐的小数
    for (int i = 0; i < count; ++i)
    {
        //去掉三位小数以后的位数
        double truncatedNum = static_cast<long long>(numbers[i] * 1000) / 1000.0;
        cout << setw(maxIntPartLength + 4) << fixed << setprecision(3) << truncatedNum << endl;
    }
    cout << "------程序结束------" << endl;
    return 0;
}