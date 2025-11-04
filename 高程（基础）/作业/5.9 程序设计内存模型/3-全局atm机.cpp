#include <iostream>
using namespace std;

int balance = 100;

/****************** TODO ******************/
void save_money(int money)
{
    cout << "存钱成功" << endl;
    balance += money;
}
void retrieve_money(int x)//此时的-money是正数，x为正数
{
    if (balance >= x)
    {
        cout<< "取钱成功" << endl;
        balance -= x;
    }
    else
    {
        cout << "余额不足" << endl;

    }
}
void print_balance()
{
	cout <<"当前余额为"<< balance<<"元。" << endl;
}
/**************** TODO-END ****************/

void atm_manager(int money)
{
    if (money > 0) {
        save_money(money);
    }
    else if (money < 0) {
        retrieve_money(-money);
    }
    print_balance();
}

int main()
{
    int query;

    cin >> query;
    while (query != 0)
    {
        atm_manager(query);
        cin >> query;
    }

    return 0;
}