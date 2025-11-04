#include <conio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
//全局变量
int A[10000] = { 0 }; //矩阵A（最大100*100）
int B[10000] = { 0 }; //矩阵B（最大100*100）
int C[10000] = { 0 }; //矩阵C

void wait_for_enter();//暂停程序，等待回车键继续
void menu();
void matriplus();
void nummulti();
void matritrans();
void matrimulti();
void hadamulti();
void conv();
void demo();
void ostu();
void segementation();

int main()
{
    
    char choice, ch;
    while (true)
    {
        system("cls"); // 清屏函数
        menu();
        char choice = _getch();//不用输入回车，直接读取 
        if (choice == '0') // 选择退出
        {
            cout << "\n确定退出吗?（退出请输入Y或y）" << endl;
            char ch = _getch();
            if (ch == 'y' || ch == 'Y')
                break;
            else
                continue;
        }
        switch (choice)
        {
        case '1':
            matriplus();
            break;
        case '2':
            nummulti();
            break;
        case '3':
            matritrans();
            break;
        case '4':
            matrimulti();
            break;
        case '5':
            hadamulti();
            break;
        case '6':
            conv();
            break;
        case '7':
            demo();
            break;
        case '8':
            ostu();
			break;
        case '9':
            segementation();
            break;
        default:
            cout << "\n 输入错误，请重新输入" << endl;
        }
        wait_for_enter();
    }
    return 0;
}

