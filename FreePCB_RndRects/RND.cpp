//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "RND.h"
#include "fstream.h"
#include "clipbrd.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
double D;
double F;
double X_NEW[32];
double Y_NEW[32];
char s[2500];
AnsiString A;
AnsiString B;
AnsiString S;
long i;
long prob ;
void Ex (void);
long PROB (AnsiString ANSI , long Pr);
double ex_float (AnsiString Str, long *index);
void Save_Checked (void);
void Read_Checked (void);
void Read_Parts (void);
AnsiString ex_str (AnsiString ANSI, long *n);










//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
DecimalSeparator = ',';
Form1->PartList->Sorted = true;
Form1->PartList->MultiSelect = true;
Form1->ListBox1_pins->Visible = false;
Form1->ListBox1_pins->Sorted = false;
Form1->ListBox2_Shape->Visible = false;
Form1->ListBox3_PinsOfNet->Visible = false;
Ex();
}






//---------------------------------------------------------------------------
//----------------Execute OpenDialog1----------------------------------------
//---------------------------------------------------------------------------
void Ex (void)
{
Form1->Timer1->Enabled = false;
Form1->PartList->Clear();
AnsiString CLPBRD = Clipboard()->AsText;
Clipboard()->Clear();
if (CLPBRD.SubString(1,6) == "ObjMan")
        {
        i = PROB(CLPBRD, 1);
        Form1->OpenDialog1->FileName = ex_str(CLPBRD, &i) ;
        CLPBRD = ExtractFileName (Form1->OpenDialog1->FileName);
        Form1->Caption = "Rounding Rect for " + CLPBRD;
        }
else if (Form1->OpenDialog1->Execute())
        {
        if (Form1->OpenDialog1->FileName.Length() == 0) return;
        A = Form1->OpenDialog1->FileName;
        if (A.UpperCase().SubString((A.Length()-3),4) != ".FPC")return;
        }
else exit(0);
Form1->ValuePadsRadiusConstant->Items->Add("0");
for (float add=0.01; add<10.01; add = add)
        {
        Form1->ValuePadsRadiusConstant->Items->Add(FormatFloat("0.000",add/10));
        Form1->ValueTraceRadiusConstant->Items->Add(FormatFloat("0.000",add));
        Form1->ValueAreaRadiusConstant->Items->Add(FormatFloat("0.000",add));
        Form1->ValueMinLengthTrace->Items->Add(FormatFloat("0.000",add));
        Form1->ValueMinLengthArea->Items->Add(FormatFloat("0.000",add));
        Form1->ValueLengthPads->Items->Add(FormatFloat("0.000",add));
        Form1->LengthVia->Items->Add(FormatFloat("0.000",add));
        Form1->DiaVia->Items->Add(FormatFloat("0.000",add));
        if (add < 0.2)          add = add + 0.01;
        else if (add < 1.99)    add = add + 0.05;
        else if (add < 4.99)    add = add + 0.1;
        else                    add = add + 0.25;
        }
for (int add = 2; add<=20; add++)
        {
        Form1->ValueAreaRadiusShare->Items->Add(AnsiString(add));
        Form1->ValueTraceRadiusShare->Items->Add(AnsiString(add));
        Form1->ValuePadsRadiusShare->Items->Add(AnsiString(add));
        }
for (float add = 0.1; add<1.201; add = add + 0.1)
        {
        Form1->ValueTraceRadiusShareW->Items->Add(FormatFloat("0.000",add));
        }
Form1->ValueTraceRadiusConstant->ItemIndex = 0;
Form1->ValueAreaRadiusConstant->ItemIndex = 0;
Form1->ValuePadsRadiusConstant->ItemIndex = 0;
Form1->ValueTraceRadiusShareW->ItemIndex = 0;
Form1->ValueTraceRadiusShare->ItemIndex = 0;
Form1->ValuePadsRadiusShare->ItemIndex = 0;
Form1->ValueAreaRadiusShare->ItemIndex = 0;
Form1->ValueMinLengthTrace->ItemIndex = 0;
Form1->ValueMinLengthArea->ItemIndex = 0;
Form1->ValueLengthPads->ItemIndex = 0;
Form1->LengthVia->ItemIndex = 0;
Form1->DiaVia->ItemIndex = 0;
Read_Parts();
Read_Checked ();
Form1->Timer1->Enabled = true;
}







