//---------------------------------------------------------------------------


#pragma hdrstop

#include "FilterAll.h"
#include "Comp_man.h"
#include "Path_EXE.h"
#include "fstream.h"
int TInd=0;




//---------------------------------------------------------------------------

#pragma package(smart_init)

bool check_single_pin()
        {
        if( Form1->StringGridPins->RowCount )
                {
                AnsiString STR = Form1->StringGridPins->Cells[def_Pin][0];
                for( int i=0; i<Form1->StringGridPins->RowCount; i++ )
                        {
                        AnsiString GET = Form1->StringGridPins->Cells[def_Pin][i];
                        if( GET.Length() == 0 )
                                continue;
                        if( GET.Length() != STR.Length() )
                                return 0;
                        if( STR.SubString(1,STR.Length()) != GET.SubString(1,GET.Length()) )
                                return 0;
                        }
                return 1;
                }
        return 0;
        }

bool ShareProg (AnsiString * share, AnsiString Data)
        {
        bool bSh = true, bSp = false;
        if ( (*share).SubString(1,1) == "%")
                *share = (*share).SubString(2,((*share).Length()-1));
        int shLength = (*share).Length();
        int DtLength = Data.Length();
        if ( (*share).SubString(shLength,1) == "%")
                {
                bSh=false;
                *share = (*share).SubString(1,(shLength-1));
                shLength--;
                }
        if ( (*share).SubString(shLength,1) == " ")
                {
                bSp=true;
                *share = (*share).TrimRight();
                shLength = (*share).Length();
                }
        int pos = Data.Pos(*share);
        if (pos > 0)
                {
                if (bSh)
                        {
                        if (pos == (DtLength-shLength+1))
                                return pos;
                        else if(Data.SubString((DtLength-shLength+1),shLength) == (*share).SubString(1,shLength) )
                                return pos;
                        else    return 0;
                        }
                else if (bSp)
                        {
                        if (pos == 1 && DtLength == shLength) return pos;
                        else    return 0;
                        }
                else return pos;
                }
        else    return 0;
        }
//---------------------------------------------------------------------------



bool CMPR (int shift, int iCOL)
{
bool bRET = 1;
AnsiString Cstr="";
AnsiString DataRef="";
if( TInd == 0 )
        {
        DataRef = Form1->DataParts->Items->operator [](shift+iCOL+1);
        if( iCOL == col_RefDes )
                Cstr = Form1->CRefDes->Text;
        else if( iCOL == col_Value )
                Cstr = Form1->CValue->Text;
        else if( iCOL == col_Package )
                Cstr = Form1->CPackage->Text;
        else if( iCOL == col_FootPrint )
                Cstr = Form1->CFootPrint->Text;
        else if( iCOL == col_ValueNL )
                Cstr = Form1->CValueNL->Text;
        else if( iCOL == col_PackageNL )
                Cstr = Form1->CPackageNL->Text;
        else if( iCOL == col_Merge )
                Cstr = Form1->CMerge->Text;
        }
if( TInd == 1 )
        {
        DataRef = Form1->DataPins->Items->operator [](shift+iCOL+1);
        if( iCOL == col_Pin )
                Cstr = Form1->CPin->Text;
        else if( iCOL == col_NetPcb )
                Cstr = Form1->CPinNetPCB->Text;
        else if( iCOL == col_Netlist )
                Cstr = Form1->CNetNetlist->Text;
        int sl = Cstr.Length();
        if( iCOL == col_Pin )
                if( sl > 1 )
                        if( Cstr.Pos(".") <= 0 )
                                if( Cstr.SubString(sl-1,2) == dSPACE )
                                        Cstr = Cstr.SubString(1,sl-2) + ".";
        }
DataRef = DataRef.Trim();
int pos;
bool INVR = false;
bool bMultiple = false;
Cstr = Cstr.TrimLeft();
pos = Cstr.Pos(" ");
if( pos > 0 )
        {
        bMultiple = true;
        }
B = Cstr;
if (B.SubString(1,1) == "!")
        {
        INVR = true;
        B = B.SubString(2,(B.Length()-1));
        Cstr = Cstr.SubString(2,(B.Length()-1));
        }
if (Form2->IgnoreCase->Checked)
        {
        B = B.UpperCase();
        DataRef = DataRef.UpperCase();
        }
if (B.LowerCase().SubString((B.Length()-1),2) == ".r" )
        {
        int iof = Form1->SortedBox->Items->IndexOf("Ref" + DataRef);
        if (iof != -1 && INVR)             bRET = false;
        else if (iof == -1 && !INVR)       bRET = false;
        }
else if (B.LowerCase().SubString((B.Length()-1),2) == ".v" )
        {
        int iof = Form1->SortedBox->Items->IndexOf("Val" + DataRef);
        if (iof != -1 && INVR)             bRET = false;
        else if (iof == -1 && !INVR)       bRET = false;
        }
else if (B.LowerCase().SubString((B.Length()-1),2) == ".p" )
        {
        int iof = Form1->SortedBox->Items->IndexOf("Pac" + DataRef);
        if (iof != -1 && INVR)             bRET = false;
        else if (iof == -1 && !INVR)       bRET = false;
        }
else    {
        if (B.SubString(1,1) == "%" )
                {
                int f = ShareProg(&B, DataRef);
                if (!f && !INVR)        bRET = false;
                else if (f && INVR)     bRET = false;
                }
        else if( bMultiple )
                {
                if (Form2->IgnoreCase->Checked)
                        {
                        B = B.UpperCase();
                        Cstr = Cstr.UpperCase();
                        }
                if(!INVR)
                        {
                        int dPos=0;
                        int dPos1 = Cstr.Pos(" "+DataRef+" ");
                        AnsiString D = DataRef+" ";
                        AnsiString E = " "+DataRef;
                        if( Cstr.SubString(1,DataRef.Length()+1) == D.SubString(1,D.Length()) )
                                dPos = 1;
                        else if( dPos1 > 0)
                                dPos = dPos1+1;
                        else if( Cstr.SubString((Cstr.Length()-DataRef.Length()),DataRef.Length()+1) == E.SubString(1,E.Length()) )
                                dPos = (Cstr.Length()-DataRef.Length());
                        if (dPos < 1)
                                bRET = false;
                        }
                else    {
                        long dPos=1;
                        AnsiString D;
                        do      {
                                D = while_not_space(Cstr,&dPos);
                                D = D.Trim();
                                if(D.Length())
                                        {
                                        int p = DataRef.Pos(D);
                                        if(p==1)
                                                {
                                                bRET = false;
                                                break;
                                                }
                                        }
                                }while(dPos);
                        }
                }
        else if (B.SubString(1,B.Length()) != DataRef.SubString(1,B.Length()) && !INVR)  bRET = false;
        else if (B.SubString(1,B.Length()) == DataRef.SubString(1,B.Length()) && INVR)   bRET = false;
        }
return bRET;
}


