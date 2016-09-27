#include "stdafx.h"
#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <time.h>
#include "resource.h"
#include "MainView.h"
#include "password.h"
#include "classon.h"
#include "person.h"
TCHAR usernamepassword[256]={0};
BOOL WINAPI Password_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        HANDLE_MSG(hWnd, WM_INITDIALOG, Password_OnInitDialog);
        HANDLE_MSG(hWnd, WM_COMMAND, Password_OnCommand);
		HANDLE_MSG(hWnd,WM_CLOSE, Password_OnClose);
    }

    return FALSE;
}

BOOL Password_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	TCHAR *buff=(TCHAR *)lParam;
	lstrcpy(usernamepassword,buff);
	HWND hwnd_combo_add=GetDlgItem(hwnd,IDC_COMBOADD);
	show_course(hwnd,hwnd_combo_add,usernamepassword);
    return TRUE;
}

void Password_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	
    switch(id)
    {
        case ID_OKPASSWORD:
		
			{
				
				int ret = 0;
				ret = password(hwnd,usernamepassword,IDC_EDITOLD,IDC_EDITNEW,IDC_EDITNEWAGAIN);
				if(ret == 0)
				{
					MessageBox(hwnd,"更改成功。","",MB_OK);
				}
				
			}
			
		
        break;
        default:
		break;
    }
}

void Password_OnClose(HWND hwnd)
{
    EndDialog(hwnd, 0);
}