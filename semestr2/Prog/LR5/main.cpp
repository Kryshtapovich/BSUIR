#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int check()
{
	int a;
	while (!scanf("%d", &a) || a <= 0)
	{
		printf("Incorrect input, repeat: ");
		rewind(stdin);
	}
	return a;
}

struct ListNode
{
	char* word;
	ListNode* pNext, * pPrev;
};

struct List
{
	int size;
	ListNode* pHead, * pTail;
};

List* CreateList()
{
	List* temp = (List*)malloc(sizeof(List));
	if (temp == nullptr) exit(0);
	temp->size = 0;
	temp->pHead = temp->pTail = nullptr;
	return temp;
}

void Reverse(char* s, int length)
{
	if (length == 0)
	{
		printf("%c", s[length]);
		return;
	}
	else
	{
		printf("%c", s[length]);
		Reverse(s, length - 1);
	}
}

char* Word()
{
	printf("Enter the word: ");
	char* word = (char*)malloc(80 * sizeof(char));
	if (!word) exit(2);
	rewind(stdin);
	fgets(word, 80, stdin);
	return word;
}

void AddToList(List* lst)
{
	ListNode* temp = (ListNode*)malloc(sizeof(ListNode));
	if (!temp) exit(1);
	temp->word = Word();
	temp->pNext = nullptr;
	temp->pPrev = lst->pTail;
	if (lst->pTail) lst->pTail->pNext = temp;
	lst->pTail = temp;
	if (!lst->pHead) lst->pHead = temp;
	lst->size++;
}

void DeleteFromList(List* lst)
{
	if (!lst->pTail) exit(2);
	ListNode* temp = lst->pTail;
	lst->pTail = lst->pTail->pPrev;
	lst->pTail->pNext = nullptr;
	lst->size--;
	free(temp);
}

void DeleteList(List* lst)
{
	while (lst->pHead) DeleteFromList(lst);
	free(lst);
}

void PrintList(List* lst)
{
	if (!lst->pHead) exit(3);
	ListNode* temp = lst->pHead;
	for(int i = 1; temp; i++)
	{
		Reverse(temp->word, strlen(temp->word) - 1);
		temp = temp->pNext;
	}
}


struct StackNode
{
	List* list;
	StackNode* pNext, * pPrev;
};

struct StackOfLists
{
	int size;
	StackNode* pHead, * pTail;
};

StackOfLists* CreateStackOfLists()
{
	StackOfLists* temp = (StackOfLists*)malloc(sizeof(StackOfLists));
	if (!temp) exit(0);
	temp->size = 0;
	temp->pHead = temp->pTail = nullptr;
}

void AddToStackOfLists(StackOfLists* stk)
{
	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
	if (!temp)exit(1);
	int num;
	printf("Enter number of words: ");
	while (!scanf("%d", &num) || num <= 0)
	{
		printf("Incorrect input, repeat: ");
		rewind(stdin);
	}
	temp->list = CreateList();
	for (int i = 0; i < num; i++) AddToList(temp->list);
	temp->pNext = nullptr;
	temp->pPrev = stk->pTail;
	if (!stk->pHead) stk->pHead = temp;
	if (stk->pTail) stk->pTail->pNext = temp;
	stk->pTail = temp;
	stk->size++;
}

void DeleteFromStackOfLists(StackOfLists* stk)
{
	stk->size--;
	StackNode* temp = stk->pTail;
	stk->pTail = stk->pTail->pPrev;
	free(temp);
}

void DeleteStackOfLists(StackOfLists* stk)
{
	while (stk->size) DeleteFromStackOfLists(stk);
	free(stk);
}

void PrintStackOfLists(StackOfLists* stk)
{
	StackNode* temp = stk->pHead;
	for (int i = 1; temp; i++)
	{
		printf("\nList %d", i);
		PrintList(temp->list);
		printf("\n");
		temp = temp->pNext;
	}
}


struct Node
{
	char* word;
	Node* pNext, * pPrev;
};

struct Stack
{
	int size;
	Node* pHead, * pTail;
};

Stack* CreateStack()
{
	Stack* temp = (Stack*)malloc(sizeof(Stack));
	if (!temp) exit(0);
	temp->size = 0;
	temp->pHead = temp->pTail = nullptr;
}

void AddToStack(Stack* stk, char* w)
{
	Node* temp = (Node*)malloc(sizeof(Node));
	if (!temp)exit(1);
	temp->word = w;
	temp->pNext = nullptr;
	temp->pPrev = stk->pTail;
	if (!stk->pHead) stk->pHead = temp;
	if (stk->pTail) stk->pTail->pNext = temp;
	stk->pTail = temp;
	stk->size++;
}

void DeleteFromStack(Stack* stk)
{
	stk->size--;
	Node* temp = stk->pTail;
	stk->pTail = stk->pTail->pPrev;
	free(temp);
}

void DeleteStack(Stack* stk)
{
	while (stk->size) DeleteFromStack(stk);
	free(stk);
}

void PrintStack(Stack* stk)
{
	printf("\nSorted words:\n");
	Node* temp = stk->pHead;
	for (int i = 1; temp; i++)
	{
		printf("%d. ", i);
		printf("%s", temp->word);
		temp = temp->pNext;
	}
}

void Sort(StackOfLists* sol, Stack* stk)
{
	int str = 0;
	StackNode* temp = sol->pHead;
	for (int i = 0; i < sol->size; i++)
	{
		str += temp->list->size;
		temp = temp->pNext;
	}
	char** words = (char**)malloc(str * sizeof(char*));
	if (!words) exit(3);
	for (int i = 0; i < str; i++)
	{
		words[i] = (char*)malloc(80 * sizeof(char));
		if (!words) exit(2);
	}
	temp = sol->pHead;
	ListNode* ln = temp->list->pHead;
	for (int i = 0; i < str; i++)
	{
		if (!ln)
		{
			temp = temp->pNext;
			ln = temp->list->pHead;
			i--;
		}
		else
		{
			words[i] = ln->word;
			ln = ln->pNext;
		}
	}

	for (int i = 0; i < str; i++)
	{
		for (int j = i + 1; j < str; j++)
		{
			if (strcmp(words[i], words[j]) > 0)
			{
				char* temp = (char*)malloc(80 * sizeof(char));
				strcpy(temp, words[i]);
				strcpy(words[i], words[j]);
				strcpy(words[j], temp);
			}
		}
	}
	for (int i = 0; i < str; i++) AddToStack(stk, words[i]);
}

int main()
{
	StackOfLists* sol = CreateStackOfLists();
	printf("Enter the number of lists in stack: ");
	int num = check();
	for (int i = 0; i < num; i++)
	{
		printf("List %d:\n", i + 1);
		AddToStackOfLists(sol);
	}
	printf("Reversed words in stack's lists:");
	PrintStackOfLists(sol);
	Stack* stk = CreateStack();
	Sort(sol, stk);
	DeleteStackOfLists(sol);
	PrintStack(stk);
	DeleteStack(stk);
	printf("\nPress Enter to exit");
	getchar();
	return 0;
}
