//---------------------------------------------------------------------------


#pragma hdrstop

#include "Read_File.h"
#include "Comp_man.h"
#include "fstream.h"
#include "Path_EXE.h"
//---------------------------------------------------------------------------
#define maximum_number_of_parts 9999


#pragma package(smart_init)
int CW = 0x2000;
int TOP = 0x4000;
static int save_copper_layers = 0;
struct prev_footprint
{
        AnsiString name;
        int i;
};
//===========================================================================
// convert angle in degrees from CW to CCW
//
int ccw( int angle )
{
	return (720-angle)%360;
}
//===========================================================================
// Get angle of part as reported in status line, corrected for centroid angle and side
//
int GetReportedAngleForPart( int part_angle, int cent_angle, int side )
{
	int angle = (360 + part_angle - cent_angle) % 360; 
	if( side )
		angle = (angle + 180) % 360;
	return ccw(angle);
}

//===========================================================================
void mirror_angle (int Part_angle, bool Part_layer, float *X, float *Y)
        {
        if(Part_layer ){(*X) = -(*X);}
        Rotate_Vertex (X, Y, -Part_angle);
        }
//===========================================================================
int iof1(AnsiString * pin, AnsiString * pcb_net)
        {
        int RET=-1;
        AnsiString find = pin->TrimRight();
        int fl = find.Length();
        for( int ii=0; ii<Form1->DataParts->Items->Count; ii++ )
                {
                AnsiString Out = Form1->DataParts->Items->operator [](ii);
                AnsiString Q = Out.TrimRight();
                int ql = Q.Length();
                if( Q.SubString(1,1) == DOG )
                        {
                        *pcb_net = Q.SubString(2,ql-1);
                        RET = ii;
                        }
                else    {
                        if( fl == ql )
                                if( Q.SubString(1,fl) == find.SubString(1,fl) )
                                        {
                                        *pin = Out;
                                        return RET;
                                        }
                        }
                }
        *pcb_net = "";
        return -1;
        }
//===========================================================================
int iof2(AnsiString find, AnsiString * nl_net)
        {
        int RET=-1;
        find = find.TrimRight();
        int fl = find.Length();
        for( int ii=0; ii<Form1->DataPins->Items->Count; ii++ )
                {
                AnsiString Q = Form1->DataPins->Items->operator [](ii);
                Q = Q.TrimRight();
                int ql = Q.Length();
                if( Q.SubString(1,1) == DOG )
                        {
                        *nl_net = Q.SubString(2,Q.Length()-1);
                        RET = ii;
                        }
                else    {
                        if( fl == ql )
                                if( Q.SubString(1,fl) == find.SubString(1,fl) )
                                        return RET;
                        }
                }
        *nl_net = "";
        return -1;
        }




// extract ref index
AnsiString ExtractRefIndex( AnsiString str )
        {
        int i1=0, i2=0;
        for( int caret=1; caret<=str.Length(); caret++ )
                {
                if( str[caret] >= '0' && str[caret] <= '9')
                        {
                        i1 = caret;
                        break;
                        }
                }
        if(i1)  {
                for( int caret=i1; caret<=str.Length(); caret++ )
                        {
                        if( str[caret] < '0' || str[caret] > '9')
                                {
                                i2 = caret-1;
                                break;
                                }
                        }
                if(!i2)
                        i2 = str.Length();
                }
        if( i1 && i2 )
                {
                AnsiString out;
                if( i2-i1 == 0 )
                        out = "00" + str.SubString(i1,i2-i1+1);
                else if( i2-i1 == 1 )
                        out = "0" + str.SubString(i1,i2-i1+1);
                else
                        out = str.SubString(i1,i2-i1+1);
                return out;
                }
        else    return "000";
        }


AnsiString Read_TXT_Table ( AnsiString path, int order )
        {
        int MAX_NUM_PARTS = 10000;
        AnsiString str;
        if( !FileName.Length())
                return "";
        AnsiString out = path + ".NET";
        ifstream r( path.c_str() );
        ofstream wr( (out).c_str() );
        wr << "*PADS-PCB*" << endl;
        wr << "*PART*" << endl;
        A = "1";
        int c=0;
        while( !r.eof()&&A.Length() )
                {
                n = 0;
                r.getline(s,2500);
                A = s;
                int L = A.Length();
                if( L && A.SubString(1,L) != "*PADS-PCB*" &&
                         A.SubString(1,L) != "*PART" )
                        {
                        AnsiString ref = while_not_space(A,&n);
                        AnsiString val="", foot="";
                        while (n)
                                {
                                if( order )
                                        val += while_not_space(A,&n);
                                else    foot += while_not_space(A,&n);
                                if(n>1)
                                if(A.SubString(n-2,2) == dSPACE || *(A.SubString(n-1,1)).c_str() == '\t')
                                        break;
                                }
                        while (n)
                                {
                                if( order )
                                        foot += while_not_space(A,&n);
                                else    val += while_not_space(A,&n);
                                if(n>1)
                                if(A.SubString(n-2,2) == dSPACE || *(A.SubString(n-1,1)).c_str() == '\t')
                                        break;
                                }
                        val.Trim();
                        foot.Trim();
                        wr << (ref+dSPACE+val).c_str();
                        if( val.Length() || foot.Length() )
                                {
                                if( val.SubString(val.Length(),1) != DOG )
                                        wr << DOG;
                                wr << (foot).c_str();
                                }
                        wr << endl;
                        c++;
                        if( c >= MAX_NUM_PARTS )
                                {
                                ShowMessage("  The maximum number of parts is limited to 10,000.");
                                break;
                                }
                        }
                }
        wr << "*NET*" << endl;
        wr << "*END*" << endl;
        r.close();
        wr.close();
        Sleep(999);
        return out;
        }



//===========================================================================
//-------------               Read_File                      ----------------
//============               ������ �����                      ==============
//===========================================================================

