#include "stdafx.h"
#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <time.h>
#include "resource.h"
#include "MainView.h"
#include "about.h"


BOOL WINAPI About_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        HANDLE_MSG(hWnd, WM_INITDIALOG, About_OnInitDialog);
        HANDLE_MSG(hWnd, WM_COMMAND, About_OnCommand);
		HANDLE_MSG(hWnd,WM_CLOSE, About_OnClose);
    }

    return FALSE;
}

BOOL About_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	
    return TRUE;
}

void About_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	
    switch(id)
    {
        case IDC_BUTTON_ADD:
		
			{
				
				
				
			}
			
		
        break;
        default:
		break;
    }
}

void About_OnClose(HWND hwnd)
{
    EndDialog(hwnd, 0);
}