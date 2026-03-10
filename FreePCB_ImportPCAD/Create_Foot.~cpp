//---------------------------------------------------------------------------


#pragma hdrstop

#include "Create_Foot.h"
#include "HEAD.h"
#include "LSTBXS.h"
#include "fstream.h"
#include "math.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

static long hole_diam;
static long type_top;
static long type_bot;
static long type_inn;
static long w_top;
static long h_top;
static long w_bot;
static long h_bot;
static long w_inn;
static long h_inn;
static long TrmlTop;
static long TrmlInner;
static long rnd_radius;
static long thermal;
static long pinX;
static long pinY;
static long posX;
static long posY;
static long rotationPAD;        //pad
static long rotateFoot;         //foot
static long Angle;              //part
static long sel_rect1;
static long sel_rect2;
static long sel_rect3;
static long sel_rect4;
static bool FlagVia;
static bool Side;
static AnsiString Reference;
static int n_pins;


//---------------------------
//void stringPADSrecord (void)
//---------------------------
void stringPADSrecord (AnsiString PinDes)
        {
        n_pins++;
        if (((rotateFoot)||(Form1->ListBox1->Items->Count > 2))||
           ((rotationPAD != 90)&&(rotationPAD != 180)&&(rotationPAD != 270)&&(rotationPAD != 0)))
                {
                double SwellSM = StrToFloat(Form1->ComboBox2->Items->operator [](Form1->ComboBox2->ItemIndex));
                SwellSM = SwellSM*1000000;
                thermal = 3;
                AnsiString PinName = Reference + "." + PinDes;
                AnsiString A = "";
                int Operator = -1;
                while (A.SubString(1,A.Length()) != PinName.SubString(1,PinName.Length()))
                        {
                        Operator++;
                        if (Operator >= Form2->StringGrid1->RowCount){Operator--; break;}
                        A = Form2->StringGrid1->Cells[0][Operator];       //PINS
                        }
                AnsiString Net = Form2->StringGrid1->Cells[2][Operator];  //NETS
                if (Net.SubString(1,Net.Length()) == "Unconnected")
                        {
                        Net = Net + "__" + PinName;
                        AnsiString B = ExtractFilePath (Application->ExeName)  ;
                        ofstream UnConn;
                        UnConn.open((B + "Import_Tango\\CombNetList.txt").c_str(), std::ios_base::app );
                        UnConn << ("net: \"" + Net + "\"").c_str();
                        UnConn << endl;
                        UnConn << ("pin: 1 " + PinName).c_str();
                        UnConn << endl;
                        UnConn.close();
                        }

                // TOP
                rnd_radius = w_top/4;
                if (rnd_radius > (h_top/4)) rnd_radius = h_top/4;
                double PARAM_TOP[12];
                PARAM_TOP[0] = type_top;                //Type_top;
                PARAM_TOP[1] = w_top;                   //W_top;
                PARAM_TOP[2] = h_top;                   //L_top;
                PARAM_TOP[3] = rnd_radius;              //R_top;
                PARAM_TOP[4] = Angle;                   //A_Prt;
                PARAM_TOP[5] = rotationPAD;             //A_P;
                PARAM_TOP[6] = rotateFoot;              //Angle;
                PARAM_TOP[7] = pinX;                    //X_P;
                PARAM_TOP[8] = pinY;                    //Y_P;
                PARAM_TOP[9] = posX;                    //X_pos;
                PARAM_TOP[10] = posY;                   //Y_pos;
                if (Side) PARAM_TOP[11] = 3;            //top pad bottom side
                else      PARAM_TOP[11] = 0;            //top pad top side
                Generate_Poly ( &PARAM_TOP[0] , Net);

                //Generate SM cutout
                if (w_top) PARAM_TOP[1] = w_top + SwellSM*2;
                if (h_top) PARAM_TOP[2] = h_top + SwellSM*2;
                PARAM_TOP[3] = rnd_radius + SwellSM;
                if (PARAM_TOP[3] < 0) PARAM_TOP[3] = 0;
                Generate_Poly ( &PARAM_TOP[0] , "__Solder");

                //Generate Paste
                if (w_top) PARAM_TOP[1] = w_top - SwellSM*2;
                if (h_top) PARAM_TOP[2] = h_top - SwellSM*2;
                PARAM_TOP[3] = rnd_radius - SwellSM;
                if (PARAM_TOP[3] < 0) PARAM_TOP[3] = 0;
                Generate_Poly ( &PARAM_TOP[0] , "__Paste");

                // BOTTOM
                rnd_radius = w_bot/4;
                if (rnd_radius > (h_bot/4)) rnd_radius = h_bot/4;
                double PARAM_BOT[12];
                PARAM_BOT[0] = type_bot;                //Type_bot;
                PARAM_BOT[1] = w_bot;                   //W_bot;
                PARAM_BOT[2] = h_bot;                   //L_bot;
                PARAM_BOT[3] = rnd_radius;              //R_bot;
                PARAM_BOT[4] = Angle;                   //A_Prt;
                PARAM_BOT[5] = rotationPAD;             //A_P;
                PARAM_BOT[6] = rotateFoot;              //Angle;
                PARAM_BOT[7] = pinX;                    //X_P;
                PARAM_BOT[8] = pinY;                    //Y_P;
                PARAM_BOT[9] = posX;                    //X_pos;
                PARAM_BOT[10] = posY;                   //Y_pos;
                if (Side) PARAM_BOT[11] = 2;            //bottom pad bottom side  (canvas top)
                else      PARAM_BOT[11] = 1;            //bottom pad top side     (canvas bot)
                Generate_Poly ( &PARAM_BOT[0], Net );

                //Generate SM cutout
                if (w_bot) PARAM_BOT[1] = w_bot + SwellSM*2;
                if (h_bot) PARAM_BOT[2] = h_bot + SwellSM*2;
                PARAM_BOT[3] = rnd_radius + SwellSM;
                if (PARAM_BOT[3] < 0) PARAM_BOT[3] = 0;
                Generate_Poly ( &PARAM_BOT[0] , "__Solder");

                //Generate Paste
                if (w_bot) PARAM_BOT[1] = w_bot - SwellSM*2;
                if (h_bot) PARAM_BOT[2] = h_bot - SwellSM*2;
                PARAM_BOT[3] = rnd_radius - SwellSM;
                if (PARAM_BOT[3] < 0) PARAM_BOT[3] = 0;
                Generate_Poly ( &PARAM_BOT[0] , "__Paste");
                //
                if (type_top) type_top = 1;
                if (type_inn) type_inn = 1;
                if (type_bot) type_bot = 1;
                if (w_top > h_top) w_top = h_top;
                if (w_bot > h_bot) w_bot = h_bot;
                if (w_inn > h_inn) w_inn = h_inn;
                double X = (double)pinX;
                double Y = (double)pinY;
                Rotate_Vertex (&X, &Y, rotateFoot );
                pinX = (long )X;
                pinY = (long )Y;
                Form1->ListBox1->Items->Clear();
                if      ((rotationPAD != 90) &&
                        (rotationPAD != 180) &&
                        (rotationPAD != 0) &&
                        (rotationPAD != 270) ) rotationPAD = 0;
                }
        //
        AnsiString PAD = "  pin: \"";
        PAD += PinDes;
        PAD += "\" ";
        PAD += hole_diam;
        PAD += " ";
        if (sel_rect1 > pinX) sel_rect1 = pinX;
        if (sel_rect3 < pinX) sel_rect3 = pinX;
        PAD += pinX;
        PAD += " ";
        if (sel_rect2 > pinY) sel_rect2 = pinY;
        if (sel_rect4 < pinY) sel_rect4 = pinY;
        PAD += pinY;
        PAD += " ";
        PAD += rotationPAD;
        Form1->ListBox2->Items->Add(PAD);
        if ((type_top)&&(w_top)&&(h_top))
                {
                rnd_radius = w_top/4;
                if (rnd_radius > (h_top/4)) rnd_radius = h_top/4;
                PAD = "    top_pad: ";
                PAD += type_top;
                PAD += " ";
                PAD += w_top;
                PAD += " ";
                PAD += h_top/2;
                PAD += " ";
                PAD += h_top/2;
                PAD += " ";
                PAD += rnd_radius;
                PAD += " ";
                PAD += thermal;
                Form1->ListBox2->Items->Add(PAD);
                }
        if ((type_inn)&&(w_inn)&&(h_inn))
                {
                rnd_radius = w_inn/4;
                if (rnd_radius > (h_inn/4)) rnd_radius = h_inn/4;
                PAD = "    inner_pad: ";
                PAD += type_inn;
                PAD += " ";
                PAD += w_inn;
                PAD += " ";
                PAD += h_inn/2;
                PAD += " ";
                PAD += h_inn/2;
                PAD += " ";
                PAD += rnd_radius;
                PAD += " ";
                PAD += thermal;
                Form1->ListBox2->Items->Add(PAD);
                }
        if ((type_bot)&&(w_bot)&&(h_bot))
                {
                rnd_radius = w_bot/4;
                if (rnd_radius > (h_bot/4)) rnd_radius = h_bot/4;
                PAD = "    bottom_pad: ";
                PAD += type_bot;
                PAD += " ";
                PAD += w_bot;
                PAD += " ";
                PAD += h_bot/2;
                PAD += " ";
                PAD += h_bot/2;
                PAD += " ";
                PAD += rnd_radius;
                PAD += " ";
                PAD += thermal;
                Form1->ListBox2->Items->Add(PAD);
                }
        }




