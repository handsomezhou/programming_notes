/**
  *  Copyright (C) 2014-06-10  Handsome Zhou
  */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
static void layer_index_set(layer_index_t *layer_index, int base_value, int multiple);
static int calc_elem_value(int which_layer, int base_value, int multiple);
static layer_index_t *malloc_layer_index();
static void free_layer_index(layer_index_t *layer_index);
static void show_layer_index(layer_index_t *layer_index);
static int get_layer_value_sum_by_curlayer(layer_index_t *layer_index);
static int get_layer_value_sum_until_curplayer(layer_index_t *first_layer_index, int cur_player);

typedef void *(*pf_data_elem_malloc)();
typedef void (*pf_data_elem_free)(void *);
typedef void (*pf_data_elem_set)(void *,int);
typedef int (*pf_data_elem_get)(void *);
typedef void (*pf_data_elem_show)(void *);

static void *int_elem_malloc();
static void int_elem_free(void *elem);
static void int_elem_set(void *elem, int value);
static int int_elem_get(void *elem);
static void int_elem_show(void *elem);

static elem_t *elem_malloc(pf_data_elem_malloc f_data_elem_malloc);
static void elem_free(elem_t *elem,pf_data_elem_free f_data_elem_free);
static void elem_set(elem_t *elem, void *value, pf_data_elem_set f_data_elem_set);
static void elem_get(elem_t *elem,void *value, pf_data_elem_get f_data_elem_get);
static void elem_show(elem_t *elem, pf_data_elem_show f_data_elem_show);


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

static void int_elem_set(void *elem, int value)
{
	int *p_elem=(int *)elem;
	if((NULL!=p_elem)){
		*p_elem=value;
	}
}

static int int_elem_get(void *elem)
{
	int *p_elem=(int *)elem;
	if(NULL!=p_elem){
		return (*p_elem);
	}

	return ELEM_VALUE_NULL_VALUE;
}

static void int_elem_show(void *elem)
{
	int *p_elem=(int *)elem;
	if(NULL!=p_elem){
		printf("%-4d ",*p_elem);
	}
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

static void elem_set(elem_t *elem, void *value, pf_data_elem_set f_data_elem_set)
{
	elem_t *p_elem=elem;
	void *p_value=value;
	if((NULL==p_elem)||(NULL==p_value)){
		return ;
	}

	if(NULL!=f_data_elem_set){
		f_data_elem_set(p_elem->elem,*(int *)p_value);
	}	

	return;
}

static void elem_get(elem_t *elem,void *value, pf_data_elem_get f_data_elem_get)
{
	elem_t *p_elem=elem;
	void *p_value=value;
	if((NULL==p_elem)||(NULL==p_value)){
		return ;
	}

	if(NULL!=f_data_elem_get){
		*(int *)p_value=f_data_elem_get(p_elem->elem);
	}
	
}
static void elem_show(elem_t *elem, pf_data_elem_show f_data_elem_show)
{
	elem_t *p_elem=elem;
	if(NULL==p_elem){
		return;
	}

	if(NULL!=f_data_elem_show){
		f_data_elem_show(p_elem->elem);
	}

	return;

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
#if 0
			cur_layer_index=first_layer_index;
			while(NULL!=cur_layer_index){
				next_layer_index=cur_layer_index->next_layer;
				//free(cur_layer_index);
				free_layer_index(cur_layer_index);
				cur_layer_index=next_layer_index;
			}
#endif			
			layer_index_free(first_layer_index);
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
		free_layer_index(cur_layer_index);
		cur_layer_index=next_layer_index;
	}

	return;
	
}

static void layer_index_set(layer_index_t *layer_index, int base_value, int multiple)
{
	layer_index_t *p_layer_index=layer_index;
	elem_t *p_elem=NULL;
	int elem_value=0;
	int which_layer=0;
	if(NULL==p_layer_index){
		return;
	}

	while(NULL!=p_layer_index){
		++which_layer;
		elem_value=calc_elem_value(which_layer,base_value,multiple);
		p_elem=p_layer_index->elem;
		while(NULL!=p_elem){
			elem_set(p_elem,&elem_value,int_elem_set);
			p_elem=p_elem->next_elem;
		}
		p_layer_index=p_layer_index->next_layer;
	}
	
	return;
}

static int calc_elem_value(int which_layer, int base_value, int multiple)
{
	//base_value*(multiple^(cur_layer-1))
	int elem_value=-1;
	elem_value=base_value*(pow(multiple,(which_layer-1)));
	
	return elem_value;
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
	elem_t *p_elem=NULL;
	int i=0;
	if(NULL==p_layer_index){
		return;
	}

	while(NULL!=p_layer_index){
		p_elem=p_layer_index->elem;
		printf("[layer=%-2d]",++i);
		while(NULL!=p_elem){
			elem_show(p_elem,int_elem_show);
			p_elem=p_elem->next_elem;
		}
		printf("\n");
		
		p_layer_index=p_layer_index->next_layer;
	}
}

