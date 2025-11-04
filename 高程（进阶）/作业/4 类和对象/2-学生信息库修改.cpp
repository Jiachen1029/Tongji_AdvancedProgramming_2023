#include<iostream>
#include<string>
using namespace std;

class Student
{
	string name;
	int num=0;
	int chi_score=0;//语文成绩
	int math_score=0;
	int eng_score=0;
	double avg_score=0.0;

public:
	//计算平均成绩
	void avg()
	{
		avg_score = (chi_score + math_score + eng_score) / 3.0;
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
	//修改学生信息
	void change()
	{
		//首先输入修改的科目数量
		int n;
		cin >> n;
		//然后输入修改的科目和成绩
		for (int i = 0; i < n; ++i)
		{
			string subject;
			int score;
			cin >> subject >> score;
			if (subject == "1")
			{
				chi_score = score;
			}
			else if (subject == "2")
			{
				math_score = score;
			}
			else if (subject == "3")
			{
				eng_score = score;
			}
		}
		avg();//重新计算平均成绩
	}
};


int main()
{
	int num_students;
	cout << "请输入学生个数: ";
	cin >> num_students;

	Student* students = new Student[num_students];
	for (int i = 0; i < num_students; ++i)
	{
		string name;
		int num, chi_score, math_score, eng_score;
		//输入学生信息
		cin >> name >> num >> chi_score >> math_score >> eng_score;

		students[i].set(name, num, chi_score, math_score, eng_score);
		//修改学生信息
		students[i].change();
	}
	//输出所有学生信息
	for (int i = 0; i < num_students; ++i)
	{
		students[i].print();
	}

	delete[] students;
	return 0;
}
