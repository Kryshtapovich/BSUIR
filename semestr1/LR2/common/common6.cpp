#include <iostream>
#include <math.h>

using namespace std;

int main() {
	float a, b, c, Y;
    int N;
	cout << "a = ";
	cin >> a;
	cout << "b = ";
	cin >> b;
	cout << "c = ";
	cin >> c;
	cout << "N = ";
	cin >> N;
	switch(N){
		case 2: Y = (b * c) - pow(a, 2); break;
		case 56: Y = b * c; break;
		case 7: Y = pow(a, 2) + c; break;
		case 3: Y = a - (b * c); break;
		default: Y = pow((a + b), 3); break;
	}
	cout << "Y = " << Y;

	return 0;
}
