//---------------------------------------------------------------------------


#pragma hdrstop

#include "ex_str.h"
#include "FPC_to_PCB.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)



//извлекаем строку в строке А заключенную в ""

AnsiString ex_str (unsigned index)
{
AnsiString Q = "";
while (A.SubString(index,1) != "\"" )
        {
        index++;
        if ((int)index > A.Length()) return "Error";
        }
/*while (A.SubString(index,1) == "\"" )*/
index++;
while (A.SubString(index,1) != "\"" )
        {
        Q = Q + A.SubString(index,1);
        index++;
        if ((int)index > A.Length())
                {
                Flag_Warning6 = true;
                return "Error";
                }
        }
i = index;
return Q;
}