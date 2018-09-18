#ifndef OP_COMM_DB_UTIL
#define OP_COMM_DB_UTIL

#include "op_comm_include.h"

#define OP_CONNECTIONS_SIZE 50
#define OP_SQL_RESULT_SIZE 10


// DB connection 포인터 배열
MYSQL* p_connections[OP_CONNECTIONS_SIZE];
// sql result 메모리풀
apr_pool_t *op_sr_mp;
// sql result 다이나믹 어레이 헤더
apr_array_header_t *op_sr_array;


// db 커넥션 초기화
bool op_init_db_connection(int db_idx, char* db_host, char* db_name, char* db_user, char* db_pass, int db_port); 

// db 커넥션 닫기
void op_close_db_connection(int db_idx);

// sql 수행 
int op_execute_sql(int db_idx, char* sql);

// select query 수행
MYSQL_RES* op_execute_select(int db_idx, char* sql);

// dml(insert, update, delete) 수행
bool op_execute_dml(int db_idx, char* sql);

// sql result memory 해제함수
void op_free_sql_result();

#endif
