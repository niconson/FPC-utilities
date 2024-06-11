//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DXF_3D.h"
#include "fstream.h"
#include "clipbrd.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"
TForm1 *Form1;
double D;
double F;
long i;
long prob;
long n_pins = 0;
long pins = 0;
long Type_3D = 0;
long lines = 0;
int MaxPins = 0;
int MaxLines = 0;
char s[255];
AnsiString A;
AnsiString B;
AnsiString C;

static double *X_pins;
static double *Y_pins;
static double *W_top;
static double *L_top;
static double *W_bot;
static double *L_bot;
static double *Hole_pins;
double H;
double PH;
double DX;
double DY;
static AnsiString *ANG_pins;
static long *Type_top;
static long *Type_bot;
double **LINES;
double *W_LINES;
double sel_rect_1[2];
double sel_rect_2[2];
double CENTX = 0;
double CENTY = 0;
long *Type_lines;
bool *Poly_lines;
bool units = false;
bool Flag_DXF = false;
bool FL_Warning1 = false;
bool FL_Warning2 = false;
//long Count_pins = 0;
//long Count_lines = 0;
// ЦВЕТА СЛОЕВ:
//1 - Board
//2 - Top_copper
//3 - Bottom_copper
//4 - Top_silk
//5 - Bottom_silk
//6 - Grid
//7 - Text
//8 - Solder_mask_cutout
void read_foot (void);
void Prob(void);
void MIRROR (void);
void MIRROR_ROTATE (bool Lay, AnsiString Ang);
float ex_float (long index);
void Rotate_Vertex (double *X, double *Y, double Ang);
AnsiString ex_str (AnsiString ANSI, long *n);
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
Form1->StringGrid1->Options<<10 = true;
Form1->Height = 412;
Form1->Label9->Enabled = false;
Form1->Label10->Enabled = false;
Form1->ComboBox4->Enabled = false;
Form1->ComboBox5->Enabled = false;
Form1->Label1->Caption = "Толщина линий:";
Form1->Label2->Caption = "В Описании футпринта(Descryption)";
Form1->Label3->Caption = "необходимо указать:";
Form1->Label4->Caption = "Высота компонента h=...(mm)(Обязательно)";
Form1->Label12->Caption = "Высота полилиний Ph=...(mm)(Опционально)";
Form1->Label5->Caption = "Форма: R-круг, S-по TopSilk(Опционально)";
Form1->Label6->Caption = "Пример: \"DXF: S, h=3, Ph=2\"";
Form1->Label14->Caption = "По умолчанию форма = SelRect компонента";
Form1->Label15->Caption = "Для SelRect: dx, dy изменение размеров";
Form1->FormStyle = fsStayOnTop;
Form1->BorderStyle = bsDialog;
Form1->CheckBox1->Caption = "Печатать в файл сетку";
Form1->Label7->Caption = "Толщина платы:";
Form1->Label8->Caption = "Толщина Фольги:";
Form1->Label9->Caption = "Диаметр точки:";
Form1->Label10->Caption = "Шаг сетки:";
Form1->Label11->Caption = "Процесс: 0%";
Form1->Label13->Caption = "Высота текста:";
Form1->ComboBox1->Style = csOwnerDrawFixed;
Form1->ComboBox2->Style = csOwnerDrawFixed;
Form1->ComboBox3->Style = csOwnerDrawFixed;
Form1->ComboBox4->Style = csOwnerDrawFixed;
Form1->ComboBox5->Style = csOwnerDrawFixed;
Form1->CheckBox2->Caption = "Трассы верх";
Form1->CheckBox3->Caption = "Площадки верх";
Form1->CheckBox4->Caption = "Вырезы в маске";
Form1->CheckBox5->Caption = "Верх 3DRect";
Form1->CheckBox6->Caption = "Низ 3DRect";
Form1->CheckBox7->Caption = "Трассы низ"  ;
Form1->CheckBox8->Caption = "Площадки низ";
Form1->CheckBox9->Caption = "Отверстия";
Form1->CheckBox10->Caption = "Текст: Обозначения";
Form1->CheckBox11->Caption = "Текст: Значения";
Form1->CheckBox12->Caption = "Текст под углом";
Form1->CheckBox13->Caption = "Шелкография верх";
Form1->CheckBox14->Caption = "Шелкография низ";
Form1->CheckBox15->Caption = "Рамка выделения (SelRect)";
i = 10;
while (i < 201)
      {
       ComboBox1->Items->Add(AnsiString(i) + " micrometers");
       i = i + 10;
      }
i = 250;
while (i < 1001)
      {
       ComboBox1->Items->Add(AnsiString(i) + " micrometers");
       i = i + 50;
      }
ComboBox1->ItemIndex = 9;
i = 100;
while (i < 5001)
      {
       ComboBox2->Items->Add(AnsiString(i) + " micrometers");
       i = i + 100;
      }
i = 10;
while (i < 151)
      {
       ComboBox4->Items->Add(AnsiString(i) + " micrometers");
       i = i + 10;
      }
i = 160;
while (i < 501)
      {
       ComboBox4->Items->Add(AnsiString(i) + " micrometers");
       i = i + 50;
      }
i = 300;
while (i < 1001)
      {
       ComboBox5->Items->Add(AnsiString(i) + " micrometers");
       i = i + 100;
      }
i = 2000;
while (i < 10001)
      {
       ComboBox5->Items->Add(AnsiString(i) + " micrometers");
       i = i + 1000;
      }
i = 300;
while (i < 2001)
      {
       ComboBox6->Items->Add(AnsiString(i) + " micrometers");
       i = i + 100;
      }
ComboBox2->ItemIndex = 14;
ComboBox3->Items->Add("18 micrometers");
ComboBox3->Items->Add("35 micrometers");
ComboBox3->Items->Add("50 micrometers");
ComboBox3->ItemIndex = 1;
ComboBox4->ItemIndex = 4;
ComboBox5->ItemIndex = 9;
ComboBox6->ItemIndex = 2;
AnsiString CLPBRD = Clipboard()->AsText;
if (CLPBRD.SubString(1,15) == "Message_from_CM")
        {
        A = CLPBRD;
        prob = 1;
        Prob();
        OpenDialog1->FileName = ex_str(CLPBRD, &prob) ;
        CLPBRD = ExtractFileName (OpenDialog1->FileName);
        Form1->Caption = "DXF export for " + CLPBRD;
        }
else if (OpenDialog1->Execute())
   {
    if(OpenDialog1->FileName.Length() == 0) return;
   }
