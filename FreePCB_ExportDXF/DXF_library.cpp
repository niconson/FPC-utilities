//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DXF_library.h"
#include "To_DXF.h"
#include "Logo.h"
#include "Enter_Name.h"
#include "fstream.h"
#include "math.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
static AnsiString
        StringF,
        NmB,
        LibPath;
int     SwapRow = -1,
        SwapCol = -1;
int     SwellMem (void);
int bReplace_YZ_to_XY = 0;
int bReplace_XZ_to_XY = 0;
int bLibModified = 0;




void DownGridValues(int col)
        {
        bLibModified = true;
        int row = Form2->StringGrid1->Row;
        AnsiString nm, cnm;
        nm = Form2->StringGrid1->Cells[PACKAGES][row];
        cnm = nm;
        while (nm.SubString(1,nm.Length()) == cnm.SubString(1,cnm.Length()) )
                {
                AnsiString A = Form2->StringGrid1->Cells[col][row];
                float Q = StrToFloat(Str_Float_Format(A));
                if (col == ANGLE_XY || col == ANGLE_XZ || col == ANGLE_YZ) Q = Q - 5;
                else if (SHIFT) Q = Q - 0.5;
                else Q = Q - 0.05;
                Form2->StringGrid1->Cells[col][row] = FormatFloat("0.00",Q);
                if (Form2->Complex1->Checked == 0)
                        break;
                row++;
                cnm = Form2->StringGrid1->Cells[PACKAGES][row];
                }
        if (Form2->Complex1->Checked)
                {
                row = Form2->StringGrid1->Row-1;
                cnm = Form2->StringGrid1->Cells[PACKAGES][row];
                while (nm.SubString(1,nm.Length()) == cnm.SubString(1,cnm.Length()) )
                        {
                        AnsiString A = Form2->StringGrid1->Cells[col][row];
                        float Q = StrToFloat(Str_Float_Format(A));
                        if (col == ANGLE_XY || col == ANGLE_XZ || col == ANGLE_YZ) Q = Q - 5;
                        else if (SHIFT) Q = Q - 0.5;
                        else Q = Q - 0.05;
                        Form2->StringGrid1->Cells[col][row] = FormatFloat("0.00",Q);
                        row--;
                        cnm = Form2->StringGrid1->Cells[PACKAGES][row];
                        }
                }
        }


//
void UpGridValues(int col)
        {
        bLibModified = true;
        int row = Form2->StringGrid1->Row;
        AnsiString nm, cnm;
        nm = Form2->StringGrid1->Cells[PACKAGES][row];
        cnm = nm;
        while (nm.SubString(1,nm.Length()) == cnm.SubString(1,cnm.Length()) )
                {
                AnsiString A = Form2->StringGrid1->Cells[col][row];
                float Q = StrToFloat(Str_Float_Format(A));
                if (col == ANGLE_XY || col == ANGLE_XZ || col == ANGLE_YZ) Q = Q + 5;
                else if (SHIFT) Q = Q + 0.5;
                else Q = Q + 0.05;
                Form2->StringGrid1->Cells[col][row] = FormatFloat("0.00",Q);
                if (Form2->Complex1->Checked == 0)
                        break;
                row++;
                cnm = Form2->StringGrid1->Cells[PACKAGES][row];
                }
        if (Form2->Complex1->Checked)
                {
                row = Form2->StringGrid1->Row-1;
                cnm = Form2->StringGrid1->Cells[PACKAGES][row];
                while (nm.SubString(1,nm.Length()) == cnm.SubString(1,cnm.Length()) )
                        {
                        AnsiString A = Form2->StringGrid1->Cells[col][row];
                        float Q = StrToFloat(Str_Float_Format(A));
                        if (col == ANGLE_XY || col == ANGLE_XZ || col == ANGLE_YZ) Q = Q + 5;
                        else if (SHIFT) Q = Q + 0.5;
                        else Q = Q + 0.05;
                        Form2->StringGrid1->Cells[col][row] = FormatFloat("0.00",Q);
                        row--;
                        cnm = Form2->StringGrid1->Cells[PACKAGES][row];
                        }
                }
        }


int TForm2::GetFootBeg(AnsiString str, int * END)
{
long i;
AnsiString Shape,S;
int lbls = 0, LBLS = 0;
int Footprint_beg = -1;
int Footprint_end = -1;
while (LABELS[lbls] > 0)
        {
        S = Form1->File->Items->operator [](LABELS[lbls]);
        if (S.SubString(1,4) == "name" || S.SubString(1,7) == "package")
                {
                if( S.SubString(1,4) == "name" )
                        {
                        LBLS = lbls;
                        }
                i = prob(S,1);
                AnsiString ex = ex_str(S,&i);
                MOD(&ex);
                if (str.SubString(1,str.Length()) == ex.SubString(1,ex.Length()))
                        {
                        if( S.SubString(1,7) == "package" )
                                Footprint_beg = LABELS[LBLS];
                        }
                else    {
                        if( S.SubString(1,4) == "name" && Footprint_beg >= 0 )
                                Footprint_end = LABELS[lbls];
                        else if( ex.Length() )
                                {
                                Footprint_beg = -1;
                                Footprint_end = -1;
                                }
                        if( Footprint_beg > 0 )
                                break;
                        }
                }
        else if (S.SubString(1,7) == "[board]")
                {
                if( Footprint_beg > 0 )
                        {
                        Footprint_end = LABELS[lbls];
                        break;
                        }
                else    {
                        Footprint_beg = -1;
                        Footprint_end = -1;
                        break;
                        }
                }
        lbls++;
        }
if( END )
        *END = Footprint_end;
return Footprint_beg;
}







