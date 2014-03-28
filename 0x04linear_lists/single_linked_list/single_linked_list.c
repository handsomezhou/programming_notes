/**
  *  Copyright (C) 2014-03-28  Handsome Zhou
  */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "single_linked_list.h"

linklist_t init_list(void)
{
	linklist_t linklist=(node_t *)malloc(sizeof(node_t));
	if(NULL==linklist){
		printf("malloc failed:FILE=[%s],LINE=[%d],FUNCTION=[%s()]\n",__FILE__,__LINE__,__FUNCTION__);				
		return NULL;
	}

	linklist->elem=0;
	linklist->next=NULL;
	
	return linklist;
}

void free_list(linklist_t linklist)
{
	if(NULL==linklist){
		return ;
	}
	linklist_t p=linklist;
	linklist_t q=NULL;
	while(NULL!=p){
		q=p->next;
		free(p);
		p=q;
	}
	
	return;
}

void clear_list(linklist_t linklist)
{
	if(NULL==linklist){
		return;
	}
	linklist_t p=linklist->next;
	linklist_t q=NULL;
	while(NULL!=p){
		q=p->next;
		free(p);
		p=q;
	}
	linklist->next=NULL;
	
	return;
}

bool_t list_is_empty(linklist_t linklist)
{
	return (NULL==linklist->next)?(TRUE):(FALSE);
}

int list_length(linklist_t linklist)
{
	int i=0;
	if(NULL==linklist){
		return 0;
	}
	linklist_t p=linklist->next;
	while(NULL!=p){
		i++;
		p=p->next;
	}
	
	return i;
}

int get_elem(linklist_t linklist, int i, elem_t *elem)
{
	assert(NULL!=linklist);
	int j=0;
	node_t *p=linklist->next;
	
	while((NULL!=p)&&(j<i-1)){/*find the node which index is i-1.  ps:the head node's index is 0*/
		p=p->next;
		j++;
	}

	if((NULL==p)||(j>i-1)){/*greater than the length of link list or i <1*/
		return LIST_FAILED;
	}

	*elem=p->elem;	

	return LIST_SUCCEED;
}

int locate_elem(linklist_t linklist, elem_t elem, pf_node_compare node_compare)
{
	if(NULL==linklist){
		return 0;
	}
	int i=0; 	
	linklist_t p=linklist->next;
	while(NULL!=p){
		i++;
		if(node_compare(&p->elem,&elem)==0){
			return i;
		}
		p=p->next;
	}
	
	return 0;
}

int prior_elem(linklist_t linklist, elem_t cur_elem, elem_t *prev_elem)	
{

	return 0;
}

int next_elem(linklist_t linklist, elem_t cur_elem, elem_t *next_elem)
{
	
	return 0;
}

int list_node_insert(linklist_t linklist, int i, elem_t elem)
{

	assert(NULL!=linklist);
	int j=0;
	node_t *p=linklist;
	node_t *new_node=NULL;
	while((NULL!=p)&&(j<i-1)){/*find the node which index is i-1.  ps:the head node's index is 0*/
		p=p->next;
		j++;
	}

	if((NULL==p)||(j>i-1)){/*greater than the length of link list or i <1*/
		return LIST_FAILED;
	}

	new_node=(node_t *)malloc(sizeof(node_t));
	if(NULL==new_node){
		printf("malloc failed:FILE=[%s],LINE=[%d],FUNCTION=[%s()]\n",__FILE__,__LINE__,__FUNCTION__);				
		return LIST_FAILED;
	}
	new_node->elem=elem;
	new_node->next=p->next;
	p->next=new_node;
	
	return LIST_SUCCEED;
}

int list_node_delete(linklist_t linklist, int i, elem_t *elem)
{
	assert(NULL!=linklist);
	int j=0;
	node_t *p=linklist;
	node_t *q=NULL;
	
	while((NULL!=p->next)&&(j<i-1)){/*find the node which index is i-1.  ps:the head node's index is 0*/
		p=p->next;
		j++;
	}

	if((NULL==p->next)||(j>i-1)){/*greater than the length of link list or i <1*/
		return LIST_FAILED;
	}

	q=p->next;
	p->next=q->next;
	*elem=q->elem;
	free(q);
	
	return LIST_SUCCEED;
}

int list_node_insert_tail(linklist_t linklist, elem_t elem)
{
	if(NULL==linklist){
		return LIST_FAILED;
	}
	
	linklist_t p=linklist;
	node_t *new_node=NULL;
	while(NULL!=p->next){
		p=p->next;
	}

	new_node=(node_t *)malloc(sizeof(node_t));
	if(NULL==new_node){
		printf("malloc failed:FILE=[%s],LINE=[%d],FUNCTION=[%s()]\n",__FILE__,__LINE__,__FUNCTION__);				
		return LIST_FAILED;
	}
	new_node->elem=elem;
	new_node->next=NULL;

	p->next=new_node;

	return LIST_SUCCEED;
}

int list_node_delete_tail(linklist_t linklist, elem_t *elem)
{
	if(NULL==linklist){
		return LIST_FAILED;
	}
	linklist_t p=linklist;
	linklist_t q=NULL;
	while(NULL!=p->next){
		q=p;
		p=p->next;
	}

	if(NULL==q){
		return LIST_FAILED;
	}
	
	q->next=p->next;
	*elem=p->elem;
	free(p);
	
	return LIST_SUCCEED;
}

int list_travel(linklist_t linklist,pf_node_travel node_travel)
{
	assert(NULL!=linklist);
	linklist_t p=linklist->next;
	while(NULL!=p){
		node_travel((void *)&p->elem);
		p=p->next;
	}
	
	return 0;
}


int show_node(void *data)
{
	elem_t *elem=(elem_t *)data;
	printf("[%d]\n",*elem);

	return 0;
}

int compare_node(const void *elem1, const void *elem2)
{
	const elem_t *e1=(elem_t *)elem1;
	const elem_t *e2=(elem_t *)elem2;
	if(*e1>*e2){
		return 1;
	}else if(*e1<*e2){
		return -1;
	}

	return 0;
}

