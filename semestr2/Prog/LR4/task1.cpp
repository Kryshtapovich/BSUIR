#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>
#include <stdlib.h>

char** enter_text(int&, int&);
void text_to_words(char**, char*, int);
void letter(char, int, char*);
char* delete_letters(char*);
void func(char*);
int check();
void delete_array(char**, int, int);

int main()
{
	int str, col;
	char** text = enter_text(str, col);
	char* words = (char*)calloc(str * col * sizeof(char), ' ');
	if (!words) exit(0);
	text_to_words(text, words, str);

	for (int i = 0; i < str; i++)
	{
		free(text[i]);
	}
	free(text);

	char* new_words = delete_letters(words);
	if (!new_words)exit(0);
	free(words);

	printf("New text:\n%s", new_words);
	func(new_words);


	return 0;
}

char** enter_text(int& str, int& col)
{
	printf("Enter amount of strings: ");
	str = check();
	col = 80;
	rewind(stdin);
	char** text = (char**)malloc(str * sizeof(char*));
	for (int i = 0; i < str; i++)
	{
		text[i] = (char*)malloc(col * sizeof(char));
		if (!text[i])
		{
			printf("GG");
			delete_array(text, str, col);
			exit(0);
		}
	}
	printf("Enter the text:\n");
	for (int i = 0; i < str; i++)
	{
		gets_s(text[i], col);
	}

	return text;
}

void text_to_words(char** text, char* words, int str)
{
	for (int i = 0; i < str; i++)
	{
		strcat(words, text[i]);
		strcat(words, " ");
	}
	strcat(words, "\0");
}

void letter(char c, int index, char* words)
{
	for (int i = index + 1; i < strlen(words); i++)
	{
		if (c == words[i])
		{
			words[i] = '#';
		}
	}
}

char* delete_letters(char* words)
{
	int count = 0;

	for (int i = 0; i < strlen(words); i++)
		if (words[i] != '#' && words[i] != ' ')letter(words[i], i, words);

	for (int i = 0; i < strlen(words); i++)
		if (words[i] == '#')count++;

	char* arr = (char*)malloc((strlen(words) - count) * sizeof(char));
	if (!arr)exit(0);
	for (int i = 0, j = 0; j < strlen(arr);)
	{
		if (words[i] != '#')
		{
			arr[j] = words[i];
			i++;
			j++;
		}
		else i++;
	}
	return arr;
}

int check()
{
	int a;
	while (!scanf("%d", &a) || a <= 0)
	{
		rewind(stdin);
		printf("Incorrect data, repeat: ");
	}
	return a;
}

void func(char* arr)
{
	printf("\nFirst inputs:\n");
	for (int i = 0; i < strlen(arr); i++)
	{
		if (i == 0 && !isalpha(arr[i + 1]))printf("%c ", arr[i]);
		else if (i != 0 && !isalpha(arr[i - 1]) && arr[i] != ' ' && !isalpha(arr[i + 1]))printf("%c ", arr[i]);
		else if (i == strlen(arr) - 1 && !isalpha(arr[i - 1]));
	}
}
void delete_array(char** arr, int str, int col)
{
	for (int i = 0; i < str; i++)
	{
		free(arr[i]);
	}
	free(arr);
}