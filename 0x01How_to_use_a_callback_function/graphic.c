/**
  *  Copyright (C) 2013-09-10  Handsome Zhou
  */
#include <assert.h>
#include "data_type.h"
#include "graphic.h"

T_BOOL coordinate_in_rect(const T_RECT *rect,const T_COORDINATE *coordinate)
{
	assert(NULL!=rect&&NULL!=coordinate);

	if((coordinate->x >= rect->left && coordinate->x < rect->left+rect->width)&&\
		(coordinate->y >= rect->top && coordinate->y < rect->top+rect->height)){
		return TRUE;
	}

	return FALSE;
}

