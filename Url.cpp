#include "stdafx.h"
#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <time.h>
#include "resource.h"
#include "MainView.h"
#include "url.h"
#include "classon.h"
#include "classoff.h"
TCHAR usernameurl[256]={0};

BOOL WINAPI Url_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        HANDLE_MSG(hWnd, WM_INITDIALOG, Url_OnInitDialog);
        HANDLE_MSG(hWnd, WM_COMMAND, Url_OnCommand);
		HANDLE_MSG(hWnd,WM_CLOSE, Url_OnClose);
    }

    return FALSE;
}

BOOL Url_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	TCHAR *buff=(TCHAR *)lParam;
	lstrcpy(usernameurl,buff);
	HWND hwnd_combo_add=GetDlgItem(hwnd,IDC_COMBOHOME);
	show_course(hwnd,hwnd_combo_add,usernameurl);
    return TRUE;
}

void Url_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	HWND hwnd_combo_course=GetDlgItem(hwnd,IDC_COMBOHOME);
    switch(id)
    {
        case IDC_BUTTONHOME:
		
			{
			
				int ret = 0;
				ret = url(hwnd,hwnd_combo_course,usernameurl,IDC_EDITHOMEWORK);
				if(ret==0)
				{
					MessageBox(hwnd,"提交成功","",MB_OK);
				}
				
			}
			
		
        break;
        default:
		break;
    }
}

void Url_OnClose(HWND hwnd)
{
    EndDialog(hwnd, 0);
}