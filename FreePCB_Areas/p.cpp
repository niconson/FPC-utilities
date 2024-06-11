//---------------------------------------------------------------------------


#pragma hdrstop

#include "p.h"
#include "Debug_Areas.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)


float p(void)
        {
        float P = 0;
        for (int q=0; q<CntLnsArea; q++)
                {
                P += Length_Line(LinesArea[q].X1,LinesArea[q].Y1,LinesArea[q].X2,LinesArea[q].Y2);
                }
        return P;
        }
