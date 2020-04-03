#include <vcl.h>
#include <windows.h>
#include <DateUtils.hpp>
#include <fstream>
#include <string>
#include "firm.h"
#include "unit1.h"

TForm1* Form1;
Firm* firm;
int size = 0;
void Reading();
void ShowInfo();
void Sort();

__fastcall TForm1::TForm1(TComponent* Owner) :TForm(Owner) { Memo1->Lines->Clear(); }

void Reading()
{
	if (Form1->OpenDialog1->Execute())
	{
		ifstream fin(Form1->OpenDialog1->FileName.c_str(), ios::binary);
		while (!fin.eof())
		{
			std::string s;
			getline(fin, s);
			if (s != "\n")size++;
		}
		fin.seekg(0);
		firm = new Firm[size];
		for (int i = 0; i < size; i++)
		{
			fin >> firm[i].name >> firm[i].project >> firm[i].task >>
				firm[i].execute_date >> firm[i].start_date >> firm[i].end_date;
			Form1->ComboBox1->Items->Add(i + 1);
		}
		fin.close();
		Form1->Edit1->Enabled = True;
		Form1->Edit2->Enabled = True;
		Form1->Edit3->Enabled = True;
		Form1->DateTimePicker1->Enabled = True;
		Form1->DateTimePicker2->Enabled = True;
		Form1->DateTimePicker3->Enabled = True;
		Form1->ComboBox1->Enabled = True;
		Form1->Button2->Enabled = True;
		Form1->Button3->Enabled = True;
		Form1->Button4->Enabled = True;
		Form1->Button5->Enabled = True;
		Form1->Button6->Enabled = True;
		Form1->Button7->Enabled = True;
		Form1->Button8->Enabled = True;
	}
}
//--------------------------------------------------------------------------
void ShowInfo()
{
	Form1->Memo1->Lines->Clear();
	for (int i = 0; i < size; i++)
	{
		AnsiString str = firm[i].name.c_str();
		str = str + "    " + firm[i].project.c_str() + " " +
			IntToStr(firm[i].task) + "    " + firm[i].execute_date.c_str() + "    " + firm[i].start_date.c_str() + "    " + firm[i].end_date.c_str();
		Form1->Memo1->Lines->Add(str);
	}
}
//--------------------------------------------------------------------------
bool Compare(std::string a, std::string b)
{
	TDateTime dt1 = StrToDateTime(a.c_str());
	TDateTime dt2 = StrToDateTime(b.c_str());
	if (dt1 > dt2)return 1;
	else return 0;
}
//-------------------------------------------------------------------------
void Sort()
{
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (Compare(firm[j].end_date, firm[j + 1].end_date)) {
				Firm temp = firm[j];
				firm[j] = firm[j + 1];
				firm[j + 1] = temp;
			}
		}
	}
	Form1->Memo1->Lines->Clear();
	for (int i = 0; i < size; i++)
	{
		AnsiString str = firm[i].project.c_str();
		str = str + "    " + firm[i].end_date.c_str();
		Form1->Memo1->Lines->Add(str);
	}
}
//--------------------------------------------------------------------------
void WorkDay()
{
	if (Form1->ComboBox1->ItemIndex != -1)
	{
		int index = Form1->ComboBox1->ItemIndex;
		AnsiString str = firm[index].name.c_str();
		TDateTime dt = StrToDate(firm[index].execute_date.c_str());
		TDateTime now = Now();
		if (DayOf(dt) == DayOf(now) && MonthOf(dt) == MonthOf(now))
		{
			Form1->Memo1->Lines->Clear();
			AnsiString str = firm[index].name.c_str();
			str = str + ": " + firm[index].project.c_str() + " " + IntToStr(firm[index].task);
			for (int i = 0; i < size; i++)
			{
				if (i == index)continue;
				if (firm[index].name == firm[i].name)
				{
					str = str + ",   " + firm[i].project.c_str() + " " + IntToStr(firm[i].task);
				}
			}
			Form1->Memo1->Lines->Add(str);
		}
		else
		{
			ShowMessage("��������� ��������� ������� �� �������");
		}
	}
}
//--------------------------------------------------------------------------
void WorkMonth()
{
	int time;
	Form1->Memo1->Lines->Clear();
	for (int i = 0; i < size; i++)
	{
		if (firm[i].marker != 1 && MonthOf(StrToDateTime(firm[i].start_date.c_str())) == 3)
		{
			TDateTime dt1 = StrToDateTime(firm[i].execute_date.c_str());
			TDateTime dt2 = StrToDateTime(firm[i].start_date.c_str());
			time = DaysBetween(dt1, dt2);
		}
		else if (firm[i].marker != 1 && MonthOf(StrToDateTime(firm[i].start_date.c_str())) != 3)
		{
			TDateTime dt1 = StrToDateTime(firm[i].execute_date.c_str());
			TDateTime dt2 = StrToDateTime("01.03.2020");
			time = DaysBetween(dt1, dt2);
		}
		for (int j = i + 1; j < size; j++)
		{
			if (firm[i].name == firm[j].name && firm[i].marker != 1)
			{
				time += DaysBetween(StrToDateTime(firm[j].execute_date.c_str()), StrToDateTime(firm[j].start_date.c_str()));
				firm[j].marker = 1;
			}
		}
		if (firm[i].marker != 1)
		{
			AnsiString str = firm[i].name.c_str();
			str = str + ": " + IntToStr(time);
			Form1->Memo1->Lines->Add(str);
		}
	}
}
//--------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject* Sender)
{
	Reading();
	ShowInfo();
}

