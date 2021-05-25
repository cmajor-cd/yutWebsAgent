#include <stdio.h>
#include "hal.h"

void hal_get_cfg_infor(m_hal_cfg_infor* p_cfg){
	p_cfg->cur_v = 3;
	p_cfg->cur_a = 4;

    return;
}

void hal_set_cfg_infor(m_hal_cfg_infor* p_cfg) {
	printf("[hal_set_cfg_infor]Set to hal(cur_v = %d <> cur_a = %d)!! \n", p_cfg->cur_v, p_cfg->cur_a);
	return;
}


