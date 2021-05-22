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
    char* p_url_name; // router url, e.g. url: "/action/set_data".
    void* f_cb;       // the callback function pointer.
};

#define MAX_LENGTH 100 // define the max length of the callback array.
static regist_router_api m_api_callback[MAX_LENGTH] = {
    {"setCfgInfor", func_SET_CFG_INFOR},
    {"getCfgInfor", func_GET_CFG_INFOR}
};

#ifdef __cplusplus
}
#endif

#endif