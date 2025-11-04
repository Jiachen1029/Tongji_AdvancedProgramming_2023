//这个程序实现了一个简单的文件压缩和解压缩工具
//压缩算法使用了LZ77算法，它通过查找重复的字符串模式来减少文件大小
//使用方法：输入文件地址、输出文件地址和命令（zip或unzip）
//经测试，ser.log文件压缩时间4s多，压缩率在30%左右
//通过调整窗口大小和前瞻缓冲区大小可以调整压缩率和压缩时间：
//窗口大小越大，压缩率越高，压缩时间越长
//前瞻缓冲区大小越大，压缩率越低，压缩时间越短
//当然也有可能出现负数压缩率，这个就要具体情况具体分析了

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <cstring>
#include <algorithm>
using namespace std;
using namespace std::chrono;

//压缩函数
void compress(const string& inputFile, const string& outputFile, double& compressionRate, double& duration);
//解压函数
void decompress(const string& inputFile, const string& outputFile, double& duration);

int main(int argc, char* argv[])
{
    string inputFile, outputFile, command;
    cout << "请输入输入文件地址：" << endl;
    cin >> inputFile;
    cout << "请输入输出文件地址：" << endl;
    cin >> outputFile;
    cout << "请输入zip或unzip" << endl;
    cin >> command;

    double compressionRate = 0.0;
    double duration = 0.0;

    if (command == "zip")
    {
        compress(inputFile, outputFile, compressionRate, duration);
        cout << "压缩率:" << compressionRate * 100 << "%" << endl;
        cout << "压缩时间:" << duration << "秒" << endl;
    }
    else if (command == "unzip")
    {
        decompress(inputFile, outputFile, duration);
        cout << "解压时间:" << duration << "秒" << endl;
    }
    else
    {
        cout << "输入错误！" << endl;
        return 1;
    }
    return 0;
}

void compress(const string& inputFile, const string& outputFile, double& compressionRate, double& duration)
{
    ifstream in(inputFile, ios::binary | ios::ate); //打开输入文件
    ofstream out(outputFile, ios::binary); //打开输出文件

    if (!in.is_open() || !out.is_open())
    {
        cerr << "Error opening file." << endl;
        return;
    }

    auto start = high_resolution_clock::now(); //记录开始时间

    size_t inputSize = in.tellg(); //获取输入文件大小
    in.seekg(0, ios::beg); //重置文件指针到文件开头
    char* inputBuffer = new char[inputSize]; //分配输入缓冲区
    in.read(inputBuffer, inputSize); //读取输入文件内容

    size_t outputBufferSize = inputSize * 2; //预估输出缓冲区大小
    char* outputBuffer = new char[outputBufferSize]; //分配输出缓冲区
    size_t outputIndex = 0; //输出缓冲区索引

    size_t windowSize = 2048; //窗口大小
    size_t lookaheadBufferSize = 32; //前瞻缓冲区大小

    for (size_t i = 0; i < inputSize;)
    {
        size_t matchLength = 0;
        size_t matchDistance = 0;

        //查找最长匹配
        for (size_t j = max<size_t>(0, i - windowSize); j < i; ++j)
        {
            size_t k = 0;
            while (k < lookaheadBufferSize && i + k < inputSize && inputBuffer[j + k] == inputBuffer[i + k])
            {
                ++k;
            }
            if (k > matchLength)
            {
                matchLength = k;
                matchDistance = i - j;
            }
        }
        if (matchLength >= 3)
        {
            //如果找到匹配，写入匹配距离和长度
            if (outputIndex + 1 + sizeof(size_t) * 2 > outputBufferSize)
            {
                outputBufferSize *= 2;
                char* newOutputBuffer = new char[outputBufferSize];
                memcpy(newOutputBuffer, outputBuffer, outputIndex);
                delete[] outputBuffer;
                outputBuffer = newOutputBuffer;
            }
            outputBuffer[outputIndex++] = 0;
            memcpy(outputBuffer + outputIndex, &matchDistance, sizeof(matchDistance));
            outputIndex += sizeof(matchDistance);
            memcpy(outputBuffer + outputIndex, &matchLength, sizeof(matchLength));
            outputIndex += sizeof(matchLength);
            i += matchLength;
        }
        else
        {
            //如果没有找到匹配，写入字节
            if (outputIndex + 2 > outputBufferSize)
            {
                outputBufferSize *= 2;
                char* newOutputBuffer = new char[outputBufferSize];
                memcpy(newOutputBuffer, outputBuffer, outputIndex);
                delete[] outputBuffer;
                outputBuffer = newOutputBuffer;
            }
            outputBuffer[outputIndex++] = 1;
            outputBuffer[outputIndex++] = inputBuffer[i++];
        }
    }

    out.write(outputBuffer, outputIndex); //写入输出文件

    auto end = high_resolution_clock::now(); //记录结束时间
    duration = duration_cast<chrono::duration<double>>(end - start).count(); //计算压缩时间

    compressionRate = 1.0 - static_cast<double>(outputIndex) / static_cast<double>(inputSize); //计算压缩率

    delete[] inputBuffer; //释放输入缓冲区
    delete[] outputBuffer; //释放输出缓冲区
    in.close(); //关闭输入文件
    out.close(); //关闭输出文件
}

