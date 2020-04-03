#include <iostream>
#include <math.h>

using namespace std;

int main() {
	float a, x, b, c;
	cout << "x = ";
	cin >> x;
	a = sin(x);
	b = cos(x);
	c = log(x);
	if (a < b && a < c) {
		cout << "a: " << a;
	}
	else if (b < a && b < c) {
		cout << "b: " << b;
	}
	else if (c < a && c < b) {
		if (x != 0) {
			cout << "c: " << c;
		}
	}
	else if (a == b && b == c) {
		cout << a;
	}

	return 0;
}
