#include<iostream>
#include<random>
#include <fstream>
#include <cmath>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <graphics.h>
#include <conio.h>
#include <vector>
#include <string>
#include <map>
using namespace std;
const double M_PI = 3.14;

/*————————————————————*/
/*————————逻辑处理————————*/
/*————————————————————*/
// 定义时间间隔：5ms
const int INTERVAL_MS = 5;
// 定义最大燃油量
const int MAX_FUEL = 20000;
// 定义额定转速
const int RATED_RPM = 40000;
// 环境温度（初始温度）
const double T0 = 20.0;

// 定义发动机各种阶段（初始阶段，启动阶段，稳定阶段，停车阶段）
bool isInit = true;
bool isStarted_1 = false; // 启动前两秒
bool isStarted_2 = false; // 启动对数函数
bool isStable = false;
bool isStopping = false;

// 结构体用于存储发动机数据
struct EngineData
{
    double N1[2]; // 左发动机转速（两个传感器）
    double N2[2]; // 右发动机转速（两个传感器）
    double T1[2]; // 左发动机排气温度（两个传感器）
    double T2[2]; // 右发动机排气温度（两个传感器）
    double C;     // 燃油余量
    double V;     // 燃油流速

    // 基准值，允许在稳定状态下调整
    double baseN1;
    double baseN2;
    double baseT1;
    double baseT2;
    double baseV;

    EngineData() :
        baseN1(0.95 * RATED_RPM),
        baseN2(0.95 * RATED_RPM),
        baseT1(735),
        baseT2(735),
        baseV(43)
    {
    }
};

// 生成随机噪声，用于模拟数据的随机波动
double generateRandomNoise(double range)
{
    return ((rand() / (double)RAND_MAX) * 2 - 1) * range;
}

// 增大推力
void increaseThrust(EngineData& data)
{
    data.V += 1; // 燃油流速增加1单位每秒

    if (isStable)
    {
        // 基准值提升3%到5%
        double incrementFactor = 1.03 + (rand() % 3) * 0.01;
        data.baseN1 *= incrementFactor;
        data.baseN2 *= incrementFactor;
        data.baseT1 *= incrementFactor;
        data.baseT2 *= incrementFactor;
        data.baseV += 1; // 根据需求调整
    }
    for (int i = 0; i < 2; ++i)
    {
        data.N1[i] = max(0.0, data.N1[i] + data.N1[i] * (0.03 + (rand() % 3) * 0.01)); // 转速增加3%到5%
        data.N2[i] = max(0.0, data.N2[i] + data.N2[i] * (0.03 + (rand() % 3) * 0.01));
        data.T1[i] = max(T0, data.T1[i] + data.T1[i] * (0.03 + (rand() % 3) * 0.01)); // 温度增加3%到5%
        data.T2[i] = max(T0, data.T2[i] + data.T2[i] * (0.03 + (rand() % 3) * 0.01));
    }
}
// 减小推力
void decreaseThrust(EngineData& data)
{
    if (isStable)
    {
        // 基准值降低3%到5%
        double decrementFactor = 1.00 - (0.03 + (rand() % 3) * 0.01);
        data.baseN1 *= decrementFactor;
        data.baseN2 *= decrementFactor;
        data.baseT1 *= decrementFactor;
        data.baseT2 *= decrementFactor;
        data.V = max(0.0, data.V - 1); // 燃油流速减少1单位每秒，不能小于0
    }
    for (int i = 0; i < 2; ++i)
    {
        data.N1[i] = max(0.0, data.N1[i] - data.N1[i] * (0.03 + (rand() % 3) * 0.01)); // 转速减少3%到5%
        data.N2[i] = max(0.0, data.N2[i] - data.N2[i] * (0.03 + (rand() % 3) * 0.01));
        data.T1[i] = max(T0, data.T1[i] - data.T1[i] * (0.03 + (rand() % 3) * 0.01)); // 温度减少3%到5%
        data.T2[i] = max(T0, data.T2[i] - data.T2[i] * (0.03 + (rand() % 3) * 0.01));
    }
}

//定义错误类型
enum FaultType
{
    N1_1Fail, N1_2Fail, N2_1Fail, N2_2Fail, T1_1Fail, T1_2Fail, T2_1Fail, T2_2Fail,//第一种故障（单个）
    N1Fail, N2Fail, T1Fail, T2Fail,//第一种故障（单发）
    N1andN2Fail, T1andT2Fail,//第一种故障（双发）
    LowFuel, FuelSFail, OverFF,//第二种故障（燃油不足/流速）
    OverSpd1, OverSpd2,//第三种故障（转速过高）
    OverTemp1, OverTemp2, OverTemp3, OverTemp4//第四种故障（温度过高）
};


