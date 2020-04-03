#include <iostream>
#include <math.h>

using namespace std;

int main() {
	float sum = 0, d;
	int n, i = 1;
	do {
		d = 0;
		sum += pow((1.0 / 2), i) + pow((1.0 / 3), i);
		d = pow((1.0 / 2), i) + pow((1.0 / 3), i);
		i++;
	}
	while (d >= 0.001);
	cout << "Sum = " << sum << endl;
	cout << "d: " << d;

	return 0;
}
