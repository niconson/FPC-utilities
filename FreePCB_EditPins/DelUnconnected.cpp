//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DelUnconnected.h"
#include "fstream.h"
#include "math.h"
#include "clipbrd.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
long i;
int i_FOOTPRINTS;
int i_BOARD;
int i_PARTS;
int i_NETS;
int i_TEXTS;
AnsiString path;
//
int UnitsFootPrint = 0;
struct PadStack
        {
        int    TypeTop         ;
        int    TypeInner       ;
        int    TypeBottom      ;
        int    TypeTopMask     ;
        int    TypeBottomMask  ;
        int    TypeTopPaste    ;
        int    TypeBottomPaste ;
        double TopW            ;
        double InnerW          ;
        double BottomW         ;
        double MaskTopW        ;
        double MaskBottomW     ;
        double PasteTopW       ;
        double PasteBottomW    ;
        double TopH            ;
        double InnerH          ;
        double BottomH         ;
        double MaskTopH        ;
        double MaskBottomH     ;
        double PasteTopH       ;
        double PasteBottomH    ;
        double TopR            ;
        double InnerR          ;
        double BottomR         ;
        double MaskTopR        ;
        double MaskBottomR     ;
        double PasteTopR       ;
        double PasteBottomR    ;
        int    TopThrml        ;
        int    InnerThrml      ;
        int    BottomThrml     ;
        };
struct mPoint
        {
        TPoint p;
        AnsiString name;
        bool hole;
        bool T;
        bool B;
        int n_pins;
        int layer;
        };
PadStack ClientPadStack;
Line * LinesArea = 0;
mPoint ** lib_PINS = 0;
mPoint  loc_PINS[MAX_LOC];



//---------------------------------------------------------------------------
int ReadPadStack (PadStack *PADSTACK, int StartIndex)
        {
        (*PADSTACK).TypeTop =       DEFAULT+1;
        (*PADSTACK).TypeInner =     DEFAULT+1;
        (*PADSTACK).TypeBottom =    DEFAULT+1;
        (*PADSTACK).TypeTopMask =   DEFAULT+1;
        (*PADSTACK).TypeBottomMask =DEFAULT+1;
        (*PADSTACK).TypeTopPaste =  DEFAULT+1;
        (*PADSTACK).TypeBottomPaste=DEFAULT+1;
        (*PADSTACK).TopW =          DEFAULT+1;
        (*PADSTACK).InnerW =        DEFAULT+1;
        (*PADSTACK).BottomW =       DEFAULT+1;
        (*PADSTACK).MaskTopW =      DEFAULT+1;
        (*PADSTACK).MaskBottomW =   DEFAULT+1;
        (*PADSTACK).PasteTopW =     DEFAULT+1;
        (*PADSTACK).PasteBottomW =  DEFAULT+1;
        (*PADSTACK).TopH =          DEFAULT+1;
        (*PADSTACK).InnerH =        DEFAULT+1;
        (*PADSTACK).BottomH =       DEFAULT+1;
        (*PADSTACK).MaskTopH =      DEFAULT+1;
        (*PADSTACK).MaskBottomH =   DEFAULT+1;
        (*PADSTACK).PasteTopH =     DEFAULT+1;
        (*PADSTACK).PasteBottomH =  DEFAULT+1;
        (*PADSTACK).TopR =          DEFAULT+1;
        (*PADSTACK).InnerR =        DEFAULT+1;
        (*PADSTACK).BottomR =       DEFAULT+1;
        (*PADSTACK).MaskTopR =      DEFAULT+1;
        (*PADSTACK).MaskBottomR =   DEFAULT+1;
        (*PADSTACK).PasteTopR =     DEFAULT+1;
        (*PADSTACK).PasteBottomR =  DEFAULT+1;
        (*PADSTACK).TopThrml =      DEFAULT+1;
        (*PADSTACK).InnerThrml =    DEFAULT+1;
        (*PADSTACK).BottomThrml =   DEFAULT+1;
        //
        AnsiString Read = Form1->File->Items->operator [](StartIndex);
        if (Read.SubString(1,3) == "pin")StartIndex++;
        while (1)
                {
                Read = Form1->File->Items->operator [](StartIndex);
                if (Read.SubString(1,3) == "pin")       break;
                if (Read.SubString(1,4) == "name")      break;
                if (Read.SubString(1,7) == "[board]")   break;
                StartIndex++;
                //
                if (Read.SubString(1,7) == "top_pad")
                        {
                        i = prob(Read,1);
                        (*PADSTACK).TypeTop =           ex_float_NM(Read, &i, -1);
                        (*PADSTACK).TopW =              ex_float_NM(Read, &i, -1);
                        (*PADSTACK).TopH =              ex_float_NM(Read, &i, -1);
                                                        ex_float_NM(Read, &i, -1);
                        (*PADSTACK).TopR =              ex_float_NM(Read, &i, -1);
                        (*PADSTACK).TopThrml =          ex_float_NM(Read, &i, -1);
                        }
                else if (Read.SubString(1,8) == "top_mask")
                        {
                        i = prob(Read,1);
                        (*PADSTACK).TypeTopMask =       ex_float_NM(Read, &i, -1);
                        (*PADSTACK).MaskTopW =          ex_float_NM(Read, &i, -1);
                        (*PADSTACK).MaskTopH =          ex_float_NM(Read, &i, -1);
                                                        ex_float_NM(Read, &i, -1);
                        (*PADSTACK).MaskTopR =          ex_float_NM(Read, &i, -1);
                        }
                else if (Read.SubString(1,9) == "top_paste")
                        {
                        i = prob(Read,1);
                        (*PADSTACK).TypeTopPaste =      ex_float_NM(Read, &i, -1);
                        (*PADSTACK).PasteTopW =         ex_float_NM(Read, &i, -1);
                        (*PADSTACK).PasteTopH =         ex_float_NM(Read, &i, -1);
                                                        ex_float_NM(Read, &i, -1);
                        (*PADSTACK).PasteTopR =         ex_float_NM(Read, &i, -1);
                        }
                else if (Read.SubString(1,9) == "inner_pad")
                        {
                        i = prob(Read,1);
                        (*PADSTACK).TypeInner =         ex_float_NM(Read, &i, -1);
                        (*PADSTACK).InnerW =            ex_float_NM(Read, &i, -1);
                        (*PADSTACK).InnerH =            ex_float_NM(Read, &i, -1);
                                                        ex_float_NM(Read, &i, -1);
                        (*PADSTACK).InnerR =            ex_float_NM(Read, &i, -1);
                        (*PADSTACK).InnerThrml =        ex_float_NM(Read, &i, -1);
                        }
                else if (Read.SubString(1,10) == "bottom_pad")
                        {
                        i = prob(Read,1);
                        (*PADSTACK).TypeBottom =        ex_float_NM(Read, &i, -1);
                        (*PADSTACK).BottomW =           ex_float_NM(Read, &i, -1);
                        (*PADSTACK).BottomH =           ex_float_NM(Read, &i, -1);
                                                        ex_float_NM(Read, &i, -1);
                        (*PADSTACK).BottomR =           ex_float_NM(Read, &i, -1);
                        (*PADSTACK).BottomThrml =       ex_float_NM(Read, &i, -1);
                        }
                else if (Read.SubString(1,11) == "bottom_mask")
                        {
                        i = prob(Read,1);
                        (*PADSTACK).TypeBottomMask =    ex_float_NM(Read, &i, -1);
                        (*PADSTACK).MaskBottomW =       ex_float_NM(Read, &i, -1);
                        (*PADSTACK).MaskBottomH =       ex_float_NM(Read, &i, -1);
                                                        ex_float_NM(Read, &i, -1);
                        (*PADSTACK).MaskBottomR =       ex_float_NM(Read, &i, -1);
                        }
                else if (Read.SubString(1,12) == "bottom_paste")
                        {
                        i = prob(Read,1);
                        (*PADSTACK).TypeBottomPaste =   ex_float_NM(Read, &i, -1);
                        (*PADSTACK).PasteBottomW =      ex_float_NM(Read, &i, -1);
                        (*PADSTACK).PasteBottomH =      ex_float_NM(Read, &i, -1);
                                                        ex_float_NM(Read, &i, -1);
                        (*PADSTACK).PasteBottomR =      ex_float_NM(Read, &i, -1);
                        }
                }
        return (StartIndex - 1);
        }
//---------------------------------------------------------------------------




//---------------------------------------------------------------------------
void Rotate_Vertex (float *X, float *Y, float Ang)
{
long DEF = DEFAULT;
float start_Ang = 0;
float end_Ang = 0;
float radius = 0;
bool Flag = false;
if ( ABS(*X) > DEF || ABS(*Y) > DEF )
        {
        Flag = true;
        *X = (*X)/(float)DEF;
        *Y = (*Y)/(float)DEF;
        }
if (ABS(*X) < BY_ZERO)
        {
        if (*Y > 0) start_Ang = 90;
        else if (*Y < 0) start_Ang = 270;
        }
else
        {
        start_Ang = (atan(*Y/(*X)))*(float)180/(float)M_PI;
        if ((*X > 0)&&(*Y < 0)) start_Ang = (float)360 + start_Ang;
        if (*X < 0) start_Ang = (float)180 + start_Ang;
        }
end_Ang = start_Ang + Ang;
double powx = ABS(*X);
double powy = ABS(*Y);
if (powx > BY_ZERO) powx = pow(powx,2);
if (powy > BY_ZERO) powy = pow(powy,2);
if (powx > BY_ZERO || powy > BY_ZERO)   radius = sqrt(powx + powy);
else                                    radius = powx + powy;
*Y = radius*sin(end_Ang*(float)M_PI/(float)180);
*X = radius*cos(end_Ang*(float)M_PI/(float)180);
if (Flag) *X = (*X)*(float)DEF;
if (Flag) *Y = (*Y)*(float)DEF;
}
//---------------------------------------------------------------------------




