//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "fstream.h"
#include "DXF_to_FPC_FreePCB.h"
#include "math.h"
#include "time.h"
#include "clipbrd.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"



TForm1 *Form1;
AnsiString A;
AnsiString B;
AnsiString * LAYER_L;  //слой линии
AnsiString * LAYER_T;  //слой текста
AnsiString * names_layers;
AnsiString * BOARD;
AnsiString * BLK_NAME;
AnsiString Lay_Arc;      // слой дуги
double * X1=0;
double * Y1;
double * Z1;
double * X2;
double * Y2;
double * Z2;
double * W_L;  //ширина линии
double * W_T;  //ширина текста
double * BasePtX;
double * BasePtY;


long a = 0;
long i = 0;
INT MILLION=1000000;
int n = 0;
int blk_adr = -1;
long ln = 0;
long nml = 0;
long brd = 0;
long n_brd = 0;
long n_line = 0;
long SizeOfMemory = 0;
bool Revers = false;
bool F_break = false;
bool FWarning1 = false;
bool F_BLK = false;


double X0;           // координата центра дуги
double Y0;           // координата центра дуги
double Ellipse_K;
double Ellipse_X;
double Ellipse_Y;
double Ellipse_A;
double R;            // радиус дуги
double Ang_1;        // начальный угол
double Ang_2;        // конечный угол
double Th;           // толщина дуги
double D = 1000;     // допуск зазора меж верш линий
double AbsXmin = DEFAULT;
double AbsYmin = DEFAULT;
double AbsXMAX = -DEFAULT;
double AbsYMAX = -DEFAULT;
double Point_1[2];
double Point_2[2];

char stringchar[500];
void Generate_Arc (void);
void WR (void);
void download_ANG (void);
//---------------------------------------------------------------------------











//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
 DecimalSeparator = ',';
 Form1->FormStyle = fsStayOnTop;
 Form1->Shapes->Sorted = false;
 Form1->Parts->Sorted = false;
 Form1->Shapes->Visible = false;
 Form1->Parts->Visible = false;
 Form1->Label1->Enabled = false;
 Form1->ComboBox1->MultiSelect = true;
 Form1->ComboBox2->Items->Add("1000");
 Form1->ComboBox2->Items->Add("2000");
 Form1->ComboBox2->Items->Add("5000");
 Form1->ComboBox2->Items->Add("10000");
 Form1->ComboBox2->Items->Add("20000");
 Form1->ComboBox2->Items->Add("50000");
 Form1->ComboBox2->Items->Add("100000");
 Form1->ComboBox2->Items->Add("200000");
 Form1->ComboBox2->Items->Add("500000");
 Form1->ComboBox2->Items->Add("1000000");
 Form1->ComboBox2->ItemIndex = 0;
 Form1->ComboBox2->Enabled = false;
 Form1->CheckBox6->Enabled = false;
AnsiString CLPBRD = Clipboard()->AsText;
Clipboard()->Clear();
while (A.UpperCase().SubString((A.Length()-3),4) != ".DXF")
if (CLPBRD.SubString(1,6) == "ObjMan")
        {
        i = 7;
        Form1->OpenDialog1->FileName = ex_str(CLPBRD, &i) ;
        A = Form1->OpenDialog1->FileName;
        CLPBRD = "";
        }
else if (Form1->OpenDialog1->Execute())
        {
        A = Form1->OpenDialog1->FileName;
        }
else exit(0);
 if (Form1->OpenDialog1->FileName.Length() == 0) return;
 Form1->Label3->Visible = false;
 Form1->Label4->Visible = false;
 Form1->Label5->Visible = false;
//чтение слоев
 A = Form1->OpenDialog1->FileName;
 ifstream Read_L (A.c_str());
long CT = 0;
bool FlagLay = false;
bool F = 0;
while (!Read_L.eof())
        {
        Read_L.getline(stringchar,sizeof(stringchar));
        A = stringchar;
        A = A.Trim();
        CT++;
        if (A.Length())
                {
                if(F)   {
                        A = StringReplace(A,".",",",TReplaceFlags()<<rfReplaceAll);
                        double gX = StrToFloat(A);
                        if( ABS(gX) > 600 )
                                {
                                Form1->MM->Checked = 0;
                                Form1->MIL->Checked = 1;
                                Form1->MM->Enabled = 0;
                                }
                        }
                //
                if (A.SubString(1,A.Length()) == "8")       //слой
                if (CT%2)
                        {
                        FlagLay = true;
                        }
                if (FlagLay)
                if (CT%2 == 0)
                        {
                        FlagLay = false;
                        if (Form1->ComboBox1->Items->IndexOf(A) < 0)
                        Form1->ComboBox1->Items->Add(A);
                        }
                if(Form1->MM->Enabled)
                if (A.SubString(1,A.Length()) == "11")       //X coordinate
                        {
                        F = 1;
                        continue;
                        }
                }
        F = 0;
        }
Read_L.close();
try     {
        names_layers = new(std::nothrow) AnsiString[Form1->ComboBox1->Items->Count+1];    //
        }
catch(std::bad_alloc)
        {
        ShowMessage("    Ошибка выделения памяти: AnsiString[" + AnsiString(Form1->ComboBox1->Items->Count) + "]!" );
        exit(0);
        }
Form1->ComboBox1->ItemIndex = 0;
Form1->ComboBox1->Enabled = false;
}
//---------------------------------------------------------------------------











//---------------------------------------------------------------------------
//расчет углов

void download_ANG (void)
{
double L1 = X2[ln] - X1[ln];
double L2 = Y2[ln] - Y1[ln];
double L1_L2 = sqrt(pow(L1,2) + pow(L2,2));
R = L1_L2/(double)2;
if (L1)
        {
        Ang_2 = (atan(L2/L1))*180.0/M_PI;
        if ((L1 > 0)&&(L2 < 0)) Ang_2 = 360.0 + Ang_2;
        if (L1 < 0)             Ang_2 = 180.0 + Ang_2;
        if (!L2)
                {
                if (L1 > 0) Ang_2 = 0;
                else Ang_2 = 180.0;
                }
        }
else
        {
        if (L2 > 0) Ang_2 = 90.0;
        else Ang_2 = 270.0;
        }
Ang_1 = Ang_2 - 180.0;

}
//---------------------------------------------------------------------------





double GetRad(void)
{
if( ABS(Ellipse_X) > BY_ZERO || ABS(Ellipse_Y) > BY_ZERO )
        {
        double ERad1 = sqrt( (Ellipse_Y)*(Ellipse_Y) + (Ellipse_X)*(Ellipse_X) );
        double ERad2 = ERad1*ABS(Ellipse_K);
        double e = sqrt(1-(ERad2*ERad2/ERad1/ERad1));
        double diffAn = ABS(Ang_1-Ellipse_A)*M_PI/180.0;
        R = ERad2/sqrt(1-e*e*cos(diffAn)*cos(diffAn));
        }
return R;
}



//---------------------------------------------------------------------------
//генерация дуги
void Generate_Arc (void)
{
double gR = GetRad();
X1[ln] = X0 + gR*cos(Ang_1*M_PI/180.0);
Y1[ln] = Y0 + gR*sin(Ang_1*M_PI/180.0);
if (Ang_2 < Ang_1)
        {
        Ang_2 = Ang_2 + 360.0;
        }
while (1)
        {
         if (gR > 5000000)       Ang_1 = Ang_1 + 3.0;
         else if (gR > MILLION)  Ang_1 = Ang_1 + 10.0;
         else if (gR > 400000)   Ang_1 = Ang_1 + 15.0;
         else if (gR > 100000)   Ang_1 = Ang_1 + 30.0;
         else break;
         if (Ang_1 >= Ang_2) break;
         gR = GetRad();
         X2[ln] = X0 + gR*cos(Ang_1*M_PI/180.0);
         Y2[ln] = Y0 + gR*sin(Ang_1*M_PI/180.0);
         if (blk_adr < 0)
                {
                if (AbsXMAX < X2[ln]) AbsXMAX = X2[ln];
                if (AbsYMAX < Y2[ln]) AbsYMAX = Y2[ln];
                if (AbsXmin > X2[ln]) AbsXmin = X2[ln];
                if (AbsYmin > Y2[ln]) AbsYmin = Y2[ln];
                }
         LAYER_L[ln] = Lay_Arc;
         W_L[ln] = Th;
         ln++;

         X1[ln] = X0 + gR*cos(Ang_1*M_PI/180.0);
         Y1[ln] = Y0 + gR*sin(Ang_1*M_PI/180.0);
        }
Ang_1 = Ang_2;
gR = GetRad();
X2[ln] = X0 + gR*cos(Ang_2*M_PI/180.0);
Y2[ln] = Y0 + gR*sin(Ang_2*M_PI/180.0);
LAYER_L[ln] = Lay_Arc;
W_L[ln] = Th;
ln++;
R = gR;
}
//---------------------------------------------------------------------------











