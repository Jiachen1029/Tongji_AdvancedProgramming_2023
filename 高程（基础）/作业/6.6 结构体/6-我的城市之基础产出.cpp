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
}city;

int main()
{
    //初始化
    city.food = 0;
    cout << "请输入城市名称，初始人口数量，初始农田数量：" << endl;
    cin >> city.name >> city.population >> city.farm;

    //每点人口消耗 2点食物，每块农田产出4点食物
    string input;
    while (true)
    {
        cout << "请输入人口变化与农田变化（+为增加，-为减少）（quit退出）" << endl;
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

        // 在每次输入后立即更新食物数量
        if (city.population <= 0)
            city.population = 0;
        if (city.farm <= 0)
            city.farm = 0;
        city.food = city.farm * 4 - city.population * 2;

        // 显示当前状态
        if (city.food >= 0)
            cout << city.name << " " << city.population << "人" << " +" << city.food << "粮" << endl;
        else
            cout << city.name << " " << city.population << "人" << " " << city.food << "粮" << endl;
    }
    return 0;
}