void __fastcall TForm1::Button6Click(TObject* Sender) { ShowInfo(); }

void __fastcall TForm1::Button3Click(TObject* Sender)
{
	if (Edit1->Text != "" && Edit2->Text != "" && Edit3->Text != "" && Form1->ComboBox1->ItemIndex != -1)
	{
		int index = Form1->ComboBox1->ItemIndex;
		AnsiString str = Edit1->Text;
		firm[index].name = str.c_str();
		str = Edit2->Text;
		firm[index].project = str.c_str();
		firm[index].task = StrToInt(Edit3->Text);
		str = DateToStr(DateTimePicker1->Date);
		firm[index].execute_date = str.c_str();
		str = DateToStr(DateTimePicker2->Date);
		firm[index].start_date = str.c_str();
		str = DateToStr(DateTimePicker3->Date);
		firm[index].end_date = str.c_str();
		ShowInfo();
	}
}

void __fastcall TForm1::Button2Click(TObject* Sender)
{
	if (Form1->Edit1->Text != "" && Form1->Edit2->Text != "" && Form1->Edit3->Text != "")
	{
		Firm* arr = new Firm[size + 1];
		for (int i = 0; i < size; i++) arr[i] = firm[i];
		AnsiString str = Form1->Edit1->Text;
		arr[size].name = str.c_str();
		str = Form1->Edit2->Text;
		arr[size].project = str.c_str();
		arr[size].task = StrToInt(Form1->Edit3->Text);
		str = DateToStr(Form1->DateTimePicker1->Date);
		arr[size].execute_date = str.c_str();
		str = DateToStr(Form1->DateTimePicker2->Date);
		arr[size].start_date = str.c_str();
		str = DateToStr(Form1->DateTimePicker3->Date);
		arr[size].end_date = str.c_str();
		firm = arr;
		size++;
		ShowInfo();
		Form1->ComboBox1->Items->Add(size);
	}
}

void __fastcall TForm1::Button4Click(TObject* Sender)
{
	if (Form1->ComboBox1->ItemIndex != -1)
	{
		size--;
		Firm* arr = new Firm[size];
		int del = Form1->ComboBox1->ItemIndex;
		for (int i = 0; i < del; i++) arr[i] = firm[i];
		for (int i = del; i < size; i++) arr[i] = firm[i + 1];
		firm = arr;
		ShowInfo();
		Form1->ComboBox1->DeleteSelected();
		for (int i = 0; i < size; i++)
		{
			UnicodeString s = IntToStr(i + 1);
			Form1->ComboBox1->Items->Strings[i] = s;
		}
	}
}

void __fastcall TForm1::Button5Click(TObject* Sender) { Sort(); }

void __fastcall TForm1::Button7Click(TObject* Sender) { WorkDay(); }

void __fastcall TForm1::Button8Click(TObject* Sender) { WorkMonth(); }

void __fastcall TForm1::FormClose(TObject* Sender, TCloseAction& Action)
{
	if (SaveDialog1->Execute())
	{
		ofstream fout(SaveDialog1->FileName.c_str(), ofstream::app);
		for (int i = 0; i < size; i++)
		{
			fout << firm[i].name << " " << firm[i].project << " " << firm[i].task << " " <<
				firm[i].execute_date << " " << firm[i].start_date << " " << firm[i].end_date << "\n";
		}
		fout.close();
	}
}
