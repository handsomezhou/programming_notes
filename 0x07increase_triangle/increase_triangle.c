/**
  *  Copyright (C) 2014-06-10  Handsome Zhou
  */
#include <stdio.h>
#include <stdlib.h>
#include "increase_triangle.h"

typedef struct elem{
	void *elem;
	struct elem *next_elem;
}elem_t;

typedef struct layer_index{
	int elem_num;	//The number of elements per layer
	elem_t *elem;   //save elements per layer
	struct layer_index *next_layer;	
}layer_index_t;

struct increase_triangle{
  int layers; //the layers of increase triangle,layers belong to [1,N],N is a natural number
  int base_value; //the start value of	increase triangle
  int multiple;   //the increase multiple of increase_triangle
  layer_index_t *layer_index;	//save  layer info of increase triangle
};

static layer_index_t *layer_index_init(layer_index_t **p_layer_index, int layers);
static void layer_index_free(layer_index_t *layer_index);
static layer_index_t *malloc_layer_index();
static void free_layer_index(layer_index_t *layer_index);
static void show_layer_index(layer_index_t *layer_index);
static void set_elem_num(layer_index_t *layer_index, int elem_num);
static int get_elem_num(const layer_index_t *layer_index);
typedef void *(*pf_data_elem_malloc)();
typedef void (*pf_data_elem_free)(void *);
static void *int_elem_malloc();
static void int_elem_free(void *elem);
static elem_t *elem_malloc(pf_data_elem_malloc f_data_elem_malloc);
static void elem_free(elem_t *elem,pf_data_elem_free f_data_elem_free);


static void *int_elem_malloc()
{		
	int *p_elem=NULL;
	p_elem=(int *)malloc(sizeof(int));
	if(NULL==p_elem){		
		printf("I'm %s() at %d in %s:malloc int failed!\n",__func__,__LINE__,__FILE__);
		return NULL;
	}

	return p_elem;
}

static void int_elem_free(void *elem)
{
	int *p_elem=(int *)elem;
	free(p_elem);
	//p_elem=NULL;
}

static elem_t *elem_malloc(pf_data_elem_malloc f_data_elem_malloc)
{
	static int i=0;
	elem_t *p_elem=NULL;
	p_elem=(elem_t *)malloc(sizeof(elem_t));
	if(NULL==p_elem){
		printf("I'm %s() at %d in %s:malloc elem_t failed!\n",__func__,__LINE__,__FILE__);
		return NULL;
	}
	
	p_elem->elem=f_data_elem_malloc();
	if(NULL==p_elem->elem){
		free(p_elem);
		p_elem=NULL;
		return NULL;
	}
	p_elem->next_elem=NULL;

	printf("malloc[%4d]\n",i++);
	return p_elem;
}

static void elem_free(elem_t *elem,pf_data_elem_free f_data_elem_free)
{
	static int i=0;
	elem_t *p_elem=elem;
	if(NULL==p_elem){
		return;
	}

	printf("free[%4d]\n",i++);

	if(NULL!=f_data_elem_free){
		f_data_elem_free(p_elem->elem);
		p_elem->elem=NULL;
	}

	free(p_elem);
//	p_elem=NULL;
}

static layer_index_t *layer_index_init(layer_index_t **p_layer_index, int layers)
{
	int i=0;
	layer_index_t *first_layer_index=NULL;
	layer_index_t *cur_layer_index=NULL;
	layer_index_t *next_layer_index=NULL;

	// malloc layer_index_t
	first_layer_index=malloc_layer_index();
	if(NULL==first_layer_index){
		return NULL;
	}
	
	cur_layer_index=first_layer_index;
	cur_layer_index->elem_num=1;
	cur_layer_index->elem=NULL;
	cur_layer_index->next_layer=NULL;
	for(i=1; i<layers; i++){
		next_layer_index=malloc_layer_index();
		if(NULL==next_layer_index){
			cur_layer_index=first_layer_index;
			while(NULL!=cur_layer_index){
				next_layer_index=cur_layer_index->next_layer;
				//free(cur_layer_index);
				free_layer_index(cur_layer_index);
				cur_layer_index=next_layer_index;
			}
			return NULL;
		}
		cur_layer_index->next_layer=next_layer_index;
		cur_layer_index=next_layer_index;
		cur_layer_index->elem_num=i+1;
		cur_layer_index->elem=NULL;
		cur_layer_index->next_layer=NULL;
	}

	//malloc elem per layer
	elem_t *first_elem=NULL;
	elem_t *cur_elem=NULL;
	elem_t *next_elem=NULL;
	for(cur_layer_index=first_layer_index; NULL!=cur_layer_index;cur_layer_index=cur_layer_index->next_layer){
		//cur_elem=cur_layer_index->elem;
		first_elem=elem_malloc(int_elem_malloc);
		if(NULL==first_elem){
			layer_index_free(first_layer_index);
			return NULL;
		}
		
		cur_elem=first_elem;
		cur_elem->next_elem=NULL;
		for(i=1; i<cur_layer_index->elem_num; i++){
			next_elem=elem_malloc(int_elem_malloc);
			if(NULL==next_elem){
				layer_index_free(first_layer_index);
			}
			cur_elem->next_elem=next_elem;
			cur_elem=next_elem;
			cur_elem->next_elem=NULL;
		}
		cur_layer_index->elem=first_elem;
		printf("j\n");
	}
	
	*p_layer_index=first_layer_index;
	return (*p_layer_index);
	
}