//---------------------------------------------------------------------------
bool Canva (int Mode)
{
if (!FACES || !LINES)
        return false;
AnsiString Nm = Form2->StringGrid1->Cells[PACKAGES][StringGridIndexRow];
if (    !Nm.Length())
        return false;
if ( Nm.SubString(1,Nm.Length()) == NmB.SubString(1,NmB.Length()) && Form2->StringGrid1->Col == 0 )
        {
        NmB = Nm;
        return false;
        }

//
int Footprint_begin = -1;
int Footprint_end   = -1;
Footprint_begin = Form2->GetFootBeg( Nm, &Footprint_end );
if (Mode == GET_DATA)
        {
        Nm = Form2->StringGrid1->Cells[PACKAGES][StringGridIndexRow];
        NmB = Nm;
        if (Footprint_begin >= 0)
                return true;
        else
                return false;
        }

// Black Rect
Form2->pDC->Canvas->Pen->Width = 1;
Form2->pDC->Canvas->Pen->Color = clBlack;
Form2->pDC->Canvas->Brush->Color = clBlack;//clBtnFace;
Form2->pDC->Canvas->Rectangle(Fill_Rect);
//
static myRect SelRect;
static int i_head;
static int MIN_GRID_INDEX;
static int MAX_GRID_INDEX;
static int JumpsIndexInfo;

SelRect.Left =   DEFAULT;
SelRect.Bottom = DEFAULT;
SelRect._Low =   DEFAULT;
SelRect.Right = -DEFAULT;
SelRect.Top =   -DEFAULT;
SelRect._High = -DEFAULT;
if (Footprint_begin > 0)
        {
        SelRect.Left =   canvas_data[Footprint_begin].x ;
        SelRect.Bottom = canvas_data[Footprint_begin].y ;
        SelRect.Right =  canvas_data[Footprint_begin].xn;
        SelRect.Top =    canvas_data[Footprint_begin].yn;
        }
float Rotate = 0;
int Ptr;
JumpData_struct JumpData[NUMBER_OF_TJumps];
for (int q=0; q<NUMBER_OF_TJumps; q++)
        {
        JumpData[q].J =   JUMP_NOT_FOUND;
        JumpData[q].min = JUMP_NOT_FOUND;
        JumpData[q].max = JUMP_NOT_FOUND;
        }
Nm = Form2->StringGrid1->Cells[PACKAGES][StringGridIndexRow];
int i_branch =  Form2->StringGrid1->Cols[PACKAGES]->IndexOf(Nm);
if (i_branch == -1)
        return false;
i_head = i_branch;
MIN_GRID_INDEX = i_branch;
MAX_GRID_INDEX = i_branch;
JumpsIndexInfo = i_branch;
//
AnsiString S =  Form2->StringGrid1->Cells[PACKAGES][i_branch];
while (S.LowerCase().SubString(1,S.Length()) == Nm.LowerCase().SubString(1,Nm.Length()))
        {
        MAX_GRID_INDEX++;
        S = Form2->StringGrid1->Cells[PACKAGES][MAX_GRID_INDEX];
        }
MAX_GRID_INDEX--;
InsertBlock (0, 0, 0, &SelRect, RESET, 0, 0, 0);
int fB = Footprint_begin;
do      {
        while ((Ptr = InsertBlock (fB, TOP, Rotate, &SelRect, i_head, i_branch, MIN_GRID_INDEX, MAX_GRID_INDEX, 1)) == WARNING_OF_MEMORY)
                {
                MAX_FACES_AND_LINES = SwellMem()-99;
                SelRect.Left         *=_106;
                SelRect.Right        *=_106;
                SelRect.Top          *=_106;
                SelRect.Bottom       *=_106;
                SelRect._Low         *=_106;
                SelRect._High        *=_106;
                }
        if (Ptr == JUMP_NOT_FOUND)
                {
                i_branch = JumpData[0].J+1;
                i_head =   JumpData[0].J;
                for (int t=1; JumpData[t].J>0; t++)
                        i_head = JumpData[t].J;
                MIN_GRID_INDEX = JumpData[0].min;
                MAX_GRID_INDEX = JumpData[0].max;
                for (int d=0; d<(NUMBER_OF_TJumps-1); d++)
                        {    //removing
                        JumpData[d].J = JumpData[d+1].J;
                        JumpData[d].min = JumpData[d+1].min;
                        JumpData[d].max = JumpData[d+1].max;
                        }
                JumpData[NUMBER_OF_TJumps-1].J = JUMP_NOT_FOUND;
                }
        else    {
                for (int d=(NUMBER_OF_TJumps-1); d>0; d--)
                        {    //writing
                        JumpData[d].J = JumpData[d-1].J;
                        JumpData[d].min = JumpData[d-1].min;
                        JumpData[d].max = JumpData[d-1].max;
                        }
                JumpData[0].J = Ptr;
                JumpData[0].min = MIN_GRID_INDEX;
                JumpData[0].max = MAX_GRID_INDEX;
                S = Form2->StringGrid1->Cells[SHAPE][JumpData[0].J];
                Nm = S;
                i_branch = Form2->StringGrid1->Cols[PACKAGES]->IndexOf(S);
                MIN_GRID_INDEX = i_branch;
                MAX_GRID_INDEX = i_branch;
                while (S.LowerCase().SubString(1,S.Length()) == Nm.LowerCase().SubString(1,Nm.Length()))
                        {
                        MAX_GRID_INDEX++;
                        S = Form2->StringGrid1->Cells[PACKAGES][MAX_GRID_INDEX];
                        }
                MAX_GRID_INDEX--;
                i_head =   JumpData[0].J;
                for (int t=1; JumpData[t].J>0; t++)
                        i_head = JumpData[t].J;
                fB = Form2->GetFootBeg( Nm );
                if( fB == -1 )
                        fB = Footprint_begin;
                }
        }while (i_branch > 0 && Nm.Length());
Nm = Form2->StringGrid1->Cells[PACKAGES][StringGridIndexRow];
if (SelRect.Left >= SelRect.Right)
        {
        SelRect.Left  =         0;
        SelRect.Right  =        0;
        }
if (SelRect.Bottom >= SelRect.Top)
        {
        SelRect.Bottom  =       0;
        SelRect.Top  =          0;
        }
if (SelRect._Low >= SelRect._High)
        {
        SelRect._Low =          0;
        SelRect._High =         0;
        }
SelRect.Left -=         _106;
SelRect.Bottom -=       _106;
SelRect._Low -=         _106;
SelRect.Right +=        _106;
SelRect.Top +=          _106;
SelRect._High +=        _106;
long DX;
DX = SelRect.Right - SelRect.Left;
long DY;
DY = SelRect.Top - SelRect.Bottom;
long DX_fillRect = Fill_Rect.Right - Fill_Rect.Left;
long DY_fillRect = Fill_Rect.Bottom - Fill_Rect.Top;
float K1 = (float)DX_fillRect/(float)DX;
float K2 = (float)DY_fillRect/(float)DY;
float K_selrect = MIN(K1,K2);
K_selrect = K_selrect*GlobalScaleFactor;
float shifty = (DY_fillRect - DY * K_selrect)/2;
float shiftx = (DX_fillRect - DX * K_selrect)/2;
int ShiftX = -GlobalShiftX*GlobalScaleFactor/2;
int ShiftY = -GlobalShiftY*GlobalScaleFactor/2;
//GRID
float Gvalue = 0;
AnsiString AGrid = Form2->GridValues->Text;
if (AGrid.Length() > 2)
        {
        if (AGrid.UpperCase().SubString((AGrid.Length()-1),2) == "MM" )
                {
                AGrid = AGrid.SubString(1,(AGrid.Length()-2));
                AGrid = Str_Float_Format(AGrid);
                Gvalue = StrToFloat(AGrid);
                }
        }
if (AGrid.Length() > 3)
        {
        if (AGrid.UpperCase().SubString((AGrid.Length()-2),3) == "MIL" )
                {
                AGrid = AGrid.SubString(1,(AGrid.Length()-3));
                AGrid = Str_Float_Format(AGrid);
                Gvalue = StrToFloat(AGrid);
                Gvalue = Gvalue/(float)39.37;
                }
        }
float originX;
float originY;
if ( Gvalue > BY_ZERO )
        {
        float Curx = 0;
        float Cury = 0;
        Gvalue = Gvalue * K_selrect * _106;
        Cury = SelRect.Top*K_selrect + Fill_Rect.Top + shifty + ShiftY;
        Curx = -SelRect.Left*K_selrect + Fill_Rect.Left + shiftx + ShiftX;
        originX = Curx;
        originY = Cury;
        Form2->pDC->Canvas->Pen->Width = 1;
        Form2->pDC->Canvas->Pen->Color = clRed;
        Form2->pDC->Canvas->Pen->Style = psSolid;
        while (Curx > Fill_Rect.Left)
                {
                Form2->pDC->Canvas->MoveTo(Curx,Fill_Rect.Bottom);
                Form2->pDC->Canvas->LineTo(Curx,Fill_Rect.Top);
                Curx -= Gvalue;
                }
        Curx = originX;
        while (Curx < Fill_Rect.Right)
                {
                Form2->pDC->Canvas->MoveTo(Curx,Fill_Rect.Bottom);
                Form2->pDC->Canvas->LineTo(Curx,Fill_Rect.Top);
                Curx += Gvalue;
                }
        Cury = originY;
        while (Cury > 0)
                {
                Form2->pDC->Canvas->MoveTo(Fill_Rect.Left,Cury);
                Form2->pDC->Canvas->LineTo(Fill_Rect.Right,Cury);
                Cury -= Gvalue;
                }
        Cury = originY;
        while (Cury < Fill_Rect.Bottom)
                {
                Form2->pDC->Canvas->MoveTo(Fill_Rect.Left,Cury);
                Form2->pDC->Canvas->LineTo(Fill_Rect.Right,Cury);
                Cury += Gvalue;
                }
        }
// Draw footprint...
        {
        #define NP 20
        Form2->pDC->Canvas->Pen->Width = 1;
        Form2->pDC->Canvas->Pen->Color = clRed;
        Form2->pDC->Canvas->Brush->Color = clRed;
        if( Mode != SET_RECTS )
        for( int STEP=0; STEP<2; STEP++ )
                {
                for (int cnt=Footprint_begin+1; cnt<Footprint_end; cnt++)
                        {
                        if((canvas_data[cnt].lay == lr_bottom && !STEP) ||
                           (canvas_data[cnt].lay == lr_top && STEP))
                                {
                                if( canvas_data[cnt].type == tp_empty )
                                        continue;
                                int W = (float)canvas_data[cnt].xn * K_selrect;
                                int H = (float)canvas_data[cnt].yn * K_selrect;
                                int R = (float)canvas_data[cnt].w * K_selrect;
                                if ((canvas_data[cnt].type == tp_round)||(canvas_data[cnt].type == tp_square)||(canvas_data[cnt].type == tp_octagon))
                                        {
                                        H = W;
                                        R = 0;
                                        if(canvas_data[cnt].type == tp_round)
                                                R = (float)W/2.0;
                                        else if (canvas_data[cnt].type == tp_octagon)
                                                R = (float)W/4.0;
                                        }
                                else if (canvas_data[cnt].type == tp_rect)
                                        {
                                        R = 0;
                                        }
                                else if (canvas_data[cnt].type == tp_oval)
                                        {
                                        R = MIN(W/2.0,H/2.0);
                                        //float buf = H;
                                        //H = W;
                                        //W = buf;
                                        }
                                else if (canvas_data[cnt].type == tp_rndrect)
                                        {
                                        R = R/2.0;
                                        }
                                int PinX = canvas_data[cnt].x;
                                int PinY = canvas_data[cnt].y;
                                PinX = (PinX - SelRect.Left) * K_selrect + Fill_Rect.Left + shiftx + ShiftX;
                                PinY = (SelRect.Top - PinY) * K_selrect + Fill_Rect.Top + shifty + ShiftY;
                                if( R == 0 )
                                        {
                                        float x1 = - H;
                                        float y1 = - W;
                                        float x2 = + H;
                                        float y2 = - W;
                                        float x3 = + H;
                                        float y3 = + W;
                                        float x4 = - H;
                                        float y4 = + W;
                                        float z1=0,z2=0,z3=0,z4=0;
                                        if(STEP)
                                                z1=z2=z3=z4 = -BoardThick * PER_MM * K_selrect;
                                        if(canvas_data[cnt].angle)
                                                {
                                                Rotate_Vertex(&x1,&y1,canvas_data[cnt].angle);
                                                Rotate_Vertex(&x2,&y2,canvas_data[cnt].angle);
                                                Rotate_Vertex(&x3,&y3,canvas_data[cnt].angle);
                                                Rotate_Vertex(&x4,&y4,canvas_data[cnt].angle);
                                                }
                                        x1 += PinX;
                                        y1 += PinY;
                                        x2 += PinX;
                                        y2 += PinY;
                                        x3 += PinX;
                                        y3 += PinY;
                                        x4 += PinX;
                                        y4 += PinY;
                                        if(GlobalCurveXY)
                                                {
                                                x1 -= originX;
                                                x2 -= originX;
                                                x3 -= originX;
                                                x4 -= originX;
                                                y1 -= originY;
                                                y2 -= originY;
                                                y3 -= originY;
                                                y4 -= originY;
                                                Rotate_Vertex(&x1,&y1,-GlobalCurveXY);
                                                Rotate_Vertex(&x2,&y2,-GlobalCurveXY);
                                                Rotate_Vertex(&x3,&y3,-GlobalCurveXY);
                                                Rotate_Vertex(&x4,&y4,-GlobalCurveXY);
                                                x1 += originX;
                                                x2 += originX;
                                                x3 += originX;
                                                x4 += originX;
                                                y1 += originY;
                                                y2 += originY;
                                                y3 += originY;
                                                y4 += originY;
                                                }
                                        if(GlobalCurveXZ)
                                                {
                                                x1 -= originX;
                                                x2 -= originX;
                                                x3 -= originX;
                                                x4 -= originX;
                                                Rotate_Vertex(&x1,&z1,GlobalCurveXZ);
                                                Rotate_Vertex(&x2,&z2,GlobalCurveXZ);
                                                Rotate_Vertex(&x3,&z3,GlobalCurveXZ);
                                                Rotate_Vertex(&x4,&z4,GlobalCurveXZ);
                                                x1 += originX;
                                                x2 += originX;
                                                x3 += originX;
                                                x4 += originX;
                                                }
                                        if(GlobalCurveYZ)
                                                {
                                                y1 -= originY;
                                                y2 -= originY;
                                                y3 -= originY;
                                                y4 -= originY;
                                                Rotate_Vertex(&y1,&z1,GlobalCurveYZ);
                                                Rotate_Vertex(&y2,&z2,GlobalCurveYZ);
                                                Rotate_Vertex(&y3,&z3,GlobalCurveYZ);
                                                Rotate_Vertex(&y4,&z4,GlobalCurveYZ);
                                                y1 += originY;
                                                y2 += originY;
                                                y3 += originY;
                                                y4 += originY;
                                                }
                                        TPoint Pt[4];
                                        Pt[0].x = x1;
                                        Pt[0].y = y1;
                                        Pt[1].x = x2;
                                        Pt[1].y = y2;
                                        Pt[2].x = x3;
                                        Pt[2].y = y3;
                                        Pt[3].x = x4;
                                        Pt[3].y = y4;
                                        Form2->pDC->Canvas->Polygon(Pt,3);
                                        }
                                else    {
                                        TPoint Pt[NP];
                                        int np = Gen_RndRectPoly(PinX,PinY,H*2,W*2,R*2,canvas_data[cnt].angle,Pt,(canvas_data[cnt].type == tp_octagon?8:NP));
                                        if(np)
                                                {
                                                float fPt[NP*3];
                                                for( int ii=0;ii<NP*3; ii+=3 )
                                                        {
                                                        fPt[ii] = Pt[ii/3].x;
                                                        fPt[ii+1] = Pt[ii/3].y;
                                                        if(STEP)
                                                                fPt[ii+2] = -BoardThick * PER_MM * K_selrect;
                                                        else
                                                                fPt[ii+2] = 0;
                                                        }
                                                if(GlobalCurveXY)
                                                        {
                                                        for( int ii=0;ii<NP*3; ii+=3 )
                                                                {
                                                                fPt[ii] -= originX;
                                                                fPt[ii+1] -= originY;
                                                                Rotate_Vertex(&(fPt[ii]),&(fPt[ii+1]),-GlobalCurveXY);
                                                                fPt[ii] += originX;
                                                                fPt[ii+1] += originY;
                                                                }
                                                        }
                                                if(GlobalCurveXZ)
                                                        {
                                                        for( int ii=0;ii<NP*3; ii+=3 )
                                                                {
                                                                fPt[ii] -= originX;
                                                                Rotate_Vertex(&(fPt[ii]),&(fPt[ii+2]),GlobalCurveXZ);
                                                                fPt[ii] += originX;
                                                                }
                                                        }
                                                if(GlobalCurveYZ)
                                                        {
                                                        for( int ii=0;ii<NP*3; ii+=3 )
                                                                {
                                                                fPt[ii+1] -= originY;
                                                                Rotate_Vertex(&(fPt[ii+1]),&(fPt[ii+2]),GlobalCurveYZ);
                                                                fPt[ii+1] += originY;
                                                                }
                                                        }
                                                for( int ii=0;ii<NP*3; ii+=3 )
                                                        {
                                                        Pt[ii/3].x = fPt[ii];
                                                        Pt[ii/3].y = fPt[ii+1];
                                                        }
                                                Form2->pDC->Canvas->Polygon(Pt,np-1);
                                                }
                                        }
                                }
                        }
                Form2->pDC->Canvas->Pen->Width = 1;
                Form2->pDC->Canvas->Pen->Color = clGreen;
                Form2->pDC->Canvas->Brush->Color = clGreen;
                }
        Form2->pDC->Canvas->Pen->Color = clGray;
        Form2->pDC->Canvas->Brush->Color = clGray;
        if( Mode != SET_RECTS )
        for (int cnt=Footprint_begin+1; cnt<Footprint_end; cnt++)
                {
                if (canvas_data[cnt].lay == lr_silk)
                        {
                        if (canvas_data[cnt].type == tp_line || canvas_data[cnt].type == tp_arc_cw || canvas_data[cnt].type == tp_arc_ccw)
                                {
                                long w = canvas_data[cnt].w;
                                long x = canvas_data[cnt].x;
                                long y = canvas_data[cnt].y;
                                long xn = canvas_data[cnt].xn;
                                long yn = canvas_data[cnt].yn;
                                w = w * K_selrect;
                                x = (x - SelRect.Left) * K_selrect + Fill_Rect.Left + shiftx + ShiftX;
                                y = (SelRect.Top - y) * K_selrect + Fill_Rect.Top + shifty + ShiftY;
                                xn = (xn - SelRect.Left) * K_selrect + Fill_Rect.Left + shiftx + ShiftX;
                                yn = (SelRect.Top - yn) * K_selrect + Fill_Rect.Top + shifty + ShiftY;
                                Form2->pDC->Canvas->Pen->Width = 1;//w+1;
                                float ARC[99];
                                int k = Generate_Line(x,y,xn,yn,(10-canvas_data[cnt].type), &ARC[0]);
                                float bfx=DEFAULT,bfy=DEFAULT;
                                for(int n=0; n<k; n=n+2)
                                        {
                                        float fx = ARC[n];
                                        float fy = ARC[n+1];
                                        float fz = -BoardThick * PER_MM * K_selrect;
                                        if(GlobalCurveXY)
                                                {
                                                fx -= originX;
                                                fy -= originY;
                                                Rotate_Vertex(&fx,&fy,-GlobalCurveXY);
                                                fx += originX;
                                                fy += originY;
                                                }
                                        if(GlobalCurveXZ)
                                                {
                                                fx -= originX;
                                                Rotate_Vertex(&fx,&fz,GlobalCurveXZ);
                                                fx += originX;
                                                }
                                        if(GlobalCurveYZ)
                                                {
                                                fy -= originY;
                                                Rotate_Vertex(&fy,&fz,GlobalCurveYZ);
                                                fy += originY;
                                                }
                                        if(bfx != DEFAULT)
                                                {
                                                Form2->pDC->Canvas->MoveTo((int)bfx,(int)bfy);
                                                Form2->pDC->Canvas->LineTo((int)fx,(int)fy);
                                                }
                                        bfx = fx;
                                        bfy = fy;
                                        }
                                }
                        }
                }
        Form2->pDC->Canvas->Pen->Color = clBlue;
        Form2->pDC->Canvas->Brush->Color = clBlue;
        if( Mode != SET_RECTS )
        for (int cnt=Footprint_begin+1; cnt<Footprint_end; cnt++)
                {
                if (canvas_data[cnt].lay == lr_drl && canvas_data[cnt].type == tp_point)
                        {
                        int PinX = canvas_data[cnt].x;
                        int PinY = canvas_data[cnt].y;
                        PinX = (PinX - SelRect.Left) * K_selrect + Fill_Rect.Left + shiftx + ShiftX;
                        PinY = (SelRect.Top - PinY) * K_selrect + Fill_Rect.Top + shifty + ShiftY;
                        TPoint Pt[NP];
                        int np = Gen_RndRectPoly(PinX,PinY,(canvas_data[cnt].w* K_selrect),
                                                           (canvas_data[cnt].w* K_selrect),
                                                           (canvas_data[cnt].w* K_selrect/2),
                                                           0,Pt,NP);
                        if(np == NP)
                                {
                                float fPt[NP*3];
                                for( int ii=0;ii<NP*3; ii+=3 )
                                        {
                                        fPt[ii] = Pt[ii/3].x;
                                        fPt[ii+1] = Pt[ii/3].y;
                                        fPt[ii+2] = -BoardThick * PER_MM * K_selrect;
                                        }
                                if(GlobalCurveXY)
                                        {
                                        for( int ii=0;ii<NP*3; ii+=3 )
                                                {
                                                fPt[ii] -= originX;
                                                fPt[ii+1] -= originY;
                                                Rotate_Vertex(&(fPt[ii]),&(fPt[ii+1]),-GlobalCurveXY);
                                                fPt[ii] += originX;
                                                fPt[ii+1] += originY;
                                                }
                                        }
                                if(GlobalCurveXZ)
                                        {
                                        for( int ii=0;ii<NP*3; ii+=3 )
                                                {
                                                fPt[ii] -= originX;
                                                Rotate_Vertex(&(fPt[ii]),&(fPt[ii+2]),GlobalCurveXZ);
                                                fPt[ii] += originX;
                                                }
                                        }
                                if(GlobalCurveYZ)
                                        {
                                        for( int ii=0;ii<NP*3; ii+=3 )
                                                {
                                                fPt[ii+1] -= originY;
                                                Rotate_Vertex(&(fPt[ii+1]),&(fPt[ii+2]),GlobalCurveYZ);
                                                fPt[ii+1] += originY;
                                                }
                                        }
                                for( int ii=0;ii<NP*3; ii+=3 )
                                        {
                                        Pt[ii/3].x = fPt[ii];
                                        Pt[ii/3].y = fPt[ii+1];
                                        }
                                Form2->pDC->Canvas->Polygon(Pt,np-1);
                                }
                        }
                }
        #undef NP
        }
// Draw ORIGIN
if (Gvalue > BY_ZERO)
        {
        Form2->pDC->Canvas->Pen->Width = 2;
        Form2->pDC->Canvas->Pen->Color = clWhite;
        //Form2->pDC->Canvas->Brush->Style = bsSolid;
        //Form2->pDC->Canvas->Brush->Color = clBlack;
        Form2->pDC->Canvas->MoveTo(originX-20,originY);
        Form2->pDC->Canvas->LineTo(originX+20,originY);
        Form2->pDC->Canvas->MoveTo(originX,originY-20);
        Form2->pDC->Canvas->LineTo(originX,originY+20);
        Form2->pDC->Canvas->Ellipse(originX-7,originY-7,originX+7,originY+7);
        }
// Draw 3D FACEs
float pX1,pY1,pZ1, pX2,pY2,pZ2, pX3,pY3,pZ3, pX4,pY4,pZ4;
int CL;
int InLns = 0;
float minx = DEFAULT;
float miny = DEFAULT;
float minz = DEFAULT;
float maxx = -DEFAULT;
float maxy = -DEFAULT;
float maxz = -DEFAULT;
if( Mode >= 0 )
for (int r=0; FACES[r] < DEFAULT; r=r+13)
        {
        float L1 = Length_Line(FACES[r+1],FACES[r+2],FACES[r+4],FACES[r+5],FACES[r+3],FACES[r+6]);
        float L2 = Length_Line(FACES[r+4],FACES[r+5],FACES[r+7],FACES[r+8],FACES[r+6],FACES[r+9]);
        float L3 = Length_Line(FACES[r+7],FACES[r+8],FACES[r+10],FACES[r+11],FACES[r+9],FACES[r+12]);
        float L4 = Length_Line(FACES[r+10],FACES[r+11],FACES[r+1],FACES[r+2],FACES[r+12],FACES[r+3]);
        minx = MIN(FACES[r+1],minx);
        maxx = MAX(FACES[r+1],maxx);
        miny = MIN(FACES[r+2],miny);
        maxy = MAX(FACES[r+2],maxy);
        minz = MIN(FACES[r+3],minz);
        maxz = MAX(FACES[r+3],maxz);
        minx = MIN4(minx,FACES[r+4],FACES[r+7],FACES[r+10]);
        maxx = MAX4(maxx,FACES[r+4],FACES[r+7],FACES[r+10]);
        miny = MIN4(miny,FACES[r+5],FACES[r+8],FACES[r+11]);
        maxy = MAX4(maxy,FACES[r+5],FACES[r+8],FACES[r+11]);
        minz = MIN4(minz,FACES[r+6],FACES[r+9],FACES[r+12]);
        maxz = MAX4(maxz,FACES[r+6],FACES[r+9],FACES[r+12]);
        if( Mode == SET_RECTS )
                continue;
        CL = FACES[r];
        pX1 = FACES[r+1]*_106;
        pY1 = FACES[r+2]*_106;
        pZ1 = FACES[r+3]*_106;
        pX2 = FACES[r+4]*_106;
        pY2 = FACES[r+5]*_106;
        pZ2 = FACES[r+6]*_106;
        pX3 = FACES[r+7]*_106;
        pY3 = FACES[r+8]*_106;
        pZ3 = FACES[r+9]*_106;
        pX4 = FACES[r+10]*_106;
        pY4 = FACES[r+11]*_106;
        pZ4 = FACES[r+12]*_106;
        if( GlobalCurveXY )
                {
                Rotate_Vertex( &pX1, &pY1, GlobalCurveXY );
                Rotate_Vertex( &pX2, &pY2, GlobalCurveXY );
                Rotate_Vertex( &pX3, &pY3, GlobalCurveXY );
                Rotate_Vertex( &pX4, &pY4, GlobalCurveXY );
                }
        if( GlobalCurveXZ )
                {
                Rotate_Vertex( &pX1, &pZ1, -GlobalCurveXZ );
                Rotate_Vertex( &pX2, &pZ2, -GlobalCurveXZ );
                Rotate_Vertex( &pX3, &pZ3, -GlobalCurveXZ );
                Rotate_Vertex( &pX4, &pZ4, -GlobalCurveXZ );
                }
        if( GlobalCurveYZ )
                {
                Rotate_Vertex( &pY1, &pZ1, GlobalCurveYZ );
                Rotate_Vertex( &pY2, &pZ2, GlobalCurveYZ );
                Rotate_Vertex( &pY3, &pZ3, GlobalCurveYZ );
                Rotate_Vertex( &pY4, &pZ4, GlobalCurveYZ );
                }
        pX1 = (pX1 - SelRect.Left) * K_selrect + Fill_Rect.Left + shiftx;
        pY1 = (SelRect.Top - pY1) * K_selrect + Fill_Rect.Top + shifty;
        pX2 = (pX2 - SelRect.Left) * K_selrect + Fill_Rect.Left + shiftx;
        pY2 = (SelRect.Top - pY2) * K_selrect + Fill_Rect.Top + shifty;
        pX3 = (pX3 - SelRect.Left) * K_selrect + Fill_Rect.Left + shiftx;
        pY3 = (SelRect.Top - pY3) * K_selrect + Fill_Rect.Top + shifty;
        pX4 = (pX4 - SelRect.Left) * K_selrect + Fill_Rect.Left + shiftx;
        pY4 = (SelRect.Top - pY4) * K_selrect + Fill_Rect.Top + shifty;
        Form2->pDC->Canvas->Pen->Color = clYellow;
        Form2->pDC->Canvas->Brush->Color = clMedGray;
        Form2->pDC->Canvas->Brush->Style = bsClear;
        Form2->pDC->Canvas->Pen->Width = 1;
        if (CL == StringGridIndexRow && Form2->StringGrid1->Col > 1 && Form2->Select->Count == 0 )
                {
                Form2->pDC->Canvas->Pen->Color = clWhite;
                Form2->pDC->Canvas->Brush->Color = clMedGray;
                Form2->pDC->Canvas->Brush->Style = bsDiagCross;
                Form2->pDC->Canvas->Pen->Width = 3;
                }
        FloatPoint Points[4];
        int MINLEN = 99;
        Form2->pDC->Canvas->Font->Name="Areal";
        Form2->pDC->Canvas->Font->Size = 10;
        Form2->pDC->Canvas->Font->Color = clWhite;
        pX1 += ShiftX;
        pY1 += ShiftY;
        pX2 += ShiftX;
        pY2 += ShiftY;
        pX3 += ShiftX;
        pY3 += ShiftY;
        pX4 += ShiftX;
        pY4 += ShiftY;
        Points[0].x = pX1;
        Points[0].y = pY1;
        Points[1].x = pX2;
        Points[1].y = pY2;
        Points[2].x = pX3;
        Points[2].y = pY3;
        Points[3].x = pX4;
        Points[3].y = pY4;
        if      (Points[0].x == Points[1].x && Points[0].y == Points[1].y)
                {
                Form2->pDC->Canvas->MoveTo(Points[1].x,Points[1].y);
                Form2->pDC->Canvas->LineTo(Points[2].x,Points[2].y);
                }
        else if (Points[3].x == Points[0].x && Points[3].y == Points[0].y)
                {
                Form2->pDC->Canvas->MoveTo(Points[0].x,Points[0].y);
                Form2->pDC->Canvas->LineTo(Points[1].x,Points[1].y);
                }
        else    {
                TPoint Pts[4];
                Pts[0].x = pX1;
                Pts[0].y = pY1;
                Pts[1].x = pX2;
                Pts[1].y = pY2;
                Pts[2].x = pX3;
                Pts[2].y = pY3;
                Pts[3].x = pX4;
                Pts[3].y = pY4;
                Form2->pDC->Canvas->Polygon(Pts,3);
                }
        if (Form2->ShowLengthofSides1->Checked && Form2->Select->Count == 0)
                {
                if ((Points[0].x-Points[1].x)>MINLEN || (Points[0].y-Points[1].y)>MINLEN )
                        Form2->pDC->Canvas->TextOutA((pX1+pX2)/2+3,(pY1+pY2)/2,AnsiString(F_str(L1))) ;
                if ((Points[1].x-Points[2].x)>MINLEN || (Points[1].y-Points[2].y)>MINLEN )
                        Form2->pDC->Canvas->TextOutA((pX2+pX3)/2+3,(pY2+pY3)/2,AnsiString(F_str(L2))) ;
                if ((Points[2].x-Points[3].x)>MINLEN || (Points[2].y-Points[3].y)>MINLEN )
                        Form2->pDC->Canvas->TextOutA((pX3+pX4)/2+3,(pY3+pY4)/2,AnsiString(F_str(L3))) ;
                if ((Points[3].x-Points[0].x)>MINLEN || (Points[3].y-Points[0].y)>MINLEN )
                        Form2->pDC->Canvas->TextOutA((pX4+pX1)/2+3,(pY4+pY1)/2,AnsiString(F_str(L4))) ;
                }
        LINES[InLns] =    CL;
        LINES[InLns+1] =  Points[0].x;
        LINES[InLns+2] =  Points[0].y;
        LINES[InLns+3] =  Points[1].x;
        LINES[InLns+4] =  Points[1].y;
        LINES[InLns+5] =  Points[2].x;
        LINES[InLns+6] =  Points[2].y;
        LINES[InLns+7] =  Points[3].x;
        LINES[InLns+8] =  Points[3].y;
        InLns = InLns+9;
        Form2->pDC->Canvas->Brush->Style = bsSolid;
        }
LINES[InLns] = DEFAULT + 1;
Form1->NamesOfBlocks->Clear();
//Цвет текста
Form2->pDC->Canvas->Font->Color=clWhite;
//Размер шрифта в точках
Form2->pDC->Canvas->Font->Size = (Fill_Rect.Right - Fill_Rect.Left)/20;
if (Form2->pDC->Canvas->Font->Size > 20) Form2->pDC->Canvas->Font->Size = 20;
//Стиль шрифта
//TFontStyles tFontStyle;
//Зачеркнутый, наклонный, жирный, подчепкнутый
///tFontStyle << fsStrikeOut << fsItalic << fsBold << fsUnderline;
//Form2->pDC->Canvas->Font->Style =tFontStyle;
//Имя шрифта
Form2->pDC->Canvas->Brush->Color = clBlack;
Form2->pDC->Canvas->Font->Name="Areal";
Form2->pDC->Canvas->TextOutA(Fill_Rect.Left+5,Fill_Rect.Top+5,Nm) ;
Form2->pDC->Canvas->Font->Size = (Fill_Rect.Right - Fill_Rect.Left)/30;
if (Form2->pDC->Canvas->Font->Size > 10) Form2->pDC->Canvas->Font->Size = 10;
AnsiString Sizing = "Total size X: " + FormatFloat("0.000",(maxx - minx)) + "mm Total size Y: " + FormatFloat("0.000",(maxy - miny)) + "mm";
if (minx < DEFAULT && Form2->StringGrid1->Visible) Form2->pDC->Canvas->TextOutA(Fill_Rect.Left+10,Fill_Rect.Bottom-45, Sizing) ;
// SizeRects
if ((maxx-minx) > BY_ZERO)
        {
        SizeRects[JumpsIndexInfo].Left =        minx*_106;
        SizeRects[JumpsIndexInfo].Right =       maxx*_106;
        }
else if ((SelRect.Right-SelRect.Left) > BY_ZERO)
        {
        SizeRects[JumpsIndexInfo].Left =        SelRect.Left;
        SizeRects[JumpsIndexInfo].Right =       SelRect.Right;
        }
else    {
        SizeRects[JumpsIndexInfo].Left =        0;
        SizeRects[JumpsIndexInfo].Right =       0;
        }
if ((maxy-miny) > BY_ZERO)
        {
        SizeRects[JumpsIndexInfo].Top =         maxy*_106;
        SizeRects[JumpsIndexInfo].Bottom =      miny*_106;
        }
else if ((SelRect.Top-SelRect.Bottom) > BY_ZERO)
        {
        SizeRects[JumpsIndexInfo].Top =         SelRect.Top;
        SizeRects[JumpsIndexInfo].Bottom =      SelRect.Bottom;
        }
else    {
        SizeRects[JumpsIndexInfo].Top =         0;
        SizeRects[JumpsIndexInfo].Bottom =      0;
        }
if ((maxz-minz) > BY_ZERO)
        {
        SizeRects[JumpsIndexInfo]._Low =        minz*_106;
        SizeRects[JumpsIndexInfo]._High =       maxz*_106;
        }
else if ((SelRect._High-SelRect._Low) > BY_ZERO)
        {
        SizeRects[JumpsIndexInfo]._Low =         SelRect._Low;
        SizeRects[JumpsIndexInfo]._High =        SelRect._High;
        }
else    {
        SizeRects[JumpsIndexInfo]._Low =         0;
        SizeRects[JumpsIndexInfo]._High =        0;
        }
if (Footprint_begin < 0)
        {
        //Цвет текста
        Form2->pDC->Canvas->Font->Color=clRed;
        //Размер шрифта в точках
        Form2->pDC->Canvas->Font->Size = (Fill_Rect.Right - Fill_Rect.Left)/20;
        if (Form2->pDC->Canvas->Font->Size > 20) Form2->pDC->Canvas->Font->Size = 20;
        //Стиль шрифта
        //TFontStyles tFontStyle;
        //Зачеркнутый, наклонный, жирный, подчепкнутый
        ///tFontStyle << fsStrikeOut << fsItalic << fsBold << fsUnderline;
        //Form2->pDC->Canvas->Font->Style =tFontStyle;
        //Имя шрифта
        Form2->pDC->Canvas->Brush->Color = clBlack;
        Form2->pDC->Canvas->Font->Name="Areal";
        //Form2->pDC->Canvas->TextOutA(Fill_Rect.Left+5,Fill_Rect.Top+35,"Not found") ;
        }
NmB = Nm;

// Draw window
if( Mode != SET_RECTS )
        Form2->Canvas->CopyRect( Fill_Rect, Form2->pDC->Canvas, Fill_Rect );
return true;
}
//---------------------------------------------------------------------------










