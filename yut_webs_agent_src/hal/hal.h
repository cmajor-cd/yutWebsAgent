#ifndef hal__h
#define hal__h

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct _hal_cfg_infor
{
    int cur_v;
    int cur_a;
}m_hal_cfg_infor;

void hal_get_cfg_infor(m_hal_cfg_infor* p_cfg);
void hal_set_cfg_infor(m_hal_cfg_infor* p_cfg);

#ifdef __cplusplus
}
#endif

#endif