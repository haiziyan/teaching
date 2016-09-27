#ifndef _DATAOPERATE_H
#define _DATAOPERATE_H
#include "winsock.h"
#include <mysql.h>
extern "C"_declspec(dllexport) void do_disconnect(MYSQL *conn);
extern "C"_declspec(dllexport) void get_error(MYSQL *conn,TCHAR *message);
extern "C"_declspec(dllexport) MYSQL *do_connect();
extern "C"_declspec(dllexport) void process_query(MYSQL *conn,TCHAR *query);
extern "C"_declspec(dllexport) int is_user(MYSQL *conn,TCHAR *username,TCHAR *password);
#endif