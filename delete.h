#ifndef _DELETE_H
#define _DELETE_H

#include <windows.h>

BOOL WINAPI DELETE_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL DELETE_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
void DELETE_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void DELETE_OnClose(HWND hwnd);

#endif