//---------------------------------------------------------------------------
//===================!!!!!!!!WRITING!!!!!!!!!===================
//===================************************===================
void WR (void)
{
a = 0;
i = 0;
n = 0;
blk_adr = -1;
ln = 0;
nml = 0;
brd = 0;
n_brd = 0;
n_line = 0;
SizeOfMemory = 0;
static PrevSizeOfMemory = 0;
Revers = false;
F_break = false;
FWarning1 = false;
F_BLK = false;
//
Ellipse_X = 0;
Ellipse_Y = 0;
Ellipse_K = 0;
Ellipse_A = 0;
//
Form1->Label3->Visible = true;
Form1->Label4->Visible = true;
Form1->Label5->Visible = true;
A = Form1->Edit1->Text;
A = Str_Float_Format(A);
SizeOfMemory = (int)StrToFloat(A);
SizeOfMemory = MAX( SizeOfMemory, 999 );
//=============================
//ДИНАМИЧЕСКОЕ ВЫДЕЛЕНИЕ ПАМЯТИ
//=============================
//if(!X1) {
        try     {
                X1 = new(std::nothrow) double[SizeOfMemory];    //
                }
        catch(std::bad_alloc)
                {
                ShowMessage("    Ошибка выделения памяти: double[" + AnsiString(SizeOfMemory) + "]!" );
                exit(0);
                }
        try     {
                X2 = new(std::nothrow) double[SizeOfMemory];    //
                }
        catch(std::bad_alloc)
                {
                ShowMessage("    Ошибка выделения памяти: double[" + AnsiString(SizeOfMemory) + "]!" );
                exit(0);
                }
        try     {
                Y1 = new(std::nothrow) double[SizeOfMemory];    //
                }
        catch(std::bad_alloc)
                {
                ShowMessage("    Ошибка выделения памяти: double[" + AnsiString(SizeOfMemory) + "]!" );
                exit(0);
                }
        try     {
                Y2 = new(std::nothrow) double[SizeOfMemory];    //
                }
        catch(std::bad_alloc)
                {
                ShowMessage("    Ошибка выделения памяти: double[" + AnsiString(SizeOfMemory) + "]!" );
                exit(0);
                }
        try     {
                Z1 = new(std::nothrow) double[SizeOfMemory];    //
                }
        catch(std::bad_alloc)
                {
                ShowMessage("    Ошибка выделения памяти: double[" + AnsiString(SizeOfMemory) + "]!" );
                exit(0);
                }
        try     {
                Z2 = new(std::nothrow) double[SizeOfMemory];    //
                }
        catch(std::bad_alloc)
                {
                ShowMessage("    Ошибка выделения памяти: double[" + AnsiString(SizeOfMemory) + "]!" );
                exit(0);
                }
        try     {
                W_L = new(std::nothrow) double[SizeOfMemory];    //
                }
        catch(std::bad_alloc)
                {
                ShowMessage("    Ошибка выделения памяти: double[" + AnsiString(SizeOfMemory) + "]!" );
                exit(0);
                }
        try     {
                W_T = new(std::nothrow) double[SizeOfMemory];    //
                }
        catch(std::bad_alloc)
                {
                ShowMessage("    Ошибка выделения памяти: double[" + AnsiString(SizeOfMemory) + "]!" );
                exit(0);
                }
        try     {
                LAYER_L = new(std::nothrow) AnsiString[SizeOfMemory];    //
                }
        catch(std::bad_alloc)
                {
                ShowMessage("    Ошибка выделения памяти: AnsiString[" + AnsiString(SizeOfMemory) + "]!" );
                exit(0);
                }
        try     {
                LAYER_T = new(std::nothrow) AnsiString[SizeOfMemory];    //
                }
        catch(std::bad_alloc)
                {
                ShowMessage("    Ошибка выделения памяти: AnsiString[" + AnsiString(SizeOfMemory) + "]!" );
                exit(0);
                }
        try     {
                BOARD = new(std::nothrow) AnsiString[SizeOfMemory];    //
                }
        catch(std::bad_alloc)
                {
                ShowMessage("    Ошибка выделения памяти: AnsiString[" + AnsiString(SizeOfMemory) + "]!" );
                exit(0);
                }
        try     {
                BasePtX = new(std::nothrow) double[SizeOfMemory];    //
                }
        catch(std::bad_alloc)
                {
                ShowMessage("    Ошибка выделения памяти: double[" + AnsiString(SizeOfMemory) + "]!" );
                exit(0);
                }
        try     {
                BasePtY = new(std::nothrow) double[SizeOfMemory];    //
                }
        catch(std::bad_alloc)
                {
                ShowMessage("    Ошибка выделения памяти: double[" + AnsiString(SizeOfMemory) + "]!" );
                exit(0);
                }
        try     {
                BLK_NAME = new(std::nothrow) AnsiString[SizeOfMemory];    //
                }
        catch(std::bad_alloc)
                {
                ShowMessage("    Ошибка выделения памяти: AnsiString[" + AnsiString(SizeOfMemory) + "]!" );
                exit(0);
                }
//        }
for (int z=0; z<SizeOfMemory; z++)
        {
        X1[z] = 0;
        X2[z] = 0;
        Y1[z] = 0;
        Y2[z] = 0;
        Z1[z] = 0;
        Z2[z] = 0;
        }
//============================
 A = Form1->OpenDialog1->FileName;
 ifstream Read (A.c_str());
 ln = 0;
 bool Trigger;
 int lines = 0;
while (!Read.eof())
        {
        Read.getline(stringchar,sizeof(stringchar));
        lines++;
        A = stringchar;
        A = A.Trim();
        if (lines%2)    Trigger = 1;     //command
        else            Trigger = 0;     //value
        if (A.Length() == 0) continue;
        else
                {
                if (ln > (SizeOfMemory-1000))
                        {
                        FWarning1 = true;
                        ln = SizeOfMemory-1000;
                        if (ln < 0)
                                {
                                ShowMessage("   Error size of Memory!");
                                ///exit(0);
                                }
                        break;
                        }
                //******************************** БЛОКИ ***************************************
                if (A.UpperCase().SubString(1,A.Length()) == "BLOCK" && Trigger == 0)  //если блок
                        {
                        if (BLK_NAME[ln].Length() && BLK_NAME[ln].UpperCase().SubString(1,BLK_NAME[ln].Length()) != "ENDBLK")      BLK_NAME[ln] = "";
                        else if (ln>0)   BLK_NAME[ln-1] = "ENDBLK";
                        blk_adr = ln;
                        }
                else if (A.SubString(1,A.Length()) == "2" && blk_adr >= 0 && Trigger)       //X1 линии
                        {
                        Read.getline(stringchar,sizeof(stringchar));
                        lines++;
                        A = stringchar;
                        A = A.Trim();
                        BLK_NAME[blk_adr] = A;
                        }
                else if (A.SubString(1,A.Length()) == "10" && blk_adr >= 0 && Trigger)       //X1 линии
                        {
                        Read.getline(stringchar,sizeof(stringchar));
                        lines++;
                        A = stringchar;
                        A = A.Trim();
                        A = StringReplace(A,".",",",TReplaceFlags()<<rfReplaceAll);
                        BasePtX[blk_adr] = StrToFloat(A);
                        BasePtX[blk_adr] = BasePtX[blk_adr]*MILLION;
                        }
                else if (A.SubString(1,A.Length()) == "20" && blk_adr >= 0 && Trigger)       //X1 линии
                        {
                        Read.getline(stringchar,sizeof(stringchar));
                        lines++;
                        A = stringchar;
                        A = A.Trim();
                        A = StringReplace(A,".",",",TReplaceFlags()<<rfReplaceAll);
                        BasePtY[blk_adr] = StrToFloat(A);
                        BasePtY[blk_adr] = BasePtY[blk_adr]*MILLION;
                        }
                //******************************** КОНЕЦ БЛОКА *********************************
                else if (A.UpperCase().SubString(1,6) == "ENDBLK" && Trigger == 0)
                        {
                        if (BLK_NAME[ln].Length() && BLK_NAME[ln].UpperCase().SubString(1,BLK_NAME[ln].Length()) != "ENDBLK")      BLK_NAME[ln] = "";
                        else if (ln>0)   BLK_NAME[ln-1] = "ENDBLK";
                        blk_adr = -1;
                        }
                else if (A.UpperCase().SubString(1,6) == "ENDSEC" && Trigger == 0)
                        {
                        if (BLK_NAME[ln].Length() && BLK_NAME[ln].UpperCase().SubString(1,BLK_NAME[ln].Length()) != "ENDBLK")      BLK_NAME[ln] = "";
                        else if (ln>0)   BLK_NAME[ln-1] = "ENDBLK";
                        blk_adr = -1;
                        }
                else if (A.UpperCase().SubString(1,A.Length()) == "ENTITIES" && Trigger == 0)
                        {
                        if (BLK_NAME[ln].Length() && BLK_NAME[ln].UpperCase().SubString(1,BLK_NAME[ln].Length()) != "ENDBLK")      BLK_NAME[ln] = "";
                        else if (ln>0)   BLK_NAME[ln-1] = "ENDBLK";
                        blk_adr = -1;
                        }
                //******************************** ВСТАВКА БЛОКА *********************************
                else if (A.UpperCase().SubString(1,A.Length()) == "INSERT" && Trigger == 0)
                        {
                        AnsiString LAY = "";
                        AnsiString InsertName = "";
                        AnsiString CurrentBlkName = "";
                        double InsertX = 0;
                        double InsertY = 0;
                        double ScaleX = 1;
                        double ScaleY = 1;
                        double Rotation = 0;
                        int Col = 1;
                        int Row = 1;
                        double Col_Sp = 0;
                        double Row_Sp = 0;
                        while (1)     //пока не конец
                                {
                                Read.getline(stringchar,sizeof(stringchar));
                                lines++;
                                A = stringchar;
                                A = A.Trim();
                                if      (A.SubString(1,A.Length()) == "0") break;
                                else if (A.SubString(1,A.Length()) == "2")      //name
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        A = stringchar;
                                        A = A.Trim();
                                        InsertName = A;
                                        }
                                else if (A.SubString(1,A.Length()) == "8")      //LAY
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        A = stringchar;
                                        A = A.Trim();
                                        LAY = A;
                                        }
                                else if (A.SubString(1,A.Length()) == "10")      //X
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        A = stringchar;
                                        A = A.Trim();
                                        A = StringReplace(A,".",",",TReplaceFlags()<<rfReplaceAll);
                                        InsertX = StrToFloat(A);
                                        InsertX = InsertX*MILLION;
                                        }
                                else if (A.SubString(1,A.Length()) == "20")      //Y
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        A = stringchar;
                                        A = A.Trim();
                                        A = StringReplace(A,".",",",TReplaceFlags()<<rfReplaceAll);
                                        InsertY = StrToFloat(A);
                                        InsertY = InsertY*MILLION;
                                        }
                                else if (A.SubString(1,A.Length()) == "41")      //
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        A = stringchar;
                                        A = A.Trim();
                                        A = StringReplace(A,".",",",TReplaceFlags()<<rfReplaceAll);
                                        ScaleX = StrToFloat(A);
                                        }
                                else if (A.SubString(1,A.Length()) == "42")      //
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        A = stringchar;
                                        A = A.Trim();
                                        A = StringReplace(A,".",",",TReplaceFlags()<<rfReplaceAll);
                                        ScaleY = StrToFloat(A);
                                        }
                                else if (A.SubString(1,A.Length()) == "50")      //
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        A = stringchar;
                                        A = A.Trim();
                                        A = StringReplace(A,".",",",TReplaceFlags()<<rfReplaceAll);
                                        Rotation = StrToFloat(A);
                                        }
                                else if (A.SubString(1,A.Length()) == "70")      //
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        A = stringchar;
                                        A = A.Trim();
                                        A = StringReplace(A,".",",",TReplaceFlags()<<rfReplaceAll);
                                        Col = StrToInt(A);
                                        }
                                else if (A.SubString(1,A.Length()) == "71")      //
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        A = stringchar;
                                        A = A.Trim();
                                        A = StringReplace(A,".",",",TReplaceFlags()<<rfReplaceAll);
                                        Row = StrToInt(A);
                                        }
                                else if (A.SubString(1,A.Length()) == "44")      //
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        A = stringchar;
                                        A = A.Trim();
                                        A = StringReplace(A,".",",",TReplaceFlags()<<rfReplaceAll);
                                        Col_Sp = StrToFloat(A);
                                        }
                                else if (A.SubString(1,A.Length()) == "45")      //
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        A = stringchar;
                                        A = A.Trim();
                                        A = StringReplace(A,".",",",TReplaceFlags()<<rfReplaceAll);
                                        Row_Sp = StrToFloat(A);
                                        }
                                else    //пропускаем строку
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        }
                                }
                        int En = -1;
                        int Start = ln;
                        double shiftX;
                        double shiftY;
                        if (InsertName.Length())
                        for(int k=0; k<Start; k++)
                                {
                                if (BLK_NAME[k].Length())
                                if (BLK_NAME[k].SubString(1,BLK_NAME[k].Length()) == InsertName.SubString(1,InsertName.Length())) En = k;
                                shiftX = 0;
                                shiftY = 0;
                                if (En >= 0)
                                for (int sc_x=0; sc_x<Col; sc_x++)
                                        {
                                        for (int sc_y=0; sc_y<Row; sc_y++)
                                                {
                                                double Xmod1 = X1[k]*ScaleX + shiftX - BasePtX[En];
                                                double Ymod1 = Y1[k]*ScaleY + shiftY - BasePtY[En];
                                                if (Rotation) Rotate_Vertex ( &Xmod1, &Ymod1, Rotation);
                                                double Xmod2 = X2[k]*ScaleX + shiftX - BasePtX[En];
                                                double Ymod2 = Y2[k]*ScaleY + shiftY - BasePtY[En];
                                                if (Rotation) Rotate_Vertex ( &Xmod2, &Ymod2, Rotation);
                                                LAYER_L[ln] = LAY;
                                                W_L[ln] = W_L[k];
                                                X1[ln] = InsertX + Xmod1;
                                                Y1[ln] = InsertY + Ymod1;
                                                X2[ln] = InsertX + Xmod2;
                                                Y2[ln] = InsertY + Ymod2;
                                                if (AbsXMAX < X1[ln]) AbsXMAX = X1[ln];
                                                if (AbsXMAX < X2[ln]) AbsXMAX = X2[ln];
                                                if (AbsYMAX < Y1[ln]) AbsYMAX = Y1[ln];
                                                if (AbsYMAX < Y2[ln]) AbsYMAX = Y2[ln];
                                                if (AbsXmin > X1[ln]) AbsXmin = X1[ln];
                                                if (AbsXmin > X2[ln]) AbsXmin = X2[ln];
                                                if (AbsYmin > Y1[ln]) AbsYmin = Y1[ln];
                                                if (AbsYmin > Y2[ln]) AbsYmin = Y2[ln];
                                                ln++;
                                                shiftY = shiftY + Row_Sp*MILLION;
                                                }
                                        shiftY = 0;
                                        shiftX = shiftX + Col_Sp*MILLION;
                                        }
                                if (BLK_NAME[k].SubString(1,BLK_NAME[k].Length()) == "ENDBLK" ) En = -1;
                                }
                        }
                //******************************** ЛИНИИ ***************************************
                else if (A.UpperCase().SubString(1,A.Length()) == "LINE" && Trigger == 0)  //если линия
                        {
                        LAYER_L[ln] = "Unnamed";
                        W_L[ln] = 0;
                        while (1)     //пока не конец линии читаем параметры
                                {
                                Read.getline(stringchar,sizeof(stringchar));
                                lines++;
                                A = stringchar;
                                A = A.Trim();
                                if (A.Length() == 0) continue ;
                                else if (A.SubString(1,A.Length()) == "0") break;
                                else if (A.SubString(1,A.Length()) == "8")       //слой линии
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        A = stringchar;
                                        A = A.Trim();
                                        LAYER_L[ln] = A;
                                        }
                                else if (A.SubString(1,A.Length()) == "10")       //X1 линии
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        A = stringchar;
                                        A = A.Trim();
                                        A = StringReplace(A,".",",",TReplaceFlags()<<rfReplaceAll);
                                        X1[ln] = StrToFloat(A);
                                        X1[ln] = X1[ln]*MILLION;
                                        if (blk_adr < 0)
                                                {
                                                if (AbsXmin > X1[ln]) AbsXmin = X1[ln];
                                                if (AbsXMAX < X1[ln]) AbsXMAX = X1[ln];
                                                }
                                        }
                                else if (A.SubString(1,A.Length()) == "20")       //Y1 линии
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        A = stringchar;
                                        A = A.Trim();
                                        A = StringReplace(A,".",",",TReplaceFlags()<<rfReplaceAll);
                                        Y1[ln] = StrToFloat(A);
                                        Y1[ln] = Y1[ln]*MILLION;
                                        if (blk_adr < 0)
                                                {
                                                if (AbsYmin > Y1[ln]) AbsYmin = Y1[ln];
                                                if (AbsYMAX < Y1[ln]) AbsYMAX = Y1[ln];
                                                }
                                        }
                                else if (A.SubString(1,A.Length()) == "30")       //Z1 линии
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        A = stringchar;
                                        A = A.Trim();
                                        A = StringReplace(A,".",",",TReplaceFlags()<<rfReplaceAll);
                                        Z1[ln] = StrToFloat(A);
                                        Z1[ln] = Z1[ln]*MILLION;
                                        }
                                else if (A.SubString(1,A.Length()) == "11")       //X2 линии
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        A = stringchar;
                                        A = A.Trim();
                                        A = StringReplace(A,".",",",TReplaceFlags()<<rfReplaceAll);
                                        X2[ln] = StrToFloat(A);
                                        X2[ln] = X2[ln]*MILLION;
                                        if (blk_adr < 0)
                                                {
                                                if (AbsXmin > X2[ln]) AbsXmin = X2[ln];
                                                if (AbsXMAX < X2[ln]) AbsXMAX = X2[ln];
                                                }
                                        }
                                else if (A.SubString(1,A.Length()) == "21")       //Y2 линии
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        A = stringchar;
                                        A = A.Trim();
                                        A = StringReplace(A,".",",",TReplaceFlags()<<rfReplaceAll);
                                        Y2[ln] = StrToFloat(A);
                                        Y2[ln] = Y2[ln]*MILLION;
                                        if (blk_adr < 0)
                                                {
                                                if (AbsYmin > Y2[ln]) AbsYmin = Y2[ln];
                                                if (AbsYMAX < Y2[ln]) AbsYMAX = Y2[ln];
                                                }
                                        }
                                else if (A.SubString(1,A.Length()) == "31")       //Z1 линии
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        A = stringchar;
                                        A = A.Trim();
                                        A = StringReplace(A,".",",",TReplaceFlags()<<rfReplaceAll);
                                        Z2[ln] = StrToFloat(A);
                                        Z2[ln] = Z2[ln]*MILLION;
                                        }
                                else    //пропускаем строку
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        }
                                }
                        ln++;
                        }//if (A.UpperCase().SubString(1,4) == "LINE" )  //если линия

                //==============================================================================
                //******************************** SOLID ***************************************
                else if ((A.UpperCase().SubString(1,A.Length()) == "SOLID" || A.UpperCase().SubString(1,A.Length()) == "3DFACE") && Trigger == 0)  //если SOLID
                        {
                        LAYER_L[ln] = "Unnamed";
                        W_L[ln] = 0;
                        bool Flag = false;
                        while (1)     //пока не конец SOLID читаем параметры
                                {
                                Read.getline(stringchar,sizeof(stringchar));
                                lines++;
                                A = stringchar;
                                A = A.Trim();
                                if (A.Length() == 0) continue ;
                                else if (A.SubString(1,A.Length()) == "0") break;
                                else if (A.SubString(1,A.Length()) == "8")       //слой линии
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        A = stringchar;
                                        A = A.Trim();
                                        LAYER_L[ln] = A;
                                        LAYER_L[ln+1] = A;
                                        LAYER_L[ln+2] = A;
                                        LAYER_L[ln+3] = A;
                                        W_L[ln] = 0;
                                        W_L[ln+1] = 0;
                                        W_L[ln+2] = 0;
                                        W_L[ln+3] = 0;
                                        }
                                else if (A.SubString(1,A.Length()) == "10")       //X1 линии
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        A = stringchar;
                                        A = A.Trim();
                                        A = StringReplace(A,".",",",TReplaceFlags()<<rfReplaceAll);
                                        X1[ln] = StrToFloat(A)*MILLION;
                                        }
                                else if (A.SubString(1,A.Length()) == "20")       //Y1 линии
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        A = stringchar;
                                        A = A.Trim();
                                        A = StringReplace(A,".",",",TReplaceFlags()<<rfReplaceAll);
                                        Y1[ln] = StrToFloat(A)*MILLION;
                                        }
                                else if (A.SubString(1,A.Length()) == "30")       //Z1 линии
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        A = stringchar;
                                        A = A.Trim();
                                        A = StringReplace(A,".",",",TReplaceFlags()<<rfReplaceAll);
                                        Z1[ln] = StrToFloat(A)*MILLION;
                                        }
                                else if (A.SubString(1,A.Length()) == "11")       //X2 линии
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        A = stringchar;
                                        A = A.Trim();
                                        A = StringReplace(A,".",",",TReplaceFlags()<<rfReplaceAll);
                                        X2[ln] = StrToFloat(A)*MILLION;
                                        }
                                else if (A.SubString(1,A.Length()) == "21")       //Y2 линии
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        A = stringchar;
                                        A = A.Trim();
                                        A = StringReplace(A,".",",",TReplaceFlags()<<rfReplaceAll);
                                        Y2[ln] = StrToFloat(A)*MILLION;
                                        }
                                else if (A.SubString(1,A.Length()) == "31")       //Z1 линии
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        A = stringchar;
                                        A = A.Trim();
                                        A = StringReplace(A,".",",",TReplaceFlags()<<rfReplaceAll);
                                        Z2[ln] = StrToFloat(A)*MILLION;
                                        }
                                else if (A.SubString(1,A.Length()) == "12")       //X3 линии
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        A = stringchar;
                                        A = A.Trim();
                                        A = StringReplace(A,".",",",TReplaceFlags()<<rfReplaceAll);
                                        X1[ln+1] = StrToFloat(A)*MILLION;
                                        }
                                else if (A.SubString(1,A.Length()) == "22")       //Y3 линии
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        A = stringchar;
                                        A = A.Trim();
                                        A = StringReplace(A,".",",",TReplaceFlags()<<rfReplaceAll);
                                        Y1[ln+1] = StrToFloat(A)*MILLION;
                                        }
                                else if (A.SubString(1,A.Length()) == "32")       //Z1 линии
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        A = stringchar;
                                        A = A.Trim();
                                        A = StringReplace(A,".",",",TReplaceFlags()<<rfReplaceAll);
                                        Z1[ln+1] = StrToFloat(A)*MILLION;
                                        }
                                else if (A.SubString(1,A.Length()) == "13")       //X4 линии
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        A = stringchar;
                                        A = A.Trim();
                                        A = StringReplace(A,".",",",TReplaceFlags()<<rfReplaceAll);
                                        X2[ln+1] = StrToFloat(A)*MILLION;
                                        }
                                else if (A.SubString(1,A.Length()) == "23")       //Y4 линии
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        A = stringchar;
                                        A = A.Trim();
                                        A = StringReplace(A,".",",",TReplaceFlags()<<rfReplaceAll);
                                        Y2[ln+1] = StrToFloat(A)*MILLION;
                                        Flag = true;
                                        }
                                else if (A.SubString(1,A.Length()) == "33")       //Z1 линии
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        A = stringchar;
                                        A = A.Trim();
                                        A = StringReplace(A,".",",",TReplaceFlags()<<rfReplaceAll);
                                        Z2[ln+1] = StrToFloat(A)*MILLION;
                                        }
                                else    //пропускаем строку
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        }
                                }//while (1)
                        if (Flag )
                                {
                                X1[ln+2] = X1[ln];
                                Y1[ln+2] = Y1[ln];
                                Z1[ln+2] = Z1[ln];
                                X2[ln+2] = X2[ln+1];
                                Y2[ln+2] = Y2[ln+1];
                                Z2[ln+2] = Z2[ln+1];
                                X1[ln+3] = X2[ln];
                                Y1[ln+3] = Y2[ln];
                                Z1[ln+3] = Z2[ln];
                                X2[ln+3] = X1[ln+1];
                                Y2[ln+3] = Y1[ln+1];
                                Z2[ln+3] = Z1[ln+1];
                                if (blk_adr < 0)
                                        {
                                        if (AbsXmin > X1[ln])   AbsXmin = X1[ln];
                                        if (AbsYmin > Y1[ln])   AbsYmin = Y1[ln];
                                        if (AbsXmin > X2[ln])   AbsXmin = X2[ln];
                                        if (AbsYmin > Y2[ln])   AbsYmin = Y2[ln];
                                        if (AbsXmin > X1[ln+1]) AbsXmin = X1[ln+1];
                                        if (AbsYmin > Y1[ln+1]) AbsYmin = Y1[ln+1];
                                        if (AbsXmin > X2[ln+1]) AbsXmin = X2[ln+1];
                                        if (AbsYmin > Y2[ln+1]) AbsYmin = Y2[ln+1];
                                        if (AbsXmin > X1[ln+2]) AbsXmin = X1[ln+2];
                                        if (AbsYmin > Y1[ln+2]) AbsYmin = Y1[ln+2];
                                        if (AbsXmin > X2[ln+2]) AbsXmin = X2[ln+2];
                                        if (AbsYmin > Y2[ln+2]) AbsYmin = Y2[ln+2];
                                        if (AbsXmin > X1[ln+3]) AbsXmin = X1[ln+3];
                                        if (AbsYmin > Y1[ln+3]) AbsYmin = Y1[ln+3];
                                        if (AbsXmin > X2[ln+3]) AbsXmin = X2[ln+3];
                                        if (AbsYmin > Y2[ln+3]) AbsYmin = Y2[ln+3];
                                        //
                                        if (AbsXMAX < X1[ln])   AbsXMAX = X1[ln];
                                        if (AbsYMAX < Y1[ln])   AbsYMAX = Y1[ln];
                                        if (AbsXMAX < X2[ln])   AbsXMAX = X2[ln];
                                        if (AbsYMAX < Y2[ln])   AbsYMAX = Y2[ln];
                                        if (AbsXMAX < X1[ln+1]) AbsXMAX = X1[ln+1];
                                        if (AbsYMAX < Y1[ln+1]) AbsYMAX = Y1[ln+1];
                                        if (AbsXMAX < X2[ln+1]) AbsXMAX = X2[ln+1];
                                        if (AbsYMAX < Y2[ln+1]) AbsYMAX = Y2[ln+1];
                                        if (AbsXMAX < X1[ln+2]) AbsXMAX = X1[ln+2];
                                        if (AbsYMAX < Y1[ln+2]) AbsYMAX = Y1[ln+2];
                                        if (AbsXMAX < X2[ln+2]) AbsXMAX = X2[ln+2];
                                        if (AbsYMAX < Y2[ln+2]) AbsYMAX = Y2[ln+2];
                                        if (AbsXMAX < X1[ln+3]) AbsXMAX = X1[ln+3];
                                        if (AbsYMAX < Y1[ln+3]) AbsYMAX = Y1[ln+3];
                                        if (AbsXMAX < X2[ln+3]) AbsXMAX = X2[ln+3];
                                        if (AbsYMAX < Y2[ln+3]) AbsYMAX = Y2[ln+3];
                                        }
                                ln += 4;
                                }
                        }////SOLID
                //******************************** POLYLINE ***************************************
                else if (A.UpperCase().SubString(1,8) == "POLYLINE" && Trigger == 0)  //если poly-линия
                        {
                        bool CLOSED_L = false;
                        double FIRST__X = 0;
                        double FIRST__Y = 0;
                        LAYER_L[ln] = "Unnamed";
                        W_L[ln] = 0;
                        //bool VTX = false;    //флаг первой вершины
                        bool VTX2 = false;     //флаг второй вершины
                        while (1)     //пока не конец линии читаем параметры
                                {
                                Read.getline(stringchar,sizeof(stringchar));
                                lines++;
                                A = stringchar;
                                A = A.Trim();
                                if (A.Length() == 0) continue ;
                                else if (A.SubString(1,A.Length()) == "0") break;
                                else if (A.SubString(1,A.Length()) == "8")       //слой линии
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        A = stringchar;
                                        A = A.Trim();
                                        Lay_Arc = A;
                                        }
                                else if (A.SubString(1,A.Length()) == "40")       //толщина линии
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        A = stringchar;
                                        A = A.Trim();
                                        A = StringReplace(A,".",",",TReplaceFlags()<<rfReplaceAll);
                                        Th = StrToFloat(A);
                                        Th = Th*MILLION;
                                        }
                                else if (A.SubString(1,A.Length()) == "70")       //Замкнутость линии
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        A = stringchar;
                                        A = A.Trim();
                                        if (A.SubString(1,1) == "1") CLOSED_L = true;
                                        }
                                else    //пропускаем строку
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        }
                                }//while (1)
                        Read.getline(stringchar,sizeof(stringchar));
                        lines++;
                        A = stringchar;
                        A = A.Trim();
                        if (A.UpperCase().SubString(1,6) == "SEQEND") break;
                        if (A.UpperCase().SubString(1,6) == "ENDSEC") break;
                        double type_Line = 0;
                        double Flag_ARC = 0;
                        while (1)     //ищем VERTEX
                                {
                                Read.getline(stringchar,sizeof(stringchar));
                                lines++;
                                A = stringchar;
                                A = A.Trim();
                                if (A.Length() == 0) continue ;
                                else if (A.SubString(1,A.Length()) == "0")
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        A = stringchar;
                                        A = A.Trim();
                                        if (A.UpperCase().SubString(1,6) == "VERTEX")
                                                {
                                                if (VTX2)
                                                        {
                                                        X2[ln] = X0;
                                                        Y2[ln] = Y0;
                                                        LAYER_L[ln] = Lay_Arc;
                                                        W_L[ln] = Th;
                                                        if (Flag_ARC == true)
                                                                {
                                                                double x0 = X0; //save
                                                                double y0 = Y0; //save
                                                                X0 = (X1[ln] + X2[ln])/2;
                                                                Y0 = (Y1[ln] + Y2[ln])/2;
                                                                download_ANG();
                                                                Generate_Arc();
                                                                //reload X0 Y0
                                                                X0 = x0;
                                                                Y0 = y0;
                                                                X1[ln] = X0;
                                                                Y1[ln] = Y0;
                                                                }
                                                        else    {
                                                                ln++;
                                                                X1[ln] = X0;
                                                                Y1[ln] = Y0;
                                                                }
                                                        if (ABS(type_Line) == 1.0)      Flag_ARC = true;
                                                        else                            Flag_ARC = false;
                                                        }//if (VTX2 == true)
                                                else
                                                        {
                                                        X1[ln] = X0;
                                                        Y1[ln] = Y0;
                                                        FIRST__X = X1[ln];
                                                        FIRST__Y = Y1[ln];
                                                        if (ABS(type_Line) == 1.0)      Flag_ARC = true;
                                                        else                            Flag_ARC = false;
                                                        }
                                                VTX2 = true;
                                                type_Line = 0;
                                                continue;
                                                }
                                        else break;
                                        }
                                else if (A.SubString(1,A.Length()) == "8")       //слой линии
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        A = stringchar;
                                        A = A.Trim();
                                        Lay_Arc = A;
                                        }
                                else if (A.SubString(1,A.Length()) == "10")       //X линии
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        A = stringchar;
                                        A = A.Trim();
                                        A = StringReplace(A,".",",",TReplaceFlags()<<rfReplaceAll);
                                        X0 = StrToFloat(A);
                                        X0 = X0*MILLION;
                                        if (blk_adr < 0)
                                                {
                                                if (AbsXmin > X0) AbsXmin = X0;
                                                if (AbsXMAX < X0) AbsXMAX = X0;
                                                }
                                        }
                                else if (A.SubString(1,A.Length()) == "20")       //Y линии
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        A = stringchar;
                                        A = A.Trim();
                                        A = StringReplace(A,".",",",TReplaceFlags()<<rfReplaceAll);
                                        Y0 = StrToFloat(A);
                                        Y0 = Y0*MILLION;
                                        if (blk_adr < 0)
                                                {
                                                if (AbsYmin > Y0) AbsYmin = Y0;
                                                if (AbsYMAX < Y0) AbsYMAX = Y0;
                                                }
                                        }
                                else if (A.SubString(1,A.Length()) == "42")       //тип линии  (дуга == 1)
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        A = stringchar;
                                        A = A.Trim();
                                        A = StringReplace(A,".",",",TReplaceFlags()<<rfReplaceAll);
                                        type_Line = StrToFloat(A);
                                        }
                                else    //пропускаем строку
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        }
                                }//while (1)
                        double SV1 ;
                        double SV2;
                        if (VTX2)
                                {
                                X2[ln] = X0;
                                Y2[ln] = Y0;
                                SV1 = X2[ln];
                                SV2 = Y2[ln];
                                LAYER_L[ln] = Lay_Arc;
                                W_L[ln] = Th;
                                if (Flag_ARC == true)
                                        {
                                        X0 = (X1[ln] + X2[ln])/2;
                                        Y0 = (Y1[ln] + Y2[ln])/2;
                                        download_ANG();
                                        Generate_Arc();
                                        }
                                else ln++;
                                if (ABS(type_Line) == 1.0)      Flag_ARC = true;
                                else                            Flag_ARC = false;
                                }
                        if (CLOSED_L)
                                {
                                X1[ln] = SV1;
                                Y1[ln] = SV2;
                                X2[ln] = FIRST__X;
                                Y2[ln] = FIRST__Y;
                                LAYER_L[ln] = Lay_Arc;
                                W_L[ln] = Th;
                                if (Flag_ARC == true)
                                        {
                                        X0 = (X1[ln] + X2[ln])/2;
                                        Y0 = (Y1[ln] + Y2[ln])/2;
                                        download_ANG();
                                        Generate_Arc();
                                        }
                                else ln++;
                                }
                        }//else if (A.UpperCase().SubString(1,8) == "POLYLINE" )
                //****************************** LWPOLYLINE ***************************************
                //****************************** LWPOLYLINE ***************************************
                else if (A.UpperCase().SubString(1,10) == "LWPOLYLINE" || A.UpperCase().SubString(1,6) == "SPLINE" && Trigger == 0)  //если линия
                        {
                        bool SPLINE = false;
                        if( A.UpperCase().SubString(1,6) == "SPLINE" )
                                SPLINE = true;
                        double type_Line;
                        ////double Flag_ARC = 0;
                        bool CLOSED_LINE = false;
                        long FLG = 0;
                        double FIRSTX = 0;
                        double FIRSTY = 0;
                        LAYER_L[ln] = "Unnamed";
                        Th = 0;
                        W_L[ln] = 0;
                        type_Line = 0;
                        while (1)     //пока не конец линии читаем параметры
                                {
                                Read.getline(stringchar,sizeof(stringchar));
                                lines++;
                                A = stringchar;
                                A = A.Trim();
                                if (A.Length() == 0) continue ;
                                else if (A.SubString(1,A.Length()) == "0") break;
                                else if (A.SubString(1,A.Length()) == "8")       //слой линии
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        A = stringchar;
                                        A = A.Trim();
                                        Lay_Arc = A;
                                        }
                                else if (A.SubString(1,A.Length()) == "10")       //X1 линии
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        A = stringchar;
                                        A = A.Trim();
                                        if(FLG == 0)
                                                {
                                                A = StringReplace(A,".",",",TReplaceFlags()<<rfReplaceAll);
                                                X1[ln] = StrToFloat(A);
                                                X1[ln] = X1[ln]*MILLION;
                                                FIRSTX = X1[ln];
                                                }
                                        else if(FLG == 1)
                                                {
                                                A = StringReplace(A,".",",",TReplaceFlags()<<rfReplaceAll);
                                                X2[ln] = StrToFloat(A);
                                                X2[ln] = X2[ln]*MILLION;
                                                if (blk_adr < 0)
                                                        {
                                                        if (AbsXmin > X2[ln]) AbsXmin = X2[ln];
                                                        if (AbsXMAX < X2[ln]) AbsXMAX = X2[ln];
                                                        }
                                                }
                                        else if(FLG > 1)
                                                {
                                                A = StringReplace(A,".",",",TReplaceFlags()<<rfReplaceAll);
                                                X1[ln] = X2[ln-1];
                                                X2[ln] = StrToFloat(A);
                                                X2[ln] = X2[ln]*MILLION;
                                                if (blk_adr < 0)
                                                        {
                                                        if (AbsXmin > X2[ln]) AbsXmin = X2[ln];
                                                        if (AbsXMAX < X2[ln]) AbsXMAX = X2[ln];
                                                        }
                                                }
                                        LAYER_L[ln] = Lay_Arc;
                                        W_L[ln] = Th;
                                        }
                                else if (A.SubString(1,A.Length()) == "20")       //Y1 линии
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        A = stringchar;
                                        A = A.Trim();
                                        if(FLG == 0)
                                                {
                                                A = StringReplace(A,".",",",TReplaceFlags()<<rfReplaceAll);
                                                Y1[ln] = StrToFloat(A);
                                                Y1[ln] = Y1[ln]*MILLION;
                                                FIRSTY = Y1[ln];
                                                }
                                        else if(FLG == 1)
                                                {
                                                A = StringReplace(A,".",",",TReplaceFlags()<<rfReplaceAll);
                                                Y2[ln] = StrToFloat(A);
                                                Y2[ln] = Y2[ln]*MILLION;
                                                if (blk_adr < 0)
                                                        {
                                                        if (AbsYmin > Y2[ln]) AbsYmin = Y2[ln];
                                                        if (AbsYMAX < Y2[ln]) AbsYMAX = Y2[ln];
                                                        }
                                                X0 = (X1[ln] + X2[ln])/2;
                                                Y0 = (Y1[ln] + Y2[ln])/2;
                                                download_ANG();
                                                if (ABS(type_Line) != 1) ln++;
                                                else Generate_Arc();
                                                type_Line = 0;
                                                }
                                        else if(FLG > 1)
                                                {
                                                A = StringReplace(A,".",",",TReplaceFlags()<<rfReplaceAll);
                                                Y1[ln] = Y2[ln-1] ;
                                                Y2[ln] = StrToFloat(A);
                                                Y2[ln] = Y2[ln]*MILLION;
                                                if (blk_adr < 0)
                                                        {
                                                        if (AbsYmin > Y2[ln]) AbsYmin = Y2[ln];
                                                        if (AbsYMAX < Y2[ln]) AbsYMAX = Y2[ln];
                                                        }
                                                X0 = (X1[ln] + X2[ln])/2;
                                                Y0 = (Y1[ln] + Y2[ln])/2;
                                                download_ANG();
                                                int SaveLN;
                                                if (type_Line == -1)
                                                        {
                                                        Ang_1 = Ang_1 + Ang_2;
                                                        Ang_2 = Ang_1 - Ang_2;
                                                        Ang_1 = Ang_1 - Ang_2;
                                                        SaveLN = ln;
                                                        }
                                                if (ABS(type_Line) != 1) ln++;
                                                else Generate_Arc();
                                                if (type_Line == -1)
                                                        {
                                                        X1[ln] = X1[SaveLN];
                                                        X2[ln] = X1[SaveLN];
                                                        Y1[ln] = Y1[SaveLN];
                                                        Y2[ln] = Y1[SaveLN];
                                                        W_L[ln] = W_L[SaveLN];
                                                        LAYER_L[ln] = LAYER_L[SaveLN];
                                                        ln++;
                                                        }
                                                type_Line = 0;
                                                }
                                        FLG++;
                                        }
                                else if ( /*SPLINE == false && */(A.SubString(1,A.Length()) == "43" || A.SubString(1,A.Length()) == "40"))        //толщина линии
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        A = stringchar;
                                        A = A.Trim();
                                        A = StringReplace(A,".",",",TReplaceFlags()<<rfReplaceAll);
                                        Th = StrToFloat(A);
                                        Th = Th*MILLION;
                                        }
                                else if ( SPLINE == false && (A.SubString(1,A.Length()) == "42") )                    //прогиб линии
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        A = stringchar;
                                        A = A.Trim();
                                        A = StringReplace(A,".",",",TReplaceFlags()<<rfReplaceAll);
                                        type_Line = StrToFloat(A);
                                        }
                                else if ( SPLINE == false && (A.SubString(1,A.Length()) == "70") )        //Замкнутость линии
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        A = stringchar;
                                        A = A.Trim();
                                        if (A.SubString(1,1) == "1") CLOSED_LINE = true;
                                        }
                                else    //пропускаем строку
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        }
                                }//while (1)
                        if (CLOSED_LINE)
                                {
                                X1[ln] = X2[ln-1];
                                Y1[ln] = Y2[ln-1];
                                X2[ln] = FIRSTX;
                                Y2[ln] = FIRSTY;
                                LAYER_L[ln] = Lay_Arc;
                                W_L[ln] = Th;
                                X0 = (X1[ln] + X2[ln])/2;
                                Y0 = (Y1[ln] + Y2[ln])/2;
                                download_ANG();
                                int SaveLN;
                                if (type_Line == -1)
                                        {
                                        Ang_1 = Ang_1 + Ang_2;
                                        Ang_2 = Ang_1 - Ang_2;
                                        Ang_1 = Ang_1 - Ang_2;
                                        SaveLN = ln;
                                        }
                                if (ABS(type_Line) != 1) ln++;
                                else Generate_Arc();
                                if (type_Line == -1)
                                        {
                                        X1[ln] = X1[SaveLN];
                                        X2[ln] = X1[SaveLN];
                                        Y1[ln] = Y1[SaveLN];
                                        Y2[ln] = Y1[SaveLN];
                                        W_L[ln] = W_L[SaveLN];
                                        LAYER_L[ln] = LAYER_L[SaveLN];
                                        ln++;
                                        }
                                type_Line = 0;
                                }
                        }// if (A.UpperCase().SubString(1,10) == "LWPOLYLINE" )  //если линия

                //******************************** ELLIPSE ***************************************
                else if ((A.UpperCase().SubString(1,7) == "ELLIPSE" ) && Trigger == 0)  //если ELLIPSE
                         {
                        Th = 0;
                        Ang_1 = 0;
                        Ang_2 = 360;
                        LAYER_L[ln] = "Unnamed";
                        while (1)     //пока не конец линии читаем параметры
                                {
                                Read.getline(stringchar,sizeof(stringchar));
                                lines++;
                                A = stringchar;
                                A = A.Trim();
                                W_L[ln] = 0;
                                if (A.Length() == 0) continue ;
                                else if (A.SubString(1,A.Length()) == "0") break;
                                else if (A.SubString(1,A.Length()) == "ENDSEC") break;
                                else if (A.SubString(1,A.Length()) == "8")       //слой
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        A = stringchar;
                                        A = A.Trim();
                                        Lay_Arc = A;
                                        }
                                else if (A.SubString(1,A.Length()) == "10")       //X0
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        A = stringchar;
                                        A = A.Trim();
                                        A = StringReplace(A,".",",",TReplaceFlags()<<rfReplaceAll);
                                        X0 = StrToFloat(A);
                                        X0 = X0*MILLION;
                                        }
                                else if (A.SubString(1,A.Length()) == "20")       //Y0
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        A = stringchar;
                                        A = A.Trim();
                                        A = StringReplace(A,".",",",TReplaceFlags()<<rfReplaceAll);
                                        Y0 = StrToFloat(A);
                                        Y0 = Y0*MILLION;
                                        }
                                else if (A.SubString(1,A.Length()) == "11")       //Ellipse_X
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        A = stringchar;
                                        A = A.Trim();
                                        A = StringReplace(A,".",",",TReplaceFlags()<<rfReplaceAll);
                                        Ellipse_X = StrToFloat(A);
                                        Ellipse_X = Ellipse_X*MILLION;
                                        }
                                else if (A.SubString(1,A.Length()) == "21")       //Ellipse_Y
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        A = stringchar;
                                        A = A.Trim();
                                        A = StringReplace(A,".",",",TReplaceFlags()<<rfReplaceAll);
                                        Ellipse_Y = StrToFloat(A);
                                        Ellipse_Y = Ellipse_Y*MILLION;
                                        }
                                else if (A.SubString(1,A.Length()) == "39")       //толщина
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        A = stringchar;
                                        A = A.Trim();
                                        A = StringReplace(A,".",",",TReplaceFlags()<<rfReplaceAll);
                                        Th = StrToFloat(A);
                                        Th = Th*MILLION;
                                        }
                                else if (A.SubString(1,A.Length()) == "40")       //RATIO
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        A = stringchar;
                                        A = A.Trim();
                                        A = StringReplace(A,".",",",TReplaceFlags()<<rfReplaceAll);
                                        Ellipse_K = StrToFloat(A);
                                        }
                                else if (A.SubString(1,A.Length()) == "41")       //начальный угол
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        A = stringchar;
                                        A = A.Trim();
                                        A = StringReplace(A,".",",",TReplaceFlags()<<rfReplaceAll);
                                        Ang_1 = StrToFloat(A)*180.0/M_PI;
                                        }
                                else if (A.SubString(1,A.Length()) == "42")       //конечный угол
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        A = stringchar;
                                        A = A.Trim();
                                        A = StringReplace(A,".",",",TReplaceFlags()<<rfReplaceAll);
                                        Ang_2 = StrToFloat(A)*180.0/M_PI;
                                        Ellipse_A = 90.0;
                                        if( ABS(Ellipse_X) > BY_ZERO )
                                                {
                                                Ellipse_A = atan(Ellipse_Y/Ellipse_X)*180/M_PI;
                                                if( Ellipse_X < 0.0 )
                                                        Ellipse_A += 180.0;
                                                }
                                        else if( Ellipse_Y < 0.0 )
                                                Ellipse_A = -90.0;
                                        Ang_1 += (Ellipse_A);
                                        Ang_2 += (Ellipse_A);

                                        }
                                else    //пропускаем строку
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        }
                                }//while (1)
                        Generate_Arc();
                        Ellipse_X = 0;
                        Ellipse_Y = 0;
                        Ellipse_K = 0;
                        Ellipse_A = 0;
                        }
                        
                //******************************** ARC ***************************************
                else if (((A.UpperCase().SubString(1,3) == "ARC" )||(A.UpperCase().SubString(1,6) == "CIRCLE" )) && Trigger == 0)  //если ДУГА
                         {
                        Th = 0;
                        Ang_1 = 0;
                        Ang_2 = 360;
                        LAYER_L[ln] = "Unnamed";
                        while (1)     //пока не конец линии читаем параметры
                                {
                                Read.getline(stringchar,sizeof(stringchar));
                                lines++;
                                A = stringchar;
                                A = A.Trim();
                                W_L[ln] = 0;
                                if (A.Length() == 0) continue ;
                                else if (A.SubString(1,A.Length()) == "0") break;
                                else if (A.SubString(1,A.Length()) == "ENDSEC") break;
                                else if (A.SubString(1,A.Length()) == "8")       //слой дуги
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        A = stringchar;
                                        A = A.Trim();
                                        Lay_Arc = A;
                                        }
                                else if (A.SubString(1,A.Length()) == "10")       //X0 дуги
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        A = stringchar;
                                        A = A.Trim();
                                        A = StringReplace(A,".",",",TReplaceFlags()<<rfReplaceAll);
                                        X0 = StrToFloat(A);
                                        X0 = X0*MILLION;
                                        }
                                else if (A.SubString(1,A.Length()) == "20")       //Y0 дуги
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        A = stringchar;
                                        A = A.Trim();
                                        A = StringReplace(A,".",",",TReplaceFlags()<<rfReplaceAll);
                                        Y0 = StrToFloat(A);
                                        Y0 = Y0*MILLION;
                                        }
                                else if (A.SubString(1,A.Length()) == "39")       //толщина
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        A = stringchar;
                                        A = A.Trim();
                                        A = StringReplace(A,".",",",TReplaceFlags()<<rfReplaceAll);
                                        Th = StrToFloat(A);
                                        Th = Th*MILLION;
                                        }
                                else if (A.SubString(1,A.Length()) == "40")       //радиус
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        A = stringchar;
                                        A = A.Trim();
                                        A = StringReplace(A,".",",",TReplaceFlags()<<rfReplaceAll);
                                        R = StrToFloat(A);
                                        R = R*MILLION;
                                        }
                                else if (A.SubString(1,A.Length()) == "50")       //начальный угол
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        A = stringchar;
                                        A = A.Trim();
                                        A = StringReplace(A,".",",",TReplaceFlags()<<rfReplaceAll);
                                        Ang_1 = StrToFloat(A);
                                        }
                                else if (A.SubString(1,A.Length()) == "51")       //конечный угол
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        A = stringchar;
                                        A = A.Trim();
                                        A = StringReplace(A,".",",",TReplaceFlags()<<rfReplaceAll);
                                        Ang_2 = StrToFloat(A);
                                        }
                                else    //пропускаем строку
                                        {
                                        Read.getline(stringchar,sizeof(stringchar));
                                        lines++;
                                        }
                                }//while (1)
                        Generate_Arc();
                        }
                } //else (A.Length() == 0)
        } //while (out < 10)
