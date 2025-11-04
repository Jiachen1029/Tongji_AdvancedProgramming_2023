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

void sort(student*& head)
{
    if (!head || !head->next)
        return; // 链表为空或只有一个结点
    student* sorted = nullptr; // 排序后的链表
    student* current = head;

    while (current)
    {
        student* next = current->next;
        if (!sorted || current->score > sorted->score ||
            (current->score == sorted->score && current->no < sorted->no))
        {
            current->next = sorted;
            sorted = current;
        }
        else
        {
            student* temp = sorted;
            while (temp->next && (temp->next->score > current->score ||
                (temp->next->score == current->score && temp->next->no < current->no)))
            {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }
    head = sorted;
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
        cout << "请输入要添加的学生学号: ";
        cin >> query;
        student* found_student = searchbyID(head, query); //执行查询
        if (found_student)
        {
            cout << "已存在" << endl;
        }
        else
        {
            student* new_student = new (nothrow) student;
            if (!new_student)
            {
                cout << "内存分配失败！" << endl;
                return 1;
            }
            new_student->no = query;
            cout << "请输入姓名: ";
            cin >> new_student->name;
            cout << "请输入成绩: ";
            cin >> new_student->score;
            new_student->next = head;
            head = new_student;
        }
        if (!isContinue())
        {
            break; //退出循环
        }
    }
    sort(head); //排序
    printStudents(head); //打印现有学生信息
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