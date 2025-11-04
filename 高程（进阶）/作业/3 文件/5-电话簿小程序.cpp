#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;

//验证号码是否合法
bool valid(const string& number)
{
    //检查号码长度是否为11位
    if (number.length() != 11)
        return false;
    //检查号码是否以'1'开头
    if (number[0] != '1')
        return false;
    //检查号码的第二位是否在'3'到'9'之间
    if (number[1] < '3' || number[1] > '9')
        return false;
    //检查号码的每一位是否都是数字
    for (char c : number)
    {
        if (!isdigit(c))
            return false;
    }
    return true;
}

//从文件中查找以指定前三位开头的最大电话号码
string findMaxPhoneNumber(const string& prefix) {
    ifstream file("messy.content"); //打开文件
    if (!file.is_open())
    {
        cerr << "无法打开文件" << endl;
        return "";
    }
    string line;
    string maxNumber = ""; //存储最大电话号码
    //逐行读取文件内容
    while (getline(file, line))
    {
        istringstream iss(line); //使用字符串流对象处理每行内容
        string number;
        //逐个读取每个单词
        while (iss >> number)
        {
            //检查号码是否合法且是否以指定前三位开头
            if (valid(number) && number.substr(0, 3) == prefix)
            {
                //更新最大电话号码
                if (number > maxNumber)
                {
                    maxNumber = number;
                }
            }
        }
    }
    file.close(); //关闭文件
    return maxNumber;
}

int main()
{
    string prefix;
    cout << "请输入前三位号码: ";
    cin >> prefix; //获取用户输入的前三位号码

    string result = findMaxPhoneNumber(prefix); //查找最大电话号码
    if (!result.empty())
    {
        cout << "最大电话号码是: " << result << endl;
    }
    else
    {
        cout << "未找到符合条件的电话号码" << endl;
    }
    return 0;
}