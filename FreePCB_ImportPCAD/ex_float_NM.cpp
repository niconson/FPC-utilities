//---------------------------------------------------------------------------


#pragma hdrstop

#include "ex_float_NM.h"
#include "HEAD.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

 //��������� float � ������ Str ���� �����

double ex_float_NM (AnsiString Str, long *index, int units)
{
if ((*index) == 0) *index = 1;
AnsiString Q = "";
int current_units_mm = units;
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
if (Str.UpperCase().SubString((*index),2) == "MM" ) {current_units_mm = 1;  *index = (*index)+2; }
if (Str.UpperCase().SubString((*index),3) == "MIL" ) {current_units_mm = 0; *index = (*index)+3; }
if (Q.SubString(Q.Length(),1) == ",") Q = Q + "0";
double DE = StrToFloat(Q);
if (units >= 0)
        {
        if (current_units_mm) DE = DE*1000000;
        else                  DE = DE*25400;
        return ( long)DE;
        }
return DE;
}