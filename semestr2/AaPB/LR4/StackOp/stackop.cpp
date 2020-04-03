#include "stackop.h"

StackOp :: StackOp()
{
	size = 0;
	pHead = 0;
	pTail = 0;
}

void StackOp :: Add(char c)
{
	size++;
	NodeOp *temp = new NodeOp(c);
	if(pTail == 0) pTail = temp;
	else
	{
		temp->pNext = pTail;
		pTail = temp;
	}
}

char StackOp :: GetBack()
{
	return pTail->c;
}

char StackOp:: Delete()
{
	size--;
	NodeOp *temp = pTail;
	char n = temp->c;
	pTail = pTail->pNext;
	delete temp;
	return n;
}
