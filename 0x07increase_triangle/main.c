/**
  *  Copyright (C) 2014-06-10  Handsome Zhou
  */

#include <stdio.h>

int main(void)
{
	increase_triangle_t *p_increase_triangle=NULL;

	//init increase_triangle
	p_increase_triangle=increase_triangle_init(0,0,0);
	if(NULL==p_increase_triangle){
		printf("increase_triangle init failed!\n");
		return -1;
	}



	//free	increase_triangle
	if(NULL!=p_increase_triangle){
		increase_triangle_free(p_increase_triangle);
		p_increase_triangle=NULL;
	}
	
	return 0;
}

