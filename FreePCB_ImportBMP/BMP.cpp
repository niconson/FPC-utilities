//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <fstream.h>
#include "BMP.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
int H;
int W;
int x;
int y;
int XY[2];
int lns = 0;
int pds = 0;
int P;
int Px;
double Wpixel;
double Hpixel;
double Size_X;
double Size_Y;
double W_line;
double Set_W;
double x0;
double y0;
bool Flag_MAXPOINT = false;
long  color;
TRect RecT;
AnsiString LINES[100000];
AnsiString PADS[100000];
Graphics::TBitmap *Bmp = new Graphics::TBitmap;
void ReadBMP(void);
bool Find_pixel_func (bool Flag_Begin_Line, bool UPPERCASE);
bool TRIGGER (int X_pix, int Y_pix);
void CANVA (int CASE);
void PLACE_POINT (double XP, double YP, double WP);
long long prob (AnsiString ANSI , long long Pr);
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
DecimalSeparator = ',';
if (OpenPictureDialog1->Execute())  {}
else exit(0);
Bmp->LoadFromFile(OpenPictureDialog1->FileName);
Timer1->Enabled = true;
RadioButton1->Checked = true;
CheckBox1->Checked = true;
CheckBox2->Checked = true;
for( int i=1; i<=20; i++ )
        ComboBox1->Items->Add(AnsiString(i));
