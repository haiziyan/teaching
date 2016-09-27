#include "stdafx.h"
#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <time.h>
#include "resource.h"
#include "MainView.h"
#include "importteacher.h"
#include "somedata.h"

TCHAR filenameteacher[256]={0};
BOOL WINAPI ImportTeacher_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	
    switch(uMsg)
    {
        HANDLE_MSG(hWnd, WM_INITDIALOG, ImportTeacher_OnInitDialog);
        HANDLE_MSG(hWnd, WM_COMMAND, ImportTeacher_OnCommand);
		HANDLE_MSG(hWnd,WM_CLOSE, ImportTeacher_OnClose);
    }

    return FALSE;
}

BOOL ImportTeacher_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	return true;
}

void ImportTeacher_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	
    switch(id)
    {
        case IDC_BUTTON_IMPORTFILE:
		
			{
				get_filename(hwnd,filenameteacher,IDC_EDIT_FILENAME);
				
				
			}
			
		
        break;
		case IDC_BUTTON_IMPORT:
		
			{
				int ret=0;
				
			    ret = importteacher(hwnd,IDC_PROGRESSIMPORT,filenameteacher);
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

void ImportTeacher_OnClose(HWND hwnd)
{
    EndDialog(hwnd, 0);
}