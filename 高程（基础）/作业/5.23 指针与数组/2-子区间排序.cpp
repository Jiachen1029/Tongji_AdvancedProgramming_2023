#include <iostream>
using namespace std;

void partial_sort(int* start, int* end)
{
    /****************** TODO ******************/
    //如果起始位置超过了终点位置
    if (start >= end) {
		return;
	}
    //左闭右开区间进行排序
    for (int* i = start; i < end - 1; i++) 
    {
        for (int* j = i + 1; j < end; j++)
        {
            if (*i > *j)
            {
				int temp = *i;
				*i = *j;
				*j = temp;
			}
		}
    }
    /**************** TODO-END ****************/
}

int main()
{
    const int array_length = 10;
    int arr[array_length] = {};

    // 输入数组
    for (int i = 0; i < array_length; ++i) {
        cin >> arr[i];
    }

    // 输入左右边界
    int left = 0, right = 0;
    cin >> left >> right;

    // 调用函数
    partial_sort(arr + left, arr + right);

    // 输出数组
    for (int i = 0; i < array_length; ++i) {
        cout << arr[i] << ' ';
    }
    cout << endl;

    return 0;
}