//---------------------------------------------------------------------------


#pragma hdrstop

#include "Rotate_Vertex.h"
#include "Debug_Areas.h"
#include "math.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)


void Rotate_Vertex (double *X, double *Y, double Ang)
{
double start_Ang = 0;
double end_Ang = 0;
double radius = 0;
bool Flag = false;
if (( ABS(*X) > DEFAULT )||( ABS(*Y) > DEFAULT ))
        {
        Flag = true;
        *X = (*X)/(double)DEFAULT;
        *Y = (*Y)/(double)DEFAULT;
        }
if (ABS(*X) < BY_ZERO)
        {
        if (*Y > 0) start_Ang = 90;
        else if (*Y < 0) start_Ang = 270;
        }
else
        {
        start_Ang = (atan(*Y/(*X)))*(double)180/(double)M_PI;
        if ((*X > 0)&&(*Y < 0)) start_Ang = (double)360 + start_Ang;
        if (*X < 0) start_Ang = (double)180 + start_Ang;
        }
end_Ang = start_Ang + Ang;
double powx = ABS(*X);
double powy = ABS(*Y);
if (powx > BY_ZERO) powx = pow(powx,2);
if (powy > BY_ZERO) powy = pow(powy,2);
if (powx > BY_ZERO || powy > BY_ZERO)   radius = sqrt(powx + powy);
else                                    radius = powx + powy;
*Y = radius*sin(end_Ang*(double)M_PI/(double)180);
*X = radius*cos(end_Ang*(double)M_PI/(double)180);
if (Flag) *X = (*X)*(double)DEFAULT;
if (Flag) *Y = (*Y)*(double)DEFAULT;
}