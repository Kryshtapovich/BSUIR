#include <iostream>

using namespace std;

int length(string num);

bool check(string num, int size);
string ifneg(string num, int size);

int* transfer_to_int(string num, int size);
char conversion(int c);

bool coincide(int* num1, int* num2, int size); 
int compare(int* num1, int* num2, int size1, int size2); 

void sum(int* num1, int* num2, int size1, int size2);
void sum_if_coincide(int* num1, int* num2, int size1, int size2);
void sum_ifnot_coincide(int* num1, int* num2, int size1, int size2);

void sub(int* num1, int* num2, int size1, int size2);
void sub_if_s1nots2(int* num1, int* num2, int size1, int size2);


int main()
{
	string num1, num2;
	cout << "Enter the first number in seventeenfold system: ";
	cin >> num1;
	cout << "Enter the second number in seventeenfold system: ";
	cin >> num2;
	
		int size1 = length(ifneg(num1, length(num1)));
		int size2 = length(ifneg(num2, length(num2)));
		int* arr1 = transfer_to_int(ifneg(num1, length(num1)), size1);
		int* arr11 = transfer_to_int(ifneg(num1, length(num1)), size1);
		int* arr2 = transfer_to_int(ifneg(num2, length(num2)), size2);
		int* arr22 = transfer_to_int(ifneg(num2, length(num2)), size2);
		int comp = compare(arr1, arr2, size1, size2);
		if (num1[0] != '-' && num2[0] != '-')
		{
			if (comp == 0)
			{
				cout << "Result of subtraction: " << 0;
				cout << endl << "Result of addition: ";
				sum(arr1, arr2, size1, size2);
			}
			else if (comp == 1)
			{
				cout << "Result of subtraction: ";
				sub(arr1, arr2, size1, size2);
				cout << endl << "Result of addition: ";
				sum(arr11, arr22, size1, size2);
			}
			else
			{
				cout << "Result of subtraction: " << '-';
				sub(arr1, arr2, size1, size2);
				cout << endl << "Result of addition: ";
				sum(arr11, arr22, size1, size2);
			}

		}
		else if (num1[0] != '-' && num2[0] == '-')
		{
			if (comp == 0)
			{
				cout << "Result of subtraction: ";
				sum(arr1, arr2, size1, size2);
				cout << endl << "Result of addition: " << 0;
			}
			else if (comp == 1)
			{
				cout << "Result of subtraction: ";
				sum(arr1, arr2, size1, size2);
				cout << endl << "Result of addition: ";
				sub(arr11, arr22, size1, size2);
			}
			else
			{
				cout << "Result of subtraction: ";
				sum(arr1, arr2, size1, size2);
				cout << endl << "Result of addition: ";
				sub(arr11, arr22, size1, size2);
			}
		}
		else if (num1[0] == '-' && num2[0] != '-')
		{
			if (comp == 0)
			{
				cout << "Result of subtraction: " << '-';
				sum(arr1, arr2, size1, size2);
				cout << endl << "Result of addition: " << 0;
			}
			else if (comp == 1)
			{
				cout << "Result of subtraction: " << '-';
				sum(arr1, arr2, size1, size2);
				cout << endl << "Result of addition: " << '-';
				sub(arr11, arr22, size1, size2);
			}
			else
			{
				cout << "Result of subtraction: " << '-';
				sum(arr1, arr2, size1, size2);
				cout << endl << "Result of addition: ";
				sub(arr11, arr22, size1, size2);
			}
		}
		else
		{
			if (comp == 0)
			{
				cout << "Result of subtraction: " << 0;
				cout << endl << "Result of addition: " << '-';
				sum(arr1, arr2, size1, size2);
			}
			else if (comp == 1)
			{
				cout << "Result of subtraction: " << '-';
				sub(arr1, arr2, size1, size2);
				cout << endl << "Result of addition: " << '-';
				sum(arr11, arr22, size1, size2);
			}
			else
			{
				cout << "Result of subtraction: ";
				sub(arr1, arr2, size1, size2);
				cout << endl << "Result of addition: " << '-';
				sum(arr11, arr22, size1, size2);
			}
		}
	return 0;
}

