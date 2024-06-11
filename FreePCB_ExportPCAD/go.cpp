//---------------------------------------------------------------------------


#pragma hdrstop

#include "go.h"
#include "FPC_to_PCB.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)


//двигаем курсор в строке ј пока не встретим AnsiString s

int go (long index, AnsiString s)
{
while (A.UpperCase().SubString(index,s.Length()) != s.UpperCase().SubString(1,s.Length()) )
      {
        index++;
        if (index > A.Length()) return 0;
      }
return index;
}