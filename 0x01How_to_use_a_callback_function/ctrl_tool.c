/**
  *  Copyright (C) 2013-12-21  Handsome Zhou (Reference TangQiWen's code)
  */

#include "ctrl_tool.h"

p_ctrl_tool_t ctrl_tool_init(int res_num, const ctrl_tool_res_t *p_res, const ctrl_tool_callback_t *p_callback_fun)
{
	printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	
	return NULL;
}

int	ctrl_tool_handle(const p_ctrl_tool_t *p_ctrl_tool,const m_evt_code_t *p_m_evt_code)
{
	printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);

	return CTRL_TOOL_SUCCESS;
}

int ctrl_tool_paint(const p_ctrl_tool_t *p_ctrl_tool)
{
	printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);

	return CTRL_TOOL_SUCCESS;
}

void ctrl_tool_free(p_ctrl_tool_t *p_ctrl_tool)
{
	printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);

	return;
}


