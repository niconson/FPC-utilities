//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Editing.h"
#include "LoadingNets.h"
#include "ListAllNets.h"
#include "fstream.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;
AnsiString * OLDNET;
AnsiString * NEWNET;
int oldnet ;
int newnet ;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm3::Button1Click(TObject *Sender)
{
Form3->OLD->MoveSelection(Form3->NEW);
}
//---------------------------------------------------------------------------
void __fastcall TForm3::Button2Click(TObject *Sender)
{
Form3->NEW->MoveSelection(Form3->OLD);
}
//---------------------------------------------------------------------------
void __fastcall TForm3::Button3Click(TObject *Sender)
{
oldnet = 0;
newnet = 0;
try     {
        OLDNET = new(std::nothrow) AnsiString[M];
        NEWNET = new(std::nothrow) AnsiString[M];
        }
catch(std::bad_alloc)
        {
        ShowMessage("    Error: AnsiString[" + AnsiString(M) + "]!" );
        exit(0);
        }
long i = 0;
char s[2500];
AnsiString A = "";
AnsiString OUTPUT;
if (Form3->CheckBox1->Checked) OUTPUT = ExtractFilePath (Form1->OpenDialog1->FileName);
else                           OUTPUT = ExtractFilePath (Application->ExeName);
OUTPUT = OUTPUT + "Nets.fpc";
if (Form1->OpenDialog1->FileName.SubString(1,Form1->OpenDialog1->FileName.Length()) == OUTPUT.SubString(1,OUTPUT.Length()))
        {
        ShowMessage ("   Error writing output file.\n   " + Form1->OpenDialog1->FileName + " = " + OUTPUT);
        return;
        }
ofstream Wr (OUTPUT.c_str());
ifstream RF (Form1->OpenDialog1->FileName.c_str());
n_str = 0;
while (n_str < EN_net)
        {
        RF.getline(s,sizeof(s));
        A = s;
        A = A.Trim();
        n_str++;
        if (n_str < EN_net) Wr << A.c_str() << endl;
        }
i = prob(A,4);
int C_areas =       ex_float(A,&i);
int W_traces =      ex_float(A,&i);
int D_vias =        ex_float(A,&i);
int H_vias =        ex_float(A,&i);
A = "";
int cnt_new = 0;
int cnt_old = 0;
while (1)
        {
        if (A.SubString(1,7) == "[texts]")      break;
        if (A.SubString(1,3) == "net")          break;
        if (A.SubString(1,7) == "connect")
                {
                i = prob(A,2);
                int in1 =       ex_float(A,&i) + 1;
                int in2 =       ex_float(A,&i) + 1;
                int cnt_seg =   ex_float(A,&i) + 1;
                int Locked =    ex_float(A,&i);
                AnsiString pin1;
                AnsiString pin2;
                i = Form3->Indexes->Items->IndexOf(AnsiString(in1));
                if (i != -1)    pin1 = Form3->Indexes->Items->operator [](i+1);
                else            ShowMessage("  Error of the Editing Mode!" );
                i = Form3->Indexes->Items->IndexOf(AnsiString(in2));
                if (i != -1)    pin2 = Form3->Indexes->Items->operator [](i+1);
                if      (
                        (Form3->OLD->Items->IndexOf(pin1) >= 0 && Form3->NEW->Items->IndexOf(pin2) >= 0) ||
                        (Form3->OLD->Items->IndexOf(pin2) >= 0 && Form3->NEW->Items->IndexOf(pin1) >= 0)
                        )
                        {
                        //Ignore...
                        RF.getline(s,sizeof(s));
                        A = s;
                        A = A.Trim();
                        n_str++;
                        }
                else if (Form3->OLD->Items->IndexOf(pin1) >= 0)
                        {
                        cnt_old++;
                        i = Form3->OLD->Items->IndexOf(pin1);
                        OLDNET[oldnet] = "connect: " + AnsiString(cnt_old) + " " + AnsiString(i) + " ";
                        i = Form3->OLD->Items->IndexOf(pin2);
                        OLDNET[oldnet] += AnsiString(i) + " " + AnsiString(cnt_seg-1) + " " + AnsiString(Locked);
                        oldnet++;
                        int n_seg = 0;
                        while (n_seg < cnt_seg)
                                {
                                RF.getline(s,sizeof(s));
                                A = s;
                                A = A.Trim();
                                n_str++;
                                OLDNET[oldnet] = A;
                                oldnet++;
                                i = prob(A,1);
                                n_seg = ex_float(A,&i);
                                }
                        }
                else if (Form3->NEW->Items->IndexOf(pin1) >= 0)
                        {
                        cnt_new++;
                        i = Form3->NEW->Items->IndexOf(pin1);
                        NEWNET[newnet] = "connect: " + AnsiString(cnt_new) + " " + AnsiString(i) + " ";
                        i = Form3->NEW->Items->IndexOf(pin2);
                        NEWNET[newnet] += AnsiString(i) + " " + AnsiString(cnt_seg-1) + " " + AnsiString(Locked);
                        newnet++;
                        int n_seg = 0;
                        while (n_seg < cnt_seg)
                                {
                                RF.getline(s,sizeof(s));
                                A = s;
                                A = A.Trim();
                                n_str++;
                                NEWNET[newnet] = A;
                                newnet++;
                                i = prob(A,1);
                                n_seg = ex_float(A,&i);
                                }
                        }
                }
        else    {
                RF.getline(s,sizeof(s));
                A = s;
                A = A.Trim();
                n_str++;
                if (A.SubString(1,4) == "area" || A.SubString(1,6) == "corner")
                        {
                        OLDNET[oldnet] = A;
                        oldnet++;
                        }
                }
        }
AnsiString SaveA = A;
i = Form3->OLD->Items->Count;
A = Form2->ListBox1->Items->operator [](Form2->ListBox1->ItemIndex);
Wr << "net: \"";
Wr << A.c_str();
Wr << "\" ";
Wr << AnsiString(i).c_str();
Wr << " ";
Wr << AnsiString(cnt_old).c_str();
Wr << " ";
Wr << AnsiString(C_areas).c_str();
Wr << " ";
Wr << AnsiString(W_traces).c_str();
Wr << " ";
Wr << AnsiString(D_vias).c_str();
Wr << " ";
Wr << AnsiString(H_vias).c_str();
Wr << " 1";
Wr << endl;
for (int k=0; k<Form3->OLD->Items->Count; k++)
        {
        Wr << "pin: ";
        Wr << AnsiString(k+1).c_str();
        Wr << " ";
        A = Form3->OLD->Items->operator [](k);
        Wr << A.c_str() << endl;
        }
for (int k=0; k<oldnet; k++)
        {
        Wr << OLDNET[k].c_str() << endl;
        }
i = Form3->NEW->Items->Count;
Wr << "net: \"newnet_editing_mode\" ";
Wr << AnsiString(i).c_str();
Wr << " ";
Wr << AnsiString(cnt_new).c_str();
Wr << " ";
Wr << AnsiString("0").c_str();
Wr << " ";
Wr << AnsiString(W_traces).c_str();
Wr << " ";
Wr << AnsiString(D_vias).c_str();
Wr << " ";
Wr << AnsiString(H_vias).c_str();
Wr << " 1";
Wr << endl;
for (int k=0; k<Form3->NEW->Items->Count; k++)
        {
        Wr << "pin: ";
        Wr << AnsiString(k+1).c_str();
        Wr << " ";
        A = Form3->NEW->Items->operator [](k);
        Wr << A.c_str() << endl;
        }
for (int k=0; k<newnet; k++)
        {
        Wr << NEWNET[k].c_str() << endl;
        }
Wr << SaveA.c_str() << endl;
while (!RF.eof())
        {
        RF.getline(s,sizeof(s));
        A = s;
        A = A.Trim();
        n_str++;
        Wr << A.c_str() << endl;
        }

RF.close();
Wr.close();
A = ExtractFilePath (Application->ExeName);
if ((UINT)ShellExecute(NULL,
               "open",
               OUTPUT.c_str(),
               NULL,
               A.c_str() ,
               SW_SHOWNORMAL) <=32)
               {
                 ShowMessage  ("     File " + OUTPUT + " not found!");
                 return;
               }
delete OLDNET;
delete NEWNET;
}
//---------------------------------------------------------------------------