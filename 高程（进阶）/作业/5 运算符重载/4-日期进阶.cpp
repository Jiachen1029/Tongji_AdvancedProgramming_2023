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
    Date& operator++();
    Date operator++(int);
    Date& operator--();
    Date operator--(int);
    Date& operator+=(int d);
    Date& operator-=(int d);
    Date operator+(int d) const;
    Date operator-(int d) const;
    int operator-(const Date& other) const;
    bool operator<(const Date& other) const;
    bool operator>(const Date& other) const;
    bool operator<=(const Date& other) const;
    bool operator>=(const Date& other) const;
    bool operator==(const Date& other) const;
    bool operator!=(const Date& other) const;
    bool operator<(int days) const;
    bool operator>(int days) const;
    bool operator<=(int days) const;
    bool operator>=(int days) const;
    bool operator==(int days) const;
    bool operator!=(int days) const;
    operator int() const;
    // 声明友元函数
    friend bool operator<(int days, const Date& date);
    friend bool operator>(int days, const Date& date);
    friend bool operator<=(int days, const Date& date);
    friend bool operator>=(int days, const Date& date);
    friend bool operator==(int days, const Date& date);
    friend bool operator!=(int days, const Date& date);
    friend Date operator+(int days, const Date& date);
    friend Date operator-(int days, const Date& date);
    friend ostream& operator<<(ostream& os, const Date& date);
    /**************** TODO-END ****************/
};

/****************** TODO ******************/
Date::Date(int y, int m, int d) : year(y), month(m), day(d) {}

Date::Date(int days) {
    year = 1;
    month = 1;
    day = 1;
    *this += days - 1;
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
    static const int daysInMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    for (int m = 1; m < month; ++m) {
        days += (m == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) ? 29 : daysInMonth[m - 1];
    }
    days += day;
    return days;
}
Date& Date::operator++() {
    *this += 1;
    return *this;
}
Date Date::operator++(int) {
    Date temp = *this;
    *this += 1;
    return temp;
}
Date& Date::operator--() {
    *this -= 1;
    return *this;
}
Date Date::operator--(int) {
    Date temp = *this;
    *this -= 1;
    return temp;
}
Date& Date::operator+=(int d) {
    day += d;
    static const int daysInMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    while (day > ((month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) ? 29 : daysInMonth[month - 1])) {
        day -= ((month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) ? 29 : daysInMonth[month - 1]);
        if (++month > 12) {
            month = 1;
            ++year;
        }
    }
    while (day < 1) {
        if (--month < 1) {
            month = 12;
            --year;
        }
        day += ((month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) ? 29 : daysInMonth[month - 1]);
    }
    return *this;
}
Date& Date::operator-=(int d) {
    *this += -d;
    return *this;
}
Date Date::operator+(int d) const {
    Date temp = *this;
    temp += d;
    return temp;
}
Date Date::operator-(int d) const {
    Date temp = *this;
    temp -= d;
    return temp;
}
Date operator+(int d, const Date& date) {
    Date temp = date;
    temp += d;
    return temp;
}
Date operator-(int days, const Date& date) {
    Date temp = date;
    temp -= days;
    return temp;
}

int Date::operator-(const Date& other) const {
    return int(*this) - int(other);
}
bool Date::operator<(const Date& other) const {
    return int(*this) < int(other);
}
bool Date::operator>(const Date& other) const {
    return int(*this) > int(other);
}
bool Date::operator<=(const Date& other) const {
    return int(*this) <= int(other);
}
bool Date::operator>=(const Date& other) const {
    return int(*this) >= int(other);
}
bool Date::operator==(const Date& other) const {
    return int(*this) == int(other);
}
bool Date::operator!=(const Date& other) const {
    return int(*this) != int(other);
}
bool Date::operator<(int days) const {
    return int(*this) < days;
}
bool Date::operator>(int days) const {
    return int(*this) > days;
}
bool Date::operator<=(int days) const {
    return int(*this) <= days;
}
bool Date::operator>=(int days) const {
    return int(*this) >= days;
}
bool Date::operator==(int days) const {
    return int(*this) == days;
}
bool Date::operator!=(int days) const {
    return int(*this) != days;
}
bool operator<(int days, const Date& date) {
    return days < int(date);
}
bool operator>(int days, const Date& date) {
    return days > int(date);
}
bool operator<=(int days, const Date& date) {
    return days <= int(date);
}
bool operator>=(int days, const Date& date) {
    return days >= int(date);
}
bool operator==(int days, const Date& date) {
    return days == int(date);
}
bool operator!=(int days, const Date& date) {
    return days != int(date);
}
/**************** TODO-END ****************/