void decompress(const string& inputFile, const string& outputFile, double& duration)
{
    ifstream in(inputFile, ios::binary | ios::ate); //打开输入文件
    ofstream out(outputFile, ios::binary); //打开输出文件

    if (!in.is_open() || !out.is_open())
    {
        cerr << "Error opening file." << endl;
        return;
    }

    auto start = high_resolution_clock::now(); //记录开始时间

    size_t inputSize = in.tellg(); //获取输入文件大小
    in.seekg(0, ios::beg); //重置文件指针到文件开头
    char* inputBuffer = new char[inputSize]; //分配输入缓冲区
    in.read(inputBuffer, inputSize); //读取输入文件内容

    size_t outputBufferSize = inputSize * 4; //预估解压后的大小
    char* outputBuffer = new char[outputBufferSize]; //分配输出缓冲区
    memset(outputBuffer, 0, outputBufferSize); //初始化 outputBuffer
    size_t outputIndex = 0; //输出缓冲区索引

    for (size_t i = 0; i < inputSize;)
    {
        char flag = inputBuffer[i++]; //读取标志位
        if (flag == 0)
        {
            //读取匹配距离和长度
            size_t matchDistance = *reinterpret_cast<size_t*>(inputBuffer + i);
            i += sizeof(size_t);
            size_t matchLength = *reinterpret_cast<size_t*>(inputBuffer + i);
            i += sizeof(size_t);

            //检查输出缓冲区大小
            if (outputIndex + matchLength > outputBufferSize)
            {
                outputBufferSize *= 2;
                char* newOutputBuffer = new char[outputBufferSize];
                memcpy(newOutputBuffer, outputBuffer, outputIndex);
                delete[] outputBuffer;
                outputBuffer = newOutputBuffer;
            }

            //写入匹配的字符串
            size_t currentPos = outputIndex;
            for (size_t j = 0; j < matchLength; ++j)
            {
                if (currentPos - matchDistance + j < outputIndex)
                {
                    outputBuffer[outputIndex++] = outputBuffer[currentPos - matchDistance + j];
                }
                else
                {
                    cerr << "Error: Attempt to access uninitialized memory." << endl;
                    delete[] inputBuffer;
                    delete[] outputBuffer;
                    return;
                }
            }
        }
        else
        {
            //写入字节
            if (outputIndex + 1 > outputBufferSize)
            {
                outputBufferSize *= 2;
                char* newOutputBuffer = new char[outputBufferSize];
                memcpy(newOutputBuffer, outputBuffer, outputIndex);
                delete[] outputBuffer;
                outputBuffer = newOutputBuffer;
            }
            if (i < inputSize)
            {
                outputBuffer[outputIndex++] = inputBuffer[i++];
            }
            else
            {
                cerr << "Error: Attempt to read invalid data from inputBuffer." << endl;
                delete[] inputBuffer;
                delete[] outputBuffer;
                return;
            }
        }
    }

    out.write(outputBuffer, outputIndex); //写入输出文件

    auto end = high_resolution_clock::now(); //记录结束时间
    duration = duration_cast<chrono::duration<double>>(end - start).count(); //计算解压时间

    delete[] inputBuffer; //释放输入缓冲区
    delete[] outputBuffer; //释放输出缓冲区
    in.close(); //关闭输入文件
    out.close(); //关闭输出文件
}