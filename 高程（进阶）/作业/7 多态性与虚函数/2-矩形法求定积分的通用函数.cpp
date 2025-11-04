#include <iostream>
#include <cmath>


using namespace std;


/**********************************************
*
*    TO-DO:
*        请补全该区域的代码。
*
***********************************************/

class integral
{
public:
    double a, b;
    virtual double value() const = 0;
    friend istream& operator>>(istream& in, integral& obj)
    {
        in >> obj.a >> obj.b;
        return in;
    }
};

class integral_sin : public integral 
{
public:
    double value() const override 
    {
        double sum = 0.0;
        double delta_x = (b - a) / 10000.0;
        for (int i = 0; i <= 10000; ++i) 
        {
            sum += sin(a + i * delta_x) * delta_x;
        }
        return sum;
    }
};

class integral_cos : public integral 
{
public:
    double value() const override
    {
        double sum = 0.0;
        double delta_x = (b - a) / 10000.0;
        for (int i = 0; i <= 10000; ++i)
        {
            sum += cos(a + i * delta_x) * delta_x;
        }
        return sum;
    }
};

class integral_exp : public integral 
{
public:
    double value() const override
    {
        double sum = 0.0;
        double delta_x = (b - a) / 10000.0;
        for (int i = 0; i <= 10000; ++i)
        {
            sum += exp(a + i * delta_x) * delta_x;
        }
        return sum;
    }
};
/**********************************************
*
*    TO-DO END
*
***********************************************/


int main()
{
    integral_sin s1;
    integral_cos s2;
    integral_exp s3;
    integral* p;


    cout << "请输入上下限：";
    cin >> s1;
    p = &s1;
    cout << "∫sinxdx的计算结果为：" << (p->value()) << endl;


    cout << "请输入上下限：";
    cin >> s2;
    p = &s2;
    cout << "∫cosxdx的计算结果为：" << (p->value()) << endl;


    cout << "请输入上下限：";
    cin >> s3;
    p = &s3;
    cout << "∫expxdx的计算结果为：" << (p->value()) << endl;


    return 0;
}