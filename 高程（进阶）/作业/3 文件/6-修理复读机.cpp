#include <iostream>
#include <fstream>
using namespace std;

int main() 
{
    ifstream inputFile("noise.txt");
    if (!inputFile) 
    {
        cout << "无法打开文件 noise.txt" << endl;
        return 1;
    }

    const int MAX_SIZE = 2048; // 假设最大字符数为2048
    char originalContent[MAX_SIZE];
    int index = 0;
    char buffer[3];

    while (inputFile.read(buffer, 3) && index < MAX_SIZE)
    {
        originalContent[index++] = buffer[0];
    }
    //若长度不是3的倍数
    if (inputFile.gcount() > 0 && index < MAX_SIZE)
    {
        originalContent[index++] = buffer[0];
    }
    inputFile.close();
    cout << "源字符串：" << endl;
    for (int i = 0; i < index; ++i) {
        cout << originalContent[i];
    }
    cout << endl;
    return 0;
}