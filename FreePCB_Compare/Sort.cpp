//---------------------------------------------------------------------------


#pragma hdrstop

#include "Sort.h"
#include "fpcc.h"
//---------------------------------------------------------------------------
static bool DIRECT;
#pragma package(smart_init)





        
//---------------------------------------------------------------------------
void Sort ( int n_col )
{
Form1->MicroStrings->Items->Clear();
Form1->MicroStrings->Sorted = true;
int Pos;
AnsiString Str;
if (DIRECT) DIRECT = false;
else        DIRECT = true;
if (Form1->PageControl1->TabIndex == 0)
        {
        for (int k=1;k<Form1->GridFeeders->RowCount; k++)
                {
                Str = " \"" + Form1->GridFeeders->Cells[n_col][k] + "\" ";
                for( int col=0; col<Form1->GridFeeders->ColCount; col++ )
                        {
                        if( col == n_col )
                                continue;
                        Str += "\"" + Form1->GridFeeders->Cells[col][k] + "\" ";
                        }
                Form1->MicroStrings->Items->Add(Str);
                }
        if (DIRECT) for (int k=0;k<Form1->MicroStrings->Items->Count; k++)
                {
                Str = Form1->MicroStrings->Items->operator [](k);
                short int i = 0;
                Form1->GridFeeders->Cells[n_col][k+1] = ex_str( Str, &i );
                for( int col=0; col<Form1->GridFeeders->ColCount; col++ )
                        {
                        if( col == n_col )
                                continue;
                        Form1->GridFeeders->Cells[col][k+1] = ex_str( Str, &i );
                        }
                }
        else for (int k=(Form1->MicroStrings->Items->Count-1); k>=0; k--)
                {
                Str = Form1->MicroStrings->Items->operator [](k);
                short int i = 0;
                Form1->GridFeeders->Cells[n_col][Form1->MicroStrings->Items->Count-k] = ex_str( Str, &i );
                for( int col=0; col<Form1->GridFeeders->ColCount; col++ )
                        {
                        if( col == n_col )
                                continue;
                        Form1->GridFeeders->Cells[col][Form1->MicroStrings->Items->Count-k] = ex_str( Str, &i );
                        }
                }
        }
else if (Form1->PageControl1->TabIndex == 2)
        {
        for (int k=1;k<Form1->GridResult->RowCount; k++)
                {
                Str = " \"" + Form1->GridResult->Cells[n_col][k] + "\" ";
                for( int col=0; col<Form1->GridResult->ColCount; col++ )
                        {
                        if( col == n_col )
                                continue;
                        Str += "\"" + Form1->GridResult->Cells[col][k] + "\" ";
                        }
                Form1->MicroStrings->Items->Add(Str);
                }
        if (DIRECT) for (int k=0;k<Form1->MicroStrings->Items->Count; k++)
                {
                Str = Form1->MicroStrings->Items->operator [](k);
                short int i = 0;
                Form1->GridResult->Cells[n_col][k+1] = ex_str( Str, &i );
                for( int col=0; col<Form1->GridResult->ColCount; col++ )
                        {
                        if( col == n_col )
                                continue;
                        Form1->GridResult->Cells[col][k+1] = ex_str( Str, &i );
                        }
                }
        else for (int k=(Form1->MicroStrings->Items->Count-1); k>=0; k--)
                {
                Str = Form1->MicroStrings->Items->operator [](k);
                short int i = 0;
                Form1->GridResult->Cells[n_col][Form1->MicroStrings->Items->Count-k] = ex_str( Str, &i );
                for( int col=0; col<Form1->GridResult->ColCount; col++ )
                        {
                        if( col == n_col )
                                continue;
                        Form1->GridResult->Cells[col][Form1->MicroStrings->Items->Count-k] = ex_str( Str, &i );
                        }
                }
        }
Form1->MicroStrings->Items->Clear();
Form1->MicroStrings->Sorted = false;
}