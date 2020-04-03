#include <stdio.h>
#include <cmath>

int fact(int);

int check_int();

float check_float();

float to_rad(float);

int func(int, float, float);

const float E = 0.001;

int main()
{
	int n = 0;
	float x, res = 0;

	printf("Enter the argument: ");
	x = check_float();
	x = to_rad(x);

	printf("sin(%lf): %f\n", x, sin(x));
	func(n, x, res);
	return 0;
}

int fact(int n)
{
	if (n == 0) return 1;
	else return n * fact(n - 1);
}

int check_int()
{
	int a;
	rewind(stdin);
	while (!scanf_s("%d", &a) || a < 0)
	{
		rewind(stdin);
		printf("Incorrect enter, enter correct data: ");
	}
	return a;
}

float check_float()
{
	float x;
	rewind(stdin);
	while (!scanf_s("%f", &x) || (x < 0 || x > 180))
	{
		rewind(stdin);
		printf("Incorrect enter, enter correct data: ");
	}
	return x;
}

float to_rad(float x)
{
	return x / 180 * acos(-1);
}

int func(int n, float x, float res)
{
	res += pow(-1, n) * pow(x, 2 * n + 1) / fact(2 * n + 1);

	printf("n = %d\tsin(%lf)' = %lf\n", n, x, res);

	if (fabs(sin(x) - res) < E) return n;
	else func(n + 1, x, res);
}