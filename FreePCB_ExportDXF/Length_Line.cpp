//---------------------------------------------------------------------------


#pragma hdrstop

#include "Length_Line.h"
#include "To_DXF.h"
#include "math.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

int BETWEEN = 30000;
//------------------------------------------
//        длина сегмента
//------------------------------------------
float Length_Line (float X1, float Y1, float X2, float Y2, float Z1, float Z2)
        {
        float dx = X2 - X1;
        float dy = Y2 - Y1;
        float dz = Z2 - Z1;
        bool Flag = false;
        if ( ABS(dx) > BETWEEN || ABS(dy) > BETWEEN || ABS(dz) > BETWEEN )
                {
                Flag = true;
                dx = dx/BETWEEN;
                dy = dy/BETWEEN;
                dz = dz/BETWEEN;
                }
        double len;
        if (ABS(dx) > BY_ZERO || ABS(dy) > BY_ZERO || ABS(dz) > BY_ZERO)
                {
                len = pow(dx, 2) + pow(dy, 2) + pow(dz, 2);
                len = sqrt(len);
                }
        else    len = ABS(dx) + ABS(dy) + ABS(dz);
        if (Flag)
                len = len*BETWEEN;
        return len;
        }