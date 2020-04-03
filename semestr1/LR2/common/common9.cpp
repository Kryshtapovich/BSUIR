#include <iostream>

using namespace std;

int main() {
	int year, current, age, t;
	cout << "year =  ";
	cin >> year;
	cout << "current =  ";
	cin >> current;
	age = current - year;
	t = age % 10;
	if(age >= 10 && age <= 20){
	switch(t){
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 0: cout << "������� ��������: " << age << " ���"; break;
	}
	} else {
        switch(t){
		case 1: cout << "������� ��������: " << age << " ���"; break;
		case 2:
		case 3:
		case 4: cout << "������� ��������: " << age << " ����"; break;
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 0: cout << "������� ��������: " << age << " ���"; break;
	}
    }

	return 0;
}