//-------------------------------
//void W_FootPrint (AnsiString name)
//-------------------------------
void W_FootPrint (AnsiString name)
        {
        if (sel_rect1 == SELR)
                {
                sel_rect1 = 0;
                sel_rect2 = 0;
                sel_rect3 = 2540000;
                sel_rect4 = 2540000;
                }
        sel_rect1 = sel_rect1 - 254000;
        sel_rect2 = sel_rect2 - 254000;
        sel_rect3 = sel_rect3 + 254000;
        sel_rect4 = sel_rect4 + 254000;
        AnsiString B = ExtractFilePath (Application->ExeName)  ;
        ofstream FootPrints;
        FootPrints.open((B + "Import_Tango\\FootPrints.txt").c_str(), std::ios_base::app );
        FootPrints << "name: \"";
        FootPrints << name.c_str();
        FootPrints << "\"" << endl;
        FootPrints << "package: \"";
        AnsiString Pckg = name;
        int nl = name.Length();
        if( nl > 2 )
                if( name.SubString(nl-1,1) == "_" )
                        Pckg = name.SubString(1,nl-2);
        FootPrints << Pckg.c_str();
        FootPrints << "\"" << endl;
        FootPrints << "units: NM" << endl;
        FootPrints << "sel_rect: " ;
        FootPrints << sel_rect1 ;
        FootPrints << " " ;
        FootPrints << sel_rect2 ;
        FootPrints << " " ;
        FootPrints << sel_rect3 ;
        FootPrints << " " ;
        FootPrints << sel_rect4 << endl;
        FootPrints << "ref_text: 300000 0 500000 0 50000" << endl;
        FootPrints << "value_text: 300000 0 0 0 50000" << endl;
        FootPrints << "centroid: 0 0 0 0" << endl;
        int i = 0;
        while (i < Form1->ListBox4_Lines->Count)
                {
                FootPrints << (Form1->ListBox4_Lines->Items->operator [](i)).c_str() << endl;
                i++;
                }
        Form1->ListBox4_Lines->Clear();
        FootPrints << "n_pins: ";
        FootPrints << n_pins << endl;
        i = 0;
        while (i < Form1->ListBox2->Count)
                {
                FootPrints << (Form1->ListBox2->Items->operator [](i)).c_str() << endl;
                i++;
                }
        Form1->ListBox2->Clear();
        FootPrints << endl;
        FootPrints.close();
        }
