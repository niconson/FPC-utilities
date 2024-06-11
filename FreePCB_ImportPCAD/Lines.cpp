//---------------------------------------------------------------------------


#pragma hdrstop

#include "Lines.h"
#include "HEAD.h"
#include "LSTBXS.h"
#include "fstream.h"
#include "math.h"
#include "time.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
//------------------------------------------

//AnsiString *NETS;                       //GLOBAL   "netname";
PcbLine *LINES;                         //GLOBAL   format Lines[]: [X1; Y1; X2; Y2; Width; layerNumRef;]
AnsiString TRACE[20000];                //GLOBAL
AnsiString *Trassa;                     //GLOBAL
long trassa = 0;
long lns = 0;                           //GLOBAL   adres LINES
long index = 0;                         //GLOBAL   adres LINES
long Swell_Pads;                        //GLOBAL
long MEMORY;



//------------------------------------------
//        длина сегмента
//------------------------------------------
double Length_Line (double X1, double Y1, double X2, double Y2)
        {
        double dx = X2 - X1;
        double dy = Y2 - Y1;
        bool Flag = false;
        if ( abs(dx) > 30000 ) Flag = true;
        if ( abs(dy) > 30000 ) Flag = true;
        if (Flag) dx = dx/(double)100000;
        if (Flag) dy = dy/(double)100000;
        double len = pow(dx, 2) + pow(dy, 2);
        if (len) len = sqrt(len);
        if (Flag) len = len*(double)100000;
        return len;
        }




//------------------------------------------
//  WrSegment
//------------------------------------------
void WrSegment (long WrIndexViaInStringGrid,
                int *Wrtr,
                int *WrcountSeg,
                long Wrlayer,
                long WrW,
                long WrX,
                long WrY,
                bool Inc
                )
{
AnsiString PINorVIA = "";
int WVia = 0;
int HVia = 0;

if (WrIndexViaInStringGrid > 0)
        {
        PINorVIA = Form2->StringGrid1->Cells[0][WrIndexViaInStringGrid];
        if (PINorVIA.UpperCase().SubString(1,PINorVIA.Length()) == "VIA")
                {
                WrX =     StrToInt(Form2->StringGrid1->Cells[3][WrIndexViaInStringGrid]);
                WrY =     StrToInt(Form2->StringGrid1->Cells[4][WrIndexViaInStringGrid]);
                WVia =     StrToInt(Form2->StringGrid1->Cells[5][WrIndexViaInStringGrid]);
                HVia =     StrToInt(Form2->StringGrid1->Cells[6][WrIndexViaInStringGrid]);
                Form2->StringGrid1->Cells[0][WrIndexViaInStringGrid] = "ViaFind";
                }
        }
// записываем сегмент
TRACE[*Wrtr] = "seg: ";
TRACE[*Wrtr] += AnsiString(*WrcountSeg) + " ";
TRACE[*Wrtr] += AnsiString(Wrlayer) + " ";
TRACE[*Wrtr] += AnsiString(WrW) + " 0 0";
if (Inc)        (*Wrtr)++;
else            (*Wrtr)--;
(*WrcountSeg)++;
// записываем следующую точку
TRACE[*Wrtr] = "vtx: ";
TRACE[*Wrtr] += AnsiString(*WrcountSeg) + " ";
TRACE[*Wrtr] += AnsiString(WrX) + " " + AnsiString(WrY) + " ";
if ((PINorVIA.Length())&&(PINorVIA.UpperCase().SubString(1,PINorVIA.Length()) != "VIA"))
                        TRACE[*Wrtr] += AnsiString(Wrlayer);
else                    TRACE[*Wrtr] += AnsiString("0");
if (Wrlayer != 3)
        {
        if (WVia)       TRACE[*Wrtr] += " 1 ";
        else            TRACE[*Wrtr] += " 0 ";
        TRACE[*Wrtr] += AnsiString(WVia) + " " + AnsiString(HVia);
        TRACE[*Wrtr] += " 0";
        }
//
if (Inc)        (*Wrtr)++;
else            (*Wrtr)--;
}



//------------------------------------------
//        поиск STUB Trace
//------------------------------------------
int FindVertexOfTraceStub (long *X_1, long *Y_1, AnsiString NET, int LayerVertex, int StubViaWidth, int *STID, int numConnect)
        {
        static int STUB_ID = 5000;
        long i = 0;
        long n = 0;
        double WLine = 0;
        long Xback;
        long Yback;
        int CountSeg;
        int LayerSeg;
        int GetnumConnect=-1;
        AnsiString A;
        AnsiString NET2 = "";
        while (n < trassa)
                {
                A = Trassa[n];
                A = A.Trim();
                if (A.SubString(1,3) == "net" )
                        {
                        i = prob(A, 1);
                        NET2 = ex_str(A, &i);
                        }
                if (NET.SubString(1,NET.Length()) == NET2.SubString(1,NET2.Length()) )
                        {
                        if (A.SubString(1,3) == "vtx" && numConnect != GetnumConnect )
                                {
                                i = prob(A, 2);
                                long X = ex_float_NM (A, &i, -1);
                                long Y = ex_float_NM (A, &i, -1);
                                i = prob(A, 6);
                                long ViaWidth = ex_float_NM (A, &i, -1);
                                i = prob(A, 8);
                                long ReadStubID = 0;
                                if (i>0) ReadStubID = ex_float_NM (A, &i, -1);
                                double P1;
                                double P2;
                                double L = Length_Line ((double)X,(double)Y,(double)(*X_1),(double)(*Y_1));
                                double D = Distance((double)X,(double)Y,(double)Xback,(double)Yback,(double)(*X_1),(double)(*Y_1),2000000000,2000000000,&P1,&P2);
                                //
                                if (WLine)
                                        {
                                        if (ViaWidth)           WLine = ViaWidth;
                                        else if (StubViaWidth)  WLine = StubViaWidth;
                                        //
                                        if ((L < (WLine/2))||(D < (WLine/2)))
                                        if ((LayerSeg == LayerVertex)||(ViaWidth)||(StubViaWidth))
                                                {
                                                if (!ReadStubID)
                                                        {
                                                        Trassa[n] += AnsiString(STUB_ID);
                                                        *STID = STUB_ID;
                                                        STUB_ID += 10;
                                                        }
                                                else    {
                                                        *STID = ReadStubID;
                                                        }
                                                *X_1 = X;
                                                *Y_1 = Y;
                                                if (StubViaWidth)       return LayerSeg;
                                                else                    return LayerVertex;
                                                }
                                        }
                                Xback = X;
                                Yback = Y;
                                }
                        else if (A.SubString(1,3) == "seg" )
                                {
                                i = prob(A, 1);
                                long NumberSeg = ex_float_NM (A, &i, -1);
                                LayerSeg = ex_float_NM (A, &i, -1);
                                WLine = ex_float_NM (A, &i, -1);
                                if (NumberSeg == CountSeg)      WLine = 0;
                                }
                        else if (A.SubString(1,7) == "connect" )
                                {
                                i = prob(A, 1);
                                GetnumConnect = ex_float_NM (A, &i, -1);
                                WLine = 0;
                                Xback = 0;
                                Yback = 0;
                                i = prob(A, 4);
                                CountSeg = ex_float_NM (A, &i, -1);
                                }
                        }
                n++;
                }
        return 0;
        }






