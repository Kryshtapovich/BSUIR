#include <iostream>

using namespace std;

bool check(string code, int size);
int length(string num);
int* transfer_to_int(string num, int size);
int* transfer_to_add_code(int* arr, int size);
void sum(int* arr1, int* arr2, int size);

int main()
{
	string num1, num2;
	int size = 8;
	cout << "Enter the first binary number in natural form: ";
	cin >> num1;
	cout << "Enter the second binary number in natural form: ";
	cin >> num2;

	if (check(num1, length(num1)) && check(num2, length(num2)) && length(num1) <= size && length(num2) <= size)
		sum(transfer_to_add_code(transfer_to_int(num1, length(num1)), size), transfer_to_add_code(transfer_to_int(num2, length(num2)), size), size);
	else cout << "Incorrect input";
	return 0;
}

bool check(string code, int size)
{
	bool c = true;
	if (code[0] == '-' || code[0] == '+')
	{
		for (int i = 1; i < size; i++)
		{
			if (code[i] == '1' || code[i] == '0')
			{
				c = true;
			}
			else
			{
				c = false;
				break;
			}
		}
	}
	else
	{
		c = false;
	}
	return c;
}

int length(string num)
{
	int size = 0;
	for (int i = 0; num[i] != '\0'; i++)
	{
		size++;
	}
	return size;
}

int* transfer_to_int(string num, int size)
{
	int count = 8;
	int* intcode = new int[count];

	if (num[0] == '-')
	{
		intcode[0] = 1;
	}
	else
	{
		intcode[0] = 0;
	}

	for (int i = 1; i < count - size + 1; i++)
	{
		intcode[i] = 0;
	}

	for (int i = count - size + 1, j = 1; i < count; i++, j++)
	{
		intcode[i] = num[j] - '0';
	}

	return intcode;
}

int* transfer_to_add_code(int* arr, int size)
{
	if (arr[0] == 1)
	{
		for (int i = 1; i < size; i++)
		{
			if (arr[i] == 1) arr[i] = 0;
			else arr[i] = 1;
		}

		if (arr[size - 1] == 0) arr[size - 1] = 1;
		else
		{
			arr[size - 1] = 2;
			for (int i = size - 2; i > 0; i--)
			{
				if (arr[i] == 1 && arr[i + 1] == 2) arr[i]++;
				else
				{
					arr[i]++;
					break;
				}
			}
			for (int i = 1; i < size; i++)
			{
				if (arr[i] == 2) arr[i] = 0;
			}
		}
	}
	return arr;
}

void sum(int* arr1, int* arr2, int size)
{
	arr1[size - 1] += arr2[size - 1];
	for (int i = size - 2; i >= 0; i--)
	{
		if (arr1[i + 1] == 2 || arr1[i + 1] == 3) arr1[i] += arr2[i] + 1;
		else arr1[i] += arr2[i];
	}

	for (int i = 0; i < size; i++)
	{
		if (arr1[i] == 2) arr1[i] = 0;
		else if (arr1[i] == 3)arr1[i] = 1;
	}

	if (arr1[0] == 1)
	{
		for (int i = 1; i < size; i++)
		{
			if (arr1[i] == 1)arr1[i] = 0;
			else arr1[i] = 1;
		}
		arr1[size - 1]++;
		for (int i = size - 2; i > 0; i--)
		{
			if (arr1[i + 1] == 2)arr1[i]++;
			else break;
		}
		for (int i = 0; i < size; i++)
		{
			if (arr1[i] == 2)arr1[i] = 0;
		}
	}

	int count = 0;
	for (int i = 1; arr1[i] == 0; i++)count++;
	if (count == size - 1) cout << "Result of addtiton: " << 0;
	else
	{
		if (arr1[0] == 1)cout << "Result of addition: -";
		else cout << "Result of addition: +";
		for (int i = count + 1; i < size; i++)cout << arr1[i];
	}
	delete arr1;
	delete arr2;
}