//--------------------------------------------------------
//void Ex_PadStyle (AnsiString padStyleRef)
//--------------------------------------------------------
bool Ex_PadStyle (AnsiString padStyleRef, bool Flagvia)
        {
        bool RETURNFLAGIFPOLY = false;
        Form1->ListBox1->Items->Clear();
        hole_diam = 1000000;
        type_top = 0;
        type_bot = 0;
        type_inn = 0;
        w_top = 1000000;
        h_top = 1000000;
        w_bot = 1000000;
        h_bot = 1000000;
        w_inn = 1000000;
        h_inn = 1000000;
        rnd_radius = 0;
        thermal = 0;
        AnsiString A;
        AnsiString PadStyle;
        if (Flagvia)    A = "(viaStyleDef \"" + padStyleRef + "\"";
        else            A = "(padStyleDef \"" + padStyleRef + "\"";
        int Lindex;
        Lindex = Form1->Library->Items->IndexOf(A);
        long i = 0;
        long layerNumRef = 0;
        if (Lindex > 0)
        while (1)
                {
                Lindex++;
                A = Form1->Library->Items->operator [](Lindex);
                if (StrBegin (A, "(netlist"))           break;
                if (StrBegin (A, "(pcbdesign"))         break;
                if (StrBegin (A, "(viastyledef"))       break;
                if (StrBegin (A, "(padstyledef"))       break;
                if (StrBegin (A, "(holediam") )
                        {
                        i = prob (A,1);
                        hole_diam = ex_float_NM (A, &i, UNITS);
                        }
                else if ((StrBegin (A, "(padshape") )||(StrBegin (A, "(viashape") ))
                        {
                        layerNumRef = 0;
                        i = go (A, 1, "layerNumRef" );
                        if (i)
                                {
                                i = go (A, i, " " );
                                layerNumRef = ex_float_NM (A, &i, -1);
                                }
                        i = go (A, 1, "layerType" );
                        if (i)
                                {
                                i = go (A, i, " " );
                                while (A.SubString(i,1) == " " ) i++;
                                if (A.LowerCase().SubString(i,6) == "signal") layerNumRef = 3;
                                if (A.LowerCase().SubString(i,5) == "plane")  layerNumRef = 4;
                                }
                        i = go (A, 1, "shapeWidth" );
                        if (i)
                                {
                                i = go (A, i, " " );
                                if (layerNumRef == 1)   h_top = ex_float_NM (A, &i, UNITS);
                                if (layerNumRef == 2)   h_bot = ex_float_NM (A, &i, UNITS);
                                if (layerNumRef == 3)   h_inn = ex_float_NM (A, &i, UNITS);
                                }
                        i = go (A, 1, "shapeHeight" );
                        if (i)
                                {
                                i = go (A, i, " " );
                                if (layerNumRef == 1)   w_top = ex_float_NM (A, &i, UNITS);
                                if (layerNumRef == 2)   w_bot = ex_float_NM (A, &i, UNITS);
                                if (layerNumRef == 3)   w_inn = ex_float_NM (A, &i, UNITS);
                                }
                        i = go (A, 1, "padShapeType" );
                        if (!i) i = go (A, 1, "viaShapeType" );
                        if (i)
                                {
                                i = go (A, i, " ");
                                while (A.SubString(i,1) == " " ) i++;
                                if      (A.LowerCase().SubString(i,7) == "ellipse" )
                                        {
                                        if (layerNumRef == 1)
                                                {
                                                if (w_top != h_top)     type_top = 5;
                                                else                    type_top = 1;
                                                }
                                        if (layerNumRef == 2)
                                                {
                                                if (w_bot != h_bot)     type_bot = 5;
                                                else                    type_bot = 1;
                                                }
                                        if (layerNumRef == 3)
                                                {
                                                if (w_inn != h_inn)     type_inn = 5;
                                                else                    type_inn = 1;
                                                }
                                        }
                                else if (A.LowerCase().SubString(i,4) == "oval" )
                                        {
                                        if (layerNumRef == 1)
                                                {
                                                if (w_top != h_top)     type_top = 5;
                                                else                    type_top = 1;
                                                }
                                        if (layerNumRef == 2)
                                                {
                                                if (w_bot != h_bot)     type_bot = 5;
                                                else                    type_bot = 1;
                                                }
                                        if (layerNumRef == 3)
                                                {
                                                if (w_inn != h_inn)     type_inn = 5;
                                                else                    type_inn = 1;
                                                }
                                        }
                                else if (A.LowerCase().SubString(i,4) == "rect" )
                                        {
                                        if (layerNumRef == 1)   type_top = 3;
                                        if (layerNumRef == 2)   type_bot = 3;
                                        if (layerNumRef == 3)   type_inn = 3;
                                        }
                                else if (A.LowerCase().SubString(i,7) == "rndrect" )
                                        {
                                        if (layerNumRef == 1)   type_top = 4;
                                        if (layerNumRef == 2)   type_bot = 4;
                                        if (layerNumRef == 3)   type_inn = 4;
                                        }
                                else if (A.LowerCase().SubString(i,6) == "direct" )
                                        {
                                        if (hole_diam)
                                                {
                                                if (layerNumRef == 1)   type_top = 0;
                                                if (layerNumRef == 2)   type_bot = 0;
                                                if (layerNumRef == 3)   type_inn = 0;
                                                }
                                        else    {
                                                if (layerNumRef == 1)   type_top = 1;
                                                if (layerNumRef == 2)   type_bot = 1;
                                                if (layerNumRef == 3)   type_inn = 1;
                                                }
                                        }
                                else if (A.LowerCase().SubString(i,9) == "noconnect" )
                                        {
                                        if (layerNumRef == 1)   type_top = 1;
                                        if (layerNumRef == 2)   type_bot = 1;
                                        if (layerNumRef == 3)   type_inn = 1;
                                        }
                                else if (A.LowerCase().SubString(i,6) == "mthole" )
                                        {
                                        if (layerNumRef == 1)
                                                {
                                                type_top = 0;
                                                //if (hole_diam < h_top) hole_diam = h_top;
                                                }
                                        if (layerNumRef == 2)
                                                {
                                                type_bot = 0;
                                                //if (hole_diam < h_bot) hole_diam = h_bot;
                                                }
                                        if (layerNumRef == 3)
                                                {
                                                type_inn = 0;
                                                //if (hole_diam < h_inn) hole_diam = h_inn;
                                                }
                                        }
                                else if (A.LowerCase().SubString(i,7) == "polygon" )
                                        {
                                        RETURNFLAGIFPOLY = true;
                                        if (layerNumRef == 1)
                                                {
                                                type_top = 7;
                                                w_top = 254000;
                                                }
                                        if (layerNumRef == 2)
                                                {
                                                type_bot = 7;
                                                w_bot = 254000;
                                                }
                                        if (layerNumRef == 3)   type_inn = 0;
                                        else    {
                                                AnsiString T;
                                                AnsiString B;
                                                if (Side)
                                                        {
                                                        B = "TopCorner";
                                                        T = "BottomCorner";
                                                        }
                                                else    {
                                                        T = "TopCorner";
                                                        B = "BottomCorner";
                                                        }
                                                Lindex++;
                                                A = Form1->Library->Items->operator [](Lindex);
                                                i = 0;
                                                while (A.LowerCase().SubString(1,3) == "(pt")
                                                        {
                                                        AnsiString S;
                                                        if (layerNumRef == 1)   S = T + A;
                                                        else                    S = B + A;
                                                        Form1->ListBox1->Items->Add(S);
                                                        Lindex++;
                                                        i++;
                                                        A = Form1->Library->Items->operator [](Lindex);
                                                        }
                                                T = "Count" + T;
                                                B = "Count" + B;
                                                if (layerNumRef == 1)   Form1->ListBox1->Items->Add(T);
                                                if (layerNumRef == 2)   Form1->ListBox1->Items->Add(B);
                                                Form1->ListBox1->Items->Add(AnsiString(i));
                                                }//if (layerNumRef != 3)
                                        }// polygon
                                }//!i
                        }//else if ((StrBegin (A, "(padshape") ) || (StrBegin (A, "(viashape" )))
                }//while (1)
        else    ShowMessage(A + "not found!");
        return RETURNFLAGIFPOLY;
        }


