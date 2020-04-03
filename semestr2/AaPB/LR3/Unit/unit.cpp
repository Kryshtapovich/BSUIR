#include <vcl.h>
#include "list.h"
#include "unit.h"

TForm1 *Form1;
List *lst = new List();
int size = 0;
void Lock()
{
	Form1->Button1->Enabled = False;
	Form1->Button3->Enabled = False;
	Form1->Button4->Enabled = False;
}
void UnLock()
{
	Form1->Button1->Enabled = True;
	Form1->Button3->Enabled = True;
	Form1->Button4->Enabled = True;
}
void CleanEdits()

{
	Form1->Edit1->Text = "";
	Form1->Edit2->Text = "";
	Form1->Edit3->Text = "";
	Form1->Edit4->Text = "";
	Form1->Edit5->Text = "";
	Form1->Edit6->Text = "";
	Form1->Edit7->Text = "";
}
AnsiString ShowNode(int index)
{
	AnsiString str = lst->Country(index).c_str();
	str = str + "    " + lst->Team(index).c_str() + "    " +
	lst->Surname(index).c_str() + "    " + IntToStr(lst->Num(index)) + "    " + IntToStr(lst->Age(index)) + "    " +
	IntToStr(lst->Height(index)) + "    " + IntToStr(lst->Weight(index));
	return str;
}
void ShowList()
{
    Form1->Memo1->Lines->Clear();
	for (int i = 0; i < size; i++)
	{
		AnsiString str = IntToStr(i + 1) + ". " +ShowNode(i);
		Form1->Memo1->Lines->Add(str);
	}
}
void YoungestTeam()
{
	std::string *temp = new std::string[size];
	for(int i = 0; i < size; i++)temp[i] = lst->Team(i);
	for(int i = 0; i < size; i++)
	{
		for(int j = i + 1; j < size; j++) if(temp[i] == temp[j])temp[j] = "#";
	}
	int count = 0;
	for(int i = 0; i < size; i++) if(temp[i] != "#")count++;
	std::string *teams = new std::string[count];
	for (int i = 0, j = 0; i < size; i++) if (temp[i] != "#") {teams[j] = temp[i];j++;}
	delete[]temp;
	int *sp_in_team = new int[count];
	for(int i = 0; i < count ; i++) sp_in_team[i] = 0;
	for(int i = 0; i < size ; i++)
	{
		for(int j = 0; j < count; j++) if(lst->Team(i) == teams[j]) sp_in_team[j]++;
	}
	int *sum_age = new int[count];
	for(int i = 0; i < count ; i++)sum_age[i] = 0;
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < count; j++) if(lst->Team(i) == teams[j])sum_age[j] += lst->Age(i);
	}
	int *av_age = new int[count];
	for(int i = 0; i < count; i++)av_age[i] = sum_age[i] / sp_in_team[i];
    delete[]sp_in_team;
	delete[]sum_age;
	int min = av_age[0], index = 0;
	for(int i = 0; i < count; i++) if(av_age[i] < min){min = av_age[i]; index = i;}
	delete[]av_age;
	Form1->Memo1->Lines->Clear();
	for(int i = 0, j = 1; i < size; i++)
	{
		if(lst->Team(i) == teams[index])
		{
			AnsiString str = IntToStr(j) + ". " +ShowNode(i);
			Form1->Memo1->Lines->Add(str);
			j++;
		 }
	}
	delete[]teams;
}
void ShowTeam(std::string, int);
void HeightTeam(int height)
{
	std::string *temp = new std::string[size];
	for(int i = 0; i < size; i++)temp[i] = lst->Team(i);
	for(int i = 0; i < size; i++)
	{
		for(int j = i + 1; j < size; j++) if(temp[i] == temp[j])temp[j] ="#";
	}
	int num = 0;
	for(int i = 0; i < size; i++) if(temp[i] != "#") num++;
	std::string *teams = new std::string[num];
	for(int i = 0, j = 0; i < size; i++)if(temp[i] != "#"){teams[j] = temp[i];j++;}
	delete[]temp;
	for(int i = 0; i < num; i++)
	{
		ShowTeam(teams[i], height);
    }
}
void ShowTeam(std::string team, int height)
{
	int count = 0;
	for(int i = 0; i < size; i++)
	{
		if(lst->Team(i) == team)count++;
		if(lst->Height(i) >= height)count--;
	}
	if(count == 0)
	{
		Form1->Memo1->Lines->Clear();
		for(int i = 0, j = 1; i < size; i++)
		{
			if(lst->Team(i) == team)
			{
                AnsiString str = IntToStr(j) + ". " +ShowNode(i);
				Form1->Memo1->Lines->Add(str);
				j++;
            }
        }
    }
}

__fastcall TForm1::TForm1(TComponent* Owner) :TForm(Owner) {Memo1->Lines->Clear();}

