//---------------------------------------------------------------------------


#pragma hdrstop

#include "InsertBlock.h"
#include "To_DXF.h"
#include "Options.h"
#include "DXF_library.h"
#include "math.h"
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#pragma package(smart_init)
static Table_struct TJumps[NUMBER_OF_TJumps];
static float centroid__X;
static float centroid__Y;
static int fcs;
float W_Line;
float X__1;
float Y__1;
float X__2;
float Y__2;
float First_X;
float First_Y;
int type_L;
int Units_MM;
int U = 0;
int SILK_TOP (int N_STR, int ROT, Table_struct T, int CI, myRect * SELRECT, bool _3d=0);
int SILK_BOT (int N_STR, int ROT, Table_struct T, int CI, myRect * SELRECT, bool _3d=0);
void Rotate3d ( float *_1=0,
                float *_2=0,
                float *_3=0,
                float *_4=0,
                float *_5=0,
                float *_6=0,
                float *_7=0,
                float *_8=0,
                float *_9=0,
                float *_10=0,
                float *_11=0,
                float *_12=0);
//---------------------------------------------------------------------------




void Rotate3d ( float *_1,
                float *_2,
                float *_3,
                float *_4,
                float *_5,
                float *_6,
                float *_7,
                float *_8,
                float *_9,
                float *_10,
                float *_11,
                float *_12)
        {
        // ������������� ���� ��������
        // �� ������������
        return;
        /*int an = 1;
        if (_1 && _2)   Rotate_Vertex(_1,_2,an);
        if (_4 && _5)   Rotate_Vertex(_4,_5,an);
        if (_7 && _8)   Rotate_Vertex(_7,_8,an);
        if (_10 && _11) Rotate_Vertex(_10,_11,an);
        //
        if (_1 && _3)   Rotate_Vertex(_1,_3,an);
        if (_4 && _6)   Rotate_Vertex(_4,_6,an);
        if (_7 && _9)   Rotate_Vertex(_7,_9,an);
        if (_10 && _12) Rotate_Vertex(_10,_12,an);
        //
        if (_2 && _3)   Rotate_Vertex(_2,_3,an);
        if (_5 && _6)   Rotate_Vertex(_5,_6,an);
        if (_8 && _9)   Rotate_Vertex(_8,_9,an);
        if (_11 && _12) Rotate_Vertex(_11,_12,an);   */
        }




