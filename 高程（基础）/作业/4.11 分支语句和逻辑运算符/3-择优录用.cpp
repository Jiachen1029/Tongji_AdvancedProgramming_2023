#include<iostream>
#include<iomanip>
using namespace std;
int main()
{
    double m,sum=0,n=3.49999;//�������¼ȡ�ļ����ܺ��Լ�����ƽ����
    int i = 0;
    while (cin>>m)
    {
        if (m==-1)
            break;
        else
        {
            if (i < 10)
            {
                if (m > n)
                {
                    cout << setiosflags(ios::fixed) << setprecision(2) << m << "��¼���ˡ�" << endl;
                    i = ++i;
                    sum = sum + m;
                    n = sum / i;
                }
                else
                    cout << setiosflags(ios::fixed) << setprecision(2) << m << "δ��¼�á�" << endl;
            }
            else
                cout << setiosflags(ios::fixed) << setprecision(2) << m << "δ��¼�á�" << endl;
        }
    }
    return 0;
}
//����5.0����5.0���滹5.0�����
