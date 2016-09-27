#ifndef _AI_MUSIC_H
#define _AI_MUSIC_H

#include <windows.h>

BOOL WINAPI Ai_music_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL Ai_music_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
void Ai_music_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void Ai_music_OnClose(HWND hwnd);

#endif