Read.close();
Form1->Label4->Caption = AnsiString("Total Lines: ") + ln;
Form1->Label5->Caption = AnsiString("Progress bar: ") ;
if (FWarning1) ShowMessage ("   Warning! Count lines > Size Of Memory.(Limited)");
if (ln == 0) exit(0);
//===================

bool F = false;
for (int k=0; k<ln; k++)
        {
        if (BLK_NAME[k].Length() && BLK_NAME[k].SubString(1,BLK_NAME[k].Length()) != "ENDBLK")
                F = true;
        if (F)
                LAYER_L[k] = "#";
        if (BLK_NAME[k].SubString(1,BLK_NAME[k].Length()) == "ENDBLK" ) F = false;
        }
A = ExtractFilePath(Application->ExeName);
A = A + "report.csv";
ofstream report (A.c_str());
report << "LAYER_L;BLK_NAME;W_L;X1;Y1;X2;Y2;";
report << endl;
for (int k=0; k<ln; k++)
        {
        report << LAYER_L[k].c_str();
        report << ";";
        report << BLK_NAME[k].c_str();
        report << ";";
        report << W_L[k];
        report << ";";
        report << X1[k];
        report << ";";
        report << Y1[k];
        report << ";";
        report << X2[k];
        report << ";";
        report << Y2[k];
        report << ";";
        report << endl;
        }
