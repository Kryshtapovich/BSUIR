#include <iostream>
#include <math.h>

using namespace std;

int main() {
	float a, b, z, x, y;
	int num;
	cout << "a = ";
	cin >> a;
	cout << "b = ";
	cin >> b;
	cout << "z = ";
	cin >> z;
	cout << "num = ";
	cin >> num;
	switch (num) {
	case 1:
		if (z <= 0) {
			x = pow(z, 2) / 2;
			y = ((b * 2 * x) / cos(x)) + (a * log(fabs(tan(x / 2))));
			cout << "Y = " << y;
		}
		else {
			x = sqrt(z);
			y = ((b * 2 * x) / cos(x)) + (a * log(fabs(tan(x / 2))));
			cout << "Y = " << y;
		}
		break;
	case 2:
		if (z <= 0) {
			x = pow(z, 2) / 2;
			y = ((b * pow(x, 2)) / cos(x)) + (a * log(fabs(tan(x / 2))));
			cout << "Y = " << y;
		}
		else {
			x = sqrt(z);
			y = ((b * pow(x, 2)) / cos(x)) + (a * log(fabs(tan(x / 2))));
			cout << "Y = " << y;
		}
		break;
	case 3:
		if (z <= 0) {
			x = pow(z, 2) / 2;
			y = ((b * (x / 3)) / cos(x)) + (a * log(fabs(tan(x / 2))));
			cout << "Y = " << y;
		}
		else {
			x = sqrt(z);
			y = ((b * (x / 3)) / cos(x)) + (a * log(fabs(tan(x / 2))));
			cout << "Y = " << y;
		}
	default: break;
	}

	return 0;
}
