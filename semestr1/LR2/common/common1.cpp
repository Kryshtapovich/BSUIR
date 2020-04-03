#include <iostream>

using namespace std;

int main() {
	int x, y;
	float a, b, c;
	cout << "X = ";
	cin >> x;
	cout << "Y = ";
	cin >> y;
	cout << "A = ";
	cin >> a;
	cout << "B = ";
	cin >> b;
	cout << "C = ";
	cin >> c;
    cout << endl;
	if (x > y) {
		y = 0;
		cout << "X = " << x << endl;
		cout << "Y = " << y << endl;
	}
	else if (x == y) {
		x = 0;
		y = 0;
		cout << "X = " << x << endl;
		cout << "Y = " << y << endl;
	}
	else {
		x = 0;
		cout << "X = " << x << endl;
		cout << "Y = " << y << endl;
	}
	if (a > b && a > c) {
		a -= 0.3;
		cout << "A = " << a << endl;
		cout << "B = " << b << endl;
		cout << "C = " << c << endl;
	}
	else if (b > c && b > a) {
		b -= 0.3;
		cout << "A = " << a << endl;
		cout << "B = " << b << endl;
		cout << "C = " << c << endl;
	}
	else {
		c -= 0.3;
		cout << "A = " << a << endl;
		cout << "B = " << b << endl;
		cout << "C = " << c;
	}

	return 0;
}
