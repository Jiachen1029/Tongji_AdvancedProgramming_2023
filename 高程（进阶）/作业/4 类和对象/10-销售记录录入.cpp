#include <iostream>
#include <iomanip>
#include <sstream>
#include <cmath>
using namespace std;

class Book_Sale
{
private:
    char* isbn; //指向书籍编号的指针
    int sales_volume;   //销售量
    double original_price; //原始价格
    double real_price;     //实售价格
    double discount;       //折扣
    double gross_sales;    //销售总额
    //计算校验位
    int CalculateCheckDigit(const string& isbnWithoutCheckDigit)
    {
        int sum = 0;
        int multiplier = 1;
        for (char c : isbnWithoutCheckDigit)
        {
            if (c != '-')
            {
                sum += (c - '0') * multiplier;
                multiplier = (multiplier == 1) ? 3 : 1;
            }
        }
        int checkDigit = (10 - (sum % 10)) % 10;
        return checkDigit;
    }
    //不进行四舍五入的截取
    string TruncateWithoutRounding(double value, int precision)
    {
        double factor = pow(10, precision);
        double truncatedValue = floor(value * factor) / factor;
        stringstream ss;
        ss << fixed << setprecision(precision) << truncatedValue;
        string str = ss.str();
        //确保保留指定的小数位数
        size_t pos = str.find('.');
        if (pos == string::npos)
        {
            str += '.';
            pos = str.length() - 1;
        }
        while (str.length() - pos - 1 < precision)
        {
            str += '0';
        }
        return str;
    }
public:
    //构造函数
    Book_Sale(int fourthSegment, int sales_volume, double original_price, double discount)
    {
        this->sales_volume = sales_volume;
        this->original_price = original_price;
        this->discount = discount;

        real_price = original_price * discount;
        gross_sales = real_price * sales_volume;

        stringstream ss;
        ss << "978-7-121-" << setw(5) << setfill('0') << fourthSegment;
        string isbnWithoutCheckDigit = ss.str();
        int checkDigit = CalculateCheckDigit(isbnWithoutCheckDigit);
        ss << "-" << checkDigit;
        string fullIsbn = ss.str();

        isbn = new char[fullIsbn.length() + 1];
        strcpy_s(isbn, fullIsbn.length() + 1, fullIsbn.c_str());
    }
    //析构函数
    ~Book_Sale()
    {
        delete[] isbn;
    }
    //输出
    void PrintData()
    {
        cout << "该书的ISBN号为:" << isbn << endl;
        cout << "销量为:" << sales_volume << "本 原价为:" << TruncateWithoutRounding(original_price, 3) << "元 折扣为:" << TruncateWithoutRounding(discount, 3) << " 现价为:" << TruncateWithoutRounding(real_price, 3) << "元 总销售额为:" << TruncateWithoutRounding(gross_sales, 3) << "元" << endl;
    }
};
int main()
{
    while (true)
    {
        int fourthSegment, sales_volume;
        double original_price, discount;

        cin >> fourthSegment;
        if (fourthSegment == -1)
        {
            break;
        }
        cin >> sales_volume >> original_price >> discount;

        Book_Sale sale(fourthSegment, sales_volume, original_price, discount);
        sale.PrintData();
    }    