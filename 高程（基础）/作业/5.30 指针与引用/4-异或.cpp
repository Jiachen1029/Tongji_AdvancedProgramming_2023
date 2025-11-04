#include <iostream>
#include <string.h>
using namespace std;

/****************** TODO ******************/
string& xor_str(string& dst, string src)
{
	int len1 = int(dst.length());
	int len2 = int(src.length());
	if (len1 < len2)//左侧补0
	{
		dst = string(len2 - len1, '0') + dst;
	}
	else if (len1 > len2)//左侧补0
	{
		src = string(len1 - len2, '0') + src;
	}
	for (int i = 0; i < dst.length(); i++)
	{
		if (dst[i] == src[i])
		{
			dst[i] = '0';
		}
		else
		{
			dst[i] = '1';
		}
	}
	return dst;
}
//因为dst是要被修改的，而src不需要被修改，所以dst需要加引用，而src不需要加引用
/**************** TODO-END ****************/

int main()
{
	string dst, src;
	cin >> dst >> src;

	xor_str(dst, src); // dst = dst ⊕ src
	cout << dst << endl;

	// 链式异或操作
	xor_str(xor_str(dst, src), src); // dst = dst ⊕ src ⊕ src
	cout << dst << endl;
	// 链式异或操作
	xor_str(dst, src) += src; // dst = dst ⊕ src + src
	cout << dst << endl;

	cout << src << endl;

	return 0;
}