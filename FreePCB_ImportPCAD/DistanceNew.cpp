//---------------------------------------------------------------------------


#pragma hdrstop

#include "DistanceNew.h"
#include "HEAD.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)




/*double Rotate_Lines (PcbLine * LINES, int CNTL, int Options)
        {
        double ANG = Angle( LINES[0].X2, LINES[0].Y2, LINES[0].X1, LINES[0].Y1 );
        for (int adr=0; adr<CNTL; adr++)
                {
                Rotate_Vertex( &LINES[adr].X1, &LINES[adr].Y1, -ANG );
                Rotate_Vertex( &LINES[adr].X2, &LINES[adr].Y2, -ANG );
                }
        return ANG;
        } */


void Swap (double * D1, double * D2)
        {
        *D1 = *D1 + *D2;
        *D2 = *D1 - *D2;
        *D1 = *D1 - *D2;
        }



//===================================
double Distance (       double X1,        //Line1
                        double Y1,        //Line1
                        double X2,        //Line1
                        double Y2,        //Line1
                        double X3,        //Line2
                        double Y3,        //Line2
                        double X4,        //Line2
                        double Y4,        //Line2
                        double *Xout,     //
                        double *Yout)     //
{
int DEFAULT = 999999999;
if (ABS(MAX4(X1,Y1,X2,Y2)) > DEFAULT || ABS(MAX4(X1,Y1,X2,Y2)) > DEFAULT)
        {
        ShowMessage("  Distance.cpp: Value location > MAX_FLOAT_VALUE");
        exit(0);
        }
double L12 = Length_Line(X1,Y1,X2,Y2);
double L34 = Length_Line(X3,Y3,X4,Y4);
double L1 = Length_Line(X1,Y1,X3,Y3);
double L2 = Length_Line(X2,Y2,X3,Y3);
double L3 = Length_Line(X1,Y1,X4,Y4);
double L4 = Length_Line(X2,Y2,X4,Y4);
double MinDistance = L1;
if (L12 < L34)
        {
        *Xout = X3;
        *Yout = Y3;
        }
else    {
        *Xout = X1;
        *Yout = Y1;
        }
if (L2 < MinDistance)
        {
        MinDistance = L2;
        if (L12 < L34)
                {
                *Xout = X3;
                *Yout = Y3;
                }
        else    {
                *Xout = X2;
                *Yout = Y2;
                }
        }
if (L3 < MinDistance)
        {
        MinDistance = L3;
        if (L12 < L34)
                {
                *Xout = X4;
                *Yout = Y4;
                }
        else    {
                *Xout = X1;
                *Yout = Y1;
                }
        }
if (L4 < MinDistance)
        {
        MinDistance = L4;
        if (L12 < L34)
                {
                *Xout = X4;
                *Yout = Y4;
                }
        else    {
                *Xout = X2;
                *Yout = Y2;
                }
        }
double Angle;
double RotateOutput = 0;
Line LINE[2];
double dx1;
double dx2;
double dy1;
double dy2;
for (int cs=0; cs<4; cs++)
        {
        LINE[0].X1 = X1;
        LINE[0].Y1 = Y1;
        LINE[0].X2 = X2;
        LINE[0].Y2 = Y2;
        LINE[1].X1 = X3;
        LINE[1].Y1 = Y3;
        LINE[1].X2 = X4;
        LINE[1].Y2 = Y4;
        Angle = Rotate_Lines ( &LINE[0], 2, 0);
        dy1 = LINE[1].Y1 - LINE[0].Y1;
        dy2 = LINE[1].Y2 - LINE[0].Y1;
        if (    (dy1 <= 0 && dy2 >= 0) ||
                (dy1 >= 0 && dy2 <= 0) )
                {
                if (ABS(dy1) < BY_ZERO)
                        {
                        dx1 = LINE[0].X1 - LINE[1].X1;
                        dx2 = LINE[0].X2 - LINE[1].X1;
                        if (    (dx1 <= 0 && dx2 >= 0) ||
                                (dx1 >= 0 && dx2 <= 0) )
                                {
                                MinDistance = 0;
                                *Xout = LINE[1].X1;
                                *Yout = LINE[1].Y1;
                                RotateOutput = Angle;
                                break;
                                }
                        }
                else    {
                        double x = LINE[1].X1 + ((LINE[1].X2 - LINE[1].X1) * ABS(dy1) / (ABS(dy1) + ABS(dy2)));
                        dx1 = LINE[0].X1 - x;
                        dx2 = LINE[0].X2 - x;
                        if (    (dx1 <= 0 && dx2 >= 0) ||
                                (dx1 >= 0 && dx2 <= 0) )
                                {
                                MinDistance = 0;
                                *Xout = x;
                                *Yout = LINE[0].Y1;
                                RotateOutput = Angle;
                                break;
                                }
                        }
                }
        dx1 = LINE[0].X1 - LINE[1].X1;
        dx2 = LINE[0].X2 - LINE[1].X1;
        if (    (dx1 <= 0 && dx2 >= 0) ||
                (dx1 >= 0 && dx2 <= 0) )
                {
                if (ABS(dy1) < MinDistance)
                        {
                        MinDistance = ABS(dy1);
                        *Xout = LINE[1].X1;
                        *Yout = LINE[0].Y1;
                        RotateOutput = Angle;
                        }
                }
        Swap(&X3, &X4);
        Swap(&Y3, &Y4);
        if (cs%2)
                {
                Swap(&X1, &X3);
                Swap(&Y1, &Y3);
                Swap(&X2, &X4);
                Swap(&Y2, &Y4);
                }
        }
if (RotateOutput) Rotate_Vertex( Xout, Yout, RotateOutput );
return MinDistance;
}