report.close();
//
//НАЧАЛО ЗАПИСИ
//
long COUNT = 0;
double Proc = 0;
Form1->Label3->Visible = true;
Form1->Label5->Caption = "Silk Lines:";
double Dzaz = StrToFloat(Form1->ComboBox2->Items->operator [](Form1->ComboBox2->ItemIndex));
//------------     ЗАПИСЬ В ФАЙЛ     ------------

//===============================================
char DATTM[80];
time_t rawtime;                                  //определение текущего времени
struct tm * timeinfo;
time ( &rawtime );                               // текущая дата в секундах
timeinfo = localtime ( &rawtime );
strftime (DATTM,80,"_ID%H%M",timeinfo); //формирование строки с датой
AnsiString TimeStr = DATTM;
// ADD MOIRES...
int MOIRES[4] = {AbsXmin,AbsYmin,AbsXMAX,AbsYMAX};
if (!Form1->CheckBox4->Checked)
        {
        AbsXMAX -= AbsXmin;
        AbsYMAX -= AbsYmin;
        AbsXmin = 0;
        AbsYmin = 0;
        }
if (Form1->CheckBox2->Checked)
if (AbsXmin < DEFAULT-1)
        {
        double Xm;// = MOIRES[0];// - AbsXmin;
        double Ym;// = MOIRES[1];// - AbsYmin;
        double delta = (AbsXMAX - AbsXmin)/7;
        Xm = MOIRES[0] - delta;// - AbsXmin;
        Ym = MOIRES[1];// - AbsYmin;
        LAYER_L[ln] = "Sizes";
        W_L[ln] = 10000;
        X1[ln] = Xm;
        Y1[ln] = Ym;
        Xm += delta*2;
        X2[ln] = Xm;
        Y2[ln] = Ym;
        ln++;
        Xm = MOIRES[2] - delta;// - AbsXmin;
        LAYER_L[ln] = "Sizes";
        W_L[ln] = 10000;
        X1[ln] = Xm;
        Y1[ln] = Ym;
        Xm += delta*2;
        X2[ln] = Xm;
        Y2[ln] = Ym;
        ln++;
        Xm = MOIRES[0] - delta;// - AbsXmin;
        Ym = MOIRES[3];// - AbsYmin;
        LAYER_L[ln] = "Sizes";
        W_L[ln] = 10000;
        X1[ln] = Xm;
        Y1[ln] = Ym;
        Xm += delta*2;
        X2[ln] = Xm;
        Y2[ln] = Ym;
        ln++;
        Xm = MOIRES[2] - delta;// - AbsXmin;
        LAYER_L[ln] = "Sizes";
        W_L[ln] = 10000;
        X1[ln] = Xm;
        Y1[ln] = Ym;
        Xm += delta*2;
        X2[ln] = Xm;
        Y2[ln] = Ym;
        ln++;
        Xm = MOIRES[0];// - AbsXmin;
        Ym = MOIRES[1] - delta;// - AbsYmin;
        LAYER_L[ln] = "Sizes";
        W_L[ln] = 10000;
        X1[ln] = Xm;
        Y1[ln] = Ym;
        Ym += delta*2;
        X2[ln] = Xm;
        Y2[ln] = Ym;
        ln++;
        Ym = MOIRES[3] - delta;// - AbsYmin;
        LAYER_L[ln] = "Sizes";
        W_L[ln] = 10000;
        X1[ln] = Xm;
        Y1[ln] = Ym;
        Ym += delta*2;
        X2[ln] = Xm;
        Y2[ln] = Ym;
        ln++;
        Xm = MOIRES[2];// - AbsXmin;
        Ym = MOIRES[1] - delta;// - AbsYmin;
        LAYER_L[ln] = "Sizes";
        W_L[ln] = 10000;
        X1[ln] = Xm;
        Y1[ln] = Ym;
        Ym += delta*2;
        X2[ln] = Xm;
        Y2[ln] = Ym;
        ln++;
        Ym = MOIRES[3] - delta;// - AbsYmin;
        LAYER_L[ln] = "Sizes";
        W_L[ln] = 10000;
        X1[ln] = Xm;
        Y1[ln] = Ym;
        Ym += delta*2;
        X2[ln] = Xm;
        Y2[ln] = Ym;
        ln++;
        }
