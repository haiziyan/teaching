#ifndef _HOMEWORK_H
#define _HOMEWORK_H

#include <windows.h>

BOOL WINAPI HomeWork_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL HomeWork_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
void HomeWork_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void HomeWork_OnClose(HWND hwnd);

#endif