static void layer_index_free(layer_index_t *layer_index)
{
	layer_index_t *cur_layer_index=layer_index;
	layer_index_t *next_layer_index=NULL;
	elem_t *cur_elem=NULL;
	elem_t *next_elem=NULL;
	if(NULL==cur_layer_index){
		return;
	}

	while(NULL!=cur_layer_index){
		next_layer_index=cur_layer_index->next_layer;
		cur_elem=cur_layer_index->elem;
		while(NULL!=cur_elem){
			next_elem=cur_elem->next_elem;
			elem_free(cur_elem,int_elem_free);
			cur_elem=next_elem;
		}
		printf("k\n");
		free_layer_index(cur_layer_index);
		cur_layer_index=next_layer_index;
	}
	
}
static layer_index_t *malloc_layer_index()
{
	layer_index_t *p_layer_index=NULL;
	p_layer_index=(layer_index_t *)malloc(sizeof(layer_index_t));
	if(NULL==p_layer_index){
		printf("I'm %s() at %d in %s:malloc layer_index_t failed!\n",__func__,__LINE__,__FILE__);
		//return NULL;
	}

	return p_layer_index;
}

static void free_layer_index(layer_index_t *layer_index)
{
	if(NULL!=layer_index){
		free(layer_index);
		layer_index=NULL;	// have effect within this function
	}

	return;
}

static void show_layer_index(layer_index_t *layer_index)
{
	layer_index_t *p_layer_index=layer_index;
	int i=0;
	if(NULL==p_layer_index){
		return;
	}

	while(NULL!=p_layer_index){
		printf("%s() i=[%d]\n",__func__,++i);
		p_layer_index=p_layer_index->next_layer;
	}
}

static void set_elem_num(layer_index_t *layer_index, int elem_num)
{
	int en=((elem_num<0)?(0):(elem_num));
	
	if(NULL!=layer_index){
		layer_index->elem_num=en;
	}

	return;
}
static int get_elem_num(const layer_index_t *layer_index)
{
	int en=0;
	if(NULL!=layer_index){
		en=layer_index->elem_num;
	}

	return en;
}

increase_triangle_t *increase_triangle_init(int layers, int base_value, int multiple)
{
	int lyrs=layers;
	int bs_vl=base_value;
	int mltpl=multiple;
	layer_index_t *layer_index_ret=NULL;
	if(LAYERS_NULL_VALUE==lyrs){
		lyrs=LAYERS_MIN_VALUE;
	}

	if(BASE_VALUE_NULL_VALUE==bs_vl){
		bs_vl=BASE_VALUE_MIN_VALUE;
	}

	if(MULTIPLE_NULL_VALUE==mltpl){
		mltpl=MULTIPLE_MIN_VALUE;
	}

	increase_triangle_t *p_increase_triangle=NULL;
	
	do{
		
		p_increase_triangle=(increase_triangle_t *)malloc(sizeof(increase_triangle_t));
		if(NULL==p_increase_triangle){
			printf("I'm %s() at %d in %s:malloc increase_triangle_t failed!\n",__func__,__LINE__,__FILE__);
			//return NULL;
			break;
		}
	
		set_layers(p_increase_triangle,lyrs);
		set_base_value(p_increase_triangle,bs_vl);
		set_multiple(p_increase_triangle,mltpl);
	
		layer_index_ret=layer_index_init(&p_increase_triangle->layer_index,lyrs);
		if(NULL==layer_index_ret){
			free(p_increase_triangle);
			p_increase_triangle=NULL;
			//return NULL;
			break;
		}
	}while(0);
	
	return p_increase_triangle;
}


void increase_triangle_free(increase_triangle_t *increase_triangle)
{
	increase_triangle_t *p_increase_triangle=increase_triangle;
	if(NULL==p_increase_triangle){
		return;
	}

	layer_index_free(p_increase_triangle->layer_index);
	p_increase_triangle->layer_index=NULL;

	free(p_increase_triangle);
	
	return ;
}

void increase_triangle_show(increase_triangle_t *increase_triangle)
{
	increase_triangle_t *p_increase_triangle=increase_triangle;
	if(NULL==p_increase_triangle){
		return;
	}
	
	show_layer_index(p_increase_triangle->layer_index);
	
	return;
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
