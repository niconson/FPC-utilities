//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "LoadingNets.h"
#include "ListAllNets.h"
#include "fstream.h"
#include "clipbrd.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
int M;
int EN_net;
int n_str;
long prob (AnsiString ANSI , long Pr);
AnsiString ex_str (AnsiString ANSI, long *n);
void INI(AnsiString CLPBRD);
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
DecimalSeparator = ',';
INI("");
}
//---------------------------------------------------------------------------

void INI(AnsiString CLPBRD)
{
Form1->Timer1->Enabled = false;
Form1->ListBox1->Sorted = false;
Form1->ListBox1->MultiSelect = true;
Form1->ListBox1->Visible = false;
Form1->ListBox1->Clear();
while (Form1->OpenDialog1->FileName.Length() == 0)
        {
        Form1->Visible = false;
        if (!CLPBRD.Length())
                {
                Clipboard()->Open();
                CLPBRD = Clipboard()->AsText;
                Clipboard()->Clear();
                Clipboard()->Close();
                }
        if (CLPBRD.SubString(1,6) == "ObjMan")
                {
                long i = prob(CLPBRD, 1);
                Form1->OpenDialog1->FileName = ex_str(CLPBRD, &i) ;
                }
        //else if (Form1->OpenDialog1->Execute()){;}
        else exit(0);
        if (Form1->OpenDialog1->FileName.LowerCase().SubString((Form1->OpenDialog1->FileName.Length()-2),3) != "fpc") Form1->OpenDialog1->FileName = "";
        }
AnsiString FileName = ExtractFileName(Form1->OpenDialog1->FileName);
Form1->Caption = "Nets of " + FileName;
Form1->Position = poScreenCenter;
Form1->Visible = true;
Form1->FormStyle = fsStayOnTop;
Application->ProcessMessages();
long i = 0;
char s[2500];
AnsiString A = "";
ifstream R (Form1->OpenDialog1->FileName.c_str());
while (!R.eof())
        {
        R.getline(s,sizeof(s));
        A = s;
        A = A.Trim();
        if (A.SubString(1,4) == "net:")
                {
                i = prob(A,1);
                AnsiString Net = ex_str(A, &i);
                Form1->ListBox1->Items->Add(Net);
                }
        }
R.close();
Form1->Timer1->Interval = 500;
Form1->Timer1->Enabled = true;
}










//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
Form1->Timer1->Enabled = false;
Form1->ListBox1->SelectAll();
Form1->ListBox1->CopySelection(Form2->ListBox1);
Form2->Position = poScreenCenter;
Form1->Visible = false;
Form2->Visible = true;
Form2->Left = Form2->Left*2;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer2Timer(TObject *Sender)
{
if(FindWindow(NULL,"Log") == 0)
        exit(0);
}
//---------------------------------------------------------------------------

