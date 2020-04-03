#include <iostream>

using namespace std;

int fact(int a);
int* repeats(char* word);
void anagrams(int* rep, char* word);
void delete_repeats(int* repeats);

int main()
{
	char word[14];
	cout << "Enter the word: ";
	gets_s(word);
	anagrams(repeats(word), word);
	delete_repeats(repeats(word));
	return 0;
}

int* repeats(char* word)
{
	int* rep = new int[strlen(word)];
	int rep_cnt = 1;
	for (int i = 0; i < strlen(word); i++)
	{
		for (int j = i + 1; j < strlen(word); j++)
		{
			if (word[j] != '#')
			{
				if (word[i] == word[j])
				{
					rep_cnt++;
					word[j] = '#';
				}
			}
		}
		rep[i] = rep_cnt;
		rep_cnt = 1;
	}
	return rep;
}

int fact(int a)
{
	if (a == 1 || a == 0) return 1;
	else return a * fact(a - 1);
}

void anagrams(int* rep, char* word)
{
	int  amount = 1;
	for (int i = 0; i < strlen(word); i++)
	{
		amount *= fact(rep[i]);
	}
	cout << "Number of anagrams: " << fact(strlen(word)) / amount;
}

void delete_repeats(int* repeats)
{
	delete[]repeats;
}