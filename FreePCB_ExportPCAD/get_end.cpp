//---------------------------------------------------------------------------


#pragma hdrstop

#include "get_end.h"
#include "FPC_to_PCB.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)


AnsiString MEM_get_end ;
unsigned out = 0;
bool get_end (void)
{
A = str;
A = A.Trim();
if (out > 7) {out = 0; return 0;}
if (A.SubString(1,A.Length()) == MEM_get_end.SubString(1,MEM_get_end.Length())) {out++; return 1; }
out = 0;
MEM_get_end = A;
return 1;
}