#include <vcl.h>
#include <ctime>
#include "queue.h"
#include "element.h"
#include "unit.h"

TForm1 *Form1;
Queue *q1 = new Queue();
Queue *q2 = new Queue();

__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner){}

void __fastcall TForm1::Button1Click(TObject *Sender)
{
	srand(time(0));
	int amount = q1->size;
	for (int i = amount; i < amount + 10; i++)
	{
		q1->Add(rand() % 200 - 100);
		ListBox1->Items->Add(IntToStr(i + 1) + ".  " + q1->GetNum(i));
		q2->Add(rand() % 200 - 100);
		ListBox2->Items->Add(IntToStr(i + 1) + ".  " + q2->GetNum(i));
	}
	Edit1->Text = q1->GetMax();
	Edit2->Text = q1->GetMin();
	Edit3->Text = q2->GetMax();
	Edit4->Text = q2->GetMin();
	Button2->Enabled = True;
}

void __fastcall TForm1::Button2Click(TObject *Sender)
{
	ListBox3->Items->Clear();
	int indexMin, indexMax;
	for(int i = 0; i < q1->size; i++)
	{
		if(q1->GetNum(i) == q1->GetMax()) indexMax = i;
		if(q1->GetNum(i) == q1->GetMin()) indexMin = i;
	}
	Queue *q3 = new Queue();
	if(indexMin < indexMax)
	{
		for(int i = 0; i <= indexMin; i++) q3->Add(q1->GetNum(i));
		for(int i = 0; i < q2->size; i++) q3->Add(q2->GetNum(i));
		for(int i = indexMax; i < q1->size; i++) q3->Add(q1->GetNum(i));
	}
	else
	{
		for(int i = 0; i <= indexMax; i++) q3->Add(q1->GetNum(i));
		for(int i = 0; i < q2->size; i++) q3->Add(q2->GetNum(i));
		for(int i = indexMin; i < q1->size; i++) q3->Add(q1->GetNum(i));
	}
	Element *temp = q3->pHead;
	Edit5->Text = q3->GetMax();
	Edit6->Text = q3->GetMin();
	for(int i = 0; temp != nullptr; i++)
	{
		ListBox3->Items->Add(IntToStr(i + 1) + ".  " + q3->GetNum(i));
		temp = temp->pNext;
	}
	q3->DeleteQueue();
}

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
	q1->DeleteQueue();
	q2->DeleteQueue();
}