//-----------------------------------------------------------------
//AnsiString Ex_PinDes (AnsiString OpenD, AnsiString originalName, int NumPin )
//-----------------------------------------------------------------
AnsiString Ex_PinDes (AnsiString OpenD, AnsiString originalName, int NumPin )
        {
        Form1->Label4->Caption = AnsiString("Ex_PinDes: ") + NumPin + " \"" + originalName + "\" ";
        Application->ProcessMessages();
        long i = 0;
        char str[MAX_CHARS];
        AnsiString A;
        AnsiString patternName = "empty";
        ifstream read_PinDes (OpenD.c_str());
        while (A.SubString(1,9) != "(compdef ")
                {
                read_PinDes.getline(str,sizeof(str));
                A = str;
                A = A.Trim();
                A = A.LowerCase();
                }
        while (1)
                {
                read_PinDes.getline(str,sizeof(str));
                A = str;
                A = A.Trim();
                if (StrBegin (A, "(attachedPattern " ))
                        {
                        i = 1;
                        i = go( A, i, "patternName");
                        i = go( A, i, " ");
                        patternName = ex_str (A, &i);
                        patternName = patternName.UpperCase();
                        }
                else if (StrBegin (A, "(padNum ") )
                        {
                        if (patternName.SubString(1,patternName.Length()) == originalName.UpperCase().SubString(1,originalName.Length()))
                                {
                                i = prob (A, 1);
                                long pin = ex_float_NM (A, &i, -1);
                                if (pin == NumPin)
                                        {
                                        i = go (A, 1, "(compPinRef ");
                                        if (i)
                                                {
                                                i = go (A, i, " ");
                                                AnsiString PinDes = ex_str (A, &i);
                                                read_PinDes.close() ;
                                                return PinDes;
                                                }
                                        }
                                }
                        }
                //else if (StrBegin (A, "(netlist" ))      {read_PinDes.close() ;    return "error"; }
                else if (StrBegin (A, "(pcbDesign" ))    {read_PinDes.close() ;    return "error"; }
                }
        }

