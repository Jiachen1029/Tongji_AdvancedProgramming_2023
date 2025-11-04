#include <iostream>
#include <graphics.h>
#include <easyx.h>
#include <stack>
using namespace std;

// 定义保存移动信息的结构体
struct Move {
    int x1, y1; // 移动前的坐标
    int x2, y2; // 移动后的坐标
    int xOver, yOver; // 被跳过的棋子的坐标
};
stack<Move> moveHistory; // 创建保存移动历史的栈


//棋盘类：
//初始化孔明棋棋盘——0：空 1：棋子 2：选中的棋子 3：可移动的位置 4：非游戏区域
int board[7][7] = {
    {4,4,1,1,1,4,4},
    {4,4,1,1,1,4,4},
    {1,1,1,1,1,1,1},
    {1,1,1,0,1,1,1},
    {1,1,1,1,1,1,1},
    {4,4,1,1,1,4,4},
    {4,4,1,1,1,4,4} };


//计算类：
//计算剩余棋子
int countChessPieces()
{
    int count = 0;
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (board[i][j] == 1 || board[i][j] == 2)
            {
                count++;
            }
        }
    }
    return count;
}
//计算可移动位置
void countMove(int x, int y)
{
    if (board[x][y] == 2)
    {
        if (x - 2 >= 0 && board[x - 1][y] == 1 && board[x - 2][y] == 0)
        {
            board[x - 2][y] = 3;
        }
        if (x + 2 < 7 && board[x + 1][y] == 1 && board[x + 2][y] == 0)
        {
            board[x + 2][y] = 3;
        }
        if (y - 2 >= 0 && board[x][y - 1] == 1 && board[x][y - 2] == 0)
        {
            board[x][y - 2] = 3;
        }
        if (y + 2 < 7 && board[x][y + 1] == 1 && board[x][y + 2] == 0)
        {
            board[x][y + 2] = 3;
        }
    }
}
//移动棋子并将移动信息压入栈中
void moveChess(int x1, int y1, int x2, int y2)
{
    if (board[x1][y1] == 2 && board[x2][y2] == 3)
    {
        Move move = { x1, y1, x2, y2, (x1 + x2) / 2, (y1 + y2) / 2 };
        moveHistory.push(move); // 将移动信息压入栈中
        board[x1][y1] = 0;
        board[x2][y2] = 1;
        board[(x1 + x2) / 2][(y1 + y2) / 2] = 0;
    }
}
//选中棋子并计算可移动位置
void selectChess(int x, int y)
{
    board[x][y] = 2;
    countMove(x, y);
}
// 悔棋
void undoMove()
{
    if (!moveHistory.empty())
    {
        Move lastMove = moveHistory.top(); // 获取最后一次移动信息
        moveHistory.pop(); // 从栈中移除
        // 恢复棋盘状态
        board[lastMove.x1][lastMove.y1] = 1; // 恢复移动前的棋子
        board[lastMove.x2][lastMove.y2] = 0; // 清除移动后的位置
        board[lastMove.xOver][lastMove.yOver] = 1; // 恢复被跳过的棋子
    }
}

//判断胜利
bool judgeWin()
{
    if (countChessPieces() == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}
//判断失败（检查能否继续移动）
bool canMove(int x, int y)
{
    // 检查向左移动
    if (x - 2 >= 0 && (board[x - 1][y] == 1 || board[x - 1][y] == 2) && (board[x - 2][y] == 0 || board[x - 2][y] == 3))
    {
        return true;
    }
    // 检查向右移动
    if (x + 2 < 7 && (board[x + 1][y] == 1 || board[x + 1][y] == 2) && (board[x + 2][y] == 0 || board[x + 2][y] == 3))
    {
        return true;
    }
    // 检查向上移动
    if (y - 2 >= 0 && (board[x][y - 1] == 1 || board[x][y - 1] == 2) && (board[x][y - 2] == 0 || board[x][y - 2] == 3))
    {
        return true;
    }
    // 检查向下移动
    if (y + 2 < 7 && (board[x][y + 1] == 1 || board[x][y + 1] == 2) && (board[x][y + 2] == 0 || board[x][y + 2] == 3))
    {
        return true;
    }
    return false;
}
bool judgeLose()
{
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            // 对于每个1号、2号棋子，检查是否有合法的移动
            if (board[i][j] == 1 || board[i][j] == 2)
            {
                if (canMove(i, j))
                {
                    return false; // 如果找到至少一个棋子有合法移动，游戏未失败
                }
            }
        }
    }
    return true; // 如果没有找到任何合法移动，游戏失败
}


