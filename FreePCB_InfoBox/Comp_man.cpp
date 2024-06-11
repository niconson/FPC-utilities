//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "NC.h"
//#include "Find_Files.h"
#include "Path_EXE.h"
#include "Nets.h"
#include "fstream.h"
#include "Comp_man.h"
//#include "Clipbrd.hpp"
//#include "time.h"
//#include <Registry.hpp>
//#include <FileCtrl.hpp>
//#include <winuser.h>
//#include <windows.h>
//#include <mem.h>
//#include <string.h>
//#include <map>
//******************* ОБЪЯВЛЕНИЯ *************************
//--------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
AnsiString A,B;
AnsiString SVRef;
AnsiString PathProg;
AnsiString FileName;
AnsiString GerberPath;
AnsiString NetListPath;
AnsiString WindowHeader;
AnsiString HeaderBack;
AnsiString FileNameBack;
AnsiString Paste_area;
AnsiString Part_list;
AnsiString GlobalPinText;
HWND Wind;

int Form1_Left = 0;
int Form1_Top = 0;
int Form1_Width = 500;
int Form1_Height = 120;

//Drag Form1:
int MemForm1Height;
int MemMouseX;
int MemMouseY;
int SORT_CASE = 0;
//
int N_PART_ELEMENTS=0;
int N_PIN_ELEMENTS=0;
int StringGridPartsRowIndex;
int StringGridPinsRowIndex;
int n_copper_layers=0;
int m_report_flags=0;
double Grid1ColWidth[PartsColCount];
double Grid2ColWidth[PinsColCount];
long i;
long k;
long n;
long m;
long Pause;
long BRDRect[4];                //размер платы
int PartColOrder[PartsColCount] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
long CountStringsFile;          //кол-во строк в файле
long LONGDEFAULT;
int SortedCase;                 //Флаг порядка в листбокс 0-ref, 1-val, 1-package ....
int UNITS;
int FRead_File =        0;
bool Disable_ENTER =    false;  //Запрет нажатия клав ENTER
bool MousDblClick =     false;
bool BEGIN =            false;
bool FlagSaveFilter =   false;
bool FlagProgEXE =      false;
bool bEditPinsMess =    false;
bool bEditKITMess  =    false;
bool bUPDFILE =         false;
bool PinsWasR =         false;
char s[2501];
COPYDATASTRUCT CDS_SHORT;
COPYDATASTRUCT CDS_LONG;

AnsiString ColNames[PartsColCount] = {  "RefDes",
                                        "Index",
                                        "Value",
                                        "ValueNL",
                                        "Package",
                                        "FootPrint",
                                        "PackageNL",
                                        "Merge",
                                        "Pins",
                                        "Holes",
                                        "Glued",
                                        "Side",
                                        "Angle",
                                        "partX",
                                        "partY",
                                        "CompareNetlist"};

/*TButton * GetPartButton( int col )
{
switch( PartColOrder[col] )
        {
        case 0: return Form1->BRefDes;
        case 1: return Form1->BRIRange;
        case 2: return Form1->BValue;
        case 3: return Form1->BValueNL;
        case 4: return Form1->BPackage;
        case 5: return Form1->BFootPrint;
        case 6: return Form1->BPackageNL;
        case 7: return Form1->BMerge;
        case 8: return Form1->BPins;
        case 9: return Form1->BHoles;
        case 10: return Form1->BGlueds;
        case 11: return Form1->BSide;
        case 12: return Form1->BAng;
        case 13: return Form1->BX;
        case 14: return Form1->BY;
        case 15: return Form1->BCNetlist;
        }
}
TButton * GetPinButton( int col )
{
switch( PinColOrder[col] )
        {
        case 0: return Form1->BPin;
        case 1: return Form1->BPinNetPCB;
        case 2: return Form1->BCnt;
        case 3: return Form1->BPinNetList;
        case 4: return Form1->BType;
        case 5: return Form1->BW;
        case 6: return Form1->BL;
        case 7: return Form1->BTrml;
        case 8: return Form1->BDHole;
        case 9: return Form1->BPas;
        case 10: return Form1->BXPin;
        case 11: return Form1->BYPin;
        }
}
void * GetPartEdit( int col )
{
switch( PartColOrder[col] )
        {
        case 0: return Form1->CRefDes;
        case 1: return Form1->MinRI;
        case 2: return Form1->CValue;
        case 3: return Form1->CValueNL;
        case 4: return Form1->CPackage;
        case 5: return Form1->CFootPrint;
        case 6: return Form1->CPackageNL;
        case 7: return Form1->CMerge;
        case 8: return Form1->MinPin;
        case 9: return Form1->MinHoles;
        case 10: return Form1->Glueds;
        case 11: return Form1->Side;
        case 12: return Form1->Ang;
        case 13: return Form1->EXmin;
        case 14: return Form1->EYmin;
        case 15: return Form1->CCNetlist;
        }
}
void * GetPinEdit( int col )
{
switch( PinColOrder[col] )
        {
        case 0: return Form1->CPin;
        case 1: return Form1->CPinNetPCB;
        case 2: return Form1->CCnt;
        case 3: return Form1->CNetNetlist;
        case 4: return Form1->CType;
        case 5: return Form1->WPinMin;
        case 6: return Form1->LPinMin;
        case 7: return Form1->CTrml;
        case 8: return Form1->DHoleMin;
        case 9: return Form1->Pas;
        case 10: return Form1->XPinMin;
        case 11: return Form1->YPinMin;
        }
}  */
int PartsColLen(int col)
{
        int max = 5;
        if( col == def_RefDes )
                max = Form1->BRefDes->Caption.Length();
        else if( col == def_RIRange )
                max = Form1->BRIRange->Caption.Length();
        else if( col == def_Value )
                max = Form1->BValue->Caption.Length();
        else if( col == def_ValueNL )
                max = Form1->BValueNL->Caption.Length();
        else if( col == def_Package )
                max = Form1->BPackage->Caption.Length();
        else if( col == def_FootPrint )
                max = Form1->BFootPrint->Caption.Length();
        else if( col == def_PackageNL )
                max = Form1->BPackageNL->Caption.Length();
        else if( col == def_Merge )
                max = Form1->BMerge->Caption.Length();
        else if( col == def_Pins )
                max = Form1->BPins->Caption.Length();
        else if( col == def_Holes )
                max = Form1->BHoles->Caption.Length();
        else if( col == def_Gl )
                {
                max = MAX(max,Form1->BGlueds->Caption.Length());
                return max;
                }
        else if( col == def_S )
                {
                max = MAX(max,Form1->BSide->Caption.Length());
                return max;
                }
        else if( col == def_Ang )
                max = Form1->BAng->Caption.Length();
        else if( col == def_Xprt )
                max = Form1->BX->Caption.Length();
        else if( col == def_Yprt )
                max = Form1->BY->Caption.Length();
        else if( col == def_CompareNetlist )
                max = Form1->BCNetlist->Caption.Length();
        //
        max = MAX(5,max);
        for (int row=0; row<Form1->StringGridParts->RowCount; row++)
                if (max<Form1->StringGridParts->Cells[col][row].Length())
                        max=Form1->StringGridParts->Cells[col][row].Length();
        return max;
}
//---------------------
int PinsColLen(int col)
{
        int max = 5;
        if( col == def_Pin )
                max = Form1->BPin->Caption.Length();
        else if( col == def_NetPcb )
                max = Form1->BPinNetPCB->Caption.Length();
        else if( col == def_Cnt )
                max = Form1->BCnt->Caption.Length();
        else if( col == def_Netlist )
                max = Form1->BPinNetList->Caption.Length();
        else if( col == def_Type )
                max = Form1->BType->Caption.Length();
        else if( col == def_W )
                max = Form1->BW->Caption.Length();
        else if( col == def_L )
                max = Form1->BL->Caption.Length();
        else if( col == def_Thrml )
                max = Form1->BTrml->Caption.Length();
        else if( col == def_DHole )
                max = Form1->BDHole->Caption.Length();
        else if( col == def_Pas )
                max = Form1->BPas->Caption.Length();
        else if( col == def_Xpi )
                max = Form1->BXPin->Caption.Length();
        else if( col == def_Ypi )
                max = Form1->BYPin->Caption.Length();
        //
        max = MAX(5,max);
        for (int row=0; row<Form1->StringGridPins->RowCount; row++)
                if (max<Form1->StringGridPins->Cells[col][row].Length())
                        max=Form1->StringGridPins->Cells[col][row].Length();
        return max;
}



