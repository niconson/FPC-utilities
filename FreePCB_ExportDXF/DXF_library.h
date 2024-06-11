//---------------------------------------------------------------------------

#ifndef DXF_libraryH
#define DXF_libraryH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>


#define PACKAGES                0
#define SHAPE                   1
#define SIZE_X                  2
#define SIZE_Y                  3
#define SIZE_Z                  4
#define ANGLE_XY                5
#define ANGLE_XZ                6
#define ANGLE_YZ                7
#define SHIFT_X                 8
#define SHIFT_Y                 9
#define SHIFT_Z                 10
#define COL_COUNT               11
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
        TCheckBox *CheckBox1;
        TListBox *Select;
        TPopupMenu *PopupMenu1;
        TMenuItem *CopyObject1;
        TMenuItem *Copy1;
        TMenuItem *DeleteString1;
        TMenuItem *BuildDXF1;
        TMenuItem *SwapCells1;
        TMenuItem *ShowLengthofSides1;
        TMenuItem *Complex1;
        TImage *pDC;
        TMenuItem *InsertEmptyString1;
        TGroupBox *v2d;
        TButton *Button3;
        TButton *Button2;
        TButton *vTop;
        TButton *Button4;
        TButton *Button5;
        TGroupBox *v3d;
        TButton *Button6;
        TButton *Button7;
        TButton *Button8;
        TButton *Button9;
        TPageControl *PageControl1;
        TTabSheet *Viewer;
        TTabSheet *Editor;
        TStringGrid *StringGrid1;
        TGroupBox *GroupBox1;
        TListBox *Used;
        TListBox *FootPrints;
        TListBox *Shapes;
        TProgressBar *ProgressBar1;
        TGroupBox *DrawGpoupObjects;
        TComboBox *DrawGroupList;
        TButton *Draw;
        TGroupBox *GroupBox2;
        TCheckBox *SvLib;
        TGroupBox *GroupBox3;
        TComboBox *GridValues;
        TGroupBox *GroupBox4;
        TEdit *Edit1;
        TButton *DelSel;
        TButton *SelAll;
        void __fastcall StringGrid1GetEditText(TObject *Sender, int ACol,
          int ARow, AnsiString &Value);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall StringGrid1MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall StringGrid1MouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Edit1Change(TObject *Sender);
        void __fastcall StringGrid1MouseWheelDown(TObject *Sender,
          TShiftState Shift, TPoint &MousePos, bool &Handled);
        void __fastcall StringGrid1MouseWheelUp(TObject *Sender,
          TShiftState Shift, TPoint &MousePos, bool &Handled);
        void __fastcall StringGrid1DrawCell(TObject *Sender, int ACol,
          int ARow, TRect &Rect, TGridDrawState State);
        void __fastcall StringGrid1KeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall StringGrid1KeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormMouseWheelDown(TObject *Sender,
          TShiftState Shift, TPoint &MousePos, bool &Handled);
        void __fastcall FormMouseWheelUp(TObject *Sender,
          TShiftState Shift, TPoint &MousePos, bool &Handled);
        void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall CopyObject1Click(TObject *Sender);
        void __fastcall Copy1Click(TObject *Sender);
        void __fastcall DeleteString1Click(TObject *Sender);
        void __fastcall StringGrid1ContextPopup(TObject *Sender,
          TPoint &MousePos, bool &Handled);
        void __fastcall SwapCells1Click(TObject *Sender);
        void __fastcall BuildDXF1Click(TObject *Sender);
        void __fastcall FormContextPopup(TObject *Sender, TPoint &MousePos,
          bool &Handled);
        void __fastcall ShowLengthofSides1Click(TObject *Sender);
        void __fastcall Complex1Click(TObject *Sender);
        void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
        void __fastcall FormMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall vTopClick(TObject *Sender);
        void __fastcall FormResize(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall Button5Click(TObject *Sender);
        void __fastcall Button8Click(TObject *Sender);
        void __fastcall Button7Click(TObject *Sender);
        void __fastcall Button6Click(TObject *Sender);
        void __fastcall Button9Click(TObject *Sender);
        void __fastcall InsertEmptyString1Click(TObject *Sender);
        void __fastcall SvLibClick(TObject *Sender);
        void __fastcall ShapesMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall GridValuesChange(TObject *Sender);
        void __fastcall FootPrintsClick(TObject *Sender);
        void __fastcall UsedClick(TObject *Sender);
        void __fastcall PageControl1Changing(TObject *Sender,
          bool &AllowChange);
        void __fastcall StringGrid1SetEditText(TObject *Sender, int ACol,
          int ARow, const AnsiString Value);
        void __fastcall DrawClick(TObject *Sender);
        void __fastcall vTopKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall Button2KeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall Button3KeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall Button4KeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall Button5KeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall SelAllClick(TObject *Sender);
        void __fastcall DelSelClick(TObject *Sender);
        void __fastcall ShapesKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
public:		// User declarations
        __fastcall TForm2(TComponent* Owner);
        void myResize(bool Mode);
        void R_Library( bool ch);
        void S_Library( bool ch, bool bONLY = 0 );
        int GetFootBeg(AnsiString str, int * END=NULL);
        void Form2_INI();
        enum{ AllObj=0, AllinThisProject, UsedInOthersParts, AuxiliaryParts };
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