int CheckGrid1()
{
if(     Form1->MinRI->Text.Length()==0 &&
        Form1->MaxRI->Text.Length()==0 &&
        Form1->CValue->Text.Length()==0 &&
        Form1->CValueNL->Text.Length()==0 &&
        Form1->CFootPrint->Text.Length()==0 &&
        Form1->CPackage->Text.Length()==0 &&
        Form1->CPackageNL->Text.Length()==0 &&
        Form1->CMerge->Text.Length()==0 &&
        Form1->MinPin->Text.Length()==0 &&
        Form1->MaxPins->Text.Length()==0 &&
        Form1->MinHoles->Text.Length()==0 &&
        Form1->MaxHoles->Text.Length()==0 &&
        Form1->Glueds->Text.Length()==0 &&
        Form1->Side->Text.Length()==0 &&
        Form1->Ang->Text.Length()==0 &&
        Form1->EXmin->Text.Length()==0 &&
        Form1->EXmax->Text.Length()==0 &&
        Form1->EYmin->Text.Length()==0 &&
        Form1->EYmax->Text.Length()==0 &&
        Form1->CCNetlist->Text.Length()==0 )
        {
        if( Form1->CRefDes->Text.Length() || Form1->Deleted->Count )
                return 1;
        else    return 0;
        }
return 2;
}
int CheckGrid2()
{
if(     Form1->CPinNetPCB->Text.Length()==0 &&
        Form1->CCnt->Text.Length()==0 &&
        Form1->CNetNetlist->Text.Length()==0 &&
        Form1->CType->Text.Length()==0 &&
        Form1->WPinMin->Text.Length()==0 &&
        Form1->WPinMax->Text.Length()==0 &&
        Form1->LPinMin->Text.Length()==0 &&
        Form1->LPinMax->Text.Length()==0 &&
        Form1->CTrml->Text.Length()==0 &&
        Form1->DHoleMin->Text.Length()==0 &&
        Form1->DHoleMax->Text.Length()==0 &&
        Form1->Pas->Text.Length()==0 &&
        Form1->XPinMin->Text.Length()==0 &&
        Form1->XPinMax->Text.Length()==0 &&
        Form1->YPinMin->Text.Length()==0 &&
        Form1->YPinMax->Text.Length()==0 )
        {
        if( Form1->CPin->Text.Length() )
                return 1;
        else    return 0;
        }
return 2;
}
//---------------------------------------------------------------------------
//=========================== FILTER ========================================
//---------------------------------------------------------------------------

