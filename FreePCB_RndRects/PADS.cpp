//---------------------------------------------------------------------------


#pragma hdrstop

#include "PADS.h"
#include "RND.h"
#include "fstream.h"
#include "math.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
struct area
        {
        long x1;
        long x2;
        long x3;
        long y1;
        long y2;
        long y3;
        int arc1;
        int arc2;
        //int num_contour;
        };
long * STUB_ID;
long * STUB_SIZE;






//---------------------------------------------------------------------------
AnsiString Str_Float_Format (AnsiString STRING_2_DOUBLE)
{
STRING_2_DOUBLE = StringReplace(STRING_2_DOUBLE,".",",",TReplaceFlags()<<rfReplaceAll);
int L = STRING_2_DOUBLE.Length();
bool F = false;
for (int x=1; x<=L; x++)
        {
        if (STRING_2_DOUBLE.SubString(1,1) == "-") continue;
        if ((STRING_2_DOUBLE.SubString(x,1) < "0") || (STRING_2_DOUBLE.SubString(x,1) > "9"))
        if  (F) {
                STRING_2_DOUBLE = STRING_2_DOUBLE.SubString(1,(x-1));
                break;
                }
        else    {
                F = true;
                AnsiString S = STRING_2_DOUBLE.SubString(x,1);
                STRING_2_DOUBLE = StringReplace(STRING_2_DOUBLE,S,",",TReplaceFlags()<<rfReplaceAll);
                }
        }
L = STRING_2_DOUBLE.Length();
if  (((STRING_2_DOUBLE.SubString(L,1) == "-")&&(L<2))||(!L)) STRING_2_DOUBLE = "0";
if  (STRING_2_DOUBLE.SubString(1,1) == ",") STRING_2_DOUBLE = "0" + STRING_2_DOUBLE;
if  (STRING_2_DOUBLE.SubString(L,1) == ",") STRING_2_DOUBLE = STRING_2_DOUBLE + "0";
return STRING_2_DOUBLE;
}










//---------------------------------------------------------------------------
long ViaOfStub (long STUBVALUE )
        {
        long max = 0;
        for (int n=0; STUB_ID[n]>0; n++)
                {
                if (STUB_ID[n] == STUBVALUE && max < STUB_SIZE[n]) max = STUB_SIZE[n];
                }
        return max;
        }
//---------------------------------------------------------------------------








