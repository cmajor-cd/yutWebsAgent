#ifndef api__h
#define api__h

#include "cJSON.h"
#include "hal.h"

#ifdef __cplusplus
extern "C"
{
#endif


#define JSON_COMMAND "command"
#define JSON_DAT "dat"
#define JSON_ERRCODE "errCode"
#define JSON_RC "rc"

#define SET_CFG_INFOR "setCfgInfor"
#define GET_CFG_INFOR "getCfgInfor"

#define KEY_COMMAND "command"
#define KEY_cur_v "cur_v"
#define KEY_cur_a "cur_a"

int func_SET_CFG_INFOR(cJSON *json_in, cJSON *json_out);
int func_GET_CFG_INFOR(cJSON *json_in, cJSON *json_out);


#ifdef __cplusplus
}
#endif

#endif