//=================
// sizes
//=================
void SetFormComponentsSizes(bool bSetDef)
{
if( !Form2 )
        return;
#define clearance                   2.0
#define FONT_SIZE                   9
#define MIN_REF_DES_BUTTON_H        22
//#define K_REF_DES                   8.5
//#define K_PINS                      15.0
//#define K_GLUEDS                    30.0
//#define K_C_N_LIST                  6.3
//#define K_PIN                       10.0
//#define K_NET                       7.8
//#define K_CNT                       20.0
int ClientHeight = MAX(Form1->ClientHeight,MIN_FORM_H);
int ClientWidth = MAX(Form1->ClientWidth,MIN_FORM_W);
Form1->PageControl1->Height = ClientHeight - clearance;
Form1->StringGridParts->Height = Form1->Parts->ClientHeight - clearance - 2*MIN_REF_DES_BUTTON_H;
Form1->StringGridPins->Height  = Form1->Pins->ClientHeight - clearance - 2*MIN_REF_DES_BUTTON_H;
Form1->PageControl1->Width = ClientWidth - clearance;
Form1->StringGridParts->Width = Form1->Parts->ClientWidth - clearance;
Form1->StringGridPins->Width  = Form1->Pins->ClientWidth - clearance;
ClientWidth = Form1->Parts->ClientWidth - MAX(Form1->R->Width,Form1->n_el1->Width) - 5;
  //
for( int icol=0; icol<PartsColCount; icol++ )
        Grid1ColWidth[icol] = PartsColLen(icol);
for( int icol=0; icol<PinsColCount; icol++ )
        Grid2ColWidth[icol] = PinsColLen(icol);
// ******** PARTS
int SummW;
double correct = 1.0;
for( int repeat=0; repeat<2; repeat++ )
        {
        if(repeat)
                {
                correct = ((double)ClientWidth)/(double)SummW;   
                SummW = 3;
                }
        else    SummW = 0;
        //
        int mem_col = 0;
        for( int col=0; col<PartsColCount; col++ )
                {
                if( col == def_RefDes )
                if( Form2->check_refs->Checked )
                        {
                        mem_col = col;
                        if(repeat)
                                {
                                Form1->BRefDes->Left = SummW;
                                Form1->CRefDes->Left = SummW;
                                Form1->BRefDes->Width = Grid1ColWidth[def_RefDes]*correct - clearance;
                                Form1->CRefDes->Width = Grid1ColWidth[def_RefDes]*correct - clearance;
                                }
                        SummW += Grid1ColWidth[def_RefDes]*correct;
                        if(repeat)
                                Form1->StringGridParts->ColWidths[def_RefDes] = Grid1ColWidth[def_RefDes]*correct - Form1->StringGridParts->GridLineWidth - 1;
                        Form1->BRefDes->Visible = true;
                        Form1->CRefDes->Visible = true;
                        }
                else    {
                        Form1->StringGridParts->ColWidths[def_RefDes] = 0;
                        Form1->BRefDes->Visible = false;
                        Form1->CRefDes->Visible = false;
                        }
                        //
                //
                if( col == def_RIRange )
                if( Form2->check_ref_index->Checked )
                        {
                        mem_col = col;
                        if(repeat)
                                {
                                Form1->BRIRange->Left = SummW;
                                Form1->MinRI->Left = SummW;
                                Form1->BRIRange->Width = Grid1ColWidth[def_RIRange]*correct - clearance;
                                Form1->MinRI->Width = Grid1ColWidth[def_RIRange]/2.0*correct - clearance;
                                Form1->MaxRI->Left = SummW + Form1->MinRI->Width + clearance;
                                Form1->MaxRI->Width = Form1->MinRI->Width;
                                }
                        SummW += Grid1ColWidth[def_RIRange]*correct;
                        if(repeat)
                                Form1->StringGridParts->ColWidths[def_RIRange] = Grid1ColWidth[def_RIRange]*correct - Form1->StringGridParts->GridLineWidth - 1;
                        Form1->BRIRange->Visible = true;
                        Form1->MinRI->Visible = true;
                        Form1->MaxRI->Visible = true;
                        }
                else    {
                        Form1->StringGridParts->ColWidths[def_RIRange] = 0;
                        Form1->BRIRange->Visible = false;
                        Form1->MinRI->Visible = false;
                        Form1->MaxRI->Visible = false;
                        }
                        //
                //
                if( col == def_Value )
                if( Form2->check_values->Checked )
                        {
                        mem_col = col;
                        if(repeat)
                                {
                                Form1->BValue->Left = SummW;
                                Form1->CValue->Left = SummW;
                                Form1->BValue->Width = Grid1ColWidth[def_Value]*correct - clearance;
                                Form1->CValue->Width = Grid1ColWidth[def_Value]*correct - clearance;
                                }
                        SummW += Grid1ColWidth[def_Value]*correct;
                        if(repeat)
                                Form1->StringGridParts->ColWidths[def_Value] = Grid1ColWidth[def_Value]*correct - Form1->StringGridParts->GridLineWidth;
                        Form1->BValue->Visible = true;
                        Form1->CValue->Visible = true;
                        }
                else    {
                        Form1->StringGridParts->ColWidths[def_Value] = 0;
                        Form1->BValue->Visible = false;
                        Form1->CValue->Visible = false;
                        }
                        //
                //
                if( col == def_ValueNL )
                if( Form2->check_valuesNL->Checked )
                        {
                        mem_col = col;
                        if(repeat)
                                {
                                Form1->BValueNL->Left = SummW;
                                Form1->CValueNL->Left = SummW;
                                Form1->BValueNL->Width = Grid1ColWidth[def_ValueNL]*correct - clearance;
                                Form1->CValueNL->Width = Grid1ColWidth[def_ValueNL]*correct - clearance;
                                }
                        SummW += Grid1ColWidth[def_ValueNL]*correct;
                        if(repeat)
                                Form1->StringGridParts->ColWidths[def_ValueNL] = Grid1ColWidth[def_ValueNL]*correct - Form1->StringGridParts->GridLineWidth;
                        Form1->BValueNL->Visible = true;
                        Form1->CValueNL->Visible = true;
                        }
                else    {
                        Form1->StringGridParts->ColWidths[def_ValueNL] = 0;
                        Form1->BValueNL->Visible = false;
                        Form1->CValueNL->Visible = false;
                        }
                        //
                //
                if( col == def_Package )
                if( Form2->check_package->Checked )
                        {
                        mem_col = col;
                        if(repeat)
                                {
                                Form1->BPackage->Left = SummW;
                                Form1->CPackage->Left = SummW;
                                Form1->BPackage->Width = Grid1ColWidth[def_Package]*correct - clearance;
                                Form1->CPackage->Width = Grid1ColWidth[def_Package]*correct - clearance;
                                }
                        SummW += Grid1ColWidth[def_Package]*correct;
                        if(repeat)
                                Form1->StringGridParts->ColWidths[def_Package] = Grid1ColWidth[def_Package]*correct - Form1->StringGridParts->GridLineWidth;
                        Form1->BPackage->Visible = true;
                        Form1->CPackage->Visible = true;
                        }
                else    {
                        Form1->StringGridParts->ColWidths[def_Package] = 0;
                        Form1->BPackage->Visible = false;
                        Form1->CPackage->Visible = false;
                        }
                        //
                //
                if( col == def_FootPrint )
                if( Form2->check_foot->Checked )
                        {
                        mem_col = col;
                        if(repeat)
                                {
                                Form1->BFootPrint->Left = SummW;
                                Form1->CFootPrint->Left = SummW;
                                Form1->BFootPrint->Width = Grid1ColWidth[def_FootPrint]*correct - clearance;
                                Form1->CFootPrint->Width = Grid1ColWidth[def_FootPrint]*correct - clearance;
                                }
                        SummW += Grid1ColWidth[def_FootPrint]*correct;
                        if(repeat)
                                Form1->StringGridParts->ColWidths[def_FootPrint] = Grid1ColWidth[def_FootPrint]*correct - Form1->StringGridParts->GridLineWidth;
                        Form1->BFootPrint->Visible = true;
                        Form1->CFootPrint->Visible = true;
                        }
                else    {
                        Form1->StringGridParts->ColWidths[def_FootPrint] = 0;
                        Form1->BFootPrint->Visible = false;
                        Form1->CFootPrint->Visible = false;
                        }
                        //
                //
                if( col == def_PackageNL )
                if( Form2->check_packageNL->Checked )
                        {
                        mem_col = col;
                        if(repeat)
                                {
                                Form1->BPackageNL->Left = SummW;
                                Form1->CPackageNL->Left = SummW;
                                Form1->BPackageNL->Width = Grid1ColWidth[def_PackageNL]*correct - clearance;
                                Form1->CPackageNL->Width = Grid1ColWidth[def_PackageNL]*correct - clearance;
                                }
                        SummW += Grid1ColWidth[def_PackageNL]*correct;
                        if(repeat)
                                Form1->StringGridParts->ColWidths[def_PackageNL] = Grid1ColWidth[def_PackageNL]*correct - Form1->StringGridParts->GridLineWidth;
                        Form1->BPackageNL->Visible = true;
                        Form1->CPackageNL->Visible = true;
                        }
                else    {
                        Form1->StringGridParts->ColWidths[def_PackageNL] = 0;
                        Form1->BPackageNL->Visible = false;
                        Form1->CPackageNL->Visible = false;
                        }
                        //
                //
                if( col == def_Merge )
                if( Form2->check_merge->Checked )
                        {
                        mem_col = col;
                        if(repeat)
                                {
                                Form1->BMerge->Left = SummW;
                                Form1->CMerge->Left = SummW;
                                Form1->BMerge->Width = Grid1ColWidth[def_Merge]*correct - clearance;
                                Form1->CMerge->Width = Grid1ColWidth[def_Merge]*correct - clearance;
                                }
                        SummW += Grid1ColWidth[def_Merge]*correct;
                        if(repeat)
                                Form1->StringGridParts->ColWidths[def_Merge] = Grid1ColWidth[def_Merge]*correct - Form1->StringGridParts->GridLineWidth;
                        Form1->BMerge->Visible = true;
                        Form1->CMerge->Visible = true;
                        }
                else    {
                        Form1->StringGridParts->ColWidths[def_Merge] = 0;
                        Form1->BMerge->Visible = false;
                        Form1->CMerge->Visible = false;
                        }
                        //
                //
                if( col == def_Pins )
                if( Form2->check_parts_pins->Checked )
                        {
                        mem_col = col;
                        if(repeat)
                                {
                                Form1->BPins->Left = SummW;
                                Form1->MinPin->Left = SummW;
                                Form1->BPins->Width = Grid1ColWidth[def_Pins]*correct - clearance;
                                Form1->MinPin->Width = Grid1ColWidth[def_Pins]/2.0*correct - clearance;
                                Form1->MaxPins->Left = SummW + Form1->MinPin->Width + clearance;
                                Form1->MaxPins->Width = Form1->MinPin->Width;
                                }
                        SummW += Grid1ColWidth[def_Pins]*correct;
                        if(repeat)
                                Form1->StringGridParts->ColWidths[def_Pins] = Grid1ColWidth[def_Pins]*correct - Form1->StringGridParts->GridLineWidth - 1;
                        Form1->BPins->Visible = true;
                        Form1->MinPin->Visible = true;
                        Form1->MaxPins->Visible = true;
                        }
                else    {
                        Form1->StringGridParts->ColWidths[def_Pins] = 0;
                        Form1->BPins->Visible = false;
                        Form1->MinPin->Visible = false;
                        Form1->MaxPins->Visible = false;
                        }
                        //
                //
                if( col == def_Holes )
                if( Form2->check_parts_holes->Checked )
                        {
                        mem_col = col;
                        if(repeat)
                                {
                                Form1->BHoles->Left = SummW;
                                Form1->MinHoles->Left = SummW;
                                Form1->BHoles->Width = Grid1ColWidth[def_Holes]*correct - clearance;
                                Form1->MinHoles->Width = Grid1ColWidth[def_Holes]/2.0*correct - clearance;
                                Form1->MaxHoles->Left = SummW + Form1->MinHoles->Width + clearance;
                                Form1->MaxHoles->Width = Form1->MinHoles->Width;
                                }
                        SummW += Grid1ColWidth[def_Holes]*correct;
                        if(repeat)
                                Form1->StringGridParts->ColWidths[def_Holes] = Grid1ColWidth[def_Holes]*correct - Form1->StringGridParts->GridLineWidth - 1;
                        Form1->BHoles->Visible = true;
                        Form1->MinHoles->Visible = true;
                        Form1->MaxHoles->Visible = true;
                        }
                else    {
                        Form1->StringGridParts->ColWidths[def_Holes] = 0;
                        Form1->BHoles->Visible = false;
                        Form1->MinHoles->Visible = false;
                        Form1->MaxHoles->Visible = false;
                        }
                        //
                //
                if( col == def_Gl )
                if( Form2->check_glueds->Checked )
                        {
                        mem_col = col;
                        if(repeat)
                                {
                                Form1->BGlueds->Left = SummW;
                                Form1->Glueds->Left = SummW;
                                Form1->BGlueds->Width = Grid1ColWidth[def_Gl]*correct - clearance;
                                Form1->Glueds->Width = Grid1ColWidth[def_Gl]*correct - clearance;
                                }
                        SummW += Grid1ColWidth[def_Gl]*correct;
                        if(repeat)
                                Form1->StringGridParts->ColWidths[def_Gl] = Grid1ColWidth[def_Gl]*correct - Form1->StringGridParts->GridLineWidth;
                        Form1->BGlueds->Visible = true;
                        Form1->Glueds->Visible = true;
                        }
                else    {
                        Form1->StringGridParts->ColWidths[def_Gl] = 0;
                        Form1->BGlueds->Visible = false;
                        Form1->Glueds->Visible = false;
                        }
                        //
                //
                if( col == def_S )
                if( Form2->check_sides->Checked )
                        {
                        mem_col = col;
                        if(repeat)
                                {
                                Form1->BSide->Left = SummW;
                                Form1->Side->Left = SummW;
                                Form1->BSide->Width = Grid1ColWidth[def_S]*correct - clearance;
                                Form1->Side->Width = Grid1ColWidth[def_S]*correct - clearance;
                                }
                        SummW += Grid1ColWidth[def_S]*correct;
                        if(repeat)
                                Form1->StringGridParts->ColWidths[def_S] = Grid1ColWidth[def_S]*correct - Form1->StringGridParts->GridLineWidth;
                        Form1->BSide->Visible = true;
                        Form1->Side->Visible = true;
                        }
                else    {
                        Form1->StringGridParts->ColWidths[def_S] = 0;
                        Form1->BSide->Visible = false;
                        Form1->Side->Visible = false;
                        }
                        //
                //
                if( col == def_Ang )
                if( Form2->check_angles->Checked )
                        {
                        mem_col = col;
                        if(repeat)
                                {
                                Form1->BAng->Left = SummW;
                                Form1->Ang->Left = SummW;
                                Form1->BAng->Width = Grid1ColWidth[def_Ang]*correct - clearance;
                                Form1->Ang->Width = Grid1ColWidth[def_Ang]*correct - clearance;
                                }
                        SummW += Grid1ColWidth[def_Ang]*correct;
                        if(repeat)
                                Form1->StringGridParts->ColWidths[def_Ang] = Grid1ColWidth[def_Ang]*correct - Form1->StringGridParts->GridLineWidth;
                        Form1->BAng->Visible = true;
                        Form1->Ang->Visible = true;
                        }
                else    {
                        Form1->StringGridParts->ColWidths[def_Ang] = 0;
                        Form1->BAng->Visible = false;
                        Form1->Ang->Visible = false;
                        }
                        //
                //
                if( col == def_Xprt )
                if( Form2->check_partx->Checked )
                        {
                        mem_col = col;
                        if(repeat)
                                {
                                Form1->BX->Left = SummW;
                                Form1->EXmin->Left = SummW;
                                Form1->BX->Width = Grid1ColWidth[def_Xprt]*correct - clearance;
                                Form1->EXmin->Width = Grid1ColWidth[def_Xprt]/2.0*correct - clearance;
                                Form1->EXmax->Left = SummW + Form1->EXmin->Width + clearance;
                                Form1->EXmax->Width = Form1->EXmin->Width;
                                }
                        SummW += Grid1ColWidth[def_Xprt]*correct;
                        if(repeat)
                                Form1->StringGridParts->ColWidths[def_Xprt] = Grid1ColWidth[def_Xprt]*correct - Form1->StringGridParts->GridLineWidth;
                        Form1->BX->Visible = true;
                        Form1->EXmin->Visible = true;
                        Form1->EXmax->Visible = true;
                        }
                else    {
                        Form1->StringGridParts->ColWidths[def_Xprt] = 0;
                        Form1->BX->Visible = false;
                        Form1->EXmin->Visible = false;
                        Form1->EXmax->Visible = false;
                        }
                        //
                //
                if( col == def_Yprt )
                if( Form2->check_party->Checked )
                        {
                        mem_col = col;
                        if(repeat)
                                {
                                Form1->BY->Left = SummW;
                                Form1->EYmin->Left = SummW;
                                Form1->BY->Width = Grid1ColWidth[def_Yprt]*correct - clearance;
                                Form1->EYmin->Width = Grid1ColWidth[def_Yprt]/2.0*correct - clearance;
                                Form1->EYmax->Left = SummW + Form1->EYmin->Width + clearance;
                                Form1->EYmax->Width = Form1->EYmin->Width;
                                }
                        SummW += Grid1ColWidth[def_Yprt]*correct;
                        if(repeat)
                                Form1->StringGridParts->ColWidths[def_Yprt] = Grid1ColWidth[def_Yprt]*correct - Form1->StringGridParts->GridLineWidth;
                        Form1->BY->Visible = true;
                        Form1->EYmin->Visible = true;
                        Form1->EYmax->Visible = true;
                        }
                else    {
                        Form1->StringGridParts->ColWidths[def_Yprt] = 0;
                        Form1->BY->Visible = false;
                        Form1->EYmin->Visible = false;
                        Form1->EYmax->Visible = false;
                        }
                        //
                //
                if( col == def_CompareNetlist )
                if( Form2->check_comp_nlist->Checked )
                        {
                        mem_col = col;
                        if(repeat)
                                {
                                Form1->BCNetlist->Left = SummW;
                                Form1->CCNetlist->Left = SummW;
                                Form1->BCNetlist->Width = Grid1ColWidth[def_CompareNetlist]*correct - clearance;
                                Form1->CCNetlist->Width = Grid1ColWidth[def_CompareNetlist]*correct - clearance;
                                }
                        SummW += Grid1ColWidth[def_CompareNetlist]*correct;
                        if(repeat)
                                Form1->StringGridParts->ColWidths[def_CompareNetlist] = Grid1ColWidth[def_CompareNetlist]*correct - Form1->StringGridParts->GridLineWidth;
                        Form1->BCNetlist->Visible = true;
                        Form1->CCNetlist->Visible = true;
                        }
                else    {
                        Form1->StringGridParts->ColWidths[def_CompareNetlist] = 0;
                        Form1->BCNetlist->Visible = false;
                        Form1->CCNetlist->Visible = false;
                        }
                }
        }
// ******** PINS
ClientWidth = Form1->Pins->ClientWidth - MAX(Form1->R2->Width,Form1->n_el2->Width) - 5;
correct = 1.0;
for( int repeat=0; repeat<2; repeat++ )
        {
        if(repeat)
                {
                correct = (double)ClientWidth/(double)SummW;
                SummW = 3;
                }
        else    SummW = 0;
        if(repeat)
                {
                Form1->BPin->Left = SummW;
                Form1->CPin->Left = SummW;
                Form1->BPin->Width = Grid2ColWidth[def_Pin]*correct - clearance;
                Form1->CPin->Width = Grid2ColWidth[def_Pin]*correct - clearance;
                }
        if(Form2->check_pinname->Checked)
                {
                SummW += Grid2ColWidth[def_Pin]*correct;
                if(repeat)
                        Form1->StringGridPins->ColWidths[def_Pin] = Grid2ColWidth[def_Pin]*correct - Form1->StringGridPins->GridLineWidth;
                Form1->BPin->Visible = true;
                Form1->CPin->Visible = true;
                }
        else    {
                Form1->StringGridPins->ColWidths[def_Pin] = 0;
                Form1->BPin->Visible = false;
                Form1->CPin->Visible = false;
                }
        if(repeat)
                {
                Form1->BPinNetPCB->Left = SummW;
                Form1->CPinNetPCB->Left = SummW;
                Form1->BPinNetPCB->Width = Grid2ColWidth[def_NetPcb]*correct - clearance;
                Form1->CPinNetPCB->Width = Grid2ColWidth[def_NetPcb]*correct - clearance;
                }
        if(Form2->check_netpcb->Checked)
                {
                SummW += Grid2ColWidth[def_NetPcb]*correct;
                if(repeat)
                        Form1->StringGridPins->ColWidths[def_NetPcb] = Grid2ColWidth[def_NetPcb]*correct - Form1->StringGridPins->GridLineWidth;
                Form1->BPinNetPCB->Visible = true;
                Form1->CPinNetPCB->Visible = true;
                }
        else    {
                Form1->StringGridPins->ColWidths[def_NetPcb] = 0;
                Form1->BPinNetPCB->Visible = false;
                Form1->CPinNetPCB->Visible = false;
                }
        if(repeat)
                {
                Form1->BCnt->Left = SummW;
                Form1->CCnt->Left = SummW;
                Form1->BCnt->Width = Grid2ColWidth[def_Cnt]*correct - clearance;
                Form1->CCnt->Width = Grid2ColWidth[def_Cnt]*correct - clearance;
                }
        if(Form2->check_pins_cnt->Checked)
                {
                SummW += Grid2ColWidth[def_Cnt]*correct;
                if(repeat)
                        Form1->StringGridPins->ColWidths[def_Cnt] = Grid2ColWidth[def_Cnt]*correct - Form1->StringGridPins->GridLineWidth;
                Form1->BCnt->Visible = true;
                Form1->CCnt->Visible = true;
                }
        else    {
                Form1->StringGridPins->ColWidths[def_Cnt] = 0;
                Form1->BCnt->Visible = false;
                Form1->CCnt->Visible = false;
                }
        if(repeat)
                {
                Form1->BPinNetList->Left = SummW;
                Form1->CNetNetlist->Left = SummW;
                Form1->BPinNetList->Width = Grid2ColWidth[def_Netlist]*correct - clearance;
                Form1->CNetNetlist->Width = Grid2ColWidth[def_Netlist]*correct - clearance;
                }
        if(Form2->check_ext_netlist->Checked)
                {
                SummW += Grid2ColWidth[def_Netlist]*correct;
                if(repeat)
                        Form1->StringGridPins->ColWidths[def_Netlist] = Grid2ColWidth[def_Netlist]*correct - Form1->StringGridPins->GridLineWidth;
                Form1->BPinNetList->Visible = true;
                Form1->CNetNetlist->Visible = true;
                }
        else    {
                Form1->StringGridPins->ColWidths[def_Netlist] = 0;
                Form1->BPinNetList->Visible = false;
                Form1->CNetNetlist->Visible = false;
                }
        if(repeat)
                {
                Form1->BType->Left = SummW;
                Form1->CType->Left = SummW;
                Form1->BType->Width = Grid2ColWidth[def_Type]*correct - clearance;
                Form1->CType->Width = Grid2ColWidth[def_Type]*correct - clearance;
                }
        if(Form2->check_pins_type->Checked)
                {
                SummW += Grid2ColWidth[def_Type]*correct;
                if(repeat)
                        Form1->StringGridPins->ColWidths[def_Type] = Grid2ColWidth[def_Type]*correct - Form1->StringGridPins->GridLineWidth;
                Form1->BType->Visible = true;
                Form1->CType->Visible = true;
                }
        else    {
                Form1->StringGridPins->ColWidths[def_Type] = 0;
                Form1->BType->Visible = false;
                Form1->CType->Visible = false;
                }
        if(repeat)
                {
                Form1->BW->Left = SummW;
                Form1->WPinMin->Left = SummW;
                Form1->BW->Width = Grid2ColWidth[def_W]*correct - clearance;
                Form1->WPinMin->Width = Grid2ColWidth[def_W]/2.0*correct - clearance;
                Form1->WPinMax->Left = SummW + Form1->WPinMin->Width + clearance;
                Form1->WPinMax->Width = Form1->WPinMin->Width;
                }
        if(Form2->check_pins_w->Checked)
                {
                SummW += Grid2ColWidth[def_W]*correct;
                if(repeat)
                        Form1->StringGridPins->ColWidths[def_W] = Grid2ColWidth[def_W]*correct - Form1->StringGridPins->GridLineWidth;
                Form1->BW->Visible = true;
                Form1->WPinMin->Visible = true;
                Form1->WPinMax->Visible = true;
                }
        else    {
                Form1->StringGridPins->ColWidths[def_W] =0;
                Form1->BW->Visible = false;
                Form1->WPinMin->Visible = false;
                Form1->WPinMax->Visible = false;
                }
        if(repeat)
                {
                Form1->BL->Left = SummW;
                Form1->LPinMin->Left = SummW;
                Form1->BL->Width = Grid2ColWidth[def_L]*correct - clearance;
                Form1->LPinMin->Width = Grid2ColWidth[def_L]/2.0*correct - clearance;
                Form1->LPinMax->Left = SummW + Form1->LPinMin->Width + clearance;
                Form1->LPinMax->Width = Form1->LPinMin->Width;
                }
        if(Form2->check_pins_l->Checked)
                {
                SummW += Grid2ColWidth[def_L]*correct;
                if(repeat)
                        Form1->StringGridPins->ColWidths[def_L] = Grid2ColWidth[def_L]*correct - Form1->StringGridPins->GridLineWidth;
                Form1->BL->Visible = true;
                Form1->LPinMin->Visible = true;
                Form1->LPinMax->Visible = true;
                }
        else    {
                Form1->StringGridPins->ColWidths[def_L] = 0;
                Form1->BL->Visible = false;
                Form1->LPinMin->Visible = false;
                Form1->LPinMax->Visible = false;
                }
        if(repeat)
                {
                Form1->BTrml->Left = SummW;
                Form1->CTrml->Left = SummW;
                Form1->BTrml->Width = Grid2ColWidth[def_Thrml]*correct - clearance;
                Form1->CTrml->Width = Grid2ColWidth[def_Thrml]*correct - clearance;
                }
        if(Form2->check_thrml->Checked)
                {
                SummW += Grid2ColWidth[def_Thrml]*correct;
                if(repeat)
                        Form1->StringGridPins->ColWidths[def_Thrml] = Grid2ColWidth[def_Thrml]*correct - Form1->StringGridPins->GridLineWidth;
                Form1->BTrml->Visible = true;
                Form1->CTrml->Visible = true;
                }
        else    {
                Form1->StringGridPins->ColWidths[def_Thrml] = 0;
                Form1->BTrml->Visible = false;
                Form1->CTrml->Visible = false;
                }
        if(repeat)
                {
                Form1->BDHole->Left = SummW;
                Form1->DHoleMin->Left = SummW;
                Form1->BDHole->Width = Grid2ColWidth[def_DHole]*correct - clearance;
                Form1->DHoleMin->Width = Grid2ColWidth[def_DHole]/2.0*correct - clearance;
                Form1->DHoleMax->Left = SummW + Form1->DHoleMin->Width + clearance;
                Form1->DHoleMax->Width = Form1->DHoleMin->Width;
                }
        if(Form2->check_holes_diam->Checked)
                {
                SummW += Grid2ColWidth[def_DHole]*correct;
                if(repeat)
                        Form1->StringGridPins->ColWidths[def_DHole] = Grid2ColWidth[def_DHole]*correct - Form1->StringGridPins->GridLineWidth;
                Form1->BDHole->Visible = true;
                Form1->DHoleMin->Visible = true;
                Form1->DHoleMax->Visible = true;
                }
        else    {
                Form1->StringGridPins->ColWidths[def_DHole] = 0;
                Form1->BDHole->Visible = false;
                Form1->DHoleMin->Visible = false;
                Form1->DHoleMax->Visible = false;
                }
        if(repeat)
                {
                Form1->BPas->Left = SummW;
                Form1->Pas->Left = SummW;
                Form1->BPas->Width = Grid2ColWidth[def_Pas]*correct - clearance;
                Form1->Pas->Width = Grid2ColWidth[def_Pas]*correct - clearance;
                }
        if(Form2->check_paste->Checked)
                {
                SummW += Grid2ColWidth[def_Pas]*correct;
                if(repeat)
                        Form1->StringGridPins->ColWidths[def_Pas] = Grid2ColWidth[def_Pas]*correct - Form1->StringGridPins->GridLineWidth;
                Form1->BPas->Visible = true;
                Form1->Pas->Visible = true;
                }
        else    {
                Form1->StringGridPins->ColWidths[def_Pas] = 0;
                Form1->BPas->Visible = false;
                Form1->Pas->Visible = false;
                }
        if(repeat)
                {
                Form1->BXPin->Left = SummW;
                Form1->XPinMin->Left = SummW;
                Form1->BXPin->Width = Grid2ColWidth[def_Xpi]*correct - clearance;
                Form1->XPinMin->Width = Grid2ColWidth[def_Xpi]/2.0*correct - clearance;
                Form1->XPinMax->Left = SummW + Form1->XPinMin->Width + clearance;
                Form1->XPinMax->Width = Form1->XPinMin->Width;
                }
        if(Form2->check_pinsx->Checked)
                {
                SummW += Grid2ColWidth[def_Xpi]*correct;
                if(repeat)
                        Form1->StringGridPins->ColWidths[def_Xpi] = Grid2ColWidth[def_Xpi]*correct - Form1->StringGridPins->GridLineWidth;
                Form1->BXPin->Visible = true;
                Form1->XPinMin->Visible = true;
                Form1->XPinMax->Visible = true;
                }
        else    {
                Form1->StringGridPins->ColWidths[def_Xpi] = 0;
                Form1->BXPin->Visible = false;
                Form1->XPinMin->Visible = false;
                Form1->XPinMax->Visible = false;
                }
        if(repeat)
                {
                Form1->BYPin->Left = SummW;
                Form1->YPinMin->Left = SummW;
                Form1->BYPin->Width = Grid2ColWidth[def_Ypi]*correct - clearance;
                Form1->YPinMin->Width = Grid2ColWidth[def_Ypi]/2.0*correct - clearance;
                Form1->YPinMax->Left = SummW + Form1->YPinMin->Width + clearance;
                Form1->YPinMax->Width = Form1->YPinMin->Width;
                }
        if(Form2->check_pinsy->Checked)
                {
                SummW += Grid2ColWidth[def_Ypi]*correct;
                if(repeat)
                        Form1->StringGridPins->ColWidths[def_Ypi] = Grid2ColWidth[def_Ypi]*correct - Form1->StringGridPins->GridLineWidth;
                Form1->BYPin->Visible = true;
                Form1->YPinMin->Visible = true;
                Form1->YPinMax->Visible = true;
                }
        else    {
                Form1->StringGridPins->ColWidths[def_Ypi] = 0;
                Form1->BYPin->Visible = false;
                Form1->YPinMin->Visible = false;
                Form1->YPinMax->Visible = false;
                }
        }
//
if ( bSetDef )
        {
        Form1->PageControl1->Left = 1;
        Form1->PageControl1->Top = 0;
        Form1->StringGridParts->Left = 1;
        Form1->StringGridParts->Top = 2*MIN_REF_DES_BUTTON_H + clearance;
        Form1->StringGridPins->Left = 1;
        Form1->StringGridPins->Top = 2*MIN_REF_DES_BUTTON_H + clearance;
        Form1->ProgressBar1->Top = 0;
        Form1->ProgressBar1->Left = 1;
        // ================== PARTS
        // button position
        Form1->BRefDes->Top = 0;
        Form1->BRIRange->Top = 0;
        Form1->BValue->Top = 0;
        Form1->BValueNL->Top = 0;
        Form1->BPackage->Top = 0;
        Form1->BPackageNL->Top = 0;
        Form1->BFootPrint->Top = 0;
        Form1->BMerge->Top = 0;
        Form1->BPins->Top = 0;
        Form1->BHoles->Top = 0;
        Form1->BGlueds->Top = 0;
        Form1->BSide->Top = 0;
        Form1->BAng->Top = 0;
        Form1->BX->Top = 0;
        Form1->BY->Top = 0;
        Form1->BCNetlist->Top = 0;
        // button height
        Form1->BRefDes->Height = MIN_REF_DES_BUTTON_H;
        Form1->BRIRange->Height = MIN_REF_DES_BUTTON_H;
        Form1->BValue->Height = MIN_REF_DES_BUTTON_H;
        Form1->BValueNL->Height = MIN_REF_DES_BUTTON_H;
        Form1->BPackage->Height = MIN_REF_DES_BUTTON_H;
        Form1->BPackageNL->Height = MIN_REF_DES_BUTTON_H;
        Form1->BFootPrint->Height = MIN_REF_DES_BUTTON_H;
        Form1->BMerge->Height = MIN_REF_DES_BUTTON_H;
        Form1->BPins->Height =  MIN_REF_DES_BUTTON_H;
        Form1->BHoles->Height = MIN_REF_DES_BUTTON_H;
        Form1->BGlueds->Height = MIN_REF_DES_BUTTON_H;
        Form1->BSide->Height =  MIN_REF_DES_BUTTON_H;
        Form1->BAng->Height =   MIN_REF_DES_BUTTON_H;
        Form1->BX->Height =     MIN_REF_DES_BUTTON_H;
        Form1->BY->Height =     MIN_REF_DES_BUTTON_H;
        Form1->BCNetlist->Height = MIN_REF_DES_BUTTON_H;
        // cBox position
        Form1->CRefDes->Top =   MIN_REF_DES_BUTTON_H;
        Form1->MinRI->Top =     MIN_REF_DES_BUTTON_H;
        Form1->MaxRI->Top =     MIN_REF_DES_BUTTON_H;
        Form1->CValue->Top =    MIN_REF_DES_BUTTON_H;
        Form1->CValueNL->Top =  MIN_REF_DES_BUTTON_H;
        Form1->CPackage->Top =  MIN_REF_DES_BUTTON_H;
        Form1->CPackageNL->Top =MIN_REF_DES_BUTTON_H;
        Form1->CFootPrint->Top =MIN_REF_DES_BUTTON_H;
        Form1->CMerge->Top =    MIN_REF_DES_BUTTON_H;
        Form1->MinPin->Top =    MIN_REF_DES_BUTTON_H;
        Form1->MaxPins->Top =   MIN_REF_DES_BUTTON_H;
        Form1->MinHoles->Top =  MIN_REF_DES_BUTTON_H;
        Form1->MaxHoles->Top =  MIN_REF_DES_BUTTON_H;
        Form1->Glueds->Top =    MIN_REF_DES_BUTTON_H;
        Form1->Side->Top =      MIN_REF_DES_BUTTON_H;
        Form1->Ang->Top =       MIN_REF_DES_BUTTON_H;
        Form1->EXmin->Top =     MIN_REF_DES_BUTTON_H;
        Form1->EXmax->Top =     MIN_REF_DES_BUTTON_H;
        Form1->EYmin->Top =     MIN_REF_DES_BUTTON_H;
        Form1->EYmax->Top =     MIN_REF_DES_BUTTON_H;
        Form1->CCNetlist->Top = MIN_REF_DES_BUTTON_H;
        // cBox height
        Form1->CRefDes->Height =   MIN_REF_DES_BUTTON_H;
        Form1->MinRI->Height =     MIN_REF_DES_BUTTON_H;
        Form1->MaxRI->Height =     MIN_REF_DES_BUTTON_H;
        Form1->CValue->Height =    MIN_REF_DES_BUTTON_H;
        Form1->CPackage->Height =  MIN_REF_DES_BUTTON_H;
        Form1->CMerge->Height =    MIN_REF_DES_BUTTON_H;
        Form1->MinPin->Height =    MIN_REF_DES_BUTTON_H;
        Form1->MaxPins->Height =   MIN_REF_DES_BUTTON_H;
        Form1->MinHoles->Height =  MIN_REF_DES_BUTTON_H;
        Form1->MaxHoles->Height =  MIN_REF_DES_BUTTON_H;
        Form1->Glueds->Height =    MIN_REF_DES_BUTTON_H;
        Form1->Side->Height =      MIN_REF_DES_BUTTON_H;
        Form1->Ang->Height =       MIN_REF_DES_BUTTON_H;
        Form1->EXmin->Height =     MIN_REF_DES_BUTTON_H;
        Form1->EXmax->Height =     MIN_REF_DES_BUTTON_H;
        Form1->EYmin->Height =     MIN_REF_DES_BUTTON_H;
        Form1->EYmax->Height =     MIN_REF_DES_BUTTON_H;
        Form1->CCNetlist->Height = MIN_REF_DES_BUTTON_H;
        // cBox font
        Form1->CRefDes->Font->Size =    FONT_SIZE;
        Form1->MinRI->Font->Size =      FONT_SIZE;
        Form1->MaxRI->Font->Size =      FONT_SIZE;
        Form1->CValue->Font->Size =     FONT_SIZE;
        Form1->CValueNL->Font->Size =   FONT_SIZE;
        Form1->CPackage->Font->Size =   FONT_SIZE;
        Form1->CPackageNL->Font->Size = FONT_SIZE;
        Form1->CFootPrint->Font->Size = FONT_SIZE;
        Form1->CMerge->Font->Size =    FONT_SIZE;
        Form1->MinPin->Font->Size =    FONT_SIZE;
        Form1->MaxPins->Font->Size =   FONT_SIZE;
        Form1->MinHoles->Font->Size =  FONT_SIZE;
        Form1->MaxHoles->Font->Size =  FONT_SIZE;
        Form1->Glueds->Font->Size =    FONT_SIZE;
        Form1->Side->Font->Size =      FONT_SIZE;
        Form1->Ang->Font->Size =       FONT_SIZE;
        Form1->EXmin->Font->Size =     FONT_SIZE;
        Form1->EXmax->Font->Size =     FONT_SIZE;
        Form1->EYmin->Font->Size =     FONT_SIZE;
        Form1->EYmax->Font->Size =     FONT_SIZE;
        Form1->CCNetlist->Font->Size = FONT_SIZE;
        // ================== PINS
        // button position
        Form1->BPin->Top = 0;
        Form1->BPinNetPCB->Top = 0;
        Form1->BPinNetList->Top = 0;
        Form1->BCnt->Top = 0;
        Form1->BType->Top = 0;
        Form1->BW->Top = 0;
        Form1->BL->Top = 0;
        Form1->BTrml->Top = 0;
        Form1->BDHole->Top = 0;
        Form1->BPas->Top = 0;
        Form1->BXPin->Top = 0;
        Form1->BYPin->Top = 0;
        // button height
        Form1->BPin->Height =   MIN_REF_DES_BUTTON_H;
        Form1->BPinNetPCB->Height = MIN_REF_DES_BUTTON_H;
        Form1->BPinNetList->Height = MIN_REF_DES_BUTTON_H;
        Form1->BCnt->Height =   MIN_REF_DES_BUTTON_H;
        Form1->BType->Height =  MIN_REF_DES_BUTTON_H;
        Form1->BW->Height =     MIN_REF_DES_BUTTON_H;
        Form1->BL->Height =     MIN_REF_DES_BUTTON_H;
        Form1->BTrml->Height =  MIN_REF_DES_BUTTON_H;
        Form1->BDHole->Height = MIN_REF_DES_BUTTON_H;
        Form1->BPas->Height =   MIN_REF_DES_BUTTON_H;
        Form1->BXPin->Height =  MIN_REF_DES_BUTTON_H;
        Form1->BYPin->Height =  MIN_REF_DES_BUTTON_H;
        // cBox position
        Form1->CPin->Top =        MIN_REF_DES_BUTTON_H;
        Form1->CPinNetPCB->Top =  MIN_REF_DES_BUTTON_H;
        Form1->CNetNetlist->Top = MIN_REF_DES_BUTTON_H;
        Form1->CCnt->Top =        MIN_REF_DES_BUTTON_H;
        Form1->CType->Top =       MIN_REF_DES_BUTTON_H;
        Form1->WPinMin->Top =     MIN_REF_DES_BUTTON_H;
        Form1->LPinMin->Top =     MIN_REF_DES_BUTTON_H;
        Form1->WPinMax->Top =     MIN_REF_DES_BUTTON_H;
        Form1->LPinMax->Top =     MIN_REF_DES_BUTTON_H;
        Form1->CTrml->Top =       MIN_REF_DES_BUTTON_H;
        Form1->DHoleMin->Top =    MIN_REF_DES_BUTTON_H;
        Form1->DHoleMax->Top =    MIN_REF_DES_BUTTON_H;
        Form1->Pas->Top =         MIN_REF_DES_BUTTON_H;
        Form1->XPinMin->Top =     MIN_REF_DES_BUTTON_H;
        Form1->YPinMin->Top =     MIN_REF_DES_BUTTON_H;
        Form1->XPinMax->Top =     MIN_REF_DES_BUTTON_H;
        Form1->YPinMax->Top =     MIN_REF_DES_BUTTON_H;
        // cBox height
        Form1->CPin->Height =        MIN_REF_DES_BUTTON_H;
        Form1->CPinNetPCB->Height =  MIN_REF_DES_BUTTON_H;
        Form1->CNetNetlist->Height = MIN_REF_DES_BUTTON_H;
        Form1->CCnt->Height =        MIN_REF_DES_BUTTON_H;
        Form1->CType->Height =       MIN_REF_DES_BUTTON_H;
        Form1->WPinMin->Height =     MIN_REF_DES_BUTTON_H;
        Form1->LPinMin->Height =     MIN_REF_DES_BUTTON_H;
        Form1->WPinMax->Height =     MIN_REF_DES_BUTTON_H;
        Form1->LPinMax->Height =     MIN_REF_DES_BUTTON_H;
        Form1->CTrml->Height =       MIN_REF_DES_BUTTON_H;
        Form1->DHoleMin->Height =    MIN_REF_DES_BUTTON_H;
        Form1->DHoleMax->Height =    MIN_REF_DES_BUTTON_H;
        Form1->Pas->Height =         MIN_REF_DES_BUTTON_H;
        Form1->XPinMin->Height =     MIN_REF_DES_BUTTON_H;
        Form1->YPinMin->Height =     MIN_REF_DES_BUTTON_H;
        Form1->XPinMax->Height =     MIN_REF_DES_BUTTON_H;
        Form1->YPinMax->Height =     MIN_REF_DES_BUTTON_H;
        // cBox font
        Form1->CPin->Font->Size =        FONT_SIZE;
        Form1->CPinNetPCB->Font->Size =  FONT_SIZE;
        Form1->CNetNetlist->Font->Size = FONT_SIZE;
        Form1->CCnt->Font->Size =        FONT_SIZE;
        Form1->CType->Font->Size =       FONT_SIZE;
        Form1->WPinMin->Font->Size =     FONT_SIZE;
        Form1->LPinMin->Font->Size =     FONT_SIZE;
        Form1->WPinMax->Font->Size =     FONT_SIZE;
        Form1->LPinMax->Font->Size =     FONT_SIZE;
        Form1->CTrml->Font->Size =       FONT_SIZE;
        Form1->DHoleMin->Font->Size =    FONT_SIZE;
        Form1->DHoleMax->Font->Size =    FONT_SIZE;
        Form1->Pas->Font->Size =         FONT_SIZE;
        Form1->XPinMin->Font->Size =     FONT_SIZE;
        Form1->YPinMin->Font->Size =     FONT_SIZE;
        Form1->XPinMax->Font->Size =     FONT_SIZE;
        Form1->YPinMax->Font->Size =     FONT_SIZE;
        }
Form1->ProgressBar1->Top = 0;
Form1->ProgressBar1->Left = 0;
Form1->ProgressBar1->Width = Form1->ClientWidth;
Form1->R->Left = Form1->Parts->ClientWidth - Form1->R->Width;
Form1->R->Top = Form1->Parts->Top - 7;
Form1->R2->Left = Form1->Pins->ClientWidth - Form1->R2->Width;
Form1->R2->Top = Form1->Pins->Top - 7;
Form1->n_el1->Left = Form1->Parts->ClientWidth - Form1->n_el1->Width - 5;
Form1->n_el1->Top = Form1->R->Height - 3;
Form1->n_el2->Left = Form1->Pins->ClientWidth - Form1->n_el2->Width - 5;
Form1->n_el2->Top = Form1->R->Height - 3;
}



