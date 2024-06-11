//---------------------------------------------------------------------------


#pragma hdrstop

#include "SetDirection.h"
#include "Debug_Areas.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)


void SetDirection ( MLine * LINES, int nlines, int direct )
        {
        int dir = 0;
        bool bChange = false;
        for (int q=0; q<nlines; q++)
                {
                dir = PointAreaInside(LINES[q].X1+_104,LINES[q].Y1+_103, LINES, nlines);
                if (dir != dir___CW && dir != dir___CCW)
                        dir = PointAreaInside(LINES[q].X1+_103,LINES[q].Y1+_104, LINES, nlines);
                if (dir == dir___CW || dir == dir___CCW)
                        {
                        if (dir != direct)
                                {
                                bChange = true;
                                break;
                                }
                        }
                }
        if (bChange)
                {
                int d = 0;
                double D;
                for (int q=nlines-1; q>=(nlines-nlines%2)/2; q--)
                        {
                        D = LINES[q].X2;
                        LINES[q].X2 = LINES[d].X1;
                        LINES[d].X1 = D;
                        //
                        D = LINES[q].Y2;
                        LINES[q].Y2 = LINES[d].Y1;
                        LINES[d].Y1 = D;
                        //
                        if(d!=q)
                                {
                                D = LINES[q].X1;
                                LINES[q].X1 = LINES[d].X2;
                                LINES[d].X2 = D;
                                //
                                D = LINES[q].Y1;
                                LINES[q].Y1 = LINES[d].Y2;
                                LINES[d].Y2 = D;
                                }
                        d++;
                        }
                } 
        }