#include <iostream>
#define ARRAY_LENGTH 10
using namespace std;

/****************** TODO ******************/
//实现前若干个元素逆置的函数
void reverse_array(int arr[], int right)
{
	int left = 0;
	right -= 1;//初始，0和right-1交换，1和right-2交换，直到left>=right...
    while (left < right)
    {
		int temp = arr[left];
		arr[left] = arr[right];
		arr[right] = temp;
		left++;
		right--;
	}
}
/**************** TODO-END ****************/

// 下面是一个使用你所编写函数的样例程序
int main()
{
    int arr[ARRAY_LENGTH] = { 1, 8, -3, 9, 2, 0, -1, 7, 7, 6 };

    int right = 0;
    cin >> right;

    reverse_array(arr, right);

    // 输出逆置后结果
    cout << "前" << right << "个元素逆置后的结果为：" << endl;
    for (int i = 0; i < ARRAY_LENGTH; ++i)
    {
        cout << arr[i] << ' ';
    }
    cout << endl;

    return 0;
}