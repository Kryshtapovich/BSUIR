#include <iostream>

using namespace std;

int main() {
	float a, b;
	cout << "a = ";
	cin >> a;
	cout << "b = ";
	cin >> b;
	bool max = a > b;
	cout << "Max number: " << max ? a : b;

	return 0;
}