else exit(0);
}
//---------------------------------------------------------------------------
//=================== ЧТЕНИЕ - ЗАПИСЬ =======================
//=================== КНОПКА ОК =============================
void __fastcall TForm1::Button1Click(TObject *Sender)
{
Form1->Label11->Visible = true;
AnsiString A2;
A = OpenDialog1->FileName;
ifstream READ (A.c_str());
A = ExtractFilePath(Application->ExeName);
A = A + "Output.dxf";
ofstream WR (A.c_str());
A = Form1->ComboBox1->Items->operator [](Form1->ComboBox1->ItemIndex);
B = Form1->ComboBox2->Items->operator [](Form1->ComboBox2->ItemIndex);
i = 0;
while (A.SubString(i,1) != " ")i++;
A = A.SubString(1,(i-1));
long Th_line = StrToInt(A);
i = 0;
while (B.SubString(i,1) != " ")i++;
B = B.SubString(1,(i-1));
long Th_board = StrToInt(B);
A = Form1->ComboBox3->Items->operator [](Form1->ComboBox3->ItemIndex);
i = 0;
while (A.SubString(i,1) != " ")i++;
A = A.SubString(1,(i-1));
long Th_copper = StrToInt(A);
A = Form1->ComboBox4->Items->operator [](Form1->ComboBox4->ItemIndex);
i = 0;
while (A.SubString(i,1) != " ")i++;
A = A.SubString(1,(i-1));
long Th_point_grid = StrToInt(A);
A = Form1->ComboBox5->Items->operator [](Form1->ComboBox5->ItemIndex);
i = 0;
while (A.SubString(i,1) != " ")i++;
A = A.SubString(1,(i-1));
long Step_grid = StrToInt(A);
A = Form1->ComboBox6->Items->operator [](Form1->ComboBox6->ItemIndex);
i = 0;
while (A.SubString(i,1) != " ")i++;
A = A.SubString(1,(i-1));
long H_text = StrToInt(A);
long out;
WR << "0" << endl;
WR << "SECTION" << endl;
WR << "2" << endl;
WR << "ENTITIES" << endl;

//--------- Создание сетки ----------
if (Form1->CheckBox1->Checked == true)
        {//ПЕЧАТЬ СЕТКИ
        double Xmin;
        double Xmax;
        double Ymin;
        double Ymax;
        bool flg = false;
        A = OpenDialog1->FileName;
        ifstream GRID (A.c_str());
        out = 0;
        while (out < 5)
                {
                GRID.getline(s,250);
                A = s;
                A = A.Trim();
                if (A.SubString(1,7) == "[board]") break;
                if (A.SubString(1,A.Length()) == A2.SubString(1,A2.Length())) {out++; continue;}
                A2 = A;
                out = 0;
                }
        out = 0;
        //****************************************************
        //НАХОДИМ МИН И МАКС КООРДИНАТЫ
        //****************************************************
        while (out < 5)
                {
                GRID.getline(s,250);
                A = s;
                A = A.Trim();
                if (A.SubString(1,7) == "[solder") break;
                if (A.SubString(1,A.Length()) == A2.SubString(1,A2.Length())) {out++; continue;}
                A2 = A;
                out = 0;
                if (A.Length() == 0) continue;
                else if (A.SubString(1,6) == "corner")
                        {
                        i = 9;
                        B = "";
                        while (A.SubString(i,1) != " ") {i++; if (i>250)break;}
                        while (A.SubString(i,1) == " ") {i++; if (i>250)break;}
                        while (A.SubString(i,1) != " ")
                                {
                                B = B + A.SubString(i,1);
                                i++;
                                }
                        D = StrToFloat(B);
                        D = D/(double)1000000;
                        if (flg == false)
                                {
                                Xmin = D;
                                Xmax = D;
                                }
                        if (D < Xmin) Xmin = D;
                        if (D > Xmax) Xmax = D;
                        B = "";
                        while (A.SubString(i,1) == " ") {i++; if (i>250)break;}
                        while (A.SubString(i,1) != " ")
                                {
                                B = B + A.SubString(i,1);
                                i++;
                                }
                        D = StrToFloat(B);
                        D = D/(double)1000000;
                        if (flg == false)
                                {
                                Ymin = D;
                                Ymax = D;
                                }
                        if (D < Ymin) Ymin = D;
                        if (D > Ymax) Ymax = D;
                        flg = true;
                        }//else if (A.SubString(i,7) == "outline")
                }//while (out < 5)
        GRID.close();
        //****************************************************
        //РИСУЕМ СЕТКУ
        //****************************************************

        double Xm = Xmin;
        while (Ymin < Ymax)
                {
                WR << "0" << endl;
                WR << "POLYLINE" << endl;
                WR << "8" << endl;
                WR << "Grid" << endl;
                WR << "38" << endl;
                WR << "0" << endl;
                D = (double)Th_board/(double)1000;
                WR << "39" << endl;
                WR << D << endl;
                WR << "70" << endl;
                WR << "1" << endl;
                WR << "62" << endl;
                WR << "6" << endl;
                D = (double)Th_line/(double)1000;
                WR << "40" << endl;
                WR << D << endl;
                WR << "41" << endl;
                WR << D << endl;
                //---------------
                WR << "0" << endl;
                WR << "VERTEX" << endl;
                WR << "10" <<
                endl;
                D = (double)Th_point_grid/(double)1000;
                D = Xmin - D;
                WR << D << endl;
                WR << "20" << endl;
                WR << Ymin << endl;
                WR << "42" << endl;
                WR << "1" << endl;
                //---------------
                WR << "0" << endl;
                WR << "VERTEX" << endl;
                WR << "10" << endl;
                D = (double)Th_point_grid/(double)1000;
                D = Xmin + D;
                WR << D << endl;
                WR << "20" << endl;
                WR << Ymin << endl;
                WR << "42" << endl;
                WR << "1" << endl;
                WR << "0" << endl;
                WR << "SEQEND" << endl;

                D = (double)Step_grid/(double)1000;
                Xmin = Xmin + D;
                if (Xmin > Xmax)
                        {
                        Xmin = Xm;
                        Ymin = Ymin + D;
                        }
                }//while (Ymin < Ymax)
        }//ПЕЧАТЬ СЕТКИ
        //****************************************************
        //****************************************************
        //---------------БОРДЕР---------------------
out = 0;
int ML = 0;
while (out < 5)
        {
        READ.getline(s,250);
        A = s;
        A = A.Trim();
        if (A.SubString(1,7) == "[board]")
                {
                if (MaxLines < ML) MaxLines = ML;
                break;
                }
        if (A.SubString(1,A.Length()) == A2.SubString(1,A2.Length())) {out++; continue;}
        A2 = A;
        out = 0;
        if (A.SubString(1,6) == "n_pins")
                        {
                        prob = 1;
                        Prob();
                        AnsiString N_P = A.SubString(prob, (A.Length()-prob+1));
                        int NP = StrToInt(N_P);
                        if (MaxPins < NP) MaxPins = NP;
                        }
        else if (A.SubString(1,16) == "outline_polyline")ML++;
        else if (A.SubString(1,11) == "next_corner")    ML++;
        else if (A.SubString(1,6) == "close_")          ML++;
        else if (A.SubString(1,5) == "name:")
                {
                if (MaxLines < ML) MaxLines = ML;
                ML = 0;
                }
        }
//=============================
//=============================
//ДИНАМИЧЕСКОЕ ВЫДЕЛЕНИЕ ПАМЯТИ
//=============================
//=============================
Form1->Label16->Visible = true;
Form1->Label17->Visible = true;
Form1->Label16->Caption = "Lines: " + AnsiString(MaxLines);
Form1->Label17->Caption = "Pins: " + AnsiString(MaxPins);
MaxLines += 10;
MaxPins += 10;
try     {
        X_pins = new(std::nothrow) double[MaxPins];    //
        }
catch(std::bad_alloc)
        {
        ShowMessage("    Ошибка выделения памяти: double[" + AnsiString(MaxPins) + "]!" );
        exit(0);
        }
try     {
        Y_pins = new(std::nothrow) double[MaxPins];    //
        }
catch(std::bad_alloc)
        {
        ShowMessage("    Ошибка выделения памяти: double[" + AnsiString(MaxPins) + "]!" );
        exit(0);
        }
try     {
        W_top = new(std::nothrow) double[MaxPins];    //
        }
catch(std::bad_alloc)
        {
        ShowMessage("    Ошибка выделения памяти: double[" + AnsiString(MaxPins) + "]!" );
        exit(0);
        }
try     {
        L_top = new(std::nothrow) double[MaxPins];    //
        }
catch(std::bad_alloc)
        {
        ShowMessage("    Ошибка выделения памяти: double[" + AnsiString(MaxPins) + "]!" );
        exit(0);
        }
try     {
        W_bot = new(std::nothrow) double[MaxPins];    //
        }
catch(std::bad_alloc)
        {
        ShowMessage("    Ошибка выделения памяти: double[" + AnsiString(MaxPins) + "]!" );
        exit(0);
        }
try     {
        L_bot = new(std::nothrow) double[MaxPins];    //
        }
catch(std::bad_alloc)
        {
        ShowMessage("    Ошибка выделения памяти: double[" + AnsiString(MaxPins) + "]!" );
        exit(0);
        }
try     {
        Hole_pins = new(std::nothrow) double[MaxPins];    //
        }
catch(std::bad_alloc)
        {
        ShowMessage("    Ошибка выделения памяти: double[" + AnsiString(MaxPins) + "]!" );
        exit(0);
        }
try     {
        ANG_pins = new(std::nothrow) AnsiString[MaxPins];    //
        }
catch(std::bad_alloc)
        {
        ShowMessage("    Ошибка выделения памяти: AnsiString[" + AnsiString(MaxPins) + "]!" );
        exit(0);
        }
try     {
        Type_top = new(std::nothrow) long[MaxPins];    //
        }
catch(std::bad_alloc)
        {
        ShowMessage("    Ошибка выделения памяти: long[" + AnsiString(MaxPins) + "]!" );
        exit(0);
        }
try     {
        Type_bot = new(std::nothrow) long[MaxPins];    //
        }
catch(std::bad_alloc)
        {
        ShowMessage("    Ошибка выделения памяти: long[" + AnsiString(MaxPins) + "]!" );
        exit(0);
        }
//-----------
try     {
        LINES = new(std::nothrow) double*[MaxLines];    //
        }
catch(std::bad_alloc)
        {
        ShowMessage("    Ошибка выделения памяти: double[" + AnsiString(MaxLines) + "]!" );
        }
for (int ii = 0; ii<MaxLines; ii++)
        {
        try     {
                LINES[ii] = new(std::nothrow) double[4];
                }
        catch(std::bad_alloc)
                {
                ShowMessage("    Ошибка выделения памяти: double[" + AnsiString(MaxLines) + "]!" );
                }
        }
//LINES[MaxLines][4];
try     {
        W_LINES = new(std::nothrow) double[MaxLines];    //
        }
catch(std::bad_alloc)
        {
        ShowMessage("    Ошибка выделения памяти: double[" + AnsiString(MaxLines) + "]!" );
        exit(0);
        }
try     {
        Type_lines = new(std::nothrow) long[MaxLines];    //
        }
catch(std::bad_alloc)
        {
        ShowMessage("    Ошибка выделения памяти: long[" + AnsiString(MaxLines) + "]!" );
        exit(0);
        }
try     {
        Poly_lines = new(std::nothrow) bool[MaxLines];    //
        }
catch(std::bad_alloc)
        {
        ShowMessage("    Ошибка выделения памяти: bool[" + AnsiString(MaxLines) + "]!" );
        exit(0);
        }
//=============================
//=============================
//=============================
//=============================
out = 0;
while (out < 5)
        {//ЗАПИСЬ БОРДЕРА ЗАПИСЬ SOLDER MASK CUTOUT
        //bool Flag_SM_CUT = false;
        Form1->Label11->Caption = "Чтение BOARD OUTLINE";
        Application->ProcessMessages();
        READ.getline(s,250);
        A = s;
        A = A.Trim();
        if (A.SubString(1,7) == "[parts]") break;
        if (Form1->CheckBox4->Checked == false) {if (A.SubString(1,7) == "[solder") break;}
        if (A.SubString(1,A.Length()) == A2.SubString(1,A2.Length())) {out++; continue;}
        A2 = A;
        out = 0;
        if (A.Length() == 0) continue;
        else if (A.SubString(1,7) == "outline")
                {
                i = 1;
                while (A.SubString(i,1) != " ") {i++; if (i>250)break;}
                while (A.SubString(i,1) == " ") {i++; if (i>250)break;}
                while (A.SubString(i,1) != " ") {i++; if (i>250)break;}
                B = A.SubString(10,(i-10));
                D = StrToFloat(B);
                WR << "0" << endl;
                WR << "LWPOLYLINE" << endl;
                WR << "8" << endl;
                WR << "Board" << endl;
                WR << "90" << endl;
                WR << (int)D << endl;
                WR << "38" << endl;
                WR << "0" << endl;
                D = (double)Th_board/(double)1000;
                WR << "39" << endl;
                WR << D << endl;
                WR << "70" << endl;
                WR << "1" << endl;
                WR << "62" << endl;
                WR << "1" << endl;
                }//outline
        else if (A.SubString(1,6) == "corner")
                {
                i = 9;
                B = "";
                while (A.SubString(i,1) != " ") {i++; if (i>250)break;}
                while (A.SubString(i,1) == " ") {i++; if (i>250)break;}
                while (A.SubString(i,1) != " ")
                        {
                        B = B + A.SubString(i,1);
                        i++;
                        }
                D = StrToFloat(B);
                D = D/(double)1000000;
                WR << "10" << endl;
                WR << D << endl;
                B = "";
                while (A.SubString(i,1) == " ") {i++; if (i>250)break;}
                while (A.SubString(i,1) != " ")
                        {
                        B = B + A.SubString(i,1);
                        i++;
                        }
                D = StrToFloat(B);
                D = D/(double)1000000;
                WR << "20" << endl;
                WR << D << endl;
                //---------толщина ---------
                D = (double)Th_line/(double)1000;
                WR << "40" << endl;
                WR << D << endl;
                WR << "41" << endl;
                WR << D << endl;
                WR << "42" << endl;
                //------------------------
                if (A.SubString((A.Length()-1),2) == " 1" ) WR << "-0.45" << endl;
                else if (A.SubString((A.Length()-1),2) == " 2" ) WR << "0.45" << endl;
                else WR << "0" << endl;
                }//corner
        else if (A.SubString(1,9) == "sm_cutout")
                {
                //Flag_SM_CUT = true;
                Form1->Label11->Caption = "Чтение sm_cutout";
                Application->ProcessMessages();
                i = 1;
                while (A.SubString(i,1) != " ") {i++; if (i>250)break;}
                while (A.SubString(i,1) == " ") {i++; if (i>250)break;}
                while (A.SubString(i,1) != " ") {i++; if (i>250)break;}
                B = A.SubString(12,(i-12));
                D = StrToFloat(B);
                WR << "0" << endl;
                WR << "LWPOLYLINE" << endl;
                WR << "90" << endl;
                WR << (int)D << endl;
                if (A.SubString(A.Length(),1) == "9") B = "Top_copper";
                else B = "Bottom_copper";
                WR << "8" << endl;
                //WR << B.c_str() << endl;
                WR << "Solder_mask_cutout" << endl;
                D = (double)Th_board/(double)1000;
                F = (double)Th_copper/(double)1000;
                D = D + F + 0,01;
                WR << "38" << endl;
                if (B.SubString(1,1) == "T") WR << D << endl;
                else WR << -F << endl;
                D = (double)Th_board/(double)1000;
                WR << "39" << endl;
                WR << "0.01" << endl;
                WR << "70" << endl;
                WR << "1" << endl;
                WR << "62" << endl;
                WR << "8" << endl;
                }//sm_cutout
        }//ЗАПИСЬ БОРДЕРА ЗАПИСЬ SOLDER MASK CUTOUT
out = 0;
//****************************************************
//ПЛОЩАДКИ, ШЕЛКОГРАФИЯ, TOP_3D, BOTTOM_3D
//****************************************************
while (out < 5)
        {//ПЛОЩАДОК, ШЕЛКОГРАФИИ, TOP_3D, BOTTOM_3D


        //ЧТЕНИЕ PARTS



        if (A.SubString(1,6) == "[nets]") break;
        if (A.SubString(1,4) != "part")
                {
                READ.getline(s,250);
                A = s;
                A = A.Trim();
                }
        if (A.SubString(1,6) == "[nets]") break;
        if (A.SubString(1,A.Length()) == A2.SubString(1,A2.Length())) {out++; continue;}
        A2 = A;
        out = 0;
        if (A.Length() == 0) continue;
        else if (A.SubString(1,4) == "part")
                {
                Form1->Label11->Caption = "Построение " + A;
                Application->ProcessMessages();
                AnsiString reference;
                AnsiString shape;
                AnsiString value;
                AnsiString Ang_ref_text;
                AnsiString Ang_value;
                double X_pos;
                double Y_pos;
                AnsiString Angle;
                bool Layer;
                double h;
                double Ph;
                bool S;
                bool R;
                reference = A.SubString(7,(A.Length()-6)) ;
                while (1)
                        {
                        READ.getline(s,250);
                        A = s;
                        A = A.Trim();
                        C = A;
                        if (A.SubString(1,4) == "part") break;
                        else if (A.SubString(1,4) == "[net") break;
                        else if ((A.SubString(1,4) == "valu")||(A.SubString(1,4) == "shap"))
                                {
                                i = 9;
                                B = "";
                                while (A.SubString(i,2) != "\" ")
                                        {
                                        B = B + A.SubString(i,1) ;
                                        i++;
                                        if (i>=A.Length()) break;
                                        }
                                if (B.Length() > 50 ) continue;
                                i++;
                                if (A.SubString(1,4) == "shap")
                                        {
                                        shape = B;                        // shape
                                        continue ;
                                        }
                                value = B;                            // value
                                B = "";
                                while (A.SubString(i,1) == " ") i++;
                                while (A.SubString(i,1) != " ")
                                        {
                                        B = B + A.SubString(i,1);
                                        i++;
                                        if (i>A.Length()) break;
                                        }
                                if (B.Length() > 9 ) continue;
                                if (B.Length() == 0 ) continue;
                                //H_value = StrToFloat(B);              //высота  value
                                B = "";
                                while (A.SubString(i,1) == " ") i++;
                                while (A.SubString(i,1) != " ")
                                        {
                                        B = B + A.SubString(i,1);
                                        i++;
                                        if (i>A.Length()) break;
                                        }
                                if (B.Length() > 9 ) continue;
                                if (B.Length() == 0 ) continue;
                                //W_value = StrToFloat(B);              //толщина value
                                B = "";
                                while (A.SubString(i,1) == " ") i++;
                                while (A.SubString(i,1) != " ")
                                        {
                                        B = B + A.SubString(i,1) ;
                                        i++;
                                        if (i>A.Length()) break;
                                        }
                                if (B.Length() > 3 ) continue;
                                if (B.Length() == 0 ) continue;
                                Ang_value = B;                        //угол  value
                                B = "";
                                while (A.SubString(i,1) == " ") i++;
                                while (A.SubString(i,1) != " ")
                                        {
                                        B = B + A.SubString(i,1) ;
                                        i++;
                                        if (i>A.Length()) break;
                                        }
                                if (B.Length() > 9 ) continue;
                                if (B.Length() == 0 ) continue;
                                //X_value = StrToFloat(B);              // X value
                                B = "";
                                while (A.SubString(i,1) == " ") i++;
                                while (A.SubString(i,1) != " ")
                                        {
                                        B = B + A.SubString(i,1) ;
                                        i++;
                                        if (i>A.Length()) break;
                                        }
                                if (B.Length() > 9 ) continue;
                                if (B.Length() == 0 ) continue;
                                //Y_value = StrToFloat(B);              // Y
                                }
                        else if (A.SubString(1,4) == "pos:")
                                {
                                i = 6;
                                B = "";
                                while (A.SubString(i,1) != " ")
                                        {
                                        B = B + A.SubString(i,1)  ;
                                        i++;
                                        if (i>A.Length()) break;
                                        }
                                if (B.Length() > 9 ) continue;
                                if (B.Length() == 0 ) continue;
                                X_pos = StrToFloat(B);              // X_pos
                                B = "";
                                while (A.SubString(i,1) == " ") i++;
                                while (A.SubString(i,1) != " ")
                                        {
                                        B = B + A.SubString(i,1)  ;
                                        i++;
                                        if (i>A.Length()) break;
                                        }
                                if (B.Length() > 9 ) continue;
                                if (B.Length() == 0 ) continue;
                                Y_pos = StrToFloat(B);              // Y_pos
                                B = "";
                                while (A.SubString(i,1) == " ") i++;
                                while (A.SubString(i,1) != " ")
                                        {
                                        B = B + A.SubString(i,1);
                                        i++;
                                        if (i>A.Length()) break;
                                        }
                                if (B.Length() > 1 ) continue;
                                if (B.Length() == 0 ) continue;
                                if (B.SubString(1,1) == "0" ) Layer = false;   // Layer
                                else Layer = true;
                                B = "";
                                while (A.SubString(i,1) == " ") i++;
                                while (A.SubString(i,1) != " ")
                                        {
                                        B = B + A.SubString(i,1) ;
                                        i++;
                                        if (i>A.Length()) break;
                                        }
                                if (B.Length() > 3 ) continue;
                                if (B.Length() == 0 ) continue;
                                Angle = B;                     // Angle
                                }
                        }//while(1)
                B = "name: \"" + shape + "\"";
                //****************************************************
                //ЧТЕНИЕ ФУТПРИНТА
                //****************************************************
                read_foot();

                //ПЛОЩАДКИ
                long p = pins;
                pins = 0;
                while (pins < p)
                        {
                        double X1 ;
                        double X2 ;
                        double Y1 ;
                        double Y2 ;

                        // top
                        if (L_top[pins] == 0) L_top[pins] = W_top[pins];
                        if (Type_top[pins] == 5)
                        if (L_top[pins] < W_top[pins]) W_top[pins] = L_top[pins];
                        if ((ANG_pins[pins].SubString(1,1) == "9")||(ANG_pins[pins].SubString(1,1) == "2"))
                                {
                                D = X_pins[pins] - W_top[pins]/2;
                                F = Y_pins[pins] - L_top[pins]/2;
                                MIRROR_ROTATE(Layer, Angle);
                                X1 = D;
                                Y1 = F;
                                D = X_pins[pins] + W_top[pins]/2;
                                F = Y_pins[pins] + L_top[pins]/2;
                                MIRROR_ROTATE(Layer, Angle);
                                X2 = D;
                                Y2 = F;
                                }
                        else
                                {
                                D = X_pins[pins] - L_top[pins]/2;
                                F = Y_pins[pins] - W_top[pins]/2;
                                MIRROR_ROTATE(Layer, Angle);
                                X1 = D;
                                Y1 = F;
                                D = X_pins[pins] + L_top[pins]/2;
                                F = Y_pins[pins] + W_top[pins]/2;
                                MIRROR_ROTATE(Layer, Angle);
                                X2 = D;
                                Y2 = F;
                                }
                        X1 = X1 + X_pos;
                        X2 = X2 + X_pos;
                        Y1 = Y1 + Y_pos;
                        Y2 = Y2 + Y_pos;
                        X1 = X1/(double)1000000;
                        X2 = X2/(double)1000000;
                        Y1 = Y1/(double)1000000;
                        Y2 = Y2/(double)1000000;
                        bool Q = Form1->CheckBox3->Checked;
                        bool Q2 = Form1->CheckBox8->Checked;
                        if (((Q == true)&&(Layer == 0))||((Q2 == true)&&(Layer == 1)))
                                {//НАЧАЛО ЗАПИСИ ВЕРХ ПЛОЩАДКИ
                                if ((Type_top[pins] == 2)||(Type_top[pins] == 3)||(Type_top[pins] == 4))
                                        {
                                        WR << "0" << endl;
                                        WR << "SOLID" << endl;
                                        WR << "8" << endl;
                                        if (Layer == 0) WR << "Top_copper" << endl;
                                        else WR << "Bottom_copper" << endl;
                                        WR << "62" << endl;
                                        if (Layer == 0)  WR << "2" << endl;
                                        else WR << "3" << endl;
                                        D = (double)Th_board/(double)1000;
                                        F = (double)Th_copper/(double)1000;
                                        WR << "38" << endl;
                                        if (Layer == 0) WR << D << endl;
                                        else WR << -F << endl;
                                        WR << "39" << endl;
                                        WR << F << endl;
                                        WR << "10" << endl;
                                        WR << X1 << endl;
                                        WR << "20" << endl;
                                        WR << Y1 << endl;
                                        WR << "11" << endl;
                                        WR << X2 << endl;
                                        WR << "21" << endl;
                                        WR << Y1 << endl;
                                        WR << "12" << endl;
                                        WR << X1 << endl;
                                        WR << "22" << endl;
                                        WR << Y2 << endl;
                                        WR << "13" << endl;
                                        WR << X2 << endl;
                                        WR << "23" << endl;
                                        WR << Y2 << endl;
                                        }
                                if ((Type_top[pins] == 1)||(Type_top[pins] == 6)||(Type_top[pins] == 5))
                                        {
                                        WR << "0" << endl;
                                        WR << "POLYLINE" << endl;
                                        WR << "8" << endl;
                                        if (Layer == 0) WR << "Top_copper" << endl;
                                        else WR << "Bottom_copper" << endl;
                                        D = (double)Th_board/(double)1000;
                                        F = (double)Th_copper/(double)1000;
                                        WR << "38" << endl;
                                        if (Layer == 0) WR << D << endl;
                                        else WR << -F << endl;
                                        WR << "39" << endl;
                                        WR << F << endl;
                                        WR << "70" << endl;
                                        WR << "1" << endl;
                                        WR << "62" << endl;
                                        if (Layer == 0)  WR << "2" << endl;
                                        else WR << "3" << endl;
                                        D = (W_top[pins] - Hole_pins[pins])/(double)2;
                                        D = D/(double)1000000;
                                        WR << "40" << endl;
                                        WR << D << endl;
                                        WR << "41" << endl;
                                        WR << D << endl;
                                        //---------------
                                        D = X_pins[pins] - Hole_pins[pins]/(double)2 - ((W_top[pins] - Hole_pins[pins])/(double)4);
                                        F = Y_pins[pins];
                                        MIRROR_ROTATE(Layer, Angle);
                                        D = (D + X_pos)/(double)1000000;
                                        F = (F + Y_pos)/(double)1000000;
                                        WR << "0" << endl;
                                        WR << "VERTEX" << endl;
                                        WR << "10" << endl;
                                        WR << D << endl;
                                        WR << "20" << endl;
                                        WR << F << endl;
                                        WR << "42" << endl;
                                        WR << "1" << endl;
                                        //---------------
                                        D = X_pins[pins] + Hole_pins[pins]/(double)2 + ((W_top[pins] - Hole_pins[pins])/(double)4);
                                        F = Y_pins[pins];
                                        MIRROR_ROTATE(Layer, Angle);
                                        D = (D + X_pos)/(double)1000000;
                                        F = (F + Y_pos)/(double)1000000;
                                        WR << "0" << endl;
                                        WR << "VERTEX" << endl;
                                        WR << "10" << endl;
                                        WR << D << endl;
                                        WR << "20" << endl;
                                        WR << F << endl;
                                        WR << "42" << endl;
                                        WR << "1" << endl;
                                        WR << "0" << endl;
                                        WR << "SEQEND" << endl;
                                        }
                                }//if (Form1->CheckBox2->Checked = true)
                        //КОНЕЦ ЗАПИСИ ВЕРХ ПЛОЩАДКИ

                        //=======bottom




                        if (L_bot[pins] == 0) L_bot[pins] = W_bot[pins];
                        if (Type_bot[pins] == 5)
                        if (L_bot[pins] < W_bot[pins]) W_bot[pins] = L_bot[pins];
                        if ((ANG_pins[pins].SubString(1,1) == "9")||(ANG_pins[pins].SubString(1,1) == "2"))
                                {
                                D = X_pins[pins] - W_bot[pins]/2;
                                F = Y_pins[pins] - L_bot[pins]/2;
                                MIRROR_ROTATE(Layer, Angle);
                                X1 = D;
                                Y1 = F;
                                D = X_pins[pins] + W_bot[pins]/2;
                                F = Y_pins[pins] + L_bot[pins]/2;
                                MIRROR_ROTATE(Layer, Angle);
                                X2 = D;
                                Y2 = F;
                                }
                        else
                                {
                                D = X_pins[pins] - L_bot[pins]/2;
                                F = Y_pins[pins] - W_bot[pins]/2;
                                MIRROR_ROTATE(Layer, Angle);
                                X1 = D;
                                Y1 = F;
                                D = X_pins[pins] + L_bot[pins]/2;
                                F = Y_pins[pins] + W_bot[pins]/2;
                                MIRROR_ROTATE(Layer, Angle);
                                X2 = D;
                                Y2 = F;
                                }
                        X1 = X1 + X_pos;
                        X2 = X2 + X_pos;
                        Y1 = Y1 + Y_pos;
                        Y2 = Y2 + Y_pos;
                        X1 = X1/(double)1000000;
                        X2 = X2/(double)1000000;
                        Y1 = Y1/(double)1000000;
                        Y2 = Y2/(double)1000000;

                        if (((Q == true)&&(Layer == 1))||((Q2 == true)&&(Layer == 0)))
                                {//НАЧАЛО ЗАПИСИ НИЗ ПЛОЩАДКИ
                                if ((Type_bot[pins] == 2)||(Type_bot[pins] == 3)||(Type_bot[pins] == 4))
                                        {
                                        WR << "0" << endl;
                                        WR << "SOLID" << endl;
                                        WR << "8" << endl;
                                        if (Layer == 1) WR << "Top_copper" << endl;
                                        else WR << "Bottom_copper" << endl;
                                        WR << "62" << endl;
                                        if (Layer == 0)  WR << "3" << endl;
                                        else WR << "2" << endl;
                                        D = (double)Th_board/(double)1000;
                                        F = (double)Th_copper/(double)1000;
                                        WR << "38" << endl;
                                        if (Layer == 0) WR << -F << endl;
                                        else WR << D << endl;
                                        WR << "39" << endl;
                                        WR << F << endl;
                                        WR << "10" << endl;
                                        WR << X1 << endl;
                                        WR << "20" << endl;
                                        WR << Y1 << endl;
                                        WR << "11" << endl;
                                        WR << X2 << endl;
                                        WR << "21" << endl;
                                        WR << Y1 << endl;
                                        WR << "12" << endl;
                                        WR << X1 << endl;
                                        WR << "22" << endl;
                                        WR << Y2 << endl;
                                        WR << "13" << endl;
                                        WR << X2 << endl;
                                        WR << "23" << endl;
                                        WR << Y2 << endl;
                                        }
                                if ((Type_bot[pins] == 1)||(Type_bot[pins] == 6)||(Type_bot[pins] == 5))
                                        {
                                        WR << "0" << endl;
                                        WR << "POLYLINE" << endl;
                                        WR << "8" << endl;
                                        if (Layer == 1) WR << "Top_copper" << endl;
                                        else WR << "Bottom_copper" << endl;
                                        D = (double)Th_board/(double)1000;
                                        F = (double)Th_copper/(double)1000;
                                        WR << "38" << endl;
                                        if (Layer == 0) WR << -F << endl;
                                        else WR << D << endl;
                                        WR << "39" << endl;
                                        WR << F << endl;
                                        WR << "70" << endl;
                                        WR << "1" << endl;
                                        WR << "62" << endl;
                                        if (Layer == 0)  WR << "3" << endl;
                                        else WR << "2" << endl;
                                        D = (W_bot[pins] - Hole_pins[pins])/(double)2;
                                        D = D/(double)1000000;
                                        WR << "40" << endl;
                                        WR << D << endl;
                                        WR << "41" << endl;
                                        WR << D << endl;
                                        //---------------
                                        D = X_pins[pins] - Hole_pins[pins]/(double)2 - ((W_bot[pins] - Hole_pins[pins])/(double)4);
                                        F = Y_pins[pins];
                                        MIRROR_ROTATE(Layer, Angle);
                                        D = (D + X_pos)/(double)1000000;
                                        F = (F + Y_pos)/(double)1000000;
                                        WR << "0" << endl;
                                        WR << "VERTEX" << endl;
                                        WR << "10" << endl;
                                        WR << D << endl;
                                        WR << "20" << endl;
                                        WR << F << endl;
                                        WR << "42" << endl;
                                        WR << "1" << endl;
                                        //---------------
                                        D = X_pins[pins] + Hole_pins[pins]/(double)2 + ((W_bot[pins] - Hole_pins[pins])/(double)4);
                                        F = Y_pins[pins];
                                        MIRROR_ROTATE(Layer, Angle);
                                        D = (D + X_pos)/(double)1000000;
                                        F = (F + Y_pos)/(double)1000000;
                                        WR << "0" << endl;
                                        WR << "VERTEX" << endl;
                                        WR << "10" << endl;
                                        WR << D << endl;
                                        WR << "20" << endl;
                                        WR << F << endl;
                                        WR << "42" << endl;
                                        WR << "1" << endl;
                                        WR << "0" << endl;
                                        WR << "SEQEND" << endl;
                                        }
                                }//КОНЕЦ ЗАПИСИ НИЗ ПЛОЩАДКИ
                        if ((Hole_pins[pins] != 0)&&(Form1->CheckBox9->Checked == true))
                                {//ОТВЕРСТИЯ
                                WR << "0" << endl;
                                WR << "POLYLINE" << endl;
                                WR << "8" << endl;
                                WR << "Board" << endl;
                                D = (double)Th_board/(double)1000;
                                F = ((double)Th_copper + (double)10)/(double)1000;
                                D = D + F*(double)2;
                                WR << "38" << endl;
                                WR << -F << endl;
                                WR << "39" << endl;
                                WR << D << endl;
                                WR << "70" << endl;
                                WR << "1" << endl;
                                WR << "62" << endl;
                                WR << "1" << endl;
                                D = (double)Th_line/(double)1000;
                                WR << "40" << endl;
                                WR << D << endl;
                                WR << "41" << endl;
                                WR << D << endl;
                                //---------------
                                D = X_pins[pins] - Hole_pins[pins]/(double)2;
                                F = Y_pins[pins];
                                MIRROR_ROTATE(Layer, Angle);
                                D = D + X_pos;
                                D = D/(double)1000000;
                                F = F + Y_pos;
                                F = F/(double)1000000;

                                //--------------
                                WR << "0" << endl;
                                WR << "VERTEX" << endl;
                                WR << "10" << endl;
                                WR << D << endl;
                                WR << "20" << endl;
                                WR << F << endl;
                                WR << "42" << endl;
                                WR << "1" << endl;
                                //---------------
                                D = X_pins[pins] + Hole_pins[pins]/(double)2;
                                F = Y_pins[pins];
                                MIRROR_ROTATE(Layer, Angle);
                                D = D + X_pos;
                                D = D/(double)1000000;
                                F = F + Y_pos;
                                F = F/(double)1000000;

                                //---------------
                                WR << "0" << endl;
                                WR << "VERTEX" << endl;
                                WR << "10" << endl;
                                WR << D << endl;
                                WR << "20" << endl;
                                WR << F << endl;
                                WR << "42" << endl;
                                WR << "1" << endl;
                                WR << "0" << endl;
                                WR << "SEQEND" << endl;
                                }
                        pins++;
                        }//while (p < pins)

                //****************************************************
                //ШЕЛКОГРАФИЯ TOP_3D, BOTTOM_3D
                //****************************************************
                bool Q ;
                if ((Form1->CheckBox5->Checked) || (Form1->CheckBox13->Checked)) Q = true;
                bool Q2;
                if ((Form1->CheckBox6->Checked) || (Form1->CheckBox14->Checked)) Q2 = true;
                if (((Q == true)&&(Layer == 0))||((Q2 == true)&&(Layer == 1)))
                        {//НАЧАЛО ПОСТРОЕНИЯ 3D
                        //------------------------------------
                        if ((Type_3D == 1)&&(H != 0))  // КРУГ
                                {
                                //-----------------------------------
                                //-----------------------------------
                                if (Layer == 0) D = (double)Th_board/(double)1000 + (double)Th_copper/(double)1000;
                                else D = -H - (double)Th_copper/(double)1000;
                                double x_circle = (sel_rect_1[0] + sel_rect_2[0])/(double)2;
                                double y_circle = (sel_rect_1[1] + sel_rect_2[1])/(double)2;
                                double RadiuS = x_circle - sel_rect_1[0] ;
                                x_circle += X_pos;
                                y_circle += Y_pos;
                                x_circle = x_circle/(double)1000000;
                                y_circle = y_circle/(double)1000000;
                                RadiuS = RadiuS/(double)1000000;
                                F = D;
                                while (F < (D+H))
                                        {
                                        WR << "0" << endl;
                                        WR << "CIRCLE" << endl;
                                        WR << "8" << endl;
                                        if (Layer == 0) WR << "Top_silk" << endl;
                                        else WR << "Bottom_silk" << endl;
                                        WR << "62" << endl;
                                        if (Layer == 0)  WR << "4" << endl;
                                        else WR << "5" << endl;
                                        WR << "10" << endl;
                                        WR << x_circle << endl;
                                        WR << "20" << endl;
                                        WR << y_circle << endl;
                                        WR << "30" << endl;
                                        WR << F << endl;
                                        WR << "40" << endl;
                                        WR << RadiuS << endl;
                                        F += (double)1/(double)10;
                                        }
                                }
                        //-------------------------------------
                        else if (Type_3D == 0)// ПО РАМКЕ SELRECT (Type_3D == 0)
                                {

                                if ((DX)&&(DY))
                                                {
                                                sel_rect_1[0] = CENTX - DX*(double)1000000;
                                                sel_rect_1[1] = CENTY - DY*(double)1000000;
                                                }
                                ///else if (Type_3D == 2) H =0;
                                D = sel_rect_1[0];
                                F = sel_rect_1[1];
                                MIRROR_ROTATE(Layer, Angle);
                                sel_rect_1[0] = D + X_pos;
                                sel_rect_1[1] = F + Y_pos;
                                if ((DX)&&(DY))
                                                {
                                                sel_rect_2[0] = CENTX + DX*(double)1000000;
                                                sel_rect_2[1] = CENTY + DY*(double)1000000;
                                                }
                                D = sel_rect_2[0];
                                F = sel_rect_2[1];
                                MIRROR_ROTATE(Layer, Angle);
                                sel_rect_2[0] = D + X_pos;
                                sel_rect_2[1] = F + Y_pos;
                                sel_rect_1[0] = sel_rect_1[0]/(double)1000000;
                                sel_rect_1[1] = sel_rect_1[1]/(double)1000000;
                                sel_rect_2[0] = sel_rect_2[0]/(double)1000000;
                                sel_rect_2[1] = sel_rect_2[1]/(double)1000000;
                                if (H != 0)
                                        {
                                        //------ SOLID 1------
                                        WR << "0" << endl;
                                        WR << "SOLID" << endl;
                                        WR << "8" << endl;
                                        if (Layer == 0) WR << "Top_silk" << endl;
                                        else WR << "Bottom_silk" << endl;
                                        WR << "62" << endl;
                                        if (Layer == 0)  WR << "4" << endl;
                                        else WR << "5" << endl;
                                        D = H + (double)Th_board/(double)1000 + (double)Th_copper/(double)1000;
                                        F = H + (double)Th_copper/(double)1000;
                                        //УРОВЕНЬ ЛИНИИ
                                        double Z ;
                                        if (Layer == 0) Z = D;
                                        else Z = -F;
                                        //
                                        WR << "10" << endl;
                                        WR << sel_rect_1[0] << endl;
                                        WR << "20" << endl;
                                        WR << sel_rect_1[1] << endl;
                                        WR << "30" << endl;                //УРОВЕНЬ ЛИНИИ
                                        WR << Z << endl;
                                        WR << "11" << endl;
                                        WR << sel_rect_2[0] << endl;
                                        WR << "21" << endl;
                                        WR << sel_rect_1[1] << endl;
                                        WR << "31" << endl;                //УРОВЕНЬ ЛИНИИ
                                        WR << Z << endl;
                                        WR << "12" << endl;
                                        WR << sel_rect_1[0] << endl;
                                        WR << "22" << endl;
                                        WR << sel_rect_2[1] << endl;
                                        WR << "32" << endl;                //УРОВЕНЬ ЛИНИИ
                                        WR << Z << endl;
                                        WR << "13" << endl;
                                        WR << sel_rect_2[0] << endl;
                                        WR << "23" << endl;
                                        WR << sel_rect_2[1] << endl;
                                        WR << "33" << endl;                //УРОВЕНЬ ЛИНИИ
                                        WR << Z << endl;

                                        //------ SOLID 2------
                                        WR << "0" << endl;
                                        WR << "SOLID" << endl;
                                        WR << "8" << endl;
                                        if (Layer == 0) WR << "Top_silk" << endl;
                                        else WR << "Bottom_silk" << endl;
                                        WR << "62" << endl;
                                        if (Layer == 0)  WR << "4" << endl;
                                        else WR << "5" << endl;
                                        D = H + (double)Th_board/(double)1000 + (double)Th_copper/(double)1000;
                                        F = H + (double)Th_copper/(double)1000;
                                        //УРОВЕНЬ ЛИНИИ
                                        if (Layer == 0) Z = D-H;
                                        else Z = H-F;
                                        //
                                        WR << "10" << endl;
                                        WR << sel_rect_1[0] << endl;
                                        WR << "20" << endl;
                                        WR << sel_rect_1[1] << endl;
                                        WR << "30" << endl;                //УРОВЕНЬ ЛИНИИ
                                        WR << Z << endl;
                                        WR << "11" << endl;
                                        WR << sel_rect_2[0] << endl;
                                        WR << "21" << endl;
                                        WR << sel_rect_1[1] << endl;
                                        WR << "31" << endl;                //УРОВЕНЬ ЛИНИИ
                                        WR << Z << endl;
                                        WR << "12" << endl;
                                        WR << sel_rect_1[0] << endl;
                                        WR << "22" << endl;
                                        WR << sel_rect_2[1] << endl;
                                        WR << "32" << endl;                //УРОВЕНЬ ЛИНИИ
                                        WR << Z << endl;
                                        WR << "13" << endl;
                                        WR << sel_rect_2[0] << endl;
                                        WR << "23" << endl;
                                        WR << sel_rect_2[1] << endl;
                                        WR << "33" << endl;                //УРОВЕНЬ ЛИНИИ
                                        WR << Z << endl;

                                        //------ SOLID 3------
                                        WR << "0" << endl;
                                        WR << "SOLID" << endl;
                                        WR << "8" << endl;
                                        if (Layer == 0) WR << "Top_silk" << endl;
                                        else WR << "Bottom_silk" << endl;
                                        WR << "62" << endl;
                                        if (Layer == 0)  WR << "4" << endl;
                                        else WR << "5" << endl;
                                        D = (double)Th_board/(double)1000 + (double)Th_copper/(double)1000;
                                        F = H + (double)Th_copper/(double)1000;
                                        //УРОВЕНЬ ЛИНИИ
                                        ////double Z ;
                                        if (Layer == 0) Z = D;
                                        else Z = -F;
                                        //
                                        WR << "10" << endl;
                                        WR << sel_rect_1[0] << endl;
                                        WR << "20" << endl;
                                        WR << sel_rect_1[1] << endl;
                                        WR << "30" << endl;                //УРОВЕНЬ ЛИНИИ
                                        WR << Z << endl;
                                        WR << "11" << endl;
                                        WR << sel_rect_2[0] << endl;
                                        WR << "21" << endl;
                                        WR << sel_rect_1[1] << endl;
                                        WR << "31" << endl;                //УРОВЕНЬ ЛИНИИ
                                        WR << Z << endl;
                                        WR << "12" << endl;
                                        WR << sel_rect_1[0] << endl;
                                        WR << "22" << endl;
                                        WR << sel_rect_1[1] << endl;
                                        WR << "32" << endl;                //УРОВЕНЬ ЛИНИИ
                                        WR << (Z+H) << endl;
                                        WR << "13" << endl;
                                        WR << sel_rect_2[0] << endl;
                                        WR << "23" << endl;
                                        WR << sel_rect_1[1] << endl;
                                        WR << "33" << endl;                //УРОВЕНЬ ЛИНИИ
                                        WR << (Z+H) << endl;

                                        //------ SOLID 4------
                                        WR << "0" << endl;
                                        WR << "SOLID" << endl;
                                        WR << "8" << endl;
                                        if (Layer == 0) WR << "Top_silk" << endl;
                                        else WR << "Bottom_silk" << endl;
                                        WR << "62" << endl;
                                        if (Layer == 0)  WR << "4" << endl;
                                        else WR << "5" << endl;
                                        D = (double)Th_board/(double)1000 + (double)Th_copper/(double)1000;
                                        F = H + (double)Th_copper/(double)1000;
                                        //УРОВЕНЬ ЛИНИИ
                                        ////double Z ;
                                        if (Layer == 0) Z = D;
                                        else Z = -F;
                                        //
                                        WR << "10" << endl;
                                        WR << sel_rect_1[0] << endl;
                                        WR << "20" << endl;
                                        WR << sel_rect_1[1] << endl;
                                        WR << "30" << endl;                //УРОВЕНЬ ЛИНИИ
                                        WR << Z << endl;
                                        WR << "11" << endl;
                                        WR << sel_rect_1[0] << endl;
                                        WR << "21" << endl;
                                        WR << sel_rect_2[1] << endl;
                                        WR << "31" << endl;                //УРОВЕНЬ ЛИНИИ
                                        WR << Z << endl;
                                        WR << "12" << endl;
                                        WR << sel_rect_1[0] << endl;
                                        WR << "22" << endl;
                                        WR << sel_rect_1[1] << endl;
                                        WR << "32" << endl;                //УРОВЕНЬ ЛИНИИ
                                        WR << (Z+H) << endl;
                                        WR << "13" << endl;
                                        WR << sel_rect_1[0] << endl;
                                        WR << "23" << endl;
                                        WR << sel_rect_2[1] << endl;
                                        WR << "33" << endl;                //УРОВЕНЬ ЛИНИИ
                                        WR << (Z+H) << endl;

                                        //------ SOLID 5------
                                        WR << "0" << endl;
                                        WR << "SOLID" << endl;
                                        WR << "8" << endl;
                                        if (Layer == 0) WR << "Top_silk" << endl;
                                        else WR << "Bottom_silk" << endl;
                                        WR << "62" << endl;
                                        if (Layer == 0)  WR << "4" << endl;
                                        else WR << "5" << endl;
                                        D = (double)Th_board/(double)1000 + (double)Th_copper/(double)1000;
                                        F = H + (double)Th_copper/(double)1000;
                                        //УРОВЕНЬ ЛИНИИ
                                        ////double Z ;
                                        if (Layer == 0) Z = D;
                                        else Z = -F;
                                        //
                                        WR << "10" << endl;
                                        WR << sel_rect_2[0] << endl;
                                        WR << "20" << endl;
                                        WR << sel_rect_2[1] << endl;
                                        WR << "30" << endl;                //УРОВЕНЬ ЛИНИИ
                                        WR << Z << endl;
                                        WR << "11" << endl;
                                        WR << sel_rect_2[0] << endl;
                                        WR << "21" << endl;
                                        WR << sel_rect_1[1] << endl;
                                        WR << "31" << endl;                //УРОВЕНЬ ЛИНИИ
                                        WR << Z << endl;
                                        WR << "12" << endl;
                                        WR << sel_rect_2[0] << endl;
                                        WR << "22" << endl;
                                        WR << sel_rect_2[1] << endl;
                                        WR << "32" << endl;                //УРОВЕНЬ ЛИНИИ
                                        WR << (Z+H) << endl;
                                        WR << "13" << endl;
                                        WR << sel_rect_2[0] << endl;
                                        WR << "23" << endl;
                                        WR << sel_rect_1[1] << endl;
                                        WR << "33" << endl;                //УРОВЕНЬ ЛИНИИ
                                        WR << (Z+H) << endl;

                                        //------ SOLID 6------
                                        WR << "0" << endl;
                                        WR << "SOLID" << endl;
                                        WR << "8" << endl;
                                        if (Layer == 0) WR << "Top_silk" << endl;
                                        else WR << "Bottom_silk" << endl;
                                        WR << "62" << endl;
                                        if (Layer == 0)  WR << "4" << endl;
                                        else WR << "5" << endl;
                                        D = (double)Th_board/(double)1000 + (double)Th_copper/(double)1000;
                                        F = H + (double)Th_copper/(double)1000;
                                        //УРОВЕНЬ ЛИНИИ
                                        ////double Z ;
                                        if (Layer == 0) Z = D;
                                        else Z = -F;
                                        //
                                        WR << "10" << endl;
                                        WR << sel_rect_2[0] << endl;
                                        WR << "20" << endl;
                                        WR << sel_rect_2[1] << endl;
                                        WR << "30" << endl;                //УРОВЕНЬ ЛИНИИ
                                        WR << Z << endl;
                                        WR << "11" << endl;
                                        WR << sel_rect_1[0] << endl;
                                        WR << "21" << endl;
                                        WR << sel_rect_2[1] << endl;
                                        WR << "31" << endl;                //УРОВЕНЬ ЛИНИИ
                                        WR << Z << endl;
                                        WR << "12" << endl;
                                        WR << sel_rect_2[0] << endl;
                                        WR << "22" << endl;
                                        WR << sel_rect_2[1] << endl;
                                        WR << "32" << endl;                //УРОВЕНЬ ЛИНИИ
                                        WR << (Z+H) << endl;
                                        WR << "13" << endl;
                                        WR << sel_rect_1[0] << endl;
                                        WR << "23" << endl;
                                        WR << sel_rect_2[1] << endl;
                                        WR << "33" << endl;                //УРОВЕНЬ ЛИНИИ
                                        WR << (Z+H) << endl;
                                        }//if (H != 0)
                                }//else // ПО РАМКЕ SELRECT (Type_3D == 0)
                        //----------------------------------------
                        if      ((Type_3D == 2) ||     //ПО ШЕЛКОГР
                                ((Layer == 0) && (Form1->CheckBox13->Checked)) ||
                                ((Layer == 1) && (Form1->CheckBox14->Checked)) )
                                {
                                long L = lines;
                                lines = 0;
                                double H_d = 0;
                                double PH_d = 0;
                                if (Type_3D != 2)
                                if (Layer == 1)
                                        {
                                        H_d = H;
                                        PH_d = PH;
                                        }
                                int cnt = 0;
                                if (!PH) PH = H;
                                while (lines < L)
                                        {
                                        WR << "0" << endl;
                                        WR << "POLYLINE" << endl;
                                        WR << "8" << endl;
                                        if (Layer == 0) WR << "Top_silk" << endl;
                                        else WR << "Bottom_silk" << endl;
                                        D = (double)Th_board/(double)1000 + (double)Th_copper/(double)1000;
                                        if (Poly_lines[lines] == false) F = H + (double)Th_copper/(double)1000;
                                        else F = PH + (double)Th_copper/(double)1000;
                                        WR << "38" << endl;
                                        if (Poly_lines[lines] == false) {D += H_d; F -= H_d; }
                                        else {D += PH_d; F -= PH_d;}
                                        if (Layer == 0) WR << D << endl;
                                        else WR << -F << endl;
                                        if (Type_3D == 2)
                                                {
                                                WR << "39" << endl;
                                                if (Poly_lines[lines] == false) WR << H/(double)15 << endl;
                                                else WR << PH/(double)15 << endl;
                                                }
                                        WR << "70" << endl;
                                        WR << "0" << endl;
                                        WR << "62" << endl;
                                        if (Layer == 0)  WR << "4" << endl;
                                        else WR << "5" << endl;
                                        D = W_LINES[lines]/(double)1000000;
                                        WR << "40" << endl;
                                        WR << D << endl;
                                        WR << "41" << endl;
                                        WR << D << endl;
                                        //---------------
                                        WR << "0" << endl;
                                        WR << "VERTEX" << endl;
                                        WR << "10" << endl;
                                        D = LINES[lines][0];
                                        F = LINES[lines][1];
                                        MIRROR_ROTATE(Layer, Angle);
                                        D = D + X_pos;
                                        F = F + Y_pos;
                                        D = D/(double)1000000;
                                        F = F/(double)1000000;
                                        WR << D << endl;
                                        WR << "20" << endl;
                                        WR << F << endl;
                                        WR << "42" << endl;
                                        if (Layer == 0)
                                                {
                                                if (Type_lines[lines] == 1 ) WR << "-0.45" << endl;
                                                else if (Type_lines[lines] == 2 ) WR << "0.45" << endl;
                                                else WR << "0" << endl;
                                                }
                                        else    {
                                                if (Type_lines[lines] == 1 ) WR << "0.45" << endl;
                                                else if (Type_lines[lines] == 2 ) WR << "-0.45" << endl;
                                                else WR << "0" << endl;
                                                }
                                        //---------------
                                        WR << "0" << endl;
                                        WR << "VERTEX" << endl;
                                        WR << "10" << endl;
                                        D = LINES[lines][2];
                                        F = LINES[lines][3];
                                        MIRROR_ROTATE(Layer, Angle);
                                        D = D + X_pos;
                                        F = F + Y_pos;
                                        D = D/(double)1000000;
                                        F = F/(double)1000000;
                                        WR << D << endl;
                                        WR << "20" << endl;
                                        WR << F << endl;
                                        WR << "42" << endl;
                                        //if (Type_lines[lines] == 1  ) WR << "-0.45" << endl;
                                        //else if (Type_lines[lines] == 2 ) WR << "0.45" << endl;
                                        WR << "0" << endl;
                                        WR << "0" << endl;
                                        WR << "SEQEND" << endl;
                                        lines++;
                                        if (lines >= L)
                                        if (cnt < 15)
                                                {
                                                if (Type_3D != 2) break;
                                                lines = 0;
                                                cnt++;
                                                H_d += H/(double)15;
                                                PH_d += PH/(double)15;
                                                }
                                        }
                                }
                        if (Form1->CheckBox15->Checked)
                                {
                                //------- полилиния по SELRECT------
                                WR << "0" << endl;
                                WR << "POLYLINE" << endl;
                                WR << "8" << endl;
                                if (Layer == 0) WR << "Top_silk" << endl;
                                else WR << "Bottom_silk" << endl;
                                D = (double)Th_board/(double)1000 + (double)Th_copper/(double)1000;
                                F = H + (double)Th_copper/(double)1000;
                                WR << "38" << endl;
                                if (Layer == 0) WR << D << endl;
                                else WR << -F << endl;
                                WR << "39" << endl;
                                WR << H << endl;
                                WR << "70" << endl;
                                WR << "1" << endl;
                                WR << "62" << endl;
                                if (Layer == 0)  WR << "4" << endl;
                                else WR << "5" << endl;
                                D = (double)Th_line/(double)1000;
                                WR << "40" << endl;
                                WR << D << endl;
                                WR << "41" << endl;
                                WR << D << endl;
                                //---------------     POINT 1
                                WR << "0" << endl;
                                WR << "VERTEX" << endl;
                                WR << "10" << endl;
                                WR << sel_rect_1[0] << endl;
                                WR << "20" << endl;
                                WR << sel_rect_1[1] << endl;
                                WR << "42" << endl;
                                WR << "0" << endl;
                                //---------------     POINT 2
                                WR << "0" << endl;
                                WR << "VERTEX" << endl;
                                WR << "10" << endl;
                                WR << sel_rect_1[0] << endl;
                                WR << "20" << endl;
                                WR << sel_rect_2[1] << endl;
                                WR << "42" << endl;
                                WR << "0" << endl;
                                //---------------     POINT 3
                                WR << "0" << endl;
                                WR << "VERTEX" << endl;
                                WR << "10" << endl;
                                WR << sel_rect_2[0] << endl;
                                WR << "20" << endl;
                                WR << sel_rect_2[1] << endl;
                                WR << "42" << endl;
                                WR << "0" << endl;
                                //---------------     POINT 4
                                WR << "0" << endl;
                                WR << "VERTEX" << endl;
                                WR << "10" << endl;
                                WR << sel_rect_2[0] << endl;
                                WR << "20" << endl;
                                WR << sel_rect_1[1] << endl;
                                WR << "42" << endl;
                                WR << "0" << endl;
                                //-----------------
                                WR << "0" << endl;
                                WR << "SEQEND" << endl;
                                }
                        }//КОНЕЦ ПОСТРОЕНИЯ 3D

                //****************************************************
                //*********       ТЕКСТ       ***********
                //****************************************************
                AnsiString text = "";
                if (Form1->CheckBox10->Checked == true) text = text + reference + " ";
                if (Form1->CheckBox11->Checked == true) text = text + value ;
                if (text.Length() != 0)
                        {//НАЧАЛО ТЕКСТ
                        WR << "0" << endl;
                        WR << "TEXT" << endl;
                        WR << "8" << endl;
                        WR << "Text" << endl;
                        D = (double)Th_board/(double)1000;
                        F = (double)Th_copper/(double)1000;
                        WR << "38" << endl;           //уровень поднятия
                        if (PH > H) H = PH;
                        if (Layer == 0) WR << (D + F + H) << endl;
                        else WR << (-F - H) << endl;
                        WR << "40" << endl;           //высота букв
                        D = H_text/(double)1000;
                        WR << D << endl;
                        WR << "7" << endl;            //стиль
                        WR << "STANDARD" << endl;
                        if (Layer == 1)
                                {
                                WR << "71" << endl;       //отражение
                                WR << "2" << endl;
                                }
                        if (Form1->CheckBox12->Checked == true)
                                {
                                WR << "50" << endl;       //угол
                                WR << "45.0" << endl;
                                }
                        WR << "41" << endl;           //сжатие
                        WR << "0.5" << endl;
                        WR << "62" << endl;           //цвет
                        WR << "9" << endl;
                        WR << "1" << endl;
                        WR << text.c_str() << endl;
                        WR << "10" << endl;
                        WR << (X_pos/(double)1000000) << endl;
                        WR << "20" << endl;
                        WR << (Y_pos/(double)1000000) << endl;
                        }//КОНЕЦ ТЕКСТ
               }//part
       A = C;
      }//ЗАПИСЬ ПЛОЩАДОК, ШЕЛКОГРАФИИ, TOP_3D, BOTTOM_3D


//**********************************************************
// ТРАССЫ
//**********************************************************
Form1->Label11->Caption = "Построение трасс";
Application->ProcessMessages();
out = 0;
while (out < 5)
      {//ЗАПИСЬ ТРАСС

       READ.getline(s,250);
       A = s;
       A = A.Trim();
       if (A.SubString(1,7) == "[texts]") break;
       if (A.SubString(1,A.Length()) == A2.SubString(1,A2.Length())) {out++; continue;}
       A2 = A;
       out = 0;
       if (A.Length() == 0) continue;
       else if (A.SubString(1,3) == "vtx")
               {
                // обработка первой вершины
                prob = 2;
                Prob();
                B = "";
                while (A.SubString(prob,1) == " ")prob++;
                while (A.SubString(prob,1) != " ")
                      {
                       B = B + A.SubString(prob,1);
                       prob++;
                       if(prob>250)continue;
                      }
                double x = StrToFloat(B) ;                    //x
                x = x/(double)1000000;
                B = "";
                while (A.SubString(prob,1) == " ")prob++;
                while (A.SubString(prob,1) != " ")
                      {
                       B = B + A.SubString(prob,1);
                       prob++;
                       if(prob>250)continue;
                      }
                double y = StrToFloat(B) ;                    //y
                y = y/(double)1000000;
                double x2;
                double y2;
                double WTH;
                double LR;
                ////bool flag1 = false;
                while (1)
                      {// next corner..
                       READ.getline(s,250);
                       A = s;
                       A = A.Trim();
                       if (A.SubString(1,3) == "[te") break;
                       if (A.SubString(1,3) == "net") break;
                       if (A.SubString(1,3) == "con") break;
                       if (A.SubString(1,3) == "vtx")
                          {//ВЕРШИНА
                             double via_W;
                             double via_H;
                             prob = 2;
                             Prob();
                             B = "";
                             while (A.SubString(prob,1) == " ")prob++;
                             while (A.SubString(prob,1) != " ")
                                   {
                                    B = B + A.SubString(prob,1);
                                    prob++;
                                    if(prob>250)continue;
                                   }
                             x2 = StrToFloat(B) ;                    //x2
                             x2 = x2/(double)1000000;
                             B = "";
                             while (A.SubString(prob,1) == " ")prob++;
                             while (A.SubString(prob,1) != " ")
                                   {
                                    B = B + A.SubString(prob,1);
                                    prob++;
                                    if(prob>250)continue;
                                   }
                             y2 = StrToFloat(B) ;                    //y2
                             y2 = y2/(double)1000000;
                             prob = 6;
                             Prob();
                             B = "";
                             while (A.SubString(prob,1) == " ")prob++;
                             while (A.SubString(prob,1) != " ")
                                   {
                                    B = B + A.SubString(prob,1);
                                    prob++;
                                    if(prob>250)continue;
                                   }
                             via_W = StrToFloat(B) ;                    //via_W
                             via_W = via_W/(double)1000000;
                             B = "";
                             while (A.SubString(prob,1) == " ")prob++;
                             while (A.SubString(prob,1) != " ")
                                   {
                                    B = B + A.SubString(prob,1);
                                    prob++;
                                    if(prob>250)continue;
                                   }
                             via_H = StrToFloat(B) ;                    //via_H
                             via_H = via_H/(double)1000000;

           //рисуем дорожку...

                            WR << "0" << endl;
                            WR << "POLYLINE" << endl;
                            WR << "8" << endl;
                            if (LR == 12) WR << "Top_copper" << endl;
                            else WR << "Bottom_copper" << endl;

                            D = (double)Th_board/(double)1000 ;
                            F = (double)Th_copper/(double)2000;

                            WR << "38" << endl;
                            if (LR == 12) WR << D << endl;
                            else WR << -F << endl;
                            WR << "39" << endl;
                            WR << F << endl;
                            WR << "40" << endl;
                            WR << WTH << endl;
                            WR << "41" << endl;
                            WR << WTH << endl;
                            WR << "62" << endl;
                            if (LR == 12)  WR << "2" << endl;
                            else WR << "3" << endl;
                            bool aq = Form1->CheckBox2->Checked;
                            bool bq = Form1->CheckBox7->Checked;
                            D = 0;
                            if (((aq == false)&&(LR == 12))||((bq == false)&&(LR == 13))) D = 1;
                            WR << "60" << endl;    //visible/invis
                            WR << D << endl;       //visible/invis
                            //----------
                            WR << "0" << endl;
                            WR << "VERTEX" << endl;
                            WR << "10" << endl;
                            WR << x << endl;
                            WR << "20" << endl;
                            WR << y << endl;
                            WR << "42" << endl;
                            WR << "0" << endl;
                            WR << "0" << endl;
                            WR << "VERTEX" << endl;
                            WR << "10" << endl;
                            WR << x2 << endl;
                            WR << "20" << endl;
                            WR << y2 << endl;
                            WR << "42" << endl;
                            WR << "0" << endl;
                            WR << "0" << endl;
                            WR << "SEQEND" << endl;
                            //---------------
                            if (via_W != 0)
                               {  //TOP
                                 WR << "0" << endl;
                                 WR << "POLYLINE" << endl;
                                 WR << "8" << endl;
                                 WR << "Top_copper" << endl;
                                 D = (double)Th_board/(double)1000;
                                 F = (double)Th_copper/(double)1000;
                                 WR << "38" << endl;
                                 WR << D << endl;
                                 WR << "39" << endl;
                                 WR << F << endl;
                                 WR << "70" << endl;
                                 WR << "1" << endl;
                                 WR << "62" << endl;
                                 WR << "2" << endl;
                                 D = (via_W - via_H)/(double)2;
                                 WR << "40" << endl;
                                 WR << D << endl;
                                 WR << "41" << endl;
                                 WR << D << endl;

                                 //---------------
                                 WR << "0" << endl;
                                 WR << "VERTEX" << endl;
                                 WR << "10" << endl;
                                 D = x2 - via_H/(double)2 - ((via_W - via_H)/(double)4);
                                 F = x2 + via_H/(double)2 + ((via_W - via_H)/(double)4);
                                 WR << D << endl;
                                 WR << "20" << endl;
                                 WR << y2 << endl;
                                 WR << "42" << endl;
                                 WR << "1" << endl;
                                 //---------------
                                 WR << "0" << endl;
                                 WR << "VERTEX" << endl;
                                 WR << "10" << endl;
                                 WR << F << endl;
                                 WR << "20" << endl;
                                 WR << y2 << endl;
                                 WR << "42" << endl;
                                 WR << "1" << endl;
                                 WR << "0" << endl;
                                 WR << "SEQEND" << endl;

                                 //BOT
                                 WR << "0" << endl;
                                 WR << "POLYLINE" << endl;
                                 WR << "8" << endl;
                                 WR << "Bottom_copper" << endl;
                                 D = (double)Th_board/(double)1000;
                                 F = (double)Th_copper/(double)1000;
                                 WR << "38" << endl;
                                 WR << -F << endl;
                                 WR << "39" << endl;
                                 WR << F << endl;
                                 WR << "70" << endl;
                                 WR << "1" << endl;
                                 WR << "62" << endl;
                                 WR << "3" << endl;
                                 D = (via_W - via_H)/(double)2;
                                 WR << "40" << endl;
                                 WR << D << endl;
                                 WR << "41" << endl;
                                 WR << D << endl;
                                 //---------------
                                 WR << "0" << endl;
                                 WR << "VERTEX" << endl;
                                 WR << "10" << endl;
                                 D = x2 - via_H/(double)2 - ((via_W - via_H)/(double)4);
                                 F = x2 + via_H/(double)2 + ((via_W - via_H)/(double)4);
                                 WR << D << endl;
                                 WR << "20" << endl;
                                 WR << y2 << endl;
                                 WR << "42" << endl;
                                 WR << "1" << endl;
                                 //---------------
                                 WR << "0" << endl;
                                 WR << "VERTEX" << endl;
                                 WR << "10" << endl;
                                 WR << F << endl;
                                 WR << "20" << endl;
                                 WR << y2 << endl;
                                 WR << "42" << endl;
                                 WR << "1" << endl;
                                 WR << "0" << endl;
                                 WR << "SEQEND" << endl;
                               }  //if (via_W != 0)
                            if (via_H != 0)
                               {
                                 WR << "0" << endl;
                                 WR << "POLYLINE" << endl;
                                 WR << "8" << endl;
                                 WR << "Board" << endl;
                                 D = (double)Th_board/(double)1000;
                                 F = (double)Th_copper/(double)970;
                                 WR << "38" << endl;
                                 WR << -F << endl;
                                 WR << "39" << endl;
                                 WR << (D + F + F) << endl;
                                 WR << "70" << endl;
                                 WR << "1" << endl;
                                 WR << "62" << endl;
                                 WR << "1" << endl;
                                 D = (double)Th_line/(double)1000;
                                 WR << "40" << endl;
                                 WR << D << endl;
                                 WR << "41" << endl;
                                 WR << D << endl;

                                 //---------------
                                 WR << "0" << endl;
                                 WR << "VERTEX" << endl;
                                 WR << "10" << endl;
                                 D = x2 - via_H/(double)2;
                                 F = x2 + via_H/(double)2;
                                 WR << D << endl;
                                 WR << "20" << endl;
                                 WR << y2 << endl;
                                 WR << "42" << endl;
                                 WR << "1" << endl;
                                 //---------------
                                 WR << "0" << endl;
                                 WR << "VERTEX" << endl;
                                 WR << "10" << endl;
                                 WR << F << endl;
                                 WR << "20" << endl;
                                 WR << y2 << endl;
                                 WR << "42" << endl;
                                 WR << "1" << endl;
                                 WR << "0" << endl;
                                 WR << "SEQEND" << endl;
                               }  //if (via_H != 0)
                            x = x2;
                            y = y2;
                          }
                       else if (A.SubString(1,3) == "seg")
                          {//СЕГМЕНТ
                             prob = 2;
                             Prob();
                             B = "";
                             while (A.SubString(prob,1) == " ")prob++;
                             while (A.SubString(prob,1) != " ")
                                   {
                                    B = B + A.SubString(prob,1);
                                    prob++;
                                    if(prob>250)continue;
                                   }
                             LR = StrToFloat(B) ;                    //LR
                             B = "";
                             while (A.SubString(prob,1) == " ")prob++;
                             while (A.SubString(prob,1) != " ")
                                   {
                                    B = B + A.SubString(prob,1);
                                    prob++;
                                    if(prob>250)continue;
                                   }
                             WTH = StrToFloat(B) ;                    //WTH
                             WTH = WTH/(double)1000000;
                          }//else if (A.SubString(1,3) == "seg")
                      }//while (1)
               }//else if (A.SubString(1,3) == "vtx")
      }//ЗАПИСЬ ТРАСС

// ----ЗАВЕРШЕНИЕ --------
WR << "0" << endl;
WR << "ENDSEC" << endl;
WR << "0" << endl;
WR << "EOF" << endl;
READ.close();
WR.close();
if (FL_Warning1 == true) ShowMessage ("     Предупреждение: Число линий > 995!");
if (FL_Warning2 == true) ShowMessage ("     Предупреждение: Число пинов > 1495!");

//-------------запуск ------------
B = ExtractFilePath(Application->ExeName);
B = B + "Output.dxf";
A = ExtractFileName(B.c_str());
if ((UINT)ShellExecute(NULL,
               "open",
               B.c_str(),
               NULL,
               A.c_str() ,
               SW_SHOWNORMAL) <=32)
               {
                 ShowMessage  ("     File " + B + " not found!");
               }
exit(0);
}
//===========================================================================
//---------------------------------------------------------------------------
void __fastcall TForm1::CheckBox1Click(TObject *Sender)
{
if (Form1->CheckBox1->Checked == true)
   {
    Form1->Label9->Enabled = true;
    Form1->Label10->Enabled = true;
    Form1->ComboBox4->Enabled = true;
    Form1->ComboBox5->Enabled = true;
   }
else
   {
    Form1->Label9->Enabled = false;
    Form1->Label10->Enabled = false;
    Form1->ComboBox4->Enabled = false;
    Form1->ComboBox5->Enabled = false;
   }
}


