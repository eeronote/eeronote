#include "op_comm_include.h"


// init  apr memory pool
void op_init_memory_pool() {
  apr_initialize();
  apr_pool_create(&op_session_mp, NULL);
}



// destroy memory pool
void op_destroy_memory_pool() {
  apr_pool_destroy(op_session_mp);
}



// allocate heap memory
void* op_alloc(int size) {
  return apr_palloc(op_session_mp, size);
}