void __fastcall TForm1::Button2Click(TObject *Sender)
{
	AnsiString s;
	std::string country, team, surname;
	if(Edit1->Text == "")
	{
		ShowMessage("������� �������� ������!");
		Edit1->Text = "";
	}else
	{
		s = Edit1->Text;
		country = s.c_str();
	}
	if(Edit2->Text == "")
	{
		ShowMessage("������� �������� �������!");
		Edit2->Text = "";
	}else
	{
		s = Edit2->Text;
		team = s.c_str();
	}
	if(Edit3->Text == "")
	{
		ShowMessage("������� �������!");
		Edit3->Text = "";
	}else
	{
		s = Edit3->Text;
		surname = s.c_str();
	}
	int num, age, height, weight;
	try
	{
		num = StrToInt(Edit4->Text);
		if(num <= 0)
		{
			ShowMessage("������� ���������� �����!");
			Edit4->Text = "";
		}
	}
	catch(...)
	{
		ShowMessage("������� ���������� �����!");
		Edit4->Text = "";
	}

	try
	{
		age = StrToInt(Edit5->Text);
		if(age <= 0)
		{
			ShowMessage("������� ���������� �������!");
			Edit5->Text = "";
		}
	}
	catch(...)
	{
		ShowMessage("������� ���������� �������!");
		Edit5->Text = "";
	}

	try
	{
		height = StrToInt(Edit6->Text);
		if(height <= 0)
		{
			ShowMessage("������� ���������� ����!");
			Edit6->Text = "";
		}
	}
	catch(...)
	{
		ShowMessage("������� ���������� ����!");
		Edit6->Text = "";
	}

	try
	{
		weight = StrToInt(Edit7->Text);
		if(weight <= 0)
		{
			ShowMessage("������� ���������� ���!");
			Edit7->Text = "";
		}
	}
	catch(...)
	{
		ShowMessage("������� ���������� ���!");
		Edit7->Text = "";
	}
	if(country != "" && team != "" && surname != "" && Edit4->Text != "" && Edit5->Text != "" && Edit6->Text != "" && Edit7->Text != "")
	{
		lst->Add(country, team, surname, num, age, height, weight);
		size++;
		ComboBox1->Items->Add(size);
		CleanEdits();
		ShowList();
	}
	if(size != 0)UnLock();
}

void __fastcall TForm1::Button1Click(TObject *Sender)
{
	Form1->Memo1->Lines->Clear();
	if(Form1->Edit3->Text != "" && Form1->Edit6->Text == "" && Form1->Edit7->Text == "")
	{
		int count = 0;
		AnsiString s = Form1->Edit3->Text;
		std::string str =s.c_str();
		for(int i = 0; i < size; i++)
		{
			if(lst->Surname(i) == str)
			{
				Form1->Memo1->Lines->Add(ShowNode(i));
				count++;
			}
		}
		if(count == 0)ShowMessage("��������� � ����� �������� ��� � �������!");
	}
	else if(Form1->Edit3->Text == "" && Form1->Edit7->Text != "" && Form1->Edit6->Text == "")
	{
		int w, count = 0;
		try
		{
			w = StrToInt(Edit7->Text);
			if(w <= 0)
			{
				ShowMessage("������� ���������� ���!");
				Edit7->Text = "";
			}
		}
		catch(...)
		{
			ShowMessage("������� ���������� ���!");
			Edit7->Text = "";
		}

		for(int i = 0; i < size; i++)
		{
			if(lst->Weight(i) == w)
			{
				Form1->Memo1->Lines->Add(ShowNode(i));
				count++;
			}
		}
		if(count == 0) ShowMessage("� ������� ��� ��������� � ��������� ������� ���������!");

	}
	else if(Form1->Edit3->Text == "" && Form1->Edit7->Text == "" && Form1->Edit6->Text != "")
	{
		int h;
        try
		{
			h = StrToInt(Edit6->Text);
			if(h <= 0)
			{
				ShowMessage("������� ���������� ����!");
				Edit6->Text = "";
			}
		}
		catch(...)
		{
			ShowMessage("������� ���������� ����!");
			Edit6->Text = "";
		}
		HeightTeam(h);
		if(Form1->Memo1->Lines->Count == 0)
		{
			ShowMessage("� ������� ��� �������, ��� �������� ������� ���� �� ���� ���������� �����!");
			Edit6->Text = "";
		}
	}
	else ShowList();
};

void __fastcall TForm1::Button3Click(TObject *Sender)
{
	size--;
	int num = Form1->ComboBox1->ItemIndex;
	lst->Delete(num);
	ShowList();
    Form1->ComboBox1->DeleteSelected();
	for (int i = 0; i < size; i++)
	{
		UnicodeString s = IntToStr(i + 1);
		Form1->ComboBox1->Items->Strings[i] = s;
	}
}

void __fastcall TForm1::Button4Click(TObject *Sender){YoungestTeam();}