//---------------------------------------------------------------------------
//============== чтение футпринта ==============
void read_foot (void)
{
Flag_DXF = false;
n_pins = 0;
pins = 0;
lines = 0;
H = 0;
PH = 0;
DX = 0;
DY = 0;
CENTX = 0;
CENTY = 0;
Type_3D = 0;
i = 0;
while (i < MaxPins)
        {
        X_pins[i] = 0;
        Y_pins[i] = 0;
        W_top[i] = 0;
        L_top[i] = 0;
        W_bot[i] = 0;
        L_bot[i] = 0;
        Hole_pins[i] = 0;
        i++;
        }
i = 0;
while (i < MaxLines)
        {
        LINES[i][0] = 0;
        LINES[i][1] = 0;
        LINES[i][2] = 0;
        LINES[i][3] = 0;
        Poly_lines[i] = 0;
        W_LINES[i] = 0;
        i++;
        }
double XX = 0;
double YY = 0;
long mem = 0;
bool First_pin = false;
A = Form1->OpenDialog1->FileName;
ifstream read_foot (A.c_str()) ;
while (B.SubString(1,B.Length()) != A.SubString(1,A.Length()))
      {
       read_foot.getline(s,250);
       A = s;
       A = A.Trim();
       if (A.SubString(1,A.Length()) == "[board]" ) break;
      }
while (1)
      {
       if (A.SubString(1,A.Length()) == "[board]" ) break;
       if (lines > MaxLines)
                {
                lines = MaxLines;
                FL_Warning1 = true;
                }
       if (pins >= MaxPins)
                {
                pins = MaxPins;
                FL_Warning2 = true;
                return;
                }
       read_foot.getline(s,250);
       A = s;
       A = A.Trim();
       if (A.SubString(1,4) == "name" ) break;
       if (A.Length() == 0 ) break;
       if (A.SubString(1,6) == "n_pins" )
          {
           prob = 1;
           Prob();
           prob++;
           B = A.SubString(prob,(A.Length()-prob+1));
           n_pins = StrToInt(B);
         //  if (n_pins > 1495)
          }
       else if (A.SubString(1,8) == "centroid" )
               {
                 prob = 2;
                 Prob();
                 i = prob;
                 CENTX = ex_float(i);
                 CENTY = ex_float(i);
               }
       else if (A.SubString(1,8) == "descript" )
               {
                i = 10;
                while (i <= A.Length())
                      {
                       if (A.UpperCase().SubString(i,3) == "DXF") Flag_DXF = true;
                       if (Flag_DXF == true)
                       {//чтение параметров
                       if (A.UpperCase().SubString(i,1) == "R") Type_3D = 1;
                       if (A.UpperCase().SubString(i,1) == "S") Type_3D = 2;
                       if ((A.UpperCase().SubString(i,2) == "H=")||
                           (A.UpperCase().SubString(i,3) == "PH=")||
                           (A.UpperCase().SubString(i,3) == "DX=")||
                           (A.UpperCase().SubString(i,3) == "DY="))
                          {//чтение параметров DXF
                           long n = i;
                           bool FLg = false;
                           B = "";
                           while ((A.SubString(i,1) < 0 )||(A.SubString(i,1) > 9 ))
                                 {
                                   i++;
                                   if (A.SubString(i,1) == "-") B = "-";
                                   if (i>250) break;
                                 }
                           while ((A.SubString(i,1) >= 0 )&&(A.SubString(i,1) <= 9 ))
                                 {
                                  if (i>250) break;
                                  B = B + A.SubString(i,1);
                                  i++;
                                  if ((A.SubString(i,1) == "." )||(A.SubString(i,1) == "," ) )
                                     {
                                       if (FLg == true) break;
                                       B = B + ",";
                                       i++;
                                       FLg = true;
                                     }
                                 }
                           if (B.SubString(1,1) == "," ) B = "0" + B;
                           if (B.SubString(B.Length(),1) == "," ) B = B + "0";
                           if (B.Length() > 10) break;
                           B = StringReplace(B,".",",",TReplaceFlags()<<rfReplaceAll);
                           if (A.UpperCase().SubString(n,2) == "H=") H = StrToFloat(B);
                           else if (A.UpperCase().SubString(n,3) == "PH=") PH = StrToFloat(B);
                           else if (A.UpperCase().SubString(n,3) == "DX=") DX = StrToFloat(B);
                           else DY = StrToFloat(B);
                          }//крнец чтения параметров DXF
                       }//if (Flag_DXF == true)
                       i++;
                      }//while (i <= A.Length())
               }
       else if (A.SubString(1,7) == "outline" )
               {
                Poly_lines[lines] = false;
                mem = lines;
                prob = 1;
                Prob();
                B = "";
                while (A.SubString(prob,1) == " ") prob++;
                while (A.SubString(prob,1) != " ")
                      {
                       B = B + A.SubString(prob,1);
                       prob++;
                       if (prob > 250) continue;
                      }
                B = StringReplace(B,".",",",TReplaceFlags()<<rfReplaceAll);
                W_LINES[lines] = StrToFloat(B);                 // толщина линии
                if (units == false) W_LINES[lines] = W_LINES[lines]*25400;
                B = "";
                while (A.SubString(prob,1) == " ") prob++;
                while (A.SubString(prob,1) != " ")
                      {
                       B = B + A.SubString(prob,1);
                       prob++;
                       if (prob > 250) continue;
                      }
                B = StringReplace(B,".",",",TReplaceFlags()<<rfReplaceAll);
                LINES[lines][0] = StrToFloat(B);                 // X_1
                if (units == false) LINES[lines][0] = LINES[lines][0]*25400;
                XX = LINES[lines][0];
                B = "";
                while (A.SubString(prob,1) == " ") prob++;
                while (prob <= A.Length())
                      {
                       B = B + A.SubString(prob,1);
                       prob++;
                       if (prob > 250) continue;
                      }
                B = StringReplace(B,".",",",TReplaceFlags()<<rfReplaceAll);
                LINES[lines][1] = StrToFloat(B);                 // Y_1
                if (units == false) LINES[lines][1] = LINES[lines][1]*25400;
                YY = LINES[lines][1];
               }
       else if (A.SubString(1,5) == "next_" )
               {
                Poly_lines[lines] = false;
                prob = 1;
                Prob();
                B = "";
                while (A.SubString(prob,1) == " ") prob++;
                while (A.SubString(prob,1) != " ")
                      {
                       B = B + A.SubString(prob,1);
                       prob++;
                       if (prob > 250) continue;
                      }
                B = StringReplace(B,".",",",TReplaceFlags()<<rfReplaceAll);
                LINES[lines][2] = StrToFloat(B);                 // X_2
                if (units == false) LINES[lines][2] = LINES[lines][2]*25400;
                B = "";
                while (A.SubString(prob,1) == " ") prob++;
                while (A.SubString(prob,1) != " ")
                      {
                       B = B + A.SubString(prob,1);
                       prob++;
                       if (prob > 250) continue;
                      }
                B = StringReplace(B,".",",",TReplaceFlags()<<rfReplaceAll);
                LINES[lines][3] = StrToFloat(B);                 // Y_2
                if (units == false) LINES[lines][3] = LINES[lines][3]*25400;

                if (A.SubString((A.Length()-1),2) == " 0") {Type_lines[lines] = 0;lines++;}
                else if (A.SubString((A.Length()-1),2) == " 1") {Type_lines[lines] = 1;lines++;}
                else if (A.SubString((A.Length()-1),2) == " 2") {Type_lines[lines] = 2;lines++;}
                else continue;
                LINES[lines][0] = LINES[lines-1][2];
                LINES[lines][1] = LINES[lines-1][3];
                W_LINES[lines] = W_LINES[lines-1];
               }
       else if (A.SubString(1,5) == "close" )
               {
                while (mem <= lines)
                      {
                       Poly_lines[mem] = true;
                       mem++;
                      }
                LINES[lines][2] = XX;
                LINES[lines][3] = YY;
                if (A.SubString((A.Length()-1),2) == " 0") {Type_lines[lines] = 0;lines++;}
                else if (A.SubString((A.Length()-1),2) == " 1") {Type_lines[lines] = 1;lines++;}
                else if (A.SubString((A.Length()-1),2) == " 2") {Type_lines[lines] = 2;lines++;}
                else continue;
               }
       else if (A.SubString(1,3) == "pin" )
               {
                if (First_pin == true) pins++;
                First_pin = true;
                Type_top[pins] = 9;
                Type_bot[pins] = 9;
                L_top[pins] = 0;
                L_bot[pins] = 0;
                prob = 2;
                Prob();
                B = "";
                while (A.SubString(prob,1) == " ") prob++;
                while (A.SubString(prob,1) != " ")
                      {
                       B = B + A.SubString(prob,1);
                       prob++;
                       if (prob > 250) continue;
                      }
                B = StringReplace(B,".",",",TReplaceFlags()<<rfReplaceAll);
                Hole_pins[pins] = StrToFloat(B);                 // Hole
                if (units == false) Hole_pins[pins] = Hole_pins[pins]*25400;
                B = "";
                while (A.SubString(prob,1) == " ") prob++;
                while (A.SubString(prob,1) != " ")
                      {
                       B = B + A.SubString(prob,1);
                       prob++;
                       if (prob > 250) continue;
                      }
                B = StringReplace(B,".",",",TReplaceFlags()<<rfReplaceAll);
                X_pins[pins] = StrToFloat(B);                 // X
                if (units == false) X_pins[pins] = X_pins[pins]*25400;
                B = "";
                while (A.SubString(prob,1) == " ") prob++;
                while (A.SubString(prob,1) != " ")
                      {
                       B = B + A.SubString(prob,1);
                       prob++;
                       if (prob > 250) continue;
                      }
                B = StringReplace(B,".",",",TReplaceFlags()<<rfReplaceAll);
                Y_pins[pins] = StrToFloat(B);                 // Y
                if (units == false) Y_pins[pins] = Y_pins[pins]*25400;
                B = "";
                while (A.SubString(prob,1) == " ") prob++;
                while (prob <= A.Length())
                      {
                       B = B + A.SubString(prob,1);
                       prob++;
                       if (prob > 250) continue;
                      }
                ANG_pins[pins] = StrToInt(B);                 // angle
                if (units == false) ANG_pins[pins] = ANG_pins[pins]*25400;
               }
       else if ((A.SubString(1,7) == "top_pad" )||(A.SubString(1,10) == "bottom_pad" ))
               {
                long Type;
                prob = 1;
                Prob();
                B = "";
                while (A.SubString(prob,1) == " ") prob++;
                while (A.SubString(prob,1) != " ")
                      {
                       B = B + A.SubString(prob,1);
                       prob++;
                       if (prob > 250) continue;
                      }
                B = StringReplace(B,".",",",TReplaceFlags()<<rfReplaceAll);
                D = StrToFloat(B);
                                                                     // Type_
                if (A.SubString(1,3) == "top" ) Type_top[pins] = D;
                else Type_bot[pins] = D;
                Type = D;
                if (Type == 0) continue;
                B = "";
                while (A.SubString(prob,1) == " ") prob++;
                while (A.SubString(prob,1) != " ")
                      {
                       B = B + A.SubString(prob,1);
                       prob++;
                       if (prob > 250) continue;
                      }
                B = StringReplace(B,".",",",TReplaceFlags()<<rfReplaceAll);
                D = StrToFloat(B);
                if (units == false) D = D*25400;                     // W_
                if (A.SubString(1,3) == "top" ) W_top[pins] = D;
                else W_bot[pins] = D;
                if (Type == 1) continue;
                if (Type == 2) continue;
                if (Type == 6) continue;
                B = "";
                while (A.SubString(prob,1) == " ") prob++;
                while (A.SubString(prob,1) != " ")
                      {
                       B = B + A.SubString(prob,1);
                       prob++;
                       if (prob > 250) continue;
                      }
                B = StringReplace(B,".",",",TReplaceFlags()<<rfReplaceAll);
                D = StrToFloat(B);
                if (units == false) D = D*25400;                     // L_
                if (A.SubString(1,3) == "top" ) L_top[pins] = D*2;
                else L_bot[pins] = D*2;
               // if (Type == 3) continue;
               // if (Type == 5) continue;
               }
       else if (A.SubString(1,8) == "sel_rect" )
               {
                prob = 1;
                Prob();
                B = "";
                while (A.SubString(prob,1) == " ") prob++;
                while (A.SubString(prob,1) != " ")
                      {
                       B = B + A.SubString(prob,1);
                       prob++;
                       if (prob > 250) continue;
                      }
                B = StringReplace(B,".",",",TReplaceFlags()<<rfReplaceAll);
                sel_rect_1[0] = StrToFloat(B);                 // sel_rect_1[0]
                if (units == false) sel_rect_1[0] = sel_rect_1[0]*25400;
                B = "";
                while (A.SubString(prob,1) == " ") prob++;
                while (A.SubString(prob,1) != " ")
                      {
                       B = B + A.SubString(prob,1);
                       prob++;
                       if (prob > 250) continue;
                      }
                B = StringReplace(B,".",",",TReplaceFlags()<<rfReplaceAll);
                sel_rect_1[1] = StrToFloat(B);                 // sel_rect_1[1]
                if (units == false) sel_rect_1[1] = sel_rect_1[1]*25400;
                B = "";
                while (A.SubString(prob,1) == " ") prob++;
                while (A.SubString(prob,1) != " ")
                      {
                       B = B + A.SubString(prob,1);
                       prob++;
                       if (prob > 250) continue;
                      }
                B = StringReplace(B,".",",",TReplaceFlags()<<rfReplaceAll);
                sel_rect_2[0] = StrToFloat(B);                 // sel_rect_2[0]
                if (units == false) sel_rect_2[0] = sel_rect_2[0]*25400;
                B = "";
                while (A.SubString(prob,1) == " ") prob++;
                while (prob <= A.Length())
                      {
                       B = B + A.SubString(prob,1);
                       prob++;
                       if (prob > 250) continue;
                      }
                B = StringReplace(B,".",",",TReplaceFlags()<<rfReplaceAll);
                sel_rect_2[1] = StrToFloat(B);                 // sel_rect_2[1]
                if (units == false) sel_rect_2[1] = sel_rect_2[1]*25400;
               }
       else if (A.SubString(1,5) == "units" )
               {
                if (A.SubString(1,A.Length()) == "units: NM" ) units = true;
                else units = false;
               }
      }//while (1)
pins++;
read_foot.close();
}
//---------------------------------------------------------------------------
//============== prob ==============
void Prob(void)
{
 long prob2 = prob;
 prob = 1;
 while (prob2 > 0)
       {
         while (A.SubString(prob,1) == " ")prob++;
         while (A.SubString(prob,1) != " "){prob++; if (prob > A.Length()) break;}
         if (prob > A.Length()) break;
         prob2--;
       }
 if (prob > A.Length()) prob = 0;
}

