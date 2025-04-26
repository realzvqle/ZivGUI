#include "zivgui.h"
#include <minwinbase.h>
#include <minwindef.h>
#include <time.h>
#include <wchar.h>
#include <windef.h>
#include <wingdi.h>
#include <winuser.h>


// basic stuff
static HDC s_DC = NULL;
static HDC s_BackDC = NULL;
static HBITMAP s_BackBuffer = NULL;
static BOOL s_IsClosed = FALSE;

// Window static stuff
static int s_WindowX = 10;
static int s_WindowY = 10;
static int s_WindowWidth = 800;
static int s_WindowHeight = 600;
static WCHAR s_WindowTitle[64] = L"Unnamed Window\0";
static BOOL s_FinishedDrawing = FALSE;
static HANDLE s_hDrawThread;
static HANDLE s_hRenderThread;

DWORD WINAPI DrawWindow(LPVOID lpThreadParameter){
    while(s_IsClosed == FALSE){
        s_FinishedDrawing = FALSE;
        DrawRectangle(s_WindowX, s_WindowY, s_WindowWidth, 30, RGB(155, 155, 155));
        DrawRectangle(s_WindowX, s_WindowY + 30, s_WindowWidth, s_WindowHeight, RGB(255, 255, 255));
        s_FinishedDrawing = TRUE;
        Sleep(2000);
    }
    
    return 0;
}

DWORD WINAPI RenderApplication(LPVOID lpThreadParameter) {
    while(s_IsClosed == FALSE){
        if(s_FinishedDrawing == FALSE) continue;
        RECT rect;
        GetClientRect(NULL, &rect);
        InvalidateRect(NULL, &rect, TRUE);
        BitBlt(s_DC, s_WindowX, s_WindowY, s_WindowWidth, s_WindowHeight, 
                    s_BackDC, 0, 0, SRCCOPY);
        Sleep(1);
    }
    
}


void InitZivGUI(int width, int height, WCHAR* title){
    s_WindowWidth = width;
    s_WindowHeight = height;
    swprintf(s_WindowTitle, 512, L"%s", title);
    s_DC = GetDC(NULL);
    s_BackDC = CreateCompatibleDC(s_DC);
    s_BackBuffer = CreateCompatibleBitmap(s_DC, s_WindowWidth, s_WindowHeight);
    SelectObject(s_BackDC, s_BackBuffer);
    s_hDrawThread = CreateThread(NULL, 0, DrawWindow, NULL, 0, NULL);
    s_hRenderThread = CreateThread(NULL, 0, RenderApplication, NULL, 0, NULL);

}

void CloseZivGUI(){
    CloseHandle(s_hDrawThread);
    CloseHandle(s_hRenderThread);
    DeleteDC(s_BackDC);
    DeleteObject(s_BackBuffer);
    DeleteDC(s_DC);
}



HDC ReturnDeviceContext(){
    return s_DC;
}

BOOL IsWindowClosed(){
    if((GetMouseX() - s_WindowX) <= s_WindowWidth && (GetMouseY() - s_WindowY) <= 30){
        while(GetAsyncKeyState('W')){
            s_WindowX = GetMouseX();
            s_WindowY = GetMouseY();
        }
    }
    
    return s_IsClosed;
}

void DrawRectangleEx(int x, int y, int width, int height, COLORREF color, DWORD rop){
    HBRUSH brush = CreateSolidBrush(color);
    SelectObject(s_BackDC, brush);
    for(int i = x; i < (x + width); i++){
        for(int j = y; j < (y + height); j++){
            PatBlt(s_BackDC, i, j, 1, 1, rop);
        }
    }
    DeleteObject(brush);  
}




void DrawRectangle(int x, int y, int width, int height, COLORREF color){
    DrawRectangleEx(x, y, width, height, color, PATCOPY);
}


int GetScreenWidthWithoutDPI(){
    return GetSystemMetrics(SM_CXSCREEN);
}

int GetScreenHeightWithoutDPI(){
    return GetSystemMetrics(SM_CYSCREEN);
}

int GetScreenWidth(){
    int size = GetSystemMetrics(SM_CXSCREEN);
    int dpi = GetDeviceCaps(s_DC, LOGPIXELSX);
    return dpi + size * 6;
}

int GetScreenHeight(){
    int size = GetSystemMetrics(SM_CXSCREEN);
    int dpi = GetDeviceCaps(s_DC, LOGPIXELSX);
    return dpi + size * 6;
}

int GetMouseX(){
    POINT point;
    GetCursorPos(&point);
    return point.x;
}

int GetMouseY(){
    POINT point;
    GetCursorPos(&point);
    return point.y;
}