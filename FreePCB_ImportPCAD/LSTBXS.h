//---------------------------------------------------------------------------

#ifndef LSTBXSH
#define LSTBXSH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
        TListBox *ListBox1_FootPrintsName;
        TLabel *Label1;
        TStringGrid *StringGrid1;
        TButton *Button1;
        TEdit *Edit1;
        TGroupBox *GroupBox1;
        TLabel *Label2;
        TLabel *Label3;
        TEdit *Edit2;
        TEdit *Edit3;
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
