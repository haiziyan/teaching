#include "stdafx.h"
#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <time.h>
#include "resource.h"
#include "MainView.h"
#include "Ai_news.h"
#include "Ailib.h"

BOOL WINAPI Ai_news_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        HANDLE_MSG(hWnd, WM_INITDIALOG, Ai_news_OnInitDialog);
        HANDLE_MSG(hWnd, WM_COMMAND, Ai_news_OnCommand);
		HANDLE_MSG(hWnd,WM_CLOSE, Ai_news_OnClose);
    }

    return FALSE;
}

BOOL Ai_news_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	
    return TRUE;
}

void Ai_news_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	
    switch(id)
    {
        case IDC_BUTTONNEWS:
		
			{
				
				int ret = 0;
				ret = Add_news(hwnd, IDC_KEYWORD, IDC_TITLE, IDC_PICURL, IDC_URL, IDC_DESCRIPTION);
				if(ret == 0)
				{
					MessageBox(hwnd, "Ìí¼Ó³É¹¦","",MB_OK);
				}
			}
			
		
        break;
        default:
		break;
    }
}

void Ai_news_OnClose(HWND hwnd)
{
    EndDialog(hwnd, 0);
}