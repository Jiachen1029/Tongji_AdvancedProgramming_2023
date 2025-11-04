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
    int id=0;
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
    student.printStudentInfo();
    return 0;
}