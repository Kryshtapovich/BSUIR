#include <iostream>

using namespace std;

int main() {
	int n, k = 1;
	cout << "Enter dimension of the spiral: ";
	cin >> n;

	int** sp = new int* [n];
	for (int i = 0; i < n; i++) {
		sp[i] = new int[n];
	}

	int p = n / 2;
	for (int z = 1; z <= p; z++) {
		for (int j = z - 1; j < n - z + 1; j++) {
			sp[z - 1][j] = k++;
		}
		for (int i = z; i < n - z + 1; i++) {
			sp[i][n - z] = k++;
		}
		for (int j = n - z - 1; j >= z - 1; --j) {
			sp[n - z][j] = k++; 
		}
		for (int i = n - z - 1; i >= z; i--) {
			sp[i][z - 1] = k++; 
		}
	}
	if (n % 2 != 0) {
		sp[p][p] = n * n;
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << sp[i][j] << '\t';
		}
		cout << endl << endl;
	}
	for (int i = 0; i < n; i++) {
		delete[]sp[i];
	}
    delete []sp;

	return 0;
}
