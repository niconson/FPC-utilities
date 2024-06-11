//---------------------------------------------------------------------------


#pragma hdrstop

#include "prob.h"
#include "HEAD.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

long prob (AnsiString ANSI , long Pr)
{
long i = 0;
while (Pr)
        {
        if (ANSI.SubString(i,1) == "\"")
                {
                i++;
                while (ANSI.SubString(i,1) != "\"")
                        {
                        i++;
                        if (i > ANSI.Length()) return 0;
                        }
                }
        i++;
        if (ANSI.SubString(i,1) == " ") Pr--;
        while (ANSI.SubString(i,1) == " ") i++;
        if (i > ANSI.Length()) return 0;
        }
while (ANSI.SubString(i,1) == " ") i++;
return i;
}
