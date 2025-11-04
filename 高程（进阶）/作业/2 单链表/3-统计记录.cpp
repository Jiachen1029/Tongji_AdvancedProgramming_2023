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
    cout << "统计信息如下：";
    student* current = head;
    int u = 0, l = 0, z = 0, k = 0, c = 0;//优良中可差
    while (current)
    {
        if (current->score >= 90)
            u++;
        else if(current->score >= 80)
            l++;
		else if(current->score >= 70)
			z++;
		else if(current->score >= 60)
			k++;
		else
			c++;//有else if，不会重复计数
        student* temp = current;
        current = current->next;
        delete temp;
    }
    cout << "优: " << u << "人  良: " << l << "人  中: " << z << "人  及格: " << k << "人  不及格: " << c << "人" << endl;
    return 0;
}