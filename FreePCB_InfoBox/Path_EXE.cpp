//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Path_EXE.h"
#include "Comp_man.h"       
#include <FileCtrl.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
Form1->Timer1->Enabled = true;
}
//---------------------------------------------------------------------------

//============ Execute OpenDialog1 ==================

//---------------------------------------------------------------------------
void __fastcall TForm2::FormClose(TObject *Sender, TCloseAction &Action)
{
save_path_func();
Sleep (100);
Embed(Form1->Width,Form1->Height);
Form1->Visible = true;
SetFormComponentsSizes(0);
Application->ProcessMessages();
if(FileNameBack.Length() == 0)
        ShowMessage("Click on the FREEPCB window form to update the partlist");
Form1->Timer1->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::LanguageClick(TObject *Sender)
{
save_path_func();
INTER_FACE();
FileName = "";
FileNameBack = "";
WindowHeader = "res";
}
//---------------------------------------------------------------------------

void __fastcall TForm2::check_viasClick(TObject *Sender)
{
FileName = "";
FileNameBack = "";
WindowHeader = "res";
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Label1Click(TObject *Sender)
{
ShellExecute(NULL, "open", "https://github.com/Duxah/FreePCB-2/blob/master/README.md", NULL, NULL, SW_SHOWNORMAL);        
}
//---------------------------------------------------------------------------

