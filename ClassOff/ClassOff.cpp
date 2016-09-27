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
extern "C"_declspec(dllexport) int homework(HWND hwnd,HWND hwnd_combo_course,TCHAR *username,int nID_homework)
{
	int index;
	TCHAR coursechoose[256]={0};
	TCHAR homework[1024]={0};
	MYSQL *conn=NULL;
	TCHAR sql[256]={0};
	TCHAR courseid[256]={0};
	MYSQL_RES *res_set;
	MYSQL_ROW row;
	TCHAR DBName[256]={0};
	
	ZeroMemory(sql,256);
	ZeroMemory(courseid,256);
	ZeroMemory(DBName,256);
	ZeroMemory(homework,1024);
	GetDlgItemText(hwnd,nID_homework,homework,1024);
	index=ComboBox_GetCurSel(hwnd_combo_course);//未选择时返回-1
	if(index==-1)
	{
		MessageBox(hwnd,"请先选择课程","",MB_OK);
		return -1;
	}
	if(lstrlen(homework)==0)
	{
		MessageBox(hwnd,"请输入要布置的课后作业","",MB_OK);
		return -1;
	}
	ComboBox_GetLBText(hwnd_combo_course,index,coursechoose);
	conn=do_connect();
	if(conn==NULL)
	{
		MessageBox(hwnd,"请检测网络连接","",MB_OK);
		return -1;
	}
	mysql_query(conn,"set character set gbk");//读库 
	mysql_query(conn,"set names gbk");//写库 
	wsprintf(sql,"select * from xTeacher_course where UserName=%s and CourseName='%s'",username,coursechoose);
	if(mysql_query(conn,sql)!=0)
	{
		MessageBox(hwnd,"请检查网络连接","",MB_OK);
		do_disconnect(conn);
		return -1;
	}
	res_set=mysql_store_result(conn);
	if(mysql_num_rows(res_set)==0)
	{
		MessageBox(hwnd,"请检查网络连接","",MB_OK);
		mysql_free_result(res_set);
		do_disconnect(conn);
		return -1;
	}
	row=mysql_fetch_row(res_set);
	if(row==NULL)
	{
		MessageBox(hwnd,"请检查网络连接","",MB_OK);
		mysql_free_result(res_set);
		do_disconnect(conn);
		return -1;
	}
	wsprintf(courseid,"%s",row[3]);
	ZeroMemory(sql,256);
	wsprintf(sql,"update xCourse_info set Homework = '%s' where CourseId='%s'",homework,courseid);
	if(mysql_query(conn,sql)!=0)
	{
		MessageBox(hwnd,"请检查网络连接","",MB_OK);
		do_disconnect(conn);
		return -1;
	}
	return 0;
}
extern "C"_declspec(dllexport) int knowledgepoint(HWND hwnd,HWND hwnd_combo_course,TCHAR *username,int nID_knowledgepoint)
{
	int index;
	TCHAR coursechoose[256]={0};
	TCHAR knowledgepoint[1024]={0};
	MYSQL *conn=NULL;
	TCHAR sql[256]={0};
	TCHAR courseid[256]={0};
	MYSQL_RES *res_set;
	MYSQL_ROW row;
	TCHAR DBName[256]={0};
	
	ZeroMemory(sql,256);
	ZeroMemory(courseid,256);
	ZeroMemory(DBName,256);
	ZeroMemory(knowledgepoint,1024);
	GetDlgItemText(hwnd,nID_knowledgepoint,knowledgepoint,1024);
	index=ComboBox_GetCurSel(hwnd_combo_course);//未选择时返回-1
	if(index==-1)
	{
		MessageBox(hwnd,"请先选择课程","",MB_OK);
		return -1;
	}
	if(lstrlen(knowledgepoint)==0)
	{
		MessageBox(hwnd,"请输入本节知识点","",MB_OK);
		return -1;
	}
	ComboBox_GetLBText(hwnd_combo_course,index,coursechoose);
	conn=do_connect();
	if(conn==NULL)
	{
		MessageBox(hwnd,"请检测网络连接","",MB_OK);
		return -1;
	}
	mysql_query(conn,"set character set gbk");//读库 
	mysql_query(conn,"set names gbk");//写库 
	wsprintf(sql,"select * from xTeacher_course where UserName=%s and CourseName='%s'",username,coursechoose);
	if(mysql_query(conn,sql)!=0)
	{
		MessageBox(hwnd,"请检查网络连接","",MB_OK);
		do_disconnect(conn);
		return -1;
	}
	res_set=mysql_store_result(conn);
	if(mysql_num_rows(res_set)==0)
	{
		MessageBox(hwnd,"请检查网络连接","",MB_OK);
		mysql_free_result(res_set);
		do_disconnect(conn);
		return -1;
	}
	row=mysql_fetch_row(res_set);
	if(row==NULL)
	{
		MessageBox(hwnd,"请检查网络连接","",MB_OK);
		mysql_free_result(res_set);
		do_disconnect(conn);
		return -1;
	}
	wsprintf(courseid,"%s",row[3]);
	ZeroMemory(sql,256);
	wsprintf(sql,"update xCourse_info set KnowledgePoint = '%s' where CourseId='%s'",knowledgepoint,courseid);
	if(mysql_query(conn,sql)!=0)
	{
		MessageBox(hwnd,"请检查网络连接","",MB_OK);
		do_disconnect(conn);
		return -1;
	}
	return 0;
}


