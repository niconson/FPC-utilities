//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "fstream.h"
#include "ABClibrary.h"
#include "Please_wait.h"
#include <Registry.hpp>
#include <FileCtrl.hpp>
#include "Clipbrd.hpp"
#include "AddIndex.h"
#include "Combine.h"
#include "time.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
TRect Fill_Rect;
AnsiString A;
AnsiString B;
AnsiString C;
AnsiString NO_UNITS = "NO_UNITS";
AnsiString catalog;
AnsiString *NAMES_old_files;            // ИМЕНА ФАЙЛОВ СТАРОЙ БИБЛ
AnsiString *BUFER;                      //
AnsiString *footprints;                 // СТРОК
AnsiString *HEADERS;                    // ФУТПРИНТОВ
AnsiString *Packages;
AnsiString *author;
AnsiString *description;
AnsiString *units;
AnsiString FileName;
AnsiString WinHeader;
AnsiString PartJump;
AnsiString arch_pth = "";
static int bWarning1 = 0;
//
char stringchar[2500];             // СТРОКА ЧТЕНИЯ
//
long i = 0;
int out = 0;
int nm = 0;      //адрес в NAMES_old_files
int bf = 0;      //адрес в BUFER
int hd = 0;      //адрес в HEADERS
int dl = 0;      //адрес в DELETES
int hls = 0;     //кол-во отв
int m_scale = 0;
int m_ccx = 0;
int m_ccy = 0;

 long new_data = 0;
 int *n_str;           //номер строки
 int *end_str;         //номер строки
 long ft = 0;           //адрес в footprints
 int *n_holes;
 int *n_pins;
 //long num_str = 0;
 long wrt = 0;

float DEFAULT = 2100000000.0;

static long COUNTSTR;
static long HEADER_COUNTSTR;

bool WR_END = false;
bool gLocked = false;
int *DELETES = NULL;                           // ФЛАГИ УДАЛЕННЫХ ФАЙЛОВ

void FILTER (void);                             //фильтр
void SaveCh (void);
int prob (AnsiString ANSI , int Pr);            //курсор prob до заданного пробела
bool READ_CATALOG (void);                       //чтение библиотек в массив DATA
void LISTBOX (void);                            //заполнение listbox
void Attach_listbox1 (void);                     //заполнение listbox1
void ATTRIBUTE_FOOT (void);                     //чтение атрибутов футпринта
bool SelDir (void);
void FWRITE(void);                               //запись в файлы
int WR (AnsiString LibName);                    //пишем фупринты начинающиеся с одной буквы
void DELETE_FILES (void);                       //удаление старой библиотеки
void KEY (AnsiString KEY, bool KeyDown, bool KeyUp, int Pause);
void Open_PDF (void);
void Replace ( AnsiString Name, long StartIndex, long EndIndex);
void ResetShape ( AnsiString Name, long StartIndex, long EndIndex, AnsiString Read, bool Play) ;
AnsiString ex_str (AnsiString ANSI, long *n);
AnsiString Str_Float_Format (AnsiString STRING_2_DOUBLE);




//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
FileName = "";
PartJump = "";
AnsiString CLPBRD = Clipboard()->AsText;
Clipboard()->Clear();
if (CLPBRD.SubString(1,6) == "ObjMan")
        {
        long In = 7;
        FileName = ex_str(CLPBRD, &In) ;
        CLPBRD = ExtractFileName (FileName);
        Form1->Caption = "Connected to " + CLPBRD;
        WinHeader = "FreePCB - " + CLPBRD;
        bPaste->Visible = true;
        Button8->Enabled = false;
        Button7->Enabled = true;
        bCombFoot->Enabled = true;
        bAddRefStr->Enabled = true;
        bAddShapeStr->Enabled = true;
        }
else if (CLPBRD.SubString(1,9) == "SchConstr")
        {
        long In = 10;
        PartJump =      ex_str(CLPBRD, &In);
        Edit1->Text =   ex_str(CLPBRD, &In);
        }
NameEdit->Text = "";
AuthorEdit->Text = "";
DescEdit->Text = "";
Label10->Caption = "";
Sname->Visible = false;        //name
Spins->Visible = false;        //pins
Sholes->Visible = false;        //holes
Sauthor->Visible = false;
Sdescript->Visible = false;
ListBox5->Visible = false;        //Удаление повторяющихся
Sname->Sorted = true;
Spins->Sorted = true;
Sholes->Sorted = true;
Sauthor->Sorted = true;
Sdescript->Sorted = true;
Form1->RadioButton6->Enabled = false;
Form1->RadioButton7->Enabled = false;
Form1->RadioButton8->Enabled = false;
Form1->RadioButton9->Enabled = false;
Form1->RadioButton10->Enabled = false;
Form1->RadioButton11->Enabled = false;
Form1->RadioButton12->Enabled = false;
A = ExtractFilePath(Application->ExeName);
A = A + "options.txt";
ifstream SET (A.c_str());

//чтение конфигураций

while (!SET.eof())
        {
        SET.getline(stringchar,sizeof(stringchar));
        A = stringchar;
        A = A.Trim();
        if(A.SubString(1,4) == "Adr " && Edit1->Text.Length() == 0)
                                                Edit1->Text = A.SubString(5,(A.Length()-4));
        if(A.SubString(1,5) == "Alpha")         Sort_ABC->Checked = true;
        if(A.SubString(1,4) == "Pins")          Sort_n_pins->Checked = true;
        if(A.SubString(1,5) == "Holes")         Sort_n_holes->Checked = true;
        if(A.SubString(1,6) == "Author")        Sort_author->Checked = true;
        if(A.SubString(1,8) == "Descript")      Sort_desc->Checked = true;
        }
SET.close();
Application->ProcessMessages();
bool CompleteRead = false;
Form4->Visible = true;
if (Edit1->Text.Length())
        CompleteRead = READ_CATALOG();
while (!CompleteRead)
        {
        Form4->Visible = false;
        ShowMessage ("   Select a library folder, please..");
        if(SelDir())
                {
                Form4->Visible = true;
                Application->ProcessMessages();
                CompleteRead = READ_CATALOG();
                if(!CompleteRead)
                        {
                        }
                }
        else    exit(0);
        }
Timer2->Enabled = true;
}



void RotatePoint ( TPoint * p, int an, TPoint org )
        {
        double x = (*p).x;
        double y = (*p).y;
        x -= org.x;
        y -= org.y;
        Rotate_Vertex( &x, &y, an);
        x += org.x;
        y += org.y;
        (*p).x = x;
        (*p).y = y;
        }
//========================================================================================
AnsiString getDataPointInArray( long * LB_Index, bool includeDeletes, int * count=NULL );
AnsiString getDataPointInArray( long * LB_Index, bool includeDeletes, int * count )
        {
        AnsiString mainS = Form1->ListBox1->Items->operator []( *LB_Index );
        long k=prob(mainS,1);
        int prevsCount = 0;
        for( int in=*LB_Index; in>=0; in-- )
                {
                AnsiString gS = Form1->ListBox1->Items->operator [](in);
                long e=prob(gS,1);
                if (Form1->Sort_ABC->Checked==0)
                        {
                        if( mainS.SubString(k,(mainS.Length()-k+1)) == gS.SubString(e,(gS.Length()-e+1)) )
                                prevsCount++;
                        }
                else if( mainS.AnsiCompare(gS) == 0 )
                        prevsCount++;
                }
        if (Form1->Sort_ABC->Checked==0)
                mainS = "name: \"" + mainS.SubString(k,(mainS.Length()-k+1)) + "\"";
        else
                mainS = "name: \"" + mainS + "\"";
        k = -1;
        if( count )
                *count = prevsCount;
        while ( prevsCount > 0 )
                {
                k++;
                if( DELETES[k] && includeDeletes == 0 )
                        continue;
                if( mainS.SubString(1,mainS.Length()) == HEADERS[k].SubString(1,HEADERS[k].Length()) )
                        prevsCount--;
                if (HEADERS[k].SubString(1,HEADERS[k].Length()) == "end")
                        {
                        k = -1;
                        ShowMessage( "Error 9375" );
                        break;
                        }
                }
        *LB_Index = k;
        return mainS;
        }
