#include "pch.h" 
#include <utility>
#include <limits.h>
#include "Header.h"

int Add(int a, int b) { return a + b; }

int Sub(int a, int b) { return a - b; }

float Average(float a, float b) { return (a + b) / 2; }

int Mult(int a, int b) { return a * b; }

float Div(float a, float b) { return a / b; }

int Mod(int a, int b) { return a % b; }

int Factorial(int a)
{
	if (a == 0) return 1;
	else return a * Factorial(a - 1);
}

int Power(int a, int b)
{
	if (b == 0)return 1;
	else return a * Power(a, b - 1);
}