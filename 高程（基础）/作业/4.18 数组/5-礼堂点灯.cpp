#include <iostream>  
using namespace std;
int main()
{
    int light[100][2];//序号分别为0-99，3种状态
    for (int i = 0; i <= 99; i++)
    {
        light[i][0] = i;
        light[i][1] = 0;//初始是熄灭
    }
    cout << "若输入为1，则所有质数灯改变自身的开关状态。" << endl;
    cout << "若输入为2，则所有合数灯改变自身的开关状态。" << endl;
    cout << "若输入为3，则所有奇数灯改变自身的开关状态。" << endl;
    cout << "若输入为4，则所有偶数灯改变自身的开关状态。" << endl;
    cout << "若输入为-1，则程序停止，输出结果。" << endl;
    int n;
    while (cin >> n&&n!=-1)
    {
        if (n == 1)
        {
            for (int i = 2; i <= 99; i++)//i被除数，范围2到99
            {
                bool isprime = true; // 假设i是质数  
                for (int j = 2; j * j <= i; j++) // j是除数，只检查到sqrt(i)  
                {
                    if (i % j == 0) // 如果i不是质数  
                    {
                        isprime = false; 
                        break;  
                    }
                }
                if (isprime) // 如果i是质数  
                {
                    light[i][1]++; 
                }
            }
        }
        else if (n == 2)
        {
            for (int i = 2; i <= 99; i++)//i被除数，范围2到99
            {
                for (int j = 2; j * j <= i; j++)//j是除数
                {
                    if (i % j == 0)
                    {
                        light[i][1]++;//合数找到一个就可
                        break;
                    }///////////不加{}输入1234为什么会有差别？
                }
            }
        }
        else if (n == 3)
        {
            for (int i = 1; i <= 99; i += 2)
                light[i][1]++;
        }
        else
        {
            for (int i = 0; i <= 98; i += 2)
                light[i][1]++;
        }
    }
    cout << "熄灭：";
    for (int i = 0; i <= 99; i++)
    {
        if (light[i][1] % 3 == 0)
            cout << light[i][0]<<" ";
    }
    cout << endl;
    cout << "长亮：";
    for (int i = 0; i <= 99; i++)
    {
        if (light[i][1] % 3 == 1)
            cout << light[i][0]<<" ";
    }
    cout << endl;
    cout << "闪烁：";
    for (int i = 0; i <= 99; i++)
    {
        if (light[i][1] % 3 == 2)
            cout << light[i][0]<<" ";
    }
    return 0;
}