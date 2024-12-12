//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "IR.h"
#include "fstream.h"
#include "clipbrd.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
AnsiString A;
AnsiString REPORT;
float SHIFT;
float XPOS;
float YPOS;
float HEIGHT;
float WIDTH;







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
void LoadFile (void)
{
Form1->ListBox1->Items->Clear();
A = Form1->Edit1->Text;
SHIFT =         StrToFloat(Str_Float_Format(A));
if ((SHIFT > 30)||(SHIFT < 0))
        {
        ShowMessage ("    'Shift for tables' value must be < 30mm.");
        SHIFT = 30;
        }





ifstream Load (REPORT.c_str());
A = "";
char s[2501];
int Shift = 0;
AnsiString S;
while (A.SubString(1,3) != "end" )
        {
        Load.getline(s,2500);
        s[199] = '\0';
        A = s;
        A = A.Trim();
        int Len = A.Length();
        S = "";
        Form1->ListBox1->Items->Add("0");
        for (int k=1; k<=Len; k++)
                {
                if (A.SubString(k,2) != "  ")
                        {
                        if (A.SubString(k,1) != "\"")S = S + A.SubString(k,1);
                        }
                else    {
                        while (A.SubString(k,1) == " ")k++;
                        k--;
                        Shift = Shift+ SHIFT;
                        Form1->ListBox1->Items->Add(S);
                        Form1->ListBox1->Items->Add(AnsiString(Shift));
                        S = "";
                        }
                }
        Form1->ListBox1->Items->Add(S);
        Shift = 0;
        }
Load.close();
}









//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
DecimalSeparator = ',';
A = Clipboard()->AsText;
if (A.SubString(1,6) == "ObjMan")
        {
        long i = prob (A, 1);
        OpenDialog1->FileName = ex_str(A, &i) ;
        A = ExtractFilePath (OpenDialog1->FileName);
        }
else if (Form1->OpenDialog1->Execute())
        {
        if (Form1->OpenDialog1->FileName.Length() == 0) return;
        A = Form1->OpenDialog1->FileName;
        if (A.UpperCase().SubString((A.Length()-3),4) != ".FPC")
                {
                ShowMessage ("   Error format!");
                exit(0);
                }
        }
else exit(0);
REPORT = ExtractFilePath (OpenDialog1->FileName);
REPORT = REPORT + "report.txt";


FILE* F;
F = fopen(REPORT.c_str(),"rb+");
if(F == NULL)
        {
        ShowMessage ("   Pcb-report file not found!");
        exit(0);
        }
fclose(F);
ofstream AddEnd ;
AddEnd.open(REPORT.c_str(), std::ios_base::app );
AddEnd << endl;
AddEnd << "end";
AddEnd.close();
LoadFile();
}








//---------------------------------------------------------------------------

void __fastcall TForm1::Edit1Change(TObject *Sender)
{
LoadFile();
}







//---------------------------------------------------------------------------


void __fastcall TForm1::Button1Click(TObject *Sender)
{
A = Form1->Edit2->Text;
XPOS =          StrToFloat(Str_Float_Format(A));
A = Form1->Edit3->Text;
YPOS =          StrToFloat(Str_Float_Format(A));
A = Form1->Edit4->Text;
HEIGHT =        StrToFloat(Str_Float_Format(A));
A = Form1->Edit5->Text;
WIDTH =         StrToFloat(Str_Float_Format(A));
if ((XPOS > 500)||(XPOS < -500))
        {
        ShowMessage ("    'XPOS' value must be < 500mm.");
        XPOS = 500;
        }
if ((YPOS > 500)||(YPOS < -500))
        {
        ShowMessage ("    'YPOS' value must be < 500mm.");
        YPOS = 500;
        }
if ((HEIGHT > 10))
        {
        ShowMessage ("    'HEIGHT' value must be < 10mm.");
        HEIGHT = 10;
        }







ifstream Loading (Form1->OpenDialog1->FileName.c_str());
A = "";
char s[2501];
while (A.SubString(1,5) != "[end]")
        {
        Loading.getline(s,2500);
        A = s;
        A = A.Trim();
        Form1->ListBox2->Items->Add(A);
        }
Form1->ListBox2->Items->Add("Insert Report for PCB");
Loading.close();


int index = 0;
ofstream Wr (Form1->OpenDialog1->FileName.c_str());
while (A.SubString(1,7) != "[texts]")
        {
        A = Form1->ListBox2->Items->operator [](index);
        Wr << A.c_str() << endl;
        index++;
        }



long X = XPOS;
long Y = YPOS;
for (int k=0; k<Form1->ListBox1->Items->Count; k++)
        {
        if (k%2 == 0)
                {
                A = Form1->ListBox1->Items->operator [](k);
                X = XPOS + StrToInt(A);
                if (A.SubString(1,1) == "0") Y = Y - HEIGHT*2;
                }
        else    {
                A = Form1->ListBox1->Items->operator [](k);
                AnsiString WR = "text: \"";
                WR += A;
                WR += "\" ";
                WR += AnsiString(X*1000000);
                WR += " ";
                WR += AnsiString(Y*1000000);
                WR += " 10 0 0 ";
                WR += AnsiString((long)(HEIGHT*1000000));
                WR += " ";
                WR += AnsiString((long)(WIDTH*1000000));
                Wr << WR.c_str() << endl;
                }
        }




while (A.SubString(1,5) != "[end]")
        {
        A = Form1->ListBox2->Items->operator [](index);
        Wr << A.c_str() << endl;
        index++;
        }
Wr.close();



//-------------запуск ------------
AnsiString B = Form1->OpenDialog1->FileName;
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
        ShowMessage("Something went wrong .. If the problem persists more than once, report it to support at freepcb2");

exit(0);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Label6Click(TObject *Sender)
{
ShellExecute(NULL, "open", "https://github.com/niconson", NULL, NULL, SW_SHOWNORMAL);         
}
//---------------------------------------------------------------------------

