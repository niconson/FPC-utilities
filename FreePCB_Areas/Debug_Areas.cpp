//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Debug_Areas.h"
#include "ProcessMessages.h"
#include "Combine.h"
#include "fstream.h"
#include "clipbrd.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
bool bSAVE_CH=0;
AnsiString OpenD = "";
AnsiString n_copper_layers = "";
AnsiString WINDOW_HEADER = "";
bool FLAG_SWELL_CLEARENCE;
bool ObjMan = false;
bool bShowLog = false;
MLine *LinesArea                 = 0;
MLine *LinesCut                  = 0;
MPolyLine *Corners               = 0;
CanvasDataPads * DataPads       = 0;
CanvasDataLines * DataLines     = 0;
int * PointersToShape           = 0;
Indexes JUMP;
long CntLnsArea;
long CountLinesCut;
long Dtpads;
long Dtlines;
int Memory_of_LinesCut;
int none = 0;
int edge = 0;
int full = 0;
int nBO = 0;
int nTHERMAL;
int gUNITS = 0;
float annular_ring_for_pins;
float annular_ring_for_vias;
float GerberClearance;
float HoleClearance;
float SMClearance;
float SMSwell;
float DRCCopperToCopper;
float DRCBoardToCopper;
float ThermalClearance;
float ThermalLineWidth;
float MaxClearance;
float SaveTLW;
float AreaWidth;
TRect TotalRect;
TRect AreaRect;
TRect BoardRect;
//
long prob                (AnsiString ANSI , short int Pr);
AnsiString ex_str        (AnsiString ANSI, short int *n);
float ex_float_NM        (AnsiString Str, short int *index, int units);
void CopperAreasSplitter(void);
void INI (AnsiString fromClipboard);
void save_ch();
//---------------------------------------------------------------------------

int TForm1::Iof( TListBox * List, AnsiString S, int start, int end )
{
end = MIN(end,List->Count);
for( int i=start; i<end; i++ )
        {
        int len = List->Items->operator [](i).Length();
        if(S.Length() == len)
                if(List->Items->operator [](i).SubString(1,len) == S.SubString(1,S.Length()) )
                        return i;
        }
return -1;
}


__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
DecimalSeparator = ',';
//Form1->Edit_width->Font->Size = 7;
Form1->Timer1->Enabled = true;
Form1->Left = 0;
Form1->Height = 650;
Form1->Top = Screen->Height - Form1->Height;
Form1->File->Visible =                  false;
//Form1->File->Font
Form1->PinNets->Visible =               false;
Form1->InversionAreas->Visible =        false;
Form1->InversionCutouts->Visible =      false;
Form1->through->Enabled =               false;
Form1->NetsBox->Enabled =               false;
Form1->PinNets->Sorted =                false;
Form1->File->Sorted =                   false;
Form1->InversionAreas->Sorted =         false;
Form1->InversionCutouts->Sorted =       false;
Form1->NetsBox->Sorted =                true;
Form1->NetsBox->MultiSelect =           true;
TotalRect.Left =        DEFAULT;
TotalRect.Bottom =      DEFAULT;
TotalRect.Right =      -DEFAULT;
TotalRect.Top =        -DEFAULT;
}







