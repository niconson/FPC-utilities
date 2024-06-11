//---------------------------------------------------------------------------


#pragma hdrstop

#include "read_net_list.h"
#include "HEAD.h"
#include "fstream.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

void read_net_list(AnsiString OpenD, long CNT)
{
long i = 0;
char str[MAX_CHARS];
AnsiString A = "";
ifstream LoadLib(OpenD.c_str());
//"(pcbDesign "
while (A.SubString(1,11) != "(pcbDesign " )
        {
        LoadLib.getline(str,sizeof(str));
        A = str;
        A = A.Trim();
        CNT--;
        if (StrBegin (A, "(netlist "))  Form1->Library->Items->Add("netlist");
        else                            Form1->Library->Items->Add(A);
        if (CNT<0) break;
        }
LoadLib.close();
//×ÒÅÍÈÅ NET LIST
Form1->Label4->Caption = "Reading PCB netlist" ;
Application->ProcessMessages();
AnsiString B = ExtractFilePath (Application->ExeName)  ;
B = B + "Import_Tango\\NetList.txt";
ofstream WR_NET (B.c_str());
//long i_pin;
long LibIndex;
//i_pin = 0;
LibIndex = Form1->Library->Items->IndexOf("netlist");
AnsiString part;
AnsiString num_pin;
if      (LibIndex != -1)
while   (LibIndex < Form1->Library->Count)
        {
        A = Form1->Library->Items->operator [](LibIndex);
        if (A.SubString(1,5) == "(net " )
                {
                i = prob (A,1) ;
                B = ex_str (A,&i);
                B = AnsiString("net: \"") + B + "\"";
                WR_NET << B.c_str() << endl;
                //i_pin = 1;
                }
        if (A.SubString(1,6) == "(node " )
                {
                i = prob (A,1);
                part = ex_str (A,&i);
                num_pin = ex_str (A,&i);
                B = AnsiString("pin: ") + part + "." + num_pin;
                WR_NET << B.c_str() << endl;
                //i_pin++;
                }
        LibIndex++;
        }
WR_NET << "end" << endl;
WR_NET.close();
Form1->Label4->Caption = "Netlist reading completed" ;
Application->ProcessMessages();
}
