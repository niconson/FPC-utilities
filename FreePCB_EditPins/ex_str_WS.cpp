//---------------------------------------------------------------------------


#pragma hdrstop

#include "ex_str_WS.h"
#include "DelUnconnected.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)




AnsiString ex_str_WS (AnsiString ANSI, long *n, AnsiString Sym)
{
AnsiString A = "";
while (ANSI.SubString((*n),1) != Sym.SubString(1,1))
        {
        A = A + ANSI.SubString(*n,1);
        (*n)++;
        if ((*n) > ANSI.Length()) return A;
        }
while (ANSI.SubString((*n),1) == Sym.SubString(1,1)) (*n)++;
return A;
}