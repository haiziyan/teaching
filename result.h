#ifndef _RESULT_H
#define _RESULT_H

#include <windows.h>

BOOL WINAPI Result_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL Result_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
void Result_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void Result_OnClose(HWND hwnd);

#endif