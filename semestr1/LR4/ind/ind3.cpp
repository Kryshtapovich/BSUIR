#include <iostream>
#include <ctime>

using namespace std;

int main() {
	srand(time(NULL));
	int size = 0, summin = 0, summax = 0, min = 11, max = 0;

	cout << "Enter the dimension of the array: ";
	cin >> size;

	int** arr = new int* [size];
	for (int i = 0; i < size; i++) {
		arr[i] = new int[size];
	}

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			arr[i][j] = rand() % 10 + 1;
			cout << arr[i][j] << '\t';
		}
		cout << endl << endl;
	}

	for (int i = 0; i < size; i += 2) {
		for (int j = 0; j < size; j++) {
			if (arr[i][j] < min) {
				min = arr[i][j];
			}
		}
		summin += min;
		min = 11;
	}

	for (int i = 1; i < size; i += 2) {
		for (int j = 0; j < size; j++) {
			if (arr[i][j] > max) {
				max = arr[i][j];
			}
		}
		summax += max;
		max = 0;
	}

	cout << "Sum of the minimum elements of the odd lines of the array is " <<
		summin << endl << endl;

	cout << "Sum of the maximum elements of the even lines of the array is " <<
		summax << endl;

	for (int i = 0; i < size; i++) {
		delete[]arr[i];
	}
	delete[]arr;

	return 0;
}
