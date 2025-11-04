#include<iostream>
#include<string>
using namespace std;

class City {
public:
    string name;
    int population;
    int farm;
    int food;
    double science;
    bool campus, library, university, lab;
    char policyCard;

    City() : population(0), farm(0), food(0), science(0), campus(false), library(false), university(false), lab(false), policyCard(' ') {}

    void updateFood() {
        food = farm * 4 - population * 2;
    }

    void updateScience() {
        science = 0;
        if (campus) science += 4;
        if (library) science += 4 + 0.5 * population;
        if (university) science += 8 + 1 * population;
        if (lab) {
            if (population <= 10) science += 16 + 1 * population;
            else science += 16 + 10 + 3 * (population - 10);
        }

        int buildings = (library ? 1 : 0) + (university ? 1 : 0) + (lab ? 1 : 0);
        switch (policyCard) {
        case 'A':
            science += 10 * buildings;
            break;
        case 'B':
            science += 2 * population;
            break;
        case 'C':
            if (food > 0) science += food;
            break;
        }
    }

    void displayStatus() {
        cout << name << " " << population << "人 " << food << "粮 " << science << "科技点数" << endl;
    }
};

int main() {
    City city;
    cout << "请输入城市名称，初始人口数量，初始农田数量：" << endl;
    cin >> city.name >> city.population >> city.farm;

    string command;
    while (true) {
        cin >> command;
        if (command == "quit") break;
        else if (command == "farm") {
            int delta;
            cin >> delta;
            city.farm = max(0, city.farm + delta);
        }
        else if (command == "population") {
            int delta;
            cin >> delta;
            city.population = max(0, city.population + delta);
        }
        else if (command == "build") {
            string building;
            cin >> building;
            if (building == "campus" && !city.campus) city.campus = true;
            else if (building == "library" && city.campus && !city.library) city.library = true;
            else if (building == "university" && city.library && !city.university) city.university = true;
            else if (building == "lab" && city.university && !city.lab) city.lab = true;
        }
        else if (command == "set") {
            cin >> city.policyCard;
        }

        city.updateFood();
        city.updateScience();
        city.displayStatus();
    }
    return 0;
}

/*
#include<iostream>
#include<string>
using namespace std;

class City
{
public:
    static string name;
    static int population;
    static int farm;
    static int food;
    static double science;
    static bool campus, library, university, lab;
    static char policyCard;
};

string City::name = "";
int City::population = 0;
int City::farm = 0;
int City::food = 0;
double City::science = 0;
bool City::campus = false;
bool City::library = false;
bool City::university = false;
bool City::lab = false;
char City::policyCard = ' ';

int main()
{
    cout << "请输入城市名称，初始人口数量，初始农田数量：" << endl;
    cin >> City::name >> City::population >> City::farm;

    string input;
    while (true)
    {
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
        else if (input == "build")
        {
            string buildwhat;
            cin >> buildwhat;
            // 确保按照正确的顺序建造
            if (buildwhat == "campus" && !City::campus)
            {
                City::campus = true;
            }
            else if (buildwhat == "library" && City::campus && !City::library)
            {
                City::library = true;
            }
            else if (buildwhat == "university" && City::library && !City::university)
            {
                City::university = true;
            }
            else if (buildwhat == "lab" && City::university && !City::lab)
            {
                City::lab = true;
            }
        }
        else if (input == "set")
        {
            cin >> City::policyCard;
        }

        // 更新食物数量
        City::food = City::farm * 4 - City::population * 2;

        // 基础科技点数计算
        City::science = 0;
        if (City::campus) City::science += 4;
        if (City::library) City::science += 4 + 0.5 * City::population;
        if (City::university) City::science += 8 + 1 * City::population;
        if (City::lab)
        {
            if (City::population <= 10)
                City::science += 16 + 1 * City::population;
            else
                City::science += 16 + 10 + 3 * (City::population - 10);
        }
        // 根据政策卡调整科技点数
        int buildings =  (City::library ? 1 : 0) + (City::university ? 1 : 0) + (City::lab ? 1 : 0);
        switch (City::policyCard)
        {
        case 'A':
            City::science += 10 * buildings;
            break;
        case 'B':
            City::science += 2 * City::population;
            break;
        case 'C':
            if (City::food > 0)
                City::science += City::food;
            break;
        }

        // 显示当前状态
        cout << City::name << " " << City::population << "人 " << City::food << "粮";
        cout << " " << City::science << "科技点数" << endl;
    }
    return 0;
}
*/