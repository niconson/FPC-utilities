//---------------------------------------------------------------------------


#pragma hdrstop

#include "LinesCutToCornersConverter.h"
#include "Debug_Areas.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)


int LinesCutToCornersConverter (void)
        {
        int CCComb = 0;
        for (int n=LinesCut[CountLinesCut-1].First; n<CountLinesCut; n++)
                {
                Corners[CCComb].X = LinesCut[n].X1;
                Corners[CCComb].Y = LinesCut[n].Y1;
                Corners[CCComb].Flag = false;
                CCComb++;
                }
        Corners[CCComb-1].Flag = true;
        for (int n=0; n<LinesCut[CountLinesCut-1].First; n++)
                {
                Corners[CCComb].X = LinesCut[n].X1;
                Corners[CCComb].Y = LinesCut[n].Y1;
                if (LinesCut[n+1].First != LinesCut[n].First) Corners[CCComb].Flag = true;
                else                                          Corners[CCComb].Flag = false;
                CCComb++;
                }
        CCComb = CountLinesCut;
        return CCComb;
        }