ComboBox1->ItemIndex = 0;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button1Click(TObject *Sender)
{
Timer1->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
if (GetKeyState(VK_LBUTTON) & 0x800)
        return;
Timer1->Enabled = false;
Timer1->Interval = 500;
if( RadioButton4->Checked == 0 )
        {
        FRS->Checked = 0;
        FPC->Checked = 1;
        FRS->Enabled = 0;
        }
else    {
        FRS->Enabled = 1;
        }
Flag_MAXPOINT = false;
Button2->Enabled = false;
lns = 1;
while (lns <= Edit1->Text.Length())
      {
       if ((Edit1->Text.SubString(lns,1) < "0") || (Edit1->Text.SubString(lns,1) > "9"))
       if (Edit1->Text.SubString(lns,1) != ",") return;
       lns++;
      }
lns = 1;
while (lns <= Edit2->Text.Length())
      {
       if ((Edit2->Text.SubString(lns,1) < "0") || (Edit2->Text.SubString(lns,1) > "9"))
       if (Edit2->Text.SubString(lns,1) != ",") return;
       lns++;
      }
lns = 1;
while (lns <= Edit3->Text.Length())
      {
       if ((Edit3->Text.SubString(lns,1) < "0") || (Edit3->Text.SubString(lns,1) > "9"))
       if (Edit3->Text.SubString(lns,1) != ",") return;
       lns++;
      }
if (Edit1->Text.Length() == 0) Edit1->Text = "0,0" ;
if (Edit2->Text.Length() == 0) Edit2->Text = "0,0" ;
if (Edit3->Text.Length() == 0) Set_W = 1;
//
Bmp->LoadFromFile(OpenPictureDialog1->FileName);
P =  StrToInt(ComboBox1->Items->operator [](ComboBox1->ItemIndex));
if( P > 1 )
        {
        int new_y = 0;
        for( int gy=0; gy<Bmp->Height; gy+=P )
                {
                for( int gx=0; gx<Bmp->Width; gx++ )
                        {
                        Bmp->Canvas->Pixels[gx][new_y] = Bmp->Canvas->Pixels[gx][gy];
                        }
                new_y++;
                }
        Bmp->Height = new_y;
        }
P = 1;
Px = 1;//StrToInt(ComboBox1->Items->operator [](ComboBox1->ItemIndex));
H = Bmp->Height ;
W = Bmp->Width ;
Size_X = StrToFloat(Edit1->Text);
Size_Y = StrToFloat(Edit2->Text);
if (Edit3->Text.Length()) Set_W = StrToFloat(Edit3->Text);
if ((Size_X < 0.5)||(Size_Y < 0.5))
   {
     ShowMessage("   ћинимальный размер изображени€ 0.5х0.5 мм! ");
     return;
   }
GroupBox1->Enabled = false;
Button1->Enabled = false;
Bmp->Transparent = true;
Canvas->Pen->Color = (TColor)RGB(255,0,0);
Canvas->Pen->Width = 1;
int CanvW = Form1->ClientWidth;
int CanvH = Form1->ClientHeight - Form1->GroupBox1->Height - 20;
Canvas->Rectangle(0,0,CanvW,CanvH);
Wpixel = (double)CanvW/(double)W;
Hpixel = (double)CanvH/(double)H;
double W_canv;
if (Set_W) W_canv = Size_X/(double)Set_W;
else W_canv = CanvW;
Canvas->Pen->Color = (TColor)RGB(0,0,0);
Size_X = Size_X*1000000;
Size_Y = Size_Y*1000000;
Size_X = (double)Size_X/(double)W;
Size_Y = (double)Size_Y/(double)H;
if (RadioButton1->Checked == true)
   {
    W_line = Size_Y + (double)Size_Y/(double)5;
    Canvas->Pen->Width = (int)Hpixel + (int)Hpixel/5 + 1;
   }
else
   {
    W_line = Set_W*1000000;
    Canvas->Pen->Width = CanvW/W_canv + 1;
   }
x = 0;
y = 0;
lns = 0;
pds = 0;
bool FLAG = false;
bool Ch5 = Form1->RadioButton5->Checked;
while (y < H)
        {
        while (x < W)
                {
                if (TRIGGER(x,y))
                        {
                        if (Form1->RadioButton3->Checked)
                                {
                                if (CheckBox1->Checked)
                                        {
                                        if (((FLAG == false) && (P == 1)) || ((TRIGGER(x,(y-1)) == 0) && (y) && (Px == 1)))
                                                {
                                                //PLACE POINT
                                                x0 = (double)Size_X*(double)x;
                                                y0 = (double)Size_Y*(double)y;
                                                PLACE_POINT (x0, y0, W_line);
                                                if (RadioButton3->Checked) CANVA (4);
                                                }
                                        }
                                if (CheckBox2->Checked)
                                        {
                                        if ((P == 1) && (Px == 1))
                                                {
                                                //PLACE POINT
                                                x0 = (double)Size_X*(double)x;
                                                y0 = (double)Size_Y*(double)y;
                                                PLACE_POINT (x0, y0, W_line);
                                                if (RadioButton3->Checked) CANVA (4);
                                                }
                                        }
                                }
                        if (FLAG == false)
                                {
                                if (Ch5)
                                        {
                                        Ch5 = false;
                                        //PLACE POINT
                                        x0 = (double)Size_X*(double)x;
                                        y0 = (double)Size_Y*(double)y;
                                        PLACE_POINT (x0, y0, W_line);
                                        if (RadioButton3->Checked) CANVA (4);
                                        }
                                x0 = (double)Size_X*(double)x;
                                y0 = (double)Size_Y*(double)y;
                                //CONTOUR
                                if (CheckBox1->Checked == true)
                                        {
                                        if (Find_pixel_func (1,0))
                                                {
                                                LINES[lns] = "outline_polyline: ";
                                                LINES[lns] += (long long)W_line;
                                                LINES[lns] += " ";
                                                LINES[lns] += (long long)Size_X*XY[0];
                                                LINES[lns] += " ";
                                                LINES[lns] += -(long long)Size_Y*XY[1];
                                                lns++;
                                                LINES[lns] = "next_corner: ";
                                                LINES[lns] += (long long)x0;
                                                LINES[lns] += " ";
                                                LINES[lns] += -(long long)y0;
                                                LINES[lns] += " 0";
                                                lns++;
                                                if (!RadioButton3->Checked) CANVA (1);
                                                }
                                        if (Find_pixel_func (1,1))
                                                {
                                                LINES[lns] = "outline_polyline: ";
                                                LINES[lns] += (long long)W_line;
                                                LINES[lns] += " ";
                                                LINES[lns] += (long long)Size_X*XY[0];
                                                LINES[lns] += " ";
                                                LINES[lns] += -(long long)Size_Y*XY[1];
                                                lns++;
                                                LINES[lns] = "next_corner: ";
                                                LINES[lns] += (long long)x0;
                                                LINES[lns] += " ";
                                                LINES[lns] += -(long long)y0;
                                                LINES[lns] += " 0";
                                                lns++;
                                                if (!RadioButton3->Checked) CANVA (1);
                                                }
                                        }//if (CheckBox1->Checked == true)
                                        //POURED
                                if (P == 1)
                                if (CheckBox2->Checked == true)
                                        {
                                        if (!RadioButton3->Checked) CANVA (2);
                                        LINES[lns] = "outline_polyline: ";
                                        LINES[lns] += (long long)W_line;
                                        LINES[lns] += " ";
                                        LINES[lns] += (long long)x0;
                                        LINES[lns] += " ";
                                        LINES[lns] += -(long long)y0;
                                        lns++;
                                        }
                                }//if (FLAG == false)
                        FLAG = true;
                        }//if (TRIGGER(x,y))
                else
                        {
                        if (Form1->RadioButton3->Checked)
                        if (CheckBox1->Checked)
                                {
                                if (((FLAG == true) && (P == 1)) || ((TRIGGER(x,(y-1))) && (y) && (Px == 1)))
                                        {
                                        //PLACE POINT
                                        x0 = (double)Size_X*(double)x;
                                        y0 = (double)Size_Y*(double)y;
                                        PLACE_POINT (x0, y0, W_line);
                                        if (RadioButton3->Checked) CANVA (4);
                                        }
                                }
                        if (FLAG == true)
                                {
                                x--;
                                x0 = (double)Size_X*(double)x;
                                y0 = (double)Size_Y*(double)y;
                                //POURED
                                if (P == 1)
                                if (CheckBox2->Checked == true)
                                        {
                                        if (!RadioButton3->Checked) CANVA (3);
                                        double x_canv = Wpixel*x+10 + Wpixel/2;
                                        double y_canv = Hpixel*y+10 + Hpixel/2;
                                        Canvas->LineTo((int)x_canv,(int)y_canv);
                                        LINES[lns] = "next_corner: ";
                                        LINES[lns] += (long long)x0;
                                        LINES[lns] += " ";
                                        LINES[lns] += -(long long)y0;
                                        LINES[lns] += " 0";
                                        lns++;
                                        }
                                //CONTOUR
                                if (CheckBox1->Checked == true)
                                        {
                                        if (Find_pixel_func (0,0))
                                                {
                                                LINES[lns] = "outline_polyline: ";
                                                LINES[lns] += (long long)W_line;
                                                LINES[lns] += " ";
                                                LINES[lns] += (long long)Size_X*(XY[0]);
                                                LINES[lns] += " ";
                                                LINES[lns] += -(long long)Size_Y*(XY[1]);
                                                lns++;
                                                LINES[lns] = "next_corner: ";
                                                LINES[lns] += (long long)x0;
                                                LINES[lns] += " ";
                                                LINES[lns] += -(long long)y0;
                                                LINES[lns] += " 0";
                                                lns++;
                                                if (!RadioButton3->Checked) CANVA (1);
                                                }
                                        if (Find_pixel_func (0,1))
                                                {
                                                LINES[lns] = "outline_polyline: ";
                                                LINES[lns] += (long long)W_line;
                                                LINES[lns] += " ";
                                                LINES[lns] += (long long)Size_X*(XY[0]);
                                                LINES[lns] += " ";
                                                LINES[lns] += -(long long)Size_Y*(XY[1]);
                                                lns++;
                                                LINES[lns] = "next_corner: ";
                                                LINES[lns] += (long long)x0;
                                                LINES[lns] += " ";
                                                LINES[lns] += -(long long)y0;
                                                LINES[lns] += " 0";
                                                lns++;
                                                if (!RadioButton3->Checked) CANVA (1);
                                                }
                                        } //if (CheckBox1->Checked == true)
                                x++;
                                }//if (FLAG == true)
                        FLAG = false;
                        }//if (TRIGGER(x,y))
                x++;
                ////Px--;
                ////if (Px == 0)
                ////        Px = StrToInt(ComboBox1->Items->operator [](ComboBox1->ItemIndex));
                if (Flag_MAXPOINT)
                        {
                        Form1->ComboBox1->ItemIndex++;
                        Form1->Timer1->Enabled = true;
                        return;
                        }
                }//while (x < W)
        if (FLAG == true)
                {
                FLAG = false;
                x--;
                x0 = (double)Size_X*(double)x;
                y0 = (double)Size_Y*(double)y;
                //POURED
                if (P == 1)
                if (CheckBox2->Checked == true)
                        {
                        if (!RadioButton3->Checked) CANVA (3);
                        x0 = (double)Size_X*(double)x;
                        y0 = (double)Size_Y*(double)y;
                        LINES[lns] = "next_corner: ";
                        LINES[lns] += (long long)x0;
                        LINES[lns] += " ";
                        LINES[lns] += -(long long)y0;
                        LINES[lns] += " 0";
                        lns++;
                        }
                //CONTOUR
                if (CheckBox1->Checked == true)
                        {
                        if (Find_pixel_func (0,0))
                                {
                                LINES[lns] = "outline_polyline: ";
                                LINES[lns] += (long long)W_line;
                                LINES[lns] += " ";
                                LINES[lns] += (long long)Size_X*XY[0];
                                LINES[lns] += " ";
                                LINES[lns] += -(long long)Size_Y*XY[1];
                                lns++;
                                LINES[lns] = "next_corner: ";
                                LINES[lns] += (long long)x0;
                                LINES[lns] += " ";
                                LINES[lns] += -(long long)y0;
                                LINES[lns] += " 0";
                                lns++;
                                if (!RadioButton3->Checked) CANVA (1);
                                }
                        if (Find_pixel_func (0,1))
                                {
                                LINES[lns] = "outline_polyline: ";
                                LINES[lns] += (long long)W_line;
                                LINES[lns] += " ";
                                LINES[lns] += (long long)Size_X*XY[0];
                                LINES[lns] += " ";
                                LINES[lns] += -(long long)Size_Y*XY[1];
                                lns++;
                                LINES[lns] = "next_corner: ";
                                LINES[lns] += (long long)x0;
                                LINES[lns] += " ";
                                LINES[lns] += -(long long)y0;
                                LINES[lns] += " 0";
                                lns++;
                                if (!RadioButton3->Checked) CANVA (1);
                                }
                        }// if (CheckBox1->Checked == true)
                x++;
                }//if (FLAG == true)
        y++;
        x = 0;
        if (lns > 99000)
                {
                MessageBox( Form1->Handle, "Wow! You got too many lines. So many lines are not practical and can slow down the computer. Try changing the drawing settings in the options menu.", "", MB_ICONWARNING);
                break;
                }
        }//while (y < H)
if ((Form1->RadioButton4->Checked) || (Form1->RadioButton5->Checked))
        {
        Label6->Caption = AnsiString("Total lines: ") + lns/2;
        Label6->Caption = Label6->Caption + AnsiString("    Size of: ") + Edit1->Text;
        Label6->Caption = Label6->Caption + "x" + Edit2->Text;
        W_line = W_line/(double)1000000;
        AnsiString G = FormatFloat("0.00",W_line);
        Label6->Caption = Label6->Caption + "     Line width: " + G;
        }
else
        {
        Label6->Caption = AnsiString("Total point: ") + pds/2;
        Label6->Caption = Label6->Caption + AnsiString("    Size of: ") + Edit1->Text;
        Label6->Caption = Label6->Caption + "x" + Edit2->Text;
        W_line = W_line/(double)1000000;
        AnsiString G = FormatFloat("0.00",W_line);
        Label6->Caption = Label6->Caption + "     Points diameter: " + G;
        }
Button1->Enabled = true;
Button2->Enabled = true;
GroupBox1->Enabled = true;
Link->Refresh();
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Button2Click(TObject *Sender)
{
AnsiString S = ExtractFilePath (Application->ExeName);
if( FRS->Checked )
        S = S + "BMP.frs";
else    S = S + "BMP.fpc";
ofstream FPC (S.c_str()) ;
S = ExtractFileName(OpenPictureDialog1->FileName);
FPC << "[options]" << endl << endl;
if( FRS->Checked )
        {
        FPC << "version: 1.0" << endl;
        FPC << "file_version: 1.0" << endl;
        }
else    {
        FPC << "version: 2.028" << endl;
        FPC << "file_version: 2.028" << endl;
        }
FPC << "units: MM" << endl;
FPC << "n_copper_layers: 2" << endl;
FPC << "visible_grid_spacing: 2540000" << endl;
FPC << "visible_grid_item: 2.54MM" << endl;
FPC << "placement_grid_spacing: 1000" << endl;
FPC << "placement_grid_item: 0.001MM" << endl;
FPC << "routing_grid_spacing: 500" << endl;
FPC << "routing_grid_item: 0.0005MM" << endl;
FPC << "fp_visible_grid_spacing: 2540000" << endl;
FPC << "fp_visible_grid_item: 2.54MM" << endl;
FPC << "fp_placement_grid_spacing: 1000" << endl;
FPC << "fp_placement_grid_item: 0.001MM" << endl;
FPC << "[footprints]" << endl;
 if( FRS->Checked )
        FPC << "rename_page: \"First page\"" << endl;
FPC << "name: \"";
FPC << S.c_str();
FPC << "\"" << endl;
FPC << "units: NM" << endl;
FPC << "sel_rect: 0 ";
FPC << AnsiString(-(long long)Size_Y*(long long)H).c_str();
FPC << " ";
FPC << AnsiString((long long)Size_X*(long long)W).c_str();
FPC << " 0" << endl;
FPC << "ref_text: 1000000 0 0 0 100000" << endl;
FPC << "value_text: 1000000 0 1000000 0 100000" << endl;
FPC << "centroid: 0 ";
FPC << AnsiString((long long)Size_X*(long long)W/2).c_str();
FPC << " ";
FPC << AnsiString(-(long long)Size_Y*(long long)H/2).c_str();
FPC << " 0" << endl;
if (Form1->RadioButton4->Checked)
        {
        for (int i = 0; i<lns; i++)
                {
                FPC << LINES[i].c_str() << endl;
                }
        FPC << "n_pins: 0" << endl << endl;
        }
else if (Form1->RadioButton3->Checked)
        {
        FPC << ("n_pins: " + AnsiString(pds/2)).c_str() << endl;
        for (int i = 0; i<pds; i++)
                {
                FPC << PADS[i].c_str() << endl;
                }
        FPC << endl;
        }
else
        {
        FPC << "n_pins: 1" << endl;
        FPC << PADS[0].c_str() << endl;
        FPC << PADS[1].c_str() << endl;
        }
if( FRS->Checked )
        {
        FPC << "part_end" << endl;
        FPC << "view_all" << endl;
        }
FPC << "[board]" << endl;
FPC << "[solder_mask_cutouts]" << endl;
FPC << "[graphics]" << endl;

FPC << "[parts]" << endl << endl;
FPC << "part: Image1" << endl;
FPC << "ref_text: 500000 100000 0 0 0 0" << endl;
FPC << "value: \"Bitmap ";
FPC << AnsiString(W).c_str();
FPC << "x";
FPC << AnsiString(H).c_str();
FPC << "\" 500000 100000 0 0 -1000000 0" << endl;
FPC << "package: \"";
FPC << S.c_str();
FPC << "\"" << endl;
FPC << "shape: \"";
FPC << S.c_str();
FPC << "\"" << endl;
FPC << "pos: 0 0 0 0 0" << endl << endl;
FPC << "[nets]" << endl;
if (Form1->RadioButton5->Checked)
        {
        FPC << "net: \"IMAGE\" 1 1 0 0 0 0 1" << endl;
        FPC << "pin: 1 Image1.1" << endl;
        FPC << "connect: 1 0 -1 ";
        FPC << AnsiString(lns-1).c_str();
        FPC << " 1" << endl;
        int x = 0;
        int y = 0;
        AnsiString W;
        for (int i = 0; i<lns; i = i+2)
                {
                //---
                x = prob (LINES[i],1);
                y = prob (LINES[i],2);
                y = y-x-1;
                W = LINES[i].SubString(x,y);
                FPC << "vtx: ";
                FPC << (AnsiString(i+1) + " ").c_str();
                x = prob (LINES[i],2);
                y = LINES[i].Length()-x+1;
                FPC << (LINES[i].SubString(x,y) + " 12 0 0 0 0").c_str() << endl;
                FPC << "seg: ";
                FPC << (AnsiString(i+1) + " 12 ").c_str();
                FPC << W.c_str();
                FPC << " 0 0" << endl;
                //---
                FPC << "vtx: ";
                FPC << (AnsiString(i+2) + " ").c_str();
                x = prob (LINES[i+1],1);
                y = prob (LINES[i+1],3);
                y = y-x-1;
                FPC << (LINES[i+1].SubString(x,y) + " 12 0 0 0 0").c_str() << endl;
                if (i != (lns-2))
                        {
                        FPC << "seg: ";
                        FPC << (AnsiString(i+2) + " 6 0 0 0").c_str() << endl;
                        }
                }
        }
FPC << "[texts]" << endl;
FPC << "[merges]" << endl;
FPC << "[end]" << endl;
FPC.close();
Sleep(1000);
//-------------запуск ------------
AnsiString B = ExtractFilePath (Application->ExeName);
if( FRS->Checked )
        B = B + "BMP.frs";
else    B = B + "BMP.fpc";
//
SHELLEXECUTEINFO info = {0};
AnsiString fn = ExtractFilePath(Application->ExeName);
fn.SetLength(fn.Length()-1);
fn = ExtractFilePath(fn);
fn.SetLength(fn.Length()-1);
if( FRS->Checked )
        fn = ExtractFilePath(fn) + "FreeCds.exe";
else    fn = ExtractFilePath(fn) + "FreePcb.exe";

// RUS
if( FileExists(fn) == 0 )
        if( FRS->Checked )
                fn = ExtractFilePath(fn) + "—хемјтор.exe";
        else
                fn = ExtractFilePath(fn) + "ѕлат‘орм.exe";
//
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

//exit(0);
}
//---------------------------------------------------------------------------

//==================== Function CONTOUR ====================

bool Find_pixel_func (bool Flag_Begin_Line, bool UPPERCASE)
{
 //save x save y

 int xs = x;
 int ys = y;
 bool FLRND = false;
 bool Flag_A  = false;
 //-------------------------------------------------------
if (UPPERCASE){                      //if (UPPERCASE){
 if (Flag_Begin_Line)
    {
      if ((TRIGGER(x,(y-1))) && (y))
         {
           if ((y != (H-1)) && (!TRIGGER(x,(y+1))) ) FLRND = true;
           x--;
           if (x < 0)
              {
               XY[0] = 0;
               XY[1] = y-1;
               x = xs;
               y = ys;
               return 1;
              }
           if ((Form1->CheckBox3->Checked == true) && (TRIGGER((x+1),(y+1))) && (!TRIGGER(x,(y+1))))
              {
               Flag_A = true;
               if (!TRIGGER(x,(y-1)))
                  {
                   x = xs;
                   y = ys;
                   return 0;
                  }
              }
           while (x == (xs-1))
                 {
                  y--;
                  if (y < 0) { y = 0; break; }
                  if (TRIGGER((x+1),y) == 0)
                     {
                      if ((Form1->CheckBox3->Checked == true) && (FLRND == false))
                         {
                          x = xs;
                          y = ys;
                          return 0;
                         }
                      y = y+1;
                      break;
                     }
                  while ((TRIGGER(x,y)) && (x >= 0))
                        {
                         x--;
                         if ((x < (xs-8)) && (y < (ys-2)))
                            {
                              XY[0] = xs;
                              XY[1] = y+1;
                              x = xs;
                              y = ys;
                              return 1;
                            }
                         if (TRIGGER(x,(y+1)))
                            {
                              if (y == (ys-1)) XY[0] = x;
                              else XY[0] = xs;
                              XY[1] = y+1;
                              x = xs;
                              y = ys;
                              return 1;
                            }
                        }
                  if (Form1->CheckBox3->Checked == false) break;
                 }
           if ((x > (xs-3)) && (y == (ys-1)) && (Flag_A) && (Form1->CheckBox3->Checked))
                {
                x = xs;
                y = ys;
                return 0;
                }
           XY[0] = x+1;
           XY[1] = y;
         }                      //if (TRIGGER(x,(y-1)))
      else
         {
          while (x < W)
                {
                 x++;
                 if (!TRIGGER(x,y)) break;
                 if (y != 0)
                 if (TRIGGER(x,(y-1)))
                    {
                     x = xs;
                     y = ys;
                     return 0;
                    }
                }       //while (x < W)
          XY[0] = x-1;
          XY[1] = y;
         }//else
    }                 // if (Flag_Begin_Line)
 else
    {
      if (!y) return 0;
      if (TRIGGER(x,(y-1)))
         {
           if ((y != (H-1)) && (!TRIGGER(x,(y+1))) ) FLRND = true;
           x++;
           if (x >= W)
              {
               XY[0] = W-1;
               XY[1] = y-1;
               x = xs;
               y = ys;
               return 1;
              }
           if ((Form1->CheckBox3->Checked == true) && (TRIGGER((x-1),(y+1))) && (!TRIGGER(x,(y+1))))
              {
               Flag_A = true;
               if (!TRIGGER(x,(y-1)))
                  {
                  x = xs;
                  y = ys;
                  return 0;
                  }
              }
           while (x == (xs+1))
                 {
                  y--;
                  if (y < 0) { y = 0; break; }
                  if (TRIGGER((x-1),y) == 0)
                     {
                      if ((Form1->CheckBox3->Checked == true) && (FLRND == false))
                         {
                          x = xs;
                          y = ys;
                          return 0;
                         }
                      y = y+1;
                      break;
                     }
                  while ((TRIGGER(x,y)) && (x < W))
                        {
                         x++;
                         if ((x > (xs+8)) && (y < (ys-2)))
                            {
                              XY[0] = xs;
                              XY[1] = y+1;
                              x = xs;
                              y = ys;
                              return 1;
                            }
                         if (TRIGGER(x,(y+1)))
                            {
                              if (y == (ys-1)) XY[0] = x;
                              else XY[0] = xs;
                              XY[1] = y+1;
                              x = xs;
                              y = ys;
                              return 1;
                            }
                        }
                  if (Form1->CheckBox3->Checked == false) break;
                 }
           if ((x < (xs+3)) && (y == (ys-1)) && (Flag_A) && (Form1->CheckBox3->Checked))
                {
                x = xs;
                y = ys;
                return 0;
                }
           XY[0] = x-1;
           XY[1] = y;
         }
      else
         {
          x = xs;
          y = ys;
          return 0;
         }
    }               //else  if (Flag_Begin_Line)
 x = xs;
 y = ys;
 return 1;
}                             //if (UPPERCASE){
//-----------------------------------------------------------

else{//(UPPERCASE == 0)            ******* LOWERCASE *******
 if (Flag_Begin_Line)
    {
      //if (y == (H-1)) return 0;
      if ((TRIGGER(x,(y+1))) && (y != (H-1)))
         {
           x--;
           if (x < 0)
              {
               XY[0] = 0;
               XY[1] = y+1;
               x = xs;
               y = ys;
               return 1;
              }
           if ((Form1->CheckBox3->Checked == true) && (TRIGGER((x+1),(y-1))) && (!TRIGGER(x,(y-1))))
              {
               Flag_A = true;
               if (!TRIGGER(x,(y+1)))
                  {
                  x = xs;
                  y = ys;
                  return 0;
                  }
              }
           while (x == (xs-1))
                 {
                  y++;
                  if (y >= H) { y = H-1; break; }
                  if (TRIGGER((x+1),y) == 0)
                     {
                      if (Form1->CheckBox3->Checked == true)
                         {
                          x = xs;
                          y = ys;
                          return 0;
                         }
                      y = y-1;
                      break;
                     }
                  while ((TRIGGER(x,y)) && (x >= 0))
                        {
                         x--;
                         if ((x < (xs-8)) && (y > (ys+2)))
                            {
                              XY[0] = xs;
                              XY[1] = y-1;
                              x = xs;
                              y = ys;
                              return 1;
                            }
                         if (TRIGGER(x,(y-1)))
                            {
                              if (y == (ys+1)) XY[0] = x;
                              else XY[0] = xs;
                              XY[1] = y-1;
                              x = xs;
                              y = ys;
                              return 1;
                            }
                        }
                  if (Form1->CheckBox3->Checked == false) break;
                 }
           if ((x > (xs-3)) && (y == (ys+1)) && (Flag_A) && (Form1->CheckBox3->Checked))
                {
                x = xs;
                y = ys;
                return 0;
                }
           XY[0] = x+1;
           XY[1] = y;
         }
      else
         {
          while (x < W)
                {
                 x++;
                 if (!TRIGGER(x,y)) break;
                 if (y != (H-1))
                 if (TRIGGER(x,(y+1)))
                    {
                     x = xs;
                     y = ys;
                     return 0;
                    }
                }       //while (x < W)
          XY[0] = x-1;
          XY[1] = y;
         }
    }                 // if (Flag_Begin_Line)
 else
    {
      if (y == (H-1)) return 0;
      if (TRIGGER(x,(y+1)))
         {
           x++;
           if (x >= W)
              {
               XY[0] = W-1;
               XY[1] = y+1;
               x = xs;
               y = ys;
               return 1;
              }
           if ((Form1->CheckBox3->Checked == true) && (TRIGGER((x-1),(y-1))) && (!TRIGGER(x,(y-1))))
              {
               Flag_A = true;
               if (!TRIGGER(x,(y+1)))
                  {
                  x = xs;
                  y = ys;
                  return 0;
                  }
              }
           while (x == (xs+1))
                 {
                  y++;
                  if (y >= H) { y = H-1; break; }
                  if (TRIGGER((x-1),y) == 0)
                     {
                      if (Form1->CheckBox3->Checked == true)
                         {
                          x = xs;
                          y = ys;
                          return 0;
                         }
                      y = y-1;
                      break;
                     }
                  while ((TRIGGER(x,y)) && (x < W))
                        {
                         x++;
                         if ((x > (xs+8)) && (y > (ys+2)))
                            {
                              XY[0] = xs;
                              XY[1] = y-1;
                              x = xs;
                              y = ys;
                              return 1;
                            }
                         if (TRIGGER(x,(y-1)))
                            {
                              if (y == (ys+1)) XY[0] = x;
                              else XY[0] = xs;
                              XY[1] = y-1;
                              x = xs;
                              y = ys;
                              return 1;
                            }
                        }
                  if (Form1->CheckBox3->Checked == false) break;
                 }
           if ((x < (xs+3)) && (y == (ys+1)) && (Flag_A) && (Form1->CheckBox3->Checked))
                {
                x = xs;
                y = ys;
                return 0;
                }
           XY[0] = x-1;
           XY[1] = y;
         }
      else
         {
          x = xs;
          y = ys;
          return 0;
         }
    }               //else  if (Flag_Begin_Line)
 x = xs;
 y = ys;
 return 1;



}                             //(UPPERCASE == 0)
}

//-------------- trigger func ----------------------

bool TRIGGER (int X_pix, int Y_pix)
{
color = ColorToRGB(Bmp->Canvas->Pixels[X_pix][Y_pix]);
int R = GetRValue(color);
int G = GetGValue(color);
int B = GetBValue(color);
int R_trigg = Form1->TrackBar1->Position;
int G_trigg = Form1->TrackBar2->Position;
int B_trigg = Form1->TrackBar3->Position;
if ((R < R_trigg) || (G < G_trigg) || (B < B_trigg)) return 1;
else return 0;
}
void __fastcall TForm1::RadioButton2Click(TObject *Sender)
{
Edit3->Text = "0,05";
Timer1->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton1Click(TObject *Sender)
{
Edit3->Text = "";
Timer1->Enabled = true;
}
//---------------------------------------------------------------------------

void CANVA (int CASE)
{
double x_canv;
double y_canv;
switch (CASE) {
case 1:
       x_canv = Wpixel*(x0/Size_X) +10 + Wpixel/2;
       y_canv = Hpixel*(y0/Size_Y) +10 + Hpixel/2;
       Form1->Canvas->MoveTo((int)x_canv,(int)y_canv);
       x_canv = Wpixel*XY[0]+10 + Wpixel/2;
       y_canv = Hpixel*XY[1]+10 + Hpixel/2;
       Form1->Canvas->LineTo((int)x_canv,(int)y_canv);
       break;
case 2:
       x_canv = Wpixel*x+10 + Wpixel/2;
       y_canv = Hpixel*y+10 + Hpixel/2;
       Form1->Canvas->MoveTo((int)x_canv,(int)y_canv);
       break;
case 3:
       x_canv = Wpixel*x+10 + Wpixel/2;
       y_canv = Hpixel*y+10 + Hpixel/2;
       Form1->Canvas->LineTo((int)x_canv,(int)y_canv);
       break;
case 4:
       x_canv = Wpixel*x+10 + Wpixel/2;
       y_canv = Hpixel*y+10 + Hpixel/2;
       Form1->Canvas->MoveTo((int)x_canv,(int)y_canv);
       x_canv = Wpixel*(x+1)+10 + Wpixel/2;
       y_canv = Hpixel*y+10 + Hpixel/2;
       Form1->Canvas->LineTo((int)x_canv,(int)y_canv);
       break;
                }
}

//---------------------------------------------------------------------------

//************************* PLACE_POINT *************************************
//---------------------------------------------------------------------------
void PLACE_POINT (double XP, double YP, double WP)
{
PADS[pds] = "pin: \"" + AnsiString(pds/2+1) + "\" 0 ";
PADS[pds] += AnsiString((long long)XP) + " " + AnsiString((long long)(-YP)) + " 0";
pds++;
PADS[pds] = "  top_pad: 1 " + AnsiString((long long)WP) + " ";
PADS[pds] += AnsiString((long long)WP) + " ";
PADS[pds] += AnsiString((long long)WP) + " 0 0";
pds++;
if (pds > 99000)
        Flag_MAXPOINT = true;
}
void __fastcall TForm1::RadioButton3Click(TObject *Sender)
{
Timer1->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton5Click(TObject *Sender)
{
Timer1->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton4Click(TObject *Sender)
{
Timer1->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TrackBar1Change(TObject *Sender)
{
Timer1->Enabled = true;      
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TrackBar2Change(TObject *Sender)
{
Timer1->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TrackBar3Change(TObject *Sender)
{
Timer1->Enabled = true; 
}
//---------------------------------------------------------------------------


void __fastcall TForm1::CheckBox1Click(TObject *Sender)
{
Timer1->Enabled = true;
if( CheckBox1->Checked )
        CheckBox3->Enabled = true;
else    CheckBox3->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CheckBox3Click(TObject *Sender)
{
Timer1->Enabled = true;        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CheckBox2Click(TObject *Sender)
{
Timer1->Enabled = true;        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ComboBox1Change(TObject *Sender)
{
Timer1->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit2Change(TObject *Sender)
{
Timer1->Interval = 2000;
Timer1->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit1Change(TObject *Sender)
{
Timer1->Interval = 2000;
Timer1->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::LinkClick(TObject *Sender)
{
ShellExecute(NULL, "open", "https://github.com/niconson", NULL, NULL, SW_SHOWNORMAL);          
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit3Change(TObject *Sender)
{
Timer1->Enabled = true;           
}
//---------------------------------------------------------------------------

