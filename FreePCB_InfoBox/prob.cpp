//---------------------------------------------------------------------------


#pragma hdrstop

#include "prob.h"
#include "Comp_man.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)


long prob (AnsiString ANSI , long Pr)
{
 int ANSILength = ANSI.Length();
 long ind = 0;
 while (Pr)
       {
        ind++;
        if (ind >= ANSILength) return 0;
        if (ANSI.SubString(ind,1) == "\"")
                {
                ind++;
                while (ANSI.SubString(ind,1) != "\"")
                        {
                        ind++;
                        if (ind >= ANSILength) return 0;
                        }
                }
        if (ANSI.SubString(ind,1) == " ") Pr--;
       }
 while (ANSI.SubString(ind,1) == " ") ind++;
 return ind;
}