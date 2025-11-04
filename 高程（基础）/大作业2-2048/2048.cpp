#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <iomanip>
#include<random>
#include<ctime>
using namespace std;

void wait_for_enter();
void print_menu();
void print_help();
void print_exit();
void print_interface(int board[4][4], int score, int step);
void play_game();
int rand_board();
int rand_num();
void up(int board[4][4], int& score, int& step);//传递引用，可以改变数值
void down(int board[4][4], int& score, int& step);
void left(int board[4][4], int& score, int& step);
void right(int board[4][4], int& score, int& step);
bool win(int board[4][4]);
bool lose(int board[4][4]);

void play_game()
{
	int board[4][4] = {}; // 4*4的棋盘
	int score = 0;		  // 分数
	int step = 0;		  // 步数
	char choice = '\0';	  // 用户选择
	int start = 0;//看是不是第一次进入游戏
	// 游戏初始化，包括生成随机数等操作
	// 生成两个随机数,代表棋盘上的两个格子
	// 游戏开始时生成两个随机数放在这两个格子上面，有可能是2，也有可能是4，2的可能性更大，不妨定为90%
	int count = 0;
	while (count < 2)
	{
		int x = rand_board();
		int y = rand_board();
		if (board[x][y] == 0)//如果第二个生成的和第一个重合，那么也会重新生成
		{
			board[x][y] = rand_num();
			count++;
		}
	}
	// 打印游戏界面
	print_interface(board, score, step);
	while (1)
	{
		choice = _getch();// 获取用户输入
		switch (choice)// 根据用户输入进行相应操作
		{
		case 72://上
		{
			up(board, score, step);
			break;
		}
		case 80://下
		{
			down(board, score, step);
			break;
		}
		case 75://左
		{
			left(board, score, step);
			break;
		}
		case 77://右
		{
			right(board, score, step);
			break;
		}
		case 27://ESC键
		{
			cout << "是否退出游戏？（Y/y是，其他为否）" << endl;
			choice = _getch();
			if (choice == 'Y' || choice == 'y')
			{
				print_menu();
				return;
			}
			else
			{
				continue;
			}
		}
		}
		print_interface(board, score, step);// 打印游戏界面
		// 判断游戏是否结束，如果结束则跳出循环
		if (win(board)&&start==0)
		{
			cout << "恭喜你，获得2048，游戏胜利！" << endl;
			cout << endl;
			cout<<"是否继续游戏？（Y/y是，其他为否）" << endl;
			choice = _getch();
			if (choice == 'Y' || choice == 'y')
			{
				start = 1;
				continue;
			}
			else
			{
				wait_for_enter();
				break;
			}

		}
		if (lose(board))
		{
			cout << "很遗憾，游戏失败！" << endl;
			wait_for_enter();
			break;
		}
	}
}
int main()
{
	char choice = '\0';
	SetConsoleTitle(TEXT("2048"));	// 设置控制台标题为2048
	while (1)
	{
		print_menu();
		choice = _getche();

		// 根据用户选择进行相应操作
		switch (choice)
		{
		case 'a':
			play_game();
			break;
		case 'b':
			print_help();
			break;
		case'c':
			print_exit();
			return 0;
		default:
			cout << "\n输入错误，请从新输入" << endl;
			wait_for_enter();
		}
	}
	return 0;
}

