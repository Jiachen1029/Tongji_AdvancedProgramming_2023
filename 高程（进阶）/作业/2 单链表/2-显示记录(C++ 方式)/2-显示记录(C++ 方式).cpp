#include <iostream>
#include <fstream>
#include <new>

using namespace std;

struct student {
    int no;                // 学号
    char name[20];         // 姓名
    int score;             // 成绩
    struct student* next;  // 下一结点
};

int main() {
    ifstream file("student.txt");//打开文件
    if (!file) {
        cout << "无法打开文件！" << endl;
        return 1;
    }
    int m;
    file >> m;//读取学生人数
    student* head = nullptr;//头指针
    student* tail = nullptr;//尾指针

    for (int i = 0; i < m; ++i) 
    {
        student* new_student = new (nothrow) student;//分配内存
        if (!new_student) 
        {
            cout << "内存分配失败！" << endl;
            return 1;
        }
        file >> new_student->no >> new_student->name >> new_student->score;//读取学生信息
        new_student->next = nullptr;
        if (!head) {
            head = new_student;
        }
        else {
            tail->next = new_student;
        }
        tail = new_student;//将新结点设为尾结点
    }
    file.close();
    cout << "所有的学生信息如下：" << endl;
    student* current = head;
    while (current) 
    {
        cout << "学号:" << current->no << " 姓名:" << current->name << " 成绩:" << current->score << endl;
        student* temp = current;
        current = current->next;
        delete temp;
    }
    return 0;
}
