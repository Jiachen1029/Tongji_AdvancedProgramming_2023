#include <iostream>
using namespace std;
int main()
{
    const char* s[] = {
    "����", "����", "����",
    "����", "��ɮ", "���",
    "�˽�", "ɳɮ", "��Ǵ���",
    "���Ǵ���", "�캢��", "�׹Ǿ�" };
    int k = 5;
    char c = 'C';
    do {
        switch (c++) {
        case 'A':
            k %= 8;
            break;
        case 'B':
            c = 'G';
            k *= 9;
        case 'C':
            k = k / 4 - 1;
            break;
        case 'D':
            k = k * 2;
            continue;
        case 'E':
            k = k * 4 + 1;
            break;
        case 'F':
            c -= 6;
            break;
        default:
            k = k + 3;
        }
        k++;
        // �������д�����������s�еĵ�k��Ԫ�ء�
        // ע�⣬����Ԫ�ش��㿪ʼ��ţ�����s[0]="����"��
        cout << s[k];
    } while (c < 'G');
    cout << endl;
    return 0;
}