//------------------------------------------
//              ПОИСК ТОЧКИ
//------------------------------------------
int  FindNextPoint (    long X,
                        long Y,
                        AnsiString netName,
                        long layerNumRef,
                        long WLine,
                        bool *FlagIfEnd,
                        int *IndexViaStringGrid,
                        int *IndexPinStringGrid,
                        long *Len
                        )
        {
        // Find Via:
        *IndexViaStringGrid = 0;
        double LengthMin = SELR;
        int ind = 1;
        AnsiString PinN;
        AnsiString NetVia;
        if (layerNumRef > 2)
                if (layerNumRef < 12)
                        ind= Form2->StringGrid1->RowCount;
        //
        if (netName.SubString(1,9) != "noConnect" )
        while (ind < Form2->StringGrid1->RowCount)
                {
                NetVia = Form2->StringGrid1->Cells[2][ind];
                PinN = Form2->StringGrid1->Cells[0][ind];
                if (PinN.Length())
                if (netName.SubString(1,netName.Length()) == NetVia.SubString(1,NetVia.Length()))
                if (PinN.UpperCase().SubString(1,PinN.Length()) == "VIA")
                        {
                        long ViaX =  StrToInt(Form2->StringGrid1->Cells[3][ind]);
                        long ViaY =  StrToInt(Form2->StringGrid1->Cells[4][ind]);
                        long W = StrToInt(Form2->StringGrid1->Cells[5][ind]);
                        double LengthV = Length_Line((double)ViaX, (double)ViaY, (double)X, (double)Y);
                        if (LengthV < LengthMin)
                        if (LengthV < (W/2+WLine/2))
                                {
                                LengthMin = LengthV;
                                *IndexViaStringGrid = ind;
                                }
                        }
                ind++;
                }

        // Find Pin:
        *IndexPinStringGrid = 0;
        int CountListBox = Form2->StringGrid1->RowCount;
        ind = 1;
        LengthMin = SELR;
        AnsiString Net;
        int COL = 5;
        if (layerNumRef == 1)           COL += 0;
        else if (layerNumRef == 2)      COL += 4;
        else if (layerNumRef > 11)      COL += 8;
        else ind = CountListBox;
        if (netName.SubString(1,9) != "noConnect" )
        while (ind < CountListBox)
                {
                Net = Form2->StringGrid1->Cells[2][ind];
                PinN = Form2->StringGrid1->Cells[0][ind];
                if (PinN.Length())
                if (PinN.UpperCase().SubString(1,PinN.Length()) != "VIA")
                if (PinN.UpperCase().SubString(1,PinN.Length()) != "VIAFIND")
                if (Net.SubString(1,Net.Length()) == netName.SubString(1,netName.Length()))
                        {
                        long P1 = StrToInt(Form2->StringGrid1->Cells[COL][ind]);
                        long P2 = StrToInt(Form2->StringGrid1->Cells[COL+1][ind]);
                        long P3 = StrToInt(Form2->StringGrid1->Cells[COL+2][ind]);
                        long P4 = StrToInt(Form2->StringGrid1->Cells[COL+3][ind]);
                        long PinX =  StrToInt(Form2->StringGrid1->Cells[3][ind]);
                        long PinY =  StrToInt(Form2->StringGrid1->Cells[4][ind]);
                        double Length = Length_Line((double)PinX, (double)PinY, (double)X, (double)Y);
                        if (Length < LengthMin)
                        if ((X > P1)&&(X < P3)&&(Y > P2)&&(Y < P4))
                                {
                                LengthMin = Length;
                                *IndexPinStringGrid = ind;
                                }
                        }
                ind++;
                }
        if (*IndexPinStringGrid)
                {
                *FlagIfEnd = true;
                return 0;
                }

        // Find Line:
        long INDEX = -1;
        long LengMin = 10000000;
        int RETURN = 0;
        index = -1;   //GLOBAL
        while (index < (lns-1))
                {
                index++;
                if (LINES[index].Net.SubString(1,5) == "#DEL#" ) continue;
                if (LINES[index].Layer > 27)
                        {
                        LINES[index].Net = "#DEL#";
                        FlagWarning1 = true;
                        continue;
                        }
                if (netName.SubString(1,netName.Length()) == LINES[index].Net.SubString(1,LINES[index].Net.Length()))
                        {
                        // извлекаем параметры линии
                        long Leng1 = ( long)Length_Line (       (double)LINES[index].X1,
                                                                (double)LINES[index].Y1,
                                                                (double)X,
                                                                (double)Y);
                        // извлекаем параметры линии
                        long Leng2 = ( long)Length_Line (       (double)LINES[index].X2,
                                                                (double)LINES[index].Y2,
                                                                (double)X,
                                                                (double)Y);
                        int SegmentLayer = LINES[index].Layer;
                        //
                        if (*IndexViaStringGrid)
                                {
                                long ViaX =  StrToInt(Form2->StringGrid1->Cells[3][*IndexViaStringGrid]);
                                long ViaY =  StrToInt(Form2->StringGrid1->Cells[4][*IndexViaStringGrid]);
                                long W = StrToInt(Form2->StringGrid1->Cells[5][*IndexViaStringGrid]);
                                double LengthL1 = Length_Line((double)ViaX, (double)ViaY, (double)LINES[index].X1, (double)LINES[index].Y1);
                                double LengthL2 = Length_Line((double)ViaX, (double)ViaY, (double)LINES[index].X2, (double)LINES[index].Y2);
                                //
                                if ((LengthL1 < ((double)W/2 + LINES[index].Width/2))&&(LengthL2 < ((double)W/2 + LINES[index].Width/2)))
                                        {
                                        LINES[index].Net = "#DEL#";
                                        continue;
                                        }
                                else if (LengthL1 < ((double)W/2 + LINES[index].Width/2))
                                        {
                                        if (LengthL1 < LengthL2)
                                        if (Leng1 < LengthMin)
                                                {
                                                LengMin = Leng1;
                                                RETURN = 2;
                                                INDEX = index;
                                                }
                                        }
                                else if (LengthL2 < ((double)W/2 + LINES[index].Width/2))
                                        {
                                        if (Leng2 < LengthMin)
                                                {
                                                LengMin = Leng2;
                                                RETURN = 0;
                                                INDEX = index;
                                                }
                                        }
                                }
                        else    {
                                if (SegmentLayer == layerNumRef)
                                if      ((Leng1 < ((LINES[index].Width)/2 + WLine/2))&&(Leng1 < Leng2))
                                        {
                                        if (Leng1 < LengMin)
                                                {
                                                LengMin = Leng1;
                                                RETURN = 2;
                                                INDEX = index;
                                                }
                                        }
                                else if (Leng2 < ((LINES[index].Width)/2 + WLine/2))
                                        {
                                        if (Leng2 < LengMin)
                                                {
                                                LengMin = Leng2;
                                                RETURN = 0;
                                                INDEX = index;
                                                }
                                        }
                                }
                        }
                }
        if (INDEX >= 0)
                {
                index = INDEX;
                *Len = LengMin;
                return RETURN;
                }
        *FlagIfEnd = true;
        return 0;
        }
//******************************************************************************


