#include <iostream>
#define BLOCK_NUM 200 // 盘块数量
#define INSTR_LENGTH 100 // 指令最大长度
using namespace std;

int memory[BLOCK_NUM] = {};  // 模拟内存

/****************** TODO ******************/
bool BlockManager(char instr[])
{
	int x, n, num;
	char op[10] = {};
	sscanf_s(instr, "%9s", op, (unsigned)_countof(op)); // 限制读取的字符数，防止溢出  
	if (op[0] == 'n')
	{
		sscanf_s(instr, "%9s %d %d", op, (unsigned)_countof(op), &x, &n);
		for (int i = x; i < x + n; i++)
		{
			if (memory[i] != 0)
			{
				cout << "失败" << endl;
				return true;
			}
			memory[i] = 1;
		}
		cout << "成功" << endl;
	}
	else if (op[0] == 'f')
	{
		sscanf_s(instr, "%9s %d %d", op, (unsigned)_countof(op), &x, &n);
		for (int i = x; i < x + n; i++)
		{
			if (memory[i] == 0)
			{
				cout << "失败" << endl;
				return true;
			}
			memory[i] = 0;
		}
		cout << "成功" << endl;
	}
	else if (op[0] == 'r')
	{
		sscanf_s(instr, "%9s %d", op, (unsigned)_countof(op), &x);
		if (memory[x] == 0)
		{
			cout << "失败" << endl;
			return true;
		}
		cout << "成功" << endl;
		cout << memory[x] << endl;
	}
	else if (op[0] == 'w')
	{
		sscanf_s(instr, "%9s %d %d", op, (unsigned)_countof(op), &x, &num);
		if (memory[x] == 0)
		{
			cout << "失败" << endl;
			return true;
		}
		memory[x] = num;
		cout << "成功" << endl;
	}
	else if (op[0] == 'q')
	{
		return false;
	}
	return true;
}
/**************** TODO-END ****************/

int main()
{
	char instr[INSTR_LENGTH] = {}; // 输入的指令
	cin.getline(instr, INSTR_LENGTH);

	while (BlockManager(instr)) {
		cin.getline(instr, INSTR_LENGTH);
	}

	return 0;
}