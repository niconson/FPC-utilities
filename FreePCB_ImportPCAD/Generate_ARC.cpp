//---------------------------------------------------------------------------


#pragma hdrstop

#include "Generate_ARC.h"
#include "HEAD.h"
#include "math.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)


float ang (double dx_, double dy_)
        {
        double ANG_s;
        if (dx_ == 0)
                {
                if (dy_ > 0) ANG_s = 90;
                else ANG_s = 270;
                }
        else
                {
                double Dxy = dy_/dx_;
                ANG_s = (atan(Dxy))*573/10;
                if ((dx_ > 0)&&(dy_ < 0)) ANG_s = 360 + ANG_s;
                if (dx_ < 0) ANG_s = 180 + ANG_s;
                }
        return ANG_s;
}

long Generate_ARC(      double X,
                        double Y,
                        double X2,
                        double Y2,
                        double x0, //center ARC
                        double y0, //center ARC
                        double *OutPut)
{
long lines = 0;
while (lines < 298) // ����� ����������� ������� �� ��������� !!!
        {
        *(OutPut + lines) = 0;      //������� ������
        lines++;
        }
lines = 0;
double dx;
double dy;
double angL;
double ang_end;
double rad;
double len;
ang_end = ang((X2-x0),(Y2-y0)) ;
angL = ang((X-x0),(Y-y0)) ;
int CountVTX;
if (ang_end > angL)     CountVTX = (ang_end - angL)/IncrementArc;
else if (ang_end < angL)CountVTX = (ang_end - angL + 360)/IncrementArc;
if (ang_end == angL)    CountVTX = 360/IncrementArc;
*(OutPut + lines) = X;
lines++;
*(OutPut + lines) = Y;
lines++;
X = X - x0;
Y = Y - y0;
while (CountVTX>0)
        {
        Rotate_Vertex (&X, &Y, IncrementArc);
        X = X + x0;
        Y = Y + y0;
        *(OutPut + lines) = X;
        lines++;
        *(OutPut + lines) = Y;
        lines++;
        CountVTX--;
        X = X - x0;
        Y = Y - y0;
        }
*(OutPut + lines) = X2;
lines++;
*(OutPut + lines) = Y2;
lines++;
return lines;
}