#ifndef _DELETEID_H
#define _DELETEID_H

#include <windows.h>

BOOL WINAPI DeleteId_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL DeleteId_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
void DeleteId_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void DeleteId_OnClose(HWND hwnd);

#endif