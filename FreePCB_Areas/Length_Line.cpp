//---------------------------------------------------------------------------


#pragma hdrstop

#include "Length_Line.h"
#include "Debug_Areas.h"
#include "math.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
//double BETWEEN = 30000;
//------------------------------------------
//        ����� ��������
//------------------------------------------
double Length_Line (double X1, double Y1, double X2, double Y2)
        {
        double dx = X2 - X1;
        double dy = Y2 - Y1;
        /*bool Flag = false;
        if ( ABS(dx) > BETWEEN || ABS(dy) > BETWEEN )
                {
                Flag = true;
                dx = dx/BETWEEN;
                dy = dy/BETWEEN;
                } */
        double len;
        if (ABS(dx) > BY_ZERO && ABS(dy) > BY_ZERO)
                {
                len = pow(dx, 2) + pow(dy, 2);
                len = sqrt(len);
                }
        else    len = ABS(dx) + ABS(dy);
        //if (Flag)       len = len*BETWEEN;
        return len;
        }