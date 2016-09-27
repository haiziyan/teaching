// ClassOff.cpp : Defines the entry point for the DLL application.
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

extern "C"_declspec(dllexport) int Add_text(HWND hwnd, int nId_keyword, int nId_content)
{
	int ret = 0;
	TCHAR keyword[256] = {0};
	TCHAR content[10000] = {0};
	TCHAR sql[256] = {0};
	MYSQL *conn = NULL;
	MYSQL_RES *res_set;
	GetDlgItemText(hwnd, nId_keyword, keyword,256);
	GetDlgItemText(hwnd, nId_content, content, 10000);
	if(lstrlen(keyword) == 0 || lstrlen(content) == 0)
	{
		MessageBox(hwnd,"不能为空","错误信息",MB_OK);
		return -1;
	}
	conn = do_connect();
	if(conn == NULL)
	{
		MessageBox(hwnd,"请检测网络连接","",MB_OK);
		return -1;
	}
	mysql_query(conn,"set character set gbk");//读库 
	mysql_query(conn,"set names gbk");//写库 
	wsprintf(sql,"select * from xAi_recover where keyword='%s'",keyword);
	if(mysql_query(conn,sql)!=0)
	{
		MessageBox(hwnd,"请检查网络连接","",MB_OK);
		do_disconnect(conn);
		return -1;
	}
	res_set=mysql_store_result(conn);
	if(mysql_num_rows(res_set)!=0)
	{
		MessageBox(hwnd,"关键词已存在，关键词一旦录入，便永久存在，不提供修改。\n为什么？\n因为我想保存这些作为一个纪念。","",MB_OK);
		mysql_free_result(res_set);
		do_disconnect(conn);
		return -1;
	}
	wsprintf(sql,"insert into xAi_recover (keyword,type,content) values ('%s','%s','%s')",keyword,"text",content);
	if(mysql_query(conn,sql)!=0)
	{
		MessageBox(hwnd,"请检查网络连接","",MB_OK);
		do_disconnect(conn);
		return -1;
	}
	do_disconnect(conn);
	return ret ;
}

extern "C"_declspec(dllexport) int Add_news(HWND hwnd, int nId_keyword, int nId_title, int nId_picurl, int nId_url, int nId_description)
{
	int ret = 0;
	TCHAR keyword[256] = {0};
	TCHAR title[256] = {0};
	TCHAR picurl[256] = {0};
	TCHAR url[256] = {0};
	TCHAR description[10000] = {0};
	TCHAR sql[256] = {0};
	MYSQL *conn = NULL;
	MYSQL_RES *res_set;
	GetDlgItemText(hwnd, nId_keyword, keyword,256);
	GetDlgItemText(hwnd, nId_title, title, 256);
	GetDlgItemText(hwnd, nId_picurl, picurl, 256);
	GetDlgItemText(hwnd, nId_url, url, 256);
	GetDlgItemText(hwnd, nId_description, description, 10000);
	if(lstrlen(keyword) == 0 || lstrlen(description) == 0 || lstrlen(title) == 0)
	{
		MessageBox(hwnd,"不能为空","错误信息",MB_OK);
		return -1;
	}
	conn = do_connect();
	if(conn == NULL)
	{
		MessageBox(hwnd,"请检测网络连接","",MB_OK);
		return -1;
	}
	mysql_query(conn,"set character set gbk");//读库 
	mysql_query(conn,"set names gbk");//写库 
		wsprintf(sql,"select * from xAi_recover where keyword='%s'",keyword);
	if(mysql_query(conn,sql)!=0)
	{
		MessageBox(hwnd,"请检查网络连接","",MB_OK);
		do_disconnect(conn);
		return -1;
	}
	res_set=mysql_store_result(conn);
	if(mysql_num_rows(res_set)!=0)
	{
		MessageBox(hwnd,"关键词已存在，关键词一旦录入，便永久存在，不提供修改。\n为什么？\n因为我想保存这些作为一个纪念。","",MB_OK);
		mysql_free_result(res_set);
		do_disconnect(conn);
		return -1;
	}
	wsprintf(sql,"insert into xAi_recover (keyword,type,title,picurl,url,description) values ('%s','%s','%s','%s','%s','%s')",keyword,"news",title,picurl,url,description);
	if(mysql_query(conn,sql)!=0)
	{
		MessageBox(hwnd,"请检查网络连接","",MB_OK);
		do_disconnect(conn);
		return -1;
	}
	do_disconnect(conn);
	return ret ;
}

extern "C"_declspec(dllexport) int Add_music(HWND hwnd, int nId_keyword, int nId_musicurl)
{
	int ret = 0;
	TCHAR keyword[256] = {0};
	TCHAR musicurl[256] = {0};
	TCHAR sql[256] = {0};
	MYSQL *conn = NULL;
	MYSQL_RES *res_set;
	GetDlgItemText(hwnd, nId_keyword, keyword,256);
	GetDlgItemText(hwnd, nId_musicurl, musicurl, 10000);
	if(lstrlen(keyword) == 0 || lstrlen(musicurl) == 0)
	{
		MessageBox(hwnd,"不能为空","错误信息",MB_OK);
		return -1;
	}
	conn = do_connect();
	if(conn == NULL)
	{
		MessageBox(hwnd,"请检测网络连接","",MB_OK);
		return -1;
	}
	mysql_query(conn,"set character set gbk");//读库 
	mysql_query(conn,"set names gbk");//写库 
		wsprintf(sql,"select * from xAi_recover where keyword='%s'",keyword);
	if(mysql_query(conn,sql)!=0)
	{
		MessageBox(hwnd,"请检查网络连接","",MB_OK);
		do_disconnect(conn);
		return -1;
	}
	res_set=mysql_store_result(conn);
	if(mysql_num_rows(res_set)!=0)
	{
		MessageBox(hwnd,"关键词已存在，关键词一旦录入，便永久存在，不提供修改。\n为什么？\n因为我想保存这些作为一个纪念。","",MB_OK);
		mysql_free_result(res_set);
		do_disconnect(conn);
		return -1;
	}
	wsprintf(sql,"insert into xAi_recover (keyword,type,musicurl) values ('%s','%s','%s')",keyword,"music",musicurl);
	if(mysql_query(conn,sql)!=0)
	{
		MessageBox(hwnd,"请检查网络连接","",MB_OK);
		do_disconnect(conn);
		return -1;
	}
	do_disconnect(conn);
	return ret ;
}