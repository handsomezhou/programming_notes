/**
  *  Copyright (C) 2013-12-21  Handsome Zhou (Reference TangQiWen's code)
  */
#include <stdlib.h>
#include <string.h>
#include "ctrl_tool.h"

#define MAX_DATA_LEN	(256)

static int ctrl_tool_mouse_event(const void *screen, p_void_ctrl_tool_t p_void_ctrl_tool, m_evt_code_t *p_m_evt_code);
static int ctrl_tool_key_event(p_void_ctrl_tool_t p_void_ctrl_tool, m_evt_code_t *p_m_evt_code);

typedef struct ctrl_tool_resource{
	ctrl_tool_res_t ctrl_tool_res;
	bool visible;
}ctrl_tool_resource_t,*p_ctrl_tool_resource_t;

typedef struct ctrl_tool{
	bool loopmode;
	int total_item;
	int cur_item;
	ctrl_tool_resource_t *p_ctrl_tool_resource;
	ctrl_tool_callback_t *p_ctrl_tool_callback;
}ctrl_tool_t;

p_void_ctrl_tool_t ctrl_tool_init(int res_num, const ctrl_tool_res_t *p_res, const ctrl_tool_callback_t *p_callback_fun)
{
	int i=0;
	ctrl_tool_t *p_ctrl_tool=NULL;
	if((res_num<0)||(NULL==p_res)||(NULL==p_callback_fun)){
		return NULL;
	}

	p_ctrl_tool=(ctrl_tool_t *)malloc(sizeof(ctrl_tool_t));
	if(NULL==p_ctrl_tool){
		return NULL;
	}
	memset(p_ctrl_tool,0,sizeof(ctrl_tool_t));
	p_ctrl_tool->loopmode=TRUE;
	p_ctrl_tool->total_item=res_num;
	p_ctrl_tool->cur_item=0;

	p_ctrl_tool->p_ctrl_tool_resource=(ctrl_tool_resource_t *)malloc(p_ctrl_tool->total_item*sizeof(ctrl_tool_resource_t));
	if(NULL==p_ctrl_tool->p_ctrl_tool_resource){
		free(p_ctrl_tool);
		return NULL;
	}
	memset(p_ctrl_tool->p_ctrl_tool_resource,0,p_ctrl_tool->total_item*sizeof(ctrl_tool_resource_t));
	
	for(i=0; i<p_ctrl_tool->total_item; i++){
		p_ctrl_tool->p_ctrl_tool_resource[i].visible=TRUE;
		cpy_rect(&p_ctrl_tool->p_ctrl_tool_resource[i].ctrl_tool_res.rect,&p_res[i].rect);
		p_ctrl_tool->p_ctrl_tool_resource[i].ctrl_tool_res.icon_normal=p_res[i].icon_normal;
		p_ctrl_tool->p_ctrl_tool_resource[i].ctrl_tool_res.icon_select=p_res[i].icon_select;
		p_ctrl_tool->p_ctrl_tool_resource[i].ctrl_tool_res.pdata=(char *)malloc(MAX_DATA_LEN);
		if(NULL==p_ctrl_tool->p_ctrl_tool_resource[i].ctrl_tool_res.pdata){
			for(--i; i>=0; i--){
				free(p_ctrl_tool->p_ctrl_tool_resource[i].ctrl_tool_res.pdata);
				p_ctrl_tool->p_ctrl_tool_resource[i].ctrl_tool_res.pdata=NULL;
			}
			free(p_ctrl_tool->p_ctrl_tool_resource);
			p_ctrl_tool->p_ctrl_tool_resource=NULL;

			free(p_ctrl_tool);
			p_ctrl_tool=NULL;

			return NULL;
		}
		memset(p_ctrl_tool->p_ctrl_tool_resource[i].ctrl_tool_res.pdata,0,MAX_DATA_LEN);
		strncpy(p_ctrl_tool->p_ctrl_tool_resource[i].ctrl_tool_res.pdata,p_res[i].pdata,\
			(strlen(p_res[i].pdata)<=MAX_DATA_LEN)?(strlen(p_res[i].pdata)):(MAX_DATA_LEN));
	}

	p_ctrl_tool->p_ctrl_tool_callback=(ctrl_tool_callback_t *)malloc(sizeof(ctrl_tool_callback_t));
	if(NULL==p_ctrl_tool->p_ctrl_tool_callback){
		for(i=0; i<p_ctrl_tool->total_item; i++){
			free(p_ctrl_tool->p_ctrl_tool_resource[i].ctrl_tool_res.pdata);
			p_ctrl_tool->p_ctrl_tool_resource[i].ctrl_tool_res.pdata=NULL;
		}

		free(p_ctrl_tool->p_ctrl_tool_resource);
		p_ctrl_tool->p_ctrl_tool_resource=NULL;

		free(p_ctrl_tool);
		p_ctrl_tool=NULL;

		return NULL;
		
	}
	memset(p_ctrl_tool->p_ctrl_tool_callback,0,sizeof(ctrl_tool_callback_t));
	memcpy(p_ctrl_tool->p_ctrl_tool_callback,p_callback_fun,sizeof(ctrl_tool_callback_t));
	
	return p_ctrl_tool;
}

