//---------------------------------------------------------------------------


#pragma hdrstop

#include "prob.h"
#include "Debug_Areas.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

//---------------------------------------------------------------------------
long prob (AnsiString ANSI , short int Pr)
{
short int ind = 0;
int ANSILength = ANSI.Length();
while (Pr)
        {
        ind++;
        if (ind > ANSILength) return 0;
        if (ANSI.SubString(ind,1) == "\"")
                {
                ind++;
                while (ANSI.SubString(ind,1) != "\"")
                        {
                        ind++;
                        if (ind > ANSILength) return 0;
                        }
                }
        if (ANSI.SubString(ind,1) == " ")
                {
                Pr--;
                while (ANSI.SubString(ind,1) == " ")
                        {
                        ind++;
                        if (ind > ANSILength) return 0;
                        }
                ind--;
                }
        }
while (ANSI.SubString(ind,1) == " ") ind++;
if (ind > ANSILength) return 0;
return ind;
}
