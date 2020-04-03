#include <iostream>
#include <math.h>

using namespace std;

int main() {
	float a, y;
	cout << "a = ";
	cin >> a;
	if (a <= -1) {
		y = -1 / a;
		cout << "f(a) = " << y;
	}
	else if (a > -1 && a <= 2) {
		y = pow(a, 2);
		cout << "f(a) = " << y;
	}
	else if (a > 2) {
		y = 4;
		cout << "f(a) = " << y;
	}

	return 0;
}
