#include "stdafx.h"
#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <time.h>
#include "resource.h"
#include "MainView.h"
#include "knowledgepoint.h"
#include "classon.h"
#include "classoff.h"
TCHAR usernameaddknow[256]={0};
BOOL WINAPI KnowledgePoint_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        HANDLE_MSG(hWnd, WM_INITDIALOG, KnowledgePoint_OnInitDialog);
        HANDLE_MSG(hWnd, WM_COMMAND, KnowledgePoint_OnCommand);
		HANDLE_MSG(hWnd,WM_CLOSE, KnowledgePoint_OnClose);
    }

    return FALSE;
}

BOOL KnowledgePoint_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	TCHAR *buff=(TCHAR *)lParam;
	lstrcpy(usernameaddknow,buff);
	HWND hwnd_combo_add=GetDlgItem(hwnd,IDC_COMBOKNOWLEDGEPOINT);
	show_course(hwnd,hwnd_combo_add,usernameaddknow);
    return TRUE;
}

void KnowledgePoint_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	HWND hwnd_combo_course=GetDlgItem(hwnd,IDC_COMBOKNOWLEDGEPOINT);
    switch(id)
    {
        case IDC_BUTTONKNOWLEDGEPOINT:
		
			{
				int ret = 0;
				ret = knowledgepoint(hwnd,hwnd_combo_course,usernameaddknow,IDC_EDITKNOWLEDGEPOINT);
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

void KnowledgePoint_OnClose(HWND hwnd)
{
    EndDialog(hwnd, 0);
}