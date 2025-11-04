#include <iostream>
#include <cmath>


using namespace std;


/**********************************************
*
*    TO-DO:
*        请补全该区域的代码。
*
***********************************************/
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class Shape {
public:
    virtual double area() const = 0; //纯虚函数
    virtual ~Shape() {} //虚析构函数
};

class Circle : public Shape 
{
private:
    double radius;
public:
    Circle(double r) : radius(r) {}
    double area() const override
    {
        return M_PI * radius * radius;
    }
};

class Square : public Shape 
{
private:
    double side;
public:
    Square(double s) : side(s) {}
    double area() const override 
    {
        return side * side;
    }
};

class Rectangle : public Shape
{
private:
    double length, width;
public:
    Rectangle(double l, double w) : length(l), width(w) {}
    double area() const override
    {
        return length * width;
    }
};

class Trapezoid : public Shape 
{
private:
    double base1, base2, height;
public:
    Trapezoid(double b1, double b2, double h) : base1(b1), base2(b2), height(h) {}
    double area() const override
    {
        return (base1 + base2) * height / 2;
    }
};

class Triangle : public Shape
{
private:
    double a, b, c;
public:
    Triangle(double side1, double side2, double side3) : a(side1), b(side2), c(side3) {}
    double area() const override
    {
        double s = (a + b + c) / 2;
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }
};

/**********************************************
*
*    TO-DO END
*
***********************************************/


int main() {
    Circle    c1(2);
    Square    s1(3);
    Rectangle r1(4, 5);
    Trapezoid t1(6, 7, 8);
    Triangle  t2(3, 4, 5);


    Shape* s[5] = { &c1, &s1, &r1, &t1, &t2 };


    for (int i = 0; i < 5; i++) {
        cout << s[i]->area() << endl;
    }
    return 0;
}