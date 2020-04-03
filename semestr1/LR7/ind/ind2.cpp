#include <iostream>

using namespace std;

bool check(int* code, int size);
void transfer(int* code, int size);

int main()
{
	const int size = 8;
	int code[size];
	cout << "Enter number in direct code: ";
	for (int i = 0; i < size; i++)
	{
		cin >> code[i];
	}

	if (check(code, size))
	{
		cout << "Your number in direct code: ";
		for (int i = 0; i < size; i++)
		{
			cout << code[i];
		}
		cout << endl;

		cout << "Number in additional code: ";
		transfer(code, size);
	}
	else cout << "Incorrect input";
	return 0;
}

bool check(int* code, int size)
{
	bool c = true;
	for (int i = 0; i < size; i++)
	{
		if (code[i] == 1 || code[i] == 0)
		{
			c = true;
		}
		else
		{
			c = false;
			break;
		}
	}
	return c;
}

void transfer(int* code, int size)
{
	if (code[0] == 1)
	{
		for (int i = 1; i < size; i++)
		{
			if (code[i] == 1)
			{
				code[i] = 0;
			}
			else
			{
				code[i] = 1;
			}
		}

		if (code[size - 1] == 0)
		{
			code[size - 1] = 1;
		}
		else
		{
			code[size - 1] = 2;
			for (int i = size - 2; i > 0; i--)
			{
				if (code[i] == 1 && code[i + 1] == 2)
				{
					code[i]++;
				}
				else if (code[i] == 0 && code[i + 1] == 2)
				{
					code[i]++;
					break;
				}
			}

			for (int i = 1; i < size; i++)
			{
				if (code[i] == 2)
				{
					code[i] = 0;
				}
			}
		}
	}
	for (int i = 0; i < size; i++)
	{
		cout << code[i];
	}
}