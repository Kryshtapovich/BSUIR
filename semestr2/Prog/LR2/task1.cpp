#include <stdio.h>

void menu();
int check();
void commands();
void calc(int, int, int, int);

int main()
{
	menu();
	return 0;
}

void menu()
{
	int euro_price = 0, year = 0, engine = 0, dist = 0;
	int n;
	do
	{
		commands();
		n = check();
		switch (n)
		{
		case 1:
			printf("Price in Europe(€): ");
			euro_price = check();
			break;
		case 2:
			printf("Year of issue: ");
			year = check();
			break;
		case 3:
			printf("Engine volume: ");
			engine = check();
			break;
		case 4:
			printf("Distance: ");
			dist = check();
			break;
		case 5:
			calc(euro_price, 2020 - year, engine, dist);
			system("pause");
			break;
		case 6:
			printf("GrossTransport v2.2.8, Mikhail Kryshtapovich\n");
			system("pause");
			break;
		default:
			printf("Выход");
			break;
		}
	} while (n >= 1 && n <= 6);
}

int check()
{
	int a = 1;
	rewind(stdin);
	while (!scanf_s("%d", &a) || (a < 0))
	{
		rewind(stdin);
		printf("Incorrect input, try again: ");
	}
	return a;
}

void commands()
{
	system("cls");
	printf("1 - Enter price in Europe\n");
	printf("2 - Enter issue year\n");
	printf("3 - Enter engine volume\n");
	printf("4 - Enter distance\n");
	printf("5 - Calculate\n");
	printf("6 - Information\n");
	printf("Enter command: ");
}

void calc(int euro, int year, int engine, int dist)
{
	if (euro == 0 || year < 0 || engine == 0 || dist == 0)
		printf("You haven't entered some data or enetered wrong\n");
	else {
		float rast;
		if (year < 3)
		{
			rast = engine * 0.6;
		}
		else if (year > 3 && year <= 10)
		{
			if (engine < 2500)
			{
				rast = engine * 0.35;
			}
			else
			{
				rast = engine * 0.6;
			}
		}
		else if (year > 10 && year <= 14)
		{
			rast = engine * 0.6;
		}
		else
		{
			rast = engine * 2;
		}
		float total = euro + rast + 0.5 * dist;
		printf("Sum(€): %d\n", (int)total);
	}
}