#include "stdafx.h"
#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <time.h>
#include "resource.h"
#include "MainView.h"
#include "personinformation.h"
#include "classon.h"
#include "person.h"
TCHAR usernameperson[256]={0};
BOOL WINAPI Person_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        HANDLE_MSG(hWnd, WM_INITDIALOG, Person_OnInitDialog);
        HANDLE_MSG(hWnd, WM_COMMAND, Person_OnCommand);
		HANDLE_MSG(hWnd,WM_CLOSE, Person_OnClose);
    }

    return FALSE;
}

BOOL Person_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	TCHAR *buff=(TCHAR *)lParam;
	lstrcpy(usernameperson,buff);
	HWND hwnd_combo_add=GetDlgItem(hwnd,IDC_COMBOADD);
	show_course(hwnd,hwnd_combo_add,usernameperson);
    return TRUE;
}

void Person_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	
    switch(id)
    {
        case ID_OKPERSON:
		
			{
				int ret = 0;
				ret = person(hwnd,usernameperson,IDC_EDITNAME,IDC_EDITPHONE,IDC_EDITWECHAT,IDC_EDITQQ);
				if(ret == 0)
				{
					MessageBox(hwnd,"–ª–ªÃ·Ωª£¨“‡ ¶“‡”—°£","",MB_OK);
				}
				
				
			}
			
		
        break;
        default:
		break;
    }
}

void Person_OnClose(HWND hwnd)
{
    EndDialog(hwnd, 0);
}