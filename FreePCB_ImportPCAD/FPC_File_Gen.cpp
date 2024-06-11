//---------------------------------------------------------------------------


#pragma hdrstop

#include "FPC_File_Gen.h"
#include "HEAD.h"
#include "fstream.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)


//подсчет кол-во пинов, сегментов трасс, полигонов
void ex_count_net_param (int *countPin, int *countCon, int *countArea, AnsiString NetName)
        {
        long i = 0;
        char str[MAX_CHARS];
        *countPin = 0;
        *countCon = 0;
        *countArea = 0;
        //read Ntlst_and_Area.txt
        AnsiString A = ExtractFilePath (Application->ExeName)  ;
        A = A + "Import_Tango\\Ntlst_and_Area.txt";
        ifstream NETS (A.c_str());
        AnsiString NET;
        while (A.SubString(1,3) != "end")
                {
                NETS.getline(str,sizeof(str));
                A = str;
                A = A.Trim();
                if (A.SubString(1,3) == "net")
                        {
                        i = prob(A,1);
                        NET = ex_str (A, &i);
                        }
                if (NET.SubString(1,NET.Length()) == NetName.SubString(1,NetName.Length()))
                        {
                        if (A.SubString(1,4) == "area") (*countArea)++;
                        if (A.SubString(1,3) == "pin") (*countPin)++;
                        if (A.SubString(1,7) == "connect") (*countCon)++;
                        }
                }
        NETS.close();
        }

