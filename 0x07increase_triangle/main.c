/**
  *  Copyright (C) 2014-06-10  Handsome Zhou
  */

#include <stdio.h>
#include "increase_triangle.h"

int main(void)
{
	increase_triangle_t *p_increase_triangle=NULL;

	//init increase_triangle
	p_increase_triangle=increase_triangle_init(LAYERS_MAX_VALUE,-1,-1);
	if(NULL==p_increase_triangle){
		printf("increase_triangle init failed!\n");
		return -1;
	}


	increase_triangle_show(p_increase_triangle);
	
	//free	increase_triangle
	if(NULL!=p_increase_triangle){
		increase_triangle_free(p_increase_triangle);
		p_increase_triangle=NULL;
	}
	
	return 0;
}

