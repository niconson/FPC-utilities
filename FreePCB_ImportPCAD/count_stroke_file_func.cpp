//---------------------------------------------------------------------------


#pragma hdrstop

#include "count_stroke_file_func.h"
#include "HEAD.h"
#include "fstream.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

long count_stroke_file_func (AnsiString OpenD)
{
ifstream read_S (OpenD.c_str());
AnsiString B = ExtractFilePath (Application->ExeName)  ;
B = B + "Import_Tango\\Grb.txt";
ofstream WR_Grb (B.c_str());
char str[MAX_CHARS];
long i;
AnsiString A  ;
long count_stroke_file = 0;
Form1->Label4->Caption = "Counting the number of lines in a PCB file" ;
Application->ProcessMessages();
while  (A.SubString(1,12) != "(asciiHeader" )
        {
        read_S.getline(str,sizeof(str))  ;
        A = str;
        A = A.Trim();
        count_stroke_file++;
        if (count_stroke_file > 50) {ShowMessage ("    Format not available!"); return 0;}
        }
while (1)
        {
        read_S.getline(str,sizeof(str))  ;
        A = str;
        A = A.Trim();
        count_stroke_file++;
        if (read_S.eof()) break;
        if (A.SubString(1,10) == "(fileUnits" )
                {
                i = prob (A,1) ;
                if (A.UpperCase().SubString(i,2) == "MM" )
                        {
                        UNITS = 1;
                        WR_Grb << AnsiString("Units: MM").c_str() << endl;
                        }
                else if (A.UpperCase().SubString(i,3) == "MIL" )
                        {
                        UNITS = 0;
                        WR_Grb << AnsiString("Units: MIL").c_str() << endl;
                        }
                else ShowMessage ("   Error fileUnits!");
                }
        else if (A.SubString(1,12) == "(solderSwell" )
                {
                i = prob (A,1) ;
                long mask_clearance = ex_float_NM (A, &i, UNITS);
                WR_Grb << (AnsiString("mask_clearance: ") + AnsiString(mask_clearance)).c_str() << endl;
                }
        else if (A.SubString(1,11) == "(pasteSwell" )
                {
                i = prob (A,1) ;
                long shrink_paste_mask  = ex_float_NM (A, &i, UNITS);
                WR_Grb << (AnsiString("shrink_paste_mask: ") + AnsiString(shrink_paste_mask)).c_str() << endl;
                }
        else if (A.SubString(1,11) == "(planeSwell" )
                {
                i = prob (A,1) ;
                long fill_clearance = ex_float_NM (A, &i, UNITS);
                WR_Grb << (AnsiString("fill_clearance: ") + AnsiString(fill_clearance)).c_str() << endl;
                }
        }
Form1->Label5->Caption = AnsiString("Line Count: ") + AnsiString(count_stroke_file);
Form1->Label4->Caption = "Line Count Completed" ;
Application->ProcessMessages();
read_S.close();
WR_Grb.close();
return count_stroke_file;
}