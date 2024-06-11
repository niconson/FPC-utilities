//---------------------------------------------------------------------------


#pragma hdrstop

#include "Angle.h"
#include "To_DXF.h"
#include "math.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)



float Angle (float dx, float dy, float x0, float y0)
        {
        float ANG_s;
        dx = dx - x0;
        dy = dy - y0;
        if (ABS(dx) < BY_ZERO)
                {
                if (dy > 0)     ANG_s = 90;
                else if (dy < 0)ANG_s = 270;
                else            return 0;
                }
        else
                {
                float Dxy = dy/dx;
                ANG_s = (atan(Dxy))*(float)180/(float)M_PI;
                if ((dx > 0)&&(dy < 0)) ANG_s = 360 + ANG_s;
                if (dx < 0) ANG_s = 180 + ANG_s;
                }
        return ANG_s;
        }