static int get_layer_value_sum_by_curlayer(layer_index_t *layer_index)
{
	layer_index_t *p_layer_index=layer_index;
	elem_t *p_elem=NULL;
	int layer_value_sum=0;
	int value=0;
	if(NULL==p_layer_index){
		return ELEM_VALUE_SUM_NULL_VALUE;
	}

	p_elem=p_layer_index->elem;
	while(NULL!=p_elem){
		elem_get(p_elem,&value,int_elem_get);
		layer_value_sum +=value;
		p_elem=p_elem->next_elem;
	}

	return layer_value_sum;
}

static int get_layer_value_sum_until_curplayer(layer_index_t *first_layer_index, int cur_player)
{
	layer_index_t *p_layer_index=first_layer_index;
	int count_layer=0;
	int layer_value_sum=0;
	if(NULL==p_layer_index){
		return ELEM_VALUE_SUM_NULL_VALUE;
	}

	while(NULL!=p_layer_index){
		count_layer++;
		if(count_layer>cur_player){
			break;
		}
		layer_value_sum += get_layer_value_sum_by_curlayer(p_layer_index);
		p_layer_index=p_layer_index->next_layer;
	}

	return layer_value_sum;
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
		p_increase_triangle->layer_index=NULL;
	
		layer_index_ret=layer_index_init(&p_increase_triangle->layer_index,lyrs);
		if(NULL==layer_index_ret){
			free(p_increase_triangle);
			p_increase_triangle=NULL;
			//return NULL;
			break;
		}

		layer_index_set(p_increase_triangle->layer_index,p_increase_triangle->base_value,p_increase_triangle->multiple);
		
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
	int i=0;
	int layer_value_sum=0;
	int layers_value_sum=0;
	int all_value_sum=0;
	printf("\n");
	printf("layers=[%d],base_value=[%d],multiple=[%d];\n",get_layers(p_increase_triangle),get_base_value(p_increase_triangle),get_multiple(p_increase_triangle));
	show_layer_index(p_increase_triangle->layer_index);
	printf("\n");
	
	for(i=0; i<p_increase_triangle->layers; i++){
		layer_value_sum=get_layer_value_sum(p_increase_triangle,i+1);		
		layers_value_sum=get_increase_triangle_layers_value_sum(p_increase_triangle,i+1);
		printf("layer=%-2d,layer_sum=[%-5d] 2*layer_sum=[%-5d];layers_sum=[%-5d],2*layer_sum-layers_num=[%-5d]\n",i+1,layer_value_sum,2*layer_value_sum,layers_value_sum,2*layer_value_sum-layers_value_sum);
			
	}
	printf("\n");

	all_value_sum=get_increase_triangle_all_value_sum(p_increase_triangle);
	printf("all layers sum=[%-5d]\n", all_value_sum);
	printf("\n");
	
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

int get_increase_triangle_all_value_sum(increase_triangle_t *increase_triangle)
{
	increase_triangle_t *p_increase_triangle=increase_triangle;
	layer_index_t *p_layer_index=NULL;
	int all_value_sum=0;
	if(NULL==p_increase_triangle){
		return ELEM_VALUE_SUM_NULL_VALUE;
	}

	p_layer_index=p_increase_triangle->layer_index;
	while(NULL!=p_layer_index){
		all_value_sum+=get_layer_value_sum_by_curlayer(p_layer_index);
		p_layer_index=p_layer_index->next_layer;
	}
	
	return all_value_sum;
}

int get_increase_triangle_layers_value_sum(increase_triangle_t * increase_triangle, int layers_num)
{
	increase_triangle_t *p_increase_triangle=increase_triangle;
	int layers_value_sum=0;
	if(NULL==p_increase_triangle){
		return ELEM_VALUE_SUM_NULL_VALUE;
	}
	
	layers_value_sum=get_layer_value_sum_until_curplayer(p_increase_triangle->layer_index,layers_num);
		
	return layers_value_sum;
}

int get_layer_value_sum(increase_triangle_t *increase_triangle, int which_layer)
{
	increase_triangle_t *p_increase_triangle=increase_triangle;
	layer_index_t *p_layer_index=NULL;
	elem_t *p_elem=NULL;
	int count_layer=0;
	int layer_value_sum=0;
	if(NULL==p_increase_triangle){
		return ELEM_VALUE_SUM_NULL_VALUE;
	}
		
	if(which_layer<=0 || which_layer>p_increase_triangle->layers){
		return ELEM_VALUE_SUM_NULL_VALUE;
	}

	p_layer_index=p_increase_triangle->layer_index;

	while(NULL!=p_layer_index){
		count_layer++;
		if(count_layer==which_layer){
			p_elem=p_layer_index->elem;
			layer_value_sum += get_layer_value_sum_by_curlayer(p_layer_index);
			break;
		}
		p_layer_index=p_layer_index->next_layer;
	}
	
	return layer_value_sum;
}

