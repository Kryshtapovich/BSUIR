#include <iostream>

using namespace std;

void even_digits(char* arr);

int main() {
	char arr[80];
	cout << "Enter the string: ";
	gets_s(arr);
	even_digits(arr);
	return 0;
}

void even_digits(char *arr)
{
	cout << endl << "Even digits of the string: ";
	for (int i = 0; i < strlen(arr); i++)
	{
		if (isdigit(arr[i]) && arr[i] % 2 == 0)
		{
			cout << arr[i] << " ";
		}
	}
}