//---------------------------------------------------------------------------
bool FIND (bool mode)
        {
        AnsiString ST;
        if(mode)for (int t=0; t<Form2->FootPrints->Items->Count; t++ )
                {
                ST = Form2->FootPrints->Items->operator [](t);
                if (ST.UpperCase().SubString(1,StringF.Length()) == StringF.UpperCase().SubString(1,StringF.Length()))
                        {
                        Form2->FootPrints->ItemIndex = t;
                        StringF = ST;
                        break;
                        }
                }
        Form2->StringGrid1->Row = Form2->StringGrid1->RowCount-1;
        for (int t=1; t<Form2->StringGrid1->RowCount; t++)
                {
                ST = Form2->StringGrid1->Cells[PACKAGES][t];
                if( mode )
                        {
                        if (ST.UpperCase().SubString(1,StringF.Length()) == StringF.UpperCase().SubString(1,StringF.Length()))
                                {
                                Form2->StringGrid1->Row = t;
                                Form2->StringGrid1->Col = 0;
                                StringGridIndexRow = Form2->StringGrid1->Row;
                                if( Form2->PageControl1->TabIndex == 1 )
                                        Form2->StringGrid1->Refresh();
                                return true;
                                }
                        }
                else    {
                        if (ST.UpperCase().SubString(1,ST.Length()) == StringF.UpperCase().SubString(1,StringF.Length()))
                                {
                                Form2->StringGrid1->Row = t;
                                Form2->StringGrid1->Col = 0;
                                StringGridIndexRow = Form2->StringGrid1->Row;
                                if( Form2->PageControl1->TabIndex == 1 )
                                        Form2->StringGrid1->Refresh();
                                return true;
                                }
                        }
                }
        return false;
        }
