//---------------------------------------------------------------------------


#pragma hdrstop

#include "FreePCBPaste.h"
#include "Comp_man.h"
#include "Path_EXE.h"
#include "Clipbrd.hpp"
//---------------------------------------------------------------------------

#pragma package(smart_init)

bool FreePCBPaste (AnsiString FILE, float locX, float locY, int units)
{
if (!FILE.Length())
        return false;
HWND FreePCB = FindWindow( NULL,HeaderBack.c_str());
if(!FreePCB)
        FreePCB = FindWindow( NULL, (HeaderBack+"*").c_str());
if (FreePCB)
        {
        SetForegroundWindow(FreePCB);
        AnsiString mes = "paste: \"" + FILE + "\"";
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