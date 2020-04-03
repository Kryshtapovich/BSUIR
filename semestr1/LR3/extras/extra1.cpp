#include <iostream>

using namespace std;

int _tmain() {
	int a, b;
	cout << "In these numbers doubled sum of the digits is equal to their product:"
		<< endl;
	for (int i = 10; i <= 99; i++) {
		a = i / 10;
		b = i % 10;
		if (2 * (a + b) == a * b) {
			cout << i << endl;
		}
	}
	
	return 0;
}