void Read_File (bool CMPR_PINS, bool rNETLIST)
{
if (!BEGIN || FileName.Length() == 0)
        return;
if( NetListPath.Length() == 0 && CMPR_PINS )
        {
        if (Form2->Language->Checked)
                ShowMessage( "������� �� ����������" );
        else
                ShowMessage( "Netlist did not load" );
        return;
        }
//ok
//��������
FILE* F;
F = fopen(FileName.c_str(),"r");
if(F == NULL)
        {
        fclose(F);
        Form1->StringGridParts->Hint = "";
        Form1->StringGridParts->RowCount = 1;
        Form1->StringGridPins->RowCount = 1;
        for (int j=0; j<PartsColCount; j++) Form1->StringGridParts->Cells[j][0] = "";
        for (int j=0; j<PinsColCount; j++)  Form1->StringGridPins->Cells[j][0] = "";
        FileName = "";
        return;
        }
fclose(F);
BEGIN = 0;
Form1->Timer1->Enabled = false;
float default_via_hole_width = 0;
float default_via_pad_width = 0;
short int INDEXPINS[maximum_number_of_parts];

// ���������, reset
if (FileName.SubString(1,FileName.Length()) != FileNameBack.SubString(1,FileNameBack.Length()))
        {
        NetListPath = "";
        }
GerberPath = "";
// save
AnsiString svCMerge = Form1->CMerge->Text;
AnsiString svDHoleMin = Form1->DHoleMin->Text;
AnsiString svDHoleMax = Form1->DHoleMax->Text;
AnsiString svCPinNetPCB = Form1->CPinNetPCB->Text;
AnsiString svCCNetlist = Form1->CCNetlist->Text;
AnsiString svCCnt = Form1->CCnt->Text;
// clear
while( Form1->SF->Items->Count > 4 )
        {
        TMenuItem * M = Form1->SF->Items->operator [](4);
        while( M->Count )
                M->Delete(0);
        Form1->SF->Items->Delete(4);
        }
Form1->Bufer->Items->Clear();
Form1->SortedBox->Items->Clear();
Form1->DataParts->Items->Clear();
Form1->DataPins->Items->Clear();
Form1->CMerge->Items->Clear();
Form1->DHoleMin->Items->Clear();
Form1->DHoleMax->Items->Clear();
Form1->CPinNetPCB->Items->Clear();
Form1->CCnt->Items->Clear();
//
for (int k=0; k<Form1->StringGridParts->RowCount; k++)
        {
        for (int j=0; j<PartsColCount; j++) Form1->StringGridParts->Cells[j][k] = "";
        }
for (int k=0; k<Form1->StringGridPins->RowCount; k++)
        {
        for (int j=0; j<PinsColCount; j++) Form1->StringGridPins->Cells[j][k] = "";
        }
Form1->StringGridParts->RowCount = 1;
Form1->StringGridPins->RowCount = 1;
Form1->PageControl1->Visible = 0;
Form1->CCNetlist->ItemIndex = -1;
int SaveClientHeight = Form1->ClientHeight;
if( SaveClientHeight == 0 )
        SaveClientHeight = MIN_FORM_H;//FORM_MIN_HEIGHT;
if (CMPR_PINS)
        {
        Form1->ProgressBar1->Position = 0;
        Form1->ProgressBar1->Visible = true;
        Form1->ClientHeight = 16;
        Form1->R->Visible = false;
        }
else
        Form1->ClientHeight = 0;
if (Form2->Language->Checked)   Form1->Caption = "  ������ �����...";
else                            Form1->Caption = "  File analysis...";
Application->ProcessMessages();
bool FlagFootpints = false;
ifstream loadFile (FileName.c_str());
A = "";
int PartsIndex = -1;
int MergeIndex = -1;
int insZ = 6;
int count = 0;
int ERR = 1;
Form1->SortedBox->Sorted = false;
Form1->Bufer->Items->LoadFromFile(FileName);
while (!loadFile.eof())
        {
        loadFile.getline(s,2500);
        if( ERR > 0 )
                ERR++;
        if( ERR > 5 )
                {
                Form1->Caption = "File reading suspended. Restricted file access...";
                FileNameBack = FileName;
                BEGIN = true;
                Form1->Timer1->Interval = 4000;
                Form1->Timer1->Enabled = true;
                return;
                }
        A = s;
        A = A.Trim();
        if (!FlagFootpints)
                {
                if( A.SubString(1,9) == "[options]" )
                        ERR = -1;
                if (A.SubString(1,23) == "default_via_hole_width:")
                        {
                        i = 24;
                        int ptr_U = 0;
                        default_via_hole_width = ex_float_NM(A,&i,-1,&ptr_U);
                        if( ptr_U > UNITS )
                                default_via_hole_width *= MM_TO_MIL;
                        else if( ptr_U < UNITS )
                                default_via_hole_width /= MM_TO_MIL;
                        }
                else if (A.SubString(1,22) == "default_via_pad_width:" )
                        {
                        i = 23;
                        int ptr_U = 0;
                        default_via_pad_width = ex_float_NM(A,&i,-1,&ptr_U);
                        if( ptr_U > UNITS )
                                default_via_pad_width *= MM_TO_MIL;
                        else if( ptr_U < UNITS )
                                default_via_pad_width /= MM_TO_MIL;
                        }
                /*else if (A.SubString(1,18) == "netlist_file_path:" )
                        {
                        if( NetListPath.Length() == 0 )
                                {
                                i = 19;
                                NetListPath = ex_str(A,&i);
                                }
                        if( NetListPath.SubString(1,1) != "#" )
                                {
                                i = 19;
                                NetListPath = ex_str(A,&i);
                                }
                        }*/
                else if (A.SubString(1,11) == "cam_folder:")
                        {
                        i = 12;
                        GerberPath = ex_str(A,&i);
                        }
                else if ((A.SubString(1,6) == "units:")&&(!FlagFootpints))
                        {
                        i = 7;
                        B = while_not_space(A,&i);
                        if (B.LowerCase().SubString(1,2) == "mm")       UNITS = 1;
                        else                                            UNITS = 0;
                        if (UNITS)      insZ = 5;
                        else            insZ = 6;
                        AnsiString HSTR = F_str(0.0,insZ);
                        Form1->DHoleMin->Items->Add(HSTR);
                        Form1->DHoleMax->Items->Add(HSTR);
                        }
                else if (A.SubString(1,16) == "n_copper_layers:" )
                        {
                        i = 17;
                        n_copper_layers = ex_float_NM(A,&i,-1);
                        }
                else if(A.SubString(1,14) == "report_options" )
			{
                        i = 15;
                        m_report_flags = ex_float_NM(A,&i,-1);
			}
                else if (A.SubString(1,12) == "[footprints]")
                        FlagFootpints = true;
                }
        else if (MergeIndex >= 0)
                {
                if (A.SubString(1,6) == "merge:")
                        {
                        i = 7;
                        B = ex_str(A,&i);
                        B = B.Trim();
                        Form1->CMerge->Items->Add(B);
                        }
                }
        else if (A.SubString(1,7) == "[parts]")
                PartsIndex = count;
        else if (A.SubString(1,8) == "[merges]")
                MergeIndex = count;
        count++;
        }
loadFile.close();
if (Form2->Language->Checked)   Form1->Caption = "  ������ �����...";
else                            Form1->Caption = "  Reading the file...";
Application->ProcessMessages();

// loading filters
TSearchRec sr;
AnsiString CAT = ExtractFilePath(FileName);
if (FindFirst((CAT+"related_files\\infobox\\*"), faAnyFile, sr) == 0)
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
                                if (  sr.Name.SubString((sr.Name.Length()-1), 2) == ".r"
                                   || sr.Name.SubString((sr.Name.Length()-1), 2) == ".v"
                                   || sr.Name.SubString((sr.Name.Length()-1), 2) == ".p" )
                                        {
                                        TMenuItem * n1 = new TMenuItem(Form1);
                                        n1->Caption = sr.Name;
                                        Form1->SF->Items->Add(n1);
                                        //
                                        TMenuItem * add1 = new TMenuItem(Form1);
                                        add1->Caption = "Attach current list";
                                        TMenuItem * remove1 = new TMenuItem(Form1);
                                        remove1->Caption = "Remove current list";
                                        TMenuItem * open1 = new TMenuItem(Form1);
                                        open1->Caption = "Open";
                                        TMenuItem * translate1 = new TMenuItem(Form1);
                                        translate1->Caption = "Perform";
                                        n1->Add(translate1);
                                        n1->Add(open1);
                                        n1->Add(add1);
                                        n1->Add(remove1);
                                        n1->InsertNewLineAfter(open1);
                                        add1->OnClick = Form1->MItemClick;
                                        remove1->OnClick = Form1->MItemClick;
                                        open1->OnClick = Form1->MItemClick;
                                        translate1->OnClick = Form1->MItemClick;
                                        }
                                }
                        }
                }while (FindNext(sr) == 0);
        }
//
// loading parts and pins
A = "";
long Index = PartsIndex;
if (Index == -1)
        {
        BEGIN = true;
        Form1->Timer1->Enabled = true;
        return;
        }