//---------------------------------------------------------------------------
void LoadFile(void)
{
annular_ring_for_vias = 0;
annular_ring_for_pins = 0;
//
Form1->NetsBox->Items->Clear();
Form1->PinNets->Items->Clear();
Form1->File->Items->Clear();
//Form1->NetsBox->Visible = false;
ifstream READ (OpenD.c_str() );
char str[2501];
short int i;
AnsiString A;
do{
        READ.getline(str, 2500);
        if( READ.eof() || A.SubString(1,5) == "[end]")
                {
                ShowMessage ("    Error! The file format is not supported.");
                return;
                }
        A = str;
        A = A.Trim();
        }while(A.SubString(1,9) != "[options]");
int n_str = 0;
none = 0;
edge = 0;
full = 0;
bool FF = false;    //flag [footprints] section
bool FlagBoard = false;
AnsiString CurrentNet = "";
int num_pointer_to_shape = 0;
JUMP.Merges = 0;
while (!READ.eof())
        {
        Form1->File->Items->Add(A);
        if (A.SubString(1,5) == "[end]")
                break;
        if (A.SubString(1,15) == "n_copper_layers") n_copper_layers = A;
        else if(A.SubString(1,5) == "[foot" )
                FF = true;
        else if (A.SubString(1,6) == "units:" && FF == 0)
                {
                i = prob (A, 1 );
                if (A.UpperCase().SubString(i,3) == "MIL")      gUNITS = uMIL;
                else                                            gUNITS = uMM;
                // reading check
                ifstream ch ((ExtractFilePath(Application->ExeName)+"Ch.txt").c_str());
                char s[30];
                ch.getline( s, sizeof(s) );
                if( s[0] == '*' )
                        Form1->inv->Checked = true;
                if( s[1] == '*' )
                        Form1->dwg->Checked = true;
                if( s[2] == '*' )
                        Form1->width->Checked = true;
                if( s[3] == '*' )
                        Form1->cl_holes->Checked = true;
                if( s[4] == '*' )
                        Form1->cl_pins->Checked = true;
                if( s[5] == '*' )
                        Form1->cl_brd->Checked = true;
                if( s[6] == '*' )
                        Form1->cl_areas->Checked = true;
                if( s[7] == '*' )
                        Form1->cl_sm->Checked = true;
                if( s[8] == '*' )
                        Form1->cl_thrmlp->Checked = true;
                if( s[9] == '*' )
                        Form1->cl_th_vias->Checked = true;
                if( s[10] == '*' )
                        Form1->repour->Checked = true;
                if( s[11] == '*' )
                        Form1->replace->Checked = false;
                if( s[12] == '*' )
                        Form1->Low->Checked = true;
                if( s[13] == '*' )
                        Form1->High->Checked = true;
                if( s[14] == '*' )
                        Form1->V->Checked = true;
                if( s[15] == '*' )
                        Form1->H->Checked = true;
                if( s[16] == '*' )
                        Form1->Romb->Checked = true;
                if( s[17] == '*' )
                        Form1->Stagger->Checked = true;
                short adr = 0;
                ch.getline( s, sizeof(s) );
                AnsiString S = s;
                double Edit_width =             ex_float_NM(S,&adr,-1);
                adr = 0;
                ch.getline( s, sizeof(s) );
                S = s;
                double Edit_cl_holes =          ex_float_NM(S,&adr,-1);
                adr = 0;
                ch.getline( s, sizeof(s) );
                S = s;
                double Edit_cl_pins =           ex_float_NM(S,&adr,-1);
                adr = 0;
                ch.getline( s, sizeof(s) );
                S = s;
                double Edit_cl_brd =            ex_float_NM(S,&adr,-1);
                adr = 0;
                ch.getline( s, sizeof(s) );
                S = s;
                double Edit_cl_areas =          ex_float_NM(S,&adr,-1);
                adr = 0;
                ch.getline( s, sizeof(s) );
                S = s;
                double Edit_cl_sm =             ex_float_NM(S,&adr,-1);
                adr = 0;
                ch.getline( s, sizeof(s) );
                S = s;
                double Edit_cl_thrmlp =         ex_float_NM(S,&adr,-1);
                adr = 0;
                ch.getline( s, sizeof(s) );
                Form1->Edit3->Text = s;
                ch.getline( s, sizeof(s) );
                Form1->Edit4->Text = s;
                ch.getline( s, sizeof(s) );
                Form1->Edit5->Text = s;
                ch.getline( s, sizeof(s) );
                Form1->Edit6->Text = s;
                ch.close();
                if( gUNITS == uMM )
                        {
                        //
                        Form1->Label1->Caption = "MM";
                        Form1->Label3->Caption = "mm";
                        Form1->Label5->Caption = "mm";
                        Form1->Label6->Caption = "mm";
                        Form1->Label7->Caption = "mm";
                        Form1->Edit_width->Text =       Str_Float_Format(Edit_width/_106);
                        Form1->Edit_cl_holes->Text =    Str_Float_Format(Edit_cl_holes/_106);
                        Form1->Edit_cl_pins->Text =     Str_Float_Format(Edit_cl_pins/_106);
                        Form1->Edit_cl_brd->Text =      Str_Float_Format(Edit_cl_brd/_106);
                        Form1->Edit_cl_areas->Text =    Str_Float_Format(Edit_cl_areas/_106);
                        Form1->Edit_cl_sm->Text =       Str_Float_Format(Edit_cl_sm/_106);
                        Form1->Edit_cl_thrmlp->Text =   Str_Float_Format(Edit_cl_thrmlp/_106);
                        }
                else    {
                        //
                        Form1->Label1->Caption = "MIL";
                        Form1->Label3->Caption = "mil";
                        Form1->Label5->Caption = "mil";
                        Form1->Label6->Caption = "mil";
                        Form1->Label7->Caption = "mil";
                        Form1->Edit_width->Text =       Str_Float_Format(Edit_width/_2542);
                        Form1->Edit_cl_holes->Text =    Str_Float_Format(Edit_cl_holes/_2542);
                        Form1->Edit_cl_pins->Text =     Str_Float_Format(Edit_cl_pins/_2542);
                        Form1->Edit_cl_brd->Text =      Str_Float_Format(Edit_cl_brd/_2542);
                        Form1->Edit_cl_areas->Text =    Str_Float_Format(Edit_cl_areas/_2542);
                        Form1->Edit_cl_sm->Text =       Str_Float_Format(Edit_cl_sm/_2542);
                        Form1->Edit_cl_thrmlp->Text =   Str_Float_Format(Edit_cl_thrmlp/_2542);
                        }
                }
        else if (A.SubString(1,21) == "annular_ring_for_vias")
                {
                i = prob(A,1);
                annular_ring_for_vias = ex_float_NM(A, &i, -1);
                }
        else if (A.SubString(1,21) == "annular_ring_for_pins")
                {
                i = prob(A,1);
                annular_ring_for_pins = ex_float_NM(A, &i, -1);
                }
        else if (A.SubString(1,14) == "fill_clearance" )
                {
                i = prob(A,1);
                GerberClearance = ex_float_NM(A, &i, -1);
                }
        else if (A.SubString(1,17) == "drc_copper_copper" )
                {
                i = prob(A,1);
                DRCCopperToCopper = ex_float_NM(A, &i, -1);
                }
        else if (A.SubString(1,17) == "thermal_clearance" )
                {
                i = prob(A,1);
                ThermalClearance = ex_float_NM(A, &i, -1);
                }
        else if (A.SubString(1,14) == "thermal_width:" )
                {
                i = prob(A,1);
                SaveTLW = ex_float_NM(A, &i, -1);
                }
        else if (A.SubString(1,21) == "drc_board_edge_copper" )
                {
                i = prob(A,1);
                DRCBoardToCopper = ex_float_NM(A, &i, -1);
                }
        else if (A.SubString(1,14) == "hole_clearance" )
                {
                i = prob(A,1);
                HoleClearance = ex_float_NM(A, &i, -1);
                }
        else if (A.SubString(1,14) == "mask_clearance" )
                {
                i = prob(A,1);
                SMSwell = ex_float_NM(A, &i, -1);
                }
        else if (A.SubString(1,5) == "area:" )
                {
                i = prob(A,4);
                int HatchStyle = ex_float_NM(A, &i, -1);
                i = prob(A,8);
                if( i <= 0 )
                        i = prob(A,7);  // for version FreePcb 2-032
                if(i)   {
                        int sel = ex_float_NM(A, &i, -1);
                        if(sel) {
                                if (HatchStyle == 0)none++;
                                if (HatchStyle == 2)edge++;
                                if (HatchStyle == 1)full++;
                                }
                        }
                }
        else if (A.SubString(1,7) == "[board]" )
                {
                FlagBoard = true;
                JUMP.Board = Form1->File->Items->Count - 1;
                }
        else if ((A.SubString(1,7) == "corner:" )&&(FlagBoard))
                {
                i = prob(A,2);
                long X = ex_float_NM(A, &i, -1);
                long Y = ex_float_NM(A, &i, -1);
                if (TotalRect.Left > X)  TotalRect.Left = X;
                if (TotalRect.Bottom > Y)TotalRect.Bottom = Y;
                if (TotalRect.Right < X) TotalRect.Right = X;
                if (TotalRect.Top < Y)   TotalRect.Top = Y;
                }
        else if ((A.SubString(1,4) == "net:" )&&(FlagBoard))
                {
                i = prob (A, 1 );
                CurrentNet = ex_str(A,&i);
                Form1->NetsBox->Items->Add(CurrentNet);
                }
        else if ((A.SubString(1,4) == "pin:" )&&(FlagBoard))
                {
                i = prob (A, 2 );
                AnsiString PIN = A.SubString(i,(A.Length()-i+1));
                Form1->PinNets->Items->Add(PIN);
                Form1->PinNets->Items->Add(CurrentNet);
                }
        else if (A.SubString(1,12) == "[footprints]" )
                {
                JUMP.Footprints = Form1->File->Items->Count - 1;
                }
        else if (A.SubString(1,7) == "[solder" )
                {
                JUMP.Sm_cutouts = Form1->File->Items->Count - 1;
                }
        else if (A.SubString(1,7) == "[parts]" )
                {
                JUMP.Parts = Form1->File->Items->Count - 1;
                }
        else if (A.SubString(1,6) == "[nets]" )
                {
                num_pointer_to_shape = n_str;
                JUMP.Nets = Form1->File->Items->Count - 1;
                }
        else if (A.SubString(1,7) == "[texts]" )
                {
                JUMP.Texts = Form1->File->Items->Count - 1;
                }
        else if (A.SubString(1,8) == "[merges]" )
                {
                JUMP.Merges = Form1->File->Items->Count - 1;
                }
        READ.getline(str, 2500);
        A = str;
        A = A.Trim();
        n_str++;
        }
Form1->File->Items->Add(A);
if( JUMP.Merges == 0 )
        JUMP.Merges = Form1->File->Items->Count - 1;
//
if ( PointersToShape )
        delete[] PointersToShape;
try     {
        PointersToShape = new(std::nothrow) int[num_pointer_to_shape];
        }
catch(std::bad_alloc)
        {
        ShowMessage("    Error of memory: int[" + AnsiString(num_pointer_to_shape) + "]!" );
        }
AnsiString sh_prev = "";
int str_pr = JUMP.Footprints;
for (int str=JUMP.Parts; str<JUMP.Nets; str++)
        {
        A = Form1->File->Items->operator [](str);
        PointersToShape[str] = 0;
        if (A.SubString(1,5) == "shape")
                {
                if( sh_prev.AnsiCompare(A) == 0 )
                        {
                        PointersToShape[str] = PointersToShape[str_pr];
                        }
                else    {
                        i = prob(A,1);
                        if (i>0){
                                AnsiString jmp = "name: " + A.SubString(i,(A.Length()-i+1));
                                for( i=JUMP.Footprints; i<JUMP.Board; i++ )
                                        {
                                        if( Form1->File->Items->operator [](i) == jmp )
                                                break;
                                        }
                                if( i >= JUMP.Board )
                                        {
                                        ShowMessage("    Fatal error - footprint " + jmp + " not found!" );
                                        exit(0);
                                        }
                                PointersToShape[str] = i;
                                sh_prev = A;
                                str_pr = str;
                                }
                        }
                str += 2;
                }
        }
//
Form1->NetsBox->Items->Add("Unconnected");
//Form1->NetsBox->Visible = true;
READ.close();
if( none+edge+full == 0 )
        exit(0);
Form1->find_areas->Caption = "Found selected areas: " + AnsiString(none+edge+full);
if (TotalRect.Left >= DEFAULT)
        {
        TotalRect.Left = 0;
        TotalRect.Bottom = 0;
        TotalRect.Right = 0;
        TotalRect.Top = 0;
        }
TotalRect.Left =        TotalRect.Left - MM_10;
TotalRect.Bottom =      TotalRect.Bottom - MM_10;
TotalRect.Right =       TotalRect.Right + MM_10;
TotalRect.Top =         TotalRect.Top + MM_10;
}









