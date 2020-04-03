#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>

#ifndef unitH
#define unitH

class TForm1 : public TForm
{
__published:
	TGroupBox *GroupBox1;
	TRadioButton *RadioButton1;
	TRadioButton *RadioButton2;
	TRadioButton *RadioButton3;
	TRadioButton *RadioButton4;
	TRadioButton *RadioButton5;
	TGroupBox *GroupBox2;
	TRadioButton *RadioButton8;
	TPanel *Panel1;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TRadioButton *RadioButton6;
	TLabel *Label7;
	TEdit *Edit1;
	TLabel *Label8;
	TEdit *Edit2;
	TLabel *Label9;
	TEdit *Edit3;
	TLabel *Label13;
	TEdit *Edit7;
	TLabel *Label14;
	TEdit *Edit8;
	TLabel *Label15;
	TEdit *Edit9;
	TLabel *Label18;
	TEdit *Edit12;
	TLabel *Label19;
	TLabel *Label20;
	TLabel *Label21;
	TEdit *Edit14;
	TLabel *Label22;
	TEdit *Edit15;
	TLabel *Label10;
	TLabel *Label16;
	TEdit *Edit4;
	TTimer *Timer1;
	TTimer *Timer2;
	void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall RadioButton1Click(TObject *Sender);
	void __fastcall RadioButton2Click(TObject *Sender);
	void __fastcall RadioButton4Click(TObject *Sender);
	void __fastcall RadioButton3Click(TObject *Sender);
	void __fastcall RadioButton5Click(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormMouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall FormMouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall RadioButton6Click(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall RadioButton8Click(TObject *Sender);
	void __fastcall Timer2Timer(TObject *Sender);
private:
public:	
	__fastcall TForm1(TComponent* Owner);
};

extern PACKAGE TForm1 *Form1;

#endif
