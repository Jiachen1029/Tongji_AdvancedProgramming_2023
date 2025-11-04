#include <iostream>  
#include <cmath> 
using namespace std;
int main()
{
    int a, b, light;
    int m[9][9]{};
    cout << "请输入光源的坐标(a,b)与亮度light，输入-1程序结束：" << endl;
    cin >> a;
    while (a!=-1)
    {   
        cin >> b >> light;
        m[a][b] = 10;//其他地方没有10这个数，暂且用10代替
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                int n = light - abs(i - a) - abs(j - b);
                if (n>m[i][j])//每次输入灯光，都与前面的值进行比较
                {
                    m[i][j] = n;//只要光强度变大，都应该更新数据
                }
            }
        }
        cin >> a;
    }
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (m[i][j] == 10)
            {
                cout << "*" << " ";
            }
            else
            {
                cout << m[i][j] << " ";
            }
        }
        cout << endl;
    }
    return 0;
}