//绘制类：
//绘制棋盘
void drawChessBoard()
{
    //绘制棋盘线条
    //棋盘7行7列，每个格子边长为80，但是四个角各2行2列格子不绘制
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (board[i][j] == 4)
            {
                continue;
            }
            else
            {
                if ((i + j) % 2 == 0)
                    setfillcolor(YELLOW); // 偶数格黄色
                else
                    setfillcolor(RGB(255, 165, 0)); // 奇数格橙色
                // 绘制格子
                setlinestyle(PS_SOLID, 3);//粗一点
                setlinecolor(WHITE);
                fillrectangle(120 + j * 80, 120 + i * 80, 200 + j * 80, 200 + i * 80);
                // 恢复线条样式为默认
                setlinestyle(PS_SOLID, 1);
            }
        }
    }

}
//绘制棋子
void drawChessPieces()
{
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            setlinestyle(PS_SOLID, 1);
            if (board[i][j] == 1)
            {
                setfillcolor(RED);
                fillcircle(160 + j * 80, 160 + i * 80, 30);
            }
            else if (board[i][j] == 2)
            {
                setfillcolor(RGB(255, 102, 102));//浅红色
                fillcircle(160 + j * 80, 160 + i * 80, 30);
            }
            else if (board[i][j] == 3)
            {
                setfillcolor(GREEN);
                fillcircle(160 + j * 80, 160 + i * 80, 15);
            }
        }
    }
}
//绘制控制按钮
void drawButtons()
{
    // 设置填充颜色为黄色，线条颜色为橙色
    setfillcolor(YELLOW);
    setlinecolor(RGB(255, 165, 0));
    // 设置文字样式
    LOGFONT f;
    gettextstyle(&f);                     // 获取当前字体设置
    _tcscpy_s(f.lfFaceName, _T("等线"));  // 设置字体为等线
    f.lfHeight = 36;                      // 增大字体大小
    setbkmode(TRANSPARENT); // 设置文字背景为透明
    settextcolor(BLACK);    // 设置文字颜色为黑色
    f.lfQuality = ANTIALIASED_QUALITY;    // 设置抗锯齿效果
    settextstyle(&f);                     // 应用字体设置
    // 绘制圆角矩形按钮
    fillroundrect(800, 50, 900, 100, 10, 10);
    outtextxy(815, 60, _T("退出"));
    fillroundrect(800, 150, 900, 200, 10, 10);
    outtextxy(815, 160, _T("重玩"));
    fillroundrect(800, 250, 900, 300, 10, 10);
    outtextxy(815, 260, _T("悔棋"));
    fillroundrect(800, 350, 900, 400, 10, 10);
    outtextxy(815, 360, _T("规则"));
    fillroundrect(800, 450, 955, 500, 10, 10);
    outtextxy(810, 455, _T("随机残局"));
}
//绘制显示剩余棋子
void drawCount()
{
    LOGFONT f;
    gettextstyle(&f);                     // 获取当前字体设置
    _tcscpy_s(f.lfFaceName, _T("等线"));  // 设置字体为等线
    f.lfHeight = 36;                      // 设置字体大小为36
    f.lfQuality = ANTIALIASED_QUALITY;    // 设置抗锯齿效果
    settextstyle(&f);                     // 应用字体设置
    settextcolor(BLACK);                  // 设置文字颜色为黑色
    setbkmode(TRANSPARENT);               // 设置文字背景为透明
    // 获取剩余棋子数量
    int count = countChessPieces();
    TCHAR str[100];
    _stprintf_s(str, _T("剩余棋子：%d"), count); // 格式化字符串，包含剩余棋子数量
    // 绘制文字
    outtextxy(30, 30, str); // 输出包含剩余棋子数量的字符串
}
//绘制“孔明棋”标题
void drawTitle()
{
    LOGFONT f;
    gettextstyle(&f);                     // 获取当前字体设置
    _tcscpy_s(f.lfFaceName, _T("汉仪尚巍手书W")); // 设置字体
    f.lfHeight = 160;                      // 设置字体大小为48
    f.lfQuality = ANTIALIASED_QUALITY;    // 设置抗锯齿效果
    settextstyle(&f);                     // 应用字体设置
    settextcolor(BLACK);                  // 设置文字颜色为黑色
    setbkmode(TRANSPARENT);               // 设置文字背景为透明
    outtextxy(600, 560, _T("孔明棋"));
}
//显示主要界面
void drawGameInterface()
{
    BeginBatchDraw();
    EndBatchDraw();//减少卡顿
    cleardevice();
    drawChessBoard();
    drawChessPieces();
    drawButtons();
    drawTitle();
    drawCount();
}

