#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Grids.hpp>

#ifndef unitH
#define unitH

class TForm1 : public TForm
{
__published:
	TTreeView *TreeView1;
	TStringGrid *StringGrid1;
	TLabel *Label1;
	TEdit *Edit1;
	TLabel *Label2;
	TEdit *Edit2;
	TMemo *Memo1;
	TButton *Button1;
	TButton *Button2;
	TButton *Button3;
	TButton *Button5;
	TButton *Button6;
	TButton *Button7;
	TButton *Button4;
	TButton *Button8;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall Button7Click(TObject *Sender);
	void __fastcall Button8Click(TObject *Sender);
private:
public:	
	__fastcall TForm1(TComponent* Owner);
};
extern PACKAGE TForm1 *Form1;

#endif
