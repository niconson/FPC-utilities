//---------------------------------------------------------------------------


#pragma hdrstop

#include "WR_PADSTYLE.h"
#include "FPC_to_PCB.h"
#include "fstream.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
static unsigned clock_pin = 1;

void WR_PADSTYLE (void)
{
                bool FlagFlipped;
                FlagFlipped = false;
                if (!Htop)
                if (!Wtop)
                if (Hbot)
                if (Wbot)
                        {
                        FlagFlipped = true;
                        AnsiString Mem;
                        double M;
                        Mem = type_top;
                        type_top = type_bot;
                        type_bot = Mem;
                        Htop = Hbot;
                        Wtop = Wbot;
                        Hbot = 0;
                        Wbot = 0;
                        M = PadRadius;
                        PadRadius = BPadRadius;
                        BPadRadius = M;
                        }
                AnsiString CodePadStyle;
                CodePadStyle = F_str(Htop) + "x";
                CodePadStyle += F_str(Wtop);
                AnsiString NamePadStyle = CodePadStyle;
                CodePadStyle += type_top;
                CodePadStyle += F_str(PadRadius);
                CodePadStyle += type_bot;
                CodePadStyle += F_str(Hbot);
                CodePadStyle += F_str(Wbot);
                CodePadStyle += F_str(BPadRadius);
                CodePadStyle += type_inn;
                CodePadStyle += F_str(Hinn);
                CodePadStyle += F_str(Winn);
                CodePadStyle += F_str(hole_diam);
                int Find = Form1->SavePadStyle->Items->IndexOf(CodePadStyle);
                if (Find == -1)
                        {
                        i = 1;
                        Find = Form1->SavePadStyle->Items->IndexOf(NamePadStyle);
                        while (Find != -1)
                                {
                                i++;
                                Find = Form1->SavePadStyle->Items->IndexOf(NamePadStyle + "[" + AnsiString(i) + "]");
                                }
                        if (i > 1) NamePadStyle = NamePadStyle + "[" + AnsiString(i) + "]";
                        Form1->SavePadStyle->Items->Add(CodePadStyle);
                        Form1->SavePadStyle->Items->Add(NamePadStyle);
                        ofstream PADSTYLE;
                        PADSTYLE.open((Path + "PADSTYLE.TXT").c_str(), std::ios_base::app );
                        PADSTYLE << "  (padStyleDef \"";
                        PADSTYLE << NamePadStyle.c_str();
                        PADSTYLE << "\"" << endl;
                        PADSTYLE << "    (holeDiam ";
                        PADSTYLE << F_str(hole_diam).c_str();
                        PADSTYLE << ")" << endl;
                        if (type_top.SubString(1,6) == "MtHole") PADSTYLE << "    (isHolePlated False)" << endl;
                        else if (type_bot.SubString(1,6) == "MtHole") PADSTYLE << "    (isHolePlated False)" << endl;
                        PADSTYLE << "    (StartRange 1)" << endl;
                        PADSTYLE << "    (EndRange 2)" << endl;
                        PADSTYLE << "    (padShape (layerNumRef 1) (padShapeType ";
                        //BOOL bPoly = 0;
                        //if (type_top.UpperCase().SubString(1,7) != "RND____" )
                        //        {
                                PADSTYLE << type_top.c_str();
                                PADSTYLE << ") (shapeWidth ";
                                PADSTYLE << F_str(Htop).c_str();
                                PADSTYLE << ") (shapeHeight ";
                                PADSTYLE << F_str(Wtop).c_str();
                                PADSTYLE << ") )" << endl;
                        /*        }
                        else    {
                                bPoly = 1;
                                PADSTYLE << "Polygon) (shapeOutline ";
                                PADSTYLE << endl;
                                double H = Htop/2 - PadRadius;
                                double W = Wtop/2 - PadRadius;
                                double Sh = PadRadius*707/1000;
                                double R = PadRadius;
                                //1
                                PADSTYLE << "        (pt ";
                                PADSTYLE << F_str((-H)).c_str() ;
                                PADSTYLE << " ";
                                PADSTYLE << F_str((-W-R)).c_str() ;
                                PADSTYLE << ")";
                                PADSTYLE << endl;
                                //2
                                PADSTYLE << "        (pt ";
                                PADSTYLE << F_str((-H-Sh)).c_str() ;
                                PADSTYLE << " ";
                                PADSTYLE << F_str((-W-Sh)).c_str() ;
                                PADSTYLE << ")";
                                PADSTYLE << endl;
                                //3
                                PADSTYLE << "        (pt ";
                                PADSTYLE << F_str((-H-R)).c_str() ;
                                PADSTYLE << " ";
                                PADSTYLE << F_str((-W)).c_str() ;
                                PADSTYLE << ")";
                                PADSTYLE << endl;
                                //4
                                PADSTYLE << "        (pt ";
                                PADSTYLE << F_str((-H-R)).c_str() ;
                                PADSTYLE << " ";
                                PADSTYLE << F_str((W)).c_str() ;
                                PADSTYLE << ")";
                                PADSTYLE << endl;
                                //5
                                PADSTYLE << "        (pt ";
                                PADSTYLE << F_str((-H-Sh)).c_str() ;
                                PADSTYLE << " ";
                                PADSTYLE << F_str((W+Sh)).c_str() ;
                                PADSTYLE << ")";
                                PADSTYLE << endl;
                                //6
                                PADSTYLE << "        (pt ";
                                PADSTYLE << F_str((-H)).c_str() ;
                                PADSTYLE << " ";
                                PADSTYLE << F_str((W+R)).c_str() ;
                                PADSTYLE << ")";
                                PADSTYLE << endl;
                                //7
                                PADSTYLE << "        (pt ";
                                PADSTYLE << F_str((H)).c_str() ;
                                PADSTYLE << " ";
                                PADSTYLE << F_str((W+R)).c_str() ;
                                PADSTYLE << ")";
                                PADSTYLE << endl;
                                //8
                                PADSTYLE << "        (pt ";
                                PADSTYLE << F_str((H+Sh)).c_str() ;
                                PADSTYLE << " ";
                                PADSTYLE << F_str((W+Sh)).c_str() ;
                                PADSTYLE << ")";
                                PADSTYLE << endl;
                                //9
                                PADSTYLE << "        (pt ";
                                PADSTYLE << F_str((H+R)).c_str() ;
                                PADSTYLE << " ";
                                PADSTYLE << F_str((W)).c_str() ;
                                PADSTYLE << ")";
                                PADSTYLE << endl;
                                //10
                                PADSTYLE << "        (pt ";
                                PADSTYLE << F_str((H+R)).c_str() ;
                                PADSTYLE << " ";
                                PADSTYLE << F_str((-W)).c_str() ;
                                PADSTYLE << ")";
                                PADSTYLE << endl;
                                //11
                                PADSTYLE << "        (pt ";
                                PADSTYLE << F_str((H+Sh)).c_str() ;
                                PADSTYLE << " ";
                                PADSTYLE << F_str((-W-Sh)).c_str() ;
                                PADSTYLE << ")";
                                PADSTYLE << endl;
                                //12
                                PADSTYLE << "        (pt ";
                                PADSTYLE << F_str((H)).c_str() ;
                                PADSTYLE << " ";
                                PADSTYLE << F_str((-W-R)).c_str() ;
                                PADSTYLE << ")";
                                PADSTYLE << endl;
                                //
                                PADSTYLE << "      )" << endl;
                                PADSTYLE << "    )" << endl;
                                } */
                        PADSTYLE << "    (padShape (layerNumRef 2) (padShapeType "  ;
                        //if (type_bot.UpperCase().SubString(1,7) != "RND____" )
                        //        {
                                PADSTYLE << type_bot.c_str();
                                PADSTYLE << ") (shapeWidth ";
                                PADSTYLE << F_str(Hbot).c_str();
                                PADSTYLE << ") (shapeHeight ";
                                PADSTYLE << F_str(Wbot).c_str();
                                PADSTYLE << ") )" << endl;
                        /*        }
                        else    {
                                bPoly = 1;
                                PADSTYLE << "Polygon) (shapeOutline ";
                                PADSTYLE << endl;
                                double H = Hbot/2 - BPadRadius;
                                double W = Wbot/2 - BPadRadius;
                                double Sh = BPadRadius*707/1000;
                                double R = BPadRadius;
                                //1
                                PADSTYLE << "        (pt ";
                                PADSTYLE << F_str((-H)).c_str() ;
                                PADSTYLE << " ";
                                PADSTYLE << F_str((-W-R)).c_str() ;
                                PADSTYLE << ")";
                                PADSTYLE << endl;
                                //2
                                PADSTYLE << "        (pt ";
                                PADSTYLE << F_str((-H-Sh)).c_str() ;
                                PADSTYLE << " ";
                                PADSTYLE << F_str((-W-Sh)).c_str() ;
                                PADSTYLE << ")";
                                PADSTYLE << endl;
                                //3
                                PADSTYLE << "        (pt ";
                                PADSTYLE << F_str((-H-R)).c_str() ;
                                PADSTYLE << " ";
                                PADSTYLE << F_str((-W)).c_str() ;
                                PADSTYLE << ")";
                                PADSTYLE << endl;
                                //4
                                PADSTYLE << "        (pt ";
                                PADSTYLE << F_str((-H-R)).c_str() ;
                                PADSTYLE << " ";
                                PADSTYLE << F_str((W)).c_str() ;
                                PADSTYLE << ")";
                                PADSTYLE << endl;
                                //5
                                PADSTYLE << "        (pt ";
                                PADSTYLE << F_str((-H-Sh)).c_str() ;
                                PADSTYLE << " ";
                                PADSTYLE << F_str((W+Sh)).c_str() ;
                                PADSTYLE << ")";
                                PADSTYLE << endl;
                                //6
                                PADSTYLE << "        (pt ";
                                PADSTYLE << F_str((-H)).c_str() ;
                                PADSTYLE << " ";
                                PADSTYLE << F_str((W+R)).c_str() ;
                                PADSTYLE << ")";
                                PADSTYLE << endl;
                                //7
                                PADSTYLE << "        (pt ";
                                PADSTYLE << F_str((H)).c_str() ;
                                PADSTYLE << " ";
                                PADSTYLE << F_str((W+R)).c_str() ;
                                PADSTYLE << ")";
                                PADSTYLE << endl;
                                //8
                                PADSTYLE << "        (pt ";
                                PADSTYLE << F_str((H+Sh)).c_str() ;
                                PADSTYLE << " ";
                                PADSTYLE << F_str((W+Sh)).c_str() ;
                                PADSTYLE << ")";
                                PADSTYLE << endl;
                                //9
                                PADSTYLE << "        (pt ";
                                PADSTYLE << F_str((H+R)).c_str() ;
                                PADSTYLE << " ";
                                PADSTYLE << F_str((W)).c_str() ;
                                PADSTYLE << ")";
                                PADSTYLE << endl;
                                //10
                                PADSTYLE << "        (pt ";
                                PADSTYLE << F_str((H+R)).c_str() ;
                                PADSTYLE << " ";
                                PADSTYLE << F_str((-W)).c_str() ;
                                PADSTYLE << ")";
                                PADSTYLE << endl;
                                //11
                                PADSTYLE << "        (pt ";
                                PADSTYLE << F_str((H+Sh)).c_str() ;
                                PADSTYLE << " ";
                                PADSTYLE << F_str((-W-Sh)).c_str() ;
                                PADSTYLE << ")";
                                PADSTYLE << endl;
                                //12
                                PADSTYLE << "        (pt ";
                                PADSTYLE << F_str((H)).c_str() ;
                                PADSTYLE << " ";
                                PADSTYLE << F_str((-W-R)).c_str() ;
                                PADSTYLE << ")";
                                PADSTYLE << endl;
                                //
                                PADSTYLE << "      )" << endl;
                                PADSTYLE << "    )" << endl;
                                }    */
                        if( hole_diam > 0.01 )
                                {
                                PADSTYLE << "    (padShape (layerType Signal) (padShapeType "  ;
                                PADSTYLE << "Ellipse";
                                PADSTYLE << ") (shapeWidth ";
                                PADSTYLE << F_str(Hinn).c_str();
                                PADSTYLE << ") (shapeHeight ";
                                PADSTYLE << F_str(Winn).c_str();
                                PADSTYLE << ") )" << endl;
                                PADSTYLE << "    (padShape (layerType Plane) (padShapeType " ;
                                PADSTYLE << "Direct";
                                //PADSTYLE << ") (shapeWidth ";
                                //PADSTYLE << F_str(Hinn).c_str();
                                //PADSTYLE << ") (shapeHeight ";
                                //PADSTYLE << F_str(Winn).c_str();
                                //PADSTYLE << ") )" << endl;
                                PADSTYLE << ") (shapeWidth 0.0) (shapeHeight 0.0) )" << endl;
                                //
                                PADSTYLE << "    (padShape (layerType NonSignal) (padShapeType Ellipse)";
                                PADSTYLE << " (shapeWidth 0.0) (shapeHeight 0.0) )" << endl;
                                PADSTYLE << "  )" << endl;
                                }
                        else    {
                                PADSTYLE << " (padShape (layerType Signal) (padShapeType Rect) (shapeWidth 0.0) (shapeHeight 0.0) )" << endl;
                                PADSTYLE << " (padShape (layerType Plane) (padShapeType Direct) (outsideDiam 0.0) (insideDiam 0.0) )" << endl;
                                PADSTYLE << " (padShape (layerType NonSignal) (padShapeType Ellipse) (shapeWidth 0.0) (shapeHeight 0.0) )" << endl;
                                PADSTYLE << "  )" << endl;
                                }
                        PADSTYLE.close();
                        }
                else    NamePadStyle = Form1->SavePadStyle->Items->operator [](Find+1);
AnsiString PINS = "        (pad (padNum ";
PINS = PINS + (Form1->ListBox3_Pins->Items->Count+1);
PINS = PINS + ") (padStyleRef \"";
PINS = PINS + NamePadStyle;
PINS = PINS + "\") (pt ";
PINS = PINS + F_str(X);
PINS = PINS + " ";
PINS = PINS + F_str(Y);
PINS = PINS + ") (rotation ";
int iAn = (int)Angle;
if(iAn%90)
        iAn = 180 - iAn;
if( iAn < 0 )
        iAn += 360;
if( iAn >= 360 )
        iAn -= 360;
PINS = PINS + AnsiString(iAn);
if (FlagFlipped)        PINS = PINS + ") (isFlipped True ";
PINS = PINS + ") (defaultPinDes \"";
if( Form1->ListBox4_NamePins->Items->IndexOf(num_pin) >= 0 )
        {
        if (Form1->ListBox3_Pins->Items->Count == 0)
                Form1->ListBox4_NamePins->Clear();
        int np = 1;
        int iof = -1;
        do      {
                np++;
                iof = Form1->ListBox4_NamePins->Items->IndexOf(np);                  //AnsiString(num_pin)+"_"+
                }while(iof >= 0);
        Form1->ListBox4_NamePins->Items->Add(AnsiString(np));
        PINS = PINS + AnsiString(np);
        PINS = PINS + "\") )";
        Form1->ListBox3_Pins->Items->Add(PINS);
        }
else    {
        PINS = PINS + num_pin;
        PINS = PINS + "\") )";
        if (Form1->ListBox3_Pins->Items->Count == 0)
                Form1->ListBox4_NamePins->Clear();
        Form1->ListBox3_Pins->Items->Add(PINS);
        Form1->ListBox4_NamePins->Items->Add(num_pin);
        }
clock_pin++;
}