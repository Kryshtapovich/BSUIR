#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

#ifndef unitH
#define unitH

class TForm1 : public TForm
{
__published
	TListBox *ListBox1;
	TButton *Button1;
	TListBox *ListBox2;
	TListBox *ListBox3;
	TButton *Button2;
	TLabel *Label1;
	TLabel *Label2;
	TEdit *Edit1;
	TEdit *Edit2;
	TEdit *Edit3;
	TEdit *Edit4;
	TLabel *Label3;
	TLabel *Label4;
	TEdit *Edit5;
	TEdit *Edit6;
	TLabel *Label5;
	TLabel *Label6;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:
public:	
	__fastcall TForm1(TComponent* Owner);
};

extern PACKAGE TForm1 *Form1;

#endif
