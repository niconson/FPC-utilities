//---------------------------------------------------------------------------

#ifndef Imp_schH
#define Imp_schH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
#define MM              1
#define MIL             2
#define NUMPAGES        8
#define PER_MM          1000000
#define PER_MIL         25400
#define LAY_FREE        5
#define LAY_PART        6
#define LAY_REF         7
#define LAY_PIN         8
#define LAY_PINN        9
#define LAY_NET         10
#define LAY_NETN        11
#define LAY_FOOT        12
#define LAY_VAL         13
#define LAY_DESC        14
#define DEFAULT         999999999
#define BY_ZERO         0.0001

#define setbit(reg,bit) reg|=(1<<bit)              
#define clrbit(reg,bit) reg&=~(1<<bit)             
#define invbit(reg,bit) reg^=(1<<bit)              
#define getbit(reg,bit) ((reg & (1<<bit)) ? 1 : 0) 

class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TProgressBar *ProgressBar;
        TListBox *LB1;
        TOpenDialog *OpenDialog1;
        TTimer *Timer1;
        void __fastcall Timer1Timer(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};

struct Line
{
int mx;
int my;
int nx;
int ny;
int minx;
int miny;
int maxx;
int maxy;
int npins;
AnsiString refdes;
AnsiString value;
AnsiString footprint;
AnsiString description;
int descx;
int descy;
int desca;
AnsiString netname;
int netx;
int nety;
int neta;
AnsiString pinname;
int pinx;
int piny;
int pina;
Line * next;
bool partend;
};
class List
{
private:
Line m_start;
Line * m_end;
public:
List();
Line * GetStart();
Line * part_start;
void AddLine(   int x, int y, int x2, int y2,
                AnsiString r,
                AnsiString v,
                AnsiString f,
                AnsiString d, int dx, int dy, int da,
                AnsiString n, int nx, int ny, int na,
                AnsiString p, int px, int py, int pa );
void RemoveAll();
void Partend();
Line * isPart(Line * line);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