//---------------------------------------------------------------------------
int InsertBlock (int N_STR, int ROT, bool SIDE, myRect * SELRECT, int HeadIndex, int BranchIndex, int StartIndex, int EndIndex, bool _3d)
{
if (!FACES || !LINES || HeadIndex == RESET)
        {
        fcs = 0;
        FACES[fcs] = DEFAULT + 1;
        for (int t=0; t<NUMBER_OF_TJumps; t++)
                TJumps[t].ini();
        return JUMP_NOT_FOUND;
        }
// selrect
(*SELRECT).Left         /=_106;
(*SELRECT).Right        /=_106;
(*SELRECT).Top          /=_106;
(*SELRECT).Bottom       /=_106;
(*SELRECT)._Low         /=_106;
(*SELRECT)._High        /=_106;
AnsiString A,B,U,NameBlk,HNameBlk,Rstr,LAYER__3D;
NameBlk = Form2->StringGrid1->Cells[PACKAGES][BranchIndex];
HNameBlk = Form2->StringGrid1->Cells[PACKAGES][HeadIndex];
Rstr =    Form2->StringGrid1->Cells[PACKAGES][BranchIndex];
if (SIDE)
        {
        HNameBlk += "_bot";
        LAYER__3D = "3d_bottom";
        }
else    {
        HNameBlk += "_top";
        LAYER__3D = "3d_top";
        }
Form1->NamesOfBlocks->Items->Add(HNameBlk);
Form1->NamesOfBlocks->Items->Add(CLR);
long i;
Table_struct TValues;
TValues.ini();
float DX,DY;
if (N_STR > 0 && TJumps[0].Shape == 0)
        for (int kw=(N_STR+1); kw<Form1->File->Count; kw++)
                {
                A = Form1->File->Items->operator [](kw);
                if (A.SubString(1,6) == "units:" )
                        {
                        i = prob(A,1);
                        U = A.UpperCase().SubString(i,2);
                        }
                else if (A.SubString(1,9) == "centroid:" )
                        {
                        i = prob(A,2);
                        centroid__X =     ex_float_NM(A,&i,&U)/_106;
                        centroid__Y =     ex_float_NM(A,&i,&U)/_106;
                        //int centroid__ANG =   ex_float_NM(A,&i,&NO_UNITS);
                        //ROT += centroid__ANG;
                        //if( ROT >= 360 )
                        //        ROT -= 360;
                        break;
                        }
                }
else if (TJumps[0].Shape == 0)
        {
        centroid__X = 0;
        centroid__Y = 0;
        }
if (TJumps[0].Shape)
        {
        if (SizeRects[StartIndex].Right-SizeRects[StartIndex].Left > BY_ZERO)
                {
                if (ABS(TJumps[0].SizeX) > BY_ZERO)
                        TJumps[0].ScaleX = TJumps[0].SizeX*_106/(SizeRects[StartIndex].Right - SizeRects[StartIndex].Left);
                }
        if (SizeRects[StartIndex].Top-SizeRects[StartIndex].Bottom > BY_ZERO)
                {
                if (ABS(TJumps[0].SizeY) > BY_ZERO)
                        TJumps[0].ScaleY = TJumps[0].SizeY*_106/(SizeRects[StartIndex].Top - SizeRects[StartIndex].Bottom);
                }
        if (SizeRects[StartIndex]._High-SizeRects[StartIndex]._Low > BY_ZERO)
                {
                if (ABS(TJumps[0].SizeZ) > BY_ZERO)
                        TJumps[0].ScaleZ = TJumps[0].SizeZ*_106/(SizeRects[StartIndex]._High - SizeRects[StartIndex]._Low);
                }
        }
int Count = 1;
if (Form3)
        Count = StrToInt(Form3->ComboBox1->Items->operator [](Form3->ComboBox1->ItemIndex));
bool INCREMENT_OBJECT = true;
if (HeadIndex < StartIndex || HeadIndex > EndIndex)
        INCREMENT_OBJECT = false;
int Object = HeadIndex;
for (int n_str=BranchIndex; n_str<=EndIndex; n_str++)
        {
        if( MARKS )
        if( MARKS[n_str] == 0 )
                {
                // mark string
                MARKS[n_str] = 2;
                }
        B = Form2->StringGrid1->Cells[SHAPE][n_str];
        AnsiString BP = Form2->StringGrid1->Cells[PACKAGES][n_str];
        if (B.SubString(1,B.Length()) == BP.SubString(1,BP.Length()) )
                {
                ShowMessage(" EN: FootPrint name and Shape name must be different!\n RU: ��� ��������� � ����� �� ����� ���� �����������!");
                Form2->StringGrid1->Cells[SHAPE][n_str] = "";
                B = "";
                }
        int bL = B.Length();
        if (INCREMENT_OBJECT)
                Object = n_str;
        if      (B.LowerCase().SubString(1,bL) == "oval")  TValues.Shape = SH__OVAL;
        else if (B.LowerCase().SubString(1,bL) == "rect" ) TValues.Shape = SH__RECT;
        else if (B.LowerCase().SubString(1,bL) == "silk" ) TValues.Shape = SH__SILK;
        else if (B.LowerCase().SubString(1,bL) == "arc" )  TValues.Shape = SH__ARC;
        else if (B.LowerCase().SubString(1,bL) == "pin" )  TValues.Shape = SH__PIN;
        else if (B.LowerCase().SubString(1,bL) == "sector" ) TValues.Shape = SH__SECTOR;
        else if (B.LowerCase().SubString(1,bL) == "triangle" )TValues.Shape = SH__TRIANGLE;
        else if (B.LowerCase().SubString(1,bL) == "spiral" )   TValues.Shape = SH__SPIRAL;
        else    {
                TValues.Shape = SH__NONE;
                if (B.Length())
                        {
                        (*SELRECT).Left         *=_106;
                        (*SELRECT).Right        *=_106;
                        (*SELRECT).Top          *=_106;
                        (*SELRECT).Bottom       *=_106;
                        (*SELRECT)._Low         *=_106;
                        (*SELRECT)._High        *=_106;
                        for (int u=NUMBER_OF_TJumps-1; u>0; u--)
                                TJumps[u] = TJumps[u-1];
                        TJumps[0].ini();
                        TJumps[0].Shape = 1;
                        for (long col=SIZE_X; col<COL_COUNT; col++)
                                {
                                B = Form2->StringGrid1->Cells[col][n_str];
                                i=1;
                                switch (col)
                                        {
                                        case SIZE_X: TJumps[0].SizeX =    ex_float(Str_Float_Format(B),&i); break;
                                        case SIZE_Y: TJumps[0].SizeY =    ex_float(Str_Float_Format(B),&i); break;
                                        case SIZE_Z: TJumps[0].SizeZ =    ex_float(Str_Float_Format(B),&i); break;
                                        case ANGLE_XY: TJumps[0].RotateXY = ex_float(Str_Float_Format(B),&i); break;
                                        case ANGLE_YZ: TJumps[0].RotateYZ = ex_float(Str_Float_Format(B),&i); break;
                                        case ANGLE_XZ: TJumps[0].RotateXZ = ex_float(Str_Float_Format(B),&i); break;
                                        case SHIFT_X: TJumps[0].ShiftX =  ex_float(Str_Float_Format(B),&i); break;
                                        case SHIFT_Y: TJumps[0].ShiftY =  ex_float(Str_Float_Format(B),&i); break;
                                        case SHIFT_Z: TJumps[0].ShiftZ =  ex_float(Str_Float_Format(B),&i); break;
                                        }
                                }
                        FACES[fcs] = DEFAULT + 1;
                        return n_str;
                        }
                }
        for (long col=SIZE_X; col<COL_COUNT; col++)
                {
                B = Form2->StringGrid1->Cells[col][n_str];
                i=1;
                switch (col)
                        {
                        case SIZE_X: TValues.SizeX =    ex_float(Str_Float_Format(B),&i); break;
                        case SIZE_Y: TValues.SizeY =    ex_float(Str_Float_Format(B),&i); break;
                        case SIZE_Z: TValues.SizeZ =    ex_float(Str_Float_Format(B),&i); break;
                        case ANGLE_XY: TValues.RotateXY = ex_float(Str_Float_Format(B),&i); break;
                        case ANGLE_YZ: TValues.RotateYZ = ex_float(Str_Float_Format(B),&i); break;
                        case ANGLE_XZ: TValues.RotateXZ = ex_float(Str_Float_Format(B),&i); break;
                        case SHIFT_X: TValues.ShiftX =  ex_float(Str_Float_Format(B),&i); break;
                        case SHIFT_Y: TValues.ShiftY =  ex_float(Str_Float_Format(B),&i); break;
                        case SHIFT_Z: TValues.ShiftZ =  ex_float(Str_Float_Format(B),&i); break;
                        }
                }
        DX = TValues.SizeX - TValues.SizeY;
        if (DX<0) DX = 0;
        DY = TValues.SizeY - TValues.SizeX;
        if (DY<0) DY = 0;
        // sector & triangle
        if (TValues.Shape == SH__SECTOR || TValues.Shape == SH__TRIANGLE)
                {
                float currX,currY,currZ,currXnext,currYnext,currZnext,origX,origY,origZ;
                float _currX,_currY,_currZ,_currXnext,_currYnext,_currZnext,_origX,_origY,_origZ;
                if (TValues.Shape == SH__TRIANGLE)
                        {
                        currX = 0;
                        currY = TValues.SizeY;
                        currZ = 0;
                        currXnext = TValues.SizeX;
                        currYnext = 0;
                        currZnext = 0;
                        origX = 0;
                        origY = 0;
                        origZ = 0;
                        _currX = 0;
                        _currY = TValues.SizeY;
                        _currZ = TValues.SizeZ;
                        _currXnext = TValues.SizeX;
                        _currYnext = 0;
                        _currZnext = TValues.SizeZ;
                        _origX = 0;
                        _origY = 0;
                        _origZ = TValues.SizeZ;
                        }
                else    {
                        currX = TValues.SizeX/2.0;
                        currY = 0;
                        currZ = 0;
                        currXnext = -TValues.SizeX/2.0;
                        currYnext = 0;
                        currZnext = 0;
                        origX = 0;
                        origY = TValues.SizeY;
                        origZ = 0;
                        _currX = TValues.SizeX/2.0;
                        _currY = 0;
                        _currZ = TValues.SizeZ;
                        _currXnext = -TValues.SizeX/2.0;
                        _currYnext = 0;
                        _currZnext = TValues.SizeZ;
                        _origX = 0;
                        _origY = TValues.SizeY;
                        _origZ = TValues.SizeZ;
                        }
                Rotate_Vertex(&currX,&currZ,-TValues.RotateXZ);
                Rotate_Vertex(&currXnext,&currZnext,-TValues.RotateXZ);
                Rotate_Vertex(&origX,&origZ,-TValues.RotateXZ);
                Rotate_Vertex(&currY,&currZ,-TValues.RotateYZ);
                Rotate_Vertex(&currYnext,&currZnext,-TValues.RotateYZ);
                Rotate_Vertex(&origY,&origZ,-TValues.RotateYZ);
                Rotate_Vertex(&currX,&currY,TValues.RotateXY);
                Rotate_Vertex(&currXnext,&currYnext,TValues.RotateXY);
                Rotate_Vertex(&origX,&origY,TValues.RotateXY);
                Rotate_Vertex(&_currX,&_currZ,-TValues.RotateXZ);
                Rotate_Vertex(&_currXnext,&_currZnext,-TValues.RotateXZ);
                Rotate_Vertex(&_origX,&_origZ,-TValues.RotateXZ);
                Rotate_Vertex(&_currY,&_currZ,-TValues.RotateYZ);
                Rotate_Vertex(&_currYnext,&_currZnext,-TValues.RotateYZ);
                Rotate_Vertex(&_origY,&_origZ,-TValues.RotateYZ);
                Rotate_Vertex(&_currX,&_currY,TValues.RotateXY);
                Rotate_Vertex(&_currXnext,&_currYnext,TValues.RotateXY);
                Rotate_Vertex(&_origX,&_origY,TValues.RotateXY);
                currX +=        TValues.ShiftX;
                currXnext +=    TValues.ShiftX;
                origX     +=    TValues.ShiftX;
                currY +=        TValues.ShiftY;
                currYnext +=    TValues.ShiftY;
                origY     +=    TValues.ShiftY;
                currZ +=        TValues.ShiftZ;
                currZnext +=    TValues.ShiftZ;
                origZ     +=    TValues.ShiftZ;
                _currX +=        TValues.ShiftX;
                _currXnext +=    TValues.ShiftX;
                _origX     +=    TValues.ShiftX;
                _currY +=        TValues.ShiftY;
                _currYnext +=    TValues.ShiftY;
                _origY     +=    TValues.ShiftY;
                _currZ +=        TValues.ShiftZ;
                _currZnext +=    TValues.ShiftZ;
                _origZ     +=    TValues.ShiftZ;
                for (int j=0; TJumps[j].Shape; j++)
                        {
                        if (ABS(TJumps[j].ScaleX) > BY_ZERO)
                                {
                                currX = currX*TJumps[j].ScaleX;
                                currXnext = currXnext*TJumps[j].ScaleX;
                                origX = origX*TJumps[j].ScaleX;
                                _currX = _currX*TJumps[j].ScaleX;
                                _currXnext = _currXnext*TJumps[j].ScaleX;
                                _origX = _origX*TJumps[j].ScaleX;
                                }
                        if (ABS(TJumps[j].ScaleY) > BY_ZERO)
                                {
                                currY = currY*TJumps[j].ScaleY;
                                currYnext = currYnext*TJumps[j].ScaleY;
                                origY = origY*TJumps[j].ScaleY;
                                _currY = _currY*TJumps[j].ScaleY;
                                _currYnext = _currYnext*TJumps[j].ScaleY;
                                _origY = _origY*TJumps[j].ScaleY;
                                }
                        if (ABS(TJumps[j].ScaleZ) > BY_ZERO)
                                {
                                currZ = currZ*TJumps[j].ScaleZ;
                                currZnext = currZnext*TJumps[j].ScaleZ;
                                origZ = origZ*TJumps[j].ScaleZ;
                                _currZ = _currZ*TJumps[j].ScaleZ;
                                _currZnext = _currZnext*TJumps[j].ScaleZ;
                                _origZ = _origZ*TJumps[j].ScaleZ;
                                }
                        Rotate_Vertex(&currX,&currZ,-TJumps[j].RotateXZ);
                        Rotate_Vertex(&currXnext,&currZnext,-TJumps[j].RotateXZ);
                        Rotate_Vertex(&origX,&origZ,-TJumps[j].RotateXZ);
                        Rotate_Vertex(&currY,&currZ,-TJumps[j].RotateYZ);
                        Rotate_Vertex(&currYnext,&currZnext,-TJumps[j].RotateYZ);
                        Rotate_Vertex(&origY,&origZ,-TJumps[j].RotateYZ);
                        Rotate_Vertex(&currX,&currY,TJumps[j].RotateXY);
                        Rotate_Vertex(&currXnext,&currYnext,TJumps[j].RotateXY);
                        Rotate_Vertex(&origX,&origY,TJumps[j].RotateXY);
                        Rotate_Vertex(&_currX,&_currZ,-TJumps[j].RotateXZ);
                        Rotate_Vertex(&_currXnext,&_currZnext,-TJumps[j].RotateXZ);
                        Rotate_Vertex(&_origX,&_origZ,-TJumps[j].RotateXZ);
                        Rotate_Vertex(&_currY,&_currZ,-TJumps[j].RotateYZ);
                        Rotate_Vertex(&_currYnext,&_currZnext,-TJumps[j].RotateYZ);
                        Rotate_Vertex(&_origY,&_origZ,-TJumps[j].RotateYZ);
                        Rotate_Vertex(&_currX,&_currY,TJumps[j].RotateXY);
                        Rotate_Vertex(&_currXnext,&_currYnext,TJumps[j].RotateXY);
                        Rotate_Vertex(&_origX,&_origY,TJumps[j].RotateXY);
                        currX +=        TJumps[j].ShiftX;
                        currXnext +=    TJumps[j].ShiftX;
                        origX     +=    TJumps[j].ShiftX;
                        currY +=        TJumps[j].ShiftY;
                        currYnext +=    TJumps[j].ShiftY;
                        origY     +=    TJumps[j].ShiftY;
                        currZ +=        TJumps[j].ShiftZ;
                        currZnext +=    TJumps[j].ShiftZ;
                        origZ     +=    TJumps[j].ShiftZ;
                        _currX +=        TJumps[j].ShiftX;
                        _currXnext +=    TJumps[j].ShiftX;
                        _origX     +=    TJumps[j].ShiftX;
                        _currY +=        TJumps[j].ShiftY;
                        _currYnext +=    TJumps[j].ShiftY;
                        _origY     +=    TJumps[j].ShiftY;
                        _currZ +=        TJumps[j].ShiftZ;
                        _currZnext +=    TJumps[j].ShiftZ;
                        _origZ     +=    TJumps[j].ShiftZ;
                        }
                currX +=        centroid__X;
                currXnext +=    centroid__X;
                origX +=        centroid__X;
                _currX +=       centroid__X;
                _currXnext +=   centroid__X;
                _origX +=       centroid__X;
                currY +=        centroid__Y;
                currYnext +=    centroid__Y;
                origY +=        centroid__Y;
                _currY +=       centroid__Y;
                _currYnext +=   centroid__Y;
                _origY +=       centroid__Y;
                if (!SIDE)
                        {
                        currZ +=        BoardThick;
                        currZnext +=    BoardThick;
                        origZ     +=    BoardThick;
                        _currZ +=        BoardThick;
                        _currZnext +=    BoardThick;
                        _origZ     +=    BoardThick;
                        }
                else    {
                        Rotate_Vertex(&currX,&currZ,180);
                        Rotate_Vertex(&currXnext,&currZnext,180);
                        Rotate_Vertex(&origX,&origZ,180);
                        Rotate_Vertex(&_currX,&_currZ,180);
                        Rotate_Vertex(&_currXnext,&_currZnext,180);
                        Rotate_Vertex(&_origX,&_origZ,180);
                        }
                if (_3d)
                        {
                        Rotate3d(&currX,&currY,&currZ,&currXnext,&currYnext,&currZnext,&origX,&origY,&origZ);
                        Rotate3d(&_currX,&_currY,&_currZ,&_currXnext,&_currYnext,&_currZnext,&_origX,&_origY,&_origZ);
                        }
                if (Form3->RadioButton4->Checked && CANVAS_TO_FILE)
                        {
                        W_LINE_BLK(currX,currY,currZ,currXnext,currYnext,currZnext, CLR, LAYER__3D);
                        W_LINE_BLK(origX,origY,origZ,currX,currY,currZ, CLR, LAYER__3D);
                        W_LINE_BLK(origX,origY,origZ,currXnext,currYnext,currZnext, CLR, LAYER__3D);
                        W_LINE_BLK(_currX,_currY,_currZ,_currXnext,_currYnext,_currZnext, CLR, LAYER__3D);
                        W_LINE_BLK(_origX,_origY,_origZ,_currX,_currY,_currZ, CLR, LAYER__3D);
                        W_LINE_BLK(_origX,_origY,_origZ,_currXnext,_currYnext,_currZnext, CLR, LAYER__3D);
                        W_LINE_BLK(currX,currY,currZ,_currX,_currY,_currZ, CLR, LAYER__3D);
                        W_LINE_BLK(origX,origY,origZ,_origX,_origY,_origZ, CLR, LAYER__3D);
                        W_LINE_BLK(currXnext,currYnext,currZnext,_currXnext,_currYnext,_currZnext, CLR, LAYER__3D);
                        }
                else if (CANVAS_TO_FILE)
                        {
                        W_SOLID_BLK(    currX,currY,currZ,origX,origY,origZ,currXnext,currYnext,currZnext,origX,origY,origZ, CLR, LAYER__3D);
                        W_SOLID_BLK(    _currX,_currY,_currZ,_origX,_origY,_origZ,_currXnext,_currYnext,_currZnext,_origX,_origY,_origZ, CLR, LAYER__3D);
                        W_SOLID_BLK(    currX,currY,currZ,origX,origY,origZ,_currX,_currY,_currZ,_origX,_origY,_origZ, CLR, LAYER__3D);
                        W_SOLID_BLK(    currXnext,currYnext,currZnext,origX,origY,origZ,_currXnext,_currYnext,_currZnext,_origX,_origY,_origZ, CLR, LAYER__3D);
                        W_SOLID_BLK(    currX,currY,currZ,currXnext,currYnext,currZnext,_currX,_currY,_currZ,_currXnext,_currYnext,_currZnext, CLR, LAYER__3D);
                        }
                else    {
                        FACES[fcs] = Object;
                        FACES[fcs+1] = currX;
                        FACES[fcs+2] = currY;
                        FACES[fcs+3] = currZ;
                        FACES[fcs+4] = origX;
                        FACES[fcs+5] = origY;
                        FACES[fcs+6] = origZ;
                        FACES[fcs+7] = origX;
                        FACES[fcs+8] = origY;
                        FACES[fcs+9] = origZ;
                        FACES[fcs+10] = currXnext;
                        FACES[fcs+11] = currYnext;
                        FACES[fcs+12] = currZnext;
                        fcs = fcs + 13;
                        FACES[fcs] = Object;
                        FACES[fcs+1] = _currX;
                        FACES[fcs+2] = _currY;
                        FACES[fcs+3] = _currZ;
                        FACES[fcs+4] = _origX;
                        FACES[fcs+5] = _origY;
                        FACES[fcs+6] = _origZ;
                        FACES[fcs+7] = _origX;
                        FACES[fcs+8] = _origY;
                        FACES[fcs+9] = _origZ;
                        FACES[fcs+10] = _currXnext;
                        FACES[fcs+11] = _currYnext;
                        FACES[fcs+12] = _currZnext;
                        fcs = fcs + 13;
                        FACES[fcs] = Object;
                        FACES[fcs+1] = currX;
                        FACES[fcs+2] = currY;
                        FACES[fcs+3] = currZ;
                        FACES[fcs+4] = origX;
                        FACES[fcs+5] = origY;
                        FACES[fcs+6] = origZ;
                        FACES[fcs+7] = _origX;
                        FACES[fcs+8] = _origY;
                        FACES[fcs+9] = _origZ;
                        FACES[fcs+10] = _currX;
                        FACES[fcs+11] = _currY;
                        FACES[fcs+12] = _currZ;
                        fcs = fcs + 13;
                        FACES[fcs] = Object;
                        FACES[fcs+1] = currXnext;
                        FACES[fcs+2] = currYnext;
                        FACES[fcs+3] = currZnext;
                        FACES[fcs+4] = origX;
                        FACES[fcs+5] = origY;
                        FACES[fcs+6] = origZ;
                        FACES[fcs+7] = _origX;
                        FACES[fcs+8] = _origY;
                        FACES[fcs+9] = _origZ;
                        FACES[fcs+10] = _currXnext;
                        FACES[fcs+11] = _currYnext;
                        FACES[fcs+12] = _currZnext;
                        fcs = fcs + 13;
                        FACES[fcs] = Object;
                        FACES[fcs+1] = currX;
                        FACES[fcs+2] = currY;
                        FACES[fcs+3] = currZ;
                        FACES[fcs+4] = currXnext;
                        FACES[fcs+5] = currYnext;
                        FACES[fcs+6] = currZnext;
                        FACES[fcs+7] = _currXnext;
                        FACES[fcs+8] = _currYnext;
                        FACES[fcs+9] = _currZnext;
                        FACES[fcs+10] = _currX;
                        FACES[fcs+11] = _currY;
                        FACES[fcs+12] = _currZ;
                        fcs = fcs + 13;
                        if (fcs > MAX_FACES_AND_LINES) return WARNING_OF_MEMORY;
                        //
                        (*SELRECT).Left = MIN4(origX, currX, currXnext, (*SELRECT).Left );
                        (*SELRECT).Left = MIN4(_origX, _currX, _currXnext, (*SELRECT).Left );
                        (*SELRECT).Right = MAX4(origX, currX, currXnext, (*SELRECT).Right );
                        (*SELRECT).Right = MAX4(_origX, _currX, _currXnext, (*SELRECT).Right );
                        (*SELRECT).Bottom = MIN4(origY, currY, currYnext, (*SELRECT).Bottom );
                        (*SELRECT).Bottom = MIN4(_origY, _currY, _currYnext, (*SELRECT).Bottom );
                        (*SELRECT).Top = MAX4(origY, currY, currYnext, (*SELRECT).Top );
                        (*SELRECT).Top = MAX4(_origY, _currY, _currYnext, (*SELRECT).Top );
                        (*SELRECT)._Low = MIN4(origZ, currZ, currZnext, (*SELRECT)._Low );
                        (*SELRECT)._Low = MIN4(_origZ, _currZ, _currZnext, (*SELRECT)._Low );
                        (*SELRECT)._High = MAX4(origZ, currZ, currZnext, (*SELRECT)._High );
                        (*SELRECT)._High = MAX4(_origZ, _currZ, _currZnext, (*SELRECT)._High );
                        }
                }
        // facet
        if (TValues.Shape == SH__FACET)
                {
                float fx1,fx2,fx3,fy1,fy2,fy3,fz1,fz2,fz3;
                fx1 = TValues.SizeX;
                fy1 = TValues.SizeY;
                fz1 = TValues.SizeZ;
                fx2 = TValues.RotateXY;
                fy2 = TValues.RotateYZ;
                fz2 = TValues.RotateXZ;
                fx3 = TValues.ShiftX;
                fy3 = TValues.ShiftY;
                fz3 = TValues.ShiftZ;
                if (Form3->RadioButton4->Checked && CANVAS_TO_FILE)
                        {
                        W_LINE_BLK(fx1,fy1,fz1,fx2,fy2,fz2, CLR, LAYER__3D);
                        W_LINE_BLK(fx2,fy2,fz2,fx3,fy3,fz3, CLR, LAYER__3D);
                        W_LINE_BLK(fx3,fy3,fz3,fx1,fy1,fz1, CLR, LAYER__3D);
                        }
                else if (CANVAS_TO_FILE)
                        W_SOLID_BLK(    fx1,fy1,fz1,fx2,fy2,fz2,fx3,fy3,fz3,fx1,fy1,fz1, CLR, LAYER__3D);
                else    {
                        FACES[fcs] = Object;
                        FACES[fcs+1] = fx1;
                        FACES[fcs+2] = fy1;
                        FACES[fcs+3] = fz1;
                        FACES[fcs+4] = fx2;
                        FACES[fcs+5] = fy2;
                        FACES[fcs+6] = fz2;
                        FACES[fcs+7] = fx3;
                        FACES[fcs+8] = fy3;
                        FACES[fcs+9] = fz3;
                        FACES[fcs+10] = fx1;
                        FACES[fcs+11] = fy1;
                        FACES[fcs+12] = fz1;
                        fcs = fcs + 13;
                        if (fcs > MAX_FACES_AND_LINES) return WARNING_OF_MEMORY;
                        (*SELRECT).Left = MIN4(fx1, fx2, fx3, (*SELRECT).Left );
                        (*SELRECT).Right = MAX4(fx1, fx2, fx3, (*SELRECT).Right );
                        (*SELRECT).Bottom = MIN4(fy1, fy2, fy3, (*SELRECT).Bottom );
                        (*SELRECT).Top = MAX4(fy1, fy2, fy3, (*SELRECT).Top );
                        (*SELRECT)._Low = MIN4(fz1, fz2, fz3, (*SELRECT)._Low );
                        (*SELRECT)._High = MAX4(fz1, fz2, fz3, (*SELRECT)._High );
                        }
                }
        // spiral
        if (TValues.Shape == SH__SPIRAL)
                {
                float IncAn = 180.0/16.0;
                float currX,currY,currZ,currXnext,currYnext,currZnext,origX,origY,origZ,origXn,origYn,origZn;
                int MAXPTS = 32;
                for (int r=0; r<MAXPTS; r++)
                        {
                        currX = TValues.SizeX/2.0*cos(IncAn*r*M_PI/180.0);
                        currY = TValues.SizeY/2.0*sin(IncAn*r*M_PI/180.0);
                        currZ = TValues.SizeZ*(float)r/(float)MAXPTS;
                        currXnext = TValues.SizeX/2.0*cos(IncAn*(r+1)*M_PI/180.0);
                        currYnext = TValues.SizeY/2.0*sin(IncAn*(r+1)*M_PI/180.0);
                        currZnext = TValues.SizeZ*(float)(r+1)/(float)MAXPTS;
                        origX = currX/2.0;
                        origY = currY/2.0;
                        origZ = currZ;
                        origXn = currXnext/2.0;
                        origYn = currYnext/2.0;
                        origZn = currZnext;
                        Rotate_Vertex(&currX,&currZ,-TValues.RotateXZ);
                        Rotate_Vertex(&currXnext,&currZnext,-TValues.RotateXZ);
                        Rotate_Vertex(&origX,&origZ,-TValues.RotateXZ);
                        Rotate_Vertex(&origXn,&origZn,-TValues.RotateXZ);
                        Rotate_Vertex(&currY,&currZ,-TValues.RotateYZ);
                        Rotate_Vertex(&currYnext,&currZnext,-TValues.RotateYZ);
                        Rotate_Vertex(&origY,&origZ,-TValues.RotateYZ);
                        Rotate_Vertex(&origYn,&origZn,-TValues.RotateYZ);
                        Rotate_Vertex(&currX,&currY,TValues.RotateXY);
                        Rotate_Vertex(&currXnext,&currYnext,TValues.RotateXY);
                        Rotate_Vertex(&origX,&origY,TValues.RotateXY);
                        Rotate_Vertex(&origXn,&origYn,TValues.RotateXY);
                        currX +=        TValues.ShiftX;
                        currXnext +=    TValues.ShiftX;
                        origX     +=    TValues.ShiftX;
                        origXn    +=    TValues.ShiftX;
                        currY +=        TValues.ShiftY;
                        currYnext +=    TValues.ShiftY;
                        origY     +=    TValues.ShiftY;
                        origYn    +=    TValues.ShiftY;
                        currZ +=        TValues.ShiftZ;
                        currZnext +=    TValues.ShiftZ;
                        origZ     +=    TValues.ShiftZ;
                        origZn    +=    TValues.ShiftZ;
                        for (int j=0; TJumps[j].Shape; j++)
                                {
                                if (ABS(TJumps[j].ScaleX) > BY_ZERO)
                                        {
                                        currX = currX*TJumps[j].ScaleX;
                                        currXnext = currXnext*TJumps[j].ScaleX;
                                        origX = origX*TJumps[j].ScaleX;
                                        origXn = origXn*TJumps[j].ScaleX;
                                        }
                                if (ABS(TJumps[j].ScaleY) > BY_ZERO)
                                        {
                                        currY = currY*TJumps[j].ScaleY;
                                        currYnext = currYnext*TJumps[j].ScaleY;
                                        origY = origY*TJumps[j].ScaleY;
                                        origYn = origYn*TJumps[j].ScaleY;
                                        }
                                if (ABS(TJumps[j].ScaleZ) > BY_ZERO)
                                        {
                                        currZ = currZ*TJumps[j].ScaleZ;
                                        currZnext = currZnext*TJumps[j].ScaleZ;
                                        origZ = origZ*TJumps[j].ScaleZ;
                                        origZn = origZn*TJumps[j].ScaleZ;
                                        }
                                Rotate_Vertex(&currX,&currZ,-TJumps[j].RotateXZ);
                                Rotate_Vertex(&currXnext,&currZnext,-TJumps[j].RotateXZ);
                                Rotate_Vertex(&origX,&origZ,-TJumps[j].RotateXZ);
                                Rotate_Vertex(&origXn,&origZn,-TJumps[j].RotateXZ);
                                Rotate_Vertex(&currY,&currZ,-TJumps[j].RotateYZ);
                                Rotate_Vertex(&currYnext,&currZnext,-TJumps[j].RotateYZ);
                                Rotate_Vertex(&origY,&origZ,-TJumps[j].RotateYZ);
                                Rotate_Vertex(&origYn,&origZn,-TJumps[j].RotateYZ);
                                Rotate_Vertex(&currX,&currY,TJumps[j].RotateXY);
                                Rotate_Vertex(&currXnext,&currYnext,TJumps[j].RotateXY);
                                Rotate_Vertex(&origX,&origY,TJumps[j].RotateXY);
                                Rotate_Vertex(&origXn,&origYn,TJumps[j].RotateXY);
                                currX +=        TJumps[j].ShiftX;
                                currXnext +=    TJumps[j].ShiftX;
                                origX     +=    TJumps[j].ShiftX;
                                origXn     +=   TJumps[j].ShiftX;
                                currY +=        TJumps[j].ShiftY;
                                currYnext +=    TJumps[j].ShiftY;
                                origY     +=    TJumps[j].ShiftY;
                                origYn     +=   TJumps[j].ShiftY;
                                currZ +=        TJumps[j].ShiftZ;
                                currZnext +=    TJumps[j].ShiftZ;
                                origZ     +=    TJumps[j].ShiftZ;
                                origZn     +=   TJumps[j].ShiftZ;
                                }
                        currX +=        centroid__X;
                        currXnext +=    centroid__X;
                        origX +=        centroid__X;
                        origXn +=       centroid__X;
                        currY +=        centroid__Y;
                        currYnext +=    centroid__Y;
                        origY +=        centroid__Y;
                        origYn +=       centroid__Y;
                        if (!SIDE)
                                {
                                currZ +=        BoardThick;
                                currZnext +=    BoardThick;
                                origZ     +=    BoardThick;
                                origZn    +=    BoardThick;
                                }
                        else    {
                                Rotate_Vertex(&currX,&currZ,180);
                                Rotate_Vertex(&currXnext,&currZnext,180);
                                Rotate_Vertex(&origX,&origZ,180);
                                Rotate_Vertex(&origXn,&origZn,180);
                                }
                        if (_3d)
                                {
                                Rotate3d(&currX,&currY,&currZ,&currXnext,&currYnext,&currZnext,&origX,&origY,&origZ,&origXn,&origYn,&origZn);
                                }
                        if (Form3->RadioButton4->Checked && CANVAS_TO_FILE)
                                {
                                W_LINE_BLK(currX,currY,currZ,currXnext,currYnext,currZnext, CLR, LAYER__3D);
                                W_LINE_BLK(origXn,origYn,origZn,currXnext,currYnext,currZnext, CLR, LAYER__3D);
                                W_LINE_BLK(currX,currY,currZ,origX,origY,origZ, CLR, LAYER__3D);
                                W_LINE_BLK(origX,origY,origZ,origXn,origYn,origZn, CLR, LAYER__3D);
                                }
                        else if (CANVAS_TO_FILE)
                                W_SOLID_BLK(    currX,currY,currZ,origX,origY,origZ,currXnext,currYnext,currZnext,origXn,origYn,origZn, CLR, LAYER__3D);
                        else    {
                                FACES[fcs] = Object;
                                FACES[fcs+1] = currX;
                                FACES[fcs+2] = currY;
                                FACES[fcs+3] = currZ;
                                FACES[fcs+4] = origX;
                                FACES[fcs+5] = origY;
                                FACES[fcs+6] = origZ;
                                FACES[fcs+7] = origXn;
                                FACES[fcs+8] = origYn;
                                FACES[fcs+9] = origZn;
                                FACES[fcs+10] = currXnext;
                                FACES[fcs+11] = currYnext;
                                FACES[fcs+12] = currZnext;
                                fcs = fcs + 13;
                                if (fcs > MAX_FACES_AND_LINES) return WARNING_OF_MEMORY;
                                (*SELRECT).Left = MIN4(origX, currX, currXnext, (*SELRECT).Left );
                                (*SELRECT).Left = MIN(origXn, (*SELRECT).Left );
                                (*SELRECT).Right = MAX4(origX, currX, currXnext, (*SELRECT).Right );
                                (*SELRECT).Right = MAX(origXn, (*SELRECT).Right );
                                (*SELRECT).Bottom = MIN4(origY, currY, currYnext, (*SELRECT).Bottom );
                                (*SELRECT).Bottom = MIN(origYn, (*SELRECT).Bottom );
                                (*SELRECT).Top = MAX4(origY, currY, currYnext, (*SELRECT).Top );
                                (*SELRECT).Top = MAX(origYn, (*SELRECT).Top );
                                (*SELRECT)._Low = MIN4(origZ, currZ, currZnext, (*SELRECT)._Low );
                                (*SELRECT)._Low = MIN(origZn, (*SELRECT)._Low );
                                (*SELRECT)._High = MAX4(origZ, currZ, currZnext, (*SELRECT)._High );
                                (*SELRECT)._High = MAX(origZn, (*SELRECT)._High );
                                }
                        }
                }
        //  oval
        if (TValues.Shape == SH__OVAL)
                {
                float IncAn = (float)180/(float)8;
                float currX;
                float currY;
                float currZ;
                float currXnext;
                float currYnext;
                float currZnext;
                float sv1 = 0;
                float sv2 = 0;
                float sv3 = 0;
                float sv4 = 0;
                float sv5 = 0;
                float sv6 = 0;
                float currDX;
                float currDY;
                float md = MIN(TValues.SizeX,TValues.SizeY);
                for (int r=0; r<16; r++)
                        {
                        if (r < 4)
                                {
                                currDX = DX/(float)2;
                                currDY = DY/(float)2;
                                if (r == 0 && DY > BY_ZERO)
                                        {
                                        currX = (TValues.SizeX/2)*cos(IncAn*r*M_PI/180) + currDX;
                                        currY = (TValues.SizeX/2)*sin(IncAn*r*M_PI/180) + currDY;
                                        currZ = 0;
                                        currXnext = (TValues.SizeX/2)*cos(IncAn*r*M_PI/180) + currDX;
                                        currYnext = (TValues.SizeX/2)*sin(IncAn*r*M_PI/180) - currDY;
                                        currZnext = 0;
                                        Rotate_Vertex(&currX,&currZ,-TValues.RotateXZ);
                                        Rotate_Vertex(&currXnext,&currZnext,-TValues.RotateXZ);
                                        Rotate_Vertex(&currY,&currZ,-TValues.RotateYZ);
                                        Rotate_Vertex(&currYnext,&currZnext,-TValues.RotateYZ);
                                        Rotate_Vertex(&currX,&currY,TValues.RotateXY);
                                        Rotate_Vertex(&currXnext,&currYnext,TValues.RotateXY);
                                        currX +=        TValues.ShiftX;
                                        currXnext +=    TValues.ShiftX;
                                        currY +=        TValues.ShiftY;
                                        currYnext +=    TValues.ShiftY;
                                        currZ +=        TValues.ShiftZ;
                                        currZnext +=    TValues.ShiftZ;
                                        for (int j=0; TJumps[j].Shape; j++)
                                                {
                                                if (ABS(TJumps[j].ScaleX) > BY_ZERO)
                                                        {
                                                        currX = currX*TJumps[j].ScaleX;
                                                        currXnext = currXnext*TJumps[j].ScaleX;
                                                        }
                                                if (ABS(TJumps[j].ScaleY) > BY_ZERO)
                                                        {
                                                        currY = currY*TJumps[j].ScaleY;
                                                        currYnext = currYnext*TJumps[j].ScaleY;
                                                        }
                                                if (ABS(TJumps[j].ScaleZ) > BY_ZERO)
                                                        {
                                                        currZ = currZ*TJumps[j].ScaleZ;
                                                        currZnext = currZnext*TJumps[j].ScaleZ;
                                                        }
                                                Rotate_Vertex(&currX,&currZ,-TJumps[j].RotateXZ);
                                                Rotate_Vertex(&currXnext,&currZnext,-TJumps[j].RotateXZ);
                                                Rotate_Vertex(&currY,&currZ,-TJumps[j].RotateYZ);
                                                Rotate_Vertex(&currYnext,&currZnext,-TJumps[j].RotateYZ);
                                                Rotate_Vertex(&currX,&currY,TJumps[j].RotateXY);
                                                Rotate_Vertex(&currXnext,&currYnext,TJumps[j].RotateXY);
                                                currX +=        TJumps[j].ShiftX;
                                                currXnext +=    TJumps[j].ShiftX;
                                                currY +=        TJumps[j].ShiftY;
                                                currYnext +=    TJumps[j].ShiftY;
                                                currZ +=        TJumps[j].ShiftZ;
                                                currZnext +=    TJumps[j].ShiftZ;
                                                }
                                        currX +=        centroid__X;
                                        currXnext +=    centroid__X;
                                        currY +=        centroid__Y;
                                        currYnext +=    centroid__Y;
                                        if (!SIDE)
                                                {
                                                currZ +=        BoardThick;
                                                currZnext +=    BoardThick;
                                                }
                                        else    {
                                                Rotate_Vertex(&currX,&currZ,180);
                                                Rotate_Vertex(&currXnext,&currZnext,180);
                                                }
                                        if (_3d)
                                                {
                                                Rotate3d(&currX,&currY,&currZ,&currXnext,&currYnext,&currZnext);
                                                }
                                        if (Form3->RadioButton4->Checked && CANVAS_TO_FILE) W_LINE_BLK(currX,currY,currZ,currXnext,currYnext,currZnext, CLR, LAYER__3D);
                                        sv1 = currX;
                                        sv2 = currY;
                                        sv3 = currZ;
                                        sv4 = currXnext;
                                        sv5 = currYnext;
                                        sv6 = currZnext;
                                        //
                                        currX = (TValues.SizeX/2)*cos(IncAn*r*M_PI/180) + currDX;
                                        currY = (TValues.SizeX/2)*sin(IncAn*r*M_PI/180) + currDY;
                                        currZ = TValues.SizeZ;
                                        currXnext = (TValues.SizeX/2)*cos(IncAn*r*M_PI/180) + currDX;
                                        currYnext = (TValues.SizeX/2)*sin(IncAn*r*M_PI/180) - currDY;
                                        currZnext = TValues.SizeZ;
                                        Rotate_Vertex(&currX,&currZ,-TValues.RotateXZ);
                                        Rotate_Vertex(&currXnext,&currZnext,-TValues.RotateXZ);
                                        Rotate_Vertex(&currY,&currZ,-TValues.RotateYZ);
                                        Rotate_Vertex(&currYnext,&currZnext,-TValues.RotateYZ);
                                        Rotate_Vertex(&currX,&currY,TValues.RotateXY);
                                        Rotate_Vertex(&currXnext,&currYnext,TValues.RotateXY);
                                        currX +=        TValues.ShiftX;
                                        currXnext +=    TValues.ShiftX;
                                        currY +=        TValues.ShiftY;
                                        currYnext +=    TValues.ShiftY;
                                        currZ +=        TValues.ShiftZ;
                                        currZnext +=    TValues.ShiftZ;
                                        for (int j=0; TJumps[j].Shape; j++)
                                                {
                                                if (ABS(TJumps[j].ScaleX) > BY_ZERO)
                                                        {
                                                        currX = currX*TJumps[j].ScaleX;
                                                        currXnext = currXnext*TJumps[j].ScaleX;
                                                        }
                                                if (ABS(TJumps[j].ScaleY) > BY_ZERO)
                                                        {
                                                        currY = currY*TJumps[j].ScaleY;
                                                        currYnext = currYnext*TJumps[j].ScaleY;
                                                        }
                                                if (ABS(TJumps[j].ScaleZ) > BY_ZERO)
                                                        {
                                                        currZ = currZ*TJumps[j].ScaleZ;
                                                        currZnext = currZnext*TJumps[j].ScaleZ;
                                                        }
                                                Rotate_Vertex(&currX,&currZ,-TJumps[j].RotateXZ);
                                                Rotate_Vertex(&currXnext,&currZnext,-TJumps[j].RotateXZ);
                                                Rotate_Vertex(&currY,&currZ,-TJumps[j].RotateYZ);
                                                Rotate_Vertex(&currYnext,&currZnext,-TJumps[j].RotateYZ);
                                                Rotate_Vertex(&currX,&currY,TJumps[j].RotateXY);
                                                Rotate_Vertex(&currXnext,&currYnext,TJumps[j].RotateXY);
                                                currX +=        TJumps[j].ShiftX;
                                                currXnext +=    TJumps[j].ShiftX;
                                                currY +=        TJumps[j].ShiftY;
                                                currYnext +=    TJumps[j].ShiftY;
                                                currZ +=        TJumps[j].ShiftZ;
                                                currZnext +=    TJumps[j].ShiftZ;
                                                }
                                        currX +=        centroid__X;
                                        currXnext +=    centroid__X;
                                        currY +=        centroid__Y;
                                        currYnext +=    centroid__Y;
                                        if (!SIDE)
                                                {
                                                currZ +=        BoardThick;
                                                currZnext +=    BoardThick;
                                                }
                                        else    {
                                                Rotate_Vertex(&currX,&currZ,180);
                                                Rotate_Vertex(&currXnext,&currZnext,180);
                                                }
                                        if (_3d)
                                                {
                                                Rotate3d(&currX,&currY,&currZ,&currXnext,&currYnext,&currZnext);
                                                }
                                        }
                                }
                        else if (r < 8)
                                {
                                if (r == 4 && DX > BY_ZERO)
                                        {
                                        currX = (TValues.SizeY/2)*cos(IncAn*r*M_PI/180) + currDX;
                                        currY = (TValues.SizeY/2)*sin(IncAn*r*M_PI/180) + currDY;
                                        currZ = 0;
                                        currXnext = (TValues.SizeY/2)*cos(IncAn*r*M_PI/180) - currDX;
                                        currYnext = (TValues.SizeY/2)*sin(IncAn*r*M_PI/180) + currDY;
                                        currZnext = 0;
                                        Rotate_Vertex(&currX,&currZ,-TValues.RotateXZ);
                                        Rotate_Vertex(&currXnext,&currZnext,-TValues.RotateXZ);
                                        Rotate_Vertex(&currY,&currZ,-TValues.RotateYZ);
                                        Rotate_Vertex(&currYnext,&currZnext,-TValues.RotateYZ);
                                        Rotate_Vertex(&currX,&currY,TValues.RotateXY);
                                        Rotate_Vertex(&currXnext,&currYnext,TValues.RotateXY);
                                        currX +=        TValues.ShiftX;
                                        currXnext +=    TValues.ShiftX;
                                        currY +=        TValues.ShiftY;
                                        currYnext +=    TValues.ShiftY;
                                        currZ +=        TValues.ShiftZ;
                                        currZnext +=    TValues.ShiftZ;
                                        for (int j=0; TJumps[j].Shape; j++)
                                                {
                                                if (ABS(TJumps[j].ScaleX) > BY_ZERO)
                                                        {
                                                        currX = currX*TJumps[j].ScaleX;
                                                        currXnext = currXnext*TJumps[j].ScaleX;
                                                        }
                                                if (ABS(TJumps[j].ScaleY) > BY_ZERO)
                                                        {
                                                        currY = currY*TJumps[j].ScaleY;
                                                        currYnext = currYnext*TJumps[j].ScaleY;
                                                        }
                                                if (ABS(TJumps[j].ScaleZ) > BY_ZERO)
                                                        {
                                                        currZ = currZ*TJumps[j].ScaleZ;
                                                        currZnext = currZnext*TJumps[j].ScaleZ;
                                                        }
                                                Rotate_Vertex(&currX,&currZ,-TJumps[j].RotateXZ);
                                                Rotate_Vertex(&currXnext,&currZnext,-TJumps[j].RotateXZ);
                                                Rotate_Vertex(&currY,&currZ,-TJumps[j].RotateYZ);
                                                Rotate_Vertex(&currYnext,&currZnext,-TJumps[j].RotateYZ);
                                                Rotate_Vertex(&currX,&currY,TJumps[j].RotateXY);
                                                Rotate_Vertex(&currXnext,&currYnext,TJumps[j].RotateXY);
                                                currX +=        TJumps[j].ShiftX;
                                                currXnext +=    TJumps[j].ShiftX;
                                                currY +=        TJumps[j].ShiftY;
                                                currYnext +=    TJumps[j].ShiftY;
                                                currZ +=        TJumps[j].ShiftZ;
                                                currZnext +=    TJumps[j].ShiftZ;
                                                }
                                        currX +=        centroid__X;
                                        currXnext +=    centroid__X;
                                        currY +=        centroid__Y;
                                        currYnext +=    centroid__Y;
                                        if (!SIDE)
                                                {
                                                currZ +=        BoardThick;
                                                currZnext +=    BoardThick;
                                                }
                                        else    {
                                                Rotate_Vertex(&currX,&currZ,180);
                                                Rotate_Vertex(&currXnext,&currZnext,180);
                                                }
                                        if (_3d)
                                                {
                                                Rotate3d(&currX,&currY,&currZ,&currXnext,&currYnext,&currZnext);
                                                }
                                        if (Form3->RadioButton4->Checked && CANVAS_TO_FILE) W_LINE_BLK(currX,currY,currZ,currXnext,currYnext,currZnext, CLR, LAYER__3D);
                                        sv1 = currX;
                                        sv2 = currY;
                                        sv3 = currZ;
                                        sv4 = currXnext;
                                        sv5 = currYnext;
                                        sv6 = currZnext;
                                        //
                                        currX = (TValues.SizeY/2)*cos(IncAn*r*M_PI/180) + currDX;
                                        currY = (TValues.SizeY/2)*sin(IncAn*r*M_PI/180) + currDY;
                                        currZ = TValues.SizeZ;
                                        currXnext = (TValues.SizeY/2)*cos(IncAn*r*M_PI/180) - currDX;
                                        currYnext = (TValues.SizeY/2)*sin(IncAn*r*M_PI/180) + currDY;
                                        currZnext = TValues.SizeZ;
                                        Rotate_Vertex(&currX,&currZ,-TValues.RotateXZ);
                                        Rotate_Vertex(&currXnext,&currZnext,-TValues.RotateXZ);
                                        Rotate_Vertex(&currY,&currZ,-TValues.RotateYZ);
                                        Rotate_Vertex(&currYnext,&currZnext,-TValues.RotateYZ);
                                        Rotate_Vertex(&currX,&currY,TValues.RotateXY);
                                        Rotate_Vertex(&currXnext,&currYnext,TValues.RotateXY);
                                        currX +=        TValues.ShiftX;
                                        currXnext +=    TValues.ShiftX;
                                        currY +=        TValues.ShiftY;
                                        currYnext +=    TValues.ShiftY;
                                        currZ +=        TValues.ShiftZ;
                                        currZnext +=    TValues.ShiftZ;
                                        for (int j=0; TJumps[j].Shape; j++)
                                                {
                                                if (ABS(TJumps[j].ScaleX) > BY_ZERO)
                                                        {
                                                        currX = currX*TJumps[j].ScaleX;
                                                        currXnext = currXnext*TJumps[j].ScaleX;
                                                        }
                                                if (ABS(TJumps[j].ScaleY) > BY_ZERO)
                                                        {
                                                        currY = currY*TJumps[j].ScaleY;
                                                        currYnext = currYnext*TJumps[j].ScaleY;
                                                        }
                                                if (ABS(TJumps[j].ScaleZ) > BY_ZERO)
                                                        {
                                                        currZ = currZ*TJumps[j].ScaleZ;
                                                        currZnext = currZnext*TJumps[j].ScaleZ;
                                                        }
                                                Rotate_Vertex(&currX,&currZ,-TJumps[j].RotateXZ);
                                                Rotate_Vertex(&currXnext,&currZnext,-TJumps[j].RotateXZ);
                                                Rotate_Vertex(&currY,&currZ,-TJumps[j].RotateYZ);
                                                Rotate_Vertex(&currYnext,&currZnext,-TJumps[j].RotateYZ);
                                                Rotate_Vertex(&currX,&currY,TJumps[j].RotateXY);
                                                Rotate_Vertex(&currXnext,&currYnext,TJumps[j].RotateXY);
                                                currX +=        TJumps[j].ShiftX;
                                                currXnext +=    TJumps[j].ShiftX;
                                                currY +=        TJumps[j].ShiftY;
                                                currYnext +=    TJumps[j].ShiftY;
                                                currZ +=        TJumps[j].ShiftZ;
                                                currZnext +=    TJumps[j].ShiftZ;
                                                }
                                        currX +=        centroid__X;
                                        currXnext +=    centroid__X;
                                        currY +=        centroid__Y;
                                        currYnext +=    centroid__Y;
                                        if (!SIDE)
                                                {
                                                currZ +=        BoardThick;
                                                currZnext +=    BoardThick;
                                                }
                                        else    {
                                                Rotate_Vertex(&currX,&currZ,180);
                                                Rotate_Vertex(&currXnext,&currZnext,180);
                                                }
                                        if (_3d)
                                                {
                                                Rotate3d(&currX,&currY,&currZ,&currXnext,&currYnext,&currZnext);
                                                }
                                        }
                                currDX = -DX/(float)2;
                                currDY = DY/(float)2;
                                }
                        else if (r < 12)
                                {
                                if (r == 8 && DY > BY_ZERO)
                                        {
                                        currX = (TValues.SizeX/2)*cos(IncAn*r*M_PI/180) - currDX;
                                        currY = (TValues.SizeX/2)*sin(IncAn*r*M_PI/180) - currDY;
                                        currZ = 0;
                                        currXnext = (TValues.SizeX/2)*cos(IncAn*r*M_PI/180) - currDX;
                                        currYnext = (TValues.SizeX/2)*sin(IncAn*r*M_PI/180) + currDY;
                                        currZnext = 0;
                                        Rotate_Vertex(&currX,&currZ,-TValues.RotateXZ);
                                        Rotate_Vertex(&currXnext,&currZnext,-TValues.RotateXZ);
                                        Rotate_Vertex(&currY,&currZ,-TValues.RotateYZ);
                                        Rotate_Vertex(&currYnext,&currZnext,-TValues.RotateYZ);
                                        Rotate_Vertex(&currX,&currY,TValues.RotateXY);
                                        Rotate_Vertex(&currXnext,&currYnext,TValues.RotateXY);
                                        currX +=        TValues.ShiftX;
                                        currXnext +=    TValues.ShiftX;
                                        currY +=        TValues.ShiftY;
                                        currYnext +=    TValues.ShiftY;
                                        currZ +=        TValues.ShiftZ;
                                        currZnext +=    TValues.ShiftZ;
                                        for (int j=0; TJumps[j].Shape; j++)
                                                {
                                                if (ABS(TJumps[j].ScaleX) > BY_ZERO)
                                                        {
                                                        currX = currX*TJumps[j].ScaleX;
                                                        currXnext = currXnext*TJumps[j].ScaleX;
                                                        }
                                                if (ABS(TJumps[j].ScaleY) > BY_ZERO)
                                                        {
                                                        currY = currY*TJumps[j].ScaleY;
                                                        currYnext = currYnext*TJumps[j].ScaleY;
                                                        }
                                                if (ABS(TJumps[j].ScaleZ) > BY_ZERO)
                                                        {
                                                        currZ = currZ*TJumps[j].ScaleZ;
                                                        currZnext = currZnext*TJumps[j].ScaleZ;
                                                        }
                                                Rotate_Vertex(&currX,&currZ,-TJumps[j].RotateXZ);
                                                Rotate_Vertex(&currXnext,&currZnext,-TJumps[j].RotateXZ);
                                                Rotate_Vertex(&currY,&currZ,-TJumps[j].RotateYZ);
                                                Rotate_Vertex(&currYnext,&currZnext,-TJumps[j].RotateYZ);
                                                Rotate_Vertex(&currX,&currY,TJumps[j].RotateXY);
                                                Rotate_Vertex(&currXnext,&currYnext,TJumps[j].RotateXY);
                                                currX +=        TJumps[j].ShiftX;
                                                currXnext +=    TJumps[j].ShiftX;
                                                currY +=        TJumps[j].ShiftY;
                                                currYnext +=    TJumps[j].ShiftY;
                                                currZ +=        TJumps[j].ShiftZ;
                                                currZnext +=    TJumps[j].ShiftZ;
                                                }
                                        currX +=        centroid__X;
                                        currXnext +=    centroid__X;
                                        currY +=        centroid__Y;
                                        currYnext +=    centroid__Y;
                                        if (!SIDE)
                                                {
                                                currZ +=        BoardThick;
                                                currZnext +=    BoardThick;
                                                }
                                        else    {
                                                Rotate_Vertex(&currX,&currZ,180);
                                                Rotate_Vertex(&currXnext,&currZnext,180);
                                                }
                                        if (_3d)
                                                {
                                                Rotate3d(&currX,&currY,&currZ,&currXnext,&currYnext,&currZnext);
                                                }
                                        if (Form3->RadioButton4->Checked && CANVAS_TO_FILE) W_LINE_BLK(currX,currY,currZ,currXnext,currYnext,currZnext, CLR, LAYER__3D);
                                        sv1 = currX;
                                        sv2 = currY;
                                        sv3 = currZ;
                                        sv4 = currXnext;
                                        sv5 = currYnext;
                                        sv6 = currZnext;
                                        //
                                        currX = (TValues.SizeX/2)*cos(IncAn*r*M_PI/180) - currDX;
                                        currY = (TValues.SizeX/2)*sin(IncAn*r*M_PI/180) - currDY;
                                        currZ = TValues.SizeZ;
                                        currXnext = (TValues.SizeX/2)*cos(IncAn*r*M_PI/180) - currDX;
                                        currYnext = (TValues.SizeX/2)*sin(IncAn*r*M_PI/180) + currDY;
                                        currZnext = TValues.SizeZ;
                                        Rotate_Vertex(&currX,&currZ,-TValues.RotateXZ);
                                        Rotate_Vertex(&currXnext,&currZnext,-TValues.RotateXZ);
                                        Rotate_Vertex(&currY,&currZ,-TValues.RotateYZ);
                                        Rotate_Vertex(&currYnext,&currZnext,-TValues.RotateYZ);
                                        Rotate_Vertex(&currX,&currY,TValues.RotateXY);
                                        Rotate_Vertex(&currXnext,&currYnext,TValues.RotateXY);
                                        currX +=        TValues.ShiftX;
                                        currXnext +=    TValues.ShiftX;
                                        currY +=        TValues.ShiftY;
                                        currYnext +=    TValues.ShiftY;
                                        currZ +=        TValues.ShiftZ;
                                        currZnext +=    TValues.ShiftZ;
                                        for (int j=0; TJumps[j].Shape; j++)
                                                {
                                                if (ABS(TJumps[j].ScaleX) > BY_ZERO)
                                                        {
                                                        currX = currX*TJumps[j].ScaleX;
                                                        currXnext = currXnext*TJumps[j].ScaleX;
                                                        }
                                                if (ABS(TJumps[j].ScaleY) > BY_ZERO)
                                                        {
                                                        currY = currY*TJumps[j].ScaleY;
                                                        currYnext = currYnext*TJumps[j].ScaleY;
                                                        }
                                                if (ABS(TJumps[j].ScaleZ) > BY_ZERO)
                                                        {
                                                        currZ = currZ*TJumps[j].ScaleZ;
                                                        currZnext = currZnext*TJumps[j].ScaleZ;
                                                        }
                                                Rotate_Vertex(&currX,&currZ,-TJumps[j].RotateXZ);
                                                Rotate_Vertex(&currXnext,&currZnext,-TJumps[j].RotateXZ);
                                                Rotate_Vertex(&currY,&currZ,-TJumps[j].RotateYZ);
                                                Rotate_Vertex(&currYnext,&currZnext,-TJumps[j].RotateYZ);
                                                Rotate_Vertex(&currX,&currY,TJumps[j].RotateXY);
                                                Rotate_Vertex(&currXnext,&currYnext,TJumps[j].RotateXY);
                                                currX +=        TJumps[j].ShiftX;
                                                currXnext +=    TJumps[j].ShiftX;
                                                currY +=        TJumps[j].ShiftY;
                                                currYnext +=    TJumps[j].ShiftY;
                                                currZ +=        TJumps[j].ShiftZ;
                                                currZnext +=    TJumps[j].ShiftZ;
                                                }
                                        currX +=        centroid__X;
                                        currXnext +=    centroid__X;
                                        currY +=        centroid__Y;
                                        currYnext +=    centroid__Y;
                                        if (!SIDE)
                                                {
                                                currZ +=        BoardThick;
                                                currZnext +=    BoardThick;
                                                }
                                        else    {
                                                Rotate_Vertex(&currX,&currZ,180);
                                                Rotate_Vertex(&currXnext,&currZnext,180);
                                                }
                                        if (_3d)
                                                {
                                                Rotate3d(&currX,&currY,&currZ,&currXnext,&currYnext,&currZnext);
                                                }
                                        }
                                currDX = -DX/(float)2;
                                currDY = -DY/(float)2;
                                }
                        else    {
                                if (r == 12 && DX > BY_ZERO)
                                        {
                                        currX = (TValues.SizeY/2)*cos(IncAn*r*M_PI/180) - currDX;
                                        currY = (TValues.SizeY/2)*sin(IncAn*r*M_PI/180) - currDY;
                                        currZ = 0;
                                        currXnext = (TValues.SizeY/2)*cos(IncAn*r*M_PI/180) + currDX;
                                        currYnext = (TValues.SizeY/2)*sin(IncAn*r*M_PI/180) - currDY;
                                        currZnext = 0;
                                        Rotate_Vertex(&currX,&currZ,-TValues.RotateXZ);
                                        Rotate_Vertex(&currXnext,&currZnext,-TValues.RotateXZ);
                                        Rotate_Vertex(&currY,&currZ,-TValues.RotateYZ);
                                        Rotate_Vertex(&currYnext,&currZnext,-TValues.RotateYZ);
                                        Rotate_Vertex(&currX,&currY,TValues.RotateXY);
                                        Rotate_Vertex(&currXnext,&currYnext,TValues.RotateXY);
                                        currX +=        TValues.ShiftX;
                                        currXnext +=    TValues.ShiftX;
                                        currY +=        TValues.ShiftY;
                                        currYnext +=    TValues.ShiftY;
                                        currZ +=        TValues.ShiftZ;
                                        currZnext +=    TValues.ShiftZ;
                                        for (int j=0; TJumps[j].Shape; j++)
                                                {
                                                if (ABS(TJumps[j].ScaleX) > BY_ZERO)
                                                        {
                                                        currX = currX*TJumps[j].ScaleX;
                                                        currXnext = currXnext*TJumps[j].ScaleX;
                                                        }
                                                if (ABS(TJumps[j].ScaleY) > BY_ZERO)
                                                        {
                                                        currY = currY*TJumps[j].ScaleY;
                                                        currYnext = currYnext*TJumps[j].ScaleY;
                                                        }
                                                if (ABS(TJumps[j].ScaleZ) > BY_ZERO)
                                                        {
                                                        currZ = currZ*TJumps[j].ScaleZ;
                                                        currZnext = currZnext*TJumps[j].ScaleZ;
                                                        }
                                                Rotate_Vertex(&currX,&currZ,-TJumps[j].RotateXZ);
                                                Rotate_Vertex(&currXnext,&currZnext,-TJumps[j].RotateXZ);
                                                Rotate_Vertex(&currY,&currZ,-TJumps[j].RotateYZ);
                                                Rotate_Vertex(&currYnext,&currZnext,-TJumps[j].RotateYZ);
                                                Rotate_Vertex(&currX,&currY,TJumps[j].RotateXY);
                                                Rotate_Vertex(&currXnext,&currYnext,TJumps[j].RotateXY);
                                                currX +=        TJumps[j].ShiftX;
                                                currXnext +=    TJumps[j].ShiftX;
                                                currY +=        TJumps[j].ShiftY;
                                                currYnext +=    TJumps[j].ShiftY;
                                                currZ +=        TJumps[j].ShiftZ;
                                                currZnext +=    TJumps[j].ShiftZ;
                                                }
                                        currX +=        centroid__X;
                                        currXnext +=    centroid__X;
                                        currY +=        centroid__Y;
                                        currYnext +=    centroid__Y;
                                        if (!SIDE)
                                                {
                                                currZ +=        BoardThick;
                                                currZnext +=    BoardThick;
                                                }
                                        else    {
                                                Rotate_Vertex(&currX,&currZ,180);
                                                Rotate_Vertex(&currXnext,&currZnext,180);
                                                }
                                        if (_3d)
                                                {
                                                Rotate3d(&currX,&currY,&currZ,&currXnext,&currYnext,&currZnext);
                                                }
                                        if (Form3->RadioButton4->Checked) W_LINE_BLK(currX,currY,currZ,currXnext,currYnext,currZnext, CLR, LAYER__3D);
                                        sv1 = currX;
                                        sv2 = currY;
                                        sv3 = currZ;
                                        sv4 = currXnext;
                                        sv5 = currYnext;
                                        sv6 = currZnext;
                                        //
                                        currX = (TValues.SizeY/2)*cos(IncAn*r*M_PI/180) - currDX;
                                        currY = (TValues.SizeY/2)*sin(IncAn*r*M_PI/180) - currDY;
                                        currZ = TValues.SizeZ;
                                        currXnext = (TValues.SizeY/2)*cos(IncAn*r*M_PI/180) + currDX;
                                        currYnext = (TValues.SizeY/2)*sin(IncAn*r*M_PI/180) - currDY;
                                        currZnext = TValues.SizeZ;
                                        Rotate_Vertex(&currX,&currZ,-TValues.RotateXZ);
                                        Rotate_Vertex(&currXnext,&currZnext,-TValues.RotateXZ);
                                        Rotate_Vertex(&currY,&currZ,-TValues.RotateYZ);
                                        Rotate_Vertex(&currYnext,&currZnext,-TValues.RotateYZ);
                                        Rotate_Vertex(&currX,&currY,TValues.RotateXY);
                                        Rotate_Vertex(&currXnext,&currYnext,TValues.RotateXY);
                                        currX +=        TValues.ShiftX;
                                        currXnext +=    TValues.ShiftX;
                                        currY +=        TValues.ShiftY;
                                        currYnext +=    TValues.ShiftY;
                                        currZ +=        TValues.ShiftZ;
                                        currZnext +=    TValues.ShiftZ;
                                        for (int j=0; TJumps[j].Shape; j++)
                                                {
                                                if (ABS(TJumps[j].ScaleX) > BY_ZERO)
                                                        {
                                                        currX = currX*TJumps[j].ScaleX;
                                                        currXnext = currXnext*TJumps[j].ScaleX;
                                                        }
                                                if (ABS(TJumps[j].ScaleY) > BY_ZERO)
                                                        {
                                                        currY = currY*TJumps[j].ScaleY;
                                                        currYnext = currYnext*TJumps[j].ScaleY;
                                                        }
                                                if (ABS(TJumps[j].ScaleZ) > BY_ZERO)
                                                        {
                                                        currZ = currZ*TJumps[j].ScaleZ;
                                                        currZnext = currZnext*TJumps[j].ScaleZ;
                                                        }
                                                Rotate_Vertex(&currX,&currZ,-TJumps[j].RotateXZ);
                                                Rotate_Vertex(&currXnext,&currZnext,-TJumps[j].RotateXZ);
                                                Rotate_Vertex(&currY,&currZ,-TJumps[j].RotateYZ);
                                                Rotate_Vertex(&currYnext,&currZnext,-TJumps[j].RotateYZ);
                                                Rotate_Vertex(&currX,&currY,TJumps[j].RotateXY);
                                                Rotate_Vertex(&currXnext,&currYnext,TJumps[j].RotateXY);
                                                currX +=        TJumps[j].ShiftX;
                                                currXnext +=    TJumps[j].ShiftX;
                                                currY +=        TJumps[j].ShiftY;
                                                currYnext +=    TJumps[j].ShiftY;
                                                currZ +=        TJumps[j].ShiftZ;
                                                currZnext +=    TJumps[j].ShiftZ;
                                                }
                                        currX +=        centroid__X;
                                        currXnext +=    centroid__X;
                                        currY +=        centroid__Y;
                                        currYnext +=    centroid__Y;
                                        if (!SIDE)
                                                {
                                                currZ +=        BoardThick;
                                                currZnext +=    BoardThick;
                                                }
                                        else    {
                                                Rotate_Vertex(&currX,&currZ,180);
                                                Rotate_Vertex(&currXnext,&currZnext,180);
                                                }
                                        if (_3d)
                                                {
                                                Rotate3d(&currX,&currY,&currZ,&currXnext,&currYnext,&currZnext);
                                                }
                                        }
                                currDX = DX/(float)2;
                                currDY = -DY/(float)2;
                                }
                        if ((r == 0 && DY > BY_ZERO)
                        || (r == 4 && DX > BY_ZERO)
                        || (r == 8 && DY > BY_ZERO)
                        || (r == 12 && DX > BY_ZERO))
                                {
                                if (Form3->RadioButton4->Checked && CANVAS_TO_FILE) W_LINE_BLK(currX,currY,currZ,currXnext,currYnext,currZnext, CLR, LAYER__3D);
                                else if (CANVAS_TO_FILE)
                                        {
                                        W_SOLID_BLK(   sv1,sv2,sv3,sv4,sv5,sv6,
                                                currX,currY,currZ,currXnext,currYnext,currZnext , CLR, LAYER__3D);
                                        float CenX = 0;
                                        float CenY = 0;
                                        float CenZ = TValues.SizeZ;
                                        Rotate_Vertex(&CenX,&CenZ,-TValues.RotateXZ);
                                        Rotate_Vertex(&CenY,&CenZ,-TValues.RotateYZ);
                                        Rotate_Vertex(&CenX,&CenY,TValues.RotateXY);
                                        CenX += TValues.ShiftX;
                                        CenY += TValues.ShiftY;
                                        CenZ += TValues.ShiftZ;
                                        for (int j=0; TJumps[j].Shape; j++)
                                                {
                                                if (ABS(TJumps[j].ScaleX) > BY_ZERO)
                                                        CenX = CenX*TJumps[j].ScaleX;
                                                if (ABS(TJumps[j].ScaleY) > BY_ZERO)
                                                        CenY = CenY*TJumps[j].ScaleY;
                                                if (ABS(TJumps[j].ScaleZ) > BY_ZERO)
                                                        CenZ = CenZ*TJumps[j].ScaleZ;
                                                Rotate_Vertex(&CenX,&CenZ,-TJumps[j].RotateXZ);
                                                Rotate_Vertex(&CenY,&CenZ,-TJumps[j].RotateYZ);
                                                Rotate_Vertex(&CenX,&CenY, TJumps[j].RotateXY);
                                                CenX +=         TJumps[j].ShiftX;
                                                CenY +=         TJumps[j].ShiftY;
                                                CenZ +=         TJumps[j].ShiftZ;
                                                }
                                        CenX +=        centroid__X;
                                        CenY +=        centroid__Y;
                                        if (!SIDE) CenZ += BoardThick;
                                        else       Rotate_Vertex(&CenX,&CenZ,180);
                                        if (_3d)
                                                {
                                                Rotate3d(&CenX,&CenY,&CenZ);
                                                }
                                        W_SOLID_BLK(    currX,currY,currZ,
                                                        CenX,CenY,CenZ,
                                                        currXnext,currYnext,currZnext,
                                                        CenX,CenY,CenZ, CLR, LAYER__3D);
                                        CenX = 0;
                                        CenY = 0;
                                        CenZ = 0;
                                        Rotate_Vertex(&CenX,&CenZ,-TValues.RotateXZ);
                                        Rotate_Vertex(&CenY,&CenZ,-TValues.RotateYZ);
                                        Rotate_Vertex(&CenX,&CenY,TValues.RotateXY);
                                        CenX += TValues.ShiftX;
                                        CenY += TValues.ShiftY;
                                        CenZ += TValues.ShiftZ;
                                        for (int j=0; TJumps[j].Shape; j++)
                                                {
                                                if (ABS(TJumps[j].ScaleX) > BY_ZERO)
                                                        CenX = CenX*TJumps[j].ScaleX;
                                                if (ABS(TJumps[j].ScaleY) > BY_ZERO)
                                                        CenY = CenY*TJumps[j].ScaleY;
                                                if (ABS(TJumps[j].ScaleZ) > BY_ZERO)
                                                        CenZ = CenZ*TJumps[j].ScaleZ;
                                                Rotate_Vertex(&CenX,&CenZ,-TJumps[j].RotateXZ);
                                                Rotate_Vertex(&CenY,&CenZ,-TJumps[j].RotateYZ);
                                                Rotate_Vertex(&CenX,&CenY, TJumps[j].RotateXY);
                                                CenX +=         TJumps[j].ShiftX;
                                                CenY +=         TJumps[j].ShiftY;
                                                CenZ +=         TJumps[j].ShiftZ;
                                                }
                                        CenX +=        centroid__X;
                                        CenY +=        centroid__Y;
                                        if (!SIDE) CenZ += BoardThick;
                                        else       Rotate_Vertex(&CenX,&CenZ,180);
                                        if (_3d)
                                                {
                                                Rotate3d(&CenX,&CenY,&CenZ);
                                                }
                                        W_SOLID_BLK(    sv1,sv2,sv3,
                                                        CenX,CenY,CenZ,
                                                        sv4,sv5,sv6,
                                                        CenX,CenY,CenZ, CLR, LAYER__3D);
                                        }
                                else    {
                                        FACES[fcs] = Object;
                                        FACES[fcs+1] = sv1;
                                        FACES[fcs+2] = sv2;
                                        FACES[fcs+3] = sv3;
                                        FACES[fcs+4] = sv4;
                                        FACES[fcs+5] = sv5;
                                        FACES[fcs+6] = sv6;
                                        FACES[fcs+7] = currXnext;
                                        FACES[fcs+8] = currYnext;
                                        FACES[fcs+9] = currZnext;
                                        FACES[fcs+10] = currX;
                                        FACES[fcs+11] = currY;
                                        FACES[fcs+12] = currZ;
                                        fcs = fcs + 13;
                                        float CenX = 0;
                                        float CenY = 0;
                                        float CenZ = TValues.SizeZ;
                                        Rotate_Vertex(&CenX,&CenZ,-TValues.RotateXZ);
                                        Rotate_Vertex(&CenY,&CenZ,-TValues.RotateYZ);
                                        Rotate_Vertex(&CenX,&CenY,TValues.RotateXY);
                                        CenX += TValues.ShiftX;
                                        CenY += TValues.ShiftY;
                                        CenZ += TValues.ShiftZ;
                                        for (int j=0; TJumps[j].Shape; j++)
                                                {
                                                if (ABS(TJumps[j].ScaleX) > BY_ZERO)
                                                        CenX = CenX*TJumps[j].ScaleX;
                                                if (ABS(TJumps[j].ScaleY) > BY_ZERO)
                                                        CenY = CenY*TJumps[j].ScaleY;
                                                if (ABS(TJumps[j].ScaleZ) > BY_ZERO)
                                                        CenZ = CenZ*TJumps[j].ScaleZ;
                                                Rotate_Vertex(&CenX,&CenZ,-TJumps[j].RotateXZ);
                                                Rotate_Vertex(&CenY,&CenZ,-TJumps[j].RotateYZ);
                                                Rotate_Vertex(&CenX,&CenY, TJumps[j].RotateXY);
                                                CenX +=         TJumps[j].ShiftX;
                                                CenY +=         TJumps[j].ShiftY;
                                                CenZ +=         TJumps[j].ShiftZ;
                                                }
                                        CenX +=        centroid__X;
                                        CenY +=        centroid__Y;
                                        if (!SIDE) CenZ += BoardThick;
                                        else       Rotate_Vertex(&CenX,&CenZ,180);
                                        if (_3d)
                                                {
                                                Rotate3d(&CenX,&CenY,&CenZ);
                                                }
                                        FACES[fcs] = Object;
                                        FACES[fcs+1] = currX;
                                        FACES[fcs+2] = currY;
                                        FACES[fcs+3] = currZ;
                                        FACES[fcs+4] = CenX;
                                        FACES[fcs+5] = CenY;
                                        FACES[fcs+6] = CenZ;
                                        FACES[fcs+7] = CenX; 
                                        FACES[fcs+8] = CenY; 
                                        FACES[fcs+9] = CenZ; 
                                        FACES[fcs+10] = currXnext;
                                        FACES[fcs+11] = currYnext;
                                        FACES[fcs+12] = currZnext;
                                        fcs = fcs + 13;
                                        CenX = 0;
                                        CenY = 0;
                                        CenZ = 0;
                                        Rotate_Vertex(&CenX,&CenZ,-TValues.RotateXZ);
                                        Rotate_Vertex(&CenY,&CenZ,-TValues.RotateYZ);
                                        Rotate_Vertex(&CenX,&CenY,TValues.RotateXY);
                                        CenX += TValues.ShiftX;
                                        CenY += TValues.ShiftY;
                                        CenZ += TValues.ShiftZ;
                                        for (int j=0; TJumps[j].Shape; j++)
                                                {
                                                if (ABS(TJumps[j].ScaleX) > BY_ZERO)
                                                        CenX = CenX*TJumps[j].ScaleX;
                                                if (ABS(TJumps[j].ScaleY) > BY_ZERO)
                                                        CenY = CenY*TJumps[j].ScaleY;
                                                if (ABS(TJumps[j].ScaleZ) > BY_ZERO)
                                                        CenZ = CenZ*TJumps[j].ScaleZ;
                                                Rotate_Vertex(&CenX,&CenZ,-TJumps[j].RotateXZ);
                                                Rotate_Vertex(&CenY,&CenZ,-TJumps[j].RotateYZ);
                                                Rotate_Vertex(&CenX,&CenY, TJumps[j].RotateXY);
                                                CenX +=         TJumps[j].ShiftX;
                                                CenY +=         TJumps[j].ShiftY;
                                                CenZ +=         TJumps[j].ShiftZ;
                                                }
                                        CenX +=        centroid__X;
                                        CenY +=        centroid__Y;
                                        if (!SIDE) CenZ += BoardThick;
                                        else       Rotate_Vertex(&CenX,&CenZ,180);
                                        if (_3d)
                                                {
                                                Rotate3d(&CenX,&CenY,&CenZ);
                                                }
                                        FACES[fcs] = Object;
                                        FACES[fcs+1] = sv1;
                                        FACES[fcs+2] = sv2;
                                        FACES[fcs+3] = sv3;
                                        FACES[fcs+4] = CenX;
                                        FACES[fcs+5] = CenY;
                                        FACES[fcs+6] = CenZ;
                                        FACES[fcs+7] = CenX;
                                        FACES[fcs+8] = CenY;
                                        FACES[fcs+9] = CenZ;
                                        FACES[fcs+10] = sv4;
                                        FACES[fcs+11] = sv5;
                                        FACES[fcs+12] = sv6;
                                        fcs = fcs + 13;
                                        if (fcs > MAX_FACES_AND_LINES) return WARNING_OF_MEMORY;
                                        (*SELRECT).Left = MIN4(sv1, sv4, currXnext, (*SELRECT).Left );
                                        (*SELRECT).Left = MIN(currX, (*SELRECT).Left );
                                        (*SELRECT).Right = MAX4(sv1, sv4, currXnext, (*SELRECT).Right );
                                        (*SELRECT).Right = MAX(currX, (*SELRECT).Right );
                                        (*SELRECT).Bottom = MIN4(sv2, sv5, currYnext, (*SELRECT).Bottom );
                                        (*SELRECT).Bottom = MIN(currY, (*SELRECT).Bottom );
                                        (*SELRECT).Top = MAX4(sv2, sv5, currYnext, (*SELRECT).Top );
                                        (*SELRECT).Top = MAX(currY, (*SELRECT).Top );
                                        (*SELRECT)._Low = MIN4(sv3, sv6, currZnext, (*SELRECT)._Low );
                                        (*SELRECT)._Low = MIN(currZ, (*SELRECT)._Low );
                                        (*SELRECT)._High = MAX4(sv3, sv6, currZnext, (*SELRECT)._High );
                                        (*SELRECT)._High = MAX(currZ, (*SELRECT)._High );
                                        }
                                }
                        currX = (md/2)*cos(IncAn*r*M_PI/180) + currDX;
                        currY = (md/2)*sin(IncAn*r*M_PI/180) + currDY;
                        currZ = 0;
                        currXnext = (md/2)*cos(IncAn*(r+1)*M_PI/180) + currDX;
                        currYnext = (md/2)*sin(IncAn*(r+1)*M_PI/180) + currDY;
                        currZnext = 0;
                        float CX1, CY1, CZ1;
                        CX1 = 0;
                        CY1 = 0;
                        CZ1 = 0;
                        Rotate_Vertex(&currX,&currZ,-TValues.RotateXZ);
                        Rotate_Vertex(&currXnext,&currZnext,-TValues.RotateXZ);
                        Rotate_Vertex(&CX1,&CZ1,-TValues.RotateXZ);
                        Rotate_Vertex(&currY,&currZ,-TValues.RotateYZ);
                        Rotate_Vertex(&currYnext,&currZnext,-TValues.RotateYZ);
                        Rotate_Vertex(&CY1,&CZ1,-TValues.RotateYZ);
                        Rotate_Vertex(&currX,&currY,TValues.RotateXY);
                        Rotate_Vertex(&currXnext,&currYnext,TValues.RotateXY);
                        Rotate_Vertex(&CX1,&CY1,TValues.RotateXY);
                        currX +=        TValues.ShiftX;
                        currXnext +=    TValues.ShiftX;
                        CX1 +=          TValues.ShiftX;
                        currY +=        TValues.ShiftY;
                        currYnext +=    TValues.ShiftY;
                        CY1 +=          TValues.ShiftY;
                        currZ +=        TValues.ShiftZ;
                        currZnext +=    TValues.ShiftZ;
                        CZ1 +=          TValues.ShiftZ;
                        for (int j=0; TJumps[j].Shape; j++)
                                {
                                if (ABS(TJumps[j].ScaleX) > BY_ZERO)
                                        {
                                        currX = currX*TJumps[j].ScaleX;
                                        currXnext = currXnext*TJumps[j].ScaleX;
                                        CX1 = CX1*TJumps[j].ScaleX;
                                        }
                                if (ABS(TJumps[j].ScaleY) > BY_ZERO)
                                        {
                                        currY = currY*TJumps[j].ScaleY;
                                        currYnext = currYnext*TJumps[j].ScaleY;
                                        CY1 = CY1*TJumps[j].ScaleY;
                                        }
                                if (ABS(TJumps[j].ScaleZ) > BY_ZERO)
                                        {
                                        currZ = currZ*TJumps[j].ScaleZ;
                                        currZnext = currZnext*TJumps[j].ScaleZ;
                                        CZ1 = CZ1*TJumps[j].ScaleZ;
                                        }
                                Rotate_Vertex(&currX,&currZ,-TJumps[j].RotateXZ);
                                Rotate_Vertex(&currXnext,&currZnext,-TJumps[j].RotateXZ);
                                Rotate_Vertex(&CX1,&CZ1,-TJumps[j].RotateXZ);
                                Rotate_Vertex(&currY,&currZ,-TJumps[j].RotateYZ);
                                Rotate_Vertex(&currYnext,&currZnext,-TJumps[j].RotateYZ);
                                Rotate_Vertex(&CY1,&CZ1,-TJumps[j].RotateYZ);
                                Rotate_Vertex(&currX,&currY,TJumps[j].RotateXY);
                                Rotate_Vertex(&currXnext,&currYnext,TJumps[j].RotateXY);
                                Rotate_Vertex(&CX1,&CY1,TJumps[j].RotateXY);
                                currX +=        TJumps[j].ShiftX;
                                currXnext +=    TJumps[j].ShiftX;
                                CX1 +=          TJumps[j].ShiftX;
                                currY +=        TJumps[j].ShiftY;
                                currYnext +=    TJumps[j].ShiftY;
                                CY1 +=          TJumps[j].ShiftY;
                                currZ +=        TJumps[j].ShiftZ;
                                currZnext +=    TJumps[j].ShiftZ;
                                CZ1 +=          TJumps[j].ShiftZ;
                                }
                        currX +=        centroid__X;
                        currXnext +=    centroid__X;
                        CX1 +=          centroid__X;
                        currY +=        centroid__Y;
                        currYnext +=    centroid__Y;
                        CY1 +=          centroid__Y;
                        if (!SIDE)
                                {
                                currZ +=        BoardThick;
                                currZnext +=    BoardThick;
                                CZ1 +=          BoardThick;
                                }
                        else    {
                                Rotate_Vertex(&currX,&currZ,180);
                                Rotate_Vertex(&currXnext,&currZnext,180);
                                Rotate_Vertex(&CX1,&CZ1,180);
                                }
                        if (_3d)
                                {
                                Rotate3d(&currX,&currY,&currZ,&currXnext,&currYnext,&currZnext,&CX1,&CY1,&CZ1);
                                }
                        if (Form3->RadioButton4->Checked && CANVAS_TO_FILE) W_LINE_BLK(currX,currY,currZ,currXnext,currYnext,currZnext, CLR, LAYER__3D);
                        float sv1back = sv1;
                        float sv2back = sv2;
                        float sv3back = sv3;
                        float sv4back = sv4;
                        float sv5back = sv5;
                        float sv6back = sv6;
                        sv1 = currX;
                        sv2 = currY;
                        sv3 = currZ;
                        sv4 = currXnext;
                        sv5 = currYnext;
                        sv6 = currZnext;
                        //
                        currX = (md/2)*cos(IncAn*r*M_PI/180) + currDX;
                        currY = (md/2)*sin(IncAn*r*M_PI/180) + currDY;
                        currZ = TValues.SizeZ;
                        currXnext = (md/2)*cos(IncAn*(r+1)*M_PI/180) + currDX;
                        currYnext = (md/2)*sin(IncAn*(r+1)*M_PI/180) + currDY;
                        currZnext = TValues.SizeZ;
                        float CX2, CY2, CZ2;
                        CX2 = 0;
                        CY2 = 0;
                        CZ2 = TValues.SizeZ;
                        Rotate_Vertex(&currX,&currZ,-TValues.RotateXZ);
                        Rotate_Vertex(&currXnext,&currZnext,-TValues.RotateXZ);
                        Rotate_Vertex(&CX2,&CZ2,-TValues.RotateXZ);
                        Rotate_Vertex(&currY,&currZ,-TValues.RotateYZ);
                        Rotate_Vertex(&currYnext,&currZnext,-TValues.RotateYZ);
                        Rotate_Vertex(&CY2,&CZ2,-TValues.RotateYZ);
                        Rotate_Vertex(&currX,&currY,TValues.RotateXY);
                        Rotate_Vertex(&currXnext,&currYnext,TValues.RotateXY);
                        Rotate_Vertex(&CX2,&CY2,TValues.RotateXY);
                        currX +=        TValues.ShiftX;
                        currXnext +=    TValues.ShiftX;
                        CX2 +=          TValues.ShiftX;
                        currY +=        TValues.ShiftY;
                        currYnext +=    TValues.ShiftY;
                        CY2 +=          TValues.ShiftY;
                        currZ +=        TValues.ShiftZ;
                        currZnext +=    TValues.ShiftZ;
                        CZ2 +=          TValues.ShiftZ;
                        for (int j=0; TJumps[j].Shape; j++)
                                {
                                if (ABS(TJumps[j].ScaleX) > BY_ZERO)
                                        {
                                        currX = currX*TJumps[j].ScaleX;
                                        currXnext = currXnext*TJumps[j].ScaleX;
                                        CX2 = CX2*TJumps[j].ScaleX;
                                        }
                                if (ABS(TJumps[j].ScaleY) > BY_ZERO)
                                        {
                                        currY = currY*TJumps[j].ScaleY;
                                        currYnext = currYnext*TJumps[j].ScaleY;
                                        CY2 = CY2*TJumps[j].ScaleY;
                                        }
                                if (ABS(TJumps[j].ScaleZ) > BY_ZERO)
                                        {
                                        currZ = currZ*TJumps[j].ScaleZ;
                                        currZnext = currZnext*TJumps[j].ScaleZ;
                                        CZ2 = CZ2*TJumps[j].ScaleZ;
                                        }
                                Rotate_Vertex(&currX,&currZ,-TJumps[j].RotateXZ);
                                Rotate_Vertex(&currXnext,&currZnext,-TJumps[j].RotateXZ);
                                Rotate_Vertex(&CX2,&CZ2,-TJumps[j].RotateXZ);
                                Rotate_Vertex(&currY,&currZ,-TJumps[j].RotateYZ);
                                Rotate_Vertex(&currYnext,&currZnext,-TJumps[j].RotateYZ);
                                Rotate_Vertex(&CY2,&CZ2,-TJumps[j].RotateYZ);
                                Rotate_Vertex(&currX,&currY,TJumps[j].RotateXY);
                                Rotate_Vertex(&currXnext,&currYnext,TJumps[j].RotateXY);
                                Rotate_Vertex(&CX2,&CY2,TJumps[j].RotateXY);
                                currX +=        TJumps[j].ShiftX;
                                currXnext +=    TJumps[j].ShiftX;
                                CX2 +=          TJumps[j].ShiftX;
                                currY +=        TJumps[j].ShiftY;
                                currYnext +=    TJumps[j].ShiftY;
                                CY2 +=          TJumps[j].ShiftY;
                                currZ +=        TJumps[j].ShiftZ;
                                currZnext +=    TJumps[j].ShiftZ;
                                CZ2 +=          TJumps[j].ShiftZ;
                                }
                        currX +=        centroid__X;
                        currXnext +=    centroid__X;
                        CX2 +=          centroid__X;
                        currY +=        centroid__Y;
                        currYnext +=    centroid__Y;
                        CY2 +=          centroid__Y;
                        if (!SIDE)
                                {
                                currZ +=        BoardThick;
                                currZnext +=    BoardThick;
                                CZ2 +=          BoardThick;
                                }
                        else    {
                                Rotate_Vertex(&currX,&currZ,180);
                                Rotate_Vertex(&currXnext,&currZnext,180);
                                Rotate_Vertex(&CX2,&CZ2,180);
                                }
                        if (_3d)
                                {
                                Rotate3d(&currX,&currY,&currZ,&currXnext,&currYnext,&currZnext,&CX2,&CY2,&CZ2);
                                }
                        if (Form3->RadioButton4->Checked && CANVAS_TO_FILE) W_LINE_BLK(sv1,sv2,sv3,currX,currY,currZ, CLR, LAYER__3D);
                        //
                        if (Form3->RadioButton4->Checked && CANVAS_TO_FILE) W_LINE_BLK(currX,currY,currZ,currXnext,currYnext,currZnext, CLR, LAYER__3D);
                        else if (CANVAS_TO_FILE)
                                {
                                W_SOLID_BLK(   sv1,sv2,sv3,sv4,sv5,sv6,
                                        currX,currY,currZ,currXnext,currYnext,currZnext , CLR, LAYER__3D);
                                if ((r+2)%2)
                                        {
                                        W_SOLID_BLK(    sv1back,sv2back,sv3back,CX1,CY1,CZ1,
                                                sv1,sv2,sv3,sv4,sv5,sv6, CLR, LAYER__3D);
                                        W_SOLID_BLK(    sv4back,sv5back,sv6back,CX2,CY2,CZ2,
                                                currX,currY,currZ,currXnext,currYnext,currZnext, CLR, LAYER__3D);
                                        }
                                }
                        else    {
                                FACES[fcs] = Object;
                                FACES[fcs+1] = sv1;
                                FACES[fcs+2] = sv2;
                                FACES[fcs+3] = sv3;
                                FACES[fcs+4] = sv4;
                                FACES[fcs+5] = sv5;
                                FACES[fcs+6] = sv6;
                                FACES[fcs+7] = currXnext;
                                FACES[fcs+8] = currYnext;
                                FACES[fcs+9] = currZnext;
                                FACES[fcs+10] = currX;
                                FACES[fcs+11] = currY;
                                FACES[fcs+12] = currZ;
                                fcs = fcs + 13;
                                if ((r+2)%2)
                                        {
                                       FACES[fcs] = Object;
                                       FACES[fcs+1] = sv1back;
                                       FACES[fcs+2] = sv2back;
                                       FACES[fcs+3] = sv3back;
                                       FACES[fcs+4] = CX1;
                                       FACES[fcs+5] = CY1;
                                       FACES[fcs+6] = CZ1;
                                       FACES[fcs+7] = sv4;
                                       FACES[fcs+8] = sv5;
                                       FACES[fcs+9] = sv6;
                                       FACES[fcs+10] = sv1;
                                       FACES[fcs+11] = sv2;
                                       FACES[fcs+12] = sv3;
                                       fcs = fcs + 13;
                                       FACES[fcs] = Object;
                                       FACES[fcs+1] = sv4back;
                                       FACES[fcs+2] = sv5back;
                                       FACES[fcs+3] = sv6back;
                                       FACES[fcs+4] = CX2;
                                       FACES[fcs+5] = CY2;
                                       FACES[fcs+6] = CZ2;
                                       FACES[fcs+7] = currXnext;
                                       FACES[fcs+8] = currYnext;
                                       FACES[fcs+9] = currZnext;
                                       FACES[fcs+10] = currX;
                                       FACES[fcs+11] = currY;
                                       FACES[fcs+12] = currZ;
                                       fcs = fcs + 13;
                                       (*SELRECT).Left = MIN3(sv1back, sv4back, (*SELRECT).Left );
                                       (*SELRECT).Right = MAX3(sv1back, sv4back, (*SELRECT).Right );
                                       (*SELRECT).Bottom = MIN3(sv2back, sv5back, (*SELRECT).Bottom );
                                       (*SELRECT).Top = MAX3(sv2back, sv5back, (*SELRECT).Top );
                                       (*SELRECT)._Low = MIN3(sv3back, sv6back, (*SELRECT)._Low );
                                       (*SELRECT)._High = MAX3(sv3back, sv6back, (*SELRECT)._High );
                                       }
                                if (fcs > MAX_FACES_AND_LINES) return WARNING_OF_MEMORY;
                                (*SELRECT).Left = MIN4(sv1, sv4, currXnext, (*SELRECT).Left );
                                (*SELRECT).Left = MIN(currX, (*SELRECT).Left );
                                (*SELRECT).Right = MAX4(sv1, sv4, currXnext, (*SELRECT).Right );
                                (*SELRECT).Right = MAX(currX, (*SELRECT).Right );
                                (*SELRECT).Bottom = MIN4(sv2, sv5, currYnext, (*SELRECT).Bottom );
                                (*SELRECT).Bottom = MIN(currY, (*SELRECT).Bottom );
                                (*SELRECT).Top = MAX4(sv2, sv5, currYnext, (*SELRECT).Top );
                                (*SELRECT).Top = MAX(currY, (*SELRECT).Top );
                                (*SELRECT)._Low = MIN4(sv3, sv6, currZnext, (*SELRECT)._Low );
                                (*SELRECT)._Low = MIN(currZ, (*SELRECT)._Low );
                                (*SELRECT)._High = MAX4(sv3, sv6, currZnext, (*SELRECT)._High );
                                (*SELRECT)._High = MAX(currZ, (*SELRECT)._High );
                                }
                        sv4 = currX;
                        sv5 = currY;
                        sv6 = currZ;
                        }
                }
        //  rect
        else if (TValues.Shape == SH__RECT)
                {
                float p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12;
                float p_1,p_2,p_3,p_4,p_5,p_6,p_7,p_8,p_9,p_10,p_11,p_12;
                for (int f=0; f<3; f++)
                        {
                        switch(f)
                                {
                                case 0: p1 =  + TValues.SizeX/2;
                                        p2 =  - TValues.SizeY/2;
                                        p3 = 0;
                                        p4 =  - TValues.SizeX/2;
                                        p5 =  - TValues.SizeY/2;
                                        p6 = 0;
                                        p7 =  + TValues.SizeX/2;
                                        p8 =  + TValues.SizeY/2;
                                        p9 = 0;
                                        p10 =  - TValues.SizeX/2;
                                        p11 =  + TValues.SizeY/2;
                                        p12 = 0;
                                        break;
                                case 1: p1 =  + TValues.SizeX/2;
                                        p2 =  - TValues.SizeY/2;
                                        p3 = 0;
                                        p4 =  - TValues.SizeX/2;
                                        p5 =  - TValues.SizeY/2;
                                        p6 = 0;
                                        p7 =  + TValues.SizeX/2;
                                        p8 =  - TValues.SizeY/2;
                                        p9 = TValues.SizeZ;
                                        p10 =  - TValues.SizeX/2;
                                        p11 =  - TValues.SizeY/2;
                                        p12 = TValues.SizeZ;
                                        break;
                                case 2: p1 =  - TValues.SizeX/2;
                                        p2 =  - TValues.SizeY/2;
                                        p3 = 0;
                                        p4 =  - TValues.SizeX/2;
                                        p5 =  + TValues.SizeY/2;
                                        p6 = 0;
                                        p7 =  - TValues.SizeX/2;
                                        p8 =  - TValues.SizeY/2;
                                        p9 = TValues.SizeZ;
                                        p10 =  - TValues.SizeX/2;
                                        p11 =  + TValues.SizeY/2;
                                        p12 = TValues.SizeZ;
                                        break;
                                }
                        p_1 =  p1;
                        p_2 =  p2;
                        p_3 =  p3;
                        p_4 =  p4;
                        p_5 =  p5;
                        p_6 =  p6;
                        p_7 =  p7;
                        p_8 =  p8;
                        p_9 =  p9;
                        p_10 =  p10;
                        p_11 =  p11;
                        p_12 =  p12;
                        for (int g=0; g<(Count+1); g++)
                                {
                                if (f == 0)
                                        {
                                        p_1 =  p1;
                                        p_2 =  p2;
                                        p_3 = p3 + (TValues.SizeZ/(float)Count)*g;
                                        p_4 =  p4;
                                        p_5 =  p5;
                                        p_6 = p6 + (TValues.SizeZ/(float)Count)*g;
                                        p_7 =  p7;
                                        p_8 =  p8;
                                        p_9 = p9 + (TValues.SizeZ/(float)Count)*g;
                                        p_10 = p10;
                                        p_11 = p11;
                                        p_12 = p12 + (TValues.SizeZ/(float)Count)*g;
                                        }
                                else if (f == 1)
                                        {
                                        p_1 =  p1;
                                        p_2 =  p2 + TValues.SizeY/(float)Count*g;
                                        p_3 =  p3;
                                        p_4 =  p4;
                                        p_5 =  p5 + TValues.SizeY/(float)Count*g;
                                        p_6 =  p6;
                                        p_7 =  p7;
                                        p_8 =  p8 + TValues.SizeY/(float)Count*g;
                                        p_9 =  p9;
                                        p_10 = p10;
                                        p_11 = p11 + TValues.SizeY/(float)Count*g;
                                        p_12 = p12;
                                        }
                                else if (f == 2)
                                        {
                                        p_1 = p1 + (TValues.SizeX/(float)Count)*g;
                                        p_2 =  p2;
                                        p_3 =  p3;
                                        p_4 = p4 + (TValues.SizeX/(float)Count)*g;
                                        p_5 =  p5;
                                        p_6 =  p6;
                                        p_7 = p7 + (TValues.SizeX/(float)Count)*g;
                                        p_8 =  p8;
                                        p_9 =  p9;
                                        p_10 = p10 + (TValues.SizeX/(float)Count)*g;
                                        p_11 = p11;
                                        p_12 = p12;
                                        }
                                Rotate_Vertex(&p_1,&p_3,-TValues.RotateXZ);
                                Rotate_Vertex(&p_4,&p_6,-TValues.RotateXZ);
                                Rotate_Vertex(&p_7,&p_9,-TValues.RotateXZ);
                                Rotate_Vertex(&p_10,&p_12,-TValues.RotateXZ);
                                Rotate_Vertex(&p_2,&p_3,-TValues.RotateYZ);
                                Rotate_Vertex(&p_5,&p_6,-TValues.RotateYZ);
                                Rotate_Vertex(&p_8,&p_9,-TValues.RotateYZ);
                                Rotate_Vertex(&p_11,&p_12,-TValues.RotateYZ);
                                Rotate_Vertex(&p_1,&p_2,TValues.RotateXY);
                                Rotate_Vertex(&p_4,&p_5,TValues.RotateXY);
                                Rotate_Vertex(&p_7,&p_8,TValues.RotateXY);
                                Rotate_Vertex(&p_10,&p_11,TValues.RotateXY);
                                p_1 += TValues.ShiftX;
                                p_2 += TValues.ShiftY;
                                p_3 += TValues.ShiftZ;
                                p_4 += TValues.ShiftX;
                                p_5 += TValues.ShiftY;
                                p_6 += TValues.ShiftZ;
                                p_7 += TValues.ShiftX;
                                p_8 += TValues.ShiftY;
                                p_9 += TValues.ShiftZ;
                                p_10 += TValues.ShiftX;
                                p_11 += TValues.ShiftY;
                                p_12 += TValues.ShiftZ;
                                for (int j=0; TJumps[j].Shape; j++)
                                        {
                                        if (ABS(TJumps[j].ScaleX) > BY_ZERO)
                                                {
                                                p_1 = p_1*TJumps[j].ScaleX;
                                                p_4 = p_4*TJumps[j].ScaleX;
                                                p_7 = p_7*TJumps[j].ScaleX;
                                                p_10 = p_10*TJumps[j].ScaleX;
                                                }
                                        if (ABS(TJumps[j].ScaleY) > BY_ZERO)
                                                {
                                                p_2 = p_2*TJumps[j].ScaleY;
                                                p_5 = p_5*TJumps[j].ScaleY;
                                                p_8 = p_8*TJumps[j].ScaleY;
                                                p_11 = p_11*TJumps[j].ScaleY;
                                                }
                                        if (ABS(TJumps[j].ScaleZ) > BY_ZERO)
                                                {
                                                p_3 = p_3*TJumps[j].ScaleZ;
                                                p_6 = p_6*TJumps[j].ScaleZ;
                                                p_9 = p_9*TJumps[j].ScaleZ;
                                                p_12 = p_12*TJumps[j].ScaleZ;
                                                }
                                        Rotate_Vertex(&p_1,&p_3,-TJumps[j].RotateXZ);
                                        Rotate_Vertex(&p_4,&p_6,-TJumps[j].RotateXZ);
                                        Rotate_Vertex(&p_7,&p_9,-TJumps[j].RotateXZ);
                                        Rotate_Vertex(&p_10,&p_12,-TJumps[j].RotateXZ);
                                        Rotate_Vertex(&p_2,&p_3,-TJumps[j].RotateYZ);
                                        Rotate_Vertex(&p_5,&p_6,-TJumps[j].RotateYZ);
                                        Rotate_Vertex(&p_8,&p_9,-TJumps[j].RotateYZ);
                                        Rotate_Vertex(&p_11,&p_12,-TJumps[j].RotateYZ);
                                        Rotate_Vertex(&p_1,&p_2,TJumps[j].RotateXY);
                                        Rotate_Vertex(&p_4,&p_5,TJumps[j].RotateXY);
                                        Rotate_Vertex(&p_7,&p_8,TJumps[j].RotateXY);
                                        Rotate_Vertex(&p_10,&p_11,TJumps[j].RotateXY);
                                        p_1 += TJumps[j].ShiftX;
                                        p_2 += TJumps[j].ShiftY;
                                        p_3 += TJumps[j].ShiftZ;
                                        p_4 += TJumps[j].ShiftX;
                                        p_5 += TJumps[j].ShiftY;
                                        p_6 += TJumps[j].ShiftZ;
                                        p_7 += TJumps[j].ShiftX;
                                        p_8 += TJumps[j].ShiftY;
                                        p_9 += TJumps[j].ShiftZ;
                                        p_10 += TJumps[j].ShiftX;
                                        p_11 += TJumps[j].ShiftY;
                                        p_12 += TJumps[j].ShiftZ;
                                        }
                                p_1 +=          centroid__X;
                                p_4 +=          centroid__X;
                                p_7 +=          centroid__X;
                                p_10 +=         centroid__X;
                                p_2 +=          centroid__Y;
                                p_5 +=          centroid__Y;
                                p_8 +=          centroid__Y;
                                p_11 +=         centroid__Y;
                                if (!SIDE)
                                        {
                                        p_3 += BoardThick;
                                        p_6 += BoardThick;
                                        p_9 += BoardThick;
                                        p_12 += BoardThick;
                                        }
                                else    {
                                        Rotate_Vertex(&p_1,&p_3,180);
                                        Rotate_Vertex(&p_4,&p_6,180);
                                        Rotate_Vertex(&p_7,&p_9,180);
                                        Rotate_Vertex(&p_10,&p_12,180);
                                        }
                                if (_3d)
                                        {
                                        Rotate3d(&p_1,&p_2,&p_3,&p_4,&p_5,&p_6,&p_7,&p_8,&p_9,&p_10,&p_11,&p_12);
                                        }
                                if (Form3->RadioButton4->Checked && CANVAS_TO_FILE)
                                        {
                                        W_LINE_BLK(p_1,p_2,p_3,p_4,p_5,p_6,CLR,LAYER__3D);
                                        W_LINE_BLK(p_7,p_8,p_9,p_10,p_11,p_12,CLR,LAYER__3D);
                                        W_LINE_BLK(p_1,p_2,p_3,p_7, p_8, p_9, CLR,LAYER__3D);
                                        W_LINE_BLK(p_4,p_5,p_6,p_10,p_11,p_12,CLR,LAYER__3D);
                                        }
                                else if (CANVAS_TO_FILE)   W_SOLID_BLK(       p_1,p_2,p_3,p_4,p_5,p_6,
                                                                        p_7,p_8,p_9,p_10,p_11,p_12,CLR,LAYER__3D);
                                else    {
                                        FACES[fcs] = Object;
                                        FACES[fcs+1] = p_1;
                                        FACES[fcs+2] = p_2;
                                        FACES[fcs+3] = p_3;
                                        FACES[fcs+4] = p_4;
                                        FACES[fcs+5] = p_5;
                                        FACES[fcs+6] = p_6;
                                        FACES[fcs+7] = p_10;
                                        FACES[fcs+8] = p_11;
                                        FACES[fcs+9] = p_12;
                                        FACES[fcs+10] = p_7;
                                        FACES[fcs+11] = p_8;
                                        FACES[fcs+12] = p_9;
                                        fcs = fcs + 13;
                                        if (fcs > MAX_FACES_AND_LINES) return WARNING_OF_MEMORY;
                                        (*SELRECT).Left = MIN4(p_1, p_4, p_7, (*SELRECT).Left );
                                        (*SELRECT).Left = MIN(p_10, (*SELRECT).Left );
                                        (*SELRECT).Right = MAX4(p_1, p_4, p_7, (*SELRECT).Right );
                                        (*SELRECT).Right = MAX(p_10, (*SELRECT).Right );
                                        (*SELRECT).Bottom = MIN4(p_2, p_5, p_8, (*SELRECT).Bottom );
                                        (*SELRECT).Bottom = MIN(p_11, (*SELRECT).Bottom );
                                        (*SELRECT).Top = MAX4(p_2, p_5, p_8, (*SELRECT).Top );
                                        (*SELRECT).Top = MAX(p_11, (*SELRECT).Top );
                                        (*SELRECT)._Low = MIN4(p_3, p_6, p_9, (*SELRECT)._Low );
                                        (*SELRECT)._Low = MIN(p_12, (*SELRECT)._Low );
                                        (*SELRECT)._High = MAX4(p_3, p_6, p_9, (*SELRECT)._High );
                                        (*SELRECT)._High = MAX(p_12, (*SELRECT)._High );
                                        }
                                }
                        }
                }
        else if (TValues.Shape == SH__SILK /*&& TJumps[0].Shape == 0*/)
                {
                if (!SIDE)
                        {
                        if(SILK_TOP(N_STR, ROT, TValues, Object, SELRECT, _3d) == WARNING_OF_MEMORY) return WARNING_OF_MEMORY;
                        }
                else    {
                        if(SILK_BOT(N_STR, ROT, TValues, Object, SELRECT) == WARNING_OF_MEMORY) return WARNING_OF_MEMORY;
                        }
                }
        else if (TValues.Shape == SH__ARC)
                {
                //arc
                float p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12;
                float p_1,p_2,p_3,p_4,p_5,p_6,p_7,p_8,p_9,p_10,p_11,p_12;
                float dX = TValues.SizeX - TValues.SizeY;
                float dY = TValues.SizeY - TValues.SizeX;
                if (dX < 0) dX = 0;
                if (dY < 0) dY = 0;
                p1 = TValues.SizeX - dX;
                p2 = 0;
                p3 = 0;
                p4 = TValues.SizeX - dX;
                p5 = 0;
                p6 = TValues.SizeZ;
                p7 = TValues.SizeX - dX;
                p8 = 0;
                p9 = 0;
                p10 = TValues.SizeX - dX;
                p11 = 0;
                p12 = TValues.SizeZ;
                Rotate_Vertex(&p7,&p8,30);
                Rotate_Vertex(&p10,&p11,30);
                for (int t=0; t<3; t++)
                        {
                        p_1 = p1;
                        p_2 = p2;
                        p_3 = p3;
                        p_4 = p4;
                        p_5 = p5;
                        p_6 = p6;
                        p_7 = p7;
                        p_8 = p8;
                        p_9 = p9;
                        p_10 =p10;
                        p_11 =p11;
                        p_12 =p12;
                        Rotate_Vertex(&p_1,&p_2,TValues.RotateXY);
                        Rotate_Vertex(&p_4,&p_5,TValues.RotateXY);
                        Rotate_Vertex(&p_7,&p_8,TValues.RotateXY);
                        Rotate_Vertex(&p_10,&p_11,TValues.RotateXY);
                        Rotate_Vertex(&p_1,&p_3,-TValues.RotateXZ);
                        Rotate_Vertex(&p_4,&p_6,-TValues.RotateXZ);
                        Rotate_Vertex(&p_7,&p_9,-TValues.RotateXZ);
                        Rotate_Vertex(&p_10,&p_12,-TValues.RotateXZ);
                        Rotate_Vertex(&p_2,&p_3,-TValues.RotateYZ);
                        Rotate_Vertex(&p_5,&p_6,-TValues.RotateYZ);
                        Rotate_Vertex(&p_8,&p_9,-TValues.RotateYZ);
                        Rotate_Vertex(&p_11,&p_12,-TValues.RotateYZ);
                        p_1 += TValues.ShiftX;
                        p_2 += TValues.ShiftY;
                        p_3 += TValues.ShiftZ;
                        p_4 += TValues.ShiftX;
                        p_5 += TValues.ShiftY;
                        p_6 += TValues.ShiftZ;
                        p_7 += TValues.ShiftX;
                        p_8 += TValues.ShiftY;
                        p_9 += TValues.ShiftZ;
                        p_10 += TValues.ShiftX;
                        p_11 += TValues.ShiftY;
                        p_12 += TValues.ShiftZ;
                        for (int j=0; TJumps[j].Shape; j++)
                                {
                                if (ABS(TJumps[j].ScaleX) > BY_ZERO)
                                        {
                                        p_1 = p_1*TJumps[j].ScaleX;
                                        p_4 = p_4*TJumps[j].ScaleX;
                                        p_7 = p_7*TJumps[j].ScaleX;
                                        p_10 = p_10*TJumps[j].ScaleX;
                                        }
                                if (ABS(TJumps[j].ScaleY) > BY_ZERO)
                                        {
                                        p_2 = p_2*TJumps[j].ScaleY;
                                        p_5 = p_5*TJumps[j].ScaleY;
                                        p_8 = p_8*TJumps[j].ScaleY;
                                        p_11 = p_11*TJumps[j].ScaleY;
                                        }
                                if (ABS(TJumps[j].ScaleZ) > BY_ZERO)
                                        {
                                        p_3 = p_3*TJumps[j].ScaleZ;
                                        p_6 = p_6*TJumps[j].ScaleZ;
                                        p_9 = p_9*TJumps[j].ScaleZ;
                                        p_12 = p_12*TJumps[j].ScaleZ;
                                        }
                                Rotate_Vertex(&p_1,&p_3,-TJumps[j].RotateXZ);
                                Rotate_Vertex(&p_4,&p_6,-TJumps[j].RotateXZ);
                                Rotate_Vertex(&p_7,&p_9,-TJumps[j].RotateXZ);
                                Rotate_Vertex(&p_10,&p_12,-TJumps[j].RotateXZ);
                                Rotate_Vertex(&p_2,&p_3,-TJumps[j].RotateYZ);
                                Rotate_Vertex(&p_5,&p_6,-TJumps[j].RotateYZ);
                                Rotate_Vertex(&p_8,&p_9,-TJumps[j].RotateYZ);
                                Rotate_Vertex(&p_11,&p_12,-TJumps[j].RotateYZ);
                                Rotate_Vertex(&p_1,&p_2,TJumps[j].RotateXY);
                                Rotate_Vertex(&p_4,&p_5,TJumps[j].RotateXY);
                                Rotate_Vertex(&p_7,&p_8,TJumps[j].RotateXY);
                                Rotate_Vertex(&p_10,&p_11,TJumps[j].RotateXY);
                                p_1 += TJumps[j].ShiftX;
                                p_2 += TJumps[j].ShiftY;
                                p_3 += TJumps[j].ShiftZ;
                                p_4 += TJumps[j].ShiftX;
                                p_5 += TJumps[j].ShiftY;
                                p_6 += TJumps[j].ShiftZ;
                                p_7 += TJumps[j].ShiftX;
                                p_8 += TJumps[j].ShiftY;
                                p_9 += TJumps[j].ShiftZ;
                                p_10 += TJumps[j].ShiftX;
                                p_11 += TJumps[j].ShiftY;
                                p_12 += TJumps[j].ShiftZ;
                                }
                        p_1 +=          centroid__X;
                        p_4 +=          centroid__X;
                        p_7 +=          centroid__X;
                        p_10 +=         centroid__X;
                        p_2 +=          centroid__Y;
                        p_5 +=          centroid__Y;
                        p_8 +=          centroid__Y;
                        p_11 +=         centroid__Y;
                        if (!SIDE)
                                {
                                p_3 += BoardThick;
                                p_6 += BoardThick;
                                p_9 += BoardThick;
                                p_12 += BoardThick;
                                }
                        else    {
                                Rotate_Vertex(&p_1,&p_3,180);
                                Rotate_Vertex(&p_4,&p_6,180);
                                Rotate_Vertex(&p_7,&p_9,180);
                                Rotate_Vertex(&p_10,&p_12,180);
                                }
                        if (_3d)
                                {
                                Rotate3d(&p_1,&p_2,&p_3,&p_4,&p_5,&p_6,&p_7,&p_8,&p_9,&p_10,&p_11,&p_12);
                                }
                        if (Form3->RadioButton4->Checked && CANVAS_TO_FILE)
                                {
                                W_LINE_BLK(p_1,p_2,p_3,p_4,p_5,p_6,CLR,LAYER__3D);
                                W_LINE_BLK(p_7,p_8,p_9,p_10,p_11,p_12,CLR,LAYER__3D);
                                W_LINE_BLK(p_1,p_2,p_3,p_7, p_8, p_9, CLR,LAYER__3D);
                                W_LINE_BLK(p_4,p_5,p_6,p_10,p_11,p_12,CLR,LAYER__3D);
                                }
                        else if (CANVAS_TO_FILE)   W_SOLID_BLK(       p_1,p_2,p_3,p_4,p_5,p_6,
                                                                p_7,p_8,p_9,p_10,p_11,p_12,CLR,LAYER__3D);
                        else    {
                                FACES[fcs] = Object;
                                FACES[fcs+1] = p_1;
                                FACES[fcs+2] = p_2;
                                FACES[fcs+3] = p_3;
                                FACES[fcs+4] = p_4;
                                FACES[fcs+5] = p_5;
                                FACES[fcs+6] = p_6;
                                FACES[fcs+7] = p_10;
                                FACES[fcs+8] = p_11;
                                FACES[fcs+9] = p_12;
                                FACES[fcs+10] = p_7;
                                FACES[fcs+11] = p_8;
                                FACES[fcs+12] = p_9;
                                fcs = fcs + 13;
                                if (fcs > MAX_FACES_AND_LINES) return WARNING_OF_MEMORY;
                                (*SELRECT).Left = MIN4(p_1, p_4, p_7, (*SELRECT).Left );
                                (*SELRECT).Left = MIN(p_10, (*SELRECT).Left );
                                (*SELRECT).Right = MAX4(p_1, p_4, p_7, (*SELRECT).Right );
                                (*SELRECT).Right = MAX(p_10, (*SELRECT).Right );
                                (*SELRECT).Bottom = MIN4(p_2, p_5, p_8, (*SELRECT).Bottom );
                                (*SELRECT).Bottom = MIN(p_11, (*SELRECT).Bottom );
                                (*SELRECT).Top = MAX4(p_2, p_5, p_8, (*SELRECT).Top );
                                (*SELRECT).Top = MAX(p_11, (*SELRECT).Top );
                                (*SELRECT)._Low = MIN4(p_3, p_6, p_9, (*SELRECT)._Low );
                                (*SELRECT)._Low = MIN(p_12, (*SELRECT)._Low );
                                (*SELRECT)._High = MAX4(p_3, p_6, p_9, (*SELRECT)._High );
                                (*SELRECT)._High = MAX(p_12, (*SELRECT)._High );
                                }
                        Rotate_Vertex(&p1,&p2,30);
                        Rotate_Vertex(&p4,&p5,30);
                        Rotate_Vertex(&p7,&p8,30);
                        Rotate_Vertex(&p10,&p11,30);
                        }
                if (dX > 0)
                        {
                        p_1 = 0;
                        p_2 = TValues.SizeY;
                        p_3 = 0;
                        p_4 = -dX;
                        p_5 = TValues.SizeY;
                        p_6 = 0;
                        p_7 = 0;
                        p_8 = TValues.SizeY;
                        p_9 = TValues.SizeZ;
                        p_10 = -dX;
                        p_11 = TValues.SizeY;
                        p_12 = TValues.SizeZ;
                        Rotate_Vertex(&p_1,&p_2,TValues.RotateXY);
                        Rotate_Vertex(&p_4,&p_5,TValues.RotateXY);
                        Rotate_Vertex(&p_7,&p_8,TValues.RotateXY);
                        Rotate_Vertex(&p_10,&p_11,TValues.RotateXY);
                        Rotate_Vertex(&p_1,&p_3,-TValues.RotateXZ);
                        Rotate_Vertex(&p_4,&p_6,-TValues.RotateXZ);
                        Rotate_Vertex(&p_7,&p_9,-TValues.RotateXZ);
                        Rotate_Vertex(&p_10,&p_12,-TValues.RotateXZ);
                        Rotate_Vertex(&p_2,&p_3,-TValues.RotateYZ);
                        Rotate_Vertex(&p_5,&p_6,-TValues.RotateYZ);
                        Rotate_Vertex(&p_8,&p_9,-TValues.RotateYZ);
                        Rotate_Vertex(&p_11,&p_12,-TValues.RotateYZ);
                        p_1 += TValues.ShiftX;
                        p_2 += TValues.ShiftY;
                        p_3 += TValues.ShiftZ;
                        p_4 += TValues.ShiftX;
                        p_5 += TValues.ShiftY;
                        p_6 += TValues.ShiftZ;
                        p_7 += TValues.ShiftX;
                        p_8 += TValues.ShiftY;
                        p_9 += TValues.ShiftZ;
                        p_10 += TValues.ShiftX;
                        p_11 += TValues.ShiftY;
                        p_12 += TValues.ShiftZ;
                        for (int j=0; TJumps[j].Shape; j++)
                                {
                                if (ABS(TJumps[j].ScaleX) > BY_ZERO)
                                        {
                                        p_1 = p_1*TJumps[j].ScaleX;
                                        p_4 = p_4*TJumps[j].ScaleX;
                                        p_7 = p_7*TJumps[j].ScaleX;
                                        p_10 = p_10*TJumps[j].ScaleX;
                                        }
                                if (ABS(TJumps[j].ScaleY) > BY_ZERO)
                                        {
                                        p_2 = p_2*TJumps[j].ScaleY;
                                        p_5 = p_5*TJumps[j].ScaleY;
                                        p_8 = p_8*TJumps[j].ScaleY;
                                        p_11 = p_11*TJumps[j].ScaleY;
                                        }
                                if (ABS(TJumps[j].ScaleZ) > BY_ZERO)
                                        {
                                        p_3 = p_3*TJumps[j].ScaleZ;
                                        p_6 = p_6*TJumps[j].ScaleZ;
                                        p_9 = p_9*TJumps[j].ScaleZ;
                                        p_12 = p_12*TJumps[j].ScaleZ;
                                        }
                                Rotate_Vertex(&p_1,&p_3,-TJumps[j].RotateXZ);
                                Rotate_Vertex(&p_4,&p_6,-TJumps[j].RotateXZ);
                                Rotate_Vertex(&p_7,&p_9,-TJumps[j].RotateXZ);
                                Rotate_Vertex(&p_10,&p_12,-TJumps[j].RotateXZ);
                                Rotate_Vertex(&p_2,&p_3,-TJumps[j].RotateYZ);
                                Rotate_Vertex(&p_5,&p_6,-TJumps[j].RotateYZ);
                                Rotate_Vertex(&p_8,&p_9,-TJumps[j].RotateYZ);
                                Rotate_Vertex(&p_11,&p_12,-TJumps[j].RotateYZ);
                                Rotate_Vertex(&p_1,&p_2,TJumps[j].RotateXY);
                                Rotate_Vertex(&p_4,&p_5,TJumps[j].RotateXY);
                                Rotate_Vertex(&p_7,&p_8,TJumps[j].RotateXY);
                                Rotate_Vertex(&p_10,&p_11,TJumps[j].RotateXY);
                                p_1 += TJumps[j].ShiftX;
                                p_2 += TJumps[j].ShiftY;
                                p_3 += TJumps[j].ShiftZ;
                                p_4 += TJumps[j].ShiftX;
                                p_5 += TJumps[j].ShiftY;
                                p_6 += TJumps[j].ShiftZ;
                                p_7 += TJumps[j].ShiftX;
                                p_8 += TJumps[j].ShiftY;
                                p_9 += TJumps[j].ShiftZ;
                                p_10 += TJumps[j].ShiftX;
                                p_11 += TJumps[j].ShiftY;
                                p_12 += TJumps[j].ShiftZ;
                                }
                        p_1 +=          centroid__X;
                        p_4 +=          centroid__X;
                        p_7 +=          centroid__X;
                        p_10 +=         centroid__X;
                        p_2 +=          centroid__Y;
                        p_5 +=          centroid__Y;
                        p_8 +=          centroid__Y;
                        p_11 +=         centroid__Y;
                        if (!SIDE)
                                {
                                p_3 += BoardThick;
                                p_6 += BoardThick;
                                p_9 += BoardThick;
                                p_12 += BoardThick;
                                }
                        else    {
                                Rotate_Vertex(&p_1,&p_3,180);
                                Rotate_Vertex(&p_4,&p_6,180);
                                Rotate_Vertex(&p_7,&p_9,180);
                                Rotate_Vertex(&p_10,&p_12,180);
                                }
                        if (_3d)
                                {
                                Rotate3d(&p_1,&p_2,&p_3,&p_4,&p_5,&p_6,&p_7,&p_8,&p_9,&p_10,&p_11,&p_12);
                                }
                        if (Form3->RadioButton4->Checked && CANVAS_TO_FILE)
                                {
                                W_LINE_BLK(p_1,p_2,p_3,p_4,p_5,p_6,CLR,LAYER__3D);
                                W_LINE_BLK(p_7,p_8,p_9,p_10,p_11,p_12,CLR,LAYER__3D);
                                W_LINE_BLK(p_1,p_2,p_3,p_7, p_8, p_9, CLR,LAYER__3D);
                                W_LINE_BLK(p_4,p_5,p_6,p_10,p_11,p_12,CLR,LAYER__3D);
                                }
                        else if (CANVAS_TO_FILE)   W_SOLID_BLK(       p_1,p_2,p_3,p_4,p_5,p_6,
                                                                p_7,p_8,p_9,p_10,p_11,p_12,CLR,LAYER__3D);
                        else    {
                                FACES[fcs] = Object;
                                FACES[fcs+1] = p_1;
                                FACES[fcs+2] = p_2;
                                FACES[fcs+3] = p_3;
                                FACES[fcs+4] = p_4;
                                FACES[fcs+5] = p_5;
                                FACES[fcs+6] = p_6;
                                FACES[fcs+7] = p_10;
                                FACES[fcs+8] = p_11;
                                FACES[fcs+9] = p_12;
                                FACES[fcs+10] = p_7;
                                FACES[fcs+11] = p_8;
                                FACES[fcs+12] = p_9;
                                fcs = fcs + 13;
                                if (fcs > MAX_FACES_AND_LINES) return WARNING_OF_MEMORY;
                                (*SELRECT).Left = MIN4(p_1, p_4, p_7, (*SELRECT).Left );
                                (*SELRECT).Left = MIN(p_10, (*SELRECT).Left );
                                (*SELRECT).Right = MAX4(p_1, p_4, p_7, (*SELRECT).Right );
                                (*SELRECT).Right = MAX(p_10, (*SELRECT).Right );
                                (*SELRECT).Bottom = MIN4(p_2, p_5, p_8, (*SELRECT).Bottom );
                                (*SELRECT).Bottom = MIN(p_11, (*SELRECT).Bottom );
                                (*SELRECT).Top = MAX4(p_2, p_5, p_8, (*SELRECT).Top );
                                (*SELRECT).Top = MAX(p_11, (*SELRECT).Top );
                                (*SELRECT)._Low = MIN4(p_3, p_6, p_9, (*SELRECT)._Low );
                                (*SELRECT)._Low = MIN(p_12, (*SELRECT)._Low );
                                (*SELRECT)._High = MAX4(p_3, p_6, p_9, (*SELRECT)._High );
                                (*SELRECT)._High = MAX(p_12, (*SELRECT)._High );
                                }
                        }
                if (dY > 0)
                        {
                        p_1 = TValues.SizeX;
                        p_2 = 0;
                        p_3 = 0;
                        p_4 = TValues.SizeX;
                        p_5 = -dY;
                        p_6 = 0;
                        p_7 = TValues.SizeX;
                        p_8 = 0;
                        p_9 = TValues.SizeZ;
                        p_10 = TValues.SizeX;
                        p_11 = -dY;
                        p_12 = TValues.SizeZ;
                        Rotate_Vertex(&p_1,&p_2,TValues.RotateXY);
                        Rotate_Vertex(&p_4,&p_5,TValues.RotateXY);
                        Rotate_Vertex(&p_7,&p_8,TValues.RotateXY);
                        Rotate_Vertex(&p_10,&p_11,TValues.RotateXY);
                        Rotate_Vertex(&p_1,&p_3,-TValues.RotateXZ);
                        Rotate_Vertex(&p_4,&p_6,-TValues.RotateXZ);
                        Rotate_Vertex(&p_7,&p_9,-TValues.RotateXZ);
                        Rotate_Vertex(&p_10,&p_12,-TValues.RotateXZ);
                        Rotate_Vertex(&p_2,&p_3,-TValues.RotateYZ);
                        Rotate_Vertex(&p_5,&p_6,-TValues.RotateYZ);
                        Rotate_Vertex(&p_8,&p_9,-TValues.RotateYZ);
                        Rotate_Vertex(&p_11,&p_12,-TValues.RotateYZ);
                        p_1 += TValues.ShiftX;
                        p_2 += TValues.ShiftY;
                        p_3 += TValues.ShiftZ;
                        p_4 += TValues.ShiftX;
                        p_5 += TValues.ShiftY;
                        p_6 += TValues.ShiftZ;
                        p_7 += TValues.ShiftX;
                        p_8 += TValues.ShiftY;
                        p_9 += TValues.ShiftZ;
                        p_10 += TValues.ShiftX;
                        p_11 += TValues.ShiftY;
                        p_12 += TValues.ShiftZ;
                        for (int j=0; TJumps[j].Shape; j++)
                                {
                                if (ABS(TJumps[j].ScaleX) > BY_ZERO)
                                        {
                                        p_1 = p_1*TJumps[j].ScaleX;
                                        p_4 = p_4*TJumps[j].ScaleX;
                                        p_7 = p_7*TJumps[j].ScaleX;
                                        p_10 = p_10*TJumps[j].ScaleX;
                                        }
                                if (ABS(TJumps[j].ScaleY) > BY_ZERO)
                                        {
                                        p_2 = p_2*TJumps[j].ScaleY;
                                        p_5 = p_5*TJumps[j].ScaleY;
                                        p_8 = p_8*TJumps[j].ScaleY;
                                        p_11 = p_11*TJumps[j].ScaleY;
                                        }
                                if (ABS(TJumps[j].ScaleZ) > BY_ZERO)
                                        {
                                        p_3 = p_3*TJumps[j].ScaleZ;
                                        p_6 = p_6*TJumps[j].ScaleZ;
                                        p_9 = p_9*TJumps[j].ScaleZ;
                                        p_12 = p_12*TJumps[j].ScaleZ;
                                        }
                                Rotate_Vertex(&p_1,&p_3,-TJumps[j].RotateXZ);
                                Rotate_Vertex(&p_4,&p_6,-TJumps[j].RotateXZ);
                                Rotate_Vertex(&p_7,&p_9,-TJumps[j].RotateXZ);
                                Rotate_Vertex(&p_10,&p_12,-TJumps[j].RotateXZ);
                                Rotate_Vertex(&p_2,&p_3,-TJumps[j].RotateYZ);
                                Rotate_Vertex(&p_5,&p_6,-TJumps[j].RotateYZ);
                                Rotate_Vertex(&p_8,&p_9,-TJumps[j].RotateYZ);
                                Rotate_Vertex(&p_11,&p_12,-TJumps[j].RotateYZ);
                                Rotate_Vertex(&p_1,&p_2,TJumps[j].RotateXY);
                                Rotate_Vertex(&p_4,&p_5,TJumps[j].RotateXY);
                                Rotate_Vertex(&p_7,&p_8,TJumps[j].RotateXY);
                                Rotate_Vertex(&p_10,&p_11,TJumps[j].RotateXY);
                                p_1 += TJumps[j].ShiftX;
                                p_2 += TJumps[j].ShiftY;
                                p_3 += TJumps[j].ShiftZ;
                                p_4 += TJumps[j].ShiftX;
                                p_5 += TJumps[j].ShiftY;
                                p_6 += TJumps[j].ShiftZ;
                                p_7 += TJumps[j].ShiftX;
                                p_8 += TJumps[j].ShiftY;
                                p_9 += TJumps[j].ShiftZ;
                                p_10 += TJumps[j].ShiftX;
                                p_11 += TJumps[j].ShiftY;
                                p_12 += TJumps[j].ShiftZ;
                                }
                        p_1 +=          centroid__X;
                        p_4 +=          centroid__X;
                        p_7 +=          centroid__X;
                        p_10 +=         centroid__X;
                        p_2 +=          centroid__Y;
                        p_5 +=          centroid__Y;
                        p_8 +=          centroid__Y;
                        p_11 +=         centroid__Y;
                        if (!SIDE)
                                {
                                p_3 += BoardThick;
                                p_6 += BoardThick;
                                p_9 += BoardThick;
                                p_12 += BoardThick;
                                }
                        else    {
                                Rotate_Vertex(&p_1,&p_3,180);
                                Rotate_Vertex(&p_4,&p_6,180);
                                Rotate_Vertex(&p_7,&p_9,180);
                                Rotate_Vertex(&p_10,&p_12,180);
                                }
                        if (_3d)
                                {
                                Rotate3d(&p_1,&p_2,&p_3,&p_4,&p_5,&p_6,&p_7,&p_8,&p_9,&p_10,&p_11,&p_12);
                                }
                        if (Form3->RadioButton4->Checked && CANVAS_TO_FILE)
                                {
                                W_LINE_BLK(p_1,p_2,p_3,p_4,p_5,p_6,CLR,LAYER__3D);
                                W_LINE_BLK(p_7,p_8,p_9,p_10,p_11,p_12,CLR,LAYER__3D);
                                W_LINE_BLK(p_1,p_2,p_3,p_7, p_8, p_9, CLR,LAYER__3D);
                                W_LINE_BLK(p_4,p_5,p_6,p_10,p_11,p_12,CLR,LAYER__3D);
                                }
                        else if (CANVAS_TO_FILE)   W_SOLID_BLK(       p_1,p_2,p_3,p_4,p_5,p_6,
                                                                p_7,p_8,p_9,p_10,p_11,p_12,CLR,LAYER__3D);
                        else    {
                                FACES[fcs] = Object;
                                FACES[fcs+1] = p_1;
                                FACES[fcs+2] = p_2;
                                FACES[fcs+3] = p_3;
                                FACES[fcs+4] = p_4;
                                FACES[fcs+5] = p_5;
                                FACES[fcs+6] = p_6;
                                FACES[fcs+7] = p_10;
                                FACES[fcs+8] = p_11;
                                FACES[fcs+9] = p_12;
                                FACES[fcs+10] = p_7;
                                FACES[fcs+11] = p_8;
                                FACES[fcs+12] = p_9;
                                fcs = fcs + 13;
                                if (fcs > MAX_FACES_AND_LINES) return WARNING_OF_MEMORY;
                                (*SELRECT).Left = MIN4(p_1, p_4, p_7, (*SELRECT).Left );
                                (*SELRECT).Left = MIN(p_10, (*SELRECT).Left );
                                (*SELRECT).Right = MAX4(p_1, p_4, p_7, (*SELRECT).Right );
                                (*SELRECT).Right = MAX(p_10, (*SELRECT).Right );
                                (*SELRECT).Bottom = MIN4(p_2, p_5, p_8, (*SELRECT).Bottom );
                                (*SELRECT).Bottom = MIN(p_11, (*SELRECT).Bottom );
                                (*SELRECT).Top = MAX4(p_2, p_5, p_8, (*SELRECT).Top );
                                (*SELRECT).Top = MAX(p_11, (*SELRECT).Top );
                                (*SELRECT)._Low = MIN4(p_3, p_6, p_9, (*SELRECT)._Low );
                                (*SELRECT)._Low = MIN(p_12, (*SELRECT)._Low );
                                (*SELRECT)._High = MAX4(p_3, p_6, p_9, (*SELRECT)._High );
                                (*SELRECT)._High = MAX(p_12, (*SELRECT)._High );
                                }
                        }
                }
        else if (TValues.Shape == SH__PIN)
                {
                //pin
                float p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12;
                float p_1,p_2,p_3,p_4,p_5,p_6,p_7,p_8,p_9,p_10,p_11,p_12;
                float memTValuesSizeX = 0;
                TValues.SizeZ = ABS(TValues.SizeZ);
                TValues.SizeX = ABS(TValues.SizeX);
                TValues.SizeY = ABS(TValues.SizeY);
                if (TValues.SizeZ < TValues.SizeX)
                        {
                        memTValuesSizeX = TValues.SizeX;
                        TValues.SizeX = TValues.SizeZ;
                        }
                p1 = 0;
                p2 = -TValues.SizeY/2.0;
                p3 = -TValues.SizeX/2.0;
                p4 = 0;
                p5 = TValues.SizeY/2.0;
                p6 = -TValues.SizeX/2.0;
                p7 = 0;
                p8 = -TValues.SizeY/2.0;
                p9 = -TValues.SizeX/2.0;
                p10 = 0;
                p11 = TValues.SizeY/2.0;
                p12 = -TValues.SizeX/2.0;
                p_1 = p1;
                p_2 = p2;
                p_3 = p3;
                p_4 = p4;
                p_5 = p5;
                p_6 = p6;
                for (int q=0; q<5; q++)
                        {
                        if (q == 2)
                                {
                                Rotate_Vertex(&p7,&p9,90);
                                Rotate_Vertex(&p10,&p12,90);
                                }
                        else    {
                                Rotate_Vertex(&p7,&p9,45);
                                Rotate_Vertex(&p10,&p12,45);
                                }
                        p_7 = p7;
                        p_8 = p8;
                        p_9 = p9;
                        p_10 = p10;
                        p_11 = p11;
                        p_12 = p12;
                        if (q > 2)
                                {
                                p_1 +=  TValues.SizeX/2.0;
                                p_4 +=  TValues.SizeX/2.0;
                                p_7 +=  TValues.SizeX/2.0;
                                p_10 += TValues.SizeX/2.0;
                                p_3 +=  TValues.SizeZ - TValues.SizeX/2.0;
                                p_6 +=  TValues.SizeZ - TValues.SizeX/2.0;
                                p_9 +=  TValues.SizeZ - TValues.SizeX/2.0;
                                p_12 += TValues.SizeZ - TValues.SizeX/2.0;
                                }
                        if (q < 2)
                                {
                                p_1 -=  TValues.SizeX/2.0;
                                p_4 -=  TValues.SizeX/2.0;
                                p_7 -=  TValues.SizeX/2.0;
                                p_10 -= TValues.SizeX/2.0;
                                p_3 +=  TValues.SizeX/2.0;
                                p_6 +=  TValues.SizeX/2.0;
                                p_9 +=  TValues.SizeX/2.0;
                                p_12 += TValues.SizeX/2.0;
                                }
                        if (q == 2)
                                {
                                p_1 =   0;
                                p_2 =   -TValues.SizeY/2.0;
                                p_3 =   TValues.SizeX/2.0;
                                p_4 =   0;
                                p_5 =   TValues.SizeY/2.0;
                                p_6 =   TValues.SizeX/2.0;
                                p_7 =   0;
                                p_8 =   -TValues.SizeY/2.0;
                                p_9 =   TValues.SizeZ - TValues.SizeX/2.0;
                                p_10 =  0;
                                p_11 =  TValues.SizeY/2.0;
                                p_12 =  TValues.SizeZ - TValues.SizeX/2.0;
                                }
                        Rotate_Vertex(&p_1,&p_3,-TValues.RotateXZ);
                        Rotate_Vertex(&p_4,&p_6,-TValues.RotateXZ);
                        Rotate_Vertex(&p_7,&p_9,-TValues.RotateXZ);
                        Rotate_Vertex(&p_10,&p_12,-TValues.RotateXZ);
                        Rotate_Vertex(&p_2,&p_3,-TValues.RotateYZ);
                        Rotate_Vertex(&p_5,&p_6,-TValues.RotateYZ);
                        Rotate_Vertex(&p_8,&p_9,-TValues.RotateYZ);
                        Rotate_Vertex(&p_11,&p_12,-TValues.RotateYZ);
                        Rotate_Vertex(&p_1,&p_2,TValues.RotateXY);
                        Rotate_Vertex(&p_4,&p_5,TValues.RotateXY);
                        Rotate_Vertex(&p_7,&p_8,TValues.RotateXY);
                        Rotate_Vertex(&p_10,&p_11,TValues.RotateXY);
                        p_1 += TValues.ShiftX;
                        p_2 += TValues.ShiftY;
                        p_3 += TValues.ShiftZ;
                        p_4 += TValues.ShiftX;
                        p_5 += TValues.ShiftY;
                        p_6 += TValues.ShiftZ;
                        p_7 += TValues.ShiftX;
                        p_8 += TValues.ShiftY;
                        p_9 += TValues.ShiftZ;
                        p_10 += TValues.ShiftX;
                        p_11 += TValues.ShiftY;
                        p_12 += TValues.ShiftZ;
                        for (int j=0; TJumps[j].Shape; j++)
                                {
                                if (ABS(TJumps[j].ScaleX) > BY_ZERO)
                                        {
                                        p_1 = p_1*TJumps[j].ScaleX;
                                        p_4 = p_4*TJumps[j].ScaleX;
                                        p_7 = p_7*TJumps[j].ScaleX;
                                        p_10 = p_10*TJumps[j].ScaleX;
                                        }
                                if (ABS(TJumps[j].ScaleY) > BY_ZERO)
                                        {
                                        p_2 = p_2*TJumps[j].ScaleY;
                                        p_5 = p_5*TJumps[j].ScaleY;
                                        p_8 = p_8*TJumps[j].ScaleY;
                                        p_11 = p_11*TJumps[j].ScaleY;
                                        }
                                if (ABS(TJumps[j].ScaleZ) > BY_ZERO)
                                        {
                                        p_3 = p_3*TJumps[j].ScaleZ;
                                        p_6 = p_6*TJumps[j].ScaleZ;
                                        p_9 = p_9*TJumps[j].ScaleZ;
                                        p_12 = p_12*TJumps[j].ScaleZ;
                                        }
                                Rotate_Vertex(&p_1,&p_3,-TJumps[j].RotateXZ);
                                Rotate_Vertex(&p_4,&p_6,-TJumps[j].RotateXZ);
                                Rotate_Vertex(&p_7,&p_9,-TJumps[j].RotateXZ);
                                Rotate_Vertex(&p_10,&p_12,-TJumps[j].RotateXZ);
                                Rotate_Vertex(&p_2,&p_3,-TJumps[j].RotateYZ);
                                Rotate_Vertex(&p_5,&p_6,-TJumps[j].RotateYZ);
                                Rotate_Vertex(&p_8,&p_9,-TJumps[j].RotateYZ);
                                Rotate_Vertex(&p_11,&p_12,-TJumps[j].RotateYZ);
                                Rotate_Vertex(&p_1,&p_2,TJumps[j].RotateXY);
                                Rotate_Vertex(&p_4,&p_5,TJumps[j].RotateXY);
                                Rotate_Vertex(&p_7,&p_8,TJumps[j].RotateXY);
                                Rotate_Vertex(&p_10,&p_11,TJumps[j].RotateXY);
                                p_1 += TJumps[j].ShiftX;
                                p_2 += TJumps[j].ShiftY;
                                p_3 += TJumps[j].ShiftZ;
                                p_4 += TJumps[j].ShiftX;
                                p_5 += TJumps[j].ShiftY;
                                p_6 += TJumps[j].ShiftZ;
                                p_7 += TJumps[j].ShiftX;
                                p_8 += TJumps[j].ShiftY;
                                p_9 += TJumps[j].ShiftZ;
                                p_10 += TJumps[j].ShiftX;
                                p_11 += TJumps[j].ShiftY;
                                p_12 += TJumps[j].ShiftZ;
                                }
                        p_1 +=          centroid__X;
                        p_4 +=          centroid__X;
                        p_7 +=          centroid__X;
                        p_10 +=         centroid__X;
                        p_2 +=          centroid__Y;
                        p_5 +=          centroid__Y;
                        p_8 +=          centroid__Y;
                        p_11 +=         centroid__Y;
                        if (!SIDE)
                                {
                                p_3 += BoardThick;
                                p_6 += BoardThick;
                                p_9 += BoardThick;
                                p_12 += BoardThick;
                                }
                        else    {
                                Rotate_Vertex(&p_1,&p_3,180);
                                Rotate_Vertex(&p_4,&p_6,180);
                                Rotate_Vertex(&p_7,&p_9,180);
                                Rotate_Vertex(&p_10,&p_12,180);
                                }
                        if (_3d)
                                {
                                Rotate3d(&p_1,&p_2,&p_3,&p_4,&p_5,&p_6,&p_7,&p_8,&p_9,&p_10,&p_11,&p_12);
                                }
                        if (!(q == 2 && memTValuesSizeX > BY_ZERO) )
                        if (Form3->RadioButton4->Checked && CANVAS_TO_FILE)
                                {
                                W_LINE_BLK(p_1,p_2,p_3,p_4,p_5,p_6,    CLR,LAYER__3D);
                                W_LINE_BLK(p_7,p_8,p_9,p_10,p_11,p_12, CLR,LAYER__3D);
                                W_LINE_BLK(p_1,p_2,p_3,p_7, p_8, p_9,  CLR,LAYER__3D);
                                W_LINE_BLK(p_4,p_5,p_6,p_10,p_11,p_12, CLR,LAYER__3D);
                                }
                        else if (CANVAS_TO_FILE)      W_SOLID_BLK(    p_1,p_2,p_3,p_4,p_5,p_6,
                                                                p_7,p_8,p_9,p_10,p_11,p_12,CLR,LAYER__3D);
                        else    {
                                FACES[fcs] = Object;
                                FACES[fcs+1] = p_1;
                                FACES[fcs+2] = p_2;
                                FACES[fcs+3] = p_3;
                                FACES[fcs+4] = p_4;
                                FACES[fcs+5] = p_5;
                                FACES[fcs+6] = p_6;
                                FACES[fcs+7] = p_10;
                                FACES[fcs+8] = p_11;
                                FACES[fcs+9] = p_12;
                                FACES[fcs+10] = p_7;
                                FACES[fcs+11] = p_8;
                                FACES[fcs+12] = p_9;
                                fcs = fcs + 13;
                                if (fcs > MAX_FACES_AND_LINES) return WARNING_OF_MEMORY;
                                (*SELRECT).Left = MIN4(p_1, p_4, p_7, (*SELRECT).Left );
                                (*SELRECT).Left = MIN(p_10, (*SELRECT).Left );
                                (*SELRECT).Right = MAX4(p_1, p_4, p_7, (*SELRECT).Right );
                                (*SELRECT).Right = MAX(p_10, (*SELRECT).Right );
                                (*SELRECT).Bottom = MIN4(p_2, p_5, p_8, (*SELRECT).Bottom );
                                (*SELRECT).Bottom = MIN(p_11, (*SELRECT).Bottom );
                                (*SELRECT).Top = MAX4(p_2, p_5, p_8, (*SELRECT).Top );
                                (*SELRECT).Top = MAX(p_11, (*SELRECT).Top );
                                (*SELRECT)._Low = MIN4(p_3, p_6, p_9, (*SELRECT)._Low );
                                (*SELRECT)._Low = MIN(p_12, (*SELRECT)._Low );
                                (*SELRECT)._High = MAX4(p_3, p_6, p_9, (*SELRECT)._High );
                                (*SELRECT)._High = MAX(p_12, (*SELRECT)._High );
                                }
                        p_1 = p7;
                        p_2 = p8;
                        p_3 = p9;
                        p_4 = p10;
                        p_5 = p11;
                        p_6 = p12;
                        }
                if (memTValuesSizeX > BY_ZERO)
                        {
                        TValues.SizeX = memTValuesSizeX;
                        p_1 = -TValues.SizeX/2.0;
                        p_2 = -TValues.SizeY/2.0;
                        p_3 = 0;
                        p_4 = -TValues.SizeX/2.0;
                        p_5 = TValues.SizeY/2.0;
                        p_6 = 0;
                        p_7 = -TValues.SizeZ/2.0;
                        p_8 = -TValues.SizeY/2.0;
                        p_9 = 0;
                        p_10 = -TValues.SizeZ/2.0;
                        p_11 = TValues.SizeY/2.0;
                        p_12 = 0;
                        Rotate_Vertex(&p_1,&p_3,-TValues.RotateXZ);
                        Rotate_Vertex(&p_4,&p_6,-TValues.RotateXZ);
                        Rotate_Vertex(&p_7,&p_9,-TValues.RotateXZ);
                        Rotate_Vertex(&p_10,&p_12,-TValues.RotateXZ);
                        Rotate_Vertex(&p_2,&p_3,-TValues.RotateYZ);
                        Rotate_Vertex(&p_5,&p_6,-TValues.RotateYZ);
                        Rotate_Vertex(&p_8,&p_9,-TValues.RotateYZ);
                        Rotate_Vertex(&p_11,&p_12,-TValues.RotateYZ);
                        Rotate_Vertex(&p_1,&p_2,TValues.RotateXY);
                        Rotate_Vertex(&p_4,&p_5,TValues.RotateXY);
                        Rotate_Vertex(&p_7,&p_8,TValues.RotateXY);
                        Rotate_Vertex(&p_10,&p_11,TValues.RotateXY);
                        p_1 += TValues.ShiftX;
                        p_2 += TValues.ShiftY;
                        p_3 += TValues.ShiftZ;
                        p_4 += TValues.ShiftX;
                        p_5 += TValues.ShiftY;
                        p_6 += TValues.ShiftZ;
                        p_7 += TValues.ShiftX;
                        p_8 += TValues.ShiftY;
                        p_9 += TValues.ShiftZ;
                        p_10 += TValues.ShiftX;
                        p_11 += TValues.ShiftY;
                        p_12 += TValues.ShiftZ;
                        for (int j=0; TJumps[j].Shape; j++)
                                {
                                if (ABS(TJumps[j].ScaleX) > BY_ZERO)
                                        {
                                        p_1 = p_1*TJumps[j].ScaleX;
                                        p_4 = p_4*TJumps[j].ScaleX;
                                        p_7 = p_7*TJumps[j].ScaleX;
                                        p_10 = p_10*TJumps[j].ScaleX;
                                        }
                                if (ABS(TJumps[j].ScaleY) > BY_ZERO)
                                        {
                                        p_2 = p_2*TJumps[j].ScaleY;
                                        p_5 = p_5*TJumps[j].ScaleY;
                                        p_8 = p_8*TJumps[j].ScaleY;
                                        p_11 = p_11*TJumps[j].ScaleY;
                                        }
                                if (ABS(TJumps[j].ScaleZ) > BY_ZERO)
                                        {
                                        p_3 = p_3*TJumps[j].ScaleZ;
                                        p_6 = p_6*TJumps[j].ScaleZ;
                                        p_9 = p_9*TJumps[j].ScaleZ;
                                        p_12 = p_12*TJumps[j].ScaleZ;
                                        }
                                Rotate_Vertex(&p_1,&p_3,-TJumps[j].RotateXZ);
                                Rotate_Vertex(&p_4,&p_6,-TJumps[j].RotateXZ);
                                Rotate_Vertex(&p_7,&p_9,-TJumps[j].RotateXZ);
                                Rotate_Vertex(&p_10,&p_12,-TJumps[j].RotateXZ);
                                Rotate_Vertex(&p_2,&p_3,-TJumps[j].RotateYZ);
                                Rotate_Vertex(&p_5,&p_6,-TJumps[j].RotateYZ);
                                Rotate_Vertex(&p_8,&p_9,-TJumps[j].RotateYZ);
                                Rotate_Vertex(&p_11,&p_12,-TJumps[j].RotateYZ);
                                Rotate_Vertex(&p_1,&p_2,TJumps[j].RotateXY);
                                Rotate_Vertex(&p_4,&p_5,TJumps[j].RotateXY);
                                Rotate_Vertex(&p_7,&p_8,TJumps[j].RotateXY);
                                Rotate_Vertex(&p_10,&p_11,TJumps[j].RotateXY);
                                p_1 += TJumps[j].ShiftX;
                                p_2 += TJumps[j].ShiftY;
                                p_3 += TJumps[j].ShiftZ;
                                p_4 += TJumps[j].ShiftX;
                                p_5 += TJumps[j].ShiftY;
                                p_6 += TJumps[j].ShiftZ;
                                p_7 += TJumps[j].ShiftX;
                                p_8 += TJumps[j].ShiftY;
                                p_9 += TJumps[j].ShiftZ;
                                p_10 += TJumps[j].ShiftX;
                                p_11 += TJumps[j].ShiftY;
                                p_12 += TJumps[j].ShiftZ;
                                }
                        p_1 +=          centroid__X;
                        p_4 +=          centroid__X;
                        p_7 +=          centroid__X;
                        p_10 +=         centroid__X;
                        p_2 +=          centroid__Y;
                        p_5 +=          centroid__Y;
                        p_8 +=          centroid__Y;
                        p_11 +=         centroid__Y;
                        if (!SIDE)
                                {
                                p_3 += BoardThick;
                                p_6 += BoardThick;
                                p_9 += BoardThick;
                                p_12 += BoardThick;
                                }
                        else    {
                                Rotate_Vertex(&p_1,&p_3,180.0);
                                Rotate_Vertex(&p_4,&p_6,180.0);
                                Rotate_Vertex(&p_7,&p_9,180.0);
                                Rotate_Vertex(&p_10,&p_12,180.0);
                                }
                        if (_3d)
                                {
                                Rotate3d(&p_1,&p_2,&p_3,&p_4,&p_5,&p_6,&p_7,&p_8,&p_9,&p_10,&p_11,&p_12);
                                }
                        if (Form3->RadioButton4->Checked && CANVAS_TO_FILE)
                                {
                                W_LINE_BLK(p_1,p_2,p_3,p_4,p_5,p_6,    CLR,LAYER__3D);
                                W_LINE_BLK(p_7,p_8,p_9,p_10,p_11,p_12, CLR,LAYER__3D);
                                W_LINE_BLK(p_1,p_2,p_3,p_7, p_8, p_9,  CLR,LAYER__3D);
                                W_LINE_BLK(p_4,p_5,p_6,p_10,p_11,p_12, CLR,LAYER__3D);
                                }
                        else if (CANVAS_TO_FILE)      W_SOLID_BLK(    p_1,p_2,p_3,p_4,p_5,p_6,
                                                                p_7,p_8,p_9,p_10,p_11,p_12,CLR,LAYER__3D);
                        else    {
                                FACES[fcs] = Object;
                                FACES[fcs+1] = p_1;
                                FACES[fcs+2] = p_2;
                                FACES[fcs+3] = p_3;
                                FACES[fcs+4] = p_4;
                                FACES[fcs+5] = p_5;
                                FACES[fcs+6] = p_6;
                                FACES[fcs+7] = p_10;
                                FACES[fcs+8] = p_11;
                                FACES[fcs+9] = p_12;
                                FACES[fcs+10] = p_7;
                                FACES[fcs+11] = p_8;
                                FACES[fcs+12] = p_9;
                                fcs = fcs + 13;
                                if (fcs > MAX_FACES_AND_LINES) return WARNING_OF_MEMORY;
                                (*SELRECT).Left = MIN4(p_1, p_4, p_7, (*SELRECT).Left );
                                (*SELRECT).Left = MIN(p_10, (*SELRECT).Left );
                                (*SELRECT).Right = MAX4(p_1, p_4, p_7, (*SELRECT).Right );
                                (*SELRECT).Right = MAX(p_10, (*SELRECT).Right );
                                (*SELRECT).Bottom = MIN4(p_2, p_5, p_8, (*SELRECT).Bottom );
                                (*SELRECT).Bottom = MIN(p_11, (*SELRECT).Bottom );
                                (*SELRECT).Top = MAX4(p_2, p_5, p_8, (*SELRECT).Top );
                                (*SELRECT).Top = MAX(p_11, (*SELRECT).Top );
                                (*SELRECT)._Low = MIN4(p_3, p_6, p_9, (*SELRECT)._Low );
                                (*SELRECT)._Low = MIN(p_12, (*SELRECT)._Low );
                                (*SELRECT)._High = MAX4(p_3, p_6, p_9, (*SELRECT)._High );
                                (*SELRECT)._High = MAX(p_12, (*SELRECT)._High );
                                }
                        p_1 = TValues.SizeX/2.0;
                        p_2 = -TValues.SizeY/2.0;
                        p_3 = TValues.SizeZ;
                        p_4 = TValues.SizeX/2.0;
                        p_5 = TValues.SizeY/2.0;
                        p_6 = TValues.SizeZ;
                        p_7 = TValues.SizeZ/2.0;
                        p_8 = -TValues.SizeY/2.0;
                        p_9 = TValues.SizeZ;
                        p_10 = TValues.SizeZ/2.0;
                        p_11 = TValues.SizeY/2.0;
                        p_12 = TValues.SizeZ;
                        Rotate_Vertex(&p_1,&p_3,-TValues.RotateXZ);
                        Rotate_Vertex(&p_4,&p_6,-TValues.RotateXZ);
                        Rotate_Vertex(&p_7,&p_9,-TValues.RotateXZ);
                        Rotate_Vertex(&p_10,&p_12,-TValues.RotateXZ);
                        Rotate_Vertex(&p_2,&p_3,-TValues.RotateYZ);
                        Rotate_Vertex(&p_5,&p_6,-TValues.RotateYZ);
                        Rotate_Vertex(&p_8,&p_9,-TValues.RotateYZ);
                        Rotate_Vertex(&p_11,&p_12,-TValues.RotateYZ);
                        Rotate_Vertex(&p_1,&p_2,TValues.RotateXY);
                        Rotate_Vertex(&p_4,&p_5,TValues.RotateXY);
                        Rotate_Vertex(&p_7,&p_8,TValues.RotateXY);
                        Rotate_Vertex(&p_10,&p_11,TValues.RotateXY);
                        p_1 += TValues.ShiftX;
                        p_2 += TValues.ShiftY;
                        p_3 += TValues.ShiftZ;
                        p_4 += TValues.ShiftX;
                        p_5 += TValues.ShiftY;
                        p_6 += TValues.ShiftZ;
                        p_7 += TValues.ShiftX;
                        p_8 += TValues.ShiftY;
                        p_9 += TValues.ShiftZ;
                        p_10 += TValues.ShiftX;
                        p_11 += TValues.ShiftY;
                        p_12 += TValues.ShiftZ;
                        for (int j=0; TJumps[j].Shape; j++)
                                {
                                if (ABS(TJumps[j].ScaleX) > BY_ZERO)
                                        {
                                        p_1 = p_1*TJumps[j].ScaleX;
                                        p_4 = p_4*TJumps[j].ScaleX;
                                        p_7 = p_7*TJumps[j].ScaleX;
                                        p_10 = p_10*TJumps[j].ScaleX;
                                        }
                                if (ABS(TJumps[j].ScaleY) > BY_ZERO)
                                        {
                                        p_2 = p_2*TJumps[j].ScaleY;
                                        p_5 = p_5*TJumps[j].ScaleY;
                                        p_8 = p_8*TJumps[j].ScaleY;
                                        p_11 = p_11*TJumps[j].ScaleY;
                                        }
                                if (ABS(TJumps[j].ScaleZ) > BY_ZERO)
                                        {
                                        p_3 = p_3*TJumps[j].ScaleZ;
                                        p_6 = p_6*TJumps[j].ScaleZ;
                                        p_9 = p_9*TJumps[j].ScaleZ;
                                        p_12 = p_12*TJumps[j].ScaleZ;
                                        }
                                Rotate_Vertex(&p_1,&p_3,-TJumps[j].RotateXZ);
                                Rotate_Vertex(&p_4,&p_6,-TJumps[j].RotateXZ);
                                Rotate_Vertex(&p_7,&p_9,-TJumps[j].RotateXZ);
                                Rotate_Vertex(&p_10,&p_12,-TJumps[j].RotateXZ);
                                Rotate_Vertex(&p_2,&p_3,-TJumps[j].RotateYZ);
                                Rotate_Vertex(&p_5,&p_6,-TJumps[j].RotateYZ);
                                Rotate_Vertex(&p_8,&p_9,-TJumps[j].RotateYZ);
                                Rotate_Vertex(&p_11,&p_12,-TJumps[j].RotateYZ);
                                Rotate_Vertex(&p_1,&p_2,TJumps[j].RotateXY);
                                Rotate_Vertex(&p_4,&p_5,TJumps[j].RotateXY);
                                Rotate_Vertex(&p_7,&p_8,TJumps[j].RotateXY);
                                Rotate_Vertex(&p_10,&p_11,TJumps[j].RotateXY);
                                p_1 += TJumps[j].ShiftX;
                                p_2 += TJumps[j].ShiftY;
                                p_3 += TJumps[j].ShiftZ;
                                p_4 += TJumps[j].ShiftX;
                                p_5 += TJumps[j].ShiftY;
                                p_6 += TJumps[j].ShiftZ;
                                p_7 += TJumps[j].ShiftX;
                                p_8 += TJumps[j].ShiftY;
                                p_9 += TJumps[j].ShiftZ;
                                p_10 += TJumps[j].ShiftX;
                                p_11 += TJumps[j].ShiftY;
                                p_12 += TJumps[j].ShiftZ;
                                }
                        p_1 +=          centroid__X;
                        p_4 +=          centroid__X;
                        p_7 +=          centroid__X;
                        p_10 +=         centroid__X;
                        p_2 +=          centroid__Y;
                        p_5 +=          centroid__Y;
                        p_8 +=          centroid__Y;
                        p_11 +=         centroid__Y;
                        if (!SIDE)
                                {
                                p_3 += BoardThick;
                                p_6 += BoardThick;
                                p_9 += BoardThick;
                                p_12 += BoardThick;
                                }
                        else    {
                                Rotate_Vertex(&p_1,&p_3,180);
                                Rotate_Vertex(&p_4,&p_6,180);
                                Rotate_Vertex(&p_7,&p_9,180);
                                Rotate_Vertex(&p_10,&p_12,180);
                                }
                        if (_3d)
                                {
                                Rotate3d(&p_1,&p_2,&p_3,&p_4,&p_5,&p_6,&p_7,&p_8,&p_9,&p_10,&p_11,&p_12);
                                }
                        if (Form3->RadioButton4->Checked && CANVAS_TO_FILE)
                                {
                                W_LINE_BLK(p_1,p_2,p_3,p_4,p_5,p_6,    CLR,LAYER__3D);
                                W_LINE_BLK(p_7,p_8,p_9,p_10,p_11,p_12, CLR,LAYER__3D);
                                W_LINE_BLK(p_1,p_2,p_3,p_7, p_8, p_9,  CLR,LAYER__3D);
                                W_LINE_BLK(p_4,p_5,p_6,p_10,p_11,p_12, CLR,LAYER__3D);
                                }
                        else if (CANVAS_TO_FILE)      W_SOLID_BLK(    p_1,p_2,p_3,p_4,p_5,p_6,
                                                                p_7,p_8,p_9,p_10,p_11,p_12,CLR,LAYER__3D);
                        else    {
                                FACES[fcs] = Object;
                                FACES[fcs+1] = p_1;
                                FACES[fcs+2] = p_2;
                                FACES[fcs+3] = p_3;
                                FACES[fcs+4] = p_4;
                                FACES[fcs+5] = p_5;
                                FACES[fcs+6] = p_6;
                                FACES[fcs+7] = p_10;
                                FACES[fcs+8] = p_11;
                                FACES[fcs+9] = p_12;
                                FACES[fcs+10] = p_7;
                                FACES[fcs+11] = p_8;
                                FACES[fcs+12] = p_9;
                                fcs = fcs + 13;
                                if (fcs > MAX_FACES_AND_LINES) return WARNING_OF_MEMORY;
                                (*SELRECT).Left = MIN4(p_1, p_4, p_7, (*SELRECT).Left );
                                (*SELRECT).Left = MIN(p_10, (*SELRECT).Left );
                                (*SELRECT).Right = MAX4(p_1, p_4, p_7, (*SELRECT).Right );
                                (*SELRECT).Right = MAX(p_10, (*SELRECT).Right );
                                (*SELRECT).Bottom = MIN4(p_2, p_5, p_8, (*SELRECT).Bottom );
                                (*SELRECT).Bottom = MIN(p_11, (*SELRECT).Bottom );
                                (*SELRECT).Top = MAX4(p_2, p_5, p_8, (*SELRECT).Top );
                                (*SELRECT).Top = MAX(p_11, (*SELRECT).Top );
                                (*SELRECT)._Low = MIN4(p_3, p_6, p_9, (*SELRECT)._Low );
                                (*SELRECT)._Low = MIN(p_12, (*SELRECT)._Low );
                                (*SELRECT)._High = MAX4(p_3, p_6, p_9, (*SELRECT)._High );
                                (*SELRECT)._High = MAX(p_12, (*SELRECT)._High );
                                }
                        }
                }
        }
FACES[fcs] = DEFAULT + 1;
//
if (ABS((*SELRECT).Left) > _103)
        {
        (*SELRECT).Left  = 0;
        (*SELRECT).Right = 0;
        (*SELRECT).Top   = 0;
        (*SELRECT).Bottom= 0;
        (*SELRECT)._Low  = 0;
        (*SELRECT)._High = 0;
        }
(*SELRECT).Left         *=_106;
(*SELRECT).Right        *=_106;
(*SELRECT).Top          *=_106;
(*SELRECT).Bottom       *=_106;
(*SELRECT)._Low         *=_106;
(*SELRECT)._High        *=_106;
//
for (int u=1; u<NUMBER_OF_TJumps; u++)
        TJumps[u-1] = TJumps[u];
TJumps[NUMBER_OF_TJumps-1].ini();
if (CLR < 32)
        {
        if (TJumps[0].Shape == 0)
                CLR++;
        }
else CLR = 20;
return JUMP_NOT_FOUND;
}
//---------------------------------------------------------------------------























