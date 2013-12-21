/**
  *  Copyright (C) 2013-09-10  Handsome Zhou
  */
#include <assert.h>
#include "data_type.h"

T_COORDINATE *cpy_coordinate(T_COORDINATE *dst, const T_COORDINATE *src)
{
	assert(NULL!=dst&&NULL!=src);
	T_COORDINATE *addr=dst;
	dst->y=src->y;
	dst->x=src->x;
		  
	return addr;
}

T_RECT *cpy_rect(T_RECT *dst, const T_RECT *src)
{
	assert(NULL!=dst&&NULL!=src);
	T_RECT *addr=dst;
		  
	dst->top=src->top;
	dst->left=src->left;
	dst->height=src->height;
	dst->width=src->width;
		  
	return addr;
}

