//---------------------------------------------------------------------------


#pragma hdrstop

#include "Rotate_Vertex.h"
#include "Comp_man.h"
#include "math.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)


void Rotate_Vertex (float *X, float *Y, float Ang)
{
float start_Ang = 0;
float end_Ang = 0;
float radius = 0;
bool Flag = false;
if (( ABS(*X) > DEFAULT )||( ABS(*Y) > DEFAULT ))
        {
        Flag = true;
        *X = (*X)/DEFAULT;
        *Y = (*Y)/DEFAULT;
        }
if (ABS(*X) < BY_ZERO)
        {
        if (*Y > 0) start_Ang = 90.0;
        else if (*Y < 0) start_Ang = 270.0;
        }
else
        {
        start_Ang = (atan(*Y/(*X)))*180.0/M_PI;
        if ((*X > 0)&&(*Y < 0)) start_Ang = 360.0 + start_Ang;
        if (*X < 0) start_Ang = 180.0 + start_Ang;
        }
end_Ang = start_Ang + Ang;
double powx = ABS(*X);
double powy = ABS(*Y);
if (powx > BY_ZERO) powx = pow(powx,2);
if (powy > BY_ZERO) powy = pow(powy,2);
if (powx > BY_ZERO || powy > BY_ZERO)   radius = sqrt(powx + powy);
else                                    radius = powx + powy;
*Y = radius*sin(end_Ang*M_PI/180.0);
*X = radius*cos(end_Ang*M_PI/180.0);
if (Flag) *X = (*X)*DEFAULT;
if (Flag) *Y = (*Y)*DEFAULT;
}