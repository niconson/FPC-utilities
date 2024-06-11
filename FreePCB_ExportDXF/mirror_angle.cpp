//---------------------------------------------------------------------------


#pragma hdrstop

#include "mirror_angle.h"
#include "To_DXF.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)







//---------------------------------------------------------------------------
void mirror_angle (float Part_angle, bool Part_layer, float *X, float *Y)
{
if(Part_layer) (*X) = -(*X);
Rotate_Vertex (X, Y, (-Part_angle));
}