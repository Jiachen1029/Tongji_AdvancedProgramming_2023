#include <iostream>
#include <fstream>

using namespace std;

int main() 
{
    int numbers[20]{};
    //从标准输入读取 10 个整数
    cout << "请输入 10 个整数，每行一个：" << endl;
    for (int i = 0; i < 10; ++i) 
    {
        cin >> numbers[i];
    }
    //从文件读取
    ifstream infile("1.txt");
    if (!infile)
    {
        cerr << "无法打开文件 1.txt" << endl;
        return 1;
    }
    for (int i = 10; i < 20; ++i) 
    {
        infile >> numbers[i];
    }
    infile.close();
    //冒泡排序
    for (int i = 0; i < 20 - 1; ++i)
    {
        for (int j = 0; j < 20 - 1 - i; ++j) 
        {
            if (numbers[j] > numbers[j + 1])
            {
                int temp = numbers[j];
                numbers[j] = numbers[j + 1];
                numbers[j + 1] = temp;
            }
        }
    }
    //输出结果
    cout << "排序后的 20 个整数：" << endl;
    for (int i = 0; i < 20; ++i) 
    {
        cout << numbers[i] << " ";
    }
    cout << endl;
    return 0;
}