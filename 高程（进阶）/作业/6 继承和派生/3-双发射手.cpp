#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring> 
#define LAWN_LENGTH 9
#define SUNLIGHT_TIME 3
#define TARGET_DAMAGE 3000
#define MAX_PLANTS 100 
using namespace std;

time_t current = 0;  // 模拟记录时间，单位s

/*************将基类的声明拷贝至此**************/
class PlantBase {
private:
    int hp;            // 植物的生命值
    char* name;        // 植物的名字（长度不超过20）

protected:
    int cost;         // 种植花费的阳光
    time_t plant_time; // 植物被种下的时间

public:
    PlantBase(int hp, int cost);
    PlantBase(PlantBase& base); // 复制构造函数
    virtual ~PlantBase();

    bool hurt(int damage);
    char* get_name();
    void set_name(const char* aname);
    int get_hp() const;
    time_t get_plant_time() const { return plant_time; }
    void set_plant_time(time_t time) { plant_time = time; }
};

/********************************************/

/*************在这里给出基类的实现**************/
PlantBase::PlantBase(int hp, int cost) : hp(hp), cost(cost), plant_time(0) {
    name = new char[21]; //为植物名字分配空间
    name[0] = '\0'; 
}

PlantBase::PlantBase(PlantBase& base) : hp(base.hp), cost(base.cost), plant_time(base.plant_time) {
    name = new char[strlen(base.name) + 1];
    strcpy(name, base.name);
}

PlantBase::~PlantBase() {
    delete[] name;
}

bool PlantBase::hurt(int damage) {
    hp -= damage;
    return hp <= 0;
}

char* PlantBase::get_name() {
    return name;
}

void PlantBase::set_name(const char* aname) {
    delete[] name; //释放之前内存
    name = new char[strlen(aname) + 1]; //新内存
    strcpy(name, aname); //复制字符串
}

int PlantBase::get_hp() const {
    return hp;
}
/********************************************/

/**********在这里给出派生类的声明和实现***********/
class Repeater : public PlantBase {
private:
    static const int shoot_damage = 20;
    static const int interval = 2;

public:
    Repeater() : PlantBase(60, 150) {}

    int get_damage() const {
        return shoot_damage;
    }

    int get_interval() const {
        return interval;
    }
};

class GatlingPea : public PlantBase {
private:
    static const int shoot_damage = 40;
    static const int interval = 2;

public:
    GatlingPea(Repeater* repeater) : PlantBase(60, 150) {
        // 使用Repeater的名字
        strcpy(get_name(), repeater->get_name());
    }

    int get_damage() const {
        return shoot_damage;
    }

    int get_interval() const {
        return interval;
    }
};

/********************************************/

int main() {
    /* 变量声明 */
    int plant_num = 0; // 记录植物总数
    Repeater* lawn1[LAWN_LENGTH] = {};
    GatlingPea* lawn2[LAWN_LENGTH] = {};
    time_t records[MAX_PLANTS] = {}; // 使用数组记录植物种植时间
    int record_index = 0; // 记录数组的当前索引

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
            if (lawn1[i] != nullptr && (current - lawn1[i]->get_plant_time()) % lawn1[i]->get_interval() == 0) {
                damage += lawn1[i]->get_damage();
            }
        }
        for (int i = 0; i < LAWN_LENGTH; i++) {
            if (lawn2[i] != nullptr && (current - lawn2[i]->get_plant_time()) % lawn2[i]->get_interval() == 0) {
                damage += lawn2[i]->get_damage();
            }
        }
        /* 3. 玩家：放植物（一次只能放一株）*/
        int judge = 2;
        for (int i = 0; i < LAWN_LENGTH; i++) {
            if (lawn1[i] == nullptr && lawn2[i] == nullptr) {
                judge = 1;
                break;
            }
        }
        if (judge == 1) {
            for (int i = 0; i < LAWN_LENGTH; i++) {
                if (sunlight >= 150 && lawn1[i] == nullptr && lawn2[i] == nullptr) {
                    char aname[21]; // 临时数组来存储植物名字
                    cin >> aname; // 输入名字
                    lawn1[i] = new Repeater();
                    lawn1[i]->set_name(aname); // 设置植物名字
                    lawn1[i]->set_plant_time(current); // 记录植物的种植时间
                    records[record_index++] = current; // 记录种植时间

                    plant_num++;
                    sunlight -= 150; // 消耗阳光

                    break;
                }
            }
        }
        if (judge == 2) {
            for (int i = 0; i < LAWN_LENGTH; i++) {
                if (lawn2[i] == nullptr && sunlight >= 150 && lawn1[i] != nullptr) {
                    GatlingPea* gat = new GatlingPea(lawn1[i]);
                    lawn2[i] = gat;
                    lawn2[i]->set_plant_time(current); // 记录植物的种植时间
                    records[record_index++] = current; // 记录种植时间

                    sunlight -= 150;

                    delete lawn1[i];
                    lawn1[i] = nullptr;
                    break;
                }
            }
        }
        /* 4. 僵尸：从第n秒开始，每一秒最右侧的植物会收到10*(current - n)的伤害 */
        if (current >= n) {
            for (int i = LAWN_LENGTH - 1; i >= 0; i--) {
                if (lawn2[i] != nullptr) {
                    int bad_damage = static_cast<int>(10 * (current - n));
                    if (lawn2[i]->hurt(bad_damage)) {
                        delete lawn2[i]; // 删除植物
                        lawn2[i] = nullptr; // 设置为空
                        plant_num--;
                    }
                    break; // 只处理最右侧的植物
                }
                else if (lawn1[i] != nullptr) {
                    int bad_damage = static_cast<int>(10 * (current - n));
                    if (lawn1[i]->hurt(bad_damage)) {
                        delete lawn1[i]; // 删除植物
                        lawn1[i] = nullptr; // 设置为空
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
    for (int i = 0; i < record_index; i++) {
        cout << records[i] << " ";
    }
    cout << endl;

    // 输出存活植物的名字和类型
    cout << endl << "幸存植物的名字：" << endl;
    for (int i = 0; i < LAWN_LENGTH; i++) {
        if (lawn1[i] != nullptr && lawn2[i] == nullptr) {
            cout << "Repeater:" << lawn1[i]->get_name() << endl;
        }
        else if (lawn1[i] == nullptr && lawn2[i] != nullptr) {
            cout << "Gatling:" << lawn2[i]->get_name() << endl;
        }
    }
    // 内存回收
    for (int i = 0; i < LAWN_LENGTH; i++) {
        delete lawn1[i];
        delete lawn2[i];
    }
    return 0;
}