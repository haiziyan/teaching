#ifndef _PASSWORD_H
#define _PASSWORD_H

#include <windows.h>

BOOL WINAPI Password_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL Password_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
void Password_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void Password_OnClose(HWND hwnd);

#endif