//---------------------------------------------------------------------------











//---------------------------------------------------------------------------
void TForm2::R_Library( bool ch )
{
if (ch)
        LibPath = ExtractFilePath(Form1->OpenDialog1->FileName) + "related_files\\";
else
        LibPath = ExtractFilePath(Application->ExeName);
char s[DEF_CHAR];
FILE* F;
F = fopen((LibPath + "dxf_lib.csv").c_str(),"rb+");
if(F == 0)
        {
        if(ch == 0)
                {
                ShowMessage("Library file dxf_lib.csv not found!");
                exit(0);
                }
        else    {
                fclose(F);
                return;
                }
        }
fclose(F);
ifstream Rlib ((LibPath + "dxf_lib.csv").c_str());
Form1->OutputBox->Clear();
Form1->OutputBox->Sorted = true;
Rlib.getline(s,DEF_CHAR);
AnsiString S = s;
S = S.Trim();
AnsiString R = "";
int max = S.Length();
long col = 0;
if (S.SubString(1,7) != "Package" && S.SubString(1,4) != "Foot")
        {
        if (S.Length())
                {
                //ShowMessage("  Message:\n\n    En: Error file dxf_lib.csv!\n    Ru: Ошибка в Файле dxf_lib.csv!");
                exit(0);
                }
        }
while (!Rlib.eof())
        {
        Rlib.getline(s,DEF_CHAR);
        S = s;
        S = S.Trim();
        if (S.Length())
                Form1->OutputBox->Items->Add(S);
        else    break;
        }
Rlib.close();
//
Form2->Shapes->Clear();
Form2->Shapes->Sorted = true;
//AnsiString NB = "";
Form2->StringGrid1->RowCount = 2;
for (int c=0; c<COL_COUNT; c++)
        Form2->StringGrid1->Cells[c][1] = "";
for (int k=0; k<Form1->OutputBox->Items->Count; k++)
        {
        Form2->StringGrid1->RowCount++;
        for (int c=0; c<COL_COUNT; c++)
                Form2->StringGrid1->Cells[c][Form2->StringGrid1->RowCount-1] = "";
        S = Form1->OutputBox->Items->operator [](k);
        R = "";
        col = 0;
        max = S.Length();
        for (int g=1; g<=max; g++)
                {
                if (S.SubString(g,1) == ";")
                        {
                        Form2->StringGrid1->Cells[col][k+1] = R;
                        if (col == 0)
                                {
                                if( Form2->Shapes->Items->IndexOf(R) == -1 )
                                        Form2->Shapes->Items->Add(R);
                                }
                        R = "";
                        col++;
                        }
                else if (g == max)
                        {
                        R = R + S.SubString(g,1);
                        Form2->StringGrid1->Cells[col][k+1] = R;
                        if (col == 0)
                                {
                                if( Form2->Shapes->Items->IndexOf(R) == -1 )
                                        Form2->Shapes->Items->Add(R);
                                }
                        R = "";
                        col++;
                        }
                else    R = R + S.SubString(g,1);
                }
        }
Form1->OutputBox->Clear();
Form1->OutputBox->Sorted = false;
Form2->StringGrid1->Row = Form2->StringGrid1->RowCount-1;
StringGridIndexRow = Form2->StringGrid1->Row;
Form2->StringGrid1->Col = COL_COUNT-1;
long i;
for (int u=0; u<Form1->File->Count; u++)
        {
        AnsiString A = Form1->File->Items->operator [](u);
        if (A.SubString(1,9) == "package: ")
                {
                i = prob(A,1);
                AnsiString PACK = ex_str(A,&i);
                MOD(&PACK);
                if (Form2->StringGrid1->Cols[PACKAGES]->IndexOf(PACK) == -1 || !PACK.Length())
                        {
                        Form2->StringGrid1->RowCount++;
                        for (int c=0; c<COL_COUNT; c++)
                                Form2->StringGrid1->Cells[c][Form2->StringGrid1->RowCount-1] = "";
                        Form2->StringGrid1->Cells[PACKAGES][Form2->StringGrid1->Row] = PACK;
                        Form2->StringGrid1->Row++;
                        }
                }
        }
Form2->FootPrints->Items->Clear();
/*Form2->Shapes->MultiSelect = true;
Form2->Shapes->SelectAll();
Form2->Shapes->CopySelection(Form2->FootPrints);
Form2->Shapes->ClearSelection();*/
Form2->Shapes->MultiSelect = false;
Form2->Shapes->Sorted = false;
Form2->Shapes->Items->Add("Silk");
Form2->Shapes->Items->Add("Triangle");
Form2->Shapes->Items->Add("Sector");
Form2->Shapes->Items->Add("Arc");
Form2->Shapes->Items->Add("Pin");
Form2->Shapes->Items->Add("Oval");
Form2->Shapes->Items->Add("Rect");
}
//---------------------------------------------------------------------------










