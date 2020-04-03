#include "stacknum.h"

StackNum :: StackNum()
{
	size = 0;
	pHead = 0;
	pTail = 0;
}

void StackNum :: Add(float n)
{
	size++;
	NodeNum *temp = new NodeNum(n);
	if(pTail == 0) pTail = temp;
	else
	{
		temp->pNext = pTail;
		pTail = temp;
	}
}

float StackNum :: GetBack()
{
	return pTail->num;
}

float StackNum:: Delete()
{
	size--;
	NodeNum *temp = pTail;
	float n = temp->num;
	pTail = pTail->pNext;
	delete temp;
	return n;
}