//界面类：
// 规则界面：
void rule()
{
    initgraph(850, 450, 1);
    setbkcolor(RGB(255, 210, 220)); //淡粉色
    cleardevice();
    // 设置文字样式
    LOGFONT f;
    gettextstyle(&f);                     // 获取当前字体设置
    _tcscpy_s(f.lfFaceName, _T("隶书"));  // 设置字体
    f.lfHeight = 32;                      // 设置字体大小为36
    f.lfQuality = ANTIALIASED_QUALITY;    // 设置抗锯齿效果
    settextstyle(&f);                     // 应用字体设置
    settextcolor(BLACK);                  // 设置文字颜色为黑色
    setbkmode(TRANSPARENT);               // 设置文字背景为透明
    // 绘制规则界面
    outtextxy(50, 40, _T("孔明棋规则："));
    outtextxy(50, 80, _T("1. 棋子为红色圆形，选中的位置为浅红色圆形，可移"));
    outtextxy(50, 120, _T("    动的位置为绿色圆形。"));
    outtextxy(50, 160, _T("2. 棋子只能横向或纵向移动，且只能跳过一个棋子。"));
    outtextxy(50, 200, _T("3. 棋子移动后，被跳过的棋子会消失。"));
    outtextxy(50, 240, _T("4. 棋子移动后，若无法继续移动，则游戏失败。"));
    outtextxy(50, 280, _T("5. 如果只剩下一枚棋子，则游戏胜利。"));
    outtextxy(50, 320, _T("6. 通过悔棋按钮可以实现悔棋。"));
    outtextxy(50, 360, _T("7. 关闭窗口请点击“返回游戏”>>"));

    // 绘制一个“返回游戏”按钮
    setfillcolor(YELLOW);
    setlinecolor(RGB(255, 165, 0));
    fillroundrect(550, 360, 700, 400, 10, 10);
    _tcscpy_s(f.lfFaceName, _T("等线"));
    settextcolor(RED);                  // 设置文字颜色为黑色
    setbkmode(TRANSPARENT);               // 设置文字背景为透明
    settextstyle(&f);                     // 应用字体设置
    outtextxy(560, 365, _T("返回游戏"));
    // 消息循环，等待用户操作
    bool running = true;
    while (running)
    {
        ExMessage m;        // 获取鼠标消息
        if (peekmessage(&m, EM_MOUSE))
        {
            // 检查是否点击了“返回游戏”按钮的区域
            if (m.message == WM_LBUTTONDOWN && m.x >= 550 && m.x <= 700 && m.y >= 360 && m.y <= 400)
            {
                running = false; // 结束循环
            }
        }
    }
    // 关闭规则窗口后重新绘制游戏界面
    initgraph(1000, 760, 0);
    setbkcolor(RGB(255, 210, 220)); //淡粉色
    drawGameInterface();
}


