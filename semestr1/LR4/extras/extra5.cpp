#include <iostream>
#include <ctime>

using namespace std;

int main() {
	srand(time(0));
	int n, m;
	cout << "Enter number of rows of the array: ";
	cin >> n;
	cout << "Enter number of columns of the array: ";
	cin >> m;

	int** arr = new int* [n];
	for (int i = 0; i < n; i++) {
		arr[i] = new int[m];
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			arr[i][j] = rand() % 10 - 5;
			cout << arr[i][j] << "\t";
		}
		cout << endl << endl;
	}
	cout << endl << endl;

	if (n < m) {
		bool exit = false;
		while (!exit) {
			exit = true;
			for (int i = 0; i < n - 1; i++) {
				for (int j = 0; j < n - 1 - i; j++) {
					if (j + i <= n - 1) {
						if (arr[i][j] > arr[i + 1][j]) {
							int k = arr[i][j];
							arr[i][j] = arr[i + 1][j];
							arr[i + 1][j] = k;
						}
						if (arr[i][j] > arr[i][j + 1]) {
							int temp = arr[i][j];
							arr[i][j] = arr[i][j + 1];
							arr[i][j + 1] = temp;
							exit = false;
						}
					}
				}
			}
		}
	}
	else if (n > m) {
		bool exit = false;
		while (!exit) {
			exit = true;
			for (int i = 0; i < m - 1; i++) {
				for (int j = 0; j < m - 1 - i; j++) {
					if (j + i <= m - 1) {
						if (arr[i][j] > arr[i + 1][j])
						{
							int k = arr[i][j];
							arr[i][j] = arr[i + 1][j];
							arr[i + 1][j] = k;
						}
						if (arr[i][j] > arr[i][j + 1]) {
							int temp = arr[i][j];
							arr[i][j] = arr[i][j + 1];
							arr[i][j + 1] = temp;
							exit = false;
						}
					}
				}
			}
		}
	}
	else {
		bool exit = false;
		while (!exit) {
			exit = true;
			for (int i = 0; i < n - 1; i++) {
				for (int j = 0; j < m - 1 - i; j++) {
					if (j + i <= n - 1 && j + i <= m - 1) {
						if (arr[i][j] > arr[i + 1][j])
						{
							int k = arr[i][j];
							arr[i][j] = arr[i + 1][j];
							arr[i + 1][j] = k;
						}
						if (arr[i][j] > arr[i][j + 1]) {
							int temp = arr[i][j];
							arr[i][j] = arr[i][j + 1];
							arr[i][j + 1] = temp;
							exit = false;
						}
					}
				}
			}
		}
	}
    cout << "Sotred array:" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << arr[i][j] << "\t";
		}
		cout << endl << endl;
	}

	for (int i = 0; i < n; i++) {
		delete[]arr[i];
	}
	delete[]arr;

	return 0;
}
