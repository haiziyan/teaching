#include "stdafx.h"
#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "shellapi.h " //调用网站
#include "resource.h"
#include "MainDlg.h"
#include "MainView.h"
#include "dataoperate.h"
#include "winsock.h"
#include <mysql.h>
#pragma comment(lib,"libmySQL.lib")
#pragma comment(lib,"DataOperate.lib")


BOOL WINAPI Main_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        HANDLE_MSG(hWnd, WM_INITDIALOG, Main_OnInitDialog);
        HANDLE_MSG(hWnd, WM_COMMAND, Main_OnCommand);
		HANDLE_MSG(hWnd,WM_CLOSE, Main_OnClose);
    }

    return FALSE;
}

BOOL Main_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	 
    return TRUE;
}

int LoginFunc(HWND hwnd,TCHAR *pusername)
{
	
	MYSQL *conn=NULL;
	
	TCHAR username[256];
	TCHAR password[256];
	ZeroMemory(username,256);
	ZeroMemory(password,256);
	GetDlgItemText(hwnd,IDC_LOGINUSERNAME,username,256);
	GetDlgItemText(hwnd,IDC_LOGINPASSWORD,password,256);
	
	SetDlgItemText(hwnd,IDC_LOGININFORMTION,"正在连接服务器...");
	if((conn=do_connect())==NULL)
	{
		SetDlgItemText(hwnd,IDC_LOGININFORMTION,"连接失败");
		return 0;
	}
	Sleep(200);
	SetDlgItemText(hwnd, IDC_LOGININFORMTION,"连接成功...");
	Sleep(200);
	SetDlgItemText(hwnd, IDC_LOGININFORMTION,"正在验证用户...");
	if(is_user(conn,username,password)==0){
	Sleep(200);
	SetDlgItemText(hwnd,IDC_LOGININFORMTION,"登录成功");
	lstrcpy(pusername,username);
	Sleep(200);
	do_disconnect(conn);
	return 1;

	
	
	}
	else
	{
		do_disconnect(conn);
		SetDlgItemText(hwnd,IDC_LOGININFORMTION,"用户名或密码错误");
	
	}
	return 0;
}

void Main_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	
	
	HINSTANCE hInstance = (HINSTANCE )GetWindowLong(hwnd,GWL_HINSTANCE);
	

    switch(id)
    {
		
        case IDC_LOGIN:
			{
				int ret =0;
				TCHAR *username=(TCHAR *)malloc(sizeof(TCHAR )*256);
				ret =LoginFunc(hwnd,username);
				if(ret == 1)
				{
					
					EndDialog(hwnd,IDD_MAIN);
					DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_MAINVIEW), NULL, MainView_Proc,(LPARAM)username);
				}
			
			}
        break;
        default:
		break;
    }
}

void Main_OnClose(HWND hwnd)
{
    EndDialog(hwnd, 0);
}