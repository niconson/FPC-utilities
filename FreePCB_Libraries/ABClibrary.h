//---------------------------------------------------------------------------

#ifndef ABClibraryH
#define ABClibraryH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
#define MLN 1000000
#define ABS(A)                ((A)<0  ? (-(A)) : (A))
#define MAX(A, B)             ((A)>(B) ? (A) : (B))
#define MIN(A, B)             ((A)<(B) ? (A) : (B))
#define MAX3(A, B, C)         ((A)>(B) ? ((A)>(C) ? (A) : (C)) : ((B)>(C) ? B : C))
#define MIN3(A, B, C)         ((A)<(B) ? ((A)<(C) ? (A) : (C)) : ((B)<(C) ? B : C))
#define PAD_ROUND       1
#define PAD_SQUARE      2
#define PAD_RECT        3
#define PAD_RNDRECT     4
#define PAD_OVAL        5
#define PAD_OCTAGON     6
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TEdit *Edit1;
        TGroupBox *GroupBox1;
        TRadioButton *Sort_ABC;
        TRadioButton *Sort_n_pins;
        TButton *Button1;
        TRadioButton *Sort_n_holes;
        TGroupBox *GroupBox3;
        TListBox *ListBox1;
        TLabel *Label7;
        TLabel *Label8;
        TLabel *Label9;
        TEdit *Edit2;
        TEdit *Edit3;
        TEdit *Edit4;
        TSpeedButton *SpeedButton3;
        TButton *bOpenPDF;
        TButton *bOpenLib;
        TTimer *Timer2;
        TOpenDialog *OpenDialog1;
        TListBox *Sname;
        TListBox *Spins;
        TListBox *Sholes;
        TListBox *ListBox5;
        TButton *bEditFoot;
        TListBox *ListBox6;
        TRadioButton *Sort_author;
        TRadioButton *Sort_desc;
        TListBox *Sauthor;
        TListBox *Sdescript;
        TButton *R;
        TLabel *Label3;
        TImage *Image1;
        TGroupBox *GroupBox2;
        TButton *Button2;
        TLabel *Button8;
        TGroupBox *GroupBox4;
        TRadioButton *RadioButton6;
        TRadioButton *RadioButton7;
        TRadioButton *RadioButton8;
        TRadioButton *RadioButton9;
        TRadioButton *RadioButton10;
        TRadioButton *RadioButton11;
        TRadioButton *RadioButton12;
        TCheckBox *CheckBox2;
        TButton *bCombFoot;
        TButton *bAddRefStr;
        TButton *bAddShapeStr;
        TButton *Button6;
        TButton *Button7;
        TGroupBox *GroupBox5;
        TLabel *Label5;
        TLabel *Label6;
        TLabel *Label12;
        TLabel *Label2;
        TEdit *NameEdit;
        TButton *Mod;
        TEdit *PackageEdit;
        TComboBox *AuthorEdit;
        TComboBox *DescEdit;
        TCheckBox *CheckBox1;
        TLabel *Label10;
        TButton *Button3;
        TButton *bPaste;
        void __fastcall Button1Click(TObject *Sender);
        //void __fastcall SpeedButton1Click(TObject *Sender);
        //void __fastcall SpeedButton2Click(TObject *Sender);
        void __fastcall ListBox1Click(TObject *Sender);
        void __fastcall Sort_ABCClick(TObject *Sender);
        void __fastcall Sort_n_pinsClick(TObject *Sender);
        void __fastcall Sort_n_holesClick(TObject *Sender);
        void __fastcall ListBox1DblClick(TObject *Sender);
        void __fastcall Edit1Change(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Edit2Change(TObject *Sender);
        void __fastcall Edit3Change(TObject *Sender);
        void __fastcall Edit4Change(TObject *Sender);
        void __fastcall CheckBox2Click(TObject *Sender);
        void __fastcall RadioButton6Click(TObject *Sender);
        void __fastcall RadioButton7Click(TObject *Sender);
        void __fastcall RadioButton8Click(TObject *Sender);
        void __fastcall RadioButton9Click(TObject *Sender);
        void __fastcall RadioButton10Click(TObject *Sender);
        void __fastcall RadioButton11Click(TObject *Sender);
        void __fastcall RadioButton12Click(TObject *Sender);
        void __fastcall SpeedButton3Click(TObject *Sender);
        void __fastcall Timer2Timer(TObject *Sender);
        void __fastcall bOpenPDFClick(TObject *Sender);
        void __fastcall bOpenLibClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall Button6Click(TObject *Sender);
        void __fastcall Button8Click(TObject *Sender);
        void __fastcall Button7Click(TObject *Sender);
        void __fastcall bEditFootClick(TObject *Sender);
        void __fastcall bAddRefStrClick(TObject *Sender);
        void __fastcall bAddShapeStrClick(TObject *Sender);
        void __fastcall bCombFootClick(TObject *Sender);
        void __fastcall Sort_authorClick(TObject *Sender);
        void __fastcall Sort_descClick(TObject *Sender);
        void __fastcall RClick(TObject *Sender);
        void __fastcall ModClick(TObject *Sender);
        void __fastcall Label3Click(TObject *Sender);
        void __fastcall FormMouseWheelDown(TObject *Sender,
          TShiftState Shift, TPoint &MousePos, bool &Handled);
        void __fastcall FormMouseWheelUp(TObject *Sender,
          TShiftState Shift, TPoint &MousePos, bool &Handled);
        void __fastcall Image1MouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall CheckBox1Click(TObject *Sender);
        void __fastcall bPasteClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
        int __fastcall OnWMCopyData(TWMCopyData &Msg);
BEGIN_MESSAGE_MAP
        MESSAGE_HANDLER(WM_COPYDATA, TWMCopyData, OnWMCopyData);
END_MESSAGE_MAP(TForm);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
extern float DEFAULT;
extern AnsiString A;
extern AnsiString NO_UNITS;
extern AnsiString FileName;
extern AnsiString *HEADERS;
extern AnsiString *footprints;
extern int *n_str;
extern int *end_str;
extern bool gLocked;
extern void     GenBuf          ( void );
extern void     KEY             (AnsiString KEY, bool KeyDown, bool KeyUp, int Pause);
extern void     Replace         (AnsiString Name, long StartIndex, long EndIndex);
extern void     ResetShape      (AnsiString Name, long StartIndex, long EndIndex, AnsiString Read, bool Play);
extern AnsiString       ex_str  (AnsiString ANSI, long *n);
extern int      prob            (AnsiString ANSI , int Pr);
extern float    ex_float_NM     (AnsiString Str, long *index, AnsiString *UnitS /*NM, MM or MIL*/);
extern int      Generate_Line   (double X, double Y, double X2, double Y2,  int type_L , float *OutPut);
extern float    Length_Line (float X1, float Y1, float X2, float Y2);
extern void     Rotate_Vertex   (double *X, double *Y, double Ang);
extern long TextLength (AnsiString Text);
extern AnsiString Str_Float_Format (AnsiString STRING_2_DOUBLE);
//---------------------------------------------------------------------------
#endif
