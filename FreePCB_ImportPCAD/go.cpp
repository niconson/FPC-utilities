//---------------------------------------------------------------------------


#pragma hdrstop

#include "go.h"
#include "HEAD.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

 //������� ������ � ������ Ansi ���� �� �������� AnsiString s

int go (AnsiString Ansi, int index, AnsiString S)
{
while (Ansi.UpperCase().SubString(index, S.Length()) != S.UpperCase().SubString(1,S.Length()) )
      {
        index++;
        if (index > Ansi.Length()) return 0;
      }
return index;
}