#ifndef _IMPORTSCORE_H
#define _IMPORTSCORE_H

#include <windows.h>

BOOL WINAPI ImportScore_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL ImportScore_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
void ImportScore_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void ImportScore_OnClose(HWND hwnd);

#endif