//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Combine.h"
#include "ABClibrary.h"
#include "Please_wait.h"
#include "fstream.h"
#include "time.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;
long n;
long m;
AnsiString UnitsC;
struct TypeDefText
        {
        AnsiString TextString;
        long H;
        long W;
        long X;
        long Y;
        long Angle;
        long Layer;
        bool Mirror;
        };
struct TypeDefPart
        {
        long PosX;
        long PosY;
        long Side;
        long Angle;
        long Glueds;
        AnsiString Shape;
        AnsiString Package;
        AnsiString RefText;
        AnsiString ValueText;
        long RefX;
        long RefY;
        long RefWidth;
        long RefHeight;
        long RefAngle;
        bool RefVisible;
        long ValueX;
        long ValueY;
        long ValueWidth;
        long ValueHeight;
        long ValueAngle;
        bool ValueVisible;
        };
TypeDefPart * PART;
/*struct TypeDefPin
        {
        AnsiString Name;
        long Hole;
        long X;
        long Y;
        long Angle;
        long TopType;
        long TopWidth;
        long TopHeight;
        long TopRndRadius;
        long TopThrmlType;
        long BottomType;
        long BottomWidth;
        long BottomHeight;
        long BottomRndRadius;
        long BottomThrmlType;
        long InnerType;
        long InnerWidth;
        long InnerHeight;
        long InnerRndRadius;
        long InnerThrmlType;
        }; */





//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
        : TForm(Owner)
{

}






//---------------------------------------------------------------------------
//��������� �� �, ������� ���������
void mirror_angle (double Part_angle, bool Part_layer, double *X, double *Y)
{
double D;
if(Part_layer) (*X) = -(*X);
Rotate_Vertex (X, Y, (-Part_angle));
}





//---------------------------------------------------------------------------
AnsiString Symbol(int N)
        {
        AnsiString OutSymbol = "";
        switch (N/25)
                {
                case 0: OutSymbol += "";  break;
                case 1: OutSymbol += "A"; break;
                case 2: OutSymbol += "B"; break;
                case 3: OutSymbol += "C"; break;
                case 4: OutSymbol += "D"; break;
                case 5: OutSymbol += "E"; break;
                case 6: OutSymbol += "F"; break;
                case 7: OutSymbol += "G"; break;
                case 8: OutSymbol += "H"; break;
                case 9: OutSymbol += "I"; break;
                case 10:OutSymbol += "J"; break;
                case 11: OutSymbol += "K";break;
                case 12: OutSymbol += "L";break;
                case 13: OutSymbol += "M";break;
                case 14: OutSymbol += "N";break;
                case 15: OutSymbol += "O";break;
                case 16: OutSymbol += "P";break;
                case 17: OutSymbol += "Q";break;
                case 18: OutSymbol += "R";break;
                case 19: OutSymbol += "S";break;
                case 20: OutSymbol += "T";break;
                case 21: OutSymbol += "U";break;
                case 22: OutSymbol += "V";break;
                case 23: OutSymbol += "W";break;
                case 24: OutSymbol += "X";break;
                case 25: OutSymbol += "Y";break;
                case 26: OutSymbol += "Z";break;
                }
        switch (N%25)
                {
                case 0: OutSymbol += "A"; break;
                case 1: OutSymbol += "B"; break;
                case 2: OutSymbol += "C"; break;
                case 3: OutSymbol += "D"; break;
                case 4: OutSymbol += "E"; break;
                case 5: OutSymbol += "F"; break;
                case 6: OutSymbol += "G"; break;
                case 7: OutSymbol += "H"; break;
                case 8: OutSymbol += "I"; break;
                case 9: OutSymbol += "J"; break;
                case 10: OutSymbol += "K";break;
                case 11: OutSymbol += "L";break;
                case 12: OutSymbol += "M";break;
                case 13: OutSymbol += "N";break;
                case 14: OutSymbol += "O";break;
                case 15: OutSymbol += "P";break;
                case 16: OutSymbol += "Q";break;
                case 17: OutSymbol += "R";break;
                case 18: OutSymbol += "S";break;
                case 19: OutSymbol += "T";break;
                case 20: OutSymbol += "U";break;
                case 21: OutSymbol += "V";break;
                case 22: OutSymbol += "W";break;
                case 23: OutSymbol += "X";break;
                case 24: OutSymbol += "Y";break;
                }                         
        return OutSymbol;                 
        }                                 
                                          






