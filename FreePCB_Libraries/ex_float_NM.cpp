//---------------------------------------------------------------------------


#pragma hdrstop

#include "ex_float_NM.h"
#include "ABClibrary.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)




 //извлекаем float в строке Str пока число

float ex_float_NM (AnsiString Str, long *index, AnsiString *UnitS /*NM, MM or MIL*/)
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
///if (Str.UpperCase().SubString((*index),2) == "MM" ) {current_units_mm = 1;  *index = (*index)+2; }
///if (Str.UpperCase().SubString((*index),3) == "MIL" ) {current_units_mm = 0; *index = (*index)+3; }
if (Q.SubString(Q.Length(),1) == ",") Q = Q + "0";
float DE = StrToFloat(Q);
if ((*UnitS).UpperCase().SubString(1,3) == "MIL")       DE = DE*25400;
else if ((*UnitS).UpperCase().SubString(1,2) == "MM")   DE = DE*MLN;
return DE;
}