//--------------------------------------------------------
//********************* BUTTON "..." *********************
//--------------------------------------------------------
//----------------BUTTON OK--------------------------------------------------
//---------------------------------------------------------------------------
//----------------TIMER------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
if (Form1->EnableOvalVia->Checked)
   {
   Form1->Label7->Enabled = true;
   Form1->Label8->Enabled = true;
   Form1->Label9->Enabled = true;
   Form1->Label10->Enabled = true;
   Form1->DiaVia->Enabled = true;
   Form1->LengthVia->Enabled = true;
   Form1->NewStyle->Enabled = true;
   }
else
   {
   Form1->Label7->Enabled = false;
   Form1->Label8->Enabled = false;
   Form1->Label9->Enabled = false;
   Form1->Label10->Enabled = false;
   Form1->DiaVia->Enabled = false;
   Form1->LengthVia->Enabled = false;
   Form1->NewStyle->Enabled = false;
   }
if (Form1->EnableRndArea->Checked)
   {
    Form1->AreaRadiusConstant->Enabled = true;
    Form1->ValueAreaRadiusConstant->Enabled = true;
    Form1->AreaRadiusShare->Enabled = true;
    Form1->ValueAreaRadiusShare->Enabled = true;
    Form1->MinLengthArea->Enabled = true;
    Form1->ValueMinLengthArea->Enabled = true;
    Form1->Area2->Enabled = true;
    Form1->Area3->Enabled = true;
    Form1->Area4->Enabled = true;
    Form1->Area5->Enabled = true;
    Form1->RndContour->Enabled = true;
    Form1->RndCutouts->Enabled = true;
    Form1->forNone->Enabled = true;
    Form1->forFull->Enabled = true;
    Form1->forEdge->Enabled = true;
   }
else
   {
    Form1->AreaRadiusConstant->Enabled = false;
    Form1->ValueAreaRadiusConstant->Enabled = false;
    Form1->AreaRadiusShare->Enabled = false;
    Form1->ValueAreaRadiusShare->Enabled = false;
    Form1->MinLengthArea->Enabled = false;
    Form1->ValueMinLengthArea->Enabled = false;
    Form1->Area2->Enabled = false;
    Form1->Area3->Enabled = false;
    Form1->Area4->Enabled = false;
    Form1->Area5->Enabled = false;
    Form1->RndContour->Enabled = false;
    Form1->RndCutouts->Enabled = false;
    Form1->RndContour->Checked = false;
    Form1->RndCutouts->Checked = false;
    Form1->forNone->Enabled = false;
    Form1->forFull->Enabled = false;
    Form1->forEdge->Enabled = false;
   }
if (Form1->EnableRndTrace->Checked)
   {
    Form1->TraceRadiusConstant->Enabled = true;
    Form1->ValueTraceRadiusConstant->Enabled = true;
    Form1->TraceRadiusShare->Enabled = true;
    Form1->TraceRadiusShareW->Enabled = true;
    Form1->ValueTraceRadiusShare->Enabled = true;
    Form1->ValueTraceRadiusShareW->Enabled = true;
    Form1->MinimumLengthTrace->Enabled = true;
    Form1->ValueMinLengthTrace->Enabled = true;
    Form1->TraceSame2->Enabled = true;
    Form1->TraceSame3->Enabled = true;
    Form1->TraceSame4->Enabled = true;
    Form1->TraceSame5->Enabled = true;
    Form1->TracesOfParts->Enabled = true;
    if(Form1->TracesOfParts->Checked)
        Form1->PartList->Enabled = true;
    Form1->WRangeMin->Enabled = true;
    Form1->WRangeMax->Enabled = true;
    Form1->AutoCorrRad->Enabled = true;
    Form1->AutoCorrWid->Enabled = true;
    Form1->Label1->Enabled = true;
    Form1->WAngmin->Enabled = true;
    Form1->WAngmax->Enabled = true;
   }
else
   {
    Form1->TraceRadiusConstant->Enabled = false;
    Form1->ValueTraceRadiusConstant->Enabled = false;
    Form1->TraceRadiusShare->Enabled = false;
    Form1->TraceRadiusShareW->Enabled = false;
    Form1->ValueTraceRadiusShare->Enabled = false;
    Form1->ValueTraceRadiusShareW->Enabled = false;
    Form1->MinimumLengthTrace->Enabled = false;
    Form1->ValueMinLengthTrace->Enabled = false;
    Form1->TraceSame2->Enabled = false;
    Form1->TraceSame3->Enabled = false;
    Form1->TraceSame4->Enabled = false;
    Form1->TraceSame5->Enabled = false;
    Form1->TracesOfParts->Enabled = false;
    Form1->PartList->Enabled = false;
    Form1->WRangeMin->Enabled = false;
    Form1->WRangeMax->Enabled = false;
    Form1->AutoCorrRad->Enabled = false;
    Form1->AutoCorrWid->Enabled = false;
    Form1->Label1->Enabled = false;
    Form1->WAngmin->Enabled = false;
    Form1->WAngmax->Enabled = false;
   }
