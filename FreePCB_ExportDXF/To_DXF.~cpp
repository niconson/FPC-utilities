//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "To_DXF.h"
#include "DXF_library.h"
#include "PolyFace.h"
#include "Options.h"
#include "Logo.h"
#include "fstream.h"
#include "clipbrd.hpp"
#include "math.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
float BoardThick;
float default_mask_clearance = 0;
float default_paste_clearance = 0;
float ABSMIN_X = DEFAULT;
float ABSMIN_Y = DEFAULT;
float ABSMAX_X = -DEFAULT;
float ABSMAX_Y = -DEFAULT;
float BrdRectLeft ;
float BrdRectTop ;
float BrdRectRight ;
float BrdRectBottom ;
float GlobalScaleFactor = 1;
float * FACES = 0;
int CLR = 20;
int IndexFoot = 0;
int IndexParts = 0;
int IndexBoard = 0;
int IndexNets = 0;
int StringGridIndexRow = 0;
int MAX_FACES_AND_LINES;
int GlobalShiftX = 0;
int GlobalShiftY = 0;
int GlobalCurveXY = 0;
int GlobalCurveXZ = 0;
int GlobalCurveYZ = 0;
int StartGCXZ = 0;
int StartGCYZ = 0;
int StartGCXY = 0;
int mouseStartX = 0;
int mouseStartY = 0;
int * LABELS = 0;
int * LINES = 0;
bool CTRL = false;
bool SHIFT = false;
int * MARKS = NULL;
bool CANVAS_TO_FILE = false;



canvas_data_struct * canvas_data = 0;
AnsiString NO_UNITS = "NO_UNITS";
AnsiString NO_PACKAGE = "";
TRect Fill_Rect;
TRect SaveRect;
myRectInt * SizeRects = 0;

//---------------------------------------------------------------------------