if( Form1->OpenDialog1->FileName.Length() )
        A = ExtractFilePath(Form1->OpenDialog1->FileName);
else
        A = ExtractFilePath(Application->ExeName);
if( Form1->Freeasy->Checked )
        A = A + "ImportDXF.cds";
else    A = A + "ImportDXF.fpc";
AnsiString NAME = A;
ofstream Write (A.c_str());
Write << "[options]" << endl;
if( Form1->Freeasy->Checked )
        {
        Write << "version: 1.0" << endl;
        Write << "file_version: 1.0" << endl;
        }
else    {
        Write << "version: 2.028" << endl;
        Write << "file_version: 2.028" << endl;
        }
Write << "units: MM" << endl;
Write << "m_scale_factor: 9999" << endl;
Write << "m_top_layer: 12" << endl;
Write << "m_org_x: -999" << endl;
Write << "m_org_y: -999" << endl;
Write << "placement_grid_spacing: 2540" << endl;
Write << "routing_grid_spacing: 2540" << endl;
Write << "default_trace_width: 558800" << endl;
Write << "default_via_pad_width: 1778000" << endl;
Write << "default_via_hole_width: 965200" << endl;
Write << "n_width_menu: 1" << endl;
Write << "width_menu_item: 1 558800 1778000 965200" << endl;
Write << "n_copper_layers: 2" << endl;
Write << "layer_info: \"selection\" 0 255 255 255 1" << endl;
Write << "layer_info: \"background\" 1 0 0 0 1" << endl;
Write << "layer_info: \"visible grid\" 2 255 255 255 1" << endl;
Write << "layer_info: \"highlight\" 3 255 255 255 1" << endl;
Write << "layer_info: \"DRC error\" 4 0 0 0 1" << endl;
Write << "layer_info: \"board outline\" 5 0 0 255 1" << endl;
Write << "layer_info: \"rat line\" 6 128 128 255 1" << endl;
Write << "layer_info: \"top silk\" 7 255 255 255 1" << endl;
Write << "layer_info: \"bottom silk\" 8 255 125 125 0" << endl;
Write << "layer_info: \"top sm cutout\" 9 160 160 160 1" << endl;
Write << "layer_info: \"bot sm cutout\" 10 95 95 95 1" << endl;
Write << "layer_info: \"thru pad\" 11 0 255 0 1" << endl;
Write << "layer_info: \"top copper\" 12 0 128 0 1" << endl;
Write << "[footprints]" << endl;
if( Form1->Freeasy->Checked )
        Write << "rename_page: \"page 1\"" << endl;
