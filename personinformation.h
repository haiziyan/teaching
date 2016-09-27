#ifndef _PERSONINFOR_H
#define _PERSONINFOR_H

#include <windows.h>

BOOL WINAPI Person_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL Person_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
void Person_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void Person_OnClose(HWND hwnd);

#endif