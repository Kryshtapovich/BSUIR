#include <iostream>

using namespace std;

int** create_array(int rows, int columns) {
	int** arr = new int* [rows];
	for (int i = 0; i < rows; i++) {
		arr[i] = new int[columns];
	}
	return arr;
}

void filling_output_array(int **arr, int rows, int columns) {
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			cout << "Array[" << i << "][" << j << "] = ";
			cin >> arr[i][j];
		}
	}

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			cout << arr[i][j] << '\t';
		}
		cout << endl << endl;
	}
}

void mult(int**arr, int rows, int columns) {
	int mult = 1;

	int* elements = new int[rows];
	for (int i = 0; i < rows; i++)
	{
		elements[i] = 1;
	}

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (i == j && arr[i][j] % 2 == 0)
			{
				elements[i] = arr[i][j];
			}
		}
	}

	for (int i = 0; i < rows; i++)
	{
		mult *= elements[i];
	}
	cout << "Product of even elements of the main diagonal: " << mult << endl;
	delete[]elements;
}

int main() {
	int rows, columns;
	cout << "Enter number of rows of the array: ";
	cin >> rows;
	cout << "Enter number of columns of the array: ";
	cin >> columns;

	int** arr;

	arr = create_array(rows, columns);

	filling_output_array(arr, rows, columns);

	mult(arr, rows, columns);

	for (int i = 0; i < rows; i++)
	{
		delete[]arr[i];
	}
	delete[]arr;

	return 0;
}
