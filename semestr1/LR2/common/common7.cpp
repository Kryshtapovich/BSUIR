#include <iostream>
#include <math.h>

using namespace std;

int main() {
	float a, b, c, x1, x2, x3, x4, D, q, r;
	cout << "a = ";
	cin >> a;
	cout << "b = ";
	cin >> b;
	cout << "c = ";
	cin >> c;
	if (a == 0 && b == 0 && c == 0) {
		cout << "Roots are all numbers";
	}
	else if (a == 0 && b != 0 && c != 0) {
		if ((b > 0 && c > 0) || (b < 0 && c < 0)) {
			cout << "Equation doesn't have roots";
		}
		else if ((b > 0 && c < 0) || (b < 0 && c > 0)) {
			x1 = sqrt(fabs(c / b));
			x2 = -sqrt(fabs(c / b));
			cout << "Equation roots: " << x1 << " " << x2;
		}
	}
	else if (b == 0 && a != 0 && c != 0) {
		if ((a > 0 && c > 0) || (a < 0 && c < 0)) {
			cout << "Equation doesn't have roots";
		}
		else if ((a > 0 && c < 0) || (a < 0 && c > 0)) {
			x1 = sqrt(sqrt(fabs(c / a)));
			x2 = -sqrt(sqrt(fabs(c / a)));
			cout << "Equation roots: " << x1 << " " << x2;
		}
	}
	else if (c == 0 && a != 0 && b != 0) {
		if ((a > 0 && b > 0) || (a < 0 && b < 0)) {
			cout << "Equation doesn't have roots";
		}
		else if ((a > 0 && b < 0) || (a < 0 && b > 0)) {
			x1 = sqrt(fabs(b / a));
			x2 = -sqrt(fabs(b / a));
			cout << "Equation roots: " << 0 << " " << x1 << " " << x2;
		}
	}
	else if (a == 0 && b == 0 && c != 0) {
		cout << "Roots are all numbers";
	}
	else if ((a == 0 && c == 0 && b != 0) || (b == 0 && c == 0 && a != 0)) {
		cout << "All roots are: " << 0;
	}
	else if (a != 0 && b != 0 && c != 0) {
		D = pow(b, 2) - (4 * a * c);
		if (D < 0) {
			cout << "Equation doesn't have roots";
		}
		else if (D == 0) {
			x1 = sqrt(sqrt(fabs(c / a)));
			x2 = -sqrt(sqrt(fabs(c / a)));
			cout << "Equation roots: " << x1 << " " << x2;
		}
		else if (D > 0) {
			q = (-b + sqrt(D)) / (2 * a);
			r = (-b - sqrt(D)) / (2 * a);
			if (q < 0 && r < 0) {
				cout << "Equation doesn't have roots";
			}
			else if (q < 0 && r >= 0) {
				x1 = sqrt(r);
				x2 = -sqrt(r);
				cout << "Equation roots: " << x1 << " " << x2;
			}
			else if (q >= 0 && r < 0) {
				x1 = sqrt(q);
				x2 = -sqrt(q);
				cout << "Equation roots: " << x1 << " " << x2;
			}
			else if (q >= 0 && r >= 0) {
				x1 = sqrt(q);
				x2 = -sqrt(q);
				x3 = sqrt(r);
				x4 = -sqrt(r);
				cout << "Equation roots: " << x1 << " " << x2 << " " <<
					x3 << " " << x4;
			}
		}
	}

	return 0;
}
