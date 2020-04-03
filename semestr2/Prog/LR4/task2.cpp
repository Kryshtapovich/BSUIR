#include <stdio.h>
#include <malloc.h>
#include <ctype.h>
#include <stdlib.h>

int filesize(FILE*);
void reading(char*, int, FILE*);
void average(char*, int);
int pow(int n, int p);


int main()
{
	FILE* file;
	file = fopen("Num.txt", "r");

	int size = filesize(file);
	char* arr = (char*)malloc(size);
	if (!arr)exit(0);
	reading(arr, size - 1, file);
	fclose(file);

	average(arr, size);
	free(arr);
	return 0;
}

int filesize(FILE* file)
{
	int pos, size;
	pos = ftell(file);
	fseek(file, 0L, SEEK_END);
	size = ftell(file);
	fseek(file, pos, SEEK_SET);
	return size;
}

void reading(char* arr, int size, FILE* file)
{
	for (int i = 0; i < size; i++)
	{
		fscanf(file, "%c", &arr[i]);
	}
	arr[size] = '\0';
}

void average(char* arr, int size)
{
	int count_digits = 0, number = 0, count_positive = 0;
	float sum = 0;
	
	for (int i = 0; i < size; i++)
	{
		if (arr[i] == '-') for (int j = i + 1; arr[j] != ' ' && arr[j] != '\n'; j++)arr[j] = '#';
		else if (isdigit(arr[i]))
		{
			for (int j = i; isdigit(arr[j]); j++)count_digits++;
			for (int j = i; isdigit(arr[j]); j++)
			{
				number += (arr[j] - '0') * pow(10, count_digits - 1);
				count_digits--;
			}
			for (int j = i; arr[j] != ' ' && arr[j] != '\0'; j++)arr[j] = '#';
			count_positive++;
			sum += number;
			number = 0;
		}
	}
	printf("Average of positive: %.2f", sum / count_positive);
}

int pow(int n, int p)
{
	if (p == 0)return 1;
	else return n * pow(n, p - 1);
}