//==============================================================================================
void Draw()
{
if( Form1->ListBox1->Items->Count == 0 )
        return;
if( Form1->ListBox1->ItemIndex < 0 || Form1->ListBox1->ItemIndex >= Form1->ListBox1->Items->Count )
        Form1->ListBox1->ItemIndex = 0;
ATTRIBUTE_FOOT();

i = Form1->ListBox1->ItemIndex;
A = getDataPointInArray(&i,0);
TCanvas * Canvas = Form1->Image1->Canvas;
if (i != -1)
        {
        Canvas->Pen->Width = 1;
        Canvas->Pen->Color = clBlack;
        Canvas->Brush->Color = clBlack;//clBtnFace;
        Canvas->Rectangle(Fill_Rect.Left,Fill_Rect.Top,Fill_Rect.Right,Fill_Rect.Bottom);
        TRect Sel_Rect(0,0,0,0);
        TRect Pins_Rect(0,0,0,0);
        TPoint p1(0,0), p2(0,0), p3(0,0), p4(0,0);
        long DX_fillRect = Fill_Rect.Right - Fill_Rect.Left;
        long DY_fillRect = Fill_Rect.Bottom - Fill_Rect.Top;
        long k;
        AnsiString units;
        long Shift;
        long xF;
        long yF;
        long xB;
        long yB;
        long PinX;
        long PinY;
        long Hole;
        long PinAngle;
        float K_selrect;
        bool INV = 0;
        for (int cnt=n_str[i]; cnt<=end_str[i]; cnt++)
                {
                if      (footprints[cnt].SubString(1,3) == "pin")
                        {
                        k = prob(footprints[cnt],2);
                        Hole = ex_float_NM(footprints[cnt], &k, &units);
                        PinX = ex_float_NM(footprints[cnt], &k, &units)+1;
                        PinY = ex_float_NM(footprints[cnt], &k, &units)+1;
                        PinAngle = ex_float_NM(footprints[cnt], &k, &NO_UNITS);
                        if( p2.x || p2.y )
                                {
                                if( p3.x == 0 && p3.y == 0 )
                                        {
                                        if( PinX == p1.x || PinX == p2.x || PinY == p1.y || PinY == p2.y )
                                                {
                                                p3.x = PinX;
                                                p3.y = PinY;
                                                }
                                        }
                                else if( p3.x != PinX || p3.y != PinY )
                                        {
                                        if( p3.y == PinY && INV == 0 )
                                                {
                                                if(( p4.x == 0 && p4.y == 0 )||( ABS(p4.x-p3.x) > ABS(PinX-p3.x) ))
                                                        {
                                                        p4.x = PinX;
                                                        p4.y = PinY;
                                                        }
                                                }
                                        else if( p3.x == PinX && INV )
                                                {
                                                if(( p4.x == 0 && p4.y == 0 )||( ABS(p4.y-p3.y) > ABS(PinY-p3.y) ))
                                                        {
                                                        p4.x = PinX;
                                                        p4.y = PinY;
                                                        }
                                                }
                                        }
                                }
                        if( p1.x == 0 && p1.y == 0 )
                                {
                                p1.x = PinX;
                                p1.y = PinY;
                                }
                        else if( p1.x != PinX || p1.y != PinY )
                                {
                                if( p1.x == PinX && INV == 0 )
                                        {
                                        if(( p2.x == 0 && p2.y == 0 )||( ABS(p2.y-p1.y) > ABS(PinY-p1.y) ))
                                                {
                                                p2.x = PinX;
                                                p2.y = PinY;
                                                }
                                        }
                                else if( p1.y == PinY )
                                        {
                                        if( p2.x == 0 && p2.y == 0 )
                                                {
                                                INV = 1;
                                                p2.x = PinX;
                                                p2.y = PinY;
                                                }
                                        else if( ABS(p2.x-p1.x) > ABS(PinX-p1.x) && INV )
                                                {
                                                p2.x = PinX;
                                                p2.y = PinY;
                                                }
                                        }
                                }
                        PinX = (PinX - Sel_Rect.Left) * K_selrect + Fill_Rect.Left;
                        PinY = (Sel_Rect.Top - PinY) * K_selrect + Fill_Rect.Top + Shift;
                        Hole = Hole * K_selrect;
                        }
                else if (footprints[cnt].SubString(1,7) == "top_pad")
                        {
                        k = prob(footprints[cnt],1);
                        long type = ex_float_NM(footprints[cnt], &k, &NO_UNITS);
                        long W = ex_float_NM(footprints[cnt], &k, &units);
                        W = W/2;
                        long H = ex_float_NM(footprints[cnt], &k, &units);
                        H = ex_float_NM(footprints[cnt], &k, &units);
                        if ((type == 1)||(type == 2)||(type == 6)) H = W;
                        if ( PinAngle%90 == 0 && PinAngle%180 )
                                {
                                W = W + H;
                                H = W - H;
                                W = W - H;
                                }
                        long R = ex_float_NM(footprints[cnt], &k, &units);
                        if (type == 5) R = MIN(W,H);
                        W = W * K_selrect + 1;
                        H = H * K_selrect + 1;
                        R = R * K_selrect + 1;
                        Canvas->Pen->Width = 1;
                        Canvas->Pen->Color = clGreen;
                        Canvas->Brush->Color = clGreen;
                        if ((type == PAD_ROUND)||(type == PAD_OCTAGON))
                                Canvas->Ellipse((PinX-W),(PinY-W),(PinX+W),(PinY+W));
                        else if ((type == PAD_SQUARE)||(type == PAD_RECT))
                                {
                                if ( PinAngle%90 == 0 )
                                        Canvas->Rectangle((PinX-H),(PinY-W),(PinX+H),(PinY+W));
                                else    {
                                        TPoint p[4];
                                        TPoint org( PinX, PinY );
                                        p[0].x = PinX - H;
                                        p[0].y = PinY - W;
                                        p[1].x = PinX - H;
                                        p[1].y = PinY + W;
                                        p[2].x = PinX + H;
                                        p[2].y = PinY + W;
                                        p[3].x = PinX + H;
                                        p[3].y = PinY - W;
                                        RotatePoint(&p[0], PinAngle, org);
                                        RotatePoint(&p[1], PinAngle, org);
                                        RotatePoint(&p[2], PinAngle, org);
                                        RotatePoint(&p[3], PinAngle, org);
                                        Canvas->Polygon(p,3);
                                        }
                                }
                        else if ((type == PAD_RNDRECT)||(type == PAD_OVAL))
                                {
                                if ( PinAngle%90 == 0 )
                                        {
                                        Canvas->Rectangle((PinX-H+R),(PinY-W),(PinX+H-R),(PinY+W));
                                        Canvas->Rectangle((PinX-H),(PinY-W+R),(PinX+H),(PinY+W-R));
                                        Canvas->Ellipse((PinX-H),(PinY-W),(PinX-H+2*R),(PinY-W+2*R));
                                        Canvas->Ellipse((PinX+H),(PinY+W),(PinX+H-2*R),(PinY+W-2*R));
                                        Canvas->Ellipse((PinX+H),(PinY-W),(PinX+H-2*R),(PinY-W+2*R));
                                        Canvas->Ellipse((PinX-H),(PinY+W),(PinX-H+2*R),(PinY+W-2*R));
                                        }
                                else    {
                                        TPoint p[8];
                                        TPoint org( PinX, PinY );
                                        p[0].x = PinX - H + R;
                                        p[0].y = PinY - W;
                                        p[1].x = PinX - H;
                                        p[1].y = PinY - W + R;
                                        p[2].x = PinX - H;
                                        p[2].y = PinY + W - R;
                                        p[3].x = PinX - H + R;
                                        p[3].y = PinY + W;
                                        RotatePoint(&p[0], PinAngle, org);
                                        RotatePoint(&p[1], PinAngle, org);
                                        RotatePoint(&p[2], PinAngle, org);
                                        RotatePoint(&p[3], PinAngle, org);
                                        p[4].x = p[0].x;
                                        p[4].y = p[0].y;
                                        p[5].x = p[1].x;
                                        p[5].y = p[1].y;
                                        p[6].x = p[2].x;
                                        p[6].y = p[2].y;
                                        p[7].x = p[3].x;
                                        p[7].y = p[3].y;
                                        RotatePoint(&p[4], 180, org);
                                        RotatePoint(&p[5], 180, org);
                                        RotatePoint(&p[6], 180, org);
                                        RotatePoint(&p[7], 180, org);
                                        Canvas->Polygon(p,7);
                                        p[0].x = PinX - H + R;
                                        p[0].y = PinY - W + R;
                                        p[1].x = PinX - H + R;
                                        p[1].y = PinY + W - R;
                                        p[2].x = PinX + H - R;
                                        p[2].y = PinY + W - R;
                                        p[3].x = PinX + H - R;
                                        p[3].y = PinY - W + R;
                                        RotatePoint(&p[0], PinAngle, org);
                                        RotatePoint(&p[1], PinAngle, org);
                                        RotatePoint(&p[2], PinAngle, org);
                                        RotatePoint(&p[3], PinAngle, org);
                                        Canvas->Ellipse( p[0].x-R, p[0].y-R, p[0].x+R, p[0].y+R );
                                        Canvas->Ellipse( p[1].x-R, p[1].y-R, p[1].x+R, p[1].y+R );
                                        Canvas->Ellipse( p[2].x-R, p[2].y-R, p[2].x+R, p[2].y+R );
                                        Canvas->Ellipse( p[3].x-R, p[3].y-R, p[3].x+R, p[3].y+R );
                                        }
                                }
                        Canvas->Pen->Color = clBlue;
                        Canvas->Brush->Color = clBlue;
                        Canvas->Ellipse((PinX-Hole/2),(PinY-Hole/2),(PinX+Hole/2),(PinY+Hole/2));
                        }
                else if (footprints[cnt].SubString(1,10) == "bottom_pad")
                        {
                        k = prob(footprints[cnt],1);
                        long type = ex_float_NM(footprints[cnt], &k, &NO_UNITS);
                        long W = ex_float_NM(footprints[cnt], &k, &units);
                        W = W/2;
                        long H = ex_float_NM(footprints[cnt], &k, &units);
                        H = ex_float_NM(footprints[cnt], &k, &units);
                        if ((type == 1)||(type == 2)||(type == 6)) H = W;
                        if ( PinAngle%90 == 0 && PinAngle%180 )
                                {
                                W = W + H;
                                H = W - H;
                                W = W - H;
                                }
                        long R = ex_float_NM(footprints[cnt], &k, &units);
                        if (type == 5) R = MIN(W,H);
                        W = W * K_selrect + 1;
                        H = H * K_selrect + 1;
                        R = R * K_selrect + 1;
                        Canvas->Pen->Width = 1;
                        Canvas->Pen->Color = clRed;
                        Canvas->Brush->Color = clRed;
                        if ((type == PAD_ROUND)||(type == PAD_OCTAGON))
                                Canvas->Ellipse((PinX-W),(PinY-W),(PinX+W),(PinY+W));
                        else if ((type == PAD_SQUARE)||(type == PAD_RECT))
                                {
                                if ( PinAngle%90 == 0 )
                                        Canvas->Rectangle((PinX-H),(PinY-W),(PinX+H),(PinY+W));
                                else    {
                                        TPoint p[4];
                                        TPoint org( PinX, PinY );
                                        p[0].x = PinX - H;
                                        p[0].y = PinY - W;
                                        p[1].x = PinX - H;
                                        p[1].y = PinY + W;
                                        p[2].x = PinX + H;
                                        p[2].y = PinY + W;
                                        p[3].x = PinX + H;
                                        p[3].y = PinY - W;
                                        RotatePoint(&p[0], PinAngle, org);
                                        RotatePoint(&p[1], PinAngle, org);
                                        RotatePoint(&p[2], PinAngle, org);
                                        RotatePoint(&p[3], PinAngle, org);
                                        Canvas->Polygon(p,3);
                                        }
                                }
                        else if ((type == PAD_RNDRECT)||(type == PAD_OVAL))
                                {
                                if ( PinAngle%90 == 0 )
                                        {
                                        Canvas->Rectangle((PinX-H+R),(PinY-W),(PinX+H-R),(PinY+W));
                                        Canvas->Rectangle((PinX-H),(PinY-W+R),(PinX+H),(PinY+W-R));
                                        Canvas->Ellipse((PinX-H),(PinY-W),(PinX-H+2*R),(PinY-W+2*R));
                                        Canvas->Ellipse((PinX+H),(PinY+W),(PinX+H-2*R),(PinY+W-2*R));
                                        Canvas->Ellipse((PinX+H),(PinY-W),(PinX+H-2*R),(PinY-W+2*R));
                                        Canvas->Ellipse((PinX-H),(PinY+W),(PinX-H+2*R),(PinY+W-2*R));
                                        }
                                else    {
                                        TPoint p[8];
                                        TPoint org( PinX, PinY );
                                        p[0].x = PinX - H + R;
                                        p[0].y = PinY - W;
                                        p[1].x = PinX - H;
                                        p[1].y = PinY - W + R;
                                        p[2].x = PinX - H;
                                        p[2].y = PinY + W - R;
                                        p[3].x = PinX - H + R;
                                        p[3].y = PinY + W;
                                        RotatePoint(&p[0], PinAngle, org);
                                        RotatePoint(&p[1], PinAngle, org);
                                        RotatePoint(&p[2], PinAngle, org);
                                        RotatePoint(&p[3], PinAngle, org);
                                        p[4].x = p[0].x;
                                        p[4].y = p[0].y;
                                        p[5].x = p[1].x;
                                        p[5].y = p[1].y;
                                        p[6].x = p[2].x;
                                        p[6].y = p[2].y;
                                        p[7].x = p[3].x;
                                        p[7].y = p[3].y;
                                        RotatePoint(&p[4], 180, org);
                                        RotatePoint(&p[5], 180, org);
                                        RotatePoint(&p[6], 180, org);
                                        RotatePoint(&p[7], 180, org);
                                        Canvas->Polygon(p,7);
                                        p[0].x = PinX - H + R;
                                        p[0].y = PinY - W + R;
                                        p[1].x = PinX - H + R;
                                        p[1].y = PinY + W - R;
                                        p[2].x = PinX + H - R;
                                        p[2].y = PinY + W - R;
                                        p[3].x = PinX + H - R;
                                        p[3].y = PinY - W + R;
                                        RotatePoint(&p[0], PinAngle, org);
                                        RotatePoint(&p[1], PinAngle, org);
                                        RotatePoint(&p[2], PinAngle, org);
                                        RotatePoint(&p[3], PinAngle, org);
                                        Canvas->Ellipse( p[0].x-R, p[0].y-R, p[0].x+R, p[0].y+R );
                                        Canvas->Ellipse( p[1].x-R, p[1].y-R, p[1].x+R, p[1].y+R );
                                        Canvas->Ellipse( p[2].x-R, p[2].y-R, p[2].x+R, p[2].y+R );
                                        Canvas->Ellipse( p[3].x-R, p[3].y-R, p[3].x+R, p[3].y+R );
                                        }
                                }
                        Canvas->Pen->Color = clBlue;
                        Canvas->Brush->Color = clBlue;
                        Canvas->Ellipse((PinX-Hole/2),(PinY-Hole/2),(PinX+Hole/2),(PinY+Hole/2));
                        }
                else if (footprints[cnt].SubString(1,7) == "outline")
                        {
                        k = prob(footprints[cnt],1);
                        long w = ex_float_NM(footprints[cnt], &k, &units);
                        long x = ex_float_NM(footprints[cnt], &k, &units);
                        long y = ex_float_NM(footprints[cnt], &k, &units);
                        w = w * K_selrect;
                        Canvas->Pen->Width = w+1;
                        x = (x - Sel_Rect.Left) * K_selrect + Fill_Rect.Left;
                        y = (Sel_Rect.Top - y) * K_selrect + Fill_Rect.Top + Shift;
                        Canvas->Pen->Color = clGray;
                        Canvas->Brush->Color = clGray;
                        Canvas->MoveTo(x,y);
                        xF = x;
                        yF = y;
                        xB = x;
                        yB = y;
                        }
                else if (footprints[cnt].SubString(1,4) == "next")
                        {
                        k = prob(footprints[cnt],1);
                        long x = ex_float_NM(footprints[cnt], &k, &units);
                        long y = ex_float_NM(footprints[cnt], &k, &units);
                        long type = ex_float_NM(footprints[cnt], &k, &NO_UNITS);
                        x = (x - Sel_Rect.Left) * K_selrect + Fill_Rect.Left;
                        y = (Sel_Rect.Top - y) * K_selrect + Fill_Rect.Top + Shift;
                        float ARC[99];
                        k = Generate_Line(xB,yB,x,y,(3-type), &ARC[0]);
                        for(int n=0; n<k; n=n+2) Canvas->LineTo((int)ARC[n],(int)ARC[n+1]);
                        xB = x;
                        yB = y;
                        }
                else if (footprints[cnt].SubString(1,5) == "close")
                        {
                        k = prob(footprints[cnt],1);
                        long type = ex_float_NM(footprints[cnt], &k, &NO_UNITS);
                        float ARC[99];
                        k = Generate_Line(xB,yB,xF,yF,(3-type), &ARC[0]);
                        for(int n=0; n<k; n=n+2) Canvas->LineTo((int)ARC[n],(int)ARC[n+1]);
                        }
                else if (footprints[cnt].SubString(1,8) == "sel_rect")
                        {
                        k = prob(footprints[cnt],1);
                        Sel_Rect.Left =         ex_float_NM(footprints[cnt], &k, &units)-m_scale-m_ccx;
                        Sel_Rect.Bottom =       ex_float_NM(footprints[cnt], &k, &units)-m_scale+m_ccy;
                        Sel_Rect.Right =        ex_float_NM(footprints[cnt], &k, &units)+m_scale-m_ccx;
                        Sel_Rect.Top =          ex_float_NM(footprints[cnt], &k, &units)+m_scale+m_ccy;
                        long DX = Sel_Rect.Right - Sel_Rect.Left;
                        long DY = Sel_Rect.Top - Sel_Rect.Bottom;
                        if( DX < 1.0 )
                                K_selrect = 0.0;
                        else
                                K_selrect = (float)DX_fillRect/(float)DX;
                        Shift = (DY_fillRect - DY * K_selrect)/2;
                        if (Shift < 0)
                                {
                                K_selrect = 0.99 * K_selrect * (float)DY_fillRect / (((float)DY_fillRect - (float)Shift*(float)2));
                                Shift = 0;
                                }
                        TRect CANVAS;
                        CANVAS.Left = Fill_Rect.Left;
                        CANVAS.Top = Shift + Fill_Rect.Top;
                        CANVAS.Right = Fill_Rect.Right;
                        CANVAS.Bottom = Shift + Fill_Rect.Top + DY * K_selrect;
                        Canvas->Pen->Color = clGray;
                        Canvas->Brush->Color = clBackground;
                        //Canvas->Rectangle(CANVAS);
                        }
                else if (footprints[cnt].SubString(1,5) == "units")
                        {
                        k = prob(footprints[cnt],1);
                        units = footprints[cnt].SubString(k,(footprints[cnt].Length()-k+1));
                        }
                }
        if( p2.x || p2.y )
                {
                if( p4.x == 0 && p4.y == 0 )
                        {
                        if( p3.x == p1.x && INV || p3.y == p1.y && INV == 0 )
                                {
                                p4.x = p1.x;
                                p4.y = p1.y;
                                }
                        else if( p3.x == p2.x && INV || p3.y == p2.y && INV == 0 )
                                {
                                p4.x = p2.x;
                                p4.y = p2.y;
                                }
                        }
                Canvas->Pen->Width = 1;
                Canvas->Pen->Color = clWhite;
                Canvas->Brush->Color = clWhite;
                Canvas->Font->Size = 10;
                double L = Length_Line( p1.x,p1.y,p2.x,p2.y );
                AnsiString Tout;
                if( units.LowerCase() == "nm" )
                        {
                        L /= MLN;
                        if( L < 1.5 )
                                Tout = FormatFloat("0.00", L) + "mm";
                        else    Tout = FormatFloat("0.0", L) + "mm";
                        }
                else if( units.LowerCase() == "mil" )
                        {
                        L /= 25400;
                        Tout = AnsiString((int)L) + "mil";
                        }
                else    Tout = FormatFloat("0.0", L) + "mm";
                p1.x = (p1.x - Sel_Rect.Left) * K_selrect + Fill_Rect.Left;
                p1.y = (Sel_Rect.Top - p1.y) * K_selrect + Fill_Rect.Top + Shift;
                p2.x = (p2.x - Sel_Rect.Left) * K_selrect + Fill_Rect.Left;
                p2.y = (Sel_Rect.Top - p2.y) * K_selrect + Fill_Rect.Top + Shift;
                Canvas->Pen->Width = 4;
                Canvas->MoveTo(p1.x,p1.y);
                Canvas->LineTo(p1.x,p1.y);
                Canvas->MoveTo(p2.x,p2.y);
                Canvas->LineTo(p2.x,p2.y);
                Canvas->Pen->Width = 1;
                Canvas->MoveTo(p1.x,p1.y);
                Canvas->LineTo(p2.x,p2.y);
                if( p4.x || p4.y )
                        {
                        L = Length_Line( p3.x,p3.y,p4.x,p4.y );
                        AnsiString Tout2;
                        if( units.LowerCase() == "nm" )
                                {
                                L /= MLN;
                                if( L < 1.5 )
                                        Tout2 = FormatFloat("0.00", L) + "mm";
                                else    Tout2 = FormatFloat("0.0", L) + "mm";
                                }
                        else if( units.LowerCase() == "mil" )
                                {
                                L /= 25400;
                                Tout2 = AnsiString((int)L) + "mil";
                                }
                        else    Tout2 = FormatFloat("0.0", L) + "mm";
                        p3.x = (p3.x - Sel_Rect.Left) * K_selrect + Fill_Rect.Left;
                        p3.y = (Sel_Rect.Top - p3.y) * K_selrect + Fill_Rect.Top + Shift;
                        p4.x = (p4.x - Sel_Rect.Left) * K_selrect + Fill_Rect.Left;
                        p4.y = (Sel_Rect.Top - p4.y) * K_selrect + Fill_Rect.Top + Shift;
                        Canvas->Pen->Width = 4;
                        Canvas->MoveTo(p3.x,p3.y);
                        Canvas->LineTo(p3.x,p3.y);
                        Canvas->MoveTo(p4.x,p4.y);
                        Canvas->LineTo(p4.x,p4.y);
                        Canvas->Pen->Width = 1;
                        Canvas->MoveTo(p3.x,p3.y);
                        Canvas->LineTo(p4.x,p4.y);
                        tagSIZE S = Canvas->TextExtent(Tout2);
                        Canvas->TextOutA( (p3.x+p4.x)/2-S.cx/2, (p3.y+p4.y)/2-S.cy/2, Tout2) ;
                        }
                tagSIZE S = Canvas->TextExtent(Tout);
                Canvas->TextOutA( (p1.x+p2.x)/2-S.cx/2, (p1.y+p2.y)/2-S.cy/2, Tout) ;
                }
        }
//Canvas->Pen->Width = 1;
//Canvas->Pen->Color = Form1->Color;
//Canvas->Brush->Color = Form1->Color;
//Canvas->Rectangle(0,0,Fill_Rect.Left,Form1->ClientHeight);
//Canvas->Rectangle(0,0,Form1->ClientWidth,Fill_Rect.Top);
//Canvas->Rectangle(0,Fill_Rect.Bottom,Form1->ClientWidth,Form1->ClientHeight);
//Canvas->Rectangle(Fill_Rect.right,0,Form1->ClientWidth,Form1->ClientHeight);
A = catalog + "\\";
B = Form1->ListBox1->Items->operator [](Form1->ListBox1->ItemIndex);
long k = prob(B,1);
if (Form1->Sort_ABC->Checked)
        B = B.SubString(1,1);
else    B = B.SubString(1,k-1).Trim();
if(B.SubString(1,1) == "\"")
        {
        long g=1;
        B = ex_str(B,&g);
        }
B = A + B;
FILE* F;
F = fopen((B + ".pdf").c_str(),"rb+");
if(F == NULL)   Form1->bOpenPDF->Enabled = false;
else            Form1->bOpenPDF->Enabled = true;
fclose(F);
F = fopen((B + ".fpl").c_str(),"rb+");
if(F == NULL)   Form1->bOpenLib->Enabled = false;
else            Form1->bOpenLib->Enabled = true;
fclose(F);
//
//
i = Form1->ListBox1->ItemIndex;
A = getDataPointInArray(&i,0);
bool FlagRShape = false;
bool FlagReplace = false;
if (FileName.Length())
        {
        Form1->bAddRefStr->Enabled = true;
        Form1->bAddShapeStr->Enabled = true;
        if (i != -1)
                {
                //A = ExtractFilePath(Application->ExeName);
                //A = A + "\\UpdateLib.fpc";
                ifstream Rd (FileName.c_str());
                while   (A.SubString(1,7) != "[texts]" )
                        {
                        Rd.getline(stringchar,sizeof(stringchar));
                        A = stringchar;
                        A = A.Trim();
                        if (A.SubString(1,8) == "package:" )
                                {
                                long pr = 7;
                                AnsiString S = ex_str(A,&pr);
                                S = "name: \"" + S + "\"";
                                if (S.SubString(1,S.Length()) == HEADERS[i].SubString(1,HEADERS[i].Length()))FlagRShape = true;
                                }
                        else if (A.SubString(1,6) == "shape:" )
                                {
                                long pr = 7;
                                AnsiString S = ex_str(A,&pr);
                                S = "name: \"" + S + "\"";
                                if (S.SubString(1,S.Length()) == HEADERS[i].SubString(1,HEADERS[i].Length()))FlagReplace = true;
                                }
                        if (FlagRShape && FlagReplace) break;
                        }
                Rd.close();
                }
        }
else    {
        Form1->bAddRefStr->Enabled = false;
        Form1->bAddShapeStr->Enabled = false;
        }
if(FlagReplace) Form1->Button6->Enabled = true;
else            Form1->Button6->Enabled = false;
Form1->Button3->Refresh();
}





