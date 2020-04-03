#include <iostream>
#include <math.h>

using namespace std;

int main() {
	float x1, x2, y1, y2, r1, r2, a1, a2, L;
	int n;
	cout << "n = ";
	cin >> n;
	switch (n) {
	case 1:
		cout << "x1 = ";
		cin >> x1;
		cout << "y1 = ";
		cin >> y1;
		cout << "x2 = ";
		cin >> x2;
		cout << "y2 = ";
		cin >> y2;
		L = sqrt((pow(x2, 2) - pow(x1, 2)) + (pow(y2, 2) - pow(y1, 2)));
		cout << "L = " << L;
		break;
	case 0:
		cout << "r1 = ";
		cin >> r1;
		cout << "a1 = ";
		cin >> a1;
		cout << "r2 = ";
		cin >> r2;
		cout << "a2 = ";
		cin >> a2;
		x1 = r1 * cos(a1 * M_PI / 180);
		y1 = r1 * sin(a1 * M_PI / 180);
		x2 = r2 * cos(a2 * M_PI / 180);
		y2 = r2 * sin(a2 * M_PI / 180);
		L = sqrt((pow(x2, 2) - pow(x1, 2)) + (pow(y2, 2) - pow(y1, 2)));
		cout << "L = " << L;
		break;
	}

	return 0;
}
