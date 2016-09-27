#ifndef _CLASSOFF_H
#define _CLASSOFF_H
#include "winsock.h"
#include <mysql.h>
extern "C"_declspec(dllexport) int homework(HWND hwnd,HWND hwnd_combo_course,TCHAR *username,int nID_homework);
extern "C"_declspec(dllexport) int knowledgepoint(HWND hwnd,HWND hwnd_combo_course,TCHAR *username,int nID_knowledgepoint);
extern "C"_declspec(dllexport) int url(HWND hwnd,HWND hwnd_combo_course,TCHAR *username,int nID_url)
#endif