//---------------------------------------------------------------------------


#pragma hdrstop

#include "CanvasHoles.h"
#include "Debug_Areas.h"
#include "ProcessMessages.h"
#include "fstream.h"
#include "math.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)




//======================================================================
//Вырезы  Holes..========================================================
//======================================================================
void CanvasHoles (AnsiString NET_AREA, int LayerArea)
{
if (Form1->cl_holes->Checked == 0 )
        return;
Form3->Label1->Caption = "Canvas holes...";
Application->ProcessMessages();
int NET_AREA_LEN = NET_AREA.Length();
double Z;
for (int p=0; p<Dtpads; p++)
        {
        if (DataPads[p].isHole == 0)
                continue;
        if ((DataPads[p].posX + MAX(DataPads[p].sizeX,DataPads[p].sizeY) + HoleClearance) < AreaRect.Left)  continue;
        if ((DataPads[p].posX - MAX(DataPads[p].sizeX,DataPads[p].sizeY) - HoleClearance) > AreaRect.Right) continue;
        if ((DataPads[p].posY + MAX(DataPads[p].sizeX,DataPads[p].sizeY) + HoleClearance) < AreaRect.Bottom)continue;
        if ((DataPads[p].posY - MAX(DataPads[p].sizeX,DataPads[p].sizeY) - HoleClearance) > AreaRect.Top)   continue;
        if (DataPads[p].ThermalType != TT_NC)
                {
                if (Form1->AutoSelect->Checked &&
                        NET_AREA.SubString(1,NET_AREA_LEN) == DataPads[p].Net.SubString(1,DataPads[p].Net.Length()))
                        continue;
                }
        //
        Z = GerberClearance + MAX(DataPads[p].sizeX,DataPads[p].sizeY)/2;
        if ((AreaRect.Left - DataPads[p].posX) <   Z )
        if ((AreaRect.Bottom - DataPads[p].posY) < Z )
        if ((DataPads[p].posX - AreaRect.Right) <  Z )
        if ((DataPads[p].posY - AreaRect.Top) <    Z )
                {
                short int LR = DataPads[p].Layer;
                float CW = DataPads[p].sizeX + 2.0*HoleClearance;
                float CH = DataPads[p].sizeY + 2.0*HoleClearance;
                /*CW = CW*CORR_CL;
                CH = CH*CORR_CL;
                float min = MIN(DataPads[p].sizeX, DataPads[p].sizeY);  */
                float CR;
                float CanvasAng = -DataPads[p].Tilt;
                float CIncAn = DataPads[p].IncAngle;
                if ( Form1->Low->Checked || CIncAn>30.0 ) CR = DataPads[p].radius + 2*HoleClearance*0.2928932;
                else
                        CR = DataPads[p].radius + HoleClearance;
                float CX = DataPads[p].posX;
                float CY = DataPads[p].posY;
                //
                int cLay = MIN( LayerArea-LR_TOP, INNER_LAYER );
                //
                if (Form1->AutoSelect->Checked)
                        {
                        if (cLay == LR || LR == ALL_LAYERS)
                                Generate_Cutout(CW, CH, CR, CanvasAng, CIncAn, CX, CY, -1);
                        }
                else    {
                        int ind = Form1->Iof(Form1->NetsBox, DataPads[p].Net, 0, Form1->NetsBox->Count);
                        if (ind >= 0)
                                {
                                if (Form1->NetsBox->Selected[ind])
                                        {
                                        if (Form1->through->Checked || cLay == LR || LR == ALL_LAYERS)
                                                Generate_Cutout(CW, CH, CR, CanvasAng, CIncAn, CX, CY, -1);
                                        }
                                }
                        }
                }
        }
Application->ProcessMessages();
}
