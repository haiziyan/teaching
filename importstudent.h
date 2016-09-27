#ifndef _IMPORTSTUDENT_H
#define _IMPORTSTUDEN_H

#include <windows.h>

BOOL WINAPI ImportStudent_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL ImportStudent_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
void ImportStudent_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void ImportStudent_OnClose(HWND hwnd);

#endif