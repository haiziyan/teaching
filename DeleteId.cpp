#include "stdafx.h"
#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <time.h>
#include "resource.h"
#include "MainView.h"
#include "DeleteId.h"
#include "classon.h"

TCHAR usernamedel[256]={0};
BOOL WINAPI DeleteId_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        HANDLE_MSG(hWnd, WM_INITDIALOG, DeleteId_OnInitDialog);
        HANDLE_MSG(hWnd, WM_COMMAND, DeleteId_OnCommand);
		HANDLE_MSG(hWnd,WM_CLOSE, DeleteId_OnClose);
    }

    return FALSE;
}

BOOL DeleteId_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	TCHAR *buff=(TCHAR *)lParam;
	lstrcpy(usernamedel,buff);
	HWND hwnd_combo_del=GetDlgItem(hwnd,IDC_COMBODELETE);
	show_course(hwnd,hwnd_combo_del,usernamedel);
    return TRUE;
}

void DeleteId_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	HINSTANCE hInstance = (HINSTANCE )GetWindowLong(hwnd,GWL_HINSTANCE);
    switch(id)
    {
        case IDC_BUTTON_DELETE:
		
			{
				
				HWND hwndcombo=GetDlgItem(hwnd,IDC_COMBODELETE);
				int ret = 0;
				ret = add_del_student(hwnd,hwndcombo,IDC_DELETESTUDENTID,usernamedel,0);
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

void DeleteId_OnClose(HWND hwnd)
{
    EndDialog(hwnd, 0);
}