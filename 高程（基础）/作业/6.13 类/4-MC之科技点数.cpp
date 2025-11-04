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
    int science;
    bool campus{};
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
        else if (input == "campus")
        {
			city.campus = true;
		}
		else
			cout << "输入错误，请重新输入" << endl;

        // 在每次输入后立即更新食物数量
        if (city.population <= 0)
            city.population = 0;
        if (city.farm <= 0)
            city.farm = 0;
        city.food = city.farm * 4 - city.population * 2;
        if(city.campus)
			city.science=4;
        // 显示当前状态
        cout << city.name << " " << city.population << "人" << " " << city.food << "粮";
        cout << " " << city.science << "科技点数" << endl;
    }
    return 0;
}
/*
#include<iostream>
#include<string>
using namespace std;

// 类
class City
{
public:
    static string name;
    static int population;
    static int farm;
    static int food;
    static int science;
    static bool campus;

    City() { campus = false; } // 构造函数
};

// 静态成员变量初始化
string City::name = "";
int City::population = 0;
int City::farm = 0;
int City::food = 0;
int City::science = 0;
bool City::campus = false;

int main()
{
    //初始化
    City::food = 0;
    cout << "请输入城市名称，初始人口数量，初始农田数量：" << endl;
    cin >> City::name >> City::population >> City::farm;

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
            City::farm += deltafarm;
        }
        else if (input == "population")
        {
            int deltapopulation;
            cin >> deltapopulation;
            City::population += deltapopulation;
        }
        else if (input == "campus")
        {
            City::campus = true;
        }
        else
            cout << "输入错误，请重新输入" << endl;

        // 在每次输入后立即更新食物数量
        if (City::population <= 0)
            City::population = 0;
        if (City::farm <= 0)
            City::farm = 0;
        City::food = City::farm * 4 - City::population * 2;
        if(City::campus)
            City::science=4;
        // 显示当前状态
        cout << City::name << " " << City::population << "人" << " " << City::food << "粮";
        cout << " " << City::science << "科技点数" << endl;
    }
    return 0;
}

*/