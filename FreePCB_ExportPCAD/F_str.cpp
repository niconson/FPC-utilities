//---------------------------------------------------------------------------


#pragma hdrstop

#include "F_str.h"
#include "FPC_to_PCB.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


AnsiString F_str (double DBL)
{
 AnsiString STRNG;
 STRNG = FormatFloat("0.0000",DBL);
 STRNG = StringReplace(STRNG,",",".",TReplaceFlags()<<rfReplaceAll);
 return STRNG;
}