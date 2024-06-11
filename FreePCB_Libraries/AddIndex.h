//---------------------------------------------------------------------------

#ifndef AddIndexH
#define AddIndexH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
        TButton *OK_ADD_STR;
        TGroupBox *GroupBox1;
        TCheckBox *RadioButtonRef;
        TCheckBox *RadioButtonShape;
        TGroupBox *GroupBox2;
        TRadioButton *AddStr;
        TRadioButton *DelStr;
        TCheckBox *ReplaceOrigFile;
        TGroupBox *GroupBox3;
        TRadioButton *RadioButtonBegin;
        TRadioButton *RadioButtonEnd;
        TLabel *Label1;
        TEdit *Edit1;
        TGroupBox *GroupBox4;
        TRadioButton *ReplaceStr;
        TLabel *Label2;
        TLabel *Label3;
        TEdit *Edit2;
        TEdit *Edit3;
        TCheckBox *InEnd;
        TCheckBox *InBegin;
        void __fastcall OK_ADD_STRClick(TObject *Sender);
        void __fastcall AddStrClick(TObject *Sender);
        void __fastcall ReplaceStrClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
