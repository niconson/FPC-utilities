//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FPC_to_PCB.h"
#include "fstream.h"
#include "math.h"
#include "clipbrd.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
AnsiString OpenD;
AnsiString Path ;
AnsiString A;
AnsiString B;
AnsiString E;
AnsiString Name_Foot;
AnsiString Reference;
AnsiString Value;
AnsiString Package ;
AnsiString Package_for_Type;
AnsiString num_pin;
AnsiString type_top;
AnsiString type_bot;
AnsiString type_inn;
AnsiString Thermal;
AnsiString Inners[99];
AnsiString centroid ;
//-------------
double X_val;
double Y_val;
double X_ref;
double Y_ref;
double W_ref;
double H_ref;
double W_val;
double H_val;
int ANG_ref;
int ANG_val;
double PadRadius;
double BPadRadius;
//-------------
long i = 0;                                     //������ � ������ � � ��.
long n = 0;
long m = 0;

unsigned txt_style_index;
long n_pins = 0;
double n_cop = 0;


char str[2501];                                  //������ ��� ������ �����
bool Vis_ref = true;
bool Vis_val = true;
int  units_mm = 1;                              //���� ���� ������� - ����������
//bool current_units_mm = 0;                    //������� ���� ���� ������� - ����������
bool Side = false;                              //0-top 1-bot
bool Flag_pin = false;
bool Flag_foot = false;
bool Flag_Warning1 = false;
bool Flag_Warning2 = false;
bool Flag_Warning5 = false;
bool Flag_Warning6 = false;
long count_stroke_file = 0;                     //���-�� ����� � ����� ascii P-cad

double X = 0;                                   //X
double Y = 0;                                   //Y
int LVIS, LLAY;
double Xpos = 0;
double Ypos = 0;
int pF = 0;
double D = 0;                                   // ��������...
double W = 0;                                   // ��������...
double F = 0;                                   // ��������...
double H = 0;                                   // ��������...
double Angle = 0;                               // ����
double mask_clearance = (double)4/(double)100;
double shrink_paste_mask = (double)4/(double)100;
double glue_width = (double)4/(double)10;
double fill_clearance = (double)4/(double)10;
double board_outline_width = (double)2/(double)10;;
double First_X;
double First_Y;
double hole_diam ;
double Wtop;
double Htop;
double Wbot;
double Hbot;
double Winn;
double Hinn;
double thermal_width = (double)4/(double)10;
int go_not_int (unsigned index);                //������� ������ � ������ � ���� �� �����
double ex_float_NM (long *index, int units);     //��������� float � ������ � ���� �����
AnsiString ex_str (unsigned index);             //��������� ������ � ������ � ����������� � ""
int go (long index, AnsiString s);              //������� ������ � ������ � ���� �� �������� AnsiString s
void mirr (bool layer_index);                   //��������� ��������� X Y � ������ ������� PART
bool get (AnsiString s);                        //���� A == s return 0 else 1 (s = char str)
void WR_FOOT (void);
int Prob (int Count);                           //������� ��������� ���-�� ��������
void WR_PADSTYLE (void);
bool get_end (void);                            //������ ����� �� �����
float ang (double dx_, double dy_) ;
void ADD_text_style (void);
void WR_part (void);
void PCB_file_designer (void);
AnsiString F_str (double DBL);
void Translate (void);
void Trace (AnsiString Str1, AnsiString Str2, AnsiString Str3, AnsiString net);
AnsiString viaStyle (void);
void CUTOUT (int CASE, int LaYeR);
long Generate_Line (double X, double Y, double X2, double Y2,  int type_L , double *OutPut);
void Rotate_Vertex (double *X, double *Y, double Ang);
double Length_Line (double X1, double Y1, double X2, double Y2);
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
DecimalSeparator = ',';
Timer1->Enabled = false;
AnsiString CLPBRD = Clipboard()->AsText;
if (CLPBRD.SubString(1,6) == "ObjMan")
        {
        A = CLPBRD;
        i = Prob (1);
        OpenDialog1->FileName = ex_str(i) ;
        CLPBRD = ExtractFileName (OpenDialog1->FileName);
        Form1->Caption = "Export Tango for " + CLPBRD;
        Clipboard()->Clear();
        }
else if (Form1->OpenDialog1->Execute())
   {
    if (Form1->OpenDialog1->FileName.Length() == 0) return;
    A = Form1->OpenDialog1->FileName;
    if (A.UpperCase().SubString((A.Length()-3),4) != ".FPC") {ShowMessage ("   ������ ����� �� �������."); exit(0);  }
   }
else exit(0);
Form1->LB_Pack_for_T->Sorted = false;
Form1->ListBox1_Lines->Sorted = false;
Form1->ListBox2_Texts->Sorted = false;
Form1->ListBox3_Pins->Sorted = false;
Form1->ListBox4_NamePins->Sorted = false;
Form1->SavePadStyle->Sorted = false;
Form1->ListBox1_Lines->Visible = false;
Form1->ListBox2_Texts->Visible = false;
Form1->ListBox3_Pins->Visible = false;
Form1->SavePadStyle->Visible = false;
Form1->LB_Pack_for_T->Visible = false;
Form1->ListBox4_NamePins->Visible = false;
Timer1->Interval = 300;
Timer1->Enabled = true;
}



