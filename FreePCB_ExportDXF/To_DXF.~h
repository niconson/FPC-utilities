//---------------------------------------------------------------------------

#ifndef To_DXFH
#define To_DXFH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>                   
#include <ComCtrls.hpp>
//
#define setbit(reg,bit) reg|=(1<<bit)
#define getbit(reg,bit) ((reg & (1<<bit)) ? 1 : 0)
//
#define PER_MIL         25400.0
#define INV_PER_MIL     0.0254
#define PER_MM          1000000.0
#define GET_DATA        1
#define SET_RECTS       3
#define CANVAS          4
#define RESET           0
#define NUMBER_OF_TJumps  10
#define JUMP_NOT_FOUND    -1
#define WARNING_OF_MEMORY -2
#define TOP             false
#define BOTTOM          true
#define CL_BOARD        0
#define CL_TOPPADS      1
#define CL_TOPLINES     2
#define CL_TOPAREAS     3
#define CL_TOPMASK      4
#define CL_TOPPASTE     5
#define CL_TOPSILK      6
#define CL_BOTPADS      7
#define CL_BOTLINES     8
#define CL_BOTAREAS     9
#define CL_BOTMASK      10
#define CL_BOTPASTE     11
#define CL_BOTSILK      12
#define CL_3DTOP        13
#define CL_3DBOTTOM     14
#define CL_VIAS         15
#define CL_VIA_HOLES    16
#define CL_HOLES        17
#define lr_top          1
#define lr_bottom       2
#define lr_drl          3
#define lr_silk         4
#define tp_empty        0
#define tp_round        1
#define tp_square       2
#define tp_rect         3
#define tp_rndrect      4
#define tp_oval         5
#define tp_octagon      6
#define tp_line         7
#define tp_arc_cw       8
#define tp_arc_ccw      9
#define tp_point        10
#define SH__NONE         0
#define SH__OVAL        1
#define SH__RECT        2
#define SH__SILK        3
#define SH__ARC         4
#define SH__PIN         5
#define SH__SECTOR      6
#define SH__TRIANGLE    7
#define SH__SPIRAL      8
#define SH__FACET       9
#define LT              "3d_top"
#define LB              "3d_bottom"
#define LT_COPP         15
#define LB_COPP         16
#define FP_TOP_COPPER   13
#define FP_BOT_COPPER   15
//
#define ABS(A)                ((A)<0  ? (-(A)) : (A))
#define MAX(A, B)             ((A)>(B) ? (A) : (B))
#define MIN(A, B)             ((A)<(B) ? (A) : (B))
#define MAX3(A, B, C)         ((A)>(B) ? ((A)>(C) ? (A) : (C)) : ((B)>(C) ? (B) : (C)))
#define MIN3(A, B, C)         ((A)<(B) ? ((A)<(C) ? (A) : (C)) : ((B)<(C) ? (B) : (C)))
#define MAX4(A, B, C, D)      ((A)>(D) ? ((A)>(B) ? ((A)>(C) ? (A) : (C)) : ((B)>(C) ? (B) : (C))) : ((D)>(B) ? ((D)>(C) ? (D) : (C)) : ((B)>(C) ? (B) : (C))))
#define MIN4(A, B, C, D)      ((A)<(D) ? ((A)<(B) ? ((A)<(C) ? (A) : (C)) : ((B)<(C) ? (B) : (C))) : ((D)<(B) ? ((D)<(C) ? (D) : (C)) : ((B)<(C) ? (B) : (C))))
#define SWAP(A, B)            {(A)=(A)^(B); (B)=(B)^(A); (A)=(A)^(B);}
#define DEFAULT 1073741823
#define BY_ZERO 0.00001
#define _103    1000
#define _106    1000000
#define _109    1000000000
#define N_PARAM 14
#define DEF_CHAR 2500
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TCheckBox *CheckBox1;
        TCheckBox *CheckBox2;
        TCheckBox *CheckBox3;
        TCheckBox *CheckBox4;
        TCheckBox *CheckBox5;
        TCheckBox *CheckBox6;
        TCheckBox *CheckBox8;
        TCheckBox *CheckBox9;
        TCheckBox *CheckBox10;
        TCheckBox *CheckBox11;
        TCheckBox *CheckBox12;
        TCheckBox *CheckBox14;
        TCheckBox *CheckBox15;
        TButton *Button1;
        TButton *Button2;
        TListBox *OutputBox;
        TCheckBox *CheckBox16;
        TCheckBox *CheckBox17;
        TButton *Button3;
        TOpenDialog *OpenDialog1;
        TListBox *File;
        TCheckBox *CheckBox7;
        TCheckBox *CheckBox13;
        TButton *Button4;
        TGroupBox *GroupBox1;
        TListBox *Parts;
        TListBox *Blocks;
        TLabel *Label1;
        TListBox *NamesOfBlocks;
        TGroupBox *GroupBox2;
        TListBox *Nets;
        TCheckBox *AllP;
        TCheckBox *CheckBox19;
        TGroupBox *GroupBox3;
        TRadioButton *RadioButton1;
        TRadioButton *RadioButton2;
        TCheckBox *InsideBRD;
        TCheckBox *CheckBox18;
        TLabel *Label2;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall AllPClick(TObject *Sender);
        void __fastcall CheckBox19Click(TObject *Sender);
        void __fastcall Label2Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
        void Ini();
};
struct FloatPoint
        {
        double x;
        double y;
        bool Flag;
        };
struct myRect
        {
        float Left;
        float Right;
        float Top;
        float Bottom;
        float _Low;
        float _High;
        };
