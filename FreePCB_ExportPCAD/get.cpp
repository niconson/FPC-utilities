//---------------------------------------------------------------------------


#pragma hdrstop

#include "get.h"
#include "FPC_to_PCB.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)


//если A == s return 0 else 1 (s == char str)
bool get (AnsiString s)
{
  A = str;
  A = A.Trim();
  i = s.Length();
  if (A.UpperCase().SubString(1,i) == s.UpperCase().SubString(1,i)) return 0;
  else return 1;
}