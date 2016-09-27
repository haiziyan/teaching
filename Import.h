#ifndef _IMPORT_H
#define _IMPORT_H

#include <windows.h>

BOOL WINAPI Import_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL Import_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
void Import_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void Import_OnClose(HWND hwnd);

#endif