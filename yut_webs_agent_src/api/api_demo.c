
#include <stdio.h>

#include "api.h"

/** *******************************
 * func_GET_CFG_INFOR(cJSON* json_in, cJSON* json_out)
 * input: json_root
 *   the formated echo result JSON：
			{ "rc":0/1, "errCode": error msg tx,
			"dat": {
				"command":"xx",
				"cur_v":"xx",
				"cur_a":"xx"}
				}
			}
*/
int func_GET_CFG_INFOR(cJSON *json_in, cJSON *json_out) {
	cJSON* p_json_node;
	int rc = 0;
	char errCode[100] = "";

	// read the input value from hal
	m_hal_cfg_infor hal_cfg;
	m_hal_cfg_infor* p_hal_cfg = &hal_cfg;
	hal_get_cfg_infor(&hal_cfg);
	// write the echo result
	// 1. fill the "dat".
	p_json_node = cJSON_GetObjectItem(json_out, JSON_DAT);
	cJSON_AddItemToObject(p_json_node, KEY_COMMAND, cJSON_CreateString("getCfgInfor"));
	cJSON_AddItemToObject(p_json_node, KEY_cur_v, cJSON_CreateNumber(p_hal_cfg->cur_v));
	cJSON_AddItemToObject(p_json_node, KEY_cur_a, cJSON_CreateNumber(p_hal_cfg->cur_a));
	// 2. fill the "rc"
	rc = 0; // success rc
	cJSON_AddItemToObject(json_out, JSON_RC, cJSON_CreateNumber(rc));
	// 3. fill the "errCode"
	strcat(errCode, "no error!");
	cJSON_AddItemToObject(json_out, JSON_ERRCODE, cJSON_CreateString(errCode));
	//char strLog[200];
	printf("func_GET_CFG_INFOR \n Log[ajax-ret] : [%s]\n", cJSON_Print(json_out));

	// 4. fill the goAction webs return.

	return 1;

}

/** *******************************
 * func_SET_CFG_INFOR(cJSON* json_root)
 * input: json_root
 *   the formated echo result JSON：
			{ "rc":0/1, "errCode": error msg tx,
			}
*/
int func_SET_CFG_INFOR(cJSON *json_in, cJSON *json_out) {
	cJSON* p_json_node;
	int rc = 0;
	char errCode[100] = "";

	// read the input value
	cJSON *_json_dat_node = NULL;
	char *_KEY_cur_v_value, *_KEY_cur_a_value;
	p_json_node = cJSON_GetObjectItem(json_in, JSON_DAT);
	_json_dat_node = cJSON_GetObjectItem(p_json_node, KEY_cur_v);
	_KEY_cur_v_value = cJSON_GetStringValue(_json_dat_node);
	_json_dat_node = cJSON_GetObjectItem(p_json_node, KEY_cur_a);
	_KEY_cur_a_value = cJSON_GetStringValue(_json_dat_node);
	// set value to hal
	m_hal_cfg_infor hal_cfg;
	m_hal_cfg_infor* p_hal_cfg = &hal_cfg;
	hal_cfg.cur_v = atoi(_KEY_cur_v_value);
	hal_cfg.cur_a = atoi(_KEY_cur_a_value);
	hal_set_cfg_infor(&hal_cfg);
	// write the echo result
	// 1. fill the "dat".
	// 2. fill the "rc"
	rc = 0; // success rc
	cJSON_AddItemToObject(json_out, JSON_RC, cJSON_CreateNumber(rc));
	// 3. fill the "errCode"
	strcat(errCode, "setCfgInfor");
	cJSON_AddItemToObject(json_out, JSON_ERRCODE, cJSON_CreateString(errCode));
	//char strLog[200];
	printf("func_SET_CFG_INFOR \n Log[ajax-ret] : [%s]\n", cJSON_Print(json_out));

	// 4. fill the goAction webs return.


	return 1;
}