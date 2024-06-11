//---------------------------------------------------------------------------


#pragma hdrstop

#include "ex_str.h"
#include "Comp_man.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)


AnsiString ex_str (AnsiString ANSI, long *n)
{
  int ANSILength = ANSI.Length();
  while ((ANSI.SubString(*n,1) != "\"")&&((*n) <= ANSILength)) (*n)++;
  if ((*n) > ANSILength) return "";
  (*n)++;
  long Startin = (*n);
  AnsiString RETURNED = "";
  while ((ANSI.SubString((*n),1) != "\"")&&((*n) <= ANSILength)) (*n)++;
  if ((*n) > ANSILength) return "";
  if ((*n) > Startin)   RETURNED = ANSI.SubString(Startin,(*n - Startin));
  while (ANSI.SubString((*n),1) == "\"") (*n)++;
  if ((*n) > ANSILength) (*n) = 0;
  return RETURNED;
}