//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Warning.h"
#include "Comp_man.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
        : TForm(Owner)
{
Form3->Visible = false;
Form3->BorderStyle = bsDialog;
Form3->Position = poScreenCenter;
Form3->FormStyle = fsStayOnTop;
}
//---------------------------------------------------------------------------
void __fastcall TForm3::Button2Click(TObject *Sender)
{
ModalResult = mrCancel;
}
//---------------------------------------------------------------------------
void __fastcall TForm3::Button1Click(TObject *Sender)
{
ModalResult = mrOk;
}
//---------------------------------------------------------------------------