long lay;
n = -2000000;
int SHIFT = 0;
double Xback = 0;
double Yback = 0;
double X2back = 0;
double Y2back = 0;
while(1)
        {//ЗАПИСЬ ФУТПРИНТОВ
        lay = 0;
        if (n < -300000000)
                {
                n = -2000000;
                SHIFT += 25654000;
                if (SHIFT > 400000000)
                        {
                        ShowMessage("    Ru: Ошибка! Нет места для размещения компонентов.\n\n    En: Error! There is no place to place the components." );
                        exit(0);
                        }
                }
        while (LAYER_L[lay].SubString(1,1) == "#")
                {
                lay++;
                if (lay >= ln)
                        break;
                }
        if (lay >= ln)
                break;
        A = LAYER_L[lay];
        if (Form1->CheckBox7->Checked) A = "Sizes";
        if (Form1->CheckBox5->Checked && Form1->CheckBox2->Checked) A = "Sizes";
        names_layers[nml] = A;
        nml++;
        Write << (AnsiString("name: \"DXF_") + A + TimeStr + "\"").c_str() << endl;
        Write << "units: NM" << endl;
        Write << "sel_rect: ";
        Write << AnsiString((long)(SHIFT-254000)).c_str();
        Write << " ";
        Write << AnsiString((long)(n-254000)).c_str();
        Write << " ";
        Write << AnsiString((long)(SHIFT+25654000)).c_str();
        Write << " ";
        Write << AnsiString((long)(n+2254000)).c_str() << endl;
        Write << "ref_text: 300000 0 0 0 10000" << endl;
        Write << "value_text: 300000 0 0 0 10000" << endl;
        Write << "centroid: 0 0 0 0" << endl;

        // draw label
        /*Write << "outline_polyline: 200000 ";
        Write << AnsiString(SHIFT).c_str();
        Write << " ";
        Write << AnsiString((long)(n+2000000)).c_str() << endl;
        Write << "next_corner: ";
        Write << AnsiString(SHIFT).c_str();
        Write << " ";
        Write << AnsiString((long)n).c_str();
        Write << " 0" << endl;
        Write << "next_corner: ";
        Write << AnsiString(SHIFT+25400000).c_str();
        Write << " ";
        Write << AnsiString((long)n).c_str();
        Write << " 0" << endl;
        Write << "next_corner: ";
        Write << AnsiString(SHIFT+25400000).c_str();
        Write << " ";
        Write << AnsiString((long)(n+2000000)).c_str();
        Write << " 0" << endl;
        Write << "close_polyline: 0" << endl;
        Write << "text: \"DXF: ";
        Write <<  A.c_str();
        Write <<  "\"";
        Write << (AnsiString(" ") + AnsiString(MILLION) + AnsiString(" ")).c_str();
        Write << AnsiString(SHIFT+600000).c_str();
        Write << " ";
        Write << AnsiString((long)(n+600000)).c_str();
        Write << " 0 200000 0 4" << endl;  */
        n = n-2000000;
        i = 0;
        while (i < ln)
                {
                if(LAYER_L[i].SubString(1,1) == "#")
                        {
                        i++;
                        continue;
                        }
                if (!Form1->CheckBox5->Checked)
                if(LAYER_L[i].SubString(1,LAYER_L[i].Length()) != A.SubString(1,A.Length()))
                        {
                        i++;
                        continue;
                        }
                LAYER_L[i] = "#" + LAYER_L[i];
                if (W_L[i] == 0) W_L[i] = 10000;
                if (ABS(X1[i]-X2[i]) > BY_ZERO || ABS(Y1[i]-Y2[i]) > BY_ZERO)
                        {
                        if (ABS(Xback-X1[i]) < BY_ZERO && ABS(Yback-Y1[i]) < BY_ZERO && ABS(X2back-X2[i]) < BY_ZERO && ABS(Y2back-Y2[i]) < BY_ZERO)
                                {
                                //empty
                                }
                        else if (ABS(Xback-X2[i]) < BY_ZERO && ABS(Yback-Y2[i]) < BY_ZERO && ABS(X2back-X1[i]) < BY_ZERO && ABS(Y2back-Y1[i]) < BY_ZERO)
                                {
                                //empty
                                }
                        else if (ABS(Z1[i]-Z2[i]) > BY_ZERO)
                                {
                                //empty
                                }
                        else    {
                                Write << "outline_polyline: ";
                                Write << (AnsiString((int)W_L[i]) + " ").c_str();
                                Write << (AnsiString((int)X1[i] - (int)AbsXmin) + " ").c_str();
                                Write << (AnsiString((int)Y1[i] - (int)AbsYmin)).c_str() << endl;
                                Write << "next_corner: ";
                                Write << (AnsiString((int)X2[i] - (int)AbsXmin) + " ").c_str();
                                Write << (AnsiString((int)Y2[i] - (int)AbsYmin) + " 0").c_str() << endl;
                                Xback = X1[i];
                                Yback = Y1[i];
                                X2back = X2[i];
                                Y2back = Y2[i];
                                }
                        }
                i++;
                COUNT++;
                Proc = (COUNT*100)/ln;
                Form1->Label3->Caption = AnsiString((int)Proc) + "%";
                Application->ProcessMessages();
                }
        // ADD SIZES...
        if (Form1->CheckBox2->Checked)
        if (A.SubString(1,9) == "Sizes")
        if (AbsXmin < DEFAULT-1)
                {
                Write << "text: \"[0;0]\" 3000000 ";
                Write << AnsiString((long)(MOIRES[0] - AbsXmin - 12000000)).c_str();
                Write << " ";
                Write << AnsiString((long)(MOIRES[1] - AbsYmin - 4000000)).c_str();
                Write << " 0 500000 0 4" << endl;
                Write << "text: \"[";
                Write << FormatFloat("0.00",(MOIRES[2] - AbsXmin)/MILLION).c_str();
                Write << ";";
                Write << FormatFloat("0.00",(MOIRES[3] - AbsYmin)/MILLION).c_str();
                Write <<  "]\"";
                Write << " 3000000 ";
                Write << AnsiString((long)(MOIRES[2] - AbsXmin + 1500000)).c_str();
                Write << " ";
                Write << AnsiString((long)(MOIRES[3] - AbsYmin + 1500000)).c_str();
                Write << " 0 500000 0 4" << endl;
                }
        Write << "n_pins: 0" << endl;
        Write << "part_end" << endl;
        if (Form1->CheckBox7->Checked)
                break;
        }//КОНЕЦ ЗАПИСИ ФУТПРИНТОВ
