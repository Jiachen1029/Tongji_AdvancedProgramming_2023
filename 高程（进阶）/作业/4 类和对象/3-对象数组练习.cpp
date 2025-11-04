#include<iostream>
using namespace std;

class Student
{
public:
	int num;
	float score;
	Student* p;	//指针
};

int main()
{
	Student students[5]{}; //创建一个包含5个学生的数组
	Student* p = students; //指针指向数组首元素

	//输入学生数据
	for (int i = 0; i < 5; i++)
	{
		cout << "请输入第" << i + 1 << "个学生的学号和成绩:";
		cin >> students[i].num >> students[i].score;
	}

	cout << "第1个学生的学号和成绩：" << p->num << " " << p->score << endl;
	cout << "第3个学生的学号和成绩：" << (p + 2)->num << " " << (p + 2)->score << endl;
	cout << "第5个学生的学号和成绩：" << (p + 4)->num << " " << (p + 4)->score << endl;

	return 0;
}