//异常情况检测与处理
void checkData(EngineData& data, bool& isInit, bool& isStarted_1, bool& isStarted_2, bool& isStable, bool& isStopping,
    vector<FaultType>& faults, std::map<FaultType, double>& faultTimeMap, double currentTime, ofstream& logFile, std::map<FaultType, double>& faultLogTimeMap)
{
    /*——————传感器异常——————*/
    bool sensorN1_0 = true, sensorN1_1 = true, sensorN2_0 = true, sensorN2_1 = true; //假设都是正常的
    bool sensorT1_0 = true, sensorT1_1 = true, sensorT2_0 = true, sensorT2_1 = true; //假设都是正常的

    if (data.N1[0] > 1.25 * RATED_RPM)
        sensorN1_1 = false;
    if (data.N1[1] > 1.25 * RATED_RPM)
        sensorN1_1 = false;
    if (data.N2[0] > 1.25 * RATED_RPM)
        sensorN2_0 = false;
    if (data.N2[1] > 1.25 * RATED_RPM)
        sensorN2_1 = false;
    if (data.T1[0] > 1200 || data.T1[0] < -5)
        sensorT1_0 = false;
    if (data.T1[1] > 1200 || data.T1[1] < -5)
        sensorT1_1 = false;
    if (data.T2[0] > 1200 || data.T2[0] < -5)
        sensorT2_0 = false;
    if (data.T2[1] > 1200 || data.T2[1] < -5)
        sensorT2_1 = false;

    auto logFault = [&](FaultType fault) {
        if (currentTime - faultLogTimeMap[fault] >= 5.0) {
            faults.push_back(fault);
            faultTimeMap[fault] = currentTime;
            logFile << currentTime << "s: " << fault << endl;
            faultLogTimeMap[fault] = currentTime;
        }
        };

    // 单个转速传感器故障（无效值）
    // 单发转速传感器故障（无效值）
    // 双发转速传感器故障（无效值）
    if (!sensorN1_0 && !sensorN1_1 && !sensorN2_0 && !sensorN2_1)
    {
        // 红色警告
        isStopping = true;
        isStarted_1 = false;
        isStarted_2 = false;
        isStable = false;
        logFault(N1andN2Fail);
    }
    else if (!sensorN1_0 && !sensorN1_1)
    {
        // 琥珀色警告
        logFault(N1Fail);
    }
    else if (!sensorN2_0 && !sensorN2_1)
    {
        // 琥珀色警告
        logFault(N2Fail);
    }
    else if (!sensorN1_0)
    {
        //白色警告
        logFault(N1_1Fail);
    }
    else if (!sensorN1_1)
    {
        //白色警告
        logFault(N1_2Fail);
    }
    else if (!sensorN2_0)
    {
        //白色警告
        logFault(N2_1Fail);
    }
    else if (!sensorN2_1)
    {
        //白色警告
        logFault(N2_2Fail);
    }
    // 单个EGT传感器故障（无效值）
    // 单发EGT传感器故障（无效值）
    // 双发EGT传感器故障（无效值）
    if (!sensorT1_0 && !sensorT1_1 && !sensorT2_0 && !sensorT2_1)
    {
        // 红色警告
        isStopping = true;
        isStarted_1 = false;
        isStarted_2 = false;
        isStable = false;
        logFault(T1andT2Fail);
    }
    else if (!sensorT1_0 && !sensorT1_1)
    {
        // 琥珀色警告
        logFault(T1Fail);
    }
    else if (!sensorT2_0 && !sensorT2_1)
    {
        // 琥珀色警告
        logFault(T2Fail);
    }
    else if (!sensorT1_0)
    {
        //白色警告
        logFault(T1_1Fail);
    }
    else if (!sensorT1_1)
    {
        //白色警告
        logFault(T1_2Fail);
    }
    else if (!sensorT2_0)
    {
        //白色警告
        logFault(T2_1Fail);
    }
    else if (!sensorT2_1)
    {
        //白色警告
        logFault(T2_2Fail);
    }

    /*——————燃油异常——————*/
    if (data.C <= 1000 && data.C > 0)
    {
        // 燃油余量低告警
        // 琥珀色警告
        logFault(LowFuel);
    }
    else if (data.C <= 0)
    {
        // 传感器故障告警
        // 红色警告
        isStopping = true;
        isStarted_1 = false;
        isStarted_2 = false;
        isStable = false;
        data.C = 0;
        logFault(FuelSFail);
    }
    if (data.V > 50)
    {
        // 燃油指示告警
        // 琥珀色警告
        logFault(OverFF);
    }
    /*——————转速异常（平均值代替）—————*/
    if (((data.N1[0] + data.N1[0] + data.N2[0] + data.N1[1]) / 4) > 1.05 * RATED_RPM && ((data.N1[0] + data.N1[0] + data.N2[0] + data.N1[1]) / 4) <= 1.20 * RATED_RPM)
    {
        //琥珀色警告
        logFault(OverSpd1);
    }
    else if (((data.N1[0] + data.N1[0] + data.N2[0] + data.N1[1]) / 4) > 1.20 * RATED_RPM)
    {
        //红色警告
        isStopping = true;
        isStarted_1 = false;
        isStarted_2 = false;
        isStable = false;
        logFault(OverSpd2);
    }

    /*——————温度异常（平均值代替）——————*/
    //启动过程中
    if (isStarted_1 || isStarted_2)
    {
        if (((data.T1[0] + data.T1[1] + data.T2[0] + data.T2[1]) / 4) > 1000)
        {
            //红色警告
            isStopping = true;
            isStarted_1 = false;
            isStarted_2 = false;
            isStable = false;
            logFault(OverTemp2);
        }
        else if (((data.T1[0] + data.T1[1] + data.T2[0] + data.T2[1]) / 4) > 850 && ((data.T1[0] + data.T1[1] + data.T2[0] + data.T2[1]) / 4) <= 1000)
        {
            //琥珀色警告
            logFault(OverTemp1);
        }
    }
    //稳态中
    else if (isStable)
    {
        if (((data.T1[0] + data.T1[1] + data.T2[0] + data.T2[0]) / 4) > 1100)
        {
            //红色警告
            isStopping = true;
            isStarted_1 = false;
            isStarted_2 = false;
            isStable = false;
            logFault(OverTemp4);
        }
        else if (((data.T1[0] + data.T1[1] + data.T2[0] + data.T2[0]) / 4) > 950 && ((data.T1[0] + data.T1[1] + data.T2[0] + data.T2[0]) / 4) <= 1100)
        {
            //琥珀色警告
            logFault(OverTemp3);
        }
    }
}


