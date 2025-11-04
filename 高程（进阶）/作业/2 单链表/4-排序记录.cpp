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

student* read(const char* filename, int& count)
{
    ifstream file(filename); // 打开文件
    if (!file)
    {
        cout << "无法打开文件！" << endl;
        return nullptr;
    }
    file >> count; // 读取学生人数
    student* head = nullptr; // 头指针
    student* tail = nullptr; // 尾指针

    for (int i = 0; i < count; ++i)
    {
        student* new_student = new (nothrow) student; // 分配内存
        if (!new_student)
        {
            cout << "内存分配失败！" << endl;
            return nullptr;
        }
        file >> new_student->no >> new_student->name >> new_student->score; // 读取学生信息
        new_student->next = nullptr;
        if (!head)
        {
            head = new_student;
        }
        else
        {
            tail->next = new_student;
        }
        tail = new_student; // 将新结点设为尾结点
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

void print_students(const student* head)
{
    cout << "排序后的学生信息如下：" << endl;
    const student* current = head;
    while (current)
    {
        cout << "学号:" << current->no << " 姓名:" << current->name << " 成绩:" << current->score << endl;
        current = current->next;
    }
}

void free_memory(student* head)
{
    while (head)
    {
        student* temp = head;
        head = head->next;
        delete temp;
    }
}

int main()
{
    int count;
    student* head = read("student.txt", count);
    if (!head) return 1;
    sort(head);
    print_students(head);
    free_memory(head);
    return 0;
}