//---------------------------------------------------------------------------
void TForm2::S_Library( bool ch, bool bONLY )
{
if (ch)
        LibPath = ExtractFilePath(Form1->OpenDialog1->FileName) + "related_files\\";
else
        LibPath = ExtractFilePath(Application->ExeName);
ofstream Wlib ((LibPath + "dxf_lib.csv").c_str());
AnsiString R,S,F,Fn;
for (int n=0; n<(Form2->StringGrid1->RowCount-1); n++)
        {
        if (MARKS[n] == 0 && bONLY && ch && n)
                continue;
        F = Form2->StringGrid1->Cells[PACKAGES][n];
        Fn = F;
        if( F.Length() )
                {
                while ( Fn.SubString(1,Fn.Length())==F.SubString(1,F.Length()) )
                        {
                        R = "";
                        if (Form2->StringGrid1->Cells[PACKAGES][n].Length())
                        if (Form2->StringGrid1->Cells[SHAPE][n].Length())
                        for (int m=0; m<COL_COUNT; m++)
                                {
                                S = Form2->StringGrid1->Cells[m][n];
                                if (m == 0 || m == 1)
                                        MOD(&S);
                                R = R + S + ";" ;
                                }
                        if (R.Length()) Wlib << R.c_str() << endl;
                        n++;
                        Fn = Form2->StringGrid1->Cells[PACKAGES][n];
                        }
                n = n-1;
                }
        }
Wlib.close();
}
//---------------------------------------------------------------------------












//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
Form2->Used->MultiSelect = true;
Form2->Select->Visible = false;
Form2->Select->Sorted = false;
Form2->ProgressBar1->Visible = false;
Form2->pDC->Visible = false;
Form2->pDC->Left = 0;
Form2->pDC->Top = 0;
Form2->pDC->Width = Form2->ClientWidth;
Form2->pDC->Height = Form2->ClientHeight;
Form2->StringGrid1->ColCount =          COL_COUNT;
Form2->StringGrid1->RowCount =          2;
Form2->StringGrid1->FixedCols =         0;
Form2->StringGrid1->FixedRows =         0;
Form2->StringGrid1->DefaultColWidth =   35;
Form2->StringGrid1->ColWidths[0] =      99;
Form2->StringGrid1->ColWidths[1] =      60;
Form2->StringGrid1->Cells[PACKAGES][0] =        "Package";
Form2->StringGrid1->Cells[SHAPE][0] =           "Shape";
Form2->StringGrid1->Cells[SIZE_X][0] =          "W";
Form2->StringGrid1->Cells[SIZE_Y][0] =          "L";
Form2->StringGrid1->Cells[SIZE_Z][0] =          "H";
Form2->StringGrid1->Cells[ANGLE_XY][0] =        "Ang1";
Form2->StringGrid1->Cells[ANGLE_XZ][0] =        "Ang2";
Form2->StringGrid1->Cells[ANGLE_YZ][0] =        "Ang3";
Form2->StringGrid1->Cells[SHIFT_X][0] =         "Sh X";
Form2->StringGrid1->Cells[SHIFT_Y][0] =         "Sh Y";
Form2->StringGrid1->Cells[SHIFT_Z][0] =         "Sh Z";
Form2->PageControl1->TabIndex = 0;

//GridValues
Form2->GridValues->Items->Add("5mil");
Form2->GridValues->Items->Add("10mil");
Form2->GridValues->Items->Add("20mil");
Form2->GridValues->Items->Add("50mil");
Form2->GridValues->Items->Add("100mil");
Form2->GridValues->Items->Add("200mil");
Form2->GridValues->Items->Add("500mil");
Form2->GridValues->Items->Add("0.1mm");
Form2->GridValues->Items->Add("0.2mm");
Form2->GridValues->Items->Add("0.25mm");
Form2->GridValues->Items->Add("0.3mm");
Form2->GridValues->Items->Add("0.4mm");
Form2->GridValues->Items->Add("0.5mm");
Form2->GridValues->Items->Add("0.65mm");
Form2->GridValues->Items->Add("0.8mm");
Form2->GridValues->Items->Add("1mm");
Form2->GridValues->Items->Add("2mm");
Form2->GridValues->Items->Add("2.54mm");
Form2->GridValues->Items->Add("5mm");
Form2->GridValues->Items->Add("10mm");
Form2->GridValues->Items->Add("20mm");
Form2->GridValues->Items->Add("50mm");
Form2->GridValues->ItemIndex = 17;

// DrawGpoupList
Form2->DrawGroupList->Style = csOwnerDrawFixed;
Form2->DrawGroupList->Sorted = 0;
Form2->DrawGroupList->Items->Add("All Objects");
Form2->DrawGroupList->Items->Add("All in this Project");
Form2->DrawGroupList->Items->Add("Used in others Parts");
Form2->DrawGroupList->Items->Add("Auxiliary Parts");
Form2->DrawGroupList->ItemIndex = 1;
//
AnsiString S = "Shift + mouse wheel: discrete = 0.5mm";
StringGrid1->Hint = S;
Form2_INI();
}
//---------------------------------------------------------------------------

void TForm2::Form2_INI()
{
try     {
        FACES = new(std::nothrow) float[_103];
        }
catch(std::bad_alloc)
        {
        ShowMessage("float[" + AnsiString(_103) + "]!" );
        exit(0);
        }
try     {
        LINES = new(std::nothrow) int[_103];
        }
catch(std::bad_alloc)
        {
        ShowMessage("int[" + AnsiString(_103) + "]!" );
        exit(0);
        }
MAX_FACES_AND_LINES = _103-99;

// canvas rect
Fill_Rect.Left = Form2->PageControl1->Width+5;
Fill_Rect.Top = 0;
Fill_Rect.Right = MAX(Form2->ClientWidth,Fill_Rect.Left+1);
Fill_Rect.Bottom = MAX(Form2->ClientHeight-65,1);

// reading lib
R_Library(SvLib->Checked);
GetRects();
Form1->Visible = true;
Form5->Visible = false;
}











//---------------------------------------------------------------------------
void __fastcall TForm2::StringGrid1GetEditText(TObject *Sender, int ACol,
      int ARow, AnsiString &Value)
{
if (Form2->StringGrid1->Row == (Form2->StringGrid1->RowCount-1))
        {
        Form2->StringGrid1->RowCount++;
        for (int q=0; q<COL_COUNT; q++)
                Form2->StringGrid1->Cells[q][Form2->StringGrid1->RowCount-1] = "";
        ShiftSizeRectsArrow(Form2->StringGrid1->RowCount,1);
        }
}
//---------------------------------------------------------------------------












//---------------------------------------------------------------------------
void __fastcall TForm2::FormClose(TObject *Sender, TCloseAction &Action)
{
Form2->Visible = 0;
Form2->SvLib->Enabled = true;
Application->ProcessMessages();
if( bLibModified )
        {
        if( MessageBox( NULL, "Save changes?", "The library has been modified.", MB_YESNO | MB_ICONQUESTION ) == ID_YES )
                {
                S_Library(SvLib->Checked,SvLib->Checked);
                }
        }
else    S_Library(SvLib->Checked,SvLib->Checked);
delete[] MARKS;
MARKS = NULL;
bLibModified = 0;
}
//---------------------------------------------------------------------------






//---------------------------------------------------------------------------
void __fastcall TForm2::StringGrid1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
StringF = Form2->StringGrid1->Cells[Form2->StringGrid1->Col][Form2->StringGrid1->Row];
StringGridIndexRow = Form2->StringGrid1->Row;
Form2->Select->Clear();
Form2->Shapes->Visible = 0;
Application->ProcessMessages();
for( int t=StringGridIndexRow; t<Form2->StringGrid1->RowCount && t<StringGridIndexRow+20; t++ )
        if( Form2->StringGrid1->Cells[PACKAGES][t].Length() )
                if( Form2->Shapes->Items->IndexOf(Form2->StringGrid1->Cells[PACKAGES][t]) == -1 )
                        Form2->Shapes->Items->Add(Form2->StringGrid1->Cells[PACKAGES][t]);
for( int t=StringGridIndexRow; t>0 && t>StringGridIndexRow-20; t-- )
        if( Form2->StringGrid1->Cells[PACKAGES][t].Length() )
                if( Form2->Shapes->Items->IndexOf(Form2->StringGrid1->Cells[PACKAGES][t]) == -1 )
                        Form2->Shapes->Items->Add(Form2->StringGrid1->Cells[PACKAGES][t]);
}
//---------------------------------------------------------------------------








//---------------------------------------------------------------------------
void __fastcall TForm2::StringGrid1MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if (SwapRow >= 0 && SwapCol >= 0)
        {
        AnsiString buf = Form2->StringGrid1->Cells[SwapCol][SwapRow];
        Form2->StringGrid1->Cells[SwapCol][SwapRow] = Form2->StringGrid1->Cells[Form2->StringGrid1->Col][Form2->StringGrid1->Row];
        Form2->StringGrid1->Cells[Form2->StringGrid1->Col][Form2->StringGrid1->Row] = buf;
        }
SwapRow = -1;
SwapCol = -1;
Form2->CheckBox1->Checked = false;
Form2->StringGrid1->Refresh();
Canva(CANVAS);
}
//---------------------------------------------------------------------------