//等待回车函数
void wait_for_enter()
{
	cout << endl << "按回车键继续";
	while (_getch() != '\r')
		;
	cout << endl << endl;
}
//菜单显示函数
void print_menu()
{
	// 清屏
	system("CLS");
	// 获取标准输出设备句柄
	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
	// 设置控制台文字颜色
	SetConsoleTextAttribute(handle_out, FOREGROUND_BLUE | FOREGROUND_GREEN);
	// 打印菜单
	cout << "--------------------------------------------\n";
	cout << "********************************************\n";
	// 设置控制台文字颜色
	SetConsoleTextAttribute(handle_out, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	// 打印标题
	cout << "                   2048\n";
	cout << "                a.经典模式\n";
	cout << "                b.游戏规则\n";
	cout << "                c.退出游戏\n";
	// 设置控制台文字颜色
	SetConsoleTextAttribute(handle_out, FOREGROUND_BLUE | FOREGROUND_GREEN);
	// 打印菜单
	cout << "********************************************\n";
	cout << "--------------------------------------------\n";
	// 恢复控制台文字颜色为默认颜色
	SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout << "\n请输入你的选择(a-c):";
}
//规则显示函数
void print_help()
{
	// 清屏
	system("CLS");
	// 获取标准输出设备句柄
	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
	// 设置控制台文字颜色
	SetConsoleTextAttribute(handle_out, FOREGROUND_BLUE | FOREGROUND_GREEN);
	cout << "--------------------------------------------\n";
	cout << "********************************************\n\n";
	// 设置控制台文字颜色
	SetConsoleTextAttribute(handle_out, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	// 打印游戏规则
	cout << "操作说明：\n\n";
	cout << "↓：下   ←：左  ↑：上  →：右  ESC键：退出\n\n";
	cout << "游戏介绍：\n\n";
	cout << "每次选择一个方向移动，移动时数字向该方向靠拢\n";
	cout << "相同数字可合并，移动后空格处会生成随机数字2/4\n";
	cout << "如果得到数字2048，则游戏胜利!\n";
	cout << "如果棋盘被数字填满，无法进行移动，则游戏失败!\n\n";
	// 设置控制台文字颜色
	SetConsoleTextAttribute(handle_out, FOREGROUND_BLUE | FOREGROUND_GREEN);
	cout << "********************************************\n";
	cout << "--------------------------------------------\n";
	// 恢复控制台文字颜色为默认颜色
	SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	wait_for_enter();
}
//退出显示函数
void print_exit()
{
	cout << "\n退出中";
	for (int i = 4; i > 0; --i)
	{
		Sleep(200);
		cout << ".";
	}
}
//界面显示函数
void print_interface(int board[4][4], int score, int step)
{
	// 清屏
	system("CLS");
	//获取标准输入设备句柄
	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
	// 设置控制台文字颜色
	SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN);
	// 打印游戏界面
	cout << "            --------------------------------------------\n";
	cout << "            分数：" << setw(6) << score << "              步数：" << setw(6) << step << endl;
	cout << "            --------------------------------------------\n";
	cout << "            ********************************************\n";
	// 设置控制台文字颜色
	SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "                       |----|----|----|----|\n";

	for (int i = 0; i < 4; i++)
	{
		cout << "                       |";
		for (int j = 0; j < 4; j++)
		{
			if (board[i][j] != 0)
			{
				cout << setw(4) << board[i][j] << "|";
			}
			else
			{
				cout << "    |";
			}
		}
		cout << "\n                       |----|----|----|----|\n";
	}
	// 设置控制台文字颜色
	SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN);
	cout << "            ********************************************\n";
	cout << "            --------------------------------------------\n";
	cout << "            ↓：下   ←：左  ↑：上  →：右  ESC键：退出\n\n";
	// 恢复控制台文字颜色为默认颜色
	SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}
