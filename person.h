#ifndef _PERSON_H
#define _PERSON_H
#include "winsock.h"
#include <mysql.h>
extern "C"_declspec(dllexport) int person(HWND hwnd,TCHAR *username,int nID_name,int nID_phone,int nID_wechat,int nID_qq);
extern "C"_declspec(dllexport) int password(HWND hwnd,TCHAR *username,int nID_old,int nID_new,int nID_newagain);
#endif