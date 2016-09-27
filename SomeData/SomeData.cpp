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



extern "C"_declspec(dllexport) void get_filename(HWND hwnd,TCHAR *FileName,int nID)
{	
	OPENFILENAME ofn;
	char szFile[MAX_PATH];
	ZeroMemory(&ofn,sizeof(ofn));
	ofn.lStructSize=sizeof(ofn);
	ofn.lpstrFile=szFile;
	ofn.lpstrFile[0]=TEXT('\0');
	ofn.nMaxFile=sizeof(szFile);
	ofn.lpstrFilter=TEXT("CSV\0*.csv\0");
	ofn.nFilterIndex=1;
	ofn.hwndOwner=hwnd;
	ofn.lpstrFileTitle=NULL;
	ofn.nMaxFileTitle=0;
	ofn.lpstrInitialDir=NULL;
	ofn.Flags=OFN_EXPLORER|OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST;
	if(GetOpenFileName(&ofn))
	{
		lstrcpy(FileName,ofn.lpstrFile);
		
		SetDlgItemText(hwnd,nID,FileName);
		
	}

	
}
int GetFileLineCount(TCHAR *filename)
{
	FILE *fp=NULL;
	fp=fopen(filename,"r");
	if(fp==NULL)
	{
		MessageBox(NULL,"打开文件失败","",MB_OK);
		return 0;
	}
	int icount=0;
	TCHAR buff[256]={0};
	while(!feof(fp))
	{
		icount++;
		fgets(buff,256,fp);
	}
	fclose(fp);
	
	return icount;
}
TCHAR *replaceAll(TCHAR *src,TCHAR oldChar,TCHAR newChar){
	char *head=src;
	while(*src!='\0'){

		if(*src==oldChar) 
			*src=newChar;
		src++;
		}
	return head;
}
int split(char dst[][256], char* str, const char* spl)
{
    int n = 0;
    char *result = NULL;
    result = strtok(str, spl);
    while( result != NULL )
    {
        strcpy(dst[n++], result);
        result = strtok(NULL, spl);
    }
    return n;
}
extern "C"_declspec(dllexport) int importscore(HWND hwnd,int nID_progressimport,TCHAR *filename)
{	
	
	
	TCHAR *FileName=replaceAll(filename,'\\','/');
	if(strlen(filename)==0)
	{
		MessageBox(hwnd,"请选择文件","",MB_OK);
		return -1;
	}
	MYSQL *conn;
	TCHAR sql[512]={0};
	conn=do_connect();
	if(conn==NULL)
	{
		MessageBox(hwnd,"请检测网络连接","",MB_OK);
		return -1;
	}
	mysql_query(conn,"set character set gbk");//读库 
	mysql_query(conn,"set names gbk");//写库 
	
	
	
	
	
	int ilineCount = GetFileLineCount(FileName);
	
	SendDlgItemMessage(hwnd,nID_progressimport,PBM_SETRANGE,0,MAKELPARAM(0,ilineCount));
	FILE *fp=NULL;
	fp=fopen(FileName,"r");
	if(fp==NULL)
	{
		MessageBox(hwnd,"打开文件错误","",MB_OK);
		return -1;
	}
	
	TCHAR student[6][256]={0};
	TCHAR tmpstudent[256]={0};
	int icount=0;
	ZeroMemory(sql,512);
	ZeroMemory(tmpstudent,256);
	fscanf(fp,"%s,%s,%s,%s,%s,%s",tmpstudent);
	while(!feof(fp))
	{
		
		split(student,tmpstudent,",");
		SendDlgItemMessage(hwnd,nID_progressimport,PBM_SETPOS,icount,0);
		icount++;
		wsprintf(sql,"insert into chengji_1 (xuehao,name,banji,kecheng,xuefen,score) values ('%s','%s','%s','%s','%s','%s')",student[0],student[1],student[2],student[3],student[4],student[5]);
		if(mysql_query(conn,sql)!=0)
		{
	    MessageBox(hwnd,"请检查网络连接",student[0],MB_OK);
		do_disconnect(conn);
		fclose(fp);
		return -1;
		}
		ZeroMemory(sql,512);
		ZeroMemory(tmpstudent,256);
		fscanf(fp,"%s,%s,%s,%s,%s,%s",tmpstudent);
	}
	ZeroMemory(sql,256);

	fclose(fp);
	do_disconnect(conn);
	return 0;
}

