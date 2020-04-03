

#ifndef Lr1H
#define Lr1H

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>

class TForm1 : public TForm
{
__published:
	TShape *Road;
	TShape *Shape1;
	TShape *Shape2;
	TShape *Shape3;
	TShape *Shape4;
	TShape *Shape5;
	TShape *Shape6;
	TShape *Shape7;
	TShape *Shape8;
	TShape *Shape9;
	TShape *Shape10;
	TButton *Button2;
	TTimer *Timer1;
	TTimer *Timer2;
	TTimer *Timer3;
	TShape *Shape11;
	TShape *Shape12;
	TShape *Shape13;
	TShape *Shape14;
	TShape *Shape15;
	TShape *Shape16;
	TShape *Shape17;
	TShape *Shape18;
	TShape *Shape19;
	TShape *Shape20;
	TShape *Shape21;
	TShape *Shape22;
	TShape *Shape23;
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall Timer2Timer(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Timer3Timer(TObject *Sender);
private:	
public:		
	__fastcall TForm1(TComponent* Owner);
};

extern PACKAGE TForm1 *Form1;

#endif
