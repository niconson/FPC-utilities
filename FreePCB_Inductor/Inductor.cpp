//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "Inductor.h"
#include "fstream.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#define LTOP 15
#define LBOT 16
TForm1 *Form1;
long DataCirquit[16];
long ViaLocations[32];
long YminC;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
DecimalSeparator = ',';
char s[50];
AnsiString Path = ExtractFilePath(Application->ExeName);
ifstream R( (Path+"Config.txt").c_str() );
R.getline(s,sizeof(s));
Edit1->Text = s;
R.getline(s,sizeof(s));
Edit2->Text = s;
R.getline(s,sizeof(s));
Edit3->Text = s;
R.getline(s,sizeof(s));
Edit4->Text = s;
R.getline(s,sizeof(s));
Edit5->Text = s;
R.getline(s,sizeof(s));
Edit6->Text = s;
R.getline(s,sizeof(s));
Edit7->Text = s;
R.getline(s,sizeof(s));
Edit8->Text = s;
R.getline(s,sizeof(s));
Edit9->Text = s;
R.getline(s,sizeof(s));
Edit10->Text = s;
R.close();
}
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
int pos = STRING_2_DOUBLE.Pos(",");
if (pos > 0 && pos < L)
        {
        AnsiString posStr = STRING_2_DOUBLE.SubString(pos+1,(L-pos));
        if (posStr.Pos(",") > 0) return 0;
        }
if (L > 1)
        {
        AnsiString posStr = STRING_2_DOUBLE.SubString(2,(L-1));
        if (posStr.Pos("-") > 0) return 0;
        }