int PartGridIndex = -1;
int PinGridIndex = -1;
float PosX;
float PosY;
int Side;
int Angle;
int AxisAn=0;
AnsiString SHAPE="";
AnsiString PartPackage="";
prev_footprint Prev;
Prev.name = "";
PinsWasR = (Form1->PageControl1->TabIndex>0 || rNETLIST);
while (A.SubString(1,6) != "[nets]")
        {
        A = Form1->Bufer->Items->operator[](Index);
        i = prob(A,1);
        A = A.Trim();
        if (A.SubString(1,4) == "part" )
                {
                SHAPE = "";
                PartPackage = "";
                PartGridIndex++;
                if (PartGridIndex)
                        Form1->StringGridParts->RowCount++;
                B = while_not_space(A, &i);
                Form1->StringGridParts->Cells[def_RefDes][PartGridIndex] = B;
                Form1->StringGridParts->Cells[def_RIRange][PartGridIndex] = ExtractRefIndex(B);
                Form1->StringGridParts->Cells[def_Value][PartGridIndex] = EMP;
                Form1->StringGridParts->Cells[def_ValueNL][PartGridIndex] = EMP;
                Form1->StringGridParts->Cells[def_Package][PartGridIndex] = EMP;
                Form1->StringGridParts->Cells[def_PackageNL][PartGridIndex] = EMP;
                Form1->StringGridParts->Cells[def_FootPrint][PartGridIndex] = EMP;
                Form1->StringGridParts->Cells[def_Merge][PartGridIndex] = EMP;
                Form1->StringGridParts->Cells[def_Pins][PartGridIndex] = "000";
                Form1->StringGridParts->Cells[def_Holes][PartGridIndex] = EMP;
                if (Form2->Language->Checked)
                        Form1->StringGridParts->Cells[def_CompareNetlist][PartGridIndex] = "������_��_�����";
                else
                        Form1->StringGridParts->Cells[def_CompareNetlist][PartGridIndex] = "Only_on_the_Board";
                Form1->SortedBox->Items->Add(B);
                Form1->SortedBox->Items->Add(PartGridIndex);
                INDEXPINS[PartGridIndex] = -1;
                }
        else if (A.SubString(1,5) == "merge" )
                {
                if( A.SubString(1,1) != "\"" )
                        {
                        i = 7;
                        int m_id = ex_float_NM(A,&i,-1);
                        if( m_id >= 0 && m_id < Form1->CMerge->Items->Count )
                                {
                                B = Form1->CMerge->Items->operator [](m_id);
                                if (B.Length())
                                        Form1->StringGridParts->Cells[def_Merge][PartGridIndex] = B;
                                }
                        }
                }
        else if (A.SubString(1,5) == "value" )
                {
                B = ex_str(A, &i);
                B = B.Trim();
                if( B.Length() )
                        Form1->StringGridParts->Cells[def_Value][PartGridIndex] = B;
                }
        else if (A.SubString(1,5) == "shape" )
                {
                SHAPE = ex_str(A, &i);
                Form1->StringGridParts->Cells[def_FootPrint][PartGridIndex] = SHAPE;
                }
        else if (A.SubString(1,7) == "package" )
                {
                PartPackage = ex_str(A, &i);
                Form1->StringGridParts->Cells[def_Package][PartGridIndex] = PartPackage;
                }
        else if (A.SubString(1,3) == "pos" )
                {
                int ins0;
                if (UNITS)      ins0 = 6;
                else            ins0 = 8;
                PosX = ex_float_NM(A,&i,UNITS);
                Form1->StringGridParts->Cells[def_Xprt][PartGridIndex] = F_str(PosX,ins0);
                PosY = ex_float_NM(A,&i,UNITS);
                Form1->StringGridParts->Cells[def_Yprt][PartGridIndex] = F_str(PosY,ins0);
                Side = ex_float_NM(A,&i,-1);
                if (Side && Form2->Language->Checked)
                        Form1->StringGridParts->Cells[def_S][PartGridIndex] = "�";
                else if (!Side && Form2->Language->Checked)
                        Form1->StringGridParts->Cells[def_S][PartGridIndex] = "�";
                else if (Side && !Form2->Language->Checked)
                        Form1->StringGridParts->Cells[def_S][PartGridIndex] = "B";
                else if (!Side && !Form2->Language->Checked)
                        Form1->StringGridParts->Cells[def_S][PartGridIndex] = "T";
                Angle = ex_float_NM(A,&i,-1);
                //
                int GL= ex_float_NM(A,&i,-1);
                if (GL && Form2->Language->Checked)
                        Form1->StringGridParts->Cells[def_Gl][PartGridIndex] = "��";
                else if (!GL && Form2->Language->Checked)
                        Form1->StringGridParts->Cells[def_Gl][PartGridIndex] = "���";
                else if (GL && !Form2->Language->Checked)
                        Form1->StringGridParts->Cells[def_Gl][PartGridIndex] = "Yes";
                else if (!GL && !Form2->Language->Checked)
                        Form1->StringGridParts->Cells[def_Gl][PartGridIndex] = "No";
                //
                bool ON_PAS_ALL = true;
                bool OFF_PAS_ALL = true;
                int Cpins = 0;
                int Choles= 0;
                int unitsF = 0;
                int n_pins = 0;
                float hdiam;  //hole diam
                long AN;      //angle pin
                int ftpr;
                if( Prev.name.Length() && Prev.name.SubString(1,Prev.name.Length()) == SHAPE.SubString(1,SHAPE.Length()))
                        ftpr = Prev.i;
                else    ftpr = Form1->Bufer->Items->IndexOf("name: \""+SHAPE+"\"");
                if (ftpr != -1)
                        {
                        Prev.name = SHAPE;
                        Prev.i = ftpr;
                        while(1)//READING FOOTPRINT
                                {
                                ftpr++;
                                B = Form1->Bufer->Items->operator [](ftpr);
                                B = B.Trim();
                                if (B.SubString(1,4) == "name" )
                                        break;
                                else if (B.SubString(1,7) == "[board]")
                                        break;
                                else if (B.SubString(1,5) == "units")
                                        {
                                        i = prob(B,1);
                                        AnsiString C = while_not_space(B,&i);
                                        if (UNITS)
                                        if (C.LowerCase().SubString(1,2) == "nm")       unitsF = 1;
                                        else                                            unitsF = 2;
                                        else if (C.LowerCase().SubString(1,2) == "nm")  unitsF = 0;
                                        else                                            unitsF = -1;
                                        }
                                else if (B.SubString(1,7) == "package")
                                        {
                                        if (PartPackage.Length() == 0)
                                                {
                                                i = 9;
                                                PartPackage = ex_str(B, &i);
                                                Form1->StringGridParts->Cells[def_Package][PartGridIndex] = PartPackage;
                                                }
                                        }
                                else if (B.SubString(1,6) == "n_pins" )
                                        {
                                        i = 6;
                                        n_pins = ex_float_NM(B,&i,-1);
                                        if ( n_pins <= 999 )
                                                Form1->StringGridParts->Cells[def_Pins][PartGridIndex] = AnsiString(F_str(n_pins,6)).SubString(1,3);
                                        else    Form1->StringGridParts->Cells[def_Pins][PartGridIndex] = ">999";
                                        if(PinsWasR==0)
                                                break;
                                        }
                                else if (B.SubString(1,8) == "centroid")
                                        {
                                        i = prob(B,2);
                                        float Xmod = ex_float_NM(B,&i,unitsF);
                                        float Ymod = ex_float_NM(B,&i,unitsF);
                                        AxisAn = ex_float_NM(B,&i,-1);
                                        // Report Angle
                                        int Gen_A = GetReportedAngleForPart( Angle, AxisAn, Side );
                                        if( m_report_flags & CW )
						Gen_A = ccw(Gen_A);		// degrees cw
					if( !(m_report_flags & TOP) )
						Gen_A = 180 - Gen_A;	        // viewed from bottom, flipped left-right
					if( Gen_A < 0.0 )
						Gen_A += 360.0;
                                        Form1->StringGridParts->Cells[def_Ang][PartGridIndex] = AnsiString(Gen_A);
                                        //
                                        mirror_angle(Angle, Side, &Xmod, &Ymod);
                                        int ins0;
                                        if (UNITS)      ins0 = 6;
                                        else            ins0 = 8;
                                        Form1->StringGridParts->Cells[def_Xprt][PartGridIndex] = F_str(PosX+Xmod,ins0);
                                        Form1->StringGridParts->Cells[def_Yprt][PartGridIndex] = F_str(PosY+Ymod,ins0);
                                        }
                                else if (B.SubString(1,3) == "pin" )
                                        {
                                        if (Cpins)
                                                {
                                                if (Form1->StringGridPins->Cells[def_Pas][PinGridIndex].SubString(2,1) == "n")
                                                        OFF_PAS_ALL = false;
                                                else    ON_PAS_ALL = false;
                                                }
                                        Cpins++;
                                        PinGridIndex++;
                                        if (Cpins == 1)
                                                INDEXPINS[PartGridIndex] = PinGridIndex;
                                        AnsiString fNet = "Unconnected";
                                        if (Form2->Language->Checked)
                                                fNet = "�� �����.";
                                        //
                                        Form1->StringGridPins->Cells[def_NetPcb][PinGridIndex] = fNet;
                                        Form1->StringGridPins->Cells[def_Netlist][PinGridIndex] = fNet;
                                        if (PinGridIndex)
                                                Form1->StringGridPins->RowCount++;
                                        i = prob(B,1);
                                        AnsiString name = ex_str(B, &i);
                                        hdiam = ex_float_NM(B,&i,unitsF);
                                        float XP = ex_float_NM(B,&i,unitsF);
                                        float YP = ex_float_NM(B,&i,unitsF);
                                        AN = ex_float_NM(B,&i,-1);
                                        mirror_angle(Angle, Side, &XP, &YP);
                                        AnsiString HOLESTR = F_str(hdiam,insZ);
                                        if (hdiam > 0.001)
                                                {
                                                Choles++;
                                                if (Form1->DHoleMin->Items->IndexOf(HOLESTR) == -1)
                                                        {
                                                        Form1->DHoleMin->Items->Add(HOLESTR);
                                                        Form1->DHoleMax->Items->Add(HOLESTR);
                                                        }
                                                Form1->StringGridPins->Cells[def_Pas][PinGridIndex] = "Off";
                                                }
                                        else    {
                                                Form1->StringGridPins->Cells[def_Pas][PinGridIndex] = "On";
                                                }
                                        Form1->StringGridPins->Cells[def_Type][PinGridIndex] = "None";
                                        Form1->StringGridPins->Cells[def_DHole][PinGridIndex] = HOLESTR;
                                        Form1->StringGridPins->Cells[def_Xpi][PinGridIndex] = F_str(XP + PosX,ins0);
                                        Form1->StringGridPins->Cells[def_Ypi][PinGridIndex] = F_str(YP + PosY,ins0);
                                        Form1->StringGridPins->Cells[def_Pin][PinGridIndex] = Form1->StringGridParts->Cells[def_RefDes][PartGridIndex] + "." + name;
                                        }
                                else if (B.SubString(1,7) == "top_pad" || (B.SubString(1,10) == "bottom_pad" && hdiam < 0.01))
                                        {
                                        i = 9;
                                        int Type = ex_float_NM(B,&i,-1);
                                        float w = ex_float_NM(B,&i,unitsF);
                                        float h = ex_float_NM(B,&i,unitsF)*2;
                                        if      (Type == 0) {h = 0;w = 0;}
                                        else if (Type == 1 || Type == 2 || Type == 6) h = w;
                                        int an_sum = AN+Angle;
                                        if (an_sum > 359) an_sum -= 360;
                                        if (an_sum == 90 || an_sum == 270)
                                                {
                                                float WL = w + h;
                                                w = WL - w;
                                                h = WL - w;
                                                }
                                        ex_float_NM(B,&i,unitsF);
                                        ex_float_NM(B,&i,unitsF);
                                        int Thrml = ex_float_NM(B,&i,-1);
                                        if (Form2->Language->Checked) Type = Type + N_PAD_SH;
                                        switch (Type){
                                                case NONE: Form1->StringGridPins->Cells[def_Type][PinGridIndex] = "None";
                                                       break;
                                                case CIRC: Form1->StringGridPins->Cells[def_Type][PinGridIndex] = "Round";
                                                       break;
                                                case SQUA: Form1->StringGridPins->Cells[def_Type][PinGridIndex] = "Square";
                                                       break;
                                                case RECT_: Form1->StringGridPins->Cells[def_Type][PinGridIndex] = "Rect";
                                                       break;
                                                case RNDR: Form1->StringGridPins->Cells[def_Type][PinGridIndex] = "RndRect";
                                                       break;
                                                case OVAL: Form1->StringGridPins->Cells[def_Type][PinGridIndex] = "Oval";
                                                       break;
                                                case OCTA: Form1->StringGridPins->Cells[def_Type][PinGridIndex] = "Octagon" ;
                                                       break;
                                                case NONE+N_PAD_SH: Form1->StringGridPins->Cells[def_Type][PinGridIndex] = "���";
                                                       break;
                                                case CIRC+N_PAD_SH: Form1->StringGridPins->Cells[def_Type][PinGridIndex] = "����";
                                                       break;
                                                case SQUA+N_PAD_SH: Form1->StringGridPins->Cells[def_Type][PinGridIndex] = "�������";
                                                       break;
                                                case RECT_+N_PAD_SH: Form1->StringGridPins->Cells[def_Type][PinGridIndex] = "�������";
                                                       break;
                                                case RNDR+N_PAD_SH: Form1->StringGridPins->Cells[def_Type][PinGridIndex] = "�������";
                                                       break;
                                                case OVAL+N_PAD_SH: Form1->StringGridPins->Cells[def_Type][PinGridIndex] = "����";
                                                       break;
                                                case OCTA+N_PAD_SH: Form1->StringGridPins->Cells[def_Type][PinGridIndex] = "�������" ;
                                                       break;
                                                }
                                        Form1->StringGridPins->Cells[def_W][PinGridIndex] = F_str(w,ins0-1);
                                        Form1->StringGridPins->Cells[def_L][PinGridIndex] = F_str(h,ins0-1);
                                        switch (Thrml){
                                                case 0: Form1->StringGridPins->Cells[def_Thrml][PinGridIndex] = "Default";
                                                        break;
                                                case 1: Form1->StringGridPins->Cells[def_Thrml][PinGridIndex] = "NC";
                                                        break;
                                                case 2: Form1->StringGridPins->Cells[def_Thrml][PinGridIndex] = "Thermal";
                                                        break;
                                                case 3: Form1->StringGridPins->Cells[def_Thrml][PinGridIndex] = "NoThrml";
                                                        break;
                                                }
                                        }
                                else if (B.SubString(1,9) == "top_paste" || (B.SubString(1,12) == "bottom_paste" && hdiam < 0.01))
                                        {
                                        i = 11;
                                        int T = ex_float_NM(B,&i,-1);
                                        if (!T) {
                                                Form1->StringGridPins->Cells[def_Pas][PinGridIndex] = "Off";
                                                ON_PAS_ALL = false;
                                                }
                                        else    {
                                                Form1->StringGridPins->Cells[def_Pas][PinGridIndex] = "On";
                                                OFF_PAS_ALL = false;
                                                }
                                        }
                                }
                        }
                if (n_pins != Cpins && PinsWasR)
                        ShowMessage("    EN: Error! number of pins and n_pins is different.\n    n_pins = " +
                        AnsiString(n_pins) + "\n    Cpins = " + AnsiString(Cpins) + "\n    " + Prev.name );
                if (Cpins)
                        {
                        if (Form1->StringGridPins->Cells[def_Pas][PinGridIndex].SubString(2,1) == "n")
                                OFF_PAS_ALL = false;
                        else    ON_PAS_ALL = false;
                        }
                if  ( ON_PAS_ALL || OFF_PAS_ALL )
                        for (int indx=0; indx<Cpins; indx++)
                                {
                                if      (ON_PAS_ALL)  Form1->StringGridPins->Cells[def_Pas][PinGridIndex-indx] = "On(All)";
                                else if (OFF_PAS_ALL) Form1->StringGridPins->Cells[def_Pas][PinGridIndex-indx] = "Off(All)";
                                }
                if( PinsWasR )
                        {
                        if ( Choles <= 999 )
                                Form1->StringGridParts->Cells[def_Holes][PartGridIndex] = AnsiString(F_str(Choles,6)).SubString(1,3);
                        else    Form1->StringGridParts->Cells[def_Holes][PartGridIndex] = ">999";
                        }
                }
        Index++;
        }
