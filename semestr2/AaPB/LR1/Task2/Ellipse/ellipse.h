#include "polygon.h"

#ifndef ellipseH
#define ellipseH

class Ellipse : public Polygon
{
public:
	int a, b, x1, y1, x2, y2, massx, massy, dx, dy;
	void Set(int x1, int y1, int x2, int y2);
	void Draw(TCanvas *Canvas);
	void MassCenter();
	int Square();
	int Perimetr();
	void Hide(TCanvas *Canvas);
	void Move(TCanvas *Canvas, int dir);
	void Resize(TCanvas *Canvas, int a);
	void DxDy(int x, int y);
	void MoveMC(TCanvas *Canvas, int x, int y);
};

#endif
