#include <iostream>
#include <math.h>

using namespace std;

int main() {
	int i = 1, a, b, N = 0;
	while (i <= 30) {
		if (i % 2 == 0) {
			a = i / 2;
			b = pow(i, 3);
		}
		else {
			a = i;
			b = pow(i, 2);
		}
		N += pow((a - b), 2);
		i++;
	}
	cout << "N = " << N;

	return 0;
}
