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
        // 重载输入流运算符
    friend istream& operator>>(istream& in, Matrix& m);
    // 重载输出流运算符
    friend ostream& operator<<(ostream& out, const Matrix& m);
    // 重载矩阵数乘运算符（右乘）
    Matrix operator*(int k) const;
    // 重载矩阵数乘运算符（左乘）
    friend Matrix operator*(int k, const Matrix& m);
    /**************** TODO-END ****************/
};

/****************** TODO ******************/
Matrix::Matrix(int r, int c) : row(r), col(c) {
    data = new int* [row];
    for (int i = 0; i < row; ++i) {
        data[i] = new int[col];
    }
}

Matrix::~Matrix() {
    for (int i = 0; i < row; ++i) {
        delete[] data[i];
    }
    delete[] data;
}

istream& operator>>(istream& in, Matrix& m) {
    for (int i = 0; i < m.row; ++i) {
        for (int j = 0; j < m.col; ++j) {
            in >> m.data[i][j];
        }
    }
    return in;
}

ostream& operator<<(ostream& out, const Matrix& m) {
    for (int i = 0; i < m.row; ++i) {
        for (int j = 0; j < m.col; ++j) {
            out << m.data[i][j] << " ";
        }
        out << endl;
    }
    return out;
}

Matrix Matrix::operator*(int k) const {
    Matrix result(row, col);
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            result.data[i][j] = data[i][j] * k;
        }
    }
    return result;
}

Matrix operator*(int k, const Matrix& m) {
    return m * k;
}
/**************** TODO-END ****************/

int main()
{
    // 输入矩阵的行数和列数
    int r, c;
    cout << "请输入矩阵的行数和列数：" << endl;
    cin >> r >> c;
    // 创建矩阵对象
    Matrix M(r, c);
    // 输入矩阵的元素
    cout << "请输入矩阵M的元素：" << endl;
    cin >> M;
    // 输入数乘的数
    int k;
    cout << "请输入数乘的数k：" << endl;
    cin >> k;

    /********** 测试矩阵左 / 右乘一个数 **********/
    Matrix M1 = M * k;
    cout << "M1 = M * " << k << "：" << endl;
    cout << M1 << endl;
    Matrix M2 = k * M;
    cout << "M2 = " << k << " * M：" << endl;
    cout << M2 << endl;

    /************* 测试矩阵复合乘法 *************/
    Matrix M3 = M * k * k;
    cout << "M3 = M * " << k << " * " << k << "：" << endl;
    cout << M3 << endl;
    Matrix M4 = k * M * k;
    cout << "M4 = " << k << " * M * " << k << "：" << endl;
    cout << M4 << endl;
    Matrix M5 = k * (k * M);
    cout << "M5 = " << k << " * " << k << " * M：" << endl;
    cout << M5 << endl;

    return 0;
}