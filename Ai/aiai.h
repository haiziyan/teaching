#ifndef _AIAI_H
#define _AIAI_H
#include "winsock.h"
#include <mysql.h>
extern "C"_declspec(dllexport) int Add_text(HWND hwnd, int nId_keyword, int nId_content);
extern "C"_declspec(dllexport) int Add_news(HWND hwnd, int nId_kyeword, int nId_title, int nId_picurl, int nId_url, int nId_description);
#endif