#include "triangle.h"

void Triangle ::Set(int x1, int y1, int a)
{
	this->x1 = points[0].x = x1;
	this->y1 = points[0].y = y1;
	this->x2 = points[1].x = x1 + a;
	this->y2 = points[1].y = y1;
	this->x3 = points[2].x = x1 + a / 2;
	this->y3 = points[2].y = round(y1 - (a / 2) * sqrt(3));
}
void Triangle ::Draw(TCanvas *Canvas)
{
	Canvas->Pen->Color = clRed;
	Canvas->Pen->Width = 3;
	Canvas->Polygon(points, 2);
}
void Triangle ::Hide(TCanvas *Canvas)
{
	Canvas->Pen->Color = clWhite;
	Canvas->Pen->Width = 3;
	Canvas->Polygon(points, 2);
}
int Triangle ::Square()
{
	side = points[1].x - points[0].x;
	return round(pow(side, 2) * sqrt(3) / 4);
}
int Triangle ::Perimetr()
{
	return 3 * side;
}
void Triangle ::MassCenter()
{
	massx = round((points[0].x + points[1].x + points[2].x) / 3);
	massy = round((points[0].y + points[1].y + points[2].y) / 3);
}
void Triangle ::Move(TCanvas *Canvas, int dir)
{
	Hide(Canvas);
	switch (dir)
	{
	case 65:
		x1 -= 10;
		x2 -= 10;
		x3 -= 10;
		points[0].x -= 10;
		points[1].x -= 10;
		points[2].x -= 10;
		break;
	case 87:
		y1 -= 10;
		y2 -= 10;
		y3 -= 10;
		points[0].y -= 10;
		points[1].y -= 10;
		points[2].y -= 10;
		break;
	case 68:
		x1 += 10;
		x2 += 10;
		x3 += 10;
		points[0].x += 10;
		points[1].x += 10;
		points[2].x += 10;
		break;
	case 83:
		y1 += 10;
		y2 += 10;
		y3 += 10;
		points[0].y += 10;
		points[1].y += 10;
		points[2].y += 10;
		break;
	}
}
void Triangle ::Resize(TCanvas *Canvas, int a)
{
	Hide(Canvas);
	if (a == 1)
	{
		x1 -= 10;
		x2 += 10;
		y1 += 10;
		y2 += 10;
		y3 -= 10;
		points[0].x -= 10;
		points[0].y += 10;
		points[1].x += 10;
		points[1].y += 10;
		points[2].y -= 10;
	}
	else
	{
		x1 += 10;
		x2 -= 10;
		y1 -= 10;
		y2 -= 10;
		y3 += 10;
		points[0].x += 10;
		points[0].y -= 10;
		points[1].x -= 10;
		points[1].y -= 10;
		points[2].y += 10;
	}
}
void Triangle ::DxDy(int x, int y)
{
	MassCenter();
	dx = (x - massx) / 10;
	dy = (y - massy) / 10;
}
void Triangle ::MoveMC(TCanvas *Canvas, int x, int y)
{
	Hide(Canvas);
	if (abs(x - massx) > 1)
	{
		points[0].x += dx;
		points[1].x += dx;
		points[2].x += dx;
		massx += dx;
	}
	if (abs(y - massy) > 1)
	{
		points[0].y += dy;
		points[1].y += dy;
		points[2].y += dy;
		massy += dy;
	}
}
void Triangle ::Rotate(TCanvas *Canvas, double a)
{
	HideRotate(Canvas);
	if (angle <= a)
	{
		new_x1 = x1;
		new_y1 = y1;

		new_x2 = (x2 - x1) * cos(angle) + (y2 - y1) * sin(angle) + x1;
		new_y2 = -(x2 - x1) * sin(angle) + (y2 - y1) * cos(angle) + y1;

		new_x3 = (x3 - x1) * cos(angle) + (y3 - y1) * sin(angle) + x1;
		new_y3 = -(x3 - x1) * sin(angle) + (y3 - y1) * cos(angle) + y1;
		angle += M_PI / 180;
	}
	Show(Canvas);
}
void Triangle ::Show(TCanvas *Canvas)
{
	Canvas->Pen->Color = clRed;
	Canvas->Pen->Width = 3;
	points[0] = Point(new_x1, new_y1);
	points[1] = Point(new_x2, new_y2);
	points[2] = Point(new_x3, new_y3);
	Canvas->Polygon(points, 2);
}
void Triangle ::HideRotate(TCanvas *Canvas)
{
	Canvas->Pen->Color = clWhite;
	Canvas->Pen->Width = 3;
	points[0] = Point(new_x1, new_y1);
	points[1] = Point(new_x2, new_y2);
	points[2] = Point(new_x3, new_y3);
	Canvas->Polygon(points, 2);
}
