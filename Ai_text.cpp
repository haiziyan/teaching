#include "stdafx.h"
#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <time.h>
#include "resource.h"
#include "MainView.h"
#include "Ai_text.h"
#include "Ailib.h"

BOOL WINAPI Ai_text_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        HANDLE_MSG(hWnd, WM_INITDIALOG, Ai_text_OnInitDialog);
        HANDLE_MSG(hWnd, WM_COMMAND, Ai_text_OnCommand);
		HANDLE_MSG(hWnd,WM_CLOSE, Ai_text_OnClose);
    }

    return FALSE;
}

BOOL Ai_text_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	
    return TRUE;
}

void Ai_text_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	
    switch(id)
    {
        case IDC_BUTTONTEXT:
		
			{
				int ret = 0;
				ret = Add_text(hwnd, IDC_KEYWORD, IDC_CONTENT);
				if(ret == 0)
				{
					MessageBox(hwnd, "Ìí¼Ó³É¹¦", "",MB_OK);
				}
			}
			
		
        break;
        default:
		break;
    }
}

void Ai_text_OnClose(HWND hwnd)
{
    EndDialog(hwnd, 0);
}