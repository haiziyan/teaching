#ifndef _MAINVIEW_H
#define _MAINVIEW_H

#include <windows.h>

BOOL WINAPI MainView_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL MainView_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
void MainView_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void MainView_OnClose(HWND hwnd);

#endif