#include "common/op_comm.h"
#include "sample.h"


static int controller_handler(request_rec* r) {

    if (!r->handler || strcmp(r->handler, "eeronote"))
        return DECLINED;

    if (r->method_number != M_GET)
        return HTTP_METHOD_NOT_ALLOWED;
 
    if (!strcmp(r->uri, "/sample")) {
      sample(r);  
    } else if (!strcmp(r->uri, "/test")) {
      ap_set_content_type(r, "application/json;charset=utf-8");
      ap_rputs("{\"message\":\"this is test\"}", r);
    }

    return OK;
}


// hook 등록 함수
static void register_hooks(apr_pool_t* pool) {
    ap_hook_handler(controller_handler, NULL, NULL, APR_HOOK_MIDDLE);
}


// 네이태그
module AP_MODULE_DECLARE_DATA eeronote_module = {
    STANDARD20_MODULE_STUFF,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    register_hooks
};

