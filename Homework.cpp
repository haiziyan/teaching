#include "stdafx.h"
#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <time.h>
#include "resource.h"
#include "MainView.h"
#include "homework.h"
#include "classon.h"
#include "classoff.h"
TCHAR usernamehomework[256]={0};

BOOL WINAPI HomeWork_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        HANDLE_MSG(hWnd, WM_INITDIALOG, HomeWork_OnInitDialog);
        HANDLE_MSG(hWnd, WM_COMMAND, HomeWork_OnCommand);
		HANDLE_MSG(hWnd,WM_CLOSE, HomeWork_OnClose);
    }

    return FALSE;
}

BOOL HomeWork_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	TCHAR *buff=(TCHAR *)lParam;
	lstrcpy(usernamehomework,buff);
	HWND hwnd_combo_add=GetDlgItem(hwnd,IDC_COMBOHOME);
	show_course(hwnd,hwnd_combo_add,usernamehomework);
    return TRUE;
}

void HomeWork_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	HWND hwnd_combo_course=GetDlgItem(hwnd,IDC_COMBOHOME);
    switch(id)
    {
        case IDC_BUTTONHOME:
		
			{
			
				int ret = 0;
				ret = homework(hwnd,hwnd_combo_course,usernamehomework,IDC_EDITHOMEWORK);
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

void HomeWork_OnClose(HWND hwnd)
{
    EndDialog(hwnd, 0);
}