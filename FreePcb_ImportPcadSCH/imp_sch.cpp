//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "fstream.h"
#include "Imp_sch.h"
#include "math.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
const int compInstPos = 0;
const int symbolDefPos = 1;
int fileUnits = 0;
int currentPage = 0;
int * BOOLS = NULL;
int netlistPos = 0;
List mList[NUMPAGES];
AnsiString A;
AnsiString B;
AnsiString C;
//---------------------------------------------------------------------------
int ABS( int v )
{
        if( v > 0 )
                return v;
        else    return -v;
}
//---------------------------------------------------------------------------
void Rotate_Vertex (double *X, double *Y, double Ang)
{
double start_Ang = 0;
double end_Ang = 0;
double radius = 0;
bool Flag = false;
if (( ABS(*X) > DEFAULT )||( ABS(*Y) > DEFAULT ))
        {
        Flag = true;
        *X = (*X)/(double)DEFAULT;
        *Y = (*Y)/(double)DEFAULT;
        }
if (ABS(*X) < BY_ZERO)
        {
        if (*Y > 0) start_Ang = 90;
        else if (*Y < 0) start_Ang = 270;
        }
else
        {
        start_Ang = (atan(*Y/(*X)))*(double)180/(double)M_PI;
        if ((*X > 0)&&(*Y < 0)) start_Ang = (double)360 + start_Ang;
        if (*X < 0) start_Ang = (double)180 + start_Ang;
        }
end_Ang = start_Ang + Ang;
double powx = ABS(*X);
double powy = ABS(*Y);
if (powx > BY_ZERO) powx = pow(powx,2);
if (powy > BY_ZERO) powy = pow(powy,2);
if (powx > BY_ZERO || powy > BY_ZERO)   radius = sqrt(powx + powy);
else                                    radius = powx + powy;
*Y = radius*sin(end_Ang*(double)M_PI/(double)180);
*X = radius*cos(end_Ang*(double)M_PI/(double)180);
if (Flag) *X = (*X)*(double)DEFAULT;
if (Flag) *Y = (*Y)*(double)DEFAULT;
}
//---------------------------------------------------------------------------
AnsiString Extract( AnsiString str, AnsiString p1, AnsiString p2 )
{
        int i1 = 1;
        if( p1.Length() )
                i1 = str.Pos(p1);
        AnsiString str2 = str.SubString(i1+p1.Length(),str.Length()-i1+1-p1.Length());
        int i2 = str2.Length();
        if( p2.Length() )
                i2 = str2.Pos(p2)-1;
        if( i2 > 0 )
                return str2.SetLength(i2).Trim();
        else    return "";
}
//---------------------------------------------------------------------------
void WrPin(     AnsiString refdes,
                AnsiString value,
                AnsiString pattern,
                double pinptx,
                double pinpty,
                double pinrot,
                double pinlen,
                AnsiString pinname,
                double pnmx,
                double pnmy,
                double pnmrot,
                AnsiString pindesc,
                double pdscx,
                double pdscy,
                double pdscrot,
                double rotation,
                double movex,
                double movey,
                int nobj
                )
{
        AnsiString svA = A;

        // get pin net
        AnsiString currentNet="";
        AnsiString pinnet="";
        if( pattern.Length() == 0 )
                {
                pattern = "None";
                if( mList[currentPage].part_start )
                        mList[currentPage].part_start->footprint = pattern;
                for( int i=netlistPos; i<Form1->LB1->Items->Count; i++ )
                        {
                        A = Form1->LB1->Items->operator [](i);
                        if( A.Pos("(net ") ==  1 )
                                {
                                currentNet = Extract(A, "(net ", "");
                                for( int io=currentNet.Pos("\""); io>0; io=currentNet.Pos("\"") )
                                        currentNet.Delete(io,1);
                                }
                        if( A.Pos("(node ") ==  1 )
                                {
                                AnsiString nodeRef = Extract(A, "(node ", "\" \"");
                                for( int io=nodeRef.Pos("\""); io>0; io=nodeRef.Pos("\"") )
                                        nodeRef.Delete(io,1);
                                AnsiString nodePin = Extract(A, "\" \"", ")");
                                for( int io=nodePin.Pos("\""); io>0; io=nodePin.Pos("\"") )
                                        nodePin.Delete(io,1);
                                bool eFlag1=0, eFlag2=0;
                                if( nodeRef.Pos(refdes) == 1 && refdes.Pos(nodeRef) == 1 )
                                        eFlag1 = true;
                                if( nodePin.Pos(pinname) == 1 && pinname.Pos(nodePin) == 1 )
                                        eFlag2 = true;
                                if( eFlag1 && eFlag2 )
                                        {
                                        if( currentNet.Pos("NET") == 0 )
                                                {
                                                pinnet = currentNet;
                                                pattern = "NetPoint";
                                                if( mList[currentPage].part_start )
                                                        mList[currentPage].part_start->footprint = pattern;
                                                }
                                        break;
                                        }
                                }
                        }
                }
        double x2, y2;
        if( pinrot == 90 )
                {
                x2 = pinptx;
                y2 = pinpty + pinlen;
                }
        else if( pinrot == 180 )
                {
                x2 = pinptx - pinlen;
                y2 = pinpty;
                }
        else if( pinrot == 270 )
                {
                x2 = pinptx;
                y2 = pinpty - pinlen;
                }
        else    {
                x2 = pinptx + pinlen;
                y2 = pinpty;
                }
        pnmrot -= pinrot;
        pdscrot -= pinrot;
        if( fileUnits == MM )
                {
                pinptx *= PER_MM;
                pinpty *= PER_MM;
                x2 *= PER_MM;
                y2 *= PER_MM;
                pnmx *= PER_MM;
                pnmy *= PER_MM;
                pdscx *= PER_MM;
                pdscy *= PER_MM;
                }
        else    {
                pinptx *= PER_MIL;
                pinpty *= PER_MIL;
                x2 *= PER_MIL;
                y2 *= PER_MIL;
                pnmx *= PER_MIL;
                pnmy *= PER_MIL;
                pdscx *= PER_MIL;
                pdscy *= PER_MIL;
                }
        if( rotation )
                {
                Rotate_Vertex( &pinptx, &pinpty, rotation );
                Rotate_Vertex( &x2, &y2, rotation );
                Rotate_Vertex( &pnmx, &pnmy, rotation );
                Rotate_Vertex( &pdscx, &pdscy, rotation );
                pnmrot -= rotation;
                pdscrot -= rotation;
                }
        pinptx += movex;
        pinpty += movey;
        x2 += movex;
        y2 += movey;
        pnmx += movex;
        pnmy += movey;
        pdscx += movex;
        pdscy += movey;
        if( nobj == 0 )
                mList[currentPage].AddLine(pinptx,pinpty,x2,y2,refdes,value,pattern,pindesc,pdscx,pdscy,pdscrot,pinnet,pnmx,pnmy-PER_MM,0,pinname,pnmx,pnmy,pnmrot);
        else    mList[currentPage].AddLine(pinptx,pinpty,x2,y2,"","","",pindesc,pdscx,pdscy,pdscrot,pinnet,pnmx,pnmy-PER_MM,0,pinname,pnmx,pnmy,pnmrot);
        A = svA;
}
//---------------------------------------------------------------------------
void GetPartData(AnsiString symbol, AnsiString refDesRef, int x, int y, int rotation)
{
bool eFlag = false;
AnsiString originalName = "";
AnsiString compValue    = "";
AnsiString patternName  = "";
for( int i=0; i<Form1->LB1->Items->Count; i++ )
        {
        if( eFlag == 0 && getbit( BOOLS[i], compInstPos ) == 0 )
                continue;

        A = Form1->LB1->Items->operator [](i);
        if( getbit( BOOLS[i], compInstPos ) )
                {
                AnsiString gRef = Extract(A, "(compInst ", "");
                for( int io=gRef.Pos("\""); io>0; io=gRef.Pos("\"") )
                        gRef.Delete(io,1);
                if( gRef.Pos(refDesRef) == 1 && refDesRef.Pos(gRef) == 1 )
                        eFlag = true;
                else if( eFlag )
                        break;
                continue;
                }

        if( A.Pos("(originalName ") == 1 )
                {
                originalName = Extract(A, "(originalName ", "\")");
                for( int io=originalName.Pos("\""); io>0; io=originalName.Pos("\"") )
                        originalName.Delete(io,1);
                }
        if( A.Pos("(compValue ") == 1 )
                {
                compValue = Extract(A, "(compValue ", "\")");
                for( int io=compValue.Pos("\""); io>0; io=compValue.Pos("\"") )
                        compValue.Delete(io,1);
                }
        if( A.Pos("(patternName ") == 1 )
                {
                patternName = Extract(A, "(patternName ", "\")");
                for( int io=patternName.Pos("\""); io>0; io=patternName.Pos("\"") )
                        patternName.Delete(io,1);
                }
        }
if( compValue.Length() == 0 )
        compValue = originalName;
eFlag = false;
int n_obj = 0;
double pinptx = 0;
double pinpty = 0;
double pinrot = 0;
double pinlen = 0;
AnsiString pinname="";
double pnmx = 0;
double pnmy = 0;
double pnmrot = 0;
AnsiString pindesc="";
double pdscx = 0;
double pdscy = 0;
double pdscrot = 0;
for( int i=0; i<Form1->LB1->Items->Count; i++ )
        {
        if( eFlag == 0 && getbit( BOOLS[i], symbolDefPos ) == 0 )
                continue;

        A = Form1->LB1->Items->operator [](i);
        if( getbit( BOOLS[i], symbolDefPos ) )
                {
                AnsiString gSymb = Extract(A, "(symbolDef ", "");
                for( int io=gSymb.Pos("\""); io>0; io=gSymb.Pos("\"") )
                        gSymb.Delete(io,1);
                if( gSymb.Pos(symbol) == 1 && symbol.Pos(gSymb) == 1 )
                        eFlag = true;
                else if( eFlag )
                        break;
                continue;
                }
        if( A.Pos("(compDef ") ==  1 )
                break;
        else if( A.Pos("(netlist ") ==  1 )
                break;

        if( A.Pos("(line ") == 1 )
                {
                B = Extract(A,"(pt ",")");
                C = Extract(B,""," ");
                double x1 = C.ToDouble();
                C = Extract(B," ","");
                double y1 = C.ToDouble();
                B = Extract(A,"(pt ","");
                B = Extract(B,"(pt ",")");
                C = Extract(B,""," ");
                double x2 = C.ToDouble();
                C = Extract(B," ","");
                double y2 = C.ToDouble();
                if( fileUnits == MM )
                        {
                        x1 *= PER_MM;
                        y1 *= PER_MM;
                        x2 *= PER_MM;
                        y2 *= PER_MM;
                        }
                else    {
                        x1 *= PER_MIL;
                        y1 *= PER_MIL;
                        x2 *= PER_MIL;
                        y2 *= PER_MIL;
                        }
                if( rotation )
                        {
                        Rotate_Vertex( &x1, &y1, rotation );
                        Rotate_Vertex( &x2, &y2, rotation );
                        }
                x1 += x;
                y1 += y;
                x2 += x;
                y2 += y;
                if( n_obj == 0 )
                        mList[currentPage].AddLine(x1,y1,x2,y2,refDesRef,compValue,patternName,"",0,0,0,"",0,0,0,"",0,0,0);
                else    mList[currentPage].AddLine(x1,y1,x2,y2,"","","","",0,0,0,"",0,0,0,"",0,0,0);
                n_obj++;
                }
        if( A.Pos("(pin ") == 1 )
                {
                if( pinname.Length() )
                        {
                        WrPin(refDesRef,compValue,patternName,pinptx,pinpty,pinrot,pinlen,pinname,pnmx,pnmy,pnmrot,pindesc,pdscx,pdscy,pdscrot,rotation,x,y,n_obj);
                        pinname = "";
                        n_obj++;
                        }
                B = Extract(A,"(pt ",")");
                C = Extract(B,""," ");
                pinptx = C.ToDouble();
                C = Extract(B," ","");
                pinpty = C.ToDouble();
                pinrot = 0;
                if( A.Pos("(rotation ") > 0 )
                        {
                        B = Extract(A,"(rotation ",")");
                        pinrot = B.ToDouble();
                        }
                if( fileUnits == MM )
                        pinlen = 2;
                else if( fileUnits == MIL )
                        pinlen = 80;
                else    pinlen = 0.1;
                if( A.Pos("(pinLength ") > 0 )
                        {
                        B = Extract(A,"(pinLength ",")");
                        pinlen = B.ToDouble();
                        }
                }
        if( A.Pos("(pinDes ") == 1 )
                {
                pinname = Extract(A," \"","\" ");
                B = Extract(A,"(pt ",")");
                C = Extract(B,""," ");
                pnmx = C.ToDouble();
                C = Extract(B," ","");
                pnmy = C.ToDouble();
                pnmrot = 0;
                if( A.Pos("(rotation ") > 0 )
                        {
                        B = Extract(A,"(rotation ",")");
                        pnmrot = B.ToDouble();
                        }
                }
        if( A.Pos("(pinName ") == 1 )
                {
                pindesc = Extract(A," \"","\" ");
                B = Extract(A,"(pt ",")");
                C = Extract(B,""," ");
                pdscx = C.ToDouble();
                C = Extract(B," ","");
                pdscy = C.ToDouble();
                pdscrot = 0;
                if( A.Pos("(rotation ") > 0 )
                        {
                        B = Extract(A,"(rotation ",")");
                        pdscrot = B.ToDouble();
                        }
                }
        }
if( pinname.Length() )
        {
        WrPin(refDesRef,compValue,patternName,pinptx,pinpty,pinrot,pinlen,pinname,pnmx,pnmy,pnmrot,pindesc,pdscx,pdscy,pdscrot,rotation,x,y,n_obj);
        pinname = "";
        n_obj++;
        }
mList[currentPage].Partend();
}
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
DecimalSeparator = '.';
Form1->OpenDialog1->Execute();
Timer1->Enabled = true;
}
//---------------------------------------------------------------------------
void List::AddLine(     int x, int y, int x2, int y2,
                        AnsiString r,
                        AnsiString v,
                        AnsiString f,
                        AnsiString d, int dx, int dy, int da,
                        AnsiString n, int nx, int ny, int na,
                        AnsiString p, int px, int py, int pa )
{
        Line * L = new Line;
        L->mx = x;
        L->my = y;
        L->nx = x2;
        L->ny = y2;
        if( part_start )
                {
                part_start->minx = min( part_start->minx, x );
                part_start->miny = min( part_start->miny, y );
                part_start->maxx = max( part_start->maxx, x );
                part_start->maxy = max( part_start->maxy, y );
                part_start->minx = min( part_start->minx, x2 );
                part_start->miny = min( part_start->miny, y2 );
                part_start->maxx = max( part_start->maxx, x2 );
                part_start->maxy = max( part_start->maxy, y2 );
                }
        else    {
                L->minx = min( x, x2 );
                L->miny = min( y, y2 );
                L->maxx = max( x, x2 );
                L->maxy = max( y, y2 );
                }
        L->refdes = r;
        L->value = v;
        L->footprint = f;
        L->description = d;
        L->descx = dx;
        L->descy = dy;
        L->desca = da;
        L->netname = n;
        L->netx = nx;
        L->nety = ny;
        L->neta = na;
        L->pinname = p;
        L->pinx = px;
        L->piny = py;
        L->pina = pa;
        L->partend = 0;
        if( r.Length() )
                {
                if( part_start )
                        ShowMessage("Error 8365");
                part_start = L;
                }
        m_end->next = L;
        L->next = NULL;
        m_end = L;
}
//---------------------------------------------------------------------------
void List::RemoveAll()
{
Line * prev = NULL;
for( Line * L=GetStart(); L; L=L->next )
        {
        if( prev )
                delete prev;
        prev = L;
        }
if( prev )
        delete prev;
List();
}
//---------------------------------------------------------------------------
Line * List::GetStart()
{
return m_start.next;
}
//---------------------------------------------------------------------------
List::List()
{
m_start.next = NULL;
m_end = &m_start;
part_start = NULL;
}
//---------------------------------------------------------------------------
void List::Partend()
{
part_start = NULL;
m_end->partend = true;
}
//---------------------------------------------------------------------------
Line * List::isPart(Line * line)
{
Line * lp = NULL;
for( Line * L=GetStart(); L; L=L->next )
        {
        if( L->refdes.Length() )
                lp = L;
        if( L == line )
                return lp;
        if( L->partend )
                lp = NULL;
        }
return NULL;
}
//---------------------------------------------------------------------------
void Import()
{
Form1->Label1->Caption = "Starting format conversion";
Application->ProcessMessages();
AnsiString fileStr = Form1->OpenDialog1->FileName;
if( fileStr.Length() == 0 )
        exit(0);
ifstream read (fileStr.c_str());
char str[2540];
int First = 0;
int parts = 0;
while( read.eof() == 0 )
        {
        read.getline(str,sizeof(str));
        A = str;
        A = A.Trim();
        if( First == 0 )
                if( A.Pos("ACCEL_ASCII") != 1 )
                        break;
        if( A.Length() == 0 )
                continue;
        First++;
        Form1->LB1->Items->Add(A);
        if( A.Pos("(symbol ") == 1 )
                parts++;
        if( First%500 == 0 )
                {
                Form1->Label1->Caption = "Starting format conversion " + AnsiString(First);
                Application->ProcessMessages();
                }
        }
read.close();
BOOLS = new int[ Form1->LB1->Items->Count ];
for( int i=0; i<Form1->LB1->Items->Count; i++ )
        {
        BOOLS[i] = 0;
        A = Form1->LB1->Items->operator [](i);
        if( A.SubString(1,10) == "(compInst " )
                setbit( BOOLS[i], compInstPos );
        if( A.SubString(1,11) == "(symbolDef " )
                setbit( BOOLS[i], symbolDefPos );
        if( A.SubString(1,9) == "(netlist " )
                netlistPos = i;
        }
int nWire = 1;
double step = (double)100.0/(double)parts;
double bar_pos = 0.0;
for( int i=0; i<Form1->LB1->Items->Count; i++ )
        {
        A = Form1->LB1->Items->operator [](i);
        if( A.Pos("(fileUnits ") == 1 && fileUnits == 0 )
                {
                if( A.Pos("mil") > 0 || A.Pos("Mil") > 0 || A.Pos("MIL") > 0 )
                        fileUnits = MIL;
                else    fileUnits = MM;
                }
        if( A.Pos("(sheet ") == 1 )
                {
                if( A.Pos("(sheetNum 1)") > 0 )
                        currentPage = 0;
                else if( A.Pos("(sheetNum 2)") > 0 )
                        currentPage = 1;
                else if( A.Pos("(sheetNum 3)") > 0 )
                        currentPage = 2;
                else if( A.Pos("(sheetNum 4)") > 0 )
                        currentPage = 3;
                else if( A.Pos("(sheetNum 5)") > 0 )
                        currentPage = 4;
                else if( A.Pos("(sheetNum 6)") > 0 )
                        currentPage = 5;
                else if( A.Pos("(sheetNum 7)") > 0 )
                        currentPage = 6;
                else if( A.Pos("(sheetNum 8)") > 0 )
                        currentPage = 7;
                }
        if( A.Pos("(wire ") == 1 )
                {
                B = Extract(A,"(pt ",")");
                C = Extract(B,""," ");
                double x1 = C.ToDouble();
                C = Extract(B," ","");
                double y1 = C.ToDouble();
                B = Extract(A,"(pt ","(width ");
                B = Extract(B,"(pt ",")");
                C = Extract(B,""," ");
                double x2 = C.ToDouble();
                C = Extract(B," ","");
                double y2 = C.ToDouble();
                if( A.Pos("RightLead") > 0 )
                        {
                        if( ABS(x1-x2) > ABS(y1-y2) )
                                y1 = y2 = max(y1,y2);
                        else    x1 = x2 = max(x1,x2);
                        }
                if( fileUnits == MM )
                        {
                        x1 *= PER_MM;
                        y1 *= PER_MM;
                        x2 *= PER_MM;
                        y2 *= PER_MM;
                        }
                else    {
                        x1 *= PER_MIL;
                        y1 *= PER_MIL;
                        x2 *= PER_MIL;
                        y2 *= PER_MIL;
                        }
                Form1->Label1->Caption = "Wire" + AnsiString(nWire) + " creation";
                Application->ProcessMessages();
                nWire++;
                mList[currentPage].AddLine(x1,y1,x2,y2,"","","","",0,0,0,"",0,0,0,"",0,0,0);
                }
        if( A.Pos("(port ") == 1 )
                {
                B = Extract(A,"(pt ",")");
                C = Extract(B,""," ");
                double x1 = C.ToDouble();
                C = Extract(B," ","");
                double y1 = C.ToDouble();
                AnsiString Net = Extract(A,"(netNameRef ",")");
                for( int io=Net.Pos("\""); io>0; io=Net.Pos("\"") )
                        Net.Delete(io,1);
                if( Net.Pos("NET") == 1 )
                        Net = "?" + Net;
                int x2 = x1;
                int y2 = y1;
                if( fileUnits == MM )
                        {
                        x1 *= PER_MM;
                        y1 *= PER_MM;
                        x2 *= PER_MM;
                        y2 *= PER_MM;
                        }
                else    {
                        x1 *= PER_MIL;
                        y1 *= PER_MIL;
                        x2 *= PER_MIL;
                        y2 *= PER_MIL;
                        }
                x2 += PER_MM;
                y2 += PER_MM;
                mList[currentPage].AddLine(x1,y1,x2,y2,"","","","",0,0,0,Net,x2,y2,0,"",0,0,0);
                }
        if( A.Pos("(bus ") == 1 )
                {
                B = Extract(A,"(pt ",")");
                C = Extract(B,""," ");
                double x1 = C.ToDouble();
                C = Extract(B," ","");
                double y1 = C.ToDouble();
                B = Extract(A,"(pt ","");
                B = Extract(B,"(pt ",")");
                C = Extract(B,""," ");
                double x2 = C.ToDouble();
                C = Extract(B," ","");
                double y2 = C.ToDouble();
                if( fileUnits == MM )
                        {
                        x1 *= PER_MM;
                        y1 *= PER_MM;
                        x2 *= PER_MM;
                        y2 *= PER_MM;
                        }
                else    {
                        x1 *= PER_MIL;
                        y1 *= PER_MIL;
                        x2 *= PER_MIL;
                        y2 *= PER_MIL;
                        }
                AnsiString bus = Extract(A, "(bus ", "(pt ");
                for( int io=bus.Pos("\""); io>0; io=bus.Pos("\"") )
                        bus.Delete(io,1);
                mList[currentPage].AddLine(x1,y1,x2,y2,"","","",bus,x1,y1,0,"",0,0,0,"",0,0,0);
                }
        if( A.Pos("(symbol ") == 1 )
                {
                AnsiString symbolRef = Extract(A, "(symbolRef ", ")");
                for( int io=symbolRef.Pos("\""); io>0; io=symbolRef.Pos("\"") )
                        symbolRef.Delete(io,1);
                AnsiString refDesRef = Extract(A, "(refDesRef ", ")");
                for( int io=refDesRef.Pos("\""); io>0; io=refDesRef.Pos("\"") )
                        refDesRef.Delete(io,1);
                B = Extract(A,"(pt ",")");
                C = Extract(B,""," ");
                double x1 = C.ToDouble();
                C = Extract(B," ","");
                double y1 = C.ToDouble();
                int ang = 0;
                if( A.Pos("(rotation ") > 0 )
                        {
                        B = Extract(A,"(rotation ",")");
                        ang = B.ToDouble();
                        }
                if( fileUnits == MM )
                        {
                        x1 *= PER_MM;
                        y1 *= PER_MM;
                        }
                else    {
                        x1 *= PER_MIL;
                        y1 *= PER_MIL;
                        }
                Form1->Label1->Caption = "Page: " + AnsiString(currentPage+1) + ", part: " + refDesRef;
                if( bar_pos < 100 )
                        bar_pos += step;
                Form1->ProgressBar->Position = bar_pos;
                Application->ProcessMessages();
                GetPartData( symbolRef, refDesRef, x1, y1, ang );
                }
        }

ofstream WFile ((fileStr+".cds").c_str());
WFile << "[options]";
WFile << endl;
WFile << "project_name: \"";
WFile << (ExtractFileName(fileStr)+".cds").c_str();
WFile << "\"";
WFile << endl;
ifstream opt ((ExtractFilePath(Application->ExeName)+"options.txt").c_str());
while( opt.eof() == 0 )
        {
        opt.getline(str,sizeof(str));
        A = str;
        A = A.Trim();
        WFile << A.c_str();
        WFile << endl;
        }
opt.close();
WFile << endl;
WFile << "[graphics]";
WFile << endl;
for( int i=0; i<NUMPAGES; i++ )
        {
        if( i == 0 )
                {
                WFile << "rename_page: \"main_page\"";
                WFile << endl;
                }
        else if( mList[i].GetStart() )
                {
                WFile << "add_new_page: \"additional\"";
                WFile << endl;
                }
        for( Line * L=mList[i].GetStart(); L; L=L->next )
                {
                if( L->refdes.Length() )
                        {
                        WFile << "ref_des: \"";
                        WFile << L->refdes.c_str();
                        WFile << "\" ";
                        WFile << AnsiString(L->maxx).c_str();
                        WFile << " ";
                        WFile << AnsiString(L->maxy).c_str();
                        WFile << " ";
                        WFile << AnsiString(LAY_REF).c_str();
                        WFile << " ";
                        WFile << AnsiString(0).c_str();         //ang
                        WFile << " ";
                        WFile << AnsiString(800000).c_str();   //font h
                        WFile << " ";
                        WFile << AnsiString(100000).c_str();   //font w
                        WFile << " -1 -1 11 1";
                        WFile << endl;
                        }
                if( L->value.Length() )
                        {
                        WFile << "part_value: \"";
                        WFile << L->value.c_str();
                        WFile << "\" ";
                        WFile << AnsiString(L->maxx).c_str();
                        WFile << " ";
                        WFile << AnsiString(L->maxy - 1000000).c_str();
                        WFile << " ";
                        WFile << AnsiString(LAY_VAL).c_str();
                        WFile << " ";
                        WFile << AnsiString(0).c_str();         //ang
                        WFile << " ";
                        WFile << AnsiString(800000).c_str();   //font h
                        WFile << " ";
                        WFile << AnsiString(100000).c_str();   //font w
                        WFile << " -1 -1 11 1";
                        WFile << endl;
                        }
                if( L->footprint.Length() )
                        {
                        WFile << "footprint_name: \"";
                        WFile << L->footprint.c_str();
                        WFile << "\" ";
                        WFile << AnsiString(L->maxx).c_str();
                        WFile << " ";
                        WFile << AnsiString(L->maxy - 2000000).c_str();
                        WFile << " ";
                        WFile << AnsiString(LAY_FOOT).c_str();
                        WFile << " ";
                        WFile << AnsiString(0).c_str();         //ang
                        WFile << " ";
                        WFile << AnsiString(800000).c_str();   //font h
                        WFile << " ";
                        WFile << AnsiString(100000).c_str();   //font w
                        WFile << " -1 -1 11 1";
                        WFile << endl;
                        }
                WFile << "polyline: 2 0 ";
                if( L->netname.Length() )
                        WFile << AnsiString(LAY_NET).c_str();
                else if( L->pinname.Length() )
                        WFile << AnsiString(LAY_PIN).c_str();
                else if( mList[i].isPart(L) )
                        WFile << AnsiString(LAY_PART).c_str();
                else if( L->description.Pos("BUS") == 1 )
                        WFile << AnsiString(LAY_DESC+1).c_str();
                else    WFile << AnsiString(LAY_FREE).c_str();
                if( L->description.Pos("BUS") == 1 )
                        WFile << " 1500000 -1 -1 -1 0";
                else    WFile << " 200000 -1 -1 -1 0";
                WFile << endl;
                WFile << "corner: 1 ";
                WFile << AnsiString(L->mx).c_str();
                WFile << " ";
                WFile << AnsiString(L->my).c_str();
                WFile << " 0 0";
                WFile << endl;
                WFile << "corner: 2 ";
                WFile << AnsiString(L->nx).c_str();
                WFile << " ";
                WFile << AnsiString(L->ny).c_str();
                WFile << " 0 0";
                WFile << endl;
                if( L->description.Length() )
                        {
                        WFile << "description: \"";
                        WFile << L->description.c_str();
                        WFile << "\" ";
                        WFile << AnsiString(L->descx).c_str();
                        WFile << " ";
                        WFile << AnsiString(L->descy).c_str();
                        WFile << " ";
                        WFile << AnsiString(LAY_DESC).c_str();
                        WFile << " ";
                        WFile << AnsiString(L->desca).c_str();
                        WFile << " ";
                        WFile << AnsiString(800000).c_str();   //font h
                        WFile << " ";
                        WFile << AnsiString(100000).c_str();   //font w
                        WFile << " -1 -1 11 1";
                        WFile << endl;
                        }
                if( L->pinname.Length() )
                        {
                        WFile << "pin_name: \"";
                        WFile << L->pinname.c_str();
                        WFile << "\" ";
                        WFile << AnsiString(L->pinx).c_str();
                        WFile << " ";
                        WFile << AnsiString(L->piny).c_str();
                        WFile << " ";
                        WFile << AnsiString(LAY_PINN).c_str();
                        WFile << " ";
                        WFile << AnsiString(L->pina).c_str();
                        WFile << " ";
                        WFile << AnsiString(800000).c_str();   //font h
                        WFile << " ";
                        WFile << AnsiString(100000).c_str();   //font w
                        WFile << " -1 -1 11 1";
                        WFile << endl;
                        }
                if( L->netname.Length() )
                        {
                        WFile << "net_name: \"";
                        WFile << L->netname.c_str();
                        WFile << "\" ";
                        WFile << AnsiString(L->netx).c_str();
                        WFile << " ";
                        WFile << AnsiString(L->nety).c_str();
                        WFile << " ";
                        WFile << AnsiString(LAY_NETN).c_str();
                        WFile << " ";
                        WFile << AnsiString(L->neta).c_str();
                        WFile << " ";
                        WFile << AnsiString(800000).c_str();   //font h
                        WFile << " ";
                        WFile << AnsiString(100000).c_str();   //font w
                        WFile << " -1 -1 11 1";
                        WFile << endl;
                        }
                if( L->partend )
                        {
                        WFile << "part_end";
                        WFile << endl;
                        }
                }
        }
WFile << "[end]";
WFile << endl;
WFile.close();
for( int i=0; i<NUMPAGES; i++ )
        mList[i].RemoveAll();
ShellExecute(NULL,"open",(fileStr+".cds").c_str(),NULL,ExtractFilePath(fileStr).c_str(),0);
delete BOOLS;
exit(0);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
Timer1->Enabled = false;
Import();
}
//---------------------------------------------------------------------------
