#include "queue.h"

Queue :: Queue()
{
	size = 0;
	pHead = pTail = nullptr;
}
void Queue :: Add(int num)
{
	Element *temp =  new Element(num);
	temp->pNext = nullptr;
	temp->pPrev = pTail;
	if(pTail)
	{
		pTail->pNext = temp;
        if(pTail->number > pMax->number) pMax = pTail;
		if(pTail->number < pMin->number) pMin = pTail;
	}
	pTail = temp;
	if(!pHead)
	{
		pHead = temp;
		pMin = pMax = pHead;
	}
	size++;
}
int Queue :: GetNum(int index)
{
	int counter = 0;
	Element *temp = pHead;
	while(temp)
	{
		if(counter == index) return temp->number;
		temp = temp->pNext;
        counter++;
	}
}
int Queue :: GetMax() { return pMax->number; }
int Queue :: GetMin() { return pMin->number; }
void Queue :: DeleteQueue()
{
	while(pHead)
	{
		Element *temp = pHead->pNext;
		delete temp;
		pHead = temp;
	}
}