void TForm1::Ini()
{
BrdRectLeft =   DEFAULT;
BrdRectTop =    -DEFAULT;
BrdRectRight =  -DEFAULT;
BrdRectBottom = DEFAULT;
long i;
Form1->File->Sorted = 0;
Form1->Blocks->Sorted = 0;
Form1->OutputBox->Sorted = 0;
Form1->NamesOfBlocks->Sorted = 0;
Form1->File->Visible = 0;
Form1->Blocks->Visible = 0;
Form1->OutputBox->Visible = 0;
Form1->NamesOfBlocks->Visible = 0;
AnsiString A;
static AnsiString CLPBRD = Clipboard()->AsText;
Clipboard()->Clear();
while (A.UpperCase().SubString((A.Length()-3),4) != ".FPC")
if (CLPBRD.SubString(1,6) == "ObjMan")
        {
        i = prob(CLPBRD, 1);
        Form1->OpenDialog1->FileName = ex_str(CLPBRD, &i) ;
        A = Form1->OpenDialog1->FileName;
        }
else if (Form1->OpenDialog1->Execute())
        {
        A = Form1->OpenDialog1->FileName;
        CLPBRD = "ObjMan \"" + A + "\"";
        }
else exit(0);
//
Form5->Visible = true;
Application->ProcessMessages();
ifstream R (Form1->OpenDialog1->FileName.c_str());
char s[DEF_CHAR];
IndexFoot = 0;
IndexParts = 0;
IndexNets = 0;
IndexBoard= 0;
Form1->Parts->Items->Clear();
Form1->Nets->Items->Clear();
for (int Str=0; !R.eof(); Str++)
        {
        R.getline(s,DEF_CHAR);
        A = s;
        A = A.TrimLeft();
        Form1->File->Items->Add(A);
        if (A.SubString(1,5) == "part:")
                {
                i = prob(A, 1);
                AnsiString ADD = A.SubString(i,(A.Length()-i+1));
                Form1->Parts->Items->Add(ADD.Trim());
                }
        else if (A.SubString(1,12) == "file_version" )
                {
                i = prob(A, 1);
                float ver = ex_float(A, &i);
                if( ver < 2.022 )
                        {
                        ShowMessage("This file cannot be processed because it was created in the previous version of FREEPCB.");
                        exit(0);
                        }
                }
        else if (A.SubString(1,4) == "net:" )
                {
                i = prob(A, 1);
                AnsiString ADD = ex_str(A,&i);
                Form1->Nets->Items->Add(ADD);
                }
        else if (A.SubString(1,14) == "mask_clearance" )
                {
                i = 2;
                default_mask_clearance = ex_float(A, &i);
                }
        else if (A.SubString(1,17) == "shrink_paste_mask" )
                {
                i = 2;
                default_paste_clearance = ex_float(A, &i);
                }
        else if (A.SubString(1,12) == "[footprints]")
                {
                IndexFoot = Str;
                }
        else if (A.SubString(1,7) == "[parts]")
                {
                IndexParts = Str;
                }
        else if (A.SubString(1,6) == "[nets]")
                {
                IndexNets = Str;
                }
        else if (A.SubString(1,7) == "[board]")
                {
                IndexBoard = Str;
                }
        }
R.close();
if (!LABELS)
        {
        try     {
                LABELS = new(std::nothrow) int[IndexNets];
                }
        catch(std::bad_alloc)
                {
                ShowMessage("Error memory of int[" + AnsiString(Form1->File->Count) + "]!" );
                exit(0);
                }
        }
if (!canvas_data)
        {
        try     {
                canvas_data = new(std::nothrow) canvas_data_struct[IndexParts];
                }
        catch(std::bad_alloc)
                {
                ShowMessage("Error memory of canvas_data_struct[]!" );
                exit(0);
                }
        }
for (int e=0; e<IndexParts; e++)
        {
        canvas_data[e].ini();
        }
//
AnsiString units = "NM";
int lbls=0, Sel_Rect=0, First=0;
long PinX=0,PinY=0;
for (int Str=0; Str < Form1->File->Items->Count; Str++)
        {
        A = Form1->File->Items->operator [](Str);
        if (    A.SubString(1,5) == "part:" ||
                A.SubString(1,6) == "shape:" ||
                A.SubString(1,8) == "package:" ||
                A.SubString(1,7) == "[board]" ||
                A.SubString(1,5) == "name:" ||
                A.SubString(1,6) == "[nets]" )
                {
                LABELS[lbls] = Str;
                lbls++;
                }
        //
        if (Str > IndexBoard)
                continue;
        if (A.SubString(1,5) == "units")
                {
                i = prob(A,1);
                units = A.SubString(i,(A.Length()-i+1));
                }
        else if (A.SubString(1,4) == "name")
                {
                Sel_Rect = Str;
                canvas_data[Sel_Rect].x =   DEFAULT;
                canvas_data[Sel_Rect].y =   DEFAULT;
                canvas_data[Sel_Rect].xn = -DEFAULT;
                canvas_data[Sel_Rect].yn = -DEFAULT;
                }
        else if (A.SubString(1,3) == "pin")
                {
                i = prob(A,2);
                long Hole = ex_float_NM(A, &i, &units);
                PinX = ex_float_NM(A, &i, &units);
                PinY = ex_float_NM(A, &i, &units);
                canvas_data[Sel_Rect].angle =   ex_float_NM(A, &i, &NO_UNITS);
                canvas_data[Sel_Rect].x =  MIN(canvas_data[Sel_Rect].x, (PinX-Hole/2.0));
                canvas_data[Sel_Rect].xn = MAX(canvas_data[Sel_Rect].xn,(PinX+Hole/2.0));
                canvas_data[Sel_Rect].y =  MIN(canvas_data[Sel_Rect].y ,(PinY-Hole/2.0));
                canvas_data[Sel_Rect].yn = MAX(canvas_data[Sel_Rect].yn,(PinY+Hole/2.0));
                canvas_data[Str].x = PinX;
                canvas_data[Str].y = PinY;
                canvas_data[Str].w = Hole;
                canvas_data[Str].type = tp_point;
                canvas_data[Str].lay = lr_drl;
                }
        else if (A.SubString(1,7) == "top_pad" || A.SubString(1,10) == "bottom_pad")
                {
                i = prob(A,1);
                canvas_data[Str].type = ex_float_NM(A, &i, &NO_UNITS);
                long sx = ex_float_NM(A, &i, &units)/2;
                long sy = ex_float_NM(A, &i, &units);
                sy =      ex_float_NM(A, &i, &units);
                if (canvas_data[Str].type == tp_round || canvas_data[Str].type == tp_square)
                        sy = sx;
                canvas_data[Str].w = ex_float_NM(A, &i, &units);    // radius
                long ss = MAX(sx,sy);
                canvas_data[Sel_Rect].x =  MIN(canvas_data[Sel_Rect].x ,(PinX-ss));
                canvas_data[Sel_Rect].xn = MAX(canvas_data[Sel_Rect].xn,(PinX+ss));
                canvas_data[Sel_Rect].y =  MIN(canvas_data[Sel_Rect].y ,(PinY-ss));
                canvas_data[Sel_Rect].yn = MAX(canvas_data[Sel_Rect].yn,(PinY+ss));
                canvas_data[Str].x = PinX;
                canvas_data[Str].y = PinY;
                canvas_data[Str].xn = sx;
                canvas_data[Str].yn = sy;
                canvas_data[Str].angle = canvas_data[Sel_Rect].angle;
                if (A.SubString(1,1) == "t")
                        canvas_data[Str].lay = lr_top;
                else    canvas_data[Str].lay = lr_bottom;
                }
        else if (A.SubString(1,7) == "outline")
                {
                i = prob(A,1);
                canvas_data[Str].w = ex_float_NM(A, &i, &units);
                long x = ex_float_NM(A, &i, &units);
                long y = ex_float_NM(A, &i, &units);
                canvas_data[Sel_Rect].x =  MIN(canvas_data[Sel_Rect].x ,x);
                canvas_data[Sel_Rect].xn = MAX(canvas_data[Sel_Rect].xn,x);
                canvas_data[Sel_Rect].y =  MIN(canvas_data[Sel_Rect].y ,y);
                canvas_data[Sel_Rect].yn = MAX(canvas_data[Sel_Rect].yn,y);
                canvas_data[Str].x = x;
                canvas_data[Str].y = y;
                canvas_data[Str].xn = x;
                canvas_data[Str].yn = y;
                canvas_data[Str].type = tp_line;
                canvas_data[Str].lay = lr_silk;
                First = Str;
                }
        else if (A.SubString(1,4) == "next")
                {
                i = prob(A,1);
                long x = ex_float_NM(A, &i, &units);
                long y = ex_float_NM(A, &i, &units);
                int arc = ex_float_NM(A, &i, &NO_UNITS);
                canvas_data[Sel_Rect].x =  MIN(canvas_data[Sel_Rect].x ,x);
                canvas_data[Sel_Rect].xn = MAX(canvas_data[Sel_Rect].xn,x);
                canvas_data[Sel_Rect].y =  MIN(canvas_data[Sel_Rect].y ,y);
                canvas_data[Sel_Rect].yn = MAX(canvas_data[Sel_Rect].yn,y);
                canvas_data[Str-1].xn = x;
                canvas_data[Str-1].yn = y;
                canvas_data[Str-1].type += arc;
                canvas_data[Str].w = canvas_data[Str-1].w;
                canvas_data[Str].x = x;
                canvas_data[Str].y = y;
                canvas_data[Str].xn = x;
                canvas_data[Str].yn = y;
                canvas_data[Str].type = tp_line;
                canvas_data[Str].lay = lr_silk;
                }
        else if (A.SubString(1,5) == "close")
                {
                i = prob(A,1);
                int arc = ex_float_NM(A, &i, &NO_UNITS);
                canvas_data[Str-1].xn = canvas_data[First].x;
                canvas_data[Str-1].yn = canvas_data[First].y;
                canvas_data[Str-1].type += arc;
                }
        }
LABELS[lbls] = -1;
}




