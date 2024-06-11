//---------------------------------------------------------------------------


#pragma hdrstop

#include "RotatePoints.h"
#include "To_DXF.h"
#include "DXF_library.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)


 void RotatePoints(TPoint * P, int npoints, float angle)
 {      for( int i=0; i<npoints; i++)
                {
                float x = P[i].x;
                float y = P[i].y;
                Rotate_Vertex(&x,&y,angle);
                P[i].x = x;
                P[i].y = y;
                }
 }
