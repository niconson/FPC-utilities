//---------------------------------------------------------------------------


#pragma hdrstop

#include "count_seg.h"
#include "RND.h"
#include "fstream.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

int count_seg (AnsiString B2, long num_str)
{
             long k = 0;
             B2 = ExtractFilePath(Application->ExeName);
             B2 = B2 + "_RND.fpc";
             ifstream FIND (B2.c_str());
             while (num_str)
                   {
                     FIND.getline (s, sizeof(s)) ;
                     num_str--;
                   }
             FIND.getline (s, sizeof(s)) ;
             B2 = s;
             B2 = B2.Trim();
             while ((B2.SubString(1,3) == "vtx")||(B2.SubString(1,3) == "seg"))
                   {
                     if (B2.SubString(1,3) == "seg") k++;
                     FIND.getline (s, sizeof(s)) ;
                     B2 = s;
                     B2 = B2.Trim();
                   }
             while (B2.SubString(1,6) == "corner")
                   {
                     k++;
                     FIND.getline (s, sizeof(s)) ;
                     B2 = s;
                     B2 = B2.Trim();
                   }
             FIND.close();
             return k;
}