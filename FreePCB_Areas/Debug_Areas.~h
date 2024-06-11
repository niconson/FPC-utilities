//---------------------------------------------------------------------------

#ifndef Debug_AreasH
#define Debug_AreasH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Dialogs.hpp>
#include <math.h>
#include <Buttons.hpp>
#include "Combine.h"
#define PER_MIL                 39.37007874015748
#define ABS(A)                  ((A)<0  ? (-(A)) : (A))
#define MAX(A, B)               ((A)>(B) ? (A) : (B))
#define MIN(A, B)               ((A)<(B) ? (A) : (B))
#define MAX3(A, B, C)           ((A)>(B) ? ((A)>(C) ? (A) : (C)) : ((B)>(C) ? (B) : (C)))
#define MIN3(A, B, C)           ((A)<(B) ? ((A)<(C) ? (A) : (C)) : ((B)<(C) ? (B) : (C)))
#define MAX4(A, B, C, D)        ((A)>(D) ? ((A)>(B) ? ((A)>(C) ? (A) : (C)) : ((B)>(C) ? (B) : (C))) : ((D)>(B) ? ((D)>(C) ? (D) : (C)) : ((B)>(C) ? (B) : (C))))
#define MIN4(A, B, C, D)        ((A)<(D) ? ((A)<(B) ? ((A)<(C) ? (A) : (C)) : ((B)<(C) ? (B) : (C))) : ((D)<(B) ? ((D)<(C) ? (D) : (C)) : ((B)<(C) ? (B) : (C))))
//#define IN_RANGE (A,B,C)	((B)>(C) ? ((A)>(C) ? ((A)<(B) ?  1  :  0 ) : 0 ) : ((A)>(B) ? ((A)<(C) ? 1 : 0 ) : 0 ))
#define TT_DEF          0
#define TT_NC           1
#define TT_T            2
#define TT_NT           3
//
#define SWAP(A, B)              {(A)=(A)^(B); (B)=(B)^(A); (A)=(A)^(B);}
#define DEFAULT                 1073741823.0
#define BY_ZERO                 0.00001
#define TOP_LAYER               0
#define BOTTOM_LAYER            1
#define INNER_LAYER             2
#define ALL_LAYERS              3
#define LR_TOP                  15
#define LR_BOT                  16
#define NONE_PAD                0
#define ROUND_PAD               1
#define SQUARE_PAD              2
#define RECT_PAD                3
#define RND_RECT_PAD            4
#define OVAL_PAD                5
#define OCTAGON_PAD             6
#define C_AREA_CUT              0
#define C_BOARD_CUT             1
#define IS_LINE                 1
#define IS_PAD                  0
//
#define BOTTOM                  0
#define LEFT                    2
#define RIGHT                   3
#define END                     4
#define GEN_ARC_NUM_CORNERS     12
#define _101                    9
#define _102                    99
#define _777                    777
#define _103                    1000
#define _2541                   2540
#define _5x103                  5000
#define _104                    10000
#define _2542                   25400
#define _105                    100000
#define _106                    1000000
#define MM_5                    5000000
#define MM_10                   10000000
#define MM_100                  100000000
#define CORR_CL 1.02
#define dir___CW      -1
#define dir___CCW     1
#define uMM     2
#define uNM     1
#define uMIL    0
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TGroupBox *GroupBox1;
        TGroupBox *GroupBox4;
        TEdit *Edit3;
        TTimer *Timer1;
        TOpenDialog *OpenDialog1;
        TCheckBox *cl_brd;
        TCheckBox *replace;
        TGroupBox *GroupBox5;
        TRadioButton *Rect;
        TRadioButton *Romb;
        TLabel *Label5;
        TLabel *Label7;
        TEdit *Edit4;
        TEdit *Edit5;
        TEdit *Edit6;
        TLabel *Label4;
        TLabel *Label8;
        TLabel *Label9;
        TLabel *Label10;
        TImage *Image2;
        TImage *Image4;
        TListBox *File;
        TListBox *PinNets;
        TCheckBox *cl_pins;
        TGroupBox *GroupBox6;
        TRadioButton *Low;
        TRadioButton *High;
        TCheckBox *dwg;
        TCheckBox *inv;
        TCheckBox *repour;
        TEdit *Edit_cl_pins;
        TEdit *Edit_cl_brd;
        TCheckBox *cl_areas;
        TEdit *Edit_cl_areas;
        TGroupBox *GroupBox2;
        TListBox *NetsBox;
        TRadioButton *AutoSelect;
        TRadioButton *Manual;
        TCheckBox *through;
        TCheckBox *Stagger;
        TListBox *InversionAreas;
        TListBox *InversionCutouts;
        TEdit *ClipB;
        TBitBtn *BitBtn1;
        TListBox *WRITEFPC;
        TListBox *ONLY;
        TGroupBox *GroupBox3;
        TRadioButton *V;
        TRadioButton *H;
        TCheckBox *cl_thrmlp;
        TEdit *Edit_cl_thrmlp;
        TCheckBox *width;
        TEdit *Edit_width;
        TLabel *Label2;
        TEdit *Edit_cl_sm;
        TCheckBox *cl_sm;
        TLabel *ShLog;
        TLabel *find_areas;
        TButton *bSelectAll;
        TCheckBox *cl_holes;
        TEdit *Edit_cl_holes;
        TLabel *Link;
        TLabel *Label3;
        TLabel *Label6;
        TGroupBox *GroupBox7;
        TLabel *Label1;
        TCheckBox *cl_th_vias;
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall ShLogMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
        void __fastcall GroupBox1MouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall bSelectAllClick(TObject *Sender);
        void __fastcall LinkMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
        void __fastcall LinkClick(TObject *Sender);
        void __fastcall ShLogClick(TObject *Sender);
        void __fastcall invClick(TObject *Sender);
        void __fastcall dwgClick(TObject *Sender);
        void __fastcall widthClick(TObject *Sender);
        void __fastcall cl_holesClick(TObject *Sender);
        void __fastcall cl_pinsClick(TObject *Sender);
        void __fastcall cl_brdClick(TObject *Sender);
        void __fastcall cl_areasClick(TObject *Sender);
        void __fastcall cl_smClick(TObject *Sender);
        void __fastcall cl_thrmlpClick(TObject *Sender);
        void __fastcall repourClick(TObject *Sender);
        void __fastcall LowClick(TObject *Sender);
        void __fastcall HighClick(TObject *Sender);
        void __fastcall VClick(TObject *Sender);
        void __fastcall HClick(TObject *Sender);
        void __fastcall Edit_widthChange(TObject *Sender);
        void __fastcall Edit_cl_holesChange(TObject *Sender);
        void __fastcall Edit_cl_pinsChange(TObject *Sender);
        void __fastcall Edit_cl_brdChange(TObject *Sender);
        void __fastcall Edit_cl_areasChange(TObject *Sender);
        void __fastcall Edit_cl_smChange(TObject *Sender);
        void __fastcall Edit_cl_thrmlpChange(TObject *Sender);
        void __fastcall Edit3Change(TObject *Sender);
        void __fastcall Edit4Change(TObject *Sender);
        void __fastcall Edit5Change(TObject *Sender);
        void __fastcall Edit6Change(TObject *Sender);
        void __fastcall RombClick(TObject *Sender);
        void __fastcall RectClick(TObject *Sender);
        void __fastcall StaggerClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
        void __fastcall OnWMCopyData(TWMCopyData &Msg);
        int Iof( TListBox * List, AnsiString S, int start, int end );
