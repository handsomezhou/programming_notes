/**
  *  Copyright (C) 2014-06-10  Handsome Zhou
  */

#ifndef INCREASE_TRIANGLE_H
#define INCREASE_TRIANGLE_H

#define LAYERS_MIN_VALUE			(6)
#define LAYERS_MAX_VALUE			(10)
#define LAYERS_DEFAULT_VALUE		(LAYERS_MIN_VALUE)
#define LAYERS_NULL_VALUE			(-1)

#define BASE_VALUE_MIN_VALUE		(8)
#define BASE_VALUE_MAX_VALUE		(80)
#define BASE_VALUE_DEFAULT_VALUE	(BASE_VALUE_MIN_VALUE)
#define BASE_VALUE_NULL_VALUE		(-1)

#define MULTIPLE_MIN_VALUE			(2)
#define MULTIPLE_MAX_VALUE			(4)
#define MULTIPLE_DEFAULT_VALUE		(MULTIPLE_MIN_VALUE)
#define MULTIPLE_NULL_VALUE			(-1)

struct increase_triangle;
typedef struct increase_triangle increase_triangle_t;

/*
int layers; 
int base_value;
int multiple;
*/
/*************************************************************************
	Function: increase_triangle_init
	Parameter:
		layers:This parameter is preferably greater than or equal to LAYERS_MIN_VALUE less than or equal LAYERS_MAX_VALUE;
		base_value:This parameter is preferably greater than or equal to BASE_VALUE_MIN_VALUE less than or equal BASE_VALUE_MAX_VALUE;
		multiple:This parameter is preferably greater than or equal to MULTIPLE_MIN_VALUE less than or equal MULTIPLE_MAX_VALUE;
		Of course,we can use default value of these parameters if we set these parameters to -1.
	Return:   0  
*************************************************************************/
extern increase_triangle_t *increase_triangle_init(int layers, int base_value, int multiple);
extern void increase_triangle_free(increase_triangle_t *increase_triangle);
extern void increase_triangle_show(increase_triangle_t *increase_triangle);

extern void set_layers(increase_triangle_t *increase_triangle, int layers);
extern int get_layers(increase_triangle_t *increase_triangle);
extern void set_base_value(increase_triangle_t *increase_triangle, int base_value);
extern int get_base_value(increase_triangle_t *increase_triangle);
extern void set_multiple(increase_triangle_t *increase_triangle, int multiple);
extern int get_multiple(increase_triangle_t *increase_triangle);

#endif/*INCREASE_TRIANGLE_H*/
