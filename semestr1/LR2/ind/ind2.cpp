#include <iostream>
#include <math.h>

using namespace std;

int main() {
	float x, y, s;
	cout << "y = ";
	cin >> y;
	cout << "x = ";
	cin >> x;
	if (x > fabs(y)) {
		s = (2 * pow(x, 3)) + (3 * pow(y, 2));
		cout << "S = " << s;

	}
	else if (x > 3 && x < fabs(y)) {
		s = fabs(x - y);
		cout << "S = " << s;
	}
	else {
		s = pow(fabs(x - y), (1.0 / 3));
		cout << "S = " << s;

	}

	return 0;
}
