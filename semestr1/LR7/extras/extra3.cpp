#include <iostream>

using namespace std;

void transfer(int num);

int main()
{
	int num;
	cout << "Enter tne number: ";
	cin >> num;
	transfer(num);
	return 0;
}

void transfer(int num)
{
	int count = 1, a = num;
	while (a > 2)
	{
		a /= 3;
		count++;
	}
	int* arr = new int[count];
	for (int i = count - 1; i >= 0; i--)
	{
		if (num >= 3)
		{
			arr[i] = num % 3;
			num /= 3;
		}
		else arr[i] = num;
	}
	if (arr[0] == 0)arr[0]--;
	for (int i = count - 1; i >= 1; i--)
	{
		if (arr[i] <= 0)
		{
			arr[i] += 3;
			arr[i - 1] -= 1;
		}
	}
	cout << "Number in new system: ";
	for (int i = 0; i < count; i++)
	{
		if (arr[i] > 0)cout << arr[i];
	}
	delete[]arr;
}