/**
  *  Copyright (C) 2013-09-10  Handsome Zhou
  */
#include <assert.h>
#include "data_type.h"

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

