#include<iostream>
using namespace std;
int main()
{
    char colour,sound,touch;
    double density;
    cin >> colour >> sound >> touch >> density;
    if (colour == 71)//�����G����ɫ
    {
        if (sound == 77)//�����M������
            cout << "������Ǻùϡ�" ;
        else//�����C,���
        {
            if(touch==72)//�����H��Ӳ
                cout << "������Ǻùϡ�" ;
            else//�����S����
                cout << "������ǻ��ϡ�" ;
        }
    }
    else if (colour == 66)//�����B����ɫ
    {
        if(density<0.4)
            cout << "������Ǻùϡ�" ;
        else
            cout << "������ǻ��ϡ�" ;
    }
    else//�����W����ɫ
        cout << "������ǻ��ϡ�" ;
    return 0;
}
