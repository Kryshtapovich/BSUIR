#include <iostream>
#include <math.h>

using namespace std;

int main() {
	int M = 20, A = 0;
	float B, H, x = 0, y;
	B = M_PI / 2;
	H = (B - A) / M;
	cout << "y" << '\t' << '\t' << "x" << endl;
	for (int i = 1; x >= 0, x <= M_PI / 2; i++) {
		x = A + (i * H);
		y = sin(x) - cos(x);
		cout << y << '\t' << x << endl;
	}

	return 0;
}
