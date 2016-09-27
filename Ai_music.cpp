#include "stdafx.h"
#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <time.h>
#include "resource.h"
#include "MainView.h"
#include "Ai_music.h"
#include "Ailib.h"

BOOL WINAPI Ai_music_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        HANDLE_MSG(hWnd, WM_INITDIALOG, Ai_music_OnInitDialog);
        HANDLE_MSG(hWnd, WM_COMMAND, Ai_music_OnCommand);
		HANDLE_MSG(hWnd,WM_CLOSE, Ai_music_OnClose);
    }

    return FALSE;
}

BOOL Ai_music_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	
    return TRUE;
}

void Ai_music_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	
    switch(id)
    {
        case IDC_BUTTONMUSIC:
		
			{
				int ret = 0;
				ret = Add_music(hwnd, IDC_KEYWORD, IDC_MUSICURL);
				if(ret == 0)
				{
					MessageBox(hwnd, "ÃÌº”ÕÍ≥…","",MB_OK);
				}
				
			}
			
		
        break;
        default:
		break;
    }
}

void Ai_music_OnClose(HWND hwnd)
{
    EndDialog(hwnd, 0);
}