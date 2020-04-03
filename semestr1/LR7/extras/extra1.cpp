#include <iostream>
#include <string>

using namespace std;

void replace(string str);

int main()
{
	string str;
	cout << "Enter the text: ";
	getline(cin, str);
	replace(str);
	return 0;
}

void replace(string str)
{
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == 'x')
		{
			str.resize(str.length() + 1);
			for (int j = str.length(); j > i + 1; j--)
			{
				str[j] = str[j - 1];
			}
			str[i] = 'k';
			str[i + 1] = 's';
		}
		if (str[i] == 'X')
		{
			str.resize(str.length() + 1);
			for (int j = str.length(); j > i + 1; j--)
			{
				str[j] = str[j - 1];
			}
			str[i] = 'K';
			str[i + 1] = 's';
		}
		if (str[i] == 'o' && str[i + 1] == 'o')
		{
			str[i] = 'u';
			for (int j = i + 1; j < str.length() - 1; j++)
			{
				str[j] = str[j + 1];
			}
			str[str.length() - 1] = '\0';
		}
		if (str[i] == 'O' && str[i + 1] == 'o')
		{
			str[i] = 'U';
			for (int j = i + 1; j < str.length() - 1; j++)
			{
				str[j] = str[j + 1];
			}
			str[str.length() - 1] = '\0';
		}
		if (str[i] == 't' && str[i + 1] == 'h')
		{
			str[i] = 'z';
			for (int j = i + 1; j < str.length() - 1; j++)
			{
				str[j] = str[j + 1];
			}
			str[str.length() - 1] = '\0';
		}
		if (str[i] == 'T' && str[i + 1] == 'h')
		{
			str[i] = 'Z';
			for (int j = i + 1; j < str.length() - 1; j++)
			{
				str[j] = str[j + 1];
			}
			str[str.length() - 1] = '\0';
		}
		if (str[i] == 'e' && str[i + 1] == 'e')
		{
			str[i] = 'i';
			for (int j = i + 1; j < str.length() - 1; j++)
			{
				str[j] = str[j + 1];
			}
			str[str.length() - 1] = '\0';
		}
		if (str[i] == 'E' && str[i + 1] == 'e')
		{
			str[i] = 'I';
			for (int j = i + 1; j < str.length() - 1; j++)
			{
				str[j] = str[j + 1];
			}
			str[str.length() - 1] = '\0';
		}
		if (str[i] == 'p' && str[i + 1] == 'h')
		{
			str[i] = 'f';
			for (int j = i + 1; j < str.length() - 1; j++)
			{
				str[j] = str[j + 1];
			}
			str[str.length() - 1] = '\0';
		}
		if (str[i] == 'P' && str[i + 1] == 'h')
		{
			str[i] = 'F';
			for (int j = i + 1; j < str.length() - 1; j++)
			{
				str[j] = str[j + 1];
			}
			str[str.length() - 1] = '\0';
		}
		if (str[i] == 'y' && str[i + 1] == 'o' && str[i + 2] == 'u')
		{
			str[i] = 'u';
			for (int j = i + 1; j < str.length() - 2; j++)
			{
				str[j] = str[j + 2];
			}
			str[str.length() - 2] = '\0';
			str[str.length() - 1] = '\0';
		}
		if (str[i] == 'Y' && str[i + 1] == 'o' && str[i + 2] == 'u')
		{
			str[i] = 'U';
			for (int j = i + 1; j < str.length() - 2; j++)
			{
				str[j] = str[j + 2];
			}
			str[str.length() - 2] = '\0';
			str[str.length() - 1] = '\0';

		}
		if (str[i] == 'w')
		{
			str[i] = 'v';
		}if (str[i] == 'W')
		{
			str[i] = 'V';
		}
		if (str[i] == 'c' && (str[i + 1] == 'e' || str[i + 1] == 'i' || str[i + 1] == 'y'))
		{
			str[i] = 's';
		}
		if (str[i] == 'C' && (str[i + 1] == 'e' || str[i + 1] == 'i' || str[i + 1] == 'y'))
		{
			str[i] = 'S';
		}
		if (str[i] == 'q' && str[i + 1] == 'u')
		{
			str[i] = 'k';
			str[i + 1] = 'v';
		}if (str[i] == 'Q' && str[i + 1] == 'u')
		{
			str[i] = 'K';
			str[i + 1] = 'v';
		}
		if (str[i] == 'q' || str[i] == 'c')
		{
			str[i] = 'k';
		}
		if (str[i] == 'Q' || str[i] == 'C')
		{
			str[i] = 'K';
		}
		if (str[i] == str[i + 1])
		{
			for (int j = i + 1; j < str.length() - 1; j++)
			{
				str[j] = str[j + 1];
			}
			str[str.length() - 1] = '\0';
		}
	}
	cout << str;
}