void FPC_File_Gen (void)
{
AnsiString S = ExtractFilePath (Application->ExeName);
S = S + "Import_Tango\\SM.txt";
ofstream smcut;
smcut.open (S.c_str(), std::ios_base::app);
smcut << "end" << endl;
smcut.close();


//создание файла FPC
long i = 0;
char str[MAX_CHARS];
Form1->Label4->Caption = "FPC_File_Gen..." ;
Application->ProcessMessages();
Sleep (500);

//read GRB.txt
AnsiString A = ExtractFilePath (Application->ExeName)  ;
ifstream Grb ((A + "Import_Tango\\Grb.txt").c_str());
ifstream Opt ((A + "Import_Tango\\Options.txt").c_str());
Grb.getline(str,sizeof(str));
//AnsiString Units = str;
Grb.getline(str,sizeof(str));
AnsiString mask_clearance = str;
Grb.getline(str,sizeof(str));
AnsiString shrink_paste_mask = str;
Grb.getline(str,sizeof(str));
AnsiString fill_clearance = str;
Grb.close();

//создание файла FPC
ofstream FPC (SaveD.c_str());
Opt.getline(str,sizeof(str));
A = str;
A = A.Trim();
while (A.SubString(1,3) != "end")
        {
        if      (A.SubString(1,14) == "fill_clearance")         FPC << fill_clearance.c_str() << endl;
        else if (A.SubString(1,14) == "mask_clearance")         FPC << mask_clearance.c_str() << endl;
        else if (A.SubString(1,17) == "shrink_paste_mask")      FPC << shrink_paste_mask.c_str() << endl;
        else if (A.SubString(1,15) == "n_copper_layers")
                {
                FPC << "n_copper_layers: ";
                MaxLayerNumRef = MaxLayerNumRef - 11;
                if (MaxLayerNumRef < 2) MaxLayerNumRef = 2;
                FPC << AnsiString(MaxLayerNumRef).c_str() << endl;
                }
        else    FPC << A.c_str() << endl;
        Opt.getline(str,sizeof(str));
        A = str;
        A = A.Trim();
        }
FPC << endl;
FPC << endl;
Opt.close();
FPC << "[footprints]" << endl;
FPC << endl;
//===================
//read FootPrints.txt
A = ExtractFilePath (Application->ExeName)  ;
A = A + "Import_Tango\\FootPrints.txt";
ifstream FootPr (A.c_str());
while (1)
        {
        FootPr.getline(str,sizeof(str));
        A = str;
        if (A.SubString(1,A.Length()) == "end" )        continue;
        if (A.SubString(1,A.Length()) == "Total" )      break;
        FPC << str << endl;
        }
FootPr.close();
FPC << endl;
for (int b = 0; b<11; b++)
        {
        A = ExtractFilePath (Application->ExeName)  ;
        switch (b)
                {
                case 0: A = A + "Import_Tango\\TOP_LINES.txt";          break;
                case 1: A = A + "Import_Tango\\BOTTOM_LINES.txt";       break;
                case 2: A = A + "Import_Tango\\INNERS_LINES.txt";       break;
                case 3: A = A + "Import_Tango\\TOP_SILK.txt";           break;
                case 4: A = A + "Import_Tango\\BOTTOM_SILK.txt";        break;
                case 5: A = A + "Import_Tango\\TOP_MASK.txt";           break;
                case 6: A = A + "Import_Tango\\BOTTOM_MASK.txt";        break;
                case 7: A = A + "Import_Tango\\TOP_PASTE.txt";          break;
                case 8: A = A + "Import_Tango\\BOTTOM_PASTE.txt";       break;
                case 9: A = A + "Import_Tango\\ASSY_TOP_LINES.txt";     break;
                case 10: A = A + "Import_Tango\\ASSY_BOTTOM_LINES.txt"; break;
                }
        ifstream AllLines (A.c_str());
        while (1)
                {
                AllLines.getline(str,sizeof(str));
                A = str;
                if (A.SubString(1,A.Length()) == "end" )        break;
                if (A.Length()) FPC << str << endl;
                }
        AllLines.close();
        }
//===================
FPC << endl;
FPC << "[board]" << endl;
FPC << endl;
//===================
//read Board.txt
A = ExtractFilePath (Application->ExeName)  ;
A = A + "Import_Tango\\Board.txt";
ifstream Board (A.c_str());
while (1)
        {
        Board.getline(str,sizeof(str));
        A = str;
        if (A.SubString(1,A.Length()) == "end" ) break;
        FPC << str << endl;
        }
Board.close();
//===================
FPC << endl;
FPC << "[solder_mask_cutouts]" << endl;
A = ExtractFilePath (Application->ExeName)  ;
A = A + "Import_Tango\\SM.txt";
ifstream SMC (A.c_str());
while (1)
        {
        SMC.getline(str,sizeof(str));
        A = str;
        if (A.SubString(1,A.Length()) == "end" ) break;
        FPC << str << endl;
        }
SMC.close();
FPC << endl;
//===================
FPC << endl;
FPC << "[graphics]" << endl;
A = ExtractFilePath (Application->ExeName)  ;
A = A + "Import_Tango\\Graphics.txt";
ifstream Graphic (A.c_str());
while (1)
        {
        Graphic.getline(str,sizeof(str));
        A = str;
        if (A.SubString(1,A.Length()) == "end" ) break;
        FPC << str << endl;
        }
Graphic.close();
//===================
FPC << endl;
FPC << "[parts]" << endl;
FPC << endl;
//===================
//read PartList.txt
A = ExtractFilePath (Application->ExeName)  ;
A = A + "Import_Tango\\PartList.txt";
ifstream PartL (A.c_str());
AnsiString M;
while (1)
        {
        PartL.getline(str,sizeof(str));
        A = str;
        A = A.Trim();
        if (A.SubString(1,A.Length()) == "Total" )
                break;
        if (A.SubString(1,A.Length()) == "end" )
                continue;
        if (A.SubString(1,4) == "pos:")
                {
                M = A;
                continue;
                }
        else if(A.SubString(1,6) == "shape:")
                {
                FPC << str << endl;
                FPC << M.c_str() << endl;
                continue;
                }
        FPC << str << endl;
        }
PartL.close();
//===================
AnsiString PART;
AnsiString SHAPE;
for (int b=0; b<11; b++)
        {
        switch (b)
                {
                case 0: PART = "TopLinesImport";
                        SHAPE = "TOP_LINES";
                        break;
                case 1: PART = "BottomLinesImport";
                        SHAPE = "BOTTOM_LINES";
                        break;
                case 2: PART = "InnersLinesImport";
                        SHAPE = "INNERS_LINES";
                        break;
                case 3: PART = "TopSilkImport";
                        SHAPE = "TOP_SILK";
                        break;
                case 4: PART = "BotSilkImport";
                        SHAPE = "BOTTOM_SILK";
                        break;
                case 5: PART = "TopMaskImport";
                        SHAPE = "TOP_MASK";
                        break;
                case 6: PART = "BotMaskImport";
                        SHAPE = "BOTTOM_MASK";
                        break;
                case 7: PART = "TopPasteImport";
                        SHAPE = "TOP_PASTE";
                        break;
                case 8: PART = "BotPasteImport";
                        SHAPE = "BOTTOM_PASTE";
                        break;
                case 9: PART = "TopAssyImport";
                        SHAPE = "ASSY_TOP_LINES";
                        break;
                case 10:PART = "BotAssyImport";
                        SHAPE = "ASSY_BOTTOM_LINES";
                        break;
                }
        SHAPE += TimeStr;
        FPC << endl;
        FPC << ("part: " + PART).c_str() << endl;
        FPC << "ref_text: 0 0 0 0 0 0" << endl;
        FPC << ("shape: \"" + SHAPE + "\"").c_str() << endl;
        FPC << "pos: ";
        FPC <<  AnsiString(BRD_RECT[0]).c_str();
        FPC <<  " ";
        FPC <<  AnsiString(BRD_RECT[1]).c_str();
        FPC <<  " 0 0 1" << endl;
        }
//
FPC << endl;
FPC << "[nets]" << endl;
FPC << endl;
//===================
//read NETS
A = ExtractFilePath (Application->ExeName)  ;
A = A + "Import_Tango\\Ntlst_and_Area.txt";
ifstream NETL (A.c_str());
int n_Area;
int n_Connect;
while (1)
        {
        NETL.getline(str,sizeof(str));
        A = str;
        if (A.SubString(1,A.Length()) == "end" ) break;
        if (A.SubString(1,4) == "area" )
                {
                n_Area++;
                FPC << "area: ";
                FPC << AnsiString(n_Area).c_str();
                FPC << " ";
                i = prob(A,2);
                FPC << A.SubString(i,(A.Length()-i+1)).c_str() << endl;
                }
        else if (A.SubString(1,7) == "connect" )
                {
                n_Connect++;
                FPC << "connect: ";
                FPC << AnsiString(n_Connect).c_str();
                FPC << " ";
                i = prob(A,2);
                FPC << A.SubString(i,(A.Length()-i+1)).c_str() << endl;
                }
        else if (A.SubString(1,3) == "net" )
                {
                n_Area = 0;
                n_Connect = 0;
                i = prob(A,1);
                AnsiString Net = ex_str (A, &i);
                int CNT_PIN;
                int CNT_AREA;
                int CNT_CON;
                ex_count_net_param (&CNT_PIN, &CNT_CON, &CNT_AREA, Net);
                FPC << str;
                FPC << " ";
                FPC << AnsiString(CNT_PIN).c_str();
                FPC << " ";
                FPC << AnsiString(CNT_CON).c_str();
                FPC << " ";
                FPC << AnsiString(CNT_AREA).c_str();
                FPC << " 0 0 0 1" << endl;
                }
        else    FPC << str << endl;
        }
NETL.close();
//===================
FPC << endl;
FPC << "[texts]" << endl;
i = 0;
while (i < Form1->ListBox3_TEXTS->Count)
        {
        FPC << (Form1->ListBox3_TEXTS->Items->operator [](i)).c_str();
        FPC << endl;
        i++;
        }
FPC << endl;
FPC << "[merges]";
//===================
FPC << endl;
FPC << "[end]" << endl;
FPC.close();
}
