#include<iostream>
using namespace std;
int main()
{
    cout << "������Сʱ/������" << endl;
    int h, min;
    cin >> h >> min;
    if (h <= 14 || h >= 18)
        cout << "���û�����ʱ��Ϊ0���ӡ�" << endl;
    else
    {
        if (h == 15)
        {
            if (min < 30)
                cout << "���û�����ʱ��Ϊ0���ӡ�" << endl;
            else
                cout << "���û�����ʱ��Ϊ" << (17 - h) * 60 + (5 - min) << "���ӡ�" << endl;
        }
        else if (h == 16)
        {
            if (min < 15 || min >= 20)
                cout << "���û�����ʱ��Ϊ" << (17 - h) * 60 + (5 - min) << "���ӡ�" << endl;
            else
                cout << "���û�����ʱ��Ϊ0���ӡ�" << endl;
        }
        else
        {
            if (min < 5)
                cout << "���û�����ʱ��Ϊ" << (17 - h) * 60 + (5 - min) << "���ӡ�" << endl;
            else
                cout << "���û�����ʱ��Ϊ0���ӡ�" << endl;
        }
    }
    return 0;
}
