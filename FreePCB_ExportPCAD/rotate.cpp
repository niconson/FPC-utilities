//---------------------------------------------------------------------------


#pragma hdrstop

#include "rotate.h"
#include "FPC_to_PCB.h"
#include "math.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)


 
//поворот координат X Y

//void rotate (double Ang)
//{
/* double start_Ang;
 double end_Ang;
 double radius;
 if (X == 0)
    {
     if (Y > 0) start_Ang = 90;
     else if (Y < 0) start_Ang = 270;
    }
 else
    {
     start_Ang = (atan(Y/X))*573/10;
     if ((X > 0)&&(Y < 0)) start_Ang = 360 + start_Ang;
     if (X < 0) start_Ang = 180 + start_Ang;
    }
 end_Ang = start_Ang + Ang;
 radius = sqrt(pow(X,2) + pow(Y,2));
 Y = radius*sin(end_Ang*10/573);
 X = radius*cos(end_Ang*10/573);  */
//}