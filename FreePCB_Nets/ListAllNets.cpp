//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ListAllNets.h"
#include "LoadingNets.h"
#include "Editing.h"
#include "fstream.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
//Form2->Visible = false;
Form2->FormStyle = fsStayOnTop;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FormClose(TObject *Sender, TCloseAction &Action)
{
exit(0);        
}
//---------------------------------------------------------------------------
void __fastcall TForm2::ListBox1Click(TObject *Sender)
{
AnsiString FName = ExtractFileName (Form1->OpenDialog1->FileName);
if (!Form1->OpenDialog1->FileName.Length())             return;
if (!Form2->ListBox1->Count)                            return;
if (FName.SubString(1,FName.Length()) == "Nets.fpc")    return;
Form1->ListBox1->Items->Clear();
Form3->OLD->Items->Clear();
Form3->Indexes->Items->Clear();
Form3->OLD->Sorted = true;
Form3->Indexes->Sorted = false;
AnsiString NET = Form2->ListBox1->Items->operator [](Form2->ListBox1->ItemIndex);
ifstream ReadPins (Form1->OpenDialog1->FileName.c_str());
AnsiString A;
EN_net = 0;
n_str = 0;
char s[2500];
while (A.SubString(1,7) != "[board]" )
        {
        ReadPins.getline(s,sizeof(s));
        A = s;
        A = A.Trim();
        n_str++;
        }
int Label__1;
int Label__2;
while (A.SubString(1,7) != "[texts]" )
        {
        ReadPins.getline(s,sizeof(s));
        A = s;
        A = A.Trim();
        n_str++;
        if (A.SubString(1,6) == "[nets]")  Label__1 = n_str;
        if (A.SubString(1,3) == "net")
                {
                if (EN_net) break;
                long i = prob(A,1);
                A = ex_str(A, &i);
                if (A.SubString(1,A.Length()) == NET.SubString(1,NET.Length())) EN_net = n_str;
                }
        if (A.SubString(1,3) == "pin" && EN_net)
                {
                long n = prob(A,1);
                int INDEX = ex_float(A, &n);
                n = prob(A,2);
                AnsiString P = A.SubString(n,(A.Length()-n+1)) ;
                Form3->OLD->Items->Add(P);
                Form3->Indexes->Items->Add(INDEX);
                Form3->Indexes->Items->Add(P);
                long m = A.Length();
                while (A.SubString(m,1) != "." ) m--;
                AnsiString part = A.SubString(n,(m-n));
                if (Form1->ListBox1->Items->IndexOf(part) == -1) Form1->ListBox1->Items->Add(part);
                }
        }
M = n_str - Label__1;
ReadPins.close();
if (Form2->CheckBox5->Checked)
        {
        Form3->Visible = true;
        return;
        }
AnsiString OUTPUT = ExtractFilePath (Application->ExeName);
OUTPUT = OUTPUT + "Nets.fpc";
ofstream W (OUTPUT.c_str());
ifstream R (Form1->OpenDialog1->FileName.c_str());
A = "";
n_str = 0;
bool EN_part = false;
int UNI = 0;
while (!R.eof())
        {
        R.getline(s,sizeof(s));
        A = s;
        A = A.Trim();
        n_str++;
        if (A.SubString(1,9) == "[options]" )   EN_part = true;
        if (A.SubString(1,5) == "units" )
                {
                long i = prob(A,1);
                if (A.LowerCase().SubString(i,2) == "mm" )  UNI = 2;
                if (A.LowerCase().SubString(i,2) == "nm" )  UNI = 1;
                if (A.LowerCase().SubString(i,2) == "mi" )  UNI = 0;
                }
        if (A.SubString(1,7) == "top_pad" || A.SubString(1,10) == "bottom_pad" || A.SubString(1,9) == "inner_pad")
                {
                long i = prob(A,1);
                long m = prob(A,3);
                if (Form2->CheckBox3->Checked)
                        {
                        if (UNI == 0) A = A.SubString(1,(i-1)) + "1 10 " + A.SubString(m,(A.Length()-m+1));
                        if (UNI == 1) A = A.SubString(1,(i-1)) + "1 254000 " + A.SubString(m,(A.Length()-m+1));
                        if (UNI == 2) A = A.SubString(1,(i-1)) + "1 0.254 " + A.SubString(m,(A.Length()-m+1));
                        }
                }
        if (A.SubString(1,16) == "outline_polyline")
                {
                long i = prob(A,1);
                long m = prob(A,2);
                A = A.SubString(1,(i-1)) + "0 " + A.SubString(m,(A.Length()-m+1));
                if (Form2->CheckBox4->Checked)
                while
                (A.SubString(1,7) == "outline" || A.SubString(1,4) == "next" || A.SubString(1,5) == "close" )
                        {
                        R.getline(s,sizeof(s));
                        A = s;
                        A = A.Trim();
                        n_str++;
                        }
                }
        if (    A.SubString(1,7) == "[solder" ||
                A.SubString(1,6) == "[nets]" ||
                A.SubString(1,7) == "[texts]" ||
                A.SubString(1,5) == "[end]" )
                {
                EN_part = false;
                W << A.c_str() << endl;
                }
        if (    A.SubString(1,8) == "[merges]" )
                {
                EN_part = true;
                }
        if (A.SubString(1,7) == "[parts]" )     W << "[parts]" << endl;
        if (A.SubString(1,5) == "part:" )
                {
                long i = prob(A,1);
                AnsiString Part = A.SubString(i,(A.Length()-i+1));
                if (Form1->ListBox1->Items->IndexOf(Part) >= 0) EN_part = true;
                else                                            EN_part = false;
                }
        if (A.SubString(1,8) == "ref_text" )
                {
                long i = prob(A,6);
                int vis;
                if (Form2->CheckBox1->Checked)  vis = 0;
                else                            vis = 1;
                if (i) A = A.SubString(1,(i-1)) + vis;
                else A = A + " " + vis;
                }
        if (A.SubString(1,5) == "value" )
                {
                long i = prob(A,7);
                int vis;
                if (Form2->CheckBox2->Checked)  vis = 0;
                else                            vis = 1;
                if (i) A = A.SubString(1,(i-1)) + vis;
                else A = A + " " + vis;
                }
        if (A.SubString(1,3) == "net" && n_str > EN_net) EN_net = 999999999;
        if (n_str >= EN_net || EN_part) W << A.c_str() << endl;
        }
R.close();
W.close();
Application->ProcessMessages();
Sleep(500);
A = ExtractFilePath (Application->ExeName);
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
AnsiString ps = OUTPUT;
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
}
//---------------------------------------------------------------------------

void __fastcall TForm2::OnWMCopyData(TWMCopyData &Msg)
{
    const AnsiString mes = (char*)Msg.CopyDataStruct->lpData;
    Form2->ListBox1->Clear();
    INI( mes );
}

