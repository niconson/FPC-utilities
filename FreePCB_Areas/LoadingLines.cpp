//---------------------------------------------------------------------------


#pragma hdrstop

#include "LoadingLines.h"
#include "Debug_Areas.h"
#include "ProcessMessages.h"
#include "fstream.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)


//===================================================================






//===================================================================
void mirror_angle (float Part_angle, bool Part_layer, double *X, double *Y)
{
if(Part_layer) (*X) = -(*X);
Rotate_Vertex (X, Y, (-Part_angle));
}
// ==================================================================







//===================================================================
int CountShapes (AnsiString Shape)
        {
        int CNT = 0;
        AnsiString A;
        for   (int cnt=JUMP.Parts; cnt<JUMP.Nets; cnt++)
                {
                A = Form1->File->Items->operator [](cnt);
                if (A.SubString(1,5) == "shape")
                        {
                        short int i = 6;
                        AnsiString Sh = ex_str (A, &i );
                        if (Shape.SubString(1,Shape.Length()) == Sh.SubString(1,Sh.Length())) CNT++;
                        }
                }
        return CNT;
        }



//===================================================================
// ==================================================================
//===================================================================
bool ExPad ( AnsiString S, bool MM)
{
#define DEF 0
#define NC  1
#define T   2
#define NT  3
short int i =   prob (S, 1 );
short int Type =ex_float_NM (S, &i ,-1);              // òèï
float W =       ex_float_NM (S, &i, MM );             // W
float L =       ex_float_NM (S, &i, MM );             // L
L =             ex_float_NM (S, &i, MM);              // L
L = L*2;
if (L < BY_ZERO || Type == 1 || Type == 2 || Type == 6) L = W;
float R = ex_float_NM (S, &i, MM );                   // Rad
DataPads[Dtpads].clear();
DataPads[Dtpads].ThermalType = ex_float_NM (S, &i, -1 ); // Thrml
if (Type == 0)
        {
        //none
        return false;
        }
else if (Type == 1)
        {
        if (Form1->Low->Checked) DataPads[Dtpads].radius   = W*0.2928932;
        else    {
                W = W*CORR_CL;
                L = L*CORR_CL;
                DataPads[Dtpads].radius   = W*0.5;
                }
        }
else if (Type == 2 || Type == 3)
        {
        DataPads[Dtpads].radius = 0;
        }
else if (Type == 4)
        {
        if (Form1->Low->Checked) DataPads[Dtpads].radius   = R/1.7;
        else                     DataPads[Dtpads].radius   = R*0.94;
        }
else if (Type == 5)
        {
        if (Form1->Low->Checked) DataPads[Dtpads].radius   = MIN(W,L)*0.2928932;
        else    {
                W = W*CORR_CL;
                L = L*CORR_CL;
                DataPads[Dtpads].radius   = MIN(W,L)*0.5;
                }
        }
else if (Type == 6)
        {
        DataPads[Dtpads].radius   = W/3.48;
        }
DataPads[Dtpads].sizeX    = W;
DataPads[Dtpads].sizeY    = L;
if (Form1->Low->Checked || Type == 6)   DataPads[Dtpads].IncAngle = 90;
else                                    DataPads[Dtpads].IncAngle = 22.5;
return true;
}




