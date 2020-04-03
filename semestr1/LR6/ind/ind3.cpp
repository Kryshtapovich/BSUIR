#include <iostream>

using namespace std;

void check(char** arr, int rows);
char* deletespace(char* arr);
int length(char* arr);

int main() {
	int rows, columns = 80;
	cout << "Enter number of strings: ";
	cin >> rows;
	char** arr = new char* [rows];
	for (int i = 0; i < rows; i++)
	{
		arr[i] = new char[columns];
	}

	cin.clear();
	cin.ignore();

	for (int i = 0; i < rows; i++)
	{
		cin.getline(arr[i], columns);
	}

	check(arr, rows);

	for (int i = 0; i < rows; i++)
	{
		delete[]arr[i];
	}
	delete[]arr;
	return 0;
}

int length(char* arr)
{
	int length = 0;
	for  (int i = 0; arr[i] != '\0'; i++)
	{
		length++;
	}
	return length;
}

char* deletespace(char* arr)
{
	int cnt_space = 0;
	for (int i = 0; i < length(arr); i++)
	{
		if (arr[i] == ' ')
		{
			cnt_space++;
			for (int j = i; j < length(arr) - 1; j++)
			{
				arr[j] = arr[j + 1];
			}
		}
	}
	arr[length(arr) - cnt_space] = '\0';
	return arr;
}

void check(char** arr, int rows)
{
	for (int i = 0; i < rows; i++)
	{
		arr[i] = deletespace(arr[i]);
	}
	cout << endl;
	int count = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < length(arr[i]); j++)
		{
			if (arr[i][j] == arr[i][length(arr[i]) - j - 1])
			{
				count++;
			}
		}
		if (count == length(arr[i]))
		{
			cout << i + 1 << " string is palindrome" << endl;
		}
		else
		{
			cout << i + 1 << " string isn't palindrome" << endl;
		}
		count = 0;
	}
}