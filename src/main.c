#include <wchar.h>
#include <windows.h>
#include <winuser.h>




int wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd){
    MessageBoxW(NULL, L"Wassup", L"Wassup", MB_OK | MB_ICONERROR);
    return 0;
}