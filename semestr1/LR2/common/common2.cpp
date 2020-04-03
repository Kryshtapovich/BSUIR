#include <iostream>

using namespace std;

int main() {
	float d, a;
	char zn;
	cout << "d = ";
	cin >> d;
	cout << "a = ";
	cin >> a;
sign:
	cout << "Enter sign: ";
	cin >> zn;
	switch (zn) {
	case '+':
		d += a;
		cout << "d + a = " << d << endl;
		break;
	case '-':
		d -= a;
		cout << "d - a = " << d << endl;
		break;
	case '/':
		d /= a;
		cout << "d / a =  " << d << endl;
		break;
	case '*':
		d *= a;
		cout << "d * a = " << d << endl;
		break;
	default:
		cout << "Incorrect input" << endl;
		cout << "Type 'Y' to repeat: ";
		cin >> zn;
		if (zn == 'y' || zn == 'Y') {
			goto sign;
		}
		else {
			break;
		}

	}

	return 0;
}
