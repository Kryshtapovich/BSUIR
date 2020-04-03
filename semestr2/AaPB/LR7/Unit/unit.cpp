#include <vcl.h>
#include "hashtable.h"
#include "unit.h"

TForm1 *Form1;
HashTable table;

__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner)
{
	table.Create();
	srand(time(0));
	Memo1->Lines->Clear();
}

void __fastcall TForm1::Button1Click(TObject *Sender)
{
	if(Edit1->Text != "")
	{
		int key = rand() % 100;
		table.Add(key, Edit1->Text);
		table.Show(Memo1);
	}
}

void __fastcall TForm1::Button2Click(TObject *Sender)
{
	try
	{
		int key = StrToInt(Edit2->Text);
		if(key < 0)
		{
			ShowMessage("������� ���������� ����");
		}
		else
		{
			table.Delete(Memo1, key);
			table.Show(Memo1);
		}
	}
	catch(...)
	{
		ShowMessage("������� ���������� ����");
	}
	Edit2->Text = "";
}

void __fastcall TForm1::Button3Click(TObject *Sender)
{
	try
	{
		int key = StrToInt(Edit2->Text);
		if(key < 0)
		{
			ShowMessage("������� ���������� ����");
			Edit2->Text = "";
		}
		else table.Search(Memo1, key);
	}
	catch(...)
	{
		ShowMessage("������� ���������� ����");
        Edit2->Text = "";
	}
}

void __fastcall TForm1::Button4Click(TObject *Sender)
{
    table.Decrease(Memo1);
}
