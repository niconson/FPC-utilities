//---------------------------------------------------------------------------

#ifndef DXF_to_FPC_FreePCBH
#define DXF_to_FPC_FreePCBH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>

#define ABS(A)                ((A)<0  ? (-(A)) : (A))
#define MAX(A, B)             ((A)>(B) ? (A) : (B))
#define MIN(A, B)             ((A)<(B) ? (A) : (B))
#define MAX3(A, B, C)         ((A)>(B) ? ((A)>(C) ? (A) : (C)) : ((B)>(C) ? (B) : (C)))
#define MIN3(A, B, C)         ((A)<(B) ? ((A)<(C) ? (A) : (C)) : ((B)<(C) ? (B) : (C)))
#define MAX4(A, B, C, D)      ((A)>(D) ? ((A)>(B) ? ((A)>(C) ? (A) : (C)) : ((B)>(C) ? (B) : (C))) : ((D)>(B) ? ((D)>(C) ? (D) : (C)) : ((B)>(C) ? (B) : (C))))
#define MIN4(A, B, C, D)      ((A)<(D) ? ((A)<(B) ? ((A)<(C) ? (A) : (C)) : ((B)<(C) ? (B) : (C))) : ((D)<(B) ? ((D)<(C) ? (D) : (C)) : ((B)<(C) ? (B) : (C))))
#define SWAP(A, B)            {(A)=(A)^(B); (B)=(B)^(A); (A)=(A)^(B);}
#define DEFAULT 1073741823
#define BY_ZERO 0.001
///#define MILLION 25400
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TOpenDialog *OpenDialog1;
        TButton *Button1;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TImage *Image1;
        TGroupBox *GroupBox1;
        TCheckBox *CheckBox1;
        TLabel *Label1;
        TComboBox *ComboBox2;
        TLabel *Label2;
        TListBox *ComboBox1;
        TGroupBox *GroupBox2;
        TCheckBox *CheckBox4;
        TCheckBox *CheckBox3;
        TEdit *Edit1;
        TCheckBox *CheckBox5;
        TCheckBox *CheckBox6;
        TListBox *Shapes;
        TListBox *Parts;
        TCheckBox *CheckBox7;
        TCheckBox *CheckBox2;
        TLabel *Label6;
        TGroupBox *GroupBox3;
        TRadioButton *MM;
        TRadioButton *MIL;
        TRadioButton *Freeasy;
        TRadioButton *FreePcb;
        void __fastcall CheckBox1Click(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall CheckBox3Click(TObject *Sender);
        void __fastcall Label6Click(TObject *Sender);
        void __fastcall FreeasyClick(TObject *Sender);
        void __fastcall FreePcbClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
extern void Rotate_Vertex (double *X, double *Y, double Ang);
extern AnsiString ex_str (AnsiString ANSI, long *n);
extern AnsiString Str_Float_Format (AnsiString STRING_2_DOUBLE);
//---------------------------------------------------------------------------
#endif
