#include <vcl.h>

#ifndef hashtableH
#define hashtableH

class HashNode
{
public:
	int key;
    int nodes;
	AnsiString info;
	HashNode *pNext;
	HashNode(int, AnsiString);
};

class HashTable
{
private:
	static const int size = 30;
	HashNode **elements;
	int Hash(int);
	void Swap(HashNode*, HashNode*);
public:
	void Create();
	void Add(int, AnsiString);
	void Delete(TMemo*, int);
	void Show(TMemo*);
	void Search(TMemo*, int);
	void Decrease(TMemo*);
};

#endif
