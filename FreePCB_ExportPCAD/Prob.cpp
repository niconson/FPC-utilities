//---------------------------------------------------------------------------


#pragma hdrstop

#include "Prob.h"
#include "FPC_to_PCB.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)



int Prob (int Count)
{
 long ind = 0;
 while (Count > 0)
       {
        while (ind <= A.Length())
              {
                if (A.SubString(ind,1) == "\"")
                        {
                        i++;
                        while (A.SubString(ind,1) != "\"")
                                {
                                ind++;
                                if (ind > A.Length()) return 0;
                                }
                        }
                ind++;
                if (A.SubString(ind,1) == " ")
                   {
                    Count--;
                    while (A.SubString(ind,1) == " ") ind++;
                    break;
                   }
              }
        if (ind > A.Length()) return 0;
       }
 return ind;
}