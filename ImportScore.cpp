#include "stdafx.h"
#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <time.h>
#include "resource.h"
#include "MainView.h"
#include "importscore.h"
#include "somedata.h"

TCHAR filenamescore[256]={0};
BOOL WINAPI ImportScore_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	
    switch(uMsg)
    {
        HANDLE_MSG(hWnd, WM_INITDIALOG, ImportScore_OnInitDialog);
        HANDLE_MSG(hWnd, WM_COMMAND, ImportScore_OnCommand);
		HANDLE_MSG(hWnd,WM_CLOSE, ImportScore_OnClose);
    }

    return FALSE;
}

BOOL ImportScore_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	return true;
}

void ImportScore_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	
    switch(id)
    {
        case IDC_BUTTON_IMPORTFILE:
		
			{
				get_filename(hwnd,filenamescore,IDC_EDIT_FILENAME);
				
				
			}
			
		
        break;
		case IDC_BUTTON_IMPORT:
		
			{
				int ret=0;
				
			    ret = importscore(hwnd,IDC_PROGRESSIMPORT,filenamescore);
				if(ret == 0)
				{
					MessageBox(hwnd,"导入成功","",MB_OK);
					
				}
				
			}
			
		
        break;
		case IDC_truncate:
			{
				int ret = 0;
				ret = truncate(hwnd);
				if(ret == 0)
				{
					MessageBox(hwnd,"清空成功","",MB_OK);
				}
			}
			break;
        default:
		break;
    }
}

void ImportScore_OnClose(HWND hwnd)
{
    EndDialog(hwnd, 0);
}