if (Form1->EnableRndPads->Checked)
   {
    Form1->RectPads->Enabled = true;
    Form1->RndRectPads->Enabled = true;
    if (Form1->RectPads->Checked)
        {
        Form1->PadsRadiusConstant->Enabled = false;
        Form1->ValuePadsRadiusConstant->Enabled = false;
        Form1->PadsRadiusShare->Enabled = false;
        Form1->ValuePadsRadiusShare->Enabled = false;
        Form1->OnlyR->Checked = false;
        Form1->OnlyR->Enabled = false;
        }
    else
        {
        Form1->PadsRadiusConstant->Enabled = true;
        Form1->ValuePadsRadiusConstant->Enabled = true;
        Form1->PadsRadiusShare->Enabled = true;
        Form1->ValuePadsRadiusShare->Enabled = true;
        Form1->OnlyR->Enabled = true;
        }
   }
else
   {
    Form1->RectPads->Enabled = false;
    Form1->RndRectPads->Enabled = false;
    Form1->ValuePadsRadiusConstant->Enabled = false;
    Form1->PadsRadiusConstant->Enabled = false;
    Form1->PadsRadiusShare->Enabled = false;
    Form1->ValuePadsRadiusShare->Enabled = false;
    Form1->OnlyR->Enabled = false;
   }
if (Form1->EnableOvalPads->Checked)
   {
   Form1->LengthPads->Enabled = true;
   Form1->ValueLengthPads->Enabled = true;
   Form1->Label6->Enabled = true;
   Form1->RoundedPads->Enabled = true;
   //Form1->RectanglePads->Enabled = true;
   }
else
   {
   Form1->LengthPads->Enabled = false;
   Form1->ValueLengthPads->Enabled = false;
   Form1->Label6->Enabled = false;
   Form1->RoundedPads->Enabled = false;
   Form1->RectanglePads->Enabled = false;
   }
}



