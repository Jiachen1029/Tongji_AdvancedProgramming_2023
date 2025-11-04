#include <iostream>
#include <iomanip>
#define SAMPLE_LENGTH 10
#define DATA_NUM 4
#define PARAMS_NUM 4
#define MAX_ITERATION 128
using namespace std;

/****************** TODO ******************/
// mean_square_error 函数
double mean_square_error(int data[SAMPLE_LENGTH][DATA_NUM], double params[PARAMS_NUM])
{
	double loss = 0;
    for (int i = 0; i < SAMPLE_LENGTH; i++)
    {
		double y = params[0] * data[i][0] + params[1] * data[i][1] + params[2] * data[i][2] + params[3];
		loss += (y - data[i][3]) * (y - data[i][3]);
	}
	return loss / SAMPLE_LENGTH;
}
// update_params 函数
void update_params(int data[SAMPLE_LENGTH][DATA_NUM], double params[PARAMS_NUM])
{
	double w1 = 0, w2 = 0, w3 = 0, b = 0;
    for (int i = 0; i < SAMPLE_LENGTH; i++)
    {
		double y = params[0] * data[i][0] + params[1] * data[i][1] + params[2] * data[i][2] + params[3];
		w1 += (y - data[i][3]) * data[i][0];
		w2 += (y - data[i][3]) * data[i][1];
		w3 += (y - data[i][3]) * data[i][2];
		b += (y - data[i][3]);
	}
	params[0] -= 0.01 * w1 / 5;
	params[1] -= 0.01 * w2 / 5;
	params[2] -= 0.01 * w3 / 5;
	params[3] -= 0.01 * b / 5;
}
/**************** TODO-END ****************/

int main()
{
    int data[SAMPLE_LENGTH][DATA_NUM] = {};

    // 输入训练数据
    for (int i = 0; i < SAMPLE_LENGTH; ++i)
    {
        for (int j = 0; j < DATA_NUM; ++j)
        {
            cin >> data[i][j];
        }
    }

    // 1. 参数初始化
    double params[PARAMS_NUM] = {};
    // 四个参数初始化为零，从前往后分别是w1,w2,w3,b

    // 进行迭代
    double loss = 0;
    cout << "Start Iteration!" << endl;
    cout << fixed << setprecision(6);
    for (int i = 0; i < MAX_ITERATION; ++i)
    {
        // 2. 使用当前参数和数据，计算损失函数
        loss = mean_square_error(data, params);
        // i 固定三位宽度输出，loss 固定六位小数位数输出
        cout << "iter: " << setw(3) << i << ", loss: ";
        cout << loss << endl;

        // 3. 计算梯度，使用梯度下降的方法更新参数
        update_params(data, params);
    }
    cout << "Iteration Finished!" << endl;

    // 输出回归后的参数值：
    cout << "params:" << endl;
    for (int i = 0; i < PARAMS_NUM; ++i)
    {
        cout << params[i] << endl;
    }

    return 0;
}