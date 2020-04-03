#include <iostream>
#include <math.h>

using namespace std;

int _tmain() {
	float x, shag, part, min = 100, y, mini;
	cout << "How many parts to divide the root search area: ";
	cin >> part;
	shag = 2.0 / part;
	for (float i = 0; i <= 2; i += shag) {
		y = log10(cosh(i)) - tanh(i) + 0.5;
		if (fabs(y) < min) {
			min = fabs(y);
			mini = i;
		}
	}
	cout << "Approximate root of the equation: " << mini;

	return 0;
}
