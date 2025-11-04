#include <iostream>
#include <iomanip>
#include <graphics.h>
#include <math.h>
#include <conio.h>
#include <time.h>
#include <easyx.h>
using namespace std;

#ifndef PI
#define PI 3.14159265358979323846
#endif

class Clock
{
private:
    int prevHour, prevMinute, prevSecond;

public:
    Clock()
    {
        time_t now;
        struct tm t;
        time(&now);
        localtime_s(&t, &now);
        prevHour = t.tm_hour;
        prevMinute = t.tm_min;
        prevSecond = t.tm_sec;
    }

    void drawClock(int hour, int minute, int second, int millisecond)
    {
        //双缓冲
        BeginBatchDraw();
        //清除之前的画布
        cleardevice();
        //绘制表盘
        drawAntialiasedRing(320, 240, 200, 190); //表盘外圆环
        //绘制刻度
        //调整线条颜色和宽度
        setlinecolor(BLACK);
        setlinestyle(PS_SOLID, 5);
        for (int i = 0; i < 60; ++i)
        {
            double angle = i * PI / 30;
            int x1 = 320 + (int)(190 * cos(angle));
            int y1 = 240 - (int)(190 * sin(angle));
            int x2 = 320 + (int)((i % 5 == 0 ? 170 : 180) * cos(angle));
            int y2 = 240 - (int)((i % 5 == 0 ? 170 : 180) * sin(angle));
            line(x1, y1, x2, y2);
        }

        //绘制数字标记
        settextcolor(BLACK);
        settextstyle(40, 0, _T("Impact")); //调整字体大小为40
        for (int i = 1; i <= 12; ++i)
        {
            double angle = i * PI / 6 - PI / 2;
            int x = 325 + (int)(150 * cos(angle));
            int y = 240 + (int)(150 * sin(angle));
            TCHAR num[3];
            _stprintf_s(num, _T("%02d"), i); //使用%02d格式化为两位数
            outtextxy(x - 20, y - 20, num); //调整数字位置
        }

        //绘制中心点
        setfillcolor(BLACK);
        solidcircle(320, 240, 5);

        //绘制飘带
        drawTrail(hour, minute, second, millisecond);
        //绘制指针
        drawHands(hour, minute, second, millisecond);
        EndBatchDraw();
    }
    void init()
    {
        //初始化图形窗口
        initgraph(640, 640); //图形方式初始化
        //设置背景颜色为浅黄色
        setbkcolor(RGB(255, 255, 224));
        cleardevice();
        //绘制刻度
        for (int i = 0; i < 60; ++i)
        {
            double angle = i * PI / 30;
            int x1 = 320 + (int)(190 * cos(angle));
            int y1 = 240 - (int)(190 * sin(angle));
            int x2 = 320 + (int)((i % 5 == 0 ? 170 : 180) * cos(angle));
            int y2 = 240 - (int)((i % 5 == 0 ? 170 : 180) * sin(angle));
            line(x1, y1, x2, y2);
        }

        //绘制表盘
        setlinecolor(BLACK);
        setlinestyle(PS_SOLID, 2);
        drawAntialiasedRing(320, 240, 200, 190); //表盘外圆环

        //绘制数字标记
        settextcolor(BLACK);
        settextstyle(40, 0, _T("Impact")); //调整字体大小为40
        for (int i = 1; i <= 12; ++i)
        {
            double angle = i * PI / 6 - PI / 2;
            int x = 325 + (int)(150 * cos(angle));
            int y = 240 + (int)(150 * sin(angle));
            TCHAR num[3];
            _stprintf_s(num, _T("%02d"), i); //使用%02d格式化为两位数
            outtextxy(x - 20, y - 20, num); //调整数字位置
        }

        //绘制中心点
        setfillcolor(BLACK);
        solidcircle(320, 240, 5);
    }
    void drawAntialiasedRing(int xc, int yc, int outerRadius, int innerRadius)
    {
        for (int y = -outerRadius; y <= outerRadius; y++)
        {
            for (int x = -outerRadius; x <= outerRadius; x++)
            {
                double distance = sqrt(x * x + y * y);
                if (distance <= outerRadius && distance >= innerRadius)
                {
                    putpixel(xc + x, yc + y, RGB(0, 0, 0));
                }
                else if (distance > outerRadius - 1 && distance <= outerRadius)
                {
                    double alpha = outerRadius - distance;
                    putAntialiasedPixel(xc + x, yc + y, alpha);
                }
                else if (distance < innerRadius + 1 && distance >= innerRadius)
                {
                    double alpha = distance - innerRadius;
                    putAntialiasedPixel(xc + x, yc + y, alpha);
                }
            }
        }
    }
    void putAntialiasedPixel(int x, int y, double alpha)
    {
        int colorValue = static_cast<int>(255 * alpha);
        putpixel(x, y, BLACK);
    }
    void drawHands(int hour, int minute, int second, int millisecond)
    {
        //绘制时针
        double hourAngle = (hour % 12 + minute / 60.0) * PI / 6;
        int hourX = 320 + (int)(60 * cos(hourAngle - PI / 2));
        int hourY = 240 + (int)(60 * sin(hourAngle - PI / 2));
        setlinecolor(BLUE);
        setlinestyle(PS_SOLID, 4);
        line(320, 240, hourX, hourY);
        //绘制分针
        double minuteAngle = (minute + second / 60.0) * PI / 30;
        int minuteX = 320 + (int)(100 * cos(minuteAngle - PI / 2));
        int minuteY = 240 + (int)(100 * sin(minuteAngle - PI / 2));
        setlinecolor(YELLOW);
        setlinestyle(PS_SOLID, 3);
        line(320, 240, minuteX, minuteY);
        //绘制秒针
        double secondAngle = (second /*+ millisecond / 1000.0*/)*PI / 30;
        int secondX = 320 + (int)(120 * cos(secondAngle - PI / 2));
        int secondY = 240 + (int)(120 * sin(secondAngle - PI / 2));
        setlinecolor(RED);
        setlinestyle(PS_SOLID, 2);
        line(320, 240, secondX, secondY);
    }
    COLORREF getGradientColor(COLORREF startColor, COLORREF endColor, double ratio)
    {
        int r = static_cast<int>(GetRValue(startColor) + ratio * (GetRValue(endColor) - GetRValue(startColor)));
        int g = static_cast<int>(GetGValue(startColor) + ratio * (GetGValue(endColor) - GetGValue(startColor)));
        int b = static_cast<int>(GetBValue(startColor) + ratio * (GetBValue(endColor) - GetBValue(startColor)));
        return RGB(r, g, b);
    }
    void drawTrail(int hour, int minute, int second, int millisecond)
    {
        //绘制秒针飘带
        for (int i = 0; i < 30; ++i)
        {
            double secondAngle = (second + millisecond / 1000.0 - i / 30.0) * PI / 30;
            for (int j = 0; j < 15; ++j)
            {
                double trailAngle = secondAngle - j * PI / 90; //60度
                int secondX = 320 + (int)(120 * cos(trailAngle - PI / 2));
                int secondY = 240 + (int)(120 * sin(trailAngle - PI / 2));
                setlinecolor(getGradientColor(RED, WHITE, j / 15.0)); //渐变色
                setlinestyle(PS_SOLID, 2);
                line(320, 240, secondX, secondY);
            }
        }

        //绘制分针飘带
        for (int i = 0; i < 30; ++i)
        {
            double minuteAngle = (minute + second / 60.0 - i / 30.0) * PI / 30;
            for (int j = 0; j < 15; ++j)
            {
                double trailAngle = minuteAngle - j * PI / 90; //60度
                int minuteX = 320 + (int)(100 * cos(trailAngle - PI / 2));
                int minuteY = 240 + (int)(100 * sin(trailAngle - PI / 2));
                setlinecolor(getGradientColor(YELLOW, WHITE, j / 15.0)); //渐变色
                setlinestyle(PS_SOLID, 3);
                line(320, 240, minuteX, minuteY);
            }
        }

        //绘制时针飘带
        for (int i = 0; i < 30; ++i)
        {
            double hourAngle = (hour % 12 + minute / 60.0 - i / 30.0) * PI / 6;
            for (int j = 0; j < 15; ++j)
            {
                double trailAngle = hourAngle - j * PI / 90; //60度
                int hourX = 320 + (int)(60 * cos(trailAngle - PI / 2));
                int hourY = 240 + (int)(60 * sin(trailAngle - PI / 2));
                setlinecolor(getGradientColor(BLUE, WHITE, j / 15.0)); //渐变色
                setlinestyle(PS_SOLID, 4);
                line(320, 240, hourX, hourY);
            }
        }
    }
};