bool DeleteDir(AnsiString DirName)
        {
        TSearchRec sr;
        if (DirName.Length())
                {
                if (!FindFirst(DirName+"\\*.*",faAnyFile,sr)) do
                        {
                        if (!(sr.Name=="." || sr.Name==".."))// это не удаляем
                        if (((sr.Attr & faDirectory) == faDirectory ) ||  (sr.Attr == faDirectory))// найдена папка
                                {
                                FileSetAttr(DirName+"\\"+sr.Name, faDirectory );
                                DeleteDir(DirName+"\\"+sr.Name);//рекурсивно удаляем найденную папку
                                RemoveDir(DirName + "\\"+sr.Name);// удаляем уже пустую папку
                                }
                        else// найден файл
                                {
                                FileSetAttr(DirName+"\\"+sr.Name, 0);
                                DeleteFile(DirName+"\\"+sr.Name);// удаляем файл
                                }
                        } while (!FindNext(sr));// ищем пока не найдем все FindClose(sr);
                }
        RemoveDir(DirName);
        return true;
        }


//---------ОСНОВНАЯ ЧАСТЬ...------------------------------------------------------------------
//=====================================


bool READ_CATALOG (void)
{
if(gLocked)
        return false;
gLocked = true;
Form1->ListBox1->Items->Clear();
Form1->Sname->Items->Clear();
Form1->Spins->Items->Clear();
Form1->Sholes->Items->Clear();
Form1->AuthorEdit->Items->Clear();
Form1->DescEdit->Items->Clear();
Form1->Sort_ABC->Enabled =      true;
Form1->Sort_n_pins->Enabled =   true;
Form1->Sort_n_holes->Enabled =  true;
Form1->Sort_author->Enabled =   true;
Form1->Sort_desc->Enabled =     true;
catalog = Form1->Edit1->Text;
TSearchRec sra;
catalog = catalog.UpperCase();
catalog = catalog.Trim();
if (FindFirst(catalog, faAnyFile, sra) == 0) {}
FindClose(sra);

Application->ProcessMessages();
//=============================
//ДИНАМИЧЕСКОЕ ВЫДЕЛЕНИЕ ПАМЯТИ:        HEADERS_SYS
//                                      NAMES_old_files
//=============================
try     {
        if(DELETES)
                delete [] NAMES_old_files;
        NAMES_old_files = new(std::nothrow) AnsiString[999];    //
        }
catch(std::bad_alloc)
        {
        ShowMessage("    Ошибка выделения памяти: AnsiString[" + AnsiString(999) + "]!" );
        exit(0);
        }
//=============================

//---------------
TSearchRec(sr);
//==============================================
// подсчет общего кол ва строк
//==============================================
COUNTSTR = 0;
HEADER_COUNTSTR = 0;
Form1->Button2->Enabled = true;
if (FindFirst(catalog+"\\*", faAnyFile, sr) == 0)
        {
        do
                {
                if (sr.Attr & faDirectory) // directory
                        {
                        }
                else
                        {
                        A = catalog + "\\" + sr.Name;
                        if (A.UpperCase().SubString((A.Length()-3),4) == ".FPL" ||
                            A.UpperCase().SubString((A.Length()-3),4) == ".FPC")
                                {
                                BOOL FPFlag = 0;
                                if(A.UpperCase().SubString((A.Length()-3),4) == ".FPL")
                                        FPFlag = 1;
                                else    Form1->Button2->Enabled = false;
                                ifstream READCOUNTSTR (A.c_str());
                                out = 0;
                                while (out < 10)
                                        {
                                        READCOUNTSTR.getline(stringchar,sizeof(stringchar));
                                        A = stringchar;
                                        A = A.Trim();
                                        if(FPFlag)
                                                COUNTSTR++;
                                        if (A.Length() == 0) out++;
                                        else    {
                                                out = 0;
                                                if(A.SubString(1,6) == "[board")
                                                        break;
                                                else if(A.SubString(1,10) == "[footprint")
                                                        FPFlag = 1;
                                                else if ( FPFlag == 0 )
                                                        continue;
                                                else if (A.SubString(1,5) == "name:") HEADER_COUNTSTR++;
                                                }
                                        }       //while (out < 10)
                                READCOUNTSTR.close();
                                }       //if (A.UpperCase().SubString((A.Length()-3),4) == ".FPL")
                        }
                } while (FindNext(sr) == 0);
        }       //if (FindFirst(catalog+"\\*", faAnyFile, sr) == 0)
HEADER_COUNTSTR++;
FindClose(sr);
if (!HEADER_COUNTSTR || !COUNTSTR)
        {
        gLocked = false;
        return false;
        }
//=============================================================
//ДИНАМИЧЕСКОЕ ВЫДЕЛЕНИЕ ПАМЯТИ:        BUFER (HEADER_COUNTSTR)
//                                      HEADERS (HEADER_COUNTSTR)
//                                      footprints (COUNTSTR)
//                                      Packages (HEADER_COUNTSTR)
//                                      author (HEADER_COUNTSTR)
//                                      description (HEADER_COUNTSTR)
//                                      units (HEADER_COUNTSTR)
//                                      n_str (HEADER_COUNTSTR)
//                                      end_str (HEADER_COUNTSTR)
//                                      n_holes (HEADER_COUNTSTR)
//                                      n_pins (HEADER_COUNTSTR)
//                                      DELETES (HEADER_COUNTSTR)
//==============================================================
try     {
        if( DELETES )
                {
                delete [] DELETES;
                delete [] BUFER;
                delete [] HEADERS;
                delete [] footprints;
                delete [] Packages;
                delete [] author;
                delete [] description;
                delete [] units;
                delete [] n_str;
                delete [] end_str;
                delete [] n_holes;
                delete [] n_pins;
                }
        DELETES = new(std::nothrow) int [HEADER_COUNTSTR];
        BUFER = new(std::nothrow) AnsiString[HEADER_COUNTSTR];
        HEADERS = new(std::nothrow) AnsiString[HEADER_COUNTSTR];
        footprints = new(std::nothrow) AnsiString[COUNTSTR];
        Packages = new(std::nothrow) AnsiString[HEADER_COUNTSTR];
        author = new(std::nothrow) AnsiString[HEADER_COUNTSTR];
        description = new(std::nothrow) AnsiString[HEADER_COUNTSTR];
        units = new(std::nothrow) AnsiString[HEADER_COUNTSTR];
        n_str = new(std::nothrow) int [HEADER_COUNTSTR];
        end_str = new(std::nothrow) int [HEADER_COUNTSTR];
        n_holes = new(std::nothrow) int [HEADER_COUNTSTR];
        n_pins = new(std::nothrow) int [HEADER_COUNTSTR];
        for (int ii=0; ii<HEADER_COUNTSTR; ii++)
                DELETES[ii] = false;
        }
catch(std::bad_alloc)
        {
        ShowMessage("Error of memory! Exit..." );
        exit(0);
        }
//=============================
HEADERS[0]              = "end";
NAMES_old_files[0]      = "end";
BUFER[0]                = "end";
footprints[0]           = "end";
HEADERS[0]              = "end";
nm = 0;
bf = 0;
ft = 0;
hd = -1;
dl = 0;
//num_str = -1;
// get time
char DATTM[80];
time_t rawtime;
struct tm * timeinfo;
time ( &rawtime );
timeinfo = localtime ( &rawtime );
strftime (DATTM,80,"_ID_%Y_%m_%d_%H_%M_%S",timeinfo);
AnsiString TimeStr = DATTM;
// remove old archive
DeleteDir(arch_pth);
//
arch_pth = ExtractFilePath(Application->ExeName) + "Archive";
CreateDirectory( arch_pth.c_str(),NULL );
arch_pth += "\\" + ExtractFileName(catalog) + TimeStr;
CreateDirectory( arch_pth.c_str(),NULL );
Application->ProcessMessages();
AnsiString ALLPINS = "  ";
if (FindFirst(catalog+"\\*", faAnyFile, sr) == 0)
        {
        do
                {
                if (sr.Attr & faDirectory) // directory                    //если каталог
                        {
                        }
                else
                        {
                        A = catalog + "\\" + sr.Name;
                        if (A.UpperCase().SubString((A.Length()-3),4) == ".FPL" ||
                            A.UpperCase().SubString((A.Length()-3),4) == ".FPC")
                                {
                                BOOL FPFlag = 0;
                                if(A.UpperCase().SubString((A.Length()-3),4) == ".FPL")
                                        {
                                        FPFlag = 1;
                                        CopyFile((A).c_str(), (arch_pth + "\\" + sr.Name).c_str(), 0 );
                                        }
                                Application->ProcessMessages();
                                NAMES_old_files[nm] = A;
                                nm++;
                                NAMES_old_files[nm] = "end";
                                ifstream READ (A.c_str());
                                AnsiString libname = A;
                                out = 0;
                                int oldFormat = 0;
                                while (out < 10)
                                        {
                                        READ.getline(stringchar,sizeof(stringchar));
                                        //num_str++;
                                        A = stringchar;
                                        A = A.Trim();
                                        if (A.Length() == 0)
                                                out++;
                                        else
                                                {
                                                out = 0;
                                                if(A.SubString(1,6) == "[board")
                                                        break;
                                                else if(A.SubString(1,10) == "[footprint")
                                                        FPFlag = 1;
                                                else if ( FPFlag == 0 )
                                                        continue;
                                                else if (A.SubString(1,5) == "name:")
                                                        {
                                                        hd++;
                                                        if( hd%50 == 0 )
                                                                {
                                                                Form4->comment->Caption = "footprint " + AnsiString(hd) + " from " + AnsiString(HEADER_COUNTSTR-1);
                                                                Application->ProcessMessages();
                                                                }
                                                        if( A.SubString(A.Length(),1) != "\"" )
                                                                {
                                                                oldFormat = 1;
                                                                int ins = prob(A,1);
                                                                A.Insert("\"",ins);
                                                                A += "\"";
                                                                }
                                                        HEADERS[hd] = A;
                                                        Packages[hd] = "";
                                                        author[hd] = "unknown";
                                                        description[hd] = "none";
                                                        n_str[hd] = ft;
                                                        if (hd > 0)
                                                                {
                                                                n_holes[hd-1] = hls;
                                                                end_str[hd-1] = ft-1;
                                                                }
                                                        hls = 0;
                                                        //----------
                                                        i = 0;
                                                        }       //if (A.SubString(1,5) == "name:")
                                                else if (A.SubString(1,7) == "package") Packages[hd] = A.SubString(11,(A.Length()-11));
                                                else if (A.SubString(1,9) == "author: \"")
                                                        {
                                                        AnsiString str_a = A.SubString(10,(A.Length()-10));
                                                        if( str_a.Length() )
                                                                author[hd] = A.SubString(10,(A.Length()-10));
                                                        if( Form1->AuthorEdit->Items->IndexOf(author[hd]) == -1 )
                                                                Form1->AuthorEdit->Items->Add(author[hd]);
                                                        }
                                                else if (A.SubString(1,5) == "units")  units[hd] = A.SubString(8,(A.Length()-7));
                                                else if (A.SubString(1,14) == "description: \"")
                                                        {
                                                        AnsiString str_d = A.SubString(15,(A.Length()-15));
                                                        if( str_d.Length() )
                                                                description[hd] = str_d;
                                                        if( Form1->DescEdit->Items->IndexOf(description[hd]) == -1 )
                                                                Form1->DescEdit->Items->Add(description[hd]);
                                                        }
                                                else if (A.SubString(1,6) == "n_pins")
                                                        {
                                                        //AnsiString np = Str_Float_Format(A.SubString(9,(A.Length()-8)));
                                                        //n_pins[hd] = (int)StrToFloat(np);
                                                        n_pins[hd] = 0; //num_diff_pins = 0;
                                                        ALLPINS = "  ";
                                                        }
                                                else if (A.SubString(1,3) == "pin")
                                                        {
                                                        long pr = prob(A,1) ;
                                                        int pr2 = prob(A,2) ;
                                                        if (A.SubString(pr2,1) != "0")
                                                                hls++;
                                                        AnsiString pinname = ex_str( A, &pr );
                                                        if(pinname.Length() == 0)
                                                                {
                                                                pr = prob(A,1) ;
                                                                pinname = A.SubString(pr,pr2-pr-1);
                                                                }
                                                        if( ALLPINS.Pos(" "+pinname+" ") <= 0 )
                                                                {
                                                                n_pins[hd]++; //num_diff_pins++;
                                                                ALLPINS += pinname+" ";
                                                                }
                                                        }
                                                footprints[ft] = A;
                                                ft++;
                                                }
                                        }       //while (out < 10)
                                READ.close();
                                if(oldFormat)
                                        {
                                        //AnsiString mess = "The library " + libname + " was created in earlier versions of FreePcb when the quotation mark was not used in the footprint header. Fixed";
                                        //ShowMessage(mess);
                                        }
                                }       //if (A.UpperCase().SubString((A.Length()-3),4) == ".FPL")
                        }       //если файл...
                } while (FindNext(sr) == 0);
        }       //if (FindFirst(catalog+"\\*", faAnyFile, sr) == 0)
 FindClose(sr);
 hd++;
 if (hd > 0)
        {
        n_holes[hd-1] = hls;
        end_str[hd-1] = ft-1;
        }
 else   {
        Form4->Visible = false;
        ShowMessage ("   Empty folder !") ;
        gLocked = false;
        return false;
        }
 Application->ProcessMessages();
 HEADERS[hd] = "end";
 footprints[ft] = "end";
 hls = 0;
 LISTBOX();
 Attach_listbox1();
 gLocked = false;
 FILTER();
 Form1->ListBox1->ItemIndex = -1;
 return true;
}