//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
DecimalSeparator = ',';
}
//---------------------------------------------------------------------------










//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
static bool bF = true;
Form1->Button1->Enabled = false;
CANVAS_TO_FILE = false;
AnsiString A = Form3->Edit1->Text;
BoardThick = StrToFloat(Str_Float_Format(A));
Form2->StringGrid1->Row = Form2->StringGrid1->RowCount-1;
// reading lib
Form1->Label1->Visible = true;
Form1->Label1->Caption = "Reading library. Please wait...";
Application->ProcessMessages();
AnsiString LibPath = ExtractFilePath(Form1->OpenDialog1->FileName) + "related_files\\";
FILE* F;
F = fopen((LibPath + "dxf_lib.csv").c_str(),"rb+");
if(F && bF)
        {
        ShowMessage("Locally stored library found: \"" + LibPath + "\"");
        Form2->SvLib->Caption = "Use local library";
        Form2->SvLib->Checked = bF;
        }
Form2->R_Library(Form2->SvLib->Checked);
GetRects();
CanvasAll(Form2->AllObj);
Form1->Label1->Caption = "";
Form1->Label1->Visible = false;
Form2->Visible = true;
Form2->PageControl1->ActivePageIndex = 0;
Form2->PageControl1->Refresh();
Form2->myResize(1);
CanvasAll(Form2->DrawGroupList->ItemIndex);
Form1->Button1->Enabled = true;

// reset bF
bF = false;
}
//---------------------------------------------------------------------------









//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
//Form1->FormStyle = fsNormal;
Form3->Visible = true;
}
//---------------------------------------------------------------------------








//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
CANVAS_TO_FILE = true;
NO_PACKAGE = "";
Form1->Blocks->Clear();
Form1->NamesOfBlocks->Clear();
Form1->OutputBox->Clear();
Form2->StringGrid1->Row = Form2->StringGrid1->RowCount-1;
if (Form1->AllP->Checked || Form1->InsideBRD->Checked)
        {
        Form1->Parts->Enabled = true;
        Form1->Parts->SelectAll();
        }
if (Form1->CheckBox19->Checked)
        {
        Form1->Nets->Enabled = true;
        Form1->Nets->SelectAll();
        }
AnsiString A;
AnsiString B;
AnsiString NameBlk;
A = Form3->Edit1->Text;
BoardThick = StrToFloat(Str_Float_Format(A));
long i;
Form1->Label1->Visible = true;
//
Form1->OutputBox->Items->Add("0");
Form1->OutputBox->Items->Add("SECTION");
Form1->OutputBox->Items->Add("2");
Form1->OutputBox->Items->Add("ENTITIES");
//
//---------------------------------------------------------------------------
//                    board, mask & paste cutouts
//---------------------------------------------------------------------------
int ST =        Form1->File->Items->IndexOf("[board]");
if (ST == -1)   ShowMessage ("  Label [board] not found!");
int sm =        Form1->File->Items->IndexOf("[solder_mask_cutouts]");
if (sm == -1)   ShowMessage ("  Label [solder_mask_cutouts] not found!");
int off =       Form1->File->Items->IndexOf("[graphics]");
if (off == -1)
        off =   Form1->File->Items->IndexOf("[parts]");
