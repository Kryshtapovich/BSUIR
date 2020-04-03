#include <iostream>
#include <math.h>

using namespace std;

int counter(int *arr, int first, int last, int count);

int main() {
	int n;
	cout << "Enter number of elements of the array: ";
	cin >> n;
	int* arr = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	cout << "number is: " << counter(arr, 0, n, 0);
	delete[]arr;

	return 0;
}

int counter(int* arr, int first, int last, int count) {
	if (first < (last / 3)) {
		double x = arr[first];
		first++;
		if (cos(x * x) > 0 && x < 0) {
			count++;
		}
		return counter(arr, first, last, count);
	}
	else if (first < last) {
		double x = arr[first];
		first++;
		if (cos(x * x) > 0 && x < 0) {
			count++;
		}
		return counter(arr, first, last, count);
	}
	else {
		return count;
	}
}
