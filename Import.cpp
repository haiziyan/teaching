#include "stdafx.h"
#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <time.h>
#include "resource.h"
#include "MainView.h"
#include "Import.h"
#include "classon.h"
TCHAR username[256]={0};
TCHAR filename[256]={0};
BOOL WINAPI Import_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	
    switch(uMsg)
    {
        HANDLE_MSG(hWnd, WM_INITDIALOG, Import_OnInitDialog);
        HANDLE_MSG(hWnd, WM_COMMAND, Import_OnCommand);
		HANDLE_MSG(hWnd,WM_CLOSE, Import_OnClose);
    }

    return FALSE;
}

BOOL Import_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	TCHAR *buff;
	buff=(TCHAR *)lParam;
	lstrcpy(username,buff);
    return TRUE;
}

void Import_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	
    switch(id)
    {
        case IDC_BUTTON_IMPORTFILE:
		
			{
				get_filename(hwnd,filename,IDC_EDIT_FILENAME);
				
				
			}
			
		
        break;
		case IDC_BUTTON_IMPORT:
		
			{
				int ret=0;
				
			    ret = import(hwnd,IDC_CLASSNAME,IDC_CLASSID,IDC_PROGRESSIMPORT,username,filename);
				if(ret == 0)
				{
					MessageBox(hwnd,"导入成功","",MB_OK);
					EndDialog(hwnd,IDD_IMPORT);
				}
				
			}
			
		
        break;
        default:
		break;
    }
}

void Import_OnClose(HWND hwnd)
{
    EndDialog(hwnd, 0);
}