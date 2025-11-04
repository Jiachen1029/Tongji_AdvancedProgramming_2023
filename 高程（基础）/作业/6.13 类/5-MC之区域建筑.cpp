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
    static double science;
    static bool campus,library,university,lab;
};

// 静态成员变量初始化
string City::name = "";
int City::population = 0;
int City::farm = 0;
int City::food = 0;
double City::science = 0;
bool City::campus = false;
bool City::library = false;
bool City::university = false;
bool City::lab = false;

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
        else if (input == "build")
        {
            
            string buildwhat;
            cin>> buildwhat;
            if (buildwhat == "campus")
            {
                City::campus = true;
            }
            else if (buildwhat == "library" && City::campus)
            {
				City::library = true;
			}
            else if (buildwhat == "university"&&City::library)
            {
				City::university = true;
			}
            else if (buildwhat == "lab"&&City::university)
            {
				City::lab = true;
			}
			else
				cout << "输入错误，请重新输入" << endl;
        }
        else
            cout << "输入错误，请重新输入" << endl;

        // 在每次输入后立即更新食物数量
        if (City::population <= 0)
            City::population = 0;
        if (City::farm <= 0)
            City::farm = 0;
        City::food = City::farm * 4 - City::population * 2;
        
        if (City::campus&&!City::library&&!City::university&&!City::lab)
            City::science = 4;
        else if (City::campus&&City::library&&!City::university&&!City::lab)
            City::science = 8 + 0.5 * City::population;
        else if (City::campus&&City::library&&City::university&&!City::lab)
            City::science = 16 + 1.5 * City::population;
        else if (City::campus && City::library && City::university && City::lab)
        {
            if(City::population<=10)
                City::science = 32 + 2.5 * City::population;
            else
                City::science = 32 + 2.5 * 10 + 4.5 * (City::population - 10);
        }
        //建造顺序必须为书院区域 → 图书馆 → 大学 → 研究实验室,没有修建前面的就不能修建后面的，相应的改成false



        // 显示当前状态
        cout << City::name << " " << City::population << "人" << " " << City::food << "粮";
        cout << " " << City::science << "科技点数" << endl;
    }
    return 0;
}
