#include <iostream>
#include <string>
#include <limits>
#include <cctype>
using namespace std;
/*复读整数，并拒绝错误输入*/
istream& f(istream& in)
{
    string input;
    int num;

    while (true)
    {
        in >> ws; //忽略空白字符
        if (in.eof())
        {
            break;
        }
        in >> input;
        //检查是否为结束标志
        if (input == "-1")
        {
            cout << "------程序结束------" << endl;
            break;
        }
        //检查是否包含小数点或字母
        bool isIllegal = false;
        for (char ch : input)
        {
            if (ch == '.' || isalpha(ch))
            {
                isIllegal = true;
                break;
            }
        }
        //检查是否超出int的范围（我是真的不知道怎么整了...）
        if (!isIllegal)
        {
            try
            {
                size_t pos;
                num = stoi(input, &pos);
                if (pos != input.length())
                {
                    isIllegal = true;
                }
            }
            catch (out_of_range&)
            {
                isIllegal = true;
            }
            catch (invalid_argument&)
            {
                isIllegal = true;
            }
        }

        if (isIllegal)
        {
            cout << "Illegal" << endl;
        }
        else
        {
            cout << "你说了:" << num << endl;
        }
    }

    in.clear(); //清除所有错误标志，使流处于有效状态
    return in;
}

int main()
{
    cout << "请输入一些整数，以-1或Ctrl+Z结束。" << endl;
    f(cin);
    return 0;
}
