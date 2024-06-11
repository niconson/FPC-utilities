//---------------------------------------------------------------------------


#pragma hdrstop

#include "Areas.h"
#include "HEAD.h"
#include "fstream.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

void Areas (AnsiString OpenD, long CNT)
{
if ((BRD_RECT[0] == 2000000000)||(BRD_RECT[2] == 0))
        {
        BRD_RECT[0] = 100000000;
        BRD_RECT[1] = 100000000;
        BRD_RECT[2] = 200000000;
        BRD_RECT[3] = 200000000;
        }
else    {
        //BRD_RECT[0] -= 10000000;
        //BRD_RECT[1] -= 10000000;
        //BRD_RECT[2] += 10000000;
        //BRD_RECT[3] += 10000000;
        }
//ЧТЕНИЕ Areas
Form1->Label4->Caption = "Reading Areas" ;
Application->ProcessMessages();
AnsiString A;
ifstream read_Areas (OpenD.c_str());
long i = 0;
long layerNumRef = 0;              //layer Area
char str[MAX_CHARS];
AnsiString netNameRef;
int n_corner = 1;
bool Flag_pcbPoly = false;
bool Flag_island = false;
bool Flag_copperPour95 = false;

//Открытие Area.txt
AnsiString B = ExtractFilePath (Application->ExeName)  ;
ofstream Areas;
Areas.open((B + "Import_Tango\\Area.txt").c_str(), std::ios_base::app );
int SC = 0;
AnsiString Corner;
AnsiString CornerBack;
AnsiString StringBeginPoly = "(pcbPoly";
bool FlagLayerDef = false;
int layerPlane = 0;
while (CNT)
        {
        CNT--;
        read_Areas.getline(str,sizeof(str));
        A = str;
        A = A.Trim();
        if (!A.Length()) continue;
        if (Flag_copperPour95) Scob(A, &SC);   // scobki
//======================================================================
        if (A.LowerCase().SubString(1,9) == "(layerdef" )               FlagLayerDef = true;
        else if (A.LowerCase().SubString(1,11) == "(multilayer" )       FlagLayerDef = false;
        else if (A.LowerCase().SubString(1,9) == "(layernum" )
                {
                if (FlagLayerDef)
                        {
                        i = prob (A, 1);
                        layerPlane = ex_float_NM (A, &i, -1);
                        }
                }
        else if (A.LowerCase().SubString(1,10) == "(layertype" )
                {
                if (FlagLayerDef)
                if (A.LowerCase().SubString(1,16) != "(layertype plane" )FlagLayerDef = false;
                }
        else if (A.LowerCase().SubString(1,14) == "(layercontents" )
                {
                i = prob (A, 1);
                if (A.LowerCase().SubString(i,12) == "(layernumref" )
                        {
                        i = prob (A, 2);
                        layerNumRef = ex_float_NM (A, &i, -1);
                        int layer;
                        if (layerNumRef < 3)            layer = layerNumRef + 11;
                        else if (layerNumRef > 11)      layer = layerNumRef + 2;
                        else                            layer = layerNumRef;
                        if (MaxLayerNumRef < layer) MaxLayerNumRef = layer;
                        }
                }
        else if (A.LowerCase().SubString(1,11) == "(netnameref")
                {
                if ((Flag_copperPour95)||(FlagLayerDef))
                        {
                        i = prob (A, 1);
                        netNameRef = ex_str(A, &i);
                        if (FlagLayerDef)
                        if ((layerPlane > 11)||(layerPlane < 28))
                                {
                                //запись полигона
                                if (netNameRef.Length())
                                        {
                                        Areas << "net: \"";
                                        Areas << netNameRef.c_str();
                                        Areas << "\"";
                                        }
                                else    {
                                        Areas << "net: \"Unconnected_Area.\"";
                                        }
                                Areas << endl;
                                if (MaxLayerNumRef < (layerPlane+2)) MaxLayerNumRef = (layerPlane+2);
                                Areas << "area: 1 4 ";
                                Areas << AnsiString(layerPlane+2).c_str();
                                Areas << " 0";
                                Areas << endl;

                                Areas << "corner: 1 ";
                                Areas << AnsiString(BRD_RECT[0]).c_str();
                                Areas << " ";
                                Areas << AnsiString(BRD_RECT[1]).c_str();
                                Areas << " 0 0";
                                Areas << endl;

                                Areas << "corner: 2 ";
                                Areas << AnsiString(BRD_RECT[2]).c_str();
                                Areas << " ";
                                Areas << AnsiString(BRD_RECT[1]).c_str();
                                Areas << " 0 0";
                                Areas << endl;

                                Areas << "corner: 3 ";
                                Areas << AnsiString(BRD_RECT[2]).c_str();
                                Areas << " ";
                                Areas << AnsiString(BRD_RECT[3]).c_str();
                                Areas << " 0 0";
                                Areas << endl;

                                Areas << "corner: 4 ";
                                Areas << AnsiString(BRD_RECT[0]).c_str();
                                Areas << " ";
                                Areas << AnsiString(BRD_RECT[3]).c_str();
                                Areas << " 0 1";
                                Areas << endl;
                                netNameRef = "";
                                }
                        FlagLayerDef = false;
                        }
                }
        else if (A.LowerCase().SubString(1,13) == "(copperpour95" )
                {
                Scob(A, &SC);
                Flag_copperPour95 = true;
                n_corner = 1;
                CornerBack = "";
                Corner = "";
                StringBeginPoly = "(pcbPoly";
                }
        else if (A.LowerCase().SubString(1,9) == "(planeobj" )
                {
                Scob(A, &SC);
                Flag_copperPour95 = true;
                n_corner = 1;
                CornerBack = "";
                Corner = "";
                StringBeginPoly = "(pcbPoly";
                }
        //НАЧАЛО ПОЛИГОНА:
        else if (A.LowerCase().SubString(1,A.Length()) == "(island" )
                {
                Flag_island = true;
                Form1->ListBox1->Items->Clear();
                n_corner = 1;
                CornerBack = "";
                Corner = "";
                }
        else if (A.LowerCase().SubString(1,A.Length()) == "(pcbpoly" )
                {
                Flag_pcbPoly = true;
                Form1->ListBox1->Items->Clear();
                n_corner = 1;
                CornerBack = "";
                Corner = "";
                }
//======================================================================
        if (layerNumRef)
        if (Flag_pcbPoly)
        if (Flag_copperPour95)
                {
                if (A.SubString(1,4) == "(pt " )
                        {
                        if ( n_corner > 1)
                        if (CornerBack.SubString(CornerBack.Length(),1) != "1" )
                                {
                                CornerBack = Corner + " 0";
                                Form1->ListBox1->Items->Add(CornerBack);
                                }
                        else    {
                                Form1->ListBox1->Items->Add(CornerBack);
                                CornerBack = "";
                                }
                        long X;
                        long Y;
                        i = prob (A, 1);
                        X = ex_float_NM (A, &i, UNITS);
                        Y = ex_float_NM (A, &i, UNITS);
                        Corner = "corner: ";
                        Corner += AnsiString(n_corner);
                        Corner += " ";
                        Corner += AnsiString(X);
                        Corner += " ";
                        Corner += AnsiString(Y);
                        Corner += " 0";
                        n_corner++;
                        }
                else if (A.UpperCase().SubString(1,14) == "(CUTOUTOUTLINE")
                        {
                        if (n_corner > 1) CornerBack = Corner + " 1";
                        }
        //======================================================================
                if (((SC == 1) && (Flag_island)) || (SC <= 0))
                        {
                        if (Form1->ListBox1->Items->Count > 2)
                        if (((layerNumRef < 3)||(layerNumRef > 11))&&(layerNumRef < 28))
                                {
                                if (n_corner > 1) Form1->ListBox1->Items->Add(Corner + " 1");
                                //запись полигона
                                if (netNameRef.Length())
                                        {
                                        Areas << "net: \"";
                                        Areas << netNameRef.c_str();
                                        Areas << "\"";
                                        }
                                else    {
                                        Areas << "net: \"Unconnected_Area.\"";
                                        }
                                Areas << endl;
                                Areas << "area: 1 ";
                                Areas << AnsiString(Form1->ListBox1->Items->Count).c_str();
                                Areas << " ";
                                if (layerNumRef < 3)            Areas << AnsiString(layerNumRef+11).c_str();
                                else if (layerNumRef > 11)      Areas << AnsiString(layerNumRef+2).c_str();
                                //else ShowMessage ("    Ошибка! Полигон в неизвестном слое.");
                                Areas << " 0";
                                Areas << endl;
                                i = 0;
                                while (i < Form1->ListBox1->Items->Count)
                                        {
                                        Areas << Form1->ListBox1->Items->operator [](i).c_str() << endl;
                                        i++;
                                        }
                                }
                        Flag_island = false;
                        Form1->ListBox1->Items->Clear();
                        if (SC == 0)
                                {
                                netNameRef = "";
                                Flag_copperPour95 = false;
                                Flag_pcbPoly = false;
                                }
                        }//if (((SC == 1) && (Flag_island)) || (SC <= 0))
                }//if (layerNumRef) if (Flag_pcbPoly) if (Flag_copperPour95)
//======================================================================
        }//while (CNT)
read_Areas.close();
Areas << "end" << endl;
Areas.close();
}




