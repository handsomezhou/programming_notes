/**
  *  Copyright (C) 2014-06-10  Handsome Zhou
  */

struct increase_triangle{
  int layers; //the layers of increase triangle,layers belong to [1,N],N is a natural number
  int base_value; //the start value of	increase triangle
  int multiple;   //the increase multiple of increase_triangle
};

typedef struct layer_index{

	struct layer_index *next_layer;
}layer_index_t;



increase_triangle_t *increase_triangle_init(int layers, int base_value, int multiple)
{
	
	return NULL;
}

void increase_triangle_free(increase_triangle_t *increase_triangle)
{

	return ;
}


void set_layers(increase_triangle_t *increase_triangle, int layers)
{
	if(NULL!=increase_triangle){
		increase_triangle->layers=layers;
	}

	return;
}

int get_layers(increase_triangle_t *increase_triangle)
{
	int layers=LAYERS_NULL_VALUE;
	if(NULL!=increase_triangle){
		layers=increase_triangle->layers;
	}

	return layers;
}

void set_base_value(increase_triangle_t *increase_triangle, int base_value)
{
	if(NULL!=increase_triangle){
		increase_triangle->base_value=base_value;
	}	

	return;
}

int get_base_value(increase_triangle_t *increase_triangle)
{
	int base_value=BASE_VALUE_NULL_VALUE;
	if(NULL!=increase_triangle){
		base_value=increase_triangle->base_value;
	}

	return base_value;
}

void set_multiple(increase_triangle_t *increase_triangle, int multiple)
{
	if(NULL!=increase_triangle){
		increase_triangle->multiple=multiple;
	}

	return;
}

int get_multiple(increase_triangle_t *increase_triangle)
{
	int multiple=MULTIPLE_NULL_VALUE;
	if(NULL!=increase_triangle){
		multiple=increase_triangle->multiple;
	}

	return multiple;
	
}
