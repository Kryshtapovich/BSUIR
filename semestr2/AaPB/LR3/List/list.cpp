#include "list.h"

List::List()
{
	size = 0;
	pHead = nullptr;
}
void List::Add(std::string c, std::string t, std::string s, int n, int a, int h, int w)
{
	if (pHead == nullptr) pHead = new Node(c, t, s, n, a, h, w);
	else
	{
		Node* temp = pHead;
		while (temp->pNext)
		{
			temp = temp->pNext;
		}
		temp->pNext = new Node(c, t, s, n, a, h, w);
	}
	size++;
}
void List::Delete(int index)
{
	if (index == 0)
	{
		Node* current = pHead;
		pHead = pHead->pNext;
		delete current;
	}
	else
	{
		Node* prev = pHead;
		for (int i = 0; i < index - 1; i++) prev = prev->pNext;
		Node* temp = prev->pNext;
		prev->pNext = temp->pNext;
		delete temp;
	}
	size--;
}
std::string& List::Country(int index)
{
	int counter = 0;
	Node* temp = pHead;
	while (temp != nullptr)
	{
		if (counter == index) return temp->country;
		temp = temp->pNext;
		counter++;
	}
}
std::string& List::Team(int index)
{
	int counter = 0;
	Node* temp = pHead;
	while (temp != nullptr)
	{
		if (counter == index) return temp->team;
		temp = temp->pNext;
		counter++;
	}
}
std::string& List::Surname(int index)
{
	int counter = 0;
	Node* temp = pHead;
	while (temp != nullptr)
	{
		if (counter == index) return temp->surname;
		temp = temp->pNext;
		counter++;
	}
}
int& List::Num(int index)
{
	int counter = 0;
	Node* temp = pHead;
	while (temp != nullptr)
	{
		if (counter == index) return temp->num;
		temp = temp->pNext;
		counter++;
	}
}
int& List::Age(int index)
{
	int counter = 0;
	Node* temp = pHead;
	while (temp != nullptr)
	{
		if (counter == index) return temp->age;
		temp = temp->pNext;
		counter++;
	}
}
int& List::Height(int index)
{
	int counter = 0;
	Node* temp = pHead;
	while (temp != nullptr)
	{
		if (counter == index) return temp->height;
		temp = temp->pNext;
		counter++;
	}
}
int& List::Weight(int index)
{
	int counter = 0;
	Node* temp = pHead;
	while (temp != nullptr)
	{
		if (counter == index) return temp->weight;
		temp = temp->pNext;
		counter++;
	}
}