if (off == -1)  ShowMessage ("  Label [parts] not found!");
int Ccor = 0;
int HatchPattern = 0;
int LAYER = 0;
float Fx = 0;
float Fy = 0;
Form1->Label1->Caption = "Board, mask, paste...";
Application->ProcessMessages();
for (int st=ST; st < off; st++)
        {
        A = Form1->File->Items->operator [](st);
        B = Form1->File->Items->operator [](st+1);
        if (A.SubString(1,7) == "outline")
                {
                i = prob(A,1);
                Ccor =          ex_float(A, &i);
                }
        if (A.SubString(1,9) == "sm_cutout" )
                {
                i = prob(A,1);
                Ccor =          ex_float(A, &i);
                HatchPattern =  ex_float(A, &i);
                LAYER =         ex_float(A, &i);
                }
        if (A.SubString(1,6) == "corner" && B.SubString(1,6) == "corner")
                {
                i = prob(A,1);
                int Ncor =      ex_float(A, &i);
                float x1 =      ex_float(A, &i)/(float)_106;
                float y1 =      ex_float(A, &i)/(float)_106;
                long T1 =       ex_float(A, &i);
                int end1 =      ex_float(A, &i);
                i = prob(B,1);
                int Endcor =    ex_float(B, &i);
                float x2 =      ex_float(B, &i)/(float)_106;
                float y2 =      ex_float(B, &i)/(float)_106;
                long T2 =       ex_float(B, &i);
                int end2 =      ex_float(B, &i);
                //
                //
                if (Form1->InsideBRD->Checked && st > sm)
                        {
                        if (BrdRectLeft > (x1+0.1))  continue;
                        if (BrdRectRight < (x1-0.1)) continue;
                        if (BrdRectBottom > (y1+0.1))continue;
                        if (BrdRectTop < (y1-0.1))   continue;
                        }
                // bounds
                if (x1 < ABSMIN_X) ABSMIN_X = x1;
                if (y1 < ABSMIN_Y) ABSMIN_Y = y1;
                if (x1 > ABSMAX_X) ABSMAX_X = x1;
                if (y1 > ABSMAX_Y) ABSMAX_Y = y1;
                if (x2 < ABSMIN_X) ABSMIN_X = x2;
                if (y2 < ABSMIN_Y) ABSMIN_Y = y2;
                if (x2 > ABSMAX_X) ABSMAX_X = x2;
                if (y2 > ABSMAX_Y) ABSMAX_Y = y2;
                // first corner
                if (Ncor == 1)
                        {
                        Fx = x1;
                        Fy = y1;
                        }
                // end contour
                int Count;
                float NEW[99];
                if( end1 != end2 )
                        {
                        Count = Generate_Line (x1, y1, Fx, Fy, T1 , &NEW[0]);
                        for (int a=0; (a+2) < Count; a=a+2)
                                {
                                if (st > sm && HatchPattern == 2 && LAYER == 9)         W_LINE (NEW[a],NEW[a+1],BoardThick,NEW[a+2],NEW[a+3],BoardThick,CL_TOPPASTE,"top_paste");
                                else if (st > sm && HatchPattern == 2 && LAYER == 10)   W_LINE (NEW[a],NEW[a+1],0,NEW[a+2],NEW[a+3],0,CL_BOTPASTE,"bottom_paste");
                                else if (st > sm && LAYER == 9)                         W_LINE (NEW[a],NEW[a+1],BoardThick,NEW[a+2],NEW[a+3],BoardThick,CL_TOPMASK,"top_mask");
                                else if (st > sm && LAYER == 10)                        W_LINE (NEW[a],NEW[a+1],0,NEW[a+2],NEW[a+3],0,CL_BOTMASK,"bottom_mask");
                                else                                                    W_LINE (NEW[a],NEW[a+1],0,NEW[a+2],NEW[a+3],0,CL_BOARD,"board_outline");
                                if (BoardThick && st < sm)
                                        {
                                        W_LINE (NEW[a],NEW[a+1],BoardThick,NEW[a+2],NEW[a+3],BoardThick,CL_BOARD,"board_outline");
                                        W_LINE (NEW[a+2],NEW[a+3],0,NEW[a+2],NEW[a+3],BoardThick,CL_BOARD,"board_outline");
                                        W_SOLID(        NEW[a],NEW[a+1],0,NEW[a+2],NEW[a+3],0,
                                                NEW[a],NEW[a+1],BoardThick,NEW[a+2],NEW[a+3],BoardThick,CL_BOARD,"board_outline");
                                        }
                                }
                        Fx = x2;
                        Fy = y2;
                        continue;
                        }
                // draw line
                Count = Generate_Line (x1, y1, x2, y2, T1 , &NEW[0]);
                for (int a=0; (a+2) < Count; a=a+2)
                        {
                        if (st > sm && HatchPattern == 2 && LAYER == 9)         W_LINE (NEW[a],NEW[a+1],BoardThick,NEW[a+2],NEW[a+3],BoardThick,CL_TOPPASTE,"top_paste");
                        else if (st > sm && HatchPattern == 2 && LAYER == 10)   W_LINE (NEW[a],NEW[a+1],0,NEW[a+2],NEW[a+3],0,CL_BOTPASTE,"bottom_paste");
                        else if (st > sm && LAYER == 9)                         W_LINE (NEW[a],NEW[a+1],BoardThick,NEW[a+2],NEW[a+3],BoardThick,CL_TOPMASK,"top_mask");
                        else if (st > sm && LAYER == 10)                        W_LINE (NEW[a],NEW[a+1],0,NEW[a+2],NEW[a+3],0,CL_BOTMASK,"bottom_mask");
                        else                                                    W_LINE (NEW[a],NEW[a+1],0,NEW[a+2],NEW[a+3],0,CL_BOARD,"board_outline");
                        if (BoardThick && st < sm)
                                {
                                BrdRectLeft =   MIN(NEW[a],    BrdRectLeft);
                                BrdRectLeft =   MIN(NEW[a+2],  BrdRectLeft);
                                BrdRectRight =  MAX(NEW[a],    BrdRectRight);
                                BrdRectRight =  MAX(NEW[a+2],  BrdRectRight);
                                BrdRectBottom = MIN(NEW[a+1],  BrdRectBottom);
                                BrdRectBottom = MIN(NEW[a+3],  BrdRectBottom);
                                BrdRectTop =    MAX(NEW[a+1],  BrdRectTop);
                                BrdRectTop =    MAX(NEW[a+3],  BrdRectTop);
                                W_LINE (NEW[a],NEW[a+1],BoardThick,NEW[a+2],NEW[a+3],BoardThick,CL_BOARD,"board_outline");
                                W_LINE (NEW[a+2],NEW[a+3],0,NEW[a+2],NEW[a+3],BoardThick,CL_BOARD,"board_outline");
                                W_SOLID(        NEW[a],NEW[a+1],0,NEW[a+2],NEW[a+3],0,
                                                NEW[a],NEW[a+1],BoardThick,NEW[a+2],NEW[a+3],BoardThick,CL_BOARD,"board_outline");
                                }
                        }
                // end board outline
                if (Endcor == Ccor)
                        {
                        Count = Generate_Line (x2, y2, Fx, Fy, T2 , &NEW[0]);
                        for (int a=0; (a+2) < Count; a=a+2)
                                {
                                if (st > sm && HatchPattern == 2 && LAYER == 9)         W_LINE (NEW[a],NEW[a+1],BoardThick,NEW[a+2],NEW[a+3],BoardThick,CL_TOPPASTE,"top_paste");
                                else if (st > sm && HatchPattern == 2 && LAYER == 10)   W_LINE (NEW[a],NEW[a+1],0,NEW[a+2],NEW[a+3],0,CL_BOTPASTE,"bottom_paste");
                                else if (st > sm && LAYER == 9)                         W_LINE (NEW[a],NEW[a+1],BoardThick,NEW[a+2],NEW[a+3],BoardThick,CL_TOPMASK,"top_mask");
                                else if (st > sm && LAYER == 10)                        W_LINE (NEW[a],NEW[a+1],0,NEW[a+2],NEW[a+3],0,CL_BOTMASK,"bottom_mask");
                                else                                                    W_LINE (NEW[a],NEW[a+1],0,NEW[a+2],NEW[a+3],0,CL_BOARD,"board_outline");
                                if (BoardThick && st < sm)
                                        {
                                        W_LINE (NEW[a],NEW[a+1],BoardThick,NEW[a+2],NEW[a+3],BoardThick,CL_BOARD,"board_outline");
                                        W_LINE (NEW[a+2],NEW[a+3],0,NEW[a+2],NEW[a+3],BoardThick,CL_BOARD,"board_outline");
                                        W_SOLID(        NEW[a],NEW[a+1],0,NEW[a+2],NEW[a+3],0,
                                                NEW[a],NEW[a+1],BoardThick,NEW[a+2],NEW[a+3],BoardThick,CL_BOARD,"board_outline");
                                        }
                                }
                        } 
                }
        }
