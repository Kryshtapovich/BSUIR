#include "rectangle.h"

void Rectangle ::Set(int x1, int y1, int x2, int y2)
{
	this->x1 = points[0].x = x1;
	this->y1 = points[0].y = y1;
	points[1].x = x1;
	points[1].y = y2;
	this->x2 = points[2].x = x2;
	this->y2 = points[2].y = y2;
	points[3].x = x2;
	points[3].y = y1;
}
void Rectangle ::Draw(TCanvas *Canvas)
{
	Canvas->Pen->Color = clRed;
	Canvas->Pen->Width = 3;
	Canvas->Polygon(points, 3);
}
void Rectangle ::Hide(TCanvas *Canvas)
{
	Canvas->Pen->Color = clWhite;
	Canvas->Pen->Width = 3;
	Canvas->Polygon(points, 3);
}
int Rectangle ::Square()
{
	return abs(points[2].x - points[0].x) * abs(points[2].y - points[0].y);
}
int Rectangle ::Perimetr()
{
	return 2 * (abs(points[2].x - points[0].x) + abs(points[2].y - points[0].y));
}
void Rectangle ::MassCenter()
{
	massx = points[0].x + (points[2].x - points[0].x) / 2;
	massy = points[0].y + (points[2].y - points[0].y) / 2;
}
void Rectangle ::Move(TCanvas *Canvas, int dir)
{
	Hide(Canvas);
	switch (dir)
	{
	case 65:
		x1 -= 10;
		x2 -= 10;
		points[0].x -= 10;
		points[1].x -= 10;
		points[2].x -= 10;
		points[3].x -= 10;
		break;
	case 87:
		y1 -= 10;
		y2 -= 10;
		points[0].y -= 10;
		points[1].y -= 10;
		points[2].y -= 10;
		points[3].y -= 10;
		break;
	case 68:
		x1 += 10;
		x2 += 10;
		points[0].x += 10;
		points[1].x += 10;
		points[2].x += 10;
		points[3].x += 10;
		break;
	case 83:
		y1 += 10;
		y2 += 10;
		points[0].y += 10;
		points[1].y += 10;
		points[2].y += 10;
		points[3].y += 10;
		break;
	}
}
void Rectangle ::Resize(TCanvas *Canvas, int a)
{
	Hide(Canvas);
	if (a == 0)
	{
		x1 += 10;
		x2 -= 10;
		y1 += 10;
		y2 -= 10;
		points[0].x += 10;
		points[0].y += 10;
		points[1].x += 10;
		points[1].y -= 10;
		points[2].x -= 10;
		points[2].y -= 10;
		points[3].x -= 10;
		points[3].y += 10;
	}
	else
	{
		x1 -= 10;
		x2 += 10;
		y1 -= 10;
		y2 += 10;
		points[0].x -= 10;
		points[0].y -= 10;
		points[1].x -= 10;
		points[1].y += 10;
		points[2].x += 10;
		points[2].y += 10;
		points[3].x += 10;
		points[3].y -= 10;
	}
}
void Rectangle ::MoveMC(TCanvas *Canvas, int x, int y)
{
	Hide(Canvas);
	if (massx != x)
	{
		points[0].x += dx;
		points[1].x += dx;
		points[2].x += dx;
		points[3].x += dx;
		massx += dx;
	}
	if (massy != y)
	{
		points[0].y += dy;
		points[1].y += dy;
		points[2].y += dy;
		points[3].y += dy;
		massy += dy;
	}
}
void Rectangle ::DxDy(int x, int y)
{
	MassCenter();
	dx = (x - massx) / 10;
	dy = (y - massy) / 10;
}
void Rectangle ::Rotate(TCanvas *Canvas, double ang)
{
	HideRotate(Canvas);
	if (angle <= ang)
	{
		new_x1 = (x1 - x1) * cos(angle) + (y1 - y2) * sin(angle) + x1;
		new_y1 = -(x1 - x1) * sin(angle) + (y1 - y2) * cos(angle) + y2;

		new_x2 = x1;
		new_y2 = y2;

		new_x3 = (x2 - x1) * cos(angle) + (y2 - y2) * sin(angle) + x1;
		new_y3 = -(x2 - x1) * sin(angle) + (y2 - y2) * cos(angle) + y2;

		new_x4 = (x2 - x1) * cos(angle) + (y1 - y2) * sin(angle) + x1;
		new_y4 = -(x2 - x1) * sin(angle) + (y1 - y2) * cos(angle) + y2;
		angle += M_PI / 180;
	}
	Show(Canvas);
}
void Rectangle ::Show(TCanvas *Canvas)
{
	Canvas->Pen->Color = clRed;
	Canvas->Pen->Width = 3;
	points[0] = Point(new_x1, new_y1);
	points[1] = Point(new_x2, new_y2);
	points[2] = Point(new_x3, new_y3);
	points[3] = Point(new_x4, new_y4);
	Canvas->Polygon(points, 3);
}
void Rectangle::HideRotate(TCanvas *Canvas)
{
	Canvas->Pen->Color = clWhite;
	Canvas->Pen->Width = 3;
	points[0] = Point(new_x1, new_y1);
	points[1] = Point(new_x2, new_y2);
	points[2] = Point(new_x3, new_y3);
	points[3] = Point(new_x4, new_y4);
	Canvas->Polygon(points, 3);
}
