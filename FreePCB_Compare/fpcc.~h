//---------------------------------------------------------------------------

#ifndef IRH
#define IRH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <Grids.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#define ABS(A)                ((A)<0  ? (-(A)) : (A))
#define dSPACE "  "
//#define TRUE true
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label5;
        TTimer *CmdPlay;
        TListBox *MicroStrings;
        TPageControl *PageControl1;
        TTabSheet *Step_2;
        TTabSheet *Step_3;
        TTabSheet *Step_5;
        TButton *ButtonFeeders;
        TButton *Btn_Feed_Sort_V;
        TButton *Btn_Feed_Sort_P;
        TStringGrid *GridFeeders;
        TListBox *ProjectsList;
        TButton *ButtonProjects;
        TLabel *Label4;
        TButton *Btn_Sort_Match_V;
        TButton *Btn_Sort_Match_P;
        TStringGrid *GridResult;
        TButton *ButtonScan;
        TComboBox *ComboHelp;
        TProgressBar *ProgressBar1;
        TTabSheet *TabSheet1;
        TListBox *lbReport;
        TTabSheet *TabSheet2;
        TLabel *Label12;
        TLabel *Label13;
        TMemo *ExclV;
        TMemo *ExclP;
        TGroupBox *ExcludingGroup;
        TCheckBox *ExcludeAsterisk;
        TCheckBox *ExcludeDash;
        TCheckBox *ExcludeUnderscore;
        TCheckBox *ExcludeParentheses;
        TCheckBox *ExcludeSlash;
        TCheckBox *ExcludeComma;
        TTreeView *TreeReport;
        TButton *bnR;
        TTabSheet *TabSheet3;
        TMemo *lbNoReplace;
        TButton *bnTest;
        TLabel *Label14;
        TButton *Button1;
        TCheckBox *ch_txt;
        TCheckBox *ch_csv;
        TCheckBox *ch_cmpr;
        TLabel *Label3;
        TCheckBox *BOM;
        TStringGrid *lbReplace;
        TCheckBox *DSL;
        TMemo *Memo1;
        TComboBox *VALUES;
        TComboBox *PACKAGES;
        TComboBox *StorageLine;
        TLabel *Label2;
        TComboBox *FileNumbers;
        TButton *Reset;
        TComboBox *ColMem;
        TButton *Button2;
        TButton *Button3;
        TLabel *Label7;
        TLabel *Label15;
        TSaveDialog *SaveDialog;
        TCheckBox *StrikeThrough;
        TButton *Button4;
        TButton *Button5;
        TGroupBox *GroupBox1;
        TEdit *fdr_col_V;
        TEdit *fdr_col_P;
        TLabel *Label16;
        TLabel *Label19;
        TGroupBox *GroupBox2;
        TLabel *Label1;
        TLabel *Label8;
        TEdit *Vcol;
        TEdit *Pcol;
        TLabel *Mess;
        TComboBox *FileBox;
        TLabel *Label6;
        TCheckBox *AddSelSimilar;
        void __fastcall CmdPlayTimer(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall ButtonProjectsClick(TObject *Sender);
        void __fastcall ButtonFeedersClick(TObject *Sender);
        void __fastcall Btn_Feed_Sort_VClick(TObject *Sender);
        void __fastcall Btn_Feed_Sort_PClick(TObject *Sender);
        void __fastcall Btn_Sort_Match_VClick(TObject *Sender);
        void __fastcall Btn_Sort_Match_PClick(TObject *Sender);
        void __fastcall ProjectsListDblClick(TObject *Sender);
        void __fastcall bnRClick(TObject *Sender);
        void __fastcall ButtonScanMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall bnTestMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall GridFeedersDrawCell(TObject *Sender, int ACol,
          int ARow, TRect &Rect, TGridDrawState State);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Label5Click(TObject *Sender);
        void __fastcall ch_csvClick(TObject *Sender);
        void __fastcall ExcludeAsteriskClick(TObject *Sender);
        void __fastcall TreeReportKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall TreeReportCustomDrawItem(TCustomTreeView *Sender,
          TTreeNode *Node, TCustomDrawState State, bool &DefaultDraw);
        void __fastcall TreeReportMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall TreeReportMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall lbReplaceClick(TObject *Sender);
        void __fastcall DSLMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall StorageLineKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall StorageLineChange(TObject *Sender);
        void __fastcall ResetMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall fdr_col_PChange(TObject *Sender);
        void __fastcall fdr_col_VChange(TObject *Sender);
        void __fastcall VcolChange(TObject *Sender);
        void __fastcall PcolChange(TObject *Sender);
        void __fastcall TreeReportExpanded(TObject *Sender,
          TTreeNode *Node);
        void __fastcall TreeReportExpanding(TObject *Sender,
          TTreeNode *Node, bool &AllowExpansion);
        void __fastcall TreeReportMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall GridFeedersClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
        void __fastcall OnWMCopyData(TWMCopyData &Msg);
BEGIN_MESSAGE_MAP
        MESSAGE_HANDLER(WM_COPYDATA, TWMCopyData, OnWMCopyData);
END_MESSAGE_MAP(TForm);
};
struct TTreeChain
        {
        TTreeNode * NODE;
        TTreeChain * PREV;
        TTreeChain * NEXT;
        };