extern "C"_declspec(dllexport) int url(HWND hwnd,HWND hwnd_combo_course,TCHAR *username,int nID_url)
{
	int index;
	TCHAR coursechoose[256]={0};
	TCHAR url[1024]={0};
	MYSQL *conn=NULL;
	TCHAR sql[256]={0};
	TCHAR courseid[256]={0};
	MYSQL_RES *res_set;
	MYSQL_ROW row;
	TCHAR DBName[256]={0};
	
	ZeroMemory(sql,256);
	ZeroMemory(courseid,256);
	ZeroMemory(DBName,256);
	ZeroMemory(url,1024);
	GetDlgItemText(hwnd,nID_url,url,1024);
	index=ComboBox_GetCurSel(hwnd_combo_course);//未选择时返回-1
	if(index==-1)
	{
		MessageBox(hwnd,"请先选择课程","",MB_OK);
		return -1;
	}
	if(lstrlen(url)==0)
	{
		MessageBox(hwnd,"请输入网址","",MB_OK);
		return -1;
	}
	ComboBox_GetLBText(hwnd_combo_course,index,coursechoose);
	conn=do_connect();
	if(conn==NULL)
	{
		MessageBox(hwnd,"请检测网络连接","",MB_OK);
		return -1;
	}
	mysql_query(conn,"set character set gbk");//读库 
	mysql_query(conn,"set names gbk");//写库 
	wsprintf(sql,"select * from xTeacher_course where UserName=%s and CourseName='%s'",username,coursechoose);
	if(mysql_query(conn,sql)!=0)
	{
		MessageBox(hwnd,"请检查网络连接","",MB_OK);
		do_disconnect(conn);
		return -1;
	}
	res_set=mysql_store_result(conn);
	if(mysql_num_rows(res_set)==0)
	{
		MessageBox(hwnd,"请检查网络连接","",MB_OK);
		mysql_free_result(res_set);
		do_disconnect(conn);
		return -1;
	}
	row=mysql_fetch_row(res_set);
	if(row==NULL)
	{
		MessageBox(hwnd,"请检查网络连接","",MB_OK);
		mysql_free_result(res_set);
		do_disconnect(conn);
		return -1;
	}
	wsprintf(courseid,"%s",row[3]);
	ZeroMemory(sql,256);
	wsprintf(sql,"update xCourse_info set url = '%s' where CourseId='%s'",url,courseid);
	if(mysql_query(conn,sql)!=0)
	{
		MessageBox(hwnd,"请检查网络连接","",MB_OK);
		do_disconnect(conn);
		return -1;
	}
	return 0;
}