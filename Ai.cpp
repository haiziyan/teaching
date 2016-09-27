#include "stdafx.h"
#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <time.h>
#include "resource.h"
#include "MainView.h"
#include "ai.h"
#include "Ai_text.h"
#include "Ai_news.h"
#include "Ai_music.h"


BOOL WINAPI Ai_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        HANDLE_MSG(hWnd, WM_INITDIALOG, Ai_OnInitDialog);
        HANDLE_MSG(hWnd, WM_COMMAND, Ai_OnCommand);
		HANDLE_MSG(hWnd,WM_CLOSE, Ai_OnClose);
    }

    return FALSE;
}

BOOL Ai_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	
    return TRUE;
}

void Ai_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	HINSTANCE hInstance = (HINSTANCE )GetWindowLong(hwnd,GWL_HINSTANCE);
    switch(id)
    {
        case IDC_BUTTON_TEXT:
		
			{
				
			
				DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_TEXT), NULL, Ai_text_Proc,NULL);
			}
			
		
        break;
		case IDC_BUTTON_NEWS:
		
			{
				
			
				DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_NEWS), NULL, Ai_news_Proc,NULL);
			}
			
		
        break;
		case IDC_BUTTON_MUSIC:
		
			{
				
			
				DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_MUSIC), NULL, Ai_music_Proc,NULL);
			}
			
		
        break;
        default:
		break;
    }
}

void Ai_OnClose(HWND hwnd)
{
    EndDialog(hwnd, 0);
}