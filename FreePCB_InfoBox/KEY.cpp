//---------------------------------------------------------------------------


#pragma hdrstop

#include "KEY.h"
#include "Comp_man.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

void KEYS (AnsiString key, bool KeyDown, bool KeyUp, int Pause, int REP)
        {
        INPUT inp[2];
        memset(inp,0,sizeof(inp));
        for (int cnt=0; cnt<REP; cnt++)
                {
                if (KeyDown)
                        {
                        //��������...
                        inp[0].type=INPUT_KEYBOARD;
                        if (key.UpperCase().SubString(1,3) == "ALT" )   inp[0].ki.wVk=VK_MENU;
                        if (key.UpperCase().SubString(1,2) == "UP" )    inp[0].ki.wVk=VK_UP;
                        if (key.UpperCase().SubString(1,4) == "DOWN" )  inp[0].ki.wVk=VK_DOWN;
                        if (key.UpperCase().SubString(1,4) == "LEFT" )  inp[0].ki.wVk=VK_LEFT;
                        if (key.UpperCase().SubString(1,5) == "RIGHT" ) inp[0].ki.wVk=VK_RIGHT;
                        if (key.UpperCase().SubString(1,5) == "ENTER" ) inp[0].ki.wVk=VK_RETURN;
                        if (key.UpperCase().SubString(1,4) == "CTRL" )  inp[0].ki.wVk=VK_CONTROL;
                        if (key.UpperCase().SubString(1,1) == "V" )     inp[0].ki.wVk= 'V';
                        if (key.UpperCase().SubString(1,3) == "ESC" )   inp[0].ki.wVk=VK_ESCAPE;
                        if (key.UpperCase().SubString(1,2) == "F4" )    inp[0].ki.wVk=VK_F4;
                        if (key.UpperCase().SubString(1,2) == "F1" )    inp[0].ki.wVk=VK_F1;
                        if (key.UpperCase().SubString(1,2) == "F2" )    inp[0].ki.wVk=VK_F2;
                        if (key.UpperCase().SubString(1,3) == "TAB" )   inp[0].ki.wVk=VK_TAB;
                        if (key.UpperCase().SubString(1,4) == "HOME" )  inp[0].ki.wVk=VK_HOME;
                        if (key.UpperCase().SubString(1,3) == "DEL" )   inp[0].ki.wVk=VK_DELETE;
                        }
                if (KeyUp)
                        {
                        // ��������...
                        inp[1].type=INPUT_KEYBOARD;
                        if (key.UpperCase().SubString(1,3) == "ALT" )   inp[1].ki.wVk=VK_MENU;
                        if (key.UpperCase().SubString(1,2) == "UP" )    inp[1].ki.wVk=VK_UP;
                        if (key.UpperCase().SubString(1,4) == "DOWN" )  inp[1].ki.wVk=VK_DOWN;
                        if (key.UpperCase().SubString(1,4) == "LEFT" )  inp[1].ki.wVk=VK_LEFT;
                        if (key.UpperCase().SubString(1,5) == "RIGHT" ) inp[1].ki.wVk=VK_RIGHT;
                        if (key.UpperCase().SubString(1,5) == "ENTER" ) inp[1].ki.wVk=VK_RETURN;
                        if (key.UpperCase().SubString(1,4) == "CTRL" )  inp[1].ki.wVk=VK_CONTROL;
                        if (key.UpperCase().SubString(1,1) == "V" )     inp[1].ki.wVk= 'V';
                        if (key.UpperCase().SubString(1,3) == "ESC" )   inp[1].ki.wVk=VK_ESCAPE;
                        if (key.UpperCase().SubString(1,2) == "F4" )    inp[1].ki.wVk=VK_F4;
                        if (key.UpperCase().SubString(1,2) == "F1" )    inp[1].ki.wVk=VK_F1;
                        if (key.UpperCase().SubString(1,2) == "F2" )    inp[1].ki.wVk=VK_F2;
                        if (key.UpperCase().SubString(1,3) == "TAB" )   inp[1].ki.wVk=VK_TAB;
                        if (key.UpperCase().SubString(1,4) == "HOME" )  inp[1].ki.wVk=VK_HOME;
                        if (key.UpperCase().SubString(1,3) == "DEL" )   inp[1].ki.wVk=VK_DELETE;
                        inp[1].ki.dwFlags=KEYEVENTF_KEYUP;
                        }
                //�������� �������� ������� � �������
                SendInput(2,inp,sizeof(INPUT));
                Sleep(Pause);
                }
        }