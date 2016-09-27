// DataOperate.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "winsock.h"
#include <mysql.h>
#include <stdlib.h>
#include <stdio.h>
#pragma comment(lib,"libmySQL.lib")
#define HOSTNAME "115.28.151.44"
#define USERNAME "root"
#define PASSWORD "13117197951wn520"
#define DBNAME  "zjou2015"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}
extern "C"_declspec(dllexport) void do_disconnect(MYSQL *conn)
{
	mysql_close(conn);
}

extern "C"_declspec(dllexport) void get_error(MYSQL *conn,TCHAR *message,TCHAR *errorinfo)
{
	TCHAR errorbuff[255]={0};
		if(NULL!=conn)
		{
			
			wsprintf(errorbuff,"%s\nError%u (%s)\n",message,mysql_errno(conn),mysql_error(conn));

		}
		else 
		{
			return ;
		}
		if(errorinfo==NULL)
		{
			errorinfo=(TCHAR *)malloc(sizeof(TCHAR)*255);
		}
		lstrcpy(errorinfo,errorbuff);
}

extern "C"_declspec(dllexport)MYSQL *do_connect()
{
	MYSQL *conn=NULL;

	conn = mysql_init(NULL);
	if(NULL==conn)
	{
		
		//TCHAR *message="mysql_init()failed(probably out of memory)";
	//	get_error(conn,message,errorbuff);
		//MessageBox(hwnd,TEXT("ERROR"),errorbuff,MB_ICONERROR);
		
		return NULL;
	}
	if(mysql_real_connect(conn,HOSTNAME,USERNAME,PASSWORD,DBNAME,0,NULL,0)==NULL)
	{
		
	//	TCHAR *message="mysql_real_connect()failed";
	//	get_error(conn,message,errorbuff);
		//MessageBox(hwnd,TEXT("ERROR"),errorbuff,MB_ICONERROR);
		
		return NULL;
	}
	if(mysql_select_db(conn,DBNAME)!=0)
	{
		
	//	TCHAR *message="mysql_select_db()failed";
	//	get_error(conn,message,errorbuff);
		//MessageBox(hwnd,TEXT("ERROR"),errorbuff,MB_ICONERROR);

		do_disconnect(conn);
		return NULL;
	}
	return conn;
	
}



extern "C"_declspec(dllexport) void process_query(MYSQL *conn,TCHAR *query)
{
	
}


extern "C"_declspec(dllexport) int is_user(MYSQL *conn,TCHAR *username,TCHAR *password)
{
	MYSQL_RES *res_set;
	TCHAR sql[256];
	mysql_query(conn,"set character set gbk");//¶Á¿â 
	mysql_query(conn,"set names gbk");//Ð´¿â 
	wsprintf(sql,"select * from xTeacher_user where UserName=%s and Password=%s",username,password);
	if(conn==NULL)
	{
		return -1;
	}
	if((mysql_query(conn,sql))!=0)
	{
		return -1;
	}
	res_set=mysql_store_result(conn);
	
//	rowcount = mysql_num_rows(res_set);
	if(mysql_num_rows(res_set)==0)
	{
		mysql_free_result(res_set);
		return -1;
	}
	//MessageBox(NULL,password,username,MB_OK);
	mysql_free_result(res_set);
	return 0;
}