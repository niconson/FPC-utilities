//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Nets.h"
#include "Comp_man.h"
#include "fstream.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm5 *Form5;
//---------------------------------------------------------------------------
__fastcall TForm5::TForm5(TComponent* Owner)
        : TForm(Owner)
{
Form5->Nets_LSTBX->Sorted = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm5::Nets_LSTBXClick(TObject *Sender)
{
if (!FileNameBack.Length()) return;
Form5->Visible = false;
Form1->PINS_BOX->Items->Clear();
AnsiString NET = Form5->Nets_LSTBX->Items->operator [](Form5->Nets_LSTBX->ItemIndex);
ifstream Fpc (FileNameBack.c_str());
A = ExtractFilePath (Application->ExeName);
A = A + "Nets.fpc";
ofstream NETS (A.c_str());
while (A.SubString(1,6) != "[nets]" )
        {
        Fpc.getline(s,sizeof(s));
        A = s;
        A = A.Trim();
        NETS << A.c_str() << endl;
        }
while (A.SubString(1,NET.Length()) != NET.SubString(1,NET.Length()) )
        {
        Fpc.getline(s,sizeof(s));
        A = s;
        A = A.Trim();
        }
NETS << A.c_str() << endl;
while (1)
        {
        Fpc.getline(s,sizeof(s));
        A = s;
        A = A.Trim();
        if (A.SubString(1,4) == "pin:" )
                {
                long n = prob(A,2);
                long m = A.Length();
                while (A.SubString(m,1) != "." ) m--;
                AnsiString S = A.SubString(n,(m-n));
                S = "part: " + S;
                Form1->PINS_BOX->Items->Add(S);
                }
        if (A.SubString(1,4) == "net:" )        break;
        if (A.SubString(1,7) == "[texts]" )     break;
        NETS << A.c_str() << endl;
        }
NETS << "[texts]" << endl;
NETS << "[end]" << endl;
NETS.close();
Fpc.close();
Sleep(100);
A = ExtractFilePath (Application->ExeName);
A = A + "Nets.fpc";
ifstream nets_1 (A.c_str());
A = ExtractFilePath (Application->ExeName);
A = A + "Nets2.fpc";
ofstream nets_2 (A.c_str());
bool Flag = false;
A = "";
while (A.SubString(1,7) != "[parts]" )
        {
        nets_1.getline(s,sizeof(s));
        A = s;
        A = A.Trim();
        nets_2 << A.c_str() << endl;
        }
while (1)
        {
        nets_1.getline(s,sizeof(s));
        A = s;
        A = A.Trim();
        if (A.SubString(1,6) == "[nets]" )              break;
        if (A.SubString(1,5) == "part:" )               Flag = false;
        if (Form1->PINS_BOX->Items->IndexOf(A) >= 0)   Flag = true;
        if (Flag) nets_2 << A.c_str() << endl;
        }
nets_2 << A.c_str() << endl;
while (A.SubString(1,5) != "[end]" )
        {
        nets_1.getline(s,sizeof(s));
        A = s;
        A = A.Trim();
        nets_2 << A.c_str() << endl;
        }
nets_1.close();
nets_2.close();
B = ExtractFilePath (Application->ExeName);
B = B + "Nets2.fpc";
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

