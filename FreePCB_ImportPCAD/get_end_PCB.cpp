//---------------------------------------------------------------------------


#pragma hdrstop

#include "get_end_PCB.h"
#include "HEAD.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)


static AnsiString Back = "123";
static AnsiString Back2 = "234";
static AnsiString Back3 = "234";

bool get_end_PCB (AnsiString STRNG)
{
Back2 = Back;
Back = STRNG;
int K = 0;
for (int k=1; k<=STRNG.Length(); k++)
                {
                if (STRNG.SubString(k,1) == "\"") K++;
                }
if (!K%2)
if (STRNG.SubString(1,STRNG.Length()) != "(" && STRNG.SubString(1,STRNG.Length()) != ")")
if (Back2.SubString(1,Back2.Length()) == Back.SubString(1,Back.Length()))
if (STRNG.SubString(1,STRNG.Length()) == Back.SubString(1,Back.Length()))   return false;
return true;
}