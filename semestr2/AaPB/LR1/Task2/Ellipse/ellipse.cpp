#include "ellipse.h"

void Ellipse ::Set(int x1, int y1, int x2, int y2)
{
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;
}
void Ellipse ::Draw(TCanvas *Canvas)
{
	Canvas->Pen->Color = clRed;
	Canvas->Pen->Width = 3;
	Canvas->Ellipse(x1, y1, x2, y2);
}
void Ellipse ::Hide(TCanvas *Canvas)
{
	Canvas->Pen->Color = clWhite;
	Canvas->Pen->Width = 3;
	Canvas->Ellipse(x1, y1, x2, y2);
}
void Ellipse ::Move(TCanvas *Canvas, int dir)
{
	Hide(Canvas);
	switch (dir)
	{
	case 65:
		x1 -= 10;
		x2 -= 10;
		break;
	case 87:
		y1 -= 10;
		y2 -= 10;
		break;
	case 68:
		x1 += 10;
		x2 += 10;
		break;
	case 83:
		y1 += 10;
		y2 += 10;
		break;
	}
}
void Ellipse ::MassCenter()
{
	a = (x2 - x1) / 2;
	b = (y2 - y1) / 2;
	massx = x1 + a;
	massy = y1 + b;
}
int Ellipse ::Square()
{
	return round(a * b * M_PI);
}
int Ellipse ::Perimetr()
{
	if (a > 0 && b > 0)
		return round(4 * (M_PI * a * b + pow(a - b, 2)) / (a + b));
	else
		return 0;
}
void Ellipse ::Resize(TCanvas *Canvas, int a)
{
	Hide(Canvas);
	if (a == 0)
	{
		x1 += 10;
		y1 += 10;
		x2 -= 10;
		y2 -= 10;
	}
	else
	{
		x1 -= 10;
		y1 -= 10;
		x2 += 10;
		y2 += 10;
	}
}
void Ellipse ::DxDy(int x, int y)
{
	MassCenter();
	dx = (x - massx) / 10;
	dy = (y - massy) / 10;
}
void Ellipse ::MoveMC(TCanvas *Canvas, int x, int y)
{
	Hide(Canvas);
	if (massx != x)
	{
		x1 += dx;
		x2 += dx;
		massx += dx;
	}
	if (massy != y)
	{
		y1 += dy;
		y2 += dy;
		massy += dy;
	}
}
