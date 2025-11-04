#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring> // 包含字符串处理
#define LAWN_LENGTH 9
#define SUNLIGHT_TIME 3
#define TARGET_DAMAGE 1000 
#define MAX_PLANTS 100 // 定义最大植物数量
using namespace std;

time_t current = 0;  // 模拟记录时间，单位s

/*************将基类的声明拷贝至此**************/
class PlantBase {
private:
    int hp;			// 植物的生命值
    char* name;		// 植物的名字（长度不超过20）

protected:
    int cost;		// 种植花费的阳光
    time_t plant_time;	// 植物被种下的时间

public:
    PlantBase(int hp, int cost);
    ~PlantBase();
    bool hurt(int damage);
    char* get_name();
    void set_name(const char* aname);
    time_t get_time() {
        return plant_time;
    }
    void set_time(time_t atime) {
        plant_time = atime;
    }
};

/********************************************/

/*************在这里给出基类的实现**************/
PlantBase::PlantBase(int hp, int cost) : hp(hp), cost(cost), plant_time(0) {
    name = new char[21];
    name[0] = '\0';
}
PlantBase::~PlantBase() {
    delete[] name; // 删除 name
}
char* PlantBase::get_name() {
    return name;
}
void PlantBase::set_name(const char* aname) {
    delete[] name; //释放内存
    name = new char[strlen(aname) + 1];
    strcpy(name, aname);
}
bool PlantBase::hurt(int damage) {
    hp -= damage;
    return hp <= 0; //返回是否死亡
}
/********************************************/

/**********在这里给出派生类的声明和实现***********/
class PeaShooter : virtual public PlantBase {
private:
    static const int shoot_damage = 10;
    static const int shoot_interval = 2;

public:
    PeaShooter() : PlantBase(60, 125) {}

    int get_damage() const {
        return shoot_damage;
    }

    int get_interval() const {
        return shoot_interval;
    }

};
class SunFlower : virtual public PlantBase {
private:
    static const int sunlight_produce = 25;
    static const int product_interval = 5;
public:
    SunFlower() :PlantBase(60, 125) {}
    int get_produce()const {
        return sunlight_produce;
    }
    int get_interval()const {
        return product_interval;
    }
};
class SunnyPea : public PeaShooter, public SunFlower {
private:

public:
    SunnyPea() : PlantBase(60, 125), PeaShooter(), SunFlower() {}
};
/********************************************/

int main() {
    /* 变量声明 */
    int plant_num = 0; // 记录植物总数
    SunnyPea* lawn[LAWN_LENGTH] = {};
    time_t records[MAX_PLANTS] = {}; // 使用数组记录植物种植时间
    int record_count = 0; // 记录种植时间的数量

    // 输入数据
    int sunlight = 0;  // 初始阳光
    int damage = 0;    // 当前造成的伤害
    time_t n = 0;      // 僵尸发起攻击的时间
    cin >> sunlight >> n;

    while (true) {
        // 1. 环境：每3秒掉落25阳光
        if (current % SUNLIGHT_TIME == 0 && current > 0) {
            sunlight += 25;
        }
        /* 2. 植物：发动攻击 */
        for (int i = 0; i < LAWN_LENGTH; i++) {
            if (lawn[i] != nullptr && (current - lawn[i]->get_time()) % lawn[i]->PeaShooter::get_interval() == 0) {
                damage += lawn[i]->get_damage();
            }
        }
        for (int i = 0; i < LAWN_LENGTH; i++) {
            if (lawn[i] != nullptr && (current - lawn[i]->get_time()) % lawn[i]->SunFlower::get_interval() == 0) {
                sunlight += lawn[i]->get_produce();
            }
        }
        /* 3. 玩家：放植物（一次只能放一株）*/
        for (int i = 0; i < LAWN_LENGTH; i++) {
            if (sunlight >= 120 && lawn[i] == nullptr) {
                char aname[21]; // 临时数组来存储植物名字
                cin >> aname; // 输入名字
                lawn[i] = new SunnyPea();
                lawn[i]->set_name(aname); // 设置植物名字
                lawn[i]->set_time(current); // 记录植物的种植时间

                if (record_count < MAX_PLANTS) {
                    records[record_count++] = current; // 记录种植时间
                }
                else {
                    cout << "记录数组已满，无法记录更多种植时间" << endl;
                }

                plant_num++;
                sunlight -= 125; // 消耗阳光

                break;
            }
        }
        /* 4. 僵尸：从第n秒开始，每一秒最右侧的植物会收到10*(current - n)的伤害 */
        if (current >= n) {
            for (int i = LAWN_LENGTH - 1; i >= 0; i--) {
                if (lawn[i] != nullptr) {
                    int bad_damage = static_cast<int>(10 * (current - n));
                    if (lawn[i]->hurt(bad_damage)) {

                        delete lawn[i]; // 删除植物
                        lawn[i] = nullptr; // 设置为空
                        plant_num--;
                    }
                    break; // 只处理最右侧的植物
                }
            }
        }
        // 5. 游戏胜利/失败判断
        if (damage >= TARGET_DAMAGE) {
            cout << "游戏胜利" << endl;
            break;
        }
        else if (current >= n && plant_num == 0) {
            cout << "游戏失败" << endl;
            break;
        }
        else if (current >= 100) { // 如果第100秒过去仍未积累足够阳光，则判负
            cout << "游戏失败" << endl;
            break;
        }

        current++;

    }

    cout << endl << "时刻数：" << current << " 阳光数：" << sunlight << " 植物数：" << plant_num << endl;
    cout << endl << "每一株植物种下的时刻：" << endl;
    for (int i = 0; i < record_count; i++) {
        cout << records[i] << " ";
    }
    cout << endl;

    // 输出存活植物的名字和类型
    cout << endl << "幸存植物的名字：" << endl;
    for (int i = 0; i < LAWN_LENGTH; i++) {
        if (lawn[i] != nullptr) {
            cout << lawn[i]->get_name() << endl;
        }
    }
    //内存回收
    for (int i = 0; i < LAWN_LENGTH; i++) {
        delete lawn[i];
    }
    return 0;
}