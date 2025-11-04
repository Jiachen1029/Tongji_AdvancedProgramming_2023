#include <iostream>
using namespace std;

class Date
{
private:
    int year, month, day;

public:
    Date(int y, int m, int d);
    Date(int days); // 从公元元年（0001年）1月1日开始的天数，仅考虑公元元年之后的日期

    // 注意输出格式，格式为"yyyy-mm-dd"，如"2000-01-01"，位数不足的要补0
    /****************** TODO ******************/
    friend ostream& operator<<(ostream& os, const Date& date);
    operator int() const;
    int operator-(const Date& other) const;
    /**************** TODO-END ******************/
};

/****************** TODO ******************/
Date::Date(int y, int m, int d) : year(y), month(m), day(d) {
    // 构造函数实现
}

Date::Date(int days) {
    year = 1;
    while (true) {
        int daysInYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0) ? 366 : 365;
        if (days <= daysInYear) break;
        days -= daysInYear;
        ++year;
    }
    month = 1;
    while (true) {
        int daysInMonth;
        if (month == 2) {
            daysInMonth = ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) ? 29 : 28;
        }
        else if (month == 4 || month == 6 || month == 9 || month == 11) {
            daysInMonth = 30;
        }
        else {
            daysInMonth = 31;
        }
        if (days <= daysInMonth) break;
        days -= daysInMonth;
        ++month;
    }
    day = days;
}

ostream& operator<<(ostream& os, const Date& date) {
    os << (date.year < 1000 ? "0" : "") << (date.year < 100 ? "0" : "") << (date.year < 10 ? "0" : "") << date.year << '-'
        << (date.month < 10 ? "0" : "") << date.month << '-'
        << (date.day < 10 ? "0" : "") << date.day;
    return os;
}

Date::operator int() const {
    int days = 0;
    for (int y = 1; y < year; ++y) {
        days += (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0) ? 366 : 365;
    }
    for (int m = 1; m < month; ++m) {
        if (m == 2) {
            days += ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) ? 29 : 28;
        }
        else if (m == 4 || m == 6 || m == 9 || m == 11) {
            days += 30;
        }
        else {
            days += 31;
        }
    }
    days += day; // 确保0001年1月1日是第1天
    return days;
}

int Date::operator-(const Date& other) const {
    return int(*this) - int(other);
}
/**************** TODO-END ******************/

int main()
{
    // 测试构造函数
    int year, month, day;
    cout << "请输入d1年月日：" << endl;
    cin >> year >> month >> day;
    Date d1(year, month, day);

    int days;
    cout << "请输入d2天数：" << endl;
    cin >> days;
    Date d2(days);

    cout << "d1日期为：" << endl;
    cout << d1 << endl;
    cout << "d2日期为：" << endl;
    cout << d2 << endl;

    // 测试类型转换运算符重载
    cout << "d1转换为天数为：" << endl;
    cout << int(d1) << endl;
    cout << "d2转换为天数为：" << endl;
    cout << int(d2) << endl;

    // 测试减法运算符重载
    cout << "d1和d2相差天数为：" << endl;
    cout << d1 - d2 << endl;

    return 0;
}