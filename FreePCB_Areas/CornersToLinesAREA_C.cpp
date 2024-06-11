//---------------------------------------------------------------------------


#pragma hdrstop

#include "CornersToLinesAREA_C.h"
#include "Debug_Areas.h"
#include "fstream.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)


void CornersToLinesAREA_C (int start_index)
        {
       /*bool FLAG = false;
        bool ENABLE = true;
        CountLinesCut = start_index;
        int frst = CountLinesCut;
        int a_st = 0;
        if (LinesArea)
                delete[] LinesArea;
        try     {
                LinesArea = new(std::nothrow) MLine[CCComb];}
        catch(std::bad_alloc)
                {
                ShowMessage("    Ошибка выделения памяти: Line[" + AnsiString(CCComb) + "]!" );
                }
        AreaRect.Left =        DEFAULT;
        AreaRect.Bottom =      DEFAULT;
        AreaRect.Right =      -DEFAULT;
        AreaRect.Top =        -DEFAULT;
        for (int a=0; a<CCComb; a++)
                {
                if (Corners[a].Flag)
                        {
                        a_st = a+1;
                        if (FLAG == 0) CntLnsArea = a+1;
                        FLAG = true;
                        frst = CountLinesCut;
                        LinesCut[frst].Bounds =   DEFAULT;
                        LinesCut[frst+1].Bounds = -DEFAULT;
                        if (a == (CCComb-1))break;
                        if (PointAreaInside(Corners[a+1].X, Corners[a+1].Y, LinesArea, CntLnsArea)) ENABLE = true;
                        else  ENABLE = false;
                        continue;
                        }
                if (a == (CCComb-1))break;
                if (FLAG == 0)
                        {
                        if (Corners[a].Flag == 0)
                                {
                                LinesArea[a].X1 = Corners[a].X;
                                LinesArea[a].Y1 = Corners[a].Y;
                                LinesArea[a].X2 = Corners[a+1].X;
                                LinesArea[a].Y2 = Corners[a+1].Y;
                                }
                        if (Corners[a+1].Flag)
                                {
                                LinesArea[a+1].X1 = Corners[a+1].X;
                                LinesArea[a+1].Y1 = Corners[a+1].Y;
                                LinesArea[a+1].X2 = Corners[0].X;
                                LinesArea[a+1].Y2 = Corners[0].Y;
                                }
                        if (Corners[a].X < AreaRect.Left)   AreaRect.Left =   Corners[a].X;
                        if (Corners[a].X > AreaRect.Right)  AreaRect.Right =  Corners[a].X;
                        if (Corners[a].Y < AreaRect.Bottom) AreaRect.Bottom = Corners[a].Y;
                        if (Corners[a].Y > AreaRect.Top)    AreaRect.Top =    Corners[a].Y;
                        }
                else if (ENABLE)
                        {
                        if (Corners[a].Flag == 0)
                                {
                                LinesCut[CountLinesCut].X1 = Corners[a].X;
                                LinesCut[CountLinesCut].Y1 = Corners[a].Y;
                                LinesCut[CountLinesCut].X2 = Corners[a+1].X;
                                LinesCut[CountLinesCut].Y2 = Corners[a+1].Y;
                                LinesCut[CountLinesCut].First = frst;
                                LinesCut[CountLinesCut].n_board = -1;
                                LinesCut[CountLinesCut].FlagDelete = 0;
                                LinesCut[CountLinesCut].FlagWrite = 0;
                                LinesCut[CountLinesCut].Arc = 0;
                                CountLinesCut++;
                                LinesCut[frst].Bounds =   MIN(Corners[a].X,LinesCut[frst].Bounds);
                                LinesCut[frst+1].Bounds = MAX(Corners[a].X,LinesCut[frst+1].Bounds);
                                }
                        if (Corners[a+1].Flag)
                                {
                                LinesCut[CountLinesCut].X1 = Corners[a+1].X;
                                LinesCut[CountLinesCut].Y1 = Corners[a+1].Y;
                                LinesCut[CountLinesCut].X2 = Corners[a_st].X;
                                LinesCut[CountLinesCut].Y2 = Corners[a_st].Y;
                                LinesCut[CountLinesCut].First = frst;
                                LinesCut[CountLinesCut].n_board = -1;
                                LinesCut[CountLinesCut].FlagDelete = 0;
                                LinesCut[CountLinesCut].FlagWrite = 0;
                                LinesCut[CountLinesCut].Arc = 0;
                                CountLinesCut++;
                                LinesCut[frst].Bounds =   MIN(Corners[a].X,LinesCut[frst].Bounds);
                                LinesCut[frst+1].Bounds = MAX(Corners[a].X,LinesCut[frst+1].Bounds);
                                }
                        }
                }
        LinesCut[CountLinesCut].First = CountLinesCut; */
        }