/**
 * 
*/
#ifndef regist_router_api__h
#define regist_router_api__h

#include "api.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct{
    char* p_url_name;  // router url, e.g. url: "/action/set_data".
    void  (* fn_cb)(cJSON* p1,cJSON* p2);       // the callback function pointer. e.g. func_SET_CFG_INFOR(cJSON *json_in, cJSON *json_out);
}t_regist_router_api;

typedef enum {
    _ROUTER_API_BEGIN = 0,  // TODO, !!add your router_api name into the line!!
    _setCfgInfor,
    _getCfgInfor,
    _ROUTER_API_MAX_LENGTH  // define the max length of the api callback function  array.
}t_regist_router_api_number;

t_regist_router_api m_api_callback[_ROUTER_API_MAX_LENGTH] = {
    // TODO, !!add your router_api name/callback function pair into the line!!
    {"setCfgInfor", func_SET_CFG_INFOR},
    {"getCfgInfor", func_GET_CFG_INFOR}
};

#ifdef __cplusplus
}
#endif

#endif