extern "C"_declspec(dllexport) int importteacher(HWND hwnd,int nID_progressimport,TCHAR *filename)
{	
	
	
	TCHAR *FileName=replaceAll(filename,'\\','/');		
	if(strlen(filename)==0)
	{
		MessageBox(hwnd,"请选择文件","",MB_OK);
		return -1;
	}
	MYSQL *conn;
	TCHAR sql[512]={0};
	conn=do_connect();
	if(conn==NULL)
	{
		MessageBox(hwnd,"请检测网络连接","",MB_OK);
		return -1;
	}
	mysql_query(conn,"set character set gbk");//读库 
	mysql_query(conn,"set names gbk");//写库 
	int ilineCount = GetFileLineCount(FileName);
	SendDlgItemMessage(hwnd,nID_progressimport,PBM_SETRANGE,0,MAKELPARAM(0,ilineCount));
	FILE *fp=NULL;
	fp=fopen(FileName,"r");
	if(fp==NULL)
	{
		MessageBox(hwnd,"打开文件错误","",MB_OK);
		return -1;
	}
	
	TCHAR teacher[2][256]={0};
	TCHAR tmpteacher[256]={0};
	int icount=0;
	ZeroMemory(sql,512);
	ZeroMemory(tmpteacher,256);
	fscanf(fp,"%s,%s",tmpteacher);
	while(!feof(fp))
	{
		
		split(teacher,tmpteacher,",");
		SendDlgItemMessage(hwnd,nID_progressimport,PBM_SETPOS,icount,0);
		icount++;
		wsprintf(sql,"insert into xTeacher_user (UserName,PassWord) values ('%s','%s')",teacher[0],teacher[1]);
		if(mysql_query(conn,sql)!=0)
		{
	    MessageBox(hwnd,"请检查网络连接",teacher[0],MB_OK);
		do_disconnect(conn);
		fclose(fp);
		return -1;
		}
		wsprintf(sql,"insert into xTeacher_info (UserName) values ('%s')",teacher[0]);
		if(mysql_query(conn,sql)!=0)
		{
	    MessageBox(hwnd,"请检查网络连接",teacher[0],MB_OK);
		do_disconnect(conn);
		fclose(fp);
		return -1;
		}
		ZeroMemory(sql,512);
		ZeroMemory(tmpteacher,256);
		fscanf(fp,"%s,%s",tmpteacher);
	}
	ZeroMemory(sql,256);

	fclose(fp);
	do_disconnect(conn);
	return 0;
}


extern "C"_declspec(dllexport) int importstudent(HWND hwnd,int nID_progressimport,TCHAR *filename)
{
		TCHAR *FileName=replaceAll(filename,'\\','/');		
	if(strlen(filename)==0)
	{
		MessageBox(hwnd,"请选择文件","",MB_OK);
		return -1;
	}
	MYSQL *conn;
	TCHAR sql[512]={0};
	conn=do_connect();
	if(conn==NULL)
	{
		MessageBox(hwnd,"请检测网络连接","",MB_OK);
		return -1;
	}
	mysql_query(conn,"set character set gbk");//读库 
	mysql_query(conn,"set names gbk");//写库 
	int ilineCount = GetFileLineCount(FileName);
	SendDlgItemMessage(hwnd,nID_progressimport,PBM_SETRANGE,0,MAKELPARAM(0,ilineCount));
	FILE *fp=NULL;
	fp=fopen(FileName,"r");
	if(fp==NULL)
	{
		MessageBox(hwnd,"打开文件错误","",MB_OK);
		return -1;
	}
	
	TCHAR student[3][256]={0};
	TCHAR tmpstudent[256]={0};
	int icount=0;
	ZeroMemory(sql,512);
	ZeroMemory(tmpstudent,256);
	fscanf(fp,"%s,%s,%s",tmpstudent);
	while(!feof(fp))
	{
		
		split(student,tmpstudent,",");
		SendDlgItemMessage(hwnd,nID_progressimport,PBM_SETPOS,icount,0);
		icount++;
		wsprintf(sql,"insert into xStudent_info (StudentId,StudentName,Class) values ('%s','%s','%s')",student[0],student[1],student[2]);
		if(mysql_query(conn,sql)!=0)
		{
	    MessageBox(hwnd,"请检查网络连接",student[0],MB_OK);
		do_disconnect(conn);
		fclose(fp);
		return -1;
		}
		ZeroMemory(sql,512);
		wsprintf(sql,"insert into asuser (xuehao,name,banji) values ('%s','%s','%s')",student[0],student[1],student[2]);
		if(mysql_query(conn,sql)!=0)
		{
	    MessageBox(hwnd,"请检查网络连接",student[0],MB_OK);
		do_disconnect(conn);
		fclose(fp);
		return -1;
		}
		ZeroMemory(sql,512);
		ZeroMemory(tmpstudent,256);
		fscanf(fp,"%s,%s,%s",tmpstudent);
	}
	

	fclose(fp);
	do_disconnect(conn);
	return 0;
}




extern "C"_declspec(dllexport) int truncate(HWND hwnd)
{
	MYSQL *conn;
	TCHAR sql[512]={0};
	conn=do_connect();
	if(conn==NULL)
	{
		MessageBox(hwnd,"请检测网络连接","",MB_OK);
		return -1;
	}
	mysql_query(conn,"set character set gbk");//读库 
	mysql_query(conn,"set names gbk");//写库 
	wsprintf(sql,"truncate table chengji_3");
	if(mysql_query(conn,sql)!=0)
		{
	    MessageBox(hwnd,"请检查网络连接","error",MB_OK);
		do_disconnect(conn);
		
		return -1;
		}
	do_disconnect(conn);
	return 0;
}
