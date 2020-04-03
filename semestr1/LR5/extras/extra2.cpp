#include <iostream>

using namespace std;

int func(int i);
int sum(int p, int q);

int main() {
	int p, q, k;
	cout << "Enter number of tests you want to run: ";
	cin >> k;
	cout << "Enter p and q: " << endl;
	int* arr = new int[k];
	for (int i = 0; i < k; i++)
	{
		cin >> p >> q;
		if (p < 0 && q < 0)break;
		func(i);
		arr[i] = sum(p, q);
	}

	cout << endl;

	for (int i = 0; i < k; i++)
	{
		if (arr[i] <= 0) break;
		cout << arr[i] << endl;
	}

	delete[]arr;

	return 0;
}

int func(int i) {
	if (i % 10 > 0) return (i % 10);
	else  if (i == 0) return 0;
	else return func(i / 10);
}

int sum(int p, int q) {
	int sum = 0;
	for (int i = p; i <= q; i++) sum += func(i);
	return sum;
}