BEGIN_MESSAGE_MAP
        MESSAGE_HANDLER(WM_COPYDATA, TWMCopyData, OnWMCopyData);
END_MESSAGE_MAP(TForm);
};
class Indexes
        {
        public:
        int Footprints;
        int Board;
        int Sm_cutouts;
        int Parts;
        int Nets;
        int Texts;
        int Merges;
        void RST(void)
                {
                Footprints=-1;
                Board=-1;
                Sm_cutouts=-1;
                Parts=-1;
                Nets=-1;
                Texts=-1;
                Merges=-1;
                }
        };
class CanvasDataPads
        {
        public:
        AnsiString Net;
        int Layer;
        int Tilt;
        int ThermalType;
        int InnerThermal;
        int BottomThermal;
        int Mask;
        int isMask;
        bool isHole;
        bool isVia;
        double sizeX;
        double sizeY;
        double radius;
        double posX;
        double posY;
        double IncAngle;
        void clear (void)
                {
                Net = "";
                Layer = 0;
                Tilt = 0;
                ThermalType = TT_DEF;
                InnerThermal = TT_DEF;
                BottomThermal = TT_DEF;
                Mask = -1;
                isMask = -1;
                isHole = false;
                isVia = false;
                sizeX = 0;
                sizeY = 0;
                radius = 0;
                posX = 0;
                posY = 0;
                IncAngle = 30;
                }
        };
