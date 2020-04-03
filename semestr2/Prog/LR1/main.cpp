#include <stdio.h>
using namespace std;

float check();
int chec();

int main()
{
	printf("Enter float number: ");
	float f = check();
	printf("Enter integer number: ");
	int n = chec();
	float x = 1;
	float a = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int k = 0; k <= i; k++)
		{
			a += (f + k);
		}
		x *= (1 / a);
		a = 0;
	}
	printf("Result: %f", x);
	return 0;
}

float check()
{
	float f;
	while (!scanf_s("%f", &f))
	{
		rewind(stdin);
		printf("Incorrect data, enter correct data: ");
	}
	return f;
}

int chec()
{
	int a;
	rewind(stdin);
	while (!scanf_s("%d", &a))
	{
		rewind(stdin);
		printf("Incorrect data, enter correct data: ");
	}
	return a;
}

