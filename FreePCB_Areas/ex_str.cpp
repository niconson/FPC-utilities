//---------------------------------------------------------------------------


#pragma hdrstop

#include "ex_str.h"
#include "Debug_Areas.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

AnsiString ex_str (AnsiString ANSI, short int *n)
{
short int LEN = ANSI.Length();
while (ANSI.SubString((*n),1) != "\"")
        {
        (*n)++;
        if ((*n) > LEN) return "Empty";
        }
(*n)++;
short int st = *n;
while (ANSI.SubString((*n),1) != "\"")
        {
        (*n)++;
        if ((*n) > LEN) return "Error_func_ex_str";
        }
short int end = *n;
(*n)++;
return ANSI.SubString(st,(end-st)) ;
}