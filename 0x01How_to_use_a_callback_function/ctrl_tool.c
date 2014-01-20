/**
  *  Copyright (C) 2013-12-21  Handsome Zhou (Reference TangQiWen's code)
  */
#include <stdlib.h>
#include <string.h>
#include "data_type.h"
#include "ctrl_tool.h"

#define MAX_DATA_LEN	(256)

static int ctrl_tool_mouse_event(p_void_data_t p_void_data, p_void_ctrl_tool_t p_void_ctrl_tool,const m_evt_code_t *p_m_evt_code);
static int ctrl_tool_key_event(p_void_data_t p_void_data, p_void_ctrl_tool_t p_void_ctrl_tool, const m_evt_code_t *p_m_evt_code);
static int ctrl_tool_prev_focus(p_void_data_t p_void_data, p_void_ctrl_tool_t p_void_ctrl_tool, const m_evt_code_t *p_m_evt_code);
static int ctrl_tool_next_focus(p_void_data_t p_void_data, p_void_ctrl_tool_t p_void_ctrl_tool, const m_evt_code_t *p_m_evt_code);
static int ctrl_tool_response_click(p_void_data_t p_void_data, p_void_ctrl_tool_t p_void_ctrl_tool, const m_evt_code_t *p_m_evt_code);
static int ctrl_tool_response_press(p_void_data_t p_void_data, p_void_ctrl_tool_t p_void_ctrl_tool, const m_evt_code_t *p_m_evt_code);
static int ctrl_tool_response_release(p_void_data_t p_void_data, p_void_ctrl_tool_t p_void_ctrl_tool, const m_evt_code_t *p_m_evt_code);
static int ctrl_tool_response_focus(p_void_data_t p_void_data, p_void_ctrl_tool_t p_void_ctrl_tool, const m_evt_code_t *p_m_evt_code);
static int ctrl_tool_response_exit(p_void_data_t p_void_data, p_void_ctrl_tool_t p_void_ctrl_tool, const m_evt_code_t *p_m_evt_code);
static coordinate_t *get_coordinate(coordinate_t *coordinate,const m_evt_mouse_t *mevnet);
static bool point_in_rect(const coordinate_t *left_vertex,const rect_t *rect,const coordinate_t *coordinate);


typedef struct ctrl_tool_resource{
	ctrl_tool_res_t ctrl_tool_res;
	bool visible;
}ctrl_tool_resource_t,*p_ctrl_tool_resource_t;

