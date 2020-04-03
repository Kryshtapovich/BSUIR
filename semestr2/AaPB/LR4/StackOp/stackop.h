#include "nodeop.h"

#ifndef stackopH
#define stackopH

class StackOp
{
public:
	NodeOp *pHead, *pTail;
	int size;
	StackOp();
	void Add(char c);
    char GetBack();
	char Delete();
};

#endif
