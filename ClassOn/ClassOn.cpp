// ClassOn.cpp : Defines the entry point for the DLL application.
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


extern "C"_declspec(dllexport) void show_course(HWND hwnd,HWND hwnd_combo_course,TCHAR *username)
{
	MYSQL *conn=NULL;
	TCHAR sql[256];
	MYSQL_RES *res_set;
	MYSQL_ROW row;
	TCHAR course[256]={0};
	conn = do_connect();
	if(conn==NULL)
	{
		MessageBox(hwnd,"请检查网络连接...","",MB_OK);
		return ;
	}
	if ( mysql_set_character_set(conn,"gbk") ) { 
            MessageBox(hwnd,"请检查网络连接...","",MB_OK);
			return ;
        } 

	wsprintf(sql,"select * from xTeacher_course where UserName=%s",username);
	if((mysql_query(conn,sql))!=0)
	{
		MessageBox(hwnd,"请尽快导入课程","",MB_OK);
		do_disconnect(conn);
		return ;
	}
	
	res_set=mysql_store_result(conn);
	if(mysql_num_rows(res_set)==0)
	{
		MessageBox(hwnd,"请尽快导入课程","",MB_OK);
		mysql_free_result(res_set);
		do_disconnect(conn);
		return ;
	}
	else
	{
		
		while((row=mysql_fetch_row(res_set))!=NULL)
		{
			wsprintf(course,"%s",row[2]);
			ComboBox_InsertString(hwnd_combo_course,-1,TEXT(course));
			ZeroMemory(course,256);
			
		}
		mysql_free_result(res_set);
		do_disconnect(conn);
		
	}
	
	return ;

}