//---------------------------------------------------------------------------
void mirror_angle (float Part_angle, bool Part_layer, float *X, float *Y)
{
if(Part_layer) (*X) = -(*X);
Rotate_Vertex (X, Y, (-Part_angle));
}
//---------------------------------------------------------------------------





//---------------------------------------------------------------------------
void ReadFoot (AnsiString Reference, AnsiString Shape, bool side, int An, long xpos, long ypos)
        {
        static int loc = 0;
        if (loc >= (MAX_LOC-1)) return;
        ofstream report ;
        report.open((path + "report.txt").c_str(), std::ios_base::app );
        AnsiString S;
        float x,y;
        int cnt = 0;
        int index = Form1->lib_NAMES->Items->IndexOf(Shape) ;
        if (index == -1 ) ShowMessage("    Fatal Error! Footprint: " + Shape + " not found!" );
        else while   (cnt<lib_PINS[index][0].n_pins)
                {
                x = lib_PINS[index][cnt].p.x;
                y = lib_PINS[index][cnt].p.y;
                mirror_angle(An,side,&x,&y);
                x += xpos;
                y += ypos;
                loc_PINS[loc].p.x = x;
                loc_PINS[loc].p.y = y;
                loc_PINS[loc].hole = lib_PINS[index][cnt].hole;
                AnsiString test_str = Reference + "." + lib_PINS[index][cnt].name;
                int iof = Form1->EditList->Items->IndexOf(test_str);
                if( iof == -1 )
                        Form1->AllPins->Items->Add(test_str);
                Form1->loc_NAMES->Items->Add(test_str);
                if (!lib_PINS[index][cnt].hole)
                        {
                        Form1->SMTpins->Items->Add(Reference + "." + lib_PINS[index][cnt].name);
                        if (side)
                                {
                                if (lib_PINS[index][cnt].T) loc_PINS[loc].layer = LAY_BOT;
                                else                        loc_PINS[loc].layer = LAY_TOP;
                                }
                        else    {
                                if (lib_PINS[index][cnt].T) loc_PINS[loc].layer = LAY_TOP;
                                else                        loc_PINS[loc].layer = LAY_BOT;
                                }
                        }
                report << (Reference + "." + lib_PINS[index][cnt].name).c_str();
                report << " ";
                report << AnsiString (x).c_str();
                report << " ";
                report << AnsiString (y).c_str() << endl;
                loc++;
                cnt++;
                }
        report.close();
        }
//---------------------------------------------------------------------------








void ini()
{
Form1->AllPins->Clear();
Form1->EditList->Clear();
AnsiString S = "";
Form1->AllPins->Sorted = false;
Form1->File->           Sorted = false;
Form1->ChangeList->     Sorted = false;
Form1->SMTpins   ->     Sorted = false;
Form1->Connected   ->   Sorted = false;
Form1->lib_NAMES->      Sorted = false;
Form1->loc_NAMES->      Sorted = false;
Form1->current_net_pins->Sorted = false;
Form1->AllPins->MultiSelect = true;
Form1->EditList->MultiSelect = true;
Form1->File->           MultiSelect = true;
Form1->ChangeList->     MultiSelect = true;
Form1->SMTpins   ->     MultiSelect = true;
Form1->Connected   -> MultiSelect = true;
Form1->NoChange_top->Checked = true;
Form1->NoChange_inner->Checked = true;
Form1->NoChange_bottom->Checked = true;
//
AnsiString CLPBRD = Clipboard()->AsText;
Clipboard()->Clear();
if (CLPBRD.SubString(1,6) == "ObjMan")
        {
        i = prob(CLPBRD, 1);
        Form1->OpenDialog1->FileName = ex_str(CLPBRD, &i) ;
        }
else if (Form1->OpenDialog1->FileName.Length()){;}
else if (Form1->OpenDialog1->Execute()){;}
else exit(0);
if (Form1->OpenDialog1->FileName.Length() == 0) return;
//
path = ExtractFilePath(Application->ExeName);
ofstream report ((path + "report.txt").c_str());
report.close();
char s[2501];
ifstream RFile (Form1->OpenDialog1->FileName.c_str());
int max_pins = 0;
int cnt_footprints = 0;
for (int cnt=0; !RFile.eof(); cnt++ )
        {
        RFile.getline(s,2500);
        S = s;
        S = S.Trim();
        if (S.SubString(1,7) == "n_pins:")
                {
                i = prob(S, 1);
                int pins = ex_float_NM(S, &i, -1);
                max_pins = MAX(max_pins,pins);
                }
        if (S.SubString(1,5) == "name:" )               cnt_footprints++;
        if (S.SubString(1,S.Length()) == "[footprints]")i_FOOTPRINTS = cnt;
        if (S.SubString(1,S.Length()) == "[board]")     i_BOARD = cnt;
        if (S.SubString(1,S.Length()) == "[parts]")     i_PARTS = cnt;
        if (S.SubString(1,S.Length()) == "[nets]")      i_NETS = cnt;
        if (S.SubString(1,S.Length()) == "[texts]")     i_TEXTS = cnt;
        Form1->File->Items->Add(S);
        }
RFile.close();
//-----------
if( lib_PINS )
        {
        for( int im=Form1->lib_NAMES->Items->Count-1; im>=0; im-- )
                delete[] lib_PINS[im];
        delete[] lib_PINS;
        lib_PINS = NULL;
        }
if( cnt_footprints )
        try     {lib_PINS = new(std::nothrow) mPoint*[cnt_footprints]; }
        catch(std::bad_alloc){ ShowMessage("    Error memory!" ); }
//-----------
AnsiString cur_f;
int cur_n_pins;
int add;
int P=0;
Form1->lib_NAMES->Items->Clear();
if( cnt_footprints ) for (int index=i_FOOTPRINTS; index<i_BOARD; index++)
        {
        S = Form1->File->Items->operator [](index);
        if (S.LowerCase().SubString(1,4) == "name")
                {
                P = 0;
                add = 0;
                i = prob(S, 1);
                cur_f = ex_str(S,&i);
                Form1->lib_NAMES->Items->Add(cur_f);
                try     {lib_PINS[Form1->lib_NAMES->Count-1] = new(std::nothrow) mPoint[1];}
                catch(std::bad_alloc){ ShowMessage("    Error memory!" );}
                lib_PINS[Form1->lib_NAMES->Count-1][0].n_pins = 0;
                }
        else if (S.LowerCase().SubString(1,6) == "units:" )
                {
                i = prob(S, 1);
                if      (S.LowerCase().SubString(i,2) == "mm" ) UnitsFootPrint = 2;
                else if (S.LowerCase().SubString(i,2) == "mi" ) UnitsFootPrint = 0;
                else                                            UnitsFootPrint = 1;
                }
        else if (S.LowerCase().SubString(1,7) == "n_pins:" && Form1->lib_NAMES->Count)
                {
                i = prob(S, 1);
                cur_n_pins = ex_float_NM(S, &i, -1);
                if( cur_n_pins > 1 )
                        {
                        delete[] lib_PINS[Form1->lib_NAMES->Count-1];
                        try     {
                                lib_PINS[Form1->lib_NAMES->Count-1] = new(std::nothrow) mPoint[cur_n_pins];
                                }
                        catch(std::bad_alloc)
                                {
                                ShowMessage("    Error memory!" );
                                }
                        }
                lib_PINS[Form1->lib_NAMES->Count-1][0].n_pins = cur_n_pins;
                }
        else if (S.LowerCase().SubString(1,4) == "pin:")
                {
                P++;
                if( P > cur_n_pins )
                        ShowMessage(" num_pin > n_pins ");
                i = prob(S, 1);
                lib_PINS[Form1->lib_NAMES->Count-1][add].name = ex_str(S,&i);
                lib_PINS[Form1->lib_NAMES->Count-1][add].hole = ex_float_NM(S, &i, UnitsFootPrint);
                lib_PINS[Form1->lib_NAMES->Count-1][add].p.x =  ex_float_NM(S, &i, UnitsFootPrint);
                lib_PINS[Form1->lib_NAMES->Count-1][add].p.y =  ex_float_NM(S, &i, UnitsFootPrint);
                lib_PINS[Form1->lib_NAMES->Count-1][add].n_pins = cur_n_pins;
                if (!lib_PINS[Form1->lib_NAMES->Count-1][add].hole)
                        {
                        lib_PINS[Form1->lib_NAMES->Count-1][add].T = false;
                        lib_PINS[Form1->lib_NAMES->Count-1][add].B = false;
                        AnsiString next = Form1->File->Items->operator [](index+1);
                        if (next.LowerCase().SubString(1,1) == "t")     lib_PINS[Form1->lib_NAMES->Count-1][add].T = true;
                        else                                            lib_PINS[Form1->lib_NAMES->Count-1][add].B = true;
                        }
                add++;
                }
        }
//
AnsiString Ref;
AnsiString Shape;
long part_x;
long part_y;
bool part_sid;
int  part_an;
Form1->loc_NAMES->Items->Clear();
for (int index=i_PARTS; index<i_TEXTS; index++)
        {
        S = Form1->File->Items->operator [](index);
        if (S.SubString(1,4) == "part")
                {
                if (Ref.Length() && Shape.Length()) ReadFoot (Ref,Shape,part_sid,part_an,part_x,part_y);
                part_x = 0;
                part_y = 0;
                part_sid = 0;
                part_an = 0;
                Shape = "";
                i = prob(S,1);
                Ref = S.SubString(i,(S.Length()-i+1));
                }
        else if (S.SubString(1,5) == "shape")
                {
                i = prob(S,1);
                if (i)  Shape = ex_str(S,&i);
                }
        else if (S.SubString(1,3) == "pos")
                {
                i = prob(S,1);
                part_x =   ex_float_NM(S, &i, -1);
                part_y =   ex_float_NM(S, &i, -1);
                part_sid = ex_float_NM(S, &i, -1);
                part_an =  ex_float_NM(S, &i, -1);
                }
        else if (S.SubString(1,3) == "pin")
                {
                i = prob(S,2);
                AnsiString Pin = S.SubString(i,(S.Length()-i+1));
                Pin = Pin.Trim();
                Form1->Connected->Items->Add(Pin);
                }
        }
if (Ref.Length() && Shape.Length())
        ReadFoot (Ref,Shape,part_sid,part_an,part_x,part_y);
}








