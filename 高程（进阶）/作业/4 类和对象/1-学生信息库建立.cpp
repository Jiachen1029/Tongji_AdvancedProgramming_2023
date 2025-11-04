#include<iostream>
#include<string>
using namespace std;

class Student
{
	string name;
	int num;
	int chi_score;//语文成绩
	int math_score;
	int eng_score;
	int avg_score;

public:
	//计算平均成绩
	void avg()
	{
		avg_score = (chi_score + math_score + eng_score) / 3;
	}
	//设置学生信息
	void set(string n, int nu, int chi, int math, int eng)
	{
		name = n;
		num = nu;
		chi_score = chi;
		math_score = math;
		eng_score = eng;
		avg();
	}
	//输出学生信息
	void print()
	{
		cout << "==学生信息==" << endl;
		cout << "姓名：" << name << endl;
		cout << "学号：" << num << endl;
		cout << "====成绩====" << endl;
		cout << "语文成绩：" << chi_score << endl;
		cout << "数学成绩：" << math_score << endl;
		cout << "英语成绩：" << eng_score << endl;
		cout << "平均成绩：" << avg_score << endl;
		cout << endl;
	}
};
int main()
{
	const int num_students = 5;
	Student students[num_students];
	for (int i = 0; i < num_students; ++i)
	{
		string name;
		int num, chi_score, math_score, eng_score;
		//输入学生信息
		cin >> name >> num >> chi_score >> math_score >> eng_score;

		students[i].set(name, num, chi_score, math_score, eng_score);
	}
	//输出所有学生信息
	for (int i = 0; i < num_students; ++i)
	{
		students[i].print();
	}
	return 0;
}