if (Form3->BPoured->Checked)
        {
        //PolyFace::CContour Cont;
        //Cont.
        //PolyFace BRD;
        //BRD.PolygonTriangulation()
        }
if (Form1->InsideBRD->Checked && ABS(BrdRectLeft-DEFAULT) < 1)
        {
        ShowMessage("  Board outline not found!");
        }
//---------------------------------------------------------------------------
int All = Form1->Parts->SelCount;
for (int k=0; k<Form1->Parts->Count; k++)
        {
        if (Form1->Parts->Selected[k])
                {
                A = Form1->Parts->Items->operator [](k);
                if (Form1->InsideBRD->Checked)
                        {
                        TPoint pp = Print_Part(A,1);
                        if (    BrdRectLeft > (pp.x+0.1)   ||
                                BrdRectRight < (pp.x-0.1)  ||
                                BrdRectBottom > (pp.y+0.1) ||
                                BrdRectTop < (pp.y-0.1) )
                                {
                                Form1->Label1->Caption = AnsiString(A) + " ignored...";
                                Application->ProcessMessages();
                                continue;
                                }
                        }
                Form1->Label1->Caption = "Part " + AnsiString(k+1) + " from " + AnsiString(All);
                Application->ProcessMessages();
                Print_Part(A);
                }
        }
//---------------------------------------------------------------------------
if (Form3->CheckBox1->Checked && ABSMIN_X < DEFAULT && ABSMIN_Y < DEFAULT)
        {
        W_SOLID(ABSMIN_X,ABSMIN_Y,0,ABSMIN_X,ABSMAX_Y,0,
                ABSMAX_X,ABSMIN_Y,0,ABSMAX_X,ABSMAX_Y,0,17,"Polyface");
        W_SOLID(ABSMIN_X,ABSMIN_Y,BoardThick,ABSMIN_X,ABSMAX_Y,BoardThick,
                ABSMAX_X,ABSMIN_Y,BoardThick,ABSMAX_X,ABSMAX_Y,BoardThick,17,"Polyface");
        }
//----------------------------- Warning --------------------------------------
if( NO_PACKAGE.Length() )
        ShowMessage("Warning!: No Packages for parts:\n" + NO_PACKAGE);