void menu()//菜单
{
    cout << "我是汪嘉晨！我是2353900！我爱矩阵运算大作业！" << endl;
    cout << "******************************************************" << endl;
    cout << "*      1 矩阵加法    2 矩阵数乘    3 矩阵转置        *" << endl;
    cout << "*      4 矩阵乘法    5 Hadmard乘积 6 矩阵卷积        *" << endl;
    cout << "*      7 卷积应用    8 OSTU算法    9 Segementation   *" << endl;
    cout << "*                    0 退出                          *" << endl;
    cout << "******************************************************" << endl;
    cout << "请选择菜单项<0~9>：" << endl;
}
void wait_for_enter()//暂停程序，等待回车键继续
{
    cout << endl
        << "按回车键继续";
    while (_getch() != '\r')
            ;
    cout << endl
        << endl;
}
void matriplus()//矩阵加法
{
    cout << "请输入两个矩阵的行数和列数：" << endl;
    int m, n;//矩阵行数，列数
    cin >> m >> n;
    cout << "请输入矩阵A：" << endl;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> A[i * n + j];
        }
    }
    cout << "请输入矩阵B：" << endl;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> B[i * n + j];
        }
    }
    cout << "矩阵A+B=" << endl;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << A[i * n + j] + B[i * n + j] << " ";
        }
        cout << endl;
    }
}
void nummulti()//矩阵数乘
{
    cout << "请输入矩阵的行数和列数：" << endl;
    int m, n,num;//矩阵行数，列数与数
    cin >> m >> n;
    cout << "请输入矩阵：" << endl;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> A[i * n + j];
        }
    }
    cout << "请输入数乘的数：" << endl;
    cin >> num;
    cout<< "矩阵*num=" << endl;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << A[i * n + j] * num << " ";
        }
        cout << endl;
    }
}
void matritrans()//矩阵转置
{
	cout << "请输入矩阵的行数和列数：" << endl;
	int m, n;
	cin >> m >> n;
    cout << "请输入矩阵：" << endl;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> A[i * n + j];
        }
    }
    cout << "矩阵转置为：" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << A[j * n + i] << " ";
        }
        cout << endl;
    }
}
void matrimulti()//矩阵乘法
{
    cout << "请输入矩阵A的行数和列数：" << endl;
    int m, n;//矩阵A行数，列数
    cin >> m >> n;
    cout << "请输入矩阵A" << endl;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> A[i * n + j];
        }
    }
    cout << "请输入矩阵B的行数和列数：" << endl;
    int p, q;//矩阵B行数，列数
    cin >> p >> q;
    cout << "请输入矩阵B：" << endl;
    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < q; j++)
        {
            cin >> B[i * q + j];
        }
    }
    if (n != p)
    {
        cout << "矩阵A的列数不等于矩阵B的行数，无法相乘" << endl;
        return;
    }
    cout << "矩阵AB=" << endl;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < q; j++)
        {
            int sum = 0;
            for (int k = 0; k < n; k++)
            {
                sum += A[i * n + k] * B[k * q + j];
            }
            cout << sum << " ";
        }
        cout << endl;
    }
}
void hadamulti()//Hadamard乘积
{
    cout << "请输入两个矩阵的行数和列数：" << endl;
    int m, n;//矩阵行数，列数
    cin >> m >> n;
    cout << "请输入矩阵A：" << endl;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> A[i * n + j];
        }
    }
    cout << "请输入矩阵B：" << endl;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> B[i * n + j];
        }
    }
    cout << "Hadamard乘积=" << endl;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << A[i * n + j] * B[i * n + j] << " ";
        }
        cout << endl;
    }
}
void conv()
{
    char back = '0';
    int m = 0, n = 0;
    cout << "请输入矩阵的行数和列数：" << endl;
    cin >> m >> n;
    cout << "请输入需要卷积的矩阵：" << endl;
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cin >> A[i * n + j];
        }
    }
    cout << "请输入一个 3 行 3 列的卷积核：" << std::endl;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            cin >> B[i * 3 + j];
        }
    }
    // 卷积操作并输出结果
    cout << "卷积操作结果：" << endl;
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            int sum = 0;
            for (int ki = -1; ki <= 1; ++ki)
            {
                for (int kj = -1; kj <= 1; ++kj)
                {
                    int ni = i + ki;
                    int nj = j + kj;
                    // 对超出边界的部分进行padding
                    if (ni < 0 || ni >= m || nj < 0 || nj >= n)
                    {
                        sum += 0; // padding 0
                    }
                    else
                    {
                        sum += A[ni * n + nj] * B[(ki + 1) * 3 + (kj + 1)];
                    }
                }
            }
            cout << sum << " ";
        }
        cout << endl;
    }
    return;
}
void demo()//卷积应用
{
    Mat image = imread("C:\\Users\\wangj\\Desktop\\高程\\作业\\大作业1-矩阵运算\\images\\demolena.jpg", IMREAD_GRAYSCALE); 
    //图像的灰度值存放在格式为Mat的变量image中
    // 宽度和高度
    int width = image.cols;
    int height = image.rows;
    //输入卷积核B1-B6
    float kernel1[9] = { 1.0f / 9, 1.0f / 9, 1.0f / 9, 1.0f / 9, 1.0f / 9, 1.0f / 9, 1.0f / 9, 1.0f / 9, 1.0f / 9 };
    float kernel2[9] = { -1, -2, -1, 0, 0, 0, 1, 2, 1 };
    float kernel3[9] = { -1, 0, 1, -2, 0, 2, -1, 0, 1 };
    float kernel4[9] = { -1, -1, -1, -1, 9, -1, -1, -1, -1 };
    float kernel5[9] = { -1, -1, 0, -1, 0, 1, 0, 1, 1 };
    float kernel6[9] = { 1.0f/16, 2.0f/16, 1.0f/16, 2.0f/16, 4.0f/16, 2.0f/16, 1.0f/16, 2.0f/16, 1.0f/16 };
    //卷积运算
    Mat result1 = image.clone();
    for (int y = 1; y < image.rows - 1; y++)
    {
        for (int x = 1; x < image.cols - 1; x++)
        {
            float sum1 = 0;
            for (int j = -1; j <= 1; j++)
            {
                for (int i = -1; i <= 1; i++)
                {
                    sum1 += kernel1[(j + 1) * 3 + (i + 1)] * (float)(image.at<uchar>(y - j, x - i));
                }
            }
            if(sum1>=255) sum1=255;
            if(sum1<=0) sum1=0;
            result1.at<uchar>(y, x) = sum1;
        }
    }
    Mat result2= image.clone();
    for (int y = 1; y < image.rows - 1; y++)
    {
        for (int x = 1; x < image.cols - 1; x++)
        {
			float sum2 = 0;
            for (int j = -1; j <= 1; j++)
            {
                for (int i = -1; i <= 1; i++)
                {
					sum2 += kernel2[(j + 1) * 3 + (i + 1)] * (float)(image.at<uchar>(y - j, x - i));
				}
			}
			if(sum2>=255) sum2=255;
			if(sum2<=0) sum2=0;
			result2.at<uchar>(y, x) = sum2;
		}
	}
    Mat result3= image.clone();
    for (int y = 1; y < image.rows - 1; y++)
    {
        for (int x = 1; x < image.cols - 1; x++)
        {
            float sum3 = 0;
            for (int j = -1; j <= 1; j++)
            {
                for (int i = -1; i <= 1; i++)
                {
					sum3 += kernel3[(j + 1) * 3 + (i + 1)] * (float)(image.at<uchar>(y - j, x - i));
				}
			}
            if(sum3>=255) sum3=255;
            if(sum3<=0) sum3=0;
            result3.at<uchar>(y, x) = sum3;
        }
    }
    Mat result4= image.clone();
    for (int y = 1; y < image.rows - 1; y++)
    {
        for (int x = 1; x < image.cols - 1; x++)
        {
			float sum4 = 0;
            for (int j = -1; j <= 1; j++)
            {
                for (int i = -1; i <= 1; i++)
                {
					sum4 += kernel4[(j + 1) * 3 + (i + 1)] * (float)(image.at<uchar>(y - j, x - i));
				}
                if(sum4>=255) sum4=255;
                if(sum4<=0) sum4=0;
                result4.at<uchar>(y, x) = sum4;//亮度太低了！！！！
            }
        }
    }
    Mat result5= image.clone();
    for (int y = 1; y < image.rows - 1; y++)
    {
        for (int x = 1; x < image.cols - 1; x++)
        {
            float sum5= 0;
            for (int j = -1; j <= 1; j++)
            {
                for (int i = -1; i <= 1; i++)
                {
					sum5 += kernel5[(j + 1) * 3 + (i + 1)] * (float)(image.at<uchar>(y - j, x - i));
				}
			}
            if(sum5>=255) sum5=255;
			if(sum5<=0) sum5=0;
			result5.at<uchar>(y, x) = sum5;
        }
    }
    Mat result6= image.clone();
    for (int y = 1; y < image.rows - 1; y++)
    {
        for (int x = 1; x < image.cols - 1; x++)
        {
			float sum6 = 0;
            for (int j = -1; j <= 1; j++)
            {
                for (int i = -1; i <= 1; i++)
                {
					sum6 += kernel6[(j + 1) * 3 + (i + 1)] * (float)(image.at<uchar>(y - j, x - i));
				}
                if(sum6>=255) sum6=255;
                if(sum6<=0) sum6=0;
                result6.at<uchar>(y, x) = sum6;
            }
        }
    }
    cout << result1 << endl;
    imshow("Image-original", image);//显示原图像
    waitKey(0);//等待按键
    imshow("Image-conv1", result1);
    waitKey(0);
    cout << result2 << endl;
    imshow("Image-conv2", result2);
    waitKey(0);
    cout << result3 << endl;
    imshow("Image-conv3", result3);
    waitKey(0);
    cout << result4 << endl;
    imshow("Image-conv4", result4);
    waitKey(0);
    cout << result5 << endl;
    imshow("Image-conv5", result5);
    waitKey(0);
    cout << result6 << endl;
    imshow("Image-conv6", result6);
    waitKey(0);
    destroyAllWindows(); // 关闭所有打开的窗口
    return;
}
void ostu()//大津法 加分项2 二值化
{
    Mat image = imread("C:\\Users\\wangj\\Desktop\\高程\\作业\\大作业1-矩阵运算\\images\\demolena.jpg", IMREAD_GRAYSCALE);
    //图像的灰度值存放在格式为Mat的变量image中
    Mat binaryImage;
    threshold(image, binaryImage, 0, 255, THRESH_OTSU);
    imshow("Image-original", image);//显示原图像
    waitKey(0);
    imshow("Image-binary", binaryImage);
    waitKey(0);
    destroyAllWindows(); 
    return;
}
void segementation()//二值化PLUS，加分项3
{
    Mat image1 = imread("C:\\Users\\wangj\\Desktop\\高程\\作业\\大作业1-矩阵运算\\images\\snowball.jpg", IMREAD_GRAYSCALE);
    Mat image2 = imread("C:\\Users\\wangj\\Desktop\\高程\\作业\\大作业1-矩阵运算\\images\\polyhedrosis.jpg", IMREAD_GRAYSCALE);
    Mat image3 = imread("C:\\Users\\wangj\\Desktop\\高程\\作业\\大作业1-矩阵运算\\images\\ship.jpg", IMREAD_GRAYSCALE);
    Mat image4 = imread("C:\\Users\\wangj\\Desktop\\高程\\作业\\大作业1-矩阵运算\\images\\brain.jpg", IMREAD_GRAYSCALE);
    //二值化图像（取一个黑白模子）
    Mat binary_image1, binary_image2, binary_image3, binary_image4;
    threshold(image1, binary_image1, 127, 255, THRESH_OTSU);
    threshold(image2, binary_image2, 127, 255, THRESH_OTSU);
    threshold(image3, binary_image3, 127, 255, THRESH_OTSU);
    threshold(image4, binary_image4, 127, 255, THRESH_OTSU);
    binary_image1 = 255 - binary_image1;//黑的变成255，白的变成0，方便后面的叠加
    binary_image2 = 255 - binary_image2;
    binary_image3 = 255 - binary_image3;
    binary_image4 = 255 - binary_image4;
    image1 = 255 - image1;
    image2 = 255 - image2;
    image3 = 255 - image3;
    image4 = 255 - image4;
    Mat result1, result2, result3, result4;
    result1 = binary_image1 + image1;
    result2 = binary_image2 + image2;
    result3 = binary_image3 + image3;
    result4 = binary_image4 + image4;
    result1 = 255 - result1;
    result2 = 255 - result2;
    result3 = 255 - result3;
    result4 = 255 - result4;//类似于穿脱原理？倒回来
    // 限制结果图像的像素值不超过255
    result1 = min(result1, 255);
    result2 = min(result2, 255);
    result3 = min(result3, 255);
    result4 = min(result4, 255);
    imshow("Binary Image1", result1);
    waitKey(0);
    imshow("Binary Image2", result2);
    waitKey(0);
    imshow("Binary Image3", result3);
    waitKey(0);
    imshow("Binary Image4", result4);
    waitKey(0);
    destroyAllWindows();
    return;
}