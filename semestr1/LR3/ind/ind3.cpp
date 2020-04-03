#include <iostream>
#include <math.h>

using namespace std;

int _tmain() {
	float x, y;
	cout << "y" << '\t' << "x" << endl;
	for (float i = 3; i <= 4; i += 0.2) {
		y = sqrt(i) * cosh(i);
		cout << y << '\t' << i << endl;
	}

	return 0;
}
