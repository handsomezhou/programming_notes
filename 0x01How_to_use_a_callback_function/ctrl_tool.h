/**
  *  Copyright (C) 2013-12-21  Handsome Zhou (Reference TangQiWen's code)
  */
#ifndef CTRL_TOOL_H
#define CTRL_TOOL_H

#ifdef __cplusplus
extern "C" {
#endif	/*__cplusplus*/

#include "message_event.h"
#include "data_type.h"
//#include "ctrl_tool.h"

#ifdef KEY_ENTER
#undef KEY_ENTER
#define KEY_ENTER	(0x0A)
#endif

#ifndef KEY_ESC
#define KEY_ESC	(0x1B)
#endif


#define CTRL_TOOL_SUCCESS	(0)
#define CTRL_TOOL_FAILED	(-1)

typedef void *p_void_ctrl_tool_t;
typedef void *p_void_data_t;	//pass data point that call the control tool

typedef struct ctrl_tool_res{
	rect_t rect;	//show location
	int icon_normal;//set unselected background color 
	int icon_select;//set select  background color
	char *pdata;	//display data
}ctrl_tool_res_t;

typedef struct ctrl_tool_callback{
	int (* pf_event_paint)(p_void_data_t p_void_data, rect_t *p_rect, int index, bool sel_flag);
	int (* pf_event_pen_up)(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index);
	int (* pf_event_pen_down)(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index);
	int (* pf_event_select)(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index);
	int (* pf_event_enter)(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index);
	int (* pf_event_exit)(p_void_data_t p_void_data, const m_evt_code_t *p_m_evt_code, int sel_index);
}ctrl_tool_callback_t;

extern p_void_ctrl_tool_t ctrl_tool_init(int res_num, const ctrl_tool_res_t *p_res, const ctrl_tool_callback_t *p_callback_fun);
extern int	ctrl_tool_handle(p_void_data_t p_void_data, p_void_ctrl_tool_t p_void_ctrl_tool,const m_evt_code_t *p_m_evt_code);
extern int ctrl_tool_paint(const p_void_data_t p_void_data, const p_void_ctrl_tool_t p_void_ctrl_tool);
extern void ctrl_tool_free(p_void_ctrl_tool_t p_void_ctrl_tool);
extern bool ctrl_tool_set_loop_mode(p_void_ctrl_tool_t p_void_ctrl_tool, bool loop_mode);
extern bool ctrl_tool_set_visible(p_void_ctrl_tool_t p_void_ctrl_tool, int item, bool visible);
#ifdef __cplusplus
}
#endif	/*__cplusplus*/

#endif	/*CTRL_TOOL_H*/