//-----------------------------------------------------------------
//void Ex_Shape (AnsiString OpenD, AnsiString shape, long  rotateFoot)
//-----------------------------------------------------------------
bool Ex_Shape (AnsiString shape, long rotateFoot)
        {
        Form1->ListBox2->Clear();
        Form1->ListBox4_Lines->Clear();
        bool RETURNFLAGIFPOLY = false;
        Form1->Label4->Caption = "Ex_Shape " + shape;
        Application->ProcessMessages();
        AnsiString A;
        AnsiString Pattern;
        AnsiString originalName = "noName";
        long i = 0;
        char s[255];
        sel_rect1 = SELR;
        sel_rect2 = SELR;
        sel_rect3 = -SELR;
        sel_rect4 = -SELR;
        n_pins = 0;
        A = "(patternDefExtended \"" + shape + "\"";
        int Lindex;
        Lindex = Form1->Library->Items->IndexOf(A);
        while (1)
                {
                Lindex++;
                A = Form1->Library->Items->operator [](Lindex);
                if (StrBegin (A, "(patternDefExtended"))break;
                if (StrBegin (A, "(netlist"))           break;
                if (StrBegin (A, "(pcbdesign"))         break;
                if (StrBegin (A, "(originalName "))
                        {
                        i = prob (A,1);
                        originalName = ex_str (A, &i);
                        }
                //-------------------------- ЛИНИИ ----------------------------------------------------
                if (StrBegin (A, "(arc "))
                        {
                        AnsiString LINE;
                        long X_center= 0;
                        long Y_center = 0;
                        long R = 0;
                        long A1 = 0;
                        long A2 = 0;
                        long W = 0;
                        long X1;
                        long Y1;
                        long X2;
                        long Y2;
                        AnsiString N = "noConnect";
                        i = go(A,1,"(pt ");
                        if (i) X_center = ex_float_NM(A, &i, UNITS);
                        if (i) Y_center = ex_float_NM(A, &i, UNITS);
                        i = go(A,1,"radius");
                        if (i) R = ex_float_NM(A, &i, UNITS);
                        i = go(A,1,"startAngle");
                        if (i) A1 = ex_float_NM(A, &i, -1);
                        i = go(A,1,"sweepAngle");
                        if (i) A2 = ex_float_NM(A, &i, -1);
                        A2 = A1 + A2;
                        i = go(A,1,"width");
                        if (i) W = ex_float_NM(A, &i, UNITS);
                        ////i = go(A,1,"netNameRef");
                        ////if (i) N = ex_str(A,&i);
                        X1 = X_center + R*cos((double)A1*(double)10/(double)573);
                        Y1 = Y_center + R*sin((double)A1*(double)10/(double)573);
                        X2 = X_center + R*cos((double)A2*(double)10/(double)573);
                        Y2 = Y_center + R*sin((double)A2*(double)10/(double)573);
                        if      ((rotateFoot == 90) ||
                                (rotateFoot == 180) ||
                                (rotateFoot == 0) ||
                                (rotateFoot == 270) ) {;}
                        else    {
                                double X = (double)X_center;
                                double Y = (double)Y_center;
                                Rotate_Vertex (&X, &Y, rotateFoot );
                                X_center = ( long)X;
                                Y_center = ( long)Y;
                                X = (double)X1;
                                Y = (double)Y1;
                                Rotate_Vertex (&X, &Y, rotateFoot );
                                X1 = ( long)X;
                                Y1 = ( long)Y;
                                X = (double)X2;
                                Y = (double)Y2;
                                Rotate_Vertex (&X, &Y, rotateFoot );
                                X2 = ( long)X;
                                Y2 = ( long)Y;
                                }
                        double ARC[299];
                        i = Generate_ARC        ((double)X1, (double)Y1,
                                                (double)X2, (double)Y2,
                                                (double)X_center, (double)Y_center,  &ARC[0]);
                        if (i > 3)
                                {
                                int n = 0;
                                LINE = "  outline_polyline: ";
                                LINE += W;
                                LINE += " ";
                                if (sel_rect1 > ARC[n]) sel_rect1 = (long)ARC[n];
                                if (sel_rect3 < ARC[n]) sel_rect3 = (long)ARC[n];
                                LINE += (long)ARC[n];
                                n++;
                                LINE += " ";
                                if (sel_rect2 > ARC[n]) sel_rect2 = (long)ARC[n];
                                if (sel_rect4 < ARC[n]) sel_rect4 = (long)ARC[n];
                                LINE += (long)ARC[n];
                                n++;
                                Form1->ListBox4_Lines->Items->Add(LINE);
                                while (n < i)
                                        {
                                        LINE = "    next_corner: ";
                                        if (sel_rect1 > ARC[n]) sel_rect1 = (long)ARC[n];
                                        if (sel_rect3 < ARC[n]) sel_rect3 = (long)ARC[n];
                                        LINE += (long)ARC[n];
                                        n++;
                                        LINE += " ";
                                        if (sel_rect2 > ARC[n]) sel_rect2 = (long)ARC[n];
                                        if (sel_rect4 < ARC[n]) sel_rect4 = (long)ARC[n];
                                        LINE += (long)ARC[n];
                                        n++;
                                        LINE += " 0";
                                        Form1->ListBox4_Lines->Items->Add(LINE);
                                        }
                                }
                        }//if (A.SubString(1,5) == "(arc ")
                //---------------------  triplePointArc -----------------------
                else if ((StrBegin (A, "(line " )) ||
                        (StrBegin (A, "(triplePointArc")) )
                        {
                        AnsiString LINE;
                        bool FlagArc = false;
                        long x1 = 0;
                        long y1 = 0;
                        long x2 = 0;
                        long y2 = 0;
                        long x3 = 0;
                        long y3 = 0;
                        long w = 0;
                        i = go (A, 1, "(pt ");
                        if (i)
                                {
                                i = go (A, i, " ");
                                x1 = ex_float_NM (A, &i, UNITS);
                                y1 = ex_float_NM (A, &i, UNITS);
                                if      ((rotateFoot == 90) ||
                                        (rotateFoot == 180) ||
                                        (rotateFoot == 0) ||
                                        (rotateFoot == 270) ) {;}
                                else    {
                                        double X = (double)x1;
                                        double Y = (double)y1;
                                        Rotate_Vertex (&X, &Y, rotateFoot );
                                        x1 = ( long)X;
                                        y1 = ( long)Y;
                                        }
                                }
                        i = go (A, i, "(pt ");
                        if (i)
                                {
                                i = go (A, i, " ");
                                x2 = ex_float_NM (A, &i, UNITS);
                                y2 = ex_float_NM (A, &i, UNITS);
                                if      ((rotateFoot == 90) ||
                                        (rotateFoot == 180) ||
                                        (rotateFoot == 0) ||
                                        (rotateFoot == 270) ) {;}
                                else    {
                                        double X = (double)x2;
                                        double Y = (double)y2;
                                        Rotate_Vertex (&X, &Y, rotateFoot );
                                        x2 = (long)X;
                                        y2 = (long)Y;
                                        }
                                }
                        i = go (A, i, "(pt ");
                        if (i)
                                {
                                FlagArc = true;
                                i = go (A, i, " ");
                                x3 = ex_float_NM (A, &i, UNITS);
                                y3 = ex_float_NM (A, &i, UNITS);
                                if      ((rotateFoot == 90) ||
                                        (rotateFoot == 180) ||
                                        (rotateFoot == 0) ||
                                        (rotateFoot == 270) ) {;}
                                else    {
                                        double X = (double)x3;
                                        double Y = (double)y3;
                                        Rotate_Vertex (&X, &Y, rotateFoot );
                                        x3 = (long)X;
                                        y3 = (long)Y;
                                        }
                                }
                        i = go (A, i, "(width");
                        if (i)
                                {
                                i = go (A, i, " ");
                                w = ex_float_NM (A, &i, UNITS);
                                }
                        if (FlagArc)
                                {
                                double ARC[299];
                                i = Generate_ARC (x2,y2,x3,y3,x1,y1, &ARC[0]);
                                if (i > 3)
                                        {
                                        int n = 0;
                                        LINE = "  outline_polyline: ";
                                        LINE += w;
                                        LINE += " ";
                                        if (sel_rect1 > ARC[n]) sel_rect1 = (long)ARC[n];
                                        if (sel_rect3 < ARC[n]) sel_rect3 = (long)ARC[n];
                                        LINE += (long)ARC[n];
                                        n++;
                                        LINE += " ";
                                        if (sel_rect2 > ARC[n]) sel_rect2 = (long)ARC[n];
                                        if (sel_rect4 < ARC[n]) sel_rect4 = (long)ARC[n];
                                        LINE += (long)ARC[n];
                                        n++;
                                        Form1->ListBox4_Lines->Items->Add(LINE);
                                        while (n < i)
                                                {
                                                LINE = "    next_corner: ";
                                                if (sel_rect1 > ARC[n]) sel_rect1 = (long)ARC[n];
                                                if (sel_rect3 < ARC[n]) sel_rect3 = (long)ARC[n];
                                                LINE += (long)ARC[n];
                                                n++;
                                                LINE += " ";
                                                if (sel_rect2 > ARC[n]) sel_rect2 = (long)ARC[n];
                                                if (sel_rect4 < ARC[n]) sel_rect4 = (long)ARC[n];
                                                LINE += (long)ARC[n];
                                                n++;
                                                LINE += " 0";
                                                Form1->ListBox4_Lines->Items->Add(LINE);
                                                }
                                        }
                                }
                        else    {
                                LINE = "  outline_polyline: ";
                                LINE += w;
                                LINE += " ";
                                if (sel_rect1 > x1) sel_rect1 = x1;
                                if (sel_rect3 < x1) sel_rect3 = x1;
                                LINE += x1;
                                LINE += " ";
                                if (sel_rect2 > y1) sel_rect2 = y1;
                                if (sel_rect4 < y1) sel_rect4 = y1;
                                LINE += y1;
                                Form1->ListBox4_Lines->Items->Add(LINE);
                                LINE = "    next_corner: ";
                                if (sel_rect1 > x2) sel_rect1 = x2;
                                if (sel_rect3 < x2) sel_rect3 = x2;
                                LINE += x2;
                                LINE += " ";
                                if (sel_rect2 > y2) sel_rect2 = y2;
                                if (sel_rect4 < y2) sel_rect4 = y2;
                                LINE += y2;
                                LINE += " 0";
                                Form1->ListBox4_Lines->Items->Add(LINE);
                                }
                        }
                //-------------------------- pads ----------------------------------------------------
                //-------------------------------
                else if (StrBegin (A, "(pad " ))
                        {
                        pinX = 0;
                        pinY = 0;
                        rotationPAD = 0;
                        AnsiString PinDes;
                        long NumPin = 0;
                        i = go (A, 1, "(padNum");
                        if (i)
                                {
                                i = go(A, i, " ");
                                NumPin = ex_float_NM (A, &i, -1);
                                PinDes = Ex_PinDes (OpenD, originalName, (int)NumPin );
                                }
                        i = go (A, 1, "padStyleRef");
                        if (i)
                                {
                                bool FLAG;
                                i = go(A, i, " ");
                                AnsiString padStyleRef = ex_str(A, &i);
                                if (PinDes.SubString(1,5) != "error" ) FLAG = Ex_PadStyle (padStyleRef,0);
                                if (FLAG) RETURNFLAGIFPOLY = true;
                                }
                        i = go (A, 1, "rotation");
                        if (i)
                                {
                                i = go (A, i, " ");
                                rotationPAD = ex_float_NM (A, &i, -1);
                                }
                        i = go (A, 1, "isFlipped");
                        if (i)
                                {
                                rotationPAD = 180 - rotationPAD;
                                if (rotationPAD > 360) rotationPAD = rotationPAD - 360;
                                type_top = type_top + type_bot;
                                type_bot = type_top - type_bot;
                                type_top = type_top - type_bot;
                                w_top = w_top + w_bot;
                                w_bot = w_top - w_bot;
                                w_top = w_top - w_bot;
                                h_top = h_top + h_bot;
                                h_bot = h_top - h_bot;
                                h_top = h_top - h_bot;
                                }
                        i = go (A, 1, "(pt" );
                        if (i)
                                {
                                i = go (A, i, " " );
                                pinX = ex_float_NM (A, &i, UNITS);
                                pinY = ex_float_NM (A, &i, UNITS);
                                }

                        //   если (PinDes.SubString(1,5) != "error" )
                        if (PinDes.SubString(1,5) != "error" )
                                {
                                //запись ПАДОВ...
                                stringPADSrecord (PinDes);
                                }
                        }
                }
        return RETURNFLAGIFPOLY;
        }


