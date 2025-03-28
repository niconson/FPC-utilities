//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AddIndex.h"
#include "ABClibrary.h"
#include "Please_wait.h"
#include "fstream.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
Form2->Label2->Enabled = 0;
Form2->Label3->Enabled = 0;
Form2->GroupBox4->Enabled = 0;
Form2->InBegin->Enabled = 0;
Form2->InEnd->Enabled = 0;
//
Form2->Label1->Enabled = 1;
Form2->GroupBox3->Enabled = 1;
Form2->RadioButtonBegin->Enabled = 1;
Form2->RadioButtonEnd->Enabled = 1;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::OK_ADD_STRClick(TObject *Sender)
{
if (gLocked)
        return;
gLocked = true;
AnsiString InF = FileName;
AnsiString OutF;
if (FileName.SubString((FileName.Length()-11),12) == "AddIndex.fpc" )   OutF = ExtractFilePath(Application->ExeName) + "AddIndex2.fpc";
else                                                                    OutF = ExtractFilePath(Application->ExeName) + "AddIndex.fpc";
ifstream R (InF.c_str());
ofstream W (OutF.c_str());
AnsiString Strng = Form2->Edit1->Text;
AnsiString OldStrng = Form2->Edit2->Text;
AnsiString NewStrng = Form2->Edit3->Text;
int LStrng = Strng.Length();
char s[2501];
bool NetsFlag = false;
A = "";
while (A.SubString(1,5) != "[end]")
        {
        R.getline(s,2500);
        A = s;
        A = A.Trim();
        if (A.SubString(1,6) == "[nets]" )     NetsFlag = true;
        if ((A.SubString(1,5) == "name:" )&&(Form2->RadioButtonShape->Checked))
                {
                long In = 6;
                AnsiString Name = ex_str(A,&In);
                int LName = Name.Length();
                if (Form2->AddStr->Checked)
                        {
                        if (Form2->RadioButtonBegin->Checked)   Name = Strng + Name;
                        if (Form2->RadioButtonEnd->Checked)     Name = Name + Strng;
                        }
                else if (Form2->DelStr->Checked)
                        {
                        if (Form2->RadioButtonBegin->Checked &&
                            Strng.SubString(1,LStrng) == Name.SubString(1,LStrng))
                                Name = Name.SubString((LStrng+1),(LName-LStrng));
                        if (Form2->RadioButtonEnd->Checked &&
                            Strng.SubString(1,LStrng) == Name.SubString(LName-LStrng+1,LStrng))
                                Name = Name.SubString(1,(LName-LStrng));
                        }
                else    {
                        AnsiString key = "";
                        AnsiString oldkey = "";
                        AnsiString cstr = Name;
                        int pos = cstr.Pos(OldStrng);
                        int ol = OldStrng.Length();
                        int nl = NewStrng.Length();
                        int Disable = 0;
                        for( int step=0; pos > 0; step++ )
                                {
                                if( InBegin->Checked && (pos > 1 || step) )
                                        break;
                                if( InEnd->Checked && pos < cstr.Length()-ol+1 )
                                        Disable = 1;
                                oldkey += cstr.SubString(1,pos+ol-1);
                                cstr.Delete(pos,ol);
                                cstr.Insert(NewStrng,pos);
                                key += cstr.SubString(1,pos+nl-1);
                                int cl = cstr.Length();
                                if( pos+nl > cl )
                                        cstr = "";
                                else
                                        cstr = cstr.SubString(pos+nl,cl-pos-nl+1);
                                pos = cstr.Pos(OldStrng);
                                if( Disable )
                                        key = oldkey;
                                else
                                        Name = key + cstr;
                                Disable = 0;
                                }
                        }
                Name = "name: \"" + Name + "\"";
                W << Name.c_str() << endl;
                }
        else if ((A.SubString(1,6) == "shape:" )&&(Form2->RadioButtonShape->Checked))
                {
                long In = 7;
                AnsiString Shape = ex_str(A,&In);
                int LShape = Shape.Length();
                if (Form2->AddStr->Checked)
                        {
                        if (Form2->RadioButtonBegin->Checked)   Shape = Strng + Shape;
                        if (Form2->RadioButtonEnd->Checked)     Shape = Shape + Strng;
                        }
                else if (Form2->DelStr->Checked)
                        {
                        if (Form2->RadioButtonBegin->Checked &&
                            Strng.SubString(1,LStrng) == Shape.SubString(1,LStrng))
                                Shape = Shape.SubString((LStrng+1),(LShape-LStrng));
                        if (Form2->RadioButtonEnd->Checked &&
                            Strng.SubString(1,LStrng) == Shape.SubString(LShape-LStrng+1,LStrng))
                                Shape = Shape.SubString(1,(LShape-LStrng));
                        }
                else    {
                        AnsiString key = "";
                        AnsiString oldkey = "";
                        AnsiString cstr = Shape;
                        int pos = cstr.Pos(OldStrng);
                        int ol = OldStrng.Length();
                        int nl = NewStrng.Length();
                        int Disable = 0;
                        for( int step=0; pos > 0; step++ )
                                {
                                if( InBegin->Checked && (pos > 1 || step) )
                                        break;
                                if( InEnd->Checked && pos < cstr.Length()-ol+1 )
                                        Disable = 1;
                                oldkey += cstr.SubString(1,pos+ol-1);
                                cstr.Delete(pos,ol);
                                cstr.Insert(NewStrng,pos);
                                key += cstr.SubString(1,pos+nl-1);
                                int cl = cstr.Length();
                                if( pos+nl > cl )
                                        cstr = "";
                                else
                                        cstr = cstr.SubString(pos+nl,cl-pos-nl+1);
                                pos = cstr.Pos(OldStrng);
                                if( Disable )
                                        key = oldkey;
                                else
                                        Shape = key + cstr;
                                Disable = 0;
                                }
                        }
                Shape = "shape: \"" + Shape + "\"";
                W << Shape.c_str() << endl;
                }
        else if ((A.SubString(1,5) == "part:" )&&(Form2->RadioButtonRef->Checked))
                {
                int pr = prob(A,1);
                AnsiString Part = A.SubString(pr,(A.Length()-pr+1));
                int LPart = Part.Length();
                if (Form2->AddStr->Checked)
                        {
                        if (Form2->RadioButtonBegin->Checked)   Part = Strng + Part;
                        if (Form2->RadioButtonEnd->Checked)     Part = Part + Strng;
                        }
                else if (Form2->DelStr->Checked)
                        {
                        if (Form2->RadioButtonBegin->Checked &&
                            Strng.SubString(1,LStrng) == Part.SubString(1,LStrng))
                                Part = Part.SubString((LStrng+1),(LPart-LStrng));
                        if (Form2->RadioButtonEnd->Checked &&
                            Strng.SubString(1,LStrng) == Part.SubString(LPart-LStrng+1,LStrng))
                                Part = Part.SubString(1,(LPart-LStrng));
                        }
                else    {
                        AnsiString key = "";
                        AnsiString oldkey = "";
                        AnsiString cstr = Part;
                        int pos = cstr.Pos(OldStrng);
                        int ol = OldStrng.Length();
                        int nl = NewStrng.Length();
                        int Disable = 0;
                        for( int step=0; pos > 0; step++ )
                                {
                                if( InBegin->Checked && (pos > 1 || step) )
                                        break;
                                if( InEnd->Checked && pos < cstr.Length()-ol+1 )
                                        Disable = 1;
                                oldkey += cstr.SubString(1,pos+ol-1);
                                cstr.Delete(pos,ol);
                                cstr.Insert(NewStrng,pos);
                                key += cstr.SubString(1,pos+nl-1);
                                int cl = cstr.Length();
                                if( pos+nl > cl )
                                        cstr = "";
                                else
                                        cstr = cstr.SubString(pos+nl,cl-pos-nl+1);
                                pos = cstr.Pos(OldStrng);
                                if( Disable )
                                        key = oldkey;
                                else
                                        Part = key + cstr;
                                Disable = 0;
                                }
                        }
                Part = "part: " + Part;
                W << Part.c_str() << endl;
                }
        else if ((A.SubString(1,4) == "pin:" )&&(Form2->RadioButtonRef->Checked)&&(NetsFlag))
                {
                int pr = prob(A,2) ;
                int IndexPoint = A.Length();
                while (IndexPoint > 0)
                        {
                        if (A.SubString(IndexPoint,1) == ".") break;
                        IndexPoint--;
                        }
                AnsiString Pin = A;
                if (IndexPoint > 0)
                        {
                        Pin = A.SubString(pr,(IndexPoint - pr)) ;
                        int LPin = Pin.Length();
                        if (Form2->AddStr->Checked)
                                {
                                if (Form2->RadioButtonBegin->Checked)   Pin = Strng + Pin;
                                if (Form2->RadioButtonEnd->Checked)     Pin = Pin + Strng;
                                }
                        else if (Form2->DelStr->Checked)
                                {
                                if (Form2->RadioButtonBegin->Checked &&
                                    Strng.SubString(1,LStrng) == Pin.SubString(1,LStrng))
                                        Pin = Pin.SubString((LStrng+1),(LPin-LStrng));
                                if (Form2->RadioButtonEnd->Checked &&
                                    Strng.SubString(1,LStrng) == Pin.SubString(LPin-LStrng+1,LStrng))
                                        Pin = Pin.SubString(1,(LPin-LStrng));
                                }
                        else    {
                                AnsiString key = "";
                                AnsiString oldkey = "";
                                AnsiString cstr = Pin;
                                int pos = cstr.Pos(OldStrng);
                                int nl = NewStrng.Length();
                                int ol = OldStrng.Length();
                                int Disable = 0;
                                for( int step=0; pos > 0; step++ )
                                        {
                                        if( InBegin->Checked && (pos > 1 || step) )
                                                break;
                                        if( InEnd->Checked && pos < cstr.Length()-ol+1 )
                                                Disable = 1;
                                        oldkey += cstr.SubString(1,pos+ol-1);
                                        cstr.Delete(pos,ol);
                                        cstr.Insert(NewStrng,pos);
                                        key += cstr.SubString(1,pos+nl-1);
                                        int cl = cstr.Length();
                                        if( pos+nl > cl )
                                                cstr = "";
                                        else
                                                cstr = cstr.SubString(pos+nl,cl-pos-nl+1);
                                        pos = cstr.Pos(OldStrng);
                                        if( Disable )
                                                key = oldkey;
                                        else
                                                Pin = key + cstr;
                                        Disable = 0;
                                        }
                                }
                        Pin = A.SubString(1,(pr-1)) + Pin + A.SubString(IndexPoint,(A.Length()-IndexPoint+1));
                        }
                W << Pin.c_str() << endl;
                }
        else    W << A.c_str() << endl;
        }
R.close();
W.close();
if (Form2->ReplaceOrigFile->Checked)
        {
        ifstream r  (OutF.c_str());
        ofstream wr (FileName.c_str());
        while (!r.eof() )
                {
                r.getline(s,2500);
                wr << s << endl;
                }
        OutF = FileName;
        r.close();
        wr.close();
        }
Application->ProcessMessages();
Sleep(500);
//--------������ ------------
AnsiString fn = ExtractFilePath(Application->ExeName);
AnsiString B = OutF;
//
SHELLEXECUTEINFO info = {0};
fn.SetLength(fn.Length()-1);
fn = ExtractFilePath(fn);
fn.SetLength(fn.Length()-1);
fn = ExtractFilePath(fn) + "freepcb.exe";

// RUS
if( FileExists(fn) == 0 )
        fn = ExtractFilePath(fn) + "��������.exe";

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
gLocked = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::AddStrClick(TObject *Sender)
{
Form2->Label2->Enabled = 0;
Form2->Label3->Enabled = 0;
Form2->GroupBox4->Enabled = 0;
Form2->InBegin->Enabled = 0;
Form2->InEnd->Enabled = 0;
//
Form2->Label1->Enabled = 1;
Form2->GroupBox3->Enabled = 1;
Form2->RadioButtonBegin->Enabled = 1;
Form2->RadioButtonEnd->Enabled = 1;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::ReplaceStrClick(TObject *Sender)
{
Form2->Label2->Enabled = 1;
Form2->Label3->Enabled = 1;
Form2->GroupBox4->Enabled = 1;
Form2->InBegin->Enabled = 1;
Form2->InEnd->Enabled = 1;
//
Form2->Label1->Enabled = 0;
Form2->GroupBox3->Enabled = 0;
Form2->RadioButtonBegin->Enabled = 0;
Form2->RadioButtonEnd->Enabled = 0;
}
//---------------------------------------------------------------------------

