#include "hashtable.h"

HashNode :: HashNode(int k, AnsiString i)
{
	key = k;
	info = i;
	nodes = 1;
	pNext = nullptr;
}

void HashTable :: Create()
{
	elements = (HashNode**)calloc(size, sizeof(HashNode*));
	for(int i = 0; i < size; i++)
	{
		elements[i] = (HashNode*)calloc(1, sizeof(HashNode));
        elements[i] = nullptr;
	}
}

int HashTable :: Hash(int num)
{
	if(!num) return num % size + 10;
	else return num % size;
}

void HashTable :: Add(int n, AnsiString str)
{
	int i = Hash(n);
	if(!elements[i]) elements[i] = new HashNode(n, str);
	else
	{
		HashNode *temp = elements[i];
		while(temp->pNext) temp = temp->pNext;
		temp->pNext = new HashNode(n, str);
		elements[i]->nodes++;
	}
}

void HashTable :: Delete(TMemo *Memo, int num)
{
	int i = Hash(num);
	int marker = 0;
	for(HashNode *del = elements[i], *temp = nullptr; del; del = del->pNext)
	{
		if(del->key == num)
		{
			if(!temp) elements[i] = del->pNext;
			else
			{
				temp->pNext = del->pNext;
                elements[i]->nodes--;
			}
			del = nullptr;
			marker++;
			break;
		}
		temp = del;
	}
	if(!marker) ShowMessage("��� �������� � ����� ������");
}

void HashTable :: Show(TMemo *Memo)
{
	Memo->Lines->Clear();
	for(int  i = 0; i < size; i++)
	{
		if(elements[i])
		{
			AnsiString str = "(" + IntToStr(elements[i]->key) + ", " + elements[i]->info + ")";
			if(!elements[i]->pNext) Memo->Lines->Add(str);
			else
			{
				AnsiString s = "";
				HashNode *temp = elements[i]->pNext;
				while(temp)
				{
					s += "   (" + IntToStr(temp->key) +", " + temp->info + ")";
					temp = temp->pNext;
				}
				str += s;
				Memo->Lines->Add(str);
            }
		}
	}
	Memo->Lines->Add("\n");
}

void HashTable :: Search(TMemo *Memo, int num)
{
	int i = Hash(num);
	if(!elements[i])
	{
		ShowMessage("��� �������� � ����� ������");
        return;
	}
	if(elements[i]->key == num)
	{
		Memo->Lines->Add("������� ������");
		Memo->Lines->Add("����: " + IntToStr(elements[i]->key) + "   ��������: " +
		elements[i]->info);
	}
	else
	{
		int marker = 0;
		for(HashNode *temp = elements[i]->pNext; temp; temp = temp->pNext)
		{
			if(temp->key == num)
			{
				marker++;
                Memo->Lines->Add("������� ������");
				Memo->Lines->Add("����: " + IntToStr(temp->key) + "   ��������: " +
				temp->info);
				break;
            }
		}
		if(!marker) ShowMessage("��� �������� � ����� ������");
	}
	Memo->Lines->Add("\n");
}

void HashTable :: Decrease(TMemo *Memo)
{
	int length = 0;
	for(int i = 0; i < size; i++)
	{
		if(elements[i])
		{
			if(elements[i]->pNext) length += elements[i]->nodes;
			else length++;
		}
	}
	HashNode **arr = (HashNode**)calloc(length, sizeof(HashNode*));
	for(int i = 0; i < length; i++)
	{
		arr[i] = (HashNode*)calloc(1, sizeof(HashNode));
		arr[i] = new HashNode(0, "");
	}
	for(int i = 0, j = 0; i < size; i++)
	{
		if(elements[i])
		if(!elements[i]->pNext)
		{
			arr[j]->key = elements[i]->key;
			arr[j]->info = elements[i]->info;
			j++;
        }
		else
		{
			HashNode *temp = elements[i];
			while(temp)
			{
				arr[j]->key = temp->key;
				arr[j]->info = temp->info;
				j++;
				temp = temp->pNext;
            }
		}
	}

   int left = 0, right = length - 1;
   while(left <= right)
   {
		for(int i = right; i >=left ; i--)
		if(arr[i - 1]->key < arr[i]->key)
		 Swap(arr[i - 1], arr[i]);
		left++;

		for(int i = left; i <= right; i++)
		if(arr[i - 1]->key < arr[i]->key)
		Swap(arr[i - 1], arr[i]);
		right--;
   }

   Memo->Lines->Clear();
   for(int i = 0; i < length; i++)
   Memo->Lines->Add("����: " + IntToStr(arr[i]->key) + "   ��������: " + arr[i]->info);
   Memo->Lines->Add("\n");
}

void HashTable :: Swap(HashNode *a, HashNode *b)
{
	int n = a->key;
	AnsiString s = a->info;
	a->key = b->key;
	a->info = b->info;
	b->key = n;
	b->info = s;
}
