//---------------------------------------------------------------------------


#pragma hdrstop

#include "ex_float.h"
#include "FPC_to_PCB.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)


 //извлекаем float в строке А пока число

float ex_float (unsigned index)
{
AnsiString Q = "";
current_units_mm = units_mm;
while ((A.SubString(index,1) < "0")||(A.SubString(index,1) > "9"))
      {
       if (A.SubString(index,1) == "-") Q = Q + A.SubString(index,1);
       if (A.SubString(index,1) == "+") Q = Q + A.SubString(index,1);
       index++;
       if ((int)index > A.Length())
                {
                i = 0;
                return 0;
                }
      }
while ((A.SubString(index,1) >= "0")&&(A.SubString(index,1) <= "9"))
      {
       Q = Q + A.SubString(index,1);
       index++;
       if ((A.SubString(index,1) == ".")||(A.SubString(index,1) == ","))
          {
            Q = Q + ",";
            index++;
          }
      }
if (A.UpperCase().SubString(index,2) == "MM" ) current_units_mm = true;
if (A.UpperCase().SubString(index,3) == "MIL" ) current_units_mm = false;
if (A.UpperCase().SubString(index,3) == " MM" ) current_units_mm = true;
if (A.UpperCase().SubString(index,4) == " MIL" ) current_units_mm = false;
if (Q.SubString(Q.Length(),1) == ",") Q = Q + "0";
double DE = StrToFloat(Q);
i = index;
return DE;
}