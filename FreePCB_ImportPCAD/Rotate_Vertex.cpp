//---------------------------------------------------------------------------


#pragma hdrstop

#include "Rotate_Vertex.h"
#include "HEAD.h"
#include "math.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)


void Rotate_Vertex (double *X, double *Y, double Ang)
{
double start_Ang;
double end_Ang;
double radius;
bool Flag = false;
if ( abs(*X) > 30000 ) Flag = true;
if ( abs(*Y) > 30000 ) Flag = true;
if (Flag) *X = (*X)/(double)100000;
if (Flag) *Y = (*Y)/(double)100000;
if (*X == 0)
        {
        if (*Y > 0) start_Ang = 90;
        else if (*Y < 0) start_Ang = 270;
        }
else
        {
        start_Ang = (atan(*Y/(*X)))*573/10;
        if ((*X > 0)&&(*Y < 0)) start_Ang = 360 + start_Ang;
        if (*X < 0) start_Ang = 180 + start_Ang;
        }
end_Ang = start_Ang + Ang;
if ((*X!=0)||(*Y!=0))
radius = sqrt(pow(*X,2) + pow(*Y,2));
else radius = 0;
*Y = radius*sin(end_Ang*10/573);
*X = radius*cos(end_Ang*10/573);
if (Flag) *X = (*X)*(double)100000;
if (Flag) *Y = (*Y)*(double)100000;
}