/**
  *  Copyright (C) 2013-12-21  Handsome Zhou (Reference TangQiWen's code)
  */

#ifndef CTRL_TOOL_H
#define CTRL_TOOL_H

#ifdef __cplusplus
extern "C" {
#endif	/*__cplusplus*/

#include "message_event.h"

typedef void* p_ctrl_tool_t;

typedef struct ctrl_tool_res{

}ctrl_tool_res_t;

typedef struct ctrl_tool_callback{
	int (* pf_event_paint)(T_pRECT p_rect,int index, T_BOOL sel_flag);
	int (* pf_event_pen_up)(const m_evt_code_t *p_m_evt_code, int sel_index);
	int (* pf_event_pen_down)(const m_evt_code_t *p_m_evt_code, int sel_index);
	int (* pf_event_select)(const m_evt_code_t *p_m_evt_code, int sel_index);
	int (* pf_event_enter_select)(const m_evt_code_t *p_m_evt_code, int sel_index);
	int (* pf_event_esc)(const *m_evt_code_t *p_m_evt_code, int sel_index);
}ctrl_tool_callback_t;

p_ctrl_tool_t ctrl_tool_init(int res_num, const ctrl_tool_res_t *p_res, const ctrl_tool_callback_t *p_callback_fun);
int	ctrl_tool_handle(const p_ctrl_tool_t *p_ctrl_tool,const m_evt_code_t *p_m_evt_code);
int ctrl_tool_paint(const p_ctrl_tool_t *p_ctrl_tool);
void ctrl_tool_free(p_ctrl_tool_t *p_ctrl_tool);
#ifdef __cplusplus
}
#endif	/*__cplusplus*/

#endif	/*CTRL_TOOL_H*/
