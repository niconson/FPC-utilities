//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "RPL.h"
#include "fstream.h"
#include "clipbrd.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
long i;
AnsiString A;
int units;
int UNITS;
//---------------------------------------------------------------------------
#define LAY_TOP_COPPER          15
#define LAY_BOTTOM_COPPER       16
#define LAY_INNER_COPPER        17






//---------------------------------------------------------------------------
long PROB (AnsiString ANSI , long Pr)
{
long ind = 0;
while (Pr)
        {
        ind++;
        if (ind > ANSI.Length()) return 0;
        if (ANSI.SubString(ind,1) == "\"")
                {
                ind++;
                while (ANSI.SubString(ind,1) != "\"")
                        {
                        ind++;
                        if (ind > ANSI.Length()) return 0;
                        }
                }
        if (ANSI.SubString(ind,1) == " ")
                {
                Pr--;
                while (ANSI.SubString(ind,1) == " ")
                        {
                        ind++;
                        if (ind > ANSI.Length()) return 0;
                        }
                ind--;
                }
        }
while (ANSI.SubString(ind,1) == " ") ind++;
return ind;
}
//---------------------------------------------------------------------------









//---------------------------------------------------------------------------
AnsiString ex_str (AnsiString ANSI, long *n)
{
  while (ANSI.SubString((*n),1) != "\"") {(*n)++; if ((*n) > ANSI.Length()) return "";}
  (*n)++;
  AnsiString A = "";
  while (ANSI.SubString((*n),1) != "\"")
        {
         A = A + ANSI.SubString(*n,1);
         (*n)++;
         if ((*n) > ANSI.Length()) return "Error_func_ex_str";
        }
  (*n)++;
  return A;
}
//---------------------------------------------------------------------------










//---------------------------------------------------------------------------
float ex_float_NM (AnsiString Str, long *index, int units)
{
if ((*index) == 0)              *index = 1;
if ((*index) > Str.Length())    return 0;
AnsiString Q = "";
///int current_units_mm = units;
while ((Str.SubString(*index,1) < "0")||(Str.SubString(*index,1) > "9"))
        {
        if ((*index) >= Str.Length()) return 0;
        if (Str.SubString(*index,1) == "-") Q = Q + Str.SubString(*index,1);
        if (Str.SubString(*index,1) == "+") Q = Q + Str.SubString(*index,1);
        (*index)++;
        }
while ((Str.SubString(*index,1) >= "0")&&(Str.SubString(*index,1) <= "9"))
        {
        if ((*index) > Str.Length()) return 0;
        Q = Q + Str.SubString(*index,1);
        (*index)++;
        if ((Str.SubString(*index,1) == ".")||(Str.SubString(*index,1) == ","))
                {
                Q = Q + ",";
                (*index)++;
                }
        }
if (!Q.Length()) return 0;
while (Str.SubString((*index),1) == " ") (*index)++;
///if (Str.UpperCase().SubString((*index),2) == "MM" ) {current_units_mm = 1;  *index = (*index)+2; }
///if (Str.UpperCase().SubString((*index),3) == "MIL" ) {current_units_mm = 0; *index = (*index)+3; }
if (Q.SubString(Q.Length(),1) == ",") Q = Q + "0";
float DE = StrToFloat(Q);
//
if (units == 0)         DE = DE*25400;
else if (units == 2)    DE = DE*1000000;
//
return DE;
}
//---------------------------------------------------------------------------











