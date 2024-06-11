//---------------------------------------------------------------------------


#pragma hdrstop

#include "PointBoardInside.h"
#include "Debug_Areas.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)



bool PointBoardInside (double X, double Y)
        {
        int count_inside = 0;
        for (int b=0; b<Dtlines; b++)
                {
                if (DataLines[b].Board >= 0)
                        {
                        double st_angle =   Angle(DataLines[b].X, DataLines[b].Y, X, Y);
                        double back_angle = st_angle;
                        double diff_angle;
                        double angle;
                        double SUM = 0;
                        int nb=b;
                        while (DataLines[nb].Board == DataLines[b].Board)
                                {
                                angle = Angle(DataLines[nb].X, DataLines[nb].Y, X, Y);
                                diff_angle = angle - back_angle;
                                if      (diff_angle < -180.0) diff_angle += 360.0;
                                else if (diff_angle > 180.0)  diff_angle -= 360.0;
                                SUM += diff_angle;
                                back_angle = angle;
                                nb++;
                                }
                        diff_angle = st_angle - back_angle;
                        if      (diff_angle < -180.0) diff_angle += 360.0;
                        else if (diff_angle > 180.0)  diff_angle -= 360.0;
                        SUM += diff_angle;
                        if      (ABS(SUM) > 180) count_inside++;
                        b = nb-1;
                        }
                }
        if (count_inside%2) return true;
        else return false;
        }