//---------------------------------------------------------------------------
void __fastcall TForm3::BCOMBClick(TObject *Sender)
{
if( ListBox1->ItemIndex < 0 )
        return;
if (ListBox2->Selected[ListBox1->ItemIndex])
        {
        ShowMessage("  Select two different parts!");
        return;
        }
if (gLocked)
        return;
gLocked = true;
AnsiString Component =  ListBox1->Items->operator [](ListBox1->ItemIndex);
char DATTM[80];
time_t rawtime;
struct tm * timeinfo;
time ( &rawtime );
timeinfo = localtime ( &rawtime );
strftime (DATTM,80,"_ID%H%M%S",timeinfo);
AnsiString TimeStr = DATTM;
//
AnsiString A;
long n_pins = 0;
long NUM = 0;
Form3->ListBox1->Items->Clear();
Form3->ListBox2->CopySelection(Form3->ListBox1);
Form3->ListBox2->Items->Clear();
try     {
        PART = new(std::nothrow) TypeDefPart[Form3->ListBox1->Count+1];    //
        }
catch(std::bad_alloc)
        {
        ShowMessage("    ������ ��������� ������: TypeDefPart[" + AnsiString(Form3->ListBox1->Count) + "]!" );
        exit(0);
        }
n = Form1->ListBox6->Items->IndexOf(Component);
if (n != -1)
        {
        m = prob(Component,1);
        PART[0].RefText = Component.SubString(m,(Component.Length()-m+1));
        }
else    ShowMessage ("    Fatal error: String " + Component + " not found!");
n++;
UnitsC = "NM";
Application->ProcessMessages();
while(1){
        A = Form1->ListBox6->Items->operator [](n);
        if ((A.SubString(1,4) == "part")||(A.SubString(1,6) == "[nets]"))
                {
                Application->ProcessMessages();
                NUM++;
                if (NUM > Form3->ListBox1->Count) break;
                AnsiString Comp = Form3->ListBox1->Items->operator [](NUM-1);
                n = Form1->ListBox6->Items->IndexOf(Comp);
                if (n != -1)
                        {
                        m = prob(Comp,1);
                        PART[NUM].RefText = Comp.SubString(m,(Comp.Length()-m+1));
                        }
                else    ShowMessage ("    Fatal error: String " + Comp + " not found!");
                n++;
                continue;
                }
        if (A.SubString(1,3) == "ref")
                {
                PART[NUM].RefVisible = 1;
                m = prob(A,1);
                PART[NUM].RefHeight =       ex_float_NM(A,&m,&UnitsC);
                PART[NUM].RefWidth =        ex_float_NM(A,&m,&UnitsC);
                PART[NUM].RefAngle =        ex_float_NM(A,&m,&NO_UNITS);
                PART[NUM].RefX =            ex_float_NM(A,&m,&UnitsC);
                PART[NUM].RefY =            ex_float_NM(A,&m,&UnitsC);
                PART[NUM].RefVisible =      ex_float_NM(A,&m,&NO_UNITS);
                }
        else if (A.SubString(1,5) == "value")
                {
                PART[NUM].ValueVisible = 1;
                m = prob(A,1);
                PART[NUM].ValueText =       ex_str(A,&m);
                PART[NUM].ValueHeight =     ex_float_NM(A,&m,&UnitsC);
                PART[NUM].ValueWidth =      ex_float_NM(A,&m,&UnitsC);
                PART[NUM].ValueAngle =      ex_float_NM(A,&m,&NO_UNITS);
                PART[NUM].ValueX =          ex_float_NM(A,&m,&UnitsC);
                PART[NUM].ValueY =          ex_float_NM(A,&m,&UnitsC);
                PART[NUM].ValueVisible =    ex_float_NM(A,&m,&NO_UNITS);
                }
        else if (A.SubString(1,5) == "shape")
                {
                m = prob(A,1);
                PART[NUM].Shape =   ex_str(A,&m);
                }
        else if (A.SubString(1,7) == "package")
                {
                m = prob(A,1);
                PART[NUM].Package = ex_str(A,&m);
                }
        else if (A.SubString(1,3) == "pos")
                {
                m = prob(A,1);
                PART[NUM].PosX =    ex_float_NM(A,&m,&UnitsC);
                PART[NUM].PosY =    ex_float_NM(A,&m,&UnitsC);
                PART[NUM].Side =    ex_float_NM(A,&m,&NO_UNITS);
                PART[NUM].Angle =   ex_float_NM(A,&m,&NO_UNITS);
                PART[NUM].Glueds =  ex_float_NM(A,&m,&NO_UNITS);
                }
        n++;
        }
//
A = ExtractFilePath(Application->ExeName);
ofstream NewFoot  ((A + "Combine.txt").c_str());
n = Form1->ListBox6->Items->IndexOf(("name: \"" + PART[0].Shape + "\""));
A = Form1->ListBox6->Items->operator [](n);
n++;
NUM = 0;
TRect SELRECT;
SELRECT.Left =          DEFAULT;
SELRECT.Bottom =        DEFAULT;
SELRECT.Right =         -DEFAULT;
SELRECT.Top =           -DEFAULT;
NewFoot << ("name: \"" + PART[0].Shape + TimeStr + "\"").c_str() << endl;
//
//======= texts ======
Application->ProcessMessages();
while (1)
        {
        A = Form1->ListBox6->Items->operator [](n);
        if ((A.SubString(1,5) == "name:")||(A.SubString(1,7)=="[board]"))
                {
                Application->ProcessMessages();
                NUM++;
                if (NUM > Form3->ListBox1->Count) break;
                n = Form1->ListBox6->Items->IndexOf(("name: \"" + PART[NUM].Shape + "\""));
                n++;
                continue;
                }
        //
        if (!A.Length()){;}
        else if (A.SubString(1,3) == "pin")     {;}
        else if (A.SubString(1,3) == "top")     {;}
        else if (A.SubString(1,3) == "inn")     {;}
        else if (A.SubString(1,3) == "bot")     {;}
        else if (A.SubString(1,3) == "out")     {;}
        else if (A.SubString(1,3) == "nex")     {;}
        else if (A.SubString(1,3) == "clo")     {;}
        else if (A.SubString(1,3) == "out")     {;}
        //
        else if (A.SubString(1,5) == "units")
                {
                m = prob(A,1);
                UnitsC = A.SubString(m,(A.Length()-m+1));
                if (NUM == 0)
                        NewFoot << "units: NM" << endl;
                }
        else if (A.SubString(1,6) == "n_pins")
                {
                m = prob(A,1);
                n_pins +=  ex_float_NM(A,&m,&NO_UNITS);
                }
        else if (A.SubString(1,8) == "sel_rect")
                {
                m = prob(A,1);
                double X1;
                double Y1;
                double X2;
                double Y2;
                X1 = ex_float_NM(A,&m,&UnitsC);
                Y1 = ex_float_NM(A,&m,&UnitsC);
                X2 = ex_float_NM(A,&m,&UnitsC);
                Y2 = ex_float_NM(A,&m,&UnitsC);
                mirror_angle(PART[NUM].Angle, PART[NUM].Side, &X1, &Y1);
                mirror_angle(PART[NUM].Angle, PART[NUM].Side, &X2, &Y2);
                X1 = X1 + PART[NUM].PosX - PART[0].PosX;
                Y1 = Y1 + PART[NUM].PosY - PART[0].PosY;
                X2 = X2 + PART[NUM].PosX - PART[0].PosX;
                Y2 = Y2 + PART[NUM].PosY - PART[0].PosY;
                SELRECT.Left =          MIN3(X1,X2,SELRECT.Left);
                SELRECT.Bottom =        MIN3(Y1,Y2,SELRECT.Bottom);
                SELRECT.Right =         MAX3(X1,X2,SELRECT.Right);
                SELRECT.Top =           MAX3(Y1,Y2,SELRECT.Top);
                }
        else if (A.SubString(1,8) == "ref_text")
                {
                if (NUM == 0)
                        {
                        m = prob(A,1);
                        long RH =       ex_float_NM(A,&m,&UnitsC);
                        double RX =     ex_float_NM(A,&m,&UnitsC);
                        double RY =     ex_float_NM(A,&m,&UnitsC);
                        long RA =       ex_float_NM(A,&m,&NO_UNITS);
                        long RW =       ex_float_NM(A,&m,&UnitsC);
                        mirror_angle(PART[0].Angle, PART[0].Side, &RX, &RY);
                        RA += PART[0].Angle;
                        if (RA >= 360) RA -= 360;
                        //
                        if (PART[0].Side)
                                {
                                float L = TextLength("REF");
                                if      (RA == 0)       RX = RX - (float)RH/(float)MLN*L;
                                else if (RA == 90)      RY = RY + (float)RH/(float)MLN*L;
                                else if (RA == 180)     RX = RX + (float)RH/(float)MLN*L;
                                else if (RA == 270)     RY = RY - (float)RH/(float)MLN*L;
                                }
                        //
                        NewFoot << "ref_text: " ;
                        NewFoot << RH;
                        NewFoot << " ";
                        NewFoot << AnsiString((long)RX).c_str();
                        NewFoot << " ";
                        NewFoot << AnsiString((long)RY).c_str();
                        NewFoot << " ";
                        NewFoot << RA;
                        NewFoot << " ";
                        NewFoot << RW;
                        NewFoot << endl;
                        }
                }
        else if (A.SubString(1,5) == "value")
                {
                if (NUM == 0)
                        {
                        m = prob(A,1);
                        long VH =       ex_float_NM(A,&m,&UnitsC);
                        double VX =     ex_float_NM(A,&m,&UnitsC);
                        double VY =     ex_float_NM(A,&m,&UnitsC);
                        long VA =       ex_float_NM(A,&m,&NO_UNITS);
                        long VW =       ex_float_NM(A,&m,&UnitsC);
                        mirror_angle(PART[0].Angle, PART[0].Side, &VX, &VY);
                        VA += PART[0].Angle;
                        if (VA >= 360) VA -= 360;
                        //
                        if (PART[0].Side)
                                {
                                float L = TextLength("VALUE");
                                if      (VA == 0)       VX = VX - (float)VH/(float)MLN*L;
                                else if (VA == 90)      VY = VY + (float)VH/(float)MLN*L;
                                else if (VA == 180)     VX = VX + (float)VH/(float)MLN*L;
                                else if (VA == 270)     VY = VY - (float)VH/(float)MLN*L;
                                }
                        //
                        NewFoot << "value_text: " ;
                        NewFoot << VH;
                        NewFoot << " ";
                        NewFoot << AnsiString((long)VX).c_str();
                        NewFoot << " ";
                        NewFoot << AnsiString((long)VY).c_str();
                        NewFoot << " ";
                        NewFoot << VA;
                        NewFoot << " ";
                        NewFoot << VW;
                        NewFoot << endl;
                        }
                }
        else if (A.SubString(1,8) == "adhesive")
                {
                if (NUM == 0)
                        {
                        m = prob(A,1);
                        long P1 =       ex_float_NM(A,&m,&NO_UNITS);
                        long P2 =       ex_float_NM(A,&m,&UnitsC);
                        double AX =     ex_float_NM(A,&m,&UnitsC);
                        double AY =     ex_float_NM(A,&m,&UnitsC);
                        mirror_angle(PART[0].Angle, PART[0].Side, &AX, &AY);
                        NewFoot << "adhesive: " ;
                        NewFoot << AnsiString(P1).c_str();
                        NewFoot << " ";
                        NewFoot << AnsiString(P2).c_str();
                        NewFoot << " ";
                        NewFoot << AnsiString((long)AX).c_str();
                        NewFoot << " ";
                        NewFoot << AnsiString((long)AY).c_str();
                        NewFoot << endl;
                        }
                }
        else if (A.SubString(1,4) == "text")
                {
                TypeDefText TEXT;
                m = prob(A,1);
                TEXT.TextString =       ex_str(A,&m);
                TEXT.H =                ex_float_NM(A,&m,&UnitsC);
                TEXT.X =                ex_float_NM(A,&m,&UnitsC);
                TEXT.Y =                ex_float_NM(A,&m,&UnitsC);
                TEXT.Angle =            ex_float_NM(A,&m,&NO_UNITS);
                TEXT.W =                ex_float_NM(A,&m,&UnitsC);
                TEXT.Mirror =           ex_float_NM(A,&m,&NO_UNITS);
                TEXT.Layer =            ex_float_NM(A,&m,&NO_UNITS);
                double X = TEXT.X;
                double Y = TEXT.Y;
                mirror_angle(PART[NUM].Angle, PART[NUM].Side, &X, &Y);
                TEXT.X = X;
                TEXT.Y = Y;
                //
                if (!PART[NUM].Side)
                        {
                        TEXT.Angle += PART[NUM].Angle;
                        if (TEXT.Angle >= 360) TEXT.Angle -= 360;
                        }
                else    {
                        TEXT.Angle -= PART[NUM].Angle;
                        if (TEXT.Angle < 0) TEXT.Angle += 360;
                        if ( TEXT.Angle%90 == 0 && TEXT.Angle%180 )
                                {
                                TEXT.Angle += 180;
                                if (TEXT.Angle >= 360) TEXT.Angle -= 360;
                                }
                        float L = TextLength(TEXT.TextString);
                        if      (TEXT.Angle == 0)       TEXT.X = TEXT.X - (float)TEXT.H/(float)MLN*L;
                        else if (TEXT.Angle == 90)      TEXT.Y = TEXT.Y + (float)TEXT.H/(float)MLN*L;
                        else if (TEXT.Angle == 180)     TEXT.X = TEXT.X + (float)TEXT.H/(float)MLN*L;
                        else if (TEXT.Angle == 270)     TEXT.Y = TEXT.Y - (float)TEXT.H/(float)MLN*L;
                        }
                //
                NewFoot << "text: \"" ;
                NewFoot << TEXT.TextString.c_str();
                NewFoot << "\" ";
                NewFoot << TEXT.H;
                NewFoot << " ";
                NewFoot << AnsiString(TEXT.X + PART[NUM].PosX - PART[0].PosX).c_str();
                NewFoot << " ";
                NewFoot << AnsiString(TEXT.Y + PART[NUM].PosY - PART[0].PosY).c_str();
                NewFoot << " ";
                NewFoot << TEXT.Angle;
                NewFoot << " ";
                NewFoot << TEXT.W;
                NewFoot << " ";
                NewFoot << TEXT.Mirror;
                NewFoot << " ";
                NewFoot << TEXT.Layer;
                NewFoot << endl;
                }
        else    {
                if (NUM == 0) NewFoot << A.c_str() << endl;
                }
        n++;
        }
//======= add references ======
double XR;
double YR;
for (NUM = 1; NUM <= Form3->ListBox1->Count; NUM++)
        {
        if ((PART[NUM].RefVisible && Form3->Def->Checked) || (Form3->Ref->Checked))
                {
                NewFoot << "text: \"" ;
                NewFoot << PART[NUM].RefText .c_str();
                NewFoot << "\" ";
                NewFoot << PART[NUM].RefHeight;
                NewFoot << " ";
                XR = PART[NUM].RefX;
                YR = PART[NUM].RefY;
                mirror_angle(PART[NUM].Angle, PART[NUM].Side, &XR, &YR);
                if (!PART[NUM].Side)
                        {
                        PART[NUM].RefAngle += PART[NUM].Angle;
                        if (PART[NUM].RefAngle >= 360)
                                PART[NUM].RefAngle -= 360;
                        }
                else    {
                        PART[NUM].RefAngle -= PART[NUM].Angle;
                        if (PART[NUM].RefAngle < 0)
                                PART[NUM].RefAngle += 360;
                        if ( PART[NUM].RefAngle%90 == 0 && PART[NUM].RefAngle%180 )
                                {
                                PART[NUM].RefAngle += 180;
                                if (PART[NUM].RefAngle >= 360)
                                        PART[NUM].RefAngle -= 360;
                                }
                        float L = TextLength(PART[NUM].RefText);
                        if      (PART[NUM].RefAngle == 0)
                                XR = XR - (float)PART[NUM].RefHeight/(float)MLN*L;
                        else if (PART[NUM].RefAngle == 90)
                                YR = YR + (float)PART[NUM].RefHeight/(float)MLN*L;
                        else if (PART[NUM].RefAngle == 180)
                                XR = XR + (float)PART[NUM].RefHeight/(float)MLN*L;
                        else if (PART[NUM].RefAngle == 270)
                                YR = YR - (float)PART[NUM].RefHeight/(float)MLN*L;
                        }
                NewFoot << AnsiString((long)XR + PART[NUM].PosX - PART[0].PosX).c_str();
                NewFoot << " ";
                NewFoot << AnsiString((long)YR + PART[NUM].PosY - PART[0].PosY).c_str();
                NewFoot << " ";
                NewFoot << PART[NUM].RefAngle;
                NewFoot << " ";
                NewFoot << PART[NUM].RefWidth;
                NewFoot << " 0 4";
                NewFoot << endl;
                }
        if ((PART[NUM].ValueVisible && Form3->Def->Checked) || (Form3->Val->Checked))
        if ( PART[NUM].ValueText.Length() )
                {
                NewFoot << "text: \"" ;
                NewFoot << PART[NUM].ValueText .c_str();
                NewFoot << "\" ";
                NewFoot << PART[NUM].ValueHeight;
                NewFoot << " ";
                XR = PART[NUM].ValueX;
                YR = PART[NUM].ValueY;
                mirror_angle(PART[NUM].Angle, PART[NUM].Side, &XR, &YR);
                if (!PART[NUM].Side)
                        {
                        PART[NUM].ValueAngle += PART[NUM].Angle;
                        if (PART[NUM].ValueAngle >= 360) PART[NUM].ValueAngle -= 360;
                        }
                else    {
                        PART[NUM].ValueAngle -= PART[NUM].Angle;
                        if (PART[NUM].ValueAngle < 0) PART[NUM].ValueAngle += 360;
                        if (PART[NUM].ValueAngle%90 == 0 && PART[NUM].ValueAngle%180)
                                {
                                PART[NUM].ValueAngle += 180;
                                if (PART[NUM].ValueAngle >= 360) PART[NUM].ValueAngle -= 360;
                                }
                        float L = TextLength(PART[NUM].ValueText);
                        if      (PART[NUM].ValueAngle == 0)       XR = XR - (float)PART[NUM].ValueHeight/(float)MLN*L;
                        else if (PART[NUM].ValueAngle == 90)      YR = YR + (float)PART[NUM].ValueHeight/(float)MLN*L;
                        else if (PART[NUM].ValueAngle == 180)     XR = XR + (float)PART[NUM].ValueHeight/(float)MLN*L;
                        else if (PART[NUM].ValueAngle == 270)     YR = YR - (float)PART[NUM].ValueHeight/(float)MLN*L;
                        }
                NewFoot << AnsiString((long)XR + PART[NUM].PosX - PART[0].PosX).c_str();
                NewFoot << " ";
                NewFoot << AnsiString((long)YR + PART[NUM].PosY - PART[0].PosY).c_str();
                NewFoot << " ";
                NewFoot << PART[NUM].ValueAngle;
                NewFoot << " ";
                NewFoot << PART[NUM].ValueWidth;
                NewFoot << " 0 4";
                NewFoot << endl;
                }
        }
//======= outlines ======
Application->ProcessMessages();
n = Form1->ListBox6->Items->IndexOf(("name: \"" + PART[0].Shape + "\""));
A = Form1->ListBox6->Items->operator [](n);
n++;
NUM = 0;
while (1)
        {
        A = Form1->ListBox6->Items->operator [](n);
        if ((A.SubString(1,5) == "name:")||(A.SubString(1,7)=="[board]"))
                {
                Application->ProcessMessages();
                NUM++;
                if (NUM > Form3->ListBox1->Count) break;
                n = Form1->ListBox6->Items->IndexOf(("name: \"" + PART[NUM].Shape + "\""));
                n++;
                continue;
                }
        //
        if (!A.Length()){;}
        else if (A.SubString(1,5) == "units")
                {
                m = prob(A,1);
                UnitsC = A.SubString(m,(A.Length()-m+1));
                }
        else if (A.SubString(1,7) == "outline")
                {
                m = prob(A,1);
                double W =      ex_float_NM(A,&m,&UnitsC);
                double X =      ex_float_NM(A,&m,&UnitsC);
                double Y =      ex_float_NM(A,&m,&UnitsC);
                long vis=0, htch=0, lay=0;
                if( m > 0 )
                        vis =   ex_float_NM(A,&m,&NO_UNITS);
                if( m > 0 )
                        htch =  ex_float_NM(A,&m,&NO_UNITS);
                if( m > 0 )
                        lay =   ex_float_NM(A,&m,&NO_UNITS);
                mirror_angle(PART[NUM].Angle, PART[NUM].Side, &X, &Y);
                NewFoot << "outline_polyline: " ;
                NewFoot << (long)W;
                NewFoot << " ";
                NewFoot << AnsiString((long)X + PART[NUM].PosX - PART[0].PosX).c_str();
                NewFoot << " ";
                NewFoot << AnsiString((long)Y + PART[NUM].PosY - PART[0].PosY).c_str();
                NewFoot << " ";
                NewFoot << AnsiString(vis).c_str();
                NewFoot << " ";
                NewFoot << AnsiString(htch).c_str();
                NewFoot << " ";
                NewFoot << AnsiString(lay).c_str();
                NewFoot << endl;
                }
        else if (A.SubString(1,4) == "next")
                {
                m = prob(A,1);
                double X =      ex_float_NM(A,&m,&UnitsC);
                double Y =      ex_float_NM(A,&m,&UnitsC);
                long type =     ex_float_NM(A,&m,&NO_UNITS);
                mirror_angle(PART[NUM].Angle, PART[NUM].Side, &X, &Y);
                NewFoot << "next_corner: " ;
                NewFoot << AnsiString((long)X + PART[NUM].PosX - PART[0].PosX).c_str();
                NewFoot << " ";
                NewFoot << AnsiString((long)Y + PART[NUM].PosY - PART[0].PosY).c_str();
                NewFoot << " ";
                if (type == 1 && PART[NUM].Side )       NewFoot << "2" << endl;
                else if (type == 2 && PART[NUM].Side )  NewFoot << "1" << endl;
                else    NewFoot << type << endl;
                }
        else if (A.SubString(1,5) == "close")
                {
                m = prob(A,1);
                long type =     ex_float_NM(A,&m,&NO_UNITS);
                if (type == 1 && PART[NUM].Side )       NewFoot << "close_polyline: 2" << endl;
                else if (type == 2 && PART[NUM].Side )  NewFoot << "close_polyline: 1" << endl;
                else    NewFoot << A.c_str() << endl;
                }
        n++;
        }
//
//======= pins ======
Application->ProcessMessages();
Form3->ListBox2->Sorted = false;
n = Form1->ListBox6->Items->IndexOf(("name: \"" + PART[0].Shape + "\""));
A = Form1->ListBox6->Items->operator [](n);
n++;
NUM = 0;
NewFoot << "n_pins: " ;
NewFoot << AnsiString(n_pins).c_str() << endl;
int MaxNumPin = 0;
int cnt_pins = 0;
while (1)
        {
        A = Form1->ListBox6->Items->operator [](n);
        if ((A.SubString(1,5) == "name:")||(A.SubString(1,7)=="[board]"))
                {
                Application->ProcessMessages();
                NUM++;
                if (NUM > Form3->ListBox1->Count) break;
                n = Form1->ListBox6->Items->IndexOf(("name: \"" + PART[NUM].Shape + "\""));
                n++;
                continue;
                }
        //
        if      (!A.Length()){;}
        else if (A.SubString(1,5) == "units")
                {
                m = prob(A,1);
                UnitsC = A.SubString(m,(A.Length()-m+1));
                }
        else if (A.SubString(1,6) == "n_pins")
                {
                m = prob(A,1);
                cnt_pins =  ex_float_NM(A,&m,&NO_UNITS);
                }
        else if (A.SubString(1,3) == "pin")
                {
                m = prob(A,1);
                AnsiString PName =      ex_str(A,&m);
                Form3->ListBox2->Items->Add(PART[NUM].RefText + "." + PName);
                if (Form3->RadioButton1->Checked) PName = Symbol(NUM) + PName;
                else if (Form3->RadioButton2->Checked)
                        {
                        if (NUM){
                                MaxNumPin++;
                                PName = AnsiString(MaxNumPin);
                                }
                        else    {
                                long t = 1;
                                int pin = ex_float_NM(PName, &t, &NO_UNITS);
                                MaxNumPin = MAX3( pin, MaxNumPin, cnt_pins );
                                }
                        }
                else    PName = PART[NUM].RefText + "_" + PName;
                Form3->ListBox2->Items->Add(PName);
                long PH =               ex_float_NM(A,&m,&UnitsC);
                double PX =             ex_float_NM(A,&m,&UnitsC);
                double PY =             ex_float_NM(A,&m,&UnitsC);
                long PA =               ex_float_NM(A,&m,&NO_UNITS);
                AnsiString Pdsc = "";
                if( m > 0 )
                        Pdsc = ex_str(A,&m);
                mirror_angle(PART[NUM].Angle, PART[NUM].Side, &PX, &PY);
                PA += PART[NUM].Angle;
                if (PA >= 360) PA -= 360;
                NewFoot << "pin: \"" ;
                NewFoot << PName.c_str();
                NewFoot << "\" ";
                NewFoot << PH;
                NewFoot << " ";
                NewFoot << AnsiString((long)PX + PART[NUM].PosX - PART[0].PosX).c_str();
                NewFoot << " ";
                NewFoot << AnsiString((long)PY + PART[NUM].PosY - PART[0].PosY).c_str();
                NewFoot << " ";
                NewFoot << PA;
                NewFoot << " \"";
                NewFoot << Pdsc.c_str();
                NewFoot << "\"";
                NewFoot << endl;
                }
        else if (A.SubString(1,4) == "top_" || A.SubString(1,7) == "bottom_")
                {
                m = 0;
                m = prob(A,1);
                AnsiString  key = A.SubString(1,m-1);
                long pTYPE =            ex_float_NM(A,&m,&NO_UNITS);
                double pW =             ex_float_NM(A,&m,&UnitsC);
                double pH1 =            ex_float_NM(A,&m,&UnitsC);
                double pH2 =            ex_float_NM(A,&m,&UnitsC);
                double pR =             ex_float_NM(A,&m,&UnitsC);
                if (PART[NUM].Side)
                        {
                        if (A.SubString(1,7) == "top_pad")      key = "bottom_pad: ";
                        if (A.SubString(1,8) == "top_mask")     key = "bottom_mask: ";
                        if (A.SubString(1,9) == "top_paste")    key = "bottom_paste: ";
                        if (A.SubString(1,10) == "bottom_pad")      key = "top_pad: ";
                        if (A.SubString(1,11) == "bottom_mask")     key = "top_mask: ";
                        if (A.SubString(1,12) == "bottom_paste")    key = "top_paste: ";
                        }
                NewFoot << key.c_str();
                NewFoot << AnsiString(pTYPE).c_str();
                NewFoot << " ";
                NewFoot << AnsiString((long)pW).c_str();
                NewFoot << " ";
                NewFoot << AnsiString((long)pH1).c_str();
                NewFoot << " ";
                NewFoot << AnsiString((long)pH2).c_str();
                NewFoot << " ";
                NewFoot << AnsiString((long)pR).c_str();
                NewFoot << endl;
                }
        else if (A.SubString(1,5) == "inner")
                {
                NewFoot << A.c_str() << endl;
                }
        n++;
        }  
NewFoot << "end" << endl;
NewFoot.close();
Application->ProcessMessages();
Sleep(500);
A = ExtractFilePath(Application->ExeName);
ifstream RNewFoot ((A + "Combine.txt").c_str());
ofstream WNewFoot ((A + "Combine.fpl").c_str());
A = "";
char s[2501];
while (A.SubString(1,3) != "end" )
        {
        RNewFoot.getline(s,sizeof(s));
        A = s;
        A = A.Trim();
        if(A.Length() == 0 )
                break;
        if (A.SubString(1,5) == "units" )
                {
                WNewFoot << A.c_str() << endl;
                WNewFoot << "sel_rect: " ;
                WNewFoot << SELRECT.Left;
                WNewFoot << " ";
                WNewFoot << SELRECT.Bottom;
                WNewFoot << " ";
                WNewFoot << SELRECT.Right;
                WNewFoot << " ";
                WNewFoot << SELRECT.Top << endl;
                }
        else    WNewFoot << A.c_str() << endl;
        }
RNewFoot.close();
WNewFoot << "end" << endl;
WNewFoot.close();
Application->ProcessMessages();
Sleep(500);
A = ExtractFilePath(Application->ExeName);
if (Form3->CheckBox1->Checked)  A = FileName;
else                            A = A + "Combine.fpc";
ofstream Combine(A.c_str());
A = "";
bool Disabled = false;
bool ComponentFlag = false;
bool PartsFlag = false;
int in = -1;
while (A.SubString(1,5) != "[end]" )
        {
        in++;
        A = Form1->ListBox6->Items->operator [](in);
        if (A.SubString(1,7) == "[parts]" )
                {
                PartsFlag = true;
                }
        else if (A.SubString(1,6) == "[nets]" )
                {
                Disabled = false;
                ComponentFlag = false;
                }
        else if (A.SubString(1,12) == "[footprints]" )
                {
                AnsiString S = ExtractFilePath(Application->ExeName);
                ifstream RFoot  ((S + "Combine.fpl").c_str());
                Combine << endl;
                Combine << "[footprints]" << endl;
                S = "";
                while (S.SubString(1,3) != "end" )
                        {
                        Combine << S.c_str() << endl;
                        RFoot.getline(s,sizeof(s));
                        S = s;
                        }
                RFoot.close();
                Combine << endl;
                continue;
                }
        else if (A.SubString(1,5) == "part:" )
                {
                if (A.SubString(1,A.Length()) == Component.SubString(1,Component.Length()))     ComponentFlag = true;
                else                                                                            ComponentFlag = false;
                if (Form3->ListBox1->Items->IndexOf(A) != -1)   Disabled = true;
                else                                            Disabled = false;
                }
        else if (A.SubString(1,8) == "ref_text" && ComponentFlag )
                {
                Combine << "ref_text: " ;
                Combine << PART[0].RefHeight;
                Combine << " ";
                Combine << PART[0].RefWidth;
                Combine << " ";
                double XR = PART[0].RefX;
                double YR = PART[0].RefY;
                mirror_angle(PART[0].Angle, PART[0].Side, &XR, &YR);
                if (!PART[0].Side)
                        {
                        PART[0].RefAngle += PART[0].Angle;
                        if (PART[0].RefAngle >= 360) PART[0].RefAngle -= 360;
                        }
                else    {
                        PART[0].RefAngle -= PART[0].Angle;
                        if (PART[0].RefAngle < 0) PART[0].RefAngle += 360;
                        if (PART[0].RefAngle%90 == 0 && PART[0].RefAngle%180)
                                {
                                PART[0].RefAngle += 180;
                                if (PART[0].RefAngle >= 360) PART[0].RefAngle -= 360;
                                }
                        float L = TextLength(PART[0].RefText);
                        if      (PART[0].RefAngle == 0)       XR = XR - (float)PART[0].RefHeight/(float)MLN*L;
                        else if (PART[0].RefAngle == 90)      YR = YR + (float)PART[0].RefHeight/(float)MLN*L;
                        else if (PART[0].RefAngle == 180)     XR = XR + (float)PART[0].RefHeight/(float)MLN*L;
                        else if (PART[0].RefAngle == 270)     YR = YR - (float)PART[0].RefHeight/(float)MLN*L;

                        }
                Combine << PART[0].RefAngle;
                Combine << " ";
                Combine << AnsiString((long)XR).c_str();
                Combine << " ";
                Combine << AnsiString((long)YR).c_str();
                if ((PART[0].RefVisible && Form3->Def->Checked) || (Form3->Ref->Checked)) Combine << " 1";
                else Combine << " 0";
                Combine << endl;
                continue;
                }
        else if (A.SubString(1,5) == "value" && ComponentFlag )
                {
                Combine << "value: \"";
                Combine << PART[0].ValueText.c_str();
                Combine << "\" ";
                Combine << PART[0].ValueHeight;
                Combine << " ";
                Combine << PART[0].ValueWidth;
                Combine << " ";
                double XR = PART[0].ValueX;
                double YR = PART[0].ValueY;
                mirror_angle(PART[0].Angle, PART[0].Side, &XR, &YR);
                if (!PART[0].Side)
                        {
                        PART[0].ValueAngle += PART[0].Angle;
                        if (PART[0].ValueAngle >= 360) PART[0].ValueAngle -= 360;
                        }
                else    {
                        PART[0].ValueAngle -= PART[0].Angle;
                        if (PART[0].ValueAngle < 0) PART[0].ValueAngle += 360;
                        if (PART[0].ValueAngle%90 == 0 && PART[0].ValueAngle%180)
                                {
                                PART[0].ValueAngle += 180;
                                if (PART[0].ValueAngle >= 360) PART[0].ValueAngle -= 360;
                                }
                        float L = TextLength(PART[0].ValueText);
                        if      (PART[0].ValueAngle == 0)       XR = XR - (float)PART[0].ValueHeight/(float)MLN*L;
                        else if (PART[0].ValueAngle == 90)      YR = YR + (float)PART[0].ValueHeight/(float)MLN*L;
                        else if (PART[0].ValueAngle == 180)     XR = XR + (float)PART[0].ValueHeight/(float)MLN*L;
                        else if (PART[0].ValueAngle == 270)     YR = YR - (float)PART[0].ValueHeight/(float)MLN*L;

                        }
                Combine << PART[0].ValueAngle;
                Combine << " ";
                Combine << AnsiString((long)XR).c_str();
                Combine << " ";
                Combine << AnsiString((long)YR).c_str();
                if ((PART[0].ValueVisible && Form3->Def->Checked) || (Form3->Val->Checked)) Combine << " 1";
                else Combine << " 0";
                Combine << endl;
                continue;
                }
        else if ((A.SubString(1,6) == "shape:" ) && (ComponentFlag) && (PartsFlag))
                {
                Combine << AnsiString("shape: \"" + PART[0].Shape + TimeStr + "\"").c_str() << endl;
                continue;
                }
        else if ((A.SubString(1,4) == "pos:" ) && (ComponentFlag) && (PartsFlag))
                {
                Combine << "pos: ";
                Combine << AnsiString(PART[0].PosX).c_str();
                Combine << " ";
                Combine << AnsiString(PART[0].PosY).c_str();
                Combine << " 0 0 1" << endl;
                continue;
                }
        else if ((A.SubString(1,4) == "pin:" ) && (PartsFlag))
                {
                m = prob(A,1);
                int PinIndex = ex_float_NM(A,&m,&NO_UNITS);
                n = m;
                while ((A.SubString(m,1) != ".")&&(m <= A.Length())) m++;
                AnsiString PartP = A.SubString(n,(m-n));
                AnsiString PinN = A.SubString((m+1),(A.Length()-m));
                int index = Form3->ListBox1->Items->IndexOf(("part: " + PartP));
                if ((index != -1) || (PartP.SubString(1,PartP.Length()) == PART[0].RefText.SubString(1,PART[0].RefText.Length())))
                        {
                        m = Form3->ListBox2->Items->IndexOf(PartP + "." + PinN);
                        if (m != -1) PinN = Form3->ListBox2->Items->operator [](m+1);
                        else    {
                                //ShowMessage("    Fatal error: pin " + PartP + "." + PinN + " not found!");
                                PinN = "NotFound_" + PinN;
                                }
                        Combine << ("pin: " + AnsiString(PinIndex) + " " + PART[0].RefText + "." + PinN).c_str() << endl;
                        continue;
                        }
                }
        //
        if (Disabled == 0)  Combine << A.c_str() << endl;
        }
Combine.close();
Application->ProcessMessages();
Sleep(500);
//
//-------------������ ------------
A = ExtractFilePath(Application->ExeName);
if (Form3->CheckBox1->Checked)  A = FileName;
else                            A = A + "Combine.fpc";
AnsiString fn = ExtractFilePath(Application->ExeName);
AnsiString B = A;
//
SHELLEXECUTEINFO info = {0};
fn.SetLength(fn.Length()-1);
fn = ExtractFilePath(fn);
fn.SetLength(fn.Length()-1);
fn = ExtractFilePath(fn) + "freepcb.exe";
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
delete[] PART;
Form3->Ini();
gLocked = false;
}
//---------------------------------------------------------------------------

void TForm3::Ini()
{
Form1->ListBox6->Sorted = false;
Form1->ListBox6->Clear();
Form3->ListBox1->Sorted = true;
Form3->ListBox1->Clear();
Form3->ListBox2->Sorted = true;
Form3->ListBox2->Clear();
ifstream RComb (FileName.c_str());
A = "";
char s[2501];
Application->ProcessMessages();
while(A.SubString(1,5) != "[end]" )
        {
        RComb.getline(s,2500);
        A = s;
        A = A.Trim();
        Form1->ListBox6->Items->Add(A);
        if (A.SubString(1,5) == "part:" )
                {
                Form3->ListBox1->Items->Add(A);
                Form3->ListBox2->Items->Add(A);
                }
        }
RComb.close();
}