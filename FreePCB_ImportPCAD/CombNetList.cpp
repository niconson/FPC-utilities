//---------------------------------------------------------------------------


#pragma hdrstop

#include "CombNetList.h"
#include "HEAD.h"
#include "LSTBXS.h"
#include "fstream.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)


void CombNetList (AnsiString OpenD, long CNT)
{
long i;
char str[MAX_CHARS];
AnsiString A;
AnsiString B = ExtractFilePath (Application->ExeName)  ;
ofstream V;
V.open((B + "Import_Tango\\NetListVias.txt").c_str(), std::ios_base::app );
V << "end";
V << endl;
V.close();
Sleep (300);
Form1->Label4->Caption = "Combining netlists ..." ;
Application->ProcessMessages();

// Combine NetList:

// NetList.txt
B = ExtractFilePath (Application->ExeName)  ;
B = B + "Import_Tango\\NetList.txt";
ifstream NetList (B.c_str());

//�������� CombNetList.txt
B = ExtractFilePath (Application->ExeName)  ;
B = B + "Import_Tango\\CombNetList.txt";
ofstream CombNetList (B.c_str());
CombNetList << "net: \"Unconnected_Area.\"" << endl;
int indexPin = 0;
AnsiString net;
while (1)
        {
        NetList.getline(str,sizeof(str));
        A = str;
        A = A.Trim();
        if (A.SubString(1,3) == "end" ) break;
        if (A.SubString(1,3) == "pin" )
                {
                indexPin++;
                i = prob (A,1);
                CombNetList << "pin: ";
                CombNetList << indexPin;
                CombNetList << " ";
                CombNetList << A.SubString(i,(A.Length()-i+1)).c_str() << endl;
                Form2->StringGrid1->Cells[0][Form2->StringGrid1->Row] = A.SubString(i,(A.Length()-i+1));
                Form2->StringGrid1->Cells[1][Form2->StringGrid1->Row] = AnsiString(indexPin-1);
                Form2->StringGrid1->Cells[2][Form2->StringGrid1->Row] = net;
                Form2->StringGrid1->RowCount++;
                Form2->StringGrid1->Row++;
                Form2->StringGrid1->Cells[0][Form2->StringGrid1->Row] = "";
                Form2->StringGrid1->Cells[1][Form2->StringGrid1->Row] = "-1";
                Form2->StringGrid1->Cells[2][Form2->StringGrid1->Row] = "Unconnected";
                }
        else    CombNetList << A.c_str() << endl;
        if (A.SubString(1,3) == "net" )
                {
                indexPin = 0;
                Form1->Label4->Caption = "Combine netList: " + A ;
                Application->ProcessMessages();
                i = prob (A,1);
                net = ex_str (A, &i) ;
                // NetListVias.txt
                B = ExtractFilePath (Application->ExeName)  ;
                B = B + "Import_Tango\\NetListVias.txt";
                ifstream NetListVias (B.c_str());
                AnsiString net2;
                while (B.SubString(1,3) != "end" )
                        {
                        NetListVias.getline(str,sizeof(str));
                        B = str;
                        B = B.Trim();
                        if (B.UpperCase().SubString(1,9) != "FREEPAD__") net2 = B;
                        else
                                {
                                if (net.SubString(1,net.Length()) == net2.SubString(1,net2.Length()))
                                        {
                                        indexPin++;
                                        CombNetList << "pin: ";
                                        CombNetList << indexPin;
                                        CombNetList << " ";
                                        CombNetList <<  B.c_str() << endl;
                                        Form2->StringGrid1->Cells[0][Form2->StringGrid1->Row] = B;
                                        Form2->StringGrid1->Cells[1][Form2->StringGrid1->Row] = AnsiString(indexPin-1);
                                        Form2->StringGrid1->Cells[2][Form2->StringGrid1->Row] = net;
                                        Form2->StringGrid1->RowCount++;
                                        Form2->StringGrid1->Row++;
                                        Form2->StringGrid1->Cells[0][Form2->StringGrid1->Row] = "";
                                        Form2->StringGrid1->Cells[1][Form2->StringGrid1->Row] = "-1";
                                        Form2->StringGrid1->Cells[2][Form2->StringGrid1->Row] = "Unconnected";
                                        }
                                }
                        }
                NetListVias.close();
                }
        }
CombNetList.close();
NetList.close();

Form1->Label4->Caption = "Combining netlists completed!" ;
Application->ProcessMessages();
}