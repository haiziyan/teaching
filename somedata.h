#ifndef _SOMEDATA_H
#define _SOMEDATA_H
#include "winsock.h"
#include <mysql.h>
extern "C"_declspec(dllexport) int importscore(HWND hwnd,int nID_progressimport,TCHAR *filename);
extern "C"_declspec(dllexport) int importteacher(HWND hwnd,int nID_progressimport,TCHAR *filename);
extern "C"_declspec(dllexport) int importstudent(HWND hwnd,int nID_progressimport,TCHAR *filename);
extern "C"_declspec(dllexport) void get_filename(HWND hwnd,TCHAR *FileName,int nID);
extern "C"_declspec(dllexport) int truncate(HWND hwnd);
#endif