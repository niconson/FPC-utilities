//---------------------------------------------------------------------------


#pragma hdrstop

#include "C_area_C_board.h"
#include "Debug_Areas.h"
#include "ProcessMessages.h"
#include "New.h"
#pragma package(smart_init)
MLine * BRD;
int brd;
int BrdMem;
double Fx;
double Fy;






//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
bool CirquitDirect (MLine * Lines, int cnt)
        {
        return 0;
        }






//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void ExBRD (int Start, int CntCor)
        {
        short int i;
        AnsiString S = "";
        AnsiString SBack = "";
        int I = Start;
        BrdMem = 0;
        while (I < (Start + CntCor))
                {
                S = Form1->File->Items->operator [](I);
                I++;
                if ( S.SubString(1,3) == "cor" )
                        {
                        i = prob(S,4);
                        int T = ex_float_NM ( S, &i, -1);
                        if (T)  BrdMem = BrdMem + 20;
                        else    BrdMem++;
                        }
                }
        if (BRD)   delete[] BRD;
        try                     {BRD = new(std::nothrow) MLine[BrdMem];}
        catch(std::bad_alloc)   {ShowMessage("    Error of memory: Line[" + AnsiString(BrdMem) + "]!" );}
        brd = 0;
        I = Start;
        while (I < (Start + CntCor))
                {
                S = Form1->File->Items->operator [](I);
                I++;
                if ( S.SubString(1,3) == "cor" && SBack.SubString(1,3) == "cor" )
                        {
                        i = prob(S,1);
                        int  NCo =      ex_float_NM ( S,&i, -1);
                        float Xcor1 =   ex_float_NM ( S,&i, -1);
                        float Ycor1 =   ex_float_NM ( S,&i, -1);
                        i = prob(SBack,2);
                        float Xcor2 =   ex_float_NM ( SBack,&i, -1);
                        float Ycor2 =   ex_float_NM ( SBack,&i, -1);
                        int T =         ex_float_NM ( SBack,&i, -1);
                        if (NCo == 2)
                                {
                                Fx = Xcor2;
                                Fy = Ycor2;
                                }
                        if (NCo > 1)
                        for (int k=0; k<2; k++)
                                {
                                float ARC[GEN_ARC_NUM_CORNERS*2];
                                int CLines = Generate_Line(Xcor2,Ycor2,Xcor1,Ycor1,T,&ARC[0]);
                                for (int m=0; (m+3)<CLines; m=m+2)
                                        {
                                        BRD[brd].X1 = ARC[m];
                                        BRD[brd].Y1 = ARC[m+1];
                                        BRD[brd].X2 = ARC[m+2];
                                        BRD[brd].Y2 = ARC[m+3];
                                        BRD[brd].First = 0;
                                        BRD[brd].FlagDelete = 0;
                                        BRD[brd].FlagWrite = 0;
                                        brd++;
                                        }
                                if (NCo < CntCor) break;
                                Xcor2 = Xcor1;
                                Ycor2 = Ycor1;
                                Xcor1 = Fx;
                                Ycor1 = Fy;
                                i = prob(S,4);
                                T =     ex_float_NM ( S,&i, -1);
                                }
                        }
                SBack = S;
                }
        }








//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void FindLinesBRD (void)
        {
        short int i;
        AnsiString S = "";
        AnsiString SBack = "";
        int indexEND = Form1->File->Items->IndexOf("[solder_mask_cutouts]") ;
        int index = Form1->File->Items->IndexOf("[board]") ;
        index++;
        if (index == -1 ) ShowMessage("    Fatal Error! String: [board] not found!" );
        else while (index < indexEND)
                {
                S = Form1->File->Items->operator [](index);
                index++;
                if ( S.SubString(1,3) == "out" )
                        {
                        i = prob(S,1);
                        int cntVertex =     ex_float_NM ( S,&i, -1);
                        ExBRD ((index+1), cntVertex);
                        }
                }
        }




//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void CombineWithArea_CombineWithBoard (void)
        {
        //Generate NewLineBrd
        FindLinesBRD();

        for (int k=0; k<CntLnsArea; k++)
                {
                Form3->Label1->Caption = "Creating contour ¹ ";
                Application->ProcessMessages();
                }
        if (BRD)   delete[] BRD;
        }