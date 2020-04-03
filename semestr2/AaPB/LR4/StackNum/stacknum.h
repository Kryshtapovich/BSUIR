#include "nodenum.h"

#ifndef stacknumH
#define stacknumH

class StackNum
{
public:
	NodeNum *pHead, *pTail;
	int size;
	StackNum();
	void Add(float n);
	float GetBack();
	float Delete();
};

#endif