//
if( Form1->Freeasy->Checked )
        Write << "view_all" << endl;
//
Xback = 0;
Yback = 0;
//
// Все линии как PCB компонент
if (Form1->CheckBox7->Checked)
        {
        int cnt_lines_foot = ln/2000;
        int indexback = 0;
        int corrX;
        int corrY;
        int LINES = 0;
        for (int q=0; q<ln; q++)
                {
                if (ABS(X1[q] - X2[q]) < 999 && ABS(Y1[q] - Y2[q]) < 999)   {;}
                else if (ABS(Z1[q] - Z2[q]) > BY_ZERO)                      {;}
                else if (LAYER_L[q].SubString(1,1) != "#" )
                        {
                        static int partNum = 0;
                        if (partNum > 0 && (ABS(X1[q] - X1[indexback]) < 9999 || ABS(Y1[q] - Y1[indexback]) < 9999 || LINES < cnt_lines_foot))
                                {
                                A = "outline_polyline: ";
                                A += AnsiString((int)W_L[q]) + " ";
                                A += AnsiString((int)X1[q] - corrX) + " ";
                                A += AnsiString((int)Y1[q] - corrY);
                                Form1->Shapes->Items->Add(A);
                                }

                        else if (q == 0 || ABS(X1[q] - X2[indexback]) > 9999 || ABS(Y1[q] - Y2[indexback]) > 9999)
                                {
                                int Xpos = (X1[q] + X2[q])/2 - AbsXmin;
                                int Ypos = (Y1[q] + Y2[q])/2 - AbsYmin;
                                Form1->Parts->Items->Add("part: Line" + AnsiString(partNum));
                                Form1->Parts->Items->Add("ref_text: 0 0 0 0 0 0");
                                Form1->Parts->Items->Add("shape: \"Line" + AnsiString(partNum) + "\"");
                                Form1->Parts->Items->Add("pos: " + AnsiString(Xpos) + " " + AnsiString(Ypos) + " 0 0 0");
                                Form1->Shapes->Items->Add("name: \"Line" + AnsiString(partNum) + "\"");
                                Form1->Shapes->Items->Add("units: NM");
                                Form1->Shapes->Items->Add("sel_rect: -127000 -127000 127000 127000");
                                Form1->Shapes->Items->Add("ref_text: 0 0 0 0 0");
                                Form1->Shapes->Items->Add("value_text: 0 0 0 0 0");
                                Form1->Shapes->Items->Add("centroid: 0 0 0 0");
                                A = "outline_polyline: ";
                                A += AnsiString((int)W_L[q]) + " ";
                                A += AnsiString((int)X1[q] - (int)(X1[q] + X2[q])/2) + " ";
                                A += AnsiString((int)Y1[q] - (int)(Y1[q] + Y2[q])/2);
                                Form1->Shapes->Items->Add(A);
                                partNum++;
                                LINES = 1;
                                corrX = (int)(X1[q] + X2[q])/2;
                                corrY = (int)(Y1[q] + Y2[q])/2;
                                }
                        A = "next_corner: ";
                        A += AnsiString((int)X2[q] - corrX) + " ";
                        A += AnsiString((int)Y2[q] - corrY) + " 0";
                        Form1->Shapes->Items->Add(A);
                        //Form1->Shapes->Items->Add("n_pins: 0");
                        indexback = q;
                        COUNT++;
                        LINES++;
                        if (q%25 == 0)
                                {
                                Proc = (COUNT*100)/ln;
                                Form1->Label3->Caption = AnsiString((int)Proc) + "%";
                                Application->ProcessMessages();
                                }
                        }
                LAYER_L[q] = "#" + LAYER_L[q];
                }
        }
//
//ЕСЛИ CheckBox1->Checked == TRUE ЗАПИСЬ БОРДЕРА
Write << "[board]" << endl;
if (Form1->CheckBox1->Checked == true)
        {
        Form1->Label5->Caption = "Board Lines:";
        //
        TRect CurrentRect;
        int ind_brd;
        long CNT = 0;
        long COUNT_BRD = 0;
        i = 0;
        n = 0;
        while (i < ln)
                { //Считаем кол во линий бордера
                ind_brd = Form1->ComboBox1->Items->IndexOf(LAYER_L[i].SubString(2,(LAYER_L[i].Length()-1)));
                if (ind_brd >= 0)
                if (Form1->ComboBox1->Selected[ind_brd])
                        {
                        COUNT_BRD++;
                        n++;
                        }
                i++;
                }
        COUNT_BRD++;
        COUNT_BRD = COUNT_BRD*2;
        //ДИНАМИЧЕСКОЕ ВЫДЕЛЕНИЕ ПАМЯТИ
        double *X;
        try     {
                X = new(std::nothrow) double[COUNT_BRD];    //
                }
        catch(std::bad_alloc)
                {
                ShowMessage("    Ошибка выделения памяти: double[" + AnsiString(COUNT_BRD) + "]!" );
                exit(0);
                }
        double *Y;
        try     {
                Y = new(std::nothrow) double[COUNT_BRD];    //
                }
        catch(std::bad_alloc)
                {
                ShowMessage("    Ошибка выделения памяти: double[" + AnsiString(COUNT_BRD) + "]!" );
                exit(0);
                }
        double *XX;
        try     {
                XX = new(std::nothrow) double[COUNT_BRD];    //
                }
        catch(std::bad_alloc)
                {
                ShowMessage("    Ошибка выделения памяти: double[" + AnsiString(COUNT_BRD) + "]!" );
                exit(0);
                }
        double *YY;
        try     {
                YY = new(std::nothrow) double[COUNT_BRD];    //
                }
        catch(std::bad_alloc)
                {
                ShowMessage("    Ошибка выделения памяти: double[" + AnsiString(COUNT_BRD) + "]!" );
                exit(0);
                }
        //
        COUNT = 0;
        i = 0;
        while (i < ln)
                { //ПЕРЕПИСЫВАЕМ ЛИНИИ ВЫБРАННОГО СЛОЯ В ДРУГОЙ МАССИВ
                ind_brd = Form1->ComboBox1->Items->IndexOf(LAYER_L[i].SubString(2,(LAYER_L[i].Length()-1)));
                if (ind_brd >= 0)
                if (Form1->ComboBox1->Selected[ind_brd])
                if (ABS(Z1[i]-Z2[i]) < BY_ZERO)
                        {
                        X[COUNT] = X1[i];
                        Y[COUNT] = Y1[i];
                        XX[COUNT] = X2[i];
                        YY[COUNT] = Y2[i];
                        COUNT++;
                        }
                i++;
                }
        if (COUNT == 0) COUNT = 1;
        ln = COUNT;
        n = 0;
        i = 0;
        while (i < ln)
                {
                if (ABS(X[i]-XX[i]) > BY_ZERO || ABS(Y[i]-YY[i]) > BY_ZERO)
                        {
                        LAYER_L[n] = "Board_layer";
                        X1[n] = X[i];
                        Y1[n] = Y[i];
                        X2[n] = XX[i];
                        Y2[n] = YY[i];
                        n++;
                        }
                i++;
                }
        ln = n;
        delete [] X;
        delete [] Y;
        delete [] XX;
        delete [] YY;
        brd = COUNT_BRD/2;
        BOARD[brd] = AnsiString((int)X1[0] - (int)AbsXmin) + " " + AnsiString((int)Y1[0] - (int)AbsYmin);
        brd++;
        BOARD[brd] = AnsiString((int)X2[0] - (int)AbsXmin) + " " + AnsiString((int)Y2[0] - (int)AbsYmin);
        brd++;
        Point_1[0] = X1[0];
        Point_1[1] = Y1[0];
        Point_2[0] = X2[0];
        Point_2[1] = Y2[0];
        double Start[2];
        Start[0] = X1[0];
        Start[1] = Y1[0];
        Xback = X1[0];
        Yback = Y1[0];
        CurrentRect.Left =  DEFAULT;
        CurrentRect.Right = -DEFAULT;
        CurrentRect.Bottom =DEFAULT;
        CurrentRect.Top =   -DEFAULT;
        CurrentRect.Left =  MIN(X1[0],CurrentRect.Left);
        CurrentRect.Right = MAX(X1[0],CurrentRect.Right);
        CurrentRect.Bottom =MIN(Y1[0],CurrentRect.Bottom);
        CurrentRect.Top =   MAX(Y1[0],CurrentRect.Top);
        CurrentRect.Left =  MIN(CurrentRect.Left,X2[0]);
        CurrentRect.Right = MAX(CurrentRect.Right,X2[0]);
        CurrentRect.Bottom =MIN(CurrentRect.Bottom,Y2[0]);
        CurrentRect.Top =   MAX(CurrentRect.Top,Y2[0]);
        X1[0] = DEFAULT;
        Y1[0] = DEFAULT;
        X2[0] = DEFAULT;
        Y2[0] = DEFAULT;
        Revers = false;
        i = 0;
        n = 0;
        n_line = 0;
        n_brd = 2;
        while(1)
                {//ЗАПИСЬ БОРДЕРА
                while(1)
                        {//ПОИСК ТОЧЕК
                        i++;
                        if (i >= ln){n = 0; break;}
                        if ( ABS(X1[i] - Point_2[0]) < Dzaz && ABS(Y1[i] - Point_2[1]) < Dzaz )  {n = 1; break;}
                        if ( ABS(X2[i] - Point_2[0]) < Dzaz && ABS(Y2[i] - Point_2[1]) < Dzaz )  {n = 2; break;}
                        }//ПОИСК ТОЧЕК
                if (n == 1)
                        {
                        if (ABS(X2[i] - Xback) > Dzaz || ABS(Y2[i] - Yback) > Dzaz)
                                {
                                CNT++;
                                if (ABS(X2[i] - Start[0]) < Dzaz && ABS(Y2[i] - Start[1]) < Dzaz && n_brd > 3)
                                        {
                                        n = 0;
                                        Revers = true;
                                        }
                                else    {
                                        BOARD[brd] = AnsiString((int)X2[i] - (int)AbsXmin) + " " + AnsiString((int)Y2[i] - (int)AbsYmin);
                                        if(Revers == true) brd--;
                                        else brd++;
                                        n_brd++;
                                        Point_2[0] = X2[i];
                                        Point_2[1] = Y2[i];
                                        Xback = X1[i];
                                        Yback = Y1[i];
                                        CurrentRect.Left =  MIN(X1[i],CurrentRect.Left);
                                        CurrentRect.Right = MAX(X1[i],CurrentRect.Right);
                                        CurrentRect.Bottom =MIN(Y1[i],CurrentRect.Bottom);
                                        CurrentRect.Top =   MAX(Y1[i],CurrentRect.Top);
                                        CurrentRect.Left =  MIN(CurrentRect.Left,X2[i]);
                                        CurrentRect.Right = MAX(CurrentRect.Right,X2[i]);
                                        CurrentRect.Bottom =MIN(CurrentRect.Bottom,Y2[i]);
                                        CurrentRect.Top =   MAX(CurrentRect.Top,Y2[i]);
                                        }
                                }
                        X1[i] = DEFAULT;
                        Y1[i] = DEFAULT;
                        X2[i] = DEFAULT;
                        Y2[i] = DEFAULT;
                        i = 0;
                        }
                if (n == 2)
                        {
                        if (ABS(X1[i] - Xback) > Dzaz || ABS(Y1[i] - Yback) > Dzaz)
                                {
                                CNT++;
                                if (ABS(X1[i] - Start[0]) < Dzaz && ABS(Y1[i] - Start[1]) < Dzaz && n_brd > 3)
                                        {
                                        n = 0;
                                        Revers = true;
                                        }
                                else    {
                                        BOARD[brd] = AnsiString((int)X1[i] - (int)AbsXmin) + " " + AnsiString((int)Y1[i] - (int)AbsYmin);
                                        if(Revers == true) brd--;
                                        else brd++;
                                        n_brd++;
                                        Point_2[0] = X1[i];
                                        Point_2[1] = Y1[i];
                                        Xback = X2[i];
                                        Yback = Y2[i];
                                        CurrentRect.Left =  MIN(X1[i],CurrentRect.Left);
                                        CurrentRect.Right = MAX(X1[i],CurrentRect.Right);
                                        CurrentRect.Bottom =MIN(Y1[i],CurrentRect.Bottom);
                                        CurrentRect.Top =   MAX(Y1[i],CurrentRect.Top);
                                        CurrentRect.Left =  MIN(CurrentRect.Left,X2[i]);
                                        CurrentRect.Right = MAX(CurrentRect.Right,X2[i]);
                                        CurrentRect.Bottom =MIN(CurrentRect.Bottom,Y2[i]);
                                        CurrentRect.Top =   MAX(CurrentRect.Top,Y2[i]);
                                        }
                                }
                        X1[i] = DEFAULT;
                        Y1[i] = DEFAULT;
                        X2[i] = DEFAULT;
                        Y2[i] = DEFAULT;
                        i = 0;
                        }
                if (n == 0)
                        {
                        if(BOARD[(COUNT_BRD/2)].Length() == 0) break;
                        if (Revers == false)
                                {
                                Revers = true;
                                Point_2[0] = Point_1[0];
                                Point_2[1] = Point_1[1];
                                brd = COUNT_BRD/2 - 1;
                                i = 0;
                                continue;
                                }
                        else
                                {
                                Revers = false;
                                if (brd < COUNT_BRD/2)  i = brd+1;
                                else                    i = COUNT_BRD/2;
                                if (n_brd > 3)
                                        {
                                        Write << (AnsiString("outline: ") + AnsiString(n_brd) + " " + AnsiString(n_line)).c_str() << endl;
                                        n_line++;
                                        }
                                n = 1;
                                int max = n_brd + i;
                                while (i < max)
                                        {
                                        if (n_brd > 3)
                                                {
                                                Write << (AnsiString("corner: ") + AnsiString(n) + " " + BOARD[i] + " 0").c_str() << endl ;
                                                n++;
                                                }
                                        BOARD[i] = "";
                                        i++;
                                        }
                                i = 0;
                                while (X1[i] >= (DEFAULT-1))
                                        {
                                        i++;
                                        if(i >= ln){ F_break = true; break; }
                                        }
                                if (F_break == true) break;
                                Point_1[0] = X1[i];
                                Point_1[1] = Y1[i];
                                Point_2[0] = X2[i];
                                Point_2[1] = Y2[i];
                                Xback = X1[i];
                                Yback = Y1[i];
                                Start[0] = X1[i];
                                Start[1] = Y1[i];
                                brd = COUNT_BRD/2;
                                BOARD[brd] = AnsiString((int)X1[i] - (int)AbsXmin) + " " + AnsiString((int)Y1[i] - (int)AbsYmin);
                                brd++;
                                BOARD[brd] = AnsiString((int)X2[i] - (int)AbsXmin) + " " + AnsiString((int)Y2[i] - (int)AbsYmin);
                                brd++;
                                //
                                // AUTOHOLES
                                int dCx = CurrentRect.Right - CurrentRect.Left;
                                int dCy = CurrentRect.Top - CurrentRect.Bottom;
                                if (ABS(dCx - dCy) < ABS(dCx + dCy)/20 && n_brd > 5)
                                        {
                                        static int partNum = 0;
                                        int Dhole = (dCx + dCy)/2;
                                        int Xpos = (CurrentRect.Right + CurrentRect.Left)/2 - AbsXmin;
                                        int Ypos = (CurrentRect.Top + CurrentRect.Bottom)/2 - AbsYmin;
                                        double floatDhole = (double)Dhole/(double)MILLION;
                                        AnsiString value = FormatFloat("0.00",floatDhole);
                                        value = StringReplace(value,",",".",TReplaceFlags()<<rfReplaceAll);
                                        Form1->Parts->Items->Add("part: " + AnsiString(partNum));
                                        partNum++;
                                        Form1->Parts->Items->Add("ref_text: 0 0 0 0 0 0");
                                        Form1->Parts->Items->Add("value: \"" + value + "mm\" 500000 80000 0 0 0 1");
                                        Form1->Parts->Items->Add("shape: \"" + value + "mm\"");
                                        Form1->Parts->Items->Add("pos: " + AnsiString(Xpos) + " " + AnsiString(Ypos) + " 0 0 0");
                                        if (Form1->Shapes->Items->IndexOf("name: \"" + value + "mm\"") == -1)
                                                {
                                                Form1->Shapes->Items->Add("name: \"" + value + "mm\"");
                                                Form1->Shapes->Items->Add("units: MM");
                                                Form1->Shapes->Items->Add("sel_rect: -0.5 -0.5 0.5 0.5");
                                                Form1->Shapes->Items->Add("ref_text: 0 0 0 0 0");
                                                Form1->Shapes->Items->Add("value_text: 0 0 0 0 0");
                                                Form1->Shapes->Items->Add("centroid: 0 0 0 0");
                                                Form1->Shapes->Items->Add("n_pins: 1");
                                                Form1->Shapes->Items->Add("pin: \"hole\" " + value + " 0 0 0");
                                                }
                                        }
                                CurrentRect.Left =  DEFAULT;
                                CurrentRect.Right = -DEFAULT;
                                CurrentRect.Bottom =DEFAULT;
                                CurrentRect.Top =   -DEFAULT;
                                CurrentRect.Left =  MIN(X1[i],CurrentRect.Left);
                                CurrentRect.Right = MAX(X1[i],CurrentRect.Right);
                                CurrentRect.Bottom =MIN(Y1[i],CurrentRect.Bottom);
                                CurrentRect.Top =   MAX(Y1[i],CurrentRect.Top);
                                CurrentRect.Left =  MIN(CurrentRect.Left,X2[i]);
                                CurrentRect.Right = MAX(CurrentRect.Right,X2[i]);
                                CurrentRect.Bottom =MIN(CurrentRect.Bottom,Y2[i]);
                                CurrentRect.Top =   MAX(CurrentRect.Top,Y2[i]);
                                X1[i] = DEFAULT;
                                Y1[i] = DEFAULT;
                                X2[i] = DEFAULT;
                                Y2[i] = DEFAULT;
                                n_brd = 2;
                                }
                        }
                Proc = CNT*100/COUNT;
                Form1->Label3->Caption = AnsiString((int)Proc) + "%";
                Application->ProcessMessages();
                }//КОНЕЦ ЗАПИСИ БОРДЕРА
        }