//------------------------------------------------------
//******************* Save_Checked *********************
//------------------------------------------------------
void Save_Checked (void)
{
A = ExtractFilePath (Application->ExeName);
A = A + "RND_checked.txt";
ofstream Save (A.c_str());
Save << "RND_checked" << endl;
if (Form1->EnableRndPads->Checked)              Save << "*" << endl;    // 0
else                                            Save << endl;
if (Form1->EnableRndTrace->Checked)             Save << "*" << endl;    // 1
else                                            Save << endl;
if (Form1->EnableRndArea->Checked)              Save << "*" << endl;    // 2
else                                            Save << endl;
if (Form1->EnableOvalVia->Checked)              Save << "*" << endl;    // 3
else                                            Save << endl;
if (Form1->EnableOvalPads->Checked)             Save << "*" << endl;    // 4
else                                            Save << endl;
if (Form1->ReplaceOrFile->Checked)              Save << "*" << endl;    // 5
else                                            Save << endl;
if (Form1->PadsRadiusConstant->Checked)         Save << "*" << endl;    // 6
else                                            Save << endl;
if (Form1->PadsRadiusShare->Checked)            Save << "*" << endl;    // 7
else                                            Save << endl;
if (Form1->RectPads->Checked)                   Save << "*" << endl;    // 8
else                                            Save << endl;
if (Form1->RndRectPads->Checked)                Save << "*" << endl;    // 9
else                                            Save << endl;
if (Form1->OnlyR->Checked)                      Save << "*" << endl;    // 10
else                                            Save << endl;
if (Form1->TraceRadiusConstant->Checked)        Save << "*" << endl;    // 11
else                                            Save << endl;
if (Form1->TraceRadiusShare->Checked)           Save << "*" << endl;    // 12
else                                            Save << endl;
if (Form1->TraceRadiusShareW->Checked)          Save << "*" << endl;    // 13
else                                            Save << endl;
if (Form1->TraceSame2->Checked)                 Save << "*" << endl;    // 14
else                                            Save << endl;
if (Form1->TraceSame3->Checked)                 Save << "*" << endl;    // 15
else                                            Save << endl;
if (Form1->TraceSame4->Checked)                 Save << "*" << endl;    // 16
else                                            Save << endl;
if (Form1->TraceSame5->Checked)                 Save << "*" << endl;    // 17
else                                            Save << endl;
if (Form1->AutoCorrRad->Checked)                Save << "*" << endl;    // 18
else                                            Save << endl;
if (Form1->AutoCorrWid->Checked)                Save << "*" << endl;    // 19
else                                            Save << endl;
if (Form1->AreaRadiusConstant->Checked)         Save << "*" << endl;    // 20
else                                            Save << endl;
if (Form1->AreaRadiusShare->Checked)            Save << "*" << endl;    // 21
else                                            Save << endl;
if (Form1->Area2->Checked)                      Save << "*" << endl;    // 22
else                                            Save << endl;
if (Form1->Area3->Checked)                      Save << "*" << endl;    // 23
else                                            Save << endl;
if (Form1->Area4->Checked)                      Save << "*" << endl;    // 24
else                                            Save << endl;
if (Form1->Area5->Checked)                      Save << "*" << endl;    // 25
else                                            Save << endl;
if (Form1->RndContour->Checked)                 Save << "*" << endl;    // 26
else                                            Save << endl;
if (Form1->RndCutouts->Checked)                 Save << "*" << endl;    // 27
else                                            Save << endl;
if (Form1->forNone->Checked)                    Save << "*" << endl;    // 28
else                                            Save << endl;
if (Form1->forFull->Checked)                    Save << "*" << endl;    // 29
else                                            Save << endl;
if (Form1->forEdge->Checked)                    Save << "*" << endl;    // 30
else                                            Save << endl;
if (Form1->NewStyle->Checked)                   Save << "*" << endl;    // 31
else                                            Save << endl;
if (Form1->RoundedPads->Checked)                Save << "*" << endl;    // 32
else                                            Save << endl;
if (Form1->RectanglePads->Checked)              Save << "*" << endl;    // 33
else                                            Save << endl;
// ComboBoxes
for (int b=0; b<Form1->ValuePadsRadiusConstant->ItemIndex; b++) Save << "*";    // 34
Save << endl;
for (int b=0; b<Form1->ValuePadsRadiusShare->ItemIndex; b++) Save << "*";       // 35
Save << endl;
for (int b=0; b<Form1->ValueTraceRadiusConstant->ItemIndex; b++) Save << "*";   // 36
Save << endl;
for (int b=0; b<Form1->ValueTraceRadiusShare->ItemIndex; b++) Save << "*";      // 37
Save << endl;
for (int b=0; b<Form1->ValueTraceRadiusShareW->ItemIndex; b++) Save << "*";     // 38
Save << endl;
for (int b=0; b<Form1->ValueMinLengthTrace->ItemIndex; b++) Save << "*";        // 39
Save << endl;
for (int b=0; b<Form1->ValueAreaRadiusConstant->ItemIndex; b++) Save << "*";    // 40
Save << endl;
for (int b=0; b<Form1->ValueAreaRadiusShare->ItemIndex; b++) Save << "*";       // 41
Save << endl;
for (int b=0; b<Form1->ValueMinLengthArea->ItemIndex; b++) Save << "*";         // 42
Save << endl;
for (int b=0; b<Form1->DiaVia->ItemIndex; b++) Save << "*";                     // 43
Save << endl;
for (int b=0; b<Form1->LengthVia->ItemIndex; b++) Save << "*";                  // 44
Save << endl;
for (int b=0; b<Form1->ValueLengthPads->ItemIndex; b++) Save << "*";            // 45
Save << endl;
for (int b=0; b<Form1->Control->TabIndex; b++) Save << "*";                     // 46
Save << endl;
//add 30-3-2016
if (Form1->TracesOfParts->Checked)              Save << "*" << endl;            // 47
else                                            Save << endl;
Save << Form1->WRangeMin->Text.c_str() << endl;                                 // 48
Save << Form1->WRangeMax->Text.c_str() << endl;                                 // 49
Save << Form1->WAngmin->Text.c_str() << endl;                                   // 50
Save << Form1->WAngmax->Text.c_str() << endl;                                   // 51
for (int z=0; z<Form1->PartList->Count; z++)
        {
        if (Form1->PartList->Selected[z]) Save << Form1->PartList->Items->operator [](z).c_str() << endl;
        }
Save << "eof" << endl;
Save.close();
}




