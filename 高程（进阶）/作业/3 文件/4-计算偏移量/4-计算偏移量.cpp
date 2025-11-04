#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream file("foo.bar", ios::binary);
    if (!file.is_open())
    {
        cout << "无法打开文件" << endl;
        return 1;
    }

    int lineCount = 0;
    int offset = 0;
    int currentOffset = 0;
    char ch;
    //存储偏移量
    int offsets[2048] = { 0 };

    //读取文件内容并计算偏移量
    cout << "-*以下是文件内容*-" << endl;
    while (file.get(ch))
    {
        cout << ch; //输出文件内容
        if (ch == '\n')
        {
            offsets[lineCount + 1] = currentOffset + 1;
            lineCount++;
        }
        currentOffset++;
    }

    //如果文件最后没有换行符，手动增加最后一行的偏移量
    if (currentOffset > 0 && ch != '\n')
    {
        currentOffset++; //加上最后一行的换行符
        lineCount++;
        offsets[lineCount] = currentOffset;
    }

    file.close();

    //输出总行数和每行的偏移量
    cout << endl;
    cout << lineCount << " ";
    for (int i = 0; i <= lineCount; ++i)
    {
        cout << offsets[i];
        if (i != lineCount)
        {
            cout << " ";
        }
    }
    cout << endl;

    return 0;
}