//---------------------------------------------------------------------------


#pragma hdrstop

#include "SortedParts.h"
#include "Comp_man.h"
#include "Path_EXE.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
static bool DIRECT=1;
//static int svCase=-1;
static int svTI=1;
//---------------------------------------------------------------------------
int DataPartsIndexOf(AnsiString DT)
        {
        int in = StrToInt(DT);
        return (in-1)*(PartsColCount+1);
        }

//---------------------------------------------------------------------------
int DataPinsIndexOf(AnsiString DT)
        {
        int in = StrToInt(DT);
        return (in-1)*(PinsColCount+1);
        }

//---------------------------------------------------------------------------
void SortedParts (int CASE)
{
int Pos;
AnsiString Str1;
AnsiString Str2;
if (CASE == SORT_CASE && Form1->PageControl1->TabIndex == svTI)
        {
        if (DIRECT)
                DIRECT = false;
        else
                DIRECT = true;
        }
if (CASE <= 0)
        CASE = SORT_CASE;
if (CASE<=0)
        return;
SORT_CASE = CASE;
if (Form2->Language->Checked)
        Form1->Caption = "Ожидайте...";
else
        Form1->Caption = "Please wait...";
Application->ProcessMessages();
Form1->SortedBox->Items->Clear();
Form1->SortedBox->Sorted = true;
TListBox * buf =new TListBox(Form1);
buf->Parent=(TWinControl *)Form1;
buf->Top=0;
buf->Left=0;
buf->Height=MIN_FORM_H;//FORM_MIN_HEIGHT;
buf->Width=MIN_FORM_W;//FORM_MIN_HEIGHT;
buf->Visible=false;
buf->Sorted=false;
Application->ProcessMessages();
int NewPos=1;
if (Form1->PageControl1->TabIndex == 0)
        {
        for (int k=0; k<Form1->DataParts->Items->Count; k=k+PartsColCount+1)
                {
                Str1 = Form1->DataParts->Items->operator [](k+CASE);
                Str2 = Form1->DataParts->Items->operator [](k);
                if (CASE == 1)
                        {
                        Pos = Str1.Length();
                        int ps = -1;
                        for (int h=1; h<=Pos; h++)
                                if (Str1.SubString(h,1) <= '9' && Str1.SubString(h,1) >= '0')
                                        {
                                        ps = h;
                                        break;
                                        }
                        if (ps >= 0)
                                for (int h=0; h<3-Pos+ps; h++) Str1.Insert("0",ps);
                        }
                Form1->SortedBox->Items->Add(Str1 + "#" + Str2);
                }
        for (int k=0;k<Form1->SortedBox->Items->Count; k++)
                {
                if (DIRECT)
                        Str1 = Form1->SortedBox->Items->operator [](k);
                else    Str1 = Form1->SortedBox->Items->operator [](Form1->SortedBox->Items->Count-k-1);
                Pos = Str1.Pos("#");
                Pos = DataPartsIndexOf(Str1.SubString((Pos+1),(Str1.Length()-Pos)));
                if (Pos < 0)
                        return;
                buf->Items->Add(NewPos);
                NewPos++;
                for (int ii=0; ii<PartsColCount; ii++)
                        buf->Items->Add(Form1->DataParts->Items->operator [](Pos+ii+1));
                }
        Form1->DataParts->Items->Clear();
        for (int k=0;k<buf->Items->Count; k++)
                Form1->DataParts->Items->Add(buf->Items->operator [](k));
        }
else if (Form1->PageControl1->TabIndex == 1)
        {
        for (int k=0; k<Form1->DataPins->Items->Count; k=k+PinsColCount+1)
                {
                Str1 = Form1->DataPins->Items->operator [](k+CASE);
                Str2 = Form1->DataPins->Items->operator [](k);
                if (CASE == 1)
                        {
                        Pos = Str1.Pos(".");
                        for (int h=(Str1.Length() - Pos); h<3; h++)
                                Str1.Insert("0",(Pos+1));
                        int ps = -1;
                        for (int h=1; h<Pos; h++)
                                if (Str1.SubString(h,1) <= '9' && Str1.SubString(h,1) >= '0')
                                        {
                                        ps = h;
                                        break;
                                        }
                        if (ps >= 0)
                                for (int h=0; h<3-Pos+ps; h++) Str1.Insert("0",ps);
                        }
                Form1->SortedBox->Items->Add(Str1 + "#" + Str2);
                }
        for (int k=0; k<Form1->SortedBox->Items->Count; k++)
                {
                if (DIRECT)
                        Str1 = Form1->SortedBox->Items->operator [](k);
                else    Str1 = Form1->SortedBox->Items->operator [](Form1->SortedBox->Items->Count-k-1);
                Pos = Str1.Pos("#");
                Str1 = Str1.SubString((Pos+1),(Str1.Length()-Pos));
                Pos = DataPinsIndexOf(Str1);
                if (Pos < 0)
                        return;
                buf->Items->Add(NewPos);
                NewPos++;
                for (int ii=0; ii<PinsColCount; ii++)
                        buf->Items->Add(Form1->DataPins->Items->operator [](Pos+ii+1));
                }
        Form1->DataPins->Items->Clear();
        for (int k=0;k<buf->Items->Count; k++)
                Form1->DataPins->Items->Add(buf->Items->operator [](k));
        }
Form1->SortedBox->Items->Clear();
delete buf;
if (Form2->Language->Checked)   Form1->Caption = "Сортировка успешно завершена.";
else                            Form1->Caption = "Sorted successfully.";
//if (CASE > 0)
//        svCase = CASE;
svTI = Form1->PageControl1->TabIndex;
Application->ProcessMessages();
FilterAll();
}



