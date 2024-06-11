//---------------------------------------------------------------------------


#pragma hdrstop
          
#include "ex_float_NM.h"
#include "Debug_Areas.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

 //извлекаем float в строке Str пока число

float ex_float_NM (AnsiString Str, short int *index, int units)
{
if ((*index) == 0)              *index = 1;
if ((*index) > Str.Length())    return 0;
AnsiString out = "";
//
short int LenStr = Str.Length();
bool inv = false;
while ((Str.SubString(*index,1) < "0")||(Str.SubString(*index,1) > "9"))
        {
        if ((*index) >= LenStr) return 0;
        if (Str.SubString(*index,1) == "-") inv = true;
        (*index)++;
        }
short int st = (*index);
bool f = false;
while ((Str.SubString(*index,1) >= "0")&&(Str.SubString(*index,1) <= "9"))
        {
        if ((*index) > LenStr) return 0;
        (*index)++;
        if ((Str.SubString(*index,1) == ".")||(Str.SubString(*index,1) == ","))
                {
                if (f) return 0;
                f = true;
                if (st == (*index)) return 0;
                out = Str.SubString(st,((*index) - st)) + ",";
                (*index)++;
                st = (*index);
                }
        }
if (st != (*index)) out += Str.SubString(st,((*index) - st));
while (Str.SubString((*index),1) == " ") (*index)++;
float DE = StrToFloat(out);
//
if (units == uMIL)         DE = DE*_2542;
else if (units == uMM)     DE = DE*_106;
//
if (inv)        return -DE;
else            return DE;
}