//---------------------------------------------------------------------------


#pragma hdrstop

#include "prob.h"
#include "DelUnconnected.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)



//---------------------------------------------------------------------------
long prob (AnsiString ANSI , long Pr)
{
long ind = 0;
while (Pr)
        {
        ind++;
        if (ind > ANSI.Length()) return 0;
        if (ANSI.SubString(ind,1) == "\"")
                {
                ind++;
                while (ANSI.SubString(ind,1) != "\"")
                        {
                        ind++;
                        if (ind > ANSI.Length()) return 0;
                        }
                }
        if (ANSI.SubString(ind,1) == " ")
                {
                Pr--;
                while (ANSI.SubString(ind,1) == " ")
                        {
                        ind++;
                        if (ind > ANSI.Length()) return 0;
                        }
                ind--;
                }
        }
while (ANSI.SubString(ind,1) == " ") ind++;
return ind;
}