//=================
// defaults
//=================
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
DecimalSeparator = ',';
Form1->Visible = false;
n_copper_layers = 2;
i = 0;
k = 0;
n = 0;
m = 0;
Pause = 30;
BRDRect[0] = 0;
BRDRect[1] = 0;
BRDRect[2] = 0;
BRDRect[3] = 0;
CountStringsFile = 0;
LONGDEFAULT = 2000000000;
SortedCase = 0;
UNITS = 1;
Form1->Left = 0;
Form1->Width = MIN_FORM_W;
Form1->Timer1->Enabled = false;
PathProg = ExtractFilePath(Application->ExeName);
PathProg = PathProg.SubString(1,(PathProg.Length()-1));
PathProg = ExtractFilePath(PathProg);
Form1->ProgressBar1->Top = 5;
Form1->ProgressBar1->Visible = false;
Form1->BorderStyle = bsSizeable;
Form1->FormStyle = fsStayOnTop;
Form1->Top = 0;
Form1->ClientHeight = 0;
Form1->PageControl1->Height = 85;
Form1->Bufer->Sorted =          false;
Form1->DataParts->Sorted =      false;
Form1->DataPins ->Sorted =      false;
Form1->Deleted->Sorted =        true;
Form1->SortedBox->Sorted =      true;
Form1->DHoleMin->Sorted =       true;
Form1->DHoleMax->Sorted =       true;
Form1->CPinNetPCB->Sorted =     true;
Form1->CCnt->Sorted =           true;
Form1->Bufer->Visible =         false;
Form1->Deleted->Visible =       false;
Form1->DataParts->Visible =     false;
Form1->DataPins ->Visible =     false;
Form1->SortedBox->Visible =     false;
Form1->Values->Sorted =         false;
Form1->Values->Visible =        false;
Form1->CMerge->Sorted =         false;
//     StringGridParts
Form1->StringGridParts->ColCount = PartsColCount;
Form1->StringGridParts->GridLineWidth = 0;
//     StringGridPins
Form1->StringGridPins->ColCount = PinsColCount;
Form1->StringGridPins->GridLineWidth = 0;
//
// fonts
BRIRange->Font = BRefDes->Font;
BValue->Font = BRefDes->Font;
BValueNL->Font = BRefDes->Font;
BPackage->Font = BRefDes->Font;
BPackageNL->Font = BRefDes->Font;
BFootPrint->Font = BRefDes->Font;
BMerge->Font = BRefDes->Font;
BPins->Font = BRefDes->Font;
BHoles->Font = BRefDes->Font;
BGlueds->Font = BRefDes->Font;
BSide->Font = BRefDes->Font;
BAng->Font = BRefDes->Font;
BX->Font = BRefDes->Font;
BY->Font = BRefDes->Font;
BCNetlist->Font = BRefDes->Font;
BPin->Font = BRefDes->Font;
BPinNetPCB->Font = BRefDes->Font;
BCnt->Font = BRefDes->Font;
BPinNetList->Font = BRefDes->Font;
BType->Font = BRefDes->Font;
BW->Font = BRefDes->Font;
BL->Font = BRefDes->Font;
BTrml->Font = BRefDes->Font;
BDHole->Font = BRefDes->Font;
BPas->Font = BRefDes->Font;
BXPin->Font = BRefDes->Font;
BYPin->Font = BRefDes->Font;
StringGridPins->Font = BRefDes->Font;
StringGridParts->Font = BRefDes->Font;
Font = BRefDes->Font;
CDS_SHORT.cbData =      CDS_SHORT_MAX_LEN;
CDS_LONG.cbData =       CDS_LONG_MAX_LEN;
}



//=================
// timer
//=================
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
static int prev_W=0;
static int prev_H=0;
Form1->Timer1->Interval = 500; //def
if (MousDblClick)
        {
        MousDblClick = false;
        return;
        }
else if (FRead_File)
        {
        prev_W = 0;
        prev_H = 0;
        if( FRead_File == FALSE_FALSE )
                Read_File(false, false);
        else if( FRead_File == FALSE_TRUE )
                Read_File(false, true);
        else if( FRead_File == TRUE_TRUE )
                Read_File(true, true);
        FRead_File = 0;
        return;
        }
Form1->Timer1->Enabled = 0;
if (FindWindow( NULL,"Log") == NULL)
        exit(0);
if (!BEGIN)
        {
        Inicialization();
        Wind = FindWindow( NULL, NULL );
        do      {
                char ch[200];
                GetWindowText( Wind, ch, 200 );
                A = ch;
                if( A.SubString(1,10) == FREEPCB_HEADER )
                        break;
                Wind = ::GetNextWindow (Wind, GW_HWNDNEXT);
                } while( Wind );
        }
else    {
        Wind = GetForegroundWindow();
        }
// FreePcb change size
if( WindowHeader.SubString(1,10) == FREEPCB_HEADER )
        if( Mouse->Capture == 0 )
                if( prev_W != Form1->Width || prev_H != Form1->Height )
                        {
                        Embed(Form1->Width,Form1->Height);
                        SetFormComponentsSizes(false);
                        Form1->PageControl1->Visible = 1;
                        R->Visible = 1;
                        prev_W = Form1->Width;
                        prev_H = Form1->Height;
                        }
//
char WN[200];
GetWindowText(Wind, WN, 200);
AnsiString WinName = WN;
if( WinName.SubString(1,WinName.Length()) == "Log" )
        {
        //Log
        }
else if (WinName.SubString(1,WinName.Length()) != Form1->Caption.SubString(1,Form1->Caption.Length()))
        {
        Form1->Caption = "Infobox";
        //если PCB файл изменен
        //if file change
        AnsiString WindowH = WindowHeader + "*";
        if (WinName.SubString(1,WinName.Length()) == WindowH.SubString(1,WindowH.Length()))
                {
                WindowHeader = WindowH;
                }
        //если PCB файл сохранен
        //if file saved
        int wl = WindowHeader.Length();
        if(wl)  {
                WindowH = WindowHeader.SubString(1,(wl-1));
                if (WinName.SubString(1,WinName.Length()) == WindowH.SubString(1,WindowH.Length()))
                        {
                        WindowHeader = WindowH;
                        FRead_File = FALSE_FALSE;
                        bUPDFILE = true;      // Upd PCB Data
                        }
                }
        //При смене активного окна...
        //action window change
        if  ( WinName.SubString(1,WinName.Length()) != WindowHeader.SubString(1,WindowHeader.Length()) )
                {
                if( WinName.SubString(1,10) == FREEPCB_HEADER )
                        {
                        //
                        Enquary(WinName);
                        HeaderBack = WinName;
                        }
                else    {
                        Form1->Timer1->Interval = 150;
                        //if( Form2->FreePos->Checked )
                                Form1->Visible = false;
                        FileName = "";
                        }
                }
        WindowHeader = WinName;
        }
//
if(bEditPinsMess)
        {
        if( SendMessage_EP("FreePcb - Edit Pins"))
                bEditPinsMess = 0;
        }
if(bEditKITMess)
        {
        AnsiString STORAGE = "storage: \""+ExtractFilePath(Application->ExeName)+"VPL\"";
        if( SendMessage_FILE("FreePcb - Compare"))
                if( SendMessage_FILE("FreePcb - Compare", &STORAGE) )
                        bEditKITMess = 0;
        }
if(bUPDFILE)
        {
        SendMessage_UPDFILE("Areas");
        SendMessage_UPDFILE("Nets");
        bUPDFILE = 0;
        }
Form1->Timer1->Enabled = true;
}







//=================
// order ref
//=================
void __fastcall TForm1::BRefDesClick(TObject *Sender)
{
StringGridPartsRowIndex = 0;
StringGridPinsRowIndex = 0;
SortedParts(col_RefDes+1);
}
//=================
// order value
//=================
void __fastcall TForm1::BValueClick(TObject *Sender)
{
StringGridPartsRowIndex = 0;
StringGridPinsRowIndex = 0;
SortedParts(col_Value+1);
}
//=================
// order pack
//=================
void __fastcall TForm1::BPackageClick(TObject *Sender)
{
StringGridPartsRowIndex = 0;
StringGridPinsRowIndex = 0;
SortedParts(col_Package+1);
}




//=================
// String Grid Parts Key Up
//=================
void __fastcall TForm1::StringGridPartsKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if (Disable_ENTER )
        return;
//VK_UP
if (Key == VK_UP)
        {
        if (!FlagSaveFilter && StringGridPartsRowIndex == 0)
                {
                Form1->CRefDes->SetFocus();
                }
        StringGridPartsRowIndex = Form1->StringGridParts->Row;
        }
else if (Key == VK_DOWN)
        {
        StringGridPartsRowIndex = Form1->StringGridParts->Row;
        }
//VK_DELETE
else if (Key == VK_DELETE)
        {
        Disable_ENTER = true;
        Form1->Timer1->Enabled = false;
        if (JUMP(Form1->StringGridParts->Cells[def_RefDes][Form1->StringGridParts->Row]))
                {
                SetForegroundWindow( FindWindow( NULL, Form1->Caption.c_str() ) );
                DeleteColls ();
                }
        Disable_ENTER = false;
        Form1->Timer1->Enabled = true;
        }
//VK_ESCAPE
else if (Key == VK_ESCAPE)
        {
        if (FlagSaveFilter) SaveFilter(999);
        if( Form2->OnTheRight->Checked == 0 )
                Form1->Height = Form1_Height;
        SetFormComponentsSizes(false);
        Wind = FindWindow(NULL, WindowHeader.c_str());
        SetForegroundWindow(Wind);
        }
else if (Key == VK_RETURN)
        {
        Disable_ENTER = true;
        Form1->Timer1->Enabled = false;
        JUMP(Form1->StringGridParts->Cells[def_RefDes][Form1->StringGridParts->Row]);
        Disable_ENTER = false;
        Form1->Timer1->Enabled = true;
        }
else if (Key == VK_F1)
        {
        Disable_ENTER = true;
        Form1->Timer1->Enabled = false;
        if (JUMP(Form1->StringGridParts->Cells[def_RefDes][Form1->StringGridParts->Row]))
                {
                Wind = FindWindow(NULL, WindowHeader.c_str());
                if (Wind) SetForegroundWindow(Wind);
                Sleep(Pause);
                KEYS ("F1", 1,1, Pause, 1);
                }
        Disable_ENTER = false;
        Form1->Timer1->Enabled = true;
        }
else if (Key == VK_F2)
        {
        Disable_ENTER = true;
        Form1->Timer1->Enabled = false;
        if (JUMP(Form1->StringGridParts->Cells[def_RefDes][Form1->StringGridParts->Row]))
                {
                Wind = FindWindow(NULL, WindowHeader.c_str());
                if (Wind) SetForegroundWindow(Wind);
                Sleep(Pause);
                KEYS ("F2", 1,1, Pause, 1);
                }
        Disable_ENTER = false;
        Form1->Timer1->Enabled = true;
        }
else if (Key == VK_F4)
        {
        Disable_ENTER = true;
        Form1->Timer1->Enabled = false;
        MOVE(Form1->StringGridParts->Cells[def_RefDes][Form1->StringGridParts->Row]);
        //Form1->StringGridParts->SetFocus();
        /*if (move_ok)
        if (StringGridPartsRowIndex < (Form1->StringGridParts->RowCount-1))
                {
                Form1->StringGridParts->Row++;
                StringGridPartsRowIndex++;
                Form1->StringGridParts->Refresh();
                }*/
        Disable_ENTER = false;
        Form1->Timer1->Enabled = true;
        }
Form1->StringGridParts->Refresh();
}



//=================
// String Grid Parts Draw Cell
//=================
void __fastcall TForm1::StringGridPartsDrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
if (ARow == StringGridPartsRowIndex && ACol == StringGridParts->Col)
        {
        StringGridParts->Canvas->Brush->Color = clBlack;
        StringGridParts->Canvas->Font->Color = clWhite;
        StringGridParts->Canvas->FillRect(Rect);
        }
else if (StringGridParts->Cells[def_RefDes][ARow].Length() == 0)
        {
        StringGridParts->Canvas->Brush->Color = clMedGray;
        StringGridParts->Canvas->Font->Color = StringGridParts->Font->Color;
        StringGridParts->Canvas->FillRect(Rect);
        }