//---------------------------------------------------------------------------
AnsiString Str_Float_Format (AnsiString STRING_2_DOUBLE)
{
STRING_2_DOUBLE = StringReplace(STRING_2_DOUBLE,".",",",TReplaceFlags()<<rfReplaceAll);
int L = STRING_2_DOUBLE.Length();
bool F = false;
for (int x=1; x<=L; x++)
        {
        if (STRING_2_DOUBLE.SubString(1,1) == "-") continue;
        if ((STRING_2_DOUBLE.SubString(x,1) < "0") || (STRING_2_DOUBLE.SubString(x,1) > "9"))
        if  (F) {
                STRING_2_DOUBLE = STRING_2_DOUBLE.SubString(1,(x-1));
                break;
                }
        else    {
                F = true;
                AnsiString S = STRING_2_DOUBLE.SubString(x,1);
                STRING_2_DOUBLE = StringReplace(STRING_2_DOUBLE,S,",",TReplaceFlags()<<rfReplaceAll);
                }
        }
L = STRING_2_DOUBLE.Length();
if  (((STRING_2_DOUBLE.SubString(L,1) == "-")&&(L<2))||(!L)) STRING_2_DOUBLE = "0";
if  (STRING_2_DOUBLE.SubString(1,1) == ",") STRING_2_DOUBLE = "0" + STRING_2_DOUBLE;
if  (STRING_2_DOUBLE.SubString(L,1) == ",") STRING_2_DOUBLE = STRING_2_DOUBLE + "0";
return STRING_2_DOUBLE;
}
//---------------------------------------------------------------------------









//---------------------------------------------------------------------------
AnsiString F_str (double DBL)
{
 AnsiString STRNG;
 STRNG = FormatFloat("0.0000",DBL);
 STRNG = StringReplace(STRNG,",",".",TReplaceFlags()<<rfReplaceAll);
 STRNG = STRNG.SubString(1,6);
 return STRNG;
}
//---------------------------------------------------------------------------











//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
DecimalSeparator = ',';
AnsiString CLPBRD = Clipboard()->AsText;
Clipboard()->Clear();
if (CLPBRD.SubString(1,6) == "ObjMan")
        {
        i = PROB(CLPBRD, 1);
        Form1->OpenDialog1->FileName = ex_str(CLPBRD, &i) ;
        CLPBRD = ExtractFileName (Form1->OpenDialog1->FileName);
        Form1->Caption = "Replacement in file " + CLPBRD;
        }
else if (Form1->OpenDialog1->Execute())
        {
        if (Form1->OpenDialog1->FileName.Length() == 0) return;
        A = Form1->OpenDialog1->FileName;
        if (A.UpperCase().SubString((A.Length()-3),4) != ".FPC") return;
        }
else exit(0);
//
UNITS = 1;
char s[2501];
bool FOOTPRINT = true;
ifstream R (Form1->OpenDialog1->FileName.c_str());
while (!R.eof())
        {
        R.getline(s,2500);
        A = s;
        A = A.Trim();
        if (A.LowerCase().SubString(1,12) == "[footprints]" )
                FOOTPRINT = false;
        if (A.LowerCase().SubString(1,5) == "units" && FOOTPRINT)
                {
                FOOTPRINT = false;
                i = PROB(A, 1);
                if (A.LowerCase().SubString(i,2) == "mm") UNITS = 2;
                else                                      UNITS = 0;
                Form1->Label4->Caption = A;
                }
        else if( A.LowerCase().SubString(1,12) == "file_version" )
                {
                i = PROB(A, 1);
                float f = ex_float_NM(A,&i,-1);
                if( f < 2.022 )
                        {
                        ShowMessage("  This file cannot be processed because it was created in the previous version of FREEPCB.");
                        exit(0);
                        }
                }
        Form1->ListBox1->Items->Add(A);
        }
R.close();
}
//---------------------------------------------------------------------------











