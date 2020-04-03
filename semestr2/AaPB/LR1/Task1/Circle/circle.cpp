#include "circle.h"
#include "Rectangle.h"

Circle::Circle(int x1, int y1, int x2, int y2) : Rectangle(x1, y1, x2, y2)
{
}
void Circle::Show(TCanvas *Canvas, TColor C)
{
   Canvas->Brush->Color = C;
   Canvas->Pen->Color = C;
   Canvas->Ellipse(x1, y1, x2, y2);
}
void Circle::Move(TCanvas *Canvas)
{
   Rectangle::Move(Canvas);
}
void Circle::MoveX(TCanvas *Canvas, TColor C)
{
   Rectangle::MoveX(Canvas, C);
}
void Circle::MoveDown(TCanvas *Canvas, TColor C)
{
   y1 += 10;
   y2 += 10;
   Show(Canvas, C);
}
