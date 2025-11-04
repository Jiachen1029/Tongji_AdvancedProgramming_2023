#include <iostream>
using namespace std;

void anticlockwise_print(int* array, int rows, int cols)
{
    /****************** TODO ******************/
    int top = 0, bottom = rows - 1;
    int left = 0, right = cols - 1;
    while (true)
    {
        //从上到下
        for (int i = top; i <= bottom; ++i) {
            cout << array[i * cols + left] << " ";
        }
        if (++left > right) {
            break;
        }
        //从左到右
        for (int i = left; i <= right; ++i) {
            cout << array[bottom * cols + i] << " ";
        }
        if (--bottom < top) {
            break;
        }
        //从下到上
        for (int i = bottom; i >= top; --i) {
            cout << array[i * cols + right] << " ";
        }
        if (--right < left) {
            break;
        }
        //从右到左
        for (int i = right; i >= left; --i) {
            cout << array[top * cols + i] << " ";
        }
        if (++top > bottom) {
            break;
        }
    }
    /**************** TODO-END ****************/
}

int main()
{
    const int max_rows = 20, max_cols = 20;
    int rows = 0, cols = 0;
    cin >> rows >> cols;

    // 用一维数组存储矩阵
    int array[max_rows * max_cols] = {};

    // 读取矩阵
    for (int i = 0; i < rows * cols; ++i) {
        cin >> array[i];
    }

    anticlockwise_print(array, rows, cols);

    return 0;
}