// 根据时间生成发动机数据（可以有小范围的浮动）
void generateData(EngineData& data, bool& isInit, bool& isStarted_1, bool& isStarted_2, bool& isStable, bool& isStopping, const vector<FaultType>& faults)
{
    static double phaseTime = 0.0; // 用于跟踪当前阶段的时间
    if (isInit)
    {
        // 初始化阶段，数据为0
        for (int i = 0; i < 2; ++i)
        {
            data.N1[i] = 0;
            data.N2[i] = 0;
            data.T1[i] = T0;
            data.T2[i] = T0;
        }
        phaseTime = 0.0; // 重置阶段时间

        // 定义基准值
        double baseN1 = 0.95 * RATED_RPM; // 稳定阶段转速为额定转速的95%
        double baseN2 = 0.95 * RATED_RPM;
        double baseT1 = 735;
        double baseT2 = 735;
        double baseV = 43;//根据数据设置
    }
    else if (isStarted_1)
    {
        // 启动阶段1，线性增加
        for (int i = 0; i < 2; ++i)
        {
            
            if (std::find(faults.begin(), faults.end(), N1_1Fail) == faults.end() && std::find(faults.begin(), faults.end(), N1Fail) == faults.end())
            {
                data.N1[0] = 10000 * phaseTime + generateRandomNoise(data.N1[0] * 0.005);
            }
            else
            {
                data.N1[0] = 0;
            }

            if (std::find(faults.begin(), faults.end(), N1_2Fail) == faults.end() && std::find(faults.begin(), faults.end(), N1Fail) == faults.end())
            {
                data.N1[1] = 10000 * phaseTime + generateRandomNoise(data.N1[1] * 0.005);
            }
            else
            {
                data.N1[1] = 0;
            }

            if (std::find(faults.begin(), faults.end(), N2_1Fail) == faults.end() && std::find(faults.begin(), faults.end(), N2Fail) == faults.end())
            {
                data.N2[0] = 10000 * phaseTime + generateRandomNoise(data.N2[0] * 0.005);
            }
            else
            {
                data.N2[0] = 0;
            }

            if (std::find(faults.begin(), faults.end(), N2_2Fail) == faults.end() && std::find(faults.begin(), faults.end(), N2Fail) == faults.end())
            {
                data.N2[1] = 10000 * phaseTime + generateRandomNoise(data.N2[1] * 0.005);
            }
            else
            {
                data.N2[1] = 0;
            }

            if (std::find(faults.begin(), faults.end(), T1_1Fail) == faults.end() && std::find(faults.begin(), faults.end(), T1Fail) == faults.end())
            {
                if (std::find(faults.begin(), faults.end(), OverTemp3) != faults.end())
                {
                    data.T1[0] = 1000;
                }
                else if (std::find(faults.begin(), faults.end(), OverTemp1) != faults.end())
                {
                    data.T1[0] = 900;
                }
                else
                {
                    data.T1[0] = T0 + generateRandomNoise(data.T1[0] * 0.005);
                }
            }
            else
            {
                data.T1[0] = T0;
            }

			if (std::find(faults.begin(), faults.end(), T1_2Fail) == faults.end() && std::find(faults.begin(), faults.end(), T1Fail) == faults.end())
			{
				if (std::find(faults.begin(), faults.end(), OverTemp3) != faults.end())
				{
					data.T1[1] = 1000;
				}
				else if (std::find(faults.begin(), faults.end(), OverTemp1) != faults.end())
				{
					data.T1[1] = 900;
				}
				else
				{
					data.T1[1] = T0 + generateRandomNoise(data.T1[1] * 0.005);
				}
			}
			else
			{
				data.T1[1] = T0;
			}

            if (std::find(faults.begin(), faults.end(), T2_1Fail) == faults.end() && std::find(faults.begin(), faults.end(), T2Fail) == faults.end())
            {
				if (std::find(faults.begin(), faults.end(), OverTemp3) != faults.end())
				{
					data.T2[0] = 1000;
				}
				else if (std::find(faults.begin(), faults.end(), OverTemp1) != faults.end())
				{
					data.T2[0] = 900;
				}
				else
				{
					data.T2[0] = T0 + generateRandomNoise(data.T2[0] * 0.005);
				}
			}
            else
            {
                data.T2[0] = T0;
            }

			if (std::find(faults.begin(), faults.end(), T2_2Fail) == faults.end() && std::find(faults.begin(), faults.end(), T2Fail) == faults.end())
			{
				if (std::find(faults.begin(), faults.end(), OverTemp3) != faults.end())
				{
					data.T2[1] = 1000;
				}
				else if (std::find(faults.begin(), faults.end(), OverTemp1) != faults.end())
				{
					data.T2[1] = 900;
				}
				else
				{
					data.T2[1] = T0 + generateRandomNoise(data.T2[1] * 0.005);
				}
			}


            //不可能出现小于0的情况
            data.N1[i] = max(0.0, data.N1[i]);
            data.N2[i] = max(0.0, data.N2[i]);
            data.T1[i] = max(T0, data.T1[i]);
            data.T2[i] = max(T0, data.T2[i]);
        }
        data.V = 5 * phaseTime + generateRandomNoise(data.V * 0.005);

        if (phaseTime >= 2.0)
        {
            isStarted_1 = false;
            isStarted_2 = true;
            phaseTime = 0.0; // 重置阶段时间
        }
        phaseTime += INTERVAL_MS / 1000.0; // 增加阶段时间
    }
    else if (isStarted_2)
    {
        // 启动阶段2，对数函数增加
        for (int i = 0; i < 2; ++i)
        {
            //阶段时间重置，所以函数需要更改
            if (std::find(faults.begin(), faults.end(), N1_1Fail) == faults.end() && std::find(faults.begin(), faults.end(), N1Fail) == faults.end())
            {
                data.N1[0] = (23000 * log(phaseTime + 1) + 20000) + generateRandomNoise(data.N1[0] * 0.005);
            }
            else
            {
                data.N1[0] = 0;
            }

            if (std::find(faults.begin(), faults.end(), N1_2Fail) == faults.end() && std::find(faults.begin(), faults.end(), N1Fail) == faults.end())
            {
                data.N1[1] = (23000 * log(phaseTime + 1) + 20000) + generateRandomNoise(data.N1[1] * 0.005);
            }
            else
            {
                data.N1[1] = 0;
            }

            if (std::find(faults.begin(), faults.end(), N2_1Fail) == faults.end() && std::find(faults.begin(), faults.end(), N2Fail) == faults.end())
            {
                data.N2[0] = (23000 * log(phaseTime + 1) + 20000) + generateRandomNoise(data.N2[0] * 0.005);
            }
            else
            {
                data.N2[0] = 0;
            }

            if (std::find(faults.begin(), faults.end(), N2_2Fail) == faults.end() && std::find(faults.begin(), faults.end(), N2Fail) == faults.end())
            {
                data.N2[1] = (23000 * log(phaseTime + 1) + 20000) + generateRandomNoise(data.N2[1] * 0.005);
            }
            else
            {
                data.N2[1] = 0;
            }

            if (std::find(faults.begin(), faults.end(), T1_1Fail) == faults.end() && std::find(faults.begin(), faults.end(), T1Fail) == faults.end())
            {
                if (std::find(faults.begin(), faults.end(), OverTemp4) != faults.end())
                {
                    data.T1[0] = 1200;
                }
                else if (std::find(faults.begin(), faults.end(), OverTemp3) != faults.end())
                {
                    data.T1[0] = 1000;
                }
                else if (std::find(faults.begin(), faults.end(), OverTemp2) != faults.end())
                {
                    data.T1[0] = 1100;
                }
                else if (std::find(faults.begin(), faults.end(), OverTemp1) != faults.end())
                {
                    data.T1[0] = 900;
                }
                else
                {
                    data.T1[0] = 900 * log(phaseTime + 1) + T0 + generateRandomNoise(data.T1[0] * 0.005);
                }
            }
            else
            {
                data.T1[0] = T0;
            }

			if (std::find(faults.begin(), faults.end(), T1_2Fail) == faults.end() && std::find(faults.begin(), faults.end(), T1Fail) == faults.end())
			{
				if (std::find(faults.begin(), faults.end(), OverTemp4) != faults.end())
				{
					data.T1[1] = 1200;
				}
				else if (std::find(faults.begin(), faults.end(), OverTemp3) != faults.end())
				{
					data.T1[1] = 1000;
				}
				else if (std::find(faults.begin(), faults.end(), OverTemp2) != faults.end())
				{
					data.T1[1] = 1100;
				}
				else if (std::find(faults.begin(), faults.end(), OverTemp1) != faults.end())
				{
					data.T1[1] = 900;
				}
				else
				{
					data.T1[1] = 900 * log(phaseTime + 1) + T0 + generateRandomNoise(data.T1[1] * 0.005);
				}
			}
			else
			{
				data.T1[1] = T0;
			}


            if (std::find(faults.begin(), faults.end(), T2_1Fail) == faults.end() && std::find(faults.begin(), faults.end(), T2Fail) == faults.end())
            {
                if (std::find(faults.begin(), faults.end(), OverTemp4) != faults.end())
                {
                    data.T2[0] = 1200;
                }
                else if (std::find(faults.begin(), faults.end(), OverTemp3) != faults.end())
                {
                    data.T2[0] = 1000;
                }
                else if (std::find(faults.begin(), faults.end(), OverTemp2) != faults.end())
                {
                    data.T2[0] = 1100;
                }
                else if (std::find(faults.begin(), faults.end(), OverTemp1) != faults.end())
                {
                    data.T2[0] = 900;
                }
                else
                {
                    data.T2[0] = 900 * log(phaseTime + 1) + T0 + generateRandomNoise(data.T2[0] * 0.005);
                }
            }
            else
			{
				data.T2[0] = T0;
			}

            if (std::find(faults.begin(), faults.end(), T2_2Fail) == faults.end() && std::find(faults.begin(), faults.end(), T2Fail) == faults.end())
            {
                if (std::find(faults.begin(), faults.end(), OverTemp4) != faults.end())
                {
                    data.T2[1] = 1200;
                }
                else if (std::find(faults.begin(), faults.end(), OverTemp3) != faults.end())
                {
                    data.T2[1] = 1000;
                }
                else if (std::find(faults.begin(), faults.end(), OverTemp2) != faults.end())
                {
                    data.T2[1] = 1100;
                }
                else if (std::find(faults.begin(), faults.end(), OverTemp1) != faults.end())
                {
                    data.T2[1] = 900;
                }
                else
                {
                    data.T2[1] = 900 * log(phaseTime + 1) + T0 + generateRandomNoise(data.T2[1] * 0.005);
                }
			}
            else
            {
                data.T2[1] = T0;
            }

        }
        data.V = 42 * log(phaseTime + 1) + 10 + generateRandomNoise(data.V * 0.005);

        // 判断是否达到稳定状态
        if ((data.N1[0] / RATED_RPM >= 0.95 && data.N2[0] / RATED_RPM >= 0.95) ||
            (data.N1[1] / RATED_RPM >= 0.95 && data.N2[1] / RATED_RPM >= 0.95))
        {
            isStarted_2 = false;
            isStable = true;
            phaseTime = 0.0; // 重置阶段时间
        }
        phaseTime += INTERVAL_MS / 1000.0; // 增加阶段时间
    }
    else if (isStable)
    {
        // 稳定阶段，数据在±3%范围内波动

        for (int i = 0; i < 2; ++i)
        {
            if (std::find(faults.begin(), faults.end(), N1_1Fail) == faults.end() && std::find(faults.begin(), faults.end(), N1Fail) == faults.end())
            {
                data.N1[0] = data.baseN1 + generateRandomNoise(data.baseN1 * 0.03);
            }
            else
            {
                data.N1[0] = 0;
            }

            if (std::find(faults.begin(), faults.end(), N1_2Fail) == faults.end() && std::find(faults.begin(), faults.end(), N1Fail) == faults.end())
            {
                data.N1[1] = data.baseN1 + generateRandomNoise(data.baseN1 * 0.03);
            }
            else
            {
                data.N1[1] = 0;
            }

            if (std::find(faults.begin(), faults.end(), N2_1Fail) == faults.end() && std::find(faults.begin(), faults.end(), N2Fail) == faults.end())
            {
                data.N2[0] = data.baseN2 + generateRandomNoise(data.baseN2 * 0.03);
            }
            else
            {
                data.N2[0] = 0;
            }

            if (std::find(faults.begin(), faults.end(), N2_2Fail) == faults.end() && std::find(faults.begin(), faults.end(), N2Fail) == faults.end())
            {
                data.N2[1] = data.baseN2 + generateRandomNoise(data.baseN2 * 0.03);
            }
            else
            {
                data.N2[1] = 0;
            }

            if (std::find(faults.begin(), faults.end(), T1_1Fail) == faults.end() && std::find(faults.begin(), faults.end(), T1Fail) == faults.end())
            {
                if (std::find(faults.begin(), faults.end(), OverTemp4) != faults.end())
                {
                    data.T1[0] = 1200;
                }
                else if (std::find(faults.begin(), faults.end(), OverTemp3) != faults.end())
                {
                    data.T1[0] = 1000;
                }
                else if (std::find(faults.begin(), faults.end(), OverTemp2) != faults.end())
                {
                    data.T1[0] = 1100;
                }
                else if (std::find(faults.begin(), faults.end(), OverTemp1) != faults.end())
                {
                    data.T1[0] = 900;
                }
                else
                {
                    data.T1[0] = data.baseT1 + generateRandomNoise(data.baseT1 * 0.03);
                }
            }
            else
            {
                data.T1[0] = T0;
            }


            if (std::find(faults.begin(), faults.end(), T1_2Fail) == faults.end() && std::find(faults.begin(), faults.end(), T1Fail) == faults.end())
            {
                if (std::find(faults.begin(), faults.end(), OverTemp4) != faults.end())
                {
                    data.T1[1] = 1200;
                }
                else if (std::find(faults.begin(), faults.end(), OverTemp3) != faults.end())
                {
                    data.T1[1] = 1000;
                }
                else if (std::find(faults.begin(), faults.end(), OverTemp2) != faults.end())
                {
                    data.T1[1] = 1100;
                }
                else if (std::find(faults.begin(), faults.end(), OverTemp1) != faults.end())
                {
                    data.T1[1] = 900;
                }
                else
                {
                    data.T1[1] = data.baseT1 + generateRandomNoise(data.baseT1 * 0.03);
                }
            }
            else
            {
                data.T1[1] = T0;
            }

			if (std::find(faults.begin(), faults.end(), T2_1Fail) == faults.end() && std::find(faults.begin(), faults.end(), T2Fail) == faults.end())
			{
				if (std::find(faults.begin(), faults.end(), OverTemp4) != faults.end())
				{
					data.T2[0] = 1200;
				}
				else if (std::find(faults.begin(), faults.end(), OverTemp3) != faults.end())
				{
					data.T2[0] = 1000;
				}
				else if (std::find(faults.begin(), faults.end(), OverTemp2) != faults.end())
				{
					data.T2[0] = 1100;
				}
				else if (std::find(faults.begin(), faults.end(), OverTemp1) != faults.end())
				{
					data.T2[0] = 900;
				}
				else
				{
					data.T2[0] = data.baseT2 + generateRandomNoise(data.baseT2 * 0.03);
				}
			}
			else
			{
				data.T2[0] = T0;
			}

            if (std::find(faults.begin(), faults.end(), T2_2Fail) == faults.end() && std::find(faults.begin(), faults.end(), T2Fail) == faults.end())
            {
                if (std::find(faults.begin(), faults.end(), OverTemp4) != faults.end())
                {
                    data.T2[1] = 1200;
                }
                else if (std::find(faults.begin(), faults.end(), OverTemp3) != faults.end())
                {
                    data.T2[1] = 1000;
                }
                else if (std::find(faults.begin(), faults.end(), OverTemp2) != faults.end())
                {
                    data.T2[1] = 1100;
                }
                else if (std::find(faults.begin(), faults.end(), OverTemp1) != faults.end())
                {
                    data.T2[1] = 900;
                }
                else
                {
                    data.T2[1] = data.baseT2 + generateRandomNoise(data.baseT2 * 0.03);
                }
            }
			else
			{
				data.T2[1] = T0;
			}

           
        }
        data.V = data.baseV + generateRandomNoise(data.baseV * 0.03);
    }
    else if (isStopping)
    {
        // 定义停止时间
        const double maxStoppingTime = 10.0; // 最大停车时间为10秒
        const double decayBase = 0.90; // 底数a，确保在10秒内衰减到接近零
        //底数越大，衰减速度越慢

        // 随机扰动因子
        const double randomFactor = 0.01; // 随机扰动因子

        // 判断是否完全停止
        bool allStopped = true;
        for (int i = 0; i < 2; ++i)
        {
            // 如果任一转速未达到0，则没有完全停止
            if (data.N1[i] > 0 || data.N2[i] > 0 || data.T1[i] > T0 * 1.01 || data.T2[i] > T0 * 1.01)
            {
                allStopped = false;
                break;
            }
        }

        if (allStopped)
        {
            // 完全停止后重置所有数据
            for (int i = 0; i < 2; ++i)
            {
                data.N1[i] = 0;
                data.N2[i] = 0;
                data.T1[i] = T0;
                data.T2[i] = T0;
            }
            data.V = 0;
            isStopping = false;
            isInit = true;
            phaseTime = 0.0; // 重置阶段时间
        }
        else
        {
            // 模拟转速对数衰减（没有达到0时才衰减）
            for (int i = 0; i < 2; ++i)
            {
                if (data.N1[i] > 0)
                {
                    data.N1[i] = max(0.0, data.N1[i] * pow(decayBase, phaseTime) + (rand() % 100 - 50) * randomFactor);
                }
                if (data.N2[i] > 0)
                {
                    data.N2[i] = max(0.0, data.N2[i] * pow(decayBase, phaseTime) + (rand() % 100 - 50) * randomFactor);
                }

                // 温度扰动：在 T0 附近波动
                data.T1[i] = max(T0, T0 + (data.T1[i] - T0) * pow(decayBase, phaseTime) + (rand() % 100 - 50) * randomFactor);
                data.T2[i] = max(T0, T0 + (data.T2[i] - T0) * pow(decayBase, phaseTime) + (rand() % 100 - 50) * randomFactor);
            }

            // 燃油流速直接归零
            data.V = 0;
            phaseTime += INTERVAL_MS / 1000.0; // 增加阶段时间
        }
    }

    // 更新燃油余量
    data.C -= data.V * (INTERVAL_MS / 1000.0);
    if (data.C < 0)
    {
        data.C = 0;
        isStopping = true; // 如果没油则停止
    }
}


