//---------------------------------------------------------------------------


#pragma hdrstop

#include "StrBegin.h"
#include "HEAD.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

bool StrBegin (AnsiString STR1, AnsiString STR2)
        {
        if (!STR1.Length()) return false;
        if (!STR2.Length()) return false;
        if (STR1.LowerCase().SubString(1,STR1.Length()) == STR2.LowerCase().SubString(1,STR1.Length()) )
        return true;
        if (STR1.LowerCase().SubString(1,STR2.Length()) == STR2.LowerCase().SubString(1,STR2.Length()) )
        return true;
        return false;
        }