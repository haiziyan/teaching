#ifndef _AI_NEWS_H
#define _AI_NEWS_H

#include <windows.h>

BOOL WINAPI Ai_news_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL Ai_news_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
void Ai_news_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void Ai_news_OnClose(HWND hwnd);

#endif