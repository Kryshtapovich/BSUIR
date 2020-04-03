#include "Node.h"

#ifndef listH
#define listH

class List {
private:
    int size;
	Node *pHead;
public:
	List();
	~List();
	void Add(std::string c, std::string t, std::string s, int n, int a, int h, int w);
    void Delete(int index);
	int Size() {return size;};
	std::string& Country(int index);
	std::string& Team(int index);
	std::string& Surname(int index);
	int& Num(int index);
	int& Age(int index);
	int& Height(int index);
	int& Weight(int index);
};

#endif
