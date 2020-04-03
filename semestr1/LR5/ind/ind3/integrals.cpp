#include "integrals.h"
#include <iostream>
#include <cmath>
using namespace std;

double f1(double x) {
	return sqrt(0.4 * x * x) + 1.5) / (2.5 + sqrt(2 * x + 0.8));
}

double f2(double x) {
	return cos(x * x) + 0.8) / (1.5 + sin(0.6 * x + 0.5));
}

double f3(double x) {
	return 1 / sqrt(1 + 2 * x * x);
}

double f4(double x) {
	return tan(x * x + 0.5) / (1 + 2 * x * x);
}

void integral1(double(*f1)(double)) {
	int n;
	double a = 0.8, b = 2.4, x, I = 0;
	cout << "How many parts do you want to split the integration segment: ";
	cin >> n;
	cout << endl;
	double h = (b - a) / n;

	for (int i = 0; i <= n - 1; i++) {
		x = a + i * h;
		I += f1(x);
	}
	cout << "Integral 1 by method of left rectangles on the segment from 0.8 to 2.4: "
		<< h * I << endl << endl << endl;
}

void integral2(double(*f2)(double)) {
	int n;
	double a = 0.4, b = 1.2, x, I = 0;
	cout << "How many parts do you want to split the integration segment: ";
	cin >> n;
	cout << endl;
	double h = (b - a) / n;

	for (int i = 1; i <= n; i++) {
		x = a + i * h;
		I += f2(x);
	}
	cout << "Integral 2 by method of right rectangles on the segment from 0.4 to 1.2: "
		<< h * I << endl << endl << endl;
}

void integral3(double(*f3)(double)) {
	int n;
	double a = 0.6, b = 1.5, x, I = 0;
	cout << "How many parts do you want to split the integration segment: ";
	cin >> n;
	cout << endl;
	double h = (b - a) / n;

	for (int i = 0; i <= n - 1; i++) {
		x = a + i * h + h / 2;
		I += f3(x);
	}
	cout << "Integral 3 by method of center rectangles on the segment from 0.6 to 1.5: "
		<< h * I << endl << endl << endl;
}

void integral4(double(*f4)(double)) {
	int n;
	double a = 0.4, b = 0.8, x, I = 0;
	cout << "How many parts do you want to split the integration segment: ";
	cin >> n;
	cout << endl;
	double h = (b - a) / n;

	for (int i = 0; i <= n; i++) {
		x = a + i * h;
		if (i == 0 || i == n) {
			I += f4(x) / 2;
		}
		else {
			I += f4(x);
		}
	}
	cout << "Integral 4 by method of trapezies on the segment from 0.4 to 0.8: "
		<< h * I << endl;
}