//---------------------------------------------------------------------------
void MIRROR_ROTATE (bool Lay, AnsiString Ang)
{
double X = D;
double Y = F;
Ang = StringReplace(Ang,".",",",TReplaceFlags()<<rfReplaceAll);
double AN = StrToFloat(Ang);
if(Lay == 1)  X = -X;
Rotate_Vertex (&X, &Y, -AN);
D = X;
F = Y;
}

//------------------------------------------------------------------------
float ex_float (long index)
{
AnsiString Q = "";
//current_units_mm = units_mm;
while ((A.SubString(index,1) < "0")||(A.SubString(index,1) > "9"))
      {
       if (A.SubString(index,1) == "-") Q = Q + A.SubString(index,1);
       if (A.SubString(index,1) == "+") Q = Q + A.SubString(index,1);
       index++;
      }
while ((A.SubString(index,1) >= "0")&&(A.SubString(index,1) <= "9"))
      {
       Q = Q + A.SubString(index,1);
       index++;
       if ((A.SubString(index,1) == ".")||(A.SubString(index,1) == ","))
          {
            Q = Q + ",";
            index++;
          }
      }
//if (A.UpperCase().SubString(index,2) == "MM" ) current_units_mm = true;
//if (A.UpperCase().SubString(index,3) == "MIL" ) current_units_mm = false;
//if (A.UpperCase().SubString(index,3) == " MM" ) current_units_mm = true;
//if (A.UpperCase().SubString(index,4) == " MIL" ) current_units_mm = false;
if (Q.SubString(Q.Length(),1) == ",") Q = Q + "0";
double DE = StrToFloat(Q);
i = index;
return DE;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Label11MouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
Form1->Height = 595;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CheckBox6MouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
Form1->Height = 412;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CheckBox11MouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
Form1->Height = 412;
}
//---------------------------------------------------------------------------




