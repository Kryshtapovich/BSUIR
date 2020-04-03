#include "tree.h"

Tree :: Tree()
{
	pHead = nullptr;
	NumNodes = 0;
}

void Tree :: AddNode(AnsiString str, int num)
{
	if(!pHead)
	{
		pHead = new Node;
		pHead->surname = str;
		pHead->number = num;
		pHead->pLeft = pHead->pRight = nullptr;
	}
	else
	{
		Node *node = SearchFree(pHead, num);
		node->surname = str;
		node->number = num;
		node->pLeft = node->pRight = nullptr;
	}
	NumNodes++;
}

Node* Tree :: SearchFree(Node *temp, int num)
{
	if(num < temp->number)
	{
		if(!temp->pLeft)
		{
			temp->pLeft = new Node;
			return temp->pLeft;
		}
		else return SearchFree(temp->pLeft, num);
	}
	else
	{
		if(!temp->pRight)
		{
			temp->pRight = new Node;
			return temp->pRight;
		}
		else return SearchFree(temp->pRight, num);
	}
}

void Tree :: PrintTree(Node* temp, TTreeView *TreeView, int &index)
{
	int i = index;
	if(temp->pLeft)
	{
		TreeView->Items->AddChild(TreeView->Items->Item[i], temp->pLeft->surname);
		PrintTree(temp->pLeft, TreeView, ++index);
	}
	if(temp->pRight)
	{
		TreeView->Items->AddChild(TreeView->Items->Item[i], temp->pRight->surname);
		PrintTree(temp->pRight, TreeView, ++index);
    }
}

void Tree :: ShowTree(TTreeView *TreeView)
{
	int index = 0;
	TreeView->Items->Clear();
	if(pHead)
	{
		TreeView->Items->Add(NULL, pHead->surname);
		PrintTree(pHead, TreeView, index);
    }
}

AnsiString Tree :: GetPlayer(int num)
{
	Node *temp = pHead;
	while(temp->number != num)
	{
		if(num < temp->number) temp = temp->pLeft;
		else temp = temp->pRight;
	}
	if(temp)return temp->surname;
	else return "";
}

void Tree :: DeleteNode(int num)
{
	Node *del, *prevdel, *node, *prevnode;
	del = pHead;
	prevdel = nullptr;
	while(del->number != num)
	{
		prevdel = del;
		if(num < del->number) del = del->pLeft;
		else del = del->pRight;
	}
	if(!del)return;
	if(!del->pRight) node = del->pLeft;
	else if(!del->pLeft) node = del->pRight;
	else
	{
		prevnode = del;
		node = del->pLeft;
		while(node->pRight)
		{
			prevnode = node;
			node = node->pRight;
		}
		if(prevnode == del) node->pRight = del->pRight;
		else
		{
			node->pRight = del->pRight;
			prevnode->pRight = node->pLeft;
			node->pLeft = prevnode;
        }
	}
	if(!prevdel) pHead = prevdel = node;
	else if(del->number < prevdel->number) prevdel->pLeft = node;
	else prevdel->pRight = node;
	delete del;
	NumNodes--;
}

void Tree :: Delete(Node *p)
{
	if(p)
	{
		NumNodes--;
		Delete(p->pLeft);
		Delete(p->pRight);
        delete p;
    }
}

void Tree :: Balance()
{
	int* arr = new int[NumNodes];
	AnsiString* str = new AnsiString[NumNodes];
	int size = 0;
	ToArray(pHead, arr, str, size);
	Delete(pHead);
	pHead = MakeTree(arr, str, 0, size);
}

void Tree :: ToArray(Node *p, int* arr, AnsiString* str, int &index)
{
	if(p->pLeft) ToArray(p->pLeft, arr, str, index);
	str[index] = p->surname;
	arr[index] = p->number;
	index++;
	if(p->pRight) ToArray(p->pRight, arr, str, index);
}

Node* Tree :: MakeTree(int *arr, AnsiString *str, int first, int last)
{
	if(!last) return nullptr;
	Node *node = new Node;
	node->surname = str[first + last / 2];
	node->number = arr[first + last / 2];
	NumNodes++;
	int lastl = last / 2;
	int lastr = last - lastl - 1;
	node->pLeft = MakeTree(arr, str, first, lastl);
	node->pRight = MakeTree(arr, str, first + lastl + 1, lastr);
	return node;
}

void Tree :: Right(TMemo *Memo)
{
	NLR(Memo, pHead);
}

void Tree :: NLR(TMemo *Memo, Node *p)
{
	if(p)
	{
		Memo->Lines->Add(p->surname);
		NLR(Memo, p->pLeft);
		NLR(Memo, p->pRight);
    }
}

void Tree :: Back(TMemo *Memo)
{
	LRN(Memo, pHead);
}

void Tree :: LRN(TMemo *Memo, Node *p)
{
	if(p)
	{
		LRN(Memo, p->pLeft);
		LRN(Memo, p->pRight);
		Memo->Lines->Add(p->surname);
    }
}

void Tree :: Growth(TMemo *Memo)
{
	LNR(Memo, pHead);
}

void Tree :: LNR(TMemo *Memo, Node *p)
{
	if(p)
	{
		LNR(Memo, p->pLeft);
		Memo->Lines->Add(p->surname);
		LNR(Memo, p->pRight);
    }
}

int Tree :: TwoDaughters()
{
	int amount = 0;
	Count(pHead, amount);
	return amount;
}

void Tree :: Count(Node *p, int &amount)
{
	if(p && p->pLeft && p->pRight)
	{
		Count(p->pLeft, amount);
		amount++;
		Count(p->pRight, amount);
    }
}
