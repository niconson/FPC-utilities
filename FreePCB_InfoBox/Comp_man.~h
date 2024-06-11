//---------------------------------------------------------------------------

#ifndef Comp_manH
#define Comp_manH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include <Grids.hpp>
#include <ValEdit.hpp>
#include <Graphics.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
#include <SysUtils.hpp>
#include <Buttons.hpp>
//#define FORM_MIN_HEIGHT 100
#define FALSE_FALSE 1
#define FALSE_TRUE 2
#define TRUE_TRUE 3
//
#define MIN_FORM_W      150
#define MIN_FORM_H      65
#define ABS(A)                ((A)<0  ? (-(A)) : (A))
#define MAX(A, B)             ((A)>(B) ? (A) : (B))
#define MIN(A, B)             ((A)<(B) ? (A) : (B))
#define MAX3(A, B, C)         ((A)>(B) ? ((A)>(C) ? (A) : (C)) : ((B)>(C) ? (B) : (C)))
#define MIN3(A, B, C)         ((A)<(B) ? ((A)<(C) ? (A) : (C)) : ((B)<(C) ? (B) : (C)))
#define MAX4(A, B, C, D)      ((A)>(D) ? ((A)>(B) ? ((A)>(C) ? (A) : (C)) : ((B)>(C) ? (B) : (C))) : ((D)>(B) ? ((D)>(C) ? (D) : (C)) : ((B)>(C) ? (B) : (C))))
#define MIN4(A, B, C, D)      ((A)<(D) ? ((A)<(B) ? ((A)<(C) ? (A) : (C)) : ((B)<(C) ? (B) : (C))) : ((D)<(B) ? ((D)<(C) ? (D) : (C)) : ((B)<(C) ? (B) : (C))))
#define SWAP(A, B)            {(A)=(A)^(B); (B)=(B)^(A); (A)=(A)^(B);}
#define DEFAULT 999999999.9
#define BY_ZERO 0.001
#define MM_TO_NM 1000000
#define MIL_TO_NM 25400
#define MM_TO_MIL 39.37
#define CDS_LONG_MAX_LEN 30000
#define CDS_SHORT_MAX_LEN 1000
//
#define FREEPCB_HEADER "FreePCB - "
//
// PARTS
#define col_RefDes                  0
#define col_RIRange                 1
#define col_Value                   2
#define col_ValueNL                 3
#define col_Package                 4
#define col_FootPrint               5
#define col_PackageNL               6
#define col_Merge                   7
#define col_Pins                    8
#define col_Holes                   9
#define col_Gl                      10
#define col_S                       11
#define col_Ang                     12
#define col_Xprt                    13
#define col_Yprt                    14
#define col_CompareNetlist          15
#define def_RefDes                  PartColOrder[col_RefDes        ]
#define def_RIRange                 PartColOrder[col_RIRange       ]
#define def_Value                   PartColOrder[col_Value         ]
#define def_ValueNL                 PartColOrder[col_ValueNL       ]
#define def_Package                 PartColOrder[col_Package       ]
#define def_FootPrint               PartColOrder[col_FootPrint     ]
#define def_PackageNL               PartColOrder[col_PackageNL     ]
#define def_Merge                   PartColOrder[col_Merge         ]
#define def_Pins                    PartColOrder[col_Pins          ]
#define def_Holes                   PartColOrder[col_Holes         ]
#define def_Gl                      PartColOrder[col_Gl            ]
#define def_S                       PartColOrder[col_S             ]
#define def_Ang                     PartColOrder[col_Ang           ]
#define def_Xprt                    PartColOrder[col_Xprt          ]
#define def_Yprt                    PartColOrder[col_Yprt          ]
#define def_CompareNetlist          PartColOrder[col_CompareNetlist]
#define PartsColCount               16
// PINS
#define col_Pin                     0
#define col_NetPcb                  1
#define col_Cnt                     2
#define col_Netlist                 3
#define col_Type                    4
#define col_W                       5
#define col_L                       6
#define col_Thrml                   7
#define col_DHole                   8
#define col_Pas                     9
#define col_Xpi                     10
#define col_Ypi                     11
#define def_Pin                     0
#define def_NetPcb                  1
#define def_Cnt                     2
#define def_Netlist                 3
#define def_Type                    4
#define def_W                       5
#define def_L                       6
#define def_Thrml                   7
#define def_DHole                   8
#define def_Pas                     9
#define def_Xpi                     10
#define def_Ypi                     11
#define PinsColCount                12
// pad shapes
#define NONE    0
#define CIRC    1
#define SQUA    2
#define RECT_   3
#define RNDR    4
#define OVAL    5
#define OCTA    6
#define N_PAD_SH 7
//
#define DOG "@"
#define dSPACE "  "
#define EMP "---"
#define TIMER_DBL_CLICK 300
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TListBox *SortedBox;
        TTimer *Timer1;
        TOpenDialog *OpenDialog1;
        TListBox *Bufer;
        TListBox *DataParts;
        TListBox *DataPins;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label6;
        TLabel *Label7;
        TPageControl *PageControl1;
        TTabSheet *Parts;
        TStringGrid *StringGridParts;
        TButton *BRefDes;
        TButton *BValue;
        TButton *BPackage;
        TButton *BPins;
        TButton *BHoles;
        TEdit *MinPin;
        TEdit *MinHoles;
        TEdit *MaxPins;
        TEdit *MaxHoles;
        TButton *BSide;
        TEdit *Side;
        TButton *BCNetlist;
        TButton *BGlueds;
        TEdit *Glueds;
        TButton *BAng;
        TEdit *Ang;
        TButton *BX;
        TEdit *EXmin;
        TButton *BY;
        TEdit *EYmin;
        TComboBox *CCNetlist;
        TEdit *EXmax;
        TEdit *EYmax;
        TTabSheet *Pins;
        TStringGrid *StringGridPins;
        TButton *BPin;
        TButton *BPinNetPCB;
        TButton *BType;
        TComboBox *CType;
        TButton *BPinNetList;
        TButton *BW;
        TButton *BL;
        TButton *BTrml;
        TComboBox *CTrml;
        TButton *BDHole;
        TButton *BXPin;
        TEdit *WPinMin;
        TEdit *WPinMax;
        TEdit *LPinMin;
        TEdit *LPinMax;
        TEdit *XPinMin;
        TEdit *XPinMax;
        TButton *BYPin;
        TEdit *YPinMin;
        TEdit *YPinMax;
        TEdit *CPin;
        TEdit *CNetNetlist;
        TComboBox *Values;
        TPopupMenu *Popup;
        TMenuItem *ST_popup;
        TMenuItem *PF_popup;
        TMenuItem *RF_popup;
        TMenuItem *VP_popup;
        TMenuItem *EX_popup;
        TMenuItem *CP_popup;
        TMenuItem *LN_popup;
        TProgressBar *ProgressBar1;
        TComboBox *DHoleMin;
        TComboBox *DHoleMax;
        TButton *BCnt;
        TComboBox *CPinNetPCB;
        TComboBox *CCnt;
        TButton *BPas;
        TEdit *Pas;
        TPopupMenu *SF;
        TMenuItem *SaveFilter1;
        TButton *BMerge;
        TMenuItem *SaveFilter2;
        TMenuItem *SaveFilter3;
        TEdit *CRefDes;
        TEdit *CValue;
        TEdit *CPackage;
        TMenuItem *HA_popup;
        TMenuItem *TXT_popup;
        TComboBox *CMerge;
        TEdit *CValueNL;
        TButton *BValueNL;
        TButton *BPackageNL;
        TEdit *CPackageNL;
        TButton *BFootPrint;
        TEdit *CFootPrint;
        TEdit *MaxRI;
        TEdit *MinRI;
        TButton *BRIRange;
        TOpenDialog *OpenDialog2;
        TLabel *n_el1;
        TLabel *n_el2;
        TTimer *TFilterAll;
        TMenuItem *CSC_popup;
        TListBox *Deleted;
        TMenuItem *RemoveCurrentList1;
        TImage *R;
        TImage *R2;
        TMenuItem *Utilities1;
        TMenuItem *EP_popup;
        TMenuItem *FA_popup;
        TMenuItem *NE_popup;
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall BRefDesClick(TObject *Sender);
        void __fastcall BValueClick(TObject *Sender);
        void __fastcall BPackageClick(TObject *Sender);
        void __fastcall StringGridPartsKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall StringGridPartsDrawCell(TObject *Sender, int ACol,
          int ARow, TRect &Rect, TGridDrawState State);
        void __fastcall MinPinKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall MinHolesKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall StringGridPartsMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall MaxPinsKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall MaxHolesKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall GluedsKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall SideKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall AngKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall EXminKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall EXmaxKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall EYminKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall EYmaxKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall CCNetlistKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall GluedsKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall SideKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall CCNetlistChange(TObject *Sender);
        void __fastcall CRefDeshange(TObject *Sender);
        void __fastcall StringGridPartsMouseWheelDown(TObject *Sender,
          TShiftState Shift, TPoint &MousePos, bool &Handled);
        void __fastcall StringGridPartsMouseWheelUp(TObject *Sender,
          TShiftState Shift, TPoint &MousePos, bool &Handled);
        void __fastcall StringGridPartsContextPopup(TObject *Sender,
          TPoint &MousePos, bool &Handled);
        void __fastcall PageControl1Change(TObject *Sender);
        void __fastcall StringGridPartsMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall BPinsClick(TObject *Sender);
        void __fastcall BHolesClick(TObject *Sender);
        void __fastcall BGluedsClick(TObject *Sender);
        void __fastcall BSideClick(TObject *Sender);
        void __fastcall BAngClick(TObject *Sender);
        void __fastcall BXClick(TObject *Sender);
        void __fastcall BYClick(TObject *Sender);
        void __fastcall BCNetlistClick(TObject *Sender);
        void __fastcall CRefDesKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall StringGridPinsMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall StringGridPinsMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall StringGridPinsDrawCell(TObject *Sender, int ACol,
          int ARow, TRect &Rect, TGridDrawState State);
        void __fastcall StringGridPinsKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall WPinMinKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall WPinMaxKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall LPinMinKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall LPinMaxKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall XPinMinKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall XPinMaxKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall YPinMinKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall YPinMaxKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall CTrmlChange(TObject *Sender);
        void __fastcall CTypeChange(TObject *Sender);
        void __fastcall CNetNetlistChange(TObject *Sender);
        void __fastcall CPinChange(TObject *Sender);
        void __fastcall CPinKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall CNetNetlistClick(TObject *Sender);
        void __fastcall CPinDblClick(TObject *Sender);
        void __fastcall StringGridPinsMouseWheelDown(TObject *Sender,
          TShiftState Shift, TPoint &MousePos, bool &Handled);
        void __fastcall StringGridPinsMouseWheelUp(TObject *Sender,
          TShiftState Shift, TPoint &MousePos, bool &Handled);
        void __fastcall CPinClick(TObject *Sender);
        void __fastcall StringGridPinsContextPopup(TObject *Sender,
          TPoint &MousePos, bool &Handled);
        void __fastcall LN_popupClick(TObject *Sender);
        void __fastcall RF_popupClick(TObject *Sender);
        void __fastcall PF_popupClick(TObject *Sender);
        void __fastcall EX_popupClick(TObject *Sender);
        void __fastcall ST_popupClick(TObject *Sender);
        void __fastcall CP_popupClick(TObject *Sender);
        void __fastcall EP_popupClick(TObject *Sender);
        void __fastcall FA_popupClick(TObject *Sender);
        void __fastcall NE_popupClick(TObject *Sender);
        void __fastcall DHoleMinChange(TObject *Sender);
        void __fastcall DHoleMaxChange(TObject *Sender);
        void __fastcall DHoleMinKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall DHoleMaxKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall CPinNetPCBChange(TObject *Sender);
        void __fastcall BYPinClick(TObject *Sender);
        void __fastcall PasChange(TObject *Sender);
        void __fastcall SaveFilter1Click(TObject *Sender);
        void __fastcall SaveFilter2Click(TObject *Sender);
        void __fastcall SaveFilter3Click(TObject *Sender);
        void __fastcall HA_popupClick(TObject *Sender);
        void __fastcall TXT_popupClick(TObject *Sender);
        void __fastcall BPinClick(TObject *Sender);
        void __fastcall BPinNetPCBClick(TObject *Sender);
        void __fastcall BCntClick(TObject *Sender);
        void __fastcall BPinNetListClick(TObject *Sender);
        void __fastcall BTypeClick(TObject *Sender);
        void __fastcall BWClick(TObject *Sender);
        void __fastcall BLClick(TObject *Sender);
        void __fastcall BTrmlClick(TObject *Sender);
        void __fastcall BDHoleClick(TObject *Sender);
        void __fastcall BPasClick(TObject *Sender);
        void __fastcall BXPinClick(TObject *Sender);
        void __fastcall CRefDesClick(TObject *Sender);
        void __fastcall CValueClick(TObject *Sender);
        void __fastcall CPackageClick(TObject *Sender);
        void __fastcall RClick(TObject *Sender);
        void __fastcall BValueNLClick(TObject *Sender);
        void __fastcall BPackageNLClick(TObject *Sender);
        void __fastcall BFootPrintClick(TObject *Sender);
        void __fastcall MinRIKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall MaxRIKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall BRIRangeClick(TObject *Sender);
        void __fastcall CRefDesMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall TFilterAllTimer(TObject *Sender);
        void __fastcall BCNetlistMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall VP_popupClick(TObject *Sender);
        void __fastcall CSC_popupClick(TObject *Sender);
        void __fastcall RemoveCurrentList1Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormResize(TObject *Sender);
        void __fastcall PopupPopup(TObject *Sender);
        void __fastcall MinHolesClick(TObject *Sender);
        void __fastcall MaxHolesClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
        int __fastcall OnWMCopyData(TWMCopyData &Msg);
        void __fastcall MItemClick(TObject *Sender);