//---------------------------------------------------------------------------
//                               nets
//---------------------------------------------------------------------------
ST =            Form1->File->Items->IndexOf("[nets]");
if (ST == -1)   ShowMessage ("  Label [nets] not found!");
off =           Form1->File->Items->IndexOf("[texts]");
if (off == -1)  ShowMessage ("  Label [texts] not found!");
AnsiString C;
Form1->Label1->Caption = "Traces, areas...";
Application->ProcessMessages();
bool ENABLED = false;
for (int st=ST; st < off; st++)
        {
        A = Form1->File->Items->operator [](st);
        B = Form1->File->Items->operator [](st+1);
        C = Form1->File->Items->operator [](st+2);
        if (A.SubString(1,4) == "net:")
                {
                i = prob(A,1);
                A = ex_str(A,&i);
                int indexof = Form1->Nets->Items->IndexOf(A);
                if (indexof >= 0)
                        {
                        if (Form1->Nets->Selected[indexof]) ENABLED = true;
                        else    ENABLED = false;
                        }
                }
        if (!ENABLED)
                {
                continue;
                }
        if (A.SubString(1,3) == "vtx" && B.SubString(1,3) == "seg" && C.SubString(1,3) == "vtx")
                {
                i = prob(A,2);
                float X_1 =     ex_float(A, &i)/(float)_106;
                float Y_1 =     ex_float(A, &i)/(float)_106;
                if (Form1->InsideBRD->Checked)
                        {
                        if (BrdRectLeft > (X_1+0.1))  continue;
                        if (BrdRectRight < (X_1-0.1)) continue;
                        if (BrdRectBottom > (Y_1+0.1))continue;
                        if (BrdRectTop < (Y_1-0.1))   continue;
                        }
                i = prob(C,2);
                float X_2 =     ex_float(C, &i)/(float)_106;
                float Y_2 =     ex_float(C, &i)/(float)_106;
                i = prob(B,2);
                float LAY =     ex_float(B, &i);
                float WID =     ex_float(B, &i)/(float)_106;
                i = prob(C,6);
                float VIA =     ex_float(C, &i)/(float)_106;
                float HOLE =    ex_float(C, &i)/(float)_106;
                if (LAY == LT_COPP)          W_LWPOLYLINE(X_1,Y_1,X_2,Y_2,WID,0,BoardThick,0,CL_TOPLINES,"top_lines");
                else if (LAY == LB_COPP)     W_LWPOLYLINE(X_1,Y_1,X_2,Y_2,WID,0,0,0,CL_BOTLINES,"bottom_lines");
                if (VIA > BY_ZERO)
                        {
                        ///W_LWPOLYLINE(X_2,Y_2,X_2,Y_2,VIA,0,BoardThick,0,CL_VIAS,0,"vias");
                        ///W_LWPOLYLINE(X_2,Y_2,X_2,Y_2,VIA,0,0,0,CL_VIAS,0,"vias");
                        ///W_LWPOLYLINE(X_2,Y_2,X_2,Y_2,HOLE,0,0,BoardThick,CL_VIAS,0,"vias");
                        ///W_LWPOLYLINE(X_2,Y_2,X_2,Y_2,HOLE,0,BoardThick,0,CL_VIAS,0,"vias");
                        float currX;
                        float currY;
                        float nextX;
                        float nextY;
                        float VcurrX;
                        float VcurrY;
                        float VnextX;
                        float VnextY;
                        for (int An = 0; An < 360; An = An + 30)
                                {
                                currX = X_2 + HOLE/(float)2*cos((float)An*M_PI/(float)180);
                                currY = Y_2 + HOLE/(float)2*sin((float)An*M_PI/(float)180);
                                nextX = X_2 + HOLE/(float)2*cos((float)(An + 30)*M_PI/(float)180);
                                nextY = Y_2 + HOLE/(float)2*sin((float)(An + 30)*M_PI/(float)180);
                                VcurrX = X_2 + VIA/(float)2*cos((float)An*M_PI/(float)180);
                                VcurrY = Y_2 + VIA/(float)2*sin((float)An*M_PI/(float)180);
                                VnextX = X_2 + VIA/(float)2*cos((float)(An + 30)*M_PI/(float)180);
                                VnextY = Y_2 + VIA/(float)2*sin((float)(An + 30)*M_PI/(float)180);
                                W_SOLID(        currX,currY,0,
                                                nextX,nextY,0,
                                                currX,currY,BoardThick,
                                                nextX,nextY,BoardThick,CL_VIA_HOLES,"vias");
                                W_SOLID(        currX,currY,0,
                                                nextX,nextY,0,
                                                VcurrX,VcurrY,0,
                                                VnextX,VnextY,0,CL_VIAS,"vias");
                                W_SOLID(        currX,currY,BoardThick,
                                                nextX,nextY,BoardThick,
                                                VcurrX,VcurrY,BoardThick,
                                                VnextX,VnextY,BoardThick,CL_VIAS,"vias");
                                }
                        }
                }
        if (A.SubString(1,4) == "area" )
                {
                i = prob(A,2);
                Ccor =          ex_float(A, &i);
                LAYER =         ex_float(A, &i);
                HatchPattern =  ex_float(A, &i);
                Fx = 0;
                Fy = 0;
                }
        if (A.SubString(1,6) == "corner" && B.SubString(1,6) == "corner")
                {
                i = prob(A,1);
                int Ncor =      ex_float(A, &i);
                float x1 =      ex_float(A, &i)/(float)_106;
                float y1 =      ex_float(A, &i)/(float)_106;
                long T1 =       ex_float(A, &i);
                bool FL1 =      ex_float(A, &i);
                i = prob(B,1);
                int Endcor =    ex_float(B, &i);
                float x2 =      ex_float(B, &i)/(float)_106;
                float y2 =      ex_float(B, &i)/(float)_106;
                long T2 =       ex_float(B, &i);
                bool FL2 =      ex_float(B, &i);
                if (Form1->InsideBRD->Checked)
                        {
                        if ((BrdRectLeft > (x1+0.1)) ||
                           (BrdRectRight < (x1-0.1)) ||
                           (BrdRectBottom > (y1+0.1)) ||
                           (BrdRectTop < (y1-0.1)))
                                {
                                if (Fx > BY_ZERO || Fy > BY_ZERO)
                                        {
                                        ShowMessage("  En:Intersection lines in contours board and area!\n  Cancel driving.\n  Ru: Пересекающиеся линии контуров платы и региона.\n  Рисование остановлено.");
                                        return;
                                        }
                                else continue;
                                }
                        }
                if (Ncor == 1)
                        {
                        Fx = x1;
                        Fy = y1;
                        }
                if (FL1)
                        {
                        Fx = x2;
                        Fy = y2;
                        }
                if (!FL1)
                        {
                        float NEW[99];
                        int Count = Generate_Line (x1, y1, x2, y2, T1 , &NEW[0]);
                        for (int a=0; (a+2) < Count; a=a+2)
                                {
                                if (LAYER == LT_COPP)        W_LINE (NEW[a],NEW[a+1],BoardThick,NEW[a+2],NEW[a+3],BoardThick,CL_TOPAREAS,"top_areas");
                                else if (LAYER == LB_COPP)   W_LINE (NEW[a],NEW[a+1],0,NEW[a+2],NEW[a+3],0,CL_BOTAREAS,"bottom_areas");
                                }
                        if (Endcor == Ccor || FL2)
                                {
                                Count = Generate_Line (x2, y2, Fx, Fy, T2 , &NEW[0]);
                                for (int a=0; (a+2) < Count; a=a+2)
                                        {
                                        if (LAYER == LT_COPP)        W_LINE (NEW[a],NEW[a+1],BoardThick,NEW[a+2],NEW[a+3],BoardThick,CL_TOPAREAS,"top_areas");
                                        else if (LAYER == LB_COPP)   W_LINE (NEW[a],NEW[a+1],0,NEW[a+2],NEW[a+3],0,CL_BOTAREAS,"bottom_areas");
                                        }
                                }
                        }
                }
        }