//------------------------------------------
//Lines * Lines * Lines * Lines * Lines//
//------------------------------------------
void Lines (AnsiString OpenD, long CNT, long MEM)
{
Swell_Pads = SELR;
long i = 0;
long layerNumRef = 0;              //layer lines
char str[MAX_CHARS];
if (MEM < 1000) MEM = 1000;
MEMORY = MEM;

//=============================
//=============================
//ДИНАМИЧЕСКОЕ ВЫДЕЛЕНИЕ ПАМЯТИ
//=============================
//=============================
//=============================
/*try     {
        NETS = new(std::nothrow) AnsiString[MEMORY];    //
        }
catch(std::bad_alloc)
        {
        ShowMessage("    Ошибка выделения памяти: AnsiString[" + AnsiString(MEMORY) + "]!" );
        exit(0);
        }  */
try     {
        Trassa = new(std::nothrow) AnsiString[MEMORY*2];    //
        }
catch(std::bad_alloc)
        {
        ShowMessage("    Ошибка выделения памяти: AnsiString[" + AnsiString(MEMORY) + "]!" );
        exit(0);
        }
try     {
        LINES/*[ii]*/ = new(std::nothrow) PcbLine[MEMORY];
        }
catch(std::bad_alloc)
        {
        ShowMessage("    Ошибка выделения памяти: PcbLine[" + AnsiString(MEMORY) + "]!" );
        }


//ЧТЕНИЕ Lines
Form1->Label4->Caption = "Reading Lines" ;
Application->ProcessMessages();
AnsiString A;
ifstream read_Lines (OpenD.c_str());
lns = 0;
bool Flag_pcbDesign = false;
AnsiString CurentNet = "noConnect";
while (CNT)
        {
        CNT--;
        read_Lines.getline(str,sizeof(str));
        A = str;
        A = A.Trim();
        if (A.SubString(1,11) == "(pcbDesign " )Flag_pcbDesign = true;
        if (lns >= (MEMORY-299))
                {
                FlagWarning3 = true;
                //удаление
                delete[] LINES;
                delete[] Trassa;
                return;
                }
        if (A.SubString(1,14) == "(layerContents" )
                {
                i = prob (A, 1);
                if (A.SubString(i,12) == "(layerNumRef" )
                        {
                        i = prob (A, 2);
                        layerNumRef = ex_float_NM (A, &i, -1);
                        }
                }
        if (Flag_pcbDesign)
        if (layerNumRef)
        if ((A.SubString(1,6) == "(line " ) || (A.SubString(1,9) == "(thermal "))
                {
                i = go (A, 1, "(pt ");
                i = go (A, i, " ");
                LINES[lns].X1 = ex_float_NM (A, &i, UNITS);             //X
                LINES[lns].Y1 = ex_float_NM (A, &i, UNITS);             //Y
                i = go (A, i, "(pt ");
                LINES[lns].X2 = ex_float_NM (A, &i, UNITS);             //X2
                LINES[lns].Y2 = ex_float_NM (A, &i, UNITS);             //Y2
                i = go (A, i, "width ");
                if (i)  LINES[lns].Width = ex_float_NM (A, &i, UNITS);     //width
                else    LINES[lns].Width = 0;
                LINES[lns].Layer = layerNumRef;                            //layer
                if (A.SubString(1,6) == "(line " )
                        {
                        i = go (A, i, "netNameRef");
                        if (i)  LINES[lns].Net = ex_str (A,&i);
                        else    LINES[lns].Net = "noConnect";
                        }
                else    LINES[lns].Net = CurentNet;
                if (MaxLoc < ABS(LINES[lns].X1)) MaxLoc = ABS(LINES[lns].X1);
                if (MaxLoc < ABS(LINES[lns].Y1)) MaxLoc = ABS(LINES[lns].Y1);
                // BRD_RECT
                //if (layerNumRef == 3)
                //        {
                        if (BRD_RECT[0] > LINES[lns].X1) BRD_RECT[0] = LINES[lns].X1;
                        if (BRD_RECT[1] > LINES[lns].Y1) BRD_RECT[1] = LINES[lns].Y1;
                        if (BRD_RECT[2] < LINES[lns].X1) BRD_RECT[2] = LINES[lns].X1;
                        if (BRD_RECT[3] < LINES[lns].Y1) BRD_RECT[3] = LINES[lns].Y1;
                //        }
                lns++;
                }
        else if (A.LowerCase().SubString(1,6) == "(text ")
                {
                int LayerT = 0;
                long XT = 0;             //X
                long YT = 0;             //Y
                AnsiString TEXT = "";
                long Wt = 0;
                long Ht = 0;
                int Mirror = 0;
                long RotateT = 0;
                i = go (A, 1, "(pt ");
                if (i)
                        {
                        i = go (A, i, " ");
                        XT = ex_float_NM (A, &i, UNITS);             //X
                        YT = ex_float_NM (A, &i, UNITS);             //Y
                        //i = go (A, i, " ");
                        TEXT = ex_str(A, &i);
                        }
                i = go (A, 1, "(textStyleRef");
                if (i)
                        {
                        i = go (A, i, " ");
                        AnsiString TEXTStyle = ex_str(A, &i);
                        RTextStyle (TEXTStyle, &Wt, &Ht) ;
                        }
                i = go (A, 1, "rotation");
                if (i)
                        {
                        i = go (A, i, " ");
                        RotateT = ex_float_NM (A, &i, -1);
                        }
                i = go (A, 1, "isFlipped");
                if (i)
                        {
                        RotateT = RotateT + 180;
                        if (RotateT > 360) RotateT = RotateT - 360;
                        Mirror = 1;
                        }
                if (RotateT)
                if (!Mirror) RotateT = 360 - RotateT;
                if (layerNumRef < 3)            LayerT = layerNumRef + 11;
                else if (layerNumRef > 11)      LayerT = layerNumRef + 2;
                else if (Mirror)                LayerT = 8;
                else                            LayerT = 7;
                if (TEXT.Length())
                        {
                        AnsiString StrTxt = "text: \"";
                        StrTxt += TEXT;
                        StrTxt += "\" ";
                        StrTxt += AnsiString(XT);
                        StrTxt += " ";
                        StrTxt += AnsiString(YT);
                        StrTxt += " ";
                        StrTxt += AnsiString(LayerT);
                        StrTxt += " ";
                        StrTxt += AnsiString(RotateT);
                        StrTxt += " ";
                        StrTxt += AnsiString(Mirror);
                        StrTxt += " ";
                        StrTxt += AnsiString(Ht/2);
                        StrTxt += " ";
                        StrTxt += AnsiString(Wt/2);
                        Form1->ListBox3_TEXTS->Items->Add(StrTxt);
                        }
                }
        else if (A.LowerCase().SubString(1,12) == "(netnameref ")
                {
                i = prob(A,1);
                CurentNet = ex_str(A, &i);
                }
        else if (A.SubString(1,5) == "(arc ")
                {
                double X_center= 0;
                double Y_center = 0;
                double R = 0;
                double A1 = 0;
                double A2 = 0;
                double W = 0;
                double X1 = 0;
                double Y1 = 0;
                double X2 = 0;
                double Y2 = 0;
                AnsiString N = "noConnect";
                i = go(A,1,"(pt ");
                if (i) X_center = ex_float_NM(A, &i, UNITS);
                if (i) Y_center = ex_float_NM(A, &i, UNITS);
                i = go(A,1,"radius");
                if (i) R = ex_float_NM(A, &i, UNITS);
                i = go(A,1,"startAngle");
                if (i) A1 = ex_float_NM(A, &i, -1);
                i = go(A,1,"sweepAngle");
                if (i) A2 = ex_float_NM(A, &i, -1);
                A2 = A1 + A2;
                i = go(A,1,"width");
                if (i) W = ex_float_NM(A, &i, UNITS);
                i = go(A,1,"netNameRef");
                if (i) N = ex_str(A,&i);
                X1 = X_center + R*cos(A1*M_PI/(double)180);
                Y1 = Y_center + R*sin(A1*M_PI/(double)180);
                X2 = X_center + R*cos(A2*M_PI/(double)180);
                Y2 = Y_center + R*sin(A2*M_PI/(double)180);
                double ARC[299];
                if (R > W)
                        {
                        i = Generate_ARC        (X1,Y1,X2,Y2,X_center,Y_center,&ARC[0]);
                        if (i > 3)
                                {
                                int n = 0;
                                while (1)
                                        {
                                        LINES[lns].X1 = ( long )ARC[n];
                                        LINES[lns].Y1 = ( long )ARC[n+1];
                                        LINES[lns].X2 = ( long )ARC[n+2];
                                        LINES[lns].Y2 = ( long )ARC[n+3];
                                        LINES[lns].Width = W;
                                        LINES[lns].Layer = layerNumRef;
                                        LINES[lns].Net = N;
                                        lns++;
                                        n = n+2;
                                        if ((n+4) > i) break;
                                        }
                                }//if (i > 3)
                        }//if (R > Min_Length_Line)
                else    {
                        LINES[lns].X1 = ( long )X1;
                        LINES[lns].Y1 = ( long )Y1;
                        LINES[lns].X2 = ( long )X2;
                        LINES[lns].Y2 = ( long )Y2;
                        LINES[lns].Width = W;
                        LINES[lns].Layer = layerNumRef;
                        LINES[lns].Net = N;
                        lns++;
                        }
                // BRD_RECT
                //if (layerNumRef == 3)
                //        {
                        if (BRD_RECT[0] > LINES[lns-1].X1) BRD_RECT[0] = LINES[lns-1].X1;
                        if (BRD_RECT[1] > LINES[lns-1].Y1) BRD_RECT[1] = LINES[lns-1].Y1;
                        if (BRD_RECT[2] < LINES[lns-1].X1) BRD_RECT[2] = LINES[lns-1].X1;
                        if (BRD_RECT[3] < LINES[lns-1].Y1) BRD_RECT[3] = LINES[lns-1].Y1;
                //        }
                }//if (A.SubString(1,5) == "(arc ")
        else if (A.SubString(1,15) == "(triplePointArc")
                {
                double x1 = 0;
                double y1 = 0;
                double x2 = 0;
                double y2 = 0;
                double x3 = 0;
                double y3 = 0;
                double w = 0;
                AnsiString netNameRef = "noConnect";
                i = go (A, 1, "(pt ");
                if (i)
                        {
                        i = go (A, i, " ");
                        x1 = ex_float_NM (A, &i, UNITS);
                        y1 = ex_float_NM (A, &i, UNITS);
                        }
                i = go (A, i, "(pt ");
                if (i)
                        {
                        i = go (A, i, " ");
                        x2 = ex_float_NM (A, &i, UNITS);
                        y2 = ex_float_NM (A, &i, UNITS);
                        }
                i = go (A, i, "(pt ");
                if (i)
                        {
                        i = go (A, i, " ");
                        x3 = ex_float_NM (A, &i, UNITS);
                        y3 = ex_float_NM (A, &i, UNITS);
                        }
                i = go (A, i, "(width");
                if (i)
                        {
                        i = go (A, i, " ");
                        w = ex_float_NM (A, &i, UNITS);
                        }
                i = go (A, i, "netNameRef");
                if (i)  netNameRef = ex_str (A,&i);
                double ARC[299];
                double R = Length_Line (x2,y2,x3,y3);
                if (R > w)
                        {
                        i = Generate_ARC        (x2,y2,x3,y3,x1,y1,&ARC[0]);
                        if (i > 3)
                                {
                                int n = 0;
                                while (1)
                                        {
                                        LINES[lns].X1 = ( long )ARC[n];
                                        LINES[lns].Y1 = ( long )ARC[n+1];
                                        LINES[lns].X2 = ( long )ARC[n+2];
                                        LINES[lns].Y2 = ( long )ARC[n+3];
                                        LINES[lns].Width = w;
                                        LINES[lns].Layer = layerNumRef;
                                        LINES[lns].Net = netNameRef;
                                        lns++;
                                        n = n+2;
                                        if ((n+4) > i) break;
                                        }
                                }
                        }//Length_Line ((double)x2,(double)y2,(double)x3,(double)y3) > (double)Min_Length_Line*4
                else    {
                        LINES[lns].X1 = ( long )x2;
                        LINES[lns].Y1 = ( long )y2;
                        LINES[lns].X2 = ( long )x3;
                        LINES[lns].Y2 = ( long )y3;
                        LINES[lns].Width = w;
                        LINES[lns].Layer = layerNumRef;
                        LINES[lns].Net = netNameRef;
                        lns++;
                        }
                // BRD_RECT
                //if (layerNumRef == 3)
                //        {
                        if (BRD_RECT[0] > LINES[lns-1].X1) BRD_RECT[0] = LINES[lns-1].X1;
                        if (BRD_RECT[1] > LINES[lns-1].Y1) BRD_RECT[1] = LINES[lns-1].Y1;
                        if (BRD_RECT[2] < LINES[lns-1].X1) BRD_RECT[2] = LINES[lns-1].X1;
                        if (BRD_RECT[3] < LINES[lns-1].Y1) BRD_RECT[3] = LINES[lns-1].Y1;
                //        }
                }//triplePointArc
        }//(CNT)
read_Lines.close();

// создание BOARD_OUTLINE
AnsiString B = ExtractFilePath (Application->ExeName)  ;
B = B + "Import_Tango\\Board.txt";
ofstream BOARD (B.c_str());
BOARD.close();
//
// создание LINES_GRAPHIC
B = ExtractFilePath (Application->ExeName)  ;
B = B + "Import_Tango\\Graphics.txt";
ofstream Graphics (B.c_str());
Graphics.close();

char DATTM[80];
time_t rawtime;
struct tm * timeinfo;
time ( &rawtime );
timeinfo = localtime ( &rawtime );
strftime (DATTM,80,"_ID%H%M",timeinfo);
TimeStr = DATTM;
B = ExtractFilePath (Application->ExeName)  ;
for (int t=0; t<11; t++)
        {
        switch (t)
                {
                case 0: A = "Import_Tango\\TOP_LINES.txt";              break;
                case 1: A = "Import_Tango\\BOTTOM_LINES.txt";           break;
                case 2: A = "Import_Tango\\INNERS_LINES.txt";           break;
                case 3: A = "Import_Tango\\TOP_SILK.txt";               break;
                case 4: A = "Import_Tango\\BOTTOM_SILK.txt";            break;
                case 5: A = "Import_Tango\\TOP_MASK.txt";               break;
                case 6: A = "Import_Tango\\BOTTOM_MASK.txt";            break;
                case 7: A = "Import_Tango\\TOP_PASTE.txt";              break;
                case 8: A = "Import_Tango\\BOTTOM_PASTE.txt";           break;
                case 9: A = "Import_Tango\\ASSY_TOP_LINES.txt";         break;
                case 10: A = "Import_Tango\\ASSY_BOTTOM_LINES.txt";     break;
                }
        ofstream Lines ((B + A).c_str());
        Lines << "name: \"";
        Lines << (A.SubString(14,(A.Length()-17)) + TimeStr).c_str();
        Lines << "\"" << endl;
        Lines << "units: NM" << endl;
        Lines << "sel_rect: ";
        Lines << AnsiString(-254000).c_str();
        Lines << " ";
        Lines << AnsiString(-2254000 - t*2000000).c_str();
        Lines << " ";
        Lines << AnsiString(25654000).c_str();
        Lines << " ";
        Lines << AnsiString(254000 - t*2000000).c_str();
        Lines << endl;
        Lines << "ref_text: 300000 0 0 0 10000" << endl;
        Lines << "value_text: 300000 0 0 0 10000" << endl;
        Lines << "centroid: 0 0 0 0" << endl;
        Lines << "outline_polyline: 200000 0 ";
        Lines << AnsiString(-t*2000000).c_str() << endl;
        Lines << "next_corner: 0 ";
        Lines << AnsiString(-2000000-t*2000000).c_str();
        Lines << " 0" << endl;
        Lines << "next_corner: 25400000 ";
        Lines << AnsiString(-2000000-t*2000000).c_str();
        Lines << " 0" << endl;
        Lines << "next_corner: 25400000 ";
        Lines << AnsiString(-t*2000000).c_str();
        Lines << " 0" << endl;
        Lines << "close_polyline: 0" << endl;
        Lines << "text: \"";
        Lines << ("IMPORT P-CAD: " + A.SubString(14,10) + "...").c_str();
        Lines << "\" 1000000 600000 ";
        Lines << AnsiString(-1400000-t*2000000).c_str();
        Lines << " 0 200000 0 4" << endl;
        Lines.close();
        }

index = -1;                     //GLOBAL
int num_Point;
bool FlagEnd;
int tr = 10000;
int trmin = 10000;
int trmax = 10000;
int numConnect = 0;
int countSeg;
int IndexBoard = 0;
int layer;
int layerFirstSeg;
int IndexViaInStringGrid;
int IndexPinInStringGrid;
int IndexPinStrGr_1;
int IndexPinStrGr_2;
int ViaStub_1;
int ViaStub_2;
int IndexPin_1;
int IndexPin_2;
int LayPin_1;
int LayPin_2;
long X_1;
long Y_1;
long X_2;
long Y_2;
long Length;
long W;
long MinimumW = 254000;
AnsiString netName;
//GENERATE TRACE
while (index < lns)
        {
        index++;
        if (LINES[index].Net.SubString(1,5) == "#DEL#" ) continue;
        tr = trmin;
        // стираем массив TRACE
        while (tr <= trmax) {TRACE[tr] = ""; tr++;}
        //trmin = 10000;
        //trmax = 10000;
        // извлекаем параметры линии
        X_1 = LINES[index].X1;  //x1
        Y_1 = LINES[index].Y1;  //y1
        X_2 = LINES[index].X2;  //x2
        Y_2 = LINES[index].Y2;  //y2
        W = LINES[index].Width;                                 //width
        layerNumRef = LINES[index].Layer;                       //номер слоя
        netName = LINES[index].Net;                             //netName
        if (layerNumRef < 3)            layer = layerNumRef + 11;
        else if (layerNumRef > 11)      layer = layerNumRef + 2;
        else                            layer = layerNumRef;
        tr = 10000;
        countSeg = 1;

        // записываем первую точку
        TRACE[tr] = "vtx: ";
        TRACE[tr] += AnsiString(countSeg) + " ";
        TRACE[tr] += AnsiString(X_1) + " " + AnsiString(Y_1) + " ";
        TRACE[tr] += AnsiString("0");
        if (layerNumRef != 3) TRACE[tr] += " 0 0 0 0";
        tr++;
        WrSegment (0,&tr,&countSeg,layer,W,X_2,Y_2,1);
        //trmax = tr;
        // стираем исходную точку из массива Lines;
        LINES[index].Net = "#DEL#";
        FlagEnd = false;
        layerFirstSeg = layerNumRef;
        while (1)
                {
                num_Point = FindNextPoint (X_2, Y_2, netName, layerNumRef, W, &FlagEnd, &IndexViaInStringGrid, &IndexPinInStringGrid,&Length);
                if (FlagEnd)    break;

                //Wr Via
                if (IndexViaInStringGrid)       WrSegment (IndexViaInStringGrid,&tr,&countSeg,layer,W,0,0,1);

                //Layer line
                layerNumRef = LINES[index].Layer;
                if (layerNumRef < 3)            layer = layerNumRef + 11;
                else if (layerNumRef > 11)      layer = layerNumRef + 2;
                else                            layer = layerNumRef;

                //Wr Via
                if (IndexViaInStringGrid)       WrSegment (0,&tr,&countSeg,layer,W,X_2,Y_2,1);
                if(Length > 20000)
                        {
                        if (num_Point == 0)
                                {
                                X_2 = LINES[index].X2;        //x
                                Y_2 = LINES[index].Y2;        //y
                                }
                        else    {
                                X_2 = LINES[index].X1;        //x
                                Y_2 = LINES[index].Y1;        //y
                                }
                        WrSegment (0,&tr,&countSeg,layer,W,X_2,Y_2,1);
                        }

                // извлекаем параметры линии
                if (num_Point == 0)
                        {
                        X_2 = LINES[index].X1;  //x
                        Y_2 = LINES[index].Y1;  //y
                        }
                else    {
                        X_2 = LINES[index].X2;  //x
                        Y_2 = LINES[index].Y2;  //y
                        }
                W = LINES[index].Width;                    //width

                // Minimum Width in PCB
                if ((layerNumRef  < 3)||(layerNumRef  > 11))
                if (netName.Length())
                if (netName.SubString(1,9) != "noConnect" )
                if (MinimumW > W)       MinimumW = W;

                // стираем исходную точку из массива Lines;
                LINES[index].Net = "#DEL#";

                // записываем сегмент
                WrSegment (0,&tr,&countSeg,layer,W,X_2,Y_2,1);

                if (tr > 19997) {tr = 19997; FlagWarning5 = true;}
                }
        //Wr Via
        if (!IndexPinInStringGrid)
        if (IndexViaInStringGrid)
                {
                WrSegment (IndexViaInStringGrid,&tr,&countSeg,layer,W,0,0,1);
                }
        IndexPinStrGr_1 = IndexPinInStringGrid;
        LayPin_1 = layer;
        ViaStub_1 = IndexViaInStringGrid;
        //
        trmax = tr;
        tr = 9999;
        FlagEnd = false;

        //Layer FirstSeg
        layerNumRef = layerFirstSeg;
        if (layerNumRef < 3)            layer = layerNumRef + 11;
        else if (layerNumRef > 11)      layer = layerNumRef + 2;
        else                            layer = layerNumRef;

        //REVERS
        while (1)
                {
                num_Point = FindNextPoint (X_1, Y_1, netName, layerNumRef, W, &FlagEnd, &IndexViaInStringGrid, &IndexPinInStringGrid,&Length);
                if (FlagEnd)    break;

                //Wr Via
                if (IndexViaInStringGrid)       WrSegment (IndexViaInStringGrid,&tr,&countSeg,layer,W,0,0,0);

                //Layer line
                layerNumRef = LINES[index].Layer;
                if (layerNumRef < 3)            layer = layerNumRef + 11;
                else if (layerNumRef > 11)      layer = layerNumRef + 2;
                else                            layer = layerNumRef;

                //Wr Via
                if (IndexViaInStringGrid)       WrSegment (0,&tr,&countSeg,layer,W,X_1,Y_1,0);
                if(Length > 20000)
                        {
                        if (num_Point == 0)
                                {
                                X_1 = LINES[index].X2;        //x
                                Y_1 = LINES[index].Y2;        //y
                                }
                        else    {
                                X_1 = LINES[index].X1;        //x
                                Y_1 = LINES[index].Y1;        //y
                                }
                        WrSegment (0,&tr,&countSeg,layer,W,X_1,Y_1,0);
                        }

                // извлекаем параметры линии
                if (num_Point == 0)
                        {
                        X_1 = LINES[index].X1;  //x
                        Y_1 = LINES[index].Y1;  //y
                        }
                else    {
                        X_1 = LINES[index].X2;  //x
                        Y_1 = LINES[index].Y2;  //y
                        }
                W = LINES[index].Width;                    //width

                // Minimum Width in PCB
                if ((layerNumRef  < 3)||(layerNumRef  > 11))
                if (netName.Length())
                if (netName.SubString(1,9) != "noConnect" )
                if (MinimumW > W)       MinimumW = W;

                // стираем исходную точку из массива Lines;
                LINES[index].Net = "#DEL#";

                // записываем сегмент
                WrSegment (0,&tr,&countSeg,layer,W,X_1,Y_1,0);

                if (tr < 2) {tr = 2; FlagWarning5 = true;}
                }

        //Wr Via
        if (!IndexPinInStringGrid)
        if (IndexViaInStringGrid)
                {
                WrSegment (IndexViaInStringGrid,&tr,&countSeg,layer,W,0,0,0);
                }
        IndexPinStrGr_2 = IndexPinInStringGrid;
        LayPin_2 = layer;
        ViaStub_2 = IndexViaInStringGrid;
        //
        trmin = tr;
        IndexPin_1 = -1;
        IndexPin_2 = -1;
        if (((IndexPinStrGr_1)||(IndexPinStrGr_2))&&(IndexPinStrGr_1 != IndexPinStrGr_2))
                {
                //стираем "VIAFIND"
                for (int k=0; k<Form2->StringGrid1->RowCount; k++)
                        {
                        A = Form2->StringGrid1->Cells[0][k];
                        if (A.UpperCase().SubString(1,A.Length()) == "VIAFIND") Form2->StringGrid1->Cells[0][k] = "";
                        }
                int ST_ID;
                long X_1_forStub = X_1;
                long Y_1_forStub = Y_1;
                long X_2_forStub = X_2;
                long Y_2_forStub = Y_2;
                int StubLayer = 0;
                if (IndexPinStrGr_1)
                        {
                        IndexPin_1 = StrToInt(Form2->StringGrid1->Cells[1][IndexPinStrGr_1]);
                        X_1 = StrToInt(Form2->StringGrid1->Cells[3][IndexPinStrGr_1]);
                        Y_1 = StrToInt(Form2->StringGrid1->Cells[4][IndexPinStrGr_1]);

                        // записываем сегмент
                        tr = trmax;
                        WrSegment (IndexPinInStringGrid,&tr,&countSeg,LayPin_1,MinimumW,X_1,Y_1,1);
                        trmax = tr;
                        }
                else    {
                        tr = trmax;
                        long WidthVia = 0;
                        if (ViaStub_1)  WidthVia = StrToInt(Form2->StringGrid1->Cells[5][ViaStub_1]);
                        StubLayer = FindVertexOfTraceStub (&X_2_forStub, &Y_2_forStub, netName, LayPin_1,WidthVia, &ST_ID, numConnect);
                        if (StubLayer)   WrSegment (0,&tr,&countSeg,StubLayer,MinimumW,X_2_forStub,Y_2_forStub,1);
                        trmax = tr;
                        }
                if (IndexPinStrGr_2)
                        {
                        IndexPin_2 = StrToInt(Form2->StringGrid1->Cells[1][IndexPinStrGr_2]);
                        X_2 = StrToInt(Form2->StringGrid1->Cells[3][IndexPinStrGr_2]);
                        Y_2 = StrToInt(Form2->StringGrid1->Cells[4][IndexPinStrGr_2]);
                        tr = trmin;

                        // записываем сегмент
                        tr = trmin;
                        WrSegment (IndexPinInStringGrid,&tr,&countSeg,LayPin_2,MinimumW,X_2,Y_2,0);
                        trmin = tr;
                        }
                else    {
                        tr = trmin;
                        long WidthVia = 0;
                        if (ViaStub_2)  WidthVia = StrToInt(Form2->StringGrid1->Cells[5][ViaStub_2]);
                        StubLayer = FindVertexOfTraceStub (&X_1_forStub, &Y_1_forStub, netName,LayPin_2,WidthVia, &ST_ID, numConnect);
                        if (StubLayer)   WrSegment (0,&tr,&countSeg,StubLayer,MinimumW,X_1_forStub,Y_1_forStub,0);
                        trmin = tr;
                        }
                if (MaxLayerNumRef < layer) MaxLayerNumRef = layer;

                //Построение Трассы
                if ((trassa + trmax - trmin) >= (MEMORY*2-1))
                        {
                        FlagWarning3 = true;
                        //удаление
                        delete[] LINES;
                        delete[] Trassa;
                        return;
                        }
                Form1->Label4->Caption = "Building copper routes: " + AnsiString(numConnect);
                Application->ProcessMessages();
                numConnect++;
                Trassa[trassa] = "net: \"";
                Trassa[trassa] += netName;
                Trassa[trassa] += "\"";
                trassa++;
                Trassa[trassa] = "connect: ";
                Trassa[trassa] += AnsiString(numConnect);
                Trassa[trassa] += " ";
                if (IndexPin_2 != -1)
                        {
                        Trassa[trassa] += AnsiString(IndexPin_2);
                        Trassa[trassa] += " ";
                        Trassa[trassa] += AnsiString(IndexPin_1);
                        Trassa[trassa] += " ";
                        Trassa[trassa] += AnsiString(countSeg-1);
                        Trassa[trassa] += " 0";
                        trassa++;
                        tr = trmin;
                        countSeg = 1;
                        while (tr <= trmax)
                                {
                                if (TRACE[tr].Length())
                                        {
                                        if (TRACE[tr].SubString(1,3) == "vtx" )
                                                {
                                                int n;
                                                n = prob (TRACE[tr], 2);
                                                Trassa[trassa] = "vtx: ";
                                                Trassa[trassa] += AnsiString(countSeg);
                                                Trassa[trassa] += " ";
                                                Trassa[trassa] += TRACE[tr].SubString(n,(TRACE[tr].Length()-n+1));
                                                trassa++;
                                                if ((tr == (trmax-1)) && (StubLayer)) //если последний сегмент
                                                        {
                                                        Trassa[trassa-1] += AnsiString(ST_ID);
                                                        }
                                                }
                                        else if (TRACE[tr].SubString(1,3) == "seg" )
                                                {
                                                int n;
                                                n = prob (TRACE[tr], 2);
                                                Trassa[trassa] = "seg: ";
                                                Trassa[trassa] += AnsiString(countSeg);
                                                Trassa[trassa] += " ";
                                                Trassa[trassa] += TRACE[tr].SubString(n,(TRACE[tr].Length()-n+1));
                                                trassa++;
                                                countSeg++;
                                                }
                                        else    {
                                                Trassa[trassa] = TRACE[tr];
                                                trassa++;
                                                }
                                        }
                                tr++;
                                }
                        }
                else    {
                        Trassa[trassa] += AnsiString(IndexPin_1);
                        Trassa[trassa] += " ";
                        Trassa[trassa] += AnsiString(IndexPin_2);
                        Trassa[trassa] += " ";
                        Trassa[trassa] += AnsiString(countSeg-1);
                        Trassa[trassa] += " 0";
                        trassa++;
                        tr = trmax;
                        countSeg = 1;
                        while (tr >= trmin)
                                {
                                if (TRACE[tr].Length())
                                        {
                                        if (TRACE[tr].SubString(1,3) == "vtx" )
                                                {
                                                int n;
                                                n = prob (TRACE[tr], 2);
                                                Trassa[trassa] = "vtx: ";
                                                Trassa[trassa] += AnsiString(countSeg);
                                                Trassa[trassa] += " ";
                                                Trassa[trassa] += TRACE[tr].SubString(n,(TRACE[tr].Length()-n+1));
                                                trassa++;
                                                if ((tr == (trmin+1)) && (StubLayer)) //если последний сегмент
                                                        {
                                                        Trassa[trassa-1] += AnsiString(ST_ID);
                                                        }
                                                }
                                        else if (TRACE[tr].SubString(1,3) == "seg" )
                                                {
                                                int n;
                                                n = prob (TRACE[tr], 2);
                                                Trassa[trassa] = "seg: ";
                                                Trassa[trassa] += AnsiString(countSeg);
                                                Trassa[trassa] += " ";
                                                Trassa[trassa] += TRACE[tr].SubString(n,(TRACE[tr].Length()-n+1));
                                                trassa++;
                                                countSeg++;
                                                }
                                        else    {
                                                Trassa[trassa] = TRACE[tr];
                                                trassa++;
                                                }
                                        }
                                tr--;
                                }
                        }
                }
        else    {
                //стираем "VIAFIND"
                for (int k=0; k<Form2->StringGrid1->RowCount; k++)
                        {
                        A = Form2->StringGrid1->Cells[0][k];
                        if (A.UpperCase().SubString(1,A.Length()) == "VIAFIND") Form2->StringGrid1->Cells[0][k] = "Via";
                        }
                //запись трассы в шелкографию
                //если PinIndex1 и PinIndex2 == 0
                //запись трассы TOP_LINES
                long Xtr;
                long Ytr;
                long XtrBack ;
                long YtrBack ;
                long Wtr;
                A = "";
                switch (layerNumRef)
                        {
                        case 1: A = "Import_Tango\\TOP_LINES.txt";              break;
                        case 2: A = "Import_Tango\\BOTTOM_LINES.txt";           break;
                        case 3: A = ""; break;
                        case 4: A = "Import_Tango\\TOP_MASK.txt";               break;
                        case 5: A = "Import_Tango\\BOTTOM_MASK.txt";            break;
                        case 6: A = "Import_Tango\\SILK_TOP_LINES.txt";         break;
                        case 7: A = "Import_Tango\\SILK_BOTTOM_LINES.txt";      break;
                        case 8: A = "Import_Tango\\TOP_PASTE.txt";              break;
                        case 9: A = "Import_Tango\\BOTTOM_PASTE.txt";           break;
                        case 10: A = "Import_Tango\\ASSY_TOP_LINES.txt";        break;
                        case 11: A = "Import_Tango\\ASSY_BOTTOM_LINES.txt";     break;
                        default: A = "Import_Tango\\INNERS_LINES.txt";          break;
                        }
                //запись трассы BOARD_OUTLINE
                if ( layerNumRef == 3 ||
                        (layerNumRef == 8 && Form1->TopPaste_2_Board->Checked) ||
                        (layerNumRef == 9 && Form1->BotPaste_2_Board->Checked) ||
                        (layerNumRef == 10 && Form1->TopAssy_2_Board->Checked) ||
                        (layerNumRef == 11 && Form1->BotAssy_2_Board->Checked) ||
                        (layerNumRef == 6 && Form1->TopSilk_2_Board->Checked) ||
                        (layerNumRef == 7 && Form1->BotSilk_2_Board->Checked) )
                        {
                        B = ExtractFilePath (Application->ExeName)  ;
                        ofstream Boards;
                        Boards.open((B + "Import_Tango\\Board.txt").c_str(), std::ios_base::app );
                        Boards << "outline: ";
                        Boards << AnsiString(countSeg).c_str();
                        Boards << " ";
                        Boards << AnsiString(IndexBoard).c_str();
                        Boards << endl;
                        IndexBoard++;
                        int IndCornerBrd = 1;
                        tr = trmin;
                        while (tr <= trmax)
                                {
                                if (TRACE[tr].SubString(1,3) == "vtx" )
                                        {
                                        Boards << "corner: ";
                                        Boards << AnsiString(IndCornerBrd).c_str();
                                        Boards << " ";
                                        int n = prob(TRACE[tr],2);
                                        Boards << TRACE[tr].SubString(n,(TRACE[tr].Length()-n+2)).c_str();
                                        Boards << endl;
                                        IndCornerBrd++;
                                        }
                                tr++;
                                }
                        Boards.close();
                        }
                else if (layerNumRef == 6 ||
                        layerNumRef == 7 ||
                        layerNumRef == 10 ||
                        layerNumRef == 11)
                        {
                        B = ExtractFilePath (Application->ExeName)  ;
                        ofstream Graphics;
                        Graphics.open((B + "Import_Tango\\Graphics.txt").c_str(), std::ios_base::app );
                        tr = trmin;
                        int prev = -1;
                        Wtr = 0;
                        while (tr <= trmax)
                                {
                                if (TRACE[tr].SubString(1,3) == "vtx" )
                                        {
                                        if( prev >= 0 && Wtr )
                                                {
                                                Graphics << "line: 2 0 ";
                                                int lay = layerNumRef;
                                                if( lay == 10 || lay == 11 )
                                                        lay = lay - 4;
                                                lay++;
                                                Graphics << AnsiString(lay).c_str();
                                                Graphics << " ";
                                                Graphics << AnsiString(Wtr).c_str();
                                                Graphics << endl;
                                                Graphics << "corner: 1 ";
                                                int n = prob(TRACE[prev],2);
                                                Graphics << TRACE[prev].SubString(n,(TRACE[prev].Length()-n+2)).c_str();
                                                Graphics << " 0";
                                                Graphics << endl;
                                                Graphics << "corner: 2 ";
                                                n = prob(TRACE[tr],2);
                                                Graphics << TRACE[tr].SubString(n,(TRACE[tr].Length()-n+2)).c_str();
                                                Graphics << " 0";
                                                Graphics << endl;
                                                }
                                        prev = tr;
                                        }
                                else if (TRACE[tr].SubString(1,3) == "seg" )
                                        {
                                        i = prob(TRACE[tr],3);
                                        Wtr = ex_float_NM(TRACE[tr],&i,-1);
                                        }
                                tr++;
                                }
                        Graphics.close();
                        }
                else if (A.Length())
                        {
                        B = ExtractFilePath (Application->ExeName)  ;
                        ofstream LNS;
                        LNS.open((B + A).c_str(), std::ios_base::app );
                        XtrBack = 0;
                        YtrBack = 0;
                        Wtr = 0;
                        tr = trmin;
                        while (tr <= trmax)
                                {
                                if (TRACE[tr].SubString(1,3) == "vtx" )
                                        {
                                        XtrBack = Xtr;
                                        YtrBack = Ytr;
                                        i = prob(TRACE[tr],2);
                                        Xtr = ex_float_NM(TRACE[tr],&i,-1);
                                        Ytr = ex_float_NM(TRACE[tr],&i,-1);
                                        if (XtrBack)
                                        if (YtrBack)
                                        if (tr > trmin)
                                        if (Wtr)
                                                {
                                                LNS << "outline_polyline: ";
                                                LNS << AnsiString(Wtr).c_str();
                                                LNS << " ";
                                                if( BRD_RECT[2] )
                                                        LNS << AnsiString(XtrBack - BRD_RECT[0]).c_str();
                                                else    LNS << AnsiString(XtrBack).c_str();
                                                LNS << " ";
                                                if( BRD_RECT[2] )
                                                        LNS << AnsiString(YtrBack - BRD_RECT[1]).c_str() << endl;
                                                else    LNS << AnsiString(YtrBack).c_str() << endl;
                                                LNS << "next_corner: ";
                                                if( BRD_RECT[2] )
                                                        LNS << AnsiString(Xtr - BRD_RECT[0]).c_str();
                                                else    LNS << AnsiString(Xtr).c_str();
                                                LNS << " ";
                                                if( BRD_RECT[2] )
                                                        LNS << AnsiString(Ytr - BRD_RECT[1]).c_str();
                                                else    LNS << AnsiString(Ytr).c_str();
                                                LNS << " 0" << endl;
                                                }
                                        }
                                else if (TRACE[tr].SubString(1,3) == "seg" )
                                        {
                                        i = prob(TRACE[tr],3);
                                        Wtr = ex_float_NM(TRACE[tr],&i,-1);
                                        }
                                tr++;
                                }
                        LNS.close();
                        }
                }
        index = 0;
        }
Trassa[trassa] = "end";

//повторный поиск BRANCH
//Form1->ListBox4_Lines->Clear();
int Cseg;
int LaySeg;
int Pin2;
int n = 0;
while (n <= trassa)
        {
        A = Trassa[n];
        if (A.SubString(1,3) == "net")
                {
                i = prob(A, 1);
                netName = ex_str(A, &i);
                //Form1->ListBox4_Lines->Items->Add(A);
                //tr = 0;
                //countSeg = 0;
                }
        //else if (A.Length())
        //        {
        //        TRACE[tr] = A;
        //        tr++;
        //        }
        //
        if (A.SubString(1,7) == "connect")
                {
                i = prob(A, 1);
                numConnect = ex_float_NM (A, &i, -1);
                i = prob(A, 3);
                Pin2 = ex_float_NM (A, &i, -1);
                Cseg = ex_float_NM (A, &i, -1);
                }
        else if (A.SubString(1,3) == "vtx")
                {
                i = prob(A, 1);
                int Nvtx = ex_float_NM (A, &i, -1);
                if (Nvtx == (Cseg+1))
                        {
                        int StubLay = 0;
                        int stid;
                        if (Pin2 == -1)
                                {
                                i = prob(A, 8);
                                int stubID = ex_float_NM (A, &i, -1);
                                if (!stubID)
                                        {
                                        i = prob(A, 2);
                                        long Xvtx = ex_float_NM (A, &i, -1);
                                        long Yvtx = ex_float_NM (A, &i, -1);
                                        i = prob(A, 6);
                                        int viaW = ex_float_NM (A, &i, -1);
                                        //countSeg = Cseg+1;
                                        StubLay = FindVertexOfTraceStub (&Xvtx, &Yvtx, netName, LaySeg, viaW, &stid, numConnect);
                                        //if (StubLay)   WrSegment (0,&tr,&countSeg,StubLay,MinimumW,Xvtx,Yvtx,1);
                                        }
                                }
                        if (StubLay)
                                {
                                /*i = prob(TRACE[0], 1);
                                int N = ex_float_NM (TRACE[0], &i, -1);
                                int P1 = ex_float_NM (TRACE[0], &i, -1);
                                int P2 = ex_float_NM (TRACE[0], &i, -1);
                                TRACE[0] = "connect: ";
                                TRACE[0] += AnsiString(N) + " ";
                                TRACE[0] += AnsiString(P1) + " ";
                                TRACE[0] += AnsiString(P2) + " ";
                                TRACE[0] += AnsiString(Cseg+1) + " 0"; */
                                Trassa[n] += AnsiString(stid);
                                ///TRACE[tr-1] += AnsiString(stid);
                                }
                        //int a = 0;
                        //while (a < tr)
                        //        {
                        //        Form1->ListBox4_Lines->Items->Add(TRACE[a]);
                        //        a++;
                        //        }
                        }
                }
        else if (A.SubString(1,3) == "seg")
                {
                i = prob(A, 2);
                LaySeg = ex_float_NM (A, &i, -1);
                }
        n++;
        }
n = 0;
while (n <= trassa)
        {
        A = Trassa[n];
        Form1->ListBox4_Lines->Items->Add(A);
        n++;
        }

//Запись Trace.txt
B = ExtractFilePath (Application->ExeName);
B = B + "Import_Tango\\Trace.txt";
ofstream Tpacca (B.c_str());
i = 0;
while (i < Form1->ListBox4_Lines->Items->Count)
        {
        Tpacca << (Form1->ListBox4_Lines->Items->operator [](i)).c_str() << endl;
        i++;
        }
Tpacca << "end" << endl;
Tpacca.close();

B = ExtractFilePath (Application->ExeName);
ofstream Brds;
Brds.open((B + "Import_Tango\\Board.txt").c_str(), std::ios_base::app );
Brds << "end";
Brds << endl;
Brds.close();

ofstream Gr;
Gr.open((B + "Import_Tango\\Graphics.txt").c_str(), std::ios_base::app );
Gr << "end";
Gr << endl;
Gr.close();

//запись оставшихся Via
Form1->ListBox1->Clear();
Form1->ListBox2->Clear();
Form1->ListBox4_Lines->Clear();
for (int k = 0; k<Form2->StringGrid1->RowCount; k++)
        {
        A = Form2->StringGrid1->Cells[0][k];
        if (A.UpperCase().SubString(1,A.Length()) == "VIA")
                {
                AnsiString NameF = Form2->StringGrid1->Cells[1][k];
                i = Form1->ListBox1->Items->IndexOf(NameF);
                if (i == -1)
                        {
                        Form1->ListBox1->Items->Add(NameF);
                        long VW = StrToInt(Form2->StringGrid1->Cells[5][k]);
                        long VH = StrToInt(Form2->StringGrid1->Cells[6][k]);
                        long SRect = VH/2 + 100000;
                        ofstream FootPr;
                        B = ExtractFilePath (Application->ExeName)  ;
                        FootPr.open((B + "Import_Tango\\FootPrints.txt").c_str(), std::ios_base::app );
                        FootPr << ("name: \"" + NameF + "\"").c_str() << endl;
                        FootPr << "  units: NM" << endl;
                        FootPr << "  sel_rect: ";
                        FootPr << AnsiString(-SRect).c_str();           //X Left
                        FootPr << " ";
                        FootPr << AnsiString(-SRect).c_str();           //Y Left
                        FootPr << " ";
                        FootPr << AnsiString(SRect).c_str();            //X Right
                        FootPr << " ";
                        FootPr << AnsiString(SRect).c_str() << endl;    //Y Right
                        FootPr << "  ref_text: 0 0 0 0 0" << endl;
                        FootPr << "  value_text: 0 0 0 0 0" << endl;
                        FootPr << "  centroid: 0 0 0 0" << endl;
                        FootPr << "  n_pins: 1" << endl;
                        FootPr << "  pin: \"1\" ";
                        FootPr << AnsiString(VH).c_str();               //Via Hole
                        FootPr << " 0 0 0" << endl;                     //Via X Y Angle
                        FootPr << "    top_pad: 1 ";
                        FootPr << AnsiString(VW).c_str();               //Via Width
                        FootPr << " ";
                        FootPr << AnsiString(VW/2).c_str();             //Via Len/2
                        FootPr << " ";
                        FootPr << AnsiString(VW/2).c_str();             //Via Len/2
                        FootPr << " 0" << endl;                         //Corner Rad
                        FootPr << "    bottom_pad: 1 ";
                        FootPr << AnsiString(VW).c_str();               //Via Width
                        FootPr << " ";
                        FootPr << AnsiString(VW/2).c_str();             //Via Len/2
                        FootPr << " ";
                        FootPr << AnsiString(VW/2).c_str();             //Via Len/2
                        FootPr << " 0" << endl;                         //Corner Rad
                        FootPr.close();
                        }
                long VX = StrToInt(Form2->StringGrid1->Cells[3][k]);
                long VY = StrToInt(Form2->StringGrid1->Cells[4][k]);
                B = ExtractFilePath (Application->ExeName)  ;
                ofstream PartSV;
                PartSV.open((B + "Import_Tango\\PartList.txt").c_str(), std::ios_base::app );
                PartSV << "part: Via__";
                PartSV << AnsiString(k).c_str() << endl;
                PartSV << "ref_text: 0 0 0 0 0" << endl;
                PartSV << "shape: \"";
                PartSV << AnsiString(NameF).c_str();
                PartSV << "\"" << endl;
                PartSV << "pos: ";
                PartSV << AnsiString(VX).c_str();
                PartSV << " ";
                PartSV << AnsiString(VY).c_str();
                PartSV << " 0 0 0" << endl;
                PartSV.close();

                //Добавление NET VIA
                AnsiString NetVia = Form2->StringGrid1->Cells[2][k];
                A = "Via__" + AnsiString(k) + ".1";
                Form1->ListBox4_Lines->Items->Add(NetVia);
                Form1->ListBox4_Lines->Items->Add(A);
                }
        }

//Метка : "Total"
ofstream FootPrT;
B = ExtractFilePath (Application->ExeName)  ;
FootPrT.open((B + "Import_Tango\\FootPrints.txt").c_str(), std::ios_base::app );
FootPrT << "Total";
FootPrT.close();

for (int t=0; t<11; t++)
        {
        switch (t)
                {
                case 0: A = "Import_Tango\\TOP_LINES.txt";              break;
                case 1: A = "Import_Tango\\BOTTOM_LINES.txt";           break;
                case 2: A = "Import_Tango\\INNERS_LINES.txt";           break;
                case 3: A = "Import_Tango\\TOP_SILK.txt";               break;
                case 4: A = "Import_Tango\\BOTTOM_SILK.txt";            break;
                case 5: A = "Import_Tango\\TOP_MASK.txt";               break;
                case 6: A = "Import_Tango\\BOTTOM_MASK.txt";            break;
                case 7: A = "Import_Tango\\TOP_PASTE.txt";              break;
                case 8: A = "Import_Tango\\BOTTOM_PASTE.txt";           break;
                case 9: A = "Import_Tango\\ASSY_TOP_LINES.txt";         break;
                case 10: A = "Import_Tango\\ASSY_BOTTOM_LINES.txt";     break;
                }
        ofstream TL;
        TL.open((B + A).c_str(), std::ios_base::app );
        TL << "n_pins: 0" << endl;
        /*TL << "pin: \"1\" 0 ";
        TL << AnsiString(12700000).c_str();
        TL << " ";
        TL << AnsiString(-1000000 - t*2000000).c_str();
        TL << " 0" << endl;
        TL << "top_pad: 3 1450000 12500000 12500000 0 0" << endl;  */
        TL << "end";
        TL.close();
        }
B = ExtractFilePath (Application->ExeName);
ofstream PartT;
PartT.open((B + "Import_Tango\\PartList.txt").c_str(), std::ios_base::app );
PartT << "Total";
PartT.close();
}