int length(string num)
{
	int size = 0;
	for (int i = 0; num[i] != '\0'; i++) size++;
	return size;
}

bool check(string num, int size)
{
	bool c = true;
	if (num[0] == '-') c = true;

	for (int i = 1; i < size; i++)
	{
		if (num[i] - '0' >= 0 && num[i] - '0' <= 9 || num[i] >= 'A' && num[i] <= 'G')
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

string ifneg(string num, int size)
{
	if (num[0] == '-')
	{
		for (int i = 0; i < size; i++)
		{
			num[i] = num[i + 1];
		}
	}
	return num;
}

int* transfer_to_int(string num, int size)
{
	int* code = new int[size];
	for (int i = 0; i < size; i++)
	{
		if (num[i] - '0' >= 0 && num[i] - '0' <= 9)
		{
			code[i] = num[i] - '0';
		}
		else
		{
			code[i] = num[i] - '0' - 7;
		}
	}
	return code;
	delete[]code;
}

char conversion(int c)
{
	if (c >= 10 && c <= 16) return c + '57';
	else return c + '0';
}

bool coincide(int* num1, int* num2, int size1, int size2)
{
	bool c = true;
	int x = 0;
	if (size1 == size2)
	{
		for (int i = 0; i < size1; i++)
		{
			if (num1[i] + num2[i] >= 17) x++;
		}
		if (x == size1 || x == size1 - 1) c = false;
	}
	else if ((num1[1] + num2[0] >= 17 && num1[0] == 16) || (num2[0] == 16 && num1[0] + num2[1] >= 17)) c = false;
	return c;
}

int compare(int* num1, int* num2, int size1, int size2)
{
	int c = 0, x = 0;
	if (size1 == size2)
	{
		for (int i = 0; i < size1; i++)
		{
			if (num1[i] > num2[i])
			{
				c = 1;
				break;
			}
			else if (num1[i] < num2[i])
			{
				c = 2;
				break;
			}
			else x++;
		}
		if (x == size1) c = 0;
	}
	else if (size1 > size2) c = 1;
	else c = 2;
	return c;
}

void sum(int* num1, int* num2, int size1, int size2)
{
	if (size1 > size2)
	{
		if (coincide(num1, num2, size1, size2)) sum_if_coincide(num1, num2, size1, size2);
		else sum_ifnot_coincide(num1, num2, size1, size2);
	}
	else if (size1 < size2)
	{
		if (coincide(num1, num2, size1, size2)) sum_if_coincide(num1, num2, size2, size1);
		else sum_ifnot_coincide(num2, num1, size2, size1);
	}
	else
	{
		if (coincide(num1, num2, size1, size2))
		{
			char* sum = new char[size1];
			int* res = new int[size1];
			for (int i = size1 - 1; i >= 0; i--)
			{
				res[i] = num1[i] + num2[i];
			}
			if (res[0] >= 17)
			{
				sum[0] = '1';
				for (int i = size1 - 1; i >= 0; i--)
				{
					if (res[i] >= 17)
					{
						res[i] -= 17;
						res[i - 1] += 1;
					}
					sum[i] = conversion(res[i]);
				}
				for (int i = 0; i < size1; i++)
				{
					cout << sum[i];
				}
			}
			else
			{
				for (int i = size1 - 1; i >= 0; i--)
				{
					if (res[i] >= 17)
					{
						res[i] -= 17;
						res[i - 1] += 1;
					}
					sum[i] = conversion(res[i]);
				}
				for (int i = 0; i < size1; i++)
				{
					cout << sum[i];
				}
			}
			delete[]res;
			delete[]sum;
		}
		else
		{
			char* sum = new char[size1 + 1];
			int* res = new int[size1 + 1];
			for (int i = size1 - 1, j = size1; i >= 0; i--, j--)
			{
				res[j] = num1[i] + num2[i];
			}
			res[0] = 0;
			for (int i = size1; i >= 0; i--)
			{
				if (res[i] >= 17)
				{
					res[i] -= 17;
					res[i - 1] += 1;
				}
				sum[i] = conversion(res[i]);
			}
			for (int i = 0; i < size1 + 1; i++)
			{
				cout << sum[i];
			}
			delete[]res;
			delete[]sum;
		}
	}
}

void sum_if_coincide(int* num1, int* num2, int size1, int size2)
{
	char* sum = new char[size1];
	int* res = new int[size1];
	for (int i = size1 - 1, j = size2 - 1; i >= 0; i--, j--)
	{
		if (i >= 0 && j >= 0)
		{
			res[i] = num1[i] + num2[j];
		}
		else
		{
			res[i] = num1[i];
		}
	}
	for (int i = size1 - 1; i >= 0; i--)
	{
		if (res[i] >= 17)
		{
			res[i] -= 17;
			res[i - 1] += 1;
		}
		sum[i] = conversion(res[i]);
	}
	for (int i = 0; i < size1; i++)
	{
		cout << sum[i];
	}
	delete[]sum;
	delete[]res;
}

void sum_ifnot_coincide(int* num1, int* num2, int size1, int size2)
{
	char* sum = new char[size1 + 1];
	int* res = new int[size1 + 1];
	for (int i = size1 - 1, j = size2 - 1, z = size1; i >= 0; i--, j--, z--)
	{
		if (i >= 0 && j >= 0)
		{
			res[z] = num1[i] + num2[j];
			if (res[z] >= 17)
			{
				res[z] -= 17;
				num1[i - 1] += 1;
			}
		}
		else
		{
			res[z] = num1[i];
		}
	}
	sum[0] = '1';
	for (int i = size1; i >= 1; i--)
	{
		if (res[i] >= 17)
		{
			res[i] -= 17;
			res[i - 1] += 1;
		}
		sum[i] = conversion(res[i]);
	}
	for (int i = 0; i < size1 + 1; i++)
	{
		cout << sum[i];
	}
	delete[]res;
	delete[]sum;
}

void sub(int* num1, int* num2, int size1, int size2)
{
	if (size1 > size2)
	{
		sub_if_s1nots2(num1, num2, size1, size2);
	}
	else if (size1 < size2)
	{
		sub_if_s1nots2(num2, num1, size2, size1);
	}
	else
	{
		char* sub = new char[size1];
		int* res = new int[size1];
		if (num1[0] > num2[0])
		{
			for (int i = size1 - 1; i >= 1; i--)
			{
				if (num1[i] < num2[i])
				{
					num1[i] += 17;
					num1[i - 1] -= 1;
				}
				res[i] = abs(num1[i] - num2[i]);
			}
			sub[0] = conversion(abs(num1[0] - num2[0]));
		}
		else
		{
			for (int i = size1 - 1; i >= 1; i--)
			{
				if (num2[i] < num1[i])
				{
					num2[i] += 17;
					num2[i - 1] -= 1;
				}
				res[i] = abs(num2[i] - num1[i]);
			}
			sub[0] = conversion(abs(num1[0] - num2[0]));
		}
		for (int i = size1 - 1; i >= 1; i--)
		{
			sub[i] = conversion(res[i]);
		}
		for (int i = 0; sub[i] == '0'; i++)
		{
			sub[i] = '#';
		}
		for (int i = 0; i < size1; i++)
		{
			if (sub[i] != '#') cout << sub[i];
		}
		delete[]sub;
		delete[]res;
	}
}

void sub_if_s1nots2(int* num1, int* num2, int size1, int size2)
{
	char* sub = new char[size1];
	int* res = new int[size1];
	for (int i = size1 - 1, j = size2 - 1; i >= 0; i--, j--)
	{
		if (i >= 0 && j >= 0)
		{
			if (num1[i] < num2[j])
			{
				num1[i] += 17;
				num1[i - 1] -= 1;
			}
			res[i] = num1[i] - num2[j];
		}
		else
		{
			res[i] = num1[i];
		}
		sub[i] = conversion(res[i]);
	}
	for (int i = 0; sub[i] == '0'; i++)
	{
		sub[i] = '#';
	}
	for (int i = 0; i < size1; i++)
	{
		if (sub[i] != '#') cout << sub[i];
	}
	delete[]sub;
	delete[]res;
}