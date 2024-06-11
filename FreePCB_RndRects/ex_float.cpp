//---------------------------------------------------------------------------


#pragma hdrstop

#include "ex_float.h"
#include "RND.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

//извлекаем float в строке Str пока число

double ex_float (AnsiString Str, long *index)
{
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
if (Q.SubString(Q.Length(),1) == ",") Q = Q + "0";
double DE = StrToFloat(Q);
return DE;
}