/*————————————————————*/
/*————————数据保存————————*/
/*————————————————————*/
    // 将数据保存到文件
void saveDataToFile(const EngineData& data, double time, ofstream& file)
{
    file << time << ",";
    for (int i = 0; i < 2; ++i)
    {
        file << data.N1[i] << "," << data.N2[i] << "," << data.T1[i] << "," << data.T2[i] << ",";
    }
    file << data.C << "," << data.V << "\n";
}


/*————————————————————*/
/*————————界面绘制————————*/
/*————————————————————*/
// 定义颜色
const COLORREF GRAY = RGB(128, 128, 128);
const COLORREF AMBER = RGB(255, 191, 0);

struct DataBoard
{
    LPCTSTR name;                       //表盘名称
    double value;                       //当前值
    double maxDegree = 210;             //最大值（默认210度）
    double minDegree = 0;               //最小值
    double maxValue;                    //最大值
    double minValue;                    //最小值
    double x;                           //圆心x坐标
    double y;                           //圆心y坐标
    double radius;                      //半径
    COLORREF color;                     //颜色（白色，琥珀色或红色）

    DataBoard(LPCTSTR name, double value, double maxValue, double minValue, double x, double y, double radius, COLORREF color) :
        name(name), value(value), maxValue(maxValue), minValue(minValue), x(x), y(y), radius(radius), color(color)
    {
    }
};