//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
i = 1;
double SegMin_NM = ex_float_NM((Str_Float_Format(Edit1->Text)), &i, UNITS);
i = 1;
double SegMax_NM = ex_float_NM((Str_Float_Format(Edit2->Text)), &i, UNITS);
i = 1;
double SegNew_NM = ex_float_NM((Str_Float_Format(Edit3->Text)), &i, UNITS);
//
i = 1;
double ViaHMin_NM = ex_float_NM((Str_Float_Format(Edit4->Text)), &i, UNITS);
i = 1;
double ViaHMax_NM = ex_float_NM((Str_Float_Format(Edit5->Text)), &i, UNITS);
i = 1;
double ViaHNew_NM = ex_float_NM((Str_Float_Format(Edit6->Text)), &i, UNITS);
//
i = 1;
double PadHMin_NM = ex_float_NM((Str_Float_Format(Edit7->Text)), &i, UNITS);
i = 1;
double PadHMin_MIL = PadHMin_NM/25400;
i = 1;
double PadHMax_NM = ex_float_NM((Str_Float_Format(Edit8->Text)), &i, UNITS);
i = 1;
double PadHMax_MIL = PadHMax_NM/25400;
i = 1;
double PadHNew_NM = ex_float_NM((Str_Float_Format(Edit9->Text)), &i, UNITS);
i = 1;
double PadHNew_MIL = PadHNew_NM/25400;
//
i = 1;
double ViaSMin_NM = ex_float_NM((Str_Float_Format(Edit10->Text)), &i, UNITS);
i = 1;
double ViaSMax_NM = ex_float_NM((Str_Float_Format(Edit11->Text)), &i, UNITS);
i = 1;
double ViaSNew_NM = ex_float_NM((Str_Float_Format(Edit12->Text)), &i, UNITS);
//

ofstream W (Form1->OpenDialog1->FileName.c_str());
units = 1;
bool F = true;
for (int k=0; k<Form1->ListBox1->Count; k++)
        {
        A = Form1->ListBox1->Items->operator [](k);
        if (A.LowerCase().SubString(1,7) == "[board]" ) F = false;
        if (A.LowerCase().SubString(1,5) == "units" )
                {
                i = PROB(A, 1);
                if (A.LowerCase().SubString(i,2) == "mm")       units = 2;
                else if (A.LowerCase().SubString(i,2) == "mi")  units = 0;
                else                                            units = 1;
                }
        if (A.LowerCase().SubString(1,3) == "pin" && F)
                {
                i = PROB(A, 2);
                int m = PROB(A, 3);
                double H = ex_float_NM(A, &i, -1);
                i = PROB(A, 2);
                if (units == 1 && H > PadHMin_NM && H < PadHMax_NM)
                        {
                        A = A.SubString(1,(i-1)) + long(PadHNew_NM) + " " + A.SubString(m,(A.Length()-m+1));
                        }
                else if (units == 0 && H > PadHMin_MIL && H < PadHMax_MIL)
                        {
                        A = A.SubString(1,(i-1)) + F_str(PadHNew_MIL) + " " + A.SubString(m,(A.Length()-m+1));
                        }
                else if (units == 2 && H*1000000 > PadHMin_NM && H*1000000 < PadHMax_NM)
                        {
                        A = A.SubString(1,(i-1)) + F_str(PadHNew_NM/1000000) + " " + A.SubString(m,(A.Length()-m+1));
                        }
                }
        if (A.LowerCase().SubString(1,3) == "seg" && F == 0)
                {
                i = PROB(A, 3);
                int m = PROB(A, 4);
                double seg = ex_float_NM(A, &i, -1);
                i = PROB(A, 3);
                if (seg > SegMin_NM && seg < SegMax_NM)
                        {
                        A = A.SubString(1,(i-1)) + long(SegNew_NM) + " " + A.SubString(m,(A.Length()-m+1));
                        }
                }
        if (A.LowerCase().SubString(1,3) == "vtx" && F == 0)
                {
                i = PROB(A, 6);
                int m = PROB(A, 7);
                double VS = ex_float_NM(A, &i, -1);
                i = PROB(A, 6);
                if (VS > ViaSMin_NM && VS < ViaSMax_NM)
                        {
                        A = A.SubString(1,(i-1)) + long(ViaSNew_NM) + " " + A.SubString(m,(A.Length()-m+1));
                        }
                i = PROB(A, 7);
                m = PROB(A, 8);
                double VH = ex_float_NM(A, &i, -1);
                i = PROB(A, 7);
                if (VH > ViaHMin_NM && VH < ViaHMax_NM)
                        {
                        A = A.SubString(1,(i-1)) + long(ViaHNew_NM) + " " + A.SubString(m,(A.Length()-m+1));
                        }
                }
        if (A.LowerCase().SubString(1,5) == "area:" )
                {
                int newhatch;
                if (Form1->RadioButton4->Checked) newhatch = 0;
                if (Form1->RadioButton5->Checked) newhatch = 1;
                if (Form1->RadioButton6->Checked) newhatch = 2;
                i = PROB(A, 3);
                int m = PROB(A, 4);
                int n = PROB(A, 5);
                int lay = ex_float_NM(A, &i, -1);
                int old = ex_float_NM(A, &i, -1);
                bool En = false;
                if (old == 0 && Form1->CheckBox1->Checked) En = true;
                if (old == 1 && Form1->CheckBox2->Checked) En = true;
                if (old == 2 && Form1->CheckBox3->Checked) En = true;
                if (lay == LAY_TOP_COPPER && !Form1->CheckBox7->Checked)        En = false;
                if (lay == LAY_BOTTOM_COPPER && !Form1->CheckBox8->Checked)     En = false;
                if (lay >= LAY_INNER_COPPER && !Form1->CheckBox9->Checked)      En = false;
                if (En)
                        {
                        AnsiString sA = A;
                        A = sA.SubString(1,(m-1)) + newhatch;
                        if( n > 0 )
                                A += sA.SubString(n-1,sA.Length()-n+2);
                        }
                }
        if (A.LowerCase().SubString(1,10) == "sm_cutout:" )
                {
                int newhatch;
                if (Form1->RadioButton1->Checked) newhatch = 0;
                if (Form1->RadioButton2->Checked) newhatch = 1;
                if (Form1->RadioButton3->Checked) newhatch = 2;
                i = PROB(A, 2);
                int m = PROB(A, 2);
                int old = ex_float_NM(A, &i, -1);
                bool En = false;
                if (old == 0 && Form1->CheckBox4->Checked) En = true;
                if (old == 1 && Form1->CheckBox5->Checked) En = true;
                if (old == 2 && Form1->CheckBox6->Checked) En = true;
                if (En)
                        {
                        AnsiString sA = A;
                        A = sA.SubString(1,(m-1)) + newhatch + sA.SubString((m+1),(sA.Length()-m));
                        }
                }
        W << A.c_str() << endl;
        }
