//---------------------------------------------------------------------------


#pragma hdrstop

#include "ex_float_NM.h"
#include "DelUnconnected.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)


 //извлекаем float в строке Str пока число

float ex_float_NM (AnsiString Str, long *index, int units)
{
if ((*index) == 0)              *index = 1;
if ((*index) > Str.Length())    return 0;
AnsiString Q = "";
///int current_units_mm = units;
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
if (!Q.Length()) return 0;
while (Str.SubString((*index),1) == " ") (*index)++;
if (Q.SubString(Q.Length(),1) == ",") Q = Q + "0";
float DE = StrToFloat(Q);
if (units == 0)
        {
        DE = DE*25400;
        }
if (units == 2)
        {
        DE = DE*1000000;
        }
return DE;
}