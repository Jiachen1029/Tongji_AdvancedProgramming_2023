#include <iostream>
using namespace std;

class Matrix
{
private:
    int** data; // 二维数组指针
    int row, col; // 行数和列数

public:
    Matrix(int r, int c); // 构造函数
    ~Matrix(); // 析构函数

    /****************** TODO ******************/
    Matrix(const Matrix& other); //拷贝构造函数
    Matrix& operator=(const Matrix& other); //赋值运算符重载
    Matrix operator+(const Matrix& other) const; //加法运算符重载
    Matrix operator*(int scalar) const; //数乘运算符重载
    friend istream& operator>>(istream& in, Matrix& matrix); //输入运算符重载
    friend ostream& operator<<(ostream& out, const Matrix& matrix); //输出运算符重载
    /**************** TODO-END ****************/
};

/****************** TODO ******************/
Matrix::Matrix(int r, int c) : row(r), col(c)
{
    data = new int* [row];
    for (int i = 0; i < row; ++i)
    {
        data[i] = new int[col];
    }
}

Matrix::~Matrix()
{
    for (int i = 0; i < row; ++i)
    {
        delete[] data[i];
    }
    delete[] data;
}

Matrix::Matrix(const Matrix& other) : row(other.row), col(other.col)
{
    data = new int* [row];
    for (int i = 0; i < row; ++i)
    {
        data[i] = new int[col];
        for (int j = 0; j < col; ++j)
        {
            data[i][j] = other.data[i][j];
        }
    }
}

Matrix& Matrix::operator=(const Matrix& other)
{
    if (this == &other)
        return *this;

    for (int i = 0; i < row; ++i)
    {
        delete[] data[i];
    }
    delete[] data;

    row = other.row;
    col = other.col;

    data = new int* [row];
    for (int i = 0; i < row; ++i)
    {
        data[i] = new int[col];
        for (int j = 0; j < col; ++j)
        {
            data[i][j] = other.data[i][j];
        }
    }

    return *this;
}

Matrix Matrix::operator+(const Matrix& other) const
{
    Matrix result(row, col);
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            result.data[i][j] = data[i][j] + other.data[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator*(int scalar) const
{
    Matrix result(row, col);
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            result.data[i][j] = data[i][j] * scalar;
        }
    }
    return result;
}

Matrix operator*(int scalar, const Matrix& matrix)
{
    return matrix * scalar;
}

istream& operator>>(istream& in, Matrix& matrix)
{
    for (int i = 0; i < matrix.row; ++i)
    {
        for (int j = 0; j < matrix.col; ++j)
        {
            in >> matrix.data[i][j];
        }
    }
    return in;
}

ostream& operator<<(ostream& out, const Matrix& matrix)
{
    for (int i = 0; i < matrix.row; ++i)
    {
        for (int j = 0; j < matrix.col; ++j)
        {
            out << matrix.data[i][j] << " ";
        }
        out << endl;
    }
    return out;
}
/**************** TODO-END ****************/

int main()
{
    // 输入矩阵的行数和列数
    int r, c;
    cout << "请输入矩阵的行数和列数：" << endl;
    cin >> r >> c;
    // 创建三个矩阵对象
    Matrix A(r, c), B(r, c), C(r, c);
    // 输入三个矩阵的元素
    cout << "请输入矩阵A的元素：" << endl;
    cin >> A;
    cout << "请输入矩阵B的元素：" << endl;
    cin >> B;
    cout << "请输入矩阵C的元素：" << endl;
    cin >> C;
    // 输入三个矩阵的组合系数
    int ka, kb, kc;
    cout << "请依次输入矩阵A、B、C的组合系数ka，kb，kc：" << endl;
    cin >> ka >> kb >> kc;

    /********** 测试矩阵简单线性组合 **********/
    Matrix D1 = ka * A + kb * B + kc * C;
    cout << "D1 = " << ka << " * A + " << kb << " * B + " << kc << " * C = " << endl;
    cout << D1 << endl;
    Matrix D2 = A * ka + B * kb + C * kc;
    cout << "D2 = A * " << ka << " + B * " << kb << " + C * " << kc << " = " << endl;
    cout << D2 << endl;

    /********** 测试矩阵复杂线性组合 **********/
    Matrix D3 = A * kb * kc + B * ka * kc + C * ka * kb;
    cout << "D3 = A * " << kb << " * " << kc << " + B * " << ka << " * " << kc << " + C * " << ka << " * " << kb << " = " << endl;
    cout << D3 << endl;
    Matrix D4 = ka * (kb * (A + B + C)) * kc;
    cout << "D4 = " << ka << " * (" << kb << " * (A + B + C)) * " << kc << " = " << endl;
    cout << D4 << endl;
    Matrix D5 = ka * (kb * (kc * A) + B) + C;
    cout << "D5 = " << ka << " * (" << kb << " * (" << kc << " * A) + B) + C = " << endl;
    cout << D5 << endl;

    return 0;
}