//---------------------------------------------------------------------------

#ifndef DXF_3DH
#define DXF_3DH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include "CSPIN.h"
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TCheckBox *CheckBox1;
        TButton *Button1;
        TOpenDialog *OpenDialog1;
        TLabel *Label11;
        TLabel *Label16;
        TLabel *Label17;
        TGroupBox *GroupBox1;
        TLabel *Label1;
        TCheckBox *CheckBox2;
        TCSpinEdit *CSpinEdit1;
        TLabel *Label2;
        TCSpinEdit *CSpinEdit2;
        TLabel *Label7;
        TCSpinEdit *CSpinEdit3;
        TGroupBox *GroupBox2;
        TLabel *Label8;
        TCSpinEdit *CSpinEdit4;
        TCheckBox *CheckBox3;
        TCheckBox *CheckBox4;
        TLabel *Label3;
        TCSpinEdit *CSpinEdit5;
        TCheckBox *CheckBox5;
        TCheckBox *CheckBox6;
        TCheckBox *CheckBox7;
        TLabel *Label4;
        TCSpinEdit *CSpinEdit6;
        TCheckBox *CheckBox8;
        TLabel *Label5;
        TCSpinEdit *CSpinEdit7;
        TCheckBox *CheckBox9;
        TLabel *Label6;
        TCSpinEdit *CSpinEdit8;
        TCheckBox *CheckBox10;
        TLabel *Label9;
        TCSpinEdit *CSpinEdit9;
        TCheckBox *CheckBox11;
        TLabel *Label10;
        TCSpinEdit *CSpinEdit10;
        TCheckBox *CheckBox12;
        TCheckBox *CheckBox13;
        TCheckBox *CheckBox14;
        TLabel *Label12;
        TCSpinEdit *CSpinEdit11;
        TGroupBox *GroupBox3;
        TLabel *Label13;
        TCSpinEdit *CSpinEdit12;
        TCheckBox *CheckBox15;
        TCheckBox *CheckBox16;
        TCheckBox *CheckBox17;
        TGroupBox *GroupBox4;
        TLabel *Label14;
        TCSpinEdit *CSpinEdit13;
        TCheckBox *CheckBox18;
        TCheckBox *CheckBox19;
        TCheckBox *CheckBox20;
        TCheckBox *CheckBox21;
        TCheckBox *CheckBox22;
        TCheckBox *CheckBox23;
        TLabel *Label15;
        TCSpinEdit *CSpinEdit14;
        TStringGrid *StringGrid1;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall CheckBox1Click(TObject *Sender);
        void __fastcall Label11MouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall CheckBox6MouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall CheckBox11MouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
extern void Rotate_Vertex (double *X, double *Y, double Ang);
extern AnsiString ex_str (AnsiString ANSI, long *n);
//extern long i;
//extern AnsiString A;
///extern float ex_float (long index);
//---------------------------------------------------------------------------
#endif
