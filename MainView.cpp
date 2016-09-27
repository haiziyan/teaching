#include "stdafx.h"
#include <windows.h>

#include <windowsx.h>
#include <stdlib.h>
#include <time.h>
#include "resource.h"
#include "MainView.h"
#include "captcha.h"
#include "result.h"
#include "winsock.h" 
#include "mysql.h"
#include "Import.h"
#include "AddId.h"
#include "DeleteId.h"
#include "delete.h"
#include "password.h"
#include "personinformation.h"
#include "classon.h"
#include "classoff.h"
#include "homework.h"
#include "knowledgepoint.h"
#include "person.h"
#include "about.h"
#include "ai.h"
#include "importscore.h"
#include "importteacher.h"
#include "importstudent.h"
#include "somedata.h"
#include "url.h"
#include "Ailib.h"
#include <shellapi.h>
#pragma comment(lib,"ClassOn.lib")
#pragma comment(lib,"ClassOff.lib")
#pragma comment(lib,"Person.lib")
#pragma comment(lib,"SomeData.lib")
#pragma comment(lib,"Ai.lib")
TCHAR USERNAME[256]={0};
TCHAR COURSEID[256]={0};
BOOL WINAPI MainView_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        HANDLE_MSG(hWnd, WM_INITDIALOG, MainView_OnInitDialog);
        HANDLE_MSG(hWnd, WM_COMMAND, MainView_OnCommand);
		HANDLE_MSG(hWnd,WM_CLOSE, MainView_OnClose);
    }

    return FALSE;
}

BOOL MainView_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	TCHAR *username = NULL;
	
	username=(TCHAR *)lParam;
	lstrcpy(USERNAME,username);
	HWND hwnd_combo_course=GetDlgItem(hwnd,IDC_COMBOCOURSE);
	show_course(hwnd,hwnd_combo_course,username);
	
    return TRUE;
}

void MainView_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	HINSTANCE hInstance = (HINSTANCE )GetWindowLong(hwnd,GWL_HINSTANCE);
    switch(id)
    {
        case IDC_BUTTON_DIANMING:
		
			{
				TCHAR identifycode[30];
				int ret=0;
				HWND hwnd_combo_course=GetDlgItem(hwnd,IDC_COMBOCOURSE);
				ret=dianming(hwnd,hwnd_combo_course,USERNAME,identifycode,COURSEID);
				if(ret==0)
				{
				DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_CAPTCHA), NULL, MainCaptcha_Proc,(LPARAM)identifycode);
				}
			}
			
		
        break;
		case IDC_BUTTON_RESULT:
			{
				
				if(strlen(COURSEID)==0)
				{
					MessageBox(hwnd,"请先选择课程或点名","",MB_OK);
					break;
				}
				DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_RESULT), NULL, Result_Proc,(LPARAM)COURSEID);
			}
			break;
				case ID_MENUITEMIMPORT:
			{
				
				
				DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_IMPORT), NULL, Import_Proc,(LPARAM)USERNAME);
			}
			break;
				case ID_MENUITEMIMPORTSCORE:
			{
				
				
				DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_IMPORTSCORE), NULL, ImportScore_Proc,(LPARAM)USERNAME);
			}
			break;
				case ID_MENUITEMIMPORTTEACHER:
			{
				
				
				DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_IMPORTTEACHER), NULL, ImportTeacher_Proc,(LPARAM)USERNAME);
			}
			break;
				case ID_MENUITEMIMPORTSTUDENT:
			{
				
				
				DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_IMPORTSTUDENT), NULL, ImportStudent_Proc,(LPARAM)USERNAME);
			}
			break;
				case ID_MENUITEMADDID:
			{
				
				DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_ADDID), NULL, AddId_Proc,(LPARAM)USERNAME);
			}
			break;
			case ID_MENUITEMDELETEID:
			{
				
				
				DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DELETEID), NULL, DeleteId_Proc,(LPARAM)USERNAME);
			}
			break;
			case ID_MENUITE_DELETE:
			{
				
				
				DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DELETE), NULL, DELETE_Proc,(LPARAM)USERNAME);
			}
			break;
			case ID_MENUITEMIMPORT_KNOWLEDGEPOINT:
			{
				
				
				DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_KNOWLEDGEPOINT), NULL, KnowledgePoint_Proc,(LPARAM)USERNAME);
			}
			break;
			case ID_MENUITEM_HOMEWORK:
			{
				
				
				DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_HOMEWORK), NULL, HomeWork_Proc,(LPARAM)USERNAME);
			}
			break;
				case ID_MENUITEMIMPORT_URL:
			{
				
				
				DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_ADDURL), NULL, Url_Proc,(LPARAM)USERNAME);
			}
			break;
			case ID_MENUITEMWEIXINWORK:
			{
				
				ShellExecute(hwnd, "open", "http://waywant.com/kaoshi/",NULL,NULL,SW_SHOWNORMAL);
				
			}
			break;
			case ID_MENUITEMPASSWORD:
			{
				
				
				DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_CHANGEPASSWORD), NULL, Password_Proc,(LPARAM)USERNAME);
			}
			break;
			
			case ID_MENUITEMPERSONINFORMATION:
			{
				
				
				DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_PERSONINFORMATION), NULL, Person_Proc,(LPARAM)USERNAME);
			}
			break;
			case ID_MENUITEMHELP:
			{
				
				ShellExecute(hwnd, "open", "http://waywant.com",NULL,NULL,SW_SHOWNORMAL);
				
			}
			break;
			case ID_MENUITEMABOUT:
			{
				
				
				DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_ABOUT), NULL, About_Proc,NULL);
			}
			break;
			case ID_MENUITEMAI:
			{
				
				
				DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_AI), NULL, Ai_Proc,NULL);
			}
			break;
        default:
		break;
    }
}

void MainView_OnClose(HWND hwnd)
{
    EndDialog(hwnd, 0);
}