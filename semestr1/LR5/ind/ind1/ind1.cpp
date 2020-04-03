#include <iostream>
#include <cmath>

using namespace std;

typedef char _TCHAR;

int main(int argc, _TCHAR* argv[]) {

	HINSTANCE load;
	load = LoadLibrary("Dll.dll");

	typedef void (_stdcall *pfunc) (int);
	pfunc func;

	func = (pfunc)GetProcAddress(load, "func");

	int n;
	cout << "Enter number of elements of the array: ";
	cin >> n;
	func(n);

	FreeLibrary(load);

	return 0;
}
