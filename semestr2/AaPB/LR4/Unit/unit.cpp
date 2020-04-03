#include <vcl.h>
#include <cmath>
#include "unit.h"
#include "stacknum.h"
#include "stackop.h"

TForm1 *Form1;
StackNum *stkNum = new StackNum();
StackOp *stkOp = new StackOp();
float nums[5];

bool is_space(char c)
{
	return c == ' ';
}

bool is_op(char c)
{
	return c == '+' || c == '-' || c == '*' || c == '/';
}

int priority(char c)
{
	if(c == '+' || c == '-') return 1;
	else if(c == '*' || c == '/')return 2;
	else return 0;
}

void Step(char c)
{
	float a = stkNum->Delete();
	float b = stkNum->Delete();
	switch(c)
	{
		case '+': stkNum->Add(b + a); break;
		case '-': stkNum->Add(b - a); break;
		case '*': stkNum->Add(b * a); break;
		case '/': stkNum->Add(b / a); break;
	}
}

float calc(float a, char c, float b)
{
	switch(c)
	{
		case '+': return a + b;
		case '-': return a - b;
		case '*': return a * b;
		case '/': return a / b;
    }
}

float check(char c)
{
	switch(c)
	{
		case 'a': return nums[0];
		case 'b': return nums[1];
		case 'c': return nums[2];
		case 'd': return nums[3];
		case 'e': return nums[4];
    }
}
__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner)
{for(int i = 1; i <= 15 ; i++) ComboBox1->Items->Add(i);}
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	try
	{
		nums[0] = StrToFloat(Edit1->Text);
		nums[1] = StrToFloat(Edit2->Text);
		nums[2] = StrToFloat(Edit3->Text);
		nums[3] = StrToFloat(Edit4->Text);
		nums[4] = StrToFloat(Edit5->Text);
		AnsiString temp = Edit7->Text;
		std::string node = temp.c_str();

		int j = 0;
		for(int i = 0; node[i] != '\0'; i++)
		{
			if(!is_space(node[i])) if(node[i] == '(') stkOp->Add('(');

			else if(node[i] == ')')
			{
				while(stkOp->GetBack() != '(') Step(stkOp->GetBack()), stkOp->Delete();
				stkOp->Delete();
			}

			else if(is_op(node[i]))
			{
			   char c = node[i];
			   while(stkOp->size != 0 && priority(stkOp->GetBack()) >= priority(node[i])) Step(stkOp->GetBack()), stkOp->Delete();
			   stkOp->Add(c);
			}

			else stkNum->Add(nums[j++]);
		}

		while(stkOp->size != 0) Step(stkOp->GetBack()), stkOp->Delete();
		Edit6->Text = FloatToStr(round(stkNum->GetBack() * 1000) / 1000);
	}
	catch(...)
	{
		ShowMessage("������� ���������� ������!");
		Edit1->Text = "";
		Edit2->Text = "";
		Edit3->Text = "";
		Edit4->Text = "";
		Edit5->Text = "";
		Edit7->Text = "";
	}
}
void __fastcall TForm1::ComboBox1Select(TObject *Sender)
{
	switch(ComboBox1->ItemIndex + 1)
	{
	case 1:
		Edit1->Text = "8,6";
		Edit2->Text = "2,4";
		Edit3->Text = "5,1";
		Edit4->Text = "0,3";
		Edit5->Text = "7,9";
		Edit7->Text = "a/(b-c)*(d+e)";
	break;
	case 2:
		Edit1->Text = "7,4";
		Edit2->Text = "3,6";
		Edit3->Text = "2,8";
		Edit4->Text = "9,5";
		Edit5->Text = "0,9";
		Edit7->Text = "(a+b)*(c-d)/e";
	break;
	case 3:
		Edit1->Text = "3,1";
		Edit2->Text = "5,4";
		Edit3->Text = "0,2";
		Edit4->Text = "9,6";
		Edit5->Text = "7,8";
		Edit7->Text = "a-(b+c*d)/e";
	break;
	case 4:
		Edit1->Text = "1,2";
		Edit2->Text = "0,7";
		Edit3->Text = "9,3";
		Edit4->Text = "6,5";
		Edit5->Text = "8,4";
		Edit7->Text = "a/b-((c+d)*e)";
	break;
	case 5:
		Edit1->Text = "9,7";
		Edit2->Text = "8,2";
		Edit3->Text = "3,6";
		Edit4->Text = "4,1";
		Edit5->Text = "0,5";
		Edit7->Text = "a*(b-c+d)/e";
	break;
	case 6:
		Edit1->Text = "0,8";
		Edit2->Text = "4,1";
		Edit3->Text = "7,9";
		Edit4->Text = "6,2";
		Edit5->Text = "3,5";
		Edit7->Text = "(a+b)*(c-d)/e";
	break;
	case 7:
		Edit1->Text = "1,6";
		Edit2->Text = "4,9";
		Edit3->Text = "5,7";
		Edit4->Text = "0,8";
		Edit5->Text = "2,3";
		Edit7->Text = "a*(b-c)/(d+e)";
	break;
	case 8:
		Edit1->Text = "8,5";
		Edit2->Text = "0,3";
		Edit3->Text = "2,4";
		Edit4->Text = "7,9";
		Edit5->Text = "1,6";
		Edit7->Text = "a/(b*(c+d))-e";
	break;
	case 9:
		Edit1->Text = "5,6";
		Edit2->Text = "7,4";
		Edit3->Text = "8,9";
		Edit4->Text = "3,1";
		Edit5->Text = "0,2";
		Edit7->Text = "(a+(b/c-d))*e";
	break;
	case 10:
		Edit1->Text = "0,4";
		Edit2->Text = "2,3";
		Edit3->Text = "6,7";
		Edit4->Text = "5,8";
		Edit5->Text = "9,1";
		Edit7->Text = "a*(b+c)/(d-e)";
	break;
	case 11:
		Edit1->Text = "5,6";
		Edit2->Text = "3,2";
		Edit3->Text = "0,9";
		Edit4->Text = "1,7";
		Edit5->Text = "4,8";
		Edit7->Text = "a-(b/c*(d+e))";
	break;
	case 12:
		Edit1->Text = "0,3";
		Edit2->Text = "6,7";
		Edit3->Text = "8,4";
		Edit4->Text = "9,5";
		Edit5->Text = "1,2";
		Edit7->Text = "(a-b)/(c+d)*e";
	break;
	case 13:
		Edit1->Text = "7,6";
		Edit2->Text = "4,8";
		Edit3->Text = "3,5";
		Edit4->Text = "9,1";
		Edit5->Text = "0,2";
		Edit7->Text = "a/(b+c-d*e)";
	break;
	case 14:
		Edit1->Text = "0,5";
		Edit2->Text = "6,1";
		Edit3->Text = "8,9";
		Edit4->Text = "9,5";
		Edit5->Text = "0,2";
		Edit7->Text = "a*(b-c)/(d+e)";
	break;
	case 15:
		Edit1->Text = "9,1";
		Edit2->Text = "0,6";
		Edit3->Text = "2,4";
		Edit4->Text = "3,7";
		Edit5->Text = "8,5";
		Edit7->Text = "(a+b*c)/(d-e)";
	break;
	}
}
