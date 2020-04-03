#include "polygon.h"

#ifndef rectangleH
#define rectangleH

class Rectangle : public Polygon
{
public:
	TPoint points[4];
	int x1, y1, x2, y2, new_x1, new_x2, new_x3, new_x4, new_y1, new_y2, new_y3, new_y4, dx, dy, massx, massy;
	double angle = 0;
	virtual void Set(int x1, int y1, int x2, int y2);
	virtual void Draw(TCanvas *Canvas);
	void Show(TCanvas *Canvas);
	virtual int Square();
	virtual int Perimetr();
	virtual void MassCenter();
	virtual void Hide(TCanvas *Canvas);
	void Move(TCanvas *Canvas, int dir);
	void Resize(TCanvas *Canvas, int a);
	void MoveMC(TCanvas *Canvas, int x, int y);
	void DxDy(int x, int y);
	void SetCord();
	void Rotate(TCanvas *Canvas, double ang);
	void HideRotate(TCanvas *Canvas);
};

#endif
