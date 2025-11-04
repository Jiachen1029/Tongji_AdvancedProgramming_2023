#include <iostream>
#include <conio.h>
#include <graphics.h>
#include "Game.h"
#include <cstdlib> //wcstombs所需的头文件
using namespace std;
string username;

void displayMenu() 
{
    cleardevice(); // 清屏
    //背景
    IMAGE maomaoImg;
    loadimage(&maomaoImg, _T("MAOMAO.png"), 680, 480);
    putimage(0, 0, &maomaoImg);
    //文本背景为透明
    setbkmode(TRANSPARENT);
    //绘制标题
    settextcolor(BLUE);
    settextstyle(80, 0, _T("华文彩云"), 0, 0, FW_BOLD, FALSE, FALSE, FALSE); 
    RECT titleRect = { 0, 20, 680, 120 }; 
    drawtext(_T("贪吃猫猫虫"), &titleRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    // 设置按钮字体样式
    settextstyle(30, 0, _T("等线"));
    // 定义按钮区域和标签
    RECT buttons[5] = 
    {
        {240, 160, 440, 190},
        {240, 210, 440, 240},
        {240, 260, 440, 290},
        {240, 310, 440, 340},
        {240, 360, 440, 390}
    };
    LPCTSTR labels[5] =
    {
        _T("入门版"),
        _T("进阶版"),
        _T("高级版"),
        _T("历史记录"),
        _T("退出游戏")
    };
    // 绘制按钮
    for (int i = 0; i < 5; ++i)
    {
        // 绘制按钮背景
        setfillcolor(LIGHTBLUE);
        solidrectangle(buttons[i].left, buttons[i].top, buttons[i].right, buttons[i].bottom);

        // 绘制按钮文本，居中显示
        settextcolor(WHITE);
        drawtext(labels[i], &buttons[i], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }
    FlushBatchDraw();
}

int getMenuChoice() 
{
    while (true) 
    {
        if (MouseHit()) 
        {
            MOUSEMSG msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN)
            {
                //判断鼠标点击是否在按钮区域内
                RECT buttons[5] = 
                {
                    {240, 160, 440, 190},
                    {240, 210, 440, 240},
                    {240, 260, 440, 290},
                    {240, 310, 440, 340},
                    {240, 360, 440, 390}
                };
                for (int i = 0; i < 5; ++i)
                {
                    if (msg.x >= buttons[i].left && msg.x <= buttons[i].right &&
                        msg.y >= buttons[i].top && msg.y <= buttons[i].bottom) 
                    {
                        return i + 1;
                    }
                }
            }
        }
        FlushBatchDraw(); //刷新屏幕
    }
}

void runGame(GameMode mode)
{
    Game game(mode, username);
    game.start();
}

int main() 
{
    initgraph(680, 480); // 初始化图形窗口
    setbkcolor(WHITE);   // 设置背景颜色为白色
    cleardevice();       // 清屏以应用背景颜色

    // 弹出输入框获取用户名
    if (username.empty()) {
        TCHAR userInput[50] = _T(""); // 定义一个缓冲区存储输入的用户名
        InputBox(userInput, 50, _T("请输入用户名："), _T("用户名输入"));

        // 将 TCHAR* 转换为 std::string，使用安全的 wcstombs_s 函数
        char mbstr[100];
        size_t convertedChars = 0;
        wcstombs_s(&convertedChars, mbstr, sizeof(mbstr), userInput, _TRUNCATE);
        username = mbstr;
    }

    while (true) 
    {
        displayMenu();
        int choice = getMenuChoice();

        if (choice == 1) 
        {
            runGame(GameMode::BASIC);
        }
        else if (choice == 2) 
        {
            runGame(GameMode::INTERMEDIATE);
        }
        else if (choice == 3)
        {
            runGame(GameMode::ADVANCED);
        }
        else if (choice == 4) 
        {
            Game game(GameMode::BASIC, username); // 创建一个临时游戏对象来显示历史记录
            game.displayHistory();
            game.handleHistoryInput(); // 处理用户输入
        }
        else if (choice == 5) 
        {
            break;
        }
        else {
            cout << "无效选择。" << endl;
        }
    }
    closegraph();
    return 0;
}