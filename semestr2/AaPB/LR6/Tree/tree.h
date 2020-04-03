#include <vcl.h>

#ifndef treeH
#define treeH

class Node
{
public:
	AnsiString surname;
	int number;
	Node *pLeft, *pRight;
};

class Tree
{
private:
	Node *pHead;
	Node* SearchFree(Node*, int);
	void PrintTree(Node*, TTreeView*, int&);
	void ToArray(Node*, int*, AnsiString*, int&);
    Node* MakeTree(int*, AnsiString*, int, int);
	void Delete(Node*);
	void NLR(TMemo*, Node*);
	void LRN(TMemo*, Node*);
	void LNR(TMemo*, Node*);
	void Count(Node*, int&);
public:
	int NumNodes;
	Tree();
	void AddNode(AnsiString, int);
	void ShowTree(TTreeView*);
	AnsiString GetPlayer(int);
	void DeleteNode(int);
	void Balance();
	void Right(TMemo*);
	void Back(TMemo*);
	void Growth(TMemo*);
	int TwoDaughters();
};

#endif