//======================================
//--------заполнение listbox...-----------

void LISTBOX (void)
{
  Form1->ListBox1->Items->Clear();
  Form1->Sname->Items->Clear();
  Form1->Spins->Items->Clear();
  Form1->Sholes->Items->Clear();
  Form1->Sauthor->Items->Clear();
  Form1->Sdescript->Items->Clear();

 //сортировка по имени
 hd = 0;
 i = prob(HEADERS[hd],1);
 while (HEADERS[hd].SubString(1,3) != "end")
        {
        A = HEADERS[hd].SubString((i+1),(HEADERS[hd].Length()-i-1));
        Form1->Sname->Items->Add(A);
        hd++;
        }
 Form1->Label10->Caption = AnsiString("Total footprints = ") + Form1->Sname->Count;// + " Stack size " + num_str;

 //сортировка по n_pins
 hd = 0;
 while (HEADERS[hd].SubString(1,3) != "end")
        {
        B = HEADERS[hd].SubString((i+1),(HEADERS[hd].Length()-i-1));
        if      (n_pins[hd] > 999)      A = "999pins " + B;
        else if (n_pins[hd] > 99)       A = AnsiString(n_pins[hd]) + "pins " + B;
        else if (n_pins[hd] > 9)        A = AnsiString("0") + n_pins[hd] + "pins " + B;
        else if (n_pins[hd] > 0)        A = AnsiString("00") + n_pins[hd] + "pins " + B;
        else                            A = AnsiString("000") + "pins " + B;
        Form1->Spins->Items->Add(A);
        hd++;
        }

 //сортировка по n_holes
 hd = 0;
 while (HEADERS[hd].SubString(1,3) != "end")
        {
        B = HEADERS[hd].SubString((i+1),(HEADERS[hd].Length()-i-1));
        if      (n_holes[hd] > 999)     A = "999holes " + B;
        else if (n_holes[hd] > 99)      A = AnsiString(n_holes[hd]) + "holes " + B;
        else if (n_holes[hd] > 9)       A = AnsiString("0") + n_holes[hd] + "holes " + B;
        else if (n_holes[hd] > 0)       A = AnsiString("00") + n_holes[hd] + "holes " + B;
        else                            A = AnsiString("000") + "holes " + B;
        Form1->Sholes->Items->Add(A);
        hd++;
        }
  //сортировка по author
 hd = 0;
 while (HEADERS[hd].SubString(1,3) != "end")
        {
        B = HEADERS[hd].SubString((i+1),(HEADERS[hd].Length()-i-1));
        A = "\"" + author[hd] + "\" " + B;
        Form1->Sauthor->Items->Add(A);
        hd++;
        }
   //сортировка по description
 hd = 0;
 while (HEADERS[hd].SubString(1,3) != "end")
        {
        B = HEADERS[hd].SubString((i+1),(HEADERS[hd].Length()-i-1));
        A = "\"" + description[hd] + "\" " + B;
        Form1->Sdescript->Items->Add(A);
        hd++;
        }
}