//===============================================
//void Create_Foot (AnsiString OpenD, long CNT)
//===============================================
void Create_Foot (AnsiString OpenD, long CNT)
{
AnsiString A;
long i = 0;
char str[MAX_CHARS];

//ЧТЕНИЕ PART LIST

Form1->Label4->Caption = "Footprint creation by PartList.txt" ;
Application->ProcessMessages();
A = ExtractFilePath (Application->ExeName)  ;
A = A + "Import_Tango\\PartList.txt";
ifstream PartList (A.c_str());

//Создание FootPrints.txt
AnsiString B = ExtractFilePath (Application->ExeName)  ;
B = B + "Import_Tango\\FootPrints.txt";
ofstream FootPrints (B.c_str());
FootPrints.close();

//Создание Area.txt
B = ExtractFilePath (Application->ExeName)  ;
B = B + "Import_Tango\\Area.txt";
ofstream Area (B.c_str());
Area.close();

//Создание SM.txt
B = ExtractFilePath (Application->ExeName)  ;
B = B + "Import_Tango\\SM.txt";
ofstream SM (B.c_str());
SM.close();

AnsiString shape = "";
Reference = "";
while (A.SubString(1,3) != "end" )
        {
        PartList.getline(str,sizeof(str));
        A = str;
        A = A.Trim();
        if      (StrBegin (A, "part" ))
                {
                FlagVia = false;
                Side = false;
                shape = "";
                rotateFoot = 0;
                i = prob (A,1);
                Reference = A.SubString(i,(A.Length()-i+1));
                }
        else if (StrBegin (A, "pos" ))
                {
                i = prob (A, 1);
                posX = ex_float_NM (A, &i, -1);
                posY = ex_float_NM (A, &i, -1);
                long Sd = ex_float_NM (A, &i, -1);
                if (Sd) Side = true;
                else    Side = false;
                Angle = ex_float_NM (A, &i, -1);
                }
        else if (StrBegin (A, "shape" ))
                {
                AnsiString shape_no_rot;
                rotateFoot = 0;
                i = prob (A, 1);
                shape = ex_str (A, &i);
                Form1->Label4->Caption = "Footprint creation: " + shape;
                Application->ProcessMessages();
                i = 1;
                while ((shape.SubString(i,1) != "^")&&(i <= shape.Length())) i++;
                i++;
                shape_no_rot = shape;
                if (i <= shape.Length())
                        {
                        int m = shape.Length() - i + 1;
                        AnsiString rot = shape.SubString(i,m);
                        if (!rot.Length()) rot = "0";
                        shape_no_rot = shape.SubString(1,(i-2));
                        i = 1;
                        rotateFoot = ex_float_NM (rot, &i, -1);
                        }
                i = Form2->ListBox1_FootPrintsName->Count;
                bool FLAGPOLY;
                if (StrBegin (Reference, "FREEPAD__" ))
                        {
                        ///if (StrBegin (shape, "VIA" )) FlagVia = true;
                        n_pins = 0;
                        sel_rect1 = SELR;
                        sel_rect2 = SELR;
                        sel_rect3 = -SELR;
                        sel_rect4 = -SELR;
                        Form1->ListBox4_Lines->Clear();
                        Form1->ListBox2->Clear();
                        pinX = 0;
                        pinY = 0;
                        rotationPAD = 0;
                        Ex_PadStyle (shape_no_rot,0);
                        stringPADSrecord ("1");
                        }
                else    Ex_Shape (shape_no_rot, rotateFoot);
                i = Form2->ListBox1_FootPrintsName->Items->IndexOf(shape);
                if (i < 0)
                        {
                        W_FootPrint (shape);
                        Form2->ListBox1_FootPrintsName->Items->Add(shape);
                        }
                }
        }
PartList.close();
Form1->Label4->Caption = "Footprint creation completed" ;
Application->ProcessMessages();


B = ExtractFilePath (Application->ExeName)  ;
ofstream CombN;
CombN.open((B + "Import_Tango\\CombNetList.txt").c_str(), std::ios_base::app );
CombN << "end";
CombN << endl;
CombN.close();

B = ExtractFilePath (Application->ExeName)  ;
ofstream FootP;
FootP.open((B + "Import_Tango\\FootPrints.txt").c_str(), std::ios_base::app );
FootP << "end" << endl;
FootP.close();

//--------------- vias
int GridIndex = Form2->StringGrid1->Cols[0]->IndexOf("Via") ;
if (GridIndex >= 0)     A = "Via";
else                    A = "";
AnsiString Sh;
AnsiString ShBack;
i = 0;
Form1->Label4->Caption = "Vias are created" ;
Application->ProcessMessages();
while (A.UpperCase().SubString(1,A.Length()) == "VIA")
        {
        ShBack = Sh;
        Sh = Form2->StringGrid1->Cells[1][GridIndex];
        if (ShBack.UpperCase().SubString(1,ShBack.Length()) != Sh.UpperCase().SubString(1,Sh.Length()))Ex_PadStyle (Sh, 1);
        if (w_top)      Form2->StringGrid1->Cells[5][GridIndex] = AnsiString(w_top);
        else if (w_inn) Form2->StringGrid1->Cells[5][GridIndex] = AnsiString(w_inn);
        else            Form2->StringGrid1->Cells[5][GridIndex] = AnsiString(hole_diam);
        Form2->StringGrid1->Cells[6][GridIndex] = AnsiString(hole_diam);
        Form2->StringGrid1->Cells[7][GridIndex] = "0";
        Form2->StringGrid1->Cells[8][GridIndex] = "0";
        Form2->StringGrid1->Cells[9][GridIndex] = "0";
        Form2->StringGrid1->Cells[10][GridIndex] = "0";
        Form2->StringGrid1->Cells[11][GridIndex] = "0";
        Form2->StringGrid1->Cells[12][GridIndex] = "0";
        Form2->StringGrid1->Cells[13][GridIndex] = "0";
        Form2->StringGrid1->Cells[14][GridIndex] = "0";
        Form2->StringGrid1->Cells[15][GridIndex] = "0";
        Form2->StringGrid1->Cells[16][GridIndex] = "0";
        GridIndex++;
        i++;
        A = Form2->StringGrid1->Cells[0][GridIndex];
        if (i%10 == 0)
                {
                Form1->Label4->Caption = "Vias are created " + AnsiString(i) ;
                Application->ProcessMessages();
                }
        }

}
