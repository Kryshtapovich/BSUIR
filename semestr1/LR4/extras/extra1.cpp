#include <iostream>
#include <ctime>

using namespace std;

int main() {
	srand(time(NULL));

	int sum = 0, columns, rows, rotate = 0;
	cout << "Enter number of rows of the array: ";
	cin >> rows;
	cout << "Enter number of columns of the array: ";
	cin >> columns;

	int* ch = new int[columns];
	for (int i = 0; i < columns; i++) {
		ch[i] = 0;
	}

	int** arr = new int* [rows + 1];
	for (int i = 0; i < rows + 1; i++) {
		arr[i] = new int[rows + 1];
	}

	for (int i = 0; i < rows + 1; i++)
	{
		for (int j = 0; j < columns; j++) {
			if (i < rows) {
				arr[i][j] = rand() % 10 - 5;
				cout << arr[i][j] << '\t';
			}
		}
		cout << endl << endl;
	}

	for (int i = 0; i < columns; i++) {
		sum = 0;
		for (int j = 0; j < rows; j++) {
			if (arr[j][i] < 0 && arr[j][i] % 2 != 0) {
				sum += abs(arr[j][i]);
				ch[i] = sum;
			}
		}
	}

	for (int i = 0; i < columns; i++)
	{
		arr[rows][i] = ch[i];
	}

	int temp, k;
	bool exit = false;
	while (!exit) {
		exit = true;
		for (int i = 0; i < rows + 1; i++) {
			for (int j = 0; j < columns - 1 - i; j++) {
				if (arr[rows][j] > arr[rows][j + 1]) {
					k = arr[rows][j];
					arr[rows][j] = arr[rows][j + 1];
					for (int z = 0; z < rows; z++) {
						temp = arr[z][j];
						arr[z][j] = arr[z][j + 1];
						arr[z][j + 1] = temp;
					}
					exit = false;
				}
			}
		}
	}

	cout << "Sorted array: " << endl;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			cout << arr[i][j] << '\t';
		}
		cout << endl << endl;
	}

	delete[]ch;
	for (int i = 0; i < rows + 1; i++) {
		delete[]arr[i];
	}
	delete[]arr;

	return 0;
}