AnsiString currentnet = EMP;
AnsiString CountNetPins = "000";
int nvia = 1;
long def_w;
long def_hole;
if (Form2->Language->Checked)   Form1->Caption = "  �������� �����...";
else                            Form1->Caption = "  Loading nets...";
Application->ProcessMessages();
if(PinsWasR) while (A.SubString(1,7) != "[texts]")
        {
        A = Form1->Bufer->Items->operator [](Index);
        A = A.Trim();
        if (A.SubString(1,1) == "c" || A.SubString(1,1) == "s")
                {
                // EMPTY
                }
        else if (A.SubString(1,3) == "vtx")
                {
                i = prob(A,5);
                int Flag =     ex_float_NM(A,&i,-1);
                float w =       ex_float_NM(A,&i,UNITS);
                float hole =    ex_float_NM(A,&i,UNITS);
                if ( Flag && w < BY_ZERO )
                        {
                        if ( def_w > BY_ZERO )
                                {
                                w = def_w;
                                hole = def_hole;
                                }
                        else    {
                                w = default_via_pad_width;
                                hole = default_via_hole_width;
                                }
                        }
                if (hole > BY_ZERO)
                        {
                        AnsiString Strhole = F_str(hole,insZ);
                        if (Form1->DHoleMin->Items->IndexOf(Strhole) == -1)
                                {
                                Form1->DHoleMin->Items->Add(Strhole);
                                Form1->DHoleMax->Items->Add(Strhole);
                                }
                        }
                if ( w > BY_ZERO && Form2->check_vias->Checked)
                        {
                        int ins0;
                        if (UNITS)      ins0 = 6;
                        else            ins0 = 8;
                        i = prob(A,2);
                        float vX =      ex_float_NM(A,&i,UNITS);
                        float vY =      ex_float_NM(A,&i,UNITS);
                        PinGridIndex++;
                        if (PinGridIndex)  Form1->StringGridPins->RowCount++;
                        AnsiString Strw = F_str(w,ins0-1);
                        AnsiString Strhole = F_str(hole);
                        Form1->StringGridPins->Cells[def_Pin][PinGridIndex] = AnsiString("Via�" + AnsiString(nvia));
                        Form1->StringGridPins->Cells[def_NetPcb][PinGridIndex] = currentnet;
                        Form1->StringGridPins->Cells[def_Netlist][PinGridIndex] = "";
                        Form1->StringGridPins->Cells[def_W][PinGridIndex] = Strw;
                        Form1->StringGridPins->Cells[def_L][PinGridIndex] = Strw;
                        Form1->StringGridPins->Cells[def_DHole][PinGridIndex] = Strhole;
                        Form1->StringGridPins->Cells[def_Pas][PinGridIndex] = "";
                        Form1->StringGridPins->Cells[def_Xpi][PinGridIndex] = F_str(vX,ins0);
                        Form1->StringGridPins->Cells[def_Ypi][PinGridIndex] = F_str(vY,ins0);
                        nvia++;
                        }
                }
        else if (A.SubString(1,3) == "pin")
                {
                i = prob(A,2);
                AnsiString pin = while_not_space(A,&i);
                pin = pin.Trim();
                int ind = Form1->StringGridPins->Cols[def_Pin]->IndexOf(pin);
                if (ind != -1)
                        {
                        AnsiString ref = Form1->StringGridPins->Cells[def_Pin][ind];
                        AnsiString pinn = Form1->StringGridPins->Cells[def_Pin][ind];
                        int pp = ref.Pos(".");
                        if( pp > 0 )
                                {
                                ref = ref.SubString(1,pp);
                                int pinn_len = pinn.Length();
                                int ref_len = ref.Length();
                                for( int ii = ind+1; ii<Form1->StringGridPins->RowCount; ii++ )
                                        {
                                        AnsiString str = Form1->StringGridPins->Cells[def_Pin][ii];
                                        if( str.SubString(1,ref_len) != ref.SubString(1,ref_len) )
                                                break;
                                        if( str.SubString(1,str.Length()) == pinn.SubString(1,pinn_len) )
                                                Form1->StringGridPins->Cells[def_NetPcb][ii] = currentnet;
                                        }
                                }
                        Form1->StringGridPins->Cells[def_NetPcb][ind] = currentnet;
                        Form1->StringGridPins->Cells[def_Cnt][ind] = CountNetPins;
                        }
                AnsiString part;
                ind = pin.Pos(".");
                if( ind > 1 )
                        {
                        part = pin.SubString(1, ind-1);
                        ind = Form1->StringGridParts->Cols[def_RefDes]->IndexOf(part);
                        if( ind != -1 )
                                if( Form1->StringGridParts->Cells[def_Pins][ind].SubString(1,3) == "002" )
                                        pin = pin + dSPACE;
                        }
                Form1->DataParts->Items->Add(pin);
                }
        else if (A.SubString(1,3) == "net")
                {
                i = prob(A,1);
                currentnet = ex_str(A,&i);
                int cnp = ex_float_NM(A,&i,-1);
                Form1->DataParts->Items->Add(DOG + currentnet);
                i = prob(A,6);
                def_w =         ex_float_NM(A,&i,UNITS);
                def_hole =      ex_float_NM(A,&i,UNITS);
                //
                CountNetPins = AnsiString(cnp);
                for (int u=CountNetPins.Length(); u<3; u++)
                        CountNetPins = "0" + CountNetPins;
                if (Form1->CCnt->Items->IndexOf(CountNetPins) == -1)
                        Form1->CCnt->Items->Add(CountNetPins);
                AnsiString N = currentnet + " ";
                if (Form1->CPinNetPCB->Items->IndexOf(N) == -1)
                        Form1->CPinNetPCB->Items->Add(N);
                }
        Index++;
        }
