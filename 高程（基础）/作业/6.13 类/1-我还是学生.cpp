#include <iostream>
#include <iomanip>
using namespace std;

class StudentInfo {
    /****************** TODO ******************/
private:
    char name[100]{};
    char major[100]{};
    int year; 
    double score; 
    /**************** TODO-END ****************/

public:
    void inputStudentInfo();
    void printStudentInfo();
};

/****************** TODO ******************/
void StudentInfo::inputStudentInfo() 
{
	cin.getline(StudentInfo::name, 100);
    cin.getline(StudentInfo::major, 100);
    cin>> year >> score;
}
void StudentInfo::printStudentInfo()
{
    cout << "学生信息：" << endl;
    cout << "姓名：" << name << endl;
    cout << "专业：" << major << endl;
    cout << "入学年份：" << year << endl;
    cout << "平均绩点：" << fixed << setprecision(2) << score << endl;

}
/**************** TODO-END ****************/

int main()
{
    StudentInfo student;
    // 输入学生信息
    student.inputStudentInfo();
    // 输出学生信息
    student.printStudentInfo();

    return 0;
}