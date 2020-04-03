#include <iostream>
#include <math.h>

using namespace std;

int main() {
	float k, m, x1, x2, L;
	cout << "x1 = ";
	cin >> x1;
	cout << "x2 = ";
	cin >> x2;
	cout << "m = ";
	cin >> m;
	k = pow(cos(pow(x1, 2)), 3) + pow(sin(pow(x2, 2)), 3);
	if(k >= 1){
		L = pow(k, 3) + pow(m, 0.2);
		cout << "L = " << L;
	} else if(k <= 1){
		L = pow(k, 2) - exp(m);
		cout << "L = " << L;
	}

	return 0;
}