//---------------------------------------------------------------------------
int SILK_TOP (int N_STR, int ROT, Table_struct T, int CI, myRect * SELRECT, bool _3d)
{
AnsiString A;
long i;
bool bLINE_EN=0;
for (int kw=(N_STR+1); kw<Form1->File->Count; kw++)
        {
        A = Form1->File->Items->operator [](kw);
        if (A.SubString(1,7) == "[board]") break;
        if (A.SubString(1,4) == "name")    break;
        //
        if (A.SubString(1,6) == "units:" )
                {
                i = prob(A,1);
                if (A.UpperCase().SubString(i,2) == "NM")      U = 0;
                else if (A.UpperCase().SubString(i,2) == "MI") U = 1;
                else                                           U = 2;
                }
        else if (A.SubString(1,7) == "outline")
                {
                i = prob(A,1);
                W_Line  = ex_float(A, &i);              //W
                X__1 = ex_float(A, &i);                 //X
                Y__1 = ex_float(A, &i);                 //Y
                int vis = ex_float(A, &i);              //vis
                //if(!vis)
                //        bLINE_EN = 0;
                //else
                        bLINE_EN = 1;
                if (Units_MM == 1)
                        {
                        W_Line = W_Line*INV_PER_MIL;
                        X__1 =     X__1*INV_PER_MIL;
                        Y__1 =     Y__1*INV_PER_MIL;
                        }
                else if (Units_MM == 0)
                        {
                        W_Line = W_Line/PER_MM;
                        X__1 =     X__1/PER_MM;
                        Y__1 =     Y__1/PER_MM;
                        }
                First_X = X__1;
                First_Y = Y__1;
                }
        else if ( bLINE_EN && (A.SubString(1,5) == "next_" || A.SubString(1,6) == "close_")  )
                {
                if (A.SubString(1,5) == "next_")
                        {
                        i = prob(A,1);
                        X__2 = ex_float(A, &i);                 //X
                        Y__2 = ex_float(A, &i);                 //Y
                        type_L = ex_float(A, &i);               //type_L
                        if (Units_MM == 1)
                                {
                                X__2 =     X__2*INV_PER_MIL;
                                Y__2 =     Y__2*INV_PER_MIL;
                                }
                        else if (Units_MM == 0)
                                {
                                X__2 =     X__2/PER_MM;
                                Y__2 =     Y__2/PER_MM;
                                }
                        }
                else    {
                        X__2 = First_X;                         //X
                        Y__2 = First_Y;                         //Y
                        i = prob(A, 1);
                        type_L = ex_float(A, &i);               //type_L
                        }
                if (T.Shape == SH__SILK)
                        {
                        float Z_1;
                        float Z_2;
                        float Z_3;
                        float Z_4;
                        float X_1;
                        float X_2;
                        float X_3;
                        float X_4;
                        float Y_1;
                        float Y_2;
                        float Y_3;
                        float Y_4;
                        float Vertex_Of_Lines[99];
                        int L = Generate_Line (X__1, Y__1, X__2, Y__2, type_L, &Vertex_Of_Lines[0]);
                        for (int h=0; h <= (L-4); h = h+2)
                                {
                                Z_1 = 0;
                                Z_2 = 0;
                                Z_3 = T.SizeZ;
                                Z_4 = T.SizeZ;
                                X_1 = Vertex_Of_Lines[h];
                                X_2 = Vertex_Of_Lines[h+2];
                                X_3 = Vertex_Of_Lines[h];
                                X_4 = Vertex_Of_Lines[h+2];
                                Y_1 = Vertex_Of_Lines[h+1];
                                Y_2 = Vertex_Of_Lines[h+3];
                                Y_3 = Vertex_Of_Lines[h+1];
                                Y_4 = Vertex_Of_Lines[h+3];
                                Rotate_Vertex(&X_1, &Z_1, -T.RotateXZ);
                                Rotate_Vertex(&X_2, &Z_2, -T.RotateXZ);
                                Rotate_Vertex(&X_3, &Z_3, -T.RotateXZ);
                                Rotate_Vertex(&X_4, &Z_4, -T.RotateXZ);
                                Rotate_Vertex(&Y_1, &Z_1, -T.RotateYZ);
                                Rotate_Vertex(&Y_2, &Z_2, -T.RotateYZ);
                                Rotate_Vertex(&Y_3, &Z_3, -T.RotateYZ);
                                Rotate_Vertex(&Y_4, &Z_4, -T.RotateYZ);
                                Rotate_Vertex(&X_1, &Y_1, T.RotateXY + ROT);
                                Rotate_Vertex(&X_2, &Y_2, T.RotateXY + ROT);
                                Rotate_Vertex(&X_3, &Y_3, T.RotateXY + ROT);
                                Rotate_Vertex(&X_4, &Y_4, T.RotateXY + ROT);
                                X_1 += T.ShiftX;
                                X_2 += T.ShiftX;
                                X_3 += T.ShiftX;
                                X_4 += T.ShiftX;
                                Y_1 += T.ShiftY;
                                Y_2 += T.ShiftY;
                                Y_3 += T.ShiftY;
                                Y_4 += T.ShiftY;
                                Z_1 += T.ShiftZ;
                                Z_2 += T.ShiftZ;
                                Z_3 += T.ShiftZ;
                                Z_4 += T.ShiftZ;
                                for (int j=0; TJumps[j].Shape; j++)
                                        {
                                        if (ABS(TJumps[j].ScaleX) > BY_ZERO)
                                                {
                                                X_1 = X_1*TJumps[j].ScaleX;
                                                X_2 = X_2*TJumps[j].ScaleX;
                                                X_3 = X_3*TJumps[j].ScaleX;
                                                X_4 = X_4*TJumps[j].ScaleX;
                                                }
                                        if (ABS(TJumps[j].ScaleY) > BY_ZERO)
                                                {
                                                Y_1 = Y_1*TJumps[j].ScaleY;
                                                Y_2 = Y_2*TJumps[j].ScaleY;
                                                Y_3 = Y_3*TJumps[j].ScaleY;
                                                Y_4 = Y_4*TJumps[j].ScaleY;
                                                }
                                        if (ABS(TJumps[j].ScaleZ) > BY_ZERO)
                                                {
                                                Z_1 = Z_1*TJumps[j].ScaleZ;
                                                Z_2 = Z_2*TJumps[j].ScaleZ;
                                                Z_3 = Z_3*TJumps[j].ScaleZ;
                                                Z_4 = Z_4*TJumps[j].ScaleZ;
                                                }
                                        Rotate_Vertex(&X_1,&Z_1,-TJumps[j].RotateXZ);
                                        Rotate_Vertex(&X_2,&Z_2,-TJumps[j].RotateXZ);
                                        Rotate_Vertex(&X_3,&Z_3,-TJumps[j].RotateXZ);
                                        Rotate_Vertex(&X_4,&Z_4,-TJumps[j].RotateXZ);
                                        Rotate_Vertex(&Y_1,&Z_1,-TJumps[j].RotateYZ);
                                        Rotate_Vertex(&Y_2,&Z_2,-TJumps[j].RotateYZ);
                                        Rotate_Vertex(&Y_3,&Z_3,-TJumps[j].RotateYZ);
                                        Rotate_Vertex(&Y_4,&Z_4,-TJumps[j].RotateYZ);
                                        Rotate_Vertex(&X_1,&Y_1,TJumps[j].RotateXY);
                                        Rotate_Vertex(&X_2,&Y_2,TJumps[j].RotateXY);
                                        Rotate_Vertex(&X_3,&Y_3,TJumps[j].RotateXY);
                                        Rotate_Vertex(&X_4,&Y_4,TJumps[j].RotateXY);
                                        X_1 += TJumps[j].ShiftX;
                                        Y_1 += TJumps[j].ShiftY;
                                        Z_1 += TJumps[j].ShiftZ;
                                        X_2 += TJumps[j].ShiftX;
                                        Y_2 += TJumps[j].ShiftY;
                                        Z_2 += TJumps[j].ShiftZ;
                                        X_3 += TJumps[j].ShiftX;
                                        Y_3 += TJumps[j].ShiftY;
                                        Z_3 += TJumps[j].ShiftZ;
                                        X_4 += TJumps[j].ShiftX;
                                        Y_4 += TJumps[j].ShiftY;
                                        Z_4 += TJumps[j].ShiftZ;
                                        }
                                Z_1 += BoardThick;
                                Z_2 += BoardThick;
                                Z_3 += BoardThick;
                                Z_4 += BoardThick;
                               /* X_1 += centroid__X;
                                X_2 += centroid__X;
                                X_3 += centroid__X;
                                X_4 += centroid__X;
                                Y_1 += centroid__Y;
                                Y_2 += centroid__Y;
                                Y_3 += centroid__Y;
                                Y_4 += centroid__Y;  */
                                if (_3d)
                                        {
                                        Rotate3d(&X_1,&Y_1,&Z_1,&X_2,&Y_2,&Z_2,&X_3,&Y_3,&Z_3,&X_4,&Y_4,&Z_4);
                                        }
                                if (!CANVAS_TO_FILE)
                                        {
                                        FACES[fcs] = CI;
                                        FACES[fcs+1] = X_1;
                                        FACES[fcs+2] = Y_1;
                                        FACES[fcs+3] = Z_1;
                                        FACES[fcs+4] = X_2;
                                        FACES[fcs+5] = Y_2;
                                        FACES[fcs+6] = Z_2;
                                        FACES[fcs+7] = X_4;
                                        FACES[fcs+8] = Y_4;
                                        FACES[fcs+9] = Z_4;
                                        FACES[fcs+10] = X_3;
                                        FACES[fcs+11] = Y_3;
                                        FACES[fcs+12] = Z_3;
                                        fcs = fcs + 13;
                                        if (fcs > MAX_FACES_AND_LINES) return WARNING_OF_MEMORY;
                                        (*SELRECT).Left = MIN4(X_1, X_2, X_3, (*SELRECT).Left );
                                        (*SELRECT).Left = MIN(X_4, (*SELRECT).Left );
                                        (*SELRECT).Right = MAX4(X_1, X_2, X_3, (*SELRECT).Right );
                                        (*SELRECT).Right = MAX(X_4, (*SELRECT).Right );
                                        (*SELRECT).Bottom = MIN4(Y_1, Y_2, Y_3, (*SELRECT).Bottom );
                                        (*SELRECT).Bottom = MIN(Y_4, (*SELRECT).Bottom );
                                        (*SELRECT).Top = MAX4(Y_1, Y_2, Y_3, (*SELRECT).Top );
                                        (*SELRECT).Top = MAX(Y_4, (*SELRECT).Top );
                                        }
                                else if (Form3->RadioButton3->Checked)
                                        {
                                        W_SOLID_BLK(X_1,Y_1,Z_1,  X_2,Y_2,Z_2,  X_3,Y_3,Z_3,  X_4,Y_4,Z_4, CL_3DTOP, LT );
                                        }
                                else    {
                                        W_LINE_BLK(X_1,Y_1,Z_1,  X_2,Y_2,Z_2,  CL_3DTOP, LT );
                                        W_LINE_BLK(X_3,Y_3,Z_3,  X_4,Y_4,Z_4,  CL_3DTOP, LT );
                                        W_LINE_BLK(X_1,Y_1,Z_1,  X_3,Y_3,Z_3,  CL_3DTOP, LT );
                                        W_LINE_BLK(X_2,Y_2,Z_2,  X_4,Y_4,Z_4,  CL_3DTOP, LT );
                                        }
                                }
                        }
                X__1 = X__2;
                Y__1 = Y__2;
                }
        }
return 0;
}
//---------------------------------------------------------------------------










