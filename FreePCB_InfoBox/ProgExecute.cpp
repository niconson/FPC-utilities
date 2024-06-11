//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ProgExecute.h"
#include "Comp_man.h"
#include "Path_EXE.h"
#include "Warning.h"
#include "Clipbrd.hpp"
//---------------------------------------------------------------------------

#pragma package(smart_init)
static AnsiString LastPath;
void ProgExecute (AnsiString Path)
        {
        Form1->Timer1->Enabled = false;
        Disable_ENTER = true;
        AnsiString S = ExtractFileName(Path);
        if (WindowHeader.SubString(WindowHeader.Length(),1) == "*" )
        if (S.SubString(1,5) != "DXF_2")
        if (S.SubString(1,5) != "PCB_2")
        if (S.SubString(1,5) != "BMP_2")
        if (S.SubString(1,5) != "GenIn")
        if (Path.Pos(".") > 1)
                {
                //WARNING
                if (Form3->ShowModal() == mrCancel)
                        {
                        PathProg = ExtractFilePath(Application->ExeName);
                        PathProg = PathProg.SubString(1,(PathProg.Length()-1));
                        PathProg = ExtractFilePath(PathProg);
                        FlagProgEXE = true;
                        LastPath = Path;
                        Wind = FindWindow(NULL, WindowHeader.c_str());
                        SetForegroundWindow(Wind);
                        Form1->Timer1->Enabled = true;
                        Disable_ENTER = false;
                        return;
                        }
                }
        if (FlagProgEXE) Path = LastPath;
        FlagProgEXE = false;
        Clipboard()->Open();
        Clipboard()->Clear();
        if (FileName.Length()) Clipboard()->SetTextBuf(("ObjMan \"" + FileName + "\"").c_str());
        THandle h=Clipboard()->GetAsHandle(CF_TEXT);    //»справление ошибки
        SetClipboardData(CF_LOCALE, (void*)h);          //"кракоз€бры при передаче в офис"
        Clipboard()->Close();
        AnsiString Bst = Path;
        AnsiString Ast = ExtractFilePath(Path);
        if ((UINT)ShellExecute(NULL,
                "open",
                Bst.c_str(),
                NULL,
                Ast.c_str() ,
                SW_SHOWNORMAL) <=32)
                {
                Form2->Visible = true;
                }
        PathProg = ExtractFilePath(Application->ExeName);
        PathProg = PathProg.SubString(1,(PathProg.Length()-1));
        PathProg = ExtractFilePath(PathProg);
        Form1->Timer1->Enabled = true;
        Disable_ENTER = false;
        }
