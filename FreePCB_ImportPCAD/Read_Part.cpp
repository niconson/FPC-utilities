//---------------------------------------------------------------------------


#pragma hdrstop

#include "Read_Part.h"
#include "HEAD.h"
#include "LSTBXS.h"
#include "fstream.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

static int ViaFlag = 0;  //     1-Pad 2-Via
static AnsiString Package;
static AnsiString Shape;
static AnsiString Ref;
static AnsiString Value;
static AnsiString Net;
static long Ang;
static bool Side = false;
static long PosX;
static long PosY;
static int PadIndex = 0;
static long RefRot;
static long ValueRot;
static long RefX;
static long RefY;
static long ValueX;
static long ValueY;
static bool RefVis;
static bool ValueVis;
static long WValue;
static long HValue;
static long WRef;
static long HRef;







void write_parts ( void )
        {
        if (!Ref.Length()) return;
        if (ViaFlag != 2)
                {
                bool Flag = false;
                long CAngle ;
                /*if(     (Ang == 0 ) ||
                        (Ang == 90 ) ||
                        (Ang == 180 ) ||
                        (Ang == 270 ) ) {*/CAngle = Ang;  Flag = true;/*}
                else CAngle = 0;*/
                AnsiString B = ExtractFilePath (Application->ExeName)  ;
                ofstream parts;
                parts.open((B + "Import_Tango\\PartList.txt").c_str(), std::ios_base::app );
               
                //part
                parts << "part: ";
                parts << Ref.c_str() << endl;
                if (Ref.Pos(".") > 0)
                        {
                        ShowMessage("  Error Reference: " + Ref);
                        exit(0);
                        }
                if (Side)
                        {
                        RefX = -RefX;
                        ValueX = -ValueX;
                        }
                if (CAngle)
                        {
                        double X = RefX;
                        double Y = RefY;
                        Rotate_Vertex (&X, &Y, -CAngle);
                        RefX = X;
                        RefY = Y;
                        X = ValueX;
                        Y = ValueY;
                        Rotate_Vertex (&X, &Y, -CAngle);
                        ValueX = X;
                        ValueY = Y;
                        }
                RefRot = 360 - RefRot;
                ValueRot = 360 - ValueRot;
                RefRot = RefRot + CAngle;
                ValueRot = ValueRot + CAngle;
                if (RefRot >= 360)      RefRot = RefRot - 360;
                if (ValueRot >= 360)    ValueRot = ValueRot - 360;
                //ref_text
                parts << "  ref_text: ";
                parts << AnsiString(HRef/2).c_str();
                parts << " ";
                parts << AnsiString(WRef).c_str();
                parts << " ";
                parts << AnsiString(RefRot).c_str();
                parts << " ";
                parts << AnsiString(RefX).c_str();
                parts << " ";
                parts << AnsiString(RefY).c_str();
                if (ViaFlag)            parts << " 0";
                else if (!RefVis)       parts << " 0";
                parts << endl;

                //value
                parts << "  value: \"";
                parts << Value.c_str();
                parts << "\" ";
                parts << AnsiString(HValue/2).c_str();
                parts << " ";
                parts << AnsiString(WValue).c_str();
                parts << " ";
                parts << AnsiString(ValueRot).c_str();
                parts << " ";
                parts << AnsiString(ValueX).c_str();
                parts << " ";
                parts << AnsiString(ValueY).c_str();
                if (ViaFlag)            parts << " 0";
                else if (!ValueVis)     parts << " 0";
                parts << endl;

                //pos
                parts << "  pos: ";
                parts << AnsiString(PosX).c_str();
                parts << " ";
                parts << AnsiString(PosY).c_str();
                parts << " ";
                parts << AnsiString((int)Side).c_str();
                parts << " ";
                if (!Side)
                if (CAngle) CAngle = 360 - CAngle;
                parts << AnsiString(CAngle).c_str();
                parts << " 0" << endl;

                //shape
                parts << "  shape: \"";
                parts << Shape.c_str();
                if (!Flag) parts << ("^" + AnsiString(Ang)).c_str();
                parts << "\"" << endl;
                parts.close();
                if (ViaFlag == 1)
                        {
                        B = ExtractFilePath (Application->ExeName)  ;
                        ofstream ViasNetlist;
                        ViasNetlist.open((B + "Import_Tango\\NetListVias.txt").c_str(), std::ios_base::app );
                        B = AnsiString(Ref) + ".1";
                        ViasNetlist << Net.c_str();
                        ViasNetlist << endl;
                        ViasNetlist << B.c_str();
                        ViasNetlist << endl;
                        ViasNetlist.close();
                        ViaFlag = 0;
                        }
                }
        else    {
                Form2->StringGrid1->Cells[0][Form2->StringGrid1->Row] = "Via";
                Form2->StringGrid1->Cells[1][Form2->StringGrid1->Row] = Shape;
                Form2->StringGrid1->Cells[2][Form2->StringGrid1->Row] = Net;
                Form2->StringGrid1->Cells[3][Form2->StringGrid1->Row] = PosX;
                Form2->StringGrid1->Cells[4][Form2->StringGrid1->Row] = PosY;
                Form2->StringGrid1->RowCount++;
                Form2->StringGrid1->Row++;
                Form2->StringGrid1->Cells[0][Form2->StringGrid1->Row] = "";
                Form2->StringGrid1->Cells[1][Form2->StringGrid1->Row] = "-1";
                Form2->StringGrid1->Cells[2][Form2->StringGrid1->Row] = "Unconnected";
                }

        }
