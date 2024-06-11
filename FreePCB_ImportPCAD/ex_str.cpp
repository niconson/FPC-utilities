//---------------------------------------------------------------------------


#pragma hdrstop

#include "ex_str.h"
#include "HEAD.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

AnsiString ex_str (AnsiString ANSI, long *n)
{
while (ANSI.SubString((*n),1) != "\"") {(*n)++; if ((*n) > ANSI.Length()) return "";}
(*n)++;
AnsiString A = "";
while (ANSI.SubString((*n),1) != "\"")
        {
        A = A + ANSI.SubString(*n,1);
        (*n)++;
        if ((*n) > ANSI.Length()) return "Error_func_ex_str";
        }
(*n)++;
return A;
}