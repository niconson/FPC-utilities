//---------------------------------------------------------------------------


#pragma hdrstop

#include "F_str.h"
#include "To_DXF.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)



AnsiString F_str (float DBL)
{
 AnsiString STRNG;
 STRNG = FormatFloat("0.000",DBL);
 STRNG = StringReplace(STRNG,",",".",TReplaceFlags()<<rfReplaceAll);
 return STRNG;
}