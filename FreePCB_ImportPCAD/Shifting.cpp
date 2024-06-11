//---------------------------------------------------------------------------


#pragma hdrstop

#include "Shifting.h"
#include "HEAD.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)


void Shifting (long Case, AnsiString *DATA, long *Size_of, long Ptr)
{
long index = *Size_of;
*Size_of += (int)Case;
while (index >= Ptr)
        {
        *(DATA + (int)index + (int)Case) = *(DATA + (int)index);
        index--;
        }
while (Case)
        {
        *(DATA + (int)index + (int)Case) = "";
        Case--;
        }
}