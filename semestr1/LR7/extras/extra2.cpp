#include <iostream>

using namespace std;

int size(unsigned long long int num);
bool check(unsigned long long int* arr, unsigned long long int num, int size);
unsigned long long int* transfer(unsigned long long int num, int size);

int main()
{
	int num;
	cout << "Enter the number: ";
	cin >> num;
	unsigned long long int* list = new unsigned long long int[num];
	for (unsigned long long int i = 1, j = 0; j < num; i++)
	{
		if (check(transfer(i, size(i)), i, size(i)))
		{
			list[j] = i;
			j++;
		}

	}
	cout << "Your number is: " << list[num - 1];
	delete[]list;
	return 0;
}

int size(unsigned long long int num)
{
	unsigned long long int a = num;
	int size = 0;
	while (a != 0)
	{
		size++;
		a /= 10;
	}
	return size;
}

unsigned long long int* transfer(unsigned long long int num, int size)
{
	unsigned long long int* arr = new unsigned long long int[size];
	for (int i = size - 1; i >= 0; i--)
	{
		arr[i] = num % 2;
		num /= 2;
	}
	return arr;
}

bool check(unsigned long long int* arr, unsigned long long int num, int size)
{
	bool c = true;
	for (unsigned long long int i = size - 1; num != 0; i--)
	{
		if (arr[i] == num % 10)
		{
			num /= 10;
		}
		else
		{
			c = false;
			break;
		}
	}
	delete[]arr;
	return c;
}