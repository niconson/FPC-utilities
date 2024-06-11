//---------------------------------------------------------------------------


#pragma hdrstop

#include "ex_float_NM.h"
#include "Comp_man.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)


 //извлекаем float в строке Str пока число

float ex_float_NM (AnsiString Str, long *index, int units, int * Ptr_Units)
{
if ((*index) == 0) *index = 1;
AnsiString Q = "";
int StrLength = Str.Length();
while ((Str.SubString(*index,1) < "0")||(Str.SubString(*index,1) > "9"))
        {
        if (Str.SubString(*index,1) == "-") Q += "-";
        if (Str.SubString(*index,1) == "+") Q += "+";
        (*index)++;
        if ((*index) > StrLength) return 0;
        }
if( Q.Length() > 1 )
        Q.SetLength(1);
bool bZ = 0;
while ((Str.SubString(*index,1) >= "0")&&(Str.SubString(*index,1) <= "9"))
        {
        Q += Str.SubString(*index,1);
        (*index)++;
        if ((*index) > StrLength) break;
        while((Str.SubString(*index,1) == ".")||(Str.SubString(*index,1) == ","))
                {
                if( !bZ )
                        Q += ",";
                bZ = true;
                (*index)++;
                if ((*index) > StrLength) break;
                }
        if ((*index) > StrLength) break;
        }
int endI = *index;
while (Str.SubString((*index),1) == " ") (*index)++;
if (Q.SubString(Q.Length(),1) == ",") Q += "0";
float DE = 0;
if(!TryStrToFloat( Q, DE ))
        {
//        ShowMessage(" Can't convert to float" );
        }
// convert
if (units == 0)         DE = DE/MIL_TO_NM;
else if (units == 1)    DE = DE/MM_TO_NM;
else if (units == 2)    DE = DE/MM_TO_MIL;
// Ptr_stringUnits
if(Ptr_Units)
        {
        if( endI < StrLength )
                if( Str.SubString(endI,2).UpperCase() == "MM" )
                        *Ptr_Units = 1;
        if( endI+1 < StrLength )
                if( Str.SubString(endI,3).UpperCase() == "MIL" )
                        *Ptr_Units = 0;
        }
return DE;
}