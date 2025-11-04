#define _CRT_SECURE_NO_WARNING
#include<iostream>
#include<stdio.h>

using namespace std;
struct student {
	int no;                // 学号
	char name[20];         // 姓名
	int score;             // 成绩
	struct student* next;  // 下一结点
};
int main()
{
	FILE* fp = nullptr;
	fp = fopen("student.txt", "r");//打开文件
	int* total = new(nothrow) int;
	int s = fscanf(fp, "%d", total);
	
	struct student* head, * p, * q;
	head = new(nothrow) student;
	if (head == NULL)
		return 0;
	head->next = NULL;
	p = head;
	while (!feof(fp))
	{
		q = new(nothrow) student;
		if (q == NULL)
		{
			return 0;
		}
		int s = fscanf(fp, "%d %s %d", &q->no, q->name, &q->score);
		p->next = q;
		p = q;
	}
	p->next = NULL;
	fclose(fp);
	p = head->next;
	cout << "所有的学生信息如下：" << endl;
	while (p != NULL)
	{
		cout << "学号：" << p->no << " 姓名：" << p->name << " 成绩：" << p->score << endl;
		p = p->next;
	}
	p = head->next;
	while (p != NULL)
	{
		q = p;
		p = p->next;
		delete q;//释放内存
	}
	delete head;
	return 0;
}