//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
DecimalSeparator = ',';
ini();
}







//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
AnsiString A;
AnsiString B;
AnsiString D;
AnsiString ref;
//
AnsiString OUTPUTFILE = ExtractFilePath(Application->ExeName);
ofstream EL ((OUTPUTFILE + "EditList.txt").c_str()) ;
for (int n=0; n<Form1->EditList->Count; n++)
        {
        A = Form1->EditList->Items->operator [](n);
        EL << A.c_str() << endl;
        }
EL.close();
Form1->EditList->SelectAll();
Form1->EditList->CopySelection(Form1->ChangeList);
//
for (int n=Form1->ChangeList->Count-1; n>=0; n--)
        {
        A = Form1->ChangeList->Items->operator [](n);
        i = 1;
        A = ex_str_WS(A, &i, ".");
        if (Form1->ChangeList->Items->IndexOf(A) == -1) Form1->ChangeList->Items->Add(A);
        }
//
Application->ProcessMessages();
//
if (Form1->Replace_original_Pcb_file->Checked)  OUTPUTFILE = Form1->OpenDialog1->FileName;
else                                            OUTPUTFILE += "EditPins.fpc";
ofstream NewFPC (OUTPUTFILE.c_str());
// HOLE
double tmp;
A = Form1->HoleDiameter_top->Text;
tmp = StrToFloat(Str_Float_Format(A));
float ValueHoleDiameter = tmp*1000000;
if(A.Length() == 0) ValueHoleDiameter = DEFAULT+1;
// TOP W
A = Form1->ShapeWidth_top->Text;
tmp = StrToFloat(Str_Float_Format(A));
float ValueShapeWidth_top = tmp*1000000;
if(A.Length() == 0) ValueShapeWidth_top = DEFAULT+1;
// TOP L
A = Form1->ShapeHeight_top->Text;
tmp = StrToFloat(Str_Float_Format(A));
float ValueShapeHeight_top = tmp*500000;
if(A.Length() == 0) ValueShapeHeight_top = DEFAULT+1;
// INN W
A = Form1->ShapeWidth_inner->Text;
tmp = StrToFloat(Str_Float_Format(A));
float ValueShapeWidth_inner = tmp*1000000.0;
if(A.Length() == 0) ValueShapeWidth_inner = DEFAULT+1;
// INN L
A = Form1->ShapeHeight_inner->Text;
tmp = StrToFloat(Str_Float_Format(A));
float ValueShapeHeight_inner = tmp*500000;
if(A.Length() == 0) ValueShapeHeight_inner = DEFAULT+1;
// BOT W
A = Form1->ShapeWidth_bottom->Text;
tmp = StrToFloat(Str_Float_Format(A));
float ValueShapeWidth_bottom = tmp*1000000;
if(A.Length() == 0) ValueShapeWidth_bottom = DEFAULT+1;
// BOT L
A = Form1->ShapeHeight_bottom->Text;
tmp = StrToFloat(Str_Float_Format(A));
float ValueShapeHeight_bottom = tmp*500000;
if(A.Length() == 0) ValueShapeHeight_bottom = DEFAULT+1;
// INN R
A = Form1->ShapeRadius_inner->Text;
tmp = StrToFloat(Str_Float_Format(A));
float ValueShapeRadius_inner = tmp*1000000;
if(A.Length() == 0) ValueShapeRadius_inner = DEFAULT+1;
// TOP R
A = Form1->ShapeRadius_top->Text;
tmp = StrToFloat(Str_Float_Format(A));
float ValueShapeRadius_top = tmp*1000000;
if(A.Length() == 0) ValueShapeRadius_top = DEFAULT+1;
// BOT R
A = Form1->ShapeRadius_bottom->Text;
tmp = StrToFloat(Str_Float_Format(A));
float ValueShapeRadius_bottom = tmp*1000000;
if(A.Length() == 0) ValueShapeRadius_bottom = DEFAULT+1;
//
int PinShapeTop = DEFAULT+1;
if      (Form1->none_top->Checked)      PinShapeTop = 0;
else if (Form1->round_top->Checked)     PinShapeTop = 1;
else if (Form1->rect_top->Checked)      PinShapeTop = 4;
else if (Form1->octagon_top->Checked)   PinShapeTop = 6;
//
int PinShapeInner = DEFAULT+1;
if      (Form1->none_inner->Checked)    PinShapeInner = 0;
else if (Form1->round_inner->Checked)   PinShapeInner = 1;
else if (Form1->rect_inner->Checked)    PinShapeInner = 4;
else if (Form1->octagon_inner->Checked) PinShapeInner = 6;
//
int PinShapeBottom = DEFAULT+1;
if      (Form1->none_bottom->Checked)   PinShapeBottom = 0;
else if (Form1->round_bottom->Checked)  PinShapeBottom = 1;
else if (Form1->rect_bottom->Checked)   PinShapeBottom = 4;
else if (Form1->octagon_bottom->Checked)PinShapeBottom = 6;
//
ClientPadStack.TypeTop =        PinShapeTop;
ClientPadStack.TypeInner =      PinShapeInner;
ClientPadStack.TypeBottom =     PinShapeBottom;
ClientPadStack.TopW =           ValueShapeWidth_top;
ClientPadStack.InnerW =         ValueShapeWidth_inner;
ClientPadStack.BottomW =        ValueShapeWidth_bottom;
ClientPadStack.TopH =           ValueShapeHeight_top;
ClientPadStack.InnerH =         ValueShapeHeight_inner;
ClientPadStack.BottomH =        ValueShapeHeight_bottom;
ClientPadStack.TopR =           ValueShapeRadius_top;
ClientPadStack.InnerR =         ValueShapeRadius_inner;
ClientPadStack.BottomR =        ValueShapeRadius_bottom;
double HDsave = ValueHoleDiameter;
//
Form1->ProgressBar1->Position = 0;
for(int x=0; x<Form1->File->Items->Count; x++)
        {
        A = Form1->File->Items->operator [](x);
        if (A.SubString(1,A.Length()) == "[footprints]")
                {
                NewFPC << A.c_str() << endl;
                AnsiString Ref;
                AnsiString Shape;
                int indexEND = Form1->File->Items->IndexOf("[nets]") ;
                int index = Form1->File->Items->IndexOf("[parts]") ;
                int MaxPerc = (indexEND - index)/99+1;
                if (index == -1 ) ShowMessage("    Fatal Error! String: [parts] not found!" );
                else while   (index < indexEND)
                        {
                        if (index%MaxPerc == 0 && Form1->ProgressBar1->Position < 100)
                                {
                                Form1->ProgressBar1->Position++;
                                Application->ProcessMessages();
                                }
                        B = Form1->File->Items->operator [](index);
                        index++;
                        if (B.SubString(1,4) == "part")
                                {
                                i = prob(B,1);
                                Ref = B.SubString(i,(B.Length()-i+1));
                                }
                        else if (B.SubString(1,5) == "shape")
                                {
                                i = prob(B,1);
                                Shape = ex_str(B,&i);
                                }
                        //
                        if (Ref.Length() && Shape.Length() )
                                {
                                if (Form1->ChangeList->Items->IndexOf(Ref) != -1)
                                        {
                                        int IndFoot = Form1->File->Items->IndexOf("name: \"" + Shape + "\"") ;
                                        NewFPC << endl;
                                        NewFPC << ("name: \"" + Shape + "_" + Ref + "\"").c_str() << endl;
                                        IndFoot++;
                                        int n_p_count = 0;
                                        int n_p_index = 0;
                                        while(1){
                                                D = Form1->File->Items->operator [](IndFoot);
                                                if      (D.SubString(1,4) == "name" || D.SubString(1,7) == "[board]")
                                                        {
                                                        if( n_p_index > 0 )
                                                                {
                                                                streampos mem_np = NewFPC.tellp();
                                                                AnsiString wrs = AnsiString("n_pins: ") + AnsiString(n_p_count);
                                                                NewFPC.seekp(n_p_index);
                                                                NewFPC << wrs.c_str();
                                                                NewFPC.seekp(mem_np);
                                                                n_p_index = 0;
                                                                }
                                                        break;
                                                        }
                                                else if (D.SubString(1,5) == "units")
                                                        {
                                                        NewFPC << D.c_str() << endl;
                                                        i = prob(D,1);
                                                        if (D.LowerCase().SubString(i,2) == "mi" )      UnitsFootPrint = 0;
                                                        else if (D.LowerCase().SubString(i,2) == "nm" ) UnitsFootPrint = 1;
                                                        else                                            UnitsFootPrint = 2;
                                                        }
                                                else if (D.SubString(1,6) == "n_pins")
                                                        {
                                                        streampos mem_np = NewFPC.tellp();
                                                        n_p_index = mem_np.operator long();
                                                        NewFPC << "                    " << endl;
                                                        }
                                                else if (D.SubString(1,3) == "pin")
                                                        {
                                                        ValueHoleDiameter =             HDsave;
                                                        ClientPadStack.TypeTop =        PinShapeTop;
                                                        ClientPadStack.TypeInner =      PinShapeInner;
                                                        ClientPadStack.TypeBottom =     PinShapeBottom;
                                                        ClientPadStack.TopW =           ValueShapeWidth_top;
                                                        ClientPadStack.InnerW =         ValueShapeWidth_inner;
                                                        ClientPadStack.BottomW =        ValueShapeWidth_bottom;
                                                        ClientPadStack.TopH =           ValueShapeHeight_top;
                                                        ClientPadStack.InnerH =         ValueShapeHeight_inner;
                                                        ClientPadStack.BottomH =        ValueShapeHeight_bottom;
                                                        ClientPadStack.TopR =           ValueShapeRadius_top;
                                                        ClientPadStack.InnerR =         ValueShapeRadius_inner;
                                                        ClientPadStack.BottomR =        ValueShapeRadius_bottom;
                                                        i = prob(D,1);
                                                        AnsiString PINNAME = ex_str(D,&i);
                                                        if (Form1->ChangeList->Items->IndexOf(Ref + "." + PINNAME) != -1)
                                                                {
                                                                i = prob(D,2);
                                                                double OldHole = ex_float_NM(D, &i, -1);
                                                                double OldX =    ex_float_NM(D, &i, -1);
                                                                double OldY =    ex_float_NM(D, &i, -1);
                                                                int OldAn =      ex_float_NM(D, &i, -1);
                                                                PadStack OldPadStack;
                                                                IndFoot = ReadPadStack( &OldPadStack, IndFoot );
                                                                if (UnitsFootPrint == 0)
                                                                        {
                                                                        if (ValueHoleDiameter <        DEFAULT) ValueHoleDiameter =            ValueHoleDiameter/25400;
                                                                        if (ClientPadStack.TopW <      DEFAULT) ClientPadStack.TopW =          ClientPadStack.TopW/25400;
                                                                        if (ClientPadStack.InnerW <    DEFAULT) ClientPadStack.InnerW =        ClientPadStack.InnerW/25400;
                                                                        if (ClientPadStack.BottomW <   DEFAULT) ClientPadStack.BottomW =       ClientPadStack.BottomW/25400;
                                                                        if (ClientPadStack.TopH <      DEFAULT) ClientPadStack.TopH =          ClientPadStack.TopH/25400;
                                                                        if (ClientPadStack.InnerH <    DEFAULT) ClientPadStack.InnerH =        ClientPadStack.InnerH/25400;
                                                                        if (ClientPadStack.BottomH <   DEFAULT) ClientPadStack.BottomH =       ClientPadStack.BottomH/25400;
                                                                        if (ClientPadStack.TopR <      DEFAULT) ClientPadStack.TopR =          ClientPadStack.TopR/25400;
                                                                        if (ClientPadStack.InnerR <    DEFAULT) ClientPadStack.InnerR =        ClientPadStack.InnerR/25400;
                                                                        if (ClientPadStack.BottomR <   DEFAULT) ClientPadStack.BottomR =       ClientPadStack.BottomR/25400;
                                                                        }
                                                                else if (UnitsFootPrint == 2)
                                                                        {
                                                                        if (ValueHoleDiameter <        DEFAULT) ValueHoleDiameter =            ValueHoleDiameter/1000000;
                                                                        if (ClientPadStack.TopW <      DEFAULT) ClientPadStack.TopW =          ClientPadStack.TopW/1000000;
                                                                        if (ClientPadStack.InnerW <    DEFAULT) ClientPadStack.InnerW =        ClientPadStack.InnerW/1000000;
                                                                        if (ClientPadStack.BottomW <   DEFAULT) ClientPadStack.BottomW =       ClientPadStack.BottomW/1000000;
                                                                        if (ClientPadStack.TopH <      DEFAULT) ClientPadStack.TopH =          ClientPadStack.TopH/1000000;
                                                                        if (ClientPadStack.InnerH <    DEFAULT) ClientPadStack.InnerH =        ClientPadStack.InnerH/1000000;
                                                                        if (ClientPadStack.BottomH <   DEFAULT) ClientPadStack.BottomH =       ClientPadStack.BottomH/1000000;
                                                                        if (ClientPadStack.TopR <      DEFAULT) ClientPadStack.TopR =          ClientPadStack.TopR/1000000;
                                                                        if (ClientPadStack.InnerR <    DEFAULT) ClientPadStack.InnerR =        ClientPadStack.InnerR/1000000;
                                                                        if (ClientPadStack.BottomR <   DEFAULT) ClientPadStack.BottomR =       ClientPadStack.BottomR/1000000;
                                                                        }
                                                                if (ClientPadStack.TypeTop >=   DEFAULT) ClientPadStack.TypeTop =       OldPadStack.TypeTop;
                                                                if (ClientPadStack.TypeInner >= DEFAULT) ClientPadStack.TypeInner =     OldPadStack.TypeInner;
                                                                if (ClientPadStack.TypeBottom >=DEFAULT) ClientPadStack.TypeBottom =    OldPadStack.TypeBottom;
                                                                if (ValueHoleDiameter >=        DEFAULT) ValueHoleDiameter =            OldHole;
                                                                if (ClientPadStack.TopW >=      DEFAULT) ClientPadStack.TopW =          OldPadStack.TopW;
                                                                if (ClientPadStack.InnerW >=    DEFAULT) ClientPadStack.InnerW =        OldPadStack.InnerW;
                                                                if (ClientPadStack.BottomW >=   DEFAULT) ClientPadStack.BottomW =       OldPadStack.BottomW;
                                                                if (ClientPadStack.TopH >=      DEFAULT) ClientPadStack.TopH =          OldPadStack.TopH;
                                                                if (ClientPadStack.InnerH >=    DEFAULT) ClientPadStack.InnerH =        OldPadStack.InnerH;
                                                                if (ClientPadStack.BottomH >=   DEFAULT) ClientPadStack.BottomH =       OldPadStack.BottomH;
                                                                if (ClientPadStack.TopR >=      DEFAULT) ClientPadStack.TopR =          OldPadStack.TopR;
                                                                if (ClientPadStack.InnerR >=    DEFAULT) ClientPadStack.InnerR =        OldPadStack.InnerR;
                                                                if (ClientPadStack.BottomR >=   DEFAULT) ClientPadStack.BottomR =       OldPadStack.BottomR;
                                                                // restore mask, paste
                                                                ClientPadStack.TypeTopMask =       OldPadStack.TypeTopMask;
                                                                ClientPadStack.TypeBottomMask =    OldPadStack.TypeBottomMask;
                                                                ClientPadStack.TypeTopPaste =      OldPadStack.TypeTopPaste;
                                                                ClientPadStack.TypeBottomPaste =   OldPadStack.TypeBottomPaste;
                                                                //
                                                                ClientPadStack.MaskTopW =          OldPadStack.MaskTopW;
                                                                ClientPadStack.MaskTopH =          OldPadStack.MaskTopH;
                                                                ClientPadStack.MaskTopR =          OldPadStack.MaskTopR;
                                                                ClientPadStack.PasteTopW =         OldPadStack.PasteTopW;
                                                                ClientPadStack.PasteTopH =         OldPadStack.PasteTopH;
                                                                ClientPadStack.PasteTopR =         OldPadStack.PasteTopR;
                                                                ClientPadStack.MaskBottomW =       OldPadStack.MaskBottomW;
                                                                ClientPadStack.MaskBottomH =       OldPadStack.MaskBottomH;
                                                                ClientPadStack.MaskBottomR =       OldPadStack.MaskBottomR;
                                                                ClientPadStack.PasteBottomW =      OldPadStack.PasteBottomW;
                                                                ClientPadStack.PasteBottomH =      OldPadStack.PasteBottomH;
                                                                ClientPadStack.PasteBottomR =      OldPadStack.PasteBottomR;
                                                                //
                                                                if (Form1->Swell_top->Checked && ClientPadStack.TopW < DEFAULT)        ClientPadStack.TopW += OldPadStack.TopW;
                                                                if (Form1->Swell_top->Checked && ClientPadStack.TopH < DEFAULT)        ClientPadStack.TopH += OldPadStack.TopH;
                                                                if (Form1->Swell_top->Checked && ClientPadStack.TopR < DEFAULT)        ClientPadStack.TopR += OldPadStack.TopR;
                                                                if (Form1->Swell_bottom->Checked && ClientPadStack.BottomW < DEFAULT)  ClientPadStack.BottomW += OldPadStack.BottomW;
                                                                if (Form1->Swell_bottom->Checked && ClientPadStack.BottomH < DEFAULT)  ClientPadStack.BottomH += OldPadStack.BottomH;
                                                                if (Form1->Swell_bottom->Checked && ClientPadStack.BottomR < DEFAULT)  ClientPadStack.BottomR += OldPadStack.BottomR;
                                                                if (Form1->Swell_inner->Checked && ClientPadStack.InnerW < DEFAULT)    ClientPadStack.InnerW += OldPadStack.InnerW;
                                                                if (Form1->Swell_inner->Checked && ClientPadStack.InnerH < DEFAULT)    ClientPadStack.InnerH += OldPadStack.InnerH;
                                                                if (Form1->Swell_inner->Checked && ClientPadStack.InnerR < DEFAULT)    ClientPadStack.InnerR += OldPadStack.InnerR;
                                                                //
                                                                ClientPadStack.TopW     = MAX(ClientPadStack.TopW ,     0);
                                                                ClientPadStack.TopH     = MAX(ClientPadStack.TopH ,     0);
                                                                ClientPadStack.TopR     = MAX(ClientPadStack.TopR ,     0);
                                                                ClientPadStack.BottomW  = MAX(ClientPadStack.BottomW ,  0);
                                                                ClientPadStack.BottomH  = MAX(ClientPadStack.BottomH ,  0);
                                                                ClientPadStack.BottomR  = MAX(ClientPadStack.BottomR ,  0);
                                                                ClientPadStack.InnerW   = MAX(ClientPadStack.InnerW ,   0);
                                                                ClientPadStack.InnerH   = MAX(ClientPadStack.InnerH ,   0);
                                                                ClientPadStack.InnerR   = MAX(ClientPadStack.InnerR ,   0);
                                                                //
                                                                if (    (ValueHoleDiameter < byZero || ValueHoleDiameter >= DEFAULT) &&
                                                                        (ClientPadStack.TypeTop < byZero || ClientPadStack.TypeTop >= DEFAULT || ClientPadStack.TopW >= DEFAULT || ClientPadStack.TopW < byZero ) &&
                                                                        (ClientPadStack.TypeInner < byZero || ClientPadStack.TypeInner >= DEFAULT || ClientPadStack.InnerW >= DEFAULT || ClientPadStack.InnerW < byZero ) &&
                                                                        (ClientPadStack.TypeBottom < byZero || ClientPadStack.TypeBottom >= DEFAULT || ClientPadStack.BottomW >= DEFAULT || ClientPadStack.BottomW < byZero ) &&
                                                                        (ClientPadStack.TypeTopMask >= DEFAULT) &&
                                                                        (ClientPadStack.TypeBottomMask >= DEFAULT) &&
                                                                        (ClientPadStack.TypeTopPaste >= DEFAULT) &&
                                                                        (ClientPadStack.TypeBottomPaste >= DEFAULT) )
                                                                        {
                                                                        //no writing
                                                                        if( Form1->Connected->Items->IndexOf(Ref + "." + PINNAME) != -1 )
                                                                                {
                                                                                ShowMessage("Unable to perform surgery. You are trying to remove a pin that is connected to net. Aborted..");
                                                                                NewFPC.close();
                                                                                Form1->ProgressBar1->Position = 0;
                                                                                Form1->ChangeList->Clear();
                                                                                return;
                                                                                }
                                                                        }
                                                                else    {
                                                                        streampos mem_pos = NewFPC.tellp();
                                                                        //writing top, bottom, inner, mask,paste
                                                                        int check_hole = 0;
                                                                        if(ValueHoleDiameter > byZero && ValueHoleDiameter < DEFAULT)
                                                                                check_hole = 1;
                                                                        NewFPC << "pin: \"";
                                                                        NewFPC << PINNAME.c_str();
                                                                        NewFPC << "\" ";
                                                                        if (UnitsFootPrint == 1)        NewFPC << (long)ValueHoleDiameter;
                                                                        else                            NewFPC << StringReplace(FormatFloat("0.000", ValueHoleDiameter),",",".",TReplaceFlags()<<rfReplaceAll).c_str();
                                                                        NewFPC << " ";
                                                                        if (UnitsFootPrint == 1)        NewFPC << (long)OldX;
                                                                        else                            NewFPC << StringReplace(FormatFloat("0.000",OldX),",",".",TReplaceFlags()<<rfReplaceAll).c_str();
                                                                        NewFPC << " ";
                                                                        if (UnitsFootPrint == 1)        NewFPC << (long)OldY;
                                                                        else                            NewFPC << StringReplace(FormatFloat("0.000",OldY),",",".",TReplaceFlags()<<rfReplaceAll).c_str();
                                                                        NewFPC << " ";
                                                                        NewFPC << OldAn;
                                                                        NewFPC << endl;
                                                                        //
                                                                        // TOP
                                                                        int pad_was_made = 0;
                                                                        if( ClientPadStack.TypeTop < DEFAULT && (ClientPadStack.TypeTop > 0||check_hole) && ClientPadStack.TopW < DEFAULT )
                                                                                {
                                                                                pad_was_made++;
                                                                                //writing top, topmask, toppaste
                                                                                if (ClientPadStack.TopH >= DEFAULT || ClientPadStack.TopH < byZero)
                                                                                        ClientPadStack.TopH = ClientPadStack.TopW/2;
                                                                                if (ClientPadStack.TopR >= DEFAULT || ClientPadStack.TopR < byZero)
                                                                                        ClientPadStack.TopR = 0;
                                                                                NewFPC << "top_pad: ";
                                                                                NewFPC << ClientPadStack.TypeTop;
                                                                                NewFPC << " ";
                                                                                if (UnitsFootPrint == 1)        NewFPC << (long)ClientPadStack.TopW;
                                                                                else                            NewFPC << StringReplace(FormatFloat("0.000",ClientPadStack.TopW),",",".",TReplaceFlags()<<rfReplaceAll).c_str();
                                                                                NewFPC << " ";
                                                                                if (UnitsFootPrint == 1)        NewFPC << (long)ClientPadStack.TopH;
                                                                                else                            NewFPC << StringReplace(FormatFloat("0.000",ClientPadStack.TopH),",",".",TReplaceFlags()<<rfReplaceAll).c_str();
                                                                                NewFPC << " ";
                                                                                if (UnitsFootPrint == 1)        NewFPC << (long)ClientPadStack.TopH;
                                                                                else                            NewFPC << StringReplace(FormatFloat("0.000",ClientPadStack.TopH),",",".",TReplaceFlags()<<rfReplaceAll).c_str();
                                                                                NewFPC << " ";
                                                                                if (UnitsFootPrint == 1)        NewFPC << (long)ClientPadStack.TopR;
                                                                                else                            NewFPC << StringReplace(FormatFloat("0.000",ClientPadStack.TopR),",",".",TReplaceFlags()<<rfReplaceAll).c_str();
                                                                                NewFPC << " ";
                                                                                if (Form1->ThermalCheck->Checked)       NewFPC << TT_T;
                                                                                else if (Form1->NoThrmlCheck->Checked)  NewFPC << TT_NT;
                                                                                else if (OldPadStack.TopThrml >= DEFAULT) NewFPC << "0";
                                                                                else    NewFPC << OldPadStack.TopThrml;
                                                                                NewFPC << endl;
                                                                                }
                                                                        //MASK TOP
                                                                        if (Form1->MaskOff->Checked || ClientPadStack.TypeTopMask == 0)
                                                                                NewFPC << "top_mask: 0 0 0 0 0" << endl;
                                                                        else if( ClientPadStack.TypeTopMask < DEFAULT && ClientPadStack.MaskTopW < DEFAULT )
                                                                                {
                                                                                pad_was_made++;
                                                                                if (ClientPadStack.MaskTopH >= DEFAULT || ClientPadStack.MaskTopH < byZero)
                                                                                        ClientPadStack.MaskTopH = ClientPadStack.MaskTopW/2;
                                                                                if (ClientPadStack.MaskTopR >= DEFAULT || ClientPadStack.MaskTopR < byZero)
                                                                                        ClientPadStack.MaskTopR = 0;
                                                                                NewFPC << "top_mask: ";
                                                                                NewFPC << ClientPadStack.TypeTopMask;
                                                                                NewFPC << " ";
                                                                                if (UnitsFootPrint == 1)        NewFPC << (long)ClientPadStack.MaskTopW;
                                                                                else                            NewFPC << StringReplace(FormatFloat("0.000",ClientPadStack.MaskTopW),",",".",TReplaceFlags()<<rfReplaceAll).c_str();
                                                                                NewFPC << " ";
                                                                                if (UnitsFootPrint == 1)        NewFPC << (long)ClientPadStack.MaskTopH;
                                                                                else                            NewFPC << StringReplace(FormatFloat("0.000",ClientPadStack.MaskTopH),",",".",TReplaceFlags()<<rfReplaceAll).c_str();
                                                                                NewFPC << " ";
                                                                                if (UnitsFootPrint == 1)        NewFPC << (long)ClientPadStack.MaskTopH;
                                                                                else                            NewFPC << StringReplace(FormatFloat("0.000",ClientPadStack.MaskTopH),",",".",TReplaceFlags()<<rfReplaceAll).c_str();
                                                                                NewFPC << " ";
                                                                                if (UnitsFootPrint == 1)        NewFPC << (long)ClientPadStack.MaskTopR;
                                                                                else                            NewFPC << StringReplace(FormatFloat("0.000",ClientPadStack.MaskTopR),",",".",TReplaceFlags()<<rfReplaceAll).c_str();
                                                                                NewFPC << endl;
                                                                                }
                                                                        //PASTE TOP
                                                                        if (Form1->PasteOff->Checked || ClientPadStack.TypeTopPaste == 0)
                                                                                NewFPC << "top_paste: 0 0 0 0 0" << endl;
                                                                        else if( ClientPadStack.TypeTopPaste < DEFAULT && ClientPadStack.PasteTopW < DEFAULT )
                                                                                {
                                                                                pad_was_made++;
                                                                                if (ClientPadStack.PasteTopH >= DEFAULT || ClientPadStack.PasteTopH < byZero)
                                                                                        ClientPadStack.PasteTopH = ClientPadStack.PasteTopW/2;
                                                                                if (ClientPadStack.PasteTopR >= DEFAULT || ClientPadStack.PasteTopR < byZero)
                                                                                        ClientPadStack.PasteTopR = 0;
                                                                                NewFPC << "top_paste: ";
                                                                                NewFPC << ClientPadStack.TypeTopPaste;
                                                                                NewFPC << " ";
                                                                                if (UnitsFootPrint == 1)        NewFPC << (long)ClientPadStack.PasteTopW;
                                                                                else                            NewFPC << StringReplace(FormatFloat("0.000",ClientPadStack.PasteTopW),",",".",TReplaceFlags()<<rfReplaceAll).c_str();
                                                                                NewFPC << " ";
                                                                                if (UnitsFootPrint == 1)        NewFPC << (long)ClientPadStack.PasteTopH;
                                                                                else                            NewFPC << StringReplace(FormatFloat("0.000",ClientPadStack.PasteTopH),",",".",TReplaceFlags()<<rfReplaceAll).c_str();
                                                                                NewFPC << " ";
                                                                                if (UnitsFootPrint == 1)        NewFPC << (long)ClientPadStack.PasteTopH;
                                                                                else                            NewFPC << StringReplace(FormatFloat("0.000",ClientPadStack.PasteTopH),",",".",TReplaceFlags()<<rfReplaceAll).c_str();
                                                                                NewFPC << " ";
                                                                                if (UnitsFootPrint == 1)        NewFPC << (long)ClientPadStack.PasteTopR;
                                                                                else                            NewFPC << StringReplace(FormatFloat("0.000",ClientPadStack.PasteTopR),",",".",TReplaceFlags()<<rfReplaceAll).c_str();
                                                                                NewFPC << endl;
                                                                                }
                                                                        // INNER
                                                                        if (    ClientPadStack.TypeInner < DEFAULT &&
                                                                                ClientPadStack.InnerW < DEFAULT  &&
                                                                                check_hole)
                                                                                {
                                                                                if( ClientPadStack.TypeInner ||
                                                                                    ClientPadStack.InnerW > byZero ||
                                                                                    Form1->ThermalCheck->Checked ||
                                                                                    Form1->NoThrmlCheck->Checked ||
                                                                                    (OldPadStack.InnerThrml < DEFAULT && OldPadStack.InnerThrml ))
                                                                                        {
                                                                                        //writing inner
                                                                                        if (ClientPadStack.InnerH >= DEFAULT || ClientPadStack.InnerH < byZero)
                                                                                                ClientPadStack.InnerH = ClientPadStack.InnerW/2;
                                                                                        if (ClientPadStack.InnerR >= DEFAULT || ClientPadStack.InnerR < byZero)
                                                                                                ClientPadStack.InnerR = 0;
                                                                                        NewFPC << "inner_pad: ";
                                                                                        NewFPC << ClientPadStack.TypeInner;
                                                                                        NewFPC << " ";
                                                                                        if (UnitsFootPrint == 1)        NewFPC << (long)ClientPadStack.InnerW;
                                                                                        else                            NewFPC << StringReplace(FormatFloat("0.000",ClientPadStack.InnerW),",",".",TReplaceFlags()<<rfReplaceAll).c_str();
                                                                                        NewFPC << " ";
                                                                                        if (UnitsFootPrint == 1)        NewFPC << (long)ClientPadStack.InnerH;
                                                                                        else                            NewFPC << StringReplace(FormatFloat("0.000",ClientPadStack.InnerH),",",".",TReplaceFlags()<<rfReplaceAll).c_str();
                                                                                        NewFPC << " ";
                                                                                        if (UnitsFootPrint == 1)        NewFPC << (long)ClientPadStack.InnerH;
                                                                                        else                            NewFPC << StringReplace(FormatFloat("0.000",ClientPadStack.InnerH),",",".",TReplaceFlags()<<rfReplaceAll).c_str();
                                                                                        NewFPC << " ";
                                                                                        if (UnitsFootPrint == 1)        NewFPC << (long)ClientPadStack.InnerR;
                                                                                        else                            NewFPC << StringReplace(FormatFloat("0.000",ClientPadStack.InnerR),",",".",TReplaceFlags()<<rfReplaceAll).c_str();
                                                                                        NewFPC << " ";
                                                                                        if (Form1->ThermalCheck->Checked)       NewFPC << TT_T;
                                                                                        else if (Form1->NoThrmlCheck->Checked)  NewFPC << TT_NT;
                                                                                        else if (OldPadStack.InnerThrml >= DEFAULT) NewFPC << "0";
                                                                                        else    NewFPC << OldPadStack.InnerThrml;
                                                                                        NewFPC << endl;
                                                                                        }
                                                                                }
                                                                        else    {
                                                                                int test = 0;
                                                                                }
                                                                        // BOTTOM
                                                                        if( ClientPadStack.TypeBottom < DEFAULT && (ClientPadStack.TypeBottom > 0||check_hole) && ClientPadStack.BottomW < DEFAULT  )
                                                                                {
                                                                                pad_was_made++;
                                                                                if (ClientPadStack.BottomH >= DEFAULT || ClientPadStack.BottomH < byZero)
                                                                                        ClientPadStack.BottomH = ClientPadStack.BottomW/2;
                                                                                if (ClientPadStack.BottomR >= DEFAULT || ClientPadStack.BottomR < byZero)
                                                                                        ClientPadStack.BottomR = 0;
                                                                                NewFPC << "bottom_pad: ";
                                                                                NewFPC << ClientPadStack.TypeBottom;
                                                                                NewFPC << " ";
                                                                                if (UnitsFootPrint == 1)        NewFPC << (long)ClientPadStack.BottomW;
                                                                                else                            NewFPC << StringReplace(FormatFloat("0.000",ClientPadStack.BottomW),",",".",TReplaceFlags()<<rfReplaceAll).c_str();
                                                                                NewFPC << " ";
                                                                                if (UnitsFootPrint == 1)        NewFPC << (long)ClientPadStack.BottomH;
                                                                                else                            NewFPC << StringReplace(FormatFloat("0.000",ClientPadStack.BottomH),",",".",TReplaceFlags()<<rfReplaceAll).c_str();
                                                                                NewFPC << " ";
                                                                                if (UnitsFootPrint == 1)        NewFPC << (long)ClientPadStack.BottomH;
                                                                                else                            NewFPC << StringReplace(FormatFloat("0.000",ClientPadStack.BottomH),",",".",TReplaceFlags()<<rfReplaceAll).c_str();
                                                                                NewFPC << " ";
                                                                                if (UnitsFootPrint == 1)        NewFPC << (long)ClientPadStack.BottomR;
                                                                                else                            NewFPC << StringReplace(FormatFloat("0.000",ClientPadStack.BottomR),",",".",TReplaceFlags()<<rfReplaceAll).c_str();
                                                                                NewFPC << " ";
                                                                                if (Form1->ThermalCheck->Checked)       NewFPC << TT_T;
                                                                                else if (Form1->NoThrmlCheck->Checked)  NewFPC << TT_NT;
                                                                                else if (OldPadStack.BottomThrml >= DEFAULT) NewFPC << "0";
                                                                                else    NewFPC << OldPadStack.BottomThrml;
                                                                                NewFPC << endl;
                                                                                }
                                                                        // MASK BOT
                                                                        if (Form1->MaskOff->Checked || ClientPadStack.TypeBottomMask == 0)
                                                                                NewFPC << "bottom_mask: 0 0 0 0 0" << endl;
                                                                        else if( ClientPadStack.TypeBottomMask < DEFAULT && ClientPadStack.MaskBottomW < DEFAULT )
                                                                                {
                                                                                pad_was_made++;
                                                                                if (ClientPadStack.MaskBottomH >= DEFAULT || ClientPadStack.MaskBottomH < byZero)
                                                                                        ClientPadStack.MaskBottomH = ClientPadStack.MaskBottomW/2;
                                                                                if (ClientPadStack.MaskBottomR >= DEFAULT || ClientPadStack.MaskBottomR < byZero)
                                                                                        ClientPadStack.MaskBottomR = 0;
                                                                                NewFPC << "bottom_mask: ";
                                                                                NewFPC << ClientPadStack.TypeBottomMask;
                                                                                NewFPC << " ";
                                                                                if (UnitsFootPrint == 1)        NewFPC << (long)ClientPadStack.MaskBottomW;
                                                                                else                            NewFPC << StringReplace(FormatFloat("0.000",ClientPadStack.MaskBottomW),",",".",TReplaceFlags()<<rfReplaceAll).c_str();
                                                                                NewFPC << " ";
                                                                                if (UnitsFootPrint == 1)        NewFPC << (long)ClientPadStack.MaskBottomH;
                                                                                else                            NewFPC << StringReplace(FormatFloat("0.000",ClientPadStack.MaskBottomH),",",".",TReplaceFlags()<<rfReplaceAll).c_str();
                                                                                NewFPC << " ";
                                                                                if (UnitsFootPrint == 1)        NewFPC << (long)ClientPadStack.MaskBottomH;
                                                                                else                            NewFPC << StringReplace(FormatFloat("0.000",ClientPadStack.MaskBottomH),",",".",TReplaceFlags()<<rfReplaceAll).c_str();
                                                                                NewFPC << " ";
                                                                                if (UnitsFootPrint == 1)        NewFPC << (long)ClientPadStack.MaskBottomR;
                                                                                else                            NewFPC << StringReplace(FormatFloat("0.000",ClientPadStack.MaskBottomR),",",".",TReplaceFlags()<<rfReplaceAll).c_str();
                                                                                NewFPC << endl;
                                                                                }
                                                                        // PASTE BOT
                                                                        if (Form1->PasteOff->Checked || ClientPadStack.TypeBottomPaste == 0)
                                                                                NewFPC << "bottom_paste: 0 0 0 0 0" << endl;
                                                                        else if( ClientPadStack.TypeBottomPaste < DEFAULT && ClientPadStack.PasteBottomW < DEFAULT )
                                                                                {
                                                                                pad_was_made++;
                                                                                if (ClientPadStack.PasteBottomH >= DEFAULT || ClientPadStack.PasteBottomH < byZero)
                                                                                        ClientPadStack.PasteBottomH = ClientPadStack.PasteBottomW/2;
                                                                                if (ClientPadStack.PasteBottomR >= DEFAULT || ClientPadStack.PasteBottomR < byZero)
                                                                                        ClientPadStack.PasteBottomR = 0;
                                                                                NewFPC << "bottom_paste: ";
                                                                                NewFPC << ClientPadStack.TypeBottomPaste;
                                                                                NewFPC << " ";
                                                                                if (UnitsFootPrint == 1)        NewFPC << (long)ClientPadStack.PasteBottomW;
                                                                                else                            NewFPC << StringReplace(FormatFloat("0.000",ClientPadStack.PasteBottomW),",",".",TReplaceFlags()<<rfReplaceAll).c_str();
                                                                                NewFPC << " ";
                                                                                if (UnitsFootPrint == 1)        NewFPC << (long)ClientPadStack.PasteBottomH;
                                                                                else                            NewFPC << StringReplace(FormatFloat("0.000",ClientPadStack.PasteBottomH),",",".",TReplaceFlags()<<rfReplaceAll).c_str();
                                                                                NewFPC << " ";
                                                                                if (UnitsFootPrint == 1)        NewFPC << (long)ClientPadStack.PasteBottomH;
                                                                                else                            NewFPC << StringReplace(FormatFloat("0.000",ClientPadStack.PasteBottomH),",",".",TReplaceFlags()<<rfReplaceAll).c_str();
                                                                                NewFPC << " ";
                                                                                if (UnitsFootPrint == 1)        NewFPC << (long)ClientPadStack.PasteBottomR;
                                                                                else                            NewFPC << StringReplace(FormatFloat("0.000",ClientPadStack.PasteBottomR),",",".",TReplaceFlags()<<rfReplaceAll).c_str();
                                                                                NewFPC << endl;
                                                                                }
                                                                        if( check_hole == 0 && pad_was_made == 0 )
                                                                                {
                                                                                if( Form1->Connected->Items->IndexOf(Ref + "." + PINNAME) != -1 )
                                                                                        {
                                                                                        ShowMessage("Unable to perform surgery. You are trying to remove a pin that is connected to net. Aborted..");
                                                                                        NewFPC.close();
                                                                                        Form1->ProgressBar1->Position = 0;
                                                                                        Form1->ChangeList->Clear();
                                                                                        return;
                                                                                        }
                                                                                NewFPC.seekp(mem_pos);
                                                                                }
                                                                        else    n_p_count++;
                                                                        }
                                                                }
                                                        else    {
                                                                NewFPC << D.c_str() << endl;
                                                                n_p_count++;
                                                                }
                                                        }
                                                else    NewFPC << D.c_str() << endl;
                                                IndFoot++;
                                                }
                                        }
                                Ref = "";
                                Shape = "";
                                }
                        }
                }
        else if (A.SubString(1,5) == "part:")
                {
                i = prob(A,1);
                ref = A.SubString(i,(A.Length()-i+1));
                NewFPC << A.c_str() << endl;
                }
        else if (A.SubString(1,5) == "shape")
                {
                i = prob(A,1);
                AnsiString Sh = ex_str(A,&i);
                if (Form1->ChangeList->Items->IndexOf(ref) != -1 && Sh.Length())    A = "shape: \"" + Sh + "_" + ref + "\"";
                NewFPC << A.c_str() << endl;
                }
        else    NewFPC << A.c_str() << endl;
        }