int	ctrl_tool_handle(const void *screen, const p_void_ctrl_tool_t p_void_ctrl_tool,const m_evt_code_t *p_m_evt_code)
{
	//printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	const void *scr=screen;
	const p_void_ctrl_tool_t pvct=p_void_ctrl_tool;
	const m_evt_code_t *pmec=p_m_evt_code;
	if(NULL==scr||NULL==pvct||NULL==pmec){
		return CTRL_TOOL_FAILED;
	}
	
	switch(pmec->m_evt_type){
		case M_EVT_NO_INPUT://no need to deal with
			break;
		case M_EVT_MOUSE:
			ctrl_tool_mouse_event(scr,pvct,pmec);
			break;
		case M_EVT_KEY:
			ctrl_tool_key_event(pvct,pmec);
			break;
		case M_EVT_OTHER:	//no need to deal with
			break;
		default:			//no need to deal with
			break;
	}

	return CTRL_TOOL_SUCCESS;
}

int ctrl_tool_paint(const void *screen, const p_void_ctrl_tool_t p_void_ctrl_tool)
{
	int i=0;
	const ctrl_tool_t *p_ctrl_tool=(ctrl_tool_t *)p_void_ctrl_tool;
	const void *scr=screen;
	if(NULL==p_ctrl_tool||NULL==scr){
		return CTRL_TOOL_FAILED;
	}

	for(i=0; i<p_ctrl_tool->total_item; i++){
		if(TRUE!=p_ctrl_tool->p_ctrl_tool_resource[i].visible)
			continue;

		if(NULL!=p_ctrl_tool->p_ctrl_tool_callback->pf_event_paint){
			if(i==p_ctrl_tool->cur_item){
				p_ctrl_tool->p_ctrl_tool_callback->pf_event_paint(scr,&p_ctrl_tool->p_ctrl_tool_resource[i].ctrl_tool_res.rect,i,TRUE);
			}else{
				p_ctrl_tool->p_ctrl_tool_callback->pf_event_paint(scr,&p_ctrl_tool->p_ctrl_tool_resource[i].ctrl_tool_res.rect,i,FALSE);					
			}
		}
	}

	return CTRL_TOOL_SUCCESS;
}

