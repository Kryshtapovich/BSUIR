#include <iostream>

using namespace std;

int main() {   
	int n, k, sum, end_digit, pre_end_digit, z;
	cout << "n = ";
	cin >> n;
	cout << "k = ";
	cin >> k;
	sum = n + k;
	end_digit = sum % 10;
	pre_end_digit = sum % 100;
	z = pre_end_digit * 10 + end_digit;
	if(pre_end_digit >= 11 && pre_end_digit <= 19 || pre_end_digit == 11){
	switch(pre_end_digit){
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
		case 16:
		case 17:
		case 18:
		case 19:  cout << "Sum: " << sum; break;
	}
	} else {
	switch(end_digit){
		case 1: cout << "Sum: " << sum; break;
		case 2:
		case 3:
		case 4: cout << "Sum: " << sum; break;
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 0: cout << "Sum: " << sum; break;
	}
	}

	return 0;
}