NewFPC.close();
Application->ProcessMessages();
Sleep(500);
//
//-------------������ ------------
//
SHELLEXECUTEINFO info = {0};
AnsiString fn = ExtractFilePath(Application->ExeName);
fn.SetLength(fn.Length()-1);
fn = ExtractFilePath(fn);
fn.SetLength(fn.Length()-1);
fn = ExtractFilePath(fn) + "freepcb.exe";
AnsiString FN = ("\""+fn+"\"");
AnsiString ps = OUTPUTFILE;
AnsiString PS = ("\""+ps+"\"");
info.cbSize = sizeof(SHELLEXECUTEINFO);
info.fMask = NULL;
info.hwnd = NULL;
info.lpVerb = NULL;
info.lpFile = FN.c_str();
info.lpParameters = PS.c_str();
info.lpDirectory = NULL;
info.nShow = SW_SHOW;//SW_MAXIMIZE; //SW_HIDE
info.hInstApp = NULL;
int INF = ShellExecuteEx(&info);
if( INF == 0 )
        ShowMessage("Something went wrong .. If the problem persists more than once, report it to support at freepcb.dev");
//
Form1->ProgressBar1->Position = 0;
Form1->ChangeList->Clear();
}














//---------------------------------------------------------------------------

void __fastcall TForm1::Swell_topClick(TObject *Sender)
{
if (Swell_top->Checked)
        {
        if (Form1->none_top->Checked) Form1->NoChange_top->Checked = true;
        Form1->none_top->Enabled = false;
        }
else    {
        Form1->none_top->Enabled = true;
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Swell_innerClick(TObject *Sender)
{
if (Swell_inner->Checked)
        {
        if (Form1->none_inner->Checked) Form1->NoChange_inner->Checked = true;
        Form1->none_inner->Enabled = false;
        }
else    {
        Form1->none_inner->Enabled = true;
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Swell_bottomClick(TObject *Sender)
{
if (Swell_bottom->Checked)
        {
        if (Form1->none_bottom->Checked) Form1->NoChange_bottom->Checked = true;
        Form1->none_bottom->Enabled = false;
        }
else    {
        Form1->none_bottom->Enabled = true;
        }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button2Click(TObject *Sender)
{
AnsiString A;
for (int k=0; k<Form1->SMTpins->Items->Count; k++)
        {
        A = Form1->SMTpins->Items->operator [](k);
        Form1->AllPins->Items->Delete(Form1->AllPins->Items->IndexOf(A));
        }
Application->ProcessMessages();
Form1->AllPins->SelectAll();
Application->ProcessMessages();
Form1->SMTpins->SelectAll();
Application->ProcessMessages();
Form1->SMTpins->CopySelection(Form1->AllPins);
Application->ProcessMessages();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
Form1->ChangeList->Clear();
Form1->AllPins->MoveSelection(Form1->ChangeList);
Form1->AllPins->SelectAll();
Form1->ChangeList->SelectAll();
Form1->ChangeList->CopySelection(Form1->AllPins);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
Form1->AllPins->MoveSelection(Form1->EditList);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
Form1->EditList->MoveSelection(Form1->AllPins);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button6Click(TObject *Sender)
{
AnsiString A;
for (int k=0; k<Form1->Connected->Items->Count; k++)
        {
        A = Form1->Connected->Items->operator [](k);
        i = Form1->AllPins->Items->IndexOf(A);
        while( i >= 0 )
                {
                Form1->AllPins->Items->Delete(i);
                i = Form1->AllPins->Items->IndexOf(A);
                }
        }
Application->ProcessMessages();
Form1->AllPins->SelectAll();
Application->ProcessMessages();
Form1->Connected->SelectAll();
Application->ProcessMessages();
Form1->Connected->CopySelection(Form1->AllPins);
Application->ProcessMessages();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button7Click(TObject *Sender)
{
Form1->ChangeList->Clear();
Form1->EditList->MoveSelection(Form1->ChangeList);
Form1->EditList->SelectAll();
Form1->ChangeList->SelectAll();
Form1->ChangeList->CopySelection(Form1->EditList);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit1Change(TObject *Sender)
{
Form1->AllPins->ClearSelection();
AnsiString S = Form1->Edit1->Text;
if (!S.Length()) return;
AnsiString T;
for (int m=0; m<Form1->AllPins->Count; m++)
        {
        T = Form1->AllPins->Items->operator [](m);
        if (T.UpperCase().SubString(1,S.Length()) == S.UpperCase().SubString(1,S.Length()))
                {
                Form1->AllPins->ItemIndex = m;
                Form1->AllPins->Selected[m] = true;
                Form1->AllPins->Refresh();
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit1KeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if (Key == VK_RETURN) Form1->AllPins->MoveSelection(Form1->EditList);        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
AnsiString A;
AnsiString OUTPUTFILE = ExtractFilePath(Application->ExeName);
ofstream EL ((OUTPUTFILE + "EditList.txt").c_str()) ;
for (int n=0; n<Form1->EditList->Count; n++)
        {
        A = Form1->EditList->Items->operator [](n);
        EL << A.c_str() << endl;
        }
EL.close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ThermalCheckClick(TObject *Sender)
{
Form1->NoThrmlCheck->Checked = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::NoThrmlCheckClick(TObject *Sender)
{
Form1->ThermalCheck->Checked = false;
}
//---------------------------------------------------------------------------






//---------------------------------------------------------------------------
double Angle (double dx, double dy, double x0, double y0)
        {
        double ANG_s;
        dx = dx - x0;
        dy = dy - y0;
        if (ABS(dx) < BY_ZERO)
                {
                if (dy > BY_ZERO)       ANG_s = 90;
                else if (dy < -BY_ZERO) ANG_s = 270;
                else                    return 0;
                }
        else
                {
                double Dxy = dy/dx;
                ANG_s = (atan(Dxy))*(double)180/(double)M_PI;
                if ((dx > 0)&&(dy < 0)) ANG_s = 360 + ANG_s;
                if (dx < 0) ANG_s = 180 + ANG_s;
                }
        return ANG_s;
        }
//---------------------------------------------------------------------------






//---------------------------------------------------------------------------
//---------- PointAreaInside
bool point_area_inside (double X, double Y, int CntLnsArea )
{
double st_angle =   Angle(LinesArea[0].X1, LinesArea[0].Y1, X, Y);
double back_angle = st_angle;
double d;
double vx;
double vy;
double angle;
double diff_angle = 0;
if      (diff_angle < -180) diff_angle += 360;
else if (diff_angle > 180)  diff_angle -= 360;
double SUM = 0;
for (int q=1; q<=CntLnsArea; q++)
        {
        if (LinesArea[q].n_cont > LinesArea[q-1].n_cont)
                {
                diff_angle = st_angle - back_angle;
                if      (diff_angle < -180) diff_angle += 360;
                else if (diff_angle > 180)  diff_angle -= 360;
                SUM += diff_angle;
                if (LinesArea[q-1].n_cont)
                        {
                        if (ABS(SUM) > 180) return false;
                        }
                else    {
                        if (ABS(SUM) < -180) return false;
                        }
                if ( q == CntLnsArea )
                        return true;
                st_angle = Angle(LinesArea[q].X1, LinesArea[q].Y1, X, Y);
                back_angle = st_angle;
                SUM = 0;
                }
        angle = Angle(LinesArea[q].X1, LinesArea[q].Y1, X, Y);
        diff_angle = angle - back_angle;
        if      (diff_angle < -180) diff_angle += 360;
        else if (diff_angle > 180)  diff_angle -= 360;
        SUM += diff_angle;
        back_angle = angle;
        }
return true;
}
//---------------------------------------------------------------------------





//---------------------------------------------------------------------------
int r_area(int start, int n_cor)
        {
        AnsiString A;
        int arc;
        int end;
        float fx,fy;
        if (LinesArea) delete[] LinesArea;
        try     {LinesArea = new(std::nothrow) Line[n_cor+1];}
        catch(std::bad_alloc){ShowMessage("    Error memory: Line[" + AnsiString(n_cor) + "]!" );}
        for (int a = 0; a < n_cor; a++)
                {
                A = Form1->File->Items->operator [](start);
                i = prob(A,2);
                LinesArea[a].X1 = ex_float_NM(A,&i,-1);
                LinesArea[a].Y1 = ex_float_NM(A,&i,-1);
                //arc =        (int)ex_float_NM(A,&i,-1);
                if (a)  {
                        LinesArea[a-1].X2 = LinesArea[a].X1;
                        LinesArea[a-1].Y2 = LinesArea[a].Y1;
                        LinesArea[a].n_cont = LinesArea[a-1].n_cont;
                        if (end){
                                LinesArea[a].n_cont++;
                                LinesArea[a-1].X2 = fx;
                                LinesArea[a-1].Y2 = fy;
                                fx = LinesArea[a].X1;
                                fy = LinesArea[a].Y1;
                                }
                        }
                else    {
                        fx = LinesArea[0].X1;
                        fy = LinesArea[0].Y1;
                        LinesArea[0].n_cont = 0;
                        }
                end = (bool)ex_float_NM(A,&i,-1);
                start++;
                }
        LinesArea[n_cor-1].X2 = fx;
        LinesArea[n_cor-1].Y2 = fy;
        LinesArea[n_cor].n_cont = LinesArea[n_cor-1].n_cont;
        LinesArea[n_cor].n_cont++;
        return (start+n_cor-1);
        }
//---------------------------------------------------------------------------






//---------------------------------------------------------------------------
void InsideHatch (int hatch, AnsiString net)
        {
        Form1->AllPins->ClearSelection();
        AnsiString A;
        AnsiString current_n;
        for (int rstr=i_NETS; rstr<i_TEXTS; rstr++)
                {
                A = Form1->File->Items->operator [](rstr);
                if (A.SubString(1,4) == "net:" )
                        {
                        i = prob(A,1);
                        current_n = ex_str(A,&i);
                        Form1->current_net_pins->Clear();
                        }
                else if (A.SubString(1,4) == "pin:" )
                        {
                        i = prob(A,2);
                        Form1->current_net_pins->Items->Add(A.SubString(i,(A.Length()-i+1)));
                        }
                else if (A.SubString(1,5) == "area:" )
                        {
                        i = prob(A,2);
                        int cc = ex_float_NM(A,&i,-1);
                        int lr = ex_float_NM(A,&i,-1);
                        int hs = ex_float_NM(A,&i,-1);
                        if (hs == hatch) rstr = r_area(rstr+1,cc);
                        else continue;
                        for (int p=0; p<Form1->loc_NAMES->Count; p++)
                                {
                                AnsiString pn = Form1->loc_NAMES->Items->operator [](p);
                                if (point_area_inside(loc_PINS[p].p.x,loc_PINS[p].p.y,cc) )
                                        {
                                        int ind = Form1->AllPins->Items->IndexOf(pn);
                                        if (ind != -1)
                                                {
                                                if (!loc_PINS[p].hole && loc_PINS[p].layer != lr && !Form1->AllPins->Selected[ind])
                                                        {
                                                        //isEmpty
                                                        }
                                                else if (net.SubString(1,net.Length()) == current_n.SubString(1,current_n.Length())
                                                        || !net.Length())
                                                        Form1->AllPins->Selected[ind] = true;
                                                }
                                        }
                                }
                        }
                }
        }
void __fastcall TForm1::Button8Click(TObject *Sender)
{
InsideHatch(0,"");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button9Click(TObject *Sender)
{
InsideHatch(2,"");         
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button10Click(TObject *Sender)
{
InsideHatch(1,"");
}
//---------------------------------------------------------------------------



void __fastcall TForm1::OnWMCopyData(TWMCopyData &Msg)
{
        AnsiString str = (char*)Msg.CopyDataStruct->lpData;
        int iprev = 1;
        i = prob(str,1);
        while( i > 0 )
                {
                AnsiString STR = str.SubString(iprev,i-iprev-1);
                STR = STR.Trim();
                int iof = Form1->AllPins->Items->IndexOf(STR);
                if( iof >= 0 )
                        Form1->AllPins->Items->Delete(iof);
                Form1->EditList->Items->Add( STR );
                iprev = i;
                while_not_space( str,&i );
                }
        ShowMessage("  The list is imported from the Infobox application. \n  To select pins, use the Infobox filter, which has more \n  features than the Pins filter.");
}

void __fastcall TForm1::Label22Click(TObject *Sender)
{
ShellExecute(NULL, "open", "https://github.com/Duxah/FreePCB-2/blob/master/README.md", NULL, NULL, SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------
