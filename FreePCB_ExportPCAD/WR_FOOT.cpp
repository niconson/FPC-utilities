//---------------------------------------------------------------------------


#pragma hdrstop

#include "WR_FOOT.h"
#include "FPC_to_PCB.h"
#include "fstream.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)


void WR_FOOT (void)
{
                ofstream PATTERNS;
                PATTERNS.open((Path + "PATTERNS.TXT").c_str(), std::ios_base::app );
                PATTERNS << "  (patternDefExtended \"";
                PATTERNS << Name_Foot.c_str() ;
                PATTERNS << "_0\"" << endl;
                PATTERNS << "  (originalName \""  ;
                PATTERNS << Name_Foot.c_str() ;
                PATTERNS << "\")" << endl;
                PATTERNS << "    (patternGraphicsNameRef \"Primary\")" << endl << endl;
                PATTERNS << "    (patternGraphicsDef " << endl  ;
                PATTERNS << "      (patternGraphicsNameDef \"Primary\")" << endl;
                PATTERNS << "      (multiLayer " << endl;
                if (Form1->ListBox3_Pins->Items->Count)
                        {
                        i = 0;
                        AnsiString PINS = Form1->ListBox3_Pins->Items->operator [](i);
                        while (1)
                                {
                                PATTERNS << PINS.c_str() << endl;
                                i++;
                                if (i >= Form1->ListBox3_Pins->Items->Count) break;
                                PINS = Form1->ListBox3_Pins->Items->operator [](i);
                                }
                        }
                Form1->ListBox3_Pins->Clear();
                PATTERNS << "        (pickpoint (pt ";
                PATTERNS << centroid.c_str();
                PATTERNS << ") )" << endl;
                PATTERNS << "      )"  << endl;
                int cnt = 0;
                // top copper lines
                for( int lns=0; lns<Form1->ListBox1_Lines->Items->Count; lns++ )
                        {
                        AnsiString LINE = Form1->ListBox1_Lines->Items->operator [](lns);
                        if( LINE.SubString(LINE.Length(),1) == "1" )
                                {
                                if( cnt == 0 )
                                        PATTERNS << "      (layerContents  (layerNumRef  1)" << endl;
                                PATTERNS << LINE.SubString(1,LINE.Length()-1) .c_str() << endl;
                                cnt++;
                                }
                        }
                if( cnt )
                        PATTERNS << "      )"  << endl;
                cnt = 0;
                // bot copper lines
                for( int lns=0; lns<Form1->ListBox1_Lines->Items->Count; lns++ )
                        {
                        AnsiString LINE = Form1->ListBox1_Lines->Items->operator [](lns);
                        if( LINE.SubString(LINE.Length(),1) == "2" )
                                {
                                if( cnt == 0 )
                                        PATTERNS << "      (layerContents  (layerNumRef  2)" << endl;
                                PATTERNS << LINE.SubString(1,LINE.Length()-1) .c_str() << endl;
                                cnt++;
                                }
                        }
                if( cnt )
                        PATTERNS << "      )"  << endl;
                cnt = 0;
                // top silk lines
                PATTERNS << "      (layerContents  (layerNumRef  6)" << endl;
                for( int lns=0; lns<Form1->ListBox1_Lines->Items->Count; lns++ )
                        {
                        AnsiString LINE = Form1->ListBox1_Lines->Items->operator [](lns);
                        if( LINE.SubString(LINE.Length(),1) == "6" )
                                {
                                PATTERNS << LINE.SubString(1,LINE.Length()-1) .c_str() << endl;
                                cnt++;
                                }
                        }
                // TEXTS
                if (Form1->ListBox2_Texts->Items->Count)
                        {
                        i = 0;
                        AnsiString TXT = Form1->ListBox2_Texts->Items->operator [](i);
                        while (TXT.Length())
                                {
                                PATTERNS << TXT.c_str() << endl;
                                i++;
                                if (i >= Form1->ListBox2_Texts->Items->Count) break;
                                TXT = Form1->ListBox2_Texts->Items->operator [](i);
                                }
                        }
                PATTERNS << "        (attr \"Type\" \"\" (pt 0 0) (textStyleRef \"(Default)\") )" << endl;
                PATTERNS << "        (attr \"RefDes\" \"\" (pt 0 0) (rotation 90.0) (isVisible True) (textStyleRef \"(Default)\") )" << endl;
                PATTERNS << "        (attr \"Value\" \"\" (pt 0 0) (rotation 90.0) (isVisible True) (textStyleRef \"(Default)\") )" << endl;
                PATTERNS << "      )" << endl;
                cnt = 0;
                // bot silk lines
                for( int lns=0; lns<Form1->ListBox1_Lines->Items->Count; lns++ )
                        {
                        AnsiString LINE = Form1->ListBox1_Lines->Items->operator [](lns);
                        if( LINE.SubString(LINE.Length(),1) == "7" )
                                {
                                if( cnt == 0 )
                                        PATTERNS << "      (layerContents  (layerNumRef  7)" << endl;
                                PATTERNS << LINE.SubString(1,LINE.Length()-1) .c_str() << endl;
                                cnt++;
                                }
                        }
                if( cnt )
                        PATTERNS << "      )"  << endl;
                cnt = 0;
                // top notes
                for( int lns=0; lns<Form1->ListBox1_Lines->Items->Count; lns++ )
                        {
                        AnsiString LINE = Form1->ListBox1_Lines->Items->operator [](lns);
                        if( LINE.SubString(LINE.Length(),1) == "3" )
                                {
                                if( cnt == 0 )
                                        PATTERNS << "      (layerContents  (layerNumRef  10)" << endl;
                                PATTERNS << LINE.SubString(1,LINE.Length()-1) .c_str() << endl;
                                cnt++;
                                }
                        }
                if( cnt )
                        PATTERNS << "      )"  << endl;
                cnt = 0;
                // bot notes
                for( int lns=0; lns<Form1->ListBox1_Lines->Items->Count; lns++ )
                        {
                        AnsiString LINE = Form1->ListBox1_Lines->Items->operator [](lns);
                        if( LINE.SubString(LINE.Length(),1) == "4" )
                                {
                                if( cnt == 0 )
                                        PATTERNS << "      (layerContents  (layerNumRef  11)" << endl;
                                PATTERNS << LINE.SubString(1,LINE.Length()-1) .c_str() << endl;
                                cnt++;
                                }
                        }
                if( cnt )
                        PATTERNS << "      )"  << endl;
                Form1->ListBox1_Lines->Clear();
                Form1->ListBox2_Texts->Clear();
                PATTERNS << "    )" << endl;
                PATTERNS << "  )" << endl;
                PATTERNS.close();

ofstream WR_compDef  ;
WR_compDef.open((Path + "compDef.TXT").c_str(), std::ios_base::app );
WR_compDef << "  (compDef \"";
WR_compDef << Name_Foot.c_str();
WR_compDef << "_0\"" << endl;
WR_compDef << "    (originalName \"";
WR_compDef << Name_Foot.c_str();
WR_compDef << "\")" << endl;
WR_compDef << "    (compHeader " << endl;
WR_compDef << "      (sourceLibrary \"\")" << endl;
WR_compDef << "      (numPins ";
WR_compDef << AnsiString(n_pins).c_str();
WR_compDef << ")" << endl;
WR_compDef << "      (numParts 1)" << endl;
WR_compDef << "      (alts (ieeeAlt False) (deMorganAlt False))" << endl;
WR_compDef << "      (refDesPrefix \"\")" << endl;
WR_compDef << "    )" << endl;
i = 0;
while (i < n_pins)
      {
       WR_compDef << "    (compPin \"";
       AnsiString NAME_PINS = Form1->ListBox4_NamePins->Items->operator [](i);
       WR_compDef << NAME_PINS.c_str();
       WR_compDef << "\" (partNum 0) (symPinNum 0) (gateEq 0) (pinEq 0) )" << endl;
       i++;
      }
WR_compDef << "    (attachedPattern (patternNum 1) (patternName \"";
WR_compDef << Name_Foot.c_str();
WR_compDef << "\")" << endl;
WR_compDef << "      (numPads ";
WR_compDef << AnsiString(n_pins).c_str();
WR_compDef << ")" << endl;
WR_compDef << "      (padPinMap " << endl;
i = 0;
while (i < n_pins)
      {
       WR_compDef << "        (padNum  ";
       WR_compDef << AnsiString(i + 1).c_str();
       WR_compDef << ") (compPinRef \"" ;
       AnsiString NAME_PINS = Form1->ListBox4_NamePins->Items->operator [](i);
       WR_compDef << NAME_PINS.c_str();
       WR_compDef << "\")" << endl;
       i++;
      }
Form1->ListBox4_NamePins->Clear();
WR_compDef << "      )" << endl;
WR_compDef << "    )" << endl;
////WR_compDef << "    (attr \"Value\" \"Value\" (isVisible True) (textStyleRef \"(Default)\") )" << endl;
WR_compDef << "  )" << endl;
WR_compDef.close();
}