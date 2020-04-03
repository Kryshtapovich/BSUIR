#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

#ifndef unitH
#define unitH

class TForm1 : public TForm
{
__published:	
	TLabel *Label1;
	TLabel *Label2;
	TEdit *Edit1;
	TEdit *Edit2;
	TLabel *Label3;
	TLabel *Label4;
	TEdit *Edit3;
	TEdit *Edit4;
	TLabel *Label5;
	TLabel *Label6;
	TEdit *Edit5;
	TLabel *Label7;
	TEdit *Edit6;
	TButton *Button1;
	TEdit *Edit7;
	TComboBox *ComboBox1;
	TLabel *Label8;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall ComboBox1Select(TObject *Sender);


private:
public:	
	__fastcall TForm1(TComponent* Owner);
};

extern PACKAGE TForm1 *Form1;

#endif
