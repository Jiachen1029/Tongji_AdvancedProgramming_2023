#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#define LAWN_LENGTH 9
#define SUNLIGHT_TIME 3
#define TARGET_DAMAGE 500
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
    virtual ~PlantBase(); // 虚析构函数
    bool hurt(int damage);
    char* get_name() const; // 返回名字
    void set_name(const char* aname); // 更新植物名字
};
/********************************************/

/*************在这里给出基类的实现**************/
PlantBase::PlantBase(int hp, int cost) : hp(hp), cost(cost), plant_time(0) {
    name = new char[21]; // 为植物名字分配空间
    name[0] = '\0'; // 初始化为空字符串
}

PlantBase::~PlantBase() {
    delete[] name; // 删除 name
}

bool PlantBase::hurt(int damage) {
    hp -= damage;
    return hp <= 0; // 返回是否死亡
}

char* PlantBase::get_name() const {
    return name;
}

void PlantBase::set_name(const char* aname) {
    strncpy(name, aname, 20); // 复制字符串，保证不超过20个字符
    name[20] = '\0'; // 确保字符串终止符
}
/********************************************/

/**********在这里给出派生类的声明和实现***********/
class PeaShooter : public PlantBase {
private:
    static const int shoot_damage = 10;
    static const int interval = 2;

public:
    PeaShooter() : PlantBase(60, 100) {}
    int GetInterval() {
        return interval;
    }
    void SetPlantTime(time_t time) {
        plant_time = time;
    }
    time_t GetPlantTime() const {
        return plant_time;
    }
    int GetDamage() const {
        return shoot_damage;
    }
};
/********************************************/

int main() {
    /* 变量声明 */
    int plant_num = 0; // 记录植物总数
    PeaShooter* lawn[LAWN_LENGTH] = {};
    time_t records[LAWN_LENGTH] = {}; // 使用数组记录植物种植时间
    int record_count = 0; // 记录种植时间的数量

    // 输入数据
    int sunlight = 0;
    int damage = 0;
    time_t n = 0;
    cin >> sunlight >> n;

    while (true) {
        // 1. 环境：每3/6/9/...s掉落一个25的阳光
        if (current % SUNLIGHT_TIME == 0 && current > 0) {
            sunlight += 25;
        }

        /* 2. 植物：发动攻击 */
        for (int i = 0; i < LAWN_LENGTH; i++) {
            if (lawn[i] != nullptr && (current - lawn[i]->GetPlantTime()) % lawn[i]->GetInterval() == 0) {
                damage += lawn[i]->GetDamage();
            }
        }

        /* 3. 玩家：放植物（一次只能放一株）*/
        for (int i = 0; i < LAWN_LENGTH; i++) {
            if (sunlight >= 100 && lawn[i] == nullptr) {
                lawn[i] = new PeaShooter();
                char aname[21]; // 临时数组来存储植物名字
                cin >> aname; // 输入名字
                lawn[i]->set_name(aname); // 设置植物名字
                lawn[i]->SetPlantTime(current); // 记录植物的种植时间
                records[record_count++] = current; // 记录种植时间
                plant_num++;
                sunlight -= 100; // 消耗阳光
                break;
            }
        }

        /* 4. 僵尸：从第n秒开始，每一秒最右侧的植物会收到10*(current-n)的伤害 */
        if (current >= n) {
            for (int i = LAWN_LENGTH - 1; i >= 0; i--) {
                if (lawn[i] != nullptr) {
                    int bad_damage = static_cast<int>(10 * (current - n));
                    if (lawn[i]->hurt(bad_damage)) {
                        delete lawn[i];
                        lawn[i] = nullptr;
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
        else if (current >= n && plant_num == 0) { // 提前判定失败
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

    if (record_count > 0) {
        cout << endl << "每一株植物种下的时刻：" << endl;
        for (int i = 0; i < record_count; i++) {
            cout << records[i] << (i < record_count - 1 ? " " : "\n");
        }
    }

    bool has_surviving_plants = false;
    for (int i = 0; i < LAWN_LENGTH; i++) {
        if (lawn[i] != nullptr) {
            has_surviving_plants = true;
            break;
        }
    }

    if (has_surviving_plants) {
        cout << endl << "幸存植物的名字：" << endl;
        for (int i = 0; i < LAWN_LENGTH; i++) {
            if (lawn[i] != nullptr) {
                cout << lawn[i]->get_name() << endl;
            }
        }
    }

    // 内存回收
    for (int i = 0; i < LAWN_LENGTH; i++) {
        delete lawn[i]; // 删除每一个植物对象
    }

    return 0;
}