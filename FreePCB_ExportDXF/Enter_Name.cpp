//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Enter_Name.h"
#include "To_DXF.h"
#include "DXF_library.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm4 *Form4;
//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Button1Click(TObject *Sender)
{
if (Form4->Edit1->Text.Length() == 0)
        return;
AnsiString OldName = Form2->StringGrid1->Cells[PACKAGES][Form2->StringGrid1->Row];
AnsiString RN;
int Cnt = Form2->StringGrid1->RowCount-1;
while( Form2->StringGrid1->Cells[PACKAGES][Cnt].Length() == 0 )
        Cnt--;
Cnt++;
int shift = 0;
for (int r=0; r<Cnt; r++)
        {
        RN = Form2->StringGrid1->Cells[PACKAGES][r];
        if (OldName.SubString(1,OldName.Length()) == RN.SubString(1,RN.Length()))
                {
                Form2->StringGrid1->RowCount++;
                for (int q=0; q<COL_COUNT; q++)
                        Form2->StringGrid1->Cells[q][Form2->StringGrid1->RowCount-1] = "";
                Form2->StringGrid1->Cells[PACKAGES][Cnt+shift] = Form4->Edit1->Text;
                for (int q=1; q<COL_COUNT; q++)
                        Form2->StringGrid1->Cells[q][Cnt+shift] = Form2->StringGrid1->Cells[q][r];
                shift++;
                }
        }
ShiftSizeRectsArrow(Form2->StringGrid1->RowCount,shift);
Form4->Visible = false;
Form2->StringGrid1->Row = Form2->StringGrid1->RowCount - 1;
}
//---------------------------------------------------------------------------
 