//---------------------------------------------------------------------------
int SILK_BOT (int N_STR, int ROT, Table_struct T, int CI, myRect * SELRECT, bool _3d)
{
AnsiString A;
long i;
bool bLINE_EN=0;
for (int kw=(N_STR+1); kw<Form1->File->Count; kw++)
        {
        A = Form1->File->Items->operator [](kw);
        if (A.SubString(1,7) == "[board]") break;
        if (A.SubString(1,4) == "name")    break;
        //
        if (A.SubString(1,6) == "units:" )
                {
                i = prob(A,1);
                if (A.UpperCase().SubString(i,2) == "NM")      U = 0;
                else if (A.UpperCase().SubString(i,2) == "MI") U = 1;
                else                                           U = 2;
                }
        else if (A.SubString(1,7) == "outline")
                {
                i = prob(A,1);
                W_Line  = ex_float(A, &i);              //W
                X__1 = ex_float(A, &i);                 //X
                Y__1 = ex_float(A, &i);                 //Y
                int vis = ex_float(A, &i);              //vis
                if(!vis)
                        bLINE_EN = 0;
                else
                        bLINE_EN = 1;
                if (Units_MM == 1)
                        {
                        W_Line = W_Line*INV_PER_MIL;
                        X__1 =     X__1*INV_PER_MIL;
                        Y__1 =     Y__1*INV_PER_MIL;
                        }
                else if (Units_MM == 0)
                        {
                        W_Line = W_Line/PER_MM;
                        X__1 =     X__1/PER_MM;
                        Y__1 =     Y__1/PER_MM;
                        }
                First_X = X__1;
                First_Y = Y__1;
                }
        else if ( bLINE_EN && (A.SubString(1,5) == "next_" || A.SubString(1,6) == "close_")  )
                {
                if (A.SubString(1,5) == "next_")
                        {
                        i = prob(A,1);
                        X__2 = ex_float(A, &i);                 //X
                        Y__2 = ex_float(A, &i);                 //Y
                        type_L = ex_float(A, &i);               //type_L
                        if (Units_MM == 1)
                                {
                                X__2 =     X__2*INV_PER_MIL;
                                Y__2 =     Y__2*INV_PER_MIL;
                                }
                        else if (Units_MM == 0)
                                {
                                X__2 =     X__2/PER_MM;
                                Y__2 =     Y__2/PER_MM;
                                }
                        }
                else    {
                        X__2 = First_X;                         //X
                        Y__2 = First_Y;                         //Y
                        i = prob(A, 1);
                        type_L = ex_float(A, &i);               //type_L
                        }
                if (T.Shape == SH__SILK)
                        {
                        float Z_1;
                        float Z_2;
                        float Z_3;
                        float Z_4;
                        float X_1;
                        float X_2;
                        float X_3;
                        float X_4;
                        float Y_1;
                        float Y_2;
                        float Y_3;
                        float Y_4;
                        float Vertex_Of_Lines[99];
                        int L = Generate_Line (X__1, Y__1, X__2, Y__2, type_L, &Vertex_Of_Lines[0]);
                        for (int h=0; h <= (L-4); h = h+2)
                                {
                                Z_1 = 0;
                                Z_2 = 0;
                                Z_3 = T.SizeZ;
                                Z_4 = T.SizeZ;
                                X_1 = Vertex_Of_Lines[h];
                                X_2 = Vertex_Of_Lines[h+2];
                                X_3 = Vertex_Of_Lines[h];
                                X_4 = Vertex_Of_Lines[h+2];
                                Y_1 = Vertex_Of_Lines[h+1];
                                Y_2 = Vertex_Of_Lines[h+3];
                                Y_3 = Vertex_Of_Lines[h+1];
                                Y_4 = Vertex_Of_Lines[h+3];
                                Rotate_Vertex(&X_1, &Z_1, -T.RotateXZ);
                                Rotate_Vertex(&X_2, &Z_2, -T.RotateXZ);
                                Rotate_Vertex(&X_3, &Z_3, -T.RotateXZ);
                                Rotate_Vertex(&X_4, &Z_4, -T.RotateXZ);
                                Rotate_Vertex(&Y_1, &Z_1, -T.RotateYZ);
                                Rotate_Vertex(&Y_2, &Z_2, -T.RotateYZ);
                                Rotate_Vertex(&Y_3, &Z_3, -T.RotateYZ);
                                Rotate_Vertex(&Y_4, &Z_4, -T.RotateYZ);
                                Rotate_Vertex(&X_1, &Y_1, T.RotateXY - ROT);
                                Rotate_Vertex(&X_2, &Y_2, T.RotateXY - ROT);
                                Rotate_Vertex(&X_3, &Y_3, T.RotateXY - ROT);
                                Rotate_Vertex(&X_4, &Y_4, T.RotateXY - ROT);
                                X_1 += T.ShiftX;
                                X_2 += T.ShiftX;
                                X_3 += T.ShiftX;
                                X_4 += T.ShiftX;
                                Y_1 += T.ShiftY;
                                Y_2 += T.ShiftY;
                                Y_3 += T.ShiftY;
                                Y_4 += T.ShiftY;
                                Z_1 += T.ShiftZ;
                                Z_2 += T.ShiftZ;
                                Z_3 += T.ShiftZ;
                                Z_4 += T.ShiftZ;
                                for (int j=0; TJumps[j].Shape; j++)
                                        {
                                        if (ABS(TJumps[j].ScaleX) > BY_ZERO)
                                                {
                                                X_1 = X_1*TJumps[j].ScaleX;
                                                X_2 = X_2*TJumps[j].ScaleX;
                                                X_3 = X_3*TJumps[j].ScaleX;
                                                X_4 = X_4*TJumps[j].ScaleX;
                                                }
                                        if (ABS(TJumps[j].ScaleY) > BY_ZERO)
                                                {
                                                Y_1 = Y_1*TJumps[j].ScaleY;
                                                Y_2 = Y_2*TJumps[j].ScaleY;
                                                Y_3 = Y_3*TJumps[j].ScaleY;
                                                Y_4 = Y_4*TJumps[j].ScaleY;
                                                }
                                        if (ABS(TJumps[j].ScaleZ) > BY_ZERO)
                                                {
                                                Z_1 = Z_1*TJumps[j].ScaleZ;
                                                Z_2 = Z_2*TJumps[j].ScaleZ;
                                                Z_3 = Z_3*TJumps[j].ScaleZ;
                                                Z_4 = Z_4*TJumps[j].ScaleZ;
                                                }
                                        Rotate_Vertex(&X_1,&Z_1,-TJumps[j].RotateXZ);
                                        Rotate_Vertex(&X_2,&Z_2,-TJumps[j].RotateXZ);
                                        Rotate_Vertex(&X_3,&Z_3,-TJumps[j].RotateXZ);
                                        Rotate_Vertex(&X_4,&Z_4,-TJumps[j].RotateXZ);
                                        Rotate_Vertex(&Y_1,&Z_1,-TJumps[j].RotateYZ);
                                        Rotate_Vertex(&Y_2,&Z_2,-TJumps[j].RotateYZ);
                                        Rotate_Vertex(&Y_3,&Z_3,-TJumps[j].RotateYZ);
                                        Rotate_Vertex(&Y_4,&Z_4,-TJumps[j].RotateYZ);
                                        Rotate_Vertex(&X_1,&Y_1,TJumps[j].RotateXY);
                                        Rotate_Vertex(&X_2,&Y_2,TJumps[j].RotateXY);
                                        Rotate_Vertex(&X_3,&Y_3,TJumps[j].RotateXY);
                                        Rotate_Vertex(&X_4,&Y_4,TJumps[j].RotateXY);
                                        X_1 += TJumps[j].ShiftX;
                                        Y_1 += TJumps[j].ShiftY;
                                        Z_1 += TJumps[j].ShiftZ;
                                        X_2 += TJumps[j].ShiftX;
                                        Y_2 += TJumps[j].ShiftY;
                                        Z_2 += TJumps[j].ShiftZ;
                                        X_3 += TJumps[j].ShiftX;
                                        Y_3 += TJumps[j].ShiftY;
                                        Z_3 += TJumps[j].ShiftZ;
                                        X_4 += TJumps[j].ShiftX;
                                        Y_4 += TJumps[j].ShiftY;
                                        Z_4 += TJumps[j].ShiftZ;
                                        }
                                Rotate_Vertex(&X_1, &Z_1, 180);
                                Rotate_Vertex(&X_2, &Z_2, 180);
                                Rotate_Vertex(&X_3, &Z_3, 180);
                                Rotate_Vertex(&X_4, &Z_4, 180);
                              /*  X_1 -= centroid__X;
                                X_2 -= centroid__X;
                                X_3 -= centroid__X;
                                X_4 -= centroid__X;
                                Y_1 -= centroid__Y;
                                Y_2 -= centroid__Y;
                                Y_3 -= centroid__Y;
                                Y_4 -= centroid__Y;  */
                                if (_3d)
                                        {
                                        Rotate3d(&X_1,&Y_1,&Z_1,&X_2,&Y_2,&Z_2,&X_3,&Y_3,&Z_3,&X_4,&Y_4,&Z_4);
                                        }
                                if (!CANVAS_TO_FILE)
                                        {
                                        FACES[fcs] = CI;
                                        FACES[fcs+1] = X_1;
                                        FACES[fcs+2] = Y_1;
                                        FACES[fcs+3] = Z_1;
                                        FACES[fcs+4] = X_2;
                                        FACES[fcs+5] = Y_2;
                                        FACES[fcs+6] = Z_2;
                                        FACES[fcs+7] = X_4;
                                        FACES[fcs+8] = Y_4;
                                        FACES[fcs+9] = Z_4;
                                        FACES[fcs+10] = X_3;
                                        FACES[fcs+11] = Y_3;
                                        FACES[fcs+12] = Z_3;
                                        fcs = fcs + 13;
                                        if (fcs > MAX_FACES_AND_LINES) return WARNING_OF_MEMORY;
                                        (*SELRECT).Left = MIN4(X_1, X_2, X_3, (*SELRECT).Left );
                                        (*SELRECT).Left = MIN(X_4, (*SELRECT).Left );
                                        (*SELRECT).Right = MAX4(X_1, X_2, X_3, (*SELRECT).Right );
                                        (*SELRECT).Right = MAX(X_4, (*SELRECT).Right );
                                        (*SELRECT).Bottom = MIN4(Y_1, Y_2, Y_3, (*SELRECT).Bottom );
                                        (*SELRECT).Bottom = MIN(Y_4, (*SELRECT).Bottom );
                                        (*SELRECT).Top = MAX4(Y_1, Y_2, Y_3, (*SELRECT).Top );
                                        (*SELRECT).Top = MAX(Y_4, (*SELRECT).Top );
                                        }
                                else if (Form3->RadioButton3->Checked)
                                        {
                                        W_SOLID_BLK(X_1,Y_1,Z_1,  X_2,Y_2,Z_2,  X_3,Y_3,Z_3,  X_4,Y_4,Z_4, CL_3DBOTTOM, LB );
                                        }
                                else    {
                                        W_LINE_BLK(X_1,Y_1,Z_1,  X_2,Y_2,Z_2, CL_3DBOTTOM, LB );
                                        W_LINE_BLK(X_3,Y_3,Z_3,  X_4,Y_4,Z_4, CL_3DBOTTOM, LB );
                                        W_LINE_BLK(X_1,Y_1,Z_1,  X_3,Y_3,Z_3, CL_3DBOTTOM, LB );
                                        W_LINE_BLK(X_2,Y_2,Z_2,  X_4,Y_4,Z_4, CL_3DBOTTOM, LB );
                                        }
                                }
                        }
                X__1 = X__2;
                Y__1 = Y__2;
                }
        }
return 0;
}
//---------------------------------------------------------------------------