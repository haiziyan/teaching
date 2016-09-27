#include "stdafx.h"
#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <time.h>
#include "resource.h"
#include "MainView.h"
#include "captcha.h"

BOOL WINAPI MainCaptcha_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        HANDLE_MSG(hWnd, WM_INITDIALOG, MainCaptcha_OnInitDialog);
        HANDLE_MSG(hWnd, WM_COMMAND, MainCaptcha_OnCommand);
		HANDLE_MSG(hWnd,WM_CLOSE, MainCaptcha_OnClose);
    }

    return FALSE;
}

BOOL MainCaptcha_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	TCHAR *buff = NULL;
	
	buff=(TCHAR *)lParam;
	SetDlgItemText(hwnd,IDC_CAPTCHA,buff);
	
    return TRUE;
}

void MainCaptcha_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	
    
}

void MainCaptcha_OnClose(HWND hwnd)
{
    EndDialog(hwnd, 0);
}