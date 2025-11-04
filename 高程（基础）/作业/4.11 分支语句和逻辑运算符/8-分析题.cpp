#include<iostream>
using namespace std;
int main()
{
    int a;
    cin >> a;
    if (a < 0)
        cout << "(-��, 0)" << endl;
    else if (0 < a < 100)
        cout << "(0, 100)" << endl;
    else
        cout << "(100, +��)" << endl;

    return 0;
}
