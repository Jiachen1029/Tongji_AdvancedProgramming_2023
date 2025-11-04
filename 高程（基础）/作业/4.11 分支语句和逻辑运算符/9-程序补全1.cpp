#include<iostream>
using namespace std;
int main()
{
    int score;
    cin >> score;
    switch ( score/10)
    {
        /* �� */
    case 9:
        cout << "��" << endl;
        break;
    case 8:
        cout << "��" << endl;
        break;
    case 7:
        cout << "��" << endl;
        break;
    case 6:
        cout << "����" << endl;
        break;
    default:
        cout << "������" << endl;
        /* �� */
    }
    return 0;
}
