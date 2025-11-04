#include<iostream>
using namespace std;
int main()
{
    int a, b;
    int n;//n��a��b��ÿһ������
    int i = 0;//������
    cout << "��������������a��b����������[a,b]" << endl;
    cin >> a >> b;
    for (n = a; n <= b; n++)
    {
        if (n%7==0||n%10==7||n/10%10==7||n / 100 % 10 == 7 ||n / 1000 % 10 == 7 ||n / 10000 % 10 == 7|| n / 100000 % 10 == 7)
            //1<=a<=b<=100000,�ֱ���������7����λ����λ��7
        {
            cout << n << " ";
            i += 1;
        }
    }
    if (i != 0)
    {
        cout << endl;
        cout << "һ����" << i << "��������Ҫ˵��������" << endl;
    }
    else
        cout << "һ����" << i << "��������Ҫ˵��������" << endl;
    return 0;
}
