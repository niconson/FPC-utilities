//---------------------------------------------------------------------------


#pragma hdrstop

#include "KEY.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


void KEY (AnsiString KEY, bool KeyDown, bool KeyUp, int Pause)
        {
        INPUT inp[2];
        memset(inp,0,sizeof(inp));
        if (KeyDown)
                {
                //Нажимаем...
                inp[0].type=INPUT_KEYBOARD;
                if (KEY.UpperCase().SubString(1,3) == "ALT" )   inp[0].ki.wVk=VK_MENU;
                if (KEY.UpperCase().SubString(1,2) == "UP" )    inp[0].ki.wVk=VK_UP;
                if (KEY.UpperCase().SubString(1,4) == "DOWN" )  inp[0].ki.wVk=VK_DOWN;
                if (KEY.UpperCase().SubString(1,4) == "LEFT" )  inp[0].ki.wVk=VK_LEFT;
                if (KEY.UpperCase().SubString(1,5) == "RIGHT" ) inp[0].ki.wVk=VK_RIGHT;
                if (KEY.UpperCase().SubString(1,5) == "ENTER" ) inp[0].ki.wVk=VK_RETURN;
                if (KEY.UpperCase().SubString(1,4) == "CTRL" )  inp[0].ki.wVk=VK_CONTROL;
                if (KEY.UpperCase().SubString(1,1) == "V" )     inp[0].ki.wVk= 'V';
                if (KEY.UpperCase().SubString(1,3) == "ESC" )   inp[0].ki.wVk=VK_ESCAPE;
                if (KEY.UpperCase().SubString(1,2) == "F4" )    inp[0].ki.wVk=VK_F4;
                if (KEY.UpperCase().SubString(1,2) == "F1" )    inp[0].ki.wVk=VK_F1;
                if (KEY.UpperCase().SubString(1,3) == "TAB" )   inp[0].ki.wVk=VK_TAB;
                if (KEY.UpperCase().SubString(1,4) == "HOME" )  inp[0].ki.wVk=VK_HOME;
                }
        if (KeyUp)
                {
                // Отжимаем...
                inp[1].type=INPUT_KEYBOARD;
                if (KEY.UpperCase().SubString(1,3) == "ALT" )   inp[1].ki.wVk=VK_MENU;
                if (KEY.UpperCase().SubString(1,2) == "UP" )    inp[1].ki.wVk=VK_UP;
                if (KEY.UpperCase().SubString(1,4) == "DOWN" )  inp[1].ki.wVk=VK_DOWN;
                if (KEY.UpperCase().SubString(1,4) == "LEFT" )  inp[1].ki.wVk=VK_LEFT;
                if (KEY.UpperCase().SubString(1,5) == "RIGHT" ) inp[1].ki.wVk=VK_RIGHT;
                if (KEY.UpperCase().SubString(1,5) == "ENTER" ) inp[1].ki.wVk=VK_RETURN;
                if (KEY.UpperCase().SubString(1,4) == "CTRL" )  inp[1].ki.wVk=VK_CONTROL;
                if (KEY.UpperCase().SubString(1,1) == "V" )     inp[1].ki.wVk= 'V';
                if (KEY.UpperCase().SubString(1,3) == "ESC" )   inp[1].ki.wVk=VK_ESCAPE;
                if (KEY.UpperCase().SubString(1,2) == "F4" )    inp[1].ki.wVk=VK_F4;
                if (KEY.UpperCase().SubString(1,2) == "F1" )    inp[1].ki.wVk=VK_F1;
                if (KEY.UpperCase().SubString(1,3) == "TAB" )   inp[1].ki.wVk=VK_TAB;
                if (KEY.UpperCase().SubString(1,4) == "HOME" )  inp[1].ki.wVk=VK_HOME;
                inp[1].ki.dwFlags=KEYEVENTF_KEYUP;
                }
        //Посылаем имитацию нажатий в систему
        SendInput(2,inp,sizeof(INPUT));
        Sleep(Pause);
        return;
        }