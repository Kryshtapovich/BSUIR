#include <iostream>
#include <math.h>

using namespace std;

int nine_to_ten(int num9);
void ten_to_seventeen(int num10);
void case1(int num10);
void case2(int num10);
char conversion(int c);
bool check(int num);

int main()
{
	int num9;
	cout << "Enter number in ninefold number system: ";
	cin >> num9;
	if (check(num9)) ten_to_seventeen(nine_to_ten(num9));
	else cout << "Incorrect input";
	return 0;
}

bool check(int num)
{
	bool c = true;
	while (num > 0)
	{
		if (num % 10 == 9)
		{
			c = false;
			break;
		}
		num /= 10;
	}
	return c;
}

char conversion(int c)
{
	if (c >= 10 && c <= 16) return c + '57';
	else return c + '0';
}

int nine_to_ten(int num9)
{
	int num10 = 0, digit_count = 0, a = num9;

	while (a != 0)
	{
		a /= 10;
		digit_count++;
	}

	for (int i = 0; i < digit_count; i++)
	{
		num10 += num9 % 10 * pow(9, i);
		num9 /= 10;
	}
	return num10;
}

void ten_to_seventeen(int num10)
{
	int n;
	cout << "Choose execution variant 1(cycle) or 2(array): ";
	cin >> n;
	switch (n)
	{
	case 1:
		case1(num10);
		break;
	case 2:
		case2(num10);
		break;
	default: cout << "Error";
	}
}

void case1(int num10)
{
	int a = num10, ost;
	cout << "Number in seventeenfold number system: "; 
	long num17 = 0;
	while (a >= 1)
	{
		ost = a % 17;
		num17 *= 100;
		num17 += ost + 10;
		a /= 17;
	}
	while (num17 != 0)
	{
		ost = num17 % 100;
		ost -= 10;
		cout << conversion(ost);
		num17 /= 100;
	}
}

void case2(int num10)
{
	int count = 0, b, a = num10;
	while (a >= 1)
	{
		count++;
		a /= 17;
	}
	char* arr = new char[count];
	int i = 0;
	a = num10;
	while (a >= 1)
	{
		b = a % 17;
		arr[i] = conversion(b);
		a /= 17;
		i++;
	}
	cout << "Number in seventeenfold number system: ";
	for (int j = count - 1; j >= 0; j--)
	{
		cout << arr[j];
	}
	delete[]arr;
}