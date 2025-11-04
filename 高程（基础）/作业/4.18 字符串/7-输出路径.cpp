#include<iostream>
using namespace std;

int main()
{
	char input[200]{};
	char output[200]{ "C:\\Users\\Student" };
	char tempo[200]{};
	int suojin;
	int i = -1;
	while (++i < strlen(output))
	{
		cout << output[i];
	}
	cout << endl;
	while (cin.getline(input, 200))
	{
		suojin = 3;//用来记录上一个\的位置
		if (input[0] == 'q')
		{
			break;
		}
		else
		{
			i = 2; while (++i <= strlen(input))
			{
				if (input[i] != '\\' && i != strlen(input))
				{
					tempo[i - suojin] = input[i];
					continue;
				}
				if (input[i] == '\\' || i == strlen(input))
				{
					tempo[i - suojin] = '\0';
					suojin = i + 1;
					if (tempo[0] == '.' && strlen(tempo) == 1)
					{
						continue;
					}
					else if (tempo[0] == '.' && tempo[1] == '.' && strlen(tempo) == 2)
					{
						long long c = long long(strlen(output));
						while (--c > 0)
						{
							if (output[c] == '\\' && output[c - 1] != ':')
							{
								output[c] = '\0';
								break;
							}
							else if (output[c] == '\\' && output[c - 1] == ':')
							{
								output[c + 1] = '\0';
								break;
							}
							continue;
						}
					}
					else
					{
						long long l = long long (strlen(output));
						if (output[l - 1] != '\\')
							output[l] = '\\';
						else if (output[l - 1] == '\\')
							l--;
						int j = -1;
						while (++j < strlen(tempo))
							output[l + j + 1] = tempo[j];
						output[l + strlen(tempo) + 1] = '\0';
						continue;
					}
				}
			}
		}
		i = -1;
		while (++i < strlen(output))
			cout << output[i]; 
		cout << endl;
	}
	return 0;
}

