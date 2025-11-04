#include <iostream>
using namespace std;

void sum(int* matrix, int axis, int* answer)
{
    /****************** TODO ******************/
    for (int i = 0; i < 9; ++i) 
    {
        answer[i] = 0;//防止影响后面，初始化一下
    }
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 3; ++k) {
                int index = 0;
                switch (axis) {
                case 0:
                    index = j * 3 + k;
                    break;
                case 1:
                    index = i * 3 + k;
                    break;
                case 2:
                    index = i * 3 + j;
                    break;
                }
                answer[index] += *((matrix + i * 9) + j * 3 + k);
            }
        }
    }
    /**************** TODO-END ****************/
}

int main()
{
    int arr[3][3][3] = {};
    int answer[3][3] = {};

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 3; ++k) {
                cin >> arr[i][j][k];
            }
        }
    }

    for (int axis = 0; axis < 3; ++axis)
    {
        sum(arr[0][0], axis, answer[0]);
        // 输出沿着 axis 轴向求和的结果
        cout << "axis = " << axis << endl;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cout << answer[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    return 0;
}