#include <iostream>
#include <cctype>
using namespace std;

// 整数转为二进制
void itobs(int num, char* buffer) {
    for (int i = 31; i >= 0; i--) {
        int bitnum = 1 << i;
        if (num & bitnum) //检查num的i位是否为1
        { 
            buffer[31 - i] = '1';
        }
        else {
            buffer[31 - i] = '0';
        }
    }
    buffer[32] = '\0'; 
}
// 每八位加一个空格
void printSpaces(const char* binary) {
    for (int i = 0; i < 32; i++) {
        cout << binary[i];
        if ((i + 1) % 8 == 0 && i != 31) {
            cout << ' ';
        }
    }
}
int main() {
    int num;
    char buffer[33]; // 存储二进制
    cout << "输入一些整数：" << endl;
    while (true) {
        if (!(cin >> num))// 检查输入是否为整数
        { 
            if (cin.fail()) 
            {
                cin.clear(); //清除错误状态
                char ch;
                cin >> ch;
                if (isalpha(ch))//检查是否为字母
                { 
                    cout << "------程序结束------" << endl;
                    break;
                }
                while (cin.get() != '\n'); //丢弃缓冲区中的字符
                continue;
            }
        }
        itobs(num, buffer);
        cout << num << " 的二进制是：";
        printSpaces(buffer);
        cout << endl;
    }
    return 0;
}