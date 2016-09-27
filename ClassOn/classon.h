#ifndef _DATAOPERATE_H
#define _DATAOPERATE_H
#include "winsock.h"
#include <mysql.h>
extern "C"_declspec(dllexport) void show_course(HWND hwnd_combo_course,TCHAR *username);
extern "C"_declspec(dllexport) int dianming(HWND hwnd ,HWND hwnd_combo_course,TCHAR *username,TCHAR *identifycode,TCHAR *COURSEID);
extern "C"_declspec(dllexport) void get_filename(HWND hwnd,int IDC_EDIT_FILENAME,TCHAR *FileName,int nID);
extern "C"_declspec(dllexport) int import(HWND hwnd,int nID_classname,int nID_classid,int nID_progressimport,TCHAR *username,TCHAR *filename);
extern "C"_declspec(dllexport) int add_del_student(HWND hwnd,HWND hwnd_combo_course,int nID_StudentId,TCHAR *username,int add_del);
extern "C"_declspec(dllexport) int deletecourse(HWND hwnd,HWND hwndcombo,TCHAR *username);
extern "C"_declspec(dllexport) int result(HWND hwnd,TCHAR *courseid,int nID_ActualTotalNumber,int nID_ActualToNumber,int nID_NotTotheNumberOf,int nID_RESULT);
#endif