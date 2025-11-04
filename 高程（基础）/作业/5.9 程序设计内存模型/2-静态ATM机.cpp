#include <iostream>
using namespace std;

int atm(int money)
{
    /****************** TODO ******************/
    static int count = 100;//静态变量，只会初始化一次，100元
    if (money >= 0)
    {
        cout << "存钱成功" << endl;
        count += money;
	}
    else if (count + money >= 0 && money < 0)
    {
		cout << "取钱成功" << endl;
		count += money;
    }
    else
    {
		cout<<"余额不足"<<endl;
	}
    return count;
    /**************** TODO-END ****************/
}

int main()
{
    int query;

    cin >> query;
    while (query != 0)
    {
        cout << "当前余额为" << atm(query) << "元。" << endl;
        cin >> query;
    }

    return 0;
}