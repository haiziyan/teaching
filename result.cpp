#include "stdafx.h"
#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "resource.h"
#include "MainDlg.h"
#include "MainView.h"
#include "result.h"
#include "classon.h"
BOOL WINAPI Result_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        HANDLE_MSG(hWnd, WM_INITDIALOG, Result_OnInitDialog);
        HANDLE_MSG(hWnd, WM_COMMAND, Result_OnCommand);
		HANDLE_MSG(hWnd,WM_CLOSE, Result_OnClose);
    }

    return FALSE;
}

BOOL Result_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	TCHAR *courseid=(TCHAR *)lParam;
	int ret = 0;
	ret=result(hwnd,courseid,IDC_STATIC_ActualTotalNumber,IDC_STATIC_ActualToNumber,IDC_STATIC_NotTotheNumberOf,IDC_EDIT_RESULT);
	if(ret!=0)
	{
		EndDialog(hwnd,IDD_RESULT);
	}
    return TRUE;
}

void Result_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	
	
	
    switch(id)
    {
        case 0:
		
			
		
        break;
        default:
		break;
    }
}

void Result_OnClose(HWND hwnd)
{
    EndDialog(hwnd, 0);
}