//---------------------------------------------------------------------------
void INI (AnsiString fromClipboard)
{
ObjMan = false;
if (fromClipboard.SubString(1,6) == "ObjMan")
        {
        short int i = prob(fromClipboard, 1);
        Form1->OpenDialog1->FileName = ex_str(fromClipboard, &i) ;
        ObjMan = true;
        }
else if (Form1->OpenDialog1->Execute()){;}
else exit(0);
if (Form1->OpenDialog1->FileName.Length() == 0)
        {
        //
        }
else    {
        AnsiString cs = ExtractFileName(Form1->OpenDialog1->FileName).LowerCase();
        if( cs.LowerCase() == "areas.fpc" ||
        cs.LowerCase() == "invareas.fpc" ||
        cs.LowerCase() == "onlyareas.fpc" )
                {
                ShowMessage( " The downloaded file cannot be \"areas.fpc\" \"invareas.fpc\" \"onlyareas.fpc\" ");
                INI("");
                return;
                }
        OpenD = Form1->OpenDialog1->FileName;
        Form1->Caption = "Loading File...";
        Application->ProcessMessages();
        LoadFile();
        Form1->Caption = "Loading Lines, pads and vias...";
        Application->ProcessMessages();
        LoadingLines();
        if (ObjMan)     Form1->Caption = "Areas";
        else            Form1->Caption = "Edit " + ExtractFileName(Form1->OpenDialog1->FileName);
        }
}








//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
Form1->Timer1->Enabled = false;
if( bSAVE_CH )
        {
        bSAVE_CH = 0;
        save_ch();
        }
static bool LOW_CHECKED = Form1->Low->Checked;
static bool bFirst = false;
if (inv->Checked)
        {
        Form1->V->Enabled =             false;
        Form1->H->Enabled =             false;
        Form1->dwg->Enabled =           false;
        Form1->cl_pins->Enabled =       false;
        Form1->cl_brd->Enabled =        false;
        Form1->cl_areas->Enabled =      false;
        Form1->cl_thrmlp->Enabled =     false;
        Form1->cl_th_vias->Enabled =    false;
        Form1->width->Enabled =         false;
        Form1->cl_holes->Enabled =      false;
        Form1->Edit_cl_holes->Enabled = false;
        Form1->cl_sm->Enabled =         false;
        Form1->Edit_cl_sm->Enabled =    false;
        Form1->Edit_cl_holes->Enabled = false;
        Form1->Edit_cl_pins->Enabled =  false;
        Form1->Edit_cl_brd->Enabled =   false;
        Form1->Edit_cl_areas->Enabled = false;
        Form1->Edit_cl_thrmlp->Enabled =false;
        Form1->Edit_width->Enabled =    false;
        Form1->replace->Enabled =       false;
        Form1->GroupBox6->Enabled =     false;
        Form1->Low->Enabled =           false;
        Form1->High->Enabled =          false;
        Form1->GroupBox2->Enabled =     false;
        Form1->AutoSelect->Enabled =    false;
        Form1->Manual->Enabled =        false;
        Form1->through->Enabled =       false;
        Form1->NetsBox->Enabled =       false;
        Form1->repour->Enabled =        false;
        Form1->Label2->Enabled =        false;
        }
else    {
        Form1->V->Enabled =             true;
        Form1->H->Enabled =             true;
        Form1->dwg->Enabled =           true;
        Form1->cl_pins->Enabled =       true;
        if( nBO )
                Form1->cl_brd->Enabled =        true;
        Form1->cl_areas->Enabled =      true;
        Form1->cl_thrmlp->Enabled =     true;
        Form1->cl_th_vias->Enabled =    true;
        Form1->width->Enabled =         true;
        Form1->cl_holes->Enabled =      true;
        Form1->Edit_cl_holes->Enabled = true;
        Form1->cl_sm->Enabled =         true;
        Form1->Edit_cl_sm->Enabled =    true;
        Form1->Edit_cl_holes->Enabled = true;
        Form1->Edit_cl_pins->Enabled =  true;
        Form1->Edit_cl_brd->Enabled =   true;
        Form1->Edit_cl_areas->Enabled = true;
        Form1->Edit_cl_thrmlp->Enabled =true;
        Form1->Edit_width->Enabled =    true;
        Form1->replace->Enabled =       true;
        Form1->GroupBox6->Enabled =     true;
        Form1->Low->Enabled =           true;
        Form1->High->Enabled =          true;
        Form1->GroupBox2->Enabled =     true;
        Form1->AutoSelect->Enabled =    true;
        Form1->Manual->Enabled =        true;
        Form1->through->Enabled =       true;
        Form1->NetsBox->Enabled =       true;
        Form1->repour->Enabled =        true;
        Form1->Label2->Enabled =        true;
        }
if (Form1->dwg->Checked && Form1->dwg->Enabled)
        {
        Form1->Label3->Enabled = true;
        Form1->Label4->Enabled = true;
        Form1->Label5->Enabled = true;
        Form1->Label6->Enabled = true;
        Form1->Label7->Enabled = true;
        Form1->Label8->Enabled = true;
        Form1->Label9->Enabled = true;
        Form1->Label10->Enabled =true;
        Form1->Edit3->Enabled = true;
        Form1->Edit4->Enabled = true;
        Form1->Edit5->Enabled = true;
        Form1->Edit6->Enabled = true;
        Form1->GroupBox5->Enabled = true;
        Form1->Rect->Enabled = true;
        Form1->Romb->Enabled = true;
        Form1->Stagger->Enabled = true;
        if (Form1->Rect->Checked)       Form1->Image2->Visible = true;
        else                            Form1->Image2->Visible = false;
        if (Form1->Romb->Checked)       Form1->Image4->Visible = true;
        else                            Form1->Image4->Visible = false;
        }
