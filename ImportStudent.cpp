#include "stdafx.h"
#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <time.h>
#include "resource.h"
#include "MainView.h"
#include "importstudent.h"
#include "somedata.h"

TCHAR filenamestudent[256]={0};
BOOL WINAPI ImportStudent_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	
    switch(uMsg)
    {
        HANDLE_MSG(hWnd, WM_INITDIALOG, ImportStudent_OnInitDialog);
        HANDLE_MSG(hWnd, WM_COMMAND, ImportStudent_OnCommand);
		HANDLE_MSG(hWnd,WM_CLOSE, ImportStudent_OnClose);
    }

    return FALSE;
}

BOOL ImportStudent_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	return true;
}

void ImportStudent_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	
    switch(id)
    {
        case IDC_BUTTON_IMPORTFILE:
		
			{
				get_filename(hwnd,filenamestudent,IDC_EDIT_FILENAME);
				
				
			}
			
		
        break;
		case IDC_BUTTON_IMPORT:
		
			{
				int ret=0;
				
			    ret = importstudent(hwnd,IDC_PROGRESSIMPORT,filenamestudent);
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

void ImportStudent_OnClose(HWND hwnd)
{
    EndDialog(hwnd, 0);
}