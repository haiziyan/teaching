#ifndef _KNOWLEDGEPOINT_H
#define _KNOWLEDGEPOINT_H

#include <windows.h>

BOOL WINAPI KnowledgePoint_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL KnowledgePoint_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
void KnowledgePoint_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void KnowledgePoint_OnClose(HWND hwnd);

#endif