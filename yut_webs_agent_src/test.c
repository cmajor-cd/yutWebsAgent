#include <stdio.h>
#include "test.h"

#define MAX_INPUT_BUFF 4096
// #define JSON_COMMAND "command"
// #define JSON_DAT "dat"
// #define JSON_ERRCODE "errCode"
// #define JSON_RC "rc"

void action_webs_agent()
{
	//--create input json root for "setCfgInfor" TEST.
	cJSON* json_in = cJSON_CreateObject();
	cJSON* json_in_dat = cJSON_CreateObject();
	cJSON_AddItemToObject(json_in_dat, KEY_COMMAND, cJSON_CreateString("setCfgInfor"));
	cJSON_AddItemToObject(json_in_dat, KEY_cur_v, cJSON_CreateString("11"));
	cJSON_AddItemToObject(json_in_dat, KEY_cur_a, cJSON_CreateString("12"));
	cJSON_AddItemToObject(json_in, JSON_DAT, json_in_dat);

	// create the output cjson root
	cJSON* json_out = cJSON_CreateObject();
	// create the node. "dat"
	cJSON* json_out_dat = cJSON_CreateObject();
	cJSON_AddItemToObject(json_out, JSON_DAT, json_out_dat);


	//if (!strcasecmp(p_json_node_value, SET_CFG_INFOR)) {
		//func_SET_CFG_INFOR(json_in, json_out);
	//}
	//else if (!strcasecmp(p_json_node_value, GET_CFG_INFOR)) {
		func_GET_CFG_INFOR(json_in, json_out);
	//}
	//
	// 4. fill the goAction webs return.
		printf("action_webs_agent \n Log[ajax-ret] : [%s]\n", cJSON_Print(json_out));
}



int main(int argc, char const *argv[])
{
    printf("THIS is MAIN(%s)!! \n", "TS_1");
    action_webs_agent();

    return 0;
}