//
//
//
if (Form2->Language->Checked)   Form1->Caption = "  ������ ��������...";
else                            Form1->Caption = "  Reading netlist...";
Application->ProcessMessages();
//loading netlist
bool LNetListPath = 0;
if (NetListPath.SubString(1,1) == "#" )
        {
        NetListPath = NetListPath.SubString(2,(NetListPath.Length()-1));
        LNetListPath = TRUE;
        }
if (NetListPath.Length())
if (LNetListPath || rNETLIST)
        {
        F = fopen(NetListPath.c_str(),"r");
        if(F)  {
                fclose(F);
                i = 0;
                while (i < (Form1->StringGridParts->RowCount-1))
                        {
                        if (Form2->Language->Checked)   Form1->StringGridParts->Cells[def_CompareNetlist][i] = "������_��_�����";
                        else                            Form1->StringGridParts->Cells[def_CompareNetlist][i] = "Only_on_the_Board";
                        i++;
                        }
                AnsiString R;
                AnsiString V;
                AnsiString P;
                ifstream Netlist (NetListPath.c_str());
                A = "";
                bool FlPrt = false;
                int CS = 0;
                int ALength;
                currentnet = "";
                int MAX_INDEX_ROW = Form1->StringGridParts->RowCount;
                while(!Netlist.eof()){
                        CS++;
                        Netlist.getline(s,2500);
                        A = s;
                        A = A.Trim();
                        if (A.UpperCase().SubString(1,6) == "*PART*" )
                                {
                                FlPrt = true;
                                continue;
                                }
                        if (A.UpperCase().SubString(1,5) == "*NET*" )
                                {
                                FlPrt = false;
                                continue;
                                }
                        R = "";
                        V = "";
                        P = "";
                        i = 1;
                        ALength = A.Length();
                        if (FlPrt)
                                {
                                R = while_not_space(A,&i);
                                int start = i;
                                int FindRefIndex=-1;
                                int RLength = R.Length();
                                for( int ii=0; ii<MAX_INDEX_ROW; ii++ )
                                        {
                                        AnsiString gs = Form1->StringGridParts->Cells[def_RefDes][ii];
                                        if( gs.SubString(1,gs.Length()) == R.SubString(1,RLength) )
                                                {
                                                FindRefIndex = ii;
                                                break;
                                                }
                                        }
                                i = A.Pos(DOG);
                                if (i > 0 && i <= ALength && start > 0 && start <= ALength)
                                        {
                                        V = A.SubString(start,(i - start));
                                        i++;
                                        }
                                else    i = start;
                                if (i > 0)
                                        P = A.SubString(i,(ALength-i+1));
                                if (!V.Length())
                                        V = EMP;
                                if (!P.Length())
                                        P = EMP;
                                bool OKValIndex = false;
                                bool OKPackIndex = false;
                                if ( FindRefIndex >= 0 && R.Length())
                                        {
                                        // find mirror part
                                        int MirrorIndex = -1;
                                        for( int ii=0; ii<MAX_INDEX_ROW; ii++ )
                                                {
                                                AnsiString gs = Form1->StringGridParts->Cells[def_RefDes][ii];
                                                int gslen = gs.Length();
                                                if( gslen > RLength )
                                                        if( gs.SubString(1,RLength) == R.SubString(1,RLength) )
                                                                if( gs.SubString(RLength+1,1) == "|" )
                                                                        {
                                                                        //B = Form1->StringGridParts->Cells[def_Value][FindRefIndex];
                                                                        //AnsiString B2 = Form1->StringGridParts->Cells[def_Value][ii];
                                                                        //if (B.SubString(1,B.Length()) == B2.SubString(1,B2.Length()))
                                                                        //        {
                                                                        //        B = Form1->StringGridParts->Cells[def_FootPrint][FindRefIndex];
                                                                        //        AnsiString B2 = Form1->StringGridParts->Cells[def_FootPrint][ii];
                                                                        //        if (B.SubString(1,B.Length()) == B2.SubString(1,B2.Length()))
                                                                        //                {
                                                                                        MirrorIndex = ii;
                                                                                        break;
                                                                        //                }
                                                                        //        }
                                                                        }
                                                }
                                        AnsiString sV = V;
                                        AnsiString sP = P;
                                        for( int step=0; step<2; step++ )
                                                {
                                                if( Form1->StringGridParts->Cells[def_ValueNL][FindRefIndex].SubString(1,3) == EMP &&
                                                    Form1->StringGridParts->Cells[def_PackageNL][FindRefIndex].SubString(1,3) == EMP )
                                                        {
                                                        Form1->StringGridParts->Cells[def_ValueNL][FindRefIndex] = V;
                                                        Form1->StringGridParts->Cells[def_PackageNL][FindRefIndex] = P;
                                                        }
                                                else if( R.Pos("|") < 1 && step == 0 )
                                                        ShowMessage("  External netlist error! Duplicate Reference designator: " + R);
                                                B = Form1->StringGridParts->Cells[def_Value][FindRefIndex];
                                                for( int ii=B.Length()-1; ii>=0; ii-- )
                                                        if(B.SubString(ii,1) == " " ||
                                                           B.SubString(ii,1) == "_" ||
                                                           B.SubString(ii,1) == "." ||
                                                           B.SubString(ii,1) == "," )
                                                           B.Delete(ii,1);
                                                for( int ii=V.Length()-1; ii>=0; ii-- )
                                                        if(V.SubString(ii,1) == " " ||
                                                           V.SubString(ii,1) == "_" ||
                                                           V.SubString(ii,1) == "." ||
                                                           V.SubString(ii,1) == "," )
                                                           V.Delete(ii,1);
                                                if (V.UpperCase().SubString(1,V.Length()) == B.UpperCase().SubString(1,B.Length()))
                                                        OKValIndex = true;
                                                B = Form1->StringGridParts->Cells[def_FootPrint][FindRefIndex];
                                                for( int ii=B.Length()-1; ii>=0; ii-- )
                                                        if(B.SubString(ii,1) == " " ||
                                                           B.SubString(ii,1) == "_" ||
                                                           B.SubString(ii,1) == "." ||
                                                           B.SubString(ii,1) == "," )
                                                           B.Delete(ii,1);
                                                for( int ii=P.Length()-1; ii>=0; ii-- )
                                                        if(P.SubString(ii,1) == " " ||
                                                           P.SubString(ii,1) == "_" ||
                                                           P.SubString(ii,1) == "." ||
                                                           P.SubString(ii,1) == "," )
                                                           P.Delete(ii,1);
                                                if (P.UpperCase().SubString(1,P.Length()) == B.UpperCase().SubString(1,B.Length()))
                                                        OKPackIndex = true;
                                                if ((OKValIndex)&&(OKPackIndex))
                                                        {
                                                        if (Form2->Language->Checked)
                                                                Form1->StringGridParts->Cells[def_CompareNetlist][FindRefIndex] = "��_���������";
                                                        else
                                                                Form1->StringGridParts->Cells[def_CompareNetlist][FindRefIndex] = "All_matches";
                                                        }
                                                else if (OKValIndex)
                                                        {
                                                        if (Form2->Language->Checked)
                                                                Form1->StringGridParts->Cells[def_CompareNetlist][FindRefIndex] = "��������_������";
                                                        else
                                                                Form1->StringGridParts->Cells[def_CompareNetlist][FindRefIndex] = "Footprint_only";
                                                        }
                                                else if (OKPackIndex)
                                                        {
                                                        if (Form2->Language->Checked)
                                                                Form1->StringGridParts->Cells[def_CompareNetlist][FindRefIndex] = "��������_������";
                                                        else
                                                                Form1->StringGridParts->Cells[def_CompareNetlist][FindRefIndex] = "Value_only";
                                                        }
                                                else    {
                                                        if (Form2->Language->Checked)
                                                                Form1->StringGridParts->Cells[def_CompareNetlist][FindRefIndex] = "��������_��������";
                                                        else
                                                                Form1->StringGridParts->Cells[def_CompareNetlist][FindRefIndex] = "Footprint_Value";
                                                        }
                                                if( MirrorIndex >= 0 )
                                                        {
                                                        FindRefIndex = MirrorIndex;
                                                        OKValIndex = false;
                                                        OKPackIndex = false;
                                                        V = sV;
                                                        P = sP;
                                                        }
                                                else    break;
                                                }
                                        }
                                else    {
                                        if(!V.Length())
                                                V = EMP;
                                        if(!P.Length())
                                                P = EMP;
                                        if (R.Length())
                                                {
                                                PartGridIndex++;
                                                if (PartGridIndex)  Form1->StringGridParts->RowCount++;
                                                INDEXPINS[PartGridIndex] = PinGridIndex;
                                                Form1->StringGridParts->Cells[def_RefDes][PartGridIndex] = R;
                                                Form1->StringGridParts->Cells[def_RIRange][PartGridIndex] = ExtractRefIndex(R);
                                                Form1->StringGridParts->Cells[def_ValueNL][PartGridIndex] = V;
                                                Form1->StringGridParts->Cells[def_PackageNL][PartGridIndex] = P;
                                                Form1->StringGridParts->Cells[def_Value][PartGridIndex] = EMP;
                                                Form1->StringGridParts->Cells[def_Package][PartGridIndex] = EMP;
                                                Form1->StringGridParts->Cells[def_FootPrint][PartGridIndex] = EMP;
                                                Form1->StringGridParts->Cells[def_Merge][PartGridIndex] = EMP;
                                                Form1->StringGridParts->Cells[def_Pins][PartGridIndex] = EMP;
                                                Form1->StringGridParts->Cells[def_Holes][PartGridIndex] = EMP;
                                                Form1->StringGridParts->Cells[def_Gl][PartGridIndex] = EMP;
                                                Form1->StringGridParts->Cells[def_S][PartGridIndex] = EMP;
                                                Form1->StringGridParts->Cells[def_Ang][PartGridIndex] = EMP;
                                                Form1->StringGridParts->Cells[def_Xprt][PartGridIndex] = EMP;
                                                Form1->StringGridParts->Cells[def_Yprt][PartGridIndex] = EMP;
                                                if (Form2->Language->Checked)   Form1->StringGridParts->Cells[def_CompareNetlist][PartGridIndex] = "������_�_��������";
                                                else                            Form1->StringGridParts->Cells[def_CompareNetlist][PartGridIndex] = "Only_in_netlist";
                                                }
                                        }
                                }
                        else    {
                                if (A.SubString(1,8) == "*SIGNAL*")
                                        {
                                        i = prob(A,1);
                                        currentnet = while_not_space(A,&i);
                                        currentnet = currentnet.Trim();
                                        Form1->DataPins->Items->Add(DOG + currentnet);
                                        }
                                else    {
                                        i = 1;
                                        AnsiString Part;
                                        if (currentnet.Length())
                                        do      {
                                                Part = while_not_space(A,&i);
                                                Part = Part.Trim();
                                                if (Part.Length() && currentnet.Length() && Part.SubString(1,1) != "*" )
                                                        {
                                                        Form1->DataPins->Items->Add(Part);
                                                        int ind = Form1->StringGridPins->Cols[def_Pin]->IndexOf(Part);
                                                        if (ind == -1)
                                                                {
                                                                PinGridIndex++;
                                                                Form1->StringGridPins->RowCount++;
                                                                Form1->StringGridPins->Cells[def_Pin][PinGridIndex] = Part;
                                                                if (Form2->Language->Checked)   Form1->StringGridPins->Cells[def_NetPcb][PinGridIndex] = "�� ������ ";
                                                                else                            Form1->StringGridPins->Cells[def_NetPcb][PinGridIndex] = "Not found ";
                                                                // none: Form1->StringGridPins->Cells[def_Netlist][PinGridIndex] = currentnet + " ";
                                                                Form1->StringGridPins->Cells[def_Type][PinGridIndex] = "";
                                                                Form1->StringGridPins->Cells[def_W][PinGridIndex] = "";
                                                                Form1->StringGridPins->Cells[def_L][PinGridIndex] = "";
                                                                Form1->StringGridPins->Cells[def_Thrml][PinGridIndex] = "";
                                                                Form1->StringGridPins->Cells[def_DHole][PinGridIndex] = "";
                                                                Form1->StringGridPins->Cells[def_Pas][PinGridIndex] = "";
                                                                Form1->StringGridPins->Cells[def_Xpi][PinGridIndex] = "";
                                                                Form1->StringGridPins->Cells[def_Ypi][PinGridIndex] = "";
                                                                }
                                                        else    {
                                                                // none: Form1->StringGridPins->Cells[def_Netlist][ind] = currentnet + " ";
                                                                }
                                                        }
                                                } while (i > 0);
                                        }
                                }
                        }
                Netlist.close();
                }
        else    {
                fclose(F);
                NetListPath = "";
                }
        }
