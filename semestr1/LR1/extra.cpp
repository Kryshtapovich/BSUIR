#include <iostream>
#include <math.h>

using namespace std;

int main() {
	float a, t, v0, s;
	cout << "a = ";
	cin >> a;
	cout << "t = ";
	cin >> t;
	cout << "v0 = ";
    cin >> v0;
	if(a >= 0){
		s = (v0 * t) + (a * pow(t, 2) / 2);
        cout << "s = " << s;
	}
	else{
		s = (v0 * t) - (a * pow(t, 2) / 2);
		cout << "s = " << s;
	}

	return 0;
}
