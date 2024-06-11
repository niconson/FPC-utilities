//---------------------------------------------------------------------------


#pragma hdrstop

#include "Fractional.h"
#include "Debug_Areas.h"
#include "ProcessMessages.h"
#include "fstream.h"
#include "math.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)


void Fractional  (AnsiString NET_AREA,int LayerArea)
{
if (Form1->dwg->Checked == 0) return;
double current__X;
double current__Y;
double cutout_X_value = StrToFloat(Str_Float_Format(Form1->Edit3->Text))*_106;
double cutout_Y_value = StrToFloat(Str_Float_Format(Form1->Edit4->Text))*_106;
double cutout_X2_value = StrToFloat(Str_Float_Format(Form1->Edit5->Text))*_106;
double cutout_Y2_value = StrToFloat(Str_Float_Format(Form1->Edit6->Text))*_106;
if(gUNITS == uMIL)
        {
        cutout_X_value /= PER_MIL;
        cutout_Y_value /= PER_MIL;
        cutout_X2_value /= PER_MIL;
        cutout_Y2_value /= PER_MIL;
        }
if (cutout_X_value < _105 || cutout_Y_value < _105 || cutout_X2_value < _105 || cutout_Y2_value < _105)
        return;
if (cutout_X_value > MM_10 || cutout_Y_value > MM_10 || cutout_X2_value > MM_10 || cutout_Y2_value > MM_10)
        return;
double min_X = AreaRect.Left + cutout_X_value/2 + 1000;//ABS(cutout_X2_value - cutout_X_value);
current__X = min_X;
current__Y = AreaRect.Bottom + cutout_Y_value/2 + 1000;//ABS(cutout_Y2_value - cutout_Y_value);
double max_X = AreaRect.Right - cutout_X_value/2 - 1000;//ABS(cutout_X2_value - cutout_X_value);
double max_Y = AreaRect.Top - cutout_Y_value/2 - 1000;//ABS(cutout_Y2_value - cutout_Y_value);
int count_cut = ((AreaRect.Right-AreaRect.Left)/cutout_X2_value)*((AreaRect.Top-AreaRect.Bottom)/cutout_Y2_value);
Form3->Label4->Caption = AnsiString(count_cut);
Form3->Label1->Caption = "Grid, cutout: ";
Application->ProcessMessages();
int n_cut = 0;
int cnty = 0;
int save_value_CountLinesCut = CountLinesCut;
while (current__Y < max_Y)
        {
        while (current__X < max_X)
                {
                n_cut++;
                Form3->Label3->Caption = AnsiString(n_cut);
                Application->ProcessMessages();
                bool enabled = true;
                double SQRT = sqrt(cutout_X_value*cutout_X_value + cutout_Y_value*cutout_Y_value)/2;
                double PX, PY;
                for (int i=0; i<save_value_CountLinesCut; i++)
                        {
                        if      (MAX(LinesCut[i].X1,LinesCut[i].X2) < (current__X - cutout_X_value/2)) continue;
                        else if (MIN(LinesCut[i].X1,LinesCut[i].X2) > (current__X + cutout_X_value/2)) continue;
                        else if (MAX(LinesCut[i].Y1,LinesCut[i].Y2) < (current__Y - cutout_Y_value/2)) continue;
                        else if (MIN(LinesCut[i].Y1,LinesCut[i].Y2) > (current__Y + cutout_Y_value/2)) continue;
                        else if (Distance(      LinesCut[i].X1,
                                                LinesCut[i].Y1,
                                                LinesCut[i].X2,
                                                LinesCut[i].Y2,
                                                current__X,current__Y,
                                                current__X,current__Y,
                                                &PX,&PY ) > SQRT) continue;
                        enabled = false;
                        break;
                        }
                if (enabled)
                for (int i=0; i<CntLnsArea; i++)
                        {
                        if      (MAX(LinesArea[i].X1,LinesArea[i].X2) < (current__X - cutout_X_value/2)) continue;
                        else if (MIN(LinesArea[i].X1,LinesArea[i].X2) > (current__X + cutout_X_value/2)) continue;
                        else if (MAX(LinesArea[i].Y1,LinesArea[i].Y2) < (current__Y - cutout_Y_value/2)) continue;
                        else if (MIN(LinesArea[i].Y1,LinesArea[i].Y2) > (current__Y + cutout_Y_value/2)) continue;
                        else if (Distance(      LinesArea[i].X1,
                                                LinesArea[i].Y1,
                                                LinesArea[i].X2,
                                                LinesArea[i].Y2,
                                                current__X,current__Y,
                                                current__X,current__Y,
                                                &PX,&PY ) > SQRT) continue;
                        enabled = false;
                        break;
                        }
                if (enabled) 
                if (PointAreaInside(current__X, current__Y, LinesArea, CntLnsArea) == 0) enabled = false;
                if (enabled)
                        {
                        if (Form1->Rect->Checked)
                        Generate_Cutout (       cutout_Y_value,
                                                cutout_X_value,
                                                0, 0, 90,
                                                current__X,
                                                current__Y, -1) ;
                        if (Form1->Romb->Checked)
                        Generate_Cutout (       cutout_Y_value,
                                                cutout_X_value,
                                                0, 45, 90,
                                                current__X,
                                                current__Y, -1) ;
                        current__X += cutout_X2_value;
                        }
                else if (Form1->Stagger->State==cbGrayed)
                        current__X += (cutout_X2_value/2);
                else    current__X += cutout_X2_value;
                }
        cnty++;
        current__Y += cutout_Y2_value;
        current__X = min_X;
        if (Form1->Stagger->State==cbChecked)
                if (cnty%2)
                        current__X += cutout_X2_value/2;
        }
}
