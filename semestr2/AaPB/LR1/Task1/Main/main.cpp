#include <vcl.h>
#include <windows.h>
#include "main.h"
#include "Unit1.h"
#include "Unit2.h"

TForm1 *Form1;
Rectangle wing(10, 10, 60, 80);
Rectangle tail(5, 80, 100, 130);
Rectangle body(100, 70, 250, 150);
Rectangle cabin(250, 80, 280, 130);
Rectangle cabglass(260, 80, 280, 120);
Circle ilum1(120, 90, 150, 120);
Circle ilum2(170, 90, 200, 120);
Circle ilum3(220, 90, 250, 120);
Circle shas1(120, 120, 150, 150);
Circle shas2(210, 120, 240, 150);

__fastcall TForm1::TForm1(TComponent *Owner)
	: TForm(Owner)
{
}

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
	Repaint();
	wing.Move(Form1->Canvas);
	wing.Show(Form1->Canvas, clWhite);
	tail.Move(Form1->Canvas);
	tail.Show(Form1->Canvas, clWhite);
	body.Move(Form1->Canvas);
	body.Show(Form1->Canvas, clWhite);
	cabin.Move(Form1->Canvas);
	cabin.Show(Form1->Canvas, clWhite);
	cabglass.Move(Form1->Canvas);
	cabglass.Show(Form1->Canvas, clSkyBlue);
	ilum1.Move(Form1->Canvas);
	ilum1.Show(Form1->Canvas, clSkyBlue);
	ilum2.Move(Form1->Canvas);
	ilum2.Show(Form1->Canvas, clSkyBlue);
	ilum3.Move(Form1->Canvas);
	ilum3.Show(Form1->Canvas, clSkyBlue);
	shas1.Move(Form1->Canvas);
	shas2.Move(Form1->Canvas);
	if (body.x2 == 500)
		Timer1->Enabled = False;
}

void __fastcall TForm1::Timer2Timer(TObject *Sender)
{
	if (Timer1->Enabled == False && body.x2 < 1050)
	{
		Repaint();
		wing.MoveX(Form1->Canvas, clWhite);
		tail.MoveX(Form1->Canvas, clWhite);
		body.MoveX(Form1->Canvas, clWhite);
		cabin.MoveX(Form1->Canvas, clWhite);
		cabglass.MoveX(Form1->Canvas, clSkyBlue);
		ilum1.MoveX(Form1->Canvas, clSkyBlue);
		ilum2.MoveX(Form1->Canvas, clSkyBlue);
		ilum3.MoveX(Form1->Canvas, clSkyBlue);
		shas1.MoveX(Form1->Canvas, clBlack);
		shas2.MoveX(Form1->Canvas, clBlack);
	}
}

void __fastcall TForm1::Button2Click(TObject *Sender)
{
	Timer3->Enabled = True;
	Button2->Enabled = False;
	if (Timer3->Enabled == False)
		Timer2->Enabled = True;
}

void __fastcall TForm1::Timer3Timer(TObject *Sender)
{
	Repaint();
	wing.Show(Form1->Canvas, clWhite);
	tail.Show(Form1->Canvas, clWhite);
	body.Show(Form1->Canvas, clWhite);
	cabin.Show(Form1->Canvas, clWhite);
	cabglass.Show(Form1->Canvas, clSkyBlue);
	ilum1.Show(Form1->Canvas, clSkyBlue);
	ilum2.Show(Form1->Canvas, clSkyBlue);
	ilum3.Show(Form1->Canvas, clSkyBlue);
	shas1.MoveDown(Canvas, clBlack);
	shas2.MoveDown(Canvas, clBlack);
	if (shas2.y2 == 430)
	{
		Timer3->Enabled = False;
		Timer2->Enabled = True;
	}
}

