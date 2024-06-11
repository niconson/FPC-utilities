//---------------------------------------------------------------------------

#ifndef Please_waitH
#define Please_waitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#define _2540 2540
//---------------------------------------------------------------------------
class TForm4 : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TImage *Image1;
        TTimer *Timer1;
        TLabel *comment;
        void __fastcall Timer1Timer(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm4(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern bool SendMessage_1(AnsiString WindowName);
extern bool SendMessage_2(AnsiString WindowName);
extern PACKAGE TForm4 *Form4;
//---------------------------------------------------------------------------
#endif