typedef struct ctrl_tool{
	coordinate_t left_vertex;//left vertex of Display Interface 
	bool loop_mode;
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
	p_ctrl_tool->left_vertex.x=0;
	p_ctrl_tool->left_vertex.y=0;
	p_ctrl_tool->loop_mode=TRUE;
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

int	ctrl_tool_handle(p_void_data_t p_void_data, p_void_ctrl_tool_t p_void_ctrl_tool,const m_evt_code_t *p_m_evt_code)
{
	//printf("I'm %s() at %d in %s\n",__func__,__LINE__,__FILE__);
	//const void *scr=screen;
	p_void_data_t pvd=p_void_data;
	p_void_ctrl_tool_t pvct=p_void_ctrl_tool;
	const m_evt_code_t *pmec=p_m_evt_code;
	if(NULL==pvd||NULL==pvct||NULL==pmec){
		return CTRL_TOOL_FAILED;
	}
	
	switch(pmec->m_evt_type){
		case M_EVT_NO_INPUT://no need to deal with
			break;
		case M_EVT_MOUSE:
			ctrl_tool_mouse_event(pvd,pvct,pmec);
			break;
		case M_EVT_KEY:
			ctrl_tool_key_event(pvd,pvct,pmec);
			break;
		case M_EVT_OTHER:	//no need to deal with
			break;
		default:			//no need to deal with
			break;
	}

	return CTRL_TOOL_SUCCESS;
}

int ctrl_tool_paint(const p_void_data_t p_void_data, const p_void_ctrl_tool_t p_void_ctrl_tool)
{
	int i=0;
	const ctrl_tool_t *p_ctrl_tool=(ctrl_tool_t *)p_void_ctrl_tool;
	const p_void_data_t pvd=p_void_data;
	if(NULL==p_ctrl_tool||NULL==pvd){
		return CTRL_TOOL_FAILED;
	}

	for(i=0; i<p_ctrl_tool->total_item; i++){
		if(FALSE==p_ctrl_tool->p_ctrl_tool_resource[i].visible)
			continue;

		if(NULL!=p_ctrl_tool->p_ctrl_tool_callback->pf_event_paint){
			if(i==p_ctrl_tool->cur_item){
				p_ctrl_tool->p_ctrl_tool_callback->pf_event_paint(pvd,&p_ctrl_tool->p_ctrl_tool_resource[i].ctrl_tool_res.rect,i,TRUE);
			}else{
				p_ctrl_tool->p_ctrl_tool_callback->pf_event_paint(pvd,&p_ctrl_tool->p_ctrl_tool_resource[i].ctrl_tool_res.rect,i,FALSE);					
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

bool ctrl_tool_set_loop_mode(p_void_ctrl_tool_t p_void_ctrl_tool, bool loop_mode)
{
	ctrl_tool_t *ctrl_tool=(ctrl_tool_t *)p_void_ctrl_tool;
	if(NULL==ctrl_tool){
		return FALSE;
	}
	//ctrl_tool->loop_mode=loop_mode;
	if(loop_mode){
		ctrl_tool->loop_mode=TRUE;
	}else{
		ctrl_tool->loop_mode=FALSE;
	}
	
	return TRUE;
}

bool ctrl_tool_set_visible(p_void_ctrl_tool_t p_void_ctrl_tool, int item, bool visible)
{
	int i=item;
	ctrl_tool_t *ctrl_tool=(ctrl_tool_t *)p_void_ctrl_tool;
	if(NULL==ctrl_tool){
		return FALSE;
	}

	if((0<=i)&&(i<ctrl_tool->total_item)){
		ctrl_tool->p_ctrl_tool_resource[i].visible=visible;
	}else{
		return FALSE;
	}
	
	return TRUE;
}

int set_left_vertex(p_void_ctrl_tool_t p_void_ctrl_tool,const coordinate_t *coordinate)
{
	ctrl_tool_t *ctrl_tool=(ctrl_tool_t *)p_void_ctrl_tool;
	const coordinate_t *ce=coordinate;
	if((NULL==ctrl_tool)||(NULL==ce)){
		return CTRL_TOOL_FAILED;
	}
	ctrl_tool->left_vertex.x=((ce->x>=0)?(ce->x):(0));
	ctrl_tool->left_vertex.y=((ce->y>=0)?(ce->y):(0));
	
	return CTRL_TOOL_SUCCESS;
}

static int ctrl_tool_mouse_event(p_void_data_t p_void_data, p_void_ctrl_tool_t p_void_ctrl_tool,const m_evt_code_t *p_m_evt_code)
{
	int cur_item=-1;
	p_void_data_t pvd=p_void_data;
	ctrl_tool_t *ctrl_tool=(ctrl_tool_t *)p_void_ctrl_tool;
	const m_evt_code_t *m_evt_code=p_m_evt_code;

	if((NULL==pvd)&&(NULL==ctrl_tool)&&(NULL==m_evt_code)){
		return cur_item;
	}

	switch(m_evt_code->m_evt_param.mouse_t.mouse.bstate){
		case MOUSE_WHEEL_OUT:
			cur_item=ctrl_tool_prev_focus(pvd,ctrl_tool,m_evt_code);
			break;
		case MOUSE_WHEEL_IN:			
			cur_item=ctrl_tool_next_focus(pvd,ctrl_tool,m_evt_code);
			break;
		case MOUSE_WHEEL_CLICK:	//exit
			cur_item=ctrl_tool_response_exit(pvd,ctrl_tool,m_evt_code);
			break;		
		case MOUSE_LEFT_DOWN:
		case MOUSE_WHEEL_DOWN:
			ctrl_tool_response_press(pvd,ctrl_tool,m_evt_code);
			break;
		case MOUSE_LEFT_UP:
		case MOUSE_WHEEL_UP:
			ctrl_tool_response_release(pvd,ctrl_tool,m_evt_code);
			break;
		case MOUSE_LEFT_CLICK:
			cur_item=ctrl_tool_response_focus(pvd,ctrl_tool,m_evt_code);
			break;	
			
		default:
			break;
	}
	
	return cur_item;
}

static int ctrl_tool_key_event(p_void_data_t p_void_data, p_void_ctrl_tool_t p_void_ctrl_tool,const m_evt_code_t *p_m_evt_code)
{
	p_void_data_t pvd=p_void_data;
	ctrl_tool_t *ctrl_tool=(ctrl_tool_t *)p_void_ctrl_tool;
	const m_evt_code_t *m_evt_code=p_m_evt_code;
	int cur_item=-1;
	if((NULL==pvd)||(NULL==ctrl_tool)||(NULL==m_evt_code)){
		return cur_item;
	}

	switch(m_evt_code->m_evt_param.key_t.key){
		case KEY_UP:
		case KEY_LEFT:
			cur_item=ctrl_tool_prev_focus(pvd,ctrl_tool,m_evt_code);
			break;
			
		case KEY_DOWN:
		case KEY_RIGHT:			
			cur_item=ctrl_tool_next_focus(pvd,ctrl_tool,m_evt_code);
			break;
			
		case KEY_ENTER:
			cur_item=ctrl_tool_response_focus(pvd,ctrl_tool,m_evt_code);
			break;
			
		case KEY_ESC:
			cur_item=ctrl_tool_response_exit(pvd,ctrl_tool,m_evt_code);
			break;
			
		default:
			cur_item=-1;
			break;
	}
	
	return cur_item;
}

static int ctrl_tool_prev_focus(p_void_data_t p_void_data, p_void_ctrl_tool_t p_void_ctrl_tool, const m_evt_code_t *p_m_evt_code)
{
	int i=0;
	int cur_item=-1;
	p_void_data_t pvd=p_void_data;
	ctrl_tool_t *ctrl_tool=(ctrl_tool_t *)p_void_ctrl_tool;	
	const m_evt_code_t *m_evt_code=p_m_evt_code;
	if((NULL==pvd)||(NULL==ctrl_tool)||(NULL==m_evt_code)){
		return cur_item;
	}
	for(i=0; i<ctrl_tool->total_item; i++){
		if(0==ctrl_tool->cur_item){
			if(FALSE==ctrl_tool->loop_mode){
				break;
			}
		}
		
		ctrl_tool->cur_item=(ctrl_tool->cur_item>0)?(ctrl_tool->cur_item-1):(ctrl_tool->total_item-1);
		cur_item=ctrl_tool->cur_item;
		if(FALSE!=ctrl_tool->p_ctrl_tool_resource[ctrl_tool->cur_item].visible){
			break;
		}
	}

	if((FALSE!=ctrl_tool->p_ctrl_tool_resource[ctrl_tool->cur_item].visible)&&(NULL!=ctrl_tool->p_ctrl_tool_callback->pf_event_select)){
		ctrl_tool->p_ctrl_tool_callback->pf_event_select(pvd,m_evt_code,ctrl_tool->cur_item);
	}
			
	return cur_item;
}

static int ctrl_tool_next_focus(p_void_data_t p_void_data, p_void_ctrl_tool_t p_void_ctrl_tool, const m_evt_code_t *p_m_evt_code)
{
	int i=0;
	int cur_item=-1;
	p_void_data_t pvd=p_void_data;
	ctrl_tool_t *ctrl_tool=(ctrl_tool_t *)p_void_ctrl_tool;	
	const m_evt_code_t *m_evt_code=p_m_evt_code;
	if((NULL==pvd)||(NULL==ctrl_tool)||(NULL==m_evt_code)){
		return cur_item;
	}
	
	for(i=0; i<ctrl_tool->total_item; i++){
		if(ctrl_tool->total_item-1==ctrl_tool->cur_item){
			if(FALSE==ctrl_tool->loop_mode){
				break;
			}					
		}

		ctrl_tool->cur_item=(ctrl_tool->cur_item<ctrl_tool->total_item-1)?(ctrl_tool->cur_item+1):(0);
		cur_item=ctrl_tool->cur_item;
		if(FALSE!=ctrl_tool->p_ctrl_tool_resource[ctrl_tool->cur_item].visible){
			break;
		}				
	}
		
	if((FALSE!=ctrl_tool->p_ctrl_tool_resource[ctrl_tool->cur_item].visible)&&(NULL!=ctrl_tool->p_ctrl_tool_callback->pf_event_select)){
		ctrl_tool->p_ctrl_tool_callback->pf_event_select(pvd,m_evt_code,ctrl_tool->cur_item);
	}	

	return cur_item;
}
static int ctrl_tool_response_click(p_void_data_t p_void_data, p_void_ctrl_tool_t p_void_ctrl_tool, const m_evt_code_t *p_m_evt_code)
{
	int i=0;
	int cur_item=-1;
	coordinate_t coordinate;
	p_void_data_t pvd=p_void_data;
	ctrl_tool_t *ctrl_tool=(ctrl_tool_t *)p_void_ctrl_tool;
	const m_evt_code_t *m_evt_code=p_m_evt_code;
	if((NULL==pvd)||(NULL==ctrl_tool)||(NULL==m_evt_code)){
		return cur_item;
	}

	if(NULL==get_coordinate(&coordinate,&m_evt_code->m_evt_param.mouse_t.mouse)){
		return cur_item;
	}
	
	for(i=0; i<ctrl_tool->total_item; i++){
		if(FALSE==ctrl_tool->p_ctrl_tool_resource[i].visible){
			continue;
		}
	
		if(FALSE!=point_in_rect(&ctrl_tool->left_vertex,&ctrl_tool->p_ctrl_tool_resource[i].ctrl_tool_res.rect,&coordinate)){
			ctrl_tool->cur_item=i;
			if((FALSE!=ctrl_tool->p_ctrl_tool_resource[ctrl_tool->cur_item].visible)&&(NULL!=ctrl_tool->p_ctrl_tool_callback->pf_event_pen_down)){
				ctrl_tool->p_ctrl_tool_callback->pf_event_pen_down(pvd,m_evt_code,ctrl_tool->cur_item);
				cur_item=ctrl_tool->cur_item;
			}
		}
	}
	
	return cur_item;
}

static int ctrl_tool_response_press(p_void_data_t p_void_data, p_void_ctrl_tool_t p_void_ctrl_tool, const m_evt_code_t *p_m_evt_code)
{
	//mvwprintw(stdscr,1,1,"I'm %s() at %d in %s\n",__FUNCTION__,__LINE__,__FILE__);
	
	return 0;
}

static int ctrl_tool_response_release(p_void_data_t p_void_data, p_void_ctrl_tool_t p_void_ctrl_tool, const m_evt_code_t *p_m_evt_code)
{
	//mvwprintw(stdscr,1,1,"I'm %s() at %d in %s\n",__FUNCTION__,__LINE__,__FILE__);
	
	return 0;
}

static int ctrl_tool_response_focus(p_void_data_t p_void_data, p_void_ctrl_tool_t p_void_ctrl_tool, const m_evt_code_t *p_m_evt_code)
{
	int cur_item=-1;
	p_void_data_t pvd=p_void_data;
	ctrl_tool_t *ctrl_tool=(ctrl_tool_t *)p_void_ctrl_tool;
	const m_evt_code_t *m_evt_code=p_m_evt_code;
	if((NULL==pvd)||(NULL==ctrl_tool)||(NULL==m_evt_code)){
		return cur_item;
	}
	switch(m_evt_code->m_evt_type){
		case M_EVT_MOUSE:
			cur_item=ctrl_tool_response_click(pvd,ctrl_tool,m_evt_code);
			break;
		case M_EVT_KEY:
			if((TRUE==ctrl_tool->p_ctrl_tool_resource[ctrl_tool->cur_item].visible)&&(NULL!=ctrl_tool->p_ctrl_tool_callback->pf_event_enter)){
				ctrl_tool->p_ctrl_tool_callback->pf_event_enter(pvd,m_evt_code,ctrl_tool->cur_item);
				cur_item=ctrl_tool->cur_item;
			}
			break;
		default:
			cur_item=-1;
			break;
	}

	return cur_item;
}

static int ctrl_tool_response_exit(p_void_data_t p_void_data, p_void_ctrl_tool_t p_void_ctrl_tool, const m_evt_code_t *p_m_evt_code)
{
	int cur_item=-1;
	p_void_data_t pvd=p_void_data;
	ctrl_tool_t *ctrl_tool=(ctrl_tool_t *)p_void_ctrl_tool;
	const m_evt_code_t *m_evt_code=p_m_evt_code;
	if((NULL==pvd)||(NULL==ctrl_tool)||(NULL==m_evt_code)){
		return cur_item;
	}
	
	if(NULL!=ctrl_tool->p_ctrl_tool_callback->pf_event_exit){
		ctrl_tool->p_ctrl_tool_callback->pf_event_exit(pvd,m_evt_code,ctrl_tool->cur_item);
	}
	cur_item=ctrl_tool->cur_item;
	
	return cur_item;
}

static coordinate_t *get_coordinate(coordinate_t *coordinate,const m_evt_mouse_t *mevnet)
{
	coordinate_t *ce=coordinate;
	const m_evt_mouse_t *evt=mevnet;
	if(NULL==ce||NULL==evt){
		return ce;
	}
	ce->y=(T_S16)evt->y;
	ce->x=(T_S16)evt->x;
	
	return ce;
}

static bool point_in_rect(const coordinate_t *left_vertex,const rect_t *rect,const coordinate_t *coordinate)
{
	bool ret=FALSE;
	rect_t rect_btn;
	const coordinate_t *lv=left_vertex;
	const rect_t *rct=rect;
	const coordinate_t *ce=coordinate;
	if((NULL==lv)||(NULL==rct)||(NULL==ce)){
		return FALSE;
	}
	
	rect_btn.top=lv->y+rct->top;
	rect_btn.left=lv->x+rct->left;
	rect_btn.height=rct->height;
	rect_btn.width=rct->width;
	
	ret=coordinate_in_rect(&rect_btn,ce);
	
	return ret;
}
