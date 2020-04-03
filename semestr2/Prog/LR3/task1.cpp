#include <stdio.h>
#include <malloc.h>

int check_amount();
int check_int();
void invisible_points(int*, int);

int main()
{
	printf("Enter amount of heights: ");
	int amount = check_amount();

	int* heights = (int*)malloc(sizeof(int) * amount);
	for (int i = 0; i < amount; i++)
	{
		printf("heights[%d] = ", i);
		heights[i] = check_int();
	}
	invisible_points(heights, amount);
	free(heights);
	return 0;
}

int check_amount()
{
	int a;
	while (!scanf("%d", &a) || a <= 2)
	{
		rewind(stdin);
		printf("Incorrect data, repeat: ");
	}
	return a;
}

int check_int()
{
	int a;
	while (!scanf("%d", &a) || a < 0)
	{
		rewind(stdin);
		printf("Incorrect data, repeat: ");
	}
	return a;
}

void invisible_points(int* heights, int amount)
{
	printf("Invisible points:\n");
	for (int i = 2; i < amount; i++)
	{
		for (int j = 1; j < i; j++)
		{
			if (heights[j] > heights[i])
			{
				printf("%d\n", i);
				break;
			}
		}
	}
}