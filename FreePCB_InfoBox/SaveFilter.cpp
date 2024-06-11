//---------------------------------------------------------------------------


#pragma hdrstop

#include "SaveFilter.h"
#include "Comp_man.h"
#include "Path_EXE.h"
#include "fstream.h"
//---------------------------------------------------------------------------
#define NUM_EDIT_BOXES 3
#pragma package(smart_init)
static int MCASE = 0;




int IOF(AnsiString s)
{
        for( int item=3; item<Form1->SF->Items->Count; item++ )
                {
                TMenuItem * N1 = Form1->SF->Items->operator [](item);
                AnsiString sf = N1->Caption;
                for( int i = sf.Pos("&"); i>0; i = sf.Pos("&") )
                        sf.Delete(i,1);
                if ( s.SubString(1,s.Length()) == sf.SubString(1,sf.Length()) )
                        return item;
                }
        return -1;
}






int SaveFilter(int CASE)
        {
        int ERR = 1;
        if((CASE == col_RefDes &&  Form2->check_refs->Checked == 0) ||
           (CASE == col_Value &&   Form2->check_values->Checked == 0) ||
           (CASE == col_Package && Form2->check_package->Checked == 0) )
                {
                ShowMessage("  EN: It is impossible to start the save process as the column is invisible (right-click on the parts list, then enter the SETTINGS menu)");
                return ERR;
                }
        if (FlagSaveFilter)
                CASE += MCASE + col_Package + 1;
        else
                MCASE = CASE;
        FlagSaveFilter = true;
        Form1->StringGridParts->Visible = false;
        // 1
        Form1->BRefDes->        Enabled = false;
        Form1->CRefDes->        Enabled = false;
        // 2
        Form1->BRIRange->       Enabled = false;
        Form1->MinRI->          Enabled = false;
        Form1->MaxRI->          Enabled = false;
        // 3
        Form1->BValue->         Enabled = false;
        Form1->CValue->         Enabled = false;
        // 4
        Form1->BValueNL->       Enabled = false;
        Form1->CValueNL->       Enabled = false;
        // 5
        Form1->BPackage->       Enabled = false;
        Form1->CPackage->       Enabled = false;
        // 6
        Form1->BPackageNL->     Enabled = false;
        Form1->CPackageNL->     Enabled = false;
        // 7
        Form1->BFootPrint->     Enabled = false;
        Form1->CFootPrint->     Enabled = false;
        // 8
        Form1->BMerge->         Enabled = false;
        Form1->CMerge->         Enabled = false;
        // 9
        Form1->BPins->          Enabled = false;
        Form1->MinPin->         Enabled = false;
        Form1->MaxPins->        Enabled = false;
        // 10
        Form1->BHoles->         Enabled = false;
        Form1->MinHoles->       Enabled = false;
        Form1->MaxHoles->       Enabled = false;
        // 11
        Form1->BSide->          Enabled = false;
        Form1->Side->           Enabled = false;
        // 12
        Form1->BGlueds->        Enabled = false;
        Form1->Glueds->         Enabled = false;
        // 13
        Form1->BAng->           Enabled = false;
        Form1->Ang->            Enabled = false;
        // 14
        Form1->BX->             Enabled = false;
        Form1->EXmin->          Enabled = false;
        Form1->EXmax->          Enabled = false;
        // 15
        Form1->BY->             Enabled = false;
        Form1->EYmin->          Enabled = false;
        Form1->EYmax->          Enabled = false;
        // 16
        Form1->BCNetlist->      Enabled = false;
        Form1->CCNetlist->      Enabled = false;
        //
        if (CASE == col_RefDes)
                {
                Form1->CRefDes->Enabled = true;
                if (Form2->Language->Checked)   Form1->Caption = "Âגוהטעו טלÿ Ref פטכüענא ט םאזלטעו ENTER";
                else                            Form1->Caption = "Enter name of the Ref filter and press ENTER";
                Form1->CRefDes->Text = "Enter name";
                Form1->CRefDes->SelectAll();
                }
        else if (CASE == col_Value)
                {
                Form1->CValue->Enabled = true;
                if (Form2->Language->Checked)   Form1->Caption = "Âגוהטעו טלÿ Val פטכüענא ט םאזלטעו ENTER";
                else                            Form1->Caption = "Enter name of the Value filter and press ENTER";

                Form1->CValue->Text = "Enter name";
                Form1->CValue->SelectAll();
                }
        else if (CASE == col_Package)
                {
                Form1->CPackage->Enabled = true;
                if (Form2->Language->Checked)   Form1->Caption = "Âגוהטעו טלÿ Pac פטכüענא ט םאזלטעו ENTER";
                else                            Form1->Caption = "Enter name of the Package filter and press ENTER";
                Form1->CPackage->Text = "Enter name";
                Form1->CPackage->SelectAll();
                }
        else    {
                if (CASE <= col_Package + col_Package + 1)
                        {
                        A = ExtractFilePath(FileName) + "related_files\\infobox\\";
                        if( DirectoryExists(A) == 0 )
                                CreateDirectory(A.c_str(),NULL);
                        if (CASE == col_RefDes + col_Package + 1)
                                {
                                A = A + Form1->CRefDes->Text;
                                if ( A.SubString((A.Length()-1),2) != ".r" ) A += ".r";
                                }
                        if (CASE == col_Value + col_Package + 1)
                                {
                                A = A + Form1->CValue->Text;
                                if ( A.SubString((A.Length()-1),2) != ".v" ) A += ".v";
                                }
                        if (CASE == col_Package + col_Package + 1)
                                {
                                A = A + Form1->CPackage->Text;
                                if ( A.SubString((A.Length()-1),2) != ".p" ) A += ".p";
                                }
                        if (FileName.Length())
                        if (A.SubString((A.Length()-2),1) != "\\")
                                {
                                //ןנמגונךא
                                FILE* F;
                                F = fopen(A.c_str(),"r");
                                if(F == NULL)
                                        {
                                        ofstream CreateFilter (A.c_str());
                                        CreateFilter.close();
                                        Application->ProcessMessages();
                                        }
                                else    fclose(F);
                                F = fopen(A.c_str(),"a+");
                                if(F)   {
                                        fclose(F);
                                        Form1->SortedBox->Items->Clear();
                                        Form1->SortedBox->Items->LoadFromFile(A);
                                        for (int k = 0; k < Form1->StringGridParts->RowCount; k++)
                                                {
                                                AnsiString S;
                                                if (CASE == col_RefDes + col_Package + 1)
                                                        S = Form1->StringGridParts->Cells[def_RefDes][k];
                                                else if (CASE == col_Value + col_Package + 1)
                                                        S = Form1->StringGridParts->Cells[def_Value][k];
                                                else if (CASE == col_Package + col_Package + 1)
                                                        S = Form1->StringGridParts->Cells[def_Package][k];
                                                S = S.Trim();
                                                if (S.Length())
                                                if (Form1->SortedBox->Items->IndexOf(S) == -1)
                                                        Form1->SortedBox->Items->Add(S);
                                                }
                                        ofstream FilterW;
                                        FilterW.open(A.c_str()); //// std::ios_base::app );
                                        AnsiString wr;
                                        for (int k = 0; k < Form1->SortedBox->Items->Count; k++)
                                                {
                                                wr = Form1->SortedBox->Items->operator [](k);
                                                if (wr.Length())
                                                        FilterW << wr.c_str() << endl;
                                                }
                                        FilterW.close();
                                        A = ExtractFileName(A);
                                        if (CASE >= (col_RefDes + col_Package + 1) &&
                                            CASE <= (col_Package + col_Package + 1) &&
                                            IOF(A) == -1)
                                                {
                                                TMenuItem * N = new TMenuItem(Form1);
                                                N->Caption = A;
                                                Form1->SF->Items->Add(N);
                                                //
                                                TMenuItem * add1 = new TMenuItem(Form1);
                                                add1->Caption = "Attach current list";
                                                TMenuItem * remove1 = new TMenuItem(Form1);
                                                remove1->Caption = "Remove current list";
                                                TMenuItem * open1 = new TMenuItem(Form1);
                                                open1->Caption = "Open";
                                                TMenuItem * translate1 = new TMenuItem(Form1);
                                                translate1->Caption = "Perform";
                                                N->Add(translate1);
                                                N->Add(open1);
                                                N->Add(add1);
                                                N->Add(remove1);
                                                N->InsertNewLineAfter(open1);
                                                add1->OnClick = Form1->MItemClick;
                                                remove1->OnClick = Form1->MItemClick;
                                                open1->OnClick = Form1->MItemClick;
                                                translate1->OnClick = Form1->MItemClick;
                                                }
                                        save_path_func();
                                        }
                                else    fclose(F);
                                }
                        }
                else    {
                        Form1->CRefDes->Text = "";
                        Form1->CValue->Text = "";
                        Form1->CPackage->Text = "";
                        }
                FlagSaveFilter = false;
                Form1->StringGridParts->Visible = true;
                // 1
                Form1->BRefDes->        Enabled = true;
                Form1->CRefDes->        Enabled = true;
                // 2
                Form1->BRIRange->       Enabled = true;
                Form1->MinRI->          Enabled = true;
                Form1->MaxRI->          Enabled = true;
                // 3
                Form1->BValue->         Enabled = true;
                Form1->CValue->         Enabled = true;
                // 4
                Form1->BValueNL->       Enabled = true;
                Form1->CValueNL->       Enabled = true;
                // 5
                Form1->BPackage->       Enabled = true;
                Form1->CPackage->       Enabled = true;
                // 6
                Form1->BPackageNL->     Enabled = true;
                Form1->CPackageNL->     Enabled = true;
                // 7
                Form1->BFootPrint->     Enabled = true;
                Form1->CFootPrint->     Enabled = true;
                // 8
                Form1->BMerge->         Enabled = true;
                Form1->CMerge->         Enabled = true;
                // 9
                Form1->BPins->          Enabled = true;
                Form1->MinPin->         Enabled = true;
                Form1->MaxPins->        Enabled = true;
                // 10
                Form1->BHoles->         Enabled = true;
                Form1->MinHoles->       Enabled = true;
                Form1->MaxHoles->       Enabled = true;
                // 11
                Form1->BSide->          Enabled = true;
                Form1->Side->           Enabled = true;
                // 12
                Form1->BGlueds->        Enabled = true;
                Form1->Glueds->         Enabled = true;
                // 13
                Form1->BAng->           Enabled = true;
                Form1->Ang->            Enabled = true;
                // 14
                Form1->BX->             Enabled = true;
                Form1->EXmin->          Enabled = true;
                Form1->EXmax->          Enabled = true;
                // 15
                Form1->BY->             Enabled = true;
                Form1->EYmin->          Enabled = true;
                Form1->EYmax->          Enabled = true;
                // 16
                Form1->BCNetlist->      Enabled = true;
                Form1->CCNetlist->      Enabled = true;
                ///
                if (CASE == col_RefDes + col_Package + 1)
                        Form1->CRefDes->Text = "";
                if (CASE == col_Value + col_Package + 1)
                        Form1->CValue->Text = "";
                if (CASE == col_Package + col_Package + 1)
                        Form1->CPackage->Text = "";
                Form1->SortedBox->Items->Clear();
                return 0;
                }
        return 0;
        }
