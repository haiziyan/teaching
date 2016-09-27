#ifndef _AI_H
#define _AI_H

#include <windows.h>

BOOL WINAPI Ai_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL Ai_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
void Ai_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void Ai_OnClose(HWND hwnd);

#endif