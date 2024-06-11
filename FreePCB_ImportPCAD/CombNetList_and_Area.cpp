//---------------------------------------------------------------------------


#pragma hdrstop

#include "CombNetList_and_Area.h"
#include "HEAD.h"
#include "fstream.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

void CombNetList_and_Area (AnsiString OpenD, long CNT)
{
//ЧТЕНИЕ CombNetList.txt
long i = 0;
char str[MAX_CHARS];
Form1->Label4->Caption = "Reading CombNetList.txt" ;
Application->ProcessMessages();
AnsiString A = ExtractFilePath (Application->ExeName)  ;
A = A + "Import_Tango\\CombNetList.txt";
ifstream read_N (A.c_str());

//Создание Ntlst_and_Area.txt
AnsiString B = ExtractFilePath (Application->ExeName)  ;
B = B + "Import_Tango\\Ntlst_and_Area.txt";
ofstream Ntlst (B.c_str());
AnsiString NET;
AnsiString NET2;
while (A.SubString(1,3) != "end")
        {
        if (A.SubString(1,3) == "net")
                {
                i = prob(A,1);
                NET = ex_str (A, &i);
                Ntlst << A.c_str() << endl;
                read_N.getline(str,sizeof(str));
                A = str;
                A = A.Trim();
                int CPins = 0;
                while (A.SubString(1,3) == "pin")
                        {
                        CPins++;
                        Ntlst << A.c_str() << endl;
                        read_N.getline(str,sizeof(str));
                        A = str;
                        A = A.Trim();
                        }
                //добавление Via
                i = Form1->ListBox4_Lines->Items->IndexOf(NET);
                while (i >= 0)
                        {
                        B = Form1->ListBox4_Lines->Items->operator [](i+1);
                        Form1->ListBox4_Lines->Items->Delete(i);
                        Form1->ListBox4_Lines->Items->Delete(i);
                        CPins++;
                        Ntlst << ("pin: " + AnsiString(CPins) + " " + B).c_str() << endl;
                        i = Form1->ListBox4_Lines->Items->IndexOf(NET);
                        }

                //чтение Trace.TXT
                B = ExtractFilePath (Application->ExeName)  ;
                B = B + "Import_Tango\\Trace.txt";            //чтение Trace.TXT
                ifstream read_Trace (B.c_str());
                B = "";
                NET2 = "";
                while (B.SubString(1,3) != "end")
                        {
                        if (B.SubString(1,3) == "net")
                                {
                                i = prob(B,1);
                                NET2 = ex_str (B, &i);
                                }
                        if (NET.SubString(1,NET.Length()) == NET2.SubString(1,NET2.Length()))
                        if (B.SubString(1,3) != "net")
                                {
                                Ntlst << B.c_str() << endl;
                                }
                        read_Trace.getline(str,sizeof(str));
                        B = str;
                        B = B.Trim();
                        }
                read_Trace.close();

                //чтение AREA.TXT
                B = ExtractFilePath (Application->ExeName)  ;
                B = B + "Import_Tango\\Area.txt";            //чтение AREA.TXT
                ifstream read_Area (B.c_str());
                B = "";
                NET2 = "";
                while (B.SubString(1,3) != "end")
                        {
                        if (B.SubString(1,3) == "net")
                                {
                                i = prob(B,1);
                                NET2 = ex_str (B, &i);
                                }
                        if (NET.SubString(1,NET.Length()) == NET2.SubString(1,NET2.Length()))
                        if (B.SubString(1,3) != "net")
                                {
                                Ntlst << B.c_str() << endl;
                                }
                        read_Area.getline(str,sizeof(str));
                        B = str;
                        B = B.Trim();
                        }
                read_Area.close();
                }
        else    {
                read_N.getline(str,sizeof(str));
                A = str;
                A = A.Trim();
                }
        }
Ntlst << "end" << endl;
Ntlst.close();
read_N.close();

}
