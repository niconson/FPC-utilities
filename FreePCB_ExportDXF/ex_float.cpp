//---------------------------------------------------------------------------


#pragma hdrstop

#include "ex_float.h"
#include "To_DXF.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)



//извлекаем float в строке Str пока число

float ex_float (AnsiString Str, long *index)
{
AnsiString Q = "";
//current_units_mm = units_mm;
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
while (Str.SubString(*index,1) == " ") (*index)++;
//if (A.UpperCase().SubString(index,2) == "MM" ) current_units_mm = true;
//if (A.UpperCase().SubString(index,3) == "MIL" ) current_units_mm = false;
//if (A.UpperCase().SubString(index,3) == " MM" ) current_units_mm = true;
//if (A.UpperCase().SubString(index,4) == " MIL" ) current_units_mm = false;
if (Q.SubString(Q.Length(),1) == ",") Q = Q + "0";
float DE = StrToFloat(Q);
return DE;
}