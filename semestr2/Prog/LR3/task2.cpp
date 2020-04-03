#include <stdio.h>
#include <malloc.h>
#include <CMath>
#include <windows.h>

int check();
bool full_square(int);
void input(char*, int);
void encryption(char*, int, char**, int);
void decryption(char*, int);
void delete_array(char**, int);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	printf("Enter length of the message: ");
	int length = check();
	char* words = (char*)malloc(sizeof(char) * length + 1);
	printf("Enter a phrase: ");
	input(words, length);

	int size = sqrt(length);

	char** arr = (char**)malloc(sizeof(char*) * size);
	for (int i = 0; i < size; i++) arr[i] = (char*)malloc(sizeof(char) * size);

	encryption(words, length, arr, size);
	decryption(words, length);
	
	delete_array(arr, size);
	free(words);
	return 0;
}

int check()
{
	int a;
	while (!scanf("%d", &a) || a <= 0 || full_square(a))
	{
		rewind(stdin);
		printf("Incorrect input, repeat: ");
	}
	return a;
}

bool full_square(int num)
{
	for (int i = 0; i < sqrt(num) + 1; i++)
	{
		if (i * i == num) return 0;
	}
	return 1;
}

void input(char* words, int length)
{
	char c;
	for (int i = 0; i <= length; i++)
	{
		c = getchar();
		words[i] = c;
	}
	for (int i = 0; i < length; i++)
	{
		words[i] = words[i + 1];
	}
	words[length] = '\0';
}

void encryption(char* words, int length, char** arr, int size)
{
	int k = size - 1;
	int i = 0, j = 0;
	int num = 0;
	while (k > 0)
	{
		for (; i < size - 1 - j; i++) arr[i][j] = words[num++];

		for (; j < i; j++) arr[i][j] = words[num++];

		for (; i > size - j - 1; i--) arr[i][j] = words[num++];

		for (; j > i; j--) arr[i][j] = words[num++];

		k -= 2;
		i += 1;
		j += 1;
	}
	if (size % 2 != 0)arr[size / 2][size / 2] = words[length - 1];
	printf("Encryption matrix: \n");
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			printf("%c\t", arr[i][j]);
		}
		printf("%c", '\n');
	}
	k = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			words[k] = arr[i][j];
			k++;
		}
	}
	printf("\nEncrypted phrase: %s", words);
}

void decryption(char* words, int length)
{
	int size = sqrt(length);
	char** arr = (char**)malloc(sizeof(char*) * size);
	for (int i = 0; i < size; i++) arr[i] = (char*)malloc(sizeof(char) * size);

	int k = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			arr[i][j] = words[k];
			k++;
		}
	}

	k = size - 1;
	int i = 0, j = 0;
	int num = 0;
	while (k > 0)
	{
		for (; i < size - 1 - j; i++) words[num++] = arr[i][j];

		for (; j < i; j++) words[num++] = arr[i][j];

		for (; i > size - j - 1; i--) words[num++] = arr[i][j];

		for (; j > i; j--) words[num++] = arr[i][j];

		k -= 2;
		i += 1;
		j += 1;
	}
	if (size % 2 != 0) words[length - 1] = arr[size / 2][size / 2];
	printf("\nDecrypted phrase: %s\n", words);
	delete_arr(arr, size);
}

void delete_array(char** arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		free(arr[i]);
	}
	free(arr);
}