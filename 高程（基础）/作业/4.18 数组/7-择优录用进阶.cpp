#include<iostream>
#include<iomanip>
using namespace std;
int main()
{
	double allgpa[10]{};//0-9录用
	double average = 0;
	double sumgpa=0;//用于计算平均值
	int count = 0;
	double gpa;
	cout << "请输入若干个浮点数，代表绩点，输入-1结束程序：" << endl;
	while (cin >> gpa && gpa != -1)
	{
		if (count<=9&&gpa >= 3.5&&gpa>=average)
		{
			allgpa[count] = gpa;
			sumgpa += gpa;
			count++;
			average = sumgpa / count;
		}
		else if (count == 10 && gpa >= average)
		{
			//1.排序，找到最小的
			//2.替换最小，总和与平均值修改
			//冒泡排序,满足降序排列，那么最后一个就是最小的(一定小于等于平均值），替换即可
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 10 - i - 1; j++)
				{
					if (allgpa[j] < allgpa[j + 1])
					{
						double replace = allgpa[j];
						allgpa[j] = allgpa[j + 1];
						allgpa[j + 1] = replace;
					}
				}
			}
			sumgpa = sumgpa - allgpa[9] + gpa;//减去最小的，加上最大的
			average = sumgpa / 10;
			allgpa[9] = gpa;//第十个变成新加入的gpa
		}
	}
	//都输入完以后，再排序一次（有点史山代码）
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10 - i - 1; j++)
		{
			if (allgpa[j] < allgpa[j + 1])
			{
				double replace = allgpa[j];
				allgpa[j] = allgpa[j + 1];
				allgpa[j + 1] = replace;
			}
		}
	}
	cout << "最终被录用绩点情况：" << endl;
	for (int i = 0; i <= 9; i++)
	{
		if (allgpa[i] > 0)//大于0才能显示，不然会出现一堆0.00的数
		{
			double sumgpa = 0;
			double average = 0;
			int count = 0;
			sumgpa += allgpa[i];
			count++;
			cout << setiosflags(ios::fixed) << setprecision(2) << allgpa[i] << " ";
		}
	}
	if (count > 0)
	{
		average = sumgpa / count;
	}
	else
		average = 0.00;
	cout << endl;
	cout << "平均绩点：" << endl;
	cout << setiosflags(ios::fixed) << setprecision(2) << average;
	return 0;
}