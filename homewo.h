#ifndef _ADDID_H
#define _ADDID_H

#include <windows.h>

BOOL WINAPI AddId_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL AddId_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
void AddId_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void AddId_OnClose(HWND hwnd);

#endif