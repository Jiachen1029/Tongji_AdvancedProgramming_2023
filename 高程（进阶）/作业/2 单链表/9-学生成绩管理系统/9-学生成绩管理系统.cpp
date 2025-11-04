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
    //输出排序后的链表
    student* current1 = head;
    while (current1)
    {
        cout << "学号:" << current1->no << " 姓名:" << current1->name << " 成绩:" << current1->score << endl;
        current1 = current1->next;
    }
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
void disp(student* head)
{
    student* current = head;
    while (current)
    {
        cout << "学号:" << current->no << " 姓名:" << current->name << " 成绩:" << current->score << endl;
        current = current->next;
    }
}
void addbyID(student*& head, int query)
{
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
            return;
        }
        new_student->no = query;
        cout << "请输入姓名: ";
        cin >> new_student->name;
        cout << "请输入成绩: ";
        cin >> new_student->score;
        new_student->next = head;
        head = new_student;
    }
}
void delbyID(student*& head, int query)
{
    student* current = head;
    student* prev = nullptr;
    while (current)
    {
        if (current->no == query)
        {
            if (prev)
            {
                prev->next = current->next;
            }
            else
            {
                head = current->next;
            }
            delete current;
            cout << "删除成功" << endl;
            return;
        }
        prev = current;
        current = current->next;
    }
    cout << "不存在" << endl;
}
void modibyID(student*& head, int query)
{
    student* found_student = searchbyID(head, query);
    if (found_student)
    {
        cout << "请输入新的成绩: ";
        cin >> found_student->score;
        cout << "修改成功" << endl;
    }
    else
    {
        cout << "不存在" << endl;
    }
}
void count(student* head)
{
    student* current = head;
    int u = 0, l = 0, z = 0, k = 0, c = 0; //优良中可差
    while (current)
    {
        if (current->score >= 90)
            u++;
        else if (current->score >= 80)
            l++;
        else if (current->score >= 70)
            z++;
        else if (current->score >= 60)
            k++;
        else
            c++; //有else if，不会重复计数
        current = current->next;
    }
    cout << "优: " << u << "人  良: " << l << "人  中: " << z << "人";
    cout << "  及格: " << k << "人  不及格: " << c << "人" << endl;
}
void quit(student*& head)
{
    student* current = head;
    while (current)
    {
        student* temp = current;
        current = current->next;
        delete temp;
    }
    head = nullptr;
}
void menu()
{
    int i;
    cout << endl;
    for (i = 0; i < 57; i++)
    {
        cout << '*';
    }
    cout << std::endl;
    cout << "*\t1 显示记录\t2 统计记录\t3 排序记录\t*\n";
    cout << "*\t4 查找记录\t5 删除记录\t6 修改记录\t*\n";
    cout << "*\t7 添加记录\t0 退出系统\t\t\t*\n";
    for (i = 0; i < 57; i++)
    {
        cout << '*';
    }
}

int main()
{
    student* head = read("student.txt"); //读取文件
    if (!head)
    {
        return 1;
    }
    menu();
    while (true)
    {
        int choice;
        cout << endl;
        cout << "选择菜单项(0~7):";
        cin >> choice;
        if (choice == 0) // 选择退出
        {
            cout << "\n 确定退出吗?(y/n)" << std::endl;
            char ch;
            cin >> ch;
            if (ch == 'y' || ch == 'Y')
            {
                quit(head);
                break;
            }
            else
                continue;
        }
        switch (choice)
        {
        case 1://显示记录
            disp(head);
            break;
        case 2://统计记录
            count(head);
            break;
        case 3://排序记录
            sort(head);
            break;
        case 4://查找记录
        {
            while (true)
            {
                cout << "请输入要查找的学号: ";
                int query;
                cin >> query;
                student* found_student = searchbyID(head, query);
                if (found_student)
                {
                    cout << "学号:" << found_student->no << " 姓名:" << found_student->name << " 成绩:" << found_student->score << endl;
                }
                else
                {
                    cout << "不存在" << endl;
                }
                cout << "继续查找吗?(y/n)" << endl;
                char ch;
                cin >> ch;
                if (ch == 'n' || ch == 'N')
                {
                    break;
                }
            }
            break;
        }
        case 5://删除记录
        {
            while (true)
            {
                cout << "请输入要删除的学号: ";
                int query;
                cin >> query;
                delbyID(head, query);
                cout << "继续删除吗?(y/n)" << endl;
                char ch;
                cin >> ch;
                if (ch == 'n' || ch == 'N')
                {
                    break;
                }
            }
            break;
        }
        case 6://修改记录
        {
            while (true)
            {
                cout << "请输入要修改的学号: ";
                int query;
                cin >> query;
                modibyID(head, query);
                cout << "继续修改吗?(y/n)" << endl;
                char ch;
                cin >> ch;
                if (ch == 'n' || ch == 'N')
                {
                    break;
                }
            }
            break;
        }
        case 7://添加记录
        {
            while (true)
            {
                cout << "请输入要添加的学号: ";
                int query;
                cin >> query;
                addbyID(head, query);
                cout << "继续添加吗?(y/n)" << endl;
                char ch;
                cin >> ch;
                if (ch == 'n' || ch == 'N')
                {
                    break;
                }
            }
            break;
        }
        default:
            cout << "输入错误，请从新输入" << endl;
            break;
        }
    }
    //退出前释放内存
    quit(head);
    return 0;
}