void FilterAll (bool Total, AnsiString includePin, int TIndex)
{
static int mem_prev_count =  Form1->StringGridPins->RowCount;
if (FlagSaveFilter || !BEGIN)
        return;
Form1->Caption = "Infobox*";
Application->ProcessMessages();
long shift = 0;
long RowIndex = 0;
//for parts
AnsiString DataRef;
//
//������ FILTERS: ( *.r *.v *.p )
//
Form1->SortedBox->Items->Clear();
if( FileName.Length() )
        for (int k=0; k<3; k++)
                {
                if      (k == 0)        B = Form1->CRefDes->Text;
                else if (k == 1)        B = Form1->CValue->Text;
                else if (k == 2)        B = Form1->CPackage->Text;
                if (B.SubString((B.Length()-1),2) == ".r"
                 || B.SubString((B.Length()-1),2) == ".v"
                 || B.SubString((B.Length()-1),2) == ".p" )
                        {
                        if (B.SubString(1,1) == "!")
                                {
                                B = B.SubString(2,(B.Length()-1));
                                }
                        B = ExtractFilePath(FileName) + "related_files\\infobox\\" + B;
                        //��������
                        FILE* F;
                        F = fopen(B.c_str(),"r");
                        if(F == NULL)
                                {
                                fclose(F);
                                if (Form2->Language->Checked)   Form1->Caption = "������ ������ " + B;
                                else                            Form1->Caption = "Error reading " + B;
                                }
                        else    {
                                fclose(F);
                                ifstream FilterR (B.c_str());
                                B = "";
                                while (!FilterR.eof())
                                        {
                                        FilterR.getline(s,2500);
                                        B = s;
                                        B = B.UpperCase();
                                        if (k == 0)             B = "Ref" + B;
                                        else if (k == 1)        B = "Val" + B;
                                        else if (k == 2)        B = "Pac" + B;
                                        if (Form1->SortedBox->Items->IndexOf(B) == -1)
                                                Form1->SortedBox->Items->Add(B);
                                        B = s;
                                        }
                                FilterR.close();
                                }
                        }
                }
int Vis1 = Form1->StringGridParts->Visible;
int Vis2 = Form1->StringGridPins->Visible;
Form1->StringGridParts->Visible = 0;
Form1->StringGridPins->Visible = 0;
//Form1->StringGridParts->Enabled = 0;
//Form1->StringGridPins->Enabled = 0;
bool BoolAdd;
//FILTER PARTS
if( TIndex == -1 )
        TIndex = Form1->PageControl1->TabIndex;
TInd = TIndex;
if (TIndex == 0)
        {
        if(Total)
                Total = CheckGrid2();
        int Check_FLT = CheckGrid1();
        RowIndex = -1;
        Form1->StringGridParts->RowCount = Form1->DataParts->Items->Count/(PartsColCount+1);
        while(shift < Form1->DataParts->Items->Count)
                {
                BoolAdd = true;
                if( Total || Check_FLT ) while(1)
                        {
                        //Ref
                        DataRef = Form1->DataParts->Items->operator [](shift+col_RefDes+1);
                        //Deletes
                        if (Form1->Deleted->Items->IndexOf(DataRef) >= 0)
                                {
                                BoolAdd = false;
                                break;
                                }
                        if( Total )
                                {
                                AnsiString Com = DataRef + ".";
                                int len = Com.Length();
                                bool F = false;
                                for (int ns=0; ns<Form1->StringGridPins->RowCount; ns++)
                                        if (Form1->StringGridPins->Cells[def_Pin][ns].SubString(1,len) == Com.SubString(1,len))
                                                {
                                                F = true;
                                                break;
                                                }
                                if (!F) {
                                        BoolAdd = false;
                                        break;
                                        }
                                }
                        if (Form1->CRefDes->Text.Length())
                                {
                                BoolAdd = CMPR( shift, col_RefDes );
                                if( !BoolAdd )
                                        break;
                                }
                        // flag ref only  // speed optimization
                        if( Check_FLT == 1 )
                                break;
                        //Min RI
                        if (Form1->MinRI->Text.Length())
                                {
                                int MinRI = StrToFloat(Str_Float_Format(Form1->MinRI->Text));
                                int Data = StrToFloat(Str_Float_Format(Form1->DataParts->Items->operator [](shift+col_RIRange+1)));
                                if (Data < MinRI)
                                        {
                                        BoolAdd = false;
                                        break;
                                        }
                                }
                        //Max RI
                        if (Form1->MaxRI->Text.Length())
                                {
                                int MaxRI = StrToFloat(Str_Float_Format(Form1->MaxRI->Text));
                                int Data = StrToFloat(Str_Float_Format(Form1->DataParts->Items->operator [](shift+col_RIRange+1)));
                                if (Data > MaxRI)
                                        {
                                        BoolAdd = false;
                                        break;
                                        }
                                }
                        //Value
                        if (Form1->CValue->Text.Length())
                                {
                                BoolAdd = CMPR( shift, col_Value );
                                if( !BoolAdd )
                                        break;
                                }
                        if (Form1->CValueNL->Text.Length())
                                {
                                BoolAdd = CMPR( shift, col_ValueNL );
                                if( !BoolAdd )
                                        break;
                                }
                        //Package
                        if (Form1->CPackage->Text.Length())
                                {
                                BoolAdd = CMPR( shift, col_Package );
                                if( !BoolAdd )
                                        break;
                                }
                        if (Form1->CPackageNL->Text.Length())
                                {
                                BoolAdd = CMPR( shift, col_PackageNL );
                                if( !BoolAdd )
                                        break;
                                }
                        //Merge
                        if (Form1->CMerge->Text.Length())
                                {
                                BoolAdd = CMPR( shift, col_Merge );
                                if( !BoolAdd )
                                        break;
                                }
                        //FootPrint
                        if (Form1->CFootPrint->Text.Length())
                                {
                                BoolAdd = CMPR( shift, col_FootPrint );
                                if( !BoolAdd )
                                        break;
                                }
                        //Min Pins
                        if (Form1->MinPin->Text.Length())
                                {
                                int MinP = StrToFloat(Str_Float_Format(Form1->MinPin->Text));
                                int DataPin = StrToFloat(Str_Float_Format(Form1->DataParts->Items->operator [](shift+col_Pins+1)));
                                if (DataPin < MinP)
                                        {
                                        BoolAdd = false;
                                        break;
                                        }
                                }
                        //Max Pins
                        if (Form1->MaxPins->Text.Length())
                                {
                                int MaxP = StrToFloat(Str_Float_Format(Form1->MaxPins->Text));
                                int DataPin = StrToFloat(Str_Float_Format(Form1->DataParts->Items->operator [](shift+col_Pins+1)));
                                if (DataPin > MaxP)
                                        {
                                        BoolAdd = false;
                                        break;
                                        }
                                }
                        //Min Holes
                        if (Form1->MinHoles->Text.Length())
                                {
                                int MinH = StrToFloat(Str_Float_Format(Form1->MinHoles->Text));
                                int DataHol = StrToFloat(Str_Float_Format(Form1->DataParts->Items->operator [](shift+col_Holes+1)));
                                if (DataHol < MinH)
                                        {
                                        BoolAdd = false;
                                        break;
                                        }
                                }
                        //Max Holes
                        if (Form1->MaxHoles->Text.Length())
                                {
                                int MaxH = StrToFloat(Str_Float_Format(Form1->MaxHoles->Text));
                                int DataHol = StrToFloat(Str_Float_Format(Form1->DataParts->Items->operator [](shift+col_Holes+1)));
                                if (DataHol > MaxH)
                                        {
                                        BoolAdd = false;
                                        break;
                                        }
                                }
                        //Glueds
                        if (Form1->Glueds->Text.Length())
                                {
                                B = Form1->Glueds->Text;
                                AnsiString DataGlu = Form1->DataParts->Items->operator [](shift+col_Gl+1);
                                B = B.UpperCase();
                                DataGlu = DataGlu.UpperCase();
                                if (B.SubString(1,B.Length()) != DataGlu.SubString(1,B.Length()))
                                        {
                                        BoolAdd = false;
                                        break;
                                        }
                                }
                        //Side
                        if (Form1->Side->Text.Length())
                                {
                                B = Form1->Side->Text;
                                AnsiString DataSid = Form1->DataParts->Items->operator [](shift+col_S+1);
                                B = B.UpperCase();
                                DataSid = DataSid.UpperCase();
                                if (B.SubString(1,B.Length()) != DataSid.SubString(1,B.Length()))
                                        {
                                        BoolAdd = false;
                                        break;
                                        }
                                }
                        //Angle
                        if (Form1->Ang->Text.Length())
                                {
                                B = Form1->Ang->Text;
                                AnsiString DataAng = Form1->DataParts->Items->operator [](shift+col_Ang+1);
                                B = B.UpperCase();
                                DataAng = DataAng.UpperCase();
                                if (B.SubString(1,B.Length()) != DataAng.SubString(1,B.Length()))
                                        {
                                        BoolAdd = false;
                                        break;
                                        }
                                }
                        //Min X
                        if (Form1->EXmin->Text.Length())
                                {
                                float MinX = StrToFloat(Str_Float_Format(Form1->EXmin->Text));
                                float Data__X = StrToFloat(Str_Float_Format(Form1->DataParts->Items->operator [](shift+col_Xprt+1)));
                                if (Data__X < MinX)
                                        {
                                        BoolAdd = false;
                                        break;
                                        }
                                }
                        //Max X
                        if (Form1->EXmax->Text.Length())
                                {
                                float MaxX = StrToFloat(Str_Float_Format(Form1->EXmax->Text));
                                float Data__X = StrToFloat(Str_Float_Format(Form1->DataParts->Items->operator [](shift+col_Xprt+1)));
                                if (Data__X > MaxX)
                                        {
                                        BoolAdd = false;
                                        break;
                                        }
                                }
                        //Min Y
                        if (Form1->EYmin->Text.Length())
                                {
                                float MinY = StrToFloat(Str_Float_Format(Form1->EYmin->Text));
                                float Data__Y = StrToFloat(Str_Float_Format(Form1->DataParts->Items->operator [](shift+col_Yprt+1)));
                                if (Data__Y < MinY)
                                        {
                                        BoolAdd = false;
                                        break;
                                        }
                                }
                        //Max Y
                        if (Form1->EYmax->Text.Length())
                                {
                                float MaxY = StrToFloat(Str_Float_Format(Form1->EYmax->Text));
                                float Data__Y = StrToFloat(Str_Float_Format(Form1->DataParts->Items->operator [](shift+col_Yprt+1)));
                                if (Data__Y > MaxY)
                                        {
                                        BoolAdd = false;
                                        break;
                                        }
                                }
                        //Netlist
                        if (Form1->CCNetlist->Text.Length())
                                {
                                B = Form1->CCNetlist->Text;
                                AnsiString DataNet = Form1->DataParts->Items->operator [](shift+col_CompareNetlist+1);
                                if (B.SubString(1,B.Length()) != DataNet.SubString(1,B.Length()))
                                        {
                                        BoolAdd = false;
                                        break;
                                        }
                                }
                        break;
                        }
                else if( RowIndex > mem_prev_count )  // speed optimization
                        break;
                //Add
                if(BoolAdd){
                        RowIndex++;
                        for(int ii=col_RefDes; ii<PartsColCount; ii++)
                                Form1->StringGridParts->Cells[PartColOrder[ii]][RowIndex] = Form1->DataParts->Items->operator [](shift+ii+1);
                        }
                shift = shift + PartsColCount + 1;
                }
        if (RowIndex == -1)
                {
                // search in footprint & value storage
                for(int ii=col_RefDes; ii<PartsColCount; ii++)
                        Form1->StringGridParts->Cells[ii][0] = "";
                AnsiString text;
                for (int w=0; w<Form1->Values->Items->Count; w++)
                        {
                        text = Form1->Values->Items->operator [](w);
                        int TL = text.Length();
                        int Vpos = text.Pos(dSPACE);
                        if( Vpos < 1 )
                                Vpos = text.Pos("\t");
                        AnsiString share;
                        if( Vpos < 1 )
                                {
                                Vpos = TL+1;
                                share = "";
                                B = "";
                                }
                        else    {
                                share = text.SubString(Vpos,TL-Vpos+1);
                                share = share.TrimLeft();
                                int i2 = share.Pos(dSPACE);
                                if( i2 < 1 )
                                        i2 = share.Pos("\t");
                                int sh_L = share.Length();
                                if( i2 < 1 )
                                        i2 = sh_L+1;
                                B = share.SubString(1,i2-1);
                                }
                        A = text.SubString(1,Vpos-1);
                        BoolAdd = true;
                        if (Form1->CValue->Text.Length())
                                {
                                text = Form1->CValue->Text;
                                if (Form2->IgnoreCase->Checked)
                                        {
                                        A = A.UpperCase();
                                        text = text.UpperCase();
                                        }
                                if (text.SubString(1,1) == "*" ) BoolAdd = ShareProg (&text, A);
                                else if (text.SubString(1,1) == "%" ) BoolAdd = ShareProg (&text, A);
                                else if (text.SubString(1,text.Length()) != A.SubString(1,text.Length()))
                                        BoolAdd = false;
                                }
                        if (Form1->CPackage->Text.Length())
                                {
                                text = Form1->CPackage->Text;
                                if (Form2->IgnoreCase->Checked)
                                        {
                                        B = B.UpperCase();
                                        text = text.UpperCase();
                                        }
                                if (text.SubString(1,1) == "*" ) BoolAdd = ShareProg (&text, A);
                                else if (text.SubString(1,1) == "%" ) BoolAdd = ShareProg (&text, A);
                                else if (text.SubString(1,text.Length()) != B.SubString(1,text.Length()))
                                        BoolAdd = false;
                                }
                        if (!Form1->CPackage->Text.Length() && !Form1->CValue->Text.Length())
                                BoolAdd = false;
                        if (BoolAdd)
                                {
                                RowIndex++;
                                Form1->StringGridParts->Cells[def_Value][RowIndex] = A;
                                Form1->StringGridParts->Cells[def_Package][RowIndex] = B;
                                //
                                Form1->StringGridParts->Cells[def_RefDes][RowIndex] = "";
                                Form1->StringGridParts->Cells[def_RIRange][RowIndex] = "";
                                Form1->StringGridParts->Cells[def_ValueNL][RowIndex] = "";
                                Form1->StringGridParts->Cells[def_FootPrint][RowIndex] = "";
                                Form1->StringGridParts->Cells[def_PackageNL][RowIndex] ="";
                                Form1->StringGridParts->Cells[def_Merge][RowIndex] = "";
                                Form1->StringGridParts->Cells[def_Pins][RowIndex] = "";
                                Form1->StringGridParts->Cells[def_Holes][RowIndex] = "";
                                Form1->StringGridParts->Cells[def_Gl][RowIndex] = "";
                                Form1->StringGridParts->Cells[def_S][RowIndex] = "";
                                Form1->StringGridParts->Cells[def_Ang][RowIndex] = "";
                                Form1->StringGridParts->Cells[def_Xprt][RowIndex] = "";
                                Form1->StringGridParts->Cells[def_Yprt][RowIndex] = "";
                                Form1->StringGridParts->Cells[def_CompareNetlist][RowIndex] ="";
                                }
                        }
                }
        //limit row count
        if( Total || Check_FLT )
                Form1->StringGridParts->RowCount = MAX(1,RowIndex+1);
        //mem_prev_count = Form1->StringGridParts->RowCount;
        // speed optimization
        if( mem_prev_count == Form1->DataParts->Items->Count/(PartsColCount+1) )
                mem_prev_count = Form1->StringGridParts->RowCount;
        else
                mem_prev_count = MAX( mem_prev_count, Form1->StringGridParts->RowCount );
        i = -1;
        if (Form1->CRefDes->Text.Length())
                i = Form1->StringGridParts->Cols[def_RefDes]->IndexOf(Form1->CRefDes->Text);
        if (i >= 0)
                Form1->StringGridParts->Row = i;
        if( Form1->StringGridParts->Cells[def_RefDes][Form1->StringGridParts->RowCount-1].Length() )
                Form1->n_el1->Caption = AnsiString(Form1->StringGridParts->RowCount);
        else    Form1->n_el1->Caption = AnsiString(Form1->StringGridParts->RowCount-1);
        Form1->n_el1->Left = Form1->Parts->ClientWidth - Form1->n_el1->Width - 3;
        }
else if (TIndex == 1)
        {
        if(Total)
                Total = CheckGrid1();
        int Check_FLT = CheckGrid2();
        RowIndex = -1;
        Form1->StringGridPins->RowCount = Form1->DataPins->Items->Count/(PinsColCount+1);
        AnsiString DataPin;
        while(shift < Form1->DataPins->Items->Count)
                {
                BoolAdd = true;
                if( Total || Check_FLT ) while(1)
                        {
                        DataPin = Form1->DataPins->Items->operator [](shift+col_Pin+1);
                        //Pin
                        int ps = DataPin.Pos(".");
                        if (ps > 0)
                                {
                                if( Total )
                                        if (Form1->StringGridParts->Cols[def_RefDes]->IndexOf(DataPin.SubString(1,(ps-1))) == -1)
                                                {BoolAdd = false;break;}
                                //Deletes
                                if (Form1->Deleted->Items->IndexOf(DataPin.SubString(1,(ps-1))) >= 0)
                                        {
                                        BoolAdd = false;
                                        break;
                                        }
                                }
                        if (Form1->CPin->Text.Length() && includePin.Length() == 0 )
                                {
                                BoolAdd = CMPR( shift, col_Pin );
                                if( !BoolAdd )
                                        break;
                                }
                        // flag pin ref only
                        if( Check_FLT == 1 )
                                break;
                        //Net PCB
                        if (Form1->CPinNetPCB->Text.Length())
                                {
                                BoolAdd = CMPR( shift, col_NetPcb );
                                if( !BoolAdd )
                                        break;
                                }
                        //Net list
                        if (Form1->CNetNetlist->Text.Length())
                                {
                                B = Form1->CNetNetlist->Text;
                                int invers = 0;
                                if( B.SubString(1,1) == "!" && B.Length() > 1 )
                                        {
                                        invers = 1;
                                        B = B.SubString(2,B.Length()-1);
                                        }
                                if (B.SubString(1,8) == "Changes")
                                        {
                                        AnsiString S2 = Form1->DataPins->Items->operator [](shift+col_Netlist+1);
                                        if (S2.Length())
                                                {
                                                if (S2.SubString(S2.Length()-1,2) != dSPACE && !invers)
                                                        {BoolAdd = false;break;}
                                                else if (S2.SubString(S2.Length()-1,2) == dSPACE && invers)
                                                        {BoolAdd = false;break;}
                                                }
                                        if (!NetListPath.Length())
                                                {BoolAdd = false;break;}
                                        }
                                else    {
                                        BoolAdd = CMPR( shift, col_Netlist );
                                        if( !BoolAdd )
                                                break;
                                        }
                                }
                        //Cnt
                        if (Form1->CCnt->Text.Length() )
                                {
                                B = Form1->CCnt->Text;
                                B = B.TrimLeft();
                                AnsiString Data = Form1->DataPins->Items->operator [](shift+col_Cnt+1);
                                if (B.SubString(1,B.Length()) != Data.SubString(1,B.Length())) {BoolAdd = false;break;}
                                }
                        //Type
                        if (Form1->CType->Text.Length() )
                                {
                                B = Form1->CType->Text;
                                B = B.TrimLeft();
                                bool invers = false;
                                if (B.SubString(1,1) == "!")
                                        {
                                        invers = true;
                                        B = B.SubString(2,(B.Length()-1));
                                        }
                                AnsiString Data = Form1->DataPins->Items->operator [](shift+col_Type+1);
                                if (B.UpperCase().SubString(1,B.Length()) != Data.UpperCase().SubString(1,B.Length()) && !invers)
                                        {BoolAdd = false;break;}
                                else if (B.UpperCase().SubString(1,B.Length()) == Data.UpperCase().SubString(1,B.Length()) && invers)
                                        {BoolAdd = false;break;}
                                }
                        //WPinMin
                        if (Form1->WPinMin->Text.Length())
                                {
                                float MinW = StrToFloat(Str_Float_Format(Form1->WPinMin->Text));
                                float Data__W = StrToFloat(Str_Float_Format(Form1->DataPins->Items->operator [](shift+col_W+1)));
                                if (Data__W < MinW) {BoolAdd = false;break;}
                                }
                        //WPinMax
                        if (Form1->WPinMax->Text.Length())
                                {
                                float MaxW = StrToFloat(Str_Float_Format(Form1->WPinMax->Text));
                                float Data__W = StrToFloat(Str_Float_Format(Form1->DataPins->Items->operator [](shift+col_W+1)));
                                if (Data__W > MaxW) {BoolAdd = false;break;}
                                }
                        //LPinMin
                        if (Form1->LPinMin->Text.Length())
                                {
                                float MinL = StrToFloat(Str_Float_Format(Form1->LPinMin->Text));
                                float Data__L = StrToFloat(Str_Float_Format(Form1->DataPins->Items->operator [](shift+col_L+1)));
                                if (Data__L < MinL) {BoolAdd = false;break;}
                                }
                        //LPinMax
                        if (Form1->LPinMax->Text.Length())
                                {
                                float MaxL = StrToFloat(Str_Float_Format(Form1->LPinMax->Text));
                                float Data__L = StrToFloat(Str_Float_Format(Form1->DataPins->Items->operator [](shift+col_L+1)));
                                if (Data__L > MaxL) {BoolAdd = false;break;}
                                }
                        //Trml
                        if (Form1->CTrml->Text.Length() )
                                {
                                B = Form1->CTrml->Text;
                                AnsiString Data = Form1->DataPins->Items->operator [](shift+col_Thrml+1);
                                if (B.SubString(1,B.Length()) != Data.SubString(1,B.Length())) {BoolAdd = false;break;}
                                }
                        //WHoleMin
                        if (Form1->DHoleMin->Text.Length())
                                {
                                float MinD = StrToFloat(Str_Float_Format(Form1->DHoleMin->Text));
                                float Data__D = StrToFloat(Str_Float_Format(Form1->DataPins->Items->operator [](shift+col_DHole+1)));
                                if (Data__D < MinD) {BoolAdd = false;break;}
                                }
                        //WHoleMax
                        if (Form1->DHoleMax->Text.Length())
                                {
                                float MaxD = StrToFloat(Str_Float_Format(Form1->DHoleMax->Text));
                                float Data__D = StrToFloat(Str_Float_Format(Form1->DataPins->Items->operator [](shift+col_DHole+1)));
                                if (Data__D > MaxD) {BoolAdd = false;break;}
                                }
                        //Paste
                        if (Form1->Pas->Text.Length())
                                {
                                AnsiString Paste = Form1->Pas->Text;
                                bool invers = false;
                                if (Paste.SubString(1,1) == "!")
                                        {
                                        invers = true;
                                        Paste = Paste.SubString(2,(Paste.Length()-1));
                                        }
                                AnsiString Data__P = Form1->DataPins->Items->operator [](shift+col_Pas+1);
                                if (Form2->IgnoreCase->Checked)
                                        {
                                        Paste = Paste.UpperCase();
                                        Data__P = Data__P.UpperCase();
                                        }
                                if (Paste.SubString(1,1) == "%" || Paste.SubString(Paste.Length(),1) == " ")
                                        {
                                        bool f = ShareProg (&Paste, Data__P);
                                        if (!f && !invers)    {BoolAdd = false;break;}
                                        else if (f && invers) {BoolAdd = false;break;}
                                        }
                                else if (Paste.SubString(1,Paste.Length()) != Data__P.SubString(1,Paste.Length()) && !invers)
                                        {BoolAdd = false;break;}
                                else if (Paste.SubString(1,Paste.Length()) == Data__P.SubString(1,Paste.Length()) && invers)
                                        {BoolAdd = false;break;}
                                }
                        //XPinMin
                        if (Form1->XPinMin->Text.Length())
                                {
                                float MinX = StrToFloat(Str_Float_Format(Form1->XPinMin->Text));
                                float Data__X = StrToFloat(Str_Float_Format(Form1->DataPins->Items->operator [](shift+col_Xpi+1)));
                                if (Data__X < MinX) {BoolAdd = false;break;}
                                }
                        //XPinMax
                        if (Form1->XPinMax->Text.Length())
                                {
                                float MaxX = StrToFloat(Str_Float_Format(Form1->XPinMax->Text));
                                float Data__X = StrToFloat(Str_Float_Format(Form1->DataPins->Items->operator [](shift+col_Xpi+1)));
                                if (Data__X > MaxX) {BoolAdd = false;break;}
                                }
                        //YPinMin
                        if (Form1->YPinMin->Text.Length())
                                {
                                float MinY = StrToFloat(Str_Float_Format(Form1->YPinMin->Text));
                                float Data__Y = StrToFloat(Str_Float_Format(Form1->DataPins->Items->operator [](shift+col_Ypi+1)));
                                if (Data__Y < MinY) {BoolAdd = false;break;}
                                }
                        //YPinMax
                        if (Form1->YPinMax->Text.Length())
                                {
                                float MaxY = StrToFloat(Str_Float_Format(Form1->YPinMax->Text));
                                float Data__Y = StrToFloat(Str_Float_Format(Form1->DataPins->Items->operator [](shift+col_Ypi+1)));
                                if (Data__Y > MaxY) {BoolAdd = false;break;}
                                }
                        break;
                        }
                else if( RowIndex > mem_prev_count )  // speed optimization
                        break;
                //Add
                if(BoolAdd){
                        RowIndex++;
                        for(int ii=col_Pin; ii<PinsColCount; ii++)
                                Form1->StringGridPins->Cells[ii][RowIndex] = Form1->DataPins->Items->operator [](shift+ii+1);
                        }
                shift = shift + PinsColCount + 1;
                }
        // limit row count
        if( Total || Check_FLT )
                Form1->StringGridPins->RowCount = MAX(1,RowIndex+1);
        // speed optimization
        if( mem_prev_count == Form1->DataPins->Items->Count/(PinsColCount+1) )
                mem_prev_count = Form1->StringGridPins->RowCount;
        else
                mem_prev_count = MAX( mem_prev_count, Form1->StringGridPins->RowCount );
        // clear first string
        if(RowIndex == -1)
                for(int ii=col_Pin; ii<PinsColCount; ii++)
                        Form1->StringGridPins->Cells[ii][0] = "";
        else if( check_single_pin() && includePin.Length() == 0 && Form1->CPin->Text.Length() )
                {
                // recall filter for show the net
                if( Form1->CPinNetPCB->Text.Length() == 0 )
                        {
                        Form1->CPinNetPCB->Text = Form1->StringGridPins->Cells[col_NetPcb][0] + dSPACE;
                        FilterAll(1, Form1->CPin->Text);
                        }
                else if( Form1->CPinNetPCB->Text.Length() > 2 )
                        {
                        if( Form1->CPinNetPCB->Text.SubString(Form1->CPinNetPCB->Text.Length()-1,2) == dSPACE )
                                {
                                Form1->CPinNetPCB->Text = Form1->StringGridPins->Cells[col_NetPcb][0] + dSPACE;
                                FilterAll(1, Form1->CPin->Text);
                                }
                        }
                }
        else if( RowIndex )
                {
                // show pin
                i = 1;
                if( includePin.Length() )
                        B = includePin;
                else
                        B = Form1->CPin->Text;
                B = while_not_space(B,&i);
                B = B.TrimRight();
                i = -1;
                if (B.Length())
                        i = Form1->StringGridPins->Cols[def_Pin]->IndexOf(B);
                if (i >= 0)
                        {
                        Form1->StringGridPins->Row = i;
                        }
                else if( includePin.Length() )
                        {
                        for(int ii=0; ii<Form1->StringGridPins->RowCount; ii++)
                                if( Form1->StringGridPins->Cells[def_Pin][ii].LowerCase().SubString(1,includePin.Length()) == includePin.LowerCase().SubString(1,includePin.Length())  )
                                        {
                                        Form1->StringGridPins->Row = ii;
                                        break;
                                        }
                        }
                }
        StringGridPinsRowIndex = Form1->StringGridPins->Row;
        if( Form1->StringGridPins->Cells[def_RefDes][Form1->StringGridPins->RowCount-1].Length() )
                Form1->n_el2->Caption = AnsiString(Form1->StringGridPins->RowCount);
        else    Form1->n_el2->Caption = AnsiString(Form1->StringGridPins->RowCount-1);
        Form1->n_el2->Left = Form1->Pins->ClientWidth - Form1->n_el2->Width - 3;
        }
Form1->StringGridParts->Visible = Vis1;
Form1->StringGridPins->Visible = Vis2;
Form1->SortedBox->Items->Clear();
Form1->Caption = "Infobox";
}//filter end
