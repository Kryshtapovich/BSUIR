#include <vcl.h>
#include "Rectangle.h"

#ifndef circleH
#define circleH

class Circle : public Rectangle {
public:
   Circle(int x1, int y1, int x2, int y2);
   void Show(TCanvas *Canvas, TColor C);
   void Move(TCanvas *Canvas);
   void MoveX(TCanvas *Canvas, TColor C);
   void MoveDown(TCanvas *Canvas, TColor C);
};
#endif
