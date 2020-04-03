#include <iostream>

using namespace std;

void test(int tests);
void filling();
int result(int num_fill, int m);

int main()
{
	int tests;
	cout << "Enter number of test: ";
	cin >> tests;
	test(tests);
	return 0;
}

void test(int test)
{
	for (int i = 0; i < test; i++)
	{
		filling();
	}
}

int result(int num_fill, int m)
{
	int res = 1;
	for (int i = 0; i < num_fill; i++)
	{
		res *= 26;
	}
	return res % m * 2;
}

void filling()
{
	int length, m, amount = 0;
	string s1, s2, s3;
	cout << "Enter length and m: ";
	cin >> length >> m;
	cout << "Enter s1(prefix): ";
	cin >> s1;
	cout << "Enter s2(suffix): ";
	cin >> s2;
	s3 = s1 + s2;
	for (int i = 0; i < size(s3); i++)
	{
		for (int j = i + 1; j < size(s3); j++)
		{
			if (s3[i] == s3[j])
			{
				s3[j] = '#';
			}
		}
	}
	for (int i = 0; i < size(s3); i++)
	{
		if (s3[i] != '#')
		{
			amount++;
		}
	}
	if (amount == length)
	{
		cout << "Number of fill variations: " << 1 << endl << endl;
	}
	else if (size(s1) >= length || size(s2) >= length)
	{
		cout << "Number of fill variations: " << 0 << endl << endl;
	}
	else
	{
		int num_fill = length - (size(s1) + size(s2));
		cout << "Number of fill variations: " << result(num_fill, m) << endl << endl;
	}
}