if  (((STRING_2_DOUBLE.SubString(1,1) == "-")&&(L<2))||(!L)) return 0;
if  (STRING_2_DOUBLE.SubString(1,1) == ",") STRING_2_DOUBLE = "0" + STRING_2_DOUBLE;
if  (STRING_2_DOUBLE.SubString(L,1) == ",") STRING_2_DOUBLE = STRING_2_DOUBLE + "0";
return STRING_2_DOUBLE;
}
//---------------------------------------------------------------------------
void Cirquit(long cX, long cY, long cR, long cZ, bool Direct)
        {
        if (cR < 0) cR = 0;
        if (Form1->RadioButton2->Checked && cR == 0) cR = 30000;
        if (Direct)
                {
                DataCirquit[14] = -cX/2 + cR;
                DataCirquit[15] = -cY/2;
                DataCirquit[12] = -cX/2;
                if (cR == 0)
                        {
                        DataCirquit[13] = cY/2 - YminC;
                        if (DataCirquit[13] > 0) DataCirquit[13] = 0;
                        }
                else    DataCirquit[13] = -cY/2 + cR;
                DataCirquit[10] = -cX/2;
                if (cR == 0)
                        {
                        DataCirquit[11] = -cY/2 + YminC;
                        if (DataCirquit[11] < 0) DataCirquit[11] = 0;
                        }
                else    DataCirquit[11] =  cY/2 - cR;
                DataCirquit[8] = -cX/2 + cR;
                DataCirquit[9] =  cY/2;
                DataCirquit[6] =  cX/2 - cR;
                DataCirquit[7] = cY/2;
                DataCirquit[4] = cX/2;
                if (cR == 0)
                        {
                        DataCirquit[5] = -cY/2 + YminC;
                        if (DataCirquit[5] < 0) DataCirquit[5] = 0;
                        }
                else    DataCirquit[5] = cY/2 - cR;
                DataCirquit[2] = cX/2;
                if (cR == 0)
                        {
                        DataCirquit[3] = cY/2 - YminC + cZ;
                        if (DataCirquit[3] > 0) DataCirquit[3] = 0;
                        }
                else    DataCirquit[3] = -cY/2 + cR + cZ;
                DataCirquit[0] = cX/2 - cR;
                DataCirquit[1] = -cY/2 + cZ;
                }
        else    {
                DataCirquit[0] = -cX/2 + cR;
                DataCirquit[1] = -cY/2;
                DataCirquit[2] = -cX/2;
                if (cR == 0)
                        {
                        DataCirquit[3] = cY/2 - YminC;
                        if (DataCirquit[3] > 0) DataCirquit[3] = 0;
                        }
                else    DataCirquit[3] = -cY/2 + cR;
                DataCirquit[4] = -cX/2;
                if (cR == 0)
                        {
                        DataCirquit[5] = -cY/2 + YminC;
                        if (DataCirquit[5] < 0) DataCirquit[5] = 0;
                        }
                else    DataCirquit[5] =  cY/2 - cR;
                DataCirquit[6] = -cX/2 + cR;
                DataCirquit[7] =  cY/2;
                DataCirquit[8] =  cX/2 - cR;
                DataCirquit[9] = cY/2;
                DataCirquit[10] = cX/2;
                if (cR == 0)
                        {
                        DataCirquit[11] = -cY/2 + YminC;
                        if (DataCirquit[11] < 0) DataCirquit[11] = 0;
                        }
                else    DataCirquit[11] = cY/2 - cR;
                DataCirquit[12] = cX/2;
                if (cR == 0)
                        {
                        DataCirquit[13] = cY/2 - YminC + cZ;
                        if (DataCirquit[13] > 0) DataCirquit[13] = 0;
                        }
                else    DataCirquit[13] = -cY/2 + cR + cZ;
                DataCirquit[14] = cX/2 - cR;
                DataCirquit[15] = -cY/2 + cZ;
                }
        }
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
long X;
long Y;
long W;
long R;
long Z;
long C;
long L;
long ViaW;
long ViaH;
long sh;
float D;
AnsiString S;
S = Form1->Edit1->Text;
D = StrToFloat(Str_Float_Format(S));
D = D*1000000;
X = (long)D - (long)D%2540;
S = Form1->Edit2->Text;
D = StrToFloat(Str_Float_Format(S));
D = D*1000000;
Y = (long)D - (long)D%2540;
S = Form1->Edit3->Text;
D = StrToFloat(Str_Float_Format(S));
D = D*1000000;
W = (long)D - (long)D%2540;
S = Form1->Edit4->Text;
D = StrToFloat(Str_Float_Format(S));
D = D*1000000;
R = (long)D - (long)D%2540;
S = Form1->Edit5->Text;
D = StrToFloat(Str_Float_Format(S));
D = D*1000000;
Z = (long)D - (long)D%2540;
S = Form1->Edit6->Text;
D = StrToFloat(Str_Float_Format(S));
C = (long)D;
S = Form1->Edit7->Text;
D = StrToFloat(Str_Float_Format(S));
L = (long)D;
S = Form1->Edit8->Text;
D = StrToFloat(Str_Float_Format(S));
D = D*1000000;
ViaW = (long)D - (long)D%2540;
S = Form1->Edit9->Text;
D = StrToFloat(Str_Float_Format(S));
D = D*1000000;
ViaH = (long)D - (long)D%2540;
S = Form1->Edit10->Text;
D = StrToFloat(Str_Float_Format(S));
D = D*1000000;
sh = (long)D;
YminC = Y - 2*Z*C;
//
if (RadioButton1->Checked && C > 100)
        {
        ShowMessage("Cirquit value for area: max = 100!");
        return;
        }
if (Z < W)
        {
        ShowMessage("Z value must be greater than W");
        return;
        }
if ((!L)||(!C))
        {
        ShowMessage("Values of 'L' or 'C' must be greater than 0!");
        return;
        }
if (L > 16)
        {
        ShowMessage("L value must be less than 17!");
        return;
        }
int ab;
if (R < Z*C)    ab = X - Z*C*2;
else            ab = X - R*2;
if (ab < (ViaW+Z-W)*(L+1)/2+sh)
        {
        ShowMessage("There is no space for vias!");
        //return;
        }