// 处理鼠标点击事件
pair<int, int> handleMouseClick()
{
    MOUSEMSG m = GetMouseMsg();
    switch (m.uMsg)
    {
    case WM_LBUTTONDOWN: // 如果是左键按下
        return { m.x, m.y }; // 返回鼠标点击的屏幕坐标
    }
    return { -1, -1 }; // 如果没有点击，返回无效坐标
}
int main()
{
    // 初始化图形窗口，窗口大小为1000*760，背景白色
    initgraph(1000, 760, 1);
    setbkcolor(RGB(255, 210, 220)); //淡粉色
    //绘制棋盘，棋子和控制按钮
    drawGameInterface();
    int moregame = 0;
    //处理鼠标点击并执行操作
    while (true)
    {
        pair<int, int> clickPos = handleMouseClick();
        if (clickPos.first != -1) // 检查是否有有效的点击
        {
            //退出按钮
            if (clickPos.first >= 800 && clickPos.first <= 900 && clickPos.second >= 50 && clickPos.second <= 100)
            {
                break; // 退出游戏
            }
            //重玩按钮
            else if (clickPos.first >= 800 && clickPos.first <= 900 && clickPos.second >= 150 && clickPos.second <= 200)
            {

                int refreshboard[7][7] = {
                   {4,4,1,1,1,4,4},
                   {4,4,1,1,1,4,4},
                   {1,1,1,1,1,1,1},
                   {1,1,1,0,1,1,1},
                   {1,1,1,1,1,1,1},
                   {4,4,1,1,1,4,4},
                   {4,4,1,1,1,4,4} };
                //重新初始化棋盘
                for (int i = 0; i < 7; i++)
                {
                    for (int j = 0; j < 7; j++)
                    {
                        board[i][j] = refreshboard[i][j];
                    }
                }
                // 重新绘制棋盘和棋子
                cleardevice();
                drawChessBoard();
                drawChessPieces();
                drawButtons();
                drawTitle();
                drawCount();
            }
            //悔棋按钮
            else if (clickPos.first >= 800 && clickPos.first <= 900 && clickPos.second >= 250 && clickPos.second <= 300)
            {
                undoMove();
            }
            //规则按钮
            else if (clickPos.first >= 800 && clickPos.first <= 900 && clickPos.second >= 350 && clickPos.second <= 400)
            {
                rule();
            }
            //随机残局按钮
            else if (clickPos.first >= 800 && clickPos.first <= 900 && clickPos.second >= 450 && clickPos.second <= 500)
            {
                if (moregame % 5 == 0)
                {
                    int refreshboard[7][7] = {
                      {4,4,0,0,0,4,4},
                      {4,4,0,0,0,4,4},
                      {0,0,0,0,0,0,0},
                      {0,0,0,0,0,0,0},
                      {0,1,1,0,1,1,0},
                      {4,4,1,1,1,4,4},
                      {4,4,0,1,0,4,4} };
                    //重新初始化棋盘
                    for (int i = 0; i < 7; i++)
                    {
                        for (int j = 0; j < 7; j++)
                        {
                            board[i][j] = refreshboard[i][j];
                        }
                    }
                }
                else if (moregame % 5 == 1)
                {
                    int refreshboard[7][7] = {
					  {4,4,1,1,1,4,4},
					  {4,4,0,1,1,4,4},
					  {0,0,0,0,0,0,1},
					  {0,0,1,1,1,1,1},
					  {0,1,1,0,0,1,1},
					  {4,4,1,0,1,4,4},
					  {4,4,0,1,1,4,4} };
                    //重新初始化棋盘
                    for (int i = 0; i < 7; i++)
                    {
                        for (int j = 0; j < 7; j++)
                        {
                            board[i][j] = refreshboard[i][j];
                        }
                    }
				}
                else if (moregame % 5 == 2)
                {
                    int refreshboard[7][7] = {
					  {4,4,0,0,0,4,4},
					  {4,4,0,0,0,4,4},
					  {0,0,1,0,1,0,0},
					  {0,0,1,1,1,0,0},
					  {0,0,0,1,0,0,0},
					  {4,4,1,1,1,4,4},
					  {4,4,0,0,0,4,4} };
                    //重新初始化棋盘
                    for (int i = 0; i < 7; i++)
                    {
                        for (int j = 0; j < 7; j++)
                        {
                            board[i][j] = refreshboard[i][j];
                        }
                    }
				}
                else if (moregame % 5 == 3)
                {
                    int refreshboard[7][7] = {
					  {4,4,0,0,0,4,4},
					  {4,4,0,0,0,4,4},
					  {0,0,0,1,1,1,0},
					  {0,0,0,1,1,1,0},
					  {0,0,0,1,0,0,0},
					  {4,4,0,1,0,4,4},
					  {4,4,0,1,0,4,4} };
                    //重新初始化棋盘
                    for (int i = 0; i < 7; i++)
                    {
                        for (int j = 0; j < 7; j++)
                        {
                            board[i][j] = refreshboard[i][j];
                        }
                    }
				}
                else if (moregame % 5 == 4)
                {
                    int refreshboard[7][7] = {
                      {4,4,0,0,0,4,4},
                      {4,4,0,0,0,4,4},
                      {0,0,0,0,1,0,0},
                      {0,0,1,1,1,1,0},
                      {0,0,0,0,1,0,0},
                      {4,4,0,0,0,4,4},
                      {4,4,0,0,0,4,4} };
                    //重新初始化棋盘
                    for (int i = 0; i < 7; i++)
                    {
                        for (int j = 0; j < 7; j++)
                        {
                            board[i][j] = refreshboard[i][j];
                        }
                    }
                }
                moregame++;
                // 重新绘制棋盘和棋子
                cleardevice();
                drawChessBoard();
                drawChessPieces();
                drawButtons();
                drawTitle();
                drawCount();

            }
            //点击棋盘
            MOUSEMSG m = GetMouseMsg();
            int x = (m.y - 120) / 80; // 计算行坐标
            int y = (m.x - 120) / 80; // 计算列坐标
            if (x >= 0 && x < 7 && y >= 0 && y < 7) // 检查坐标是否在棋盘范围内
            {
                //选中1号棋子，变成2号棋子，其他棋子变回1号棋子，并且计算可移动位置变成3号棋子
                if (board[x][y] == 1)
                {
                    //把其他的2号棋子变成1号棋子，3号棋子变成0号棋子
                    for (int i = 0; i < 7; i++)
                    {
                        for (int j = 0; j < 7; j++)
                        {
                            if (board[i][j] == 2)
                            {
                                board[i][j] = 1;
                            }
                            else if (board[i][j] == 3)
                            {
                                board[i][j] = 0;
                            }
                        }
                    }
                    selectChess(x, y);//改变选中的1号棋子为2号棋子，同时计算可移动位置
                }
                //点选3号棋子，移动棋子，中间的棋子消失，同时去掉其他的3号棋子
                else if (board[x][y] == 3)
                {
                    for (int i = 0; i < 7; i++)
                    {
                        for (int j = 0; j < 7; j++)
                        {
                            if (board[i][j] == 2)
                            {
                                moveChess(i, j, x, y);
                            }
                        }
                    }
                    //去掉其他的3号棋子
                    for (int i = 0; i < 7; i++)
                    {
                        for (int j = 0; j < 7; j++)
                        {
                            if (board[i][j] == 3)
                            {
                                board[i][j] = 0;
                            }
                        }
                    }
                }
            }
            // 重新绘制棋盘和棋子
            drawGameInterface();
            //判断成功失败
            if (judgeWin())
            {
                MessageBox(GetHWnd(), _T("恭喜你，游戏胜利！"), _T("游戏结束"), MB_OK);
                break;
            }
            if (judgeLose())
            {
                MessageBox(GetHWnd(), _T("很遗憾，游戏失败！"), _T("游戏结束"), MB_OK);
                break;
            }
        }
    }
    closegraph();// 关闭图形窗口
    return 0;
}