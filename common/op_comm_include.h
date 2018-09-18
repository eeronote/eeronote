#ifndef OP_COMM_INCLUDE
#define OP_COMM_INCLUDE

#include <httpd.h>
#include <http_protocol.h>
#include <http_config.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <mysql/mysql.h>
#include <json-c/json.h>


// 세션에서 사용하게 될 메모리 풀
apr_pool_t *op_session_mp;


// root 메모리풀 초기화
void op_init_memory_pool();

// root 메모리풀 destroy
void op_destroy_memory_pool();

// root 메모리풀에 메모리 할당
void* op_alloc(int size);

#endif  