//=======================================
//--------вывод в listbox1 на экран--------

void Attach_listbox1 (void)
{
if (Form1->Sort_ABC->Checked)      //по алфавиту
   {Form1->ListBox1->Items = Form1->Sname->Items; }
if (Form1->Sort_n_pins->Checked)      //по pins
   { Form1->ListBox1->Items = Form1->Spins->Items; }
if (Form1->Sort_n_holes->Checked)      //по holes
   { Form1->ListBox1->Items = Form1->Sholes->Items;}
if (Form1->Sort_author->Checked)      //по author
   { Form1->ListBox1->Items = Form1->Sauthor->Items;}
if (Form1->Sort_desc->Checked)      //по descript
   { Form1->ListBox1->Items = Form1->Sdescript->Items;}
}













//====================================
//====================================
//====================================
//====================================
//FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF---------фильтр---------FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF

void FILTER (void)
{
if (gLocked)
        return;
Form1->CheckBox1->Checked = false;
Form1->ListBox1->Visible = false;


if (Form1->Edit3->Text.Length()||        //фильтр PINS
    Form1->Edit4->Text.Length())         //фильтр HOLES
    {
    Form1->ListBox1->Clear();
    int np = -1;
    int nh = -1;
    if(Form1->Edit3->Text.Length())
        {
        B = Form1->Edit3->Text;
        AnsiString ss = Str_Float_Format(B);
        np = (int)StrToFloat(ss);
        }
    if(Form1->Edit4->Text.Length())
        {
        B = Form1->Edit4->Text;
        AnsiString ss = Str_Float_Format(B);
        nh = (int)StrToFloat(ss);
        }
    i = 0;
    while( HEADERS[i].SubString(1,3) != "end" )
        {
        A = "";
        B = "";
        if ((n_holes[i] == nh || nh == -1) && (n_pins[i] == np || np == -1))
                {
                long k=1;
                B = ex_str( HEADERS[i], &k );
                if(Form1->Sort_ABC->Checked==0)
                        {
                        if(n_pins[i] == np)
                                A += "pins="+AnsiString(n_pins[i]);
                        if(n_holes[i] == nh)
                                A += "holes="+AnsiString(n_holes[i]);
                        }
                if(A.Length())
                        A += " ";
                }
        if(B.Length())
                Form1->ListBox1->Items->Add(A+B);
        i++;
        }
    }
else    //полный список
        Attach_listbox1();
//
//FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
if (Form1->Edit2->Text.Length() != 0)         //фильтр по имени
        {
        i = Form1->ListBox1->Count-1;
        while (i >= 0 )
                {
                A = Form1->ListBox1->Items->operator [](i);
                long k=prob(A,1);
                if (Form1->Sort_ABC->Checked==0)
                        A = A.SubString(k,(A.Length()-k+1));
                B = Form1->Edit2->Text;

                if( A.UpperCase().Pos( B.UpperCase() ) <= 0 )
                        Form1->ListBox1->Items->Delete(i);
                i--;
                }
        }
//FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
if (Form1->CheckBox2->Checked)
        {
        int pad = 0; //код
        if (Form1->RadioButton6->Checked)pad = 0;         //фильтр pads none
        if (Form1->RadioButton7->Checked)pad = 1;         //фильтр pads round
        if (Form1->RadioButton8->Checked)pad = 2;         //фильтр pads square
        if (Form1->RadioButton9->Checked)pad = 3;         //фильтр pads rect
        if (Form1->RadioButton10->Checked)pad = 4;         //фильтр pads rndrect
        if (Form1->RadioButton11->Checked)pad = 5;         //фильтр pads oval
        if (Form1->RadioButton12->Checked)pad = 6;         //фильтр pads octagon
        i = Form1->ListBox1->Count-1;
        while (i >= 0 )
                {
                C = Form1->ListBox1->Items->operator [](i);
                A = C;
                long k=1;
                ex_str(A,&k);
                if (Form1->Sort_ABC->Checked==0)
                        A = A.SubString(k,(A.Length()-k+1));
                if(A.SubString(1,1) == "\"")
                        {
                        long g=1;
                        A = ex_str(A,&g);
                        }
                B = "";
                k = i;
                A = getDataPointInArray(&k,0);
                hd = k;
                ft = n_str[hd];
                int bAdd= 0;
                while (ft <= end_str[hd])
                        {
                        ft++;
                        B = footprints[ft];
                        if      ((B.SubString(1,7) == "top_pad")||
                                (B.SubString(1,10) == "bottom_pad")||
                                (B.SubString(1,9) == "inner_pad"))
                                {
                                A = B;
                                int pr = prob(A,1);
                                AnsiString np = Str_Float_Format(B.SubString(pr,1));
                                int str_int = (int)StrToFloat(np);
                                if (str_int == pad )
                                        {
                                        pr = prob(A,2);
                                        int ppr = prob(A,3);
                                        if( ppr-pr > 1 )
                                                {
                                                np = Str_Float_Format(B.SubString(pr,(ppr-pr-1)));
                                                float str_f = StrToFloat(np);
                                                if(( str_f > 0.01 && pad ) ||
                                                   ( str_f < 0.01 && pad == 0 ))
                                                        bAdd = 1;
                                                }
                                        }
                                }
                        if (B.SubString(1,3) == "end") break;
                        }
                if( bAdd == 0 )
                        Form1->ListBox1->Items->Delete(i);
                i--;
                }
        }

A = " "+Form1->Edit2->Text;
if(Form1->ListBox1->Items->Count)
        Form1->ListBox1->ItemIndex = 0;
for(int i=Form1->ListBox1->Items->Count-1; i>=0; i--)
        {
        AnsiString S = Form1->ListBox1->Items->operator [](i);
        if( S.UpperCase().Pos(A.UpperCase()) == (S.Length()-A.Length()+1) )
                {
                Form1->ListBox1->ItemIndex = i;
                break;
                }
        }
Form1->ListBox1->Visible = true;
}








//============
//КНОПКА ОБЗОР
//============
void __fastcall TForm1::Button1Click(TObject *Sender)
        {
        if (gLocked)
                return;
        if(SelDir())
                READ_CATALOG();
        }







//================
//Select Directory
//================
bool SelDir (void)
        {
        AnsiString way = Form1->Edit1->Text;
        if(SelectDirectory("Укажите путь к папке","",way))
                {
                Form1->Edit1->Text = way;
                Application->ProcessMessages();
                if (way.Length() == 0)
                        exit(0);
                return 1;
                }
        return 0;
        }



bool STR_TEST( AnsiString * STR_T )
{
       static int num_error = 0;
       //test string
       //Windows10 does not hang
       //that these characters
       //are present in the file name
       int ip;
       while ( (ip=(*STR_T).Pos("\\")) > 0 )
                (*STR_T).Delete(ip,1);
       while ( (ip=(*STR_T).Pos("\"")) > 0 )
                (*STR_T).Delete(ip,1);
       while ( (ip=(*STR_T).Pos("/")) > 0 )
                (*STR_T).Delete(ip,1);
       while ( (ip=(*STR_T).Pos("|")) > 0 )
                (*STR_T).Delete(ip,1);
       while ( (ip=(*STR_T).Pos(":")) > 0 )
                (*STR_T).Delete(ip,1);
       while ( (ip=(*STR_T).Pos("*")) > 0 )
                (*STR_T).Delete(ip,1);
       while ( (ip=(*STR_T).Pos("?")) > 0 )
                (*STR_T).Delete(ip,1);
       while ( (ip=(*STR_T).Pos("<")) > 0 )
                (*STR_T).Delete(ip,1);
       while ( (ip=(*STR_T).Pos(">")) > 0 )
                (*STR_T).Delete(ip,1);
       //still found in the internet that you can not these.
       //just in case we exclude.
       while ( (ip=(*STR_T).Pos("+")) > 0 )
                (*STR_T).Delete(ip,1);
       while ( (ip=(*STR_T).Pos("{")) > 0 )
                (*STR_T).Delete(ip,1);
       while ( (ip=(*STR_T).Pos("}")) > 0 )
                (*STR_T).Delete(ip,1);
       while ( (ip=(*STR_T).Pos("&")) > 0 )
                (*STR_T).Delete(ip,1);
       while ( (ip=(*STR_T).Pos("%")) > 0 )
                (*STR_T).Delete(ip,1);
       while ( (ip=(*STR_T).Pos("#")) > 0 )
                (*STR_T).Delete(ip,1);
       while ( (ip=(*STR_T).Pos("№")) > 0 )
                (*STR_T).Delete(ip,1);
       while ( (ip=(*STR_T).Pos("~")) > 0 )
                (*STR_T).Delete(ip,1);
       if( (*STR_T).Length() == 0 )
              {
              AnsiString nErr = AnsiString(num_error);
              (*STR_T) = "LIB_000000";
              int NL = (*STR_T).Length();
              (*STR_T).SetLength(NL-nErr.Length());
              (*STR_T) += nErr;
              num_error++;
              return 1;
              }
       return 0;
}




//==============================
//--------WRITE()---------------
//==============================
void FWRITE(void)
{
 if (gLocked)
        return;
 gLocked = true;
 WR_END = false;

 //----проверка записи------
 B = Form1->Edit1->Text;
 B = B + "\\probe.txt";
 ofstream PROBE (B.c_str());
 PROBE << "write";
 PROBE.close();
 Sleep(500);
 ifstream PROBE_r (B.c_str());
 PROBE_r.getline (stringchar,sizeof(stringchar)) ;
 PROBE_r.close();
 A = stringchar;
 if (Form1->ListBox1->Count > 1)
        {
        if (A.SubString(1,5) == "write" )
                {
                DeleteFile( B.c_str() );
                DELETE_FILES();
                }
        else    {
                ShowMessage("Aborted / This folder is protected!");
                gLocked = false;
                return;
                }
        }
 //
 Form1->ListBox5->Clear();
 //-------------------------
 Form1->ListBox1->ItemIndex = 0;
 wrt = 0;
 do    {
       A = Form1->ListBox1->Items->operator [](wrt);
       long k=1;
       AnsiString NameLib = ex_str(A,&k);

       if ((Form1->Sort_ABC->Checked))
              NameLib = A.SubString(1,1);
       else     {
                if(NameLib.Length()==0)
                        {
                        k = prob(A,1);
                        NameLib = A.SubString(1,k-1).Trim();
                        }
                STR_TEST( &NameLib );
                }
       //
       Application->ProcessMessages();
       k = wrt;
       A = getDataPointInArray(&k,1);
       hd = k;
       WR(NameLib);
       }while(!WR_END);
 i = 0;
 while (i < HEADER_COUNTSTR)
      {
       DELETES[i] = false;
       i++;
      }
 gLocked = false;
}










