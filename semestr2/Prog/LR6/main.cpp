#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int a, int b)
{
	if (a > b) return a;
	else return b;
}

struct Node
{
	char symb;
	Node* pLeft, * pRight;
};

struct Tree
{
	Node* pRoot;
};

Tree* CreateTree()
{
	Tree* temp = (Tree*)malloc(sizeof(Tree));
	if (!temp)exit(0);
	temp->pRoot = nullptr;
	return temp;
}

Node* SearchFree(Node* n, char c)
{
	if (c < n->symb)
	{
		if (!n->pLeft)
		{
			n->pLeft = (Node*)malloc(sizeof(Node));
			if (!n->pLeft) exit(0);
			return n->pLeft;
		}
		else return SearchFree(n->pLeft, c);
	}
	else
	{
		if (!n->pRight)
		{
			n->pRight = (Node*)malloc(sizeof(Node));
			if (!n->pRight) exit(0);
			return n->pRight;
		}
		else return SearchFree(n->pRight, c);
	}
}

void Add(Tree* r, char c)
{
	if (!r->pRoot)
	{
		r->pRoot = (Node*)malloc(sizeof(Node));
		if (!r->pRoot)exit(0);
		r->pRoot->symb = c;
		r->pRoot->pLeft = r->pRoot->pRight = nullptr;
		return;
	}
	else
	{
		Node* node = SearchFree(r->pRoot, c);
		node->symb = c;
		node->pLeft = node->pRight = nullptr;
		return;
	}
}

void PrintTree(Node* br, int level = 0)
{
	if (br)
	{
		PrintTree(br->pRight, level + 1);
		for (int i = 0; i < level; i++) printf(" ");
		printf("%c\n", br->symb);
		PrintTree(br->pLeft, level + 1);
	}
}

int TreeDepth(Node* br, int depth = 0)
{
	if (!br) return depth;
	else return max(TreeDepth(br->pLeft, depth + 1), TreeDepth(br->pRight, depth + 1));
}

void DeleteTree(Node* br)
{
	if (!br) return;
	DeleteTree(br->pLeft);
	DeleteTree(br->pRight);
	free(br);
	return;
}

int main()
{
	Tree* tree = CreateTree();
	char* str = (char*)malloc(80 * sizeof(char));
	if (!str) exit(1);
	printf("Enter the string: ");
	fgets(str, 80, stdin);
	str[strlen(str) - 1] = '\0';
	for (int i = 0; str[i]; i++) Add(tree, str[i]);
	free(str);
	printf("Tree:\n");
	PrintTree(tree->pRoot);
	printf("Depth of the tree: %d", TreeDepth(tree->pRoot));
	DeleteTree(tree->pRoot);
	free(tree);
	printf("\nPress Enter to exit");
	getchar();
	return 0;
}