//---------------------------------------------------------------------------
void TForm2::myResize(bool Mode)
{
// canvas rect
Fill_Rect.Left = Form2->PageControl1->Width+5;
Fill_Rect.Top = 0;
Fill_Rect.Right = MAX(Form2->ClientWidth,Fill_Rect.Left+1);
Fill_Rect.Bottom = MAX(Form2->ClientHeight-65,1);
//
Form2->Draw->Enabled = true;
if (Mode && Form2->Visible)
        {
        Form2->ProgressBar1->Top = Form2->ClientHeight - 40;
        Form2->PageControl1->Left = 0;
        Form2->PageControl1->Top = 0;
        Form2->PageControl1->Height = Form2->ClientHeight - 60;
        Form2->StringGrid1->Left = 0;
        Form2->StringGrid1->Top = 0;
        Form2->StringGrid1->Width = Form2->PageControl1->ClientWidth-1;
        Form2->StringGrid1->Height = Form2->Editor->ClientHeight-1;
        Form2->FootPrints->Height = Form2->Viewer->ClientHeight-15;
        Form2->GroupBox1->Height = Form2->Viewer->ClientHeight-50;
        Form2->SelAll->Top = Form2->Viewer->ClientHeight-40;
        Form2->DelSel->Top = Form2->Viewer->ClientHeight-40;
        Form2->Used->Height = Form2->GroupBox1->ClientHeight-24;
        Form2->v2d->Top = Form2->ClientHeight - 57;
        Form2->v3d->Top = Form2->ClientHeight - 57;
        Form2->GroupBox2->Top = Form2->ClientHeight - 57;
        Form2->GroupBox3->Top = Form2->ClientHeight - 57;
        Form2->GroupBox4->Top = Form2->ClientHeight - 57;
        Form2->DrawGpoupObjects->Top = Form2->ClientHeight - 57;
        Form2->CheckBox1->Top = Form2->ClientHeight - 40;
        Form2->pDC->Canvas->Pen->Color = Form2->Color;
        Form2->pDC->Canvas->Brush->Color = Form2->Color;
        Form2->pDC->Canvas->Rectangle(0,0,Form2->ClientWidth,Form2->ClientHeight);
        TRect Total_Rect;
        Total_Rect.Left = 0;
        Total_Rect.Top = 0;
        Total_Rect.Right = Form2->ClientWidth;
        Total_Rect.Bottom = Form2->ClientHeight;
        Form2->StringGrid1->Col = COL_COUNT-1;
        Form2->Refresh();
        Form2->Canvas->CopyRect( Total_Rect, Form2->pDC->Canvas, Total_Rect );
        }
}
//---------------------------------------------------------------------------









//---------------------------------------------------------------------------
void __fastcall TForm2::Edit1Change(TObject *Sender)
{
StringF = Form2->Edit1->Text;
FIND(true);
Canva(CANVAS);
if( Form2->FootPrints->ItemIndex >= 0 )
        {
        AnsiString s = Form2->FootPrints->Items->operator [](Form2->FootPrints->ItemIndex);
        if(Form2->PageControl1->TabIndex == 0)
                WhereElseIsThisPartUsed ( &s, Form2->Used);
        }
}
//---------------------------------------------------------------------------











//---------------------------------------------------------------------------
void __fastcall TForm2::StringGrid1MouseWheelDown(TObject *Sender,
      TShiftState Shift, TPoint &MousePos, bool &Handled)
{
if( Form2->StringGrid1->Row == 0 )
        return;
else if( Form2->StringGrid1->Row == Form2->StringGrid1->RowCount-1 )
        {
        Form2->StringGrid1->RowCount++;
        for (int q=0; q<COL_COUNT; q++)
                Form2->StringGrid1->Cells[q][Form2->StringGrid1->RowCount-1] = "";
        }
if (CTRL) return;
if (Form2->StringGrid1->Col > 1 )
        {
        if( Form2->StringGrid1->Col < 8 )
                DownGridValues(Form2->StringGrid1->Col);
        else    {
                Form2->vTop->SetFocus();
                SetCursorPos((Fill_Rect.Left + Fill_Rect.Right)/2 + Form2->Left,(Fill_Rect.Bottom + Fill_Rect.Top)/2 + Form2->Top);
                }
        Form2->StringGrid1->Row--;
        }
if (Form2->StringGrid1->Col == 0)
        {
        Form2->Select->Clear();
        }
StringGridIndexRow = Form2->StringGrid1->Row+1;
Form2->StringGrid1->Refresh();
if (Form2->StringGrid1->Col > 1)
        Canva(CANVAS);
}
//---------------------------------------------------------------------------












//---------------------------------------------------------------------------
void __fastcall TForm2::StringGrid1MouseWheelUp(TObject *Sender,
      TShiftState Shift, TPoint &MousePos, bool &Handled)
{
if( Form2->StringGrid1->Row == 0 || Form2->StringGrid1->Row == Form2->StringGrid1->RowCount-1 )
        return;
if (CTRL) return;
if (Form2->StringGrid1->Col > 1 )
        {
        if( Form2->StringGrid1->Col < 8 )
                UpGridValues(Form2->StringGrid1->Col);
        else    {
                Form2->vTop->SetFocus();
                SetCursorPos((Fill_Rect.Left + Fill_Rect.Right)/2 + Form2->Left,(Fill_Rect.Bottom + Fill_Rect.Top)/2 + Form2->Top);
                }
        Form2->StringGrid1->Row++;
        }
if (Form2->StringGrid1->Col == 0)
        {
        Form2->Select->Clear();
        }
StringGridIndexRow = Form2->StringGrid1->Row-1;
Form2->StringGrid1->Refresh();
if (Form2->StringGrid1->Col > 1)
        Canva(CANVAS);
}
//---------------------------------------------------------------------------











//---------------------------------------------------------------------------
void __fastcall TForm2::StringGrid1DrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
AnsiString S1 = Form2->StringGrid1->Cells[PACKAGES][ARow];
AnsiString S2 = Form2->StringGrid1->Cells[PACKAGES][StringGridIndexRow];
if ( Form2->CheckBox1->Checked && ACol == Form2->StringGrid1->Col && ARow == Form2->StringGrid1->Row )
        {
        Form2->StringGrid1->Canvas->Brush->Color = clBlack;
        Form2->StringGrid1->Canvas->Font->Color = clWhite;
        Form2->StringGrid1->Canvas->FillRect(Rect);
        }
else if (Form2->StringGrid1->Cells[SHAPE][ARow].Length() == 0 && Form2->StringGrid1->Cells[PACKAGES][ARow].Length() != 0)
        {
        Form2->StringGrid1->Canvas->Brush->Color = clAqua;
        Form2->StringGrid1->Canvas->Font->Color = clBlack;
        Form2->StringGrid1->Canvas->FillRect(Rect);
        }
else if (ARow == StringGridIndexRow)
        {
        Form2->StringGrid1->Canvas->Brush->Color = clMedGray;
        Form2->StringGrid1->Canvas->Font->Color = clBlack;
        Form2->StringGrid1->Canvas->FillRect(Rect);
        }
else if (S1.SubString(1,S1.Length()) == S2.SubString(1,S2.Length()))
        {
        Form2->StringGrid1->Canvas->Brush->Color = clActiveBorder;
        Form2->StringGrid1->Canvas->Font->Color = clBlack;
        Form2->StringGrid1->Canvas->FillRect(Rect);
        }
else    {
        Form2->StringGrid1->Canvas->Brush->Color = clWhite;
        Form2->StringGrid1->Canvas->Font->Color = clBlack;
        Form2->StringGrid1->Canvas->FillRect(Rect);
        }
DrawText(Form2->StringGrid1->Canvas->Handle,
Form2->StringGrid1->Cells[ACol][ARow].c_str(),
Form2->StringGrid1->Cells[ACol][ARow].Length(),&Rect, DT_CENTER);
}
//---------------------------------------------------------------------------










//---------------------------------------------------------------------------











//---------------------------------------------------------------------------
void __fastcall TForm2::StringGrid1KeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if (Key == VK_CONTROL)          CTRL = true;
else if (Key == VK_SHIFT)       SHIFT = true;
if (CTRL)
        return;
if( Form2->Shapes->Visible )
        {
        if(     Key == VK_LEFT ||
                Key == VK_RIGHT ||
                Key == VK_UP||
                Key == VK_DOWN )
                Form2->Shapes->SetFocus();
        if( Key == VK_RETURN )
                {
                int ii = Form2->Shapes->ItemIndex;
                AnsiString str = Form2->Shapes->Items->operator [](ii);
                if( str.Length() )
                        {
                        Form2->StringGrid1->Cells[Form2->StringGrid1->Col][StringGridIndexRow] = str;
                        Form2->Shapes->Visible = 0;
                        Form2->StringGrid1->Refresh();
                        Canva(CANVAS);
                        }
                }
        return;
        }
int shX=SHIFT_X, shY=SHIFT_Y, shZ=SHIFT_Z;
if( GlobalCurveXY >= 45 && GlobalCurveXY < 135 )
        {
        int buf = shX;
        shX = shY;
        shY = buf;
        shX = -shX;
        }
else if( GlobalCurveXY >= 135 && GlobalCurveXY < 225 )
        {
        shX = -shX;
        shY = -shY;
        }
else if( GlobalCurveXY >= 225 && GlobalCurveXY < 315 )
        {
        int buf = shX;
        shX = shY;
        shY = buf;
        shY = -shY;
        }
//
if( GlobalCurveXZ >= 45 && GlobalCurveXZ < 135 )
        {
        int buf = shX;
        shX = shZ;
        shZ = buf;
        }
else if( GlobalCurveXZ >= 135 && GlobalCurveXZ < 225 )
        {
        shX = -shX;
        shZ = -shZ;
        }
else if( GlobalCurveXZ >= 225 && GlobalCurveXZ < 315 )
        {
        int buf = shX;
        shX = shZ;
        shZ = buf;
        shX = -shX;
        }
//
if( GlobalCurveYZ >= 45 && GlobalCurveYZ < 135 )
        {
        int buf = shY;
        shY = shZ;
        shZ = buf;
        shY = -shY;
        }
else if( GlobalCurveYZ >= 135 && GlobalCurveYZ < 225 )
        {
        shY = -shY;
        shZ = -shZ;
        }
else if( GlobalCurveYZ >= 225 && GlobalCurveYZ < 315 )
        {
        int buf = shY;
        shY = shZ;
        shZ = buf;
        }
//
if (Key == VK_LEFT && shX >= 0 || Key == VK_RIGHT && shX < 0 )
        {
        DownGridValues(ABS(shX));
        Form2->StringGrid1->Col = 9;
        }
else if (Key == VK_LEFT && shX < 0 || Key == VK_RIGHT && shX >= 0 )
        {
        UpGridValues(ABS(shX));
        Form2->StringGrid1->Col = 9;
        }
else if (Key == VK_UP)
        {
        if( shY >= 0 )
                UpGridValues(shY);
        else
                DownGridValues(-shY);
        if (StringGridIndexRow < (Form2->StringGrid1->RowCount-1))
                Form2->StringGrid1->Row = StringGridIndexRow+1;
        }
else if (Key == VK_DOWN)
        {
        if( shY >= 0 )
                DownGridValues(shY);
        else
                UpGridValues(-shY);
        if (StringGridIndexRow > 1)
                Form2->StringGrid1->Row = StringGridIndexRow-1;
        }
}
//---------------------------------------------------------------------------











//---------------------------------------------------------------------------
void __fastcall TForm2::StringGrid1KeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if (Key == VK_CONTROL)          CTRL = false;
else if (Key == VK_SHIFT)       SHIFT = false;
if (CTRL) return;
if (Key == VK_LEFT||Key == VK_RIGHT||Key == VK_UP||Key == VK_DOWN)
        Canva(CANVAS);
}
//---------------------------------------------------------------------------










