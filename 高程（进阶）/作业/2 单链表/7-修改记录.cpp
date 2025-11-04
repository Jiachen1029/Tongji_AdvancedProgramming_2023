#include <iostream>
#include <fstream>
#include <new>
using namespace std;

struct student
{
    int no;                // 学号
    char name[20];         // 姓名
    int score;             // 成绩
    struct student* next;  // 下一结点
};

student* read(const char* filename)
{
    ifstream file(filename); // 打开文件
    if (!file)
    {
        cout << "无法打开文件！" << endl;
        return nullptr;
    }
    int m;
    file >> m; //读取学生人数
    student* head = nullptr; //头指针
    student* tail = nullptr; //尾指针

    for (int i = 0; i < m; ++i)
    {
        student* new_student = new (nothrow) student; //分配内存
        if (!new_student)
        {
            cout << "内存分配失败！" << endl;
            return nullptr;
        }
        file >> new_student->no >> new_student->name >> new_student->score; //学生信息
        new_student->next = nullptr;
        if (!head)
        {
            head = new_student;
        }
        else
        {
            tail->next = new_student;
        }
        tail = new_student; //将新结点设为尾结点
    }
    file.close();
    return head;
}

bool isContinue()
{
    cout << "是否继续?(y/n): \n";
    char tmp;
    cin >> tmp;
    if (tmp == 'Y' || tmp == 'y')
    {
        return true;
    }
    return false;
}

student* searchbyID(student* head, int query)
{
    student* current = head;
    while (current)
    {
        if (current->no == query)
        {
            return current;
        }
        current = current->next;
    }
    cout << "不存在" << endl;
    return nullptr;
}

void printStudents(student* head)
{
    student* current = head;
    while (current)
    {
        cout << "学号:" << current->no << " 姓名:" << current->name << " 成绩:" << current->score << endl;
        current = current->next;
    }
}

int main()
{
    student* head = read("student.txt"); //读取文件
    if (!head)
    {
        return 1;
    }

    while (1)
    {
        int query;
        cout << "请输入要修改的学生学号: ";
        cin >> query;
        student* found_student = searchbyID(head, query); //执行查询
        if (found_student)
        {
            int new_score;
            cout << "请输入新的成绩: ";
            cin >> new_score;
            found_student->score = new_score; //更新成绩
        }
        if (!isContinue())
        {
            break; //退出循环
        }
    }
    printStudents(head); //打印剩余学生信息

    //释放链表内存
    student* current = head;
    while (current)
    {
        student* temp = current;
        current = current->next;
        delete temp;
    }
    return 0;
}