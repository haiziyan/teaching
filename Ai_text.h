#ifndef _AI_TEXT_H
#define _AI_TEXT_H

#include <windows.h>

BOOL WINAPI Ai_text_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL Ai_text_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
void Ai_text_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void Ai_text_OnClose(HWND hwnd);

#endif