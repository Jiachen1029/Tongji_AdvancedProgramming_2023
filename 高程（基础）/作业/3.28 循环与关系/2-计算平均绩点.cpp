#include<iostream>
#include<iomanip>
using namespace std;

int main()
{
	int N;//学科数目
	int gpa;//绩点
	double credit, avg, sumcredit=0.0, sum=0.0;//学分，平均绩点，学分总和，学分*绩点总和
	cout << "请输入学科数目" << endl;
	cin >> N;
	cout << "请输入学分和五分制绩点" << endl;
	for (int i = 0; i < N; i++)
	{
		cin >> credit >> gpa;
		sum = sum + credit * gpa;//学分*绩点累计
		sumcredit += credit;//学分累计
		avg = sum / sumcredit;
		cout << "当前均绩为" << setiosflags(ios::fixed) << setprecision(2) << avg << "。" << endl;
	}
	return 0;
}