#ifndef _IMPORTTEACHER_H
#define _IMPORTTEACHER_H

#include <windows.h>

BOOL WINAPI ImportTeacher_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL ImportTeacher_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
void ImportTeacher_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void ImportTeacher_OnClose(HWND hwnd);

#endif