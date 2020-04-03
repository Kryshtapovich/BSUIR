//---------------------------------------------------------------------------
#include <vcl.h>
#include <math.h>
#include <windows.h>
#pragma hdrstop

#include "Unit1.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Ellipse.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
Rectangle rec, sq;
Triangle tr;
Ellipse el, circ;
int x, y;
double a;
//---------------------------------------------------------------------------
void CleanGB1();
void CleanGB2();
template <class X>
void Figure(X obj);
template <class X>
bool Check(X obj, int x, int y);
template <class X>
void ifRotate(X obj, double a);
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent *Owner) : TForm(Owner) {}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
									  int x, int y)
{
	CleanGB1();
	if (Edit1->Text != "" && Edit2->Text != "" && RadioButton1->Checked == True)
	{
		int a = StrToInt(Edit1->Text);
		int b = StrToInt(Edit2->Text);
		rec.Set(x, y, x + a, y + b);
		Figure(rec);
	}
	if (Edit3->Text != "" && RadioButton2->Checked == True)
	{
		int a = StrToInt(Edit3->Text);
		sq.Set(x, y, x + a, y + a);
		Figure(sq);
	}
	if (RadioButton3->Checked == True && Edit4->Text != "")
	{
		int a = StrToInt(Edit4->Text);
		tr.Set(x, y, a);
		Figure(tr);
	}
	if (RadioButton4->Checked == True && Edit7->Text != "" && Edit8->Text != "")
	{
		int a = StrToInt(Edit7->Text);
		int b = StrToInt(Edit8->Text);
		el.Set(x, y, x + 2 * a, y + 2 * b);
		Figure(el);
	}
	if (RadioButton5->Checked == True && Edit9->Text != "")
	{
		int r = StrToInt(Edit9->Text);
		circ.Set(x, y, x + 2 * r, y + 2 * r);
		Figure(circ);
	}
}
//---------------------------------------------------------------------------
void CleanGB1()
{
	Form1->Edit1->Enabled = False;
	Form1->Edit2->Enabled = False;
	Form1->Edit3->Enabled = False;
	Form1->Edit4->Enabled = False;
	Form1->Edit7->Enabled = False;
	Form1->Edit8->Enabled = False;
	Form1->Edit9->Enabled = False;
}
//---------------------------------------------------------------------------
void CleanGB2()
{
	Form1->Edit12->Enabled = False;
	Form1->Edit14->Enabled = False;
	Form1->Edit15->Enabled = False;
}
//---------------------------------------------------------------------------
template <class X>
void Figure(X obj)
{
	obj.Draw(Form1->Canvas);
	obj.MassCenter();
	Form1->Label2->Caption = abs(obj.Square());
	Form1->Label4->Caption = obj.Perimetr();
	Form1->Label6->Caption = "X: " + IntToStr(obj.massx) + " Y: " + IntToStr(obj.massy);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RadioButton1Click(TObject *Sender)
{
	CleanGB1();
	Edit1->Enabled = True;
	Edit2->Enabled = True;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RadioButton2Click(TObject *Sender)
{
	CleanGB1();
	Edit3->Enabled = True;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RadioButton4Click(TObject *Sender)
{
	CleanGB1();
	Edit7->Enabled = True;
	Edit8->Enabled = True;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RadioButton3Click(TObject *Sender)
{
	CleanGB1();
	Edit4->Enabled = True;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RadioButton5Click(TObject *Sender)
{
	CleanGB1();
	Edit9->Enabled = True;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	switch (Key)
	{
	case 65:
		if (RadioButton1->Checked == True)
		{
			rec.Move(Form1->Canvas, 65);
			Figure(rec);
		}
		if (RadioButton2->Checked == True)
		{
			sq.Move(Form1->Canvas, 65);
			Figure(sq);
		}
		if (RadioButton3->Checked == True)
		{
			tr.Move(Form1->Canvas, 65);
			Figure(tr);
		}
		if (RadioButton4->Checked == True)
		{
			el.Move(Form1->Canvas, 65);
			Figure(el);
		}
		if (RadioButton5->Checked == True)
		{
			circ.Move(Form1->Canvas, 65);
			Figure(circ);
		}
		break;
	case 87:
		if (RadioButton1->Checked == True)
		{
			rec.Move(Form1->Canvas, 87);
			Figure(rec);
		}
		if (RadioButton2->Checked == True)
		{
			sq.Move(Form1->Canvas, 87);
			Figure(sq);
		}
		if (RadioButton3->Checked == True)
		{
			tr.Move(Form1->Canvas, 87);
			Figure(tr);
		}
		if (RadioButton4->Checked == True)
		{
			el.Move(Form1->Canvas, 87);
			Figure(el);
		}
		if (RadioButton5->Checked == True)
		{
			circ.Move(Form1->Canvas, 87);
			Figure(circ);
		}
		break;
	case 68:
		if (RadioButton1->Checked == True)
		{
			rec.Move(Form1->Canvas, 68);
			Figure(rec);
		}
		if (RadioButton2->Checked == True)
		{
			sq.Move(Form1->Canvas, 68);
			Figure(sq);
		}
		if (RadioButton3->Checked == True)
		{
			tr.Move(Form1->Canvas, 68);
			Figure(tr);
		}
		if (RadioButton4->Checked == True)
		{
			el.Move(Form1->Canvas, 68);
			Figure(el);
		}
		if (RadioButton5->Checked == True)
		{
			circ.Move(Form1->Canvas, 68);
			Figure(circ);
		}
		break;
	case 83:
		if (RadioButton1->Checked == True)
		{
			rec.Move(Form1->Canvas, 83);
			Figure(rec);
		}
		if (RadioButton2->Checked == True)
		{
			sq.Move(Form1->Canvas, 83);
			Figure(sq);
		}
		if (RadioButton3->Checked == True)
		{
			tr.Move(Form1->Canvas, 83);
			Figure(tr);
		}
		if (RadioButton4->Checked == True)
		{
			el.Move(Form1->Canvas, 83);
			Figure(el);
		}
		if (RadioButton5->Checked == True)
		{
			circ.Move(Form1->Canvas, 83);
			Figure(circ);
		}
		break;
	case 32:
		Repaint();
		break;
	}
	if (RadioButton6->Checked == True && Edit14->Text != "" && Edit15->Text != "" && Key == 13)
	{
		x = StrToInt(Edit14->Text);
		y = StrToInt(Edit15->Text);
		CleanGB2();
		if (RadioButton1->Checked == True)
			rec.DxDy(x, y);
		if (RadioButton2->Checked == True)
			sq.DxDy(x, y);
		if (RadioButton3->Checked == true)
			tr.DxDy(x, y);
		if (RadioButton4->Checked == True)
			el.DxDy(x, y);
		if (RadioButton5->Checked == True)
			circ.DxDy(x, y);
		Form1->Timer1->Enabled = True;
	}
	if (RadioButton8->Checked == True && Edit12->Text != "" && Key == 13)
	{
		a = StrToFloat(Edit12->Text);
		a = a * M_PI / 180;
		Timer2->Enabled = True;
		CleanGB2();
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormMouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
										 bool &Handled)
{
	if (RadioButton1->Checked == True)
	{
		rec.Resize(Form1->Canvas, 1);
		Figure(rec);
	}
	if (RadioButton2->Checked == True)
	{
		sq.Resize(Form1->Canvas, 1);
		Figure(sq);
	}
	if (RadioButton3->Checked == True)
	{
		tr.Resize(Form1->Canvas, 1);
		Figure(tr);
	}
	if (RadioButton4->Checked == True)
	{
		el.Resize(Form1->Canvas, 1);
		Figure(el);
	}
	if (RadioButton5->Checked == True)
	{
		circ.Resize(Form1->Canvas, 1);
		Figure(circ);
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormMouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
										   bool &Handled)
{
	if (RadioButton1->Checked == True)
	{
		rec.Resize(Form1->Canvas, 0);
		Figure(rec);
	}
	if (RadioButton2->Checked == True)
	{
		sq.Resize(Form1->Canvas, 0);
		Figure(sq);
	}
	if (RadioButton3->Checked == True)
	{
		tr.Resize(Form1->Canvas, 0);
		Figure(tr);
	}
	if (RadioButton4->Checked == True)
	{
		el.Resize(Form1->Canvas, 0);
		Figure(el);
	}
	if (RadioButton5->Checked == True)
	{
		circ.Resize(Form1->Canvas, 0);
		Figure(circ);
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RadioButton6Click(TObject *Sender)
{
	CleanGB2();
	Edit14->Enabled = True;
	Edit15->Enabled = True;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
	if (RadioButton1->Checked == True)
	{
		rec.MoveMC(Form1->Canvas, x, y);
		Figure(rec);
		Check(rec, x, y);
	}
	if (RadioButton2->Checked == True)
	{
		sq.MoveMC(Form1->Canvas, x, y);
		Figure(sq);
		Check(sq, x, y);
	}
	if (RadioButton3->Checked == True)
	{
		tr.MoveMC(Form1->Canvas, x, y);
		Figure(tr);
		Check(tr, x, y);
	}
	if (RadioButton4->Checked == True)
	{
		el.MoveMC(Form1->Canvas, x, y);
		Figure(el);
		Check(el, x, y);
	}
	if (RadioButton5->Checked == True)
	{
		circ.MoveMC(Form1->Canvas, x, y);
		Figure(circ);
		Check(circ, x, y);
	}
}
//---------------------------------------------------------------------------
template <class X>
bool Check(X obj, int x, int y)
{
	if (obj.massx == x && obj.massy == y)
		return true;
	else
		return false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RadioButton8Click(TObject *Sender)
{
	CleanGB2();
	Edit12->Enabled = True;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer2Timer(TObject *Sender)
{
	if (RadioButton1->Checked == True)
		rec.Rotate(Form1->Canvas, a);
	ifRotate(rec, a);
	if (RadioButton2->Checked == True)
		sq.Rotate(Form1->Canvas, a);
	ifRotate(sq, a);
	if (RadioButton3->Checked == True)
		tr.Rotate(Form1->Canvas, a);
	ifRotate(tr, a);
}
//---------------------------------------------------------------------------
template <class X>
void ifRotate(X obj, double a)
{
	if (obj.angle >= a)
		Form1->Timer2->Enabled = False;
}
