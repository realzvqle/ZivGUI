#ifndef ZIVGUI_H_INCLUDED
#define ZIVGUI_H_INCLUDED





#include <windows.h>



void InitZivGUI(int width, int height, WCHAR* title);
void CloseZivGUI();
BOOL IsWindowClosed();
void DrawRectangle(int x, int y, int width, int height, COLORREF color);
int GetScreenWidth();
int GetScreenHeight();
void DrawApplication();
int GetMouseX();
int GetMouseY();
#endif