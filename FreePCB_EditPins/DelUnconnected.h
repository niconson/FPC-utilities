//---------------------------------------------------------------------------

#ifndef DelUnconnectedH
#define DelUnconnectedH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>                    
#include <Graphics.hpp>
#define ABS(A)                  ((A)<0  ? (-(A)) : (A))
#define MAX(A, B)               ((A)>(B) ? (A) : (B))
#define MIN(A, B)               ((A)<(B) ? (A) : (B))
#define MAX3(A, B, C)           ((A)>(B) ? ((A)>(C) ? (A) : (C)) : ((B)>(C) ? (B) : (C)))
#define MIN3(A, B, C)           ((A)<(B) ? ((A)<(C) ? (A) : (C)) : ((B)<(C) ? (B) : (C)))
#define MAX4(A, B, C, D)        ((A)>(D) ? ((A)>(B) ? ((A)>(C) ? (A) : (C)) : ((B)>(C) ? (B) : (C))) : ((D)>(B) ? ((D)>(C) ? (D) : (C)) : ((B)>(C) ? (B) : (C))))
#define MIN4(A, B, C, D)        ((A)<(D) ? ((A)<(B) ? ((A)<(C) ? (A) : (C)) : ((B)<(C) ? (B) : (C))) : ((D)<(B) ? ((D)<(C) ? (D) : (C)) : ((B)<(C) ? (B) : (C))))
#define SWAP(A, B)              {(A)=(A)^(B); (B)=(B)^(A); (A)=(A)^(B);}
#define DEFAULT                 999999999
#define BY_ZERO                 0.00001
#define byZero                  0.001
#define MAX_LOC                 30000
#define LAY_TOP                 12
#define LAY_BOT                 13
// PADS
#define PS_NONE                 0
#define PS_CIRC                 1
#define PS_SQUA                 2
#define PS_RECT                 3
#define PS_RREC                 4
#define PS_OVAL                 5
#define PS_OCTA                 6
// THERMAL TYPES
#define TT_DEF                  0
#define TT_NC                   1
#define TT_T                    2
#define TT_NT                   3
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TListBox *AllPins;
        TButton *Button1;
        TListBox *File;
        TOpenDialog *OpenDialog1;
        TListBox *ChangeList;
        TGroupBox *GroupBox3;
        TGroupBox *GroupBox4;
        TGroupBox *GroupBox5;
        TGroupBox *GroupBox1;
        TRadioButton *none_top;
        TRadioButton *round_top;
        TRadioButton *rect_top;
        TRadioButton *octagon_top;
        TLabel *Label2;
        TLabel *Label3;
        TEdit *ShapeHeight_top;
        TEdit *ShapeWidth_top;
        TEdit *ShapeWidth_inner;
        TEdit *ShapeHeight_inner;
        TEdit *ShapeWidth_bottom;
        TEdit *ShapeHeight_bottom;
        TGroupBox *GroupBox8;
        TRadioButton *none_inner;
        TRadioButton *round_inner;
        TRadioButton *rect_inner;
        TRadioButton *octagon_inner;
        TGroupBox *GroupBox6;
        TRadioButton *none_bottom;
        TRadioButton *round_bottom;
        TRadioButton *rect_bottom;
        TRadioButton *octagon_bottom;
        TLabel *Label5;
        TLabel *Label6;
        TLabel *Label8;
        TLabel *Label9;
        TRadioButton *NoChange_top;
        TRadioButton *NoChange_inner;
        TRadioButton *NoChange_bottom;
        TCheckBox *Swell_top;
        TCheckBox *Swell_inner;
        TCheckBox *Swell_bottom;
        TLabel *Label4;
        TEdit *ShapeRadius_top;
        TLabel *Label7;
        TEdit *ShapeRadius_inner;
        TLabel *Label10;
        TEdit *ShapeRadius_bottom;
        TButton *Button2;
        TButton *Button3;
        TLabel *Label11;
        TLabel *Label12;
        TLabel *Label13;
        TLabel *Label14;
        TLabel *Label15;
        TLabel *Label16;
        TLabel *Label17;
        TLabel *Label18;
        TLabel *Label19;
        TListBox *SMTpins;
        TProgressBar *ProgressBar1;
        TGroupBox *GroupBox2;
        TEdit *HoleDiameter_top;
        TLabel *Label1;
        TListBox *EditList;
        TLabel *Label21;
        TButton *Button4;
        TButton *Button5;
        TButton *Button6;
        TListBox *Connected;
        TButton *Button7;
        TEdit *Edit1;
        TGroupBox *GroupBox7;
        TCheckBox *MaskOff;
        TCheckBox *PasteOff;
        TGroupBox *GroupBox9;
        TCheckBox *ThermalCheck;
        TCheckBox *NoThrmlCheck;
        TCheckBox *Replace_original_Pcb_file;
        TImage *Image1;
        TLabel *Label20;
        TButton *Button8;
        TButton *Button9;
        TButton *Button10;
        TListBox *lib_NAMES;
        TListBox *current_net_pins;
        TListBox *loc_NAMES;
        TLabel *Label22;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Swell_topClick(TObject *Sender);
        void __fastcall Swell_innerClick(TObject *Sender);
        void __fastcall Swell_bottomClick(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall Button5Click(TObject *Sender);
        void __fastcall Button6Click(TObject *Sender);
        void __fastcall Button7Click(TObject *Sender);
        void __fastcall Edit1Change(TObject *Sender);
        void __fastcall Edit1KeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall ThermalCheckClick(TObject *Sender);
        void __fastcall NoThrmlCheckClick(TObject *Sender);
        void __fastcall Button8Click(TObject *Sender);
        void __fastcall Button9Click(TObject *Sender);
        void __fastcall Button10Click(TObject *Sender);
        void __fastcall Label22Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
        void __fastcall OnWMCopyData(TWMCopyData &Msg);
BEGIN_MESSAGE_MAP
        MESSAGE_HANDLER(WM_COPYDATA, TWMCopyData, OnWMCopyData);
END_MESSAGE_MAP(TForm);
};
struct Line
        {
        double X1;
        double Y1;
        double X2;
        double Y2;
        int n_cont;
        };
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
extern float ex_float_NM (AnsiString Str, long *index, int units);
extern long prob (AnsiString ANSI , long Pr);
extern AnsiString ex_str (AnsiString ANSI, long *n);
extern AnsiString ex_str_WS (AnsiString ANSI, long *n, AnsiString Sym);
extern AnsiString Str_Float_Format (AnsiString STRING_2_DOUBLE);
extern AnsiString while_not_space (AnsiString ANSI, long *n);
//---------------------------------------------------------------------------
#endif
