//---------------------------------------------------------------------------

#ifndef LoadingNetsH
#define LoadingNetsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TOpenDialog *OpenDialog1;
        TListBox *ListBox1;
        TTimer *Timer1;
        TTimer *Timer2;
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall Timer2Timer(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
extern int M;
extern int EN_net;
extern int n_str;
extern long prob (AnsiString ANSI , long Pr);
extern AnsiString ex_str (AnsiString ANSI, long *n);
extern double ex_float (AnsiString Str, long *index);
extern void INI(AnsiString CLPBRD);
//---------------------------------------------------------------------------
#endif