W << A.c_str() << endl;
W.close();
Application->ProcessMessages();
Sleep(500);
//A = ExtractFilePath(Form1->OpenDialog1->FileName);
//-------------------------
//
SHELLEXECUTEINFO info = {0};
AnsiString fn = ExtractFilePath(Application->ExeName);
fn.SetLength(fn.Length()-1);
fn = ExtractFilePath(fn);
fn.SetLength(fn.Length()-1);
fn = ExtractFilePath(fn) + "freepcb.exe";

// RUS
if( FileExists(fn) == 0 )
        fn = ExtractFilePath(fn) + "ПлатФорм.exe";

AnsiString FN = ("\""+fn+"\"");
AnsiString ps = Form1->OpenDialog1->FileName;
AnsiString PS = ("\""+ps+"\"");
info.cbSize = sizeof(SHELLEXECUTEINFO);
info.fMask = NULL;
info.hwnd = NULL;
info.lpVerb = NULL;
info.lpFile = FN.c_str();
info.lpParameters = PS.c_str();
info.lpDirectory = NULL;
info.nShow = SW_SHOW;//SW_MAXIMIZE; //SW_HIDE
info.hInstApp = NULL;
int INF = ShellExecuteEx(&info);
if( INF == 0 )
        ShowMessage("Something went wrong .. If the problem persists more than once, report it to support at freepcb2");
exit(0);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Label16Click(TObject *Sender)
{
ShellExecute(NULL, "open", "https://github.com/niconson", NULL, NULL, SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

