//---------------------------------------------------------------------------


#pragma hdrstop

#include "ex_str.h"
#include "ABClibrary.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

AnsiString ex_str (AnsiString ANSI, long *n)
{
  while (ANSI.SubString((*n),1) != "\"") {(*n)++; if ((*n) > ANSI.Length()) return "";}
  (*n)++;
  AnsiString OUTstr = "";
  while (ANSI.SubString((*n),1) != "\"")
        {
         OUTstr = OUTstr + ANSI.SubString(*n,1);
         (*n)++;
         if ((*n) > ANSI.Length()) return "Error_func_ex_str";
        }
  (*n)++;
  while (ANSI.SubString((*n),1) == " ") (*n)++;
  return OUTstr;
}