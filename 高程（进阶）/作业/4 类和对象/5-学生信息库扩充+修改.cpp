#include<iostream>
#include<string>
using namespace std;

class SemesterGrad
{
public:
    int chinese;
    int math;
    int english;
    double average;
    void calculateAverage()
    {
        average = (chinese + math + english) / 3.0;
    }
};

class Student
{
public:
    string name;
    int id = 0;
    SemesterGrad semesters[4]{};

    void inputStudentInfo()
    {
        cout << "请输入学生姓名和学号：" << endl;
        cin >> name >> id;
        for (int i = 0; i < 4; ++i)
        {
            cout << "请输入第" << i + 1 << "学期的语文、数学、英语成绩：" << endl;
            cin >> semesters[i].chinese >> semesters[i].math >> semesters[i].english;
            semesters[i].calculateAverage();
        }
    }
    //更新学生信息
    //最后输入三个数字代表学期 科目 分数
    void updateStudentInfo()
    {
        int semester, subject, score;
        cout << "请输入要修改的学生信息的学期、科目、分数：" << endl;
        cin >> semester >> subject >> score;
        if (subject == 1)
        {
			semesters[semester-1].chinese=score;
		}
		else if(subject==2)
		{
			semesters[semester-1].math=score;
		}
        else if (subject == 3)
        {
            semesters[semester - 1].english = score;
        }
        semesters[semester - 1].calculateAverage();
	}

    void printStudentInfo()
    {
        cout << "==学生信息==" << endl;
        cout << "姓名：" << name << endl;
        cout << "学号：" << id << endl;
        cout << "==学期成绩==" << endl;
        for (int i = 0; i < 4; ++i)
        {
            cout << "=学期" << i + 1 << "=" << endl;
            cout << "语文成绩：" << semesters[i].chinese << endl;
            cout << "数学成绩：" << semesters[i].math << endl;
            cout << "英语成绩：" << semesters[i].english << endl;
            cout << "平均成绩：" << semesters[i].average << endl;
        }
    }
};

int main() {
    Student student;
    student.inputStudentInfo();
    student.updateStudentInfo();
    student.printStudentInfo();
    return 0;
}