//---------------------------------------------------------------------------


#pragma hdrstop

#include "CanvasLines.h"
#include "Debug_Areas.h"
#include "ProcessMessages.h"
#include "math.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)







//---------------------------------------------------------------------------
void CanvasLines(AnsiString NET_AREA,int LayerArea,int AreaNum,int a_wid)
{
Form3->Label1->Caption = "Canvas lines...";
Application->ProcessMessages();
int NET_AREA_LEN = NET_AREA.Length();
double Z;
float max_clrnc = MAX(DRCCopperToCopper,GerberClearance);
for (int p=0; p<Dtlines; p++)
        {
        if ((DataLines[p].X + DataLines[p].Wid + max_clrnc) < AreaRect.Left && (DataLines[p].XNext + DataLines[p].Wid + max_clrnc) < AreaRect.Left)    continue;
        if ((DataLines[p].X - DataLines[p].Wid - max_clrnc) > AreaRect.Right && (DataLines[p].XNext - DataLines[p].Wid - max_clrnc) > AreaRect.Right)  continue;
        if ((DataLines[p].Y + DataLines[p].Wid + max_clrnc) < AreaRect.Bottom && (DataLines[p].YNext + DataLines[p].Wid + max_clrnc) < AreaRect.Bottom)continue;
        if ((DataLines[p].Y - DataLines[p].Wid - max_clrnc) > AreaRect.Top && (DataLines[p].YNext - DataLines[p].Wid - max_clrnc) > AreaRect.Top)      continue;
        if (    Form1->AutoSelect->Checked )
                {
                if( NET_AREA.SubString(1,NET_AREA_LEN) == DataLines[p].Net.SubString(1,DataLines[p].Net.Length())
                        && !DataLines[p].Area   )
                        continue;
                if ( LayerArea != DataLines[p].Layer )
                        continue;
                }
        Z = DataLines[p].Wid + max_clrnc;
        if      (
                ((AreaRect.Left - DataLines[p].X)  < Z
             && (AreaRect.Bottom - DataLines[p].Y) < Z
             && (DataLines[p].X - AreaRect.Right)  < Z
             && (DataLines[p].Y - AreaRect.Top)    < Z)
        ||
                ((AreaRect.Left - DataLines[p].XNext)  < Z
             && (AreaRect.Bottom - DataLines[p].YNext) < Z
             && (DataLines[p].XNext - AreaRect.Right)  < Z
             && (DataLines[p].YNext - AreaRect.Top)    < Z)
        ||
             LineAreaInside(    DataLines[p].X,
                                DataLines[p].Y,
                                DataLines[p].XNext,
                                DataLines[p].YNext) < (DataLines[p].Wid + max_clrnc)
                )
                {
                AnsiString N = DataLines[p].Net;
                short int LR = DataLines[p].Layer;
                float CLEARENCE = GerberClearance;
                if (DataLines[p].Area)
                        CLEARENCE = DRCCopperToCopper;
                if (DataLines[p].Board >= 0)
                        CLEARENCE = DRCBoardToCopper;
                float WID = DataLines[p].Wid;
                float CW = WID;
                if( DataLines[p].Txt <= 1 )
                        CW += 2*CLEARENCE;
                else    CW += a_wid;
                CW = CW*CORR_CL;
                if (CW < 0 )
                        CW = 0;
                float CH = Length_Line(DataLines[p].X,DataLines[p].Y,DataLines[p].XNext,DataLines[p].YNext) + CW;
                float CR = CW/2.0;
                float CanvasAng = DataLines[p].angle();
                float CIncAn = 22.5;
                float CX = DataLines[p].posX();
                float CY = DataLines[p].posY();
                if      ( DataLines[p].Txt > 0 && LayerArea == LR )
                        {
                        Generate_Cutout(CW, CH, CR, CanvasAng, CIncAn, CX, CY, -1);
                        }
                else if ( Form1->AutoSelect->Checked && LayerArea == LR )
                        {
                        if (Form1->cl_pins->Checked && DataLines[p].Trace > 0)
                                {
                                if (NET_AREA.SubString(1,NET_AREA.Length()) != N.SubString(1,N.Length()))
                                        {
                                        Generate_Cutout(CW, CH, CR, CanvasAng, CIncAn, CX, CY, -1);
                                        }
                                }
                        else if (Form1->cl_areas->Checked && DataLines[p].Area > 0)
                                {
                                if ( DataLines[p].Area == AreaNum && NET_AREA.SubString(1,NET_AREA.Length()) == N.SubString(1,N.Length()))
                                        {
                                        //isEmpty
                                        }
                                //else if ( Form1->repour->Checked == 0 && NET_AREA.SubString(1,NET_AREA.Length()) == N.SubString(1,N.Length()))
                                //        {
                                        //isEmpty
                                //        }
                                else    {
                                        int n_area = DataLines[p].Area;
                                        for (int back=(p-1); DataLines[back].Area == n_area; back--)
                                                {
                                                if ( DataLines[back].Net.SubString(1,DataLines[back].Net.Length()) != N.SubString(1,N.Length()))
                                                        break;
                                                LR = DataLines[back].Layer;
                                                WID = DataLines[back].Wid;
                                                CW = WID + 2*CLEARENCE;
                                                CW = CW*CORR_CL;
                                                CH = Length_Line(DataLines[back].X,DataLines[back].Y,DataLines[back].XNext,DataLines[back].YNext) + CW;
                                                CR = CW/2;
                                                CanvasAng = DataLines[back].angle();
                                                CIncAn = 22.5;
                                                CX = DataLines[back].posX();
                                                CY = DataLines[back].posY();
                                                Generate_Cutout(CW, CH, CR, CanvasAng, CIncAn, CX, CY, -1);
                                                }
                                        for (/*int next=p*/; DataLines[p].Area == n_area; p++)
                                                {
                                                if ( DataLines[p].Net.SubString(1,DataLines[p].Net.Length()) != N.SubString(1,N.Length()))
                                                        break;
                                                LR = DataLines[p].Layer;
                                                WID = DataLines[p].Wid;
                                                CW = WID + 2*CLEARENCE;
                                                CW = CW*CORR_CL;
                                                CH = Length_Line(DataLines[p].X,DataLines[p].Y,DataLines[p].XNext,DataLines[p].YNext) + CW;
                                                CR = CW/2;
                                                CanvasAng = DataLines[p].angle();
                                                CIncAn = 22.5;
                                                CX = DataLines[p].posX();
                                                CY = DataLines[p].posY();
                                                Generate_Cutout(CW, CH, CR, CanvasAng, CIncAn, CX, CY, -1);
                                                }
                                        p--;
                                        int First = CountLinesCut;
                                        float min = DEFAULT;
                                        float max = -DEFAULT;
                                        for (int a=p; DataLines[a].Area == n_area; a--)
                                                {
                                                if ( DataLines[a].Net.SubString(1,DataLines[a].Net.Length()) != N.SubString(1,N.Length()))
                                                        break;
                                                LinesCut[CountLinesCut].FlagDelete = 0;
                                                LinesCut[CountLinesCut].FlagWrite = 0;
                                                LinesCut[CountLinesCut].n_board = -1;
                                                LinesCut[CountLinesCut].First = First;
                                                LinesCut[CountLinesCut].X1 = DataLines[a].XNext;
                                                LinesCut[CountLinesCut].Y1 = DataLines[a].YNext;
                                                LinesCut[CountLinesCut].X2 = DataLines[a].X;
                                                LinesCut[CountLinesCut].Y2 = DataLines[a].Y;
                                                min = MIN(DataLines[a].X,min);
                                                max = MAX(DataLines[a].X,max);
                                                CountLinesCut++;
                                                }
                                        LinesCut[First].Bounds = min;
                                        LinesCut[First+1].Bounds = max;
                                        LinesCut[CountLinesCut].First = CountLinesCut;
                                        }
                                }
                        }
                else if ( Form1->Manual->Checked )
                        {
                        int ind = Form1->Iof(Form1->NetsBox, N, 0, Form1->NetsBox->Count);
                        if (ind >= 0)
                                {
                                if (Form1->NetsBox->Selected[ind])
                                        {
                                        if((Form1->through->Checked/*through all lay*/) ||
                                           (LayerArea == LR))
                                                {
                                                if (Form1->cl_pins->Checked && DataLines[p].Trace > 0)
                                                        Generate_Cutout(CW, CH, CR, CanvasAng, CIncAn, CX, CY, -1);
                                                else if (Form1->cl_areas->Checked && DataLines[p].Area > 0)
                                                        {
                                                        if ( DataLines[p].Area == AreaNum && NET_AREA.SubString(1,NET_AREA.Length()) == N.SubString(1,N.Length()))
                                                                {
                                                                //isEmpty
                                                                }
                                                        else    {
                                                                int n_area = DataLines[p].Area;
                                                                for (int back=(p-1); DataLines[back].Area == n_area; back--)
                                                                        {
                                                                        if ( DataLines[back].Net.SubString(1,DataLines[back].Net.Length()) != N.SubString(1,N.Length()))
                                                                                break;
                                                                        LR = DataLines[back].Layer;
                                                                        WID = DataLines[back].Wid;
                                                                        CW = WID + 2*CLEARENCE;
                                                                        CW = CW*CORR_CL;
                                                                        CH = Length_Line(DataLines[back].X,DataLines[back].Y,DataLines[back].XNext,DataLines[back].YNext) + CW;
                                                                        CR = CW/2;
                                                                        CanvasAng = DataLines[back].angle();
                                                                        CIncAn = 22.5;
                                                                        CX = DataLines[back].posX();
                                                                        CY = DataLines[back].posY();
                                                                        Generate_Cutout(CW, CH, CR, CanvasAng, CIncAn, CX, CY, -1);
                                                                        }
                                                                for (/*int next=p*/; DataLines[p].Area == n_area; p++)
                                                                        {
                                                                        if ( DataLines[p].Net.SubString(1,DataLines[p].Net.Length()) != N.SubString(1,N.Length()))
                                                                                break;
                                                                        LR = DataLines[p].Layer;
                                                                        WID = DataLines[p].Wid;
                                                                        CW = WID + 2*CLEARENCE;
                                                                        CW = CW*CORR_CL;
                                                                        CH = Length_Line(DataLines[p].X,DataLines[p].Y,DataLines[p].XNext,DataLines[p].YNext) + CW;
                                                                        CR = CW/2;
                                                                        CanvasAng = DataLines[p].angle();
                                                                        CIncAn = 22.5;
                                                                        CX = DataLines[p].posX();
                                                                        CY = DataLines[p].posY();
                                                                        Generate_Cutout(CW, CH, CR, CanvasAng, CIncAn, CX, CY, -1);
                                                                        }
                                                                p--;
                                                                int First = CountLinesCut;
                                                                float min = DEFAULT;
                                                                float max = -DEFAULT;
                                                                for (int a=p; DataLines[a].Area == n_area; a--)
                                                                        {
                                                                        if ( DataLines[a].Net.SubString(1,DataLines[a].Net.Length()) != N.SubString(1,N.Length()))
                                                                                break;
                                                                        LinesCut[CountLinesCut].FlagDelete = 0;
                                                                        LinesCut[CountLinesCut].FlagWrite = 0;
                                                                        LinesCut[CountLinesCut].n_board = -1;
                                                                        LinesCut[CountLinesCut].First = First;
                                                                        LinesCut[CountLinesCut].X1 = DataLines[a].XNext;
                                                                        LinesCut[CountLinesCut].Y1 = DataLines[a].YNext;
                                                                        LinesCut[CountLinesCut].X2 = DataLines[a].X;
                                                                        LinesCut[CountLinesCut].Y2 = DataLines[a].Y;
                                                                        min = MIN(DataLines[a].X,min);
                                                                        max = MAX(DataLines[a].X,max);
                                                                        CountLinesCut++;
                                                                        }
                                                                LinesCut[First].Bounds = min;
                                                                LinesCut[First+1].Bounds = max;
                                                                LinesCut[CountLinesCut].First = CountLinesCut;
                                                                }
                                                        }
                                                }
                                        else    {

                                                }
                                        }
                                }
                        }
                }
        }
Application->ProcessMessages();
}
//---------------------------------------------------------------------------
