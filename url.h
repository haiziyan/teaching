#ifndef _URL_H
#define _URL_H

#include <windows.h>

BOOL WINAPI Url_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL Url_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
void Url_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void Url_OnClose(HWND hwnd);

#endif