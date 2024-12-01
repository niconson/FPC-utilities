//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "fpcc.h"
#include "clipbrd.hpp"
#include <FileCtrl.hpp>
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
TTreeChainList TreeLabelList;
TTreeChainList DeletedNodes;
TTreeNode * Expanded=0;
TTreeNode * MouseNode=0;
// commands
bool CMD_WRITE_OPTIONS;
bool CMD_READ_OPTIONS;
bool CMD_READ_PROJECTS;
bool CMD_READ_FEEDERS;
bool mTEST;
// paths & files
AnsiString FeedersFile="";
AnsiString ProjectsDir="";
AnsiString WMCopyData="";
AnsiString WMCopyData_STORAGE="";
// variables
int V_col;
int P_col;
int V_col_fdr;
int P_col_fdr;
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
AnsiString F_str (double DBL)
{
 AnsiString STRNG;
 STRNG = FormatFloat("0.0",DBL);
 STRNG = StringReplace(STRNG,",",".",TReplaceFlags()<<rfReplaceAll);
 return STRNG;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void reset(void)
{
DeletedNodes.remove_all();
TreeLabelList.remove_all();
////Form1->TreeReport->Items->Clear();
Form1->ButtonScan->Enabled = 1;
Form1->Reset->Enabled = 0;
Form1->GridResult->RowCount = 1;
Form1->GridResult->Cells[0][1] = "";
Form1->GridResult->Cells[1][1] = "";
Form1->GridResult->Cells[2][1] = "";
ReadingProjects(ProjectsDir);
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

//----------------------------------SelectDirectory--------------------------
AnsiString SelDir (void)
        {
        AnsiString way = "";
        if(SelectDirectory("”кажите путь к папке","",way))
                return way;
        else    return "";
        }

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

//----------------------------------string to string-------------------------
AnsiString Str_Float_F (AnsiString STRING_2_DOUBLE)
{
STRING_2_DOUBLE = StringReplace(STRING_2_DOUBLE,".",",",TReplaceFlags()<<rfReplaceAll);
int L = STRING_2_DOUBLE.Length();
bool F = false;
for (int x=1; x<=L; x++)
        {
        if (STRING_2_DOUBLE.SubString(1,1) == "-") continue;
        if ((STRING_2_DOUBLE.SubString(x,1) < "0") || (STRING_2_DOUBLE.SubString(x,1) > "9"))
        if  (F) {
                STRING_2_DOUBLE = STRING_2_DOUBLE.SubString(1,(x-1));
                break;
                }
        else    {
                F = true;
                AnsiString S = STRING_2_DOUBLE.SubString(x,1);
                STRING_2_DOUBLE = StringReplace(STRING_2_DOUBLE,S,",",TReplaceFlags()<<rfReplaceAll);
                }
        }
L = STRING_2_DOUBLE.Length();
if  (((STRING_2_DOUBLE.SubString(L,1) == "-")&&(L<2))||(!L)) STRING_2_DOUBLE = "0";
if  (STRING_2_DOUBLE.SubString(1,1) == ",") STRING_2_DOUBLE = "0" + STRING_2_DOUBLE;
if  (STRING_2_DOUBLE.SubString(L,1) == ",") STRING_2_DOUBLE = STRING_2_DOUBLE + "0";
return STRING_2_DOUBLE;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
float ex_float (AnsiString Str, long *index )
{
if ((*index) == 0) *index = 1;
AnsiString Q = "";
int StrLength = Str.Length();
while ((Str.SubString(*index,1) < "0")||(Str.SubString(*index,1) > "9"))
        {
        if (Str.SubString(*index,1) == "-") Q += "-";
        if (Str.SubString(*index,1) == "+") Q += "+";
        (*index)++;
        if ((*index) > StrLength) return 0;
        }
bool bZ = 0;
if( Q.Length() > 1 )
        Q.SetLength(1);
while ((Str.SubString(*index,1) >= "0")&&(Str.SubString(*index,1) <= "9"))
        {
        Q += Str.SubString(*index,1);
        (*index)++;
        if ((*index) > StrLength) break;
        while((Str.SubString(*index,1) == ".")||(Str.SubString(*index,1) == ","))
                {
                if( !bZ )
                        Q += ",";
                bZ = true;
                (*index)++;
                if ((*index) > StrLength) break;
                }
        if ((*index) > StrLength) break;
        }
int endI = *index;
while (Str.SubString((*index),1) == " ") (*index)++;
if (Q.SubString(Q.Length(),1) == ",") Q += "0";
float DE = 0;
if( Q.Length() )
if(!TryStrToFloat( Q, DE ))
        {
        ShowMessage(" Can't convert to float: " + Q );
        }
return DE;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

//-------------------------------------extract string------------------------
AnsiString ex_str (AnsiString ANSI, short int *n)
{
short int LEN = ANSI.Length();
while (ANSI.SubString((*n),1) != "\"")
        {
        (*n)++;
        if ((*n) > LEN) return "Empty";
        }
(*n)++;
short int st = *n;
while (ANSI.SubString((*n),1) != "\"")
        {
        (*n)++;
        if ((*n) > LEN) return "Error_func_ex_str";
        }
short int end = *n;
(*n)++;
return ANSI.SubString(st,(end-st)) ;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

//--------------------------------------prob---------------------------------
// while not space
// shift cursor
long prob (AnsiString ANSI , short int Pr)
{
short int ind = 0;
int ANSILength = ANSI.Length();
while (Pr)
        {
        ind++;
        if (ind > ANSILength) return 0;
        if (ANSI.SubString(ind,1) == "\"")
                {
                ind++;
                while (ANSI.SubString(ind,1) != "\"")
                        {
                        ind++;
                        if (ind > ANSILength) return 0;
                        }
                }
        if (ANSI.SubString(ind,1) == " ")
                {
                Pr--;
                while (ANSI.SubString(ind,1) == " ")
                        {
                        ind++;
                        if (ind > ANSILength) return 0;
                        }
                ind--;
                }
        }
while (ANSI.SubString(ind,1) == " ") ind++;
if (ind > ANSILength) return 0;
return ind;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

//-------------------------------------main----------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
        mTEST = 0;
        DecimalSeparator = ',';
        Form1->TreeReport->MultiSelect = true;
        Form1->ComboHelp->Style = csOwnerDrawFixed;
        Form1->ProjectsList->MultiSelect = true;
        Form1->MicroStrings->Visible = false;
        Form1->lbReport->Visible = false;
        Form1->lbReport->Sorted = false;
        Form1->MicroStrings->Sorted = false;
        Form1->GridFeeders->RowCount = 2;
        Form1->GridFeeders->ColCount = 3;
        Form1->GridFeeders->Width = 576;
        Form1->GridFeeders->ColWidths[0] = 165;
        Form1->GridFeeders->ColWidths[1] = 187;
        Form1->GridFeeders->ColWidths[2] = 187;
        Form1->GridFeeders->Cells[0][0] = "feeder number";
        Form1->GridFeeders->Cells[1][0] = "value";
        Form1->GridFeeders->Cells[2][0] = "package";
        Form1->GridResult->RowCount = 1;
        Form1->GridResult->ColCount = 3;
        Form1->GridResult->Width = 576;
        Form1->GridResult->ColWidths[0] = 250;
        Form1->GridResult->ColWidths[1] = 145;
        Form1->GridResult->ColWidths[2] = 145;
        Form1->GridResult->Cells[0][0] = "project name";
        Form1->GridResult->Cells[1][0] = "matching feeders";
        Form1->GridResult->Cells[2][0] = "new feeders";
        //
        Form1->lbReplace->RowCount = 2;
        Form1->lbReplace->ColCount = 2;
        Form1->lbReplace->ColWidths[0] = 260;
        Form1->lbReplace->ColWidths[1] = 260;
        Form1->lbReplace->Cells[0][0] = "Attribute";
        Form1->lbReplace->Cells[1][0] = "Analogue";
        Form1->VALUES->Sorted = 0;
        Form1->PACKAGES->Sorted = 0;
        Form1->FileNumbers->Sorted = 0;
        Form1->ColMem->Sorted = 0;
        Form1->FileBox->Sorted = 0;
        Form1->ComboHelp->Sorted = 0;
        Form1->StorageLine->Sorted = 0;
        clear_cmd;
        r_options;
        r_projects;
        r_feeders;
        CmdPlay->Enabled = true;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

//--------------------------------CmdPlayTimer-------------------------------
void __fastcall TForm1::CmdPlayTimer(TObject *Sender)
{
        CmdPlay->Enabled = 0;
        if( CMD_READ_OPTIONS )
                {
                CMD_READ_OPTIONS = false;
                ReadingOptions(&FeedersFile,&ProjectsDir);
                }
        while( CMD_READ_PROJECTS )
                {
                CMD_READ_PROJECTS = false;
                if( WMCopyData.Length() )
                        {
                        ProjectsDir = WMCopyData;
                        if( Vcol->Text.SubString(1,Vcol->Text.Length()) != "1" ||
                            Pcol->Text.SubString(1,Pcol->Text.Length()) != "2" )
                                {
                                Vcol->Text = 1;
                                Pcol->Text = 2;
                                break;
                                }
                        }
                if( ProjectsDir.Length() )
                        ReadingProjects(ProjectsDir);
                }
        while( CMD_READ_FEEDERS )
                {
                CMD_READ_FEEDERS = false;
                if( WMCopyData_STORAGE.Length() )
                        {
                        FeedersFile = WMCopyData_STORAGE;
                        if( fdr_col_V->Text.SubString(1,fdr_col_V->Text.Length()) != "1" ||
                            fdr_col_P->Text.SubString(1,fdr_col_P->Text.Length()) != "2" )
                                {
                                fdr_col_V->Text = "1";
                                fdr_col_P->Text = "2";
                                break;
                                }
                        }
                if( FeedersFile.Length() )
                        ReadingFeeders(FeedersFile);
                }
        CmdPlay->Enabled = 1;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
        WritingOptions(FeedersFile,ProjectsDir,Form1->DSL->Checked);
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonProjectsClick(TObject *Sender)
{
        WMCopyData = "";
        ProjectsDir = SelDir();
        r_projects;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonFeedersClick(TObject *Sender)
{
        WMCopyData_STORAGE = "";
        AnsiString get = SelDir();
        if( get.Length() )
                {
                FeedersFile = get;
                Form1->StorageLine->Items->Add(FeedersFile);
                Form1->ColMem->Items->Add(fdr_col_V->Text+" "+fdr_col_P->Text);
                Form1->StorageLine->ItemIndex = Form1->StorageLine->Items->Count-1;
                r_feeders;
                }
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TForm1::Btn_Feed_Sort_VClick(TObject *Sender)
{
Sort(1);
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TForm1::Btn_Feed_Sort_PClick(TObject *Sender)
{
Sort(2);        
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TForm1::Btn_Sort_Match_VClick(TObject *Sender)
{
Sort(1);        
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TForm1::Btn_Sort_Match_PClick(TObject *Sender)
{
Sort(2);        
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TForm1::ProjectsListDblClick(TObject *Sender)
{
AnsiString B = Form1->ProjectsList->Items->operator [](Form1->ProjectsList->ItemIndex);
AnsiString A = ExtractFileName(B);
if ((UINT)ShellExecute(NULL,
               "open",
               B.c_str(),
               NULL,
               A.c_str() ,
               SW_SHOWNORMAL) <=32)
               {
                 ShowMessage  ("What program to open this file? There is no application associated with files.");
               }
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TForm1::bnRClick(TObject *Sender)
{
GenReportTXT();
AnsiString B = ExtractFilePath(Application->ExeName) + "report.txt";
AnsiString A = "report.txt";
if ((UINT)ShellExecute(NULL,
               "open",
               B.c_str(),
               NULL,
               A.c_str() ,
               SW_SHOWNORMAL) <=32)
               {
                 ShowMessage  ("What program to open this file? There is no application associated with *.TXT files.");
               }
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
int ClearPartFound(void)
{
int f = 0;
for( int index=Form1->FileNumbers->Items->Count-1; index>=0; index-- )
        {
        if( Form1->FileNumbers->Items->operator [](index).SubString(1,1) == "f" )
                {
                f++;
                Form1->VALUES->Items->Delete(index);
                Form1->PACKAGES->Items->Delete(index);
                Form1->FileNumbers->Items->Delete(index);
                }
        }
return f;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonScanMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if( !mTEST )
        {
        Form1->Reset->Enabled = 1;
        Form1->ButtonScan->Enabled = 0;
        }
if( V_col == P_col )
        {
        ShowMessage( " EN: The column numbers must not be equal (Columns)." );
        return;
        }
if( V_col < 0 || P_col < 0 )
        {
        ShowMessage( " EN: Illegal column number (Columns)." );
        return;
        }
if( !Form1->ProjectsList->SelCount )
        {
        ShowMessage( " EN: Please select projects (Projects)!" );
        return;
        }
TreeLabelList.remove_all();
TTreeNode * Head;
if( !mTEST )
        Head = Form1->TreeReport->Items->Add( NULL, "Report for "+ExtractFileName(FeedersFile)+" storage ("+Now().CurrentDate()+" "+Now().CurrentTime()+")");
else    Head = Form1->TreeReport->Items->Add( NULL, "Testing for "+ExtractFileName(FeedersFile)+" storage");
for( int sel=0; sel<Form1->ProjectsList->Items->Count; sel++ )
        {
        if( !Form1->ProjectsList->Selected[sel] )
                continue;
        AnsiString FILE = Form1->ProjectsList->Items->operator [](sel);
        if( !mTEST )
                {
                Form1->lbReport->Items->Clear();
                Form1->GridResult->RowCount++;
                }
        Compare( sel+1, mTEST );
        if( !mTEST )
                {
                Form1->GridResult->Cells[0][Form1->GridResult->RowCount-1] = ExtractFileName(FILE);
                TTreeNode * Childs = Form1->TreeReport->Items->AddChild(
                                                Head,
                                                ExtractFileName(FILE));
                TTreeNode * ChildMatches = Form1->TreeReport->Items->AddChild(
                                                Childs,
                                                "matches");
                TTreeNode * ChildNews = Form1->TreeReport->Items->AddChild(
                                                Childs,
                                                "new elements");
                TTreeNode * LastNode = ChildNews;
                TTreeNode * CLOSE_IN_VALUE = NULL;
                int nm=0, nn=0;
                for( int copy=0; copy<Form1->lbReport->Items->Count; copy++ )
                        {
                        AnsiString cp = Form1->lbReport->Items->operator [](copy);
                        if( cp.SubString(1,1) == "m" )
                                {
                                CLOSE_IN_VALUE = NULL;
                                nm++;
                                LastNode = Form1->TreeReport->Items->AddChild(
                                        ChildMatches,
                                        (AnsiString(nm) + ") " + cp.SubString(8,cp.Length()-7)).c_str());
                                }
                        else if( cp.SubString(1,1) == "n" )
                                {
                                CLOSE_IN_VALUE = NULL;
                                nn++;
                                LastNode = Form1->TreeReport->Items->AddChild(
                                        ChildNews,
                                        (AnsiString(nn) + ") " + cp.SubString(6,cp.Length()-5)).c_str());
                                }
                        else if( cp.SubString(1,1) == "s" )
                                {
                                CLOSE_IN_VALUE = NULL;
                                TTreeNode * SIMILAR = Form1->TreeReport->Items->AddChild(LastNode,cp);
                                Form1->TreeReport->Items->AddChild(SIMILAR,"To choose as a replacement");
                                }
                        else if( cp.SubString(1,1) == "c" )
                                {
                                if( CLOSE_IN_VALUE == NULL )
                                        {
                                        CLOSE_IN_VALUE = Form1->TreeReport->Items->AddChild(LastNode,"Show more...");
                                        }
                                TTreeNode * CLOSE = Form1->TreeReport->Items->AddChild(CLOSE_IN_VALUE,cp);
                                Form1->TreeReport->Items->AddChild(CLOSE,"To choose as a replacement");
                                }
                        }
                }
        }
if( !mTEST )
        {
        TTreeNode * found = Form1->TreeReport->Items->AddChild(
                                        Head,
                                        "feeders_found");
        TTreeNode * not_found = Form1->TreeReport->Items->AddChild(
                                        Head,
                                        "feeders_not_found");
        int num_f = 0;
        int num_nf = 0;
        for( int i=1; i<Form1->GridFeeders->RowCount; i++ )
                {
                AnsiString add0 = Form1->GridFeeders->Cells[0][i];
                AnsiString add1 = Form1->GridFeeders->Cells[1][i];
                AnsiString add2 = Form1->GridFeeders->Cells[2][i];
                if( add1.Length() || add2.Length() )
                        {
                        if( add0.SubString(1,1) == "f" )
                                Form1->TreeReport->Items->AddChild(
                                                        found,
                                                        AnsiString(++num_f)+") "+add1+" "+add2 );
                        else    Form1->TreeReport->Items->AddChild(
                                                        not_found,
                                                        AnsiString(++num_nf)+") "+add1+" "+add2 );
                        }
                }
        ClearPartFound();
        }
mTEST = 0;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TForm1::bnTestMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
mTEST = TRUE;        
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TForm1::GridFeedersDrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
AnsiString s = GridFeeders->Cells[0][ARow];
if (s.SubString(1,2) == "fo")
        {
        GridFeeders->Canvas->Brush->Color = clGray;
        GridFeeders->Canvas->Font->Color = clWhite;
        GridFeeders->Canvas->FillRect(Rect);
        }
else    {
        GridFeeders->Canvas->Brush->Color = GridFeeders->Color;
        GridFeeders->Canvas->Font->Color = GridFeeders->Font->Color;
        GridFeeders->Canvas->FillRect(Rect);
        }
DrawText(GridFeeders->Canvas->Handle,
GridFeeders->Cells[ACol][ARow].c_str(),
GridFeeders->Cells[ACol][ARow].Length(),&Rect, DT_CENTER);
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
Sort(0);        
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TForm1::Label5Click(TObject *Sender)
{
ShellExecute(NULL, "open", "https://github.com/niconson", NULL, NULL, SW_SHOWNORMAL);         
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TForm1::ch_csvClick(TObject *Sender)
{
r_projects;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TForm1::OnWMCopyData(TWMCopyData &Msg)
{
        AnsiString SS = (char*)Msg.CopyDataStruct->lpData;
        if( SS.SubString(1,7) == "storage" )
                {
                short ii = 9;
                SS = ex_str(SS,&ii);
                WMCopyData_STORAGE = SS;
                if( Form1->StorageLine->Items->IndexOf(SS) == -1 )
                        {
                        Form1->StorageLine->Items->Add(SS);
                        Form1->ColMem->Items->Add("1 2");
                        if( Form1->StorageLine->ItemIndex < 0 )
                                Form1->StorageLine->ItemIndex = Form1->StorageLine->Items->Count-1;
                        }
                r_feeders;
                //ShowMessage(WMCopyData_STORAGE);
                }
        else    {
                WMCopyData = SS;
                r_projects;
                //ShowMessage(WMCopyData);
                }
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TForm1::ExcludeAsteriskClick(TObject *Sender)
{
r_feeders;
r_projects;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TForm1::TreeReportKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if( Key == VK_DELETE )
        {
        if( Form1->TreeReport->Selected )
                ParentItemDelete(Form1->TreeReport->Selected);
        }
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TForm1::TreeReportCustomDrawItem(TCustomTreeView *Sender,
      TTreeNode *Node, TCustomDrawState State, bool &DefaultDraw)
{
if ( TreeLabelList.iof(Node) )
        {
        Form1->TreeReport->Canvas->Font->Color = clGray;
        Form1->TreeReport->Canvas->Font->Style = Form1->TreeReport->Canvas->Font->Style << fsStrikeOut;
        }
else if( DeletedNodes.iof(Node) || DeletedNodes.iof(Node->Parent) )
        {
        Form1->TreeReport->Canvas->Font->Color = clBlue;
        }
else if( Node->Text.SubString(1,4) == "To c" )
        {
        Form1->TreeReport->Canvas->Font->Color = clBlack;
        if( Node == MouseNode )
                {
                Form1->TreeReport->Canvas->Font->Color = clBlue;
                Form1->TreeReport->Canvas->Font->Style = Form1->TreeReport->Canvas->Font->Style << fsUnderline;
                }
        }
else if( Node == Expanded )
        {
        Form1->TreeReport->Canvas->Font->Color = clRed;
        }
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
int ValuesPackagesDeleteItem(AnsiString V,AnsiString P)
{
int count=0;
for( int index=ValuesPackages_iof(V,P); index>=0; index=ValuesPackages_iof(V,P) )
       {
       count++;
       Form1->VALUES->Items->Delete(index);
       Form1->PACKAGES->Items->Delete(index);
       Form1->FileNumbers->Items->Delete(index);
       }
return count;
}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TForm1::TreeReportMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if( Form1->TreeReport->Selected )
        {
        bool W = 0;
        AnsiString r = Form1->TreeReport->Selected->Text;
        int p1 = r.Pos(") ");
        if( p1 > 0 && p1 < 5 )
                W = 1;
        if(r.SubString(1,7) == "similar")
                W = 1;
        if( W ) {
                r = r.SubString(p1+1,r.Length()-p1);
                p1 = r.Pos(dSPACE);
                AnsiString gV = r.SubString(1,p1-1);
                gV = gV.Trim();
                AnsiString gP = r.SubString(p1+2,r.Length()-p1-1);
                gP = gP.Trim();
                if( TreeLabelList.iof( Form1->TreeReport->Selected ) == 0 )
                        {
                        //if( ValuesPackages_iof(gV,gP) >= 0 )
                        //        ValuesPackagesDeleteItem(gV,gP);
                        if( Form1->StrikeThrough->Checked )
                                {
                                if( Form1->ExclV->Lines->IndexOf(gV) == -1 )
                                        Form1->ExclV->Lines->Add(gV);
                                if( Form1->ExclP->Lines->IndexOf(gP) == -1 )
                                        Form1->ExclP->Lines->Add(gP);
                                for( int ii=Form1->ExclV->Lines->Count-1; ii>=0; ii-- )
                                        if( Form1->ExclV->Lines->operator [](ii).Length() == 0 )
                                                Form1->ExclV->Lines->Delete(ii);
                                for( int ii=Form1->ExclP->Lines->Count-1; ii>=0; ii-- )
                                        if( Form1->ExclP->Lines->operator [](ii).Length() == 0 )
                                                Form1->ExclP->Lines->Delete(ii);
                                }
                        TreeLabelList.add( Form1->TreeReport->Selected );
                        }
                else    {
                        //if( ValuesPackages_iof(gV,gP) == -1 )
                        //        ValuesPackages_add(gV,gP,);
                        if( Form1->StrikeThrough->Checked )
                                {
                                int ind = Form1->ExclV->Lines->IndexOf(gV);
                                if( ind != -1 )
                                        Form1->ExclV->Lines->Delete(ind);
                                ind = Form1->ExclP->Lines->IndexOf(gP);
                                if( ind != -1 )
                                        Form1->ExclP->Lines->Delete(ind);
                                for( int ii=Form1->ExclV->Lines->Count-1; ii>=0; ii-- )
                                        if( Form1->ExclV->Lines->operator [](ii).Length() == 0 )
                                                Form1->ExclV->Lines->Delete(ii);
                                for( int ii=Form1->ExclP->Lines->Count-1; ii>=0; ii-- )
                                        if( Form1->ExclP->Lines->operator [](ii).Length() == 0 )
                                                Form1->ExclP->Lines->Delete(ii);
                                }
                        TreeLabelList.deleteNode( Form1->TreeReport->Selected );
                        }
                }
        }
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
bool lbReplace_add (AnsiString s1, AnsiString s2)
{
for( int i=0; i<Form1->lbReplace->RowCount; i++ )
        {
        if( Form1->lbReplace->Cells[0][i].Length() == 0 && Form1->lbReplace->Cells[1][i].Length() == 0 )
                {
                Form1->lbReplace->Cells[0][i] = s1;
                Form1->lbReplace->Cells[1][i] = s2;
                return true;
                }
        }
Form1->lbReplace->RowCount++;
Form1->lbReplace->Cells[0][Form1->lbReplace->RowCount-1] = s1;
Form1->lbReplace->Cells[1][Form1->lbReplace->RowCount-1] = s2;
return true;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
int ValuesPackages_iof( AnsiString v, AnsiString p )
{
for( int i1=Form1->VALUES->Items->Count-1; i1>=0; i1-- )
        {
        AnsiString getv = Form1->VALUES->Items->operator [](i1);
        if( getv.SubString(1, getv.Length()) == v.SubString(1, v.Length()) )
                {
                AnsiString getp = Form1->PACKAGES->Items->operator [](i1);
                if( getp.SubString(1, getp.Length()) == p.SubString(1, p.Length()) )
                        {
                        return i1;
                        }
                }
        }
return -1;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
int ValuesPackages_add( AnsiString v, AnsiString p, AnsiString nFile )
{
        Form1->VALUES->Items->Add(v);
        Form1->PACKAGES->Items->Add(p);
        Form1->FileNumbers->Items->Add(nFile);
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void ParentItemDelete(TTreeNode * Parent)
{
int numprev = 0;
for( TTreeNode * node=Parent->GetNextVisible(); node; node=node->GetNextVisible() )
        {
        AnsiString nt = node->Text;
        int p = nt.Pos(") ");
        int num;
        if( p <= 0 || p > 4 )
                num = numprev;
        else    {
                long n = 0;
                num = ex_float( nt.SubString(1,p-1), &n );
                }
        if( num < numprev )
                break;
        else if( num > numprev )
                node->Text = AnsiString(num-1) + nt.SubString(p,nt.Length()-p+1);
        numprev = num;
        }
AnsiString nt = Parent->Text;
int p = nt.Pos(") ");
int num;
if( p > 0 && p <= 4 )
        {
        nt = nt.SubString(p+2,nt.Length()-p-1) + " - replacement found";
        Parent->Text = nt;
        }
Parent->DeleteChildren();
DeletedNodes.add(Parent);
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void IncreaseGridResult(TTreeNode * Parent)
{
for( int d=1; d<Form1->GridResult->RowCount; d++ )
        {
        Form1->GridResult->Cells[2][d] = "???";
        Form1->GridResult->Cells[1][d] = "???";
        }
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
bool LB_iof (AnsiString sA, AnsiString sB)
{
for( int ii=0; ii<Form1->lbReplace->RowCount; ii++ )
        {
        AnsiString sC = Form1->lbReplace->Cells[0][ii];
        if( sA.SubString(1,sA.Length()) == sC.SubString(1,sC.Length()) )
                {
                sC = Form1->lbReplace->Cells[1][ii];
                if( sB.SubString(1,sB.Length()) == sC.SubString(1,sC.Length()) )
                        return true;
                }
        }
int ii = Form1->lbNoReplace->Lines->IndexOf(sA+" & "+sB);
if( ii >= 0 )
        return true;
if( sA.Length() < sB.Length() )
        {
        int p = sB.Pos(sA);
        if(p==1) {
                AnsiString G = sB.SubString(sA.Length()+1,sB.Length()-sA.Length());
                if( Form1->Memo1->Lines->IndexOf(G) >= 0 )
                        return true;
                }
        }
else if( sB.Length() < sA.Length() )
        {
        int p = sA.Pos(sB);
        if(p==1) {
                AnsiString G = sA.SubString(sB.Length()+1,sA.Length()-sB.Length());
                if( Form1->Memo1->Lines->IndexOf(G) >= 0 )
                        return true;
                }
        }
return false;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TForm1::TreeReportMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if( Form1->TreeReport->Selected )
        {
        bool W = 0;
        TTreeNode * Selected = Form1->TreeReport->Selected;
        AnsiString r = Form1->TreeReport->Selected->Text;
        Form1->TreeReport->ClearSelection();
        if(r.SubString(1,4) == "To c")
                {
                TTreeNode * Parent = Selected->Parent;
                AnsiString T = Parent->Text;
                int TL = T.Length();
                //
                int p1 = T.Pos("?");
                p1 += 2;
                T = T.SubString(p1,TL-p1+1);
                TL = T.Length();
                p1 = T.Pos(" (");
                //
                T = T.SubString(1,p1-1);
                TL = T.Length();
                p1 = T.Pos(dSPACE);
                AnsiString V2 = T.SubString(1,p1-1);
                AnsiString P2 = T.SubString(p1+2,TL-p1-1);
                V2 = V2.Trim();
                P2 = P2.Trim();
                //
                Parent = Parent->Parent;
                T = Parent->Text;
                if( T.SubString(1,4) == "Show" )
                        {
                        Parent = Parent->Parent;
                        T = Parent->Text;
                        }
                TL = T.Length();
                p1 = T.Pos(")");
                int p2 = T.Pos(dSPACE);
                AnsiString V = T.SubString(p1+2,p2-p1-2);
                AnsiString P = T.SubString(p2+2,TL-p2-1);
                V = V.Trim();
                P = P.Trim();
                if( AddSelSimilar->Checked )
                        {
                        if( V.Length() && V2.Length() )
                                if( V.SubString(1,V.Length()) != V2.SubString(1,V2.Length()) )
                                        if( LB_iof(V,V2) == 0 )
                                                lbReplace_add(V,V2);
                        if( P.Length() && P2.Length() )
                                if( P.SubString(1,P.Length()) != P2.SubString(1,P2.Length()) )
                                        if( LB_iof(P,P2) == 0 )
                                                lbReplace_add(P,P2);
                        }
                //
                ValuesPackagesDeleteItem(V,P);
                IncreaseGridResult(Parent);
                ParentItemDelete(Parent);
                Form1->TreeReport->Items->AddChild(Parent,"("+V2+dSPACE+P2+")");
                Parent->Expand(true);
                }
        }
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TForm1::lbReplaceClick(TObject *Sender)
{
if( lbReplace->Row == lbReplace->RowCount-1 )
        {
        lbReplace->RowCount++;
        }
else    {
        bool bF = true;
        for( int i=lbReplace->Row+1; i<lbReplace->RowCount; i++ )
                {
                if( lbReplace->Cells[0][i].Length() || lbReplace->Cells[1][i].Length() )
                        bF = 0;
                }
        if( bF )
                lbReplace->RowCount = lbReplace->Row + 2;
        }
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TForm1::DSLMouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
if( Form1->DSL->Checked == 0 )
        WritingOptions(FeedersFile,ProjectsDir,true);
r_options;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TForm1::StorageLineKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if( Key == VK_DELETE && Form1->StorageLine->ItemIndex >= 0 )
        {
        int ii = Form1->StorageLine->ItemIndex;
        Form1->StorageLine->Items->Delete(ii);
        Form1->ColMem->Items->Delete(ii);
        Form1->StorageLine->ItemIndex = -1;
        fdr_col_V->Text = "0";
        fdr_col_P->Text = "0";
        FeedersFile = "";
        r_feeders;
        }
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TForm1::StorageLineChange(TObject *Sender)
{
if( StorageLine->ItemIndex >= 0 )
        {
        WMCopyData_STORAGE = "";
        FeedersFile = StorageLine->Items->operator [](StorageLine->ItemIndex);
        if( StorageLine->ItemIndex < ColMem->Items->Count )
                {
                AnsiString col_n = ColMem->Items->operator [](StorageLine->ItemIndex);
                long ind=0;
                int col1 = ex_float(col_n,&ind);
                int col2 = ex_float(col_n,&ind);
                fdr_col_V->Text = col1;
                fdr_col_P->Text = col2;
                }
        r_feeders;
        }
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TForm1::ResetMouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
reset();
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TForm1::fdr_col_PChange(TObject *Sender)
{
AnsiString S = Form1->fdr_col_P->Text;
P_col_fdr = (int)StrToFloat(Str_Float_F(S));
if( Form1->StorageLine->ItemIndex >= 0 )
        {
        if( Form1->StorageLine->ItemIndex < ColMem->Items->Count )
                {
                Form1->ColMem->Items->Delete(Form1->StorageLine->ItemIndex);
                }
        Form1->ColMem->Items->Insert(Form1->StorageLine->ItemIndex,fdr_col_V->Text+" "+fdr_col_P->Text);
        }
r_feeders;        
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TForm1::fdr_col_VChange(TObject *Sender)
{
AnsiString S = Form1->fdr_col_V->Text;
V_col_fdr = (int)StrToFloat(Str_Float_F(S));
if( Form1->StorageLine->ItemIndex >= 0 )
        {
        if( Form1->StorageLine->ItemIndex < ColMem->Items->Count )
                {
                Form1->ColMem->Items->Delete(Form1->StorageLine->ItemIndex);
                }
        Form1->ColMem->Items->Insert(Form1->StorageLine->ItemIndex,fdr_col_V->Text+" "+fdr_col_P->Text);
        }
r_feeders;        
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TForm1::VcolChange(TObject *Sender)
{
AnsiString S = Form1->Vcol->Text;
V_col = (int)StrToFloat(Str_Float_F(S));
r_projects;        
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TForm1::PcolChange(TObject *Sender)
{
AnsiString S = Form1->Pcol->Text;
P_col = (int)StrToFloat(Str_Float_F(S));
r_projects;        
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TForm1::TreeReportExpanded(TObject *Sender,
      TTreeNode *Node)
{
Expanded = Node;
TreeReport->Refresh();
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TForm1::TreeReportExpanding(TObject *Sender,
      TTreeNode *Node, bool &AllowExpansion)
{
Expanded = Node;
TreeReport->Refresh();
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TForm1::TreeReportMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
static int PrevNodeIndex = 0;
if( TreeReport->Items->Count > PrevNodeIndex )
        {
        TTreeNode * PrevNode = TreeReport->Items->operator [](PrevNodeIndex);
        MouseNode = TreeReport->GetNodeAt(X,Y);
        if( MouseNode && PrevNode )
                {
                if((MouseNode->Text.SubString(1,4) == "To c" && PrevNode->Text.SubString(1,4) != "To c" ) ||
                ( MouseNode->Text.SubString(1,4) != "To c" && PrevNode->Text.SubString(1,4) == "To c" ))
                        TreeReport->Refresh();
                PrevNodeIndex = MouseNode->AbsoluteIndex;
                }
        }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button2Click(TObject *Sender)
{
GenerateFeedersTXT();
AnsiString B = ExtractFilePath(Application->ExeName) + "feeders.txt";
AnsiString A = "feeders.txt";
if ((UINT)ShellExecute(NULL,
               "open",
               B.c_str(),
               NULL,
               A.c_str() ,
               SW_SHOWNORMAL) <=32)
               {
                 ShowMessage  ("What program to open this file? There is no application associated with *.TXT files.");
               }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
SaveDialog->InitialDir = FeedersFile;
SaveDialog->FileName = ExtractFileName(FeedersFile);
for( int i=0; i<StorageLine->Items->Count; i++ )
        {
        AnsiString S = StorageLine->Items->operator [](i);
        if( S.Length() > 3 )
        if( S.SubString(S.Length()-2,3) == "VPL" )
                {
                SaveDialog->InitialDir = S;
                break;
                }
        }
if(SaveDialog->Execute())
        {
        AnsiString B = GenerateVPL(SaveDialog->FileName);
        AnsiString A = ExtractFileName(B);
        if ((UINT)ShellExecute(NULL,
               "open",
               B.c_str(),
               NULL,
               A.c_str() ,
               SW_SHOWNORMAL) <=32)
               {
                 ShowMessage  ("What program to open this file? There is no application associated with *.TXT files.");
               }
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
AnsiString A = ExtractFileName(FeedersFile);
if ((UINT)ShellExecute(NULL,
               "open",
               FeedersFile.c_str(),
               NULL,
               A.c_str() ,
               SW_SHOWNORMAL) <=32)
               {
                 ShowMessage  ("What program to open this file? There is no application associated with files.");
               }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::GridFeedersClick(TObject *Sender)
{
FileBox->ItemIndex = GridFeeders->Row;
}
//---------------------------------------------------------------------------