//生成随机数函数
int rand_board()
{
	random_device rd;  // 用于获取随机数的种子
	mt19937 gen(rd()); // 使用 Mersenne Twister 算法生成随机数
	uniform_int_distribution<> dis(0, 3); // 定义随机数的分布范围[0,3]
	return dis(gen); // 生成随机数
}
int rand_num()
{
	random_device rd;  
	mt19937 gen(rd()); 
	uniform_int_distribution<> dis(0, 9); // 定义随机数的分布范围[0,9]
	int num = dis(gen);
	if (num < 9)
	{
		return 2;
	}
	else
	{
		return 4;
	}
}
//各个操作函数
void up(int board[4][4], int& score, int& step)
{
	bool flag = false;
	for (int j = 0; j <= 3; j++)
	{
		for (int i = 0; i <= 3; i++)
		{
			if (board[i][j] == 0)
			{
				for (int k = i + 1; k <= 3; k++)
				{
					if (board[k][j] != 0)
					{
						board[i][j] = board[k][j];
						board[k][j] = 0;
						flag = true;//如果可以去掉空格，可以移动
						break;
					}
				}
			}
		}//去掉空格子之后再去判断
		for (int i = 0; i <= 2; i++)
		{
			if (board[i][j] != 0 && board[i][j] == board[i + 1][j])
			{
				board[i][j] *= 2;
				score += board[i][j];
				for (int k = i + 1; k <= 2; k++)
				{
					board[k][j] = board[k + 1][j];
				}
				board[3][j] = 0;
				flag = true;
			}
		}
	}
	//更新数据
	if (flag == true)//如果有移动，那么步数可以增加，并且可以生成新的数字
	{
		step++;
		int x = rand_board();
		int y = rand_board();
		while (board[x][y] != 0)//如果有数字，那么重新生成
		{
			x = rand_board();
			y = rand_board();
		}
		board[x][y] = rand_num();
	}
}
void down(int board[4][4], int& score, int& step)
{
	bool flag = false;
	for (int j = 0; j <= 3; j++)
	{
		for (int i = 3; i >= 0; i--)
		{
			if (board[i][j] == 0)
			{
				for (int k = i - 1; k >= 0; k--)
				{
					if (board[k][j] != 0)
					{
						board[i][j] = board[k][j];
						board[k][j] = 0;
						flag = true;
						break;
					}
				}
			}
		}
		for (int i = 3; i >= 1; i--)
		{
			if (board[i][j] != 0 && board[i][j] == board[i - 1][j])
			{
				board[i][j] *= 2;
				score += board[i][j];
				for (int k = i - 1; k >= 1; k--)
				{
					board[k][j] = board[k - 1][j];
				}
				board[0][j] = 0;
				flag = true;
			}
		}
	}
	if (flag == true)
	{
		step++;
		int x = rand_board();
		int y = rand_board();
		while (board[x][y] != 0)
		{
			x = rand_board();
			y = rand_board();
		}
		board[x][y] = rand_num();
	}
}
void left(int board[4][4], int& score, int& step)
{
	bool flag = false;
	for (int i = 0; i <= 3; i++)
	{
		for (int j = 0; j <= 3; j++)
		{
			if (board[i][j] == 0)
			{
				for (int k = j + 1; k <= 3; k++)
				{
					if (board[i][k] != 0)
					{
						board[i][j] = board[i][k];
						board[i][k] = 0;
						flag = true;
						break;
					}
				}
			}
		}
		for (int j = 0; j <= 2; j++)
		{
			if (board[i][j] != 0 && board[i][j] == board[i][j + 1])
			{
				board[i][j] *= 2;
				score += board[i][j];
				for (int k = j + 1; k <= 2; k++)
				{
					board[i][k] = board[i][k + 1];
				}
				board[i][3] = 0;
				flag = true;
			}
		}
	}
	if (flag == true)
	{
		step++;
		int x = rand_board();
		int y = rand_board();
		while (board[x][y] != 0)
		{
			x = rand_board();
			y = rand_board();
		}
		board[x][y] = rand_num();
	}
}
void right(int board[4][4], int& score, int& step)
{
	bool flag = false;
	for (int i = 0; i <= 3; i++)
	{
		for (int j = 3; j >= 0; j--)
		{
			if (board[i][j] == 0)
			{
				for (int k = j - 1; k >= 0; k--)
				{
					if (board[i][k] != 0)
					{
						board[i][j] = board[i][k];
						board[i][k] = 0;
						flag = true;
						break;
					}
				}
			}
		}
		for (int j = 3; j >= 1; j--)
		{
			if (board[i][j] != 0 && board[i][j] == board[i][j - 1])
			{
				board[i][j] *= 2;
				score += board[i][j];
				for (int k = j - 1; k >= 1; k--)
				{
					board[i][k] = board[i][k - 1];
				}
				board[i][0] = 0;
				flag = true;
			}
		}
	}
	if (flag == true)
	{
		step++;
		int x = rand_board();
		int y = rand_board();
		while (board[x][y] != 0)
		{
			x = rand_board();
			y = rand_board();
		}
		board[x][y] = rand_num();
	}
}
//判断胜利/失败函数
bool win(int board[4][4])
{
	for (int i = 0; i <= 3; i++)
	{
		for (int j = 0; j <= 3; j++)
		{
			if (board[i][j] ==2048)
			{
				return true;
			}
		}
	}
	return false;
}
bool lose(int board[4][4])
{
	bool full = true;
	for (int i = 0; i <= 3; i++)
	{
		for (int j = 0; j <= 3; j++)
		{
			if (board[i][j] == 0)
			{
				full = false;
			}
		}
	}
	if (full == true)
	{
		for (int i = 0; i <= 3; i++)
		{
			for (int j = 0; j <= 3; j++)
			{
				if (i != 3 && board[i][j] == board[i + 1][j])
				{
					continue;
				}
				else if (i != 0 && board[i][j] == board[i - 1][j])
				{
					continue;
				}
				else if (j != 3 && board[i][j] == board[i][j + 1])
				{
					continue;
				}
				else if (j != 0 && board[i][j] == board[i][j - 1])
				{
					continue;
				}
				else
				{
					return true;
				}
			}
		}
	}
	return false;
}