//=========================================
//пишем фупринты начинающиеся с одной буквы
//=========================================
int WR (AnsiString LibName)
{
//
AnsiString lib = Form1->Edit1->Text;
AnsiString NameLib = lib + "\\" + LibName + ".fpl";
ofstream WRITE (NameLib.c_str());
//ofstream DL ;
//DL.open(((lib+"\\Delete.arch").c_str()), std::ios_base::app );
NameLib=LibName;
AnsiString PREV=LibName;
//пока начинается с одной буквы пишем...
long k=1;
while(1)
  {
  k = wrt;
  A = getDataPointInArray(&k,1);
  hd = k;
  if( hd >= HEADER_COUNTSTR || hd < 0 )
        {
        ShowMessage("Catastrophic error. string not found in headers. The library can be restored by changing the extension to the \".FPC\" of the Library.arch file");
        //DL.close();
        WRITE.close();
        exit(0);
        }
  ft = n_str[hd];
  //
  if( end_str[hd] - ft > 1 )
        {
          if (DELETES[hd] == false)
                {
                WRITE << HEADERS[hd].c_str() << endl;
                if( Packages[hd].Length() )
                        WRITE << ("package: \"" + Packages[hd] + "\"").c_str() << endl;
                if( author[hd].Length() )
                        WRITE << ("author: \"" + author[hd] + "\"").c_str() << endl;
                if( description[hd].Length() )
                        WRITE << ("description: \"" + description[hd] + "\"").c_str() << endl;
                }
          //else  {
                //DL << HEADERS[hd].c_str() << endl;
                //if( Packages[hd].Length() )
                //        DL << ("package: \"" + Packages[hd] + "\"").c_str() << endl;
                //if( author[hd].Length() )
                //        DL << ("author: \"" + author[hd] + "\"").c_str() << endl;
                //if( description[hd].Length() )
                //        DL << ("description: \"" + description[hd] + "\"").c_str() << endl;
                //}
          ft++;
        }
  while (ft <= end_str[hd])    // ПИШЕМ ФУТПРИНТ
        {
          if (footprints[ft].SubString(1,3) == "end")
                break;
          if ( !footprints[ft].Length() ||
                footprints[ft].SubString(1,7) == "package" ||
                footprints[ft].SubString(1,6) == "author" ||
                footprints[ft].SubString(1,8) == "descript")
                {
                ft++;
                continue;
                }
          if (DELETES[hd] == false)
                WRITE << footprints[ft].c_str() << endl;
          //else
          //      DL << footprints[ft].c_str() << endl;
          ft++;
          if (footprints[ft].SubString(1,5) == "name:")
                break;
        }
  if (DELETES[hd] == false) WRITE << endl;
  //else DL << endl;
  if((wrt + 1) >= Form1->ListBox1->Count)
        {
        WR_END = true;
        break;
        }
  wrt++;
  if( wrt%50 == 0 )
        {
        Form4->comment->Caption = "footprint " + AnsiString(wrt) + " from " + AnsiString(HEADER_COUNTSTR-1);
        Application->ProcessMessages();
        }
  A = Form1->ListBox1->Items->operator [](wrt);
  //
  PREV = NameLib;
  if (Form1->Sort_ABC->Checked)
        {
        NameLib = A.SubString(1,1);
        if (NameLib.UpperCase().SubString(1,1) != PREV.UpperCase().SubString(1,1))
                break;
        }
  else  {
        k=1;
        NameLib = ex_str(A,&k);

        if(NameLib.Length()==0)
                {
                k = prob(A,1);
                NameLib = A.SubString(1,k-1).Trim();
                }
        STR_TEST( &NameLib );
        if (    NameLib.UpperCase().SubString(1,NameLib.Length()) !=
                PREV.UpperCase().SubString(1,PREV.Length()))
                break;
        }
  }
//DL.close();
WRITE.close();
return 1;
}







//=============================
//========Save Checked=========
//=============================
void SaveCh (void)
        {
        if (gLocked ||
            Form1->Timer2->Enabled == 0 ||
            Form1->Edit1->Text.Length() == 0)
                return;
        A = ExtractFilePath(Application->ExeName);
        A = A + "options.txt";
        ofstream OPT (A.c_str());
        OPT << "Adr " << Form1->Edit1->Text.c_str() << endl;
        if (Form1->Sort_n_pins->Checked) OPT << "Pins" << endl;
        else if (Form1->Sort_n_holes->Checked) OPT << "Holes" << endl;
        else if (Form1->Sort_author->Checked) OPT << "Author" << endl;
        else if (Form1->Sort_desc->Checked)OPT << "Descript" << endl;
        else    OPT << "Alpha" << endl;
        OPT.close();
        }







//=============================
// ----клик листбокс1------

void __fastcall TForm1::ListBox1Click(TObject *Sender)
{
Draw();
SendMessage_1("Polyline Attributes");
Form1->FormStyle = fsNormal;
}






//--------изменение опций-------------------------------------------------------------------
//========================
void __fastcall TForm1::Sort_ABCClick(TObject *Sender)
{
if (gLocked)
        return;
//по алфавиту
Form1->ListBox1->Items->Clear();
if (Form1->Sort_ABC->Checked)
        Form1->ListBox1->Items = Form1->Sname->Items;
SaveCh();
}







//=====================
//--------изменение опций-------------------------------------------------------------------

void __fastcall TForm1::Sort_n_pinsClick(TObject *Sender)
{
if (gLocked)
        return;
//по pins
Form1->ListBox1->Items->Clear();
if (Form1->Sort_n_pins->Checked) Form1->ListBox1->Items = Form1->Spins->Items;
SaveCh();
}
//=======================
//--------изменение опций-------------------------------------------------------------------

void __fastcall TForm1::Sort_n_holesClick(TObject *Sender)
{
if (gLocked)
        return;
//по holes
Form1->ListBox1->Items->Clear();
if (Form1->Sort_n_holes->Checked) Form1->ListBox1->Items = Form1->Sholes->Items;
SaveCh();
}

//=============================
//    Open PDF
//=============================
void Open_PDF (void)
{
ATTRIBUTE_FOOT();
A = catalog + "\\";
B = Form1->ListBox1->Items->operator [](Form1->ListBox1->ItemIndex);
C = B;
long k = prob(B,1);
if (Form1->Sort_ABC->Checked)
        B = B.SubString(1,1) + ".pdf";
else    {
        B = B.SubString(1,k-1);
        B = B.Trim() + ".pdf";
        if(B.SubString(1,1) == "\"")
                {
                long g=1;
                B = ex_str(B,&g);
                }
        C = C.SubString(k,(C.Length()-k+1));
        }
AnsiString ASD = ExtractFileName(B);
ASD = ASD + " - Adobe Reader";
if ((UINT)ShellExecute( NULL,
                        "open",
                        B.c_str(),
                        NULL,
                        A.c_str() ,
                        SW_SHOWNORMAL) <=32)
        {
        ShowMessage  ("  What program to open this file? There is no application associated with *.PDF files.");
        return;
        }
else
        {
        Clipboard()->Clear();
        Clipboard()->SetTextBuf(C.c_str());
        //-----
        /*i = 0;
        while (FindWindow( NULL,ASD.c_str()) == NULL)
                {
                Sleep(400);
                i++;
                if (i > 40) {ShowMessage ("Не найдено окно " + B); break;}
                }
        Sleep(800);
        SetForegroundWindow (FindWindow( NULL,ASD.c_str()));
        Sleep(1000);
        KEY ("ctrl", 1, 0, 30);
        KEY ("F", 1, 1, 30);
        KEY ("ctrl", 1, 1, 30);
        KEY ("ctrl", 1, 0, 30);
        KEY ("V", 1, 1, 30);
        KEY ("ctrl", 1, 1, 30);
        KEY ("ENTER", 1, 1, 30);  */
        //
        static int bMess = 0;
        if( bMess == 0 )
                ShowMessage ("  Footprint name copied to clipboard.");
        bMess = 1;
        }
}

//---------------------------------------------------------------------------
//=============================
// ----ДВОЙНОЙ клик листбокс1(редактор LENGTH-UP LENGTH-DOWN)------

void __fastcall TForm1::ListBox1DblClick(TObject *Sender)
{
if( Form1->bOpenPDF->Enabled )
        Open_PDF();
}//--------изменение строки адреса-------------------------------------------------------------------
//===========================
void __fastcall TForm1::Edit1Change(TObject *Sender)
{
if (gLocked)
        return;
SaveCh();
}




//---------------------------------------------------------------------------
//=========================
//чтение атрибутов футпринта
void ATTRIBUTE_FOOT (void)
{
  if (gLocked)
        return;

  i = Form1->ListBox1->ItemIndex;
  A = getDataPointInArray(&i,0);
  long k = 6;
  AnsiString name = ex_str(A,&k);
  hd = i;
  if( hd >= 0 )
        {
        Form1->NameEdit->Text = name;
        Form1->PackageEdit->Text = Packages[hd];
        Form1->AuthorEdit->Text = author[hd];
        Form1->DescEdit->Text = description[hd];
        }
}


//======================================
//----- чтение даты изменения библиотек
/*
void read_data_change_library (void)
{
AnsiString catalog_d = Form1->Edit1->Text;
TSearchRec sra_d;
  catalog_d = catalog_d.UpperCase();
  catalog_d = catalog_d.Trim();
  i = 0;
  if (FindFirst(catalog_d, faAnyFile, sra_d) == 0) {}
  else {FindClose(sra_d); return;}
  FindClose(sra_d);

TSearchRec(sr_d);
  i = 0;
  new_data = old_data;
  long long new_d;
if (FindFirst(catalog_d+"\\*", faAnyFile, sr_d) == 0)
     {
       do
         {
           if (sr_d.Attr & faDirectory) // directory                    //если каталог
              {
              }
           else
              {
               A = catalog_d + "\\" + sr_d.Name;
               if (A.UpperCase().SubString((A.Length()-3),4) == ".FPL")
                  {
                          std::map<std::string, FILETIME> report;
                          WIN32_FIND_DATAA findData;
                          HANDLE hFind;
                          SYSTEMTIME sutc, st;
                          hFind = FindFirstFileA(A.c_str(), &findData);
                          report[std::string(findData.cFileName)] = findData.ftLastWriteTime;
                          FindClose(hFind);
                          for ( std::map<std::string, FILETIME>::const_iterator i = report.begin(); i != report.end(); ++i )
                              {
                               FileTimeToSystemTime(&(i->second), &sutc);
                               SystemTimeToTzSpecificLocalTime(NULL, &sutc, &st);
                              }
                          new_d = 0;
                          new_d = (st.wYear-2000)*12*31*24*60;
                          new_d = new_d + st.wMonth*31*24*60;
                          new_d = new_d + st.wDay*24*60;
                          new_d = new_d + st.wHour*60;
                          new_d = new_d + st.wMinute;
                          if (new_d > new_data) new_data = new_d;
                  }//if (A.UpperCase().SubString((A.Length()-3),4) == ".FPL")
              }//если файл...
         } while (FindNext(sr_d) == 0);
     }//if (FindFirst(catalog+"\\*", faAnyFile, sr) == 0)
 FindClose(sr_d);
 if (new_data > old_data)
    {
     Flag_change_library = true;
     Flag_CHANGE_options = true;
    }
}

*/

//=====================================================
//------ кнопка Применить к библиотекам ===============
//=====================================================
void __fastcall TForm1::Button2Click(TObject *Sender)
{
if (gLocked)
        return;
if( MessageBox(NULL, "WARNING! By clicking the button to rewrite the footprint libraries, you agree to the total sorting of the footprints, their redistribution by files, the creation of new file names according to the selected sorting style, the deletion of old fpl file names and the inability to restore custom fpl names. If this is the first sorting of the selected library, then it is strongly recommended that you back up your library before modifying it.","", MB_OKCANCEL | MB_ICONWARNING) == IDCANCEL )
        return;
Form1->FormStyle = fsNormal;
//Если FreePCB не запущена...
if (FindWindow( NULL,"Log") == NULL)
        {
        if( arch_pth.Length())
                {
                RenameFile( arch_pth, arch_pth+"#" );
                }
        Attach_listbox1();
        FWRITE();
        SaveCh();
        exit(0);
        }
else    ShowMessage("  Close FreePcb window to modify the libraries!");
}