//
long cX;
long cY;
long cR;
long cZ;
long PointX;
long PointY;
long SHIFT = sh;
long CorrShift;
int NCorner;
int Nsegment;
AnsiString Path = ExtractFilePath(Application->ExeName);
ofstream INDUCTOR ((Path + "Inductor.fpc").c_str());
ofstream TRACE ((Path + "Trace.fpc").c_str());
TRACE << AnsiString("[options]").c_str() << endl << endl;
TRACE << AnsiString("version: 2.028").c_str() << endl << endl;
TRACE << AnsiString("file_version: 2.028").c_str() << endl << endl;
TRACE << AnsiString("units: MM").c_str() << endl;
TRACE << AnsiString("n_copper_layers: ").c_str();
TRACE << AnsiString(L).c_str() << endl << endl;
TRACE << AnsiString("[footprints]").c_str() << endl << endl;
TRACE << AnsiString("name: \"ViaInductor\"").c_str() << endl;
TRACE << AnsiString("units: NM").c_str() << endl;
TRACE << AnsiString("sel_rect: -254000 -254000 254000 254000").c_str() << endl;
TRACE << AnsiString("ref_text: 300000 0 500000 0 50000").c_str() << endl;
TRACE << AnsiString("value_text: 300000 0 0 0 50000").c_str() << endl;
TRACE << AnsiString("centroid: 0 0 0 0").c_str() << endl;
TRACE << AnsiString("n_pins: 1").c_str() << endl;
TRACE << AnsiString("pin: \"1\" ").c_str();
TRACE << AnsiString(ViaH).c_str();
TRACE << AnsiString(" 0 0 0").c_str() << endl;
TRACE << AnsiString("top_pad: 1 ").c_str();
TRACE << AnsiString(ViaW).c_str();
TRACE << AnsiString(" 0 0 0 3").c_str() << endl;
TRACE << AnsiString("inner_pad: 1 ").c_str();
TRACE << AnsiString(ViaW).c_str();
TRACE << AnsiString(" 0 0 0 3").c_str() << endl;
TRACE << AnsiString("bottom_pad: 1 ").c_str();
TRACE << AnsiString(ViaW).c_str();
TRACE << AnsiString(" 0 0 0 3").c_str() << endl << endl;
TRACE << AnsiString("[board]").c_str() << endl << endl;
TRACE << AnsiString("[solder_mask_cutouts]").c_str() << endl << endl;
TRACE << AnsiString("[parts]").c_str() << endl << endl;
TRACE << AnsiString("[nets]").c_str() << endl << endl;
TRACE << AnsiString("net: \"Inductor\" ").c_str();
TRACE << AnsiString(L+1).c_str();
TRACE << AnsiString(" ").c_str();
TRACE << AnsiString(L).c_str();
TRACE << AnsiString(" 0 0 0 0 1").c_str() << endl;
//
INDUCTOR << AnsiString("[options]").c_str() << endl << endl;
INDUCTOR << AnsiString("version: 2.028").c_str() << endl << endl;
INDUCTOR << AnsiString("file_version: 2.028").c_str() << endl << endl;
INDUCTOR << AnsiString("units: MM").c_str() << endl;
INDUCTOR << AnsiString("n_copper_layers: ").c_str();
INDUCTOR << AnsiString(L).c_str() << endl << endl;
INDUCTOR << AnsiString("[footprints]").c_str() << endl << endl;
INDUCTOR << AnsiString("name: \"ViaInductor\"").c_str() << endl;
INDUCTOR << AnsiString("units: NM").c_str() << endl;
INDUCTOR << AnsiString("sel_rect: -254000 -254000 254000 254000").c_str() << endl;
INDUCTOR << AnsiString("ref_text: 300000 0 500000 0 50000").c_str() << endl;
INDUCTOR << AnsiString("value_text: 300000 0 0 0 50000").c_str() << endl;
INDUCTOR << AnsiString("centroid: 0 0 0 0").c_str() << endl;
INDUCTOR << AnsiString("n_pins: 1").c_str() << endl;
INDUCTOR << AnsiString("pin: \"1\" ").c_str();
INDUCTOR << AnsiString(ViaH).c_str();
INDUCTOR << AnsiString(" 0 0 0").c_str() << endl;
INDUCTOR << AnsiString("top_pad: 1 ").c_str();
INDUCTOR << AnsiString(ViaW).c_str();
INDUCTOR << AnsiString(" 0 0 0 3").c_str() << endl;
INDUCTOR << AnsiString("inner_pad: 1 ").c_str();
INDUCTOR << AnsiString(ViaW).c_str();
INDUCTOR << AnsiString(" 0 0 0 3").c_str() << endl;
INDUCTOR << AnsiString("bottom_pad: 1 ").c_str();
INDUCTOR << AnsiString(ViaW).c_str();
INDUCTOR << AnsiString(" 0 0 0 3").c_str() << endl << endl;
INDUCTOR << AnsiString("[board]").c_str() << endl << endl;
INDUCTOR << AnsiString("[solder_mask_cutouts]").c_str() << endl << endl;
INDUCTOR << AnsiString("[parts]").c_str() << endl << endl;
INDUCTOR << AnsiString("[nets]").c_str() << endl << endl;
INDUCTOR << AnsiString("net: \"Inductor\" ").c_str();
INDUCTOR << AnsiString(L+1).c_str();
INDUCTOR << AnsiString(" 0 ").c_str();
INDUCTOR << AnsiString(L).c_str();
INDUCTOR << AnsiString(" 0 0 0 1").c_str() << endl;
for (int lay=1; lay<=L; lay++)
        {
        cX = X;
        cY = Y;
        cR = R;
        cZ = Z;
        TRACE << AnsiString("connect: ").c_str();
        TRACE << AnsiString(lay).c_str();
        TRACE << AnsiString(" ").c_str();
        if (lay%2 == 0) TRACE << AnsiString(lay).c_str();
        else            TRACE << AnsiString(lay-1).c_str();
        TRACE << AnsiString(" ").c_str();
        if (lay%2 == 0) TRACE << AnsiString(lay-1).c_str();
        else            TRACE << AnsiString(lay).c_str();
        TRACE << AnsiString(" ").c_str();
        TRACE << AnsiString(C*8+3).c_str();
        TRACE << AnsiString(" 0").c_str() << endl;
        //
        INDUCTOR << AnsiString("area: ").c_str();
        INDUCTOR << AnsiString(lay).c_str();
        INDUCTOR << AnsiString(" ").c_str();
        INDUCTOR << AnsiString(8+C*16).c_str();
        INDUCTOR << AnsiString(" ").c_str();
        if (L < 3)      INDUCTOR << AnsiString(LTOP-1+lay).c_str();
        else if (lay==1)INDUCTOR << AnsiString(LTOP).c_str();
        else if (lay==L)INDUCTOR << AnsiString(LBOT).c_str();
        else            INDUCTOR << AnsiString(LTOP+lay).c_str();
        //
        if (C>10) INDUCTOR << " 1 0 0" << endl;
        else      INDUCTOR << " 2 0 0" << endl;
        NCorner = 1;
        Nsegment = 1;
        if (lay%2)      CorrShift = 0;
        else            CorrShift = X - 2*R - ViaW - 2*SHIFT;
        //Points of contacts
        for (int PoinT=0; PoinT<4; PoinT++)
                {
                switch(PoinT){
                        case 0: PointX = -X/2 + R + SHIFT + ViaW + CorrShift; PointY = -Y/2 + W; break;
                        case 1: PointY = PointY - Z - ViaW; break;
                        case 2: PointX = PointX - ViaW; break;
                        case 3: PointY = PointY + ViaW + Z - W; break;
                        }
                INDUCTOR << AnsiString("corner: ").c_str();
                INDUCTOR << AnsiString(NCorner).c_str();
                NCorner++;
                INDUCTOR << AnsiString(" ").c_str();
                if (lay%2)      INDUCTOR << AnsiString(PointX).c_str();
                else            INDUCTOR << AnsiString(-PointX).c_str();
                INDUCTOR << AnsiString(" ").c_str();
                INDUCTOR << AnsiString(PointY).c_str();
                INDUCTOR << AnsiString(" 0 0").c_str() << endl;
                if (PoinT >= 2)
                        {
                        int corr = 0;
                        if( Nsegment == 1 )
                                {
                                corr = ViaW/2;
                                }
                        TRACE << AnsiString("vtx: ").c_str();
                        TRACE << AnsiString(Nsegment).c_str();
                        TRACE << AnsiString(" ").c_str();
                        if (lay%2)      TRACE << AnsiString(PointX+corr).c_str();
                        else            TRACE << AnsiString(-PointX-corr).c_str();
                        TRACE << AnsiString(" ").c_str();

                        if (PoinT == 3) corr = W/2;
                        TRACE << AnsiString(PointY + corr).c_str();
                        TRACE << AnsiString(" 0 0 0 0 0").c_str() << endl;
                        TRACE << AnsiString("seg: ").c_str();
                        TRACE << AnsiString(Nsegment).c_str();
                        TRACE << AnsiString(" ").c_str();
                        if (L < 3)      TRACE << AnsiString(LTOP-1+lay).c_str();
                        else if (lay==1)TRACE << AnsiString(LTOP).c_str();
                        else if (lay==L)TRACE << AnsiString(LBOT).c_str();
                        else            TRACE << AnsiString(LTOP+lay).c_str();
                        TRACE << AnsiString(" ").c_str();
                        TRACE << AnsiString((int)W).c_str();
                        TRACE << AnsiString(" 0 0").c_str() << endl;
                        Nsegment++;
                        }
                }
        if (lay == 1)
                {
                ViaLocations[0] = PointX + ViaW/2;
                ViaLocations[1] = PointY - Z + W - ViaW/2;
                }
        for (int q=0; q<C*2; q++)
                {
                if (q)INDUCTOR << " 0" << endl;
                if (q >= C)
                        {
                        long cRcont = cR;
                        if (cRcont < 0) cRcont = 0;
                        if (CorrShift) CorrShift = cX - 2*cRcont - 2*SHIFT - Z + W;
                        if (q == C)
                                {
                                for (int PoinT=0; PoinT<4; PoinT++)
                                        {
                                        switch(PoinT){
                                                case 0: PointX = cX/2 - Z + W - SHIFT - cRcont - ViaW - CorrShift; PointY = -cY/2 + Z - W; break;
                                                case 1: PointY = PointY + Z + ViaW; break;
                                                case 2: PointX = PointX + ViaW; break;
                                                case 3: PointY = PointY - ViaW - Z + W; break;
                                                }
                                        INDUCTOR << AnsiString("corner: ").c_str();
                                        INDUCTOR << AnsiString(NCorner).c_str();
                                        NCorner++;
                                        INDUCTOR << AnsiString(" ").c_str();
                                        if (lay%2)      INDUCTOR << AnsiString(PointX).c_str();
                                        else            INDUCTOR << AnsiString(-PointX).c_str();
                                        INDUCTOR << AnsiString(" ").c_str();
                                        INDUCTOR << AnsiString(PointY).c_str();
                                        INDUCTOR << AnsiString(" 0 0").c_str() << endl;
                                        if (PoinT < 2)
                                                {
                                                TRACE << AnsiString("vtx: ").c_str();
                                                TRACE << AnsiString(Nsegment).c_str();
                                                TRACE << AnsiString(" ").c_str();
                                                int corr = 0;
                                                if (PoinT == 0)
                                                        corr = ViaW;
                                                else if(Nsegment == (C*8+4))
                                                        {
                                                        corr = ViaW/2;
                                                        }
                                                if (lay%2)      TRACE << AnsiString(PointX + corr).c_str();
                                                else            TRACE << AnsiString(-PointX - corr).c_str();
                                                TRACE << AnsiString(" ").c_str();
                                                if(Nsegment != (C*8+4))
                                                        corr = 0;
                                                TRACE << AnsiString(PointY-corr).c_str();
                                                TRACE << AnsiString(" 0 0 0 0 0").c_str() << endl;
                                                if (PoinT < 1)
                                                        {
                                                        TRACE << AnsiString("seg: ").c_str();
                                                        TRACE << AnsiString(Nsegment).c_str();
                                                        TRACE << AnsiString(" ").c_str();
                                                        if (L < 3)      TRACE << AnsiString(LTOP-1+lay).c_str();
                                                        else if (lay==1)TRACE << AnsiString(LTOP).c_str();
                                                        else if (lay==L)TRACE << AnsiString(LBOT).c_str();
                                                        else            TRACE << AnsiString(LTOP+lay).c_str();
                                                        TRACE << AnsiString(" ").c_str();
                                                        TRACE << AnsiString((int)W).c_str();
                                                        TRACE << AnsiString(" 0 0").c_str() << endl;
                                                        }
                                                Nsegment++;
                                                }
                                        }
                                if (lay == 1)
                                        {
                                        ViaLocations[2] = PointX - ViaW/2;
                                        ViaLocations[3] = PointY + Z - W + ViaW/2;
                                        }
                                }
                        Cirquit(cX,cY,cR,cZ,1);
                        cX = cX + Z*2;
                        cY = cY + Z*2;
                        cR = cR + Z;
                        }
                else    {
                        if (Form1->RadioButton2->Checked && q == 0)
                                {
                                cX = cX - W;
                                cY = cY - W;
                                cR = cR - W;
                                cR = cR/1.8;
                                }
                        Cirquit(cX,cY,cR,cZ,0);
                        if (q == (C-1))
                                {
                                cX = cX - W*2;
                                cY = cY - W*2;
                                if (Form1->RadioButton2->Checked) cR = cR - W/1.8;
                                else cR = cR - W;
                                }
                        else    {
                                cX = cX - Z*2;
                                cY = cY - Z*2;
                                if (Form1->RadioButton2->Checked) cR = cR - Z/1.8;
                                else cR = cR - Z;
                                }
                        }
                for (int cir=0; cir<16; cir++)
                        {
                        if (cir%2){
                                INDUCTOR << AnsiString(DataCirquit[cir]).c_str();
                                if (q < C)
                                        {
                                        TRACE << AnsiString(DataCirquit[cir]).c_str();
                                        TRACE << AnsiString(" 0 0 0 0 0").c_str() << endl;
                                        TRACE << AnsiString("seg: ").c_str();
                                        TRACE << AnsiString(Nsegment-1).c_str();
                                        TRACE << AnsiString(" ").c_str();
                                        if (L < 3)      TRACE << AnsiString(LTOP-1+lay).c_str();
                                        else if (lay==1)TRACE << AnsiString(LTOP).c_str();
                                        else if (lay==L)TRACE << AnsiString(LBOT).c_str();
                                        else            TRACE << AnsiString(LTOP+lay).c_str();
                                        TRACE << AnsiString(" ").c_str();
                                        TRACE << AnsiString((int)W).c_str();
                                        TRACE << AnsiString(" 0 0").c_str() << endl;
                                        }
                                if ((cir+3)%4 == 0)
                                        {
                                        if (lay%2)
                                        if (q >= C)     INDUCTOR << AnsiString(" 2").c_str();
                                        else            INDUCTOR << AnsiString(" 1").c_str();
                                        else if (q >= C)INDUCTOR << AnsiString(" 1").c_str();
                                        else            INDUCTOR << AnsiString(" 2").c_str();
                                        }
                                else                    INDUCTOR << AnsiString(" 0").c_str();
                                }
                        else    {
                                if (cir) INDUCTOR << " 0" << endl;
                                INDUCTOR << AnsiString("corner: ").c_str();
                                INDUCTOR << AnsiString(NCorner).c_str();
                                INDUCTOR << AnsiString(" ").c_str();
                                if (lay%2)      INDUCTOR << AnsiString(DataCirquit[cir]).c_str();
                                else            INDUCTOR << AnsiString(-DataCirquit[cir]).c_str();
                                INDUCTOR << AnsiString(" ").c_str();
                                if (q < C)
                                        {
                                        int corr = 0;
                                        if(Nsegment == (C*8+3))
                                                {
                                                corr = ViaW/2;
                                                }
                                        TRACE << AnsiString("vtx: ").c_str();
                                        TRACE << AnsiString(Nsegment).c_str();
                                        TRACE << AnsiString(" ").c_str();
                                        if (lay%2)      TRACE << AnsiString(DataCirquit[cir]+corr).c_str();
                                        else            TRACE << AnsiString(-DataCirquit[cir]-corr).c_str();
                                        TRACE << AnsiString(" ").c_str();
                                        }
                                NCorner++;
                                Nsegment++;
                                }
                        }
                }
        if (lay%2) SHIFT = SHIFT + ViaW + Z - W;
        INDUCTOR << " 1" << endl;
        }
