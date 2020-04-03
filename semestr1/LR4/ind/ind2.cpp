#include <iostream>

using namespace std;

int main() {
	int arr[4][3] = { {10, 2, 3}, {4, 5, 0}, {1, 5, 9}, {7, 8, 5}};
	int min = arr[2][2];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			cout << arr[i][j] << '\t';
		}
		cout << endl << endl;
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			if (i > j) {
				if (arr[i][j] < min) {
					min = arr[i][j];
				}
			}
		}
	}
	cout << "Minimum element below the main diagonal is " << min;

	return 0;
}
