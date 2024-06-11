//---------------------------------------------------------------------------


#pragma hdrstop

#include "PointAreaInside.h"
#include "Debug_Areas.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)







//---------- PointAreaInside
//---------- Distance минимальное расстояние от точки до стороны полигона
//---------- extern float LinesArea[0][Cnt]
int PointAreaInside (double X, double Y, MLine * Area, int ncorners)
{
double st_angle =   Angle(Area[0].X1, Area[0].Y1, X, Y);
double back_angle = st_angle;
double diff_angle;
double angle,px,py,d;
double SUM = 0;
for (int q=0; q<ncorners; q++)
        {
        d = Distance(   Area[q].X1, Area[q].Y1,
                        Area[q].X2, Area[q].Y2,
                        X,Y,X,Y,&px,&py);
        if (d < BY_ZERO) return 2;
        angle = Angle(Area[q].X1, Area[q].Y1, X, Y);
        diff_angle = angle - back_angle;
        if      (diff_angle < -180.0) diff_angle += 360.0;
        else if (diff_angle > 180.0)  diff_angle -= 360.0;
        SUM += diff_angle;
        back_angle = angle;
        }
diff_angle = st_angle - back_angle;
if      (diff_angle < -180.0) diff_angle += 360.0;
else if (diff_angle > 180.0)  diff_angle -= 360.0;
SUM += diff_angle;
if      (SUM < -180)    return dir___CW;
else if (SUM > 180)     return dir___CCW;
return 0;
}
