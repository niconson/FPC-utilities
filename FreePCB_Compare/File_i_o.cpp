//---------------------------------------------------------------------------


#pragma hdrstop

#include "File_i_o.h"
#include "fpcc.h"
#include "fstream.h"
//---------------------------------------------------------------------------
int format;
#pragma package(smart_init)

#define CSV 1
#define TXT 2
#define UNKNOWN 0
#define VALUE_COL       1
#define PACKAGE_COL     2
int NO_REP_COUNT=0;
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
int StorageIndexOf (AnsiString Value, AnsiString Package)
{
for( int f=0; f<Form1->GridFeeders->RowCount; f++ )
        {
        AnsiString V = Form1->GridFeeders->Cells[VALUE_COL][f];
        if( Value.Length() == 0 || V.SubString(1,V.Length()) == Value.SubString(1,Value.Length()) )
                {
                AnsiString P = Form1->GridFeeders->Cells[PACKAGE_COL][f];
                if( Package.Length() == 0 || P.SubString(1,P.Length()) == Package.SubString(1,Package.Length()) )
                        {
                        return f;
                        }
                }
        }
return -1;
}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
int StringExplode( AnsiString S )
{
        Form1->MicroStrings->Items->Clear();
        int Ls = S.Length();
        int i_st = 1;
        S = S.Trim();
        for( int i=1; i<Ls-1; i++ )
                {
                if( (S.SubString(i,2) == dSPACE && format != CSV) ||
                    (S.SubString(i,1) == "\t" && format != CSV) ||
                    (S.SubString(i,1) == ";" && format != TXT) ||
                    (S.SubString(i,3) == "\",\"" && format != TXT) )
                        {
                        if( format == UNKNOWN )
                                {
                                if( S.SubString(i,2) == dSPACE || S.SubString(i,1) == "\t" )
                                        format = TXT;
                                else    format = CSV;
                                }
                        AnsiString addstr = S.SubString(i_st,i-i_st);
                        for( int p=addstr.Pos("\""); p>0; p=addstr.Pos("\"") )
                                {
                                addstr.Delete(p,1);
                                p = addstr.Pos("\"");
                                }
                        addstr = addstr.Trim();
                        Form1->MicroStrings->Items->Add(addstr);
                        if( (S.SubString(i,1) == " " || S.SubString(i,1) == "\t") && format == TXT )
                                {
                                while( S.SubString(i,1) == " " || S.SubString(i,1) == "\t" )
                                        {
                                        if( i<Ls )      i++;
                                        else            return Form1->MicroStrings->Items->Count;
                                        }
                                i--;
                                }
                        i_st = i+1;
                        }
                }
        if( i_st < Ls )
                {
                AnsiString addstr = S.SubString(i_st,Ls-i_st+1);
                int p = addstr.Pos("\"");
                while( p > 0 )
                        {
                        addstr.Delete(p,1);
                        p = addstr.Pos("\"");
                        }
                addstr = addstr.Trim();
                Form1->MicroStrings->Items->Add(addstr);
                }
        return Form1->MicroStrings->Items->Count;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
bool lbNoReplace_add (AnsiString sA, AnsiString sB)
{
if( sA.Length() < sB.Length() )
        {
        int p = sB.Pos(sA);
        if(p==1) {
                AnsiString G = sB.SubString(sA.Length()+1,sB.Length()-sA.Length());
                if( Form1->Memo1->Lines->IndexOf(G) == -1 )
                        Form1->Memo1->Lines->Add(G);
                }
        }
else if( sB.Length() < sA.Length() )
        {
        int p = sA.Pos(sB);
        if(p==1) {
                AnsiString G = sA.SubString(sB.Length()+1,sA.Length()-sB.Length());
                if( Form1->Memo1->Lines->IndexOf(G) == -1 )
                        Form1->Memo1->Lines->Add(G);
                }
        }
AnsiString s = sA + " & " + sB;
for( int i=0; i<Form1->lbNoReplace->Lines->Count; i++)
        {
        if(Form1->lbNoReplace->Lines->operator [](i).Length() == 0)
                {
                Form1->lbNoReplace->Lines->Delete(i);
                Form1->lbNoReplace->Lines->Insert(i,s);
                return true;
                }
        }
Form1->lbNoReplace->Lines->Add(s);
return true;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void fix_str( AnsiString * S )
{
int pos;
pos = S->Pos(" ");
while( pos > 0 )
        {
        S->Delete(pos,1);
        pos = S->Pos(" ");
        }
if( Form1->ExcludeAsterisk->Checked )
        {
        pos = S->Pos("*");
        while( pos > 0 )
                {
                S->Delete(pos,1);
                pos = S->Pos("*");
                }
        }
if( Form1->ExcludeDash->Checked )
        {
        pos = S->Pos("-");
        while( pos > 0 )
                {
                S->Delete(pos,1);
                pos = S->Pos("-");
                }
        }
if( Form1->ExcludeUnderscore->Checked )
        {
        pos = S->Pos("_");
        while( pos > 0 )
                {
                S->Delete(pos,1);
                pos = S->Pos("_");
                }
        }
if( Form1->ExcludeParentheses->Checked )
        {
        pos = S->Pos("(");
        if( pos > 1 )
                {
                S->SetLength(pos-1);
                //S->TrimRight();
                }
        while( pos > 0 )
                {
                S->Delete(pos,1);
                pos = S->Pos("(");
                }
        pos = S->Pos(")");
        while( pos > 0 )
                {
                S->Delete(pos,1);
                pos = S->Pos(")");
                }
        }
if( Form1->ExcludeSlash->Checked )
        {
        pos = S->Pos("/");
        while( pos > 0 )
                {
                S->Delete(pos,1);
                pos = S->Pos("/");
                }
        pos = S->Pos("\\");
        while( pos > 0 )
                {
                S->Delete(pos,1);
                pos = S->Pos("\\");
                }
        }
if( Form1->ExcludeComma->Checked )
        {
        pos = S->Pos(",");
        while( pos > 0 )
                {
                S->Delete(pos,1);
                S->Insert(".",pos);
                pos = S->Pos(",");
                }
        }
*S = S->UpperCase();
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void ReadingFeedersData( AnsiString FileN, bool HINT )
{
        if( V_col_fdr <= 0 || P_col_fdr <= 0 )
                return;
        AnsiString fN = ExtractFileName(FileN);
        Form1->Mess->Caption = "Reading " + fN;
        bool bVPL = false;
        int pp = fN.Pos(".");
        if( pp > 1 )
                {
                fN = fN.SubString(1,pp-1);
                if( fN.Length() == pp+3 )
                        if( fN.SubString(pp,4).LowerCase() == ".vpl" )
                                bVPL = true;
                }
        Application->ProcessMessages();
        format = UNKNOWN;
        FILE * f;
        f = fopen(FileN.c_str(),"r");
        if( f ) {
                fclose(f);
                int n_str = 0;
                ifstream r_len(FileN.c_str());
                char sl[9999];
                while( !r_len.eof() )
                        {
                        r_len.getline( sl, sizeof(sl));
                        n_str++;
                        }
                r_len.close();
                char s[9999];
                int bar = 0;
                int max_col = 0;
                ifstream r_f(FileN.c_str());
                Form1->ProgressBar1->Position = 0;
                Application->ProcessMessages();
                while( !r_f.eof() )
                        {
                        if( r_f.eof() )
                                break;
                        float k = (float)bar/(float)n_str*100.0;
                        if( Form1->ProgressBar1->Position != (int)k )
                                {
                                Form1->ProgressBar1->Position = k;
                                Application->ProcessMessages();
                                }
                        r_f.getline( s, sizeof(s));
                        AnsiString S = s;
                        S = S.Trim();
                        if( S.Length() == 0 )
                                continue;
                        bar++;
                        int cs = StringExplode(S);
                        if( HINT )
                        if( max_col < Form1->MicroStrings->Items->Count )
                                {
                                Form1->ComboHelp->Items->Clear();
                                for( int hlp=0; hlp<Form1->MicroStrings->Items->Count; hlp++ )
                                        {
                                        AnsiString HLP = "(" + fN + " Col:" + AnsiString(hlp+1) + ")";
                                        HLP += Form1->MicroStrings->Items->operator [](hlp);
                                        Form1->ComboHelp->Items->Add(HLP);
                                        }
                                max_col = Form1->MicroStrings->Items->Count;
                                }
                        if( V_col_fdr <= cs )
                                {
                                AnsiString add_1 = Form1->MicroStrings->Items->operator [](V_col_fdr-1);
                                AnsiString add_2 = "";
                                if( P_col_fdr <= cs )
                                        add_2 = Form1->MicroStrings->Items->operator [](P_col_fdr-1);
                                if( add_1.Length() || add_2.Length() )
                                        {
                                        AnsiString File_Str;
                                        if( bVPL && Form1->MicroStrings->Items->Count >= 3 )
                                                File_Str = Form1->MicroStrings->Items->operator [](2);
                                        else    File_Str = fN;
                                        AnsiString num = AnsiString(Form1->GridFeeders->RowCount-1);
                                        for(int ii=0; num.Length()<4; ii++)
                                                num = "0" + num;
                                        fix_str( &add_1 );
                                        fix_str( &add_2 );
                                        if( add_1.Length() || add_2.Length() )
                                                {
                                                if( StorageIndexOf(add_1,add_2) < 0 )
                                                        {
                                                        Form1->FileBox->Items->Add(File_Str);
                                                        Form1->GridFeeders->Cells[0][Form1->GridFeeders->RowCount-1] = num;
                                                        Form1->GridFeeders->Cells[1][Form1->GridFeeders->RowCount-1] = add_1;
                                                        Form1->GridFeeders->Cells[2][Form1->GridFeeders->RowCount-1] = add_2;
                                                        Form1->GridFeeders->RowCount++;
                                                        Form1->GridFeeders->Cells[0][Form1->GridFeeders->RowCount-1] = "";
                                                        Form1->GridFeeders->Cells[1][Form1->GridFeeders->RowCount-1] = "";
                                                        Form1->GridFeeders->Cells[2][Form1->GridFeeders->RowCount-1] = "";
                                                        }
                                                }
                                        }
                                }
                        else    {
                                int test = 0;
                                }
                        }
                }
        if( Form1->ComboHelp->Items->Count )
                Form1->ComboHelp->ItemIndex = 0;
        Form1->Mess->Caption = "Reading completed successfully!";
        Form1->ProgressBar1->Position = 0;
        Application->ProcessMessages();
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void ReadingFeeders( AnsiString S )
{
        AnsiString col = Form1->fdr_col_V->Text;
        V_col_fdr = (int)StrToFloat(Str_Float_F(col));
        col = Form1->fdr_col_P->Text;
        P_col_fdr = (int)StrToFloat(Str_Float_F(col));
        Form1->ButtonScan->Enabled = 1;
        Form1->GridFeeders->Visible = 0;
        Form1->GridFeeders->RowCount = 2;
        Form1->GridFeeders->Cells[0][1] = "";
        Form1->GridFeeders->Cells[1][1] = "";
        Form1->GridFeeders->Cells[2][1] = "";
        Form1->ComboHelp->Items->Clear();
        Form1->FileBox->Items->Clear();
        Form1->ComboHelp->ItemIndex = -1;
        AnsiString save[99];//пути каталогов в которые уже заходили
        if (S.SubString(S.Length(),1) == "\\")
                S = S.SubString(1,(S.Length()-1));
        long str = 0;        //номер подкаталога
        TSearchRec sr;
        #define _set 1
        #define _out 2
        #define _in  3
        #define _none 4
        int COMMAND = _out;
        int CNTF = 0;
        format = UNKNOWN;
        while(1)
                {//НАЧАЛО ПОИСКА
                if (FindFirst((S+"\\*"), faAnyFile, sr) == 0)
                        {
                        do
                                {
                                if (COMMAND == _set )
                                        {
                                        COMMAND = _none;
                                        while (save[str].SubString(1,save[str].Length()) != sr.Name)   FindNext(sr);
                                        if (!(sr.Attr & faDirectory))
                                        while (save[str].SubString(1,save[str].Length()) != sr.Name)   FindNext(sr);
                                        if (FindNext(sr))
                                                {
                                                COMMAND = _out;
                                                break;
                                                }
                                        }
                                if (!(sr.Attr & faVolumeID))
                                if (!(sr.Attr & faSysFile) )
                                if (sr.Attr & faDirectory) // directory     //если каталог
                                        {
                                        if ((sr.Name!=".")&&(sr.Name!=".."))   //если не две точки
                                                {
                                                COMMAND = _in;
                                                break;
                                                }
                                        }
                                else     //file...
                                        {
                                        if ((sr.Name!=".")&&(sr.Name!=".."))
                                                {
                                                int Len1 = sr.Name.Length();
                                                if(( sr.Name.LowerCase().SubString(Len1-3,4) == ".txt" ) ||
                                                   ( sr.Name.LowerCase().SubString(Len1-3,4) == ".csv" ) ||
                                                   ( sr.Name.LowerCase().SubString(Len1-3,4) == ".vpl" ) ||
                                                   ( sr.Name.LowerCase().SubString(Len1-3,4) == ".bom" ))
                                                        {
                                                        CNTF++;
                                                        AnsiString A = S + "\\" + sr.Name;
                                                        if( CNTF == 1 )
                                                                ReadingFeedersData(A,true) ;
                                                        else    ReadingFeedersData(A,false) ;
                                                        Form1->Mess->Caption = "Number Of Files: " + AnsiString(CNTF);
                                                        }
                                                COMMAND = _out;
                                                }
                                        }
                                }while (FindNext(sr) == 0);
                        if (COMMAND == _out )
                                {                                                     //выходим в директорию выше
                                if (str == 0) break;
                                FindClose(sr);
                                str--;
                                S = ExtractFilePath(S);
                                S = S.SubString(1,(S.Length()-1)) ;                              //убираем символ'\'
                                FindClose(sr);
                                COMMAND = _set;
                                }
                        else if (COMMAND == _in )
                                {
                                save[str] = sr.Name;
                                S = S+"\\"+sr.Name;
                                str++;
                                FindClose(sr);
                                COMMAND = _out;
                                }
                        }
                else break;
                }
        FindClose(sr);
        Form1->GridFeeders->Visible = 1;
        if( CNTF == 0 )
                {
                Form1->GridFeeders->RowCount = 2;
                Form1->GridFeeders->Cells[0][1] = "";
                Form1->GridFeeders->Cells[1][1] = "";
                Form1->GridFeeders->Cells[2][1] = "";
                }
        #undef _set 
        #undef _out
        #undef _in
        #undef _none
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void ReadingProjectsData( AnsiString S, int nFile )
{
        if( V_col <= 0 || P_col <= 0 )
                return;
        format = UNKNOWN;
        FILE * f;
        f = fopen(S.c_str(),"r");
        if( f ) {
                fclose(f);
                int n_str = 0;
                ifstream r_len(S.c_str());
                char sl[9999];
                while( !r_len.eof() )
                        {
                        r_len.getline( sl, sizeof(sl));
                        n_str++;
                        }
                r_len.close();
                char s[9999];
                int bar = 0;
                ifstream r_f(S.c_str());
                Form1->ProgressBar1->Position = 0;
                Application->ProcessMessages();
                while( !r_f.eof() )
                        {
                        if( r_f.eof() )
                                break;
                        bar++;
                        float k = (float)bar/(float)n_str*100.0;
                        if( Form1->ProgressBar1->Position != (int)k )
                                {
                                Form1->ProgressBar1->Position = k;
                                Application->ProcessMessages();
                                }
                        r_f.getline( s, sizeof(s));
                        S = s;
                        S = S.Trim();
                        int cs = StringExplode(S);
                        if( V_col <= cs )
                                {
                                AnsiString add_1 = Form1->MicroStrings->Items->operator [](V_col-1);
                                AnsiString add_2 = "";
                                if( P_col <= cs )
                                        add_2 = Form1->MicroStrings->Items->operator [](P_col-1);
                                if( add_1.Length() || add_2.Length() )
                                        {
                                        fix_str( &add_1 );
                                        fix_str( &add_2 );
                                        if( add_1.Length() || add_2.Length() )
                                                {
                                                if( ValuesPackages_iof( add_1, add_2 ) < 0 )
                                                        {
                                                        ValuesPackages_add(add_1,add_2,AnsiString(nFile));
                                                        }
                                                }
                                        }
                                }
                        else    {
                                int test = 0;
                                }
                        }
                }
        Form1->ProgressBar1->Position = 0;
        Application->ProcessMessages();
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void ReadingProjects( AnsiString s )
{
        Form1->VALUES->Clear();
        Form1->PACKAGES->Clear();
        Form1->FileNumbers->Clear();
        Form1->ProjectsList->Items->Clear();
        AnsiString save[99];//пути каталогов в которые уже заходили
        if (s.SubString(s.Length(),1) == "\\")
                s = s.SubString(1,(s.Length()-1));
        long str = 0;        //номер подкаталога
        TSearchRec sr;
        #define _set 1
        #define _out 2
        #define _in  3
        #define _none 4
        int COMMAND = _out;
        int nFile = 0;
        format = UNKNOWN;
        while(1)
                {//НАЧАЛО ПОИСКА
                if (FindFirst((s+"\\*"), faAnyFile, sr) == 0)
                        {
                        do
                                {
                                if (COMMAND == _set )
                                        {
                                        COMMAND = _none;
                                        while (save[str].SubString(1,save[str].Length()) != sr.Name)   FindNext(sr);
                                        if (!(sr.Attr & faDirectory))
                                        while (save[str].SubString(1,save[str].Length()) != sr.Name)   FindNext(sr);
                                        if (FindNext(sr))
                                                {
                                                COMMAND = _out;
                                                break;
                                                }
                                        }
                                if (!(sr.Attr & faVolumeID))
                                if (!(sr.Attr & faSysFile) )
                                if (sr.Attr & faDirectory) // directory     //если каталог
                                        {
                                        if ((sr.Name!=".")&&(sr.Name!=".."))   //если не две точки
                                                {
                                                COMMAND = _in;
                                                break;
                                                }
                                        }
                                else     //file...
                                        {
                                        if ((sr.Name!=".")&&(sr.Name!=".."))
                                                {
                                                int Len1 = sr.Name.Length();
                                                if(( sr.Name.LowerCase().SubString(Len1-3,4) == ".txt" && Form1->ch_txt->Checked ) ||
                                                   ( sr.Name.LowerCase().SubString(Len1-3,4) == ".csv" && Form1->ch_csv->Checked ) ||
                                                   ( sr.Name.LowerCase().SubString(Len1-3,4) == ".vpl" && Form1->ch_cmpr->Checked ) ||
                                                   ( sr.Name.LowerCase().SubString(Len1-3,4) == ".bom" && Form1->BOM->Checked ))
                                                        {
                                                        AnsiString A = s + "\\" + sr.Name;
                                                        int In = Form1->ProjectsList->Items->IndexOf(A);
                                                        if (In == -1)
                                                                {
                                                                nFile++;
                                                                Form1->ProjectsList->Items->Add(A) ;
                                                                ReadingProjectsData(A,nFile);
                                                                }
                                                        }
                                                COMMAND = _out;
                                                }
                                        }
                                }while (FindNext(sr) == 0);
                        if (COMMAND == _out )
                                {                                                     //выходим в директорию выше
                                if (str == 0) break;
                                FindClose(sr);
                                str--;
                                s = ExtractFilePath(s);
                                s = s.SubString(1,(s.Length()-1)) ;                              //убираем символ'\'
                                FindClose(sr);
                                COMMAND = _set;
                                }
                        else if (COMMAND == _in )
                                {
                                save[str] = sr.Name;
                                s = s+"\\"+sr.Name;
                                str++;
                                FindClose(sr);
                                COMMAND = _out;
                                }
                        }
                else break;
                }
        nFile++;
        FindClose(sr);
        Form1->ProjectsList->SelectAll();
        ValuesPackages_add("end","end",AnsiString(nFile));
        if( Form1->VALUES->Items->Count > 0 )
                {
                Form1->VALUES->ItemIndex = 0;
                Form1->PACKAGES->ItemIndex = 0;
                Form1->FileNumbers->ItemIndex = 0;
                }
        #undef _set 
        #undef _out 
        #undef _in
        #undef _none
}


//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void ReadingOptions( AnsiString * feeders, AnsiString * projects )
{
        Form1->ExclV->Lines->Clear();
        Form1->ExclP->Lines->Clear();
        Form1->lbNoReplace->Lines->Clear();
        Form1->lbNoReplace->Visible = 0;
        Form1->Memo1->Visible = 0;
        Form1->lbReplace->Cols[0]->Clear();
        Form1->lbReplace->Cols[1]->Clear();
        Form1->lbReplace->RowCount = 2;
        Form1->lbReplace->Cells[0][0] = "Attribute";
        Form1->lbReplace->Cells[1][0] = "Analogue";
        AnsiString S = ExtractFilePath(Application->ExeName);
        ifstream r_opt((S+"options.txt").c_str());
        FILE * f;
        f = fopen((S+"options.txt").c_str(),"r");
        if( f ) {
                fclose(f);
                char s[200];
                while( !r_opt.eof() )
                        {
                        if( r_opt.eof() )
                                break;
                        r_opt.getline( s, sizeof(s));
                        S = s;
                        S = S.Trim();
                        short i = prob(S,1);
                        if( S.SubString(1,9) == "projects:" )
                                {
                                *projects = ex_str( S, &i );
                                }
                        else if( S.SubString(1,3) == "ex:" )
                                {
                                S = ex_str( S, &i );
                                if( S.SubString(1,15) == "ExcludeAsterisk" )
                                        Form1->ExcludeAsterisk->Checked = true;
                                if( S.SubString(1,11) == "ExcludeDash" )
                                        Form1->ExcludeDash->Checked = true;
                                if( S.SubString(1,17) == "ExcludeUnderscore" )
                                        Form1->ExcludeUnderscore->Checked = true;
                                if( S.SubString(1,18) == "ExcludeParentheses" )
                                        Form1->ExcludeParentheses->Checked = true;
                                if( S.SubString(1,12) == "ExcludeSlash" )
                                        Form1->ExcludeSlash->Checked = true;
                                if( S.SubString(1,15) == "ExcludeComma" )
                                        Form1->ExcludeComma->Checked = true;
                                }
                        else if( S.SubString(1,6) == "v_col:" )
                                {
                                S = ex_str( S, &i );
                                Form1->Vcol->Text = S;
                                V_col = (int)StrToFloat(Str_Float_F(S));
                                }
                        else if( S.SubString(1,6) == "p_col:" )
                                {
                                S = ex_str( S, &i );
                                Form1->Pcol->Text = S;
                                P_col = (int)StrToFloat(Str_Float_F(S));
                                }
                        else if( S.SubString(1,10) == "fdr_v_col:" )
                                {
                                S = ex_str( S, &i );
                                Form1->fdr_col_V->Text = S;
                                }
                        else if( S.SubString(1,10) == "fdr_p_col:" )
                                {
                                S = ex_str( S, &i );
                                Form1->fdr_col_P->Text = S;
                                }
                        else if( S.SubString(1,2) == "R:" && Form1->DSL->Checked )
                                {
                                AnsiString Get = ex_str( S, &i );
                                Form1->lbReplace->Cells[0][Form1->lbReplace->RowCount-1] = Get;
                                Get = ex_str( S, &i );
                                Form1->lbReplace->Cells[1][Form1->lbReplace->RowCount-1] = Get;
                                Form1->lbReplace->RowCount++;
                                }
                        else if( S.SubString(1,3) == "NR:" )
                                {
                                S = ex_str( S, &i );
                                if(S.Length())
                                        {
                                        int p = S.Pos(" & ");
                                        if(p>0) {
                                                lbNoReplace_add(S.SubString(1,p-1),S.SubString(p+3,S.Length()-p-2));
                                                }
                                        }
                                }
                        else if( S.SubString(1,4) == "ExV:" )
                                {
                                S = ex_str( S, &i );
                                Form1->ExclV->Lines->Add(S);
                                }
                        else if( S.SubString(1,4) == "ExP:" )
                                {
                                S = ex_str( S, &i );
                                Form1->ExclP->Lines->Add(S);
                                }
                        else if( S.SubString(1,8) == "feeders:" )
                                {
                                S = ex_str( S, &i );
                                if( Form1->StorageLine->Items->IndexOf(S) == -1 )
                                        Form1->StorageLine->Items->Add(S);
                                }
                        else if( S.SubString(1,5) == "cols:" )
                                {
                                if( Form1->StorageLine->Items->Count > Form1->ColMem->Items->Count )
                                        {
                                        S = ex_str( S, &i );
                                        Form1->ColMem->Items->Add(S);
                                        }
                                }
                        else if( S.SubString(1,13) == "i_of_feeders:" )
                                {
                                long a = 0;
                                int b = ex_float( S, &a );
                                if( b < Form1->StorageLine->Items->Count && WMCopyData_STORAGE.Length() == 0 )
                                        {
                                        Form1->StorageLine->ItemIndex = b;
                                        *feeders = Form1->StorageLine->Items->operator [](b);
                                        }
                                }
                        }
                r_opt.close();
                NO_REP_COUNT = Form1->lbNoReplace->Lines->Count;
                }
        if( Form1->StorageLine->ItemIndex >= 0 )
        if( Form1->StorageLine->ItemIndex < Form1->ColMem->Items->Count )
                {
                AnsiString col_n = Form1->ColMem->Items->operator [](Form1->StorageLine->ItemIndex);
                long ind=0;
                int col1 = ex_float(col_n,&ind);
                int col2 = ex_float(col_n,&ind);
                Form1->fdr_col_V->Text = col1;
                Form1->fdr_col_P->Text = col2;
                }
        Form1->lbNoReplace->Visible = 0;
        Form1->Memo1->Visible = 0;
}


//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void WritingOptions( AnsiString feeders, AnsiString projects, bool bQ )
{
        int ret = IDNO;
        if( bQ )ret = IDYES;
        if( NO_REP_COUNT > Form1->lbNoReplace->Lines->Count && bQ )
                {
                ret = Application->MessageBox(" The number of lines in the upper box has become less! Are you sure you want to delete the lines?", "Message", MB_YESNO );
                }
        if( ret == IDNO )
                {
                Form1->lbNoReplace->Visible = 0;
                Form1->lbNoReplace->Lines->Clear();
                Form1->lbReplace->Cols[0]->Clear();
                Form1->lbReplace->Cols[1]->Clear();
                Form1->lbReplace->RowCount = 2;
                Form1->lbReplace->Cells[0][0] = "Attribute";
                Form1->lbReplace->Cells[1][0] = "Analogue";
                AnsiString S = ExtractFilePath(Application->ExeName);
                ifstream r_opt((S+"options.txt").c_str());
                FILE * f;
                f = fopen((S+"options.txt").c_str(),"r");
                if( f ) {
                        fclose(f);
                        char s[200];
                        while( !r_opt.eof() )
                                {
                                if( r_opt.eof() )
                                        break;
                                r_opt.getline( s, sizeof(s));
                                S = s;
                                S = S.Trim();
                                short i = prob(S,1);
                                if( S.SubString(1,2) == "R:" )
                                        {
                                        AnsiString Get = ex_str( S, &i );
                                        Form1->lbReplace->Cells[0][Form1->lbReplace->RowCount-1] = Get;
                                        Get = ex_str( S, &i );
                                        Form1->lbReplace->Cells[1][Form1->lbReplace->RowCount-1] = Get;
                                        Form1->lbReplace->RowCount++;
                                        }
                                if( S.SubString(1,3) == "NR:" )
                                        {
                                        S = ex_str( S, &i );
                                        if(S.Length())
                                                Form1->lbNoReplace->Lines->Add(S);
                                        }
                                }
                        }
                r_opt.close();
                Form1->lbNoReplace->Visible = 0;
                }
        //
        AnsiString opt = ExtractFilePath(Application->ExeName);
        ofstream w_opt((opt+"options.txt").c_str());
        //
        for( int i=0; i<Form1->StorageLine->Items->Count; i++ )
                {
                w_opt << "feeders: \"";
                w_opt << (Form1->StorageLine->Items->operator [](i)).c_str();
                w_opt << "\"";
                w_opt << endl;
                if( i < Form1->ColMem->Items->Count )
                        {
                        w_opt << "cols: \"";
                        w_opt << (Form1->ColMem->Items->operator [](i)).c_str();
                        w_opt << "\"";
                        w_opt << endl;
                        }
                }
        //
        w_opt << "i_of_feeders: \"";
        w_opt << AnsiString(Form1->StorageLine->ItemIndex).c_str();
        w_opt << "\"";
        w_opt << endl;
        //
        w_opt << "projects: \"";
        w_opt << projects.c_str();
        w_opt << "\"";
        w_opt << endl;
        //
        w_opt << "v_col: \"";
        w_opt << (AnsiString(V_col)).c_str();
        w_opt << "\"";
        w_opt << endl;
        //
        w_opt << "p_col: \"";
        w_opt << (AnsiString(P_col)).c_str();
        w_opt << "\"";
        w_opt << endl;
        //
        w_opt << "fdr_v_col: \"";
        w_opt << (AnsiString(V_col_fdr)).c_str();
        w_opt << "\"";
        w_opt << endl;
        //
        w_opt << "fdr_p_col: \"";
        w_opt << (AnsiString(P_col_fdr)).c_str();
        w_opt << "\"";
        w_opt << endl;
        //
        if( Form1->ExcludeAsterisk->Checked )
        {
                w_opt << "ex: \"ExcludeAsterisk\"";
                w_opt << endl;
        }
        if( Form1->ExcludeDash->Checked )
        {
                w_opt << "ex: \"ExcludeDash\"";
                w_opt << endl;
        }
        if( Form1->ExcludeUnderscore->Checked )
        {
                w_opt << "ex: \"ExcludeUnderscore\"";
                w_opt << endl;
        }
        if( Form1->ExcludeParentheses->Checked )
        {
                w_opt << "ex: \"ExcludeParentheses\"";
                w_opt << endl;
        }
        if( Form1->ExcludeSlash->Checked )
        {
                w_opt << "ex: \"ExcludeSlash\"";
                w_opt << endl;
        }
        if( Form1->ExcludeComma->Checked )
        {
                w_opt << "ex: \"ExcludeComma\"";
                w_opt << endl;
        }
        for( int i=0; i<Form1->lbNoReplace->Lines->Count; i++ )
                {
                w_opt << "NR: \"";
                AnsiString add = Form1->lbNoReplace->Lines->operator [](i);
                w_opt << add.c_str();
                w_opt << "\"";
                w_opt << endl;
                }
        for( int i=1; i<Form1->lbReplace->RowCount; i++ )
                {
                AnsiString add1 = Form1->lbReplace->Cells[0][i];
                AnsiString add2 = Form1->lbReplace->Cells[1][i];
                if( add1.Length() || add2.Length() )
                        {
                        w_opt << "R: \"";
                        w_opt << add1.c_str();
                        w_opt << "\" \"";
                        w_opt << add2.c_str();
                        w_opt << "\"";
                        w_opt << endl;
                        }
                }
        for( int i=0; i<Form1->ExclV->Lines->Count; i++ )
                {
                w_opt << "ExV: \"";
                AnsiString add = Form1->ExclV->Lines->operator [](i);
                w_opt << add.c_str();
                w_opt << "\"";
                w_opt << endl;
                }
        for( int i=0; i<Form1->ExclP->Lines->Count; i++ )
                {
                w_opt << "ExP: \"";
                AnsiString add = Form1->ExclP->Lines->operator [](i);
                w_opt << add.c_str();
                w_opt << "\"";
                w_opt << endl;
                }
        w_opt.close();
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
int CloseInValue (AnsiString test_str, int col_num, int start_i)
{
int TSL = test_str.Length();
test_str= test_str.Trim();
test_str= test_str.UpperCase();
if( !TSL )
        return -1;
if( test_str[1] < '0' || test_str[1] > '9' )
        return -1;
// get text index after value
int TIndex = 1;
while ( (test_str[TIndex] >= '0' && test_str[TIndex] <= '9') ||
        test_str[TIndex] == '.' ||
        test_str[TIndex] == ',' )
        {
        TIndex++;
        if( TIndex > TSL )
                {
                TIndex = 0;
                break;
                }
        }
long i = 0;
float i1 = ex_float( test_str, &i );
if( i1 )for( int gf=start_i; gf<Form1->GridFeeders->RowCount; gf++ )
        {
        AnsiString GS = Form1->GridFeeders->Cells[col_num][gf];
        GS = GS.Trim();
        GS= GS.UpperCase();
        int GSL = GS.Length();
        // on length test
        if( !GSL )
                continue;
        // on char test
        if( GS[1] < '0' || GS[1] > '9' )
                continue;
        // test text after value
        i = 1;
        while ( (GS[i] >= '0' && GS[i] <= '9') || GS[i] == '.' || GS[i] == ',' )
                {
                i++;
                if( i > GSL )
                        {
                        i = 0;
                        break;
                        }
                }
        if( i == 0 && TIndex )
                continue;
        if( i && TIndex == 0 )
                continue;
        if( i && TIndex )
                if( GS[i] != test_str[TIndex] )
                        continue;
        // float value testing
        i = 0;
        float i2 = ex_float( GS, &i );
        if( i2 )
                if( i1/i2 < 1.5 && i2/i1 < 1.5 )
                        return gf;
        }
return -1;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
int ShareProg (AnsiString test_str, int col_num, int start_i)
{
//test_str = test_str.Trim();
test_str = test_str.UpperCase();
int TSL = test_str.Length();
//if( TSL == 0 )
//        return -1;
AnsiString test;
for( int gf=start_i; gf<Form1->GridFeeders->RowCount; gf++ )
        {
        AnsiString GS = Form1->GridFeeders->Cells[col_num][gf];
        //GS = GS.Trim();
        GS= GS.UpperCase();
        int GSL = GS.Length();

        // length testing
        if( TSL == 0 && GSL == 0 )
                return gf;
        //if( TSL/3 >= GSL )
        //        continue;
        //if( GSL/3 >= TSL )
        //        continue;

        // matches
        int MIN = TSL;
        if(GSL < TSL)
                MIN = GSL;
        if( MIN > 1 )
        if( GS.SubString(1,MIN) == test_str.SubString(1,MIN) )
                return gf;
                           
        // float value testing
        long i = 0;
        float i1 = ex_float( test_str, &i )*100;
        i = 0;
        float i2 = ex_float( GS, &i )*100;
        if( (int)i1 != (int)i2 )
                continue;

        // remove dotzero
        for( int dotzero=GS.Pos(".0"); dotzero>0; dotzero=GS.Pos(".0") )
                 GS.Delete(dotzero,2);

        // test 1
        test = test_str;
        for( int dotzero=test.Pos(".0"); dotzero>0; dotzero=test.Pos(".0") )
                 test.Delete(dotzero,2);
        int f = 0;
        for( int t=1; t<=test.Length(); t++ )
                {
                int ii = GS.Pos(test.SubString(t,1));
                if( ii > 0 )
                        {
                        f++;
                        //if( ii > 1 && f <= GSL/2 )
                        //        break;
                        GS.Delete(1,ii);
                        if( GS.Length() == 0 )
                                break;
                        }
                }
        if( f == test.Length() )
                return gf;

        // test 2
        GS = Form1->GridFeeders->Cells[col_num][gf];
        test = test_str;
        for( int dotzero=test.Pos(".0"); dotzero>0; dotzero=test.Pos(".0") )
                 test.Delete(dotzero,2);
        f = 0;
        for( int t=1; t<=GS.Length(); t++ )
                {
                int ii = test.Pos(GS.SubString(t,1));
                if( ii > 0 )
                        {
                        f++;
                        //if( ii > 1 && f <= TSL/2 )
                        //        break;
                        test.Delete(1,ii);
                        if( test.Length() == 0 )
                                break;
                        }
                }
        if( f == GS.Length() )
                return gf;
        }
return -1;
}


//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
AnsiString FindReplace (AnsiString C, int col, int * POSITION)
{
for( (*POSITION)++; (*POSITION)<Form1->lbReplace->RowCount; (*POSITION)++ )
        {
        AnsiString getS = Form1->lbReplace->Cells[0][*POSITION];
        if( getS.Length() )
        if( getS.SubString(1,getS.Length()) == C.SubString(1,C.Length()) )
                return Form1->lbReplace->Cells[1][*POSITION];
        }
return __BREAK;
}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
bool StorageLimitPackageCount (AnsiString Package, int MaxC, int*POS)
{
int count = 0;
for( int f=0; f<Form1->PACKAGES->Items->Count; f++ )
        {
        AnsiString P = Form1->PACKAGES->Items->operator [](f);
        if( P.Length() == Package.Length() )
                {
                if( P.SubString(1,P.Length()) == Package.SubString(1,Package.Length()) )
                        {
                        count++;
                        if( count > MaxC )
                                return false;
                        }
                }
        }
count = 0;
for( int f=0; f<Form1->GridFeeders->RowCount; f++ )
        {
        AnsiString P = Form1->GridFeeders->Cells[PACKAGE_COL][f];
        if( P.Length() == Package.Length() )
                {
                if( P.SubString(1,P.Length()) == Package.SubString(1,Package.Length()) )
                        {
                        count++;
                        if( count > MaxC )
                                return false;
                        }
                }
        }
AnsiString Pack=FindReplace( Package, PACKAGE_COL, POS );
if( Pack.SubString(1,Pack.Length()) == __BREAK )
        return true;
if( StorageLimitPackageCount(Pack,MaxC,POS) )
        return true;
return false;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void FindSimilarFeeders( AnsiString V_s, AnsiString P_s )
{
AnsiString sV_s = V_s;
int * MARK = new int[Form1->GridFeeders->RowCount];
for( int u=0; u<Form1->GridFeeders->RowCount; u++ )
        MARK[u] = 0;
int fnd=0;
for( int rep=ShareProg(V_s,VALUE_COL,0); rep>0; rep=ShareProg(V_s,VALUE_COL,rep+1) )
        {
        fnd++;
        MARK[rep] = 1;
        AnsiString V = Form1->GridFeeders->Cells[VALUE_COL][rep];
        AnsiString P = Form1->GridFeeders->Cells[PACKAGE_COL][rep];
        AnsiString report_s = "similar? " + V + dSPACE + P + " (" + AnsiString(rep) + ")";
        Form1->lbReport->Items->Add(report_s);
        }
if( fnd < 5 )
        {
        int f = 1;
        for( ; f<=V_s.Length(); f++ )
                {
                if( V_s.SubString(f,1) == "0" ||
                    V_s.SubString(f,1) == "1" ||
                    V_s.SubString(f,1) == "2" ||
                    V_s.SubString(f,1) == "3" ||
                    V_s.SubString(f,1) == "4" ||
                    V_s.SubString(f,1) == "5" ||
                    V_s.SubString(f,1) == "6" ||
                    V_s.SubString(f,1) == "7" ||
                    V_s.SubString(f,1) == "8" ||
                    V_s.SubString(f,1) == "9" ||
                    V_s.SubString(f,1) == "." )
                        break;
                }
        for( ; f<=V_s.Length(); f++ )
                {
                if( V_s.SubString(f,1) == "0" ||
                    V_s.SubString(f,1) == "1" ||
                    V_s.SubString(f,1) == "2" ||
                    V_s.SubString(f,1) == "3" ||
                    V_s.SubString(f,1) == "4" ||
                    V_s.SubString(f,1) == "5" ||
                    V_s.SubString(f,1) == "6" ||
                    V_s.SubString(f,1) == "7" ||
                    V_s.SubString(f,1) == "8" ||
                    V_s.SubString(f,1) == "9" ||
                    V_s.SubString(f,1) == "." )
                        continue;
                break;
                }
        if( f > 1 )
                {
                if( f <= V_s.Length() )
                        {
                        V_s = V_s.SubString(1,f-1);
                        for( int rep=ShareProg(V_s,VALUE_COL,0); rep>0; rep=ShareProg(V_s,VALUE_COL,rep+1) )
                                {
                                if( MARK[rep] )
                                        continue;
                                fnd++;
                                MARK[rep] = 1;
                                AnsiString V = Form1->GridFeeders->Cells[VALUE_COL][rep];
                                AnsiString P = Form1->GridFeeders->Cells[PACKAGE_COL][rep];
                                AnsiString report_s = "similar? " + V + dSPACE + P + " (" + AnsiString(rep) + ")";
                                Form1->lbReport->Items->Add(report_s);
                                }
                        }
                }
        }
int iPOS = 0;
if( StorageLimitPackageCount( P_s,3,&iPOS ) )
        {
        for( int rep=ShareProg(P_s,PACKAGE_COL,0); rep>0; rep=ShareProg(P_s,PACKAGE_COL,rep+1) )
                {
                if( MARK[rep] )
                        continue;
                iPOS = 0;
                AnsiString P = Form1->GridFeeders->Cells[PACKAGE_COL][rep];
                if( StorageLimitPackageCount( P,3,&iPOS ) == 0 )
                        continue;
                fnd++;
                MARK[rep] = 1;
                AnsiString V = Form1->GridFeeders->Cells[VALUE_COL][rep];
                AnsiString report_s = "similar? " + V + dSPACE + P + " (" + AnsiString(rep) + ")";
                Form1->lbReport->Items->Add(report_s);
                }
        }
for( int rep=CloseInValue(sV_s,VALUE_COL,0); rep>0; rep=CloseInValue(V_s,VALUE_COL,rep+1) )
        {
        if( MARK[rep] )
                continue;
        MARK[rep] = 1;
        AnsiString V = Form1->GridFeeders->Cells[VALUE_COL][rep];
        AnsiString P = Form1->GridFeeders->Cells[PACKAGE_COL][rep];
        AnsiString report_s = "close in value? " + V + dSPACE + P + " (" + AnsiString(rep) + ")";
        Form1->lbReport->Items->Add(report_s);
        }
delete[] MARK;
}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void Compare( int FileNumber, bool TEST )
{
int m_matches = 0;
int m_news = 0;
int i_start = 0;//Form1->FileNumbers->Items->IndexOf(AnsiString(FileNumber));
int i_end = -1;
for( int ITERATOR=0; ITERATOR<Form1->ProjectsList->Count; ITERATOR++ )
        {
        i_end = Form1->FileNumbers->Items->IndexOf(AnsiString(FileNumber+1));
        if( i_end != -1 )
                break;
        }
Form1->ProgressBar1->Position = 0;
AnsiString S;
for( int index=i_end-1; index>=i_start; index-- )
        {
        float k = (float)(i_end-index-1)/(float)(i_end-i_start)*100.0;
        if( Form1->ProgressBar1->Position != (int)k )
                {
                Form1->ProgressBar1->Position = k;
                Application->ProcessMessages();
                }
        AnsiString V_str = Form1->VALUES->Items->operator [](index);
        AnsiString P_str = Form1->PACKAGES->Items->operator [](index);
        if( !V_str.Length() && !P_str.Length() )
                continue;
        AnsiString report_m = "match: " + V_str + dSPACE + P_str;
        AnsiString report_n = "new: " + V_str + dSPACE + P_str;
        //
        if( Form1->ExclV->Lines->IndexOf(V_str) != -1 )
                continue;
        if( Form1->ExclP->Lines->IndexOf(P_str) != -1 )
                continue;
        if( TEST )
                {
                int FIND = StorageIndexOf( V_str, P_str );
                if( FIND >= 0 )
                        continue;
                int * MarkStr = new int[Form1->GridFeeders->RowCount];
                for( int is=0; is<Form1->GridFeeders->RowCount; is++ )
                        MarkStr[is] = 0;
                // FOR VALUES
                for( int rep=ShareProg(V_str,VALUE_COL,0); rep>0; rep=ShareProg(V_str,VALUE_COL,rep+1) )
                        {
                        AnsiString getV = Form1->GridFeeders->Cells[VALUE_COL][rep];
                        AnsiString getP = Form1->GridFeeders->Cells[PACKAGE_COL][rep];
                        if( Form1->ExclV->Lines->IndexOf(getV) != -1 )
                                continue;
                        if( Form1->ExclP->Lines->IndexOf(getP) != -1 )
                                continue;
                        bool P_MATCH = 0;
                        if( getP.SubString(1,getP.Length()) == P_str.SubString(1,P_str.Length()) )
                                P_MATCH = 1;
                        // Go!
                        if( getV.SubString(1,getV.Length()) == V_str.SubString(1,V_str.Length()) )
                                {
                                if( LB_iof(P_str, getP) )
                                        continue;
                                //
                                AnsiString s1,s2,s3;
                                s1 = s2 = s3 = "empty string";
                                if( P_str.Length() )
                                        s1 = P_str;
                                if( getP.Length() )
                                        s2 = getP;
                                if( V_str.Length() )
                                        s3 = V_str;
                                int ret = Application->MessageBox((" Can I assume that the package "+s1+" is equal to "+s2+"? (for "+s3+" matching values)").c_str(), "Message", MB_YESNOCANCEL );
                                if( ret == ID_YES )
                                        {
                                        lbReplace_add( P_str, getP );   // packages are replaced
                                        goto BREAK;                     // values match
                                        }
                                else if( ret == ID_CANCEL )
                                        goto RETURN;
                                else    {
                                        lbNoReplace_add(P_str,getP);
                                        }
                                }
                        else if( ShareProg(getP,PACKAGE_COL,rep) == rep )
                                {
                                if( LB_iof(V_str, getV) == 0 )
                                        {
                                        AnsiString s1,s2,s3;
                                        s1 = s2 = s3 = "empty string";
                                        if( V_str.Length() )
                                                s1 = V_str;
                                        if( getV.Length() )
                                                s2 = getV;
                                        if( P_str.Length() )
                                                s3 = P_str;
                                        if( getP.Length() )
                                                {
                                                if( !P_MATCH )
                                                        s3 += " and " + getP;
                                                }
                                        int ret = Application->MessageBox(("Similar part values found. Can I assume that "+s1+" is equal to "+s2+"? (for "+s3+" packages)").c_str(), "Message", MB_YESNOCANCEL );
                                        if( ret == ID_YES )
                                                {
                                                lbReplace_add( V_str, getV ); // values are replaced
                                                if( P_MATCH )
                                                        goto BREAK; // packages match
                                                }
                                        else if( ret == ID_CANCEL )
                                                goto RETURN;
                                        else    {
                                                lbNoReplace_add(V_str,getV);
                                                if( !P_MATCH )
                                                        {
                                                        MarkStr[rep] = 1;
                                                        continue; // apparently they are completely different, continuation.
                                                        }
                                                }
                                        }
                                if( !P_MATCH )
                                if( LB_iof(P_str, getP) == 0 )
                                        {
                                        AnsiString s1,s2,s3;
                                        s1 = s2 = s3 = "empty string";
                                        if( P_str.Length() )
                                                s1 = P_str;
                                        if( getP.Length() )
                                                s2 = getP;
                                        if( V_str.Length() )
                                                s3 = V_str;
                                        if( getV.Length() )
                                        if( getV.SubString(1,getV.Length()) != V_str.SubString(1,V_str.Length()) )
                                                s3 += " and " + getV;
                                        int ret = Application->MessageBox(("Similar package names found. Can I assume that "+s1+" is equal to "+s2+"? (for "+s3+" values)").c_str(), "Message", MB_YESNOCANCEL );
                                        if( ret == ID_YES )
                                                {
                                                lbReplace_add( P_str, getP );
                                                }
                                        else if( ret == ID_CANCEL )
                                                goto RETURN;
                                        else    {
                                                lbNoReplace_add(P_str,getP);
                                                }
                                        }
                                }
                        }
                // FOR PACKAGES
                int ipos = 0;
                if( StorageLimitPackageCount(P_str,3,&ipos) )
                for( int rep=ShareProg(P_str,PACKAGE_COL,0); rep>0; rep=ShareProg(P_str,PACKAGE_COL,rep+1) )
                        {
                        if( MarkStr[rep] )
                                {
                                continue;
                                }
                        AnsiString getV = Form1->GridFeeders->Cells[VALUE_COL][rep];
                        AnsiString getP = Form1->GridFeeders->Cells[PACKAGE_COL][rep];
                        if( Form1->ExclV->Lines->IndexOf(getV) != -1 )
                                continue;
                        if( Form1->ExclP->Lines->IndexOf(getP) != -1 )
                                continue;
                        ipos = 0;
                        if( !StorageLimitPackageCount(getP,3,&ipos) )
                                continue;
                        bool V_MATCH = 0;
                        if( getV.SubString(1,getV.Length()) == V_str.SubString(1,V_str.Length()) )
                                V_MATCH = 1;
                        bool P_MATCH = 0;
                        if( getP.SubString(1,getP.Length()) == P_str.SubString(1,P_str.Length()) )
                                P_MATCH = 1;
                        // Go!
                        if( V_MATCH == 0 )
                        if( LB_iof(V_str, getV) == 0 )
                                {
                                AnsiString s1,s2,s3,s4;
                                s1 = s2 = s3 = s4 = "empty string";
                                if( V_str.Length() )
                                        s1 = V_str;
                                if( getV.Length() )
                                        s2 = getV;
                                if( P_str.Length() )
                                        s3 = P_str;
                                //
                                if( P_MATCH )
                                        s4 = "";
                                else if( getP.Length() )
                                        s4 = " and " + getP;
                                //
                                int ret = Application->MessageBox((" Can I assume that the value "+s1+" is equal to "+s2+"? (for rare packages: "+s3+s4+")").c_str(), "Message", MB_YESNOCANCEL );
                                if( ret == ID_YES )
                                        {
                                        lbReplace_add( V_str, getV ); // values are replaced
                                        if( P_MATCH )
                                                goto BREAK; // packages match
                                        }
                                else if( ret == ID_CANCEL )
                                        goto RETURN;
                                else    {
                                        lbNoReplace_add(V_str,getV);
                                        if( !P_MATCH )
                                                continue; // apparently they are completely different, continuation.
                                        }
                                }
                        if( P_MATCH == 0 )
                        if( LB_iof(P_str, getP) == 0 )
                                {
                                AnsiString s1,s2;
                                s1 = s2 = "empty string";
                                if( P_str.Length() )
                                        s1 = P_str;
                                if( getP.Length() )
                                        s2 = getP;
                                int ret = Application->MessageBox((" Can I assume that the package "+s1+" is equal to "+s2+"?").c_str(), "Message", MB_YESNOCANCEL );
                                if( ret == ID_YES )
                                        {
                                        lbReplace_add( P_str, getP );
                                        }
                                else if( ret == ID_CANCEL )
                                        goto RETURN;
                                else    {
                                        lbNoReplace_add(P_str,getP);
                                        }
                                }
                        }
                delete[] MarkStr;
                }
        else    {
                //
                int posRepl_v = 0;
                AnsiString value = V_str;
                do      {
                        int posRepl_p = 0;
                        AnsiString package = P_str;
                        do      {
                                int FIND = StorageIndexOf( value, package );
                                if( FIND >= 0 )
                                        {
                                        if( Form1->lbReport->Items->IndexOf(report_m) == -1 )
                                                {
                                                m_matches++;
                                                report_m += " (" + AnsiString(FIND) + ")";
                                                Form1->lbReport->Items->Add(report_m);
                                                Form1->FileNumbers->Items->Delete(index);
                                                Form1->FileNumbers->Items->Insert(index,"f");
                                                if( Form1->GridFeeders->Cells[0][FIND].SubString(1,1) != "f" )
                                                        Form1->GridFeeders->Cells[0][FIND] = "found (" + Form1->GridFeeders->Cells[0][FIND] + ")";
                                                }
                                        goto BREAK;
                                        }
                                package=FindReplace( P_str, PACKAGE_COL, &posRepl_p );
                                }while( package.SubString(1,package.Length()) != __BREAK );
                        value=FindReplace( V_str, VALUE_COL, &posRepl_v );
                        }while( value.SubString(1,value.Length()) != __BREAK );
                //
                if( Form1->lbReport->Items->IndexOf(report_n) == -1 )
                        {
                        m_news++;
                        Form1->lbReport->Items->Add(report_n);
                        FindSimilarFeeders( V_str,P_str );
                        }
                }
        BREAK: continue;
        }

RETURN:
if( !TEST )
        {
        AnsiString str = AnsiString(m_matches);
        while( str.Length() < 4 )
                str = "0" + str;
        Form1->GridResult->Cells[1][Form1->GridResult->RowCount-1] = str;
        str = AnsiString(m_news);
        while( str.Length() < 4 )
                str = "0" + str;
        Form1->GridResult->Cells[2][Form1->GridResult->RowCount-1] = str;
        if( m_news==0 && m_matches!=0 && Form1->ProjectsList->Items->Count == 1 )
                {
                ShowMessage("FreePcb-2 congratulates you! There are no new parts in this PCB design.");
                }
        }
Form1->ProgressBar1->Position = 0;
Form1->Mess->Caption = "";
Application->ProcessMessages();
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void GenReportTXT()
{
int num = 0;
ofstream RP((ExtractFilePath(Application->ExeName) + "report.txt").c_str());
for( int i=0; i<Form1->TreeReport->Items->Count; i++ )
        {
        TTreeNode * N = Form1->TreeReport->Items->operator [](i);
        if( TreeLabelList.iof(N) == NULL )
                {
                AnsiString r = N->Text;
                if(N->IsVisible)
                        {
                        bool W = 0;
                        int p1 = r.Pos(") ");
                        if( p1 > 0 && p1 < 5 )
                                {
                                W = 1;
                                num++;
                                r = AnsiString(num) + ") " + r.SubString(p1+2,r.Length()-p1-1);
                                }
                        if(r.SubString(1,7) == "similar")
                                W = 1;
                        else if(N->Expanded || !N->HasChildren)
                                W = 1;
                        for(int sp=0; sp<N->Level; sp++ )
                                r = "    " + r;
                        if(W)   RP << r.c_str() << endl;
                        if( r.TrimLeft().SubString(1,6) == "new el" || r.TrimLeft().SubString(1,6) == "feeder" )
                                num = 0;
                        }

                }
        }
RP.close();
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void GenerateFeedersTXT()
{
int * max_w = new int[Form1->GridFeeders->RowCount];
for( int c=0; c<Form1->GridFeeders->ColCount; c++ )
        max_w[c] = 0;
for( int r=0; r<Form1->GridFeeders->RowCount; r++ )
for( int c=0; c<Form1->GridFeeders->ColCount; c++ )
        {
        if( max_w[c] < Form1->GridFeeders->Cells[c][r].Length() )
                max_w[c] = Form1->GridFeeders->Cells[c][r].Length();
        }
AnsiString pth = ExtractFilePath(Application->ExeName);
ofstream Rw((pth+"feeders.txt").c_str());
for( int r=0; r<Form1->GridFeeders->RowCount; r++ )
        {
        for( int c=0; c<Form1->GridFeeders->ColCount; c++ )
                {
                Rw << Form1->GridFeeders->Cells[c][r].c_str();
                for( int ii=Form1->GridFeeders->Cells[c][r].Length(); ii<max_w[c]+2; ii++ )
                        Rw << " ";
                }
        if( r==0 )
                Rw << "file";
        else    Rw << Form1->FileBox->Items->operator [](r-1).c_str();
        Rw << endl;
        }
Rw.close();
delete[] max_w;
}

AnsiString GenerateVPL(AnsiString pth)
{
if( pth.Length() > 3 )
if( pth.SubString(pth.Length()-3,4) != ".vpl" )
        pth += ".vpl";
//
ofstream Rw(pth.c_str());
AnsiString fn = ExtractFileName(pth);
for( int r=1; r<Form1->GridFeeders->RowCount; r++ )
        {
        if( Form1->GridFeeders->Cells[1][r].Length() || Form1->GridFeeders->Cells[2][r].Length() )
                {
                if( Form1->GridFeeders->Cells[1][r].Length() )
                        Rw << Form1->GridFeeders->Cells[1][r].c_str();
                else    Rw << "---";
                Rw << "\t";
                if(Form1->GridFeeders->Cells[1][r].Length()<8)
                        Rw << "\t";
                if( Form1->GridFeeders->Cells[2][r].Length() )
                        Rw << Form1->GridFeeders->Cells[2][r].c_str();
                else    Rw << "---";
                Rw << "\t";
                if(Form1->GridFeeders->Cells[2][r].Length()<8)
                        Rw << "\t";
                Rw << Form1->FileBox->Items->operator [](r-1).c_str();
                Rw << endl;
                }
        }
Rw.close();
return pth;
}
