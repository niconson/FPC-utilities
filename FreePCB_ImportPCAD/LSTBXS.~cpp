//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "LSTBXS.h"
#include "HEAD.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;

//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
Form2->StringGrid1->ColCount = 17;
Form2->StringGrid1->FixedCols = 0;
Form2->StringGrid1->FixedRows = 1;
Form2->StringGrid1->DefaultColWidth = 80;
Form2->StringGrid1->DefaultRowHeight = 15;
Form2->StringGrid1->Cells[0][0] = "PINS";
Form2->StringGrid1->Cells[1][0] = "INDEX";
Form2->StringGrid1->Cells[2][0] = "NETS";
Form2->StringGrid1->Cells[3][0] = "X";
Form2->StringGrid1->Cells[4][0] = "Y";
Form2->StringGrid1->Cells[5][0] = "T1"; //X Left     TOP
Form2->StringGrid1->Cells[6][0] = "T2"; //Y Left
Form2->StringGrid1->Cells[7][0] = "T3"; //X Right
Form2->StringGrid1->Cells[8][0] = "T4"; //Y Right
Form2->StringGrid1->Cells[9][0] = "B1"; //X Left     BOT
Form2->StringGrid1->Cells[10][0] = "B2"; //Y Left
Form2->StringGrid1->Cells[11][0] = "B3"; //X Right
Form2->StringGrid1->Cells[12][0] = "B4"; //Y Right
Form2->StringGrid1->Cells[13][0] = "I1"; //X Left    INN
Form2->StringGrid1->Cells[14][0] = "I2"; //Y Left
Form2->StringGrid1->Cells[15][0] = "I3"; //X Right
Form2->StringGrid1->Cells[16][0] = "I4"; //Y Right
Form2->StringGrid1->RowCount = 2;
Form2->StringGrid1->Row = 1;
Form2->StringGrid1->Col = 0;
Form2->StringGrid1->Cells[0][Form2->StringGrid1->Row] = "";
Form2->StringGrid1->Cells[1][Form2->StringGrid1->Row] = "-1";
Form2->StringGrid1->Cells[2][Form2->StringGrid1->Row] = "Unconnected";
}

//---------------------------------------------------------------------------


void __fastcall TForm2::Button1Click(TObject *Sender)
{
AnsiString T = Form2->Edit1->Text;
int i = 0;
while (i < Form2->StringGrid1->RowCount)
        {
        Form2->StringGrid1->Row = i;
        AnsiString S = Form2->StringGrid1->Cells[0][i];
        if (S.UpperCase().SubString(1,S.Length()) == T.UpperCase().SubString(1,T.Length())) return;
        i++;
        }
ShowMessage ("    String: " + T + " not found!");
}
//---------------------------------------------------------------------------