//---------------------------------------------------------------------------
//                         void RoundingRect (void)
//---------------------------------------------------------------------------
void RoundingRect (void)
{
long i;
AnsiString ftpr;
AnsiString A;
AnsiString B;

//Checked...
bool CheckRndPads = Form1->EnableRndPads->Checked;

//Count corners...
int Tsame;
int Acount;
if (Form1->TraceSame2->Checked)         Tsame = 2;
else if (Form1->TraceSame3->Checked)    Tsame = 3;
else if (Form1->TraceSame4->Checked)    Tsame = 4;
else                                    Tsame = 5;
if (Form1->Area2->Checked)              Acount = 2;
else if (Form1->Area3->Checked)         Acount = 3;
else if (Form1->Area4->Checked)         Acount = 4;
else                                    Acount = 5;

//SizeVia pads
double SizeVia = StrToFloat(Form1->DiaVia->Items->operator [](Form1->DiaVia->ItemIndex)) ;
double LenVia = StrToFloat(Form1->LengthVia->Items->operator [](Form1->LengthVia->ItemIndex)) ;

//Radius...
double Rad;
double Rad_trace;
double Rad_trace_Correct;
double Rad_area;
if (Form1->PadsRadiusConstant->Checked)  Rad = StrToFloat(Form1->ValuePadsRadiusConstant->Items->operator [](Form1->ValuePadsRadiusConstant->ItemIndex)) ;
else Rad = 99;
if (Form1->TraceRadiusConstant->Checked) Rad_trace = StrToFloat(Form1->ValueTraceRadiusConstant->Items->operator [](Form1->ValueTraceRadiusConstant->ItemIndex)) ;
else Rad_trace = 99;
if (Form1->AreaRadiusConstant->Checked)  Rad_area = StrToFloat(Form1->ValueAreaRadiusConstant->Items->operator [](Form1->ValueAreaRadiusConstant->ItemIndex)) ;
else Rad_area = 99;

//Share...
int SharePads ;
float ShareTrace ;
int ShareArea ;
if (Form1->PadsRadiusShare->Checked)            SharePads = StrToInt(Form1->ValuePadsRadiusShare->Items->operator [](Form1->ValuePadsRadiusShare->ItemIndex));
else                                            SharePads = 2;
if (Form1->TraceRadiusShare->Checked)           ShareTrace = StrToInt(Form1->ValueTraceRadiusShare->Items->operator [](Form1->ValueTraceRadiusShare->ItemIndex));
else if (Form1->TraceRadiusShareW->Checked)     ShareTrace = StrToFloat(Form1->ValueTraceRadiusShareW->Items->operator [](Form1->ValueTraceRadiusShareW->ItemIndex));
else                                            ShareTrace = 2;
if (Form1->AreaRadiusShare->Checked)            ShareArea = StrToInt(Form1->ValueAreaRadiusShare->Items->operator [](Form1->ValueAreaRadiusShare->ItemIndex));
else                                            ShareArea = 2;
//---------------------------------------------------------------------------
double MIN_SEG_TRACE = StrToFloat(Form1->ValueMinLengthTrace->Items->operator [](Form1->ValueMinLengthTrace->ItemIndex)) ;
double MIN_SEG_AREA =  StrToFloat(Form1->ValueMinLengthArea->Items->operator [](Form1->ValueMinLengthArea->ItemIndex)) ;








//---------------------------------------------------------------------------
//                         count pins (��� �� �����)
//---------------------------------------------------------------------------
A = Form1->OpenDialog1->FileName;
ifstream CntPins (A.c_str());
int CPins = 0;
int CFile = 0;
int index_NETS = 0;
bool FLG = true;
int GlobalUnits = -1;
while (A.SubString(1,7) != "[end]" )
        {
        CntPins.getline (s, sizeof(s)) ;
        A = s;
        A = A.Trim();
        if(A.SubString(1,6) == "units:")
                {
                i = PROB(A,1);
                if( i > 0 )
                        {
                        if(A.SubString(i,2).LowerCase() == "mm")
                                {
                                GlobalUnits = 2;
                                //Form1->GroupBox2->Caption += "(MM)";
                                }
                        else if(A.SubString(i,2).LowerCase() == "nm")
                                {
                                GlobalUnits = 1;
                                //Form1->GroupBox2->Caption += "(NM)";
                                }
                        else if(A.SubString(i,2).LowerCase() == "mi")
                                {
                                GlobalUnits = 0;
                                //Form1->GroupBox2->Caption += "(MIL)";
                                }
                        }
                }
        if(A.SubString(1,7) == "[board]") FLG = false;
        if(A.SubString(1,7) == "[nets]") index_NETS = CFile;
        if(A.SubString(1,3) == "pin" && FLG) CPins++;
        CFile++;
        }
CntPins.close();
CPins++;
CPins++;
if (!index_NETS) return;
//=============================
//������������ ��������� ������
//=============================
float * Wmin;
float * Wmax;
bool * Round;
try     {
        Round = new(std::nothrow) bool[CPins];    //
        }
catch(std::bad_alloc)
        {
        ShowMessage("    ������ ��������� ������: bool[" + AnsiString(CPins) + "]!" );
        exit(0);
        }
try     {
        Wmin = new(std::nothrow) float[CPins];    //
        }
catch(std::bad_alloc)
        {
        ShowMessage("    ������ ��������� ������: double[" + AnsiString(CPins) + "]!" );
        exit(0);
        }
try     {
        Wmax = new(std::nothrow) float[CPins];    //
        }
catch(std::bad_alloc)
        {
        ShowMessage("    ������ ��������� ������: double[" + AnsiString(CPins) + "]!" );
        exit(0);
        }
try     {
        STUB_SIZE = new(std::nothrow) long[(CFile - index_NETS)/3];    //
        }
catch(std::bad_alloc)
        {
        ShowMessage("    ������ ��������� ������: long[" + AnsiString((CFile - index_NETS)/3) + "]!" );
        exit(0);
        }
try     {
        STUB_ID = new(std::nothrow) long[(CFile - index_NETS)/3];    //
        }
catch(std::bad_alloc)
        {
        ShowMessage("    ������ ��������� ������: long[" + AnsiString((CFile - index_NETS)/3) + "]!" );
        exit(0);
        }
//---------------------------------------------------------------------------










//---------------------------------------------------------------------------
//                          ��������� ����
//---------------------------------------------------------------------------
A = Form1->OpenDialog1->FileName;
ifstream RPins (A.c_str());
AnsiString CurrentName;
int w = 0;
int UNM = 0;
while (A.SubString(1,2) != "[b" )
        {
        if (A.SubString(1,4) != "pin:" )
        if (A.SubString(1,5) != "name:" )
                {
                RPins.getline (s, sizeof(s)) ;
                A = s;
                A = A.Trim();
                }
        //
        if(A.SubString(1,5) == "name:" )
                {
                i = PROB(A,1);
                CurrentName = ex_str(A, &i);
                RPins.getline (s, sizeof(s)) ;
                A = s;
                A = A.Trim();
                }
        if (A.SubString(1,6) == "units:" )
                {
                i = PROB(A,1);
                if (A.UpperCase().SubString(i,2) == "NM" )      UNM = 1;
                else if (A.UpperCase().SubString(i,2) == "MI" ) UNM = 0;
                else                                            UNM = 2;
                }
        else if (A.SubString(1,4) == "pin:" )
                {
                i = PROB(A,1);
                AnsiString PinName = ex_str(A, &i);
                PinName = CurrentName + "." + PinName;
                Form1->ListBox1_pins->Items->Add(PinName);
                do      {
                        RPins.getline (s, sizeof(s)) ;
                        A = s;
                        A = A.Trim();
                        if (A.SubString(1,4) == "pin:" ) break;
                        if (A.SubString(1,4) == "name" ) break;
                        if (A.SubString(1,1) == "[" )    break;
                        i = PROB(A,1);
                        }while (A.SubString(i,2) == "0 ");
                if (A.SubString(1,7) == "top_pad" || A.SubString(1,10) == "bottom_pad")
                        {
                        double W1;
                        double W2;
                        i = PROB(A,1);
                        int Aperture = ex_float( A, &i);
                        W1 = ex_float( A, &i);
                        W2 = ex_float( A, &i);
                        W2 = W2*(double)2;
                        if (Aperture == 1 || Aperture == 2 || W2 < BY_ZERO) W2 = W1;
                        if (UNM == 0)
                                {
                                W1 = W1*_25400;
                                W2 = W2*_25400;
                                }
                        else if (UNM == 2)
                                {
                                W1 = W1*_MM_TO_NM;
                                W2 = W2*_MM_TO_NM;
                                }
                        Wmin[w] = MIN(W1,W2);
                        Wmax[w] = MAX(W1,W2);
                        if (Aperture == 1) Round[w] = true;
                        else               Round[w] = false;
                        }
                else    {
                        Wmin[w] = 0;
                        Wmax[w] = 0;
                        Round[w] = 0;
                        }
                w++;
                }
        }
//---------------------------------------------------------------------------










//---------------------------------------------------------------------------
//                            ��������� Parts
//---------------------------------------------------------------------------
AnsiString part;
AnsiString shape;
while (A.SubString(1,6) != "[nets]" )
        {
        RPins.getline (s, sizeof(s)) ;
        A = s;
        A = A.Trim();
        if(A.SubString(1,5) == "part:" )
                {
                i = PROB(A,1);
                part = A.SubString(i,(A.Length()-i+1));
                }
        if(A.SubString(1,6) == "shape:" )
                {
                i = PROB(A,1);
                shape = ex_str(A, &i);
                AnsiString S = part + " " + shape;
                Form1->ListBox2_Shape->Items->Add(S);
                }
        }
//---------------------------------------------------------------------------










//---------------------------------------------------------------------------
//                     ��������� Vias of branch traces
//---------------------------------------------------------------------------
int stub = 0;
while (stub < (CFile - index_NETS)/3)
        {
        STUB_ID  [stub] = 0;
        STUB_SIZE[stub] = 0;
        stub++;
        }
stub = 0;
while (A.SubString(1,7) != "[texts]" )
        {
        RPins.getline (s, sizeof(s)) ;
        A = s;
        A = A.Trim();
        if(A.SubString(1,3) == "vtx" )
                {
                i = PROB(A,8);
                if (i)  {
                        long Stub = ex_float(A, &i);
                        if (Stub)
                                {
                                i = PROB(A,6);
                                long V = ex_float(A, &i);
                                if (V)  {
                                        STUB_ID  [stub] = Stub;
                                        STUB_SIZE[stub] = V;
                                        stub++;
                                        if (stub >= (CFile - index_NETS)/3 - 1) stub--;
                                        }
                                }
                        }
                }
        }
RPins.close();
//
A = Form1->OpenDialog1->FileName;
ifstream RD (A.c_str());
A = ExtractFilePath(Application->ExeName);
A = A + "_RND.fpc";
ofstream WR (A.c_str());
//Form1->Label5->Visible = true;
Form1->Label5->Caption = "PADS";
int MP = CFile/49;
Form1->ProgressBar1->Position = 0;
Application->ProcessMessages();
//---------------------------------------------------------------------------











//---------------------------------------------------------------------------
//                              BEGIN RND ALL
//---------------------------------------------------------------------------
AnsiString Ann,An,A2,A3,A4,A5,Ab,Abb;
long WPad1      = 0;
long WPad2      = 0;
long WTmin,WTmax;
//if( GlobalUnits == 2 )  //MM
//        {
        WTmin   = (long)(StrToFloat(Str_Float_Format(Form1->WRangeMin->Text))*_MM_TO_NM);
        WTmax   = (long)(StrToFloat(Str_Float_Format(Form1->WRangeMax->Text))*_MM_TO_NM);
//        }
//else if( GlobalUnits == 1 )  //NM
//        {
//        WTmin   = (long)(StrToFloat(Str_Float_Format(Form1->WRangeMin->Text)));
//        WTmax   = (long)(StrToFloat(Str_Float_Format(Form1->WRangeMax->Text)));
//        }
//else    {          //MIL
//        WTmin   = (long)(StrToFloat(Str_Float_Format(Form1->WRangeMin->Text))*_25400);
//        WTmax   = (long)(StrToFloat(Str_Float_Format(Form1->WRangeMax->Text))*_25400);
//        }
long Angmin  = (long)(StrToFloat(Str_Float_Format(Form1->WAngmin->Text)));
long Angmax  = (long)(StrToFloat(Str_Float_Format(Form1->WAngmax->Text)));
double rds      = 0;
bool Locked     = false;
bool GLOBAL_ENPART = false;
bool G_ENABLE_RND = false;
bool WR_A3 = false;
#define A3_already_written  WR_A3 = true
#define A3_yet_written      WR_A3 == false
int currentIndex1 = -1;
int currentIndex2 = -1;
int HatchPattern;
int CountCorners;
int LastSeg;
int NM = 0;
int ceof = 0;
CFile = 0;
//--------------------------  Start  ----------------------------------------
while (1)
{
WR_A3 = false;
if (A.SubString(1,5) == "[end]" )
        break;
if (!RD.eof())
        {
        RD.getline (s, sizeof(s)) ;
        Ann = s;
        Ann = Ann.Trim();
        }
else    ceof++;
if(ceof > 3)
        break;
CFile++;
if (CFile%MP == 0)
        {
        Form1->ProgressBar1->Position++;
        Application->ProcessMessages();
        }
//---------------------------------------------------------------------------








//---------------------------------------------------------------------------
//                               RND PADS
//---------------------------------------------------------------------------
if (CheckRndPads)
        {
        if (A3.SubString(1,7) == "[board]") CheckRndPads = false;
        if (A3.SubString(1,10) == "top_pad: 2")
                {
                if (Form1->RndRectPads->Checked)
                        {
                        if (NM == 1)            rds = Rad*_MM_TO_NM;
                        else if (NM == 0)       rds = Rad*39.37;
                        i = PROB(A3,2);
                        D = ex_float(A3, &i);
                        if (rds >= D/SharePads) rds = D/SharePads;
                        D = D/2;
                        if (NM == true) D = (int)D;
                        int n = PROB(A3,2);
                        B = "top_pad: 4 " + A3.SubString(n,(i-n));
                        B = B + " " + D + " " + D + " " + rds;
                        i = PROB(A3,6);
                        if (i == 0) B = B + " 0";
                        else B = B + " " + A3.SubString(i,1);
                        B = StringReplace(B,",",".",TReplaceFlags()<<rfReplaceAll);
                        WR << B.c_str() << endl;
                        A3_already_written;
                        }
                }
        else if (A3.SubString(1,10) == "top_pad: 3")
                {
                if (Form1->RndRectPads->Checked)
                        {
                        if (NM == 1)            rds = Rad*_MM_TO_NM;
                        else if (NM == 0)       rds = Rad*39.37;
                        i = PROB(A3,2);
                        D = ex_float(A3, &i);
                        F = ex_float(A3, &i);
                        if (rds >= D/SharePads) rds = D/SharePads;
                        if (rds >= F*2/SharePads) rds = F*2/SharePads;
                        i = PROB(A3,5);
                        int n = PROB(A3,2);
                        B = "top_pad: 4 " + A3.SubString(n,(i-n));
                        B = B + rds;
                        i = PROB(A3,6);
                        if (i == 0) B = B + " 0";
                        else B = B + " " + A3.SubString(i,1);
                        B = StringReplace(B,",",".",TReplaceFlags()<<rfReplaceAll);
                        WR << B.c_str() << endl;
                        A3_already_written;
                        }
                }
        else if (A3.SubString(1,10) == "top_pad: 4")
                {
                if (Form1->RectPads->Checked)
                        {
                        A3 = StringReplace(A3,": 4",": 3",TReplaceFlags()<<rfReplaceAll);
                        WR << A3.c_str() << endl;
                        A3_already_written;
                        }
                else if (Form1->OnlyR->Checked)
                        {
                        // empty
                        }
                else    {
                        if (NM == 1)            rds = Rad*_MM_TO_NM;
                        else if (NM == 0)       rds = Rad*39.37;
                        i = PROB(A3,2);
                        D = ex_float(A3, &i);
                        F = ex_float(A3, &i);
                        if (rds >= D/SharePads) rds = D/SharePads;
                        if (rds >= F*2/SharePads) rds = F*2/SharePads;
                        i = PROB(A3,5);
                        B = A3.SubString(1,(i-1));
                        B = B + rds;
                        i = PROB(A3,6);
                        if (i == 0) B = B + " 0";
                        else B = B + " " + A3.SubString(i,1);
                        B = StringReplace(B,",",".",TReplaceFlags()<<rfReplaceAll);
                        WR << B.c_str() << endl;
                        A3_already_written;
                        }
                }
        else if (A3.SubString(1,13) == "bottom_pad: 2")
                {
                if (Form1->RndRectPads->Checked)
                        {
                        if (NM == 1)            rds = Rad*_MM_TO_NM;
                        else if (NM == 0)       rds = Rad*39.37;
                        i = PROB(A3,2);
                        D = ex_float(A3, &i);
                        if (rds >= D/SharePads) rds = D/SharePads;
                        D = D/2;
                        if (NM == true) D = (int)D;
                        int n = PROB(A3,2);
                        B = "bottom_pad: 4 " + A3.SubString(n,(i-n));
                        B = B + " " + D + " " + D + " " + rds;
                        i = PROB(A3,6);
                        if (i == 0) B = B + " 0";
                        else B = B + " " + A3.SubString(i,1);
                        B = StringReplace(B,",",".",TReplaceFlags()<<rfReplaceAll);
                        WR << B.c_str() << endl;
                        A3_already_written;
                        }
                }
        else if (A3.SubString(1,13) == "bottom_pad: 3")
                {
                if (Form1->RndRectPads->Checked)
                        {
                        if (NM == 1)            rds = Rad*_MM_TO_NM;
                        else if (NM == 0)       rds = Rad*39.37;
                        i = PROB(A3,2);
                        i = PROB(A3,2);
                        D = ex_float(A3, &i);
                        F = ex_float(A3, &i);
                        if (rds >= D/SharePads) rds = D/SharePads;
                        if (rds >= F*2/SharePads) rds = F*2/SharePads;
                        i = PROB(A3,5);
                        int n = PROB(A3,2);
                        B = "bottom_pad: 4 " + A3.SubString(n,(i-n));
                        B = B + " " + rds;
                        i = PROB(A3,6);
                        if (i == 0) B = B + " 0";
                        else B = B + " " + A3.SubString(i,1);
                        B = StringReplace(B,",",".",TReplaceFlags()<<rfReplaceAll);
                        WR << B.c_str() << endl;
                        A3_already_written;
                        }
                }
        else if (A3.SubString(1,13) == "bottom_pad: 4")
                {
                if (Form1->RectPads->Checked)
                        {
                        A3 = StringReplace(A3,": 4",": 3",TReplaceFlags()<<rfReplaceAll);
                        WR << A3.c_str() << endl;
                        A3_already_written;
                        }
                else if (Form1->OnlyR->Checked)
                        {
                        // empty
                        }
                else    {
                        if (NM == 1)            rds = Rad*_MM_TO_NM;
                        else if (NM == 0)       rds = Rad*39.37;
                        i = PROB(A3,2);
                        D = ex_float(A3, &i);
                        F = ex_float(A3, &i);
                        if (rds >= D/SharePads) rds = D/SharePads;
                        if (rds >= F*2/SharePads) rds = F*2/SharePads;
                        i = PROB(A3,5);
                        B = A3.SubString(1,(i-1));
                        B = B + rds;
                        i = PROB(A3,6);
                        if (i == 0) B = B + " 0";
                        else B = B + " " + A3.SubString(i,1);
                        B = StringReplace(B,",",".",TReplaceFlags()<<rfReplaceAll);
                        WR << B.c_str() << endl;
                        A3_already_written;
                        }
                }
        else if (A3.SubString(1,5) == "units")
                {
                i = PROB(A3,1);
                if (A3.UpperCase().SubString(i,2) == "NM")       NM = 1;
                else if (A3.UpperCase().SubString(i,2) == "MI")  NM = 0;
                else                                             NM = 2;
                }
        else if (A3.SubString(1,4) == "name")
                {
                ftpr = A3;
                }
        }// CheckRndPads
//---------------------------------------------------------------------------









//---------------------------------------------------------------------------
//                BEGIN RND TRACE, AREA, OVAL VIA, OVAL PAD
//---------------------------------------------------------------------------
if (A.SubString(1,6) == "[nets]")
        {
        Form1->Label5->Caption = "Traces, Areas, Vias";
        Application->ProcessMessages();
        }
//---------------------------------------------------------------------------










//---------------------------------------------------------------------------
//                          loading PinsOfNet
//---------------------------------------------------------------------------
if (A5.SubString(1,4) == "net:" )
        {
        Form1->ListBox3_PinsOfNet->Items->Clear();
        }
if (A4.SubString(1,4) == "pin:" )
        {
        i = PROB(A4, 2);
        AnsiString S = A4.SubString(i,(A4.Length()-i+1));
        Form1->ListBox3_PinsOfNet->Items->Add(S);
        }
//---------------------------------------------------------------------------
//                           find pins index
//---------------------------------------------------------------------------
if (A3.SubString(1,7) == "connect" )
        {
        G_ENABLE_RND = false;
        if (Form1->PartList->SelCount < Form1->PartList->Count/2) GLOBAL_ENPART = false;
        else GLOBAL_ENPART = true;
        i = PROB(A3, 2);
        int In1 = (int)ex_float(A3, &i);
        int In2 = (int)ex_float(A3, &i);
        if (In1 >= Form1->ListBox3_PinsOfNet->Items->Count || In2 >= Form1->ListBox3_PinsOfNet->Items->Count)
        {
                ShowMessage("    Error! Pin index more bounds of ListBox3_PinsOfNet container!");
        }
        i = PROB(A3, 5);
        Locked = (bool)ex_float(A3, &i);
        if (Form1->EnLocked->Checked) Locked = false;
        currentIndex1 = -1;
        currentIndex2 = -1;
        if (In1 >= 0)
                {
                part = Form1->ListBox3_PinsOfNet->Items->operator [](In1);
                i = part.Pos(".");
                if (i <= 0)
                        {
                        ShowMessage ("    Error! symbol \".\" not found in string: " + part);
                        exit(0);
                        }
                if (Form1->TracesOfParts->Checked)
                        {
                        int ind = Form1->PartList->Items->IndexOf(part.SubString(1,(i-1)));
                        if (ind >= 0)
                                {
                                if (Form1->PartList->Selected[ind] && Form1->PartList->SelCount < Form1->PartList->Count/2)
                                        GLOBAL_ENPART = true;
                                if (!Form1->PartList->Selected[ind] && Form1->PartList->SelCount >= Form1->PartList->Count/2)
                                        GLOBAL_ENPART = false;
                                }
                        }
                i++;
                AnsiString RefPin = part.SubString(i,(part.Length()-i+1));
                part = part.SubString(1,(i-2)) + " ";
                In1 = -1;
                shape = "";
                while (shape.SubString(1,part.Length()) != part.SubString(1,part.Length()))
                        {
                        In1++;
                        if (In1 >= Form1->ListBox2_Shape->Items->Count)
                                {
                                In1 = -1;
                                break;
                                }
                        shape = Form1->ListBox2_Shape->Items->operator [](In1);
                        }
                if (In1 >= 0)
                        {
                        i = PROB(shape, 1);
                        if (i < shape.Length())
                                {
                                shape = shape.SubString(i,(shape.Length()-i+1));
                                shape = shape + "." + RefPin;
                                In1 = Form1->ListBox1_pins->Items->IndexOf(shape);
                                if (In1 >= 0)
                                        {
                                        currentIndex1 = In1;
                                        }
                                }
                        }
                }
        if (In2 >= 0)
                {
                part = Form1->ListBox3_PinsOfNet->Items->operator [](In2);
                i = part.Pos(".");
                if (i <= 0)
                        {
                        ShowMessage ("    Error! symbol \".\" not found in string: " + part);
                        exit(0);
                        }
                if (Form1->TracesOfParts->Checked)
                        {
                        int ind = Form1->PartList->Items->IndexOf(part.SubString(1,(i-1)));
                        if (ind >= 0)
                                {
                                if (Form1->PartList->Selected[ind] && Form1->PartList->SelCount < Form1->PartList->Count/2)
                                        GLOBAL_ENPART = true;
                                if (!Form1->PartList->Selected[ind] && Form1->PartList->SelCount >= Form1->PartList->Count/2)
                                        GLOBAL_ENPART = false;
                                }
                        }
                i++;
                AnsiString RefPin = part.SubString(i,(part.Length()-i+1));
                part = part.SubString(1,(i-2)) + " ";
                In2 = -1;
                shape = "";
                while (shape.SubString(1,part.Length()) != part.SubString(1,part.Length()))
                        {
                        In2++;
                        if (In2 >= Form1->ListBox2_Shape->Items->Count)
                                {
                                In2 = -1;
                                break;
                                }
                        shape = Form1->ListBox2_Shape->Items->operator [](In2);
                        }
                if (In2 >= 0)
                        {
                        i = PROB(shape, 1);
                        if (i < shape.Length())
                                {
                                shape = shape.SubString(i,(shape.Length()-i+1));
                                shape = shape + "." + RefPin;
                                In2 = Form1->ListBox1_pins->Items->IndexOf(shape);
                                if (In2 >= 0)
                                        {
                                        currentIndex2 = In2;
                                        }
                                }
                        }
                }
        i = PROB(A3, 4);
        LastSeg = (int)ex_float(A3, &i);
        }          
//---------------------------------------------------------------------------











//---------------------------------------------------------------------------
if (A2.SubString(1,3) == "seg")
        {
        //---------------------------------------------------------------------------
        //                       autocorrect trace width
        //---------------------------------------------------------------------------
        i = PROB(A2, 1);
        long CurrSeg = (long) ex_float(A2, &i);
        long Lay     = (long) ex_float(A2, &i);
        long Wid     = (long) ex_float(A2, &i);
        long ViaW    = (long) ex_float(A2, &i);
        long ViaH    = (long) ex_float(A2, &i);
        if (CurrSeg == 1)
                {
                if (currentIndex1 >= 0)
                        {
                        if (Wid > Wmin[currentIndex1] && Form1->AutoCorrWid->Checked && Form1->EnableRndTrace->Checked )
                                {
                                A2 = "seg: 1 ";
                                A2 += Lay;
                                A2 += " ";
                                if (Wmin[currentIndex1]) A2 += AnsiString((long)Wmin[currentIndex1]-(long)Wmin[currentIndex1]/10);
                                else                     A2 += Wid;
                                A2 += " ";
                                A2 += ViaW;
                                A2 += " ";
                                A2 += ViaH;
                                }
                        }
                }
        else if (CurrSeg == LastSeg)
                {
                if (currentIndex2 >= 0)
                        {
                        if (Wid > Wmin[currentIndex2] && Form1->AutoCorrWid->Checked && Form1->EnableRndTrace->Checked )
                                {
                                A2 = "seg: 1 ";
                                A2 += Lay;
                                A2 += " ";
                                if (Wmin[currentIndex2]) A2 += AnsiString((long)Wmin[currentIndex2]-(long)Wmin[currentIndex2]/10);
                                else                     A2 += Wid;
                                A2 += " ";
                                A2 += ViaW;
                                A2 += " ";
                                A2 += ViaH;
                                }
                        }
                }
        //---------------------------------------------------------------------------
        //                           autocorrect radius
        //---------------------------------------------------------------------------
        if      (A.SubString(1,3) == "vtx" && A3.SubString(1,3) == "vtx")
                {
                i = PROB(A, 2);
                double X1 = ex_float(A, &i);
                double Y1 = ex_float(A, &i);
                i = PROB(A3, 2);
                double X2 = ex_float(A3, &i);
                double Y2 = ex_float(A3, &i);
                double Lseg = Length_Line(X1,Y1,X2,Y2);
                long Lmax = 0;
                if (CurrSeg == 1 && currentIndex1 >= 0)              Lmax = Wmax[currentIndex1];
                else if (CurrSeg == LastSeg && currentIndex2 >= 0)   Lmax = Wmax[currentIndex2];
                if (Lseg < Lmax && Form1->AutoCorrRad->Checked)
                        {
                        if (CurrSeg == 1)
                                {
                                if (Wmax[currentIndex1]/Wmin[currentIndex1] > 2)
                                WPad1 = Wmax[currentIndex1];
                                }
                        else if (CurrSeg == LastSeg)
                                {
                                if (Wmax[currentIndex2]/Wmin[currentIndex2] > 2)
                                WPad2 = Wmax[currentIndex2];
                                }
                        }
                }
        }
//---------------------------------------------------------------------------










//---------------------------------------------------------------------------
//                               RND TRACE
//---------------------------------------------------------------------------
if ((A.SubString(1,3) == "vtx")&&
   (A2.SubString(1,3) == "seg")&&
   (A3.SubString(1,3) == "vtx")&&
   (A4.SubString(1,3) == "seg")&&
   (A5.SubString(1,3) == "vtx"))
        {
        Rad_trace_Correct = Rad_trace;
        bool ENABLE_RND = true;
        i = PROB(A,2);
        float X1 = ex_float(A,&i);
        float Y1 = ex_float(A,&i);
        i = PROB(A3,2);
        float X2 = ex_float(A3,&i);
        float Y2 = ex_float(A3,&i);
        i = PROB(A5,2);
        float X3 = ex_float(A5,&i);
        float Y3 = ex_float(A5,&i);
        i = PROB(A2,2);
        float LAYER1 = ex_float(A2,&i);
        float WIDTH1 = ex_float(A2,&i);
        i = PROB(A4,2);
        float LAYER2 = ex_float(A4,&i);
        float WIDTH2 = ex_float(A4,&i);
        i = PROB(A3,6);
        float D_Via = ex_float(A3,&i);
        i = PROB(A3,8);
        int Association_stub = 0;
        if (i)
        Association_stub = ex_float(A3,&i);

        if (D_Via > BY_ZERO)                    ENABLE_RND = false;
        if (LAYER2 != LAYER1)                   ENABLE_RND = false;
        if (!Form1->EnableRndTrace->Checked)    ENABLE_RND = false;
        if(WIDTH1 < BY_ZERO || WIDTH2 < BY_ZERO)ENABLE_RND = false;
        if (Association_stub)                   ENABLE_RND = false;
        if (Locked)                             ENABLE_RND = false;
        if (WIDTH1 < WTmin)                     ENABLE_RND = false;
        if (WIDTH1 > WTmax)                     ENABLE_RND = false;
        if (WIDTH2 < WTmin)                     ENABLE_RND = false;
        if (WIDTH2 > WTmax)                     ENABLE_RND = false;
        if (Form1->TracesOfParts->Checked)
                {
                if (GLOBAL_ENPART == 0)
                        ENABLE_RND = false;
                }
        long DW = WIDTH1 - WIDTH2;
        if( !DW && Rad_trace_Correct < 0.05 )
                ENABLE_RND = false;
        if (ENABLE_RND)
                {
                G_ENABLE_RND = true;
                int VERT=0;
                float An1 = Angle((X1-X2),(Y1-Y2));
                float An2 = Angle((X2-X3),(Y2-Y3));
                float LEN1 = Length_Line(X1,Y1,X2,Y2);
                float LEN2 = Length_Line(X3,Y3,X2,Y2);
                float alpha = ABS(An1 - An2);
                if (alpha > 180) alpha = ABS(alpha - 360);
                if (alpha > 89.98 && alpha < 90.02) alpha = 90.02;
                float TX1 = X1;
                float TX2 = X2;
                float TX3 = X3;
                float TY1 = Y1;
                float TY2 = Y2;
                float TY3 = Y3;
                float saveX = 0;
                float saveY = 0;
                float saveXL = 0;
                float saveYL = 0;
                float saveXR = 0;
                float saveYR = 0;
                double RotX1 = X1;
                double RotX2 = X2;
                double RotX3 = X3;
                double RotY1 = Y1;
                double RotY2 = Y2;
                double RotY3 = Y3;
                bool Direct;
                Rotate_Vertex(&RotX1, &RotY1, -An1);
                Rotate_Vertex(&RotX2, &RotY2, -An1);
                Rotate_Vertex(&RotX3, &RotY3, -An1);
                if (RotY3 > RotY1)      Direct = true;
                else                    Direct = false;
                int swpad1 = WPad1;
                int swpad2 = WPad2;
                double Lrnd = DEFAULT;
                if      (alpha > 5 && alpha <= 90)  Lrnd = ABS(DW/2/tan(alpha*M_PI/180));
                else if (alpha > 90 && alpha < 175) Lrnd = ABS(DW/2/tan((180-alpha)*M_PI/180));
                //
                if (alpha > 5 && alpha < 175 && Lrnd < (MIN(LEN1,LEN2)/2)) for (int repeat=0; repeat<3; repeat++)
                        {
                        A3_already_written;
                        if      (repeat == 1)     VERT = RND_FUNC(TX1,TY1,TX2,TY2,TX3,TY3,Rad_trace_Correct,0,Tsame,MIN_SEG_TRACE,swpad2,swpad1,Angmin,Angmax);
                        else if (repeat == 2)     VERT = RND_FUNC(TX1,TY1,TX2,TY2,TX3,TY3,Rad_trace_Correct,0,Tsame,MIN_SEG_TRACE,swpad1,swpad2,Angmin,Angmax);
                        else if (Form1->TraceRadiusShareW->Checked)
                                {
                                Rad_trace_Correct = (MAX(WIDTH1,WIDTH2)/ShareTrace);
                                Rad_trace_Correct += (ABS(DW)/2/tan(alpha*M_PI/180))/tan(alpha*M_PI/360);
                                if (Rad_trace_Correct > (MIN(LEN1,LEN2)/2/tan(alpha*M_PI/360))) Rad_trace_Correct = MIN(LEN1,LEN2)/2/tan(alpha*M_PI/360);
                                Rad_trace_Correct = Rad_trace_Correct/_MM_TO_NM;
                                VERT = RND_FUNC(TX1,TY1,TX2,TY2,TX3,TY3,Rad_trace_Correct,0,Tsame,MIN_SEG_TRACE,WPad1,WPad2,Angmin,Angmax);
                                }
                        else    {
                                if (Rad_trace_Correct > 98)
                                        {
                                        Rad_trace_Correct = MIN(LEN1,LEN2)/ShareTrace;
                                        if (Rad_trace_Correct > (MIN(LEN1,LEN2)/2)) Rad_trace_Correct = MIN(LEN1,LEN2)/2;
                                        Rad_trace_Correct = Rad_trace_Correct/_MM_TO_NM/tan(alpha*M_PI/360);
                                        if (Rad_trace_Correct < 0) Rad_trace_Correct = 0;
                                        }
                                VERT = RND_FUNC(TX1,TY1,TX2,TY2,TX3,TY3,Rad_trace_Correct,0,Tsame,MIN_SEG_TRACE,WPad1,WPad2,Angmin,Angmax);
                                }
                        if (VERT)
                                { i = 0;
                                while (i<VERT)
                                        {
                                        if (i || repeat)
                                                {
                                                if (DW > 0)     WR << A4.c_str() << endl;
                                                else            WR << A2.c_str() << endl;
                                                }
                                        else if (DW < 0)
                                                {
                                                float corr;
                                                if (Tsame == 2) corr = 1.4;
                                                else corr = 1;
                                                double sX = X_NEW[0] - corr*(ABS(DW)/2/tan(alpha*M_PI/180))*cos(An2*M_PI/180);
                                                double sY = Y_NEW[0] - corr*(ABS(DW)/2/tan(alpha*M_PI/180))*sin(An2*M_PI/180);
                                                WR << "vtx: 1 ";
                                                WR << (long)sX;
                                                WR << " ";
                                                WR << (long)sY;
                                                WR << " 0 0 0 0 0" << endl;
                                                WR << A2.c_str() << endl;
                                                }
                                        WR << "vtx: 1 ";
                                        WR << (long)X_NEW[i];
                                        WR << " ";
                                        WR << (long)Y_NEW[i];
                                        WR << " 0 0 0 0 0" << endl;
                                        i++;
                                        }
                                }
                        else    {
                                if (repeat)
                                        {
                                        if (DW > 0)     WR << A4.c_str() << endl;
                                        else            WR << A2.c_str() << endl;
                                        }
                                WR << "vtx: 1 ";
                                WR << (long)TX2;
                                WR << " ";
                                WR << (long)TY2;
                                WR << " 0 0 0 0 0" << endl;
                                if (repeat == 0) break;
                                }
                        if (repeat == 0)
                                {
                                if (DW > 0)
                                        {
                                        float corr;
                                        if (Tsame == 2) corr = 1.4;
                                        else corr = 1;
                                        saveX = X_NEW[i-1] + corr*(ABS(DW)/2/tan(alpha*M_PI/180))*cos(An1*M_PI/180);
                                        saveY = Y_NEW[i-1] + corr*(ABS(DW)/2/tan(alpha*M_PI/180))*sin(An1*M_PI/180);
                                        saveXL = saveX + (DW/2)*cos((An1+90)*M_PI/180);
                                        saveYL = saveY + (DW/2)*sin((An1+90)*M_PI/180);
                                        saveXR = saveX + (DW/2)*cos((An1-90)*M_PI/180);
                                        saveYR = saveY + (DW/2)*sin((An1-90)*M_PI/180);
                                        }
                                else    {
                                        saveX = X_NEW[i-1];
                                        saveY = Y_NEW[i-1];
                                        saveXL = X_NEW[0] - (ABS(DW)/2/tan(alpha*M_PI/180))*cos(An2*M_PI/180) + (DW/2)*cos((An2+90)*M_PI/180);
                                        saveYL = Y_NEW[0] - (ABS(DW)/2/tan(alpha*M_PI/180))*sin(An2*M_PI/180) + (DW/2)*sin((An2+90)*M_PI/180);
                                        saveXR = X_NEW[0] - (ABS(DW)/2/tan(alpha*M_PI/180))*cos(An2*M_PI/180) + (DW/2)*cos((An2-90)*M_PI/180);
                                        saveYR = Y_NEW[0] - (ABS(DW)/2/tan(alpha*M_PI/180))*sin(An2*M_PI/180) + (DW/2)*sin((An2-90)*M_PI/180);
                                        }
                                }
                        if (DW > 0)
                                {
                                if (repeat == 0)
                                        {
                                        WR << A4.c_str() << endl;
                                        WR << "vtx: 1 ";
                                        if (Direct)     WR << (long)saveXR;
                                        else            WR << (long)saveXL;
                                        WR << " ";
                                        if (Direct)     WR << (long)saveYR;
                                        else            WR << (long)saveYL;
                                        WR << " 0 0 0 0 0" << endl;
                                        TX1 = X1 + (DW/2/sin(alpha*M_PI/180))*cos(An2*M_PI/180);
                                        TY1 = Y1 + (DW/2/sin(alpha*M_PI/180))*sin(An2*M_PI/180);
                                        TX2 = X2 + (DW/2/sin(alpha*M_PI/180))*cos(An2*M_PI/180);
                                        TY2 = Y2 + (DW/2/sin(alpha*M_PI/180))*sin(An2*M_PI/180);
                                        }
                                else if (repeat == 1)
                                        {
                                        TX2 = X2 - (DW/2/sin(alpha*M_PI/180))*cos(An1*M_PI/180);
                                        TY2 = Y2 - (DW/2/sin(alpha*M_PI/180))*sin(An1*M_PI/180);
                                        TX3 = X1 - (DW/2/sin(alpha*M_PI/180))*cos(An1*M_PI/180);
                                        TY3 = Y1 - (DW/2/sin(alpha*M_PI/180))*sin(An1*M_PI/180);
                                        }
                                else    {
                                        WR << A4.c_str() << endl;
                                        WR << "vtx: 1 ";
                                        if (Direct)     WR << (long)saveXL;
                                        else            WR << (long)saveXR;
                                        WR << " ";
                                        if (Direct)     WR << (long)saveYL;
                                        else            WR << (long)saveYR;
                                        WR << " 0 0 0 0 0" << endl;
                                        }
                                }
                        else if (DW < 0)
                                {
                                if (repeat == 0)
                                        {
                                        TX2 = X2 + (DW/2/sin(alpha*M_PI/180))*cos(An1*M_PI/180);
                                        TY2 = Y2 + (DW/2/sin(alpha*M_PI/180))*sin(An1*M_PI/180);
                                        TX3 = X3 + (DW/2/sin(alpha*M_PI/180))*cos(An1*M_PI/180);
                                        TY3 = Y3 + (DW/2/sin(alpha*M_PI/180))*sin(An1*M_PI/180);
                                        }
                                else if (repeat == 1)
                                        {
                                        WR << A2.c_str() << endl;
                                        WR << "vtx: 1 ";
                                        if (Direct)     WR << (long)saveXL;
                                        else            WR << (long)saveXR;
                                        WR << " ";
                                        if (Direct)     WR << (long)saveYL;
                                        else            WR << (long)saveYR;
                                        WR << " 0 0 0 0 0" << endl;
                                        WR << A2.c_str() << endl;
                                        WR << "vtx: 1 ";
                                        if (Direct)     WR << (long)saveXR;
                                        else            WR << (long)saveXL;
                                        WR << " ";
                                        if (Direct)     WR << (long)saveYR;
                                        else            WR << (long)saveYL;
                                        WR << " 0 0 0 0 0" << endl;
                                        TX1 = X3 - (DW/2/sin(alpha*M_PI/180))*cos(An2*M_PI/180);
                                        TY1 = Y3 - (DW/2/sin(alpha*M_PI/180))*sin(An2*M_PI/180);
                                        TX2 = X2 - (DW/2/sin(alpha*M_PI/180))*cos(An2*M_PI/180);
                                        TY2 = Y2 - (DW/2/sin(alpha*M_PI/180))*sin(An2*M_PI/180);
                                        }
                                }
                        else break;
                        if (repeat == 2)
                                {
                                if (DW > 0)     WR << A4.c_str() << endl;
                                else            WR << A2.c_str() << endl;
                                WR << "vtx: 1 ";
                                WR << (long)saveX;
                                WR << " ";
                                WR << (long)saveY;
                                WR << " 0 0 0 0 0" << endl;
                                }
                        if (Rad_trace_Correct < 0) Rad_trace_Correct = 0;
                        An1 = An1 + An2;
                        An2 = An1 - An2;
                        An1 = An1 - An2;
                        TX1 = TX1 + TX3;
                        TX3 = TX1 - TX3;
                        TX1 = TX1 - TX3;
                        TY1 = TY1 + TY3;
                        TY3 = TY1 - TY3;
                        TY1 = TY1 - TY3;
                        }
                }
        }
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
//                                 pad1
//---------------------------------------------------------------------------
if ( A4.SubString(1,7) == "connect" &&
     A3.SubString(1,3) == "vtx" &&
     A2.SubString(1,3) == "seg" &&
     A.SubString(1,3) == "vtx" &&
     currentIndex1 >= 0)
	{
	//pad1
	i = PROB(A3,2);
        float X = ex_float(A3,&i);
        float Y = ex_float(A3,&i);
	i = PROB(A,2);
        float Xn = ex_float(A,&i);
        float Yn = ex_float(A,&i);
	i = PROB(A2,3);
        float WIDTH = ex_float(A2,&i);
        float pnx = 0;
        float pny = 0;
        if     ((A5.SubString(1,3) == "vtx")&&
                (A4.SubString(1,3) == "seg"))
                {
                i = PROB(A5,2);
                pnx = ex_float(A5,&i);
                pny = ex_float(A5,&i);
                }
	float LenPad = StrToFloat(Form1->ValueLengthPads->Items->operator [](Form1->ValueLengthPads->ItemIndex)) ;
        bool ENABLE_PAD = true;
	if (ABS(pnx) > BY_ZERO || ABS(pny) > BY_ZERO)
                {
                if ( Test_angle_between(pnx,pny,Xn,Yn,X,Y,2/*test on 90 degree*/) < 0)
                   	ENABLE_PAD = false;
                }
	if (Wmin[currentIndex1] == 0)
		ENABLE_PAD = false;
        if (Wmin[currentIndex1] <= WIDTH)
		ENABLE_PAD = false;
        if (!Form1->EnableOvalPads->Checked)
		ENABLE_PAD = false;
        if (Locked)                                     
		ENABLE_PAD = false;
        if (Round[currentIndex1] == true && Form1->RoundedPads->Checked == false )    
		ENABLE_PAD = false;
        if (Round[currentIndex1] == false && Form1->RectanglePads->Checked == false ) 
		ENABLE_PAD = false;
        if (ENABLE_PAD)
                {
                bool Flag = VIA_FUNC(X,Y,X,Y,Xn,Yn, 99,Wmin[currentIndex1],LenPad,WIDTH,WIDTH,1,G_ENABLE_RND);
                if (Flag && X_NEW[0] && Y_NEW[0])
                        {
                        WR << A3.c_str() << endl;
                        WR << A2.c_str() << endl;
                        WR << "vtx: 1 ";
                        WR << (long)X_NEW[0];
                        WR << " ";
                        WR << (long)Y_NEW[0];
                        WR << " 0 0 0 0 0";
                        WR << endl;
                        WR << A2.c_str() << endl;
                        WR << "vtx: 1 ";
                        WR << (long)X_NEW[1];
                        WR << " ";
                        WR << (long)Y_NEW[1];
                        WR << " 0 0 0 0 0";
                        WR << endl;
                        WR << A2.c_str() << endl;
                        WR << "vtx: 1 ";
                        WR << (long)X_NEW[2];
                        WR << " ";
                        WR << (long)Y_NEW[2];
                        WR << " 0 0 0 0 0";
                        WR << endl;
                        WR << A2.c_str() << endl;
                        WR << "vtx: 1 ";
                        WR << (long)X_NEW[0];
                        WR << " ";
                        WR << (long)Y_NEW[0];
                        WR << " 0 0 0 0 0";
                        WR << endl;
                        A3_already_written;
                        }
                }
	}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
//                              pad2 & vias
//---------------------------------------------------------------------------
if ( A5.SubString(1,3) == "vtx" &&
     A4.SubString(1,3) == "seg" &&
     A3.SubString(1,3) == "vtx" )
	{
	i = PROB(A5,2);
        float Xb = ex_float(A5,&i);
        float Yb = ex_float(A5,&i);
	i = PROB(A3,2);
        float X = ex_float(A3,&i);
        float Y = ex_float(A3,&i);
        i = PROB(A4,3);
        float WIDTH = ex_float(A4,&i);
        float pbx = 0;
        float pby = 0;
        if     ((Abb.SubString(1,3) == "vtx")&&
                (Ab.SubString(1,3) == "seg"))
                {
                i = PROB(Abb,2);
                pbx = ex_float(Abb,&i);
                pby = ex_float(Abb,&i);
                }
	if (A2.SubString(1,3) != "seg" && currentIndex2 >= 0)
		{
		//pad2
		float LenPad = StrToFloat(Form1->ValueLengthPads->Items->operator [](Form1->ValueLengthPads->ItemIndex)) ;
        	bool ENABLE_PAD = true;
		if (ABS(pbx) > BY_ZERO || ABS(pby) > BY_ZERO)
                	{
                	if ( Test_angle_between(pbx,pby,Xb,Yb,X,Y,2) < 0)
                   		ENABLE_PAD = false;
                	}
		if (Wmin[currentIndex2] == 0)
			ENABLE_PAD = false;
        	if (Wmin[currentIndex2] <= WIDTH)
			ENABLE_PAD = false;
       		if (!Form1->EnableOvalPads->Checked)            
			ENABLE_PAD = false;
        	if (Locked)                                     
			ENABLE_PAD = false;
        	if (Round[currentIndex2] == true && Form1->RoundedPads->Checked == false )    
			ENABLE_PAD = false;
        	if (Round[currentIndex2] == false && Form1->RectanglePads->Checked == false )
			ENABLE_PAD = false;
        	if (ENABLE_PAD)
                	{
                	bool Flag = VIA_FUNC(X,Y,X,Y,Xb,Yb, 99,Wmin[currentIndex2],LenPad,WIDTH,WIDTH,1,G_ENABLE_RND);
                	if (Flag && X_NEW[0] && Y_NEW[0])
                        	{
                                WR << "vtx: 1 ";
                                WR << (long)X_NEW[0];
                                WR << " ";
                                WR << (long)Y_NEW[0];
                                WR << " 0 0 0 0 0";
                                WR << endl;
                                WR << A4.c_str() << endl;
                                WR << "vtx: 1 ";
                                WR << (long)X_NEW[1];
                                WR << " ";
                                WR << (long)Y_NEW[1];
                                WR << " 0 0 0 0 0";
                                WR << endl;
                                WR << A4.c_str() << endl;
                                WR << "vtx: 1 ";
                                WR << (long)X_NEW[2];
                                WR << " ";
                                WR << (long)Y_NEW[2];
                                WR << " 0 0 0 0 0";
                                WR << endl;
                                WR << A4.c_str() << endl;
                                WR << "vtx: 1 ";
                                WR << (long)X_NEW[0];
                                WR << " ";
                                WR << (long)Y_NEW[0];
                                WR << " 0 0 0 0 0";
                                WR << endl;
                                WR << A4.c_str() << endl;
                                WR << A3.c_str() << endl;
                                A3_already_written;
                        	}
                	}
		}
	else	{
		i = PROB(A3,6);
                int DVia = ex_float(A3,&i);
		float Xn=0, Yn=0, WIDTHn=0, pnx=0, pny=0;
		bool ENABLE_VIA_b = true;
		bool ENABLE_VIA_n = true;
                if( !Form1->EnableOvalVia->Checked )
                        {
                        ENABLE_VIA_b = false;
		        ENABLE_VIA_n = false;
                        }
		if (	A2.SubString(1,3) == "seg" &&
     			A.SubString(1,3) == "vtx" )
			{
			//post via
			i = PROB(A,2);
        		Xn = ex_float(A,&i);
        		Yn = ex_float(A,&i); 
			i = PROB(A2,3);
        		WIDTHn = ex_float(A2,&i);
        		if     ((Ann.SubString(1,3) == "vtx")&&
                		(An.SubString(1,3) == "seg"))
                		{
                		i = PROB(Abb,2);
                		pnx = ex_float(Ann,&i);
                		pny = ex_float(Ann,&i);
                		}
			}
		else	{
			ENABLE_VIA_n = false;
			if (DVia < BY_ZERO)
				{
				i = PROB(A3,1);
        			int n_corner = ex_float(A3,&i);
				if (n_corner == (LastSeg+1))
                			{
                			i = PROB(A3,8);
                			int ID = ex_float(A3,&i);
					// Branch
                			if (ID) DVia = ViaOfStub (ID);
					}
                		}
			}
		if (Locked || DVia < BY_ZERO || DVia >= SizeVia*_MM_TO_NM)
			{
			ENABLE_VIA_b = false;	
			ENABLE_VIA_n = false;
			}
		if (ABS(pbx) > BY_ZERO || ABS(pby) > BY_ZERO)
                	{
                	if ( Test_angle_between(pbx,pby,Xb,Yb,X,Y,2) < 0)
                		ENABLE_VIA_b = false;
                	}
		if (ABS(pnx) > BY_ZERO || ABS(pny) > BY_ZERO)
                	{
                	if ( Test_angle_between(pnx,pny,Xn,Yn,X,Y,2) < 0)
                		ENABLE_VIA_n = false;
                	}
		if ( ENABLE_VIA_b )
                	{
                	bool Flag = VIA_FUNC(X,Y,X,Y,Xb,Yb,SizeVia,DVia,LenVia,WIDTH,WIDTH,Form1->NewStyle->Checked,G_ENABLE_RND);
                	if (Flag)
                        	{
                        	if ( X_NEW[0] && Y_NEW[0] && !Form1->NewStyle->Checked)
                                	{
                                	WR << "vtx: 1 ";
                                	WR << (long)X_NEW[0];
                                	WR << " ";
                                	WR << (long)Y_NEW[0];
                                	WR << " 0 0 0 0 0";
                                	WR << endl;
                                	i = PROB(A4,3);
                                	WR << A4.SubString(1,(i-1)).c_str();
                                	WR << AnsiString((long)DVia).c_str();
                                	WR << " 0 0";
                                	WR << endl;
                                	}
                        	else if ( X_NEW[0] && Y_NEW[0])
                                	{
                                	WR << "vtx: 1 ";
                                	WR << (long)X_NEW[0];
                                	WR << " ";
                                	WR << (long)Y_NEW[0];
                                	WR << " 0 0 0 0 0";
                                	WR << endl;
                                	WR << A4.c_str() << endl;
                                	WR << "vtx: 1 ";
                                	WR << (long)X_NEW[1];
                                	WR << " ";
                                	WR << (long)Y_NEW[1];
                                	WR << " 0 0 0 0 0";
                                	WR << endl;
                                	WR << A4.c_str() << endl;
                                	WR << "vtx: 1 ";
                                	WR << (long)X_NEW[2];
                                	WR << " ";
                                	WR << (long)Y_NEW[2];
                                	WR << " 0 0 0 0 0";
                                	WR << endl;
                                	WR << A4.c_str() << endl;
                                	WR << "vtx: 1 ";
                                	WR << (long)X_NEW[0];
                                	WR << " ";
                                	WR << (long)Y_NEW[0];
                                	WR << " 0 0 0 0 0";
                                	WR << endl;
                                	WR << A4.c_str() << endl;
                                	}
				}
                        }
                if (A3_yet_written)
		        WR << A3.c_str() << endl;
                A3_already_written;
		if ( ENABLE_VIA_n )
                	{
                	bool Flag = VIA_FUNC(X,Y,X,Y,Xn,Yn,SizeVia,DVia,LenVia,WIDTHn,WIDTHn,Form1->NewStyle->Checked,G_ENABLE_RND);
                	if (Flag)
                        	{
                        	if ( X_NEW[0] && Y_NEW[0] && !Form1->NewStyle->Checked)
                                	{
                                        i = PROB(A2,3);
                                	WR << A2.SubString(1,(i-1)).c_str();
                                	WR << AnsiString((long)DVia).c_str();
                                	WR << " 0 0";
                                	WR << endl;
                                	WR << "vtx: 1 ";
                                	WR << (long)X_NEW[0];
                                	WR << " ";
                                	WR << (long)Y_NEW[0];
                                	WR << " 0 0 0 0 0";
                                	WR << endl;
                                	}
                        	else if ( X_NEW[0] && Y_NEW[0])
                                	{
                                        WR << A2.c_str() << endl;
                                	WR << "vtx: 1 ";
                                	WR << (long)X_NEW[0];
                                	WR << " ";
                                	WR << (long)Y_NEW[0];
                                	WR << " 0 0 0 0 0";
                                	WR << endl;
                                	WR << A2.c_str() << endl;
                                	WR << "vtx: 1 ";
                                	WR << (long)X_NEW[1];
                                	WR << " ";
                                	WR << (long)Y_NEW[1];
                                	WR << " 0 0 0 0 0";
                                	WR << endl;
                                	WR << A2.c_str() << endl;
                                	WR << "vtx: 1 ";
                                	WR << (long)X_NEW[2];
                                	WR << " ";
                                	WR << (long)Y_NEW[2];
                                	WR << " 0 0 0 0 0";
                                	WR << endl;
                                	WR << A2.c_str() << endl;
                                	WR << "vtx: 1 ";
                                	WR << (long)X_NEW[0];
                                	WR << " ";
                                	WR << (long)Y_NEW[0];
                                	WR << " 0 0 0 0 0";
                                	WR << endl;
                                	}
				}
                        }
		}
	}
//---------------------------------------------------------------------------






//---------------------------------------------------------------------------
//******************              RND AREA            ***********************
//---------------------------------------------------------------------------
if (A3.SubString(1,6) == "corner" && A4.SubString(1,4) == "area")
        {
        i = PROB(A4, 2);
        CountCorners =          ex_float(A4, &i);
        i = PROB(A4, 4);
        HatchPattern =          ex_float(A4, &i);
        area * AREA = NULL;
        try     {
                AREA = new(std::nothrow) area[CountCorners+1];    //
                }
        catch(std::bad_alloc)
                {
                ShowMessage("    ������ ��������� ������: area[" + AnsiString(CountCorners+1) + "]!" );
                exit(0);
                }
        bool EnableFlag;
        bool EndFlag = false;
        i = PROB(A3, 1);
        int NCorner =           ex_float(A3, &i);
        if (HatchPattern == 0 && Form1->forNone->Checked == 0)  EnableFlag = false;
        if (HatchPattern == 1 && Form1->forFull->Checked == 0)  EnableFlag = false;
        if (HatchPattern == 2 && Form1->forEdge->Checked == 0)  EnableFlag = false;
        if (Form1->EnableRndArea->Checked == 0)                 EnableFlag = false;
        double x;
        double y;
        int Type;
        while (A3.SubString(1,6) == "corner")
                {
                EnableFlag = true;
                if( NCorner == 1 && Form1->RndContour->Checked == 0 ) EnableFlag = false;
                if( NCorner != 1 && Form1->RndCutouts->Checked == 0 ) EnableFlag = false;
                NCorner++;
                if (EnableFlag)
                        {
                        int Step = 0;
                        i = PROB(A3, 2);
                        x = ex_float(A3, &i);
                        y = ex_float(A3, &i);
                        Type = ex_float(A3, &i);
                        EndFlag = ex_float(A3, &i);
                        AREA[0].x1 = x;
                        AREA[0].y1 = y;
                        AREA[0].arc1 = Type;
                        while( EndFlag == 0 )
                                {
                                Abb = Ab;
                                Ab = A5;
                                A5 = A4;
                                A4 = A3;
                                A3 = A2;
                                A2 = A;
                                A = An;
                                An = Ann;
                                RD.getline (s, sizeof(s));
                                Ann = s;
                                Ann = Ann.Trim();
                                CFile++;
                                if (CFile%MP == 0)
                                        {
                                        Form1->ProgressBar1->Position++;
                                        Application->ProcessMessages();
                                        }
                                i = PROB(A3, 2);
                                x = ex_float(A3, &i);
                                y = ex_float(A3, &i);
                                Type = ex_float(A3, &i);
                                EndFlag = ex_float(A3, &i);
                                switch (Step)
                                        {
                                        case 0: AREA[0].x2 = x;
                                                AREA[0].y2 = y;
                                                AREA[0].arc2 = Type;
                                                break;
                                        default:AREA[Step-1].x3 = x;
                                                AREA[Step-1].y3 = y;
                                                AREA[Step].x1 = AREA[Step-1].x2;
                                                AREA[Step].y1 = AREA[Step-1].y2;
                                                AREA[Step].x2 = AREA[Step-1].x3;
                                                AREA[Step].y2 = AREA[Step-1].y3;
                                                AREA[Step].arc1 = AREA[Step-1].arc2;
                                                AREA[Step].arc2 = Type;
                                                break;
                                        }
                                Step++;
                                }
                        AREA[Step-1].x3 = AREA[0].x1;
                        AREA[Step-1].y3 = AREA[0].y1;
                        AREA[Step].x1 = AREA[Step-1].x2;
                        AREA[Step].y1 = AREA[Step-1].y2;
                        AREA[Step].x2 = AREA[0].x1;
                        AREA[Step].y2 = AREA[0].y1;
                        AREA[Step].x3 = AREA[0].x2;
                        AREA[Step].y3 = AREA[0].y2;
                        AREA[Step].arc1 = Type;
                        AREA[Step].arc2 = AREA[0].arc1;
                        int VERT;
                        for (int k=0; k<=Step; k++)
                                {
                                VERT = RND_FUNC(AREA[k].x3,
                                                AREA[k].y3,
                                                AREA[k].x2,
                                                AREA[k].y2,
                                                AREA[k].x1,
                                                AREA[k].y1,
                                                Rad_area,
                                                ShareArea,
                                                Acount,
                                                MIN_SEG_AREA,
                                                0,0,0,180);
                                if (VERT && AREA[k].arc1 == 0 && AREA[k].arc2 == 0)
                                        {
                                        i = 0;
                                        while (X_NEW[i])
                                                {
                                                WR << "corner: 1 ";
                                                WR << (long long)X_NEW[i];
                                                WR << " ";
                                                WR << (long long)Y_NEW[i];
                                                WR << " ";
                                                WR << "0";
                                                WR << " ";
                                                if (k == Step && i == (VERT-1)) WR << "1" << endl;
                                                else                            WR << "0" << endl;
                                                i++;
                                                }
                                        }
                                else    {
                                        WR << "corner: 1 ";
                                        WR << AREA[k].x2;
                                        WR << " ";
                                        WR << AREA[k].y2;
                                        WR << " ";
                                        WR << AREA[k].arc2;
                                        WR << " ";
                                        if (k == Step) WR << "1" << endl;
                                        else           WR << "0" << endl;
                                        }
                                }
                        }
                else    {
                        while (EndFlag == 0 && A3.SubString(1,6) == "corner")
                                {
                                WR << A3.c_str() << endl;
                                Abb = Ab;
                                Ab = A5;
                                A5 = A4;
                                A4 = A3;
                                A3 = A2;
                                A2 = A;
                                A = An;
                                An = Ann;
                                RD.getline (s, sizeof(s));
                                Ann = s;
                                Ann = Ann.Trim();
                                CFile++;
                                if (CFile%MP == 0)
                                        {
                                        Form1->ProgressBar1->Position++;
                                        Application->ProcessMessages();
                                        }
                                i = PROB(A3, 2);
                                x = ex_float(A3, &i);
                                y = ex_float(A3, &i);
                                Type = ex_float(A3, &i);
                                EndFlag = ex_float(A3, &i);
                                }
                        WR << A3.c_str() << endl;
                        }
                Abb = Ab;
                Ab = A5;
                A5 = A4;
                A4 = A3;
                A3 = A2;
                A2 = A;
                A = An;
                An = Ann;
                RD.getline (s, sizeof(s));
                Ann = s;
                Ann = Ann.Trim();
                CFile++;
                }
        if ( AREA ) delete [] AREA;
        }
//---------------------------------------------------------------------------
WPad1 = 0;
WPad2 = 0;
//---------------------------------------------------------------------------
//-----------------            write A3 if no modify      -------------------
//---------------------------------------------------------------------------
if (A3_yet_written)
        WR << A3.c_str() << endl;
//---------------------------------------------------------------------------
//-----------------              ����� �����              -------------------
//-----------------             Shift strings             -------------------
//---------------------------------------------------------------------------
Abb = Ab;
Ab = A5;
A5 = A4;
A4 = A3;
A3 = A2;
A2 = A;
A = An;
An = Ann;
}// while (1)
//---------------------------------------------------------------------------
//-------------------------------- �����-------------------------------------
//--------------------------------- END -------------------------------------
//---------------------------------------------------------------------------
RD.close();
WR << A3.c_str() << endl;
WR << A2.c_str() << endl;
WR << A.c_str() << endl;
WR.close();
//------------------------------------------------
//   ��������� ���������� ����� � ���������
//------------------------------------------------
Form1->Label5->Caption = "Correction";
Application->ProcessMessages();
Sleep(200);
A = ExtractFilePath(Application->ExeName);
if (Form1->ReplaceOrFile->Checked)A = Form1->OpenDialog1->FileName;
else                              A = A + "RoundingRect.fpc";
ofstream outfile (A.c_str());
A = ExtractFilePath(Application->ExeName);
A = A + "_RND.fpc";
ifstream infile (A.c_str());
long C_seg = 0;      //��� �� ���������
long n_str = 0;      //����� ������
bool FLAG_net = false;
while (1)
        {
        infile.getline (s, sizeof(s)) ;
        n_str++;
        if (n_str%MP == 0)
                {
                if (Form1->ProgressBar1->Position < 100) Form1->ProgressBar1->Position++;
                Application->ProcessMessages();
                }
        A = s;
        A = A.Trim();
        if (A.SubString(1,5) == "[end]" ) break;
        if (A.SubString(1,6) == "[nets]" ) FLAG_net = true;
        if (FLAG_net == 0) { outfile << A.c_str() << endl; continue;  }
        else if (A.SubString(1,9) == "connect: " )
                {
                C_seg = count_seg(A,n_str);
                i = PROB(A,4);
                outfile << A.SubString(1,(i-1)).c_str();
                outfile << C_seg;
                i = PROB(A,5);
                outfile << (" " + A.SubString(i,(A.Length()-i+1))).c_str() << endl;
                C_seg = 1;
                }
        else if (A.SubString(1,5) == "vtx: " )
                {
                outfile << "vtx: ";
                outfile << C_seg;
                i = PROB(A,2);
                outfile << " ";
                outfile << A.SubString(i,(A.Length()-i+1)).c_str();
                outfile << endl;
                }
        else if (A.SubString(1,5) == "seg: " )
                {
                outfile << "seg: ";
                outfile << C_seg;
                i = PROB(A,2);
                outfile << " ";
                outfile << A.SubString(i,(A.Length()-i+1)).c_str();
                outfile << endl;
                C_seg++;
                }
        else if (A.SubString(1,6) == "area: " )
                {
                C_seg = count_seg(A,n_str);
                i = PROB(A,2);
                outfile << A.SubString(1,(i-1)).c_str();
                outfile << C_seg;
                i = PROB(A,3);
                outfile << A.SubString((i-1),(A.Length()-i+2)).c_str();
                outfile << endl;
                C_seg = 1;
                }
        else if (A.SubString(1,8) == "corner: " )
                {
                outfile << "corner: ";
                outfile << C_seg;
                i = PROB(A,2);
                outfile << " ";
                outfile << A.SubString(i,(A.Length()-i+1)).c_str();
                outfile << endl;
                C_seg++;
                }
        else outfile << A.c_str() << endl;
        }//while (1)
infile.close();
outfile << A.c_str() << endl;
outfile.close();
delete Round;
delete Wmin;
delete Wmax;
delete STUB_SIZE;
delete STUB_ID;
}