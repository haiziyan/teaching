#include "stdafx.h"
#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <time.h>
#include "resource.h"
#include "MainView.h"
#include "AddId.h"
#include "classon.h"
TCHAR usernameadd[256]={0};
BOOL WINAPI AddId_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        HANDLE_MSG(hWnd, WM_INITDIALOG, AddId_OnInitDialog);
        HANDLE_MSG(hWnd, WM_COMMAND, AddId_OnCommand);
		HANDLE_MSG(hWnd,WM_CLOSE, AddId_OnClose);
    }

    return FALSE;
}

BOOL AddId_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	TCHAR *buff=(TCHAR *)lParam;
	lstrcpy(usernameadd,buff);
	HWND hwnd_combo_add=GetDlgItem(hwnd,IDC_COMBOADD);
	show_course(hwnd,hwnd_combo_add,usernameadd);
    return TRUE;
}

void AddId_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	
    switch(id)
    {
        case IDC_BUTTON_ADD:
		
			{
				HWND hwndcombo=GetDlgItem(hwnd,IDC_COMBOADD);
				int ret = 0;
				ret = add_del_student(hwnd,hwndcombo,IDC_ADDSTUDENTID,usernameadd,1);
				if(ret==0)
				{
					MessageBox(hwnd,"Ìí¼Ó³É¹¦","",MB_OK);
				}
				
				
			}
			
		
        break;
        default:
		break;
    }
}

void AddId_OnClose(HWND hwnd)
{
    EndDialog(hwnd, 0);
}