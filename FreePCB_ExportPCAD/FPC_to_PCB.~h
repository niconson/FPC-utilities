//---------------------------------------------------------------------------

#ifndef FPC_to_PCBH
#define FPC_to_PCBH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#define max_arc 99

#define ABS(A)                  ((A)<0  ? (-(A)) : (A))
#define TryBegin() try{
#define TryEnd(a)  }catch(Exception &exception) {ShowMessage(a);}
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TOpenDialog *OpenDialog1;
        TGroupBox *GroupBox1;
        TLabel *Label1;
        TTimer *Timer1;
        TListBox *ListBox1_Lines;
        TListBox *ListBox2_Texts;
        TListBox *ListBox3_Pins;
        TListBox *ListBox4_NamePins;
        TImage *Image1;
        TImage *Image2;
        TListBox *SavePadStyle;
        TListBox *LB_Pack_for_T;
        void __fastcall Timer1Timer(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
extern AnsiString OpenD;
extern AnsiString Path ;
extern AnsiString num_pin;
extern AnsiString A;
extern AnsiString B;
extern AnsiString E;
extern AnsiString Name_Foot;
extern AnsiString Reference;
extern AnsiString Value;
extern AnsiString Package ;
extern AnsiString Package_for_Type;
extern AnsiString type_top;
extern AnsiString type_bot;
extern AnsiString type_inn;
extern AnsiString Thermal;
extern AnsiString Inners[99];
extern AnsiString centroid ;
//---------
extern double X_val;
extern double Y_val;
extern double X_ref;
extern double Y_ref;
extern double W_ref;
extern double H_ref;
extern double W_val;
extern double H_val;
extern int ANG_ref;
extern int ANG_val;
//---------
extern long i ;                    //индекс в строке А и др.
extern long n ;
extern long m ;

extern char str[2501];                     //строка для чтения файла

//extern unsigned texts ;
//extern unsigned pins ;
//extern unsigned lines ;
extern long n_pins ;

extern int units_mm ;                 //флаг если единицы - миллиметры
extern bool current_units_mm ;         //текущий флаг если единицы - миллиметры
extern bool Side ;                 //0-top 1-bot
extern bool Vis_ref ;
extern bool Vis_val ;
extern bool Flag_Warning1;
extern bool Flag_Warning5;
extern bool Flag_Warning6;
extern long count_stroke_file ;   //кол-во строк в файле ascii P-cad

extern double X ;                      //X
extern double Y ;                      //Y
extern double Xpos ;
extern double Ypos ;
extern double D ;                      // дополнит...
extern double W ;                      // дополнит...
extern double F ;                      // дополнит...
extern double H ;                      // дополнит...
extern double Angle ;                  //угол футпринта
extern double mask_clearance ;
extern double shrink_paste_mask ;
extern double board_outline_width;
extern double fill_clearance ;
extern double glue_width ;
extern double hole_diam ;
extern double Wtop;
extern double Htop;
extern double Wbot;
extern double Hbot;
extern double Winn;
extern double Hinn;
extern double thermal_width ;
extern double n_cop;
extern double PadRadius;
extern double BPadRadius;
//------  
extern int go_not_int (unsigned index);                 //двигаем курсор в строке А пока не число
extern double ex_float_NM (long *index, int units);      //извлекаем float в строке А пока число
extern AnsiString ex_str (unsigned index);              //извлекаем строку в строке А заключенную в ""
extern int go (long index, AnsiString s);               //двигаем курсор в строке А пока не встретим AnsiString s
extern void mirr (bool layer_index);                    //коррекция координат X Y с учетом стороны PART
extern bool get (AnsiString s);                         //если A == s return 0 else 1 (s = char str)
extern void WR_FOOT (void);
extern int Prob (int Count);                            //пропуск заданного кол-ва пробелов
extern void WR_PADSTYLE (void);
extern bool get_end (void);                             //чтение файла до конца
extern float ang (double dx_, double dy_) ;
extern void ADD_text_style (void);
extern void WR_part (void);
extern void PCB_file_designer (void);
extern AnsiString F_str (double DBL);
extern AnsiString viaStyle (void);
extern void CUTOUT (int CASE, int LaYeR);
extern long Generate_Line (double X, double Y, double X2, double Y2,  int type_L , double *OutPut);
extern void Rotate_Vertex (double *X, double *Y, double Ang);
extern double Length_Line (double X1, double Y1, double X2, double Y2);
//---------------------------------------------------------------------------
#endif
