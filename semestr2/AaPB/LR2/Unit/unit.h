#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.DBCtrls.hpp>

#ifndef unitH
#define unitH

class TForm1 : public TForm
{
__published:	
	TMemo *Memo1;
	TEdit *Edit1;
	TLabel *Label2;
	TLabel *Label3;
	TEdit *Edit2;
	TLabel *Label4;
	TEdit *Edit3;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TButton *Button1;
	TButton *Button2;
	TButton *Button3;
	TButton *Button4;
	TDateTimePicker *DateTimePicker1;
	TDateTimePicker *DateTimePicker2;
	TDateTimePicker *DateTimePicker3;
	TOpenDialog *OpenDialog1;
	TLabel *Label8;
	TButton *Button5;
	TSaveDialog *SaveDialog1;
	TButton *Button6;
	TComboBox *ComboBox1;
	TButton *Button7;
	TButton *Button8;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall Button7Click(TObject *Sender);
	void __fastcall Button8Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:
public:	
	__fastcall TForm1(TComponent* Owner);
};

extern PACKAGE TForm1 *Form1;

#endif