void Translate (void)
{
OpenD = Form1->OpenDialog1->FileName;
Path = ExtractFilePath (Application->ExeName) ;
Path = Path + "ExportTango\\";
ifstream FPC (OpenD.c_str());
//
ofstream NETLIST ((Path + "NETLIST.TXT").c_str());
ofstream PADST ((Path + "PADSTYLE.TXT").c_str());
PADST.close();
ofstream VIAST ((Path + "VIASTYLE.TXT").c_str());
VIAST.close();
ofstream compDef ((Path + "compDef.TXT").c_str());
compDef.close();
ofstream compInst ((Path + "compInst.TXT").c_str());
compInst.close();
ofstream TE ((Path + "TEXTSTYLE.TXT").c_str());
TE.close();
ofstream PAT ((Path + "PATTERNS.TXT").c_str());
PAT.close();
ofstream PArts ((Path + "PARTS.TXT").c_str());
PArts.close();
ofstream POLY ((Path + "POLY.TXT").c_str());
POLY.close();
ofstream CUTOUTS ((Path + "CUTOUTS_AREA.TXT").c_str());
CUTOUTS.close();
ofstream SOLDERMASK ((Path + "SOLDERMASK.TXT").c_str());
SOLDERMASK.close();
ofstream TEXTs ((Path + "TEXTS.TXT").c_str());
TEXTs.close();
ofstream BOARD ((Path + "BOARD.TXT").c_str());
BOARD.close();
ofstream TP ((Path + "TOP.TXT").c_str());
TP.close();
ofstream BT ((Path + "BOTTOM.TXT").c_str());
BT.close();
ofstream IN1 ((Path + "INNER1.TXT").c_str());
IN1.close();
ofstream IN2 ((Path + "INNER2.TXT").c_str());
IN2.close();
ofstream IN3 ((Path + "INNER3.TXT").c_str());
IN3.close();
ofstream IN4 ((Path + "INNER4.TXT").c_str());
IN4.close();
ofstream IN5 ((Path + "INNER5.TXT").c_str());
IN5.close();
ofstream IN6 ((Path + "INNER6.TXT").c_str());
IN6.close();
ofstream IN7 ((Path + "INNER7.TXT").c_str());
IN7.close();
ofstream IN8 ((Path + "INNER8.TXT").c_str());
IN8.close();
ofstream IN9 ((Path + "INNER9.TXT").c_str());
IN9.close();
ofstream IN10 ((Path + "INNER10.TXT").c_str());
IN10.close();
ofstream IN11 ((Path + "INNER11.TXT").c_str());
IN11.close();
ofstream IN12 ((Path + "INNER12.TXT").c_str());
IN12.close();
ofstream IN13 ((Path + "INNER13.TXT").c_str());
IN13.close();
ofstream IN14 ((Path + "INNER14.TXT").c_str());
IN14.close();

//
//=====================================================
//=====================================================
//=====================================================
Form1->Label1->Caption = "������ �����";
Application->ProcessMessages();
while (get ("[footprints]"))
        {//������ ������ �����
        FPC.getline(str,2500);
        A = str;
        A = A.Trim();
        i = Prob(1);
        if (get ("units") == 0)units_mm = 1;
        else if (get ("file_version") == 0)
                {
                D = ex_float_NM(&i, -1);
                if(D < 2.022)
                        {
                        ShowMessage("This file cannot be processed because it was created in the previous version of FREEPCB.");
                        exit(0);
                        }
                }
        else if (get ("fill_clearance") == 0)            fill_clearance = ex_float_NM(&i, units_mm);
        else if (get ("mask_clearance") == 0)            mask_clearance = ex_float_NM(&i, units_mm);
        else if (get ("thermal_width") == 0)             thermal_width = ex_float_NM(&i, units_mm);
        else if (get ("board_outline_width") == 0)       board_outline_width = ex_float_NM(&i, units_mm);
        else if (get ("shrink_paste_mask") == 0)         shrink_paste_mask = ex_float_NM(&i, units_mm);
        else if (get("n_copper_layers") == 0)
                {
                D = ex_float_NM(&i, -1);
                n_cop = D - 2;
                i = 0;
                if (n_cop<0) n_cop = 0;
                while (n_cop)
                        {
                        Inners[i] = AnsiString("  (layerDef \"Inner ") + n_cop + "\"";
                        i++;
                        Inners[i] = AnsiString("    (layerNum ") + (n_cop+11) + ")";
                        i++;
                        Inners[i] = "    (layerType Signal)";
                        i++;
                        Inners[i] = "    (fieldSetRef \"(Default)\")";
                        i++;
                        Inners[i] = "  )";
                        i++;
                        n_cop--;
                        }
                n_cop = D;
                }//if (get("n_copper_layers") == 0)
        }//����� ������ �����
//=====================================================
//=====================================================
//=====================================================
Form1->Label1->Caption = "�������� ����������";
Application->ProcessMessages();
while (get ("[board]"))
      {//������ ������ ����������

       FPC.getline(str,2500);
       A = str;
       A = A.Trim();

// ���

       if (get ("name") == 0)
          {

           if (Flag_foot == true)
              { //������ ���������
                if (Flag_pin == true)
                   { //������ PADSTYLE
                    WR_PADSTYLE();
                   }
                WR_FOOT ();
              }
           Flag_foot = true;
           Flag_pin = false;
           units_mm = true;
           i = Prob(1);
           Name_Foot = ex_str(i);
           Form1->Label1->Caption = "�������� ����������: " + Name_Foot;
           Application->ProcessMessages();
           centroid = "0.0 0.0";
           n_pins = 0;
          }//if (get ("name") == 0)
// PACKAGE

       if (get ("package") == 0)
          {
          if (Flag_foot == true)
                {
                i = Prob(1);
                Package_for_Type = ex_str(i);
                Form1->LB_Pack_for_T->Items->Add(Name_Foot);
                Form1->LB_Pack_for_T->Items->Add(Package_for_Type);
                }
          }
// ��. ���

       if (get ("units") == 0)
          {
           if (go (1,"NM")) units_mm = true;
           else             units_mm = false;
          }

// CENTROID

       if (get ("centroid") == 0)
          {
           i = Prob(2);
           X = ex_float_NM(&i, units_mm);
           Y = ex_float_NM(&i, units_mm);
           centroid = AnsiString(F_str(X)) + " " + AnsiString(F_str(Y));
          }
// ���������� �����

       if (get ("n_pins") == 0)
          {
           i = Prob(1);
           n_pins = (int)ex_float_NM(&i, -1);
          }
// �����

       if (get ("text") == 0)
          {
           AnsiString text_string;
           double x;
           double y;
           double angle;
           i = Prob(1);
           text_string = ex_str(i);                     //�����
           H = ex_float_NM(&i, units_mm);               //height
           H = 1.0;
           x = ex_float_NM(&i, units_mm);               //x
           y = ex_float_NM(&i, units_mm);               //y
           angle = ex_float_NM(&i, -1);                 //angle
           W = ex_float_NM(&i, units_mm);               //line_width
           W = 0.1;
           AnsiString TXT = "        (text (pt ";
           TXT = TXT + F_str(x);
           TXT = TXT + " ";
           TXT = TXT + F_str(y);
           TXT = TXT + ") \"";
           TXT = TXT + text_string;
           TXT = TXT + "\" (textStyleRef \"T";
           TXT = TXT + F_str(H);
           TXT = TXT + "x";
           TXT = TXT + F_str(W);
           if (angle != 0 )
              {
                if (angle == 90 ) angle = 270;
                else if (angle == 270 ) angle = 90;
                TXT = TXT + "\") (rotation " + AnsiString(angle) + ") )";
              }
           else TXT = TXT + "\") )";
           Form1->ListBox2_Texts->Items->Add(TXT);
           ADD_text_style();
          }//if (get ("text") == 0)

       // �����

       if (get ("outline_polyline") == 0)
          {
           i = Prob(1);
           W = ex_float_NM(&i, units_mm);                  //�������
           X = ex_float_NM(&i, units_mm);                  //X
           Y = ex_float_NM(&i, units_mm);                  //Y
           if( i > 0 )
                LVIS = ex_float_NM(&i, -1);                     //���������
           else
                LVIS = 1;
           i = Prob(6);
           if( i > 0 )
                LLAY = ex_float_NM(&i, -1);
           else
                LLAY = 4;
           switch( LLAY )
                {
                case 4: LLAY = 6; break;
                case 5: LLAY = 7; break;
                case 7: LLAY = 3; break;
                case 8: LLAY = 4; break;
                case 13: LLAY = 1; break;
                case 15: LLAY = 2; break;
                }
           First_X = X;
           First_Y = Y;
          }
       if (( get("next_corner") == 0 || get ("close_polyline") == 0 ) && LVIS )
          {
           double X2;
           double Y2;

           if (go (1,"next"))
              {
               i = Prob(1);
               X2 = ex_float_NM(&i, units_mm);                  //X
               Y2 = ex_float_NM(&i, units_mm);                  //Y
              }
           else
              {
               X2 = First_X;
               Y2 = First_Y;
              }
           if (go (1,"next")) i = Prob(3);
           else i = Prob(1);
           double type_L = ex_float_NM(&i, -1);       //type_L
           if (type_L == 0)
              { //������ �����
              if (Length_Line(X, Y, X2, Y2) > (1/(double)100))
                        {
                        AnsiString LINE = "        (line (pt ";
                        LINE += F_str(X);
                        LINE += " ";
                        LINE += F_str(Y);
                        LINE += ") (pt "  ;
                        LINE += F_str(X2);
                        LINE += " ";
                        LINE += F_str(Y2);
                        LINE += ") (width "  ;
                        LINE += F_str(W);
                        LINE += ") )";
                        LINE += AnsiString(LLAY);
                        Form1->ListBox1_Lines->Items->Add(LINE);
                        }
              }
           else
              { // ����
               double dx;
               double dy;
               double angL;
               double ang_end;
               double x0;
               double y0;
               double rad;
               double xmid;
               double ymid;
               double len;
               xmid = (X + X2)/(double)2;
               ymid = (Y + Y2)/(double)2;
               dx = X - X2;
               dy = Y - Y2;
               if ((dx == 0)||(dy == 0))
                  {
                  if (Length_Line(X, Y, X2, Y2) > (1/(double)100))
                        {
                        AnsiString LINE = "        (line (pt ";
                        LINE += F_str(X);
                        LINE += " ";
                        LINE += F_str(Y);
                        LINE += ") (pt "  ;
                        LINE += F_str(X2);
                        LINE += " ";
                        LINE += F_str(Y2);
                        LINE += ") (width "  ;
                        LINE += F_str(W);
                        LINE += ") )";
                        LINE += AnsiString(LLAY);
                        Form1->ListBox1_Lines->Items->Add(LINE);
                        continue;
                        }
                  }// if ((dx == 0)||(dy == 0))
               else
                  {
                  angL = ang (dx,dy);
                  if (type_L == 1) angL = angL + 90;
                  if (type_L == 2) angL = angL - 90;
                  len = sqrt((pow(dx,2) + pow(dy,2))) ;
                  double H_arc = len/(double)2;
                  if (ABS(dx) < ABS(dy)) H_arc = H_arc*(double)dy/(double)dx;
                  else H_arc = H_arc*(double)dx/(double)dy;
                  if (H_arc < 0) H_arc = -H_arc;
                  if (angL < 0) angL = angL + 360;
                  if (angL > 360) angL = angL - 360;
                  x0 = H_arc*cos(angL*10/573) + xmid;
                  y0 = H_arc*sin(angL*10/573) + ymid;

                  ang_end = ang((X2-x0),(Y2-y0)) ;
                  angL = ang((X-x0),(Y-y0)) ;
                  D = X;
                  F = Y;
                  X = X - x0;
                  Y = Y - y0;
                  while (ABS(angL - ang_end) > 15)
                        {
                         if (type_L == 1) Rotate_Vertex (&X, &Y, -15);
                         if (type_L == 2) Rotate_Vertex (&X, &Y, 15);
                         X = X + x0;
                         Y = Y + y0;
                         AnsiString LINE = "        (line (pt ";
                         LINE += F_str(D);
                         LINE += " ";
                         LINE += F_str(F);
                         LINE += ") (pt "  ;
                         LINE += F_str(X);
                         LINE += " ";
                         LINE += F_str(Y);
                         LINE += ") (width "  ;
                         LINE += F_str(W);
                         LINE += ") )";
                         LINE += AnsiString(LLAY);
                         Form1->ListBox1_Lines->Items->Add(LINE);
                         D = X;
                         F = Y;
                         X = X - x0;
                         Y = Y - y0;
                         angL = ang (X,Y);
                        } // while (ang < ang_end)
                     AnsiString LINE = "        (line (pt ";
                     LINE = LINE + F_str(D);
                     LINE = LINE + " ";
                     LINE = LINE + F_str(F);
                     LINE = LINE + ") (pt "  ;
                     LINE = LINE + F_str(X2);
                     LINE = LINE + " ";
                     LINE = LINE + F_str(Y2);
                     LINE = LINE + ") (width "  ;
                     LINE = LINE + F_str(W);
                     LINE = LINE + ") )";
                     LINE += AnsiString(LLAY);
                     Form1->ListBox1_Lines->Items->Add(LINE);
                  }// else if ((dx == 0)||(dy == 0))
              } // ����

           X = X2;
           Y = Y2;
          } // if (get ("next_corner") == 0)

       // ����

       if (get ("pin") == 0)
          {
           if (Flag_pin == true)
              { //������ PADSTYLE
               WR_PADSTYLE();
              }
           Flag_pin = true;
           i = Prob(1);
           num_pin = ex_str (i);            //����� ����
           i++;
           hole_diam = ex_float_NM(&i, units_mm);
           X = ex_float_NM(&i, units_mm);               //X
           Y = ex_float_NM(&i, units_mm);               //Y
           Angle = ex_float_NM(&i, -1);                 //Angle

           Wtop = 0;
           Htop = 0;
           Winn = 0;
           Hinn = 0;
           Wbot = 0;
           Hbot = 0;
           type_top = "Ellipse";
           type_bot = "Ellipse";
           type_inn = "Ellipse";
           Thermal = "Direct";
           PadRadius = 0;
           BPadRadius = 0;
          }
//top
       if (get ("top_pad") == 0)
          {
           double typ;
           i = Prob(1);
           typ = ex_float_NM(&i, -1);                          //��� ����
           if (typ == 0) type_top = "MtHole";
           if (typ == 1) type_top = "Ellipse";
           if (typ == 2) type_top = "Rect";
           if (typ == 3) type_top = "Rect";
           if (typ == 4) type_top = "RndRect";
           if (typ == 5) type_top = "Oval";
           if (typ == 6) type_top = "Ellipse";
           Wtop = ex_float_NM(&i, units_mm);                          //������
           Htop = ex_float_NM(&i, units_mm);                          //�����
           Htop = Htop*2;
           if (typ == 1) Htop = Wtop;
           if (typ == 2) Htop = Wtop;
           if (typ == 6) Htop = Wtop;
           if (typ == 0) { Wtop = hole_diam; Htop = hole_diam;    }
           if (Prob(5))
              {
                i = Prob(5);
                PadRadius = ex_float_NM(&i, units_mm);                  //RADIUS
                if (type_top.SubString(1,type_top.Length()) == "RndRect")
                if (PadRadius == 0) type_top = "Rect";
              }
           if (Prob(6))
              {
                i = Prob(6);
                double trml = ex_float_NM(&i, -1);
                if (trml == 1 ) Thermal = "NoConnect";
                if (trml == 3 ) Thermal = "Direct"; //type_top = "Direct";}
              }
          }//if (get ("top") == 0)
//bot
       if (get ("bottom_pad") == 0)
          {
           double typ;
           i = Prob(1);
           typ = ex_float_NM(&i, -1);              //��� ����
           if (typ == 0) type_bot = "MtHole";
           if (typ == 1) type_bot = "Ellipse";
           if (typ == 2) type_bot = "Rect";
           if (typ == 3) type_bot = "Rect";
           if (typ == 4) type_bot = "RndRect";
           if (typ == 5) type_bot = "Oval";
           if (typ == 6) type_bot = "Ellipse";
           Wbot = ex_float_NM(&i, units_mm);                  //������
           Hbot = ex_float_NM(&i, units_mm);                  //�����
           Hbot = Hbot*2;
           if (typ == 1) Hbot = Wbot;
           if (typ == 2) Hbot = Wbot;
           if (typ == 6) Hbot = Wbot;
           if (typ == 0) { Wbot = hole_diam; Hbot = hole_diam;    }
           if (Prob(5))
              {
                i = Prob(5);
                BPadRadius = ex_float_NM(&i, units_mm);
                if (type_bot.SubString(1,type_bot.Length()) == "RndRect")
                if (BPadRadius == 0) type_bot = "Rect";
              }
          }//if (get ("bot") == 0)
//inn
       if (get ("inner_pad") == 0)
          {
           double typ;
           i = Prob(1);
           typ = ex_float_NM(&i, -1);              //��� ����
           if (typ == 0) type_inn = "MtHole";
           if (typ == 1) type_inn = "Ellipse";
           if (typ == 2) type_inn = "Rect";
           if (typ == 3) type_inn = "Rect";
           if (typ == 4) type_inn = "RndRect";
           if (typ == 5) type_inn = "Oval";
           if (typ == 6) type_inn = "Ellipse";
           Winn = ex_float_NM(&i, units_mm);                  //������
           Hinn = ex_float_NM(&i, units_mm);                  //�����
           Hinn = Hinn*2;
           if (typ == 1) Hinn = Winn;
           if (typ == 2) Hinn = Winn;
           if (typ == 6) Hinn = Winn;
           if (typ == 0) { Winn = hole_diam; Hinn = hole_diam;    }
           if (Prob(5))
              {
                i = Prob(5);
                double corn_radius = ex_float_NM(&i, units_mm);
                if (type_inn.SubString(1,type_inn.Length()) == "RndRect")
                { if (corn_radius == 0) type_inn = "Rect";   }
              }
           if (Prob(6))
              {
                i = Prob(6);
                double trml = ex_float_NM(&i, -1);
                if (trml == 3 ){ type_inn = "Direct";}
              }
          }//if (get ("inn") == 0)
      }//����� ������ ����������
//=====================================================
//=====================================================
//=====================================================

if (Flag_pin == true)
              { //������ PADSTYLE
               WR_PADSTYLE();
              }
if (Flag_foot == true)
              { //������ PADSTYLE
               WR_FOOT();
              }


units_mm = 1;


//**********************************************************
//������ ����� � ������ � �����
//**********************************************************

Form1->Label1->Caption = "����� ������� �����";
Application->ProcessMessages();
ofstream BRD;
BRD.open((Path + "BOARD.TXT").c_str(), std::ios_base::app );
ofstream SM;
SM.open((Path + "SOLDERMASK.TXT").c_str(), std::ios_base::app );
bool solder_mask_cutouts = false;
bool BRD_flag = false;
bool SMM_flag = false;
F = 0;
n = 0;
E = "";
int n_cont = 0;
int prev_n_cont = 0;
BRD << "  (layerContents (layerNumRef 3)" << endl;
BRD << "    (boardOutlineObj " << endl;
while (get ("[parts]") && get ("[graphics]"))
      {//������ ������ ������� �����
        FPC.getline(str,2500);
        A = str;
        A = A.Trim();
        //-----------------------------------------------------------------------
        if (get ("[solder_mask_cutouts]") == 0)
                {
                if (BRD_flag == true)
                        {
                        double ARC[max_arc];
                        long LeN = Generate_Line (X, Y, First_X, First_Y, F, &ARC[0]);
                        long CouN = 0;
                        while (CouN < LeN)
                                {
                                BRD << "        (polyPoint " ;
                                BRD << F_str(ARC[CouN]).c_str();
                                BRD << " ";
                                BRD << F_str(ARC[CouN+1]).c_str();
                                BRD << " 0)";
                                BRD << endl;
                                CouN += 2;
                                }
                        F = 0;
                        BRD << "      )" << endl;
                        BRD << "      (width " ;
                        BRD << F_str(board_outline_width).c_str();
                        BRD << "    )" << endl;
                        BRD << "    )" << endl;
                        BRD << "  )" << endl;
                        }
                solder_mask_cutouts = true;
                n = 0;
                }
//-----------------------------------------------------------------------
        if (get ("sm_cutout") == 0)
                {
                i = Prob(3);
                W = ex_float_NM(&i, -1);         //LAYER MASK
                }
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
       if (get ("corner") == 0)
          {
            i = Prob(2);
            X = ex_float_NM(&i, units_mm);
            Y = ex_float_NM(&i, units_mm);
            if(n == 0)
                {
                First_X = X;
                First_Y = Y;
                if (solder_mask_cutouts)
                              {
                              if( SMM_flag )
                                {
                                SM << "    )";
                                SM << E.c_str();
                                SM << endl;
                                }
                              SMM_flag = true;
                              if (W == 9) E = "T";
                              else E = "B";
                              SM << "    (pcbPoly ";
                              SM << E.c_str();
                              SM << endl;
                              }
                else          {
                              if( BRD_flag )
                                {
                                BRD << "      )";
                                BRD << endl;
                                }
                              BRD_flag = true;
                              BRD << "      (enhancedPolygon " << endl;
                              }
                }
            if (i)
                F = ex_float_NM(&i, -1);   //��� �����
            if (i)
                n_cont = ex_float_NM(&i, -1);   //number of polyline
            if( n)      {
                        double ARC[max_arc];
                        long LeN;
                        if(n_cont == prev_n_cont)
                                LeN = Generate_Line (Xpos, Ypos, X, Y, pF, &ARC[0]);
                        else    {
                                LeN = Generate_Line (Xpos, Ypos, First_X, First_Y, pF, &ARC[0]);
                                }
                        long CouN = 0;
                        while (CouN < LeN)
                                {
                                   if (solder_mask_cutouts)
                                           {
                                           SM << "      (pt " ;
                                           SM << F_str(ARC[CouN]).c_str();
                                           SM << " ";
                                           SM << F_str(ARC[CouN+1]).c_str();
                                           SM << ")";
                                           SM << E.c_str();
                                           SM << endl;
                                           }
                                   else
                                           {
                                           BRD << "        (polyPoint " ;
                                           BRD << F_str(ARC[CouN]).c_str();
                                           BRD << " ";
                                           BRD << F_str(ARC[CouN+1]).c_str();
                                           BRD << " 0)";
                                           BRD << endl;
                                           }
                                   CouN += 2;
                                }
                        }
            if(n_cont != prev_n_cont)
                    {
                    First_X = X;
                    First_Y = Y;
                    F = 0;
                    if (solder_mask_cutouts)
                              {
                              SM << "    )";
                              SM << E.c_str();
                              SM << endl;
                              SM << "  )" << endl;
                              if (W == 9) E = "T";
                              else E = "B";
                              SM << "    (pcbPoly ";
                              SM << E.c_str();
                              SM << endl;
                              }
                    else      {
                              BRD << "      )";
                              BRD << endl;
                              BRD << "      (enhancedPolygon " << endl;
                              }
                    }
            Xpos = X;
            Ypos = Y;
            pF = F;
            prev_n_cont = n_cont;
            n++;
          }//if (get ("corner") == 0)
          else  {
                n = 0;
                n_cont = 0;
                prev_n_cont = 0;
                }
       }//����� ������ ������� �����
//------------------����������-----------------------------------------------------
if (SMM_flag)
       {
       double ARC[max_arc];
       long LeN = Generate_Line (Xpos, Ypos, First_X, First_Y, pF, &ARC[0]);
       long CouN = 0;
       while (CouN < LeN)
               {
               SM << "      (pt " ;
               SM << F_str(ARC[CouN]).c_str();
               SM << " ";
               SM << F_str(ARC[CouN+1]).c_str();
               SM << ")";
               SM << E.c_str();
               SM << endl;
               CouN += 2;
               }
       SM << "    )";
       SM << E.c_str();
       SM << endl;
       }
BRD.close();
SM.close();
//=====================================================
//=====================================================
//=====================================================
 /*
Form1->Label1->Caption = "������ � �����";
Application->ProcessMessages();
while (get ("[parts]"))
      {//������ ������ ������� � �����
       FPC.getline(str,2500);
       A = str;
       A = A.Trim();

      }//����� ������ ������� � �����   */

//=====================================================
//=====================================================
//=====================PARTS===========================

Form1->Label1->Caption = "����������� �����������";
Application->ProcessMessages();
bool Flag_part = false;
while (get ("[nets]"))
      {//������ ������ PART
       FPC.getline(str,2500);
       A = str;
       A = A.Trim();
       if (get ("part") == 0)
          {
           if (Flag_part == true)
              {
               WR_part();
              }
           Flag_part = true;
           i = Prob(1);
           Reference = A.SubString(i,(A.Length()-i+1)) ;
           Form1->Label1->Caption = "����������� �����������: " + Reference;
           Application->ProcessMessages();
           H = 0;
           W = 0;
           X = 0;
           Y = 0;
           Angle = 0;
           Value = "";
           Package = "";
           Package_for_Type = "";
           X_val = 0;
           Y_val = 0;
           X_ref = 0;
           Y_ref = 0;
           W_ref = 0;
           H_ref = 0;
           W_val = 0;
           H_val = 0;
           ANG_ref = 0;
           ANG_val = 0;
           Vis_ref = true;
           Vis_val = true;
          }
       if (get ("ref_text") == 0)
          {
           i = Prob(1);
           H_ref = ex_float_NM(&i, units_mm);
           W_ref = ex_float_NM(&i, units_mm);
           ANG_ref = ex_float_NM(&i, -1);             //����
           X_ref = ex_float_NM(&i, units_mm);
           Y_ref = ex_float_NM(&i, units_mm);
           if (Prob(6))
              {
               if (A.SubString(A.Length(),1) == "0") Vis_ref = false;
              }
           H = H_ref;
           if( H_ref < 0.01 )
                W_ref = 0;
           W = W_ref;
           ADD_text_style();
          }
       if (get ("shape") == 0)
          {
           i = Prob(1);
           Package = ex_str(i);
          }
       if (get ("pos") == 0)
          {
           i = Prob(1);
           Xpos = ex_float_NM(&i, units_mm);
           Ypos = ex_float_NM(&i, units_mm);
           D = ex_float_NM(&i, -1);
           if (D == 0) Side = false;            //Side
           else Side = true;
           Angle = ex_float_NM(&i, -1);         //Angle
          }
       if (get ("value") == 0)
          {
           i = Prob(1);
           Value = ex_str(i);
           H_val = ex_float_NM(&i, units_mm);
           W_val = ex_float_NM(&i, units_mm);
           ANG_val = ex_float_NM(&i, -1);             //����
           X_val = ex_float_NM(&i, units_mm);
           Y_val = ex_float_NM(&i, units_mm);
           if (i <= A.Length())
              {
               if (A.SubString(i,1) == "0" ) Vis_val = false;
              }
           H = H_val;
           if( H_val < 0.01 )
                W_val = 0;
           W = W_val;
           ADD_text_style();
          }
      }//����� ������ PART
if (Flag_part == true)
{
WR_part();
}
//=====================================================
//=====================================================
//=====================================================
ofstream compIn ;
compIn.open((Path + "compInst.TXT").c_str(), std::ios_base::app );
compIn << "END" << endl;
compIn.close();
Flag_Warning2 = false;
Form1->Label1->Caption = "����, ������, ��������...";
Application->ProcessMessages();
AnsiString NETS[19999];
AnsiString BA;
AnsiString CA;
AnsiString net_name;
FPC.getline(str,2500);
while (get ("[texts]"))
      {//������ ������ NET

       if ((A.SubString(1,3) == "vtx")&&(BA.SubString(1,3) == "seg")&&(CA.SubString(1,3) == "vtx"))
          {
            Form1->Label1->Caption = "���������� �pacc� " + net_name;
            Application->ProcessMessages();
            Trace (A,BA,CA,net_name);
          }
       else if (get ("area") == 0)
          {
            i = Prob(1);
            D = ex_float_NM(&i, -1);    //����� ��������
            Form1->Label1->Caption = AnsiString("������� ") + D + " " + net_name;
            Application->ProcessMessages();
            i = Prob(2);
            int nc = ex_float_NM(&i, -1);     // n corners
            i = Prob(3);
            int lr = ex_float_NM(&i, -1);     //���� ��������
            int hatch = ex_float_NM(&i, -1);     //hatch ��������
            if( i>0 )
                D = ex_float_NM(&i, units_mm);     //width ��������
            else
                D = 0;
            while (get ("corner")) FPC.getline(str,2500);
            if( hatch || D>0.01 || D<-0.01 )
                {
                 switch(lr){
                 case 15: B = "TOP.TXT"; break;
                 case 16: B = "BOTTOM.TXT"; break;
                 case 17: B = "INNER1.TXT"; break;
                 case 18: B = "INNER2.TXT"; break;
                 case 19: B = "INNER3.TXT"; break;
                 case 20: B = "INNER4.TXT"; break;
                 case 21: B = "INNER5.TXT"; break;
                 case 22: B = "INNER6.TXT"; break;
                 case 23: B = "INNER7.TXT"; break;
                 case 24: B = "INNER8.TXT"; break;
                 case 25: B = "INNER9.TXT"; break;
                 case 26: B = "INNER0.TXT"; break;
                 case 27: B = "INNER11.TXT"; break;
                 case 28: B = "INNER12.TXT"; break;
                 case 29: B = "INNER13.TXT"; break;
                 case 30: B = "INNER14.TXT"; break;
                 default: ShowMessage ("    ������! ����������� ���� ��������! ") ; }
                 ofstream Poly;
                 Poly.open((Path + B).c_str(), std::ios_base::app );
                 Poly << "    (copperPour95 ";
                 Poly << endl;
                 Poly << "      (pourType SolidPour)";
                 Poly << endl;
                 Poly << "      (netNameRef \"";
                 Poly << net_name.c_str();
                 Poly << "\")";
                 Poly << endl;
                 Poly << "      (width ";
                 if( D > 0.01 )
                     Poly << AnsiString(F_str(D)).c_str();
                 else    Poly << "0.01";
                 Poly << ")";
                 Poly << endl;
                 Poly << "      (pourSpacing 0.254)";
                 Poly << endl;
                 Poly << "      (pourBackoff ";
                 Poly << fill_clearance ;
                 Poly << ")";
                 Poly << endl;
                 Poly << "      (useDesignRules False)";
                 Poly << endl;
                 Poly << "      (pourSmoothness 1)";
                 Poly << endl;
                 Poly << "      (thermalType NoTherm)";      //Therm90)";
                 Poly << endl;
                 Poly << "      (thermalWidth ";
                 Poly << thermal_width;
                 Poly << ")";
                 Poly << endl;
                 Poly << "      (thermalSpokes 4)";
                 Poly << endl;
                 Poly << "      (islandRemoval None)";
                 Poly << endl;
                 Poly << "      (viaThermalType NoTherm)";
                 Poly << endl;
                 Poly << "      (viaThermalWidth 0.4)";
                 Poly << endl;
                 Poly << "      (viaThermalSpokes 4)";
                 Poly << endl;
                 Poly << "      (pcbPoly ";
                 Poly << endl;
                 AnsiString * ISLAND = new AnsiString[nc*7+1];
                 n = 0;
                 F = 0;
                 while (get ("corner") == 0)
                       {
                         i = Prob(2);
                         X = ex_float_NM(&i, units_mm);
                         Y = ex_float_NM(&i, units_mm);
                         if (n == 0)
                            {
                             First_X = X;
                             First_Y = Y;
                            }
                         if (F)                   //ARC
                            {
                             double ARC[max_arc];
                             long LeN = Generate_Line (Xpos, Ypos, X, Y, F, &ARC[0]);
                             long CouN = 0;
                             while (CouN < LeN)
                                     {
                                     ISLAND[n] = "        (pt ";
                                     ISLAND[n] = ISLAND[n] + F_str(ARC[CouN]);
                                     ISLAND[n] = ISLAND[n] + " ";
                                     ISLAND[n] = ISLAND[n] + F_str(ARC[CouN+1]);
                                     ISLAND[n] = ISLAND[n] + ")";
                                     ISLAND[n] = StringReplace(ISLAND[n],",",".",TReplaceFlags()<<rfReplaceAll);
                                     Poly << ISLAND[n].c_str() << endl;
                                     n++;
                                     CouN++;
                                     CouN++;
                                     }
                             F = 0;
                            }//if (F)
                         F = ex_float_NM(&i, -1);   // ��� �����
                         D = ex_float_NM(&i, -1);   // D = ���� cutout
                         ISLAND[n] = "        (pt ";
                         ISLAND[n] = ISLAND[n] + F_str(X);
                         ISLAND[n] = ISLAND[n] + " ";
                         ISLAND[n] = ISLAND[n] + F_str(Y);
                         ISLAND[n] = ISLAND[n] + ")";
                         ISLAND[n] = StringReplace(ISLAND[n],",",".",TReplaceFlags()<<rfReplaceAll);
                         Poly << ISLAND[n].c_str() << endl;
                         n++;
                         FPC.getline(str,2500);
                         A = str;
                         A = A.Trim();
                         if (D) break;
                         Xpos = X;
                         Ypos = Y;
                       }//while (get ("corner") == 0)
                 //
                 if (F)                   //ARC
                      {
                       double ARC[max_arc];
                             long LeN = Generate_Line (X, Y, First_X, First_Y, F, &ARC[0]);
                             long CouN = 0;
                             while (CouN < LeN)
                                     {
                                     ISLAND[n] = "        (pt ";
                                     ISLAND[n] = ISLAND[n] + F_str(ARC[CouN]);
                                     ISLAND[n] = ISLAND[n] + " ";
                                     ISLAND[n] = ISLAND[n] + F_str(ARC[CouN+1]);
                                     ISLAND[n] = ISLAND[n] + ")";
                                     ISLAND[n] = StringReplace(ISLAND[n],",",".",TReplaceFlags()<<rfReplaceAll);
                                     Poly << ISLAND[n].c_str() << endl;
                                     n++;
                                     CouN++;
                                     CouN++;
                                     }
                             F = 0;
                      }//if (F)
                 Poly << "      )" ;
                 Poly << endl;
                 Poly << "      (island ";
                 Poly << endl;
                 Poly << "        (islandOutline ";
                 Poly << endl;
                 n = 0;
                 while (ISLAND[n].Length() != 0)
                       {
                        Poly << ISLAND[n].c_str() << endl;
                        n++;
                       }
                 Poly << "        )";
                 Poly << endl;
                 if (get("corner") == 0)
                    {
                      Poly << "        (cutout ";
                      Poly << endl;
                      Poly << "          (cutoutOutline ";
                      Poly << endl;
                      CUTOUT(1,lr);
                    }
                 double FirstX = 0;
                 double FirstY = 0;
                 double Fback = 0;
                 double Xback = 0;
                 double Yback = 0;
                 int countstr = 0;
                 while (get("corner") == 0)
                       {
                         i = Prob(2);
                         X = ex_float_NM(&i, units_mm);
                         Y = ex_float_NM(&i, units_mm);
                         F = ex_float_NM(&i, -1);            // ��� �����
                         D = ex_float_NM(&i, -1);            // D = ���� cutout
                         if (!countstr)
                             {
                             FirstX = X;
                             FirstY = Y;
                             }
                         else if (countstr == 1)
                             {
                             double ARC[max_arc];
                             long LeN = Generate_Line (Xback, Yback, X, Y, Fback, &ARC[0]);
                             long CouN = 0;
                             while (CouN < LeN)
                                             {
                                             Poly << "        (pt ";
                                             Poly << F_str(ARC[CouN]).c_str();
                                             Poly << " ";
                                             Poly << F_str(ARC[CouN+1]).c_str();
                                             Poly << ")";
                                             Poly << endl;
                                             X = ARC[CouN];
                                             Y = ARC[CouN+1];
                                             CUTOUT(2,lr);
                                             CouN++;
                                             CouN++;
                                             }
                             }
                         else if (countstr > 1)
                             {
                             double ARC[max_arc];
                             long LeN = Generate_Line (Xback, Yback, X, Y, Fback, &ARC[0]);
                             long CouN = 2;
                             while (CouN < LeN)
                                             {
                                             Poly << "        (pt ";
                                             Poly << F_str(ARC[CouN]).c_str();
                                             Poly << " ";
                                             Poly << F_str(ARC[CouN+1]).c_str();
                                             Poly << ")";
                                             Poly << endl;
                                             X = ARC[CouN];
                                             Y = ARC[CouN+1];
                                             CUTOUT(2,lr);
                                             CouN++;
                                             CouN++;
                                             }
                             }
                         FPC.getline(str,2500);
                         A = str;
                         A = A.Trim();
                         if (D)       //��������� cutout...
                            {
                              if (countstr > 1)
                                     {
                                     double ARC[max_arc];
                                     long LeN = Generate_Line (X, Y, FirstX, FirstY, F, &ARC[0]);
                                     long CouN = 2;
                                     while (CouN < LeN)
                                             {
                                             Poly << "        (pt ";
                                             Poly << F_str(ARC[CouN]).c_str();
                                             Poly << " ";
                                             Poly << F_str(ARC[CouN+1]).c_str();
                                             Poly << ")";
                                             Poly << endl;
                                             X = ARC[CouN];
                                             Y = ARC[CouN+1];
                                             CUTOUT(2,lr);
                                             CouN++;
                                             CouN++;
                                             }
                                     countstr = -1;
                                     }
                              Poly << "          )";
                              Poly << endl;
                              Poly << "        )";
                              Poly << endl;
                              CUTOUT(3,lr);
                              if (get("corner") == 0)
                                 {
                                  Poly << "        (cutout ";
                                  Poly << endl;
                                  Poly << "          (cutoutOutline ";
                                  Poly << endl;
                                  CUTOUT(1,lr);
                                 }//if (get("corner") == 0)

                            }//if (D)
                         Xback = X;
                         Yback = Y;
                         Fback = F;
                         countstr++;
                       }//while (get("corner") == 0)

                 Poly << "      )";
                 Poly << endl;
                 Poly << "    )";
                 Poly << endl;
                 Poly.close();
                 delete[] ISLAND;
                 }
            continue;
          }       //else if (get ("area") == 0)
       else if (get ("net") == 0)
          {
            AnsiString ref;
            AnsiString pn;
            i = Prob(1);
            B = ex_str(i);
            net_name = B;
            NETLIST << (AnsiString("  (net \"") + B + "\"").c_str() << endl;
            do{
            FPC.getline(str,2500);
            A = str;
            A = A.Trim(); }while (A.Length() == 0);
            while (get ("pin") == 0)
                  {
                    i = Prob(2);
                    ref = "";
                    while (A.SubString(i,1) != ".")
                          {
                           ref = ref + A.SubString(i,1);
                           i++;
                          }
                    i++;
                    pn = "";
                    while (i <= A.Length())
                          {
                           pn = pn + A.SubString(i,1);
                           i++;
                          }
                    //��������� ������� �����
                    //��������� ������� �����
                    Form1->Label1->Caption = "��������� ������� �����...";
                    Application->ProcessMessages();

                    //��������� compInst.TXT
                    ifstream compIns ((Path + "compInst.TXT").c_str());
                    compIns.getline(str,2500);
                    A = str;
                    A = A.Trim();
                    B = AnsiString("(compInst \"") + ref + "\"";
                    Form1->Label1->Caption = "Netlist: ��������� " + ref;
                    Application->ProcessMessages();
                    long cnts = 0;
                    while (get(B))
                          {
                           compIns.getline(str,2500);
                           A = str;
                           A = A.Trim();
                           cnts++;
                           if (A.SubString(1,3) == "END") break;
                          }
                    compIns.getline(str,2500);
                    A = str;
                    A = A.Trim();
                    i = Prob(1);
                    B = "";
                    if (i)      B = ex_str(i);
                    compIns.close();

                    //��������� PATTERNS.TXT
                    ifstream PAT ((Path + "PATTERNS.TXT").c_str());
                    PAT.getline(str,2500);
                    A = str;
                    A = A.Trim();
                    if (B.Length()) B = AnsiString("(patternDefExtended \"") + B + "\"";
                    Form1->Label1->Caption = AnsiString("Netlist: �������� ����� ") + ref + "." + pn;
                    Application->ProcessMessages();
                    cnts = 0;
                    if (B.Length())
                    while (get(B))
                          {
                           PAT.getline(str,2500);
                           A = str;
                           A = A.Trim();
                           cnts++;
                           if (A.SubString(1,3) == "END") break;
                          }
                    cnts = 0;
                    if (B.Length())
                    while (get("(multiLayer"))
                          {
                           PAT.getline(str,2500);
                           A = str;
                           A = A.Trim();
                           cnts++;
                           if (!get("(patternDefExtended")) break;
                          }
                    cnts = 0;
                    if (!get("(multiLayer"))
                        {
                        while (get("(pad"))
                                {
                                PAT.getline(str,2500);
                                A = str;
                                A = A.Trim();
                                if (A.SubString(1,1) == ")") break;
                                }
                        }
                    bool Flag_Find_Pin = false;
                    while (get("(pad") == 0)
                          {
                           i = go(2,"defaultPinDes") ;
                           i = go(i," ") ;
                           B = ex_str(i);
                           if ( B.SubString(1,B.Length()) == pn.SubString(1,pn.Length()) )
                              {
                                Flag_Find_Pin = true;
                                break;
                              }
                           PAT.getline(str,2500);
                           A = str;
                           A = A.Trim();
                          }
                    PAT.close();
                    if (Flag_Find_Pin == false) Flag_Warning2 = true;
                    else
                       {
                         B = AnsiString("    (node \"") + ref + "\" \"" + pn + "\")";
                         i = 0;
                         while (NETS[i].Length() != 0)
                               {
                                if(NETS[i].SubString(1,NETS[i].Length()) == B.SubString(1,B.Length()) )  Flag_Find_Pin = false;
                                i++;
                               }
                         if (Flag_Find_Pin == true ) NETLIST << B.c_str() << endl;
                         NETS[i] = B;
                       }

                    FPC.getline(str,2500);
                    A = str;
                    A = A.Trim();
                  }//while (get ("pin") == 0)
            NETLIST << "  )" << endl;
            continue;
          }//if (get ("net") == 0)
       CA = BA;
       BA = A;
       FPC.getline(str,2500);
       A = str;
       A = A.Trim();
      }//����� ������ NET
//=====================================================
//=====================================================
//=====================================================
Form1->ListBox2_Texts->Clear();
Form1->Label1->Caption = "������...";
Application->ProcessMessages();
while (get ("[end]"))
      {//������ ������ �������
       FPC.getline(str,2500);
       A = str;
       A = A.Trim();
 if (get ("text:") == 0)
          {
           AnsiString text_string;
           double x;
           double y;
           double angle;
           i = Prob(1);
           text_string = ex_str(i);                     //�����
           x = ex_float_NM(&i, units_mm);               //x
           y = ex_float_NM(&i, units_mm);               //y
           int LR = ex_float_NM(&i, -1);                //layer
           Angle = ex_float_NM(&i, -1);                 //����
           int mirror = ex_float_NM(&i, -1);            //mirror
           H = ex_float_NM(&i, units_mm);               //height
           W = ex_float_NM(&i, units_mm);               //line_width

           AnsiString TXT = "        (text (pt ";
           TXT = TXT + F_str(x);
           TXT = TXT + " ";
           TXT = TXT + F_str(y);
           TXT = TXT + ") \"";
           TXT = TXT + text_string;
           TXT = TXT + "\" (textStyleRef \"T";
           TXT = TXT + F_str(H);
           TXT = TXT + "x";
           TXT = TXT + F_str(W);
           if (Angle != 0 )
              {
                if (mirror == 0) Angle = 360 - Angle;
                if( Angle < 0 )  Angle += 360;
                TXT = TXT + "\") (rotation " + Angle + ") ";
              }
           else TXT = TXT + "\") ";
           if (mirror)
                TXT = TXT + "(isFlipped True) ";//(justify LowerRight) ";
           TXT = TXT + ")";
           TXT = TXT + LR;
           Form1->ListBox2_Texts->Items->Add(TXT);
           ADD_text_style();
          }//if (get ("text") == 0)
      }//����� ������ �������
//=====================================================
//=====================================================
//=====================================================
NETLIST.close();
FPC.close();
Form1->Label1->Caption = "������!";
Application->ProcessMessages();
ofstream NETL ;
NETL.open((Path + "NETLIST.TXT").c_str(), std::ios_base::app );
NETL << "END" << endl;
NETL.close();
ofstream PAD;
PAD.open((Path + "PADSTYLE.TXT").c_str(), std::ios_base::app );
PAD << "END" << endl;
PAD.close();
ofstream VIA ;
VIA.open((Path + "VIASTYLE.TXT").c_str(), std::ios_base::app );
VIA << "END" << endl;
VIA.close();
ofstream compD ;
compD.open((Path + "compDef.TXT").c_str(), std::ios_base::app );
compD << "END" << endl;
compD.close();
///ofstream compIn ;
///compIn.open((Path + "compInst.TXT").c_str(), std::ios_base::app );
///compIn << "END" << endl;
///compIn.close();
ofstream TExtst ;
TExtst.open((Path + "TEXTSTYLE.TXT").c_str(), std::ios_base::app );
TExtst << "END" << endl;
TExtst.close();
ofstream PATTR ;
PATTR.open((Path + "PATTERNS.TXT").c_str(), std::ios_base::app );
PATTR << "END" << endl;
PATTR.close();
ofstream PArt ;
PArt.open((Path + "PARTS.TXT").c_str(), std::ios_base::app );
PArt << "END" << endl;
PArt.close();
ofstream POL ;
POL.open((Path + "POLY.TXT").c_str(), std::ios_base::app );
POL << "END" << endl;
POL.close();
ofstream CUTOUT ;
CUTOUT.open((Path + "CUTOUTS_AREA.TXT").c_str(), std::ios_base::app );
CUTOUT << "END" << endl;
CUTOUT.close();
ofstream SOLDERM ;
SOLDERM.open((Path + "SOLDERMASK.TXT").c_str(), std::ios_base::app );
SOLDERM << "END" << endl;
SOLDERM.close();
ofstream TXTs ;
TXTs.open((Path + "TEXTS.TXT").c_str(), std::ios_base::app );
TXTs << "END" << endl;
TXTs.close();
ofstream BoRD ;
BoRD.open((Path + "BOARD.TXT").c_str(), std::ios_base::app );
BoRD << "END" << endl;
BRD.close();
ofstream top ;
top.open((Path + "TOP.TXT").c_str(), std::ios_base::app );
top << "END" << endl;
top.close();
ofstream btm;
btm.open((Path + "BOTTOM.TXT").c_str(), std::ios_base::app );
btm << "END" << endl;
btm.close();
ofstream in1;
in1.open((Path + "INNER1.TXT").c_str(), std::ios_base::app );
in1 << "END" << endl;
in1.close();
ofstream in2;
in2.open((Path + "INNER2.TXT").c_str(), std::ios_base::app );
in2 << "END" << endl;
in2.close();
ofstream in3;
in3.open((Path + "INNER3.TXT").c_str(), std::ios_base::app );
in3 << "END" << endl;
in3.close();
ofstream in4;
in4.open((Path + "INNER4.TXT").c_str(), std::ios_base::app );
in4 << "END" << endl;
in4.close();
ofstream in5;
in5.open((Path + "INNER5.TXT").c_str(), std::ios_base::app );
in5 << "END" << endl;
in5.close();
ofstream in6;
in6.open((Path + "INNER6.TXT").c_str(), std::ios_base::app );
in6 << "END" << endl;
in6.close();
ofstream in7;
in7.open((Path + "INNER7.TXT").c_str(), std::ios_base::app );
in7 << "END" << endl;
in7.close();
ofstream in8;
in8.open((Path + "INNER8.TXT").c_str(), std::ios_base::app );
in8 << "END" << endl;
in8.close();
ofstream in9;
in9.open((Path + "INNER9.TXT").c_str(), std::ios_base::app );
in9 << "END" << endl;
in9.close();
ofstream in10;
in10.open((Path + "INNER10.TXT").c_str(), std::ios_base::app );
in10 << "END" << endl;
in10.close();
ofstream in11;
in11.open((Path + "INNER11.TXT").c_str(), std::ios_base::app );
in11 << "END" << endl;
in11.close();
ofstream in12;
in12.open((Path + "INNER12.TXT").c_str(), std::ios_base::app );
in12 << "END" << endl;
in12.close();
ofstream in13;
in13.open((Path + "INNER13.TXT").c_str(), std::ios_base::app );
in13 << "END" << endl;
in13.close();
ofstream in14;
in14.open((Path + "INNER14.TXT").c_str(), std::ios_base::app );
in14 << "END" << endl;
in14.close();
PCB_file_designer();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
Timer1->Interval = 30000;
Timer1->Enabled = false;
Translate();
Form1->FormStyle = fsNormal;
Form1->Visible = false;
Sleep(100);
if (Flag_Warning1 == true) ShowMessage("    Warning: the origin must be on the bottom left and outside of the circuit board objects.");
if (Flag_Warning2 == true) ShowMessage("    Warning: Netlist contains nonexistent pins. (Ignored)");
////if (Flag_Warning3 == true) ShowMessage("    ��������������: ���������� ����� ������ 1999. (����� 1999)");
////if (Flag_Warning4 == true) ShowMessage("    ��������������: ���������� ����� � ��������� ������ 1999. (����� 1999)");
if (Flag_Warning5 == true) ShowMessage("    Warning: Present unrouted segment!");
if (Flag_Warning6 == true) ShowMessage("    Error ex_str! ");
//-------------������ ------------
B = ExtractFilePath(Form1->OpenDialog1->FileName);
B = B + "PCAD\\" + ExtractFileName(Form1->OpenDialog1->FileName) + ".pcb";
A = ExtractFileName(B.c_str());
if ((UINT)ShellExecute(NULL,
               "open",
               B.c_str(),
               NULL,
               A.c_str() ,
               SW_SHOWNORMAL) <=32)
               {
                 ShowMessage  ("What program to open this file? There is no application associated with * .PCB files.");
               }
exit(0) ;
}
//---------------------------------------------------------------------------