void ctrl_tool_free(p_void_ctrl_tool_t p_void_ctrl_tool)
{
	int i=0;
	ctrl_tool_t *p_ctrl_tool=(ctrl_tool_t *)p_void_ctrl_tool;
	if(NULL==p_ctrl_tool){
		return;
	}

	if(NULL!=p_ctrl_tool->p_ctrl_tool_resource){
		for(i=0; i<p_ctrl_tool->total_item; i++){
			free(p_ctrl_tool->p_ctrl_tool_resource[i].ctrl_tool_res.pdata);
			p_ctrl_tool->p_ctrl_tool_resource[i].ctrl_tool_res.pdata=NULL;
		}

		free(p_ctrl_tool->p_ctrl_tool_resource);
		p_ctrl_tool->p_ctrl_tool_resource=NULL;
	}

	if(NULL!=p_ctrl_tool->p_ctrl_tool_callback){
		free(p_ctrl_tool->p_ctrl_tool_callback);
		p_ctrl_tool->p_ctrl_tool_callback=NULL;
	}

	free(p_ctrl_tool);
	p_ctrl_tool=NULL;
	
	return;
}

static int ctrl_tool_mouse_event(const void *screen, p_void_ctrl_tool_t p_void_ctrl_tool, m_evt_code_t *p_m_evt_code)
{

	return CTRL_TOOL_SUCCESS;
}

static int ctrl_tool_key_event(p_void_ctrl_tool_t p_void_ctrl_tool, m_evt_code_t *p_m_evt_code)
{
	ctrl_tool_t *ctrl_tool=(ctrl_tool_t *)p_void_ctrl_tool;
	m_evt_code_t *m_evt_code=p_m_evt_code;
	int i=0;
	if((NULL==ctrl_tool)||(NULL==m_evt_code)){
		return CTRL_TOOL_FAILED;
	}

	switch(m_evt_code->m_evt_param.key_t.key){
		case KEY_UP:
		case KEY_LEFT:
//			(ctrl_tool->cur_item>0)?(ctrl_tool->cur_item--):(ctrl_tool->cur_item=ctrl_tool->total_item-1);
			for(i=0; i<ctrl_tool->total_item; i++){
				if(0==ctrl_tool->cur_item){
					if(FALSE==ctrl_tool->loopmode){
						break;
					}
				}
				
				ctrl_tool->cur_item=(ctrl_tool->cur_item>0)?(ctrl_tool->cur_item-1):(ctrl_tool->total_item-1);
				if(TRUE==ctrl_tool->p_ctrl_tool_resource[ctrl_tool->cur_item].visible){
					break;
				}
			}

			if((TRUE==ctrl_tool->p_ctrl_tool_resource[ctrl_tool->cur_item].visible)&&(NULL!=ctrl_tool->p_ctrl_tool_callback->pf_event_select)){
				ctrl_tool->p_ctrl_tool_callback->pf_event_select(m_evt_code,ctrl_tool->cur_item);
			}
			
			break;
		case KEY_DOWN:
		case KEY_RIGHT:
			//(ctrl_tool->cur_item<ctrl_tool->total_item-1)?(ctrl_tool->cur_item++):(ctrl_tool->cur_item=0);			
			for(i=0; i<ctrl_tool->total_item; i++){
				if(ctrl_tool->total_item-1==ctrl_tool->cur_item){
					if(FALSE==ctrl_tool->loopmode){
						break;
					}					
				}

				ctrl_tool->cur_item=(ctrl_tool->cur_item<ctrl_tool->total_item-1)?(ctrl_tool->cur_item+1):(0);
				if(TRUE==ctrl_tool->p_ctrl_tool_resource[ctrl_tool->cur_item].visible){
					break;
				}				
			}
			
			if((TRUE==ctrl_tool->p_ctrl_tool_resource[ctrl_tool->cur_item].visible)&&(NULL!=ctrl_tool->p_ctrl_tool_callback->pf_event_select)){
				ctrl_tool->p_ctrl_tool_callback->pf_event_select(m_evt_code,ctrl_tool->cur_item);
			}			
			break;
		default:
			break;
	}
	
	return CTRL_TOOL_SUCCESS;
}

