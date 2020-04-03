#include <iostream>
#include <math.h>

using namespace std;

int _tmain() {
	int n, f = 1, amount;
	float S = 0, Y, x;
	cout << "Enter amount of raw elements: ";
	cin >> n;
	cout << "Enter amount of numbers from what you want to calculate the function: ";
	cin >> amount;
	cout << "Enter x (from 0.1 to 1): ";
	for (int i = 0; i <= amount; i++) {
		cin >> x;
		Y = ((pow(x, 2) / 4) + (x / 2.0) + 1) * exp(x / 2.0);
		f = 1;
		S = 0;
		for (int z = 1; z <= n; z++) {
			f *= z;
			S += ((pow(z, 2) + 1) / f) * pow((x / 2.0), z);
		}
		cout << "S(x) = " << S << '\t' << "Y(x) = " << Y << endl;
	}

	return 0;
}
