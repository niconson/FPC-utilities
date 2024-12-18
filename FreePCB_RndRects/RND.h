//---------------------------------------------------------------------------

#ifndef RNDH
#define RNDH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <ComCtrls.hpp>
#include <jpeg.hpp>
#define ABS(A)                ((A)<0  ? (-(A)) : (A))
#define MAX(A, B)             ((A)>(B) ? (A) : (B))
#define MIN(A, B)             ((A)<(B) ? (A) : (B))
#define MAX3(A, B, C)         ((A)>(B) ? ((A)>(C) ? (A) : (C)) : ((B)>(C) ? (B) : (C)))
#define MIN3(A, B, C)         ((A)<(B) ? ((A)<(C) ? (A) : (C)) : ((B)<(C) ? (B) : (C)))
#define MAX4(A, B, C, D)      ((A)>(D) ? ((A)>(B) ? ((A)>(C) ? (A) : (C)) : ((B)>(C) ? (B) : (C))) : ((D)>(B) ? ((D)>(C) ? (D) : (C)) : ((B)>(C) ? (B) : (C))))
#define MIN4(A, B, C, D)      ((A)<(D) ? ((A)<(B) ? ((A)<(C) ? (A) : (C)) : ((B)<(C) ? (B) : (C))) : ((D)<(B) ? ((D)<(C) ? (D) : (C)) : ((B)<(C) ? (B) : (C))))
#define SWAP(A, B)            {(A)=(A)^(B); (B)=(B)^(A); (A)=(A)^(B);}
#define DEFAULT 1073741823.0
#define BY_ZERO 0.001
#define _MM_TO_NM 1000000.0
#define _25400 25400.0
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label5;
        TImage *Image2;
        TOpenDialog *OpenDialog1;
        TTimer *Timer1;
        TCheckBox *EnableRndPads;
        TCheckBox *EnableRndTrace;
        TCheckBox *EnableRndArea;
        TCheckBox *EnableOvalVia;
        TListBox *ListBox1_pins;
        TListBox *ListBox2_Shape;
        TListBox *ListBox3_PinsOfNet;
        TCheckBox *ReplaceOrFile;
        TCheckBox *EnableOvalPads;
        TProgressBar *ProgressBar1;
        TTabSheet *TabSheet1;
        TTabSheet *TabSheet2;
        TTabSheet *TabSheet3;
        TTabSheet *TabSheet4;
        TTabSheet *TabSheet5;
        TPageControl *Control;
        TPanel *Panel3;
        TRadioButton *PadsRadiusConstant;
        TComboBox *ValuePadsRadiusConstant;
        TRadioButton *PadsRadiusShare;
        TComboBox *ValuePadsRadiusShare;
        TGroupBox *GroupBox1;
        TRadioButton *RectPads;
        TRadioButton *RndRectPads;
        TCheckBox *OnlyR;
        TPanel *Panel2;
        TRadioButton *TraceRadiusConstant;
        TRadioButton *TraceRadiusShare;
        TComboBox *ValueTraceRadiusConstant;
        TComboBox *ValueTraceRadiusShare;
        TGroupBox *GroupBox3;
        TRadioButton *TraceSame3;
        TRadioButton *TraceSame4;
        TRadioButton *TraceSame5;
        TRadioButton *TraceSame2;
        TGroupBox *MinimumLengthTrace;
        TComboBox *ValueMinLengthTrace;
        TRadioButton *TraceRadiusShareW;
        TComboBox *ValueTraceRadiusShareW;
        TPanel *Panel1;
        TRadioButton *AreaRadiusConstant;
        TRadioButton *AreaRadiusShare;
        TComboBox *ValueAreaRadiusShare;
        TComboBox *ValueAreaRadiusConstant;
        TGroupBox *GroupBox7;
        TRadioButton *Area3;
        TRadioButton *Area4;
        TRadioButton *Area5;
        TRadioButton *Area2;
        TCheckBox *RndContour;
        TCheckBox *RndCutouts;
        TCheckBox *forNone;
        TCheckBox *forFull;
        TCheckBox *forEdge;
        TGroupBox *MinLengthArea;
        TComboBox *ValueMinLengthArea;
        TPanel *Panel4;
        TLabel *Label7;
        TLabel *Label8;
        TLabel *Label9;
        TLabel *Label10;
        TComboBox *DiaVia;
        TComboBox *LengthVia;
        TCheckBox *NewStyle;
        TPanel *Panel5;
        TLabel *LengthPads;
        TLabel *Label6;
        TComboBox *ValueLengthPads;
        TCheckBox *RoundedPads;
        TCheckBox *RectanglePads;
        TCheckBox *AutoCorrRad;
        TCheckBox *AutoCorrWid;
        TCheckBox *EnLocked;
        TCheckBox *TracesOfParts;
        TListBox *PartList;
        TLabel *Label1;
        TGroupBox *GroupBox2;
        TEdit *WRangeMin;
        TEdit *WRangeMax;
        TButton *Button2;
        TLabel *Label3;
        TGroupBox *GroupBox4;
        TEdit *WAngmin;
        TEdit *WAngmax;
        TLabel *Label2;
        TImage *Image1;
        TLabel *ToTry;
        TLabel *UploadAnotherFile;
        TLabel *Label12;
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall TracesOfPartsClick(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Label2Click(TObject *Sender);
        void __fastcall UploadAnotherFileClick(TObject *Sender);
        void __fastcall ToTryClick(TObject *Sender);
        void __fastcall Image2MouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
        void __fastcall ToTryMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
        void __fastcall ReplaceOrFileClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
extern double D;
extern char s[2500];
extern double F;
extern double X_NEW[32];
extern double Y_NEW[32];
extern void RoundingRect (void);
extern long PROB (AnsiString ANSI , long Pr);
extern double ex_float (AnsiString Str, long *index);
extern int RND_FUNC(    double X1,
                        double Y1,
                        double X2,
                        double Y2,
                        double X3,
                        double Y3,
                        double R,
                        float Share,
                        int CountNew,
                        double MinSeg,
                        double Pad1,
                        double Pad2,
                        int Angmin,
                        int Angmax);
extern int count_seg (AnsiString B2, long num_str);
extern bool VIA_FUNC(   double X1,
                        double Y1,
                        double X2,
                        double Y2,
                        double X3,
                        double Y3,
                        double SizeVia,
                        double DVia,
                        double LenVia,
                        double W1,
                        double W2,
                        bool NewStyle,
                        bool RND=1);
extern double Length_Line (double X1, double Y1, double X2, double Y2);
extern float Angle (double dx, double dy);
extern AnsiString ex_str (AnsiString ANSI, long *n);
extern void Rotate_Vertex (double *X, double *Y, double Ang);
extern void Rotate_f_Vertex (float *X, float *Y, float Ang);
int Test_angle_between (        double x1, //point 1
                                double y1,
                                double x2, //point next
                                double y2,
                                double x3, //point next next
                                double y3, int mode);
//---------------------------------------------------------------------------
#endif
