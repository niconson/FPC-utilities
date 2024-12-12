//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "HEAD.h"
#include "LSTBXS.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
AnsiString SaveD = "";
AnsiString OpenD = "";
AnsiString TimeStr;
int UNITS = 0;
#define MAXLONGVALUE  2100000000

int MaxLayerNumRef = 2;
int IncrementArc;
bool FlagWarning1 = false;
bool FlagWarning3 = false;
bool FlagWarning5 = false;
long BRD_RECT[4] = {MAXLONGVALUE,MAXLONGVALUE,0,0};
long MaxLoc;




//FUNC
AnsiString ex_str (AnsiString ANSI, long *n);
double ex_float_NM (AnsiString Str, long *index, int units);
long prob (AnsiString ANSI , long Pr);
long count_stroke_file_func (AnsiString OpenD );
void read_net_list(AnsiString OpenD, long CNT);
void Read_Part (AnsiString OpenD, long CNT);
int go (AnsiString Ansi, int index, AnsiString S);
void Shifting (long Case, AnsiString *DATA, long *Size_of, long Ptr);
void Create_Foot (AnsiString OpenD, long CNT);
long Generate_ARC (double X, double Y, double X2, double Y2, double x0, double y0, double *OutPut);
void Rotate_Vertex (double *X, double *Y, double Ang);
void FPC_File_Gen (void);
AnsiString Find_net (AnsiString Pin );
void Generate_Poly ( double *PARAM, AnsiString NET_name );
void CombNetList_and_Area (AnsiString OpenD, long CNT);
void Pins_Location (void);
void Lines (AnsiString OpenD, long CNT, long MEM);
void Areas (AnsiString OpenD, long CNT);
bool StrBegin (AnsiString STR1, AnsiString STR2);
void RTextStyle (AnsiString TextStyle, long *W, long *H);
void CombNetList (AnsiString OpenD, long CNT);
void Scob (AnsiString STR, int * SCOB);
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
DecimalSeparator = ',';
Form1->ListBox1->Sorted = false;
Form1->ListBox2->Sorted = false;
Form1->ListBox3_TEXTS->Sorted = false;
Form1->ListBox4_Lines->Sorted = false;
Form1->Library->Sorted = false;
float ADD;
int i;
i = 0;
ADD = 5;
while (i < 26)
      {
        Form1->ComboBox3->Items->Add(AnsiString((int)ADD)) ;
        i++;
        ADD++;
      }
Form1->ComboBox3->ItemIndex = 7;
i = 0;
ADD = -0.5;
while (i <= 100)
      {
        Form1->ComboBox2->Items->Add(FormatFloat("0.00",ADD)) ;
        i++;
        ADD = ADD + 0.01;
      }
Form1->ComboBox2->ItemIndex = 50;
}

//-------------------------------------------------
//=============== OpenDialog1 =====================
//-------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
AnsiString A_str;
if (Form1->OpenDialog1->Execute())
   {
    if (Form1->OpenDialog1->FileName.Length() == 0) return;
    A_str = Form1->OpenDialog1->FileName;
    if (A_str.UpperCase().SubString((A_str.Length()-3),4) != ".PCB") {ShowMessage ("   Формат файла не поддерживается"); return;  }
   }
else return;
Form1->Edit1->Text = Form1->OpenDialog1->FileName;
OpenD = Form1->OpenDialog1->FileName;
//
A_str = OpenD + ".fpc";
SaveD = A_str;
Form1->Edit2->Text = A_str;
Form1->Button1->Enabled = true;
}


//-------------------------------------------------
//=============== SaveDialog1 =====================
//-------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
AnsiString A_str;
if (Form1->SaveDialog1->Execute())
   {
    if (Form1->SaveDialog1->FileName.Length() == 0) return;
    A_str = Form1->SaveDialog1->FileName;
    if (A_str.UpperCase().SubString((A_str.Length()-3),4) != ".FPC") A_str = A_str + ".fpc";
   }
else return;
Form1->Edit2->Text = A_str;
SaveD = A_str;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit1Change(TObject *Sender)
{
OpenD = Form1->Edit1->Text;        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit2Change(TObject *Sender)
{
SaveD = Form1->Edit2->Text;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
long CNT_PCB = count_stroke_file_func (OpenD);     //подсчет строк и чтение GERBER параметров
if (CNT_PCB < 50)
        {
        ShowMessage("    Format not available!");
        return;
        }
MaxLoc = 0;
IncrementArc = StrToInt(Form1->ComboBox3->Items->operator [](Form1->ComboBox3->ItemIndex));
Sleep(300);
read_net_list(OpenD, CNT_PCB);                  //чтение нетлист
Sleep(300);
Read_Part (OpenD, CNT_PCB);                     //чтение паттернов
Sleep(300);
CombNetList (OpenD, CNT_PCB);                   //объединение нетлист и нетлистVias
Sleep(300);
Create_Foot (OpenD, CNT_PCB);                   //создание футпринтов
Sleep(300);
Pins_Location ();                               //Расчет координат пинов
Sleep(300);
long CNT_for_Lines = CNT_PCB;
Lines (OpenD, CNT_PCB, CNT_for_Lines);          //Чтение линий и генерация трасс
while (FlagWarning3)
        {
        FlagWarning3 = false;
        ShowMessage ("    Предупреждение! Применено увеличение объема памяти для линий трасс.");
        CNT_for_Lines = CNT_for_Lines*2;
        Lines (OpenD, CNT_PCB, CNT_for_Lines);
        }
Sleep(300);
Areas (OpenD, CNT_PCB);                         //Чтение Полигонов
Sleep(300);
CombNetList_and_Area (OpenD, CNT_PCB);          //объединение CombNetList и Area , Добавление трасс в NETLIST
Sleep(300);
FPC_File_Gen ();                                //создание FPC file
Form1->Label4->Caption = "Ready!" ;
Application->ProcessMessages();
Sleep(300);
if (MaxLoc > MAX_LOC)
        {
        ShowMessage ("    Error object location.");
        exit(0);
        }
if (FlagWarning1) ShowMessage ("    Внимание! Количество слоев > 16.");
if (FlagWarning5) ShowMessage ("    Внимание! Кол-во сегментов трассы > 9999.");

//-------------запуск ------------

AnsiString B = SaveD;
AnsiString A = ExtractFileName(B.c_str());
//
SHELLEXECUTEINFO info = {0};
AnsiString fn = ExtractFilePath(Application->ExeName);
fn.SetLength(fn.Length()-1);
fn = ExtractFilePath(fn);
fn.SetLength(fn.Length()-1);
fn = ExtractFilePath(fn) + "freepcb.exe";
AnsiString FN = ("\""+fn+"\"");
AnsiString ps = B;
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

if (!Form2->Visible) exit(0);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
Form2->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Label3Click(TObject *Sender)
{
ShellExecute(NULL, "open", "https://github.com/Duxah/FreePCB-2", NULL, NULL, SW_SHOWNORMAL);       
}
//---------------------------------------------------------------------------

