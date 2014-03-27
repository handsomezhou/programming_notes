/**
  *  Copyright (C) 2014-03-28  Handsome Zhou
  */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "single_linked_list.h"

typedef struct data{
	int number;
};
	
typedef struct node{
	data_t data;
	struct node *next;
};


node_t *list_new_head_node(void)
{
	node_t *list=NULL;
	list=(node_t *)malloc(sizeof(node_t));
	if(NULL==list){
		printf("list head node malloc failed:FILE=[%s],LINE=[%d],FUNCTION=[%s()]\n",__FILE__,__LINE__,__FUNCTION__);
		return list;
	}

	list->data.number=0;
	list->next=NULL;
	
	return list;
}

node_t *list_node_append(node_t *list,node_t *node)
{
	node_t *plist=list;
	node_t *cur_node=NULL;
	assert(NULL!=plist);
	if(NULL==node){
		return plist;
	}
	cur_node=plist;
	while(NULL!=cur_node){
		cur_node=cur_node->next;
		if(NULL==cur_node){
			cur_node=node;
			break;
		}
	}

	return plist;
}

node_t *produce_node(data_t *data)
{
	data_t *pdata=data;
	assert(NULL!=pdata);
	node_t *pnode=(node_t *)malloc(sizeof(node_t));
	if(NULL==pnode){
		printf("node malloc failed:FILE=[%s],LINE=[%d],FUNCTION=[%s()]\n",__FILE__,__LINE__,__FUNCTION__);		
		return NULL;
	}

	pnode->data.number=get_number_from_data(pdata);
	pnode->next=NULL;
	
	return pnode;
}

void list_travel(const node_t *list, node_proc_fun_t *proc)
{
	assert(NULL!=list);
	const node_t *plist=list;
	node_t *cur_node=plist->next;
	while(NULL!=cur_node){
		proc(&cur_node->data);
		cur_node=cur_node->next;
	}

	return ;
}

int list_delete(node_t *list)
{
	
	return 0;
}

void show_node(void *data)
{
	data_t *pdata=(data_t *)data;
	printf("...\n");
	if(NULL==pdata){
		return ;
	}
	
	//printf("data:(%d)\n",get_number_from_data(pdata));
	printf("...\n");

	return ;
}

data_t *malloc_data(void)
{
	data_t *pdata=(data_t *)malloc(sizeof(data_t));
	if(NULL==pdata){

		return NULL;
	}

	return pdata;
}

void free_data(data_t *data)
{
	if(NULL!=data){
		free(data);
		data=NULL;
	}
}

int set_number_to_data(data_t *data, int number)
{
	data_t *pdata=data;
	if(NULL==pdata){
		return -1;
	}

	pdata->number=number;

	return 0;
}
int get_number_from_data(const data_t *data)
{
	if(NULL==data){
		return -1;
	}

	return data->number;
}

