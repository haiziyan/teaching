#include "stdafx.h"
#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <time.h>
#include "resource.h"
#include "MainView.h"
#include "delete.h"
#include "classon.h"
TCHAR usernamedelete[256]={0};
BOOL WINAPI DELETE_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        HANDLE_MSG(hWnd, WM_INITDIALOG, DELETE_OnInitDialog);
        HANDLE_MSG(hWnd, WM_COMMAND, DELETE_OnCommand);
		HANDLE_MSG(hWnd,WM_CLOSE, DELETE_OnClose);
    }

    return FALSE;
}

BOOL DELETE_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	TCHAR *buff=(TCHAR *)lParam;
	lstrcpy(usernamedelete,buff);
	HWND hwnd_combo_del=GetDlgItem(hwnd,IDC_COMBO_DEL);
	show_course(hwnd,hwnd_combo_del,usernamedelete);
    return TRUE;
}

void DELETE_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	
    switch(id)
    {
        case IDC_BUTTON_DEL:
		
			{
				HWND hwndcombo=GetDlgItem(hwnd,IDC_COMBO_DEL);
				int ret = 0;
				ret = deletecourse(hwnd,hwndcombo,usernamedelete);
				if(ret==0)
				{
					
					MessageBox(hwnd,"É¾³ý³É¹¦","",MB_OK);
					
				}
				
				
			}
			
		
        break;
        default:
		break;
    }
}

void DELETE_OnClose(HWND hwnd)
{
    EndDialog(hwnd, 0);
}