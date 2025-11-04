#include<iostream>
#include<cstring>
char charr1[250], charr2[250][30];
void jieduan();//½Ø¶Ï
void shanchu();//É¾³ý
int main()
{
	using namespace std;
	cin.getline(charr1, 250);
	jieduan();
	shanchu();
	return 0;
}
void jieduan()
{
	using namespace std;
	int n = 0, i = 0, j = 0;
	while (n < 250)
	{
		if ((charr1[n] <= 57 && charr1[n] >= 48) || (charr1[n] <= 90 && charr1[n] >= 65) || (charr1[n] <= 122 && charr1[n] >= 97) || charr1[n] == 39 || charr1[n] == 45)
		{
			i++;
			if ((n > 0) && ((charr1[n - 1] <= 57 && charr1[n - 1] >= 48) || (charr1[n - 1] <= 90 && charr1[n - 1] >= 65) || (charr1[n - 1] <= 122 && charr1[n - 1] >= 97) || charr1[n - 1] == 39 || charr1[n - 1] == 45))
				i--;
			charr2[i][j] = charr1[n];
			j++;
		}
		else
		{
			i++, j = 0;
			charr2[i][j] = charr1[n];
		}
		n++;
	}
}
void shanchu()
{
	using namespace std;
	int n = 0;
	while (n < 248)
	{
		if (strcmp(charr2[n], charr2[n + 2]) == 0 && charr2[n + 1][0] == ' ')
		{
			charr2[n][0] = '\0';
			charr2[n + 1][0] = '\0';
		}
		cout << charr2[n];
		n++;
	}
}