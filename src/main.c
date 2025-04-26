#include "zivGUI/zivgui.h"
#include <time.h>
#include <wchar.h>
#include <windows.h>
#include <wingdi.h>
#include <winuser.h>




int wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd){
    InitZivGUI(800, 600, L"hello");
    // IsWindowClosed() refreshes the entire screen so it doesn't look like its cloning
    while(!IsWindowClosed()){
        DrawApplication();
    }
    CloseZivGUI();

    return 0;
}