//------------------------------------------------------
//******************* READ_Checked *********************
//------------------------------------------------------
void Read_Checked (void)
{
A = ExtractFilePath (Application->ExeName);
A = A + "RND_checked.txt";
ifstream Checked (A.c_str());
Checked.getline(s,sizeof(s));
A = s;
if (A.SubString(1,11) == "RND_checked")
for (int a=0; !Checked.eof(); a++)
        {
        Checked.getline(s,sizeof(s));
        A = s;
        if( A.SubString(1,3) == "eof" )
                break;
        switch (a)
                {
                // CheckBoxes
                case 0: Form1->EnableRndPads->Checked =         (bool)A.Length();break;
                case 1: Form1->EnableRndTrace->Checked =        (bool)A.Length();break;
                case 2: Form1->EnableRndArea->Checked =         (bool)A.Length();break;
                case 3: Form1->EnableOvalVia->Checked =         (bool)A.Length();break;
                case 4: Form1->EnableOvalPads->Checked =        (bool)A.Length();break;
                case 5: Form1->ReplaceOrFile->Checked =         (bool)A.Length();break;
                case 6: Form1->PadsRadiusConstant->Checked =    (bool)A.Length();break;
                case 7: Form1->PadsRadiusShare->Checked =       (bool)A.Length();break;
                case 8: Form1->RectPads->Checked =              (bool)A.Length();break;
                case 9: Form1->RndRectPads->Checked =           (bool)A.Length();break;
                case 10: Form1->OnlyR->Checked =                (bool)A.Length();break;
                case 11: Form1->TraceRadiusConstant->Checked =  (bool)A.Length();break;
                case 12: Form1->TraceRadiusShare->Checked =     (bool)A.Length();break;
                case 13: Form1->TraceRadiusShareW->Checked =    (bool)A.Length();break;
                case 14: Form1->TraceSame2->Checked =           (bool)A.Length();break;
                case 15: Form1->TraceSame3->Checked =           (bool)A.Length();break;
                case 16: Form1->TraceSame4->Checked =           (bool)A.Length();break;
                case 17: Form1->TraceSame5->Checked =           (bool)A.Length();break;
                case 18: Form1-> AutoCorrRad->Checked =         (bool)A.Length();break;
                case 19: Form1-> AutoCorrWid->Checked =         (bool)A.Length();break;
                case 20: Form1->AreaRadiusConstant->Checked =   (bool)A.Length();break;
                case 21: Form1->AreaRadiusShare->Checked =      (bool)A.Length();break;
                case 22: Form1->Area2->Checked =                (bool)A.Length();break;
                case 23: Form1->Area3->Checked =                (bool)A.Length();break;
                case 24: Form1->Area4->Checked =                (bool)A.Length();break;
                case 25: Form1->Area5->Checked =                (bool)A.Length();break;
                case 26: Form1->RndContour->Checked =           (bool)A.Length();break;
                case 27: Form1->RndCutouts->Checked =           (bool)A.Length();break;
                case 28: Form1->forNone->Checked =              (bool)A.Length();break;
                case 29: Form1->forFull->Checked =              (bool)A.Length();break;
                case 30: Form1->forEdge->Checked =              (bool)A.Length();break;
                case 31: Form1->NewStyle->Checked =             (bool)A.Length();break;
                case 32: Form1->RoundedPads->Checked =          (bool)A.Length();break;
                //case 33: Form1->RectanglePads->Checked =        (bool)A.Length();break;
                // ComboBoxes
                case 34: Form1->ValuePadsRadiusConstant->ItemIndex =    A.Length();break;
                case 35: Form1->ValuePadsRadiusShare->ItemIndex =       A.Length();break;
                case 36: Form1->ValueTraceRadiusConstant->ItemIndex =   A.Length();break;
                case 37: Form1->ValueTraceRadiusShare->ItemIndex =      A.Length();break;
                case 38: Form1->ValueTraceRadiusShareW->ItemIndex =     A.Length();break;
                case 39: Form1->ValueMinLengthTrace->ItemIndex =        A.Length();break;
                case 40: Form1->ValueAreaRadiusConstant->ItemIndex =    A.Length();break;
                case 41: Form1->ValueAreaRadiusShare->ItemIndex =       A.Length();break;
                case 42: Form1->ValueMinLengthArea->ItemIndex =         A.Length();break;
                case 43: Form1->DiaVia->ItemIndex =                     A.Length();break;
                case 44: Form1->LengthVia->ItemIndex =                  A.Length();break;
                case 45: Form1->ValueLengthPads->ItemIndex =            A.Length();break;
                case 46: Form1->Control->TabIndex =                     A.Length();break;
                //news
                case 47: Form1->TracesOfParts->Checked =                (bool)A.Length();break;
                case 48: Form1->WRangeMin->Text =                       A;break;
                case 49: Form1->WRangeMax->Text =                       A;break;
                case 50: Form1->WAngmin->Text =                         A;break;
                case 51: Form1->WAngmax->Text =                         A;break;
                default: i = Form1->PartList->Items->IndexOf(A);
                         if (i >= 0) Form1->PartList->Selected[i] = true;
                         break;
                }
        }
Form1->ReplaceOrFile->Checked = false;
Form1->Control->ActivePageIndex = Form1->Control->TabIndex;
Application->ProcessMessages();
Checked.close();
}