//-------------------------------------
Write << "[solder_mask_cutouts]" << endl;
Write << "[parts]" << endl;
i = 0;
n = -500000;
while (i < nml && i < 2000)
        {//ЗАПИСЬ КОМПОНЕНТОВ
        Write << (AnsiString("part: ") + names_layers[i]).c_str() << endl;
        Write << (AnsiString("ref_text: 0 200000 0 -500000 ") + n + " 0").c_str() << endl;
        Write << (AnsiString("package: \"DXF_") + names_layers[i] + "\"").c_str() << endl;
        Write << (AnsiString("shape: \"DXF_") + names_layers[i] + TimeStr + "\"").c_str() << endl;
        Write << "pos: 0 0 0 0 1" << endl;
        n = n-2000000;
        i++;
        }//КОНЕЦ ЗАПИСИ КОМПОНЕНТОВ
Write << "[nets]" << endl;
Write << "[texts]" << endl;
Write << "[merges]" << endl;
Write << "[end]" << endl;
Write.close();
//
PrevSizeOfMemory = SizeOfMemory;
delete[] LAYER_L;  //слой линии
delete[] LAYER_T;  //слой текста
delete[] BOARD;
delete[] BLK_NAME;
delete[] X1;
X1=0;
delete[] Y1;
delete[] Z1;
delete[] X2;
delete[] Y2;
delete[] Z2;
delete[] W_L;  //ширина линии
delete[] W_T;  //ширина текста
delete[] BasePtX;
delete[] BasePtY;
//
if (Form1->Shapes->Count && Form1->Parts->Count)
        {
        FILE * F;
        F = fopen(NAME.c_str(),"rb+");
        if(F)
                {
                fclose(F);
                ifstream RR (NAME.c_str());
                A = ExtractFilePath(NAME);
                if( Form1->Freeasy->Checked )
                        A = A + "ImportDXFH.cds";
                else    A = A + "ImportDXFH.fpc";
                NAME = A;
                ofstream WriteH (A.c_str());
                while (!RR.eof())
                        {
                        RR.getline(stringchar,sizeof(stringchar));
                        A = stringchar;
                        A = A.Trim();
                        if (A.SubString(1,12) == "[footprints]" )
                                {
                                WriteH << endl;
                                WriteH << "[footprints]" << endl;
                                for (int r=0; r< Form1->Shapes->Count; r++)
                                        {
                                        A = Form1->Shapes->Items->operator [](r);
                                        WriteH << A.c_str() << endl;
                                        }
                                WriteH << endl;
                                }
                        else if (A.SubString(1,7) == "[parts]" )
                                {
                                WriteH << endl;
                                WriteH << "[parts]" << endl;
                                for (int r=0; r< Form1->Parts->Count; r++)
                                        {
                                        A = Form1->Parts->Items->operator [](r);
                                        WriteH << A.c_str() << endl;
                                        }
                                WriteH << endl;
                                }
                        else    WriteH << A.c_str() << endl;
                        }
                RR.close();
                WriteH.close();
                }
        else
                fclose(F);
        }

//-------------запуск ------------
B = NAME;
A = ExtractFilePath(B);
//
SHELLEXECUTEINFO info = {0};
AnsiString fn = ExtractFilePath(Application->ExeName);
fn.SetLength(fn.Length()-1);
fn = ExtractFilePath(fn);
fn.SetLength(fn.Length()-1);
if( Form1->Freeasy->Checked )
        fn = ExtractFilePath(fn) + "FreeCds.exe";
else    fn = ExtractFilePath(fn) + "FreePcb.exe";

// RUS
if( FileExists(fn) == 0 )
        if( Form1->Freeasy->Checked )
                fn = ExtractFilePath(fn) + "СхемАтор.exe";
        else
                fn = ExtractFilePath(fn) + "ПлатФорм.exe";
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
        ShowMessage("Something went wrong .. If the problem persists more than once, report it to support at Freepcb2");

///exit(0);
}//КОНЕЦ ПРОГРАММЫ ЗАПИСИ

void __fastcall TForm1::CheckBox1Click(TObject *Sender)
{
if (Form1->CheckBox1->Checked == true)
   {
    Form1->ComboBox1->Enabled = true;
    Form1->ComboBox2->Enabled = true;
    Form1->Label1->Enabled = true;
    Form1->Label2->Enabled = true;
    ///Form1->CheckBox2->Enabled = true;
    Form1->CheckBox6->Enabled = true;
   }
else
   {
    Form1->ComboBox1->Enabled = false;
    Form1->ComboBox2->Enabled = false;
    Form1->Label1->Enabled = false;
    Form1->Label2->Enabled = false;
    ///Form1->CheckBox2->Checked = false;
    ///Form1->CheckBox2->Enabled = false;
    Form1->CheckBox6->Enabled = false;
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
if(Form1->MIL->Checked)
        MILLION = 25400;
WR();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CheckBox3Click(TObject *Sender)
{
if (Form1->CheckBox3->Checked == true)
        {
        Form1->Edit1->Enabled = true;
        }
else
        {
        Form1->Edit1->Enabled = false;
        }
}
//---------------------------------------------------------------------------




void __fastcall TForm1::Label6Click(TObject *Sender)
{
ShellExecute(NULL, "open", "https://github.com/niconson", NULL, NULL, SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FreeasyClick(TObject *Sender)
{
CheckBox1->Enabled = 0;
CheckBox4->Enabled = 0;
CheckBox5->Enabled = 0;
CheckBox7->Enabled = 0;
CheckBox1->Checked = 0;
CheckBox4->Checked = 0;
CheckBox5->Checked = 0;
CheckBox7->Checked = 0;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FreePcbClick(TObject *Sender)
{
CheckBox1->Enabled = 1;
CheckBox4->Enabled = 1;
CheckBox5->Enabled = 1;
CheckBox7->Enabled = 1;
}
//---------------------------------------------------------------------------

