#include "sample.h"


// DB connection info
#define DB_IDX  0
#define DB_HOST "localhost"
#define DB_NAME "memo"
#define DB_USER "memo"
#define DB_PASS "1q2w3e4r!"
#define DB_PORT 3306 



int sample(request_rec* r) {

      MYSQL_RES *sql_result;
      MYSQL_ROW sql_row;

      char query[255];
      int query_stat;
      char result[5000];
      char tmp_result[5000];
      int result_count = 0;

      op_init_memory_pool();
      
      if (op_init_db_connection(DB_IDX, DB_HOST, DB_NAME, DB_USER, DB_PASS, DB_PORT) != true) {
        ap_rputs("DB Connection Error", r);
        return OK;
      }

      sprintf(query, "SELECT id, content FROM memo_test");


      sql_result = op_execute_select(DB_IDX, query);

      if (sql_result == NULL) {
        ap_rputs("ERROR OCCURRED", r);
      } else {
        while((sql_row = mysql_fetch_row(sql_result))) {
          if (result_count == 0) {
             sprintf(result, "id: %s <br /> content: %s <br /> ------------------------------------------------------------- <br />", sql_row[0], sql_row[1]);
             result_count++;
          } else {
             sprintf(tmp_result, "id: %s <br /> content: %s <br /> ------------------------------------------------------------- <br />", sql_row[0], sql_row[1]);
             strcat(result, tmp_result);
          }
        }

      }

      create_return_message(result, r);
  
      // close & destroy
      op_close_db_connection(DB_IDX);
      op_destroy_memory_pool();

    return OK;
}


void create_return_message(char* result, request_rec* r) {
    // 출력!!!!
    ap_set_content_type(r, "text/html;charset=utf-8");
    ap_rputs("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01//EN\">", r);
    ap_rputs("<html><head><title>EeroNote ::</title></head>", r);
    ap_rputs("<body><h1>EeroNote Sample page!</h1>", r);
    ap_rputs(result, r); 
    ap_rputs("<br />", r); 
    ap_rputs(r->uri, r); 
    ap_rputs("<br />ver 0.0.4", r);
    ap_rputs("</body></html>", r);
}

