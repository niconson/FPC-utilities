//---------------------------------------------------------------------------


#pragma hdrstop

#include "CanvasThrmlP.h"
#include "Debug_Areas.h"
#include "ProcessMessages.h"
#include "math.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)




void CanvasThrmlP (AnsiString NET_AREA, int LayerArea)
{
Form3->Label1->Caption = "Canvas pads...";
Application->ProcessMessages();
int NET_AREA_LEN = NET_AREA.Length();
double Z;
for (int p=0; p<Dtpads; p++)
        {
        //if (DataPads[p].isHole)
        //        continue;
        if (Form1->cl_sm->Checked == 0 && DataPads[p].isMask >= 0)
                continue;
        if (Form1->cl_sm->Checked && DataPads[p].isMask == 0)
                continue;
        if (Form1->cl_holes->Checked == 0 && DataPads[p].isHole)
                continue;
        if ((DataPads[p].posX + MAX(DataPads[p].sizeX,DataPads[p].sizeY) + ThermalClearance) < AreaRect.Left)  continue;
        if ((DataPads[p].posX - MAX(DataPads[p].sizeX,DataPads[p].sizeY) - ThermalClearance) > AreaRect.Right) continue;
        if ((DataPads[p].posY + MAX(DataPads[p].sizeX,DataPads[p].sizeY) + ThermalClearance) < AreaRect.Bottom)continue;
        if ((DataPads[p].posY - MAX(DataPads[p].sizeX,DataPads[p].sizeY) - ThermalClearance) > AreaRect.Top)   continue;
        if (Form1->AutoSelect->Checked &&
                NET_AREA.SubString(1,NET_AREA_LEN) != DataPads[p].Net.SubString(1,DataPads[p].Net.Length()))
                        continue;
        if (DataPads[p].ThermalType == TT_NC || DataPads[p].ThermalType == TT_NT)
                continue;
        if (!Form1->cl_thrmlp->Checked &&
                DataPads[p].ThermalType == TT_DEF &&
                        DataPads[p].isVia == 0)
                        continue;
        //
        Z = ThermalClearance + MAX(DataPads[p].sizeX,DataPads[p].sizeY)/2;
        if ((AreaRect.Left - DataPads[p].posX) <   Z )
        if ((AreaRect.Bottom - DataPads[p].posY) < Z )
        if ((DataPads[p].posX - AreaRect.Right) <  Z )
        if ((DataPads[p].posY - AreaRect.Top) <    Z )
                {
                if( DataPads[p].sizeX < BY_ZERO || DataPads[p].sizeY < BY_ZERO )
                        continue;
                short int LR = DataPads[p].Layer;
                float CLEARENCE = ThermalClearance;
                if (DataPads[p].ThermalType == TT_NC)
                        {
                        CLEARENCE = GerberClearance;
                        if (DataPads[p].isHole || DataPads[p].isVia)
                                CLEARENCE = HoleClearance;
                        }
                float CW = DataPads[p].sizeX + 2.0*CLEARENCE;
                float CH = DataPads[p].sizeY + 2.0*CLEARENCE;
                if (DataPads[p].isVia )
                        {
                        if( DataPads[p].isHole == 0 )
                                continue;
                        if( Form1->cl_th_vias->Checked == 0 )
                                continue;
                        CW += annular_ring_for_vias;
                        CH += annular_ring_for_vias;
                        }
                else if( DataPads[p].isHole )
                        {
                        CW += annular_ring_for_pins;
                        CH += annular_ring_for_pins;
                        }
                float TX_shift = (CW-ThermalLineWidth)/4.0;
                float TY_shift = (CH-ThermalLineWidth)/4.0;
                float min = MIN(DataPads[p].sizeX, DataPads[p].sizeY);
                float CR;
                float CanvasAng = -DataPads[p].Tilt;
                float CIncAn = DataPads[p].IncAngle;
                if ( Form1->Low->Checked || CIncAn>30.0 )
                        CR = DataPads[p].radius*(1.0 + 2.0*CLEARENCE/min);
                else
                        CR = DataPads[p].radius + CLEARENCE;
                int NUM_STEPS = 1;
                BOOL EN_T = DataPads[p].ThermalType == TT_T ||
                        ( Form1->cl_thrmlp->Checked && DataPads[p].ThermalType == TT_DEF ) ||
                        ( Form1->cl_th_vias->Checked && DataPads[p].isVia);
                if ( EN_T )
                        {
                        NUM_STEPS = 4;
                        CW = TX_shift*2.0;
                        CH = TY_shift*2.0;
                        }
                //
                int R_type = 4;
                for( int nSTEP=0; nSTEP<NUM_STEPS; nSTEP++ )
                        {
                        double CX = DataPads[p].posX;
                        double CY = DataPads[p].posY;
                        if ( EN_T )
                                {
                                R_type = nSTEP - 1;
                                if( R_type < 0 )
                                        R_type = NUM_STEPS - 1;
                                if( nSTEP == 0 )
                                        {
                                        CX = (TY_shift+ThermalLineWidth/2);
                                        CY = (TX_shift+ThermalLineWidth/2);
                                        }
                                else if( nSTEP == 1 )
                                        {
                                        CX = -(TY_shift+ThermalLineWidth/2);
                                        CY = +(TX_shift+ThermalLineWidth/2);
                                        }
                                else if( nSTEP == 2 )
                                        {
                                        CX = -(TY_shift+ThermalLineWidth/2);
                                        CY = -(TX_shift+ThermalLineWidth/2);
                                        }
                                else if( nSTEP == 3 )
                                        {
                                        CX = +(TY_shift+ThermalLineWidth/2);
                                        CY = -(TX_shift+ThermalLineWidth/2);
                                        }
                                Rotate_Vertex(&CX,&CY,CanvasAng);
                                CX += DataPads[p].posX;
                                CY += DataPads[p].posY;
                                }
                        //
                        int cLay = MIN( LayerArea-LR_TOP, INNER_LAYER );
                        ////CR = MAX(ThermalClearance/2,CR);
                        if (Form1->AutoSelect->Checked)
                                {
                                if (cLay == LR || LR == ALL_LAYERS)
                                        Generate_Cutout(CW, CH, CR, CanvasAng, CIncAn, CX, CY, -1, R_type);
                                }
                        else    {
                                int ind = Form1->Iof(Form1->NetsBox, DataPads[p].Net, 0, Form1->NetsBox->Count);
                                if (ind >= 0)
                                        {
                                        if (Form1->NetsBox->Selected[ind])
                                                {
                                                if (Form1->through->Checked || cLay == LR || LR == ALL_LAYERS)
                                                        if (DataPads[p].isVia == 0 && DataPads[p].isHole == 0)
                                                                Generate_Cutout(CW, CH, CR, CanvasAng, CIncAn, CX, CY, -1, R_type);
                                                }
                                        }
                                }
                        }
                }
        }
Application->ProcessMessages();
}
