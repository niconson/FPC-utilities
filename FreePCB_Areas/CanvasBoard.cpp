//---------------------------------------------------------------------------


#pragma hdrstop

#include "CanvasBoard.h"
#include "Debug_Areas.h"
#include "ProcessMessages.h"
#include "fstream.h"
#include "math.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)


void CanvasBoard (void)
{
Form3->Label1->Caption = "Canvas board clearence...";
Application->ProcessMessages();
for (int p=0; p<Dtlines; p++)
        {
        if (DataLines[p].Board >= 0)
                {
                float CLEARENCE = DRCBoardToCopper;
                float CW = 2*CLEARENCE;
                float CH = Length_Line(DataLines[p].X,DataLines[p].Y,DataLines[p].XNext,DataLines[p].YNext) + CW;
                float CR = CW/2;
                float CanvasAng = DataLines[p].angle();
                float CIncAn = 22.5;
                float CX = DataLines[p].posX();
                float CY = DataLines[p].posY();
                Generate_Cutout(CW, CH, CR, CanvasAng, CIncAn, CX, CY, DataLines[p].Board );
                }
        }
}