//================================
//--------DELETE_FILES------------
//================================
void DELETE_FILES (void)
{
 int b = 0;
 while (NAMES_old_files[b].Length() != 0)
       {
         DeleteFile(NAMES_old_files[b]);
         b++;
         if (NAMES_old_files[b].SubString(1,NAMES_old_files[b].Length()) == "end")
                break;
       }
 while (b > 0)
       {
         NAMES_old_files[b] = "";
         b--;
       }
 NAMES_old_files[b] = "end";
}
//
//
//
void __fastcall TForm1::Edit2Change(TObject *Sender)
{
FILTER();
Draw();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Edit3Change(TObject *Sender)
{
FILTER();
Draw();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit4Change(TObject *Sender)
{
FILTER();
Draw();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CheckBox2Click(TObject *Sender)
{
if (gLocked)
        return;
if(Form1->CheckBox2->Checked)
  {
    Form1->RadioButton6->Enabled = true;
    Form1->RadioButton7->Enabled = true;
    Form1->RadioButton8->Enabled = true;
    Form1->RadioButton9->Enabled = true;
    Form1->RadioButton10->Enabled = true;
    Form1->RadioButton11->Enabled = true;
    Form1->RadioButton12->Enabled = true;
  }
else
  {
    Form1->RadioButton6->Enabled = false;
    Form1->RadioButton7->Enabled = false;
    Form1->RadioButton8->Enabled = false;
    Form1->RadioButton9->Enabled = false;
    Form1->RadioButton10->Enabled = false;
    Form1->RadioButton11->Enabled = false;
    Form1->RadioButton12->Enabled = false;
  }
FILTER();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton6Click(TObject *Sender)
{
FILTER();        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton7Click(TObject *Sender)
{
FILTER();        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton8Click(TObject *Sender)
{
FILTER();        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton9Click(TObject *Sender)
{
FILTER();        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton10Click(TObject *Sender)
{
FILTER();        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton11Click(TObject *Sender)
{
FILTER();        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton12Click(TObject *Sender)
{
FILTER();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton3Click(TObject *Sender)
{
if (gLocked)
        return;
if (Form1->ListBox1->ItemIndex == -1)
        return;
if( bWarning1 == 0 )
        {
        MessageBox(NULL, "You can modify footprint attributes by pressing the MOD button, also you can delete footprints by pressing the DELETE button, but in order for all these changes to be saved you will need to press the REWRITE ALL LIB button on completion. Libraries will be rewritten according to the selected sorting style.","Info",MB_OK | MB_ICONINFORMATION);
        bWarning1 = 2;
        //return;
        }
  long id = Form1->ListBox1->ItemIndex;
  getDataPointInArray(&id,0);
  hd = id;
  Form1->Sort_ABC->Enabled =      Form1->Sort_ABC->Checked;
  Form1->Sort_n_pins->Enabled =   Form1->Sort_n_pins->Checked;
  Form1->Sort_n_holes->Enabled =  Form1->Sort_n_holes->Checked;
  Form1->Sort_author->Enabled =   Form1->Sort_author->Checked;
  Form1->Sort_desc->Enabled =     Form1->Sort_desc->Checked;
  A = Form1->ListBox1->Items->operator [](Form1->ListBox1->ItemIndex);
  Form1->ListBox1->Items->Delete(Form1->ListBox1->ItemIndex);
  DELETES[hd] = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer2Timer(TObject *Sender)
{
static bool rectDrawn = 0;
static bool FVis2 = 0;
static bool FVis3 = 0;
if (Form2 == NULL || Form3 == NULL)
        return;
if (gLocked)
        {
        if (Form1->Visible == true)
                Form4->Visible = true;
        Form1->Visible = false;
        Form2->Visible = false;
        Form3->Visible = false;
        return;
        }
else if (Form1->Visible == false)
        {
        Form2->Visible = FVis2;
        Form3->Visible = FVis3;
        }
//
Form1->Visible = true;
Form4->Visible = false;
FVis2 = Form2->Visible;
FVis3 = Form3->Visible;
//
Fill_Rect.Left = 0;//Form1->GroupBox3->Width + 30;
Fill_Rect.Top = 0;//84;
Fill_Rect.Right = Form1->Image1->Width;//   ClientWidth - 15;
Fill_Rect.Bottom = Form1->Image1->Height;//   ClientHeight - 30 - Form1->GroupBox1->Height;
if (Form2->Visible || Form3->Visible)
        Form1->ListBox1->ItemIndex = -1;
Form3->BCOMB->Enabled = true;
if (Form3->ListBox1->ItemIndex == -1)
        Form3->BCOMB->Enabled = false;
if (Form3->ListBox2->SelCount == 0)
        Form3->BCOMB->Enabled = false;
if (Form1->ListBox1->ItemIndex >= 0)
        {
        Form1->SpeedButton3->Enabled = true;
        Form1->bEditFoot->Enabled = true;
        rectDrawn = 0;
        }
else if (rectDrawn == 0)
        {
        Form1->bEditFoot->Enabled = false;
        Form1->bOpenPDF->Enabled = false;
        Form1->bOpenLib->Enabled = false;
        Form1->SpeedButton3->Enabled = false;
        if (FileName.Length())
                {
                Form1->bAddRefStr->Enabled = true;
                Form1->bAddShapeStr->Enabled = true;
                }
        else    {
                Form1->bAddRefStr->Enabled = false;
                Form1->bAddShapeStr->Enabled = false;
                }
        Image1->Canvas->Pen->Width = 1;
        Image1->Canvas->Pen->Color = clBlack;
        Image1->Canvas->Brush->Color = clBlack;//clBtnFace;
        Image1->Canvas->Rectangle(Fill_Rect.Left,Fill_Rect.Top,Fill_Rect.Right,Fill_Rect.Bottom);
        //
        if( PartJump.Length() )
                {
                Edit2->Text = PartJump;
                PartJump = "";
                Draw();
                }
        else if( Form1->ListBox1->Count )
                {
                Form1->ListBox1->ItemIndex = 0;
                Draw();
                }
        else    rectDrawn = 1;
        return;
        }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::bOpenPDFClick(TObject *Sender)
{
if (gLocked)
        return;
Open_PDF();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::bOpenLibClick(TObject *Sender)
{
if (gLocked)
        return;
if (Form1->ListBox1->ItemIndex == -1)
        return;
ATTRIBUTE_FOOT();
A = catalog + "\\";
B = Form1->ListBox1->Items->operator [](Form1->ListBox1->ItemIndex);
C = B;
long k = prob(B,1);
if (Form1->Sort_ABC->Checked)
        B = B.SubString(1,1) + ".fpl";
else    {
        B = B.SubString(1,k-1);
        B = B.Trim() + ".fpl";
        if(B.SubString(1,1) == "\"")
                {
                long g=1;
                B = ex_str(B,&g);
                }
        C = C.SubString(k,(C.Length()-k+1));
        }
//
Application->ProcessMessages();
//Sleep(500);
SHELLEXECUTEINFO info = {0};
AnsiString fn = ExtractFilePath(Application->ExeName);
fn.SetLength(fn.Length()-1);
fn = ExtractFilePath(fn);
fn.SetLength(fn.Length()-1);
fn = ExtractFilePath(fn) + "freepcb.exe";
AnsiString FN = ("\""+fn+"\"");
AnsiString ps = A+B;
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
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
SaveCh();
// remove old archive
DeleteDir(arch_pth);
exit(0);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button6Click(TObject *Sender)
{
if (gLocked)
        return;
if (Form1->ListBox1->ItemIndex == -1)
        return;
i = Form1->ListBox1->ItemIndex;
A = getDataPointInArray(&i,0);
if (i != -1)
        {
        Replace ( HEADERS[i], n_str[i], end_str[i]);
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button8Click(TObject *Sender)
{
if (gLocked)
        return;
if (Form1->OpenDialog1->Execute())
        {
        if (Form1->OpenDialog1->FileName.Length() == 0) return;
        A = Form1->OpenDialog1->FileName;
        if (A.UpperCase().SubString((A.Length()-3),4) != ".FPC")
                {
                ShowMessage ("    Error file format!");
                Button7->Enabled = false;
                bCombFoot->Enabled = false;
                return;
                }
        else
                {
                FileName = Form1->OpenDialog1->FileName;
                AnsiString CLPBRD = ExtractFileName (FileName);
                Form1->Caption = "Library replace for " + CLPBRD;
                Button7->Enabled = true;
                bCombFoot->Enabled = true;
                bAddRefStr->Enabled = true;
                bAddShapeStr->Enabled = true;
                }
        }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button7Click(TObject *Sender)
{
if (gLocked)
        return;
Replace ( "", 0, 0);
}
//---------------------------------------------------------------------------
void GenBuf( void )
{
i = Form1->ListBox1->ItemIndex;
AnsiString F = getDataPointInArray(&i,0);
if (i != -1)
        {
        A = ExtractFilePath(Application->ExeName);
        A = A + "Show.fpc";
        ofstream Show (A.c_str());
        Show << "[options]" << endl ;
        A = Form1->Edit1->Text;
        Show << "version: 2.1" << endl;
        Show << "file_version: 2.1" << endl ;
        Show << "n_copper_layers: 2" << endl ;
        Show << ("full_library_folder: \"" + A + "\"").c_str() << endl ;
        Show << "fp_placement_grid_spacing: 2540.0" << endl ;
        Show << "fp_placement_grid_item: 1MM" << endl ;
        Show << "fp_placement_grid_item: 0.8MM" << endl ;
        Show << "fp_placement_grid_item: 0.65MM" << endl ;
        Show << "fp_placement_grid_item: 0.5MM" << endl ;
        Show << "fp_placement_grid_item: 0.45MM" << endl ;
        Show << "fp_placement_grid_item: 0.35MM" << endl ;
        Show << "fp_placement_grid_item: 0.3MM" << endl ;
        Show << "fp_placement_grid_item: 0.25MM" << endl ;
        Show << "fp_placement_grid_item: 0.2MM" << endl ;
        Show << "fp_placement_grid_item: 0.1MM" << endl ;
        Show << "fp_placement_grid_item: 0.05MM" << endl ;
        Show << "fp_placement_grid_item: 0.04MM" << endl ;
        Show << "fp_placement_grid_item: 0.035MM" << endl ;
        Show << "fp_placement_grid_item: 0.03MM" << endl ;
        Show << "fp_placement_grid_item: 0.025MM" << endl ;
        Show << "fp_placement_grid_item: 0.02MM" << endl ;
        Show << "fp_placement_grid_item: 0.015MM" << endl ;
        Show << "fp_placement_grid_item: 0.01MM" << endl ;
        Show << "[footprints]" << endl ;
        i = n_str[i];
        long LEFT;
        long BOTTOM;
        long RIGHT;
        long TOP;
        AnsiString U;
        while(1)
                {
                Show << footprints[i].c_str() << endl ;
                i++;
                if (footprints[i].SubString(1,8) == "sel_rect")
                        {
                        long m = prob(footprints[i],1);
                        LEFT =          ex_float_NM(footprints[i],&m,&U);
                        BOTTOM =        ex_float_NM(footprints[i],&m,&U);
                        RIGHT =         ex_float_NM(footprints[i],&m,&U);
                        TOP =           ex_float_NM(footprints[i],&m,&U);
                        }
                else if (footprints[i].SubString(1,5) == "units")
                        {
                        long m = prob(footprints[i],1);
                        U = footprints[i].SubString(m,(footprints[i].Length()-m+1));
                        }
                if (footprints[i].SubString(1,3) == "end")      break;
                if (footprints[i].SubString(1,5) == "name:")     break;
                }
        Show << "[board]" << endl ;
        /*Show << "outline: 4 0" << endl ;
        // corner 1
        Show << "corner: 1 ";
        Show << AnsiString(LEFT-MLN).c_str();
        Show << " ";
        Show << AnsiString(BOTTOM-3000000).c_str();
        Show << " 0" << endl ;
        // corner 2
        Show << "corner: 2 ";
        Show << AnsiString(LEFT-MLN).c_str();
        Show << " ";
        Show << AnsiString(TOP+MLN).c_str();
        Show << " 0" << endl ;
        // corner 3
        Show << "corner: 3 ";
        Show << AnsiString(RIGHT+MLN).c_str();
        Show << " ";
        Show << AnsiString(TOP+MLN).c_str();
        Show << " 0" << endl ;
        // corner 4
        Show << "corner: 4 ";
        Show << AnsiString(RIGHT+MLN).c_str();
        Show << " ";
        Show << AnsiString(BOTTOM-3000000).c_str();
        Show << " 0" << endl ;   */

        Show << "[solder_mask_cutouts]" << endl ;
        Show << "[graphics]" << endl ;
        Show << "[parts]" << endl ;
        Show << "part: VIA1" << endl ;
        Show << "ref_text: 0 0 0 ";
        Show << AnsiString(LEFT).c_str();
        Show << " ";
        Show << AnsiString(BOTTOM-MLN).c_str() << endl ;
        Show << "value: \"\" 500000 100000 0 ";
        Show << AnsiString(LEFT).c_str();
        Show << " ";
        Show << AnsiString(BOTTOM-2000000).c_str() << endl ;
        Show << ("package: \"" + F.SubString(8,(F.Length()-8)) + "\"").c_str() << endl ;
        Show << ("shape: \"" + F.SubString(8,(F.Length()-8)) + "\"").c_str() << endl ;
        Show << "pos: 0 0 0 0 0" << endl ;
        Show << "[nets]" << endl ;
        Show << "[texts]" << endl ;
        Show << "[merges]" << endl ;
        Show << "[end]" << endl ;
        Show.close();
        }
Application->ProcessMessages();
Sleep(500);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::bEditFootClick(TObject *Sender)
{
if (gLocked)
        return;
if (Form1->ListBox1->ItemIndex == -1)
        return;
GenBuf();
//
SHELLEXECUTEINFO info = {0};
AnsiString fn = ExtractFilePath(Application->ExeName);
AnsiString ps = fn + "Show.fpc";
fn.SetLength(fn.Length()-1);
fn = ExtractFilePath(fn);
fn.SetLength(fn.Length()-1);
fn = ExtractFilePath(fn) + "freepcb.exe";
AnsiString FN = ("\""+fn+"\"");
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
}
//---------------------------------------------------------------------------

void __fastcall TForm1::bAddRefStrClick(TObject *Sender)
{
if (gLocked)
        return;
Form2->RadioButtonRef->Checked = true;
Form2->RadioButtonShape->Checked = false;
Form2->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::bAddShapeStrClick(TObject *Sender)
{
if (gLocked)
        return;
Form2->RadioButtonShape->Checked = true;
Form2->RadioButtonRef->Checked = false;
Form2->Visible = true;
}
//---------------------------------------------------------------------------




void __fastcall TForm1::bCombFootClick(TObject *Sender)
{
if (gLocked)
        return;
Form3->Visible = true;
Form3->Ini();
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Sort_authorClick(TObject *Sender)
{
if (gLocked)
        return;
//по author
Form1->ListBox1->Items->Clear();
if (Form1->Sort_author->Checked)
        Form1->ListBox1->Items = Form1->Sauthor->Items;
SaveCh();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Sort_descClick(TObject *Sender)
{
if (gLocked)
        return;
//по descript
Form1->ListBox1->Items->Clear();
if (Form1->Sort_desc->Checked) Form1->ListBox1->Items = Form1->Sdescript->Items;
SaveCh();
}
//---------------------------------------------------------------------------



void __fastcall TForm1::RClick(TObject *Sender)
{
if (gLocked)
        return;
READ_CATALOG();
}
//---------------------------------------------------------------------------




void __fastcall TForm1::ModClick(TObject *Sender)
{
if (gLocked)
        return;
if (Form1->ListBox1->ItemIndex == -1)
        return;
if( bWarning1 == 0 )
        {
        MessageBox(NULL, "You can modify footprint attributes by pressing the MOD button, also you can delete footprints by pressing the DELETE button, but in order for all these changes to be saved you will need to press the REWRITE ALL LIB button on completion. Libraries will be rewritten according to the selected sorting style.","Info",MB_OK | MB_ICONINFORMATION);
        bWarning1 = 1;
        //return;
        }
if( Form1->ListBox1->ItemIndex >= 0 )
        {
        int ic = Form1->ListBox1->ItemIndex;
        int sic = ic;
        long id = ic;
        getDataPointInArray(&id,0);
        hd = id;
        AnsiString CS = Form1->NameEdit->Text;
        CS = "name: \"" + CS + "\"";
        //int CSL = CS.Length();

        AnsiString find = Form1->ListBox1->Items->operator [](ic);
        // disabled
        Form1->Sort_ABC->Enabled =      Form1->Sort_ABC->Checked;
        Form1->Sort_n_pins->Enabled =   Form1->Sort_n_pins->Checked;
        Form1->Sort_n_holes->Enabled =  Form1->Sort_n_holes->Checked;
        Form1->Sort_author->Enabled =   Form1->Sort_author->Checked;
        Form1->Sort_desc->Enabled =     Form1->Sort_desc->Checked;
        //
        Form1->ListBox1->Items->Delete(ic);
        A = Form1->NameEdit->Text;
        HEADERS[hd] = CS;
        Packages[hd] = Form1->PackageEdit->Text;
        AnsiString old_auth = author[hd];
        author[hd] = Form1->AuthorEdit->Text;
        AnsiString old_desc = description[hd];
        description[hd] = Form1->DescEdit->Text;
        //
        if (Form1->Sort_ABC->Checked)
                {
                ic = Form1->Sname->Items->IndexOf(find);
                Form1->Sname->Items->Delete(ic);
                Form1->Sname->Items->Add(A);
                }
        else if (Form1->Sort_n_pins->Checked)
                {
                if      (n_pins[hd] > 999)      A = "999pins " + A;
                else if (n_pins[hd] > 99)       A = AnsiString(n_pins[hd]) + "pins " + A;
                else if (n_pins[hd] > 9)        A = AnsiString("0") + n_pins[hd] + "pins " + A;
                else if (n_pins[hd] > 0)        A = AnsiString("00") + n_pins[hd] + "pins " + A;
                else                            A = AnsiString("000") + "pins " + A;
                int k=prob(find,1);
                AnsiString old_str = find.SubString(k,find.Length()-k+1);
                if      (n_pins[hd] > 999)      find = "999pins " + old_str;
                else if (n_pins[hd] > 99)       find = AnsiString(n_pins[hd]) + "pins " + old_str;
                else if (n_pins[hd] > 9)        find = AnsiString("0") + n_pins[hd] + "pins " + old_str;
                else if (n_pins[hd] > 0)        find = AnsiString("00") + n_pins[hd] + "pins " + old_str;
                else                            find = AnsiString("000") + "pins " + old_str;
                ic = Form1->Spins->Items->IndexOf(find);
                Form1->Spins->Items->Delete(ic);
                Form1->Spins->Items->Add(A);
                }
        else if (Form1->Sort_n_holes->Checked)
                {
                if      (n_holes[hd] > 999)     A = "999holes " + A;
                else if (n_holes[hd] > 99)      A = AnsiString(n_holes[hd]) + "holes " + A;
                else if (n_holes[hd] > 9)       A = AnsiString("0") + n_holes[hd] + "holes " + A;
                else if (n_holes[hd] > 0)       A = AnsiString("00") + n_holes[hd] + "holes " + A;
                else                            A = AnsiString("000") + "holes " + A;
                int k=prob(find,1);
                AnsiString old_str = find.SubString(k,find.Length()-k+1);
                if      (n_holes[hd] > 999)     find = "999holes " + old_str;
                else if (n_holes[hd] > 99)      find = AnsiString(n_holes[hd]) + "holes " + old_str;
                else if (n_holes[hd] > 9)       find = AnsiString("0") + n_holes[hd] + "holes " + old_str;
                else if (n_holes[hd] > 0)       find = AnsiString("00") + n_holes[hd] + "holes " + old_str;
                else                            find = AnsiString("000") + "holes " + old_str;
                ic = Form1->Sholes->Items->IndexOf(find);
                Form1->Sholes->Items->Delete(ic);
                Form1->Sholes->Items->Add(A);
                }
        else if (Form1->Sort_author->Checked)
                {
                A = "\"" + author[hd] + "\" " + A;
                int k=prob(find,1);
                AnsiString old_str = find.SubString(k,find.Length()-k+1);
                find = "\"" + old_auth + "\" " + old_str;
                ic = Form1->Sauthor->Items->IndexOf(find);
                Form1->Sauthor->Items->Delete(ic);
                Form1->Sauthor->Items->Add(A);
                }
        else if (Form1->Sort_desc->Checked)
                {
                A = "\"" + description[hd] + "\" " + A;
                int k=prob(find,1);
                AnsiString old_str = find.SubString(k,find.Length()-k+1);
                find = "\"" + old_desc + "\" " + old_str;
                ic = Form1->Sdescript->Items->IndexOf(find);
                Form1->Sdescript->Items->Delete(ic);
                Form1->Sdescript->Items->Add(A);
                }
        Form1->ListBox1->Items->Add(A);
        Form1->ListBox1->ItemIndex = sic;
        }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Label3Click(TObject *Sender)
{
ShellExecute(NULL, "open", "https://github.com/Duxah/FreePCB-2/blob/master/README.md", NULL, NULL, SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormMouseWheelDown(TObject *Sender,
      TShiftState Shift, TPoint &MousePos, bool &Handled)
{
if( MousePos.x - Form1->Left - Form1->Image1->Left > Fill_Rect.left &&
    MousePos.x - Form1->Left - Form1->Image1->Left < Fill_Rect.right &&
    MousePos.y - Form1->Top - Form1->Image1->Top >  Fill_Rect.top &&
    MousePos.y - Form1->Top - Form1->Image1->Top <  Fill_Rect.bottom )
        {
        m_scale += 50000;
        //m_ccx = -((Fill_Rect.left+Fill_Rect.right)/2 - MousePos.x + Form1->Left + Form1->Image1->Left)*m_scale/100;
        //m_ccy = -((Fill_Rect.top+Fill_Rect.bottom)/2 - MousePos.y + Form1->Top + Form1->Image1->Top)*m_scale/100;
        Draw();
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormMouseWheelUp(TObject *Sender,
      TShiftState Shift, TPoint &MousePos, bool &Handled)
{
if( MousePos.x - Form1->Left - Form1->Image1->Left > Fill_Rect.left &&
    MousePos.x - Form1->Left - Form1->Image1->Left < Fill_Rect.right &&
    MousePos.y - Form1->Top - Form1->Image1->Top >  Fill_Rect.top &&
    MousePos.y - Form1->Top - Form1->Image1->Top <  Fill_Rect.bottom )
        {
        m_scale -= 50000;
        //m_ccx = -((Fill_Rect.left+Fill_Rect.right)/2 - MousePos.x + Form1->Left + Form1->Image1->Left)*m_scale/100;
        //m_ccy = -((Fill_Rect.top+Fill_Rect.bottom)/2 - MousePos.y + Form1->Top + Form1->Image1->Top)*m_scale/100;
        Draw();
        }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Image1MouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
//if( ABS(m_scale) > MLN )
//        {
//        m_ccx = -((Fill_Rect.left+Fill_Rect.right)/2 - X)*m_scale/100;
//        m_ccy = -((Fill_Rect.top+Fill_Rect.bottom)/2 - Y)*m_scale/100;
//        Draw();
//        }        
}
//---------------------------------------------------------------------------

int __fastcall TForm1::OnWMCopyData(TWMCopyData &Msg)
{
        Form1->FormStyle = fsStayOnTop;
        Form1->Edit2->Text = (char*)Msg.CopyDataStruct->lpData;
        //Application->ProcessMessages();
        return 0;
}




void __fastcall TForm1::FormCreate(TObject *Sender)
{
Form1->Width = 326;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
if( Form1->Width == 326 )
        {
        Form1->Width = 632;
        Form1->Button3->Caption = "<<";
        }
else    {
        Form1->Width = 326;
        Form1->Button3->Caption = ">>";
        }
//Form1->Button3->Left = Form1->Width - 43;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CheckBox1Click(TObject *Sender)
{

if(Form1->CheckBox1->Checked && Form1->ListBox1->Count)
        {
        //Form4->Visible = true;
        //Form1->Visible = false;
        //Form2->Visible = false;
        //Form3->Visible = false;
        //Form4->Timer1->Enabled = true;
        //int total = Form1->ListBox1->Count;
        //int wrt = Form1->ListBox1->Count/50;
        //Form4->comment->Caption = "";
        int * Flags = new int[Form1->ListBox1->Count];
        for(int q=0; q<Form1->ListBox1->Count; q++)
                Flags[q] = 0;
        for(int id=Form1->ListBox1->Count-1; id>=0; id--)
                {
                if( Flags[id] )
                        continue;
                AnsiString str = Form1->ListBox1->Items->operator [](id);
                int iof = Form1->ListBox1->Items->IndexOf(str);
                if(iof != id)
                        Flags[iof] = 1;
                else    Form1->ListBox1->Items->Delete(id);
                
                //if( id%wrt == 0 )
                //        {
                //        Form4->comment->Caption = AnsiString(total-id) + " from " + AnsiString(total);
                //        Application->ProcessMessages();
                //        }
                }
        delete Flags;
        //Form4->Visible = 0;
        //Form1->Visible = 1;
        //Form4->Timer1->Enabled = false;
        }
else    FILTER();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::bPasteClick(TObject *Sender)
{
SendMessage_2(WinHeader);
}
//---------------------------------------------------------------------------

