//---------------------------------------------------------------------------


#pragma hdrstop

#include "MOVE.h"
#include "Comp_man.h"
//#include "Path_EXE.h"
//#include "Clipbrd.hpp"
//---------------------------------------------------------------------------

#pragma package(smart_init)
static AnsiString mes;



bool MOVE (AnsiString Ref)
{
if (!Ref.Length())      return false;
if (!FileName.Length()) return false;
int p = Ref.Pos(".");
if (p > 0)
        {
        Ref = Ref.SubString(1,(p-1));
        if (Ref.Pos(".") > 0) return false;
        }
HWND FreePCB = FindWindow( NULL,WindowHeader.c_str());
if (FreePCB)
        {
        SetForegroundWindow(FreePCB);
        mes = "move: \"" + Ref + "\"";
        char data[CDS_SHORT_MAX_LEN];
        int len = MIN(mes.Length(),(CDS_SHORT_MAX_LEN-1));
        data[len] = '\0';
        for (int cp=(len-1); cp>=0; cp--)
                data[cp] = mes[cp+1];
        CDS_SHORT.lpData = data;
        CDS_SHORT.cbData = len+1;
        SendMessageA(FreePCB, WM_COPYDATA, 0, (LPARAM)&CDS_SHORT);
        }
return true;
}