//===========================================================================
//×òåíèå FOOTPRINTS..========================================================
//===========================================================================
void ReadFoot ( AnsiString Ref,
                int PointerToShape,
                float X_pos,
                float Y_pos,
                float A_Prt,
                bool side)
{
AnsiString S;
AnsiString CurNet;
double pX;
double pY;
double Hole=0;
int iH = 0;
int iTm=-1;
int iBm=-1;
int APin;
short int Units_MM = 0;
short int i;
int index = PointersToShape[PointerToShape];
if ( index == 0 )
        {
        ShowMessage("    Fatal error - footprint not found!" );
        exit(0);
        }
while   (index < JUMP.Board)
        {
        index++;
        S = Form1->File->Items->operator [](index);
        if (S.SubString(1,4) == "name" )
                break;
        if (S.SubString(1,7) == "outline")
                {

                }
        else if (S.SubString(1,4) == "next")
                {

                }
        else if (S.SubString(1,5) == "close")
                {

                }
        else if (S.SubString(1,4) == "text")
                {

                }
        else if (S.SubString(1,3) == "pin")
                {
                iTm = -1;
                iBm = -1;
                iH = -1;
                i = prob (S, 1 );
                AnsiString Num_pin =    ex_str (S, &i );
                Hole =                  ex_float_NM (S, &i, Units_MM );         //Hole
                pX =                    ex_float_NM (S, &i, Units_MM );         //Õ
                pY =                    ex_float_NM (S, &i, Units_MM );         //Ó
                APin =                  ex_float_NM (S, &i, -1 );               //ÓÃÎË
                mirror_angle(A_Prt, side, &pX, &pY);
                if(side)
                        APin = - APin + A_Prt;
                else    APin = + APin + A_Prt;
                pX += X_pos;
                pY += Y_pos;
                //Îïðåäåëåíèå NET PIN
                AnsiString F_pin = Ref + "." + Num_pin;
                //
                i = Form1->Iof(Form1->PinNets, F_pin, 0, Form1->PinNets->Count);
                if (i >= 0)     CurNet = Form1->PinNets->Items->operator [](i+1);
                else            CurNet = "Unconnected";
                if (Hole > BY_ZERO)
                        {
                        iH = Dtpads;
                        DataPads[Dtpads].clear();
                        if (Form1->High->Checked)   Hole = Hole*CORR_CL*CORR_CL;
                        DataPads[Dtpads].Net      = CurNet;
                        DataPads[Dtpads].Layer = ALL_LAYERS;
                        DataPads[Dtpads].isHole   = true;
                        DataPads[Dtpads].sizeX    = Hole;
                        DataPads[Dtpads].sizeY    = Hole;
                        DataPads[Dtpads].Tilt     = 0;
                        if (Form1->Low->Checked)    DataPads[Dtpads].radius   = Hole*0.2928932;
                        else                        DataPads[Dtpads].radius   = Hole*0.5;
                        DataPads[Dtpads].posX     = pX;
                        DataPads[Dtpads].posY     = pY;
                        if (Form1->Low->Checked)    DataPads[Dtpads].IncAngle = 90;
                        else                        DataPads[Dtpads].IncAngle = 22.5;
                        Dtpads++;
                        }
                }
        else if (S.SubString(1,6) == "units:")
                {
                i = prob (S, 1 );
                if (S.UpperCase().SubString(i,3) == "MIL")      Units_MM = 0;
                else if (S.UpperCase().SubString(i,2) == "NM")  Units_MM = 1;
                else                                            Units_MM = 2;
                }
        else if (S.SubString(1,4) == "top_")
                {
                bool ex = ExPad (S, Units_MM);
                if (iH >= 0)
                        {
                        if (side) DataPads[iH].BottomThermal = DataPads[Dtpads].ThermalType;
                        else      DataPads[iH].ThermalType =   DataPads[Dtpads].ThermalType;
                        }
                if (S.SubString(5,5) == "paste" )
                        {
                        // Empty
                        }
                else if (ex)
                        {
                        ////DataPads[Dtpads-1].ThermalType = DataPads[Dtpads].ThermalType;
                        DataPads[Dtpads].Net = CurNet;
                        if (side) DataPads[Dtpads].Layer = BOTTOM_LAYER;
                        else      DataPads[Dtpads].Layer = TOP_LAYER;
                        DataPads[Dtpads].posX = pX;
                        DataPads[Dtpads].posY = pY;
                        if ( APin%90 == 0 && APin%180 )
                                {
                                double buf = DataPads[Dtpads].sizeX;
                                DataPads[Dtpads].sizeX = DataPads[Dtpads].sizeY;
                                DataPads[Dtpads].sizeY = buf;
                                DataPads[Dtpads].Tilt = 0;
                                }
                        else    DataPads[Dtpads].Tilt = APin;
                        if (S.SubString(5,1) == "m")
                                {
                                if(iTm>=0)
                                        {
                                        DataPads[Dtpads].isMask = iTm;
                                        DataPads[iTm].Mask = Dtpads;
                                        DataPads[Dtpads].ThermalType = DataPads[iTm].ThermalType;
                                        }
                                else
                                        DataPads[Dtpads].isMask = 0;
                                }
                        else
                                iTm = Dtpads;
                        Dtpads++;
                        }
                }
        else if (S.SubString(1,7) == "bottom_" )
                {
                bool ex = ExPad (S, Units_MM);
                if (iH >= 0)
                        {
                        if (side) DataPads[iH].ThermalType =   DataPads[Dtpads].ThermalType;
                        else      DataPads[iH].BottomThermal = DataPads[Dtpads].ThermalType;
                        }
                if (S.SubString(8,5) == "paste" )
                        {
                        // Empty
                        }
                else if (ex)
                        {
                        DataPads[Dtpads].Net = CurNet;
                        if (side) DataPads[Dtpads].Layer = TOP_LAYER ;
                        else      DataPads[Dtpads].Layer = BOTTOM_LAYER;
                        DataPads[Dtpads].posX = pX;
                        DataPads[Dtpads].posY = pY;
                        if ( APin%90 == 0 && APin%180 )
                                {
                                double buf = DataPads[Dtpads].sizeX;
                                DataPads[Dtpads].sizeX = DataPads[Dtpads].sizeY;
                                DataPads[Dtpads].sizeY = buf;
                                DataPads[Dtpads].Tilt = 0;
                                }
                        else    DataPads[Dtpads].Tilt = APin;
                        if (S.SubString(8,1) == "m")
                                {
                                if(iBm>=0)
                                        {
                                        DataPads[Dtpads].isMask = iBm;
                                        DataPads[iBm].Mask = Dtpads;
                                        DataPads[Dtpads].ThermalType = DataPads[iTm].ThermalType;
                                        }
                                else
                                        DataPads[Dtpads].isMask = 0;
                                }
                        else
                                iBm = Dtpads;
                        Dtpads++;
                        }
                }
        else if (S.SubString(1,9) == "inner_pad")
                {
                bool ex = ExPad (S, Units_MM);
                if (iH >= 0)
                        {
                        DataPads[iH].InnerThermal = DataPads[Dtpads].ThermalType;
                        }
                if (ex) {
                        DataPads[Dtpads].Net = CurNet;
                        DataPads[Dtpads].Layer = INNER_LAYER;
                        DataPads[Dtpads].posX = pX;
                        DataPads[Dtpads].posY = pY;
                        if ( APin%90 == 0 && APin%180 )
                                {
                                double buf = DataPads[Dtpads].sizeX;
                                DataPads[Dtpads].sizeX = DataPads[Dtpads].sizeY;
                                DataPads[Dtpads].sizeY = buf;
                                DataPads[Dtpads].Tilt = 0;
                                }
                        else    DataPads[Dtpads].Tilt = APin;
                        Dtpads++;
                        }
                }
        }
}
//======================================================================









