//---------------------------------------------------------------------------


#pragma hdrstop

#include "Length_Line.h"
#include "FPC_to_PCB.h"
#include "math.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

//------------------------------------------
//        ����� ��������
//------------------------------------------
double Length_Line (double X1, double Y1, double X2, double Y2)
        {
        double dx = X2 - X1;
        double dy = Y2 - Y1;
        bool Flag = false;
        if ( ABS(dx) > 30000 ) Flag = true;
        if ( ABS(dy) > 30000 ) Flag = true;
        if (Flag) dx = dx/(double)100000;
        if (Flag) dy = dy/(double)100000;
        double len = pow(dx, 2) + pow(dy, 2);
        len = sqrt(len);
        if (Flag) len = len*(double)100000;
        return len;
        }