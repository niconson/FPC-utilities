//---------------------------------------------------------------------------

#ifndef HEADH
#define HEADH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#define MAX_LOC 1200000000
#define SELR 99999999
#define ABS(A)                ((A)<0  ? (-(A)) : (A))
#define MAX(A, B)             ((A)>(B) ? (A) : (B))
#define MIN(A, B)             ((A)<(B) ? (A) : (B))
#define MAX3(A, B, C)         ((A)>(B) ? ((A)>(C) ? (A) : (C)) : ((B)>(C) ? (B) : (C)))
#define MIN3(A, B, C)         ((A)<(B) ? ((A)<(C) ? (A) : (C)) : ((B)<(C) ? (B) : (C)))
#define MAX4(A, B, C, D)      ((A)>(D) ? ((A)>(B) ? ((A)>(C) ? (A) : (C)) : ((B)>(C) ? (B) : (C))) : ((D)>(B) ? ((D)>(C) ? (D) : (C)) : ((B)>(C) ? (B) : (C))))
#define MIN4(A, B, C, D)      ((A)<(D) ? ((A)<(B) ? ((A)<(C) ? (A) : (C)) : ((B)<(C) ? (B) : (C))) : ((D)<(B) ? ((D)<(C) ? (D) : (C)) : ((B)<(C) ? (B) : (C))))
#define SWAP(A, B)            {(A)=(A)^(B); (B)=(B)^(A); (A)=(A)^(B);}
#define MAX_CHARS 2560
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TButton *Button1;
        TGroupBox *GroupBox1;
        TEdit *Edit1;
        TEdit *Edit2;
        TLabel *Label1;
        TLabel *Label2;
        TButton *Button2;
        TButton *Button3;
        TGroupBox *GroupBox3;
        TLabel *Label4;
        TOpenDialog *OpenDialog1;
        TSaveDialog *SaveDialog1;
        TLabel *Label5;
        TButton *Button4;
        TListBox *ListBox1;
        TListBox *ListBox2;
        TListBox *ListBox3_TEXTS;
        TListBox *ListBox4_Lines;
        TListBox *Library;
        TGroupBox *GroupBox4;
        TLabel *Label7;
        TLabel *Label6;
        TComboBox *ComboBox3;
        TComboBox *ComboBox2;
        TLabel *Label3;
        TGroupBox *GroupBox2;
        TCheckBox *TopPaste_2_Board;
        TCheckBox *BotPaste_2_Board;
        TCheckBox *TopAssy_2_Board;
        TCheckBox *BotAssy_2_Board;
        TCheckBox *TopSilk_2_Board;
        TCheckBox *BotSilk_2_Board;
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Edit1Change(TObject *Sender);
        void __fastcall Edit2Change(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall Label3Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
struct PcbLine
        {
        float X1;
        float Y1;
        float X2;
        float Y2;
        float Width;
        int Layer;
        AnsiString Net;
        };
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
extern AnsiString SaveD ;
extern AnsiString OpenD ;
extern AnsiString TimeStr;
extern int UNITS;
extern int MaxLayerNumRef;
extern int IncrementArc;
extern bool FlagWarning1 ;
extern bool FlagWarning3 ;
extern bool FlagWarning5 ;
extern long MAXLONGVALUE;
extern long BRD_RECT[4];
extern long MaxLoc;
//FUNC!
extern AnsiString ex_str (AnsiString ANSI, long *n);
extern long count_stroke_file_func (AnsiString OpenD);
extern void read_net_list(AnsiString OpenD, long CNT);
extern void Read_Part (AnsiString OpenD, long CNT);
///extern bool get_end_PCB (AnsiString STRNG);
extern long prob (AnsiString ANSI , long Pr);
extern double ex_float_NM (AnsiString Str, long *index, int units);
extern int go (AnsiString Ansi, int index, AnsiString S);
extern void Shifting (long Case, AnsiString *DATA, long *Size_of, long Ptr);
extern void Create_Foot (AnsiString OpenD, long CNT);
extern long Generate_ARC (double X, double Y, double X2, double Y2, double x0, double y0, double *OutPut);
extern void Rotate_Vertex (double *X, double *Y, double Ang);
extern void FPC_File_Gen (void);
extern AnsiString Find_net (AnsiString Pin );
extern void Generate_Poly ( double *PARAM, AnsiString NET_name );
extern void CombNetList_and_Area (AnsiString OpenD, long CNT);
extern void Pins_Location (void);
extern void Lines (AnsiString OpenD, long CNT, long MEM);
extern void Areas (AnsiString OpenD, long CNT);
extern bool StrBegin (AnsiString STR1, AnsiString STR2);
extern void RTextStyle (AnsiString TextStyle, long *W, long *H);
extern void CombNetList (AnsiString OpenD, long CNT);
extern double Distance ( double X1,double Y1,double X2,double Y2,double X3,double Y3,double X4,double Y4,double *Xout,double *Yout);     //Точка пересечения
extern void Scob (AnsiString STR, int * SCOB);
//---------------------------------------------------------------------------
#endif
