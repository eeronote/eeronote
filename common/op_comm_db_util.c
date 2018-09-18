#include "op_comm_db_util.h"




// get DB connection
bool op_init_db_connection(int db_idx, char* db_host, char* db_name, char* db_user, char* db_pass, int db_port) {
  MYSQL* p_connection = (MYSQL*) op_alloc(sizeof(MYSQL*));
  mysql_init(p_connection);
  mysql_options(p_connection, MYSQL_SET_CHARSET_NAME, "utf8");   
  mysql_options(p_connection, MYSQL_INIT_COMMAND, "SET NAMES utf8");   
  mysql_real_connect(p_connection, db_host, db_user, db_pass, db_name, db_port, (char *)NULL, 0);

  // initialize memory pool for MYSQL_RES list with parent memory pool(op_session_mp) 
  apr_pool_create(&op_sr_mp, op_session_mp);
  op_sr_array = apr_array_make(op_sr_mp, OP_SQL_RESULT_SIZE, sizeof(const MYSQL_RES*));

  if (p_connection == NULL) {
      return false;
  } else {
      p_connections[db_idx] = p_connection;
      return true;
  }
}



// cloase DB connection
void op_close_db_connection(int db_idx) {
  // before closing DB, free all sql results
  op_free_sql_result();
  // close connection 
  mysql_close(p_connections[db_idx]);
}



// execute sql(basic function, can execute all SQLs(DML/select))
int op_execute_sql(int db_idx, char* sql) {
  return mysql_query(p_connections[db_idx], sql);
}



// for select query
MYSQL_RES* op_execute_select(int db_idx, char* sql) {
  MYSQL_RES *sql_result;

  if (op_execute_sql(db_idx, sql) != 0 ) {
      return NULL;
  } else {
      sql_result = mysql_store_result(p_connections[db_idx]);
      // for free all mysql_ress, add to array
      *(const MYSQL_RES**)apr_array_push(op_sr_array) = sql_result;
      return sql_result;
  }
}



// for DML(insert/update/delete) 
bool op_execute_dml(int db_idx, char* sql) {
  if (op_execute_sql(db_idx, sql) != 0 ) {
      return false;
  } else {
      return true;
  }
}



// free sql results 
void op_free_sql_result() {
  int idx;
  for (idx = 0; idx < op_sr_array->nelts; idx++) {
     if (((MYSQL_RES**)op_sr_array->elts)[idx] != NULL) {
       mysql_free_result(((MYSQL_RES**)op_sr_array->elts)[idx]);
     }
  }
}