BEGIN_MESSAGE_MAP
        MESSAGE_HANDLER(WM_COPYDATA, TWMCopyData, OnWMCopyData);
END_MESSAGE_MAP(TForm);
};

//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
extern AnsiString A;
extern AnsiString B;
extern AnsiString PathProg;
extern AnsiString FileName;
extern AnsiString GerberPath;
extern AnsiString NetListPath;
extern AnsiString WindowHeader;
extern AnsiString HeaderBack;
extern AnsiString FileNameBack;
extern AnsiString ColNames[PartsColCount];
extern COPYDATASTRUCT CDS_SHORT;
extern COPYDATASTRUCT CDS_LONG;
extern HWND Wind;
extern int UNITS;
extern int N_PART_ELEMENTS;
extern int N_PIN_ELEMENTS;
extern int m_report_flags;
extern int n_copper_layers;
extern int StringGridPartsRowIndex;
extern int StringGridPinsRowIndex;
extern int PartColOrder[PartsColCount];
extern long i;
extern long n;
extern long Pause;
extern int  SORT_CASE;             //Флаг порядка в листбокс 0-ref, 1-val, 1-package ...
extern long BRDRect[4];            //размер платы
extern long LONGDEFAULT;
extern bool Disable_ENTER ;
extern bool BEGIN ;
extern bool FlagSaveFilter;
extern bool FlagProgEXE;
extern bool PinsWasR;
extern char s[2501];
        //