INDUCTOR << AnsiString("[texts]").c_str() << endl << endl;
INDUCTOR << AnsiString("[merges]").c_str() << endl << endl;
INDUCTOR << AnsiString("merge: \"Inductor\"").c_str() << endl;
INDUCTOR << AnsiString("[end]").c_str() << endl;
TRACE << AnsiString("[texts]").c_str() << endl << endl;
TRACE << AnsiString("[merges]").c_str() << endl << endl;
TRACE << AnsiString("merge: \"Inductor\"").c_str() << endl;
TRACE << AnsiString("[end]").c_str() << endl;
INDUCTOR.close();
TRACE.close();
if (Form1->RadioButton1->Checked) S = "Inductor.fpc";
else                              S = "Trace.fpc";
ifstream Corr ((Path + S).c_str());
ofstream OUTP ((Path + "Output.fpc").c_str());
char s[250];
S = "";
while (S.SubString(1,5) != "[end]")
        {
        Corr.getline(s,250);
        S = s;
        if (S.SubString(1,4) == "area")
                {
                int ind1 = 1;
                int ind2 = 1;
                while (S.SubString(ind1,1) != " ")ind1++;
                while (S.SubString(ind1,1) == " ")ind1++;
                while (S.SubString(ind1,1) != " ")ind1++;
                ind2 = ind1;
                while (S.SubString(ind2,1) == " ")ind2++;
                while (S.SubString(ind2,1) != " ")ind2++;
                S = S.SubString(1,ind1) + AnsiString(NCorner-1) + S.SubString(ind2,(S.Length()-ind2+1));
                }
        if (S.SubString(1,6) == "[nets]")
                {
                int X0 = ViaLocations[0];
                int Y0 = ViaLocations[1];
                int SH = 0;
                for (int via=0; via<(L/2+1); via++)
                        {
                        OUTP << AnsiString("part: Via").c_str();
                        OUTP << AnsiString(via).c_str() << endl;
                        OUTP << AnsiString("ref_text: 0 0 0 0 0 0").c_str() << endl;
                        OUTP << AnsiString("package: \"\"").c_str() << endl;
                        OUTP << AnsiString("shape: \"ViaInductor\"").c_str() << endl;
                        OUTP << AnsiString("merge: \"Inductor\"").c_str() << endl;
                        OUTP << (AnsiString("value: \"") + AnsiString(via*2+1) + AnsiString("\" 500000 100000 0 -200000 -1300000 1")).c_str() << endl;
                        OUTP << AnsiString("pos: ").c_str();
                        OUTP << AnsiString(X0 + SH).c_str();
                        OUTP << AnsiString(" ").c_str();
                        OUTP << AnsiString(Y0).c_str();
                        OUTP << AnsiString(" 0 0 0").c_str() << endl << endl;
                        SH = SH + ViaW + Z - W;
                        }
                X0 = ViaLocations[2];
                Y0 = ViaLocations[3];
                SH = 0;
                int st = L/2+1;
                for (int via=st; via<(L/2+L%2+st); via++)
                        {
                        OUTP << AnsiString("part: Via").c_str();
                        OUTP << AnsiString(via).c_str() << endl;
                        OUTP << AnsiString("ref_text: 0 0 0 0 0 0").c_str() << endl;

                        OUTP << AnsiString("package: \"\"").c_str() << endl;
                        OUTP << AnsiString("shape: \"ViaInductor\"").c_str() << endl;
                        OUTP << AnsiString("merge: \"Inductor\"").c_str() << endl;
                        OUTP << (AnsiString("value: \"") + AnsiString((via-st)*2+2) + AnsiString("\" 500000 100000 0 -200000 800000 1")).c_str() << endl;
                        OUTP << AnsiString("pos: ").c_str();
                        OUTP << AnsiString(X0 - SH).c_str();
                        OUTP << AnsiString(" ").c_str();
                        OUTP << AnsiString(Y0).c_str();
                        OUTP << AnsiString(" 0 0 0").c_str() << endl << endl;
                        SH = SH + ViaW + Z - W;
                        }
                }
        OUTP << S.c_str() << endl;
        if (S.SubString(1,3) == "net")
                {
                for (int pinnet=1; pinnet<=(L+1)/2; pinnet++)
                        {
                        OUTP << AnsiString("pin: ").c_str();
                        OUTP << AnsiString(pinnet*2-1).c_str();
                        OUTP << AnsiString(" Via").c_str();
                        OUTP << AnsiString(pinnet-1).c_str();
                        OUTP << AnsiString(".1").c_str() << endl;
                        //
                        OUTP << AnsiString("pin: ").c_str();
                        OUTP << AnsiString(pinnet*2).c_str();
                        OUTP << AnsiString(" Via").c_str();
                        OUTP << AnsiString(pinnet+(L/2)).c_str();
                        OUTP << AnsiString(".1").c_str() << endl;
                        }
                if (L%2 == 0)
                        {
                        OUTP << AnsiString("pin: ").c_str();
                        OUTP << AnsiString(L+1).c_str();
                        OUTP << AnsiString(" Via").c_str();
                        OUTP << AnsiString(L/2).c_str();
                        OUTP << AnsiString(".1").c_str() << endl;
                        }
                }
        }
