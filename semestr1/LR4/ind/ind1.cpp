#include <iostream>

using namespace std;

int main()

{
	const int size = 7;
	int arr[7];
	for (int i = 0; i < 7; i++) {
		cout << "Array[" << i << "] = ";
		cin >> arr[i];
	}
	int count = 0;
	for (int i = 0; i < size / 2; i++) {
		if (arr[i] == arr[6 - i])
		{
			count++;
		}
		else {
			count = 0;
		}
	}
	if (count == size / 2) {
		cout << "The array is symmetrical";
	}
	else {
		cout << "The array isn't symmetrical";
	}

	return 0;
}