else if (ARow == StringGridPartsRowIndex)
        {
        StringGridParts->Canvas->Brush->Color = clMoneyGreen;
        StringGridParts->Canvas->Font->Color = StringGridParts->Font->Color;
        StringGridParts->Canvas->FillRect(Rect);
        }
else if( N_PART_ELEMENTS > StringGridParts->RowCount )
        {
        if( ARow%2 )
                StringGridParts->Canvas->Brush->Color = clSkyBlue;
        else    StringGridParts->Canvas->Brush->Color = clAqua;
        StringGridParts->Canvas->Font->Color = StringGridParts->Font->Color;
        StringGridParts->Canvas->FillRect(Rect);
        }
else if( ARow%2 )
        {
        StringGridParts->Canvas->Brush->Color = clCream;
        StringGridParts->Canvas->Font->Color = StringGridParts->Font->Color;
        StringGridParts->Canvas->FillRect(Rect);
        }
else    {
        StringGridParts->Canvas->Brush->Color = clMenu;
        StringGridParts->Canvas->Font->Color = StringGridParts->Font->Color;
        StringGridParts->Canvas->FillRect(Rect);
        }
DrawText(StringGridParts->Canvas->Handle,
StringGridParts->Cells[ACol][ARow].c_str(),
StringGridParts->Cells[ACol][ARow].Length(),&Rect, DT_CENTER);
}




//=================
// language
//=================
void INTER_FACE (void)
{
Form1->CCNetlist->Items->Clear();
Form1->CType->Items->Clear();
Form1->CTrml->Items->Clear();
if (Form2->Language->Checked)
   { // русский
     // Form1
     Form1->BRefDes->Caption =          "Обозн.";
     Form1->BRIRange->Caption =         "Индекс";
     Form1->BValue->Caption =           "Номинал";
     Form1->BValueNL->Caption =         "Номинал-НЛ";
     Form1->BPackage->Caption =         "Корпус";
     Form1->BPackageNL->Caption =       "Футпринт-НЛ";
     Form1->BFootPrint->Caption =       "Футпринт";
     Form1->BMerge->Caption =           "Слияние";
     Form1->BPins->Caption =            "Пины";
     Form1->BHoles->Caption =           "Отв";
     Form1->BGlueds->Caption =          "Фикс";
     Form1->BSide->Caption =            "Сторона";
     Form1->BAng->Caption =             "Угол";
     Form1->BCNetlist->Caption =        "Расхождения-НЛ";
     Form1->BPin->Caption =             "Пин";
     Form1->BPinNetPCB->Caption =       "Сеть";
     Form1->BCnt->Caption =             "Кол-во";
     Form1->BPinNetList->Caption =      "Сеть-NL";
     Form1->BType->Caption =            "Форма";
     Form1->BW->Caption =               "Ширина";
     Form1->BL->Caption =               "Длина";
     Form1->BTrml->Caption =           "Термо";
     Form1->BDHole->Caption =           "Диам отв";
     Form1->BPas->Caption =             "Паста";
     Form1->Parts->Caption =            "Детали";
     Form1->Pins->Caption =             "Пины";
     Form1->ST_popup->Caption =         " Настройки...";
     Form1->RF_popup->Caption =         " Очистить консоль поиска";
     Form1->CSC_popup->Caption =        " Закрепить отфильтрованные детали";
     Form1->PF_popup->Caption =         " Открыть папку с проектом";
     Form1->HA_popup->Caption =         " Зажечь все элементы";
     Form1->VP_popup->Caption =         " Добавить Значения в хранилище";
     Form1->TXT_popup->Caption =        " Генерировать TXT список";
     Form1->EX_popup->Caption =         " Генерировать CSV список";
     Form1->CP_popup->Caption =         " Сравнить монтажный комплект";
     Form1->EP_popup->Caption =         " Редактировать пины(комплекс)";
     Form1->FA_popup->Caption =         " Залить полигоны";
     Form1->NE_popup->Caption =         " Показать сеть";
     Form1->LN_popup->Caption =         " Загрузить сети из нетлиста";
     // Form2
     Form2->Language->Caption =         "Русский интерфейс";
     Form2->IgnoreCase->Caption =       "Не учитывать регистр в фильтре";
     Form2->OnlyLatin->Caption =        "Только латинские обозначения";
     //Form2->GroupBoxPath->Caption =     "Пути к каталогу проекта";
     Form2->Memo1->Lines->Clear();
     Form2->Memo1->Lines->Add("Для быстрого редактирования, некоторые функциональные кнопки  FREEPCB работают и в INFOBOX. В окне REF строки поиска или после щелчка мышью по выбранной детали вы можете запустить:");
     Form2->Memo1->Lines->Add("F1 - Свойства открытой детали ");
     Form2->Memo1->Lines->Add("F4 - Переместить деталь в центр экрана");
     Form2->mem_pos_wnd->Caption = "Запомнить размер и положение окна ИНФОБОКСА";
     Form1->CType->          Items->Add("Нет");
     Form1->CType->          Items->Add("Круг");
     Form1->CType->          Items->Add("Квадрат");
     Form1->CType->          Items->Add("Прямоуг");
     Form1->CType->          Items->Add("СкругПр");
     Form1->CType->          Items->Add("Овал");
     Form1->CType->          Items->Add("Октагон");
     Form1->CTrml->          Items->Add("Default");
     Form1->CTrml->          Items->Add("NC");
     Form1->CTrml->          Items->Add("Thermal");
     Form1->CTrml->          Items->Add("NoThrml");
   }
else
   { // english
     // Form1
     Form1->BRefDes->Caption =          "Ref";
     Form1->BRIRange->Caption =         "Index";
     Form1->BValue->Caption =           "Value";
     Form1->BValueNL->Caption =         "Value-NL";
     Form1->BPackage->Caption =         "Package";
     Form1->BPackageNL->Caption =       "Footprint-NL";
     Form1->BFootPrint->Caption =       "Footprint";
     Form1->BMerge->Caption =           "Merge";
     Form1->BPins->Caption =            "Pins";
     Form1->BHoles->Caption =           "Holes";
     Form1->BGlueds->Caption =          "G";
     Form1->BSide->Caption =            "S";
     Form1->BAng->Caption =             "Ang";
     Form1->BCNetlist->Caption =        "Discrepancy-NL";
     Form1->BPin->Caption =             "Pin";
     Form1->BPinNetPCB->Caption =       "Net";
     Form1->BCnt->Caption =             "Cnt";
     Form1->BPinNetList->Caption =      "Net-NL";
     Form1->BType->Caption =            "Type";
     Form1->BW->Caption =               "Width";
     Form1->BL->Caption =               "Length";
     Form1->BTrml->Caption =            "Thermal";
     Form1->BDHole->Caption =           "Hole diam";
     Form1->BPas->Caption =             "Paste";
     Form1->Parts->Caption =            "Parts";
     Form1->Pins->Caption =             "Pins";
     Form1->ST_popup->Caption =         " Settings...";
     Form1->RF_popup->Caption =         " Clear Search Console";
     Form1->CSC_popup->Caption =        " Fix Filtered Parts";
     Form1->PF_popup->Caption =         " Open project folder";
     Form1->HA_popup->Caption =         " Highlight all elements";
     Form1->VP_popup->Caption =         " Add Part Values to Storage";
     Form1->TXT_popup->Caption =        " Generate TXT list";
     Form1->EX_popup->Caption =         " Generate CSV list";
     Form1->CP_popup->Caption =         " Compare PCB assembly kit";
     Form1->EP_popup->Caption =         " Edit pins (complex)";
     Form1->FA_popup->Caption =         " Pour areas";
     Form1->NE_popup->Caption =         " Show net";
     Form1->LN_popup->Caption =         " Loading nets from netlist";
     // Form2
     Form2->Language->Caption =         "Russian language";
     Form2->IgnoreCase->Caption =       "Ignore case in the filter";
     Form2->OnlyLatin->Caption =        "Only Latin symbols";
     //Form2->GroupBoxPath->Caption =     "Paths to project folders";
     Form2->Memo1->Lines->Clear();
     Form2->Memo1->Lines->Add("For quick editing, some FREEPCB function keys work in INFOBOX. From the REF search string or after clicking the mouse on the selected part, you can run");
     Form2->Memo1->Lines->Add("F1 - Open part properties");
     Form2->Memo1->Lines->Add("F4 - Move part to center of screen");
     Form2->Memo1->Lines->Add("ENTER - Jump to part");
     Form2->Memo1->Lines->Add("For example, if you want to find a part and move it, then in the search box enter the line R1(+space character) then press F4 and the part will be in your hands");
     Form2->mem_pos_wnd->Caption = "Remember size and position of the InfoBox window";
     Form1->CType->          Items->Add("None");
     Form1->CType->          Items->Add("Round");
     Form1->CType->          Items->Add("Square");
     Form1->CType->          Items->Add("Rect");
     Form1->CType->          Items->Add("RndRect");
     Form1->CType->          Items->Add("Oval");
     Form1->CType->          Items->Add("Octagon");
     Form1->CTrml->          Items->Add("Default");
     Form1->CTrml->          Items->Add("NC");
     Form1->CTrml->          Items->Add("Thermal");
     Form1->CTrml->          Items->Add("NoThrml");
   }
//CCnlistRefresh();
Application->ProcessMessages();
}



//=================
//
//=================
void __fastcall TForm1::MinPinKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if (Key == VK_DOWN)             Form1->StringGridParts->SetFocus();
else if (Key == VK_LEFT)        Form1->CMerge->SetFocus();
else if (Key == VK_RIGHT)       Form1->MaxPins->SetFocus();
else FilterAll();
}
//---------------------------------------------------------------------------








//---------------------------------------------------------------------------
void __fastcall TForm1::MinHolesKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if (Key == VK_DOWN)        Form1->StringGridParts->SetFocus();
else if (Key == VK_LEFT)        Form1->MaxPins->SetFocus();
else if (Key == VK_RIGHT)       Form1->MaxHoles->SetFocus();
else FilterAll();
}
//---------------------------------------------------------------------------







//---------------------------------------------------------------------------
void __fastcall TForm1::StringGridPartsMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
Form1->Caption = "Infobox";
if (Button == mbRight) return;
if (MousDblClick)
        {
        if (Form1->StringGridParts->Col == def_RefDes)
                {
                Disable_ENTER = true;
                Form1->Timer1->Enabled = false;
                JUMP(Form1->StringGridParts->Cells[def_RefDes][Form1->StringGridParts->Row]);
                Disable_ENTER = false;
                Form1->Timer1->Enabled = true;
                return;
                }
        else if (Form1->StringGridParts->Col == def_Value)
                Form1->CValue->Text = Form1->StringGridParts->Cells[def_Value][Form1->StringGridParts->Row];
        else if (Form1->StringGridParts->Col == def_ValueNL)
                Form1->CValueNL->Text = Form1->StringGridParts->Cells[def_ValueNL][Form1->StringGridParts->Row];
        else if (Form1->StringGridParts->Col == def_FootPrint)
                Form1->CFootPrint->Text = Form1->StringGridParts->Cells[def_FootPrint][Form1->StringGridParts->Row];
        else if (Form1->StringGridParts->Col == def_Package)
                Form1->CPackage->Text = Form1->StringGridParts->Cells[def_Package][Form1->StringGridParts->Row];
        else if (Form1->StringGridParts->Col == def_PackageNL)
                Form1->CPackageNL->Text = Form1->StringGridParts->Cells[def_PackageNL][Form1->StringGridParts->Row];
        else if (Form1->StringGridParts->Col == def_Merge)
                Form1->CMerge->Text = Form1->StringGridParts->Cells[def_Merge][Form1->StringGridParts->Row];
        FilterAll();
        }
else if (Form1->StringGridParts->Cells[def_RefDes][Form1->StringGridParts->Row].Length() == 0)
        {
        AnsiString value = Form1->StringGridParts->Cells[def_Value][Form1->StringGridParts->Row];
        value = value.LowerCase();
        if (value.Length() != 0)
                {
                AnsiString path = "";
                for (int w=0; w<Form1->Values->Items->Count; w++)
                        {
                        AnsiString text = Form1->Values->Items->operator [](w);
                        text = text.Trim();
                        int TL = text.Length();
                        int pos = text.Pos(dSPACE);
                        if( pos < 1 )
                                pos = text.Pos("\t");
                        if (pos > 0)
                                {
                                AnsiString Vtext = text.LowerCase().SubString(1,(pos-1));
                                int TL2 = Vtext.Length();
                                if (value.SubString(1,value.Length()) == Vtext.SubString(1,TL2))
                                        {
                                        AnsiString share = text.SubString(pos,TL-pos+1);
                                        share = share.TrimLeft();
                                        int i2 = share.Pos(dSPACE);
                                        if( i2 < 1 )
                                                i2 = share.Pos("\t");
                                        int sh_L = share.Length();
                                        path = share.SubString(i2,sh_L-i2+1).TrimLeft();
                                        break;
                                        }
                                }
                        }
                if (path.Length())
                        Form1->Caption = path;
                else if (Form2->Language->Checked)
                        Form1->Caption = "Строка пути отсутствует";
                else
                        Form1->Caption = "String path not found";
                }
        }
else    {
        MousDblClick = true;
        Form1->Timer1->Interval = TIMER_DBL_CLICK;
        }
}
//---------------------------------------------------------------------------









//---------------------------------------------------------------------------
void __fastcall TForm1::MaxPinsKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if (Key == VK_DOWN)             Form1->StringGridParts->SetFocus();
else if (Key == VK_LEFT)        Form1->MinPin->SetFocus();
else if (Key == VK_RIGHT)       Form1->MinHoles->SetFocus();
else FilterAll();
}
//---------------------------------------------------------------------------








//---------------------------------------------------------------------------
void __fastcall TForm1::MaxHolesKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if (Key == VK_DOWN)             Form1->StringGridParts->SetFocus();
else if (Key == VK_LEFT)        Form1->MinHoles->SetFocus();
else if (Key == VK_RIGHT)       Form1->Glueds->SetFocus();
else FilterAll();
}
//---------------------------------------------------------------------------








//---------------------------------------------------------------------------
void __fastcall TForm1::GluedsKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if (Form1->Glueds->Text.SubString(1,1) == "?") Form1->Glueds->Text = "";
if (Key == VK_DOWN)             Form1->StringGridParts->SetFocus();
else if (Key == VK_LEFT)        Form1->MaxHoles->SetFocus();
else if (Key == VK_RIGHT)       Form1->Side->SetFocus();
else FilterAll();
}
//---------------------------------------------------------------------------









//---------------------------------------------------------------------------
void __fastcall TForm1::SideKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if (Form1->Side->Text.SubString(1,1) == "?") Form1->Side->Text = "";
if (Key == VK_DOWN)             Form1->StringGridParts->SetFocus();
else if (Key == VK_LEFT)        Form1->Glueds->SetFocus();
else if (Key == VK_RIGHT)       Form1->Ang->SetFocus();
else FilterAll();
}
//---------------------------------------------------------------------------









//---------------------------------------------------------------------------
void __fastcall TForm1::AngKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
B = Form1->Ang->Text;
if (B.SubString(B.Length(),1) >= "0")
if (B.SubString(B.Length(),1) <= "9") {;}
else Form1->Ang->Text = "";
else Form1->Ang->Text = "";
if (Key == VK_DOWN)             Form1->StringGridParts->SetFocus();
else if (Key == VK_LEFT)        Form1->Side->SetFocus();
else if (Key == VK_RIGHT)       Form1->EXmin->SetFocus();
else FilterAll();
}
//---------------------------------------------------------------------------










//---------------------------------------------------------------------------
void __fastcall TForm1::EXminKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if (Key == VK_DOWN)             Form1->StringGridParts->SetFocus();
else if (Key == VK_LEFT)        Form1->Ang->SetFocus();
else if (Key == VK_RIGHT)       Form1->EXmax->SetFocus();
else FilterAll();
}
//---------------------------------------------------------------------------









//---------------------------------------------------------------------------
void __fastcall TForm1::EXmaxKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if (Key == VK_DOWN)             Form1->StringGridParts->SetFocus();
else if (Key == VK_LEFT)        Form1->EXmin->SetFocus();
else if (Key == VK_RIGHT)       Form1->EYmin->SetFocus();
else FilterAll();
}
//---------------------------------------------------------------------------










//---------------------------------------------------------------------------
void __fastcall TForm1::EYminKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if (Key == VK_DOWN)             Form1->StringGridParts->SetFocus();
else if (Key == VK_LEFT)        Form1->EXmax->SetFocus();
else if (Key == VK_RIGHT)       Form1->EYmax->SetFocus();
else FilterAll();
}
//---------------------------------------------------------------------------








//---------------------------------------------------------------------------
void __fastcall TForm1::EYmaxKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if (Key == VK_DOWN)             Form1->StringGridParts->SetFocus();
else if (Key == VK_LEFT)        Form1->EYmin->SetFocus();
else if (Key == VK_RIGHT)       Form1->CCNetlist->SetFocus();
else FilterAll();
}
//---------------------------------------------------------------------------









//---------------------------------------------------------------------------
void __fastcall TForm1::CCNetlistKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if (Key == VK_DOWN)             Form1->StringGridParts->SetFocus();
else if (Key == VK_LEFT)        Form1->EYmax->SetFocus();
else FilterAll();
}
//---------------------------------------------------------------------------




//---------------------------------------------------------------------------
void __fastcall TForm1::GluedsKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if (Form2->OnlyLatin->Checked == true) LoadKeyboardLayout("00000409", KLF_ACTIVATE);	//английская раскладка
}
//---------------------------------------------------------------------------





//---------------------------------------------------------------------------
void __fastcall TForm1::SideKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if (Form2->OnlyLatin->Checked == true) LoadKeyboardLayout("00000409", KLF_ACTIVATE);	//английская раскладка
}
//---------------------------------------------------------------------------








//---------------------------------------------------------------------------
void __fastcall TForm1::CCNetlistChange(TObject *Sender)
{
bool b1 = (Form1->CCNetlist->ItemIndex == (Form1->CCNetlist->Items->Count-1));
bool b2 = (Form1->CCNetlist->ItemIndex == (Form1->CCNetlist->Items->Count-2));
if (b1 || b2)
        {
        Form1->Timer1->Enabled = false;
        if (b1)
        if (Form1->OpenDialog2->Execute())
                {
                AnsiString new_n_list = NetListPath;
                if( Form1->OpenDialog2->FilterIndex == 1 )
                        {
                        new_n_list = Read_TXT_Table(Form1->OpenDialog2->FileName, 1 );
                        NetListPath = "#" + new_n_list;
                        }
                else if( Form1->OpenDialog2->FilterIndex == 2 )
                        {
                        new_n_list = Read_TXT_Table(Form1->OpenDialog2->FileName, 0 );
                        NetListPath = "#" + new_n_list;
                        }
                }
        else    b1 = 0;
        if (b2)
        if (Form1->OpenDialog1->Execute())
                {
                NetListPath = "#" + Form1->OpenDialog1->FileName;
                }
        else    b2 = 0;
        if( FileName.Length() == 0 && FileNameBack.Length() )
                {
                FileName = FileNameBack;
                WindowHeader = HeaderBack;
                }
        if (b1 || b2)
                FRead_File = FALSE_TRUE;
        Form1->CCNetlist->ItemIndex = -1;
        Form1->Timer1->Enabled = true;
        return;
        }
FilterAll();
}
//---------------------------------------------------------------------------










//---------------------------------------------------------------------------
void __fastcall TForm1::CRefDeshange(TObject *Sender)
{
if (FlagSaveFilter)
        return;
Form1->Caption = "Infobox";
Form1->TFilterAll->Enabled = true;
}
//---------------------------------------------------------------------------





//---------------------------------------------------------------------------
void __fastcall TForm1::StringGridPartsMouseWheelDown(TObject *Sender,
      TShiftState Shift, TPoint &MousePos, bool &Handled)
{
if (Form1->StringGridParts->Row != Form1->StringGridParts->RowCount-1)
        {
        AnsiString S;
        S = "Ref ";
        S += Form1->StringGridParts->Cells[def_RefDes][Form1->StringGridParts->Row+1];
        S += "        ";
        S += Form1->StringGridParts->Cells[def_Value][Form1->StringGridParts->Row+1];
        S += "        ";
        S += Form1->StringGridParts->Cells[def_Package][Form1->StringGridParts->Row+1];
        //Form1->Caption = S;
        StringGridPartsRowIndex = Form1->StringGridParts->Row+1;
        StringGridParts->Refresh();
        }
}
//---------------------------------------------------------------------------









//---------------------------------------------------------------------------
void __fastcall TForm1::StringGridPartsMouseWheelUp(TObject *Sender,
      TShiftState Shift, TPoint &MousePos, bool &Handled)
{
if (Form1->StringGridParts->Row)
        {
        AnsiString S;
        S = "Ref ";
        S += Form1->StringGridParts->Cells[def_RefDes][Form1->StringGridParts->Row-1];
        S += "        ";
        S += Form1->StringGridParts->Cells[def_Value][Form1->StringGridParts->Row-1];
        S += "        ";
        S += Form1->StringGridParts->Cells[def_Package][Form1->StringGridParts->Row-1];
        //Form1->Caption = S;
        StringGridPartsRowIndex = Form1->StringGridParts->Row-1;
        StringGridParts->Refresh();
        }
}
//---------------------------------------------------------------------------










//---------------------------------------------------------------------------









//---------------------------------------------------------------------------