double calcDegree(double value, double max, double min, double maxDegree, double minDegree) {
    double Degree = (maxDegree - minDegree) * value / (max - min);
    return Degree;//返回角度0`210度
}

void drawDataBoard(DataBoard& DataBoard) {
    double x = DataBoard.x;
    double y = DataBoard.y;
    double radius = DataBoard.radius;

    // 绘制表盘外圈
    setcolor(WHITE);
    pie(x - radius, y - radius, x + radius, y + radius, DataBoard.maxDegree, DataBoard.minDegree);

    // 绘制表盘名称
    outtextxy(x - 25, y - 50, DataBoard.name);

    // 绘制数值显示区域
    std::wstring value;
    value = std::to_wstring(DataBoard.value);
    RECT valueRect = { x, y - 25, x + radius + 15, y };
    rectangle(int(valueRect.left), int(valueRect.top), int(valueRect.right), int(valueRect.bottom));
    drawtext(value.c_str(), &valueRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    // 绘制填充区域
    setfillcolor(DataBoard.color);
    // 计算当前值对应的角度（从 0°顺时针开始）
    double fillAngle = calcDegree(DataBoard.value, DataBoard.maxValue, DataBoard.minValue, DataBoard.maxDegree, DataBoard.minDegree);

    // 从 minDegree (0°) 到当前计算的角度顺时针填充
    if (fillAngle > 0.01 && fillAngle < 350)
    {
        fillpie(x - radius * 0.9, y - radius * 0.9, x + radius * 0.9, y + radius * 0.9,
            (DataBoard.minDegree - fillAngle) * 2, DataBoard.minDegree);
    }

    // 恢复绘图属性
    setcolor(WHITE);
    setlinestyle(PS_SOLID, 1);
}

// 通过错误列表，判断N1表盘颜色
COLORREF checkN1DataBoardColor(std::vector<FaultType> faults) {
    if (faults.empty()) {
        return GRAY;
    }
    else {
        for (FaultType fault : faults) {
            if (fault == OverSpd2) {
                return RED;
            }
            else if (fault == OverSpd1) {
                return AMBER;
            }
        }
        return GRAY;
    }
}

// 通过错误列表，判断N2表盘颜色
COLORREF checkN2DataBoardColor(std::vector<FaultType> faults) {
    if (faults.empty()) {
        return GRAY;
    }
    else {
        for (FaultType fault : faults) {
            if (fault == OverSpd2) {
                return RED;
            }
            else if (fault == OverSpd1) {
                return AMBER;
            }
        }
        return GRAY;
    }
}

// 通过错误列表，判断EGT表盘颜色
COLORREF checkTDataBoardColor(std::vector<FaultType> faults) {
    if (faults.empty()) {
        return GRAY;
    }
    else {
        for (FaultType fault : faults) {
            if (fault == OverTemp2) {
                return RED;
            }
            else if (fault == OverTemp4) {
                return RED;
            }
            else if (fault == OverTemp1) {
                return AMBER;
            }
            else if (fault == OverTemp3) {
                return AMBER;
            }

        }
    }
    return GRAY;
}



void drawInterface(const EngineData& data, const std::vector<FaultType>& faults)
{
    // 清除绘图窗口
    cleardevice();

    // 设置字体和颜色
    settextstyle(20, 0, _T("Arial"));
    settextcolor(WHITE);

    COLORREF color;

    /*——————仪表盘——————*/
    // 绘制左发动机表盘
    color = checkN1DataBoardColor(faults);
    DataBoard leftEngineN1(_T("N_L1:"), data.N1[0] * 100 / RATED_RPM, 125 * 100, 0.0, 100, 100, 80, color);
    drawDataBoard(leftEngineN1);

    color = checkN1DataBoardColor(faults);
    DataBoard leftEngineN2(_T("N_L2:"), data.N1[1] * 100 / RATED_RPM, 125 * 100, 0.0, 100, 280, 80, color);
    drawDataBoard(leftEngineN2);

    color = checkTDataBoardColor(faults);
    DataBoard leftEngineT(_T("EGT_L:"), (data.T1[0] + data.T1[1]) / 2, 1200.0 * 100, -5.0, 100, 460, 80, color);
    drawDataBoard(leftEngineT);

    // 绘制右发动机表盘
    color = checkN2DataBoardColor(faults);
    DataBoard rightEngineN1(_T("N_R1:"), data.N2[0] * 100 / RATED_RPM, 125 * 100, 0.0, 300, 100, 80, color);
    drawDataBoard(rightEngineN1);

    color = checkN2DataBoardColor(faults);
    DataBoard rightEngineN2(_T("N_R2:"), data.N2[1] * 100 / RATED_RPM, 125 * 100, 0.0, 300, 280, 80, color);
    drawDataBoard(rightEngineN2);

    color = checkTDataBoardColor(faults);
    DataBoard rightEngineT(_T("EGT_R:"), (data.T2[0] + data.T2[1]) / 2, 1200.0 * 100, -5.0, 300, 460, 80, color);
    drawDataBoard(rightEngineT);

    setfillcolor(WHITE);

    /*—————燃油与油耗—————*/
    // 绘制燃油槽内的燃油量
    double fuel = data.C;
    double fuelMax = 20000.0;

    //流速
    setlinecolor(WHITE);
    rectangle(20, 560, 180, 590);
    outtextxy(70, 570, _T("Fuel Flow:"));

    rectangle(180, 560, 380, 590);
    wchar_t fuelFlowStr[20];
    swprintf(fuelFlowStr, 20, L"%.2f", data.V);
    outtextxy(230, 570, fuelFlowStr);
    //燃油
    rectangle(20, 600, 180, 630);
    outtextxy(70, 610, _T("Fuel:"));

    rectangle(180, 600, 380, 630);
    if (fuel == 0)
    {
        outtextxy(230, 610, _T("ERROR"));
    }
    else
    {
        wchar_t fuelStr[20];
        swprintf(fuelStr, 20, L"%.2f", fuel);
        outtextxy(230, 610, fuelStr);
    }

    // 绘制燃油槽
    setlinecolor(WHITE);
    rectangle(880, 20, 900, 180);
    if (fuel < 1000)
    {
        setfillcolor(AMBER);// 如果燃油量过少，燃油槽显示琥珀色
    }
    else
    {
        setfillcolor(WHITE);
    }
    solidrectangle(880, static_cast<int>(max(20, 180 - 160 * fuel / fuelMax)), 900, 180);

    /*————启动停车与状态显示————*/
    //绘制启动按钮
    rectangle(450, 20, 600, 90);
    RECT startRect = { 450, 20, 600, 90 };
    drawtext(_T("Start"), &startRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //绘制停车按钮
    rectangle(450, 110, 600, 180);
    RECT stopRect = { 450, 110, 600, 180 };
    drawtext(_T("Stop"), &stopRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    // 绘制增加推力按钮（上三角）
    POINT increaseThrustPoints[] = { {660, 20}, {620, 90}, {700, 90} };
    fillpolygon(increaseThrustPoints, 3);

    // 绘制减小推力按钮（下三角）
    POINT decreaseThrustPoints[] = { {660, 180}, {620, 110}, {700, 110} };
    fillpolygon(decreaseThrustPoints, 3);

    //状态显示框
    // 绘制 Start 状态显示框
    if (isStarted_1 || isStarted_2)
    {
        setfillcolor(LIGHTGRAY);
    }
    else
    {
        setfillcolor(DARKGRAY);
    }
    solidroundrect(720, 20, 870, 90, 10, 10);
    RECT startStatusRect = { 720, 20, 870, 90 };
    setbkmode(TRANSPARENT);
    drawtext(_T("Start"), &startStatusRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    // 计算N的百分比值
    double averageN = ((data.N1[0] + data.N1[1] + data.N2[0] + data.N2[1])) / (4.0 * RATED_RPM) * 100.0;

    // 绘制 Run 状态显示框
    if (isStable && averageN >= 95.0)
    {
        setfillcolor(LIGHTGRAY);
    }
    else
    {
        setfillcolor(DARKGRAY);

    }
    solidroundrect(720, 110, 870, 180, 10, 10);
    RECT runStatusRect = { 720, 110, 870, 180 };
    setbkmode(TRANSPARENT);
    drawtext(_T("Run"), &runStatusRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}


/*————故障显示————*/
COLORREF checkFaultColor(const std::vector<FaultType>& faults, FaultType faultType) {
    if (std::find(faults.begin(), faults.end(), faultType) != faults.end()) {
        switch (faultType) {
        case OverSpd2:
        case OverTemp2:
        case OverTemp4:
        case FuelSFail:
        case N1andN2Fail:
        case T1andT2Fail:
            return RED;
        case OverSpd1:
        case OverTemp1:
        case OverTemp3:
        case LowFuel:
        case OverFF:
        case N1Fail:
        case N2Fail:
        case T1Fail:
        case T2Fail:
            return AMBER;
        case N1_1Fail:
        case N1_2Fail:
        case N2_1Fail:
        case N2_2Fail:
        case T1_1Fail:
        case T1_2Fail:
        case T2_1Fail:
        case T2_2Fail:
            return WHITE;
        default:
            return DARKGRAY;
        }
    }
    return DARKGRAY;
}

void drawFaultDisplay(const std::vector<FaultType>& faults)
{
    //自定义
    LOGFONT f;
    gettextstyle(&f);						//获取当前字体设置
    f.lfHeight = 20;						//设置字体高度为 48
    _tcscpy_s(f.lfFaceName, _T("Arial"));	//设置字体
    f.lfQuality = ANTIALIASED_QUALITY;		//设置输出效果为抗锯齿  
    settextstyle(&f);
    settextcolor(BLACK);
    //——第一类故障——
    //N1_1
    setfillcolor(checkFaultColor(faults, N1_1Fail));
    solidroundrect(450, 200, 590, 240, 10, 10);
    RECT N1_1FailRect = { 450, 200, 590, 240 };
    setbkmode(TRANSPARENT);
    drawtext(_T("N1_1Fail"), &N1_1FailRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //N1_2
    setfillcolor(checkFaultColor(faults, N1_2Fail));
    solidroundrect(450, 250, 590, 290, 10, 10);
    RECT N1_2FailRect = { 450, 250, 590, 290 };
    setbkmode(TRANSPARENT);
    drawtext(_T("N1_2Fail"), &N1_2FailRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //N1
    setfillcolor(checkFaultColor(faults, N1Fail));
    solidroundrect(450, 300, 590, 340, 10, 10);
    RECT N1FailRect = { 450, 300, 590, 340 };
    setbkmode(TRANSPARENT);
    drawtext(_T("N1Fail"), &N1FailRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //N2_1
    setfillcolor(checkFaultColor(faults, N2_1Fail));
    solidroundrect(600, 200, 740, 240, 10, 10);
    RECT N2_1FailRect = { 600, 200, 740, 240 };
    setbkmode(TRANSPARENT);
    drawtext(_T("N2_1Fail"), &N2_1FailRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //N2_2
    setfillcolor(checkFaultColor(faults, N2_2Fail));
    solidroundrect(600, 250, 740, 290, 10, 10);
    RECT N2_2FailRect = { 600, 250, 740, 290 };
    setbkmode(TRANSPARENT);
    drawtext(_T("N2_2Fail"), &N2_2FailRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //N2
    setfillcolor(checkFaultColor(faults, N2Fail));
    solidroundrect(600, 300, 740, 340, 10, 10);
    RECT N2FailRect = { 600, 300, 740, 340 };
    setbkmode(TRANSPARENT);
    drawtext(_T("N2Fail"), &N2FailRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //N1andN2Fail
    setfillcolor(checkFaultColor(faults, N1andN2Fail));
    solidroundrect(750, 200, 900, 340, 10, 10);
    RECT N1andN2FailRect = { 750, 200, 900, 340 };
    setbkmode(TRANSPARENT);
    drawtext(_T("N1andN2Fail"), &N1andN2FailRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //——第二类故障——
    //T1_1
    setfillcolor(checkFaultColor(faults, T1_1Fail));
    solidroundrect(450, 350, 590, 390, 10, 10);
    RECT T1_1FailRect = { 450, 350, 590, 390 };
    setbkmode(TRANSPARENT);
    drawtext(_T("T1_1Fail"), &T1_1FailRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //T1_2
    setfillcolor(checkFaultColor(faults, T1_2Fail));
    solidroundrect(450, 400, 590, 440, 10, 10);
    RECT T1_2FailRect = { 450, 400, 590, 440 };
    setbkmode(TRANSPARENT);
    drawtext(_T("T1_2Fail"), &T1_2FailRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //T1
    setfillcolor(checkFaultColor(faults, T1Fail));
    solidroundrect(450, 450, 590, 490, 10, 10);
    RECT T1FailRect = { 450, 450, 590, 490 };
    setbkmode(TRANSPARENT);
    drawtext(_T("T1Fail"), &T1FailRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //T2_1
    setfillcolor(checkFaultColor(faults, T2_1Fail));
    solidroundrect(600, 350, 740, 390, 10, 10);
    RECT T2_1FailRect = { 600, 350, 740, 390 };
    setbkmode(TRANSPARENT);
    drawtext(_T("T2_1Fail"), &T2_1FailRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //T2_2
    setfillcolor(checkFaultColor(faults, T2_2Fail));
    solidroundrect(600, 400, 740, 440, 10, 10);
    RECT T2_2FailRect = { 600, 400, 740, 440 };
    setbkmode(TRANSPARENT);
    drawtext(_T("T2_2Fail"), &T2_2FailRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //T2
    setfillcolor(checkFaultColor(faults, T2Fail));
    solidroundrect(600, 450, 740, 490, 10, 10);
    RECT T2FailRect = { 600, 450, 740, 490 };
    setbkmode(TRANSPARENT);
    drawtext(_T("T2Fail"), &T2FailRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //T1andT2Fail
    setfillcolor(checkFaultColor(faults, T1andT2Fail));
    solidroundrect(750, 350, 900, 490, 10, 10);
    RECT T1andT2FailRect = { 750, 350, 900, 490 };
    setbkmode(TRANSPARENT);
    drawtext(_T("T1andT2Fail"), &T1andT2FailRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //第二类故障————
    //LowFuel
    setfillcolor(checkFaultColor(faults, LowFuel));
    solidroundrect(450, 500, 590, 540, 10, 10);
    RECT LowFuelRect = { 450, 500, 590, 540 };
    setbkmode(TRANSPARENT);
    drawtext(_T("LowFuel"), &LowFuelRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //FuelSFail
    setfillcolor(checkFaultColor(faults, FuelSFail));
    solidroundrect(600, 500, 740, 540, 10, 10);
    RECT FuelSFailRect = { 600, 500, 740, 540 };
    setbkmode(TRANSPARENT);
    drawtext(_T("FuelSFail"), &FuelSFailRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //OverFF
    setfillcolor(checkFaultColor(faults, OverFF));
    solidroundrect(750, 500, 900, 540, 10, 10);
    RECT OverFFRect = { 750, 500, 900, 540 };
    setbkmode(TRANSPARENT);
    drawtext(_T("OverFF"), &OverFFRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //第三类故障————
    //OverSpd1
    setfillcolor(checkFaultColor(faults, OverSpd1));
    solidroundrect(450, 550, 590, 590, 10, 10);
    RECT OverSpd1Rect = { 450, 550, 590, 590 };
    setbkmode(TRANSPARENT);
    drawtext(_T("OverSpd1"), &OverSpd1Rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //OverSpd2
    setfillcolor(checkFaultColor(faults, OverSpd2));
    solidroundrect(600, 550, 740, 590, 10, 10);
    RECT OverSpd2Rect = { 600, 550, 740, 590 };
    setbkmode(TRANSPARENT);
    drawtext(_T("OverSpd2"), &OverSpd2Rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //第四类故障————
    //OverTemp1
    setfillcolor(checkFaultColor(faults, OverTemp1));
    solidroundrect(450, 600, 590, 640, 10, 10);
    RECT OverTemp1Rect = { 450, 600, 590, 640 };
    setbkmode(TRANSPARENT);
    drawtext(_T("OverTemp1"), &OverTemp1Rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //OverTemp2
    setfillcolor(checkFaultColor(faults, OverTemp2));
    solidroundrect(600, 600, 740, 640, 10, 10);
    RECT OverTemp2Rect = { 600, 600, 740, 640 };
    setbkmode(TRANSPARENT);
    drawtext(_T("OverTemp2"), &OverTemp2Rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //OverTemp3
    setfillcolor(checkFaultColor(faults, OverTemp3));
    solidroundrect(750, 550, 900, 590, 10, 10);
    RECT OverTemp3Rect = { 750, 550, 900, 590 };
    setbkmode(TRANSPARENT);
    drawtext(_T("OverTemp3"), &OverTemp3Rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //OverTemp4
    setfillcolor(checkFaultColor(faults, OverTemp4));
    solidroundrect(750, 600, 900, 640, 10, 10);
    RECT OverTemp4Rect = { 750, 600, 900, 640 };
    setbkmode(TRANSPARENT);
    drawtext(_T("OverTemp4"), &OverTemp4Rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

// 将 FaultType 转换为字符串
string faultToString(FaultType fault)
{
    switch (fault)
    {
    case N1_1Fail: return "N1_1Fail";
    case N1_2Fail: return "N1_2Fail";
    case N2_1Fail: return "N2_1Fail";
    case N2_2Fail: return "N2_2Fail";
    case T1_1Fail: return "T1_1Fail";
    case T1_2Fail: return "T1_2Fail";
    case T2_1Fail: return "T2_1Fail";
    case T2_2Fail: return "T2_2Fail";
    case N1Fail: return "N1Fail";
    case N2Fail: return "N2Fail";
    case T1Fail: return "T1Fail";
    case T2Fail: return "T2Fail";
    case N1andN2Fail: return "N1andN2Fail";
    case T1andT2Fail: return "T1andT2Fail";
    case LowFuel: return "LowFuel";
    case FuelSFail: return "FuelSFail";
    case OverFF: return "OverFF";
    case OverSpd1: return "OverSpd1";
    case OverSpd2: return "OverSpd2";
    case OverTemp1: return "OverTemp1";
    case OverTemp2: return "OverTemp2";
    case OverTemp3: return "OverTemp3";
    case OverTemp4: return "OverTemp4";
    }
}

/*————————————————————*/
/*———————鼠标点击处理———————*/
/*————————————————————*/
int handleMouseClick()
{
    MOUSEMSG m = GetMouseMsg();
    switch (m.uMsg)
    {
    case WM_LBUTTONDOWN: // 如果是左键按下
        // 检查是否点击了 Start 按钮
        if (m.x >= 450 && m.x <= 600 && m.y >= 20 && m.y <= 90)
        {
            return 1; // 返回命令值 1
        }
        // 检查是否点击了 Stop 按钮
        if (m.x >= 450 && m.x <= 600 && m.y >= 110 && m.y <= 180)
        {
            return 2; // 返回命令值 2
        }
        // 检查是否点击了增加推力按钮（上三角）
        if (m.x >= 620 && m.x <= 700 && m.y >= 20 && m.y <= 90)
        {
            return 3; // 返回命令值 3
        }
        // 检查是否点击了减小推力按钮（下三角）
        if (m.x >= 620 && m.x <= 700 && m.y >= 110 && m.y <= 180)
        {
            return 4; // 返回命令值 4
        }

        //检查每一个故障按钮：
        // 11-17.21-27.31-33.41-42，51-54分别对应故障类型一（N）、一（T）、二、三、四
        if (m.x >= 450 && m.x <= 590 && m.y >= 200 && m.y <= 240)
        {
            return 11;
        }
        if (m.x >= 450 && m.x <= 590 && m.y >= 250 && m.y <= 290)
        {
            return 12;
        }
        if (m.x >= 450 && m.x <= 590 && m.y >= 300 && m.y <= 340)
        {
            return 13;
        }
        if (m.x >= 600 && m.x <= 740 && m.y >= 200 && m.y <= 240)
        {
            return 14;
        }
        if (m.x >= 600 && m.x <= 740 && m.y >= 250 && m.y <= 290)
        {
            return 15;
        }
        if (m.x >= 600 && m.x <= 740 && m.y >= 300 && m.y <= 340)
        {
            return 16;
        }
        if (m.x >= 750 && m.x <= 900 && m.y >= 200 && m.y <= 340)
        {
            return 17;
        }
        if (m.x >= 450 && m.x <= 590 && m.y >= 350 && m.y <= 390)
        {
            return 21;
        }
        if (m.x >= 450 && m.x <= 590 && m.y >= 400 && m.y <= 440)
        {
            return 22;
        }
        if (m.x >= 450 && m.x <= 590 && m.y >= 450 && m.y <= 490)
        {
            return 23;
        }
        if (m.x >= 600 && m.x <= 740 && m.y >= 350 && m.y <= 390)
        {
            return 24;
        }
        if (m.x >= 600 && m.x <= 740 && m.y >= 400 && m.y <= 440)
        {
            return 25;
        }
        if (m.x >= 600 && m.x <= 740 && m.y >= 450 && m.y <= 490)
        {
            return 26;
        }
        if (m.x >= 750 && m.x <= 900 && m.y >= 350 && m.y <= 490)
        {
            return 27;
        }
        if (m.x >= 450 && m.x <= 590 && m.y >= 500 && m.y <= 540)
        {
            return 31;
        }
        if (m.x >= 600 && m.x <= 740 && m.y >= 500 && m.y <= 540)
        {
            return 32;
        }
        if (m.x >= 750 && m.x <= 900 && m.y >= 500 && m.y <= 540)
        {
            return 33;
        }
        if (m.x >= 450 && m.x <= 590 && m.y >= 550 && m.y <= 590)
        {
            return 41;
        }
        if (m.x >= 600 && m.x <= 740 && m.y >= 550 && m.y <= 590)
        {
            return 42;
        }
        if (m.x >= 450 && m.x <= 590 && m.y >= 600 && m.y <= 640)
        {
            return 51;
        }
        if (m.x >= 600 && m.x <= 740 && m.y >= 600 && m.y <= 640)
        {
            return 52;
        }
        if (m.x >= 750 && m.x <= 900 && m.y >= 550 && m.y <= 590)
        {
            return 53;
        }
        if (m.x >= 750 && m.x <= 900 && m.y >= 600 && m.y <= 640)
        {
            return 54;
        }

    }
    return -1; // 如果没有点击有效区域，返回无效命令值
}

/*————————————————————*/
/*————————MAIN函数————————*/
/*————————————————————*/
int main()
{
    // 初始化发动机数据和其他变量
    EngineData engineData = {};
    engineData.C = MAX_FUEL; // 初始化燃油余量为最大燃油量
    engineData.V = 0;        // 初始燃油流速为0
    // 故障时间记录数据结构
    std::map<FaultType, double> faultTimeMap;
    // 用于记录每种故障上次记录日志的时间
    std::map<FaultType, double> faultLogTimeMap;
    vector<FaultType> faults;   // 用于存储故障信息
    double totalTime = 0.0;     // 总运行时间
    double time = 0.0;          // 当前时间



    // 打开数据文件保存文件
    ofstream dataFile("engine_data.csv");
    if (!dataFile.is_open())
    {
        cout << "无法打开数据文件！" << endl;
        return -1;
    }

    // 新增：打开日志文件
    ofstream logFile("fails.log");
    if (!logFile.is_open())
    {
        cout << "无法打开日志文件！" << endl;
        return -1;
    }

    // 写入数据文件表头
    dataFile << "Time,N1_1,N1_2,N2_1,N2_2,T1_1,T1_2,T2_1,T2_2,C,V\n";

    // 初始化绘图窗口
    initgraph(920, 660); // 根据需要调整窗口尺寸

    // 增加一个标志位，记录是否已经提示过用户
    bool hasPrompted = false;

    // 开始批量绘制
    BeginBatchDraw();

    while (true)
    {
        // 检查是否有鼠标点击
        if (MouseHit())
        {
            int command = handleMouseClick();
            if (command != -1)
            {
                if (command == 1)
                {
                    isInit = false;
                    isStarted_1 = true;
                    cout << "发动机启动中..." << endl;
                    hasPrompted = false; // 重置提示标志位
                }
                else if (command == 2)
                {
                    isStopping = true;
                    isStarted_1 = false;
                    isStarted_2 = false;
                    isStable = false;
                    cout << "发动机停止中..." << endl;
                }
                else if (command == 3)
                {
                    increaseThrust(engineData);
                    cout << "增加推力..." << endl;
                }
                else if (command == 4)
                {
                    decreaseThrust(engineData);
                    cout << "减小推力..." << endl;
                }
                else if (command >= 11 && command <= 54)
                {
                    // 处理故障模拟按键
                    FaultType fault;
                    switch (command)
                    {
                    case 11:
                        engineData.N1[0] = 0;
                        fault = N1_1Fail; break;
                    case 12:
                        engineData.N1[1] = 0;
                        fault = N1_2Fail; break;
                    case 13:
                        engineData.N1[0] = 0;
                        engineData.N1[1] = 0;
                        fault = N1Fail; break;
                    case 14:
                        engineData.N2[0] = 0;
                        fault = N2_1Fail; break;
                    case 15:
                        engineData.N2[1] = 0;
                        fault = N2_2Fail; break;
                    case 16:
                        engineData.N2[0] = 0;
                        engineData.N2[1] = 0;
                        fault = N2Fail; break;
                    case 17:
                        engineData.N1[0] = 0;
                        engineData.N1[1] = 0;
                        engineData.N2[0] = 0;
                        engineData.N2[1] = 0;
                        fault = N1andN2Fail; break;
                    case 21:
                        engineData.T1[0] = 0;
                        fault = T1_1Fail; break;
                    case 22:
                        engineData.T1[1] = 0;
                        fault = T1_2Fail; break;
                    case 23:
                        engineData.T1[0] = 0;
                        engineData.T1[1] = 0;
                        fault = T1Fail; break;
                    case 24:
                        engineData.T2[0] = 0;
                        fault = T2_1Fail; break;
                    case 25:
                        engineData.T2[1] = 0;
                        fault = T2_2Fail; break;
                    case 26:
                        engineData.T2[0] = 0;
                        engineData.T2[1] = 0;
                        fault = T2Fail; break;
                    case 27:
                        engineData.T1[0] = 0;
                        engineData.T1[1] = 0;
                        engineData.T2[0] = 0;
                        engineData.T2[1] = 0;
                        fault = T1andT2Fail; break;
                    case 31:
                        engineData.C = 750;
                        fault = LowFuel; break;
                    case 32:
                        engineData.C = 0;
                        fault = FuelSFail; break;
                    case 33:
                        engineData.V = 55;
                        fault = OverFF; break;
                    case 41:
                        engineData.N1[0] = 1.1 * RATED_RPM;
                        engineData.N1[1] = 1.1 * RATED_RPM;
                        engineData.N2[0] = 1.1 * RATED_RPM;
                        engineData.N2[1] = 1.1 * RATED_RPM;
                        fault = OverSpd1;
                        break;
                    case 42:
                        engineData.N1[0] = 1.3 * RATED_RPM;
                        engineData.N1[1] = 1.3 * RATED_RPM;
                        engineData.N2[0] = 1.3 * RATED_RPM;
                        engineData.N2[1] = 1.3 * RATED_RPM;
                        fault = OverSpd2;
                        break;
                    case 51:
                        engineData.T1[0] = 900.0;
                        engineData.T1[1] = 900.0;
                        engineData.T2[0] = 900.0;
                        engineData.T2[1] = 900.0;
                        fault = OverTemp1;
                        break;
                    case 52:
                        engineData.T1[0] = 1100.0;
                        engineData.T1[1] = 1100.0;
                        engineData.T2[0] = 1100.0;
                        engineData.T2[1] = 1100.0;
                        fault = OverTemp2; break;
                    case 53:
                        engineData.T1[0] = 1000.0;
                        engineData.T1[1] = 1000.0;
                        engineData.T2[0] = 1000.0;
                        engineData.T2[1] = 1000.0;
                        fault = OverTemp3;
                        break;
                    case 54:
                        engineData.T1[0] = 1200.0;
                        engineData.T1[1] = 1200.0;
                        engineData.T2[0] = 1200.0;
                        engineData.T2[1] = 1200.0;
                        fault = OverTemp4;
                        break;
                    }

                    // 记录故障
                    faults.push_back(fault);
                    faultTimeMap[fault] = totalTime;
                    logFile << totalTime << "s: " << faultToString(fault) << endl;
                    faultLogTimeMap[fault] = totalTime;

                    // 绘制界面，确保数据更新
                    drawInterface(engineData, faults);
                    drawFaultDisplay(faults);

                    // 如果是严重故障，停止发动机
                    if (fault == N1andN2Fail || fault == T1andT2Fail || fault == FuelSFail || fault == OverSpd2 || fault == OverTemp2 || fault == OverTemp4)
                    {
                        isStopping = true;
                        isStarted_1 = false;
                        isStarted_2 = false;
                        isStable = false;
                        cout << "发动机停止中..." << endl;
                    }
                }
                else if (command == 0)
                {
                    // 退出程序
                    break;
                }
            }
        }

        // 生成数据
        generateData(engineData, isInit, isStarted_1, isStarted_2, isStable, isStopping,faults);

        // 获取当前时间
        double currentTime = totalTime;

        // 检查故障
        checkData(engineData, isInit, isStarted_1, isStarted_2, isStable, isStopping, faults, faultTimeMap, currentTime, logFile, faultLogTimeMap);

        // 更新故障列表，保持告警显示 5 秒
        auto it = faultTimeMap.begin();
        while (it != faultTimeMap.end())
        {
            if (currentTime - it->second > 5.0)
            {
                // 故障已超过 5 秒，移除
                it = faultTimeMap.erase(it);
            }
            else
            {
                ++it;
            }
        }

        // 清空 faults 列表，重新添加未过期的故障
        faults.clear();
        for (const auto& pair : faultTimeMap)
        {
            faults.push_back(pair.first);
        }

        // 保存数据到文件
        saveDataToFile(engineData, totalTime, dataFile);

        // 绘制界面
        drawInterface(engineData, faults);
        drawFaultDisplay(faults);

        // 刷新绘图
        FlushBatchDraw();

        // 延时
        this_thread::sleep_for(chrono::milliseconds(INTERVAL_MS));

        // 更新时间
        time += INTERVAL_MS / 1000.0;
        totalTime += INTERVAL_MS / 1000.0;

        // 判断发动机是否已停止并返回初始状态
        if (isInit && !isStarted_1 && !isStarted_2 && !isStable && !isStopping)
        {
            if (!hasPrompted)
            {
                hasPrompted = true; // 标记已经提示过用户
            }
        }
    }

    // 结束批量绘制
    EndBatchDraw();

    // 关闭数据文件
    dataFile.close();
    // 关闭日志文件
    logFile.close();

    // 关闭绘图窗口
    closegraph();
    return 0;
}
