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

struct regist_router_api
{
    char* p_url_name;  // router url, e.g. url: "/action/set_data".
    void* fn_cb;       // the callback function pointer.
};

enum regist_router_api_number{
    _ROUTER_API_BEGIN = 0,  // TODO, !!add your router_api name into the line!!
    _ROUTER_API_MAX_LENGTH  // define the max length of the api callback function  array.
}

static regist_router_api m_api_callback[_ROUTER_API_MAX_LENGTH] = {
    // TODO, !!add your router_api name/callback function pair into the line!!
    {"setCfgInfor", func_SET_CFG_INFOR},
    {"getCfgInfor", func_GET_CFG_INFOR}
};

#ifdef __cplusplus
}
#endif

#endif