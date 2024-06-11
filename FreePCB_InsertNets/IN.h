//---------------------------------------------------------------------------

#ifndef INH
#define INH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
#define LAY_TOP_COPPER  15
#define LAY_SILK_TOP    10
#define LAY_TOP_NOTES   7
#define MAX(A, B)             ((A)>(B) ? (A) : (B))
#define MIN(A, B)             ((A)<(B) ? (A) : (B))
#define DEFAULT 999999999
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label3;
        TLabel *Label4;
        TEdit *Edit3;
        TEdit *Edit4;
        TGroupBox *GroupBox1;
        TListBox *ListBox1;
        TButton *Button1;
        TOpenDialog *OpenDialog1;
        TListBox *ListBox2;
        TListBox *ListBox3;
        TButton *Button2;
        TButton *Button3;
        TLabel *Label5;
        TCheckBox *ToRight;
        TCheckBox *Below;
        TLabel *Label6;
        TLabel *Label7;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Label5Click(TObject *Sender);
        void __fastcall ToRightMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall BelowMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
