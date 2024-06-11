//---------------------------------------------------------------------------

#ifndef Obj_ManH
#define Obj_ManH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TObjMan : public TForm
{
__published:	// IDE-managed Components
        TComboBox *Find;
        TEdit *TextFind;
        TListBox *ListBoxObjMan;
private:	// User declarations
public:		// User declarations
        __fastcall TObjMan(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TObjMan *ObjMan;
//---------------------------------------------------------------------------
#endif
