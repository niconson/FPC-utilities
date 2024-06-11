//---------------------------------------------------------------------------


#pragma hdrstop

#include "ex_float_NM.h"
#include "FPC_to_PCB.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)


 //извлекаем float в строке Str пока число

double ex_float_NM (long *index, int units)
{
AnsiString Str = A;
if ((*index) == 0) *index = 1;
AnsiString Q = "";
while ((Str.SubString(*index,1) < "0")||(Str.SubString(*index,1) > "9"))
        {
        if ((*index) >= Str.Length()) return 0;
        if (Str.SubString(*index,1) == "-") Q = Q + Str.SubString(*index,1);
        if (Str.SubString(*index,1) == "+") Q = Q + Str.SubString(*index,1);
        (*index)++;
        }
while ((Str.SubString(*index,1) >= "0")&&(Str.SubString(*index,1) <= "9"))
        {
        if ((*index) > Str.Length()) return 0;
        Q = Q + Str.SubString(*index,1);
        (*index)++;
        if ((Str.SubString(*index,1) == ".")||(Str.SubString(*index,1) == ","))
                {
                Q = Q + ",";
                (*index)++;
                }
        }
while (Str.SubString((*index),1) == " ") (*index)++;
if (Q.SubString(Q.Length(),1) == ",") Q = Q + "0";
double DE = StrToFloat(Q);
if (units == 1) DE = DE/(double)1000000;
else if (units == 0)
                {
                DE = DE*25400;
                DE = DE/(double)1000000;
                }
return DE;
}