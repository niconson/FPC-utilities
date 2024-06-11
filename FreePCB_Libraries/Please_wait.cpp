//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Please_wait.h"
#include "ABClibrary.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm4 *Form4;
//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
        : TForm(Owner)
{
DecimalSeparator = ',';
}
//---------------------------------------------------------------------------
void __fastcall TForm4::Timer1Timer(TObject *Sender)
{
AnsiString s = Label1->Caption + ".";
if( s.Length() > 17 )
        s.SetLength(11);
Label1->Caption = s;
}
//---------------------------------------------------------------------------
bool SendMessage_1(AnsiString WindowName)
{
HWND EP = FindWindow( NULL,WindowName.c_str());
if (EP && Form1->ListBox1->ItemIndex >= 0) {
        char data[_2540];
        AnsiString mes = "";
        mes = Form1->ListBox1->Items->operator [](Form1->ListBox1->ItemIndex);
        if (Form1->Sort_ABC->Checked)
                {
                }
        else    {
                long k=prob(mes,1);
                mes = mes.SubString(k,mes.Length()-k+1);
                }
        int len = MIN(mes.Length(),(_2540-1));
        data[len] = '\0';
        for (int cp=(len-1); cp>=0; cp--)
                data[cp] = mes[cp+1];
        COPYDATASTRUCT CDS_LONG;
        CDS_LONG.lpData = data;
        CDS_LONG.cbData = len+1;
        SendMessageA(EP, WM_COPYDATA, 0, (LPARAM)&CDS_LONG);
        return true;
        }
return false;
}
//---------------------------------------------------------------------------
bool SendMessage_2(AnsiString WindowName)
{
GenBuf();
HWND EP = FindWindow( NULL,WindowName.c_str());
if (!EP)
        EP = FindWindow( NULL,(WindowName+"*").c_str());
if (EP) {
        char data[_2540];
        AnsiString fn = ExtractFilePath(Application->ExeName);
        AnsiString ps = fn + "Show.fpc";
        AnsiString mes = "paste: \"" + ps + "\"";
        int len = MIN(mes.Length(),(_2540-1));
        data[len] = '\0';
        for (int cp=(len-1); cp>=0; cp--)
                data[cp] = mes[cp+1];
        COPYDATASTRUCT CDS_LONG;
        CDS_LONG.lpData = data;
        CDS_LONG.cbData = len+1;
        SendMessageA(EP, WM_COPYDATA, 0, (LPARAM)&CDS_LONG);
        return true;
        }
return false;
}
