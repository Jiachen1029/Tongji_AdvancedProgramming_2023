#include <iostream>
#define LAWN_LENGTH 9
#define SUNLIGHT_TIME 3
#define TARGET_SUNLIGHT 500
using namespace std;

time_t current = 0;  // 模拟记录时间，单位s

class PlantBase {
private:
	int hp;				// 植物的生命值

protected:
	time_t plant_time;	// 植物被种下的时间
	time_t interval;	// 植物攻击或生产的时间间隔

public:
	PlantBase(int hp, time_t interval);
	bool hurt(int damage);
};

/***********在这里给出PlantBase的实现***********/
PlantBase::PlantBase(int hp, time_t interval) : hp(hp), interval(interval)
{
	plant_time = current;
}
bool PlantBase::hurt(int damage) {
	hp -= damage;
	return hp > 0;
}
/********************************************/


/********在这里给出SunFlower的声明和实现*********/
class SunFlower : public PlantBase
{
public:
	SunFlower() : PlantBase(60, 5) {}  //向日葵生命值 60，需要消耗50阳光，每5s生产25点阳光
	bool produceSunlight(int& sunlight)
	{
		if ((current - plant_time) % interval == 0) 
		{
			sunlight += 25;
			return true;
		}
		return false;
	}
};
/********************************************/

int main()
{
	/* 变量声明 */
	SunFlower* lawn[LAWN_LENGTH] = {};
	int plant_num = 0; // 记录植物总数

	// 输入数据
	int sunlight;
	time_t n;
	cin >> sunlight >> n;

	while (true) {
		// 1. 环境：每3/6/9/...s掉落一个25的阳光
		if (current % SUNLIGHT_TIME == 0 && current > 0) {
			sunlight += 25;
		}

		/* 2. 植物：产阳光 */
		for (int i = 0; i < LAWN_LENGTH; ++i)
		{
			if (lawn[i]) {
				lawn[i]->produceSunlight(sunlight);
			}
		}

		/* 3. 玩家：放植物（一次只能放一株）*/
		if (sunlight >= 50 && plant_num < LAWN_LENGTH)
		{
			for (int i = 0; i < LAWN_LENGTH; ++i)
			{
				if (!lawn[i]) 
				{
					lawn[i] = new SunFlower();
					sunlight -= 50;
					plant_num++;
					break;
				}
			}
		}

		/* 4. 僵尸：从第n秒开始，每一秒最右侧的向日葵会收到10*(current-n)的伤害 */
		if (current >= n) {
			for (int i = LAWN_LENGTH - 1; i >= 0; --i) 
			{
				if (lawn[i]) {
					if (!lawn[i]->hurt(10 * int((current - n))))
					{
						delete lawn[i];
						lawn[i] = nullptr;
						plant_num--;
					}
					break;
				}
			}
		}
		cout << "时刻数：" << current << " 阳光数：" << sunlight << " 植物数：" << plant_num << endl;

		// 5. 游戏胜利/失败判断
		if (sunlight >= TARGET_SUNLIGHT) {
			cout << "游戏胜利" << endl;
			break;
		}
		else if (current >= n && plant_num == 0) {  // 提前判定失败
			cout << "游戏失败" << endl;
			break;
		}
		else if (current >= 100) {  // 如果第100秒过去仍未积累足够阳光，则判负
			cout << "游戏失败" << endl;
			break;
		}

		current++;
	}

	// 内存回收
	for (int i = 0; i < LAWN_LENGTH; ++i) {
		if (lawn[i])
			delete lawn[i];
	}

	return 0;
}