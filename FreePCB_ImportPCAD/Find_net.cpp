//---------------------------------------------------------------------------


#pragma hdrstop

#include "Find_net.h"
#include "HEAD.h"
#include "fstream.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

// ����� ����
AnsiString Find_net (AnsiString Pin )
{
//������ PART LIST
char str[MAX_CHARS];
Form1->Label4->Caption = "Reading netlist " + Pin;
Application->ProcessMessages();
AnsiString A = ExtractFilePath (Application->ExeName)  ;
A = A + "Import_Tango\\CombNetList.txt";
ifstream CombNetList (A.c_str());
AnsiString NET = "Unconnected";
while (A.SubString(1,3) != "end")
        {
        CombNetList.getline(str,sizeof(str));
        A = str;
        A = A.Trim();
        if (A.SubString(1,3) == "pin")
                {
                long m = prob (A, 2 );
                if (A.SubString(m,(A.Length()-m+1)) == Pin.SubString(1,Pin.Length())) break;
                }
        if (A.SubString(1,5) == "net: ")
                {
                long n = prob (A, 1 );
                NET = ex_str (A, &n );
                }
        }
return NET;
}