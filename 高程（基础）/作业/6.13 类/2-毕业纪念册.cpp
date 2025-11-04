#include <iostream>
#include <iomanip>
using namespace std;

class StudentInfo {
    /****************** TODO ******************/
private:
	string name{};
	char studentid[8]{};
	string sex{};
	string constellation{};
	char hobby[100]{};
	char saying[60]{};
    /**************** TODO-END ****************/

public:
    void inputStudentInfo();
    void printStudentInfo();
};

/****************** TODO ******************/
void StudentInfo::inputStudentInfo() 
{
    cin >> name >> studentid >> sex >> constellation;
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 忽略换行符
	cin.getline(hobby, 100);
	cin.getline(saying, 60);
}
void StudentInfo::printStudentInfo()
{
	//先判断是否输入错误
	if (sex!="F"&&sex!="M")
	{
		cout << "输入错误" << endl;
		return;
	}
	for (int i = 0; i < 8; i++)
	{
		if (studentid[i] < '0' || studentid[i]>'9')
		{
			cout << "输入错误" << endl;
			return;
		}
	}
	//姓名
	cout << "姓名：" << name << endl;
	//学号
	cout << "学号：" << studentid << endl;
    //性别
	if (sex == "M")
        cout << "性别：男" << endl;
    else
        cout << "性别：女" << endl;
    //星座
	cout << "星座：";
    if (constellation == "Ari")
		cout << "白羊座" << endl;
	else if (constellation == "Tau")
		cout << "金牛座" << endl;
	else if (constellation == "Gem")
		cout << "双子座" << endl;
	else if (constellation == "Cnc")
		cout << "巨蟹座" << endl;
	else if (constellation == "Leo")
		cout << "狮子座" << endl;
	else if (constellation == "Vir")
		cout << "处女座" << endl;
	else if (constellation == "Lib")
		cout << "天秤座" << endl;
	else if (constellation == "Sco")
		cout << "天蝎座" << endl;
	else if (constellation == "Sgr")
		cout << "射手座" << endl;
	else if (constellation == "Cap")
		cout << "摩羯座" << endl;
	else if (constellation == "Agr")
		cout << "水瓶座" << endl;
	else if (constellation == "Psc")
		cout << "双鱼座" << endl;
	else
		cout << "无" << endl;
	//爱好
	cout << "爱好：";
	if (hobby[0] != '\\')
	{
		cout << hobby << endl;
	}
	else
		cout << "无" << endl;
	//赠言
		if (saying[0] != '\\')
		cout << "赠言：" << saying << endl;
	else
		cout << "赠言：无" << endl;
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