class myRectInt
        {
        public:
        int Left;
        int Right;
        int Top;
        int Bottom;
        int _Low;
        int _High;
        void ini (void)
                {
                Left = 0; Bottom = 0; _Low = 0;
                Right = 0; Top = 0; _High = 0;
                }
        };
struct JumpData_struct
        {
        int J;
        int min;
        int max;
        };
class Table_struct
        {
        public:
        int   Shape;
        float ScaleX;
        float ScaleY;
        float ScaleZ;
        float SizeX;
        float SizeY;
        float SizeZ;
        float RotateXY;
        float RotateYZ;
        float RotateXZ;
        float ShiftX;
        float ShiftY;
        float ShiftZ;
        void ini (void)
                {
                Shape = 0;
                ScaleX = 0;     ScaleY = 0;     ScaleZ = 0;
                SizeX = 0;      SizeY = 0;      SizeZ = 0;
                RotateXY = 0;   RotateYZ = 0;   RotateXZ = 0;
                ShiftX = 0;     ShiftY = 0;     ShiftZ = 0;
                }
        };
class canvas_data_struct
        {
        public:
        int x;
        int y;
        int xn;
        int yn;
        int w;
        int lay;
        int type;
        int angle;
        void ini (void)
                {
                x=0; y=0; xn=0; yn=0; w=0; lay=0; type=0; angle = 0.0;
                };   
        };
class mPart
        {
        public:
        float * Faces;
        float * Lines;
        void ini (void)
                {

                };
        };
//
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
extern TRect Fill_Rect;
extern TRect SaveRect;
extern myRectInt * SizeRects;
extern AnsiString NO_UNITS;
extern AnsiString NO_PACKAGE;
extern float BoardThick;
extern float default_mask_clearance;
extern float default_paste_clearance;
extern float GlobalScaleFactor;
extern int CLR;
extern int GlobalShiftX;
extern int GlobalShiftY;
extern int GlobalCurveXY;
extern int GlobalCurveXZ;
extern int GlobalCurveYZ;
extern int StartGCXZ;
extern int StartGCYZ;
extern int StartGCXY;
extern int mouseStartX;
extern int mouseStartY;
extern int IndexFoot;
extern int IndexParts;
extern int IndexBoard;
extern int IndexNets;
extern int StringGridIndexRow;
extern int MAX_FACES_AND_LINES;
extern bool CTRL;
extern bool SHIFT;
extern bool CANVAS_TO_FILE;
extern float BrdRectLeft ;
extern float BrdRectTop ;
extern float BrdRectRight ;
extern float BrdRectBottom ;
//
extern int * MARKS;
extern int * LABELS;
extern float * FACES;
extern int * LINES;
extern canvas_data_struct * canvas_data;
//
extern AnsiString Str_Float_Format (AnsiString STRING_2_DOUBLE);
extern AnsiString ex_str (AnsiString ANSI, long *n);
extern AnsiString F_str (float DBL);
extern void W_LINE (    float x1,float y1,float z1,
                        float x2,float y2,float z2,
                        int Color,AnsiString Layer);
extern void W_LWPOLYLINE (      float x1, float y1,
                                float x2, float y2,
                                float W, float Bulge,
                                float Elevation, float Thickness,
                                int Color, AnsiString Layer);
extern void W_SOLID (   float x1,float y1,float z1,float x2,float y2,float z2,
                        float x3,float y3,float z3,float x4,float y4,float z4,
                        int Color,AnsiString Layer);
extern void W_CIRCLE (  float x,float y,float z,float R,
                        int Color,AnsiString Layer);
extern long prob (AnsiString ANSI , long Pr);
extern float ex_float (AnsiString Str, long *index);
extern float ex_float_NM (AnsiString Str, long *index, AnsiString *UnitS /*NM, MM or MIL*/);
extern int Generate_Line (float X, float Y, float X2, float Y2,  int type_L , float *OutPut);
extern float Angle (float dx, float dy, float x0, float y0);
extern float Length_Line (float X1, float Y1, float X2, float Y2, float Z1=0, float Z2=0);
extern void Rotate_Vertex (float *X, float *Y, float Ang);
extern TPoint Print_Part (AnsiString Part, bool GetPos=false);
extern void mirror_angle (float Part_angle, bool Part_layer, float *X, float *Y);
extern void Canvas_Pads ( float *PARAM, AnsiString LAYER_NAME, int MM, int COLOR);
extern int InsertBlock (int N_STR, int ROT, bool SIDE, myRect * SELRECT, int HeadIndex, int BranchIndex, int StartIndex, int EndIndex, bool _3d=0);
extern void GetRects (void);
extern void CanvasAll(int MODE);
extern void W_LINE_BLK (   float x1,
                float y1,
                float z1,
                float x2,
                float y2,
                float z2,
                int Color,
                AnsiString Layer
                );
extern void W_SOLID_BLK (  float x1,
                float y1,
                float z1,
                float x2,
                float y2,
                float z2,
                float x3,
                float y3,
                float z3,
                float x4,
                float y4,
                float z4,
                int Color,
                AnsiString Layer
                );
extern bool Canva (int Mode);
extern int SwellMem (void);
extern void MOD (AnsiString * mod);
extern void ShiftSizeRectsArrow (int i, int shift);
extern void RotatePoints(TPoint * P, int npoints, float angle);
extern int Gen_RndRectPoly (int x, int y, int dx, int dy, float rad, float ang, TPoint * OutPut, int npoints );
extern bool CheckPartOfPart( AnsiString * part );
extern int WhereElseIsThisPartUsed( AnsiString * part, TListBox * pList );
//---------------------------------------------------------------------------
#endif