//---------------------------------------------------------------------------
void __fastcall TForm1::StringGridPartsContextPopup(TObject *Sender,
      TPoint &MousePos, bool &Handled)
{
MousDblClick = false;
Form1->CP_popup->Enabled = true;
Form1->LN_popup->Enabled = false;
if (FileName.Length())
        {
        Form1->RF_popup->Enabled = true;
        Form1->PF_popup->Enabled = true;
        Form1->VP_popup->Enabled = true;
        Form1->EX_popup->Enabled = true;
        Form1->TXT_popup->Enabled = true;
        Form1->CSC_popup->Enabled = true;
        Form1->HA_popup->Enabled = true;
        }
else    {
        Form1->RF_popup->Enabled = false;
        Form1->PF_popup->Enabled = false;
        Form1->VP_popup->Enabled = false;
        Form1->EX_popup->Enabled = false;
        Form1->TXT_popup->Enabled = false;
        Form1->CSC_popup->Enabled = false;
        Form1->HA_popup->Enabled = false;
        }
}
//---------------------------------------------------------------------------







//---------------------------------------------------------------------------
void __fastcall TForm1::PageControl1Change(TObject *Sender)
{
if( Form1->PageControl1->TabIndex && PinsWasR == 0 )
        if( FRead_File == FALSE_TRUE )
                Read_File( FALSE, TRUE );
        else if( FRead_File == TRUE_TRUE )
                Read_File( TRUE, TRUE );
        else    Read_File( FALSE, FALSE );
else    {
        Form1->StringGridParts->Visible = 0;
        Form1->StringGridPins->Visible = 0;
        FilterAll(false, "", 1-Form1->PageControl1->TabIndex);
        FilterAll(true);
        Form1->StringGridParts->Visible = 1;
        Form1->StringGridPins->Visible = 1;
        }
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------


void __fastcall TForm1::StringGridPartsMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
FlagProgEXE = false;
if (Button == mbRight) return;
StringGridPartsRowIndex = Form1->StringGridParts->Row;
StringGridParts->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BPinsClick(TObject *Sender)
{
StringGridPartsRowIndex = 0;
StringGridPinsRowIndex = 0;
SortedParts(col_Pins+1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BHolesClick(TObject *Sender)
{
StringGridPartsRowIndex = 0;
StringGridPinsRowIndex = 0;
SortedParts(col_Holes+1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BGluedsClick(TObject *Sender)
{
StringGridPartsRowIndex = 0;
StringGridPinsRowIndex = 0;
SortedParts(col_Gl+1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BSideClick(TObject *Sender)
{
StringGridPartsRowIndex = 0;
StringGridPinsRowIndex = 0;
SortedParts(col_S+1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BAngClick(TObject *Sender)
{
StringGridPartsRowIndex = 0;
StringGridPinsRowIndex = 0;
SortedParts(col_Ang+1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BXClick(TObject *Sender)
{
StringGridPartsRowIndex = 0;
StringGridPinsRowIndex = 0;
SortedParts(col_Xprt+1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BYClick(TObject *Sender)
{
StringGridPartsRowIndex = 0;
StringGridPinsRowIndex = 0;
SortedParts(col_Yprt+1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BCNetlistClick(TObject *Sender)
{
StringGridPartsRowIndex = 0;
StringGridPinsRowIndex = 0;
SortedParts(col_CompareNetlist+1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CRefDesKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if (Key == VK_RETURN)
        {
        if (FlagSaveFilter) SaveFilter(0);
        else    {
                Disable_ENTER = true;
                Form1->Timer1->Enabled = false;
                if( StringGridParts->RowCount == 1 )
                        JUMP(Form1->StringGridParts->Cells[def_RefDes][0]);
                else
                        HighlightAll();
                Disable_ENTER = false;
                Form1->Timer1->Enabled = true;
                }
        }
else if (Key == VK_F4)
        {
        Disable_ENTER = true;
        Form1->Timer1->Enabled = false;
        MOVE(Form1->StringGridParts->Cells[def_RefDes][Form1->StringGridParts->Row]);
        Disable_ENTER = false;
        Form1->Timer1->Enabled = true;
        //Form1->CRefDes->SetFocus();
        }
else if (Key == VK_F1)
        {
        Disable_ENTER = true;
        Form1->Timer1->Enabled = false;
        if (JUMP(Form1->StringGridParts->Cells[def_RefDes][Form1->StringGridParts->Row]))
                {
                Wind = FindWindow(NULL, WindowHeader.c_str());
                if (Wind) SetForegroundWindow(Wind);
                Sleep(Pause);
                KEYS ("F1", 1,1, Pause, 1);
                }
        Disable_ENTER = false;
        Form1->Timer1->Enabled = true;
        }
else if (Key == VK_F2)
        {
        Disable_ENTER = true;
        Form1->Timer1->Enabled = false;
        if (JUMP(Form1->StringGridParts->Cells[def_RefDes][Form1->StringGridParts->Row]))
                {
                Wind = FindWindow(NULL, WindowHeader.c_str());
                if (Wind) SetForegroundWindow(Wind);
                Sleep(Pause);
                KEYS ("F2", 1,1, Pause, 1);
                }
        Disable_ENTER = false;
        Form1->Timer1->Enabled = true;
        }
else if (Key == VK_ESCAPE)
        {
        if (FlagSaveFilter) SaveFilter(999);
        if( Form2->OnTheRight->Checked == 0 )
                Form1->Height = Form1_Height;
        SetFormComponentsSizes(false);
        Wind = FindWindow(NULL, WindowHeader.c_str());
        SetForegroundWindow(Wind);
        }
else if (Key == VK_DOWN)
        {
        if (!FlagSaveFilter)
                {
                Form1->StringGridParts->SetFocus();
                }
        }
}

//---------------------------------------------------------------------------







void __fastcall TForm1::StringGridPinsMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
static int PrevRowIndex = -1, PrevColIndex = -1, bDrawn = 0;
//
if (Button == mbRight) return;
if (MousDblClick)
        {
        if (Form1->StringGridPins->Col == def_Pin)
                {
                Disable_ENTER = true;
                Form1->Timer1->Enabled = false;
                JUMP(Form1->StringGridPins->Cells[def_Pin][Form1->StringGridPins->Row]);
                Disable_ENTER = false;
                Form1->Timer1->Enabled = true;
                }
        else if (Form1->StringGridPins->Col == def_NetPcb)
                {
                Form1->CPinNetPCB->Text = Form1->StringGridPins->Cells[def_NetPcb][Form1->StringGridPins->Row];
                FilterAll();
                }
        else if (Form1->StringGridPins->Col == def_Netlist)
                {
                Form1->CNetNetlist->Text = Form1->StringGridPins->Cells[def_Netlist][Form1->StringGridPins->Row];
                FilterAll();
                }
        }
else if (Form1->StringGridPins->Col == def_Pin)
        {
        int Hght = 0;
        AnsiString Hint="";
        AnsiString Pin = Form1->StringGridPins->Cells[def_Pin][StringGridPinsRowIndex];
        int PinLength = Pin.Length();
        int ip = Pin.Pos(".");
        if( ip > 0 && (PrevRowIndex != StringGridPinsRowIndex || PrevColIndex != def_Pin || bDrawn == 0) )
                {
                bDrawn = 1;
                if (Form1->StringGridPins->Row+1 == Form1->StringGridPins->RowCount)
                        {
                        Form1->StringGridPins->RowCount++;
                        for(int ii=0; ii<PinsColCount; ii++)
                                Form1->StringGridPins->Cells[ii][StringGridPinsRowIndex+1] = "";
                        Form1->StringGridPins->Refresh();
                        }
                int StrLen = 0;
                for( int shift=1; shift<Form1->DataPins->Items->Count; shift+=(PinsColCount+1) )
                        {
                        AnsiString gPin = Form1->DataPins->Items->operator [](shift+col_Pin);
                        if(Pin.SubString(1,ip) == gPin.SubString(1,ip))
                        if(Pin.SubString(1,PinLength) != gPin.SubString(1,gPin.Length()))
                                {
                                Hght += Form1->StringGridPins->DefaultRowHeight;
                                Hint = Form1->DataPins->Items->operator [](shift+col_Pin);
                                Hint += "  " + Form1->DataPins->Items->operator [](shift+col_NetPcb);
                                StrLen = MAX( StrLen,Hint.Length() );
                                }
                        }
                Form1->StringGridPins->Canvas->Rectangle(X+30,Y,StrLen*8+X+30,Hght+Y);
                Hght = 1;
                for( int shift=1; shift<Form1->DataPins->Items->Count; shift+=(PinsColCount+1) )
                        {
                        AnsiString gPin = Form1->DataPins->Items->operator [](shift+col_Pin);
                        if( Pin.SubString(1,ip) == gPin.SubString(1,ip) )
                        if(Pin.SubString(1,PinLength) != gPin.SubString(1,gPin.Length()))
                                {
                                Hint = Form1->DataPins->Items->operator [](shift+col_Pin);
                                Hint += "  " + Form1->DataPins->Items->operator [](shift+col_NetPcb);
                                Form1->StringGridPins->Canvas->TextOutA(X+33,Hght+Y,Hint);
                                Hght += Form1->StringGridPins->DefaultRowHeight;
                                }
                        }
                }
        else    bDrawn = 0;
        MousDblClick = true;
        Form1->Timer1->Interval = TIMER_DBL_CLICK;
        PrevColIndex = def_Pin;
        }
else if (Form1->StringGridPins->Col == def_NetPcb ||
         Form1->StringGridPins->Col == def_Netlist)
        {
        bool npcb = (Form1->StringGridPins->Col == def_NetPcb);
        int NetCOL = 0;
        if( npcb )
                NetCOL = def_NetPcb;
        else    NetCOL = def_Netlist;
        int Hght = 0;
        AnsiString Hint="";
        AnsiString Net = Form1->StringGridPins->Cells[NetCOL][StringGridPinsRowIndex];
        AnsiString Pin = Form1->StringGridPins->Cells[def_Pin][StringGridPinsRowIndex];
        int PinLength = Pin.Length();
        Net = Net.TrimRight();
        int inet = StringGridPinsRowIndex;
        if( inet ) while( Net.SubString(1,Net.Length()) == Form1->StringGridPins->Cells[NetCOL][inet-1] )
                {
                inet--;
                if( !inet )
                        break;
                }
        //AnsiString cntpins = Form1->StringGridPins->Cells[def_Cnt][inet];
        int cnt = 0;
        if( Net.Length() )
        if( PrevRowIndex != StringGridPinsRowIndex || PrevColIndex != NetCOL || bDrawn == 0 )
                {
                bDrawn = 1;
                if (Form1->StringGridPins->Row+1 == Form1->StringGridPins->RowCount)
                        {
                        Form1->StringGridPins->RowCount++;
                        for(int ii=0; ii<PinsColCount; ii++)
                                Form1->StringGridPins->Cells[ii][StringGridPinsRowIndex+1] = "";
                        Form1->StringGridPins->Refresh();
                        }
                cnt = 0;
                int StrLen = 0;
                for( int shift=1; shift<Form1->DataPins->Items->Count; shift+=(PinsColCount+1) )
                        {
                        AnsiString Sim = Form1->DataPins->Items->operator [](shift+NetCOL);
                        AnsiString gPin = Form1->DataPins->Items->operator [](shift+def_Pin);
                        if(Pin.SubString(1,PinLength) != gPin.SubString(1,gPin.Length()))
                        if(Sim.SubString(1,Sim.Length()).TrimRight() == Net.SubString(1,Net.Length()))
                                {
                                cnt++;
                                Hint = Form1->DataPins->Items->operator [](shift+def_Pin);
                                StrLen = MAX( StrLen ,Hint.Length() );
                                }
                        }
                Hght = Form1->StringGridPins->DefaultRowHeight*cnt + 4;
                Form1->StringGridPins->Canvas->Rectangle(X+30,Y,X+StrLen*8+30,Hght+Y);
                Hght = 2;
                for( int shift=1; shift<Form1->DataPins->Items->Count; shift+=(PinsColCount+1) )
                        {
                        AnsiString Sim = Form1->DataPins->Items->operator [](shift+NetCOL);
                        AnsiString gPin = Form1->DataPins->Items->operator [](shift+def_Pin);
                        if(Pin.SubString(1,PinLength) != gPin.SubString(1,gPin.Length()))
                        if(Sim.SubString(1,Sim.Length()).TrimRight() == Net.SubString(1,Net.Length()))
                                {
                                Hint = Form1->DataPins->Items->operator [](shift+def_Pin);
                                Form1->StringGridPins->Canvas->TextOutA(X+33,Hght+Y,Hint);
                                Hght += Form1->StringGridPins->DefaultRowHeight;
                                }
                        }
                }
        else    bDrawn = 0;
        MousDblClick = true;
        Form1->Timer1->Interval = TIMER_DBL_CLICK;
        PrevColIndex = NetCOL;
        }
else    {
        MousDblClick = true;
        Form1->Timer1->Interval = TIMER_DBL_CLICK;
        Form1->StringGridPins->Refresh();
        }
PrevRowIndex = StringGridPinsRowIndex;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::StringGridPinsMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
FlagProgEXE = false;
if (Button == mbRight) return;
StringGridPinsRowIndex = Form1->StringGridPins->Row;
StringGridPins->Refresh();
}
//---------------------------------------------------------------------------



void __fastcall TForm1::StringGridPinsDrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
AnsiString N2 = StringGridPins->Cells[def_Netlist][ARow];
int N2L = N2.Length();
if (N2L)
        {
        if (N2.SubString(N2L-1,2) == dSPACE && (ACol == def_NetPcb || ACol == def_Netlist) && NetListPath.Length())
                {
                StringGridPins->Canvas->Brush->Color = clYellow;
                StringGridPins->Canvas->Font->Color = StringGridPins->Font->Color;
                StringGridPins->Canvas->FillRect(Rect);
                if (ARow == StringGridPinsRowIndex && ACol == StringGridPins->Col)
                        {
                        StringGridPins->Canvas->Brush->Color = clBlack;
                        StringGridPins->Canvas->Font->Color = clWhite;
                        StringGridPins->Canvas->FillRect(Rect);
                        }
                if (NetListPath.Length() == 0 && ACol == def_Netlist)
                        return;
                DrawText(StringGridPins->Canvas->Handle,
                StringGridPins->Cells[ACol][ARow].c_str(),
                StringGridPins->Cells[ACol][ARow].Length(),&Rect, DT_CENTER);
                return;
                }
        }
if (ARow == StringGridPinsRowIndex && ACol == StringGridPins->Col)
        {
        StringGridPins->Canvas->Brush->Color = clBlack;
        StringGridPins->Canvas->Font->Color = clWhite;
        StringGridPins->Canvas->FillRect(Rect);
        }
else if (ARow == StringGridPinsRowIndex)
        {
        StringGridPins->Canvas->Brush->Color = clMoneyGreen;
        StringGridPins->Canvas->Font->Color = clWhite;
        StringGridPins->Canvas->FillRect(Rect);
        }
else if( N_PIN_ELEMENTS > StringGridPins->RowCount )
        {
        if( ARow%2 )
                StringGridPins->Canvas->Brush->Color = clSkyBlue;
        else    StringGridPins->Canvas->Brush->Color = clAqua;
        StringGridPins->Canvas->Font->Color = StringGridPins->Font->Color;
        StringGridPins->Canvas->FillRect(Rect);
        }
else if( ARow%2 )
        {
        StringGridPins->Canvas->Brush->Color = clCream;
        StringGridPins->Canvas->Font->Color = StringGridParts->Font->Color;
        StringGridPins->Canvas->FillRect(Rect);
        }
else    {
        StringGridPins->Canvas->Brush->Color = clMenu;//clWhite;
        StringGridPins->Canvas->Font->Color = StringGridParts->Font->Color;
        StringGridPins->Canvas->FillRect(Rect);
        }
//
if (NetListPath.Length() == 0 && ACol == def_Netlist)
        return;
DrawText(StringGridPins->Canvas->Handle,
StringGridPins->Cells[ACol][ARow].c_str(),
StringGridPins->Cells[ACol][ARow].Length(),&Rect, DT_CENTER);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StringGridPinsKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if (Disable_ENTER == true) return;
//VK_DELETE
else if (Key == VK_DELETE) DeleteColls ();
//VK_ESCAPE
else if (Key == VK_ESCAPE)
        {
        if (FlagSaveFilter) SaveFilter(999);
        if( Form2->OnTheRight->Checked == 0 )
                Form1->Height = Form1_Height;
        SetFormComponentsSizes(false);
        Wind = FindWindow(NULL, WindowHeader.c_str());
        SetForegroundWindow(Wind);
        }
else if (Key == VK_RETURN)
        {
        Disable_ENTER = true;
        Form1->Timer1->Enabled = false;
        JUMP(Form1->StringGridPins->Cells[def_Pin][Form1->StringGridPins->Row]);
        Disable_ENTER = false;
        Form1->Timer1->Enabled = true;
        }
else if (Key == VK_DOWN)
        {
        StringGridPinsRowIndex = Form1->StringGridPins->Row;
        }
else if (Key == VK_UP)
        {
        //VK_UP
        if (!FlagSaveFilter && StringGridPinsRowIndex == 0)
                {
                Form1->CPin->SetFocus();
                }
        StringGridPinsRowIndex = Form1->StringGridPins->Row;
        }
else if (Key == VK_F1)
        {
        Disable_ENTER = true;
        Form1->Timer1->Enabled = false;
        AnsiString T = Form1->StringGridPins->Cells[def_Pin][StringGridPinsRowIndex];
        int ip = T.Pos(".");
        if(ip>0){
                 if (JUMP(T.SubString(1,ip-1)))
                         {
                         Wind = FindWindow(NULL, WindowHeader.c_str());
                         if (Wind) SetForegroundWindow(Wind);
                         Sleep(Pause);
                         KEYS ("F1", 1,1, Pause, 1);
                         }
                }
        Disable_ENTER = false;
        Form1->Timer1->Enabled = true;
        }
else if (Key == VK_F2)
        {
        /*Disable_ENTER = true;
        Form1->Timer1->Enabled = false;
        if (JUMP(Form1->StringGridPins->Cells[def_Pin][Form1->StringGridPins->Row]))
                {
                Wind = FindWindow(NULL, WindowHeader.c_str());
                if (Wind) SetForegroundWindow(Wind);
                Sleep(Pause);
                KEYS ("F2", 1,1, Pause, 1);
                }
        Disable_ENTER = false;
        Form1->Timer1->Enabled = true; */
        }
else if (Key == VK_F4)
        {
        Disable_ENTER = true;
        Form1->Timer1->Enabled = false;
        MOVE(Form1->StringGridPins->Cells[def_Pin][Form1->StringGridPins->Row]);
        Disable_ENTER = false;
        Form1->Timer1->Enabled = true;
        Form1->StringGridPins->SetFocus();
        }
Form1->StringGridPins->Refresh();
}
//---------------------------------------------------------------------------



void __fastcall TForm1::WPinMinKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if (Key == VK_DOWN)             Form1->StringGridPins->SetFocus();
else if (Key == VK_LEFT)        Form1->CType->SetFocus();
else if (Key == VK_RIGHT)       Form1->WPinMax->SetFocus();
else FilterAll();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::WPinMaxKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if (Key == VK_DOWN)             Form1->StringGridPins->SetFocus();
else if (Key == VK_LEFT)        Form1->WPinMin->SetFocus();
else if (Key == VK_RIGHT)       Form1->LPinMin->SetFocus();
else FilterAll();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::LPinMinKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if (Key == VK_DOWN)             Form1->StringGridPins->SetFocus();
else if (Key == VK_LEFT)        Form1->WPinMax->SetFocus();
else if (Key == VK_RIGHT)       Form1->LPinMax->SetFocus();
else FilterAll();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::LPinMaxKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if (Key == VK_DOWN)             Form1->StringGridPins->SetFocus();
else if (Key == VK_LEFT)        Form1->LPinMin->SetFocus();
else if (Key == VK_RIGHT)       Form1->DHoleMin->SetFocus();
else FilterAll();
}
//---------------------------------------------------------------------------



void __fastcall TForm1::XPinMinKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if (Key == VK_DOWN)             Form1->StringGridPins->SetFocus();
else if (Key == VK_LEFT)        Form1->DHoleMax->SetFocus();
else if (Key == VK_RIGHT)       Form1->XPinMax->SetFocus();
else FilterAll();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::XPinMaxKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if (Key == VK_DOWN)             Form1->StringGridPins->SetFocus();
else if (Key == VK_LEFT)        Form1->XPinMin->SetFocus();
else if (Key == VK_RIGHT)       Form1->YPinMin->SetFocus();
else FilterAll();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::YPinMinKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if (Key == VK_DOWN)             Form1->StringGridPins->SetFocus();
else if (Key == VK_LEFT)        Form1->XPinMax->SetFocus();
else if (Key == VK_RIGHT)       Form1->YPinMax->SetFocus();
else FilterAll();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::YPinMaxKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if (Key == VK_DOWN)             Form1->StringGridPins->SetFocus();
else if (Key == VK_LEFT)        Form1->YPinMin->SetFocus();
else FilterAll();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CTrmlChange(TObject *Sender)
{
FilterAll();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CTypeChange(TObject *Sender)
{
FilterAll();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CNetNetlistChange(TObject *Sender)
{
FilterAll();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::CPinChange(TObject *Sender)
{
AnsiString str = Form1->CPinNetPCB->Text;
if (str.Length())
        if (str.SubString(str.Length()-1,2) == dSPACE)
                Form1->CPinNetPCB->Text = "";
Form1->TFilterAll->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CPinKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if (Key == VK_RETURN)
        {
        Disable_ENTER = true;
        Form1->Timer1->Enabled = false;
        JUMP(Form1->StringGridPins->Cells[def_Pin][Form1->StringGridPins->Row]);
        Disable_ENTER = false;
        Form1->Timer1->Enabled = true;
        }
else if (Key == VK_F1)
        {
        Disable_ENTER = true;
        Form1->Timer1->Enabled = false;
        if (JUMP(Form1->StringGridPins->Cells[def_Pin][Form1->StringGridPins->Row]))
                {
                Wind = FindWindow(NULL, WindowHeader.c_str());
                if (Wind) SetForegroundWindow(Wind);
                Sleep(Pause);
                KEYS ("F1", 1,1, Pause, 1);
                }
        Disable_ENTER = false;
        Form1->Timer1->Enabled = true;
        }
else if (Key == VK_F2)
        {
        Disable_ENTER = true;
        Form1->Timer1->Enabled = false;
        if (JUMP(Form1->StringGridPins->Cells[def_Pin][Form1->StringGridPins->Row]))
                {
                Wind = FindWindow(NULL, WindowHeader.c_str());
                if (Wind) SetForegroundWindow(Wind);
                Sleep(Pause);
                KEYS ("F2", 1,1, Pause, 1);
                }
        Disable_ENTER = false;
        Form1->Timer1->Enabled = true;
        }
//VK_ESCAPE
else if (Key == VK_ESCAPE)
        {
        if( Form2->OnTheRight->Checked == 0 )
                Form1->Height = Form1_Height;
        SetFormComponentsSizes(false);
        Wind = FindWindow(NULL, WindowHeader.c_str());
        SetForegroundWindow(Wind);
        }
else if (Key == VK_F4)
        {
        Disable_ENTER = true;
        Form1->Timer1->Enabled = false;
        MOVE(Form1->StringGridPins->Cells[def_Pin][Form1->StringGridPins->Row]);
        Disable_ENTER = false;
        Form1->Timer1->Enabled = true;
        }
else if (Key == VK_DOWN)
        {
        if (!FlagSaveFilter)
                {
                Form1->StringGridPins->SetFocus();
                }
        }
}
//---------------------------------------------------------------------------






void __fastcall TForm1::CNetNetlistClick(TObject *Sender)
{
if (Form2->OnlyLatin->Checked == true) LoadKeyboardLayout("00000409", KLF_ACTIVATE);	//английская раскладка
if (Form1->CNetNetlist->Text.Length() == 0)
        Form1->CNetNetlist->Text = "Changes";
Form1->CNetNetlist->SelectAll();
}
//---------------------------------------------------------------------------








void __fastcall TForm1::CPinDblClick(TObject *Sender)
{
if (Form2->OnlyLatin->Checked == true) LoadKeyboardLayout("00000409", KLF_ACTIVATE);	//английская раскладка
if (Form1->CPin->Text.Length() == 0) Form1->CPin->Text = "Via";
Form1->CPin->SelectAll();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StringGridPinsMouseWheelDown(TObject *Sender,
      TShiftState Shift, TPoint &MousePos, bool &Handled)
{
if( Form1->StringGridPins->Row < Form1->StringGridPins->RowCount-1 )
        {
        StringGridPinsRowIndex = Form1->StringGridPins->Row+1;
        }
Form1->StringGridPins->SetFocus();
StringGridPins->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StringGridPinsMouseWheelUp(TObject *Sender,
      TShiftState Shift, TPoint &MousePos, bool &Handled)
{
if( Form1->StringGridPins->Row > 0 )
        {
        Form1->StringGridPins->SetFocus();
        StringGridPinsRowIndex = Form1->StringGridPins->Row-1;
        Form1->StringGridPins->Refresh();
        }
else
        Form1->CPin->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CPinClick(TObject *Sender)
{
Form1->Caption = "Infobox";
if (Form2->OnlyLatin->Checked == true)
        LoadKeyboardLayout("00000409", KLF_ACTIVATE);	//английская раскладка
}
//---------------------------------------------------------------------------








void __fastcall TForm1::StringGridPinsContextPopup(TObject *Sender,
      TPoint &MousePos, bool &Handled)
{
MousDblClick = false;
Form1->VP_popup->Enabled = false;
Form1->CP_popup->Enabled = false;
if (NetListPath.Length())
        Form1->LN_popup->Enabled = true;
else    Form1->LN_popup->Enabled = false;
if (FileName.Length())
        {
        Form1->RF_popup->Enabled = true;
        Form1->PF_popup->Enabled = true;
        Form1->EX_popup->Enabled = true;
        Form1->TXT_popup->Enabled = true;
        Form1->CSC_popup->Enabled = true;
        Form1->HA_popup->Enabled = true;
        }
else    {
        Form1->RF_popup->Enabled = false;
        Form1->PF_popup->Enabled = false;
        Form1->EX_popup->Enabled = false;
        Form1->TXT_popup->Enabled = false;
        Form1->CSC_popup->Enabled = false;
        Form1->HA_popup->Enabled = false;
        }
}
//---------------------------------------------------------------------------



void __fastcall TForm1::LN_popupClick(TObject *Sender)
{
if (FileName.Length())
if (NetListPath.Length())
        {
        Form1->Timer1->Enabled = false;
        if( NetListPath.SubString(1,1) != "#" )
                NetListPath = "#" + NetListPath;
        FRead_File = TRUE_TRUE;
        Form1->Timer1->Enabled = true;
        }
}
//---------------------------------------------------------------------------

void ResetFilter(bool bClearSearchConsole)
{
// Reset filter
if( !bClearSearchConsole )
        Form1->Deleted->Items->Clear();
Form1->CRefDes->Text = "*";     //  To call a function FilterAll()
Form1->CRefDes->Text = "";
Form1->MinRI->Text = "";
Form1->MaxRI->Text = "";
Form1->CValue->Text = "";
Form1->CPackage->Text = "";
Form1->CValueNL->Text = "";
Form1->CPackageNL->Text = "";
Form1->CFootPrint->Text = "";
Form1->CMerge->Text = "";
Form1->CMerge->ItemIndex = -1;
Form1->MinPin->Text = "";
Form1->MaxPins->Text = "";
Form1->MinHoles->Text = "";
Form1->MaxHoles->Text = "";
Form1->Glueds->Text = "";
Form1->Side->Text = "";
Form1->Ang->Text = "";
Form1->EXmin->Text = "";
Form1->EXmax->Text = "";
Form1->EYmin->Text = "";
Form1->EYmax->Text = "";
Form1->CCNetlist->Text = "";
Form1->CCNetlist->ItemIndex = -1;
//
Form1->CType->Text = "";
Form1->CType->ItemIndex = -1;
Form1->CTrml->Text = "";
Form1->CTrml->ItemIndex = -1;
Form1->CPin->Text = "*";   //  To call a function FilterAll()
Form1->CPin->Text = "";
Form1->CPinNetPCB->Text = "";
Form1->CCnt->Text = "";
Form1->CCnt->ItemIndex = -1;
Form1->CNetNetlist->Text = "";
Form1->WPinMin->Text = "";
Form1->WPinMax->Text = "";
Form1->LPinMin->Text = "";
Form1->LPinMax->Text = "";
Form1->DHoleMin->Text = "";
Form1->DHoleMin->ItemIndex = -1;
Form1->DHoleMax->Text = "";
Form1->DHoleMax->ItemIndex = -1;
Form1->Pas->Text = "";
Form1->XPinMin->Text = "";
Form1->XPinMax->Text = "";
Form1->YPinMin->Text = "";
Form1->YPinMax->Text = "";
Form1->Caption = "Infobox";
// Combobox

}
//---------------------------------------------------------------------------

FixFilteredParts()
{
for( int i=0; i<Form1->DataParts->Items->Count; i+=PartsColCount+1 )
        {
        AnsiString S = Form1->DataParts->Items->operator [](i+col_RefDes+1);
        if( Form1->StringGridParts->Cols[def_RefDes]->IndexOf(S) == -1 )
                if( Form1->Deleted->Items->IndexOf(S) == -1 )
                        Form1->Deleted->Items->Add(S);
        }
ResetFilter(true);
}
//---------------------------------------------------------------------------

void CCnlistRefresh()
{
Form1->CCNetlist->Text = "";
Form1->CCNetlist->Items->Clear();
if (Form2->Language->Checked)
        {
        if( Form1->StringGridParts->Cols[def_CompareNetlist]->IndexOf("Только_на_плате") >= 0 )
                Form1->CCNetlist->Items->Add("Только_на_плате");
        if( Form1->StringGridParts->Cols[def_CompareNetlist]->IndexOf("Только_в_нетлисте") >= 0 )
                Form1->CCNetlist->      Items->Add("Только_в_нетлисте");
        if( Form1->StringGridParts->Cols[def_CompareNetlist]->IndexOf("Всё_совпадает") >= 0 )
                Form1->CCNetlist->      Items->Add("Всё_совпадает");
        if( Form1->StringGridParts->Cols[def_CompareNetlist]->IndexOf("Футпринт_только") >= 0 )
                Form1->CCNetlist->      Items->Add("Футпринт_только");
        if( Form1->StringGridParts->Cols[def_CompareNetlist]->IndexOf("Значение_только") >= 0 )
                Form1->CCNetlist->      Items->Add("Значение_только");
        if( Form1->StringGridParts->Cols[def_CompareNetlist]->IndexOf("Футпринт_Значение") >= 0 )
                Form1->CCNetlist->      Items->Add("Футпринт_Значение");
        Form1->CCNetlist->Items->Add("Загрузить нетлист...");
        Form1->CCNetlist->Items->Add("Загрузить партлист...");
        }
else    {
        if( Form1->StringGridParts->Cols[def_CompareNetlist]->IndexOf("Only_on_the_Board") >= 0 )
                Form1->CCNetlist->      Items->Add("Only_on_the_Board");
        if( Form1->StringGridParts->Cols[def_CompareNetlist]->IndexOf("Only_in_netlist") >= 0 )
                Form1->CCNetlist->      Items->Add("Only_in_netlist");
        if( Form1->StringGridParts->Cols[def_CompareNetlist]->IndexOf("All_matches") >= 0 )
                Form1->CCNetlist->      Items->Add("All_matches");
        if( Form1->StringGridParts->Cols[def_CompareNetlist]->IndexOf("Footprint_only") >= 0 )
                Form1->CCNetlist->      Items->Add("Footprint_only");
        if( Form1->StringGridParts->Cols[def_CompareNetlist]->IndexOf("Value_only") >= 0 )
                Form1->CCNetlist->      Items->Add("Value_only");
        if( Form1->StringGridParts->Cols[def_CompareNetlist]->IndexOf("Footprint_Value") >= 0 )
                Form1->CCNetlist->      Items->Add("Footprint_Value");
        Form1->CCNetlist->Items->Add("Load Netlist...");
        Form1->CCNetlist->Items->Add("Load Partlist...");
        }
Form1->CCNetlist->ItemIndex = -1;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RF_popupClick(TObject *Sender)
{
ResetFilter(true);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PF_popupClick(TObject *Sender)
{
AnsiString command = ExtractFilePath(FileName);
ProgExecute (command.SubString(1,(command.Length()-1)));
}
//---------------------------------------------------------------------------

int RStorage(  AnsiString PATH )
{
FILE* F;
F = fopen(PATH.c_str(),"rb+");
if(!F)  {
        fclose(F);
        ofstream create_file (PATH.c_str());
        create_file.close();
        }
else    {
        fclose(F);
        // reading  *.vpl
        ifstream values (PATH.c_str());
        while (!values.eof())
                {
                values.getline(s,2500);
                AnsiString str = s;
                if (str.Length())
                        Form1->Values->Items->Add(str);
                }
        values.close();
        }
return Form1->Values->Items->Count;
}


void Save_Values_Packages( AnsiString PATH )
{
CreateDirectory(PATH.c_str(),NULL);
ofstream r_values;
AnsiString P = ExtractFileName(FileName);
P = P.SubString(1,P.Length()-3) + "vpl";
PATH += P;
r_values.open(PATH.c_str());
AnsiString command;
AnsiString Bstr;
Form1->Values->Items->Clear();
for (int q=0; q<Form1->StringGridParts->RowCount; q++)
        {
        command = Form1->StringGridParts->Cells[def_Value][q];
        command = command.Trim();
        Bstr = Form1->StringGridParts->Cells[def_Package][q];
        if( Bstr.Length() == 0 || Bstr.SubString(1,3) == EMP )
                Bstr = Form1->StringGridParts->Cells[def_FootPrint][q];
        if( Bstr.Length() == 0 || Bstr.SubString(1,3) == EMP )
                continue;
        Bstr = Bstr.Trim();
        //
        if( command.Length() < 8 )
                command += "\t\t";
        else    command += "\t";
        command += Bstr;
        if( Bstr.Length() < 8 )
                command += "\t\t";
        else    command += "\t";
        //
        AnsiString Ccommand = command;
        for( int pp=command.Pos("."); pp>0; pp=command.Pos(".") )
                {
                command.Delete(pp,1);
                command.Insert(",",pp);
                }
        int CL = command.Length();
        if (CL > 4)
                {
                bool yes = 1;
                for( int ind=0; ind<Form1->Values->Items->Count; ind++ )
                        {
                        AnsiString V_STR = Form1->Values->Items->operator [](ind);
                        V_STR = V_STR.SubString(1,CL);
                        for( int pp=V_STR.Pos("."); pp>0; pp=V_STR.Pos(".") )
                                {
                                V_STR.Delete(pp,1);
                                V_STR.Insert(",",pp);
                                }
                        if( V_STR.SubString(1,CL) == command.SubString(1,CL) )
                                {
                                yes = 0;
                                break;
                                }
                        }
                if( yes )
                        {
                        Ccommand += P;
                        r_values << Ccommand.c_str() << endl;
                        Form1->Values->Items->Add(Ccommand);
                        }
                }
        }
r_values.close();
ReadingStorages();
command = ExtractFilePath(PATH);
Bstr =  PATH;
/*if ((UINT)ShellExecute(NULL,
               "open",
               Bstr.c_str(),
               NULL,
               command.c_str() ,
               SW_SHOWNORMAL) <=32)
               {ShowMessage  ("     File " + Bstr + " not found!"); return;} */
}


void __fastcall TForm1::EX_popupClick(TObject *Sender)
{
// Excel
AnsiString STR, Bstr, str;
str = ExtractFilePath(FileName) + "related_files\\infobox\\" + ExtractFileName(FileName) + ".csv";
ofstream CSV (str.c_str());
CSV << AnsiString("Project:;" + FileName + ";").c_str() << endl;
n = 0;
long istr = 0;
Form1->SortedBox->Sorted = true;
if (Form1->PageControl1->TabIndex == 0)
        {
        Form1->SortedBox->Clear();
        CSV << "Num;";
        for (int ncol=0; ncol<PartsColCount; ncol++)
                {
                if(Form1->StringGridParts->ColWidths[ncol])
                        {
                        for( int ii=0; ii<PartsColCount; ii++ )
                                {
                                if( PartColOrder[ii] == ncol )
                                        {
                                        A = ColNames[ii];
                                        CSV << A.c_str();
                                        CSV << ";";
                                        }
                                }
                        }
                }
        CSV << endl;
        int CNT = 1;
        AnsiString VALUE, PACK;
        Form1->SortedBox->Items->Clear();
        while (istr < Form1->StringGridParts->RowCount)
                {
               CSV << (istr+1);
               CSV << ";";
               VALUE = Form1->StringGridParts->Cells[def_Value][istr].c_str();
               PACK = Form1->StringGridParts->Cells[def_Package][istr].c_str();
               VALUE = PACK + " @ " + VALUE + " @@ " + Form1->StringGridParts->Cells[def_RefDes][istr];
               Form1->SortedBox->Items->Add(VALUE);
               Form1->SortedBox->Items->Add(DOG + PACK);
               for (int ncol=0; ncol<PartsColCount; ncol++)
                        {
                        if(Form1->StringGridParts->ColWidths[ncol])
                                {
                                A = Form1->StringGridParts->Cells[ncol][istr];
                                if( ncol == def_Ang || ncol == def_Xprt || ncol == def_Yprt )
                                        {
                                        int p = A.Pos(".");
                                        if (p > 0)
                                                A[p] = ',';
                                        }
                                CSV << A.c_str();
                                CSV << ";";
                                }
                        }
               CSV << endl;
               istr++;
                }
        AnsiString Back = "";
        CNT = 1;
        int L;
        if (Form1->SortedBox->Count)
                {
                //-----"Package & Count"--------
                CSV << ";" << endl;
                CSV << "Package;Count;" << endl;
                int first = -1;
                for (int t=0; t<Form1->SortedBox->Count; t++)
                        {
                        STR = Form1->SortedBox->Items->operator [](t);
                        if (STR.SubString(1,1) != DOG)
                                continue;
                        if( first == -1 )
                                first = t;
                        L = STR.Length();
                        if (Back.SubString(1,L) == STR.SubString(1,L))
                                CNT++;
                        else    {
                                if (t > first)
                                        CSV << (AnsiString(CNT) + ";").c_str() << endl;
                                CSV << (STR.SubString(2,(L-1)) + ";").c_str();
                                CNT = 1;
                                }
                        Back = STR.SubString(1,L);
                        }
                CSV << (AnsiString(CNT) + ";").c_str() << endl;
                CSV << ";" << endl;
                CSV << ";" << endl;
                //
                //-----"Package & Value & Count"--------
                //
                CSV << "Package;Value;Count;" << endl;
                CNT = 1;
                Back = "";
                int start = 0;
                for (int t=0; t<Form1->SortedBox->Count; t++)
                        {
                        //
                        STR = Form1->SortedBox->Items->operator [](t);
                        if (STR.SubString(1,1) == DOG)
                                continue;
                        int pos = STR.Pos(" @@ ");
                        if (pos>0)
                                {
                                if (Back.SubString(1,pos) == STR.SubString(1,pos))
                                        CNT++;
                                else    {
                                        if (start)
                                                CSV << (AnsiString(CNT) + ";").c_str() << endl;
                                        start = 1;
                                        int p = STR.Pos(" @ ");
                                        if (p > 0)
                                                {
                                                CSV << (STR.SubString(1,(p-1)) + ";").c_str();
                                                CSV << (STR.SubString((p+2),(pos-p-1)) + ";").c_str();
                                                }
                                        CNT = 1;
                                        }
                                }
                        Back = STR.SubString(1,pos);
                        }
                CSV << (AnsiString(CNT) + ";").c_str() << endl;
                CSV << ";" << endl;
                CSV << ";" << endl;
                //
                //-----"Package & Value & Ref & Count"--------
                //
                CSV << "Package;Value;Ref;Count;" << endl;
                CNT = 1;
                start = 0;
                Back = "";
                for (int t=0; t<Form1->SortedBox->Count; t++)
                        {
                        STR = Form1->SortedBox->Items->operator [](t);
                        if (STR.SubString(1,1) == DOG)
                                continue;
                        L = STR.Pos(" @@ ");
                        if (L>0)
                                {
                                if (Back.SubString(1,L) == STR.SubString(1,L))
                                        {
                                        CNT++;
                                        CSV << (" " + STR.SubString(L+4,(STR.Length()-L-3))).c_str();
                                        }
                                else    {
                                        if (start)
                                                CSV << (";" + AnsiString(CNT) + ";").c_str() << endl;
                                        start = 1;
                                        int p = STR.Pos(" @ ");
                                        if (p > 0)
                                                {
                                                CSV << (STR.SubString(1,(p-1)) + ";").c_str();
                                                CSV << (STR.SubString((p+2),(L-p-1)) + ";").c_str();
                                                CSV << (STR.SubString(L+4,(STR.Length()-L-3))).c_str();
                                                }
                                        CNT = 1;
                                        }
                                }
                        Back = STR.SubString(1,L);
                        }
                CSV << (";" + AnsiString(CNT) + ";").c_str() << endl;
                }
        }
else if (Form1->PageControl1->TabIndex == 1)
        {
        CSV << "Num;";
        if(Form2->check_pinname->Checked)
                CSV << (Form1->BPin->Caption + ";").c_str();
        if(Form2->check_pinname->Checked)
                CSV << (Form1->BPin->Caption + ";").c_str();
        if(Form2->check_pinname->Checked)
                CSV << (Form1->BPin->Caption + ";").c_str();
        if(Form2->check_pinname->Checked)
                CSV << (Form1->BPin->Caption + ";").c_str();
        if(Form2->check_pinname->Checked)
                CSV << (Form1->BPin->Caption + ";").c_str();
        if(Form2->check_pinname->Checked)
                CSV << (Form1->BPin->Caption + ";").c_str();
        if(Form2->check_pinname->Checked)
                CSV << (Form1->BPin->Caption + ";").c_str();
        if(Form2->check_pinname->Checked)
                CSV << (Form1->BPin->Caption + ";").c_str();
        if(Form2->check_pinname->Checked)
                CSV << (Form1->BPin->Caption + ";").c_str();
        if(Form2->check_pinname->Checked)
                CSV << (Form1->BPin->Caption + ";").c_str();
        if(Form2->check_pinname->Checked)
                CSV << (Form1->BPin->Caption + ";").c_str();
        while (istr < Form1->StringGridPins->RowCount)
                {
               CSV << (istr+1);
               CSV << ";";
               STR = Form1->StringGridPins->Cells[def_Pin][istr];
               STR = StringReplace(STR,".","-",TReplaceFlags()<<rfReplaceAll);
               CSV << STR.c_str();
               CSV << ";";
               CSV << ":";
               CSV << Form1->StringGridPins->Cells[def_NetPcb][istr].c_str();
               CSV << ";";
               CSV << ":";
               CSV << Form1->StringGridPins->Cells[def_Netlist][istr].c_str();
               CSV << ";";
               CSV << Form1->StringGridPins->Cells[def_Type][istr].c_str();
               CSV << ";";
               CSV << Form1->StringGridPins->Cells[def_W][istr].c_str();
               CSV << ";";
               CSV << Form1->StringGridPins->Cells[def_L][istr].c_str();
               CSV << ";";
               CSV << Form1->StringGridPins->Cells[def_Thrml][istr].c_str();
               CSV << ";";
               CSV << Form1->StringGridPins->Cells[def_DHole][istr].c_str();
               CSV << ";";
               CSV << Form1->StringGridPins->Cells[def_Xpi][istr].c_str();
               CSV << ";";
               CSV << Form1->StringGridPins->Cells[def_Ypi][istr].c_str();
               CSV << ";" << endl;
               istr++;
                }
        }
CSV.close();
Sleep(300);
if ((UINT)ShellExecute(NULL,
       "open",
       str.c_str(),
       NULL,
       ExtractFilePath(str).c_str() ,
       SW_SHOWNORMAL) <=32)
       {ShowMessage  ("     File " + str + " not found!"); return;}
}
//---------------------------------------------------------------------------


void __fastcall TForm1::ST_popupClick(TObject *Sender)
{
// Settings
Form1->Timer1->Enabled = false;
Form2->Visible = true;
}
//---------------------------------------------------------------------------




void __fastcall TForm1::CP_popupClick(TObject *Sender)
{
Save_Values_Packages(ExtractFilePath(FileName)+"related_files\\infobox\\");
PathProg = PathProg + "FreePCB_Compare\\Fpc_Compare.exe";
ProgExecute(PathProg);
bEditKITMess = true;
}
//---------------------------------------------------------------------------







void __fastcall TForm1::EP_popupClick(TObject *Sender)
{
PathProg = PathProg + "FreePCB_EditPins\\EditPins.exe";
ProgExecute(PathProg);
bEditPinsMess = true;
}
//---------------------------------------------------------------------------




void __fastcall TForm1::FA_popupClick(TObject *Sender)
{
PathProg = PathProg + "FreePCB_Areas\\Areas.exe";
ProgExecute(PathProg);
}
//---------------------------------------------------------------------------



void __fastcall TForm1::NE_popupClick(TObject *Sender)
{
PathProg = PathProg + "FreePCB_Nets\\Nets.exe";
ProgExecute(PathProg);
}
//---------------------------------------------------------------------------



void __fastcall TForm1::DHoleMinChange(TObject *Sender)
{
FilterAll();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DHoleMaxChange(TObject *Sender)
{
FilterAll();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DHoleMinKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if (Key == VK_DOWN)             Form1->StringGridPins->SetFocus();
else if (Key == VK_LEFT)        Form1->LPinMax->SetFocus();
else if (Key == VK_RIGHT)       Form1->DHoleMax->SetFocus();
///else FilterAll();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DHoleMaxKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if (Key == VK_DOWN)             Form1->StringGridPins->SetFocus();
else if (Key == VK_LEFT)        Form1->DHoleMin->SetFocus();
else if (Key == VK_RIGHT)       Form1->XPinMin->SetFocus();

}
//---------------------------------------------------------------------------



int __fastcall TForm1::OnWMCopyData(TWMCopyData &Msg)
{
        AnsiString str = (char*)Msg.CopyDataStruct->lpData;
        if( str.SubString(1,15) == "paste_from_file" )
                {
                Paste_area = ExtractFilePath(Application->ExeName);
                Paste_area = Paste_area.SubString(1,(Paste_area.Length()-1));
                Paste_area = ExtractFilePath(Paste_area);
                Paste_area += "FreePCB_Areas\\OnlyAreas.fpc";
                FreePCBPaste(Paste_area, 0, 0, UNITS);
                Paste_area = "";
                }
        else if( str.SubString(1,9) == "part_list" )
                {
                AnsiString MessageText = str.SubString( 11,(str.Length()-10) );
                MessageText = MessageText.TrimRight();
                if( MessageText.Length() == 0 )
                        {
                        if( Form1->PageControl1->TabIndex == 0 )
                                {
                                if(Form1->CRefDes->Text.Length()==0)
                                        {
                                        }
                                else if(Form1->CRefDes->Text.SubString(Form1->CRefDes->Text.Length()-1,2) == dSPACE)
                                        Form1->CRefDes->Text = "";
                                }
                        else if( Form1->PageControl1->TabIndex == 1 )
                                {
                                if(Form1->CPin->Text.Length() < 2)
                                        {
                                        }
                                else if(Form1->CPin->Text.SubString(Form1->CPin->Text.Length()-1,2) == dSPACE)
                                        {
                                        Form1->CPin->Text = "";
                                        }
                                if(Form1->CPinNetPCB->Text.Length()==0)
                                        {
                                        }
                                else if(Form1->CPinNetPCB->Text.SubString(Form1->CPinNetPCB->Text.Length()-1,2) == dSPACE)
                                        {
                                        Form1->CPinNetPCB->Text = "";
                                        Form1->CPinNetPCB->ItemIndex = -1;
                                        Form1->TFilterAll->Enabled = true;
                                        }
                                }
                        }
                else    {
                        long p1 = MessageText.Pos(".");
                        if( Form1->PageControl1->TabIndex == 0 )
                                {
                                AnsiString RefDesText = CRefDes->Text;
                                if( p1 > 0 )
                                        MessageText = MessageText.SubString(1,p1-1);
                                int ii = RefDesText.Length();
                                if (ii == 0)
                                        {
                                        CRefDes->Text = MessageText+dSPACE;
                                        }
                                else if( RefDesText.SubString(ii-1,2) == dSPACE )
                                        {
                                        CRefDes->Text = MessageText+dSPACE;
                                        }
                                }
                        else if( Form1->PageControl1->TabIndex == 1 )
                                {
                                AnsiString CPinText = CPin->Text;
                                int plen = CPinText.Length();
                                AnsiString CPinNetPCBText = CPinNetPCB->Text;
                                int ilen = CPinNetPCBText.Length();
                                if( p1 <= 0 )
                                        {
                                        p1 = MessageText.Pos(" ");
                                        if ( p1 <= 0 )
                                                {
                                                if( plen == 0 )
                                                        CPin->Text = MessageText+dSPACE;
                                                else if( CPinText.SubString(plen-1,2) == dSPACE )
                                                        CPin->Text = MessageText+dSPACE;
                                                // clear net name if dSPACE
                                                if(ilen == 0){;}
                                                else if(CPinNetPCBText.SubString(ilen-1,2) == dSPACE )
                                                        {
                                                        Form1->CPinNetPCB->Text = "";
                                                        CPinNetPCB->ItemIndex = -1;// Text = "";
                                                        //
                                                        Form1->TFilterAll->Enabled = true;
                                                        }
                                                }
                                        }
                                else    {
                                        p1 = MessageText.Pos(" ");
                                        if( p1 > 0 )
                                                {
                                                // clear pin name if dSPACE
                                                if(plen == 0){;}
                                                else if( CPinText.SubString(plen-1,2) == dSPACE )
                                                        Form1->CPin->Text = "";
                                                long p2 = p1;
                                                //
                                                if(ilen == 0)
                                                        CPinNetPCB->Text = ex_str( MessageText,&p2 )+dSPACE;
                                                else if( CPinNetPCBText.SubString(ilen-1,2) == dSPACE )
                                                        CPinNetPCB->Text = ex_str( MessageText,&p2 )+dSPACE;
                                                if( plen == 0 )
                                                        GlobalPinText = MessageText.SubString(1,p1-1)+dSPACE;
                                                else if( CPinText.SubString(plen-1,2) == dSPACE )
                                                        GlobalPinText = MessageText.SubString(1,p1-1)+dSPACE;
                                                //
                                                Form1->TFilterAll->Enabled = true;
                                                }
                                        }
                                }
                        }
                }
        else    {
                Form1->Visible = true;
                if( str.SubString(1,str.Length()) == FileNameBack.SubString(1,FileNameBack.Length()) )
                        FileName = FileNameBack;
                else if( str.SubString(1,str.Length()) != FileName.SubString(1,FileName.Length()) )
                        {
                        FileName = str;
                        FRead_File = FALSE_FALSE;
                        }
                }
        return 1;
}

//---------------------------------------------------------------------------
void __fastcall TForm1::CPinNetPCBChange(TObject *Sender)
{
FilterAll();
//Form1->TFilterAll->Enabled = true;
}

//---------------------------------------------------------------------------

void __fastcall TForm1::PasChange(TObject *Sender)
{
FilterAll();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::SaveFilter1Click(TObject *Sender)
{
SaveFilter(col_RefDes);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SaveFilter2Click(TObject *Sender)
{
SaveFilter(col_Value);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SaveFilter3Click(TObject *Sender)
{
SaveFilter(col_Package);
}
//---------------------------------------------------------------------------






void __fastcall TForm1::HA_popupClick(TObject *Sender)
{
HighlightAll();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::TXT_popupClick(TObject *Sender)
{
AnsiString str = ExtractFilePath(FileName) + "related_files\\infobox\\" + ExtractFileName(FileName) + ".txt";
ofstream TXT ( str.c_str());
AnsiString H = ("Project: " + FileName);
TXT << H.c_str() << endl;
for( int ii=0; ii<H.Length(); ii++ )
        TXT << "=";
TXT << endl;
TXT << endl;
TXT << "This file contains a list of filtered INFOBOX parts," << endl;
TXT << "and a bill of materials. The part angles in the table" << endl;
TXT << "are given according to the settings of the FREEPCB " << endl;
TXT << "report file (see File -> Generate report file ...)" << endl;
TXT << endl;
n = 0;
Form1->SortedBox->Sorted = true;
//#define max_num 8
if (Form1->PageControl1->TabIndex == 0)
        {
        int     max[PartsColCount];
        for( int ii=0; ii<PartsColCount; ii++ )
                max[PartColOrder[ii]] = ColNames[ii].Length()+2;
        for (int scan=0; scan<Form1->StringGridParts->RowCount; scan++)
                {
                for (int col=0; col<PartsColCount; col++)
                        max[col] = MAX(max[col],(Form1->StringGridParts->Cells[col][scan].Length()+2));
                }
        //TXT << "№";
        //for(int sp=1; sp<max_num; sp++)
        //        TXT << " ";
        for (int ncol=0; ncol<PartsColCount; ncol++)
                {
                if(Form1->StringGridParts->ColWidths[ncol])
                        {
                        for( int ii=0; ii<PartsColCount; ii++ )
                                {
                                if( PartColOrder[ii] == ncol )
                                        {
                                        A = ColNames[ii];
                                        TXT << A.c_str();
                                        for(int sp=A.Length(); sp<max[ncol]; sp++)
                                                TXT << " ";
                                        }
                                }
                        }
                }
        TXT << endl;
        AnsiString VALUE, PACK;
        Form1->SortedBox->Items->Clear();
        for (int istr=0; istr<Form1->StringGridParts->RowCount; istr++)
                {
                //A = AnsiString(istr+1);
                //TXT << A.c_str();
                //for(int sp=A.Length(); sp<max_num; sp++)
                //        TXT << " ";
                VALUE = Form1->StringGridParts->Cells[def_Value][istr].c_str();
                PACK = Form1->StringGridParts->Cells[def_Package][istr].c_str();
                VALUE = PACK + " @ " + VALUE + " @@ " + Form1->StringGridParts->Cells[def_RefDes][istr];
                Form1->SortedBox->Items->Add(VALUE);
                Form1->SortedBox->Items->Add(DOG + PACK);
                for (int ncol=0; ncol<PartsColCount; ncol++)
                        {
                        if(Form1->StringGridParts->ColWidths[ncol])
                                {
                                A = Form1->StringGridParts->Cells[ncol][istr];
                                if( ncol == def_Ang || ncol == def_Xprt || ncol == def_Yprt )
                                        {
                                        int p = A.Pos(",");
                                        if (p > 0)
                                                A[p] = '.';
                                        }
                                TXT << A.c_str();
                                for(int sp=A.Length(); sp<max[ncol]; sp++)
                                        TXT << " ";
                                }
                        }
                TXT << endl;
                }
        TXT << endl;
        TXT << "bill of materials" << endl;
        for( int ii=0; ii<H.Length(); ii++ )
                TXT << "=";
        if (Form1->SortedBox->Count)
                {
                AnsiString STR;
                //-----"Package & Count"--------
                AnsiString Back="";
                TXT << endl;
                int CNT = 1;
                int first = -1;
                max[0] = 10;
                for (int t=0; t<Form1->SortedBox->Count; t++)
                        {
                        STR = Form1->SortedBox->Items->operator [](t);
                        if (STR.SubString(1,1) != DOG)
                                continue;
                        int L = STR.Length()+1;
                        max[0] = MAX( max[0], L );
                        }
                TXT << "Package";
                for(int sp=7; sp<max[0]; sp++)
                        TXT << " ";
                TXT << "Count" << endl;
                for (int t=0; t<Form1->SortedBox->Count; t++)
                        {
                        STR = Form1->SortedBox->Items->operator [](t);
                        if (STR.SubString(1,1) != DOG)
                                continue;
                        if( first == -1 )
                                first = t;
                        int L = STR.Length();
                        if (Back.SubString(1,L) == STR.SubString(1,L))
                                CNT++;
                        else    {
                                if (t > first)
                                        TXT << (AnsiString(CNT)).c_str() << endl;
                                TXT << (STR.SubString(2,(L-1))).c_str();
                                for(int sp=L-1; sp<max[0]; sp++)
                                        TXT << " ";
                                CNT = 1;
                                }
                        Back = STR.SubString(1,L);
                        }
                TXT << (AnsiString(CNT)).c_str() << endl;
                TXT << endl;
                TXT << endl;
                //
                //-----"Package & Value & Count"--------
                //
                CNT = 1;
                int start = 0;
                Back="";
                max[0] = 10;
                max[1] = 8;
                max[2] = 6;
                for (int t=0; t<Form1->SortedBox->Count; t++)
                        {
                        //
                        STR = Form1->SortedBox->Items->operator [](t);
                        if (STR.SubString(1,1) == DOG)
                                continue;
                        int pos = STR.Pos(" @ ");
                        if (pos>0)
                                {
                                int L = pos+1;
                                max[0] = MAX( max[0], L );
                                int p = STR.Pos(" @@ ");
                                if (p > 0)
                                        {
                                        int L = p-pos-1;
                                        max[1] = MAX( max[1], L );
                                        max[2] = MAX( max[2], STR.Length()-p );
                                        }
                                }
                        }
                TXT << "Package";
                for(int sp=7; sp<max[0]; sp++)
                        TXT << " ";
                TXT << "Value";
                for(int sp=5; sp<max[1]; sp++)
                        TXT << " ";
                TXT << "Count" << endl;
                for (int t=0; t<Form1->SortedBox->Count; t++)
                        {
                        //
                        STR = Form1->SortedBox->Items->operator [](t);
                        if (STR.SubString(1,1) == DOG)
                                continue;
                        int pos = STR.Pos(" @@ ");
                        if (pos>0)
                                {
                                if (Back.SubString(1,Back.Length()) == STR.SubString(1,pos))
                                        CNT++;
                                else    {
                                        if (start)
                                                TXT << (AnsiString(CNT)).c_str() << endl;
                                        start = 1;
                                        int p = STR.Pos(" @ ");
                                        if (p > 0)
                                                {
                                                TXT << (STR.SubString(1,(p-1))).c_str();
                                                for(int sp=p; sp<max[0]; sp++)
                                                        TXT << " ";
                                                TXT << (STR.SubString((p+2),(pos-p-1))).c_str();
                                                for(int sp=pos-p-2; sp<max[1]; sp++)
                                                        TXT << " ";
                                                }
                                        CNT = 1;
                                        }
                                Back = STR.SubString(1,pos);
                                }
                        }
                TXT << (AnsiString(CNT)).c_str() << endl;
                TXT << endl;
                TXT << endl;
                //
                //-----"Package & Value & Ref & Count"--------
                //
                TXT << "Package";
                for(int sp=7; sp<max[0]; sp++)
                        TXT << " ";
                TXT << "Value";
                for(int sp=5; sp<max[1]; sp++)
                        TXT << " ";
                TXT << "Ref";
                for(int sp=4; sp<max[2]; sp++)
                        TXT << " ";
                TXT << "Count" << endl;
                CNT = 1;
                start = 0;
                Back = "";
                for (int t=0; t<Form1->SortedBox->Count; t++)
                        {
                        STR = Form1->SortedBox->Items->operator [](t);
                        if (STR.SubString(1,1) == DOG)
                                continue;
                        int L = STR.Pos(" @@ ");
                        if (L>0)
                                {
                                if (Back.SubString(1,L) == STR.SubString(1,L))
                                        {
                                        CNT++;
                                        TXT << endl;
                                        for(int sp=0; sp<(max[0]+max[1]); sp++)
                                                TXT << " ";
                                        TXT << (STR.SubString(L+4,(STR.Length()-L-3))).c_str();
                                        for(int sp=STR.Length()-L-2; sp<max[2]; sp++)
                                                TXT << " ";
                                        }
                                else    {
                                        if (start)
                                                TXT << (AnsiString(CNT)).c_str();
                                        if( CNT > 1 )
                                                TXT << endl;
                                        start = 1;
                                        int p = STR.Pos(" @ ");
                                        if (p > 0)
                                                {
                                                TXT << endl;
                                                TXT << (STR.SubString(1,(p-1))).c_str();
                                                for(int sp=p; sp<max[0]; sp++)
                                                        TXT << " ";
                                                TXT << (STR.SubString((p+2),(L-p-1))).c_str();
                                                for(int sp=L-p-2; sp<max[1]; sp++)
                                                        TXT << " ";
                                                TXT << (STR.SubString(L+4,(STR.Length()-L-3))).c_str();
                                                for(int sp=STR.Length()-L-2; sp<max[2]; sp++)
                                                        TXT << " ";
                                                }
                                        CNT = 1;
                                        }
                                }
                        Back = STR.SubString(1,L);
                        }
                TXT << (AnsiString(CNT)).c_str() << endl;
                }
        }
else if (Form1->PageControl1->TabIndex == 1)
        {
        int     max[PinsColCount];
        max[def_Pin] = Form1->BPin->Caption.Length()+2;
        max[def_NetPcb] = Form1->BPinNetPCB->Caption.Length()+2;
        max[def_Cnt] = Form1->BCnt->Caption.Length()+2;
        max[def_Netlist] = Form1->BPinNetList->Caption.Length()+2;
        max[def_Type] = Form1->BType->Caption.Length()+2;
        max[def_W] = Form1->BW->Caption.Length()+2;
        max[def_L] = Form1->BL->Caption.Length()+2;
        max[def_Thrml] = Form1->BTrml->Caption.Length()+2;
        max[def_DHole] = Form1->BDHole->Caption.Length()+2;
        max[def_Pas] = Form1->BPas->Caption.Length()+2;
        max[def_Xpi] = Form1->BXPin->Caption.Length()+2;
        max[def_Ypi] = Form1->BYPin->Caption.Length()+2;
        for (int scan=0; scan<Form1->StringGridPins->RowCount; scan++)
                {
                for (int col=0; col<PinsColCount; col++)
                        max[col] = MAX(max[col],(Form1->StringGridPins->Cells[col][scan].Length()+2));
                }
        //TXT << "№";
        //for(int sp=1; sp<max_num; sp++)
        //        TXT << " ";
        if(Form2->check_pinname->Checked)
                {
                TXT << Form1->BPin->Caption.c_str();
                for(int sp=Form1->BPin->Caption.Length(); sp<max[def_Pin]; sp++)
                        TXT << " ";
                }
        if(Form2->check_netpcb->Checked)
                {
                TXT << Form1->BPinNetPCB->Caption.c_str();
                for(int sp=Form1->BPinNetPCB->Caption.Length(); sp<max[def_NetPcb]; sp++)
                        TXT << " ";
                }
        if(Form2->check_pins_cnt->Checked)
                {
                TXT << Form1->BCnt->Caption.c_str();
                for(int sp=Form1->BCnt->Caption.Length(); sp<max[def_Cnt]; sp++)
                        TXT << " ";
                }
        if(Form2->check_ext_netlist->Checked)
                {
                TXT << Form1->BPinNetList->Caption.c_str();
                for(int sp=Form1->BPinNetList->Caption.Length(); sp<max[def_Netlist]; sp++)
                        TXT << " ";
                }
        if(Form2->check_pins_type->Checked)
                {
                TXT << Form1->BType->Caption.c_str();
                for(int sp=Form1->BType->Caption.Length(); sp<max[def_Type]; sp++)
                        TXT << " ";
                }
        if(Form2->check_pins_w->Checked)
                {
                TXT << Form1->BW->Caption.c_str();
                for(int sp=Form1->BW->Caption.Length(); sp<max[def_W]; sp++)
                        TXT << " ";
                }
        if(Form2->check_pins_l->Checked)
                {
                TXT << Form1->BL->Caption.c_str();
                for(int sp=Form1->BL->Caption.Length(); sp<max[def_L]; sp++)
                        TXT << " ";
                }
        if(Form2->check_thrml->Checked)
                {
                TXT << Form1->BTrml->Caption.c_str();
                for(int sp=Form1->BTrml->Caption.Length(); sp<max[def_Thrml]; sp++)
                        TXT << " ";
                }
        if(Form2->check_holes_diam->Checked)
                {
                TXT << Form1->BDHole->Caption.c_str();
                for(int sp=Form1->BDHole->Caption.Length(); sp<max[def_DHole]; sp++)
                        TXT << " ";
                }
        if(Form2->check_paste->Checked)
                {
                TXT << Form1->BPas->Caption.c_str();
                for(int sp=Form1->BPas->Caption.Length(); sp<max[def_Pas]; sp++)
                        TXT << " ";
                }
        if(Form2->check_pinsx->Checked)
                {
                TXT << Form1->BXPin->Caption.c_str();
                for(int sp=Form1->BXPin->Caption.Length(); sp<max[def_Xpi]; sp++)
                        TXT << " ";
                }
        if(Form2->check_pinsy->Checked)
                {
                TXT << Form1->BYPin->Caption.c_str();
                for(int sp=Form1->BYPin->Caption.Length(); sp<max[def_Ypi]; sp++)
                        TXT << " ";
                }
        TXT << endl;
        for (int istr=0; istr<Form1->StringGridPins->RowCount; istr++)
                {
                //A = AnsiString(istr+1);
                //TXT << A.c_str();
                //for(int sp=A.Length(); sp<max_num; sp++)
                //        TXT << " ";

                if(Form2->check_pinname->Checked)
                        {
                        TXT << Form1->StringGridPins->Cells[def_Pin][istr].c_str();
                        for(int sp=Form1->StringGridPins->Cells[def_Pin][istr].Length(); sp<max[def_Pin]; sp++)
                                TXT << " ";
                        }
                if(Form2->check_netpcb->Checked)
                        {
                        TXT << Form1->StringGridPins->Cells[def_NetPcb][istr].c_str();
                        for(int sp=Form1->StringGridPins->Cells[def_NetPcb][istr].Length(); sp<max[def_NetPcb]; sp++)
                                TXT << " ";
                        }
                if(Form2->check_pins_cnt->Checked)
                        {
                        TXT << Form1->StringGridPins->Cells[def_Cnt][istr].c_str();
                        for(int sp=Form1->StringGridPins->Cells[def_Cnt][istr].Length(); sp<max[def_Cnt]; sp++)
                                TXT << " ";
                        }
                if(Form2->check_ext_netlist->Checked)
                        {
                        TXT << Form1->StringGridPins->Cells[def_Netlist][istr].c_str();
                        for(int sp=Form1->StringGridPins->Cells[def_Netlist][istr].Length(); sp<max[def_Netlist]; sp++)
                                TXT << " ";
                        }
                if(Form2->check_pins_type->Checked)
                        {
                        TXT << Form1->StringGridPins->Cells[def_Type][istr].c_str();
                        for(int sp=Form1->StringGridPins->Cells[def_Type][istr].Length(); sp<max[def_Type]; sp++)
                                TXT << " ";
                        }
                if(Form2->check_pins_w->Checked)
                        {
                        A = Form1->StringGridPins->Cells[def_W][istr];
                        int p = A.Pos(",");
                        if (p > 0)
                                A[p] = '.';
                        TXT << A.c_str();
                        for(int sp=A.Length(); sp<max[def_W]; sp++)
                                TXT << " ";
                        }
                if(Form2->check_pins_l->Checked)
                        {
                        A = Form1->StringGridPins->Cells[def_L][istr];
                        int p = A.Pos(",");
                        if (p > 0)
                                A[p] = '.';
                        TXT << A.c_str();
                        for(int sp=A.Length(); sp<max[def_L]; sp++)
                                TXT << " ";
                        }
                if(Form2->check_thrml->Checked)
                        {
                        TXT << Form1->StringGridPins->Cells[def_Thrml][istr].c_str();
                        for(int sp=Form1->StringGridPins->Cells[def_Thrml][istr].Length(); sp<max[def_Thrml]; sp++)
                                TXT << " ";
                        }
                if(Form2->check_holes_diam->Checked)
                        {
                        A = Form1->StringGridPins->Cells[def_DHole][istr];
                        int p = A.Pos(",");
                        if (p > 0)
                                A[p] = '.';
                        TXT << A.c_str();
                        for(int sp=A.Length(); sp<max[def_DHole]; sp++)
                                TXT << " ";
                        }
                if(Form2->check_paste->Checked)
                        {
                        TXT << Form1->StringGridPins->Cells[def_Pas][istr].c_str();
                        for(int sp=Form1->StringGridPins->Cells[def_Pas][istr].Length(); sp<max[def_Pas]; sp++)
                                TXT << " ";
                        }
                if(Form2->check_pinsx->Checked)
                        {
                        A = Form1->StringGridPins->Cells[def_Xpi][istr];
                        int p = A.Pos(",");
                        if (p > 0)
                                A[p] = '.';
                        TXT << A.c_str();
                        for(int sp=A.Length(); sp<max[def_Xpi]; sp++)
                                TXT << " ";
                        }
                if(Form2->check_pinsy->Checked)
                        {
                        A = Form1->StringGridPins->Cells[def_Ypi][istr];
                        int p = A.Pos(",");
                        if (p > 0)
                                A[p] = '.';
                        TXT << A.c_str();
                        for(int sp=A.Length(); sp<max[def_Ypi]; sp++)
                                TXT << " ";
                        }
                TXT << endl;
                }
        }
#undef max_num
TXT.close();
Sleep(300);
if ((UINT)ShellExecute(NULL,
       "open",
       str.c_str(),
       NULL,
       ExtractFilePath(str).c_str() ,
       SW_SHOWNORMAL) <=32)
       {ShowMessage  ("     File " + str + " not found!"); return;}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BPinClick(TObject *Sender)
{
StringGridPartsRowIndex = 0;
StringGridPinsRowIndex = 0;
SortedParts(col_Pin+1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BPinNetPCBClick(TObject *Sender)
{
StringGridPartsRowIndex = 0;
StringGridPinsRowIndex = 0;
SortedParts(col_NetPcb+1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BCntClick(TObject *Sender)
{
StringGridPartsRowIndex = 0;
StringGridPinsRowIndex = 0;
SortedParts(col_Cnt+1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BPinNetListClick(TObject *Sender)
{
StringGridPartsRowIndex = 0;
StringGridPinsRowIndex = 0;
SortedParts(col_Netlist+1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BTypeClick(TObject *Sender)
{
StringGridPartsRowIndex = 0;
StringGridPinsRowIndex = 0;
SortedParts(col_Type+1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BWClick(TObject *Sender)
{
StringGridPartsRowIndex = 0;
StringGridPinsRowIndex = 0;
SortedParts(col_W+1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BLClick(TObject *Sender)
{
StringGridPartsRowIndex = 0;
StringGridPinsRowIndex = 0;
SortedParts(col_L+1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BTrmlClick(TObject *Sender)
{
StringGridPartsRowIndex = 0;
StringGridPinsRowIndex = 0;
SortedParts(col_Thrml+1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BDHoleClick(TObject *Sender)
{
StringGridPartsRowIndex = 0;
StringGridPinsRowIndex = 0;
SortedParts(col_DHole+1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BPasClick(TObject *Sender)
{
StringGridPartsRowIndex = 0;
StringGridPinsRowIndex = 0;
SortedParts(col_Pas+1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BXPinClick(TObject *Sender)
{
StringGridPartsRowIndex = 0;
StringGridPinsRowIndex = 0;
SortedParts(col_Xpi+1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BYPinClick(TObject *Sender)
{
StringGridPartsRowIndex = 0;
StringGridPinsRowIndex = 0;
SortedParts(col_Ypi+1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CRefDesClick(TObject *Sender)
{
Form1->Caption = "Enter ref. Use also %ref% or %ref or !ref";
if (Form2->OnlyLatin->Checked == true)
        LoadKeyboardLayout("00000409", KLF_ACTIVATE);	//английская раскладка
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CValueClick(TObject *Sender)
{
if (Form2->OnlyLatin->Checked == true)
        LoadKeyboardLayout("00000409", KLF_ACTIVATE);	//английская раскладка        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CPackageClick(TObject *Sender)
{
if (Form2->OnlyLatin->Checked == true)
        LoadKeyboardLayout("00000409", KLF_ACTIVATE);	//английская раскладка        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RClick(TObject *Sender)
{
ResetFilter(false);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BValueNLClick(TObject *Sender)
{
StringGridPartsRowIndex = 0;
StringGridPinsRowIndex = 0;
SortedParts(col_ValueNL+1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BPackageNLClick(TObject *Sender)
{
StringGridPartsRowIndex = 0;
StringGridPinsRowIndex = 0;
SortedParts(col_PackageNL+1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BFootPrintClick(TObject *Sender)
{
StringGridPartsRowIndex = 0;
StringGridPinsRowIndex = 0;
SortedParts(col_FootPrint+1);        
}
//---------------------------------------------------------------------------


void __fastcall TForm1::MinRIKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if (Key == VK_DOWN)             Form1->StringGridParts->SetFocus();
else if (Key == VK_LEFT)        Form1->CRefDes->SetFocus();
else if (Key == VK_RIGHT)       Form1->MaxRI->SetFocus();
else FilterAll();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MaxRIKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if (Key == VK_DOWN)             Form1->StringGridParts->SetFocus();
else if (Key == VK_LEFT)        Form1->MinRI->SetFocus();
else if (Key == VK_RIGHT)       Form1->CValue->SetFocus();
else FilterAll();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BRIRangeClick(TObject *Sender)
{
StringGridPartsRowIndex = 0;
StringGridPinsRowIndex = 0;
SortedParts(col_RIRange+1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CRefDesMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if (Form1->CRefDes->Text.Length())
        {
        AnsiString str = Form1->CRefDes->Text;
        if (str.Length() > 1)
                if(str.SubString(str.Length()-1,2) == dSPACE)
                        {
                        str = str.TrimRight();
                        Form1->CRefDes->Text = str + " ";
                        }
        }        
}
//---------------------------------------------------------------------------



 void __fastcall TForm1::MItemClick(TObject *Sender)
 {
 TMenuItem * lItem = dynamic_cast<TMenuItem*>(Sender);
 if( lItem )
 if( lItem->Parent )
        {
        AnsiString Cap = lItem->Caption;
        for( int i = Cap.Pos("&"); i>0; i = Cap.Pos("&") )
                Cap.Delete(i,1);
        if( Cap.SubString(1,3) == "Att" )
                {
                Cap = lItem->Parent->Caption;
                for( int i = Cap.Pos("&"); i>0; i = Cap.Pos("&") )
                        Cap.Delete(i,1);
                int err = 1;
                if( Cap.SubString(Cap.Length(),1) == "r" )
                        {
                        err = SaveFilter(col_RefDes);
                        CRefDes->Text = Cap;
                        }
                else if( Cap.SubString(Cap.Length(),1) == "v" )
                        {
                        err = SaveFilter(col_Value);
                        CValue->Text = Cap;
                        }
                else if( Cap.SubString(Cap.Length(),1) == "p" )
                        {
                        err = SaveFilter(col_Package);
                        CPackage->Text = Cap;
                        }
                Application->ProcessMessages();
                if( err == 0 )
                        SaveFilter(0);
                ResetFilter(TRUE);
                }
        else if( Cap.SubString(1,3) == "Ope" )
                {
                Cap = lItem->Parent->Caption;
                for( int i = Cap.Pos("&"); i>0; i = Cap.Pos("&") )
                        Cap.Delete(i,1);
                AnsiString dir = ExtractFilePath( FileName );
                ShellExecute(NULL, "open", (dir+"related_files\\infobox\\"+Cap).c_str(), NULL, (dir+"related_files\\infobox\\").c_str(), SW_SHOWNORMAL);
                }
        else if( Cap.SubString(1,3) == "Rem" )
                {
                Cap = lItem->Parent->Caption;
                for( int i = Cap.Pos("&"); i>0; i = Cap.Pos("&") )
                        Cap.Delete(i,1);
                AnsiString dir = ExtractFilePath( FileName );
                AnsiString file = dir+"related_files\\infobox\\"+Cap;
                Form1->SortedBox->Items->Clear();
                Form1->SortedBox->Items->LoadFromFile(file);
                for (int k = 0; k < Form1->StringGridParts->RowCount; k++)
                        {
                        if( Cap.SubString(Cap.Length()-1,2) == ".r" )
                                A = Form1->StringGridParts->Cells[def_RefDes][k];
                        else if( Cap.SubString(Cap.Length()-1,2) == ".v" )
                                A = Form1->StringGridParts->Cells[def_Value][k];
                        else if( Cap.SubString(Cap.Length()-1,2) == ".p" )
                                A = Form1->StringGridParts->Cells[def_Package][k];
                        A = A.Trim();
                        if (A.Length())
                                {
                                int iof = Form1->SortedBox->Items->IndexOf(A);
                                if ( iof != -1)
                                        Form1->SortedBox->Items->Delete(iof);
                                }
                        }
                ofstream FilterW;
                FilterW.open(file.c_str()); //// std::ios_base::app );
                AnsiString wr;
                for (int k = 0; k < Form1->SortedBox->Items->Count; k++)
                        {
                        wr = Form1->SortedBox->Items->operator [](k);
                        if (wr.Length())
                                FilterW << wr.c_str() << endl;
                        }
                FilterW.close();
                }
        else if( Cap.SubString(1,3) == "Per" )
                {
                Cap = lItem->Parent->Caption;
                for( int i = Cap.Pos("&"); i>0; i = Cap.Pos("&") )
                        Cap.Delete(i,1);
                if( Cap.SubString(Cap.Length()-1,2) == ".r" )
                        {
                        if( Form2->check_refs->Checked == 0 )
                                {
                                ShowMessage("  EN: This is not possible when the column is invisible (right-click on the parts list, then enter the SETTINGS menu)");
                                return;
                                }
                        Form1->CRefDes->Text = Cap;
                        }
                else if( Cap.SubString(Cap.Length()-1,2) == ".v" )
                        {
                        if( Form2->check_values->Checked == 0 )
                                {
                                ShowMessage("  EN: This is not possible when the column is invisible (right-click on the parts list, then enter the SETTINGS menu)");
                                return;
                                }
                        Form1->CValue->Text = Cap;
                        }
                else if( Cap.SubString(Cap.Length()-1,2) == ".p" )
                        {
                        if( Form2->check_package->Checked == 0 )
                                {
                                ShowMessage("  EN: This is not possible when the column is invisible (right-click on the parts list, then enter the SETTINGS menu)");
                                return;
                                }
                        Form1->CPackage->Text = Cap;
                        }
                }
        }
 }
void __fastcall TForm1::TFilterAllTimer(TObject *Sender)
{
        Form1->TFilterAll->Enabled = 0;
        Form1->TFilterAll->Interval = 10;
        FilterAll(true,GlobalPinText);
        GlobalPinText = "";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BCNetlistMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
BCNetlist->ShowHint = 1;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::VP_popupClick(TObject *Sender)
{
Save_Values_Packages(ExtractFilePath(Application->ExeName)+"VPL\\");
}
//---------------------------------------------------------------------------


void ReadingStorages(void)
{
Form1->Values->Items->Clear();
TSearchRec sr;
AnsiString CAT = ExtractFilePath(Application->ExeName);
if (FindFirst((CAT+"VPL\\*"), faAnyFile, sr) == 0)
        {
        do      {
                if (sr.Attr & faDirectory) // directory
                        {
                        // isEmpty
                        }
                else    //file...
                        {
                        if ((sr.Name!=".")&&(sr.Name!=".."))
                                {
                                if (  sr.Name.SubString((sr.Name.Length()-2), 3) == "vpl" )
                                        {
                                        RStorage(CAT+"VPL\\"+sr.Name);
                                        }
                                }
                        }
                }while (FindNext(sr) == 0);
        }
}
void __fastcall TForm1::CSC_popupClick(TObject *Sender)
{
if( Form1->PageControl1->TabIndex )
        FilterAll(true, "", 0);
FixFilteredParts();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RemoveCurrentList1Click(TObject *Sender)
{
AnsiString str = ExtractFilePath(FileName) + "related_files\\infobox\\";
A = Form1->CRefDes->Text;
int i__of = IOF(A);
B = str + A;
FILE* F;
F = fopen(B.c_str(),"r+");
if(F&&i__of>0)   {
        fclose(F);
        if( MessageBox (NULL,("Are you sure you want to delete this list? ("+B+")").c_str(),"Warning",MB_YESNO) == ID_YES )
                {
                DeleteFile(B);
                TMenuItem * M = Form1->SF->Items->operator [](i__of);
                while( M->Count )
                        M->Delete(0);
                Form1->SF->Items->Delete(i__of);
                }
        return;
        }
A = Form1->CValue->Text;
i__of = IOF(A);
B = str + A;
F = fopen(B.c_str(),"r+");
if(F&&i__of>0)   {
        fclose(F);
        if( MessageBox (NULL,("Are you sure you want to delete this list? ("+B+")").c_str(),"Warning",MB_YESNO) == ID_YES )
                {
                DeleteFile(B);
                TMenuItem * M = Form1->SF->Items->operator [](i__of);
                while( M->Count )
                        M->Delete(0);
                Form1->SF->Items->Delete(i__of);
                }
        return;
        }
A = Form1->CPackage->Text;
i__of = IOF(A);
B = str + A;
F = fopen(B.c_str(),"r+");
if(F&&i__of>0)   {
        fclose(F);
        if( MessageBox (NULL,("Are you sure you want to delete this list? ("+B+")").c_str(),"Warning",MB_YESNO) == ID_YES )
                {
                DeleteFile(B);
                TMenuItem * M = Form1->SF->Items->operator [](i__of);
                while( M->Count )
                        M->Delete(0);
                Form1->SF->Items->Delete(i__of);
                }
        return;
        }
}
//---------------------------------------------------------------------------
int getTaskBarHeight(){
   RECT rect;
   HWND taskBar = FindWindow("Shell_traywnd", NULL);
   if(taskBar && GetWindowRect(taskBar, &rect))
        {
        if( rect.right-rect.left < rect.bottom-rect.top )
                return 0;
        int H = Screen->Height - rect.top;
        return H;
        }
   return 0;
}
//---------------------------------------------------------------------------
void Embed(int ClientWidth,int ClientHeight)
{
//int CORR_H = 33;
int CORR_H2 = 24;
RECT w_rect;
HWND FPC = FindWindow( NULL, WindowHeader.c_str() );
if( FPC && WindowHeader.SubString(1,10) == FREEPCB_HEADER )
        {
        GetWindowRect( FPC, &w_rect );
        }
else    {
        FPC = FindWindow( NULL, NULL );
        do      {
                char ch[200];
                GetWindowText( FPC, ch, 200 );
                A = ch;
                if( A.SubString(1,10) == FREEPCB_HEADER )
                        break;
                FPC = ::GetNextWindow (FPC, GW_HWNDNEXT);
                } while( FPC );
        if( FPC )
                GetWindowRect( FPC, &w_rect );
        }
if( !IsWindowVisible(FPC) )
        FPC = NULL;
if( IsIconic(FPC) )
        FPC = NULL;
if( Form2->OnTop->Checked )
        {
        if(Form1->Height > Screen->Height/2)
                {
                Form1->Height = Screen->Height/2;
                if( ClientHeight )
                        ClientHeight = Form1->Height;
                }
        Form1->Top = 0;
        Form1->Left = 0;
        Form1->Width = Screen->Width;
        //
        if( FPC )
                {
                if( ClientHeight )                // obscure the headline
                        ClientHeight -= 8;
                ShowWindowAsync( FPC, SW_RESTORE );
                SetWindowPos( FPC, NULL, w_rect.left, ClientHeight, w_rect.right-w_rect.left, w_rect.bottom-ClientHeight, NULL );
                }
        }
else if( Form2->OnTheRight->Checked )
        {
        if(Form1->Width > Screen->Width/2)
                {
                Form1->Width = Screen->Width/2;
                if( ClientWidth )
                        ClientWidth = Form1->Width;
                }
        Form1->Top = 0;
        Form1->Left = Screen->Width - Form1->Width;
        int tgH = getTaskBarHeight();
        Form1->Height = Screen->Height - tgH;
        //
        if( FPC )
                {
                ClientWidth -= CORR_H2;
                ShowWindowAsync( FPC, SW_RESTORE );
                SetWindowPos( FPC, NULL, w_rect.left, w_rect.top, Screen->Width-w_rect.left-ClientWidth , w_rect.bottom-w_rect.top, NULL );
                }
        }
else if( Form2->FromBelow->Checked )
        {
        if(Form1->Height > Screen->Height/2)
                {
                Form1->Height = Screen->Height/2;
                if( ClientHeight )
                        ClientHeight = Form1->Height;
                }
        Form1->Left = 0;
        Form1->Width = Screen->Width;
        int tgH = getTaskBarHeight();
        Form1->Top = Screen->Height - Form1->Height - tgH;
        //
        if( FPC )
                {
                if( ClientHeight )
                        ClientHeight -= 10;
                if( tgH < 5 )
                        tgH = 0;
                ShowWindowAsync( FPC, SW_RESTORE );
                SetWindowPos( FPC, NULL, w_rect.left, w_rect.top, w_rect.right-w_rect.left, Screen->Height-tgH-w_rect.top-ClientHeight, NULL );     //-CORR_H-CORR_H2
                }
        }
}

//---------------------------------------------------------------------------


void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
if( Form2->FreePos->Checked == 0 )
        {
        Embed(0,0);
        }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
//VK_ESCAPE
if (Key == VK_ESCAPE)
        {
        if( Form2->OnTheRight->Checked == 0 )
                Form1->Height = Form1_Height;
        SetFormComponentsSizes(false);
        Wind = FindWindow(NULL, WindowHeader.c_str());
        SetForegroundWindow(Wind);
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormResize(TObject *Sender)
{
Form1->PageControl1->Visible = 0;
R->Visible = 0;
}
//---------------------------------------------------------------------------



void __fastcall TForm1::PopupPopup(TObject *Sender)
{
bool Flag = 0;
if( Form2 )
if( Form2->FromBelow->Checked )
        {
        if( ST_popup->MenuIndex == 0 )
                Flag = 1;
        }
else    {
        if( ST_popup->MenuIndex )
                Flag = 1;
        }
if( Flag )
        for( i=0; i<Popup->Items->Count; i++ )
                {
                TMenuItem * M = Popup->Items->operator [](Popup->Items->Count-1);
                M->MenuIndex = i;
                }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::MinHolesClick(TObject *Sender)
{
if( PinsWasR == 0 )
        if( FRead_File == TRUE_TRUE )
                Read_File( TRUE, TRUE );
        else    Read_File( FALSE, TRUE );
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MaxHolesClick(TObject *Sender)
{
if( PinsWasR == 0 )
        if( FRead_File == TRUE_TRUE )
                Read_File( TRUE, TRUE );
        else    Read_File( FALSE, TRUE );
}
//---------------------------------------------------------------------------


