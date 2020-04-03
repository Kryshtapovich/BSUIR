#include "element.h"

#ifndef queueH
#define queueH

class Queue
{
public:
    int size;
	Element *pHead, *pTail, *pMax, *pMin;
	Queue();
	void Add(int);
	int GetNum(int);
	int GetMax();
	int GetMin();
    	void DeleteQueue();
};

#endif