extern "C"_declspec(dllexport) int dianming(HWND hwnd,HWND hwnd_combo_course,TCHAR *username,TCHAR *identifycode,TCHAR *COURSEID)
{
	int index;
	TCHAR coursechoose[256]={0};
	int num_rand;
	TCHAR dbname[256]={0};
	MYSQL *conn=NULL;
	TCHAR sql[256]={0};
	TCHAR courseid[256]={0};
	MYSQL_RES *res_set;
	MYSQL_ROW row;
	srand((unsigned int)(time(NULL)));
	num_rand=rand()%100000;
	itoa(num_rand,identifycode,10);
	ZeroMemory(sql,256);
	ZeroMemory(courseid,256);
	
	index=ComboBox_GetCurSel(hwnd_combo_course);//未选择时返回-1
	if(index==-1)
	{
		MessageBox(hwnd,"请先选择课程","",MB_OK);
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
	wsprintf(COURSEID,courseid);
	wsprintf(dbname,"xCourse_%s",courseid);
	mysql_free_result(res_set);
	ZeroMemory(sql,256);
	wsprintf(sql,"update xCourse_info set IdentifyCode=%s where CourseId=%s",identifycode,courseid);
	
	if(mysql_query(conn,sql)!=0)
	{
		MessageBox(hwnd,"请检查网络连接","",MB_OK);
		do_disconnect(conn);
		return -1;
	}
	ZeroMemory(sql,256);
	wsprintf(sql,"update %s set IfId=0",dbname);
	if(mysql_query(conn,sql)!=0)
	{
		MessageBox(hwnd,"请检查网络连接","",MB_OK);
		do_disconnect(conn);
		return -1;
	}
	do_disconnect(conn);
	return 0;

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
extern "C"_declspec(dllexport) int import(HWND hwnd,int nID_classname,int nID_classid,int nID_progressimport,TCHAR *username,TCHAR *filename)
{	
	TCHAR coursename[256]={0};
	TCHAR courseid[256]={0};
	TCHAR *FileName=replaceAll(filename,'\\','/');
	TCHAR DBname[256]={0};
	ZeroMemory(coursename,256);
	ZeroMemory(courseid,256);
	GetDlgItemText(hwnd,nID_classname,coursename,256);
	GetDlgItemText(hwnd,nID_classid,courseid,256);
	wsprintf(DBname,"xCourse_%s",courseid);

	if(strlen(filename)==0|| strlen(coursename)==0 || strlen(courseid)==0)
	{
		MessageBox(hwnd,"请填写完整的信息","",MB_OK);
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
	wsprintf(sql,"insert into xTeacher_course (UserName,CourseName,CourseId) values (%s,'%s','%s')",username,coursename,courseid);
	if(mysql_query(conn,sql)!=0)
	{
		MessageBox(hwnd,"请检查网络连接","",MB_OK);
		do_disconnect(conn);
		return -1;
	}
	wsprintf(sql,"insert into xCourse_info (CourseId) values ('%s')",courseid);
	if(mysql_query(conn,sql)!=0)
	{
	    MessageBox(hwnd,"请检查网络连接","",MB_OK);
		do_disconnect(conn);
		return -1;
	}
	wsprintf(sql,"CREATE TABLE IF NOT EXISTS `%s` ( `id` int(11) NOT NULL AUTO_INCREMENT, `StudentId` varchar(15) CHARACTER SET utf8 NOT NULL,`IfId` varchar(10) CHARACTER SET utf8 NOT NULL,`StudentName` varchar(20) CHARACTER SET utf8 NOT NULL,PRIMARY KEY (`id`)) ENGINE=MyISAM DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ",DBname);
	if(mysql_query(conn,sql)!=0)
	{
	    MessageBox(hwnd,"请检查网络连接","",MB_OK);
		do_disconnect(conn);
		return -1;
	}
	int ilineCount = GetFileLineCount(FileName);
	
	SendDlgItemMessage(hwnd,nID_progressimport,PBM_SETRANGE,0,MAKELPARAM(0,ilineCount));
	FILE *fp=NULL;
	fp=fopen(FileName,"r");
	if(fp==NULL)
	{
		MessageBox(hwnd,"打开文件错误","",MB_OK);
		return -1;
	}
	
	TCHAR student[2][256]={0};
	TCHAR tmpstudent[256]={0};
	int icount=0;
	
	while(!feof(fp))
	{
		ZeroMemory(sql,512);
		ZeroMemory(tmpstudent,256);
		fscanf(fp,"%s,%s",tmpstudent);
		split(student,tmpstudent,",");
		SendDlgItemMessage(hwnd,nID_progressimport,PBM_SETPOS,icount,0);
		icount++;
		wsprintf(sql,"insert into %s (StudentId,IfId,StudentName) values ('%s','0','%s')",DBname,student[0],student[1]);
		if(mysql_query(conn,sql)!=0)
		{
	    MessageBox(hwnd,"请检查网络连接",student[0],MB_OK);
		do_disconnect(conn);
		fclose(fp);
		return -1;
		}
	}
	ZeroMemory(sql,256);
	wsprintf(sql,"delete from %s where 1 order by id desc limit 1",DBname);
	if(mysql_query(conn,sql)!=0)
	{
	    MessageBox(hwnd,"请检查网络连接",student[0],MB_OK);
		do_disconnect(conn);
		fclose(fp);
		return -1;
	}
	fclose(fp);
	do_disconnect(conn);
	return 0;
}
extern "C"_declspec(dllexport) int add_del_student(HWND hwnd,HWND hwnd_combo_course,int nID_StudentId,TCHAR *username,int add_del)
{
	int index;
	TCHAR coursechoose[256]={0};
	
	MYSQL *conn=NULL;
	TCHAR sql[256]={0};
	TCHAR courseid[256]={0};
	MYSQL_RES *res_set;
	MYSQL_ROW row;
	TCHAR DBName[256]={0};
	TCHAR studentid[256];
	ZeroMemory(sql,256);
	ZeroMemory(courseid,256);
	ZeroMemory(DBName,256);
	
	index=ComboBox_GetCurSel(hwnd_combo_course);//未选择时返回-1
	if(index==-1)
	{
		MessageBox(hwnd,"请先选择课程","",MB_OK);
		return -1;
	}
	ComboBox_GetLBText(hwnd_combo_course,index,coursechoose);
	GetDlgItemText(hwnd,nID_StudentId,studentid,256);
	if(strlen(studentid)<1)
	{
		MessageBox(hwnd,"请填写学号","",MB_OK);
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
	wsprintf(DBName,"xCourse_%s",courseid);
	mysql_free_result(res_set);
	ZeroMemory(sql,256);
	if(add_del==1)
	{
		wsprintf(sql,"insert into %s (StudentId) values ('%s')",DBName,studentid);
	}
	else
	{
		wsprintf(sql,"delete from %s where StudentId='%s'",DBName,studentid);
	}
	if(mysql_query(conn,sql)!=0)
	{
		MessageBox(hwnd,"请检查网络连接","",MB_OK);
		do_disconnect(conn);
		return -1;
	}
	SetDlgItemText(hwnd,nID_StudentId,"");
	do_disconnect(conn);
	return 0;

	
}
extern "C"_declspec(dllexport) int deletecourse(HWND hwnd,HWND hwnd_combo_course,TCHAR *username)
{
	int index;
	TCHAR coursechoose[256]={0};
	
	MYSQL *conn=NULL;
	TCHAR sql[256]={0};
	TCHAR courseid[256]={0};
	MYSQL_RES *res_set;
	MYSQL_ROW row;
	TCHAR DBName[256]={0};
	
	ZeroMemory(sql,256);
	ZeroMemory(courseid,256);
	ZeroMemory(DBName,256);
	
	index=ComboBox_GetCurSel(hwnd_combo_course);//未选择时返回-1
	if(index==-1)
	{
		MessageBox(hwnd,"请先选择课程","",MB_OK);
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
	wsprintf(DBName,"xCourse_%s",courseid);
	mysql_free_result(res_set);
	ZeroMemory(sql,256);
		
	wsprintf(sql,"delete from xTeacher_course where CourseId=%s",courseid);

	if(mysql_query(conn,sql)!=0)
	{
		MessageBox(hwnd,"请检查网络连接","",MB_OK);
		do_disconnect(conn);
		return -1;
	}
	ZeroMemory(sql,256);
		
	wsprintf(sql,"delete from xCourse_info where CourseId=%s",courseid);

	if(mysql_query(conn,sql)!=0)
	{
		MessageBox(hwnd,"请检查网络连接","",MB_OK);
		do_disconnect(conn);
		return -1;
	}
	ZeroMemory(sql,256);
		
	wsprintf(sql,"drop table %s",DBName);

	if(mysql_query(conn,sql)!=0)
	{
		MessageBox(hwnd,"请检查网络连接","",MB_OK);
		do_disconnect(conn);
		return -1;
	}
	do_disconnect(conn);
	return 0;

}
extern "C"_declspec(dllexport) int result(HWND hwnd,TCHAR *courseid,int nID_ActualTotalNumber,int nID_ActualToNumber,int nID_NotTotheNumberOf,int nID_RESULT)
{
	MYSQL *conn;
	TCHAR DBName[256]={0};
	MYSQL_RES *res_set;
	MYSQL_RES *res_set_stu;
	MYSQL_ROW row_stu;
	MYSQL_ROW row;
	TCHAR sql[256]={0};
	int total_number;
	int not_number;
	int yes_number;
	TCHAR total_alp[256]={0};
	TCHAR no_alp[256]={0};
	TCHAR yes_alp[256]={0};
	TCHAR studentid[256]={0};
	TCHAR studentname[256]={0};
	TCHAR result[4096]={0};
	TCHAR tmpresult[256]={0};
	conn=do_connect();
	if(conn==NULL)
	{
		MessageBox(hwnd,"请检查网络连接15","",MB_OK);
		return -1;
	}
	mysql_query(conn,"set character set gbk");//读库 
	mysql_query(conn,"set names gbk");//写库
	wsprintf(DBName,"xCourse_%s",courseid);
	wsprintf(sql,"select * from %s",DBName);
	if(mysql_query(conn,sql)!=0)
	{
		MessageBox(hwnd,"请检查网络连接","",MB_OK);
		do_disconnect(conn);
		return -1;
	}
	res_set=mysql_store_result(conn);
	if((total_number=(int )mysql_num_rows(res_set))==0)
	{	
		MessageBox(hwnd,"请检查网络连接","",MB_OK);
		mysql_free_result(res_set);
		do_disconnect(conn);
		return -1;

	}
	itoa(total_number,total_alp,10);
	
	ZeroMemory(sql,256);
	wsprintf(sql,"select * from %s where IfId='0'",DBName);
	if(mysql_query(conn,sql)!=0)
	{
		MessageBox(hwnd,"请检查网络连接","",MB_OK);
		do_disconnect(conn);
		return -1;
	}
	res_set=mysql_store_result(conn);
	not_number=(int )mysql_num_rows(res_set);
	
	itoa(not_number,no_alp,10);
	
	yes_number=total_number-not_number;
	itoa(yes_number,yes_alp,10);
	ZeroMemory(sql,256);
	while((row=mysql_fetch_row(res_set))!=NULL)
		{

			wsprintf(studentid,"%s",row[1]);
			wsprintf(studentname,row[3]);
			wsprintf(sql,"update xStudent_absop set AbsentNumber=AbsentNumber+1 where StudentId='%s'",studentid);
			if(mysql_query(conn,sql)!=0)
			{
				MessageBox(hwnd,"请检查网络连接","",MB_OK);
				mysql_free_result(res_set);
				do_disconnect(conn);
				return -1;

			}
			
		
			
			
			wsprintf(tmpresult,"%s         %s\n",studentid,studentname);
			lstrcat(result,tmpresult);
			ZeroMemory(studentid,256);
			ZeroMemory(studentname,256);
			ZeroMemory(sql,256);
			
		}
	wsprintf(sql,"update xTeacher_course set TotalNumber=TotalNumber+%i where CourseId=%s",not_number,courseid);
	if(mysql_query(conn,sql)!=0)
		{
	    	MessageBox(hwnd,"请检查网络连接","",MB_OK);
		    mysql_free_result(res_set);
	    	do_disconnect(conn);
		    return -1;

		}
	SetDlgItemText(hwnd,nID_ActualTotalNumber,total_alp);
	SetDlgItemText(hwnd,nID_ActualToNumber,yes_alp);
	SetDlgItemText(hwnd,nID_NotTotheNumberOf,no_alp);
	SetDlgItemText(hwnd,nID_RESULT,result);
	mysql_free_result(res_set);
	ZeroMemory(sql,256);
	wsprintf(sql,"update xCourse_info set IdentifyCode=0 where CourseId=%s",courseid);
	if(mysql_query(conn,sql)!=0)
		{
	    	MessageBox(hwnd,"请检查网络连接","",MB_OK);
		    mysql_free_result(res_set);
	    	do_disconnect(conn);
		    return -1;

		}
	do_disconnect(conn);
	return 0;
}