//---------------------------------------------------------------------------
Form1->OutputBox->Items->Add("0");
Form1->OutputBox->Items->Add("ENDSEC");
Form1->OutputBox->Items->Add("0");
Form1->OutputBox->Items->Add("EOF");
//
A = ExtractFilePath(Form1->OpenDialog1->FileName);
if(CreateDirectory((A + "Model(autocad dxf format)").c_str(),NULL) )
        ShowMessage("    EN: Directory created - " + A + "Model(autocad dxf format)\n    RU: Создана папка - " + A + "Model(autocad dxf format)\n" );
A = A + "Model(autocad dxf format)\\" + ExtractFileName(Form1->OpenDialog1->FileName);
//
AnsiString OUTPUTFILE = A + ".dxf";
ofstream DXF (OUTPUTFILE.c_str());
//
DXF << "0" << endl;
DXF << "SECTION" << endl;
DXF << "2" << endl;
DXF << "BLOCKS" << endl;
//
Form1->Label1->Caption = "Writing blocks";
Application->ProcessMessages();
for (int k=0; k<Form1->Blocks->Count; k++)
        {
        A = Form1->Blocks->Items->operator [](k);
        DXF << A.c_str() << endl;
        }
//
DXF << "0" << endl;
DXF << "ENDSEC" << endl;
//
for(int b=0; b<Form1->OutputBox->Items->Count; b++)
        {
        DXF << Form1->OutputBox->Items->operator [](b).c_str() << endl;
        }
DXF.close();
Form1->OutputBox->Clear();
Form1->Blocks->Clear();
Form1->NamesOfBlocks->Clear();
//-------------запуск ------------
B = ExtractFilePath(OUTPUTFILE);
A = ExtractFileName(OUTPUTFILE);
Application->ProcessMessages();
Sleep(500);
if (Form1->RadioButton1->Checked)
        {
        if ((UINT)ShellExecute(NULL,
               "open",
               A.c_str(),
               NULL,
               B.c_str() ,
               SW_SHOWNORMAL) <=32)
               {
               ShowMessage  ("  What program to open this file? There is no application associated with * .DXF files.\n  (" + OUTPUTFILE + ")");
               }
        }
