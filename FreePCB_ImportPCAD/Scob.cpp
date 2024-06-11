//---------------------------------------------------------------------------


#pragma hdrstop

#include "Scob.h"
#include "HEAD.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)


void Scob (AnsiString STR, int * SCOB)
        {
        for (int k=1; k<=STR.Length(); k++)
                {
                if (STR.SubString(k,1) == "(") (*SCOB)++;
                if (STR.SubString(k,1) == ")") (*SCOB)--;
                }
        }