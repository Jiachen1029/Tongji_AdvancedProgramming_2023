#include<iostream>
#include<string>
using namespace std;

// 结构体
struct Farm {
    int hill; // 丘陵农田
    int plain; // 平原农田
    int floodplain; // 泛滥农田
};

struct Plantation {
    int fabric; // 织品种植园
    int food; // 食品种植园
};

struct Mine {
    int material; // 材料矿山
    int precious; // 宝石矿山
};

struct City {
    string name;
    int population;
    Farm farm;
    int food;
    Plantation plantation;
    Mine mine;
    int gold; // 金币
    int productivity; // 生产力
    bool factory; // 工厂
    bool market; // 市场
} city;

int main() {
    // 初始化
    city.food = 0;
    city.gold = 0;
    city.productivity = 0;
    city.population = 0;
    city.farm = { 0, 0, 0 };
    city.plantation = { 0, 0 };
    city.mine = { 0, 0 };
    city.factory = false;
    city.market = false;
    cout << "请输入城市名称，初始人口数量" << endl;
    cin >> city.name >> city.population;
    string input;
    while (true) {
        cout << "请输入操作（quit退出）：" << endl;
        cin >> input;

        if (input == "quit")
            break;
        else if (input == "farm") {
            string farmType;
            int delta;
            cin >> farmType >> delta;
            if (farmType == "hill")
                city.farm.hill += delta;
            else if (farmType == "plain")
                city.farm.plain += delta;
            else if (farmType == "floodplain")
                city.farm.floodplain += delta;
        }
        else if (input == "population") {
            int deltapopulation;
            cin >> deltapopulation;
            city.population += deltapopulation;
        }
        else if (input == "plantation") {
            string plantationType;
            int delta;
            cin >> plantationType >> delta;
            if (plantationType == "fabric")
                city.plantation.fabric += delta;
            else if (plantationType == "food")
                city.plantation.food += delta;
        }
        else if (input == "mine") {
            string mineType;
            int delta;
            cin >> mineType >> delta;
            if (mineType == "material")
                city.mine.material += delta;
            else if (mineType == "precious")
                city.mine.precious += delta;
        }
        else if (input == "build") {
            string building;
            cin >> building;
            if (building == "factory") {
                city.factory = true;
            }
            if (building == "market") {
                city.market = true;
            }
        }
        // 确保人口和资源数量不为负
        if (city.population < 0) city.population = 0;
        if(city.farm.hill < 0) city.farm.hill = 0;
        if(city.farm.plain < 0) city.farm.plain = 0;
        if(city.farm.floodplain < 0) city.farm.floodplain = 0;
        if(city.plantation.fabric < 0) city.plantation.fabric = 0;
        if(city.plantation.food < 0) city.plantation.food = 0;
        if(city.mine.material < 0) city.mine.material = 0;
        if(city.mine.precious < 0) city.mine.precious = 0;

        // 更新产出食物数量、金币和生产力
        city.food = city.farm.hill * 2 + city.farm.plain * 3 + city.farm.floodplain * 4 + city.plantation.food * 4 - city.population * 2;
        city.gold = city.plantation.fabric * 4 + city.mine.material * 2 + city.mine.precious * 4;
        city.productivity = city.mine.material * 4 + city.mine.precious * 2 + city.population;
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