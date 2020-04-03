#include <iostream>
#include <math.h>

using namespace std;

extern "C" void _declspec(dllexport) _stdcall func (int n) {
	double* x = new double[n];

	for (int i = 0; i < n; i++) {
		x[i] = exp(-0.5 * i - 2 * M_PI) - atan(i + 0.1);
		cout << x[i] << " ";
	}
	cout << endl << endl;

	for (int i = 0; i < n; i++) {
		if (x[i] < 0) {
			x[i] += 0.5;
		}
		else {
			x[i] = 0.1;
		}
	}

	for (int i = 0; i < n; i++) {
		cout << x[i] << " ";
	}
    delete[]x;
}
