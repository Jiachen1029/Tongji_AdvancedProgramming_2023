#include<iostream>
#include<string>
using namespace std;

//结构体
struct City
{
    string name;
    int population;
    int farm;
    int food;
    int plantation; // 种植园
    int mine; // 矿山
    int gold; // 金币
    int productivity; // 生产力
    bool factory; // 工厂
    bool market; // 市场
}city;

int main()
{
    //初始化
    city.food = 0;
    city.gold = 0;
    city.productivity = 0;
    city.population = 0;
    city.farm = 0;
    city.plantation = 0;
    city.mine = 0;
    city.factory = false;
    city.market = false;
    cout << "请输入城市名称，初始人口数量，初始农田数量" << endl;
    cin >> city.name >> city.population >> city.farm;
    string input;
    while (true)
    {
        cout << "请输入操作（quit退出）：" << endl;
        cin >> input;

        if (input == "quit")
            break;
        else if (input == "farm")
        {
            int deltafarm;
            cin >> deltafarm;
            city.farm += deltafarm;
        }
        else if (input == "population")
        {
            int deltapopulation;
            cin >> deltapopulation;
            city.population += deltapopulation;
        }
        else if (input == "plantation")
        {
            int deltaplantation;
            cin >> deltaplantation;
            city.plantation += deltaplantation;
        }
        else if (input == "mine")
        {
            int deltamine;
            cin >> deltamine;
            city.mine += deltamine;
        }
        else if (input == "build")
        {
            string building;
            cin >> building;
            if (building == "factory")
            {
                city.factory = true;
            }
            if (building == "market")
            {
                city.market = true;
            }
        }
        if (city.population < 0) city.population = 0;
        if (city.farm < 0) city.farm = 0;
        if (city.plantation < 0) city.plantation = 0;
        if (city.mine < 0) city.mine = 0;
        // 更新产出食物数量、金币和生产力
        city.food = city.farm * 4 + city.plantation * 3 - city.population * 2;
        city.gold = city.plantation * 2 + city.mine * 2;
        city.productivity = city.mine * 3 + city.population;
        if (city.factory)
        {
            city.productivity += city.population * 2;
            city.gold -= 10;
        }
        if (city.market)
            city.gold += city.population * 2;
        // 显示当前状态
        cout << city.name << " " << city.population << "人 ";
        if (city.food >= 0)
            cout << "+" << city.food << "粮 ";
        else
            cout << city.food << "粮 ";
        if (city.gold >= 0)
            cout << "+" << city.gold << "金 ";
        else
            cout << city.gold << "金 ";
        if (city.productivity >= 0)
            cout << "+" << city.productivity << "锤" << endl;
        else
            cout << city.productivity << "锤" << endl;
    }
    return 0;
}