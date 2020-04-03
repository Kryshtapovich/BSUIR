#include "polygon.h"

#ifndef trinagleH
#define trinagleH

class Triangle : public Polygon
{
public:
	TPoint points[3];
	int x1, y1, x2, y2, x3, y3, side, massx, massy, dx, dy, new_x1, new_y1, new_x2, new_y2, new_x3, new_y3;
	double angle = 0;
	void Set(int x1, int y1, int a);
	void Draw(TCanvas *Canvas);
	void Hide(TCanvas *Canvas);
	void Move(TCanvas *Canvas, int dir);
	void Resize(TCanvas *Canvas, int a);
	int Square();
	int Perimetr();
	void MassCenter();
	void DxDy(int x, int y);
	void MoveMC(TCanvas *Canvas, int x, int y);
	void Rotate(TCanvas *Canvas, double a);
	void Show(TCanvas *Canvas);
	void HideRotate(TCanvas *Canvas);
};

#endif