else    {
        Form1->Label3->Enabled = false;
        Form1->Label4->Enabled = false;
        Form1->Label5->Enabled = false;
        Form1->Label6->Enabled = false;
        Form1->Label7->Enabled = false;
        Form1->Label8->Enabled = false;
        Form1->Label9->Enabled = false;
        Form1->Label10->Enabled = false;
        Form1->Edit3->Enabled = false;
        Form1->Edit4->Enabled = false;
        Form1->Edit5->Enabled = false;
        Form1->Edit6->Enabled = false;
        Form1->GroupBox5->Enabled = false;
        Form1->Rect->Enabled = false;
        Form1->Romb->Enabled = false;
        Form1->Stagger->Enabled = false;
        Form1->Image2->Visible = false;
        Form1->Image4->Visible = false;
        }
if (Form1->AutoSelect->Checked)
        {
        Form1->bSelectAll->Enabled = false;
        Form1->NetsBox->Enabled = false;
        }
else    {
        Form1->bSelectAll->Enabled = true;
        Form1->NetsBox->Enabled = true;
        }
AnsiString CLPBRD = "";
Form1->ClipB->Text = "";
if( bFirst == 0 )
        {
        bFirst = 1;
        Form1->ClipB->PasteFromClipboard();
        CLPBRD = Form1->ClipB->Text;
        Clipboard()->Clear();
        }
if(OpenD.Length())
        if( LOW_CHECKED != Form1->Low->Checked )
                {
                save_ch();
                CLPBRD = "ObjMan \"" + OpenD + "\"";
                }
if (!OpenD.Length() || CLPBRD.SubString(1,6) == "ObjMan" )
        INI (CLPBRD);
if(ObjMan)
        Form1->replace->Visible = 0;
LOW_CHECKED = Form1->Low->Checked;
Form1->Timer1->Enabled = true;
}







//---------------------------------------------------------------------------
int NAR (int FileIndex)
        {
        AnsiString Q;
        int c = 0;
        for (int q=FileIndex; q<Form1->File->Count; q++)
                {
                Q = Form1->File->Items->operator [](q);
                if (Q.SubString(1,1) == "[")   break;
                if (Q.SubString(1,3) == "net") break;
                if (Q.SubString(1,4) == "area")
                        {
                        short int i = prob(Q,8);
                        if(i > 0){
                                long sel = ex_float_NM(Q, &i, -1);
                                if (sel)
                                        c++;
                                }
                        else    {
                                short int i = prob(Q,7);  // for version FreePcb 2-032
                                if(i > 0){
                                        long sel = ex_float_NM(Q, &i, -1);
                                        if (sel)
                                                c++;
                                        }
                                }
                        }
                }
        return c;
        }








//---------------------------------------------------------------------------





