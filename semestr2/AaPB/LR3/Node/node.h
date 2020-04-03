#include <string>

#ifndef nodeH
#define nodeH

class Node
{
	public:
		Node *pNext;
		std::string country;
		std::string team;
		std::string surname;
		int num;
		int age;
		int height;
		int weight;
		Node(std::string c, std::string t, std::string s, int n, int a, int h, int w);
};

#endif
