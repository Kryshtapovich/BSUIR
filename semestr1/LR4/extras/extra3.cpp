#include <iostream>

using namespace std;

int main() {
	int n;
	cout << "Enter odd dimension of the magic square: ";
	cin >> n;
	cout << endl << endl;

	cout << "Magic square " << n << "X" << n << ":" << endl << endl;
	int** square = new int* [n];
	for (int i = 0; i < n; i++) {
		square[i] = new int[n];
	}

	int razm = n * n;
	int i = 0, j = n / 2;  

	for (int k = 1; k <= razm; k++) {
		square[i][j] = k;
		i--;     
		j++;     
		if (k % n == 0) {   
			i += 2;
			j--;
		}
		else {
			if (j == n) {    
				j -= n;
			}
			else if (i < 0) {    
				i += n;
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << square[i][j] << '\t';
		}
		cout << endl << endl;
	}

	for (i = 0; i < n; i++) {
		delete[]square[i];
	}
    delete []square;

	return 0;
}