INDEXPINS[PartGridIndex+1] = PinGridIndex+1;
INDEXPINS[PartGridIndex+2] = maximum_number_of_parts;
//
//
//WARNINGS:
if (CMPR_PINS)
        {
        if (Form2->Language->Checked)   Form1->Caption = "  �������� �����...";
        else                            Form1->Caption = "  Loading pins...";
        int start1;
        int start2;
        int perc = Form1->StringGridPins->RowCount/99+1;
        int Pins_2_ignore = MessageBox( NULL,   "\
The polarity of the connection of two-pin parts can be\
ignored when comparing pin nets. If your PCB project \
uses parts that do not have polarity, then the Infobox can \
ignore the polarity of the connection of two-pin \
parts to optimize the list of changed nets. Ignore?",\
"How to handle two-pin parts?", MB_YESNO );
        int b_En_Same_Net = MessageBox( NULL,   "\
Infobox will be analyze all pins of Nxxxx.. format \
nets from the external netlist and compare with the \
connection of the same pins in the current PCB project. \
Make this analysis for named nets, such as + E, gnd, etc.? \
(YES - full netlist test, NO - only Nxxxx format nets are \
checked ..)","Infobox - full netlist test..", MB_YESNO );
        Application->ProcessMessages();
        int b2p;
        AnsiString nnlist, npcb, pname;
        for( int ipin=0; ipin<Form1->StringGridPins->RowCount; ipin++ )
                {
                pname = Form1->StringGridPins->Cells[def_Pin][ipin];
                npcb =  Form1->StringGridPins->Cells[def_NetPcb][ipin];
                pname = pname.TrimRight();
                int Count,CountPins,iend;
                AnsiString netOut="",fnetOut="";
                start1 = ::iof1(&pname, &npcb);
                b2p = 0;
                if (Pins_2_ignore == ID_YES)
                        {
                        int pnl = pname.Length();
                        if( pnl)
                                if (pname.SubString(pnl-1,2) == dSPACE)
                                        b2p = 1;
                        }
                int TotalC = 0;
                for( int c1=start1+1; c1<Form1->DataParts->Items->Count; c1++ )
                        {
                        AnsiString Comp1 = Form1->DataParts->Items->operator [](c1); // pins PCB
                        if( Comp1.SubString(1,1) == DOG )
                                break;
                        TotalC++;
                        }
                for( int step=0; step<2; step++ )
                        {
                        // Compare pins...
                        Count = 0;
                        CountPins = 0;
                        start2 = ::iof2(pname, &nnlist);
                        if( start1 == -1 && start2 != -1 )
                                {
                                // in pcb no connect
                                netOut = nnlist.TrimRight() + dSPACE;
                                }
                        else if( start2 == -1 && start1 != -1 )
                                {
                                // in netlist no connect
                                if (Form2->Language->Checked)
                                        netOut = AnsiString("��_�����.") + dSPACE;
                                else
                                        netOut = AnsiString("No_connect") + dSPACE;
                                }
                        else if( start1 == -1 && start2 == -1 )
                                {
                                 if (Form2->Language->Checked)
                                        netOut = AnsiString("����_��_�����.");
                                 else
                                        netOut = AnsiString("No_connect_too");
                                 break;
                                }
                        else if( npcb.SubString(1,npcb.Length()) == nnlist.SubString(1,nnlist.Length()) &&
                                 npcb.SubString(1,2).UpperCase() != "N0" && b_En_Same_Net != ID_YES )
                                {
                                // pin is not checked if names of net are the same,
                                // but the name does not begin with "N0"
                                netOut = nnlist.TrimRight();
                                CountPins = Count = TotalC;
                                break;
                                }
                        else    {
                                for( int c2=start2+1; c2<Form1->DataPins->Items->Count; c2++ )
                                        {
                                        AnsiString Comp2 = Form1->DataPins->Items->operator [](c2);  // pins nlist
                                        Comp2 = Comp2.TrimRight();
                                        if( Comp2.SubString(1,1) == DOG )
                                                break;
                                        int C2L = Comp2.Length();
                                        //
                                        for( int c1=start1+1; c1<Form1->DataParts->Items->Count; c1++ )
                                                {
                                                AnsiString Comp1 = Form1->DataParts->Items->operator [](c1); // pins PCB
                                                if( Comp1.SubString(1,1) == DOG )
                                                        break;
                                                int C1L = Comp1.Length();
                                                if( Comp1.TrimRight().SubString(1,C1L) == Comp2.SubString(1,C2L) )
                                                        {
                                                        CountPins++;
                                                        break;
                                                        }
                                                else if (Pins_2_ignore == ID_YES && C1L)
                                                        {
                                                        if( Comp1.SubString(C1L-1,2) == dSPACE )
                                                                {
                                                                Comp1 = Comp1.TrimRight();
                                                                C1L = Comp1.Length();
                                                                int ip = Comp1.Pos(".");
                                                                if (ip > 0)
                                                                        {
                                                                        if (Comp1.SubString(ip+1,C1L-ip) == "1")
                                                                                Comp1 = Comp1.SubString(1,ip) + "2";
                                                                        else if (Comp1.SubString(ip+1,C1L-ip) == "2")
                                                                                Comp1 = Comp1.SubString(1,ip) + "1";
                                                                        else if (Comp1.SubString(ip+1,C1L-ip) == "a")
                                                                                Comp1 = Comp1.SubString(1,ip) + "b";
                                                                        else if (Comp1.SubString(ip+1,C1L-ip) == "b")
                                                                                Comp1 = Comp1.SubString(1,ip) + "a";
                                                                        else if (Comp1.SubString(ip+1,C1L-ip) == "A")
                                                                                Comp1 = Comp1.SubString(1,ip) + "B";
                                                                        else if (Comp1.SubString(ip+1,C1L-ip) == "B")
                                                                                Comp1 = Comp1.SubString(1,ip) + "A";
                                                                        else continue;
                                                                        }
                                                                if( Comp1.SubString(1,C1L) == Comp2.SubString(1,C2L) )
                                                                        {
                                                                        CountPins++;
                                                                        break;
                                                                        }
                                                                }
                                                        }
                                                }
                                        Count++;
                                        }
                                netOut = nnlist;
                                if( CountPins >= Count/2+1 )
                                        break;
                                } // Compare end
                        if( b2p == 0 )
                                break;
                        int pnl = pname.TrimRight().Length();
                        int ip = pname.Pos(".");
                        if (ip > 0)
                                {
                                if (pname.SubString(ip+1,pnl-ip) == "1")
                                        pname = pname.SubString(1,ip) + "2";
                                else if (pname.SubString(ip+1,pnl-ip) == "2")
                                        pname = pname.SubString(1,ip) + "1";
                                else if (pname.SubString(ip+1,pnl-ip) == "a")
                                        pname = pname.SubString(1,ip) + "b";
                                else if (pname.SubString(ip+1,pnl-ip) == "b")
                                        pname = pname.SubString(1,ip) + "a";
                                else if (pname.SubString(ip+1,pnl-ip) == "A")
                                        pname = pname.SubString(1,ip) + "B";
                                else if (pname.SubString(ip+1,pnl-ip) == "B")
                                        pname = pname.SubString(1,ip) + "A";
                                else break;
                                }
                        if(step == 0 )
                                fnetOut = netOut;
                        }
                if( fnetOut.Length() )
                        netOut = fnetOut;
                if( npcb.SubString(1,npcb.Length()).TrimRight() != netOut.SubString(1,netOut.Length()).TrimRight() )
                        {
                        if( Count && CountPins < (Count/2+1) )
                                netOut = netOut.TrimRight() + dSPACE;
                        if( TotalC && CountPins < (TotalC/2+1) )
                                netOut = netOut.TrimRight() + dSPACE;
                        }
                Form1->StringGridPins->Cells[def_Netlist][ipin] = netOut;
                if (ipin%perc == 0)
                        {
                        Form1->ProgressBar1->Position++;
                        Application->ProcessMessages();
                        }
                }
        Form1->ProgressBar1->Visible = false;
        }
