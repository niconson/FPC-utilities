//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "NC.h"
#include "Comp_man.h"
#include "fstream.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;
AnsiString FileName2;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
        : TForm(Owner)
{
Form3->NC->Sorted = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm3::Button2Click(TObject *Sender)
{
Form3->Visible = false;
AnsiString file = ExtractFileName (FileName2);
AnsiString NameFPC;
if (file.SubString(1,file.Length()) == "NC.fpc" )       NameFPC = "NC2.fpc";
else                                                    NameFPC = "NC.fpc";
B = ExtractFilePath (Application->ExeName);
B = B + NameFPC;
A = ExtractFilePath(B);
if ((UINT)ShellExecute(NULL,
               "open",
               B.c_str(),
               NULL,
               A.c_str() ,
               SW_SHOWNORMAL) <=32)
               {
                 ShowMessage  ("     File " + B + " not found!");
                 return;
               }
}
//---------------------------------------------------------------------------
void __fastcall TForm3::Button1Click(TObject *Sender)
{
B = ExtractFilePath (Application->ExeName);
B = B + "NC.txt";
A = ExtractFilePath(B);
if ((UINT)ShellExecute(NULL,
               "open",
               B.c_str(),
               NULL,
               A.c_str() ,
               SW_SHOWNORMAL) <=32)
               {
                 ShowMessage  ("     File " + B + " not found!");
                 return;
               }
Form3->Visible = false;
}
//---------------------------------------------------------------------------




//---------------------------
//******** LOAD_NC **********
//---------------------------

void LOAD_NC (AnsiString Foot)
{
if (Foot.Length() == 0) return;
Form1->Label14->Caption = "No connected of " + Foot;
Application->ProcessMessages();
ifstream NC (FileName2.c_str());
AnsiString STR;
AnsiString ParT;
AnsiString Shape;
AnsiString PiN;
long in;
long CnT;
while (STR.SubString(1,7) != "[parts]")
        {
        NC.getline(s,sizeof(s));
        STR = s;
        STR = STR.Trim();
        }
while (1)
        {
        NC.getline(s,sizeof(s));
        STR = s;
        STR = STR.Trim();
        if (STR.SubString(1,7) == "[texts]") break;
        if (STR.SubString(1,5) == "[end]")   break;
        if (STR.SubString(1,5) == "part:")
                {
                in = prob (STR, 1);
                ParT = STR.SubString(in, (STR.Length()-in+1));
                }
        else if (STR.SubString(1,6) == "shape:")
                {
                in = prob (STR, 1);
                Shape = ex_str(STR, &in);
                if (Shape.SubString(1,(Shape.Length())) == Foot.SubString(1,(Foot.Length())))
                        {
                        CnT = 0;
                        while (CnT < Form1->PINS_BOX->Items->Count)
                                {
                                AnsiString ADD = ParT + "." + Form1->PINS_BOX->Items->operator [](CnT);
                                Form3->NC->Items->Add(ADD);
                                CnT++;
                                }
                        }
                }
        else if (STR.SubString(1,4) == "pin:")
                {
                in = prob (STR, 2);
                PiN = STR.SubString(in,(STR.Length()-in+1));
                CnT = 0;
                while ((i = Form3->NC->Items->IndexOf(PiN)) >= 0)
                        {
                        Form3->NC->Items->Delete(i);
                        }
                }
        }
NC.close();
Form1->PINS_BOX->Items->Clear();
}


//---------------------------
//******** NC_prog **********
//---------------------------
void NC_prog (AnsiString FName)
{
if (FName.SubString((FName.Length()-2),3).UpperCase() != "FPC") return;
FileName2 = FName;
if (!CountStringsFoot) return;
Form1->Timer1->Enabled = false;
Form3->NC->Items->Clear();
long LG = 0;
long indx = 0;
AnsiString FTPR = "";
while (LG < CountStringsFoot)
        {
        if (FootPrints [LG].SubString(1,4) == "name")
                {
                LOAD_NC (FTPR);
                indx = prob(FootPrints [LG],1);
                FTPR = ex_str (FootPrints [LG], &indx);
                Form1->PINS_BOX->Items->Clear();
                }
        else if (FootPrints [LG].SubString(1,3) == "pin")
                {
                indx = prob(FootPrints [LG],1);
                AnsiString NamePin = ex_str(FootPrints [LG], &indx);
                Form1->PINS_BOX->Items->Add(NamePin);
                }
        LG++;
        }
LOAD_NC ( FTPR);
Flag_NC_Prog = true;
Form1->Timer1->Enabled = true;
}


