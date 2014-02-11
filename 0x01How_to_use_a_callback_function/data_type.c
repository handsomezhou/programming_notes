/**
  *  Copyright (C) 2013-09-10  Handsome Zhou
  */
#include <assert.h>
#include "data_type.h"

coordinate_t *get_coordinate(coordinate_t *coordinate,const m_evt_mouse_t *mevent)
{
	coordinate_t *ce=coordinate;
	const m_evt_mouse_t *evt=mevent;
	if(NULL==ce||NULL==evt){
		return ce;
	}
	ce->y=(int16_t)evt->y;
	ce->x=(int16_t)evt->x;
	
	return ce;
}

extern coordinate_t *get_coordinate_from_m_evt_code(coordinate_t *coordinate,const m_evt_code_t *m_evt_code)
{
	coordinate_t *ce=coordinate;
	const m_evt_code_t *mec=m_evt_code;
	if((NULL==ce)||(NULL==mec)){
		return ce;
	}

	return get_coordinate(ce,&mec->m_evt_param.mouse_t.mouse);
}


coordinate_t *cpy_coordinate(coordinate_t *dst, const coordinate_t *src)
{
	assert(NULL!=dst&&NULL!=src);
	coordinate_t *addr=dst;
	dst->y=src->y;
	dst->x=src->x;
		  
	return addr;
}

rect_t *cpy_rect(rect_t *dst, const rect_t *src)
{
	assert(NULL!=dst&&NULL!=src);
	rect_t *addr=dst;
		  
	dst->top=src->top;
	dst->left=src->left;
	dst->height=src->height;
	dst->width=src->width;
		  
	return addr;
}

