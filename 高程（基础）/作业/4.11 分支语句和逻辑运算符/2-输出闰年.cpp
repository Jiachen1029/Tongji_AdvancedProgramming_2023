#include<iostream>
using namespace std;

int main()
{
    int N;
    cin >> N;
    if (cin.fail())
        cout << "�������";
    else
    {
        if (N % 4 == 0)
        {
            if (N % 100 == 0)
            {
                if (N % 400 == 0)
                    cout << N << "�������ꡣ" ;
                else
                    cout << N << "�겻�����ꡣ" ;
            }
            else
                cout << N << "�������ꡣ" ;
        }
        else
            cout << N << "�겻�����ꡣ";
    }
    return 0;
}
