// Person.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "winsock.h"
#include <mysql.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "dataoperate.h"
#include <windows.h>
#include <windowsx.h>
#include <time.h>
#include <commdlg.h>

#include <Commctrl.h>  
#pragma comment(lib,"libmySQL.lib")
#pragma comment(lib,"DataOperate.lib")

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

extern "C"_declspec(dllexport) int person(HWND hwnd,TCHAR *username,int nID_name,int nID_phone,int nID_wechat,int nID_qq)
{
	TCHAR Name[256]={0};
	TCHAR Phone[256]={0};
	TCHAR Wechat[256]={0};
	TCHAR QQ[256]={0};
	TCHAR sql[256]={0};
	MYSQL *conn=NULL;
	GetDlgItemText(hwnd,nID_name,Name,256);
	GetDlgItemText(hwnd,nID_phone,Phone,256);
	GetDlgItemText(hwnd,nID_wechat,Wechat,256);
	GetDlgItemText(hwnd,nID_qq,QQ,256);
	
	conn=do_connect();
	if(conn==NULL)
	{
		MessageBox(hwnd,"请检测网络连接1","",MB_OK);
		return -1;
	}
	mysql_query(conn,"set character set gbk");//读库 
	mysql_query(conn,"set names gbk");//写库 
	wsprintf(sql,"update xTeacher_info set TeacherName='%s',PhoneNumber='%s',Weixin='%s',QQ='%s' where UserName=%s",Name,Phone,Wechat,QQ,username);
	if(mysql_query(conn,sql)!=0)
	{
		MessageBox(hwnd,"请检查网络连接2","",MB_OK);
		do_disconnect(conn);
		return -1;
	}
	return 0;
}
extern "C"_declspec(dllexport) int password(HWND hwnd,TCHAR *username,int nID_old,int nID_new,int nID_newagain)
{
	TCHAR old[256]={0};
	TCHAR tmpold[256]={0};
	TCHAR newpassword[256]={0};
	TCHAR newpasswordagain[256]={0};
	TCHAR sql[256]={0};
	MYSQL_RES *res_set;
	MYSQL_ROW row;
	MYSQL *conn=NULL;
	GetDlgItemText(hwnd,nID_old,old,256);
	GetDlgItemText(hwnd,nID_new,newpassword,256);
	GetDlgItemText(hwnd,nID_newagain,newpasswordagain,256);
	if(lstrlen(old)==0 || lstrlen(newpassword)==0 ||lstrlen(newpasswordagain)==0)
	{
		MessageBox(hwnd,"请填写完整","",MB_OK);
		return -1;
	}
	if(lstrcmp(newpassword,newpasswordagain)!=0)
	{
		MessageBox(hwnd,"两次密码输入不一致","",MB_OK);
		return -1;
	}
	conn=do_connect();
	if(conn==NULL)
	{
		MessageBox(hwnd,"请检测网络连接","",MB_OK);
		return -1;
	}
	mysql_query(conn,"set character set gbk");//读库 
	mysql_query(conn,"set names gbk");//写库 
	wsprintf(sql,"select * from xTeacher_user where UserName=%s ",username);
	if(mysql_query(conn,sql)!=0)
	{
		MessageBox(hwnd,"请检查网络连接","",MB_OK);
		do_disconnect(conn);
		return -1;
	}
	res_set=mysql_store_result(conn);
	
	row=mysql_fetch_row(res_set);
	if(row==NULL)
	{
		MessageBox(hwnd,"请检查网络连接","",MB_OK);
		mysql_free_result(res_set);
		do_disconnect(conn);
		return -1;
	}
	wsprintf(tmpold,"%s",row[2]);
	if(lstrcmp(old,tmpold)!=0)
	{
		MessageBox(hwnd,"原始密码错误","",MB_OK);
		mysql_free_result(res_set);
		do_disconnect(conn);
		return -1;
	}
	mysql_free_result(res_set);
	ZeroMemory(sql,256);
	wsprintf(sql,"update xTeacher_user set Password='%s' where UserName=%s",newpassword,username);
	
	if(mysql_query(conn,sql)!=0)
	{
		MessageBox(hwnd,"请检查网络连接","",MB_OK);
		do_disconnect(conn);
		return -1;
	}

	do_disconnect(conn);
	return 0;
}