#include <iostream>
using namespace std;

class dateToDay 
{
public:
    dateToDay(int y, int m, int d); // 构造函数声明
    void setDate(int y, int m, int d); // 设置日期函数声明
    void display(); // 显示函数声明

private:
    bool checkLeap(); // 闰年检查函数声明
    bool checkValid(); // 合法性检查函数声明
    int computeDay(); // 计算日期函数声明
    int year;
    int month;
    int day;
};

// 构造函数定义
dateToDay::dateToDay(int y, int m, int d) 
{
    setDate(y, m, d);
}

// 设置日期函数定义
void dateToDay::setDate(int y, int m, int d) 
{
    year = y;
    month = m;
    day = d;
    if (!checkValid())
    {
        cout << "Illegal" << endl;
    }
}

// 显示函数定义
void dateToDay::display()
{
    if (checkValid()) 
    {
        cout << year << "-" << month << "-" << day << " 是 " << year << " 年的第 " << computeDay() << " 天" << endl;
    }
    else 
    {
        cout << "Illegal" << endl;
    }
}

// 闰年检查函数定义
bool dateToDay::checkLeap() 
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// 合法性检查函数定义
bool dateToDay::checkValid() 
{
    if (year < 1 || year > 9999) 
        return false;
    if (month < 1 || month > 12) 
        return false;
    if (day < 1) 
        return false;

    int daysInMonth[] = { 31, checkLeap() ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };//考虑闰年
    if (day > daysInMonth[month - 1]) 
        return false;

    return true;
}

// 计算日期函数定义
int dateToDay::computeDay() 
{
    int daysInMonth[] = { 31, checkLeap() ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int dayOfYear = 0;
    for (int i = 0; i < month - 1; ++i) 
    {
        dayOfYear += daysInMonth[i];
    }
    dayOfYear += day;
    return dayOfYear;
}

int main() 
{
    int y, m, d;
    cout << "请输入一个日期: ";
    cin >> y >> m >> d;
    dateToDay date1(y, m, d);
    date1.display();
    cout << "请再输入一个日期:";
    cin >> y >> m >> d;
    dateToDay date2(y, m, d);
    date2.display();
    return 0;
}