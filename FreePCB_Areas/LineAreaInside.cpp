//---------------------------------------------------------------------------


#pragma hdrstop

#include "LineAreaInside.h"
#include "Debug_Areas.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)


double LineAreaInside (double X, double Y, double X2, double Y2)
{
double MinDistance = DEFAULT;
double PX = 0;
double PY = 0;
for (int Cnt=0; Cnt<CntLnsArea; Cnt++)
        {
        if      (MIN(LinesArea[Cnt].X1,LinesArea[Cnt].X2) > (MAX(X,X2) + MinDistance))    {;}
        else if (MAX(LinesArea[Cnt].X1,LinesArea[Cnt].X2) < (MIN(X,X2) - MinDistance))    {;}
        else if (MIN(LinesArea[Cnt].Y1,LinesArea[Cnt].Y2) > (MAX(Y,Y2) + MinDistance))    {;}
        else if (MAX(LinesArea[Cnt].Y1,LinesArea[Cnt].Y2) < (MIN(Y,Y2) - MinDistance))    {;}
        else    {
                double D = Distance(   LinesArea[Cnt].X1,
                                LinesArea[Cnt].Y1,
                                LinesArea[Cnt].X2,
                                LinesArea[Cnt].Y2,
                                X,Y,X2,Y2,&PX, &PY) ;
                if (D < BY_ZERO)return 0;
                if (D < MinDistance) MinDistance = D;
                }
        }
return MinDistance;
}