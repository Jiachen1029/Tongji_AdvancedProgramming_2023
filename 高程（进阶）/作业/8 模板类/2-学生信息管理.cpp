#include <iostream>
#include <memory>
#include <vector>
#include <string>
using namespace std;

class Student {
public:
    Student(int id, const string& name) : id(id), name(name) {}

    int getId() const { return id; }
    string getName() const { return name; }

private:
    int id;
    string name;
};

class StudentManagementSystem {
public:
    void addStudent(unique_ptr<Student> stu) {
        /****************** TODO ******************/
        //unique_ptr合理：
        //独占所有权：每个 Student 对象的所有权是唯一的，不会在多个地方共享
        //自动内存管理：当 unique_ptr 超出作用域时，它会自动释放内存，避免内存泄漏
        //学生对象的所有权不需要共享，因此 unique_ptr更合适
        Students.push_back(move(stu));// 添加学生  
        /**************** TODO-END ****************/
    }

    void findAndPrintStudent(int id) {
        Student* stu = nullptr;
        /****************** TODO ******************/
        // 查找学生编号为id的学生
        for (const auto& student : Students) {
            if (student->getId() == id) {
                stu = student.get();
                break;
            }
        }
        /**************** TODO-END ****************/
        if (stu != nullptr) {
            cout << "学生编号: " << stu->getId() << "，姓名: " << stu->getName() << endl;
        }
        else {
            cout << "未找到该学生" << endl;
        }
    }

private:
    vector<unique_ptr<Student>> Students;
};

int main() {
    StudentManagementSystem stus;

    int id;
    string name;
    cout << "请依次输入学生编号和姓名：" << endl;
    while (true) {
        cin >> id;
        if (id == -1) {
            break;
        }

        cin.ignore();  // 忽略前面输入编号后的空格
        getline(cin, name);
        /****************** TODO ******************/
		stus.addStudent(make_unique<Student>(id, name));//添加学生
        /**************** TODO-END ****************/
    }

    cout << "请输入要查找的学生编号: " << endl;
    cin >> id;
    stus.findAndPrintStudent(id);

    return 0;
}