OUTP.close();
//
//-------------������ ------------
//
SHELLEXECUTEINFO info = {0};
AnsiString fn = ExtractFilePath(Application->ExeName);
fn.SetLength(fn.Length()-1);
fn = ExtractFilePath(fn);
fn.SetLength(fn.Length()-1);
fn = ExtractFilePath(fn) + "freepcb.exe";
AnsiString FN = ("\""+fn+"\"");
AnsiString ps = (Path + "Output.fpc");
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
void __fastcall TForm1::Label12Click(TObject *Sender)
{
ShellExecute(NULL, "open", "https://freepcb.dev", NULL, NULL, SW_SHOWNORMAL);        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
char s[50];
AnsiString Path = ExtractFilePath(Application->ExeName);
ofstream W( (Path+"Config.txt").c_str() );
W << Edit1->Text.c_str() << endl;
W << Edit2->Text.c_str() << endl;
W << Edit3->Text.c_str() << endl;
W << Edit4->Text.c_str() << endl;
W << Edit5->Text.c_str() << endl;
W << Edit6->Text.c_str() << endl;
W << Edit7->Text.c_str() << endl;
W << Edit8->Text.c_str() << endl;
W << Edit9->Text.c_str() << endl;
W << Edit10->Text.c_str() << endl;
W.close();
}
//---------------------------------------------------------------------------