extern int Form1_Left;
extern int Form1_Top;
extern int Form1_Width;
extern int Form1_Height;
extern void ReadingStorages(void);
extern void SetFormComponentsSizes(bool bSetDef);
extern void SortedParts (int CASE);
extern void Read_File (bool CMPR_PINS, bool rNETLIST);
extern AnsiString Read_TXT_Table ( AnsiString path, int order );
extern void save_path_func(void);
extern void FilterAll(bool Total=1, AnsiString includePin="", int TIndex=-1 );
extern void INTER_FACE (void);
extern long prob (AnsiString ANSI , long Pr);
extern AnsiString ex_str (AnsiString ANSI, long *n);
extern void Inicialization (void);
extern float ex_float_NM (AnsiString Str, long *index, int units, int * Ptr_Units=NULL);
extern AnsiString while_not_space (AnsiString ANSI, long *n);
extern void ProgExecute (AnsiString Path);
extern AnsiString F_str (float DBL, int insert0 = 0);
extern AnsiString FORMATFLOAT (AnsiString Str, AnsiString Sh, bool Replace);
extern int SaveFilter(int CASE);
extern int IOF(AnsiString s);
extern void DeleteColls (void);
extern void Rotate_Vertex (float *X, float *Y, float Ang);
extern AnsiString Str_Float_Format (AnsiString STRING_2_DOUBLE);
extern bool JUMP (AnsiString Ref);
extern bool MOVE (AnsiString Ref);
extern bool HighlightAll(void);
extern bool Enquary (AnsiString H);
extern bool FreePCBPaste (AnsiString FILE, float locX, float locY, int UNITS);
extern void KEYS (AnsiString key, bool KeyDown, bool KeyUp, int Pause, int REP);
extern void ResetFilter(bool bClearSearchConsole);
extern void CCnlistRefresh();
extern void Embed(int ClientWidth,int ClientHeight);
extern bool SendMessage_EP(AnsiString WindowName);
extern bool SendMessage_FILE(AnsiString WindowName, AnsiString*TEXT=NULL);
extern bool SendMessage_UPDFILE(AnsiString WindowName);
//---------------------------------------------------------------------------
#endif