//---------------------------------------------
//---------------------------------------------
void Read_Part (AnsiString OpenD, long CNT)
{
//long SaveCNT = CNT;
//ЧТЕНИЕ PATTERN PCAD
long i = 0;
char str[MAX_CHARS];
Form1->Label4->Caption = "Reading parts" ;
Application->ProcessMessages();
AnsiString A;
ifstream read_P (OpenD.c_str());

//Создание PartList.txt
AnsiString B = ExtractFilePath (Application->ExeName)  ;
B = B + "Import_Tango\\PartList.txt";
ofstream WR_P (B.c_str());
WR_P.close();

//Создание NetListVias.txt
B = ExtractFilePath (Application->ExeName)  ;
B = B + "Import_Tango\\NetListVias.txt";
ofstream WR_V (B.c_str());
WR_V.close();

//"(pcbDesign "
long Count_Part = 0;
while (A.SubString(1,11) != "(pcbDesign " )
        {
        read_P.getline(str,sizeof(str));
        A = str;
        A = A.Trim();
        CNT--;
        if (CNT<0) break;
        }
while (A.SubString(1,11) != "(multiLayer" )
        {
        read_P.getline(str,sizeof(str));
        A = str;
        A = A.Trim();
        CNT--;
        if (CNT<0) break;
        }
while (CNT>=0)
        {
        read_P.getline(str,sizeof(str));
        A = str;
        A = A.Trim();
        //(pattern
        if (StrBegin (A, "(pattern "))
                {
                if (Count_Part)
                        {
                        write_parts ();
                        }
                ViaFlag = 0;
                Count_Part++;
                Ref = "";
                Value = "";
                Package = "";
                Shape = "";
                RefVis = false;
                ValueVis = false;
                Side = false;
                PosX = 0;
                PosY = 0;
                Ang = 0;
                RefRot = 0;
                ValueRot = 0;
                RefX = 0;
                RefY = 0;
                ValueX = 0;
                ValueY = 0;
                WValue = 0;
                HValue = 0;
                WRef = 0;
                HRef = 0;
                i = go (A, 1, "patternRef");
                if (i)
                        {
                        i = go (A, i, " ");
                        Shape = ex_str (A,&i);
                        i = Shape.Length();
                        while (i)
                                {
                                if (Shape.SubString(i,1) == "_") break;
                                i--;
                                }
                        }
                else    ShowMessage ("    Error Shape!");
                if (i)  Package = Shape.SubString(1,(i-1));
                else    Package = "";
                //"(refDesRef"
                i = go (A, 1, "refDesRef");
                if (i)
                        {
                        i = go (A, i, " ");
                        Ref = ex_str (A,&i);
                        }
                else    ShowMessage ("    Error Ref!");
                Form1->Label4->Caption = "Reading part: " + Ref;
                Application->ProcessMessages();
                //(pt
                i = go (A, 1, "(pt ");
                if (i)
                        {
                        i = go (A, i, " ");
                        PosX = ex_float_NM (A, &i, UNITS);
                        PosY = ex_float_NM (A, &i, UNITS);
                        }
                //(rotation
                i = go (A, 1, "rotation");
                if (i)
                        {
                        i = go (A, i, " ");
                        Ang = ex_float_NM (A, &i, -1);
                        }
                //(isFlipped
                i = go (A, 1, "isFlipped");
                if (i) Side = true;
                }
        //(attr
        if (StrBegin (A, "(attr"))
                {
                i = prob (A, 1);
                AnsiString attr = ex_str (A,&i);
                if (attr.UpperCase().SubString(1,6) == "REFDES" )
                        {
                        if (go (A, 1, "isVisible" )) RefVis = true;
                        i = go (A, 1, "rotation" );
                        if (i)
                                {
                                RefRot = ex_float_NM(A, &i, -1);
                                }
                        i = go (A, 1, "(pt " );
                        if (i)
                                {
                                RefX = ex_float_NM(A, &i, UNITS);
                                RefY = ex_float_NM(A, &i, UNITS);
                                }
                        i = go (A, 1, "textStyleRef" );
                        if (i)
                                {
                                AnsiString textStyleRef = ex_str(A, &i);
                                RTextStyle (textStyleRef, &WRef, &HRef) ;
                                }
                        }
                else if (attr.UpperCase().SubString(1,5) == "VALUE" ||
                        (attr.UpperCase().SubString(1,4) == "TYPE" && Value.Length() == 0))
                        {
                        Value = ex_str (A,&i);
                        if (go (A, 1, "isVisible" )) ValueVis = true;
                        i = go (A, 1, "rotation" );
                        if (i)
                                {
                                ValueRot = ex_float_NM(A, &i, -1);
                                }
                        i = go (A, 1, "(pt " );
                        if (i)
                                {
                                ValueX = ex_float_NM(A, &i, UNITS);
                                ValueY = ex_float_NM(A, &i, UNITS);
                                }
                        i = go (A, 1, "textStyleRef" );
                        if (i)
                                {
                                AnsiString textStyleRef = ex_str(A, &i);
                                RTextStyle (textStyleRef, &WValue, &HValue) ;
                                }
                        }
                }
        //(pad, (via
        if ((StrBegin(A, "(pad ")) || (StrBegin(A, "(via ")))
                {
                if (Count_Part)
                        {
                        write_parts ();
                        }
                Count_Part++;
                PadIndex++;
                Ref = AnsiString("FreePad__") + AnsiString(PadIndex);
                Value = "";
                Package = "";
                Shape = "";
                Side = false;
                PosX = 0;
                PosY = 0;
                Ang = 0;
                Net = "";
                //(padStyleRef
                i = go (A, 1, "padStyleRef");
                if (i)
                        {
                        i = go (A, i, " ");
                        Shape = ex_str (A,&i);
                        }
                //(viaStyleRef
                i = go (A, 1, "viaStyleRef");
                if (i)
                        {
                        i = go (A, i, " ");
                        Shape = ex_str (A,&i);
                        }
                //(pt
                i = go (A, 1, "(pt ");
                if (i)
                        {
                        i = go (A, i, " ");
                        PosX = ex_float_NM (A, &i, UNITS);
                        PosY = ex_float_NM (A, &i, UNITS);
                        }
                //(rotation
                i = go (A, 1, "rotation");
                if (i)
                        {
                        i = go (A, i, " ");
                        Ang = ex_float_NM (A, &i, -1);
                        }
                //(isFlipped
                i = go (A, 1, "isFlipped");
                if (i) Side = true;
                //netNameRef
                i = go(A, 1, "netNameRef");
                if (i)
                        {
                        i = go(A, i, " ");
                        Net = ex_str(A,&i);
                        }
                if (StrBegin(A, "(pad "))       ViaFlag = 1;
                else                            ViaFlag = 2;
                }
        if (!CNT) break;
        CNT--;
        }
if (Count_Part)
        {
        write_parts ();
        }
Form1->Label4->Caption = "Reading parts completed" ;
Application->ProcessMessages();
read_P.close();

B = ExtractFilePath (Application->ExeName)  ;
ofstream PartS;
PartS.open((B + "Import_Tango\\PartList.txt").c_str(), std::ios_base::app );
PartS << "end" << endl;
PartS.close();
}



