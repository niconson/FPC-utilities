//---------------------------------------------------------------------------


#pragma hdrstop

#include "prob.h"
#include "BMP.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

long long prob (AnsiString ANSI , long long Pr)
{
 long i = 0;
 while (Pr)
       {
        i++;
        if (i >= ANSI.Length()) return 0;
        if (ANSI.SubString(i,1) == "\"")
                {
                i++;
                while (ANSI.SubString(i,1) != "\"")
                        {
                        i++;
                        if (i >= ANSI.Length()) return 0;
                        }
                }
        if (ANSI.SubString(i,1) == " ") Pr--;
       }
 while (ANSI.SubString(i,1) == " ") i++;
 return i;
}