//绘制单个数字的7段显示灯
void drawDigit(int x, int y, int num)
{
    //定义每个段的位置和大小
    int segments[7][4] = {
        {x + 10, y, x + 40, y + 10},     //A
        {x + 40, y + 10, x + 50, y + 40}, //B
        {x + 40, y + 50, x + 50, y + 80}, //C
        {x + 10, y + 80, x + 40, y + 90}, //D
        {x, y + 50, x + 10, y + 80},   //E
        {x, y + 10, x + 10, y + 40},     //F
        {x + 10, y + 40, x + 40, y + 50}  //G
    };

    //定义每个数字对应的段
    bool digits[10][7] = {
        {true, true, true, true, true, true, false},  //0
        {false, true, true, false, false, false, false}, //1
        {true, true, false, true, true, false, true},  //2
        {true, true, true, true, false, false, true},  //3
        {false, true, true, false, false, true, true}, //4
        {true, false, true, true, false, true, true},  //5
        {true, false, true, true, true, true, true},   //6
        {true, true, true, false, false, false, false}, //7
        {true, true, true, true, true, true, true},    //8
        {true, true, true, true, false, true, true}    //9
    };

    //绘制数字
    for (int i = 0; i < 7; ++i)
    {
        if (digits[num][i])
        {
            solidrectangle(segments[i][0], segments[i][1], segments[i][2], segments[i][3]);
        }
    }
}
//绘制时间
void drawTime(int hour, int minute, int second, int prevHour, int prevMinute, int prevSecond)
{

    //绘制小时
    setfillcolor(BLACK);
    drawDigit(100, 500, hour / 10);
    drawDigit(160, 500, hour % 10);

    //绘制冒号
    setfillcolor(BLACK);
    solidcircle(220, 520, 5);
    solidcircle(220, 560, 5);

    //绘制分钟
    setfillcolor(BLACK);
    drawDigit(240, 500, minute / 10);
    drawDigit(300, 500, minute % 10);

    //绘制冒号
    setfillcolor(BLACK);
    solidcircle(360, 520, 5);
    solidcircle(360, 560, 5);

    //绘制秒钟
    setfillcolor(BLACK);
    drawDigit(380, 500, second / 10);
    drawDigit(440, 500, second % 10);
}

int main()
{
    Clock clock;
    clock.init(); //自定义图形初始化函数，用于绘制时钟界面

    int prevHour = -1, prevMinute = -1, prevSecond = -1;

    while (!_kbhit()) //无键盘操作时进入循环
    {
        time_t now;
        struct tm t;
        time(&now);
        localtime_s(&t, &now); //获取当前时间
        SYSTEMTIME st;
        GetLocalTime(&st); //获取当前时间的毫秒数

        clock.drawClock(t.tm_hour, t.tm_min, t.tm_sec, st.wMilliseconds); //绘制时钟
        drawTime(t.tm_hour, t.tm_min, t.tm_sec, prevHour, prevMinute, prevSecond); //绘制时间

        prevHour = t.tm_hour;
        prevMinute = t.tm_min;
        prevSecond = t.tm_sec;

        Sleep(1000); //每秒更新一次
    }
    int ch = _getch(); //按任意键准备退出时钟程序
    closegraph(); //退出图形界面
    return 0;
}