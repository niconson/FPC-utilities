//---------------------------------------------------------------------------


#pragma hdrstop

#include "LoadArea.h"
#include "Debug_Areas.h"
#include "ProcessMessages.h"
#include "fstream.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)



int LoadArea (int ARC)
{
long MEM = Form3->Area->Items->Count;
//�������� ����������� ��������
if (LinesArea)  delete[] LinesArea;
try     {LinesArea = new(std::nothrow) MLine[MEM+1+ARC*20];}
catch(std::bad_alloc){ShowMessage("    Error of memory: Line[" + AnsiString(MEM+1+ARC*20) + "]!" );}
//
short int i;
float x1;
float y1;
float x2;
float y2;
float xF;
float yF;
int end = 0;
int Type = 0;
int currentcorner = 1;
int Lines = 0;
int NumFirst = 0;
bool Flag = false;
bool FlagBeginCutouts = false;
AreaRect.Left =        DEFAULT;
AreaRect.Bottom =      DEFAULT;
AreaRect.Right =      -DEFAULT;
AreaRect.Top =        -DEFAULT;
Form3->Area->Items->Add("Loading");
AnsiString A;
AnsiString S;
LinesCut[CountLinesCut].RST();
for (int CntL=0; CntL<MEM; CntL++ )
        {
        A = Form3->Area->Items->operator [](CntL);
        if (A.SubString(1,6) == "corner" )
                {
                if (end)
                        {
                        Flag = false;
                        x2 = xF;
                        y2 = yF;
                        if (Type)
                                {
                                float ARC[GEN_ARC_NUM_CORNERS*2];
                                int CLines = Generate_Line(x1,y1,x2,y2,Type,&ARC[0]);
                                i = 0;
                                AnsiString S;
                                while ((i+3) < CLines)
                                        {
                                        if (!FlagBeginCutouts)
                                                {
                                                LinesArea[Lines].X1 = ARC[i];
                                                i++;
                                                LinesArea[Lines].Y1 = ARC[i];
                                                i++;
                                                LinesArea[Lines].X2 = ARC[i];
                                                i++;
                                                LinesArea[Lines].Y2 = ARC[i];
                                                S = "corner: " + AnsiString(currentcorner) + " " + AnsiString((long)ARC[i-1]) + " " + AnsiString((long)ARC[i]) + " 0 0";
                                                i--;
                                                currentcorner++;
                                                Lines++;
                                                Form3->Area->Items->Add(S);
                                                }
                                        else    {
                                                LinesCut[CountLinesCut].FlagDelete = 0;
                                                LinesCut[CountLinesCut].FlagWrite = 0;
                                                LinesCut[CountLinesCut].First = NumFirst;
                                                LinesCut[CountLinesCut].X1 = ARC[i];
                                                LinesCut[NumFirst].Bounds =   MIN(ARC[i],LinesCut[NumFirst].Bounds);
                                                LinesCut[NumFirst+1].Bounds = MAX(ARC[i],LinesCut[NumFirst+1].Bounds);
                                                i++;
                                                LinesCut[CountLinesCut].Y1 = ARC[i];
                                                i++;
                                                LinesCut[CountLinesCut].X2 = ARC[i];
                                                i++;
                                                LinesCut[CountLinesCut].Y2 = ARC[i];
                                                i--;
                                                CountLinesCut++;
                                                LinesCut[CountLinesCut].RST();
                                                }
                                        }
                                }
                        else    {
                                if (!FlagBeginCutouts)
                                        {
                                        LinesArea[Lines].X1 = x1;
                                        LinesArea[Lines].Y1 = y1;
                                        LinesArea[Lines].X2 = x2;
                                        LinesArea[Lines].Y2 = y2;
                                        S = "corner: " + AnsiString(currentcorner) + " " + AnsiString((long)x2) + " " + AnsiString((long)y2) + " 0 1";
                                        currentcorner++;
                                        Lines++;
                                        Form3->Area->Items->Add(S);
                                        }
                                else    {
                                        LinesCut[CountLinesCut].FlagDelete = 0;
                                        LinesCut[CountLinesCut].FlagWrite = 0;
                                        LinesCut[CountLinesCut].First = NumFirst;
                                        LinesCut[CountLinesCut].X1 = x1;
                                        LinesCut[CountLinesCut].Y1 = y1;
                                        LinesCut[CountLinesCut].X2 = x2;
                                        LinesCut[CountLinesCut].Y2 = y2;
                                        CountLinesCut++;
                                        LinesCut[CountLinesCut].RST();
                                        LinesCut[NumFirst].Bounds =   MIN(x1,LinesCut[NumFirst].Bounds);
                                        LinesCut[NumFirst+1].Bounds = MAX(x1,LinesCut[NumFirst+1].Bounds);
                                        }
                                }
                        NumFirst = CountLinesCut;
                        LinesCut[NumFirst].Bounds =    DEFAULT;
                        LinesCut[NumFirst+1].Bounds = -DEFAULT;
                        FlagBeginCutouts = true;
                        }
                i = prob( A, 2);
                x2 = ex_float_NM( A, &i, -1);
                y2 = ex_float_NM( A, &i, -1);
                if (x2 < AreaRect.Left)         AreaRect.Left =         x2;
                if (x2 > AreaRect.Right)        AreaRect.Right =        x2;
                if (y2 < AreaRect.Bottom)       AreaRect.Bottom =       y2;
                if (y2 > AreaRect.Top)          AreaRect.Top =          y2;
                if (Flag)
                        {
                        if (Type)
                                {
                                float ARC[GEN_ARC_NUM_CORNERS*2];
                                int CLines = Generate_Line(x1,y1,x2,y2,Type,&ARC[0]);
                                i = 0;
                                AnsiString S;
                                while ((i+3) < CLines)
                                        {
                                        if (!FlagBeginCutouts)
                                                {
                                                LinesArea[Lines].X1 = ARC[i];
                                                i++;
                                                LinesArea[Lines].Y1 = ARC[i];
                                                i++;
                                                LinesArea[Lines].X2 = ARC[i];
                                                i++;
                                                LinesArea[Lines].Y2 = ARC[i];
                                                S = "corner: " + AnsiString(currentcorner) + " " + AnsiString((long)ARC[i-1]) + " " + AnsiString((long)ARC[i]) + " 0 0";
                                                i--;
                                                currentcorner++;
                                                Lines++;
                                                Form3->Area->Items->Add(S);
                                                }
                                        else    {
                                                LinesCut[CountLinesCut].FlagDelete = 0;
                                                LinesCut[CountLinesCut].FlagWrite = 0;
                                                LinesCut[CountLinesCut].First = NumFirst;
                                                LinesCut[CountLinesCut].X1 = ARC[i];
                                                LinesCut[NumFirst].Bounds =   MIN(ARC[i],LinesCut[NumFirst].Bounds);
                                                LinesCut[NumFirst+1].Bounds = MAX(ARC[i],LinesCut[NumFirst+1].Bounds);
                                                i++;
                                                LinesCut[CountLinesCut].Y1 = ARC[i];
                                                i++;
                                                LinesCut[CountLinesCut].X2 = ARC[i];
                                                i++;
                                                LinesCut[CountLinesCut].Y2 = ARC[i];
                                                i--;
                                                CountLinesCut++;
                                                LinesCut[CountLinesCut].RST();
                                                }
                                        }
                                }
                        else    {
                                if (!FlagBeginCutouts)
                                        {
                                        LinesArea[Lines].X1 = x1;
                                        LinesArea[Lines].Y1 = y1;
                                        LinesArea[Lines].X2 = x2;
                                        LinesArea[Lines].Y2 = y2;
                                        S = "corner: " + AnsiString(currentcorner) + " " + AnsiString((long)x2) + " " + AnsiString((long)y2) + " 0 0";
                                        currentcorner++;
                                        Lines++;
                                        Form3->Area->Items->Add(S);
                                        }
                                else    {
                                        LinesCut[CountLinesCut].FlagDelete = 0;
                                        LinesCut[CountLinesCut].FlagWrite = 0;
                                        LinesCut[CountLinesCut].First = NumFirst;
                                        LinesCut[CountLinesCut].X1 = x1;
                                        LinesCut[CountLinesCut].Y1 = y1;
                                        LinesCut[CountLinesCut].X2 = x2;
                                        LinesCut[CountLinesCut].Y2 = y2;
                                        CountLinesCut++;
                                        LinesCut[CountLinesCut].RST();
                                        LinesCut[NumFirst].Bounds =   MIN(x1,LinesCut[NumFirst].Bounds);
                                        LinesCut[NumFirst+1].Bounds = MAX(x1,LinesCut[NumFirst+1].Bounds);
                                        }
                                }
                        }
                else    {
                        xF = x2;
                        yF = y2;
                        Flag = true;
                        }
                i = prob( A, 4);
                Type = ex_float_NM( A, &i, -1);    // ��� �����
                end = ex_float_NM( A, &i, -1);
                x1 = x2;
                y1 = y2;
                }
        }
x2 = xF;
y2 = yF;
if (Flag)
        {
        if (Type)
                {
                float ARC[GEN_ARC_NUM_CORNERS*2];
                int CLines = Generate_Line(x1,y1,x2,y2,Type,&ARC[0]);
                i = 0;
                if (!FlagBeginCutouts)
                        {
                        while ((i+3) < CLines)
                                {
                                if (i)  {
                                        S += " 0";
                                        Form3->Area->Items->Add(S);
                                        }
                                LinesArea[Lines].X1 = ARC[i];
                                i++;
                                LinesArea[Lines].Y1 = ARC[i];
                                i++;
                                LinesArea[Lines].X2 = ARC[i];
                                S = "corner: " + AnsiString(currentcorner) + " " + AnsiString((long)ARC[i]);
                                i++;
                                LinesArea[Lines].Y2 = ARC[i];
                                S += " " + AnsiString((long)ARC[i]) + " 0";
                                i--;
                                currentcorner++;
                                Lines++;
                                }
                        S += " 1";
                        Form3->Area->Items->Add(S);
                        }
                else    {
                        while ((i+3) < CLines)
                                {
                                LinesCut[CountLinesCut].FlagDelete = 0;
                                LinesCut[CountLinesCut].FlagWrite = 0;
                                LinesCut[CountLinesCut].First = NumFirst;
                                LinesCut[CountLinesCut].X1 = ARC[i];
                                LinesCut[NumFirst].Bounds =   MIN(ARC[i],LinesCut[NumFirst].Bounds);
                                LinesCut[NumFirst+1].Bounds = MAX(ARC[i],LinesCut[NumFirst+1].Bounds);
                                i++;
                                LinesCut[CountLinesCut].Y1 = ARC[i];
                                i++;
                                LinesCut[CountLinesCut].X2 = ARC[i];
                                i++;
                                LinesCut[CountLinesCut].Y2 = ARC[i];
                                i--;
                                CountLinesCut++;
                                LinesCut[CountLinesCut].RST();
                                }
                        }
                }
        else    {
                Flag = false;
                if (!FlagBeginCutouts)
                        {
                        LinesArea[Lines].X1 = x1;
                        LinesArea[Lines].Y1 = y1;
                        LinesArea[Lines].X2 = x2;
                        LinesArea[Lines].Y2 = y2;
                        S = "corner: " + AnsiString(currentcorner) + " " + AnsiString((long)x2) + " " + AnsiString((long)y2) + " 0 1";
                        currentcorner++;
                        Lines++;
                        Form3->Area->Items->Add(S);
                        }
                else    {
                        LinesCut[CountLinesCut].FlagDelete = 0;
                        LinesCut[CountLinesCut].FlagWrite = 0;
                        LinesCut[CountLinesCut].First = NumFirst;
                        LinesCut[CountLinesCut].X1 = x1;
                        LinesCut[CountLinesCut].Y1 = y1;
                        LinesCut[CountLinesCut].X2 = x2;
                        LinesCut[CountLinesCut].Y2 = y2;
                        CountLinesCut++;
                        LinesCut[CountLinesCut].RST();
                        LinesCut[NumFirst].Bounds =   MIN(x1,LinesCut[NumFirst].Bounds);
                        LinesCut[NumFirst+1].Bounds = MAX(x1,LinesCut[NumFirst+1].Bounds);
                        }
                }
        }
LinesCut[CountLinesCut].First = CountLinesCut;
while (Form3->Area->Items->operator [](0) != "Loading") Form3->Area->Items->Delete(0);
Form3->Area->Items->Delete(0);
//REPOUR
if (Form1->repour->Checked && Form1->inv->Checked == 0)
        {
        Form3->Area->Items->Clear();
        S = "corner: 1 " + AnsiString(AreaRect.Left) + " " + AnsiString(AreaRect.Bottom) + " 0 0";
        Form3->Area->Items->Add(S);
        S = "corner: 2 " + AnsiString(AreaRect.Left) + " " + AnsiString(AreaRect.Top) + " 0 0";
        Form3->Area->Items->Add(S);
        S = "corner: 3 " + AnsiString(AreaRect.Right) + " " + AnsiString(AreaRect.Top) + " 0 0";
        Form3->Area->Items->Add(S);
        S = "corner: 4 " + AnsiString(AreaRect.Right) + " " + AnsiString(AreaRect.Bottom) + " 0 1";
        Form3->Area->Items->Add(S);

        LinesArea[0].X1 = AreaRect.Left;
        LinesArea[0].Y1 = AreaRect.Bottom;
        LinesArea[0].X2 = AreaRect.Left;
        LinesArea[0].Y2 = AreaRect.Top;

        LinesArea[1].X1 = AreaRect.Left;
        LinesArea[1].Y1 = AreaRect.Top;
        LinesArea[1].X2 = AreaRect.Right;
        LinesArea[1].Y2 = AreaRect.Top;

        LinesArea[2].X1 = AreaRect.Right;
        LinesArea[2].Y1 = AreaRect.Top;
        LinesArea[2].X2 = AreaRect.Right;
        LinesArea[2].Y2 = AreaRect.Bottom;

        LinesArea[3].X1 = AreaRect.Right;
        LinesArea[3].Y1 = AreaRect.Bottom;
        LinesArea[3].X2 = AreaRect.Left;
        LinesArea[3].Y2 = AreaRect.Bottom;
        CountLinesCut = 0;
        return 4;
        }
else return Lines;
}
