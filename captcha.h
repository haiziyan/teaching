#ifndef _CAPTCHA_H
#define _CAPTCHA_H

#include <windows.h>

BOOL WINAPI MainCaptcha_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL MainCaptcha_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
void MainCaptcha_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void MainCaptcha_OnClose(HWND hwnd);

#endif