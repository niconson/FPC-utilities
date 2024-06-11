//---------------------------------------------------------------------------

#ifndef Path_EXEH
#define Path_EXEH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
        TGroupBox *GroupBoxPath;
        TGroupBox *GroupBox1;
        TMemo *Memo1;
        TLabel *Label1;
        TCheckBox *mem_pos_wnd;
        TGroupBox *GroupBox2;
        TGroupBox *GroupBox3;
        TRadioButton *OnTop;
        TRadioButton *OnTheRight;
        TCheckBox *IgnoreCase;
        TCheckBox *Language;
        TCheckBox *OnlyLatin;
        TGroupBox *GroupBox4;
        TRadioButton *FreePos;
        TRadioButton *FromBelow;
        TCheckBox *check_refs;
        TCheckBox *check_ref_index;
        TCheckBox *check_values;
        TCheckBox *check_valuesNL;
        TCheckBox *check_package;
        TCheckBox *check_foot;
        TCheckBox *check_packageNL;
        TCheckBox *check_merge;
        TCheckBox *check_parts_pins;
        TCheckBox *check_parts_holes;
        TCheckBox *check_glueds;
        TCheckBox *check_sides;
        TCheckBox *check_angles;
        TCheckBox *check_partx;
        TCheckBox *check_party;
        TCheckBox *check_comp_nlist;
        TGroupBox *GroupBox5;
        TCheckBox *check_pinname;
        TCheckBox *check_netpcb;
        TCheckBox *check_pins_cnt;
        TCheckBox *check_ext_netlist;
        TCheckBox *check_pins_type;
        TCheckBox *check_pins_w;
        TCheckBox *check_pins_l;
        TCheckBox *check_thrml;
        TCheckBox *check_holes_diam;
        TCheckBox *check_paste;
        TCheckBox *check_pinsx;
        TCheckBox *check_pinsy;
        TCheckBox *check_vias;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall LanguageClick(TObject *Sender);
        void __fastcall check_viasClick(TObject *Sender);
        void __fastcall Label1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
