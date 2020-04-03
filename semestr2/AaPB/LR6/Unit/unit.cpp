//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "Tree.h"
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
Tree tree;
void Enable()
{
	Form1->Button2->Enabled = True;
	Form1->Button3->Enabled = True;
	Form1->Button4->Enabled = True;
	Form1->Button5->Enabled = True;
	Form1->Button6->Enabled = True;
	Form1->Button7->Enabled = True;
	Form1->Button8->Enabled = True;
}
void Disable()
{
	Form1->Button2->Enabled = False;
	Form1->Button3->Enabled = False;
	Form1->Button4->Enabled = False;
	Form1->Button5->Enabled = False;
	Form1->Button6->Enabled = False;
	Form1->Button7->Enabled = False;
	Form1->Button8->Enabled = False;
}
bool IsRepeat(int num)
{
	for(int i = 1 ; i < Form1->StringGrid1->RowCount; i++)
	{
		if(num == Form1->StringGrid1->Cells[1][i].ToInt()) return false;
	}
	return true;
}
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	StringGrid1->Cells[0][0] = "Фамилия";
	StringGrid1->Cells[1][0] = "Номер в команде";
	Memo1->Lines->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	try
	{
		AnsiString str = Edit1->Text;
		int num = StrToInt(Edit2->Text);
		if(IsRepeat(num) && Edit1->Text != "")
		{
			if(num <= 0 || num >= 100)
			{
				Edit2->Text = "";
				ShowMessage("Некорректный номер");
			}
			else
			{

				StringGrid1->RowCount++;
				StringGrid1->Cells[0][StringGrid1->RowCount - 1] = str;
				StringGrid1->Cells[1][StringGrid1->RowCount - 1] = num;
				tree.AddNode(str, num);
				Memo1->Lines->Add("Добавлен участник");
				Memo1->Lines->Add("Фамилия: " + str);
				Memo1->Lines->Add("Номер: " + IntToStr(num));
				Memo1->Lines->Add("\n");
				tree.ShowTree(Form1->TreeView1);
				Enable();
				Edit1->Text = "";
				Edit2->Text = "";
			}
		}
		else
		{
			Edit2->Text = "";
			ShowMessage("Номера не могут совпадать");
		}
	}
	catch(...)
	{
		Form1->Edit2->Text = "";
		ShowMessage("Некорректный номер");
    }

}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
	try
	{
		int num = StrToInt(Edit2->Text);
		if(num > 0 && num < 100)
		{
			AnsiString str = tree.GetPlayer(num);
			if(str != "")
			{
				Memo1->Lines->Add("Участник найден: ");
				Memo1->Lines->Add("Фамилия: " + str);
				Memo1->Lines->Add("Номер: " + IntToStr(num));
				Memo1->Lines->Add("\n");
			}
			else
			{
				Memo1->Lines->Add("Участник не найден");
				Memo1->Lines->Add("\n");
            }
		}
		else
		{
			Edit2->Text = "";
			ShowMessage("Некорректный номер");
        }
	}
	catch(...)
	{
		Edit2->Text = "";
		ShowMessage("Некорректный номер");
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
	try
	{
		int num = StrToInt(Edit2->Text);
		if(!IsRepeat(num))
		{
			AnsiString str = tree.GetPlayer(num);
			tree.DeleteNode(num);
			tree.ShowTree(TreeView1);
			Memo1->Lines->Add("Участник удален");
			Memo1->Lines->Add("Фамилия: " + str);
			Memo1->Lines->Add("Номер: " + IntToStr(num));
			Memo1->Lines->Add("\n");
			for(int i = 1, j = 1; i < StringGrid1->RowCount; i++)
			{
				if(StringGrid1->Cells[1][i] != num)
				{
					StringGrid1->Cells[0][j] = StringGrid1->Cells[0][i];
					StringGrid1->Cells[1][j] = StringGrid1->Cells[1][i];
					j++;
				}
			}
			StringGrid1->RowCount--;
			Edit1->Text = "";
			Edit2->Text = "";
			if(!tree.NumNodes) Disable();
		}
		else
		{
			Edit2->Text = "";
			ShowMessage("Нет участника с таким номером");
        }
	}
	catch(...)
	{
		Edit2->Text = "";
		ShowMessage("Некорректный номер");
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button4Click(TObject *Sender)
{
	tree.Balance();
	tree.ShowTree(Form1->TreeView1);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button5Click(TObject *Sender)
{
	Memo1->Lines->Add("Прямой обход");
	tree.Right(Memo1);
	Memo1->Lines->Add("\n");
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button6Click(TObject *Sender)
{
	Memo1->Lines->Add("Обратный обход");
	tree.Back(Memo1);
	Memo1->Lines->Add("\n");
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button7Click(TObject *Sender)
{
	Memo1->Lines->Add("Обход в порядке возрастания ключа");
	tree.Growth(Memo1);
	Memo1->Lines->Add("\n");
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button8Click(TObject *Sender)
{
	Memo1->Lines->Add("Количество узлов с двумя потомками: " + IntToStr(tree.TwoDaughters()));
	Memo1->Lines->Add("\n");
}
//---------------------------------------------------------------------------