//---------------------------------------------------------------------------
void __fastcall TForm2::FormMouseWheelDown(TObject *Sender,
      TShiftState Shift, TPoint &MousePos, bool &Handled)
{
if(Form2->Select->Count)
        return;
NmB = "";
TPoint pmb( MousePos.x,MousePos.y );
SetCursorPos((Fill_Rect.Left + Fill_Rect.Right)/2 + Form2->Left,(Fill_Rect.Bottom + Fill_Rect.Top)/2 + Form2->Top);
GetCursorPos( &MousePos );
GlobalShiftX += (pmb.x - MousePos.x)/GlobalScaleFactor*2;
GlobalShiftY += (pmb.y - MousePos.y)/GlobalScaleFactor*2;
GlobalScaleFactor = GlobalScaleFactor/1.15;
Canva(CANVAS);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TForm2::FormMouseWheelUp(TObject *Sender,
      TShiftState Shift, TPoint &MousePos, bool &Handled)
{
if(Form2->Select->Count)
        return;
NmB = "";
TPoint pmb( MousePos.x,MousePos.y );
SetCursorPos((Fill_Rect.Left + Fill_Rect.Right)/2 + Form2->Left,(Fill_Rect.Bottom + Fill_Rect.Top)/2 + Form2->Top);
GetCursorPos( &MousePos );
GlobalShiftX += (pmb.x - MousePos.x)/GlobalScaleFactor*2;
GlobalShiftY += (pmb.y - MousePos.y)/GlobalScaleFactor*2;
GlobalScaleFactor = GlobalScaleFactor*1.15;
Canva(CANVAS);
}
//---------------------------------------------------------------------------










//---------------------------------------------------------------------------
void __fastcall TForm2::FormMouseDown(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
Form2->Shapes->Visible = 0;
mouseStartX = X;
mouseStartY = Y;
StartGCXZ = GlobalCurveXZ;
StartGCYZ = GlobalCurveYZ;
StartGCXY = GlobalCurveXY;
Form2->StringGrid1->Col = 0;
NmB = "";
bool f = false;
if (Form2->Select->Count && Form2->Draw->Enabled)
        {
        int dxflrct = Fill_Rect.Right - Fill_Rect.Left;
        int dxmsrct = X - Fill_Rect.Left;
        int dymsrct = Y - Fill_Rect.Top;
        int dxsvrct = SaveRect.Right - SaveRect.Left;
        int dysvrct = SaveRect.Bottom - SaveRect.Top;
        int max = dxflrct/dxsvrct;
        int cntx = dxmsrct/dxsvrct + 1;
        int cnty = dymsrct/dysvrct;
        int index = cnty*max + cntx;
        index--;
        if (index < Form2->Select->Count && index >= 0)
                {
                StringF = Form2->Select->Items->operator [](index);
                if (FIND(false))
                        Form2->Select->Clear();
                Form2->FootPrints->ItemIndex = Form2->FootPrints->Items->IndexOf(StringF);
                WhereElseIsThisPartUsed(&StringF, Form2->Used);
                }
        }
else    {
        float Xm;
        float Ym;
        float X1;
        float Y1;
        float X2;
        float Y2;
        int index;
        for (int e=0; LINES[e] < DEFAULT; e=e+9)
                {
                index = LINES[e];
                for (int u=e; (u-e)<5; u=u+2)
                        {
                        if (Length_Line(LINES[u+1],LINES[u+2],LINES[u+3],LINES[u+4]) > 5)
                                {
                                Xm = X;
                                Ym = Y;
                                X1 = LINES[u+1];
                                Y1 = LINES[u+2];
                                X2 = LINES[u+3];
                                Y2 = LINES[u+4];
                                float AN = Angle(X2,Y2,X1,Y1);
                                Rotate_Vertex(&X1,&Y1,-AN);
                                Rotate_Vertex(&X2,&Y2,-AN);
                                Rotate_Vertex(&Xm,&Ym,-AN);
                                if (ABS(Ym - Y2) < 5 && Xm > MIN(X1,X2) && Xm < MAX(X1,X2))
                                        {
                                        Form2->StringGrid1->Col = 9;
                                        Form2->StringGrid1->Row = index;
                                        StringGridIndexRow = index;
                                        Form2->StringGrid1->Refresh();
                                        f = true;
                                        break;
                                        }
                                }
                        }
                if (f) break;
                Xm = X;
                Ym = Y;
                X1 = LINES[e+1];
                Y1 = LINES[e+2];
                X2 = LINES[e+7];
                Y2 = LINES[e+8];
                float AN = Angle(X2,Y2,X1,Y1);
                Rotate_Vertex(&X1,&Y1,-AN);
                Rotate_Vertex(&X2,&Y2,-AN);
                Rotate_Vertex(&Xm,&Ym,-AN);
                if (ABS(Ym - Y2) < 5 && Xm > MIN(X1,X2) && Xm < MAX(X1,X2))
                        {
                        Form2->StringGrid1->Col = 9;
                        Form2->StringGrid1->Row = index;
                        StringGridIndexRow = index;
                        Form2->StringGrid1->Refresh();
                        }
                }
        }
if( f && Form2->PageControl1->TabIndex )
        Form2->StringGrid1->SetFocus();
else    Form2->vTop->SetFocus();
Canva(CANVAS);
}


//---------------------------------------------------------------------------



void __fastcall TForm2::CopyObject1Click(TObject *Sender)
{
bLibModified = true;
Form4->Visible = true;
Form4->Top = Form2->Top + Form2->StringGrid1->Height;
Form4->Left = Form2->Left;
Form4->FormStyle = fsStayOnTop;        
}



//---------------------------------------------------------------------------

void __fastcall TForm2::Copy1Click(TObject *Sender)
{
if( Form2->PageControl1->TabIndex == 1 )
        {
        bLibModified = true;
        int RowCount = Form2->StringGrid1->RowCount-1;
        Form2->StringGrid1->RowCount++;
        for (int t=RowCount; t>=Form2->StringGrid1->Row; t--)
                {
                for (int q=0; q<COL_COUNT; q++)
                        Form2->StringGrid1->Cells[q][t+1] = Form2->StringGrid1->Cells[q][t];
                }
        ShiftSizeRectsArrow(Form2->StringGrid1->Row,1);
        Form2->StringGrid1->Row++;
        StringGridIndexRow = Form2->StringGrid1->Row;
        Form2->StringGrid1->Refresh();
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm2::DeleteString1Click(TObject *Sender)
{
bLibModified = true;
for (int q=0; q<COL_COUNT; q++)
        Form2->StringGrid1->Cells[q][Form2->StringGrid1->Row] = "";
for (int q=Form2->StringGrid1->Row; q<(Form2->StringGrid1->RowCount-1); q++)
        for (int w=0; w<COL_COUNT; w++)
                Form2->StringGrid1->Cells[w][q] = Form2->StringGrid1->Cells[w][q+1];
Form2->StringGrid1->RowCount--;
ShiftSizeRectsArrow((Form2->StringGrid1->Row+1),-1);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::StringGrid1ContextPopup(TObject *Sender,
      TPoint &MousePos, bool &Handled)
{
//if (MousePos.x > Form2->StringGrid1->ColWidths[PACKAGES]+Form2->StringGrid1->ColWidths[SHAPE] )
//        {
        Form2->CopyObject1->Visible =   true;
        Form2->Copy1->Visible =         true;
        Form2->DeleteString1->Visible = true;
        Form2->SwapCells1->Visible =    true;
        Form2->Complex1->Visible =      true;
        Form2->InsertEmptyString1->Visible = true;
        Form2->BuildDXF1->Visible =     false;
        Form2->ShowLengthofSides1->Visible = false;
        Form2->Shapes->Visible = 0;
        Form2->PopupMenu1->Popup(MousePos.x+Form2->Left,MousePos.y+Form2->Top);
//        }
}
//---------------------------------------------------------------------------

void __fastcall TForm2::SwapCells1Click(TObject *Sender)
{
Form2->CheckBox1->Checked = true;
SwapRow = Form2->StringGrid1->Row;
SwapCol = Form2->StringGrid1->Col;
StringGrid1->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::BuildDXF1Click(TObject *Sender)
{
CANVAS_TO_FILE = true;
StringGridIndexRow = 0;
Canva(CANVAS);
Form1->Blocks->Items->Clear();
StringGridIndexRow = Form2->StringGrid1->Row;
Canva(CANVAS);
CANVAS_TO_FILE = false;
AnsiString N = Form2->StringGrid1->Cells[PACKAGES][Form2->StringGrid1->Row];
Form1->OutputBox->Items->Add("0");
Form1->OutputBox->Items->Add("SECTION");
Form1->OutputBox->Items->Add("2");
Form1->OutputBox->Items->Add("BLOCKS");
Form1->OutputBox->Items->Add("0");
Form1->OutputBox->Items->Add("BLOCK");
Form1->OutputBox->Items->Add("2");
Form1->OutputBox->Items->Add(N + "_top");
Form1->OutputBox->Items->Add("10");
Form1->OutputBox->Items->Add("0");
Form1->OutputBox->Items->Add("20");
Form1->OutputBox->Items->Add("0");
Form1->OutputBox->Items->Add("30");
Form1->OutputBox->Items->Add("0");
for (int t=0; t<Form1->Blocks->Items->Count; t++)
        Form1->OutputBox->Items->Add(Form1->Blocks->Items->operator [](t));
Form1->OutputBox->Items->Add("0");
Form1->OutputBox->Items->Add("ENDBLK");
Form1->OutputBox->Items->Add("0");
Form1->OutputBox->Items->Add("ENDSEC");
Form1->OutputBox->Items->Add("0");
Form1->OutputBox->Items->Add("SECTION");
Form1->OutputBox->Items->Add("2");
Form1->OutputBox->Items->Add("ENTITIES");
Form1->OutputBox->Items->Add("0");
Form1->OutputBox->Items->Add("INSERT");
Form1->OutputBox->Items->Add("2");
Form1->OutputBox->Items->Add(N + "_top");
Form1->OutputBox->Items->Add("8");
Form1->OutputBox->Items->Add(LT);
Form1->OutputBox->Items->Add("62");
Form1->OutputBox->Items->Add("20");
Form1->OutputBox->Items->Add("10");
Form1->OutputBox->Items->Add("0.0");
Form1->OutputBox->Items->Add("20");
Form1->OutputBox->Items->Add("0.0");
Form1->OutputBox->Items->Add("50");
Form1->OutputBox->Items->Add("0.0");
Form1->OutputBox->Items->Add("0");
Form1->OutputBox->Items->Add("ENDSEC");
Form1->OutputBox->Items->Add("0");
Form1->OutputBox->Items->Add("EOF");
AnsiString OUTPUTFILE = ExtractFilePath(Application->ExeName) + "DXF.dxf";
ofstream MODEL (OUTPUTFILE.c_str());
for (int k=0; k<Form1->OutputBox->Count; k++)
        MODEL << (Form1->OutputBox->Items->operator [](k)).c_str() << endl;
MODEL.close();
Application->ProcessMessages();
Sleep(500);
if ((UINT)ShellExecute  (NULL,
        "open",
        OUTPUTFILE.c_str(),
        NULL,
        ExtractFilePath(OUTPUTFILE).c_str() ,
        SW_SHOWNORMAL) <=32)
        {
        ShowMessage  ("  What program to open this file? There is no application associated with * .DXF files.");
        }
Form1->OutputBox->Items->Clear();
}
//---------------------------------------------------------------------------


void __fastcall TForm2::FormContextPopup(TObject *Sender, TPoint &MousePos,
      bool &Handled)
{
if (MousePos.x+Form2->Left > Form2->StringGrid1->Width)
        {
        Form2->CopyObject1->Visible =   false;
        Form2->Copy1->Visible =         false;
        Form2->DeleteString1->Visible = false;
        Form2->SwapCells1->Visible =    false;
        Form2->Complex1->Visible =      false;
        Form2->InsertEmptyString1->Visible = false;
        Form2->BuildDXF1->Visible =     true;
        Form2->ShowLengthofSides1->Visible = true;
        Form2->PopupMenu1->Popup(MousePos.x+Form2->Left,MousePos.y+Form2->Top);
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm2::ShowLengthofSides1Click(TObject *Sender)
{
if (Form2->ShowLengthofSides1->Checked)
        Form2->ShowLengthofSides1->Checked = false;
else    Form2->ShowLengthofSides1->Checked = true;
StringGridIndexRow = 0;
Canva(CANVAS);
StringGridIndexRow = Form2->StringGrid1->Row;
Canva(CANVAS);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Complex1Click(TObject *Sender)
{
if (Form2->Complex1->Checked)
        Form2->Complex1->Checked = false;
else    Form2->Complex1->Checked = true;
}
//---------------------------------------------------------------------------




void __fastcall TForm2::FormMouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
if( mouseStartX && mouseStartY )
if( ABS(X-mouseStartX) > 5 || ABS(Y-mouseStartY) > 5 )
        {
        Form2->StringGrid1->Col = Form2->StringGrid1->ColCount-1;
        /* */
        if( bReplace_XZ_to_XY )
                {
                GlobalCurveXY = StartGCXY + (X-mouseStartX)/5;
                if( GlobalCurveXY > 360 )
                        GlobalCurveXY -= 360;
                if( GlobalCurveXY < 0 )
                        GlobalCurveXY += 360;
                GlobalCurveYZ = StartGCYZ + (Y-mouseStartY)/5;
                if( GlobalCurveYZ > 360 )
                        GlobalCurveYZ -= 360;
                if( GlobalCurveYZ < 0 )
                        GlobalCurveYZ += 360;
                }
        else if( bReplace_YZ_to_XY )
                {
                GlobalCurveXY = StartGCXY - (Y-mouseStartY)/5;
                if( GlobalCurveXY > 360 )
                        GlobalCurveXY -= 360;
                if( GlobalCurveXY < 0 )
                        GlobalCurveXY += 360;
                GlobalCurveXZ = StartGCXZ + (X-mouseStartX)/5;
                if( GlobalCurveXZ > 360 )
                        GlobalCurveXZ -= 360;
                if( GlobalCurveXZ < 0 )
                        GlobalCurveXZ += 360;
                }
        else    {
                GlobalCurveXZ = StartGCXZ + (X-mouseStartX)/5;
                if( GlobalCurveXZ > 360 )
                        GlobalCurveXZ -= 360;
                if( GlobalCurveXZ < 0 )
                        GlobalCurveXZ += 360;
                GlobalCurveYZ = StartGCYZ + (Y-mouseStartY)/5;
                if( GlobalCurveYZ > 360 )
                        GlobalCurveYZ -= 360;
                if( GlobalCurveYZ < 0 )
                        GlobalCurveYZ += 360;
                }
        Canva(CANVAS);
        }

}


//---------------------------------------------------------------------------
void ArrowCorrect(void)
{
if( (ABS(GlobalCurveYZ-90))%180 < 45 )
        bReplace_XZ_to_XY = 1;
else
        bReplace_XZ_to_XY = 0;
if( (ABS(GlobalCurveXZ-90))%180 < 45 )
        bReplace_YZ_to_XY = 1;
else
        bReplace_YZ_to_XY = 0;
mouseStartX = 0;
mouseStartY = 0;
}


//---------------------------------------------------------------------------

void __fastcall TForm2::FormMouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
ArrowCorrect();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FormResize(TObject *Sender)
{
Form2->myResize(1);
//Canva( CANVAS );
}
//---------------------------------------------------------------------------

void __fastcall TForm2::vTopClick(TObject *Sender)
{
GlobalCurveXY = 0;
GlobalCurveXZ = 0;
GlobalCurveYZ = 0;
NmB = "";
Canva(CANVAS);
ArrowCorrect();
}
//---------------------------------------------------------------------------


void __fastcall TForm2::Button2Click(TObject *Sender)
{
GlobalCurveXY = 0;
GlobalCurveXZ = 0;
GlobalCurveYZ = 270;
NmB = "";
Canva(CANVAS);
ArrowCorrect();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button3Click(TObject *Sender)
{
GlobalCurveXY = 0;
GlobalCurveXZ = 0;
GlobalCurveYZ = 90;
NmB = "";
Canva(CANVAS);
ArrowCorrect();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button4Click(TObject *Sender)
{
GlobalCurveXY = 0;
GlobalCurveXZ = 90;
GlobalCurveYZ = 0;
NmB = "";
Canva(CANVAS);
ArrowCorrect();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button5Click(TObject *Sender)
{
GlobalCurveXY = 0;
GlobalCurveXZ = 270;
GlobalCurveYZ = 0;
NmB = "";
Canva(CANVAS);
ArrowCorrect();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button8Click(TObject *Sender)
{
GlobalCurveXY = 315;
GlobalCurveXZ = 355;
GlobalCurveYZ = 335;
NmB = "";
Canva(CANVAS);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button7Click(TObject *Sender)
{
GlobalCurveXY = 15;
GlobalCurveXZ = 355;
GlobalCurveYZ = 280;
NmB = "";
Canva(CANVAS);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button6Click(TObject *Sender)
{
GlobalCurveXY = 45;
GlobalCurveXZ = 355;
GlobalCurveYZ = 285;
NmB = "";
Canva(CANVAS);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button9Click(TObject *Sender)
{
GlobalCurveXY = 345;
GlobalCurveXZ = 355;
GlobalCurveYZ = 285;
NmB = "";
Canva(CANVAS);
}
//---------------------------------------------------------------------------


void __fastcall TForm2::InsertEmptyString1Click(TObject *Sender)
{
if( Form2->PageControl1->TabIndex == 1 )
        {
        int RowCount = Form2->StringGrid1->RowCount-1;
        Form2->StringGrid1->RowCount++;
        for (int t=RowCount; t>=Form2->StringGrid1->Row; t--)
                {
                for (int q=0; q<COL_COUNT; q++)
                        Form2->StringGrid1->Cells[q][t+1] = Form2->StringGrid1->Cells[q][t];
                }
        for (int q=1; q<COL_COUNT; q++)
                Form2->StringGrid1->Cells[q][Form2->StringGrid1->Row] = "";
        ShiftSizeRectsArrow(Form2->StringGrid1->Row,1);
        StringGridIndexRow = Form2->StringGrid1->Row;
        Form2->StringGrid1->Refresh();
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm2::SvLibClick(TObject *Sender)
{
if( Form2->Visible )
        {
        Form2->SvLib->Caption = "Use local library";
        if( Form2->DrawGroupList->ItemIndex != AllinThisProject )
                {
                Form2->DrawGroupList->ItemIndex = AllinThisProject;
                CanvasAll(AllinThisProject);
                }
        S_Library(!SvLib->Checked,!SvLib->Checked);
        R_Library(SvLib->Checked);
        GetRects();
        CanvasAll(AllObj);
        CanvasAll(Form2->DrawGroupList->ItemIndex);
        }
}

//---------------------------------------------------------------------------
void __fastcall TForm2::ShapesMouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
int ii = Form2->Shapes->ItemIndex;
AnsiString str = Form2->Shapes->Items->operator [](ii);
if( str.Length() )
        {
        Form2->StringGrid1->Cells[Form2->StringGrid1->Col][StringGridIndexRow] = str;
        Form2->StringGrid1->Refresh();
        Canva(CANVAS);
        Form2->Shapes->Visible = 0;
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm2::GridValuesChange(TObject *Sender)
{
Canva(CANVAS);        
}
//---------------------------------------------------------------------------




void __fastcall TForm2::FootPrintsClick(TObject *Sender)
{
Form2->Select->Clear();
int i = Form2->FootPrints->ItemIndex;
if(i>=0){
        AnsiString s = Form2->FootPrints->Items->operator [](i);
        i = Form2->StringGrid1->Cols[PACKAGES]->IndexOf(s);
        if(i>=0){
                Form2->StringGrid1->Row = i;
                StringGridIndexRow = i;
                Canva(CANVAS);
                }
        WhereElseIsThisPartUsed(&s,Form2->Used);
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm2::UsedClick(TObject *Sender)
{
Form2->Select->Clear();
int i = Form2->Used->ItemIndex;
if(i>=0){
        AnsiString s = Form2->Used->Items->operator [](i);
        i = Form2->StringGrid1->Cols[PACKAGES]->IndexOf(s);
        if(i>=0){
                Form2->StringGrid1->Row = i;
                StringGridIndexRow = i;
                Canva(CANVAS);
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm2::PageControl1Changing(TObject *Sender,
      bool &AllowChange)
{
if( Form2->PageControl1->TabIndex == 0 )
        Form2->PageControl1->Width = 520;
else
        Form2->PageControl1->Width = 390;
Form2->myResize(1);
if( StringGridIndexRow == Form2->StringGrid1->RowCount-1 || StringGridIndexRow == -1 )
        {
        Form2->Refresh();
        //Form2->Canvas->CopyRect( Fill_Rect, Form2->pDC->Canvas, Fill_Rect );
        CanvasAll(Form2->DrawGroupList->ItemIndex);
        }
else
        Canva(CANVAS);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::StringGrid1SetEditText(TObject *Sender, int ACol,
      int ARow, const AnsiString Value)
{
bLibModified = true;
Form2->SvLib->Enabled = false;
if( Form2->StringGrid1->Col <= SHAPE )
        {
        Form2->Shapes->Left = Form2->StringGrid1->ColWidths[SHAPE]*ACol + Form2->StringGrid1->ColWidths[PACKAGES] + 4;
        TRect r = Form2->StringGrid1->CellRect(ACol,ARow);
        Form2->Shapes->Width = Form2->StringGrid1->ColWidths[SHAPE]*3;
        Form2->Shapes->Height = 250;
        Form2->Shapes->Top = MIN(r.top,Form2->PageControl1->ClientHeight-Form2->Shapes->Height-30);
        if( Form2->Shapes->Items->Count )
                {
                AnsiString s;
                AnsiString gS = Form2->StringGrid1->Cells[ACol][ARow];
                if( StringF.SubString(1,StringF.Length()) != gS.SubString(1,gS.Length()))
                        {
                        int ItemIndex = -1;
                        do{     ItemIndex++;
                                if( ItemIndex >= Form2->Shapes->Items->Count )
                                        break;
                                s = Form2->Shapes->Items->operator [](ItemIndex);
                          }while(s.SubString(1,gS.Length()).UpperCase() != gS.SubString(1,gS.Length()).UpperCase() );
                        if(ItemIndex < Form2->Shapes->Items->Count)
                                {
                                if(Form2->Shapes->ItemIndex != ItemIndex)
                                        Form2->Shapes->Visible = true;
                                Form2->Shapes->ItemIndex = ItemIndex;
                                }
                        else    Form2->Shapes->Visible = false;
                        }
                }
        }
else    Form2->Shapes->Visible = 0;
}
//---------------------------------------------------------------------------


void __fastcall TForm2::DrawClick(TObject *Sender)
{
Form2->Select->Clear();
CanvasAll(Form2->DrawGroupList->ItemIndex);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::vTopKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if( Form2->PageControl1->TabIndex == 1 )
        Form2->StringGrid1->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button2KeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if( Form2->PageControl1->TabIndex == 1 )
        Form2->StringGrid1->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button3KeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if( Form2->PageControl1->TabIndex == 1 )
        Form2->StringGrid1->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button4KeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if( Form2->PageControl1->TabIndex == 1 )
        Form2->StringGrid1->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button5KeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if( Form2->PageControl1->TabIndex == 1 )
        Form2->StringGrid1->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::SelAllClick(TObject *Sender)
{
Form2->Used->SelectAll();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::DelSelClick(TObject *Sender)
{
Form2->Used->DeleteSelected();
}
//---------------------------------------------------------------------------



void __fastcall TForm2::ShapesKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if( Key == VK_RETURN )
        {
        int ii = Form2->Shapes->ItemIndex;
        AnsiString str = Form2->Shapes->Items->operator [](ii);
        if( str.Length() )
                {
                Form2->StringGrid1->Cells[Form2->StringGrid1->Col][StringGridIndexRow] = str;
                Form2->StringGrid1->Refresh();
                Canva(CANVAS);
                Form2->Shapes->Visible = 0;
                }
        }        
}
//---------------------------------------------------------------------------