else    {
        for (int r=0; r<Form1->StringGridPins->RowCount; r++)
                Form1->StringGridPins->Cells[def_Netlist][r] = "";
        }
Form1->ClientHeight = 0;
if(LNetListPath)
        NetListPath = "#" + NetListPath;
if (Form2->Language->Checked)   Form1->Caption = "  ����������...";
else                            Form1->Caption = "  Completion...";
Application->ProcessMessages();
//loading iistboxes
Form1->DataParts->Items->Clear();
Form1->DataPins->Items->Clear();
i = 0;
N_PART_ELEMENTS = Form1->StringGridParts->RowCount;
while(i < N_PART_ELEMENTS)
        {
        //A = Form1->StringGridParts->Cells[def_RefDes][i];                      //Format DataGrids: 12
        Form1->DataParts->Items->Add(i+1);                                       //indexRef
        //Form1->DataParts->Items->AddStrings(Form1->StringGridParts->Rows[i]);
        for(int ii=col_RefDes; ii<PartsColCount; ii++)
                Form1->DataParts->Items->Add(Form1->StringGridParts->Cells[PartColOrder[ii]][i]);
        i++;
        }
Application->ProcessMessages();
i = 0;
N_PIN_ELEMENTS = Form1->StringGridPins->RowCount;
while(i < N_PIN_ELEMENTS)
        {
        //A = Form1->StringGridPins->Cells[def_Pin][i];                          //Format DataGrids
        Form1->DataPins->Items->Add(i+1);                                        //indexPin
        Form1->DataPins->Items->AddStrings(Form1->StringGridPins->Rows[i]);
        i++;
        }
Form1->Bufer->Items->Clear();
Form1->SortedBox->Items->Clear();
if( SORT_CASE )
        SortedParts(0);
CCnlistRefresh();
// restore
Form1->BCNetlist->Hint = "File:  " + FileName + "\nNetlist:  " + NetListPath;
Form1->CMerge->Text = svCMerge;
Form1->DHoleMin->Text = svDHoleMin;
Form1->DHoleMax->Text = svDHoleMax;
Form1->CPinNetPCB->Text = svCPinNetPCB;
Form1->CCNetlist->Text = svCCNetlist;
Form1->CCnt->Text = svCCnt;

FileNameBack = FileName;
BEGIN = true;
Form1->Timer1->Enabled = true;
if (FlagProgEXE)
        ProgExecute("");
FilterAll(false, "", 1-Form1->PageControl1->TabIndex);
FilterAll(true);
Form1->ClientHeight = SaveClientHeight;
Form1->PageControl1->Visible = 1;
Form1->R->Visible = true;
}