class TTreeChainList
        {
        public:
        TTreeChain m_start;
        TTreeChain m_end;
        TTreeChainList()
                {
                m_start.PREV = NULL;
                m_start.NODE = NULL;
                m_start.NEXT = &m_end;
                m_end.PREV = &m_start;
                m_end.NODE = NULL;
                m_end.NEXT = NULL;
                };
        ~TTreeChainList()
                {
                remove_all();
                };  
        TTreeChain * add( TTreeNode * addN )
                {
                TTreeChain * N = new TTreeChain;
                N->PREV = m_end.PREV;
                N->NEXT = &m_end;
                m_end.PREV->NEXT = N;
                m_end.PREV = N;
                N->NODE = addN;
                return N;
                };
        TTreeChain * iof( TTreeNode * N )
                {
                if( N == NULL )
                        return NULL;
                for( TTreeChain*n=m_start.NEXT; n!=&m_end; n=n->NEXT )
                        if( n->NODE == N )
                                return n;
                return NULL;
                };
        TTreeChain * remove( TTreeChain * N )
                {
                if( N == &m_start || N == &m_end || N == NULL )
                        return NULL;
                TTreeChain * nxt = N->NEXT;
                N->PREV->NEXT = nxt;
                nxt->PREV = N->PREV;
                delete N;
                return nxt;
                };
        void remove_all()
                {
                for( TTreeChain*n=m_start.NEXT->NEXT; n; n=n->NEXT )
                                remove(n->PREV);
                };
        TTreeChain * deleteNode( TTreeNode * Node )
                {
                return remove( iof( Node ) );
                };
        };
//---------------------------------------------------------------------------

// define
#define g_feeders       1
#define g_projects      2
//#define w_options       CMD_WRITE_OPTIONS=true
#define r_options       CMD_READ_OPTIONS=true
#define r_projects      CMD_READ_PROJECTS=true
#define r_feeders       CMD_READ_FEEDERS=true
#define clear_cmd       CMD_WRITE_OPTIONS=false;\
                        CMD_READ_OPTIONS=false;\
                        CMD_READ_PROJECTS=false;\
                        CMD_READ_FEEDERS=false
//---------------------------------------------------------------------------
AnsiString F_str (double DBL);
AnsiString ex_str (AnsiString ANSI, short int *n);
AnsiString Str_Float_F (AnsiString STRING_2_DOUBLE);
void ParentItemDelete(TTreeNode * Parent);
long prob (AnsiString ANSI , short int Pr);
// extern
extern TTreeChainList TreeLabelList;
extern PACKAGE TForm1 *Form1;
extern AnsiString WMCopyData_STORAGE;
extern void WritingOptions( AnsiString feeders, AnsiString projects, bool bQ );
extern void ReadingOptions( AnsiString * feeders, AnsiString * projects );
extern void ReadingProjects( AnsiString S );
extern void ReadingFeeders( AnsiString S );
extern void fix_str( AnsiString * S );
extern void GenReportTXT();
extern void GenerateFeedersTXT();
extern AnsiString GenerateVPL(AnsiString pth);
extern void Sort( int n_col );
extern void Compare( int FileNumber, bool TEST );
extern float ex_float (AnsiString Str, long *index );
extern bool lbReplace_add (AnsiString s1, AnsiString s2);
extern bool LB_iof (AnsiString sA, AnsiString sB);
extern int ValuesPackages_iof( AnsiString v, AnsiString p );
extern int ValuesPackages_add( AnsiString v, AnsiString p, AnsiString nFile );
extern int V_col;
extern int P_col;
extern int V_col_fdr;
extern int P_col_fdr;
//---------------------------------------------------------------------------
#endif
