/**
  *  Copyright (C) 2014-03-28  Handsome Zhou
  */

#ifndef SINGLE_LINKED_LIST_H
#define SINGLE_LINKED_LIST_H

//Reference:	http://zh.wikipedia.org/zh-cn/%E5%8D%95%E5%90%91%E9%93%BE%E8%A1%A8

typedef int bool_t;
#define TRUE	1
#define FALSE	0

#define LIST_SUCCEED	0
#define LIST_FAILED		(-1)

typedef int elem_t;
typedef struct node{
	elem_t elem;
	struct node *next;
}node_t,*linklist_t;

typedef int (*pf_node_compare)(const void *, const void *);
typedef int (*pf_node_travel)(void *);

linklist_t init_list(void);
void free_list(linklist_t linklist);
void clear_list(linklist_t linklist);
bool_t list_is_empty(linklist_t linklist);
int list_length(linklist_t linklist);
int get_elem(linklist_t linklist, int i, elem_t *elem);
int locate_elem(linklist_t linklist, elem_t elem, pf_node_compare node_compare);
int prior_elem(linklist_t linklist, elem_t cur_elem, elem_t *prev_elem);
int next_elem(linklist_t linklist, elem_t cur_elem, elem_t *next_elem);
int list_node_insert(linklist_t linklist, int i, elem_t elem);
int list_node_delete(linklist_t linklist, int i, elem_t *elem);
int list_node_insert_tail(linklist_t linklist, elem_t elem);
int list_node_delete_tail(linklist_t linklist, elem_t *elem);
int list_travel(linklist_t linklist,pf_node_travel node_travel);


int show_node(void *data);
int compare_node(const void *elem1, const void *elem2);

#endif	/*SINGLE_LINKED_LIST_H*/