//======================================================================
//======================================================================
void LoadingLines (void)
{
Form3->Visible = true;
Form1->BitBtn1->Enabled = false;
Form3->Label1->Caption = "Loading Lines, pads and vias...";
Application->ProcessMessages();
AnsiString S;
short int i;
//
//ÏÎÄÑ×ÅÒ ÊÎË-ÂÀ ÄËß ÂÛÄÅËÅÍÈß ÏÀÌßÒÈ
//
AnsiString NAME = "";
int MEM_pads = 0;
int MEM_lines = 0;
int index = 0 ;
int current_c_shapes;
float project_via_pad;
float project_via_hole;
int MaxPercent = (JUMP.Sm_cutouts)/25+1;
Form3->ProgressBar1->Position = 0;
while   (index < JUMP.Sm_cutouts)
        {
        if (index%MaxPercent == 0)
                {
                Form3->ProgressBar1->Position++;
                Application->ProcessMessages();
                }
        S = Form1->File->Items->operator [](index);
        index++;
        if (S.SubString(1,4) == "name")
                {
                i = prob(S,1);
                NAME = ex_str(S,&i);
                current_c_shapes = CountShapes (NAME);
                }
        else if (S.SubString(1,3) == "pin")
                {
                i = prob(S,2);
                float h = ex_float_NM (S, &i, -1 );
                if (h > BY_ZERO)
                        MEM_pads += (current_c_shapes*3);
                }
        else if (  S.SubString(1,4) ==  "top_"
                || S.SubString(1,7) == "bottom_"
                || S.SubString(1,6) ==  "inner_" )
                {
                MEM_pads += current_c_shapes;
                }
        else if (S.SubString(1,6) == "corner")
                {
                i = prob(S,4);
                MEM_lines++;
                int arc = ex_float_NM (S, &i, -1 );
                if (arc)
                        MEM_lines += GEN_ARC_NUM_CORNERS;
                }
        else if (S.SubString(13,9) == "pad_width" )
                {
                i = prob(S,1);
                project_via_pad = ex_float_NM (S, &i, -1 );
                }
        else if (S.SubString(13,10) == "hole_width" )
                {
                i = prob(S,1);
                project_via_hole = ex_float_NM (S, &i, -1 );
                }
        }
index = JUMP.Nets ;
MaxPercent = (JUMP.Merges - index)/25+1;
Form3->ProgressBar1->Position = 25;
while   (index < JUMP.Merges)
        {
        if (index%MaxPercent == 0)
                {
                Form3->ProgressBar1->Position++;
                Application->ProcessMessages();
                }
        S = Form1->File->Items->operator [](index);
        index++;
        if (S.SubString(1,3) == "vtx")
                {
                int bi = prob(S,5);
                i = prob(S,6);
                if (S.SubString(i,1) != "0" || S.SubString(bi,1) != "0")
                        MEM_pads = MEM_pads + 2;
                }
        if ( S.SubString(1,3) == "cor")
                {
                i = prob(S,4);
                MEM_lines++;
                if ( i>0 )
                        if (S.SubString(i,1) != "0")
                                MEM_lines += GEN_ARC_NUM_CORNERS;
                }
        if (S.SubString(1,3) == "seg" || S.SubString(1,4) == "text")
                {
                MEM_lines++;
                }
        }
//
//ÂÛÄÅËÅÍÈÅ ÏÀÌßÒÈ
//
MEM_pads += 5;
MEM_lines += 5;
if (DataPads)  delete[] DataPads;
if (DataLines) delete[] DataLines;
try     {
        DataPads = new(std::nothrow) CanvasDataPads[MEM_pads];
        }
catch(std::bad_alloc)
        {
        ShowMessage("    Error of memory: CanvasDataPads[" + AnsiString(MEM_pads) + "]!" );
        }
try     {
        DataLines = new(std::nothrow) CanvasDataLines[MEM_lines];
        }
catch(std::bad_alloc)
        {
        ShowMessage("    Error of memory: CanvasDataLines[" + AnsiString(MEM_lines) + "]!" );
        }
DataPads[0].clear();
Dtpads = 1;
Dtlines = 0;
//
//LOADING PADS
//
int index_f = 0;
AnsiString Ref;
AnsiString Shape;
float X_pos;
float Y_pos;
float A_Prt;
float side;
index = JUMP.Parts ;
MaxPercent = (JUMP.Nets - index)/25+1;
Form3->ProgressBar1->Position = 50;
while   (index < JUMP.Nets)
        {
        if (index%MaxPercent == 0)
                {
                Form3->ProgressBar1->Position++;
                Application->ProcessMessages();
                }
        S = Form1->File->Items->operator [](index);
        if (S.SubString(1,4) == "part")
                {
                if (index_f) ReadFoot (Ref,index_f,X_pos,Y_pos,A_Prt,side);
                index_f = 0;
                Ref = "";
                Shape = "";
                i = prob(S,1);
                Ref = S.SubString(i,(S.Length()-i+1));
                }
        else if (S.SubString(1,5) == "shape")
                {
                i = prob(S,1);
                if (i)  {
                        Shape = ex_str(S,&i);
                        if (Shape.Length())
                                {
                                Shape = AnsiString("name: \"") + Shape + "\"";
                                index_f = index;
                                }
                        }
                }
        else if (S.SubString(1,3) == "pos")
                {
                i = prob (S, 1 );
                if (i)  {
                        X_pos = ex_float_NM (S, &i, -1 );              // Õ
                        Y_pos = ex_float_NM (S, &i, -1 );              // Ó
                        side =  ex_float_NM (S, &i, -1 );              // Ñòîðîíà
                        A_Prt = ex_float_NM (S, &i, -1 );              // Óãîë
                        }
                }
        index++;
        }
if (index_f)
        ReadFoot (Ref,index_f,X_pos,Y_pos,A_Prt,side);
//
//LOADING LINES
BoardRect.Left =        DEFAULT+1;
BoardRect.Bottom =      DEFAULT+1;
BoardRect.Right =      -DEFAULT-1;
BoardRect.Top =        -DEFAULT-1;
int index_outline = 0, numb_cutouts = 0;
nBO = 0;
index = JUMP.Board ;
while   (index < JUMP.Sm_cutouts)
        {
        S = Form1->File->Items->operator [](index);
        if (S.SubString(1,7) == "outline")
                {
                nBO++;
                i = prob(S,2);
                index_outline = ex_float_NM (S, &i, -1 );
                index_outline += numb_cutouts;
                }
        if (S.SubString(1,3) == "cor")
                {
                double Xc;
                double Yc;
                double Xcb = DEFAULT + 1;
                double Ycb = DEFAULT + 1;
                int style;
                int style_b;
                int end=0,end_b=0;
                int start_index = Dtlines;
                do      {
                        i = prob(S,2);
                        Xc = ex_float_NM (S, &i, -1 );
                        Yc = ex_float_NM (S, &i, -1 );
                        style = ex_float_NM (S, &i, -1 );
                        if(i>0)
                                end = ex_float_NM (S, &i, -1 );
                        if (end!=end_b)
                                {
                                float ARC[GEN_ARC_NUM_CORNERS*2];
                                int CLines = Generate_Line(Xcb,Ycb,DataLines[start_index].X,DataLines[start_index].Y,style_b,&ARC[0]);
                                for (int m=0; (m+3)<CLines; m=m+2)
                                        {
                                        DataLines[Dtlines].clear();
                                        DataLines[Dtlines].X = ARC[m];
                                        DataLines[Dtlines].Y = ARC[m+1];
                                        DataLines[Dtlines].XNext = ARC[m+2];
                                        DataLines[Dtlines].YNext = ARC[m+3];
                                        DataLines[Dtlines].Board = index_outline + end_b;
                                        Dtlines++;
                                        }
                                start_index = Dtlines;
                                Xcb = DEFAULT + 1;
                                Ycb = DEFAULT + 1;
                                }
                        if (BoardRect.Left > Xc)  BoardRect.Left = Xc;
                        if (BoardRect.Bottom > Yc)BoardRect.Bottom = Yc;
                        if (BoardRect.Right < Xc) BoardRect.Right = Xc;
                        if (BoardRect.Top < Yc)   BoardRect.Top = Yc;
                        if (Xcb < DEFAULT && Ycb < DEFAULT)
                                {
                                float ARC[GEN_ARC_NUM_CORNERS*2];
                                int CLines = Generate_Line(Xcb,Ycb,Xc,Yc,style_b,&ARC[0]);
                                for (int m=0; (m+3)<CLines; m=m+2)
                                        {
                                        DataLines[Dtlines].clear();
                                        DataLines[Dtlines].X = ARC[m];
                                        DataLines[Dtlines].Y = ARC[m+1];
                                        DataLines[Dtlines].XNext = ARC[m+2];
                                        DataLines[Dtlines].YNext = ARC[m+3];
                                        DataLines[Dtlines].Board = index_outline + end_b;
                                        Dtlines++;
                                        }
                                }
                        Xcb = Xc;
                        Ycb = Yc;
                        style_b = style;
                        index++;
                        end_b = end;
                        S = Form1->File->Items->operator [](index);
                        } while (S.SubString(1,3) == "cor");
                if (Dtlines > start_index)
                        {
                        float ARC[GEN_ARC_NUM_CORNERS*2];
                        int CLines = Generate_Line(Xcb,Ycb,DataLines[start_index].X,DataLines[start_index].Y,style_b,&ARC[0]);
                        for (int m=0; (m+3)<CLines; m=m+2)
                                {
                                DataLines[Dtlines].clear();
                                DataLines[Dtlines].X = ARC[m];
                                DataLines[Dtlines].Y = ARC[m+1];
                                DataLines[Dtlines].XNext = ARC[m+2];
                                DataLines[Dtlines].YNext = ARC[m+3];
                                DataLines[Dtlines].Board = index_outline + end_b;
                                Dtlines++;
                                }
                        numb_cutouts += end_b;
                        index--;
                        }
                }
        index++;
        }
if(nBO == 0)
        {
        Form1->cl_brd->Checked = 0;
        Form1->cl_brd->Enabled = 0;
        }
index = JUMP.Nets ;
MaxPercent = (JUMP.Merges - index)/25+1;
Form3->ProgressBar1->Position = 75;
float default_via_pad;
float default_via_hole;
AnsiString cur_n;
short int cur_lay;
short int ar_n;
short int txt_lay;
int txt_wid=0;
bool txt_negative=0;
long a_w;
short int eoc = 1;
while   (index < JUMP.Merges)
        {
        if (index%MaxPercent == 0)
                {
                Form3->ProgressBar1->Position++;
                Application->ProcessMessages();
                }
        S = Form1->File->Items->operator [](index);
        if (S.SubString(1,3) == "net")
                {
                i = prob(S,1);
                cur_n = ex_str(S,&i);
                i = prob(S,6);
                default_via_pad =  ex_float_NM (S, &i, -1 );
                default_via_hole = ex_float_NM (S, &i, -1 );
                if (default_via_pad < BY_ZERO)
                        {
                        default_via_pad =  project_via_pad;
                        default_via_hole = project_via_hole;
                        if (default_via_pad < BY_ZERO)
                                ShowMessage("    Message: default via pad of net \"" + cur_n + "\" is equal to zero.");
                        }
                }
        else if (S.SubString(1,4) == "area")
                {
                eoc = 0;
                i = prob(S,1);
                ar_n = ex_float_NM (S, &i, -1 );
                i = prob(S,3);
                cur_lay = ex_float_NM (S, &i, -1 );
                int htch = 0;
                i = prob(S,4);
                if (i)
                        htch = ex_float_NM (S, &i, -1 );
                a_w = 0;
                i = prob(S,5);
                if (i)
                        a_w = ex_float_NM (S, &i, -1 );
                if( !htch && !a_w )
                        eoc = 1;
                a_w = ABS(a_w);
                }
        else if (S.SubString(1,3) == "cor" && eoc == 0)
                {
                double Xc;
                double Yc;
                int style;
                int style_b;
                while (S.SubString(1,3) == "cor")
                        {
                        int start_index = Dtlines;
                        double Xcb = DEFAULT + 1;
                        double Ycb = DEFAULT + 1;
                        do      {
                                i = prob(S,2);
                                Xc =    ex_float_NM (S, &i, -1 );
                                Yc =    ex_float_NM (S, &i, -1 );
                                style = ex_float_NM (S, &i, -1 );
                                eoc =   ex_float_NM (S, &i, -1 );
                                if (Xcb < DEFAULT && Ycb < DEFAULT)
                                        {
                                        float ARC[GEN_ARC_NUM_CORNERS*2];
                                        int CLines = Generate_Line(Xcb,Ycb,Xc,Yc,style_b,&ARC[0]);
                                        for (int m=0; (m+3)<CLines; m=m+2)
                                                {
                                                DataLines[Dtlines].clear();
                                                DataLines[Dtlines].X = ARC[m];
                                                DataLines[Dtlines].Y = ARC[m+1];
                                                DataLines[Dtlines].XNext = ARC[m+2];
                                                DataLines[Dtlines].YNext = ARC[m+3];
                                                DataLines[Dtlines].Net = cur_n;
                                                DataLines[Dtlines].Layer = cur_lay;
                                                DataLines[Dtlines].Wid = a_w;
                                                DataLines[Dtlines].Area = ar_n;
                                                Dtlines++;
                                                }
                                        }
                                Xcb = Xc;
                                Ycb = Yc;
                                style_b = style;
                                index++;
                                S = Form1->File->Items->operator [](index);
                                } while (S.SubString(1,3) == "cor" && eoc == 0);
                        if (Dtlines > start_index)
                                {
                                float ARC[GEN_ARC_NUM_CORNERS*2];
                                int CLines = Generate_Line(Xc,Yc,DataLines[start_index].X,DataLines[start_index].Y,style_b,&ARC[0]);
                                for (int m=0; (m+3)<CLines; m=m+2)
                                        {
                                        DataLines[Dtlines].clear();
                                        DataLines[Dtlines].X = ARC[m];
                                        DataLines[Dtlines].Y = ARC[m+1];
                                        DataLines[Dtlines].XNext = ARC[m+2];
                                        DataLines[Dtlines].YNext = ARC[m+3];
                                        DataLines[Dtlines].Net = cur_n;
                                        DataLines[Dtlines].Layer = cur_lay;
                                        DataLines[Dtlines].Wid = a_w;
                                        DataLines[Dtlines].Area = ar_n;
                                        Dtlines++;
                                        }
                                }
                        }
                index--;
                }
        else if (S.SubString(1,5) == "text:")
                {
                i = prob(S,4);
                txt_lay =       ex_float_NM (S, &i, -1 );
                i = prob(S,8);
                txt_wid =       ex_float_NM (S, &i, -1 );
                i = prob(S,9);
                if(i>0)
                        txt_negative =  ex_float_NM (S, &i, -1 );
                }
        else if (S.SubString(1,9) == "text_line" && txt_wid)
                {
                DataLines[Dtlines].clear();
                DataLines[Dtlines].Layer = txt_lay;
                DataLines[Dtlines].Wid = txt_wid;
                DataLines[Dtlines].Txt = 1;
                if( txt_negative )
                        DataLines[Dtlines].Txt++;
                i = prob(S,1);
                DataLines[Dtlines].X = ex_float_NM (S, &i, -1 );
                DataLines[Dtlines].Y = ex_float_NM (S, &i, -1 );
                DataLines[Dtlines].XNext = ex_float_NM (S, &i, -1 );
                DataLines[Dtlines].YNext = ex_float_NM (S, &i, -1 );
                Dtlines++;
                }
        else if (S.SubString(1,9) == "selection")
                {
                txt_wid = 0;
                }
        else if (S.SubString(1,3) == "seg")
                {
                DataLines[Dtlines].clear();
                DataLines[Dtlines].Net = cur_n;
                AnsiString Sb = Form1->File->Items->operator [](index-1);
                AnsiString Sn = Form1->File->Items->operator [](index+1);
                i = prob(S,2);
                DataLines[Dtlines].Layer = ex_float_NM (S, &i, -1 );
                DataLines[Dtlines].Wid =   ex_float_NM (S, &i, -1 );
                i = prob(Sb,2);
                DataLines[Dtlines].X =     ex_float_NM (Sb, &i, -1 );
                DataLines[Dtlines].Y =     ex_float_NM (Sb, &i, -1 );
                i = prob(Sn,2);
                DataLines[Dtlines].XNext = ex_float_NM (Sn, &i, -1 );
                DataLines[Dtlines].YNext = ex_float_NM (Sn, &i, -1 );
                DataLines[Dtlines].Trace = true;
                i = prob(Sn,5);
                int flag_via =             ex_float_NM (Sn, &i, -1 );
                float via_pad =            ex_float_NM (Sn, &i, -1 );
                float via_hole =           ex_float_NM (Sn, &i, -1 );
                if (flag_via && via_pad < BY_ZERO )
                        {
                        via_pad = default_via_pad;
                        via_hole = default_via_hole;
                        }
                if (via_pad > BY_ZERO)
                        {
                        DataPads[Dtpads].clear();
                        if (Form1->High->Checked)   via_hole = via_hole*CORR_CL;
                        DataPads[Dtpads].Net      = cur_n;
                        DataPads[Dtpads].Layer    = ALL_LAYERS;
                        DataPads[Dtpads].isHole   = true;
                        DataPads[Dtpads].isVia    = true;
                        DataPads[Dtpads].sizeX    = via_hole;
                        DataPads[Dtpads].sizeY    = via_hole;
                        if (Form1->Low->Checked)    DataPads[Dtpads].radius   = via_hole*0.2928932;
                        else                        DataPads[Dtpads].radius   = via_hole*0.5;
                        DataPads[Dtpads].posX     = DataLines[Dtlines].XNext;
                        DataPads[Dtpads].posY     = DataLines[Dtlines].YNext;
                        if (Form1->Low->Checked)    DataPads[Dtpads].IncAngle = 90;
                        else                        DataPads[Dtpads].IncAngle = 22.5;
                        Dtpads++;
                        DataPads[Dtpads].clear();
                        if (Form1->High->Checked)   via_pad = via_pad*CORR_CL;
                        DataPads[Dtpads].Net      = cur_n;
                        DataPads[Dtpads].Layer    = ALL_LAYERS;
                        DataPads[Dtpads].isVia    = true;
                        DataPads[Dtpads].sizeX    = via_pad;
                        DataPads[Dtpads].sizeY    = via_pad;
                        if (Form1->Low->Checked)    DataPads[Dtpads].radius   = via_pad*0.2928932;
                        else                        DataPads[Dtpads].radius   = via_pad*0.5;
                        DataPads[Dtpads].posX     = DataLines[Dtlines].XNext;
                        DataPads[Dtpads].posY     = DataLines[Dtlines].YNext;
                        if (Form1->Low->Checked)    DataPads[Dtpads].IncAngle = 90;
                        else                        DataPads[Dtpads].IncAngle = 22.5;
                        Dtpads++;
                        }
                Dtlines++;
                }
        index++;
        }
DataLines[Dtlines].clear();
DataPads[Dtpads].clear();
//
Form3->ProgressBar1->Position = _102;
Memory_of_LinesCut = MEM_pads + MEM_lines;
Form3->Visible = false;
Form1->BitBtn1->Enabled = true;
}