class CanvasDataLines
        {
        public:
        AnsiString Net;
        int Layer;
        double X;
        double Y;
        double XNext;
        double YNext;
        double Wid;
        bool Trace;
        int  Txt;
        int  Board;
        int  Area;
        double angle(void)
                {
                double ANG_s;
                double dx = XNext - X;
                double dy = YNext - Y;
                if (ABS(dx) < BY_ZERO)
                        {
                        if (dy > BY_ZERO)       ANG_s = 90;
                        else if (dy < -BY_ZERO) ANG_s = 270;
                        else                    return 0.0;
                        }
                else
                        {
                        double Dxy = dy/dx;
                        ANG_s = (atan(Dxy))*(double)180/(double)M_PI;
                        if ((dx > 0)&&(dy < 0)) ANG_s = 360 + ANG_s;
                        if (dx < 0) ANG_s = 180 + ANG_s;
                        }
                return ANG_s;
                }
        double posX(void)
                {
                return (X + XNext)/2;
                }
        double posY(void)
                {
                return (Y + YNext)/2;
                }
        void clear (void)
                {
                Net = "";
                Layer = 0;
                X = 0;
                Y = 0;
                XNext = 0;
                YNext = 0;
                Wid = 0;
                Trace = false;
                Board = -1;
                Area = 0;
                Txt = 0;
                }
        };
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
extern AnsiString OpenD;
extern bool FLAG_SWELL_CLEARENCE;
extern MLine * LinesArea;
extern MLine * LinesCut;
extern MPolyLine * Corners;
extern CanvasDataPads * DataPads;
extern CanvasDataLines * DataLines;
extern Indexes JUMP;
extern long CountLinesCut;
extern long CntLnsArea;
extern long Dtpads;
extern long Dtlines;
extern int * PointersToShape;
extern int Memory_of_LinesCut;
extern int nTHERMAL;
extern int gUNITS;
extern int nBO;
extern float annular_ring_for_pins;
extern float annular_ring_for_vias;
extern float GerberClearance;
extern float HoleClearance;
extern float SMClearance;
extern float SMSwell;
extern float DRCCopperToCopper;
extern float ThermalClearance;
extern float ThermalLineWidth;
extern float DRCBoardToCopper;
extern float MaxClearance;
extern TRect TotalRect;
extern TRect AreaRect;
extern TRect BoardRect;
//
extern long prob                (AnsiString ANSI , short int Pr);
extern AnsiString ex_str        (AnsiString ANSI, short int *n);
extern AnsiString Str_Float_Format (AnsiString STRING_2_DOUBLE);
extern float ex_float_NM        (AnsiString Str, short int *index, int units);
extern float p(void);
extern int Inversion            (int cc);
extern int LoadArea             (int ARC);
extern int PointAreaInside      (double X, double Y, MLine * Area, int ncorners );
extern int Generate_Line        (double X,
                                double Y,
                                double X2,
                                double Y2,
                                int type_L,
                                float *OutPut,
                                int inc = 15);
extern bool PointBoardInside    (double X, double Y);
extern double LineAreaInside    (double X,
                                double Y,
                                double X2,
                                double Y2);
extern double Angle             (double dx, double dy, double x0, double y0);
extern double Length_Line       (double X1, double Y1, double X2, double Y2);
extern double Distance          (double X1,
                                double Y1,
                                double X2,
                                double Y2,
                                double X3,
                                double Y3,
                                double X4,
                                double Y4,
                                double *Xout,
                                double *Yout);
extern void CanvasBoard         (void);
extern void CanvasPads          (AnsiString NET_AREA, int LayerArea);
extern void CanvasHoles         (AnsiString NET_AREA, int LayerArea);
extern void CanvasLines         (AnsiString NET_AREA, int LayerArea, int AreaNum, int a_wid);
extern void CanvasAreas         (AnsiString NET_AREA, int LayerArea);
extern void CanvasMask          (AnsiString NET_AREA, int LayerArea);
extern void CanvasThrmlP        (AnsiString NET_AREA, int LayerArea);
extern void Fractional          (AnsiString NET_AREA, int LayerArea);

extern void Generate_Cutout     (float W,
                                float H,
                                float R,
                                float CanvasAng,
                                float IncrementAn,
                                float X,
                                float Y,
                                int n_board,
                                int R_mode=4);
extern void Rotate_Vertex       (double *X, double *Y, double Ang);

extern void LoadingLines        (void);
extern int LinesCutToCornersConverter (void);
extern void Contours            (void);
extern void CornersToLinesAREA_C(int start_index);
extern void SetDirection        ( MLine * LINES, int nlines, int direct );

//---------------------------------------------------------------------------
#endif