else    {
        AnsiString PathP = ExtractFilePath(Application->ExeName);
        PathP = PathP.SubString(1,(PathP.Length()-1));
        PathP = ExtractFilePath(PathP);
        PathP = PathP + "FreePCB_ImportDXF\\DXF_2_FPC_FreePCB.exe";
        Clipboard()->Clear();
        Clipboard()->SetTextBuf(("ObjMan \"" + OUTPUTFILE + "\"").c_str());
        //
        Application->ProcessMessages();
        Sleep(500);
        B = PathP;
        A = ExtractFilePath(PathP);
        if ((UINT)ShellExecute  (NULL,
                "open",
                B.c_str(),
                NULL,
                A.c_str() ,
                SW_SHOWNORMAL) <=32)
                {
                ShowMessage  (" Something went wrong .. If the problem persists more than once, report it to support at freepcb.dev");
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
if (Form1->CheckBox1->Checked)
        {
        Form1->CheckBox1->Checked = false;
        Form1->CheckBox2->Checked = false;
        Form1->CheckBox3->Checked = false;
        Form1->CheckBox4->Checked = false;
        Form1->CheckBox5->Checked = false;
        Form1->CheckBox6->Checked = false;
        Form1->CheckBox7->Checked = false;
        Form1->CheckBox8->Checked = false;
        Form1->CheckBox9->Checked = false;
        Form1->CheckBox10->Checked = false;
        Form1->CheckBox11->Checked = false;
        Form1->CheckBox12->Checked = false;
        Form1->CheckBox13->Checked = false;
        Form1->CheckBox14->Checked = false;
        Form1->CheckBox15->Checked = false;
        Form1->CheckBox16->Checked = false;
        Form1->CheckBox17->Checked = false;
        Form1->CheckBox18->Checked = false;
        }
else    {
        Form1->CheckBox1->Checked = true;
        Form1->CheckBox2->Checked = true;
        Form1->CheckBox3->Checked = true;
        Form1->CheckBox4->Checked = true;
        Form1->CheckBox5->Checked = true;
        Form1->CheckBox6->Checked = true;
        Form1->CheckBox7->Checked = true;
        Form1->CheckBox8->Checked = true;
        Form1->CheckBox9->Checked = true;
        Form1->CheckBox10->Checked = true;
        Form1->CheckBox11->Checked = true;
        Form1->CheckBox12->Checked = true;
        Form1->CheckBox13->Checked = true;
        Form1->CheckBox14->Checked = true;
        Form1->CheckBox15->Checked = true;
        Form1->CheckBox16->Checked = true;
        Form1->CheckBox17->Checked = true;
        Form1->CheckBox18->Checked = true;
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::AllPClick(TObject *Sender)
{
if (!Form1->AllP->Checked)
        {
        Form1->Parts->Enabled = true;
        AnsiString LibPath = ExtractFilePath(Form1->OpenDialog1->FileName) + "related_files\\";
        FILE* F;
        F = fopen((LibPath + "dxf_lib.parts").c_str(),"rb+");
        if(F)   {
                fclose(F);
                char s[DEF_CHAR];
                AnsiString A = "1";
                ifstream RParts ((LibPath + "dxf_lib.parts").c_str());
                while( A.Length() && !RParts.eof() )
                        {
                        RParts.getline(s,DEF_CHAR);
                        A = s;
                        A.Trim();
                        int iof = Parts->Items->IndexOf(A);
                        if( iof >= 0 )
                                Parts->Selected[iof] = 1;
                        }
                RParts.close();
                }
        }
else    {
        Form1->Parts->Enabled = false;
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CheckBox19Click(TObject *Sender)
{
if (!Form1->CheckBox19->Checked)
        Form1->Nets->Enabled = true;
else
        Form1->Nets->Enabled = false;
}




//---------------------------------------------------------------------------
bool CheckPartOfPart( AnsiString * part )
{
// check on _PARTOFPART
for( int i=0; i<Form2->StringGrid1->RowCount; i++ )
        {
        AnsiString fPart = Form2->StringGrid1->Cells[SHAPE][i];
        if( part->SubString(1,part->Length()) == fPart.SubString(1,fPart.Length()) )
                {
                fPart = Form2->StringGrid1->Cells[PACKAGES][i];
                int iP=-1, iN=-1;
                if(i)
                        iP = i-1;
                if(i+1<Form2->StringGrid1->RowCount)
                        iN = i+1;
                if(iP >= 0)
                        {
                        AnsiString s = Form2->StringGrid1->Cells[PACKAGES][iP];
                        if( fPart.SubString(1,fPart.Length()) == s.SubString(1,s.Length()) )
                                return true;
                        }
                if(iN >= 0)
                        {
                        AnsiString s = Form2->StringGrid1->Cells[PACKAGES][iN];
                        if( fPart.SubString(1,fPart.Length()) == s.SubString(1,s.Length()) )
                                return true;
                        }
                }
        }
return false;
}






//---------------------------------------------------------------------------
int WhereElseIsThisPartUsed( AnsiString * part, TListBox * pList )
{
const AnsiString Line = "==================";
int iof = -1;
int CNT = 0;
int ind = 0;
if( pList )
        {
        ind = pList->Items->Count;
        iof = pList->Items->IndexOf(*part);
        if( iof >= 0 )
                {
                if( iof > 0 )
                        {
                        AnsiString s = pList->Items->operator [](iof-1);
                        if( s.SubString(1,1) == "=" )
                                {
                                pList->ClearSelection();
                                pList->ItemIndex = iof;
                                pList->Selected[iof] = true;
                                if(Form2->PageControl1->TabIndex == 0)
                                        pList->Show();
                                }
                        else    iof = -1;
                        }
                else    iof = -1;
                }
        }

for( int i=0; i<Form2->StringGrid1->RowCount; i++ )
        {
        AnsiString fPart = Form2->StringGrid1->Cells[SHAPE][i];
        if( part->SubString(1,part->Length()) == fPart.SubString(1,fPart.Length()) )
                {
                CNT++;
                if( pList && iof == -1 )
                        pList->Items->Add(Form2->StringGrid1->Cells[PACKAGES][i]);
                }
        }
if( pList && CNT && iof == -1 )
        {
        pList->Items->Add(Line);
        pList->Items->Insert(ind,*part);
        if( ind == 0 )
                pList->Items->Insert(0,Line);
        pList->ClearSelection();
        pList->ItemIndex = ind;
        pList->Selected[ind] = true;
        if(Form2->PageControl1->TabIndex == 0)
                pList->Show();
        }
return CNT;
}
void __fastcall TForm1::Label2Click(TObject *Sender)
{
ShellExecute(NULL, "open", "https://github.com/Duxah/FreePCB-2/blob/master/README.md", NULL, NULL, SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
if( Form1->AllP->Checked == 0 )
        {
        AnsiString LibPath = ExtractFilePath(Form1->OpenDialog1->FileName) + "related_files\\";
        char s[DEF_CHAR];
        AnsiString A = "1";
        ofstream WParts ((LibPath + "dxf_lib.parts").c_str());
        for( int i=0; i<Parts->Count; i++ )
                {
                if( Parts->Selected[i] )
                        WParts << Parts->Items->operator [](i).c_str() << endl;
                }
        WParts.close();
        }
}
//---------------------------------------------------------------------------