void CopperAreasSplitter(void)
{
Form1->Timer1->Enabled = false;
Form1->BitBtn1->Enabled = false;
Form3->ProgressBar1->Position = 0;
Form3->Visible = true;
AnsiString A;
A = Form1->Edit_cl_holes->Text;
HoleClearance = StrToFloat(Str_Float_Format(A));
HoleClearance = ABS(HoleClearance)*_106;
A = Form1->Edit_cl_pins->Text;
GerberClearance = StrToFloat(Str_Float_Format(A));
GerberClearance = ABS(GerberClearance)*_106;
A = Form1->Edit_cl_brd->Text;
DRCBoardToCopper = StrToFloat(Str_Float_Format(A));
DRCBoardToCopper = ABS(DRCBoardToCopper)*_106;
A = Form1->Edit_cl_areas->Text;
DRCCopperToCopper = StrToFloat(Str_Float_Format(A));
DRCCopperToCopper = ABS(DRCCopperToCopper)*_106;
A = Form1->Edit_cl_sm->Text;
SMClearance = StrToFloat(Str_Float_Format(A));
SMClearance = ABS(SMClearance)*_106;
A = Form1->Edit_cl_thrmlp->Text;
ThermalClearance = StrToFloat(Str_Float_Format(A));
ThermalClearance = ABS(ThermalClearance)*_106;
MaxClearance = MAX4( DRCCopperToCopper, GerberClearance, HoleClearance, SMClearance );
if(gUNITS == uMIL)
        {
        HoleClearance /= PER_MIL;
        GerberClearance /= PER_MIL;
        DRCBoardToCopper /= PER_MIL;
        DRCCopperToCopper /= PER_MIL;
        ThermalClearance /= PER_MIL;
        SMClearance /= PER_MIL;
        }
ThermalLineWidth = SaveTLW;
nTHERMAL = 0;
float a_w = 0;
if (Form1->width->Checked)
        {
        A = Form1->Edit_width->Text;
        a_w = StrToFloat(Str_Float_Format(A));
        a_w = a_w*_106;
        if(gUNITS == uMIL)
                a_w /= PER_MIL;
        // swell clearance
        GerberClearance +=      a_w/2;
        DRCBoardToCopper +=     a_w/2;
        DRCCopperToCopper +=    a_w/2;
        ThermalClearance +=     a_w;
        ThermalLineWidth -=     a_w;
        HoleClearance +=        a_w/2;
        SMClearance +=          a_w/2;
        if (GerberClearance < 0)  GerberClearance = 0;
        if (DRCBoardToCopper < 0) DRCBoardToCopper = 0;
        if (ThermalClearance < 0) ThermalClearance = 0;
        }
if( ThermalLineWidth < _2542 )
        ThermalLineWidth = _2542;
//
short int i;
AnsiString Areas = ExtractFilePath(Application->ExeName);
AnsiString OnlyAreas = Areas;
if (!Form1->replace->Checked) Areas += "Areas.fpc";
else    {
        Areas = OpenD;
        WINDOW_HEADER = "";
        }
OnlyAreas += "OnlyAreas.fpc";
//
float grid_X2 = StrToFloat(Str_Float_Format(Form1->Edit5->Text))*_106;
float grid_Y2 = StrToFloat(Str_Float_Format(Form1->Edit6->Text))*_106;
if(gUNITS == uMIL)
        {
        grid_X2 /= PER_MIL;
        grid_Y2 /= PER_MIL;
        }
int count_cut_grid = ((TotalRect.Right-TotalRect.Left - 2*MM_10)/grid_X2)*((TotalRect.Top-TotalRect.Bottom - 2*MM_10)/grid_Y2);
if (Form1->dwg->Checked == 0)
        count_cut_grid = 0;
//memory
if (LinesCut)
        delete[] LinesCut;
if (Corners)
        delete[] Corners;
int CornersCount = 0;
try     {
        CornersCount = Memory_of_LinesCut*20 + count_cut_grid*4;
        LinesCut = new(std::nothrow) MLine[CornersCount];
        Corners = new(std::nothrow) MPolyLine[CornersCount];
        }
catch(std::bad_alloc)
        {
        ShowMessage("    Error memory: Line[" + AnsiString(Memory_of_LinesCut*40 + count_cut_grid*4) + "]!" );
        exit(0);
        }
int C = 0;
Corners[0].RST();
FLAG_SWELL_CLEARENCE = false;
Application->ProcessMessages();
Sleep(500);
Form1->WRITEFPC->Clear();
Form1->ONLY->Clear();
Form1->InversionCutouts->Items->Clear();
Form1->InversionAreas->Items->Clear();
AnsiString CurrentNet;
int oa_num;
int ArNum;
int LastNetStringIndex1 = 0;
int LastNetStringIndex2 = 0;
int i_merges = Form1->File->Items->Count;
bool f = false;
AnsiString NetStringLeft;
AnsiString NetStringRight;
AnsiString AddToOnly;
AnsiString AddToWriteFPC;
for (int FileIndex=0; FileIndex<Form1->File->Items->Count; FileIndex++)
        {
        Form3->ProgressBar1->Position = (UINT)((float)(FileIndex+1)/(float)Form1->File->Items->Count*100.0);
        Application->ProcessMessages();
        A = Form1->File->Items->operator [](FileIndex);
        if      (A.SubString(1,4) == "net:")
                {
                if (f)
                        {
                        AddToOnly = "net: \"";
                        AddToOnly += CurrentNet;
                        AddToOnly += "\" 0 0 ";
                        AddToOnly += AnsiString(oa_num);
                        AddToOnly += " 0 0 0 1";
                        if (LastNetStringIndex1 < Form1->ONLY->Items->Count)
                                Form1->ONLY->Items->Insert(LastNetStringIndex1,AddToOnly);
                        else
                                Form1->ONLY->Items->Add(AddToOnly);
                        AddToWriteFPC = NetStringLeft;
                        AddToWriteFPC += AnsiString(ArNum);
                        AddToWriteFPC += NetStringRight;
                        if (LastNetStringIndex2 < Form1->WRITEFPC->Items->Count)
                                Form1->WRITEFPC->Items->Insert(LastNetStringIndex2,AddToWriteFPC);
                        else
                                Form1->WRITEFPC->Items->Add(AddToWriteFPC);
                        }
                f = true;
                LastNetStringIndex1 = Form1->ONLY->Items->Count;
                LastNetStringIndex2 = Form1->WRITEFPC->Items->Count;
                i = prob(A,1);
                CurrentNet = ex_str(A, &i);
                i = prob(A,4);
                NetStringLeft = A.SubString(1,(i-1));
                i = prob(A,5);
                NetStringRight = A.SubString((i-1),(A.Length()-i+2));
                ArNum = 0;
                oa_num = 0;
                continue;
                }
        else if (A.SubString(1,7) == "[texts]")
                {
                if (f)
                        {
                        AddToOnly = "net: \"";
                        AddToOnly += CurrentNet;
                        AddToOnly += "\" 0 0 ";
                        AddToOnly += AnsiString(oa_num);
                        AddToOnly += " 0 0 0 1";
                        if (LastNetStringIndex1 < Form1->ONLY->Items->Count)
                                Form1->ONLY->Items->Insert(LastNetStringIndex1,AddToOnly);
                        else
                                Form1->ONLY->Items->Add(AddToOnly);
                        AddToWriteFPC = NetStringLeft;
                        AddToWriteFPC += AnsiString(ArNum);
                        AddToWriteFPC += NetStringRight;
                        if (LastNetStringIndex2 < Form1->WRITEFPC->Items->Count)
                                Form1->WRITEFPC->Items->Insert(LastNetStringIndex2,AddToWriteFPC);
                        else
                                Form1->WRITEFPC->Items->Add(AddToWriteFPC);
                        }
                Form1->ONLY->Items->Add(A);
                }
        else if (A.SubString(1,4) == "area")
                {
                i = prob(A,1);
                short int Num =         ex_float_NM(A, &i, -1);
                short int numb_cor  =   ex_float_NM(A, &i, -1);
                short int layer =       ex_float_NM(A, &i, -1);
                short int HatchStyle =  ex_float_NM(A, &i, -1);
                int A_W =               ex_float_NM(A, &i, -1);
                short int M_index =     ex_float_NM(A, &i, -1);
                short int SubM_index =  ex_float_NM(A, &i, -1);
                i = prob(A,8);
                if( i <= 0 )
                        i = prob(A,7);     // for version FreePcb 2-032
                short int Enable =      ex_float_NM(A, &i, -1);
                CountLinesCut = 0;
                if (Form1->inv->Checked == 0)
                        {
                        C = 0;
                        Corners[0].RST();
                        }
                if (Enable)
                        {
                        Form3->Area->Items->Clear();
                        int CountArc = 0;
                        while (A.SubString(1,6) != "corner")
                                {
                                FileIndex++;
                                A = Form1->File->Items->operator [](FileIndex);
                                }
                        while (A.SubString(1,6) == "corner")
                                {
                                i = prob(A,4);
                                int T = ex_float_NM(A, &i, -1);
                                if (T) CountArc++;
                                Form3->Area->Items->Add(A);
                                FileIndex++;
                                A = Form1->File->Items->operator [](FileIndex);
                                }
                        FileIndex--;
                        /*
                        LOADING AREA */
                        CntLnsArea = LoadArea(CountArc);
                        if (p() > _104*200)
                                {
                                SetDirection(LinesArea, CntLnsArea, dir___CW);
                                LinesCut[CountLinesCut].First = CountLinesCut;
                                if( CountLinesCut )
                                        {
                                        int m_start = CountLinesCut;
                                        int m_end;
                                        do      {
                                                m_end = m_start;
                                                m_start = LinesCut[m_end-1].First;
                                                SetDirection( &LinesCut[m_start], m_end-m_start, dir___CCW );
                                                } while ( m_start );
                                        }
                                //
                                //INVERSION   == 0
                                if (Form1->inv->Checked == 0)
                                        {
                                        //CANVAS BOARD CLEARANCE
                                        if (Form1->cl_brd->Checked && BoardRect.Left < DEFAULT)
                                                {
                                                if (FLAG_SWELL_CLEARENCE == 0)
                                                        CanvasBoard  ();
                                                }

                                        //CANVAS HOLES CLEARANCE
                                        if (Form1->cl_holes->Checked)
                                                {
                                                if (FLAG_SWELL_CLEARENCE == 0)
                                                        CanvasHoles  (CurrentNet,layer);
                                                }
                                                
                                        //CANVAS PINS CLEARENCES
                                        if (Form1->cl_pins->Checked)
                                                {
                                                if (FLAG_SWELL_CLEARENCE == 0)
                                                        CanvasPads  (CurrentNet,layer);
                                                }

                                        //CANVAS AREAS
                                        if (Form1->cl_areas->Checked || Form1->cl_pins->Checked)
                                                {
                                                if (FLAG_SWELL_CLEARENCE == 0)
                                                        CanvasLines (CurrentNet,layer,Num,a_w);
                                                }

                                        //CANVAS MASKS
                                        if (Form1->cl_sm->Checked)
                                                {
                                                if (FLAG_SWELL_CLEARENCE == 0)
                                                        CanvasMask (CurrentNet,layer);
                                                }

                                        //CANVAS PINS SAME NET
                                        if (FLAG_SWELL_CLEARENCE == 0)
                                                {
                                                CanvasThrmlP  (CurrentNet,layer);
                                                }

                                        //CANVAS GRID CUTOUTS
                                        if (Form1->dwg->Checked)
                                                {
                                                if (FLAG_SWELL_CLEARENCE == 0 )
                                                        Fractional  (CurrentNet,layer);
                                                }
                                        }
                                //
                                //ADD CONTOUR TO CUTOUTS ARRAY
                                int frst = CountLinesCut;
                                LinesCut[frst].Bounds = DEFAULT;
                                LinesCut[frst+1].Bounds = -DEFAULT;
                                for (int a=0; a<CntLnsArea; a++)
                                        {
                                        LinesCut[CountLinesCut].X1 = LinesArea[a].X1;
                                        LinesCut[CountLinesCut].Y1 = LinesArea[a].Y1;
                                        LinesCut[CountLinesCut].X2 = LinesArea[a].X2;
                                        LinesCut[CountLinesCut].Y2 = LinesArea[a].Y2;
                                        LinesCut[CountLinesCut].First = frst;
                                        LinesCut[CountLinesCut].n_board = -1;
                                        LinesCut[CountLinesCut].FlagDelete = 0;
                                        LinesCut[CountLinesCut].FlagWrite = 0;
                                        LinesCut[CountLinesCut].Arc = 0;
                                        LinesCut[CountLinesCut].n_thermal = -1;
                                        CountLinesCut++;
                                        LinesCut[frst].Bounds = MIN(LinesCut[frst].Bounds,LinesArea[a].X1);
                                        LinesCut[frst+1].Bounds = MAX(LinesCut[frst+1].Bounds,LinesArea[a].X1);
                                        }
                                LinesCut[CountLinesCut].First = CountLinesCut;
                                LinesCut[frst].n_thermal = -1;
                                //
                                /*
                                COMBINE CUTOUTS AND GENERATE CONTOURS */
                                long startX,startY;
                                Form1->V->Checked = 0;

                                // start point
                                if (Form1->cl_brd->Checked && BoardRect.Left < DEFAULT)
                                        startY = (MAX(AreaRect.Bottom, BoardRect.Bottom) + MIN(AreaRect.Top, BoardRect.Top))/2;
                                else    startY = (AreaRect.Bottom + AreaRect.Top)/2;
                                startX = TotalRect.Left;
                                //
                                CCombine Doc;
                                Doc.Ini(LinesCut,Corners,CountLinesCut,CountLinesCut,startX-_2541,startY-_2541,ThermalLineWidth,!Form1->V->Checked);
                                C = 0;
                                int mem_C = 0;
                                int full = 0;
                                int memArNum = ArNum;
                                while (1)
                                        {
                                        if (CountLinesCut && FLAG_SWELL_CLEARENCE == 0)
                                                {
                                                //INVERSION
                                                if (Form1->inv->Checked)
                                                        full = Inversion  (mem_C);
                                                else    full = Doc.Combine();
                                                if( full == DEFAULT )
                                                        {
                                                        FLAG_SWELL_CLEARENCE = TRUE;
                                                        full = LinesCutToCornersConverter();
                                                        }
                                                C = full - mem_C;
                                                if (!full)
                                                        {
                                                        if( Form1->V->Checked == 0 )
                                                                {
                                                                Form1->V->Checked = 1;
                                                                startY = TotalRect.Bottom;
                                                                if (Form1->cl_brd->Checked && BoardRect.Left < DEFAULT)
                                                                        startX = (MAX(AreaRect.Left, BoardRect.Left) + MIN(AreaRect.Right, BoardRect.Right))/2;
                                                                else    startX = (AreaRect.Left + AreaRect.Right)/2;
                                                                Doc.Ini(LinesCut,Corners,CountLinesCut,CountLinesCut,startX-_2541,startY-_2541,ThermalLineWidth,!Form1->V->Checked);
                                                                continue;
                                                                }
                                                        break;
                                                        }
                                                }
                                        /* WR NEW AREA */
                                        ArNum++;
                                        oa_num++;
                                        AddToWriteFPC = "area: ";
                                        AddToOnly =     "area: ";
                                        AddToWriteFPC += AnsiString(ArNum);
                                        AddToOnly +=     AnsiString(oa_num);
                                        // ncorners
                                        AddToWriteFPC += " ";
                                        AddToOnly +=     " ";
                                        if (C) AddToWriteFPC += AnsiString(C);
                                        else   AddToWriteFPC += AnsiString(CntLnsArea);
                                        if (C) AddToOnly += AnsiString(C);
                                        else   AddToOnly += AnsiString(CntLnsArea);
                                        // layer
                                        AddToWriteFPC += " ";
                                        AddToOnly +=     " ";
                                        AddToWriteFPC += AnsiString(layer);
                                        AddToOnly +=     AnsiString(layer);
                                        // hatch
                                        AddToWriteFPC += " ";
                                        AddToOnly +=     " ";
                                        AddToWriteFPC += AnsiString(1);
                                        AddToOnly +=     AnsiString(1);
                                        // width
                                        AddToWriteFPC += " ";
                                        AddToOnly +=     " ";
                                        AddToWriteFPC += AnsiString((int)a_w);
                                        AddToOnly +=     AnsiString((int)a_w);
                                        // merge index
                                        AddToWriteFPC += " ";
                                        AddToOnly +=     " ";
                                        AddToWriteFPC += AnsiString((int)M_index);
                                        AddToOnly +=     AnsiString((int)M_index);
                                        //
                                        Form1->ONLY->Items->Add(AddToOnly);
                                        Form1->WRITEFPC->Items->Add(AddToWriteFPC);
                                        int Cor = 0;
                                        if (C) for (int n=mem_C; n<full; n++)
                                                {
                                                Cor++;
                                                AddToWriteFPC = "corner: ";
                                                AddToWriteFPC += Cor;
                                                AddToWriteFPC += " ";
                                                AddToWriteFPC += AnsiString((long)Corners[n].X);
                                                AddToWriteFPC += " ";
                                                AddToWriteFPC += AnsiString((long)Corners[n].Y);
                                                AddToWriteFPC += " 0 ";
                                                AddToWriteFPC += AnsiString((long)Corners[n].Flag);
                                                AddToOnly = "corner: ";
                                                AddToOnly += Cor;
                                                AddToOnly += " ";
                                                AddToOnly += AnsiString((long)Corners[n].X);
                                                AddToOnly += " ";
                                                AddToOnly += AnsiString((long)Corners[n].Y);
                                                AddToOnly += " 0 ";
                                                AddToOnly += AnsiString((long)Corners[n].Flag);
                                                Form1->ONLY->Items->Add(AddToOnly);
                                                Form1->WRITEFPC->Items->Add(AddToWriteFPC);
                                                }
                                        else for (int n=0; n<CntLnsArea; n++)
                                                {
                                                Cor++;
                                                AddToWriteFPC = "corner: ";
                                                AddToWriteFPC += Cor;
                                                AddToWriteFPC += " ";
                                                AddToWriteFPC += AnsiString((long)LinesArea[n].X1);
                                                AddToWriteFPC += " ";
                                                AddToWriteFPC += AnsiString((long)LinesArea[n].Y1);
                                                if (n == (CntLnsArea-1)) AddToWriteFPC += " 0 1";
                                                else                     AddToWriteFPC += " 0 0";
                                                AddToOnly = "corner: ";
                                                AddToOnly += Cor;
                                                AddToOnly += " ";
                                                AddToOnly += (long)LinesArea[n].X1;
                                                AddToOnly += " ";
                                                AddToOnly += (long)LinesArea[n].Y1;
                                                if (n == (CntLnsArea-1)) AddToOnly += " 0 1";
                                                else                     AddToOnly += " 0 0";
                                                Form1->ONLY->Items->Add(AddToOnly);
                                                Form1->WRITEFPC->Items->Add(AddToWriteFPC);
                                                }
                                        mem_C = full;
                                        if (!CountLinesCut || FLAG_SWELL_CLEARENCE)
                                                break;
                                        }
                                if( memArNum == ArNum && ObjMan )
                                        ShowMessage( "Not a single contour was obtained in this area for filling!" );
                                continue;
                                }
                        }
                ArNum++;
                AddToWriteFPC = "area: ";
                AddToWriteFPC += AnsiString(ArNum);
                AddToWriteFPC += " ";
                AddToWriteFPC += AnsiString(numb_cor);
                AddToWriteFPC += " ";
                AddToWriteFPC += AnsiString(layer);
                AddToWriteFPC += " ";
                AddToWriteFPC += AnsiString(HatchStyle);
                AddToWriteFPC += " ";
                AddToWriteFPC += AnsiString(A_W);
                AddToWriteFPC += " ";
                AddToWriteFPC += AnsiString(M_index);
                Form1->WRITEFPC->Items->Add(AddToWriteFPC);
                continue;
                }
        else if (A.SubString(1,8) == "[merges]")
                i_merges = FileIndex;
        else if (A.SubString(1,5) == "[end]")
                i_merges = Form1->File->Items->Count;
        Form1->WRITEFPC->Items->Add(A);
        if( FileIndex >= i_merges )
                Form1->ONLY->Items->Add(A);
        }
Form3->Label1->Caption = "Complete";
Application->ProcessMessages();
//
if( nTHERMAL%4 )
        {
        ShowMessage("  EN: Warning! nTHERMAL%4!=0 (Debug_Areas.cpp)");
        }
HoleClearance -= a_w/2;
ofstream WRFPC (Areas.c_str());
for (int k=0; k<Form1->WRITEFPC->Items->Count; k++)
        {
        A = Form1->WRITEFPC->Items->operator [](k);
        WRFPC << A.c_str() << endl;
        }
WRFPC.close();
ofstream ONLYA (OnlyAreas.c_str());
ONLYA << "[options]" << endl;
ONLYA << "units: MM" << endl;
ONLYA << n_copper_layers.c_str() << endl;
ONLYA << "[footprints]" << endl;
ONLYA << "[board]" << endl;
ONLYA << "[solder_mask_cutouts]" << endl;
ONLYA << "[parts]" << endl;
ONLYA << "[nets]" << endl;
for (int k=0; k<Form1->ONLY->Items->Count; k++)
        {
        A = Form1->ONLY->Items->operator [](k);
        ONLYA << A.c_str() << endl;
        }
ONLYA << "[end]" << endl;
ONLYA.close();
//-------------������ ------------
/*if (Form1->inv->Checked)
        {
        AnsiString InvAreas = ExtractFilePath(Application->ExeName);
        InvAreas += "InvAreas.fpc";
        ofstream INV (InvAreas.c_str());
        INV << "[options]" << endl;
        INV << "units: MM" << endl;
        INV << "n_copper_layers: 2" << endl;
        INV << "[footprints]" << endl;
        INV << "[board]" << endl;
        INV << "[solder_mask_cutouts]" << endl;
        INV << "[parts]" << endl;
        INV << "[nets]" << endl;
        if (Form1->InversionCutouts->Count)
                {
                INV << "net: \"invertion_areas\" 0 0 ";
                INV << AnsiString(Inversion(true, C)).c_str();
                INV << " 0 0 0 0" << endl;
                INV << "area: 1 ";
                INV << AnsiString(Form1->InversionCutouts->Count).c_str();
                INV << " 12 1" << endl;
                for (int i=0; i<Form1->InversionCutouts->Count; i++)
                        {
                        A = Form1->InversionCutouts->Items->operator [](i);
                        INV << A.c_str() << endl;
                        }
                for (int i=0; i<Form1->InversionAreas->Count; i++)
                        {
                        A = Form1->InversionAreas->Items->operator [](i);
                        INV << A.c_str() << endl;
                        }
                }
        INV << "[texts]" << endl;
        INV << "[merges]" << endl;
        INV << "[end]" << endl;
        INV.close();
        A = ExtractFilePath(InvAreas);
        //
        SHELLEXECUTEINFO info = {0};
        AnsiString fn = ExtractFilePath(Application->ExeName);
        fn.SetLength(fn.Length()-1);
        fn = ExtractFilePath(fn);
        fn.SetLength(fn.Length()-1);
        fn = ExtractFilePath(fn) + "freepcb.exe";
        AnsiString FN = ("\""+fn+"\"");
        AnsiString ps = InvAreas;
        AnsiString PS = ("\""+ps+"\"");
        info.cbSize = sizeof(SHELLEXECUTEINFO);
        info.fMask = NULL;
        info.hwnd = NULL;
        info.lpVerb = NULL;
        info.lpFile = FN.c_str();
        info.lpParameters = PS.c_str();
        info.lpDirectory = NULL;
        info.nShow = SW_SHOW;//SW_MAXIMIZE; //SW_HIDE
        info.hInstApp = NULL;
        int INF = ShellExecuteEx(&info);
        if( INF == 0 )
                ShowMessage("Something went wrong .. If the problem persists more than once, report it to support at freepcb.dev");

        exit(0);
        }
else */if (ObjMan)
        {
        COPYDATASTRUCT cd;
        AnsiString N = ExtractFileName(OpenD);
        HWND FPC = FindWindowA(NULL, ("FreePCB - "+N).c_str());
        if( FPC == NULL )
                FPC = FindWindowA(NULL, ("FreePCB - "+N+"*").c_str());
        if( FPC )
                {
                AnsiString FF = "paste: \""+OnlyAreas+"\"";
                cd.cbData = FF.Length() + 1;
                cd.lpData = FF.c_str();
                SendMessageA(FPC, WM_COPYDATA, 0, (LPARAM)&cd);
                }
        Form3->Label1->Caption = "Complete.";
        Form3->Visible = false;
        Application->ProcessMessages();
        }
else    {
        A = ExtractFilePath(Areas);
        //
        SHELLEXECUTEINFO info = {0};
        AnsiString fn = ExtractFilePath(Application->ExeName);
        fn.SetLength(fn.Length()-1);
        fn = ExtractFilePath(fn);
        fn.SetLength(fn.Length()-1);
        fn = ExtractFilePath(fn) + "freepcb.exe";
        AnsiString FN = ("\""+fn+"\"");
        AnsiString ps = Areas;
        AnsiString PS = ("\""+ps+"\"");
        info.cbSize = sizeof(SHELLEXECUTEINFO);
        info.fMask = NULL;
        info.hwnd = NULL;
        info.lpVerb = NULL;
        info.lpFile = FN.c_str();
        info.lpParameters = PS.c_str();
        info.lpDirectory = NULL;
        info.nShow = SW_SHOW;//SW_MAXIMIZE; //SW_HIDE
        info.hInstApp = NULL;
        int INF = ShellExecuteEx(&info);
        if( INF == 0 )
                ShowMessage("Something went wrong .. If the problem persists more than once, report it to support at freepcb.dev");

        }
if (ObjMan)     Form1->Caption = "Areas";
else            Form1->Caption = "Edit Areas for " + Form1->OpenDialog1->FileName;
Form1->BitBtn1->Enabled = true;
Form1->Timer1->Enabled = true;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::BitBtn1Click(TObject *Sender)
{
CopperAreasSplitter();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::OnWMCopyData(TWMCopyData &Msg)
{
Form1->Timer1->Enabled = false;
const AnsiString mes = (char*)Msg.CopyDataStruct->lpData;
INI(mes);
Form1->Timer1->Enabled = true;
}






void __fastcall TForm1::ShLogMouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
if( Form1->ShLog->Font->Size != 10 )
        {
        Form1->ShLog->Font->Size = 10;
        Form1->ShLog->Top -= 1;
        Form1->ShLog->Left -= 2;
        }
Form3->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::GroupBox1MouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
if( Form1->ShLog->Font->Size != 8 )
        {
        Form1->ShLog->Font->Size = 8;
        Form1->ShLog->Top += 1;
        Form1->ShLog->Left += 2;
        }
if( Form1->Link->Font->Size != 8 )
        {
        Form1->Link->Font->Size = 8;
        Form1->Link->Top += 1;
        Form1->Link->Left += 5;
        }
if( bShowLog == 0 )
        if( Form1->BitBtn1->Enabled )
                Form3->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::bSelectAllClick(TObject *Sender)
{
NetsBox->SelectAll();
}
//---------------------------------------------------------------------------




void __fastcall TForm1::LinkMouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
if( Form1->Link->Font->Size != 10 )
        {
        Form1->Link->Font->Size = 10;
        Form1->Link->Top -= 1;
        Form1->Link->Left -= 5;
        }        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::LinkClick(TObject *Sender)
{
ShellExecute(NULL, "open", "https://freepcb.dev", NULL, NULL, SW_SHOWNORMAL);            
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ShLogClick(TObject *Sender)
{
bShowLog = true;        
}
//---------------------------------------------------------------------------

void save_ch()
{
ofstream ch ((ExtractFilePath(Application->ExeName)+"Ch.txt").c_str());
AnsiString A = "";
if( Form1->inv->Checked )
        A += "*";
else    A += "-";
if( Form1->dwg->Checked )
        A += "*";
else    A += "-";
if( Form1->width->Checked )
        A += "*";
else    A += "-";
if( Form1->cl_holes->Checked )
        A += "*";
else    A += "-";
if( Form1->cl_pins->Checked )
        A += "*";
else    A += "-";
if( Form1->cl_brd->Checked )
        A += "*";
else    A += "-";
if( Form1->cl_areas->Checked )
        A += "*";
else    A += "-";
if( Form1->cl_sm->Checked )
        A += "*";
else    A += "-";
if( Form1->cl_thrmlp->Checked )
        A += "*";
else    A += "-";
if( Form1->cl_th_vias->Checked )
        A += "*";
else    A += "-";
if( Form1->repour->Checked )
        A += "*";
else    A += "-";
if( Form1->replace->Checked )
        A += "*";
else    A += "-";
if( Form1->Low->Checked )
        A += "*";
else    A += "-";
if( Form1->High->Checked )
        A += "*";
else    A += "-";
if( Form1->V->Checked )
        A += "*";
else    A += "-";
if( Form1->H->Checked )
        A += "*";
else    A += "-";
if( Form1->Romb->Checked )
        A += "*";
else    A += "-";
if( Form1->Stagger->Checked )
        A += "*";
else    A += "-";
ch << A.c_str() << endl;
// Edit_width
short adr = 0;
long long Edit_width = ex_float_NM(Form1->Edit_width->Text,&adr,gUNITS);
ch << AnsiString(Edit_width).c_str() << endl;
// Edit_cl_holes
adr = 0;
long long Edit_cl_holes = ex_float_NM(Form1->Edit_cl_holes->Text,&adr,gUNITS);
ch << AnsiString(Edit_cl_holes).c_str() << endl;
// Edit_cl_pins
adr = 0;
long long Edit_cl_pins = ex_float_NM(Form1->Edit_cl_pins->Text,&adr,gUNITS);
ch << AnsiString(Edit_cl_pins).c_str() << endl;
// Edit_cl_brd
adr = 0;
long long Edit_cl_brd = ex_float_NM(Form1->Edit_cl_brd->Text,&adr,gUNITS);
ch << AnsiString(Edit_cl_brd).c_str() << endl;
// Edit_cl_areas
adr = 0;
long long Edit_cl_areas = ex_float_NM(Form1->Edit_cl_areas->Text,&adr,gUNITS);
ch << AnsiString(Edit_cl_areas).c_str() << endl;
// Edit_cl_sm
adr = 0;
long long Edit_cl_sm = ex_float_NM(Form1->Edit_cl_sm->Text,&adr,gUNITS);
ch << AnsiString(Edit_cl_sm).c_str() << endl;
// Edit_cl_thrmlp
adr = 0;
long long Edit_cl_thrmlp = ex_float_NM(Form1->Edit_cl_thrmlp->Text,&adr,gUNITS);
ch << AnsiString(Edit_cl_thrmlp).c_str() << endl;
//
ch << Form1->Edit3->Text.c_str() << endl;
ch << Form1->Edit4->Text.c_str() << endl;
ch << Form1->Edit5->Text.c_str() << endl;
ch << Form1->Edit6->Text.c_str() << endl;
ch.close();
}
void __fastcall TForm1::invClick(TObject *Sender)
{
bSAVE_CH = TRUE;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::dwgClick(TObject *Sender)
{
bSAVE_CH = TRUE;           
}
//---------------------------------------------------------------------------

void __fastcall TForm1::widthClick(TObject *Sender)
{
bSAVE_CH = TRUE;           
}
//---------------------------------------------------------------------------

void __fastcall TForm1::cl_holesClick(TObject *Sender)
{
bSAVE_CH = TRUE;           
}
//---------------------------------------------------------------------------

void __fastcall TForm1::cl_pinsClick(TObject *Sender)
{
bSAVE_CH = TRUE;           
}
//---------------------------------------------------------------------------

void __fastcall TForm1::cl_brdClick(TObject *Sender)
{
bSAVE_CH = TRUE;           
}
//---------------------------------------------------------------------------

void __fastcall TForm1::cl_areasClick(TObject *Sender)
{
bSAVE_CH = TRUE;           
}
//---------------------------------------------------------------------------

void __fastcall TForm1::cl_smClick(TObject *Sender)
{
bSAVE_CH = TRUE;           
}
//---------------------------------------------------------------------------

void __fastcall TForm1::cl_thrmlpClick(TObject *Sender)
{
bSAVE_CH = TRUE;           
}
//---------------------------------------------------------------------------

void __fastcall TForm1::repourClick(TObject *Sender)
{
bSAVE_CH = TRUE;           
}
//---------------------------------------------------------------------------

void __fastcall TForm1::LowClick(TObject *Sender)
{
bSAVE_CH = TRUE;           
}
//---------------------------------------------------------------------------

void __fastcall TForm1::HighClick(TObject *Sender)
{
bSAVE_CH = TRUE;           
}
//---------------------------------------------------------------------------

void __fastcall TForm1::VClick(TObject *Sender)
{
bSAVE_CH = TRUE;           
}
//---------------------------------------------------------------------------

void __fastcall TForm1::HClick(TObject *Sender)
{
bSAVE_CH = TRUE;           
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Edit_widthChange(TObject *Sender)
{
bSAVE_CH = TRUE;           
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit_cl_holesChange(TObject *Sender)
{
bSAVE_CH = TRUE;           
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit_cl_pinsChange(TObject *Sender)
{
bSAVE_CH = TRUE;           
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit_cl_brdChange(TObject *Sender)
{
bSAVE_CH = TRUE;           
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit_cl_areasChange(TObject *Sender)
{
bSAVE_CH = TRUE;           
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit_cl_smChange(TObject *Sender)
{
bSAVE_CH = TRUE;           
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit_cl_thrmlpChange(TObject *Sender)
{
bSAVE_CH = TRUE;           
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit3Change(TObject *Sender)
{
bSAVE_CH = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit4Change(TObject *Sender)
{
bSAVE_CH = true;        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit5Change(TObject *Sender)
{
bSAVE_CH = true;        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit6Change(TObject *Sender)
{
bSAVE_CH = true;        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RombClick(TObject *Sender)
{
bSAVE_CH = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RectClick(TObject *Sender)
{
bSAVE_CH = true;        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StaggerClick(TObject *Sender)
{
bSAVE_CH = true;        
}
//---------------------------------------------------------------------------
