//---------------------------------------------------------------------------


#pragma hdrstop

#include "ang.h"
#include "FPC_to_PCB.h"
#include "math.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

float ang (double dx_, double dy_)
{
double ANG_s;
if (dx_ == 0)
                 {
                  if (dy_ > 0) ANG_s = 90;
                  else ANG_s = 270;
                 }
else
                 {
                  double Dxy = dy_/dx_;
                  ANG_s = (atan(Dxy))*573/10;
                  if ((dx_ > 0)&&(dy_ < 0)) ANG_s = 360 + ANG_s;
                  if (dx_ < 0) ANG_s = 180 + ANG_s;
                 }
return ANG_s;
}