void Read_Parts (void)
        {
        ifstream R (Form1->OpenDialog1->FileName.c_str());
        while ( A.SubString(1,5) != "[end]" )
                {
                R.getline (s, sizeof(s)) ;
                A = s;
                A = A.Trim();
                if(A.SubString(1,5) == "part:")
                        {
                        i = PROB(A, 1);
                        if (i>=0) Form1->PartList->Items->Add(A.SubString(i,(A.Length()-i+1)));
                        }
                }
        }
void __fastcall TForm1::TracesOfPartsClick(TObject *Sender)
{
if(Form1->TracesOfParts->Checked)
        Form1->PartList->Enabled = true;
else
        Form1->PartList->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
for (int p=0; p<Form1->PartList->Count; p++)
if (Form1->PartList->Selected[p]) Form1->PartList->Selected[p] = false;
else                              Form1->PartList->Selected[p] = true;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Label2Click(TObject *Sender)
{
ShellExecute(NULL, "open", "https://github.com/Duxah/FreePCB-2/blob/master/README.md", NULL, NULL, SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------




void __fastcall TForm1::UploadAnotherFileClick(TObject *Sender)
{
Form1->PartList->Sorted = true;
Form1->PartList->MultiSelect = true;
Form1->ListBox1_pins->Visible = false;
Form1->ListBox1_pins->Sorted = false;
Form1->ListBox2_Shape->Visible = false;
Form1->ListBox3_PinsOfNet->Visible = false;
//
Form1->PartList->Clear();
Form1->ListBox1_pins->Clear();
Form1->ListBox2_Shape->Clear();
Form1->ListBox3_PinsOfNet->Clear();
Ex();        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ToTryClick(TObject *Sender)
{
Form1->Timer1->Enabled = false;
Form1->ToTry->Enabled = false;
Form1->UploadAnotherFile->Enabled = false;
Save_Checked ();
RoundingRect();
Application->ProcessMessages();
Sleep(500);
//-------------запуск ------------
B = ExtractFilePath(Application->ExeName);
if (Form1->ReplaceOrFile->Checked)      B = Form1->OpenDialog1->FileName;
else                                    B = B + "RoundingRect.fpc";
A = ExtractFileName(B.c_str());
//
SHELLEXECUTEINFO info = {0};
AnsiString fn = ExtractFilePath(Application->ExeName);
fn.SetLength(fn.Length()-1);
fn = ExtractFilePath(fn);
fn.SetLength(fn.Length()-1);
fn = ExtractFilePath(fn) + "freepcb.exe";
AnsiString FN = ("\""+fn+"\"");
AnsiString ps = B;
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
        ShowMessage("Something went wrong .. If the problem persists more than once, report it to support at freepcb.dev");

//
if(Form1->ReplaceOrFile->Checked)
        exit(0);
Form1->ToTry->Enabled = true;
Form1->UploadAnotherFile->Enabled = true;
Form1->Timer1->Enabled = true;        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image2MouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
if( Form1->ToTry->Font->Size != 20 )
        {
        Form1->ToTry->Font->Size = 20;
        Form1->ToTry->Left += 5;
        Form1->ToTry->Top += 2; 
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ToTryMouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
if( Form1->ToTry->Font->Size == 20 )
        {
        Form1->ToTry->Font->Size = 24;
        Form1->ToTry->Left -= 5;
        Form1->ToTry->Top -= 2;
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ReplaceOrFileClick(TObject *Sender)
{
if( ReplaceOrFile->Checked )
        ToTry->Caption = "Replace";
else    ToTry->Caption = "To try..";
}
//---------------------------------------------------------------------------