int main()
{
    cout << "*********************************" << endl;
    cout << "1. 基础版内容测试" << endl << endl;

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

    cout << "d1转换为天数为：" << endl;
    cout << int(d1) << endl;
    cout << "d2转换为天数为：" << endl;
    cout << int(d2) << endl;

    cout << "d1 - d2 = " << d1 - d2 << endl;
    cout << "*********************************" << endl;
    cout << "2. 自增与自减运算符测试" << endl << endl;

    cout << "d1++ 结果为 " << d1++ << endl;
    cout << "++d1 结果为 " << ++d1 << endl;
    cout << "d1-- 结果为 " << d1-- << endl;
    cout << "--d1 结果为 " << --d1 << endl;

    cout << "*********************************" << endl;
    cout << "3. 复合赋值运算符测试" << endl << endl;

    int gap;
    cout << "请输入加减的天数：" << endl;
    cin >> gap;

    cout << "d1 += " << gap << " 结果为 " << (d1 += gap) << endl;
    cout << "d1 -= " << gap << " 结果为 " << (d1 -= gap) << endl;
    // 注意此时d1将会变为原来的值，因为上面的操作会改变d1的值

    cout << "*********************************" << endl;
    cout << "4. 加法/减法运算符测试" << endl << endl;

    cout << "d1 + " << gap << " = " << d1 + gap << endl;
    cout << gap << " + d1 = " << gap + d1 << endl;

    cout << "d1 - " << gap << " = " << d1 - gap << endl;
    cout << gap << " - d1 = " << gap - d1 << endl;

    cout << "*********************************" << endl;
    cout << "5. 关系运算符测试（1为真，0为假）" << endl << endl;

    cout << "d1 < d2 结果为 " << (d1 < d2) << endl;
    cout << "d1 > d2 结果为 " << (d1 > d2) << endl;
    cout << "d1 <= d2 结果为 " << (d1 <= d2) << endl;
    cout << "d1 >= d2 结果为 " << (d1 >= d2) << endl;
    cout << "d1 == d2 结果为 " << (d1 == d2) << endl;
    cout << "d1 != d2 结果为 " << (d1 != d2) << endl;

    cout << endl;

    cout << "d1 < " << days << " 结果为 " << (d1 < days) << endl;
    cout << "d1 > " << days << " 结果为 " << (d1 > days) << endl;
    cout << "d1 <= " << days << " 结果为 " << (d1 <= days) << endl;
    cout << "d1 >= " << days << " 结果为 " << (d1 >= days) << endl;
    cout << "d1 == " << days << " 结果为 " << (d1 == days) << endl;
    cout << "d1 != " << days << " 结果为 " << (d1 != days) << endl;

    cout << endl;

    cout << days << " > d1 结果为 " << (days > d1) << endl;
    cout << days << " < d1 结果为 " << (days < d1) << endl;
    cout << days << " >= d1 结果为 " << (days >= d1) << endl;
    cout << days << " <= d1 结果为 " << (days <= d1) << endl;
    cout << days << " == d1 结果为 " << (days == d1) << endl;
    cout << days << " != d1 结果为 " << (days != d1) << endl;

    cout << "*********************************" << endl;
    cout << "测试结束" << endl;

    return 0;
}
