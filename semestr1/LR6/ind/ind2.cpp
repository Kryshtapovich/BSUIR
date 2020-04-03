#include <iostream>

using namespace std;

bool check(char c);
void min_max(char* arr);

int main() {
	char arr[80];
	cout << "Enter the text: ";
	gets_s(arr);
	min_max(arr);
	return 0;
}

bool check(char c) {
	if (c != ',' && c != '.' && c != '-' && c != '?' && c != '!' && c != ':' && c != ';' && c != '"' && c != ')' && c != '(' && c != ' ' && c != '\0') return 1;
	else return 0;
}

void min_max(char* arr)
{
	int count = 0, max = 0, min = 80;
	for (int i = 0; i <= strlen(arr); i++)
	{
		if (check(arr[i]))
		{
			count++;
			if (count > max) max = count;
		}
		else if(check(arr[i + 1]) && !check(arr[i]))
		{
			if (count < min) min = count;
			count = 0;
		}
	}

	for (int i = 0; i <= strlen(arr); i++)
	{
		if (check(arr[i])) {
			count++;
			if (count == max) {
				cout << "The longest word: ";
				for (int z = i - max + 1; z <= i; z++)
				{
					cout << arr[z];
				}
				cout << endl;
			}
		}
		else
		{
			if (count == min) {
				cout << "The shortest word: ";
				for (int z = i - min; z < i; z++)
				{
					cout << arr